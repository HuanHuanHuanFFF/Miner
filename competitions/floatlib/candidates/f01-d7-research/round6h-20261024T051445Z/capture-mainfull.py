"""R12 opt-in actual MainFull observer; compatible with the fd17 run_gate API.

The unmodified official gate still owns compilation, checks and timing. Only its
statement event is observed. ELF copies stay in the runner's private temporary
directory; all nm/disassembly tools run after the original gate exits.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
import os
import re
import tempfile
import time
import uuid

LEGACY_SHA256 = 'fd17f35a4ef1bc1b1df2afe5fcfe39691d88e7e605968acbe3c38df09df9078b'
COPY_SECONDS = 3.0
TOTAL_LIMIT = 32 * 1024 * 1024
FILE_LIMIT = 8 * 1024 * 1024
MAX_FILES = 24
MAX_SYMBOLS = 20
OBJECT = re.compile(r'^(MainFull|Submission|BenchSuite)(?:\.c)?\.o(?:\.(?:export|noexport))?$')
TRACE = re.compile(r'^(MainFull|Submission|BenchSuite)(?:\.c(?:\.o(?:\.(?:export|noexport))?)?|\.o(?:\.(?:export|noexport))?|\.olean|\.ilean)?\.trace$')


def load_legacy():
    path = Path(__file__).with_name('scalar-capture-legacy-fd17.py')
    if hashlib.sha256(path.read_bytes()).hexdigest() != LEGACY_SHA256:
        raise RuntimeError('exact fd17 legacy capture module hash mismatch')
    spec = importlib.util.spec_from_file_location('r12_legacy_' + uuid.uuid4().hex, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def _snapshot(m, cwd, folder, private_dir, expected, record, staged, cancel):
    snap = record['snapshot']
    origin = record['_t0']
    snap.update(started_at_utc=m.utc(), started_seconds=time.monotonic() - origin, modules={})
    deadline = time.monotonic() + COPY_SECONDS
    try:
        m.require(not cancel.is_set(), 'snapshot cancelled before capture')
        m.require(folder is not None and private_dir is not None and expected is not None, 'capture setup unavailable')
        work = cwd / 'lean/work/Submission.lean'
        compiled = m.read_regular(work, 256000, deadline)
        snap['compiled_source'] = {'source': str(work), 'bytes': len(compiled), 'sha256': m.sha(compiled),
                                   'matches_kernel': m.sha(compiled) == expected,
                                   'artifact': 'compiled-Submission.lean'}
        m.require(m.sha(compiled) == expected, 'compiled Submission.lean differs from requested exact source')
        (folder / 'compiled-Submission.lean').write_bytes(compiled)
        upper = cwd / '.sandbox/layer/upper'
        shared = cwd / 'lean/.lake/build'
        # MainFull must be from this fresh candidate overlay. Never fall back to
        # the shipped/champion MainFull in the shared cache.
        candidates = []
        for module in ('MainFull', 'Submission', 'BenchSuite'):
            build = upper
            kind = 'original-candidate-layer'
            if module == 'BenchSuite' and not any((upper / 'ir').glob('BenchSuite*')):
                build, kind = shared, 'unchanged-shared-benchmark-module'
            for directory in (build / 'ir', build / 'lib/lean'):
                if directory.is_dir():
                    for path in directory.glob(module + '*'):
                        if path.name == module + '.c' or TRACE.fullmatch(path.name) or OBJECT.fullmatch(path.name):
                            candidates.append((module, kind, build, path))
        candidates = sorted(set(candidates), key=lambda row: (
            ('MainFull', 'Submission', 'BenchSuite').index(row[0]), row[3].name != row[0] + '.c', str(row[3])))
        m.require(len(candidates) <= MAX_FILES, 'capture file count exceeds bound')
        total = 0
        for module, kind, build, path in candidates:
            m.require(not cancel.is_set() and time.monotonic() <= deadline, 'snapshot stopped at time/cancellation bound')
            m.require(path.resolve().is_relative_to(build.resolve()), 'source path leaves selected build tree')
            raw = m.read_regular(path, min(FILE_LIMIT, TOTAL_LIMIT - total), deadline)
            total += len(raw)
            item = {'source': str(path), 'module': module, 'build_origin': kind,
                    'bytes': len(raw), 'sha256': m.sha(raw), 'state': 'VERIFIED_CAPTURED_BYTES'}
            group = snap['modules'].setdefault(module, {'files': [], 'objects': [], 'build_origin': kind})
            if OBJECT.fullmatch(path.name):
                m.require(raw.startswith(b'\x7fELF'), 'selected object is not ELF')
                fd, name = tempfile.mkstemp(prefix='.capture-object-', suffix='.tmp', dir=private_dir)
                private = Path(name)
                staged.append((private, item))
                with os.fdopen(fd, 'wb') as stream:
                    m.write_all(stream, raw)
                item.update(temporary_copy_sha256=m.sha(raw), object_retained=False)
                snap['objects'].append(item)
                group['objects'].append(item['sha256'])
            else:
                name = f'file-{len(snap["files"])}-{path.name}'
                (folder / name).write_bytes(raw)
                item.update(artifact=name, kind='c' if path.name == module + '.c' else 'trace')
                snap['files'].append(item)
                group['files'].append(name)
        # Link trace is evidence, not a retained executable or a final-link claim.
        for suffix in ('.trace', '.hash'):
            path = upper / ('bin/benchFull' + suffix)
            if path.is_file():
                raw = m.read_regular(path, min(FILE_LIMIT, TOTAL_LIMIT - total), deadline)
                total += len(raw)
                name = 'original-benchFull' + suffix + '.txt'
                (folder / name).write_bytes(raw)
                snap['files'].append({'source': str(path), 'module': 'benchFull', 'kind': 'link-provenance',
                    'bytes': len(raw), 'sha256': m.sha(raw), 'artifact': name})
        for module in ('MainFull', 'Submission'):
            m.require(any(f.get('module') == module and f['kind'] == 'c' for f in snap['files']), module + '.c absent from original layer')
            m.require(any(f.get('module') == module and f['kind'] == 'trace' for f in snap['files']), module + ' trace absent')
            m.require(any(o['module'] == module for o in snap['objects']), module + ' original ELF absent')
        m.require(m.sha(m.read_regular(work, 256000, deadline)) == expected, 'compiled source changed during capture')
        snap.update(state='CAPTURED', total_c_trace_object_bytes=total,
            mainfull_identity='Original candidate layer observed at original statement event with exact compiled source before/after',
            final_link_identity='UNKNOWN: linked binary bytes not retained; inspect available benchFull trace')
    except Exception as exc:
        snap.update(state='UNKNOWN', error=str(exc))
    finally:
        snap.update(finished_at_utc=m.utc(), finished_seconds=time.monotonic() - origin)
        if folder is not None:
            try:
                m.save_json(folder / 'snapshot.json', snap)
            except Exception as exc:
                record['errors'].append('snapshot metadata: ' + str(exc))


def c_functions(raw):
    text = raw.decode('utf-8', errors='replace')
    definitions = re.findall(r'^(?:(?:LEAN_EXPORT|static)\s+)*(?:lean_object\*|uint32_t|uint8_t|uint64_t|int|unsigned|void|size_t|double|float)\s+([A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\s*\{', text, re.M)
    closures = re.findall(r'\.m_fun\s*=\s*\(void\*\)\s*([A-Za-z_][A-Za-z0-9_]*)', text)
    return {'defined_functions': sorted(set(definitions)), 'closure_targets': sorted(set(closures))}


def bench_suite_symbol(name):
    # Private Array loops use runScalar_spec__0, not runScalar___spec__0.
    return bool(re.search(r'(?:runScalar|measure|Suite_run)(?:___|_spec__|$)', name))


def _disassemble(m, staged, folder, deadline, record):
    result = {'state': 'UNKNOWN', 'objects': [], 'selected_symbols': 0, 'selection_order': [],
              'selection_basis': 'MainFull actual C definitions/closure targets plus actual nm; then immutable BenchSuite runScalar/measure chain; then Submission scalar wrappers',
              'stems_without_nm_matches': [], 'nm_inventory_complete': True}
    scans = {}
    for item in record['snapshot']['files']:
        if item.get('kind') == 'c':
            scans[item['module']] = c_functions((folder / item['artifact']).read_bytes())
    result['actual_c_symbol_scan'] = scans
    queue = []
    for index, (private, obj) in enumerate(staged):
        entry = {'source': obj['source'], 'object_sha256': obj['sha256'], 'module': obj['module'], 'symbols': [],
                 'matching_symbols': 0, 'omitted_symbols': [], 'selection_truncated': False}
        result['objects'].append(entry)
        entry['nm'] = m._bounded_tool(['nm', '-S', '--defined-only', '--radix=x', str(private)],
            folder / f'nm-{index}.txt', min(4, max(.01, deadline-time.monotonic())), 2*1024*1024)
        entry['relocations'] = m._bounded_tool(['objdump', '-r', str(private)],
            folder / f'relocations-{index}.txt', min(4, max(.01, deadline-time.monotonic())), 4*1024*1024)
        if not entry['nm'].get('ok'):
            result['nm_inventory_complete'] = False
            continue
        module = obj['module']
        actual = scans.get(module, {})
        for line in (folder / entry['nm']['artifact']).read_text(encoding='utf-8', errors='replace').splitlines():
            fields = line.split()
            if len(fields) != 4 or fields[2] not in 'TtWw':
                continue
            name = fields[3]
            if module == 'MainFull':
                wanted = name in actual.get('defined_functions', []) or name in actual.get('closure_targets', [])
                priority = 1 if '___boxed' in name else 0
            elif module == 'BenchSuite':
                wanted = bench_suite_symbol(name)
                # Capture the actual per-element Array loop before setup/measure
                # wrappers can consume the finite symbol budget.
                priority = (2 if 'runScalar_spec__' in name else 3) + (1 if '___boxed' in name else 0)
            else:
                wanted = bool(re.fullmatch(r'lp_competition_Submission_(?:add|mul|nativeMul)(?:___[A-Za-z0-9_]+)?', name))
                priority = 6 if '___boxed' in name else 5
            if wanted:
                entry['matching_symbols'] += 1
                queue.append((priority, name, index, private, entry, fields[0], fields[1]))
    queue.sort(key=lambda row: (row[0], '___lam__' not in row[1], row[1], row[2]))
    complete = result['nm_inventory_complete']
    for priority, name, index, private, entry, address, size in queue:
        if result['selected_symbols'] >= MAX_SYMBOLS or time.monotonic() >= deadline:
            complete = False
            entry['selection_truncated'] = True
            entry['omitted_symbols'].append({'symbol': name, 'size_hex': size, 'priority': priority,
                                             'reason': 'symbol_budget_or_deadline'})
            continue
        assembly = m._bounded_tool(['objdump', '-dr', '--no-show-raw-insn', '-Mintel', '--disassemble=' + name, str(private)],
            folder / f'asm-{index}-{len(entry["symbols"])}.txt', min(4, max(.01, deadline-time.monotonic())), 4*1024*1024)
        entry['symbols'].append({'symbol': name, 'address_hex': hex(int(address, 16)),
                                 'size_hex': size, 'size_bytes': int(size, 16),
                                 'priority': priority, 'assembly': assembly})
        result['selection_order'].append({'object_index': index, 'symbol': name, 'priority': priority})
        result['selected_symbols'] += 1
        complete &= assembly.get('ok', False)
    if result['selected_symbols']:
        result['state'] = 'COMPLETE_SELECTED_SYMBOLS' if complete else 'PARTIAL'
    else:
        result['error'] = 'No requested actual symbols or postprocess tool unavailable'
    return result


def run_gate(argv, cwd, env, log_path, timeout, output, kernel):
    m = load_legacy()
    m._snapshot = lambda *args: _snapshot(m, *args)
    m._disassemble = lambda *args: _disassemble(m, *args)
    m.COPY_SECONDS = COPY_SECONDS
    m.TOTAL_LIMIT = TOTAL_LIMIT
    m.MAX_FILES = MAX_FILES
    m.MAX_SYMBOLS = MAX_SYMBOLS
    # fd17 owns unchanged argv/env, byte-exact tee, timeout semantics and all
    # private object cleanup. Exceptions still carry its codegen_record.
    try:
        completed, record = m.run_gate(argv, cwd, env, log_path, timeout, output, kernel)
    except BaseException as exc:
        record = getattr(exc, 'codegen_record', None)
        if record is not None:
            _finish_record(m, record)
        raise
    _finish_record(m, record)
    return completed, record


def _finish_record(m, record):
    record['r12_mainfull_capture'] = {'wrapper_sha256': m.sha(Path(__file__).read_bytes()),
        'legacy_module_sha256': LEGACY_SHA256, 'actual_mainfull_required': True,
        'disassembly_after_original_gate_exit': True, 'confirmation_allowed': False}
    if record.get('artifact_directory'):
        try:
            m.save_json(Path(record['artifact_directory']) / 'capture-record.json', record)
        except Exception as exc:
            record.setdefault('errors', []).append('R12 wrapper metadata: ' + str(exc))
