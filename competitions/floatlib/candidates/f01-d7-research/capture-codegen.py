"""Opt-in read-only capture of an ORIGINAL gate's live statement output.

run_gate(argv,cwd,env,log_path,timeout,output,kernel) returns (CompletedProcess,record).
Timeouts retain subprocess.run semantics: kill/drain/cleanup, then raise TimeoutExpired
with .codegen_record attached. Capture failure never changes the gate's return code.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import base64
import hashlib
import json
import os
import re
import shutil
import signal
import stat
import subprocess
import sys
import tempfile
import threading
import time
import uuid

MARKER = b'[statement] ok'
SCORE = b'[score]'
FILE_LIMIT = 8 * 1024 * 1024
TOTAL_LIMIT = 24 * 1024 * 1024
MAX_FILES = 8
COPY_SECONDS = 2.0
POST_SECONDS = 30.0
MAX_SYMBOLS = 20
OBJECT = re.compile(r'^Submission(?:\.c)?\.o(?:\.(?:export|noexport))?$')
TRACE = re.compile(r'^Submission(?:\.c(?:\.o(?:\.(?:export|noexport))?)?|\.o(?:\.(?:export|noexport))?|\.olean|\.ilean)?\.trace$')
HOT_STEMS = ('R11RawIndex_loop', 'Packed8Index_loop', 'R11CrossRows_wordLoop', 'R11CrossRows_dot8')
FOLD_OUTPUT_STEMS = ('RowStream_output', 'DirectContinuous_output', 'DirectContinuous_row',
                     'BatchLocalPacked_output', 'BatchLocalPacked_batchStep',
                     'BatchLocalPacked_row', 'BatchLocalPacked_group')
OUTPUT_STEMS = ('R11RawA_core', 'R11RawIndex_runDot', 'RowStream_emit', 'RowStream_group',
                'RowStream_row', 'RowStream_output', 'RowStream_core', 'R11CrossRows_core',
                'R11CrossRows_packGeneral', 'R11CrossRows_packShared', 'R11CrossRows_finish8',
                'R11CrossRows_words', 'DirectContinuous_core', 'DirectContinuous_output',
                'DirectContinuous_row', 'BatchLocalPacked_core', 'BatchLocalPacked_output',
                'BatchLocalPacked_batchStep', 'BatchLocalPacked_row', 'BatchLocalPacked_group',
                'BatchLocalPacked_packBatch')
LEGACY_STEMS = ('NativeFinal_dot', 'NativeFinal_dotLoop', 'NativeFinal_sumLoop', 'dotLoop',
                'DirectSmall_core', 'NativeDecodeSumWord_loop', 'Packed10Index_loop', 'LowZero')
SCALAR_STEMS = ('add', 'mul', 'nativeMul')
STEMS = HOT_STEMS + OUTPUT_STEMS + LEGACY_STEMS + SCALAR_STEMS


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def utc():
    return datetime.now(timezone.utc).isoformat()


def require(ok, message):
    if not ok:
        raise RuntimeError(message)


def write_all(stream, raw):
    view = memoryview(raw)
    while view:
        count = stream.write(view)
        if not count:
            raise OSError('short output write')
        view = view[count:]


def read_regular(path, limit, deadline):
    """No following file symlinks/FIFOs; deadline checked between bounded reads."""
    before = path.lstat()
    require(stat.S_ISREG(before.st_mode) and not path.is_symlink(), 'not a regular non-symlink file: ' + str(path))
    flags = os.O_RDONLY | getattr(os, 'O_BINARY', 0) | getattr(os, 'O_NOFOLLOW', 0) | getattr(os, 'O_NONBLOCK', 0)
    fd = os.open(path, flags)
    with os.fdopen(fd, 'rb') as stream:
        first = os.fstat(stream.fileno())
        require(stat.S_ISREG(first.st_mode) and first.st_size <= limit, 'file type/size limit: ' + str(path))
        chunks, size = [], 0
        while True:
            require(time.monotonic() <= deadline, 'capture read deadline')
            chunk = stream.read(min(1024 * 1024, limit + 1 - size))
            if not chunk:
                break
            chunks.append(chunk)
            size += len(chunk)
            require(size <= limit, 'capture file grew beyond limit')
        last = os.fstat(stream.fileno())
    require((first.st_size, first.st_mtime_ns, first.st_ino, first.st_dev) ==
            (last.st_size, last.st_mtime_ns, last.st_ino, last.st_dev), 'file changed while reading')
    raw = b''.join(chunks)
    require(len(raw) == first.st_size, 'incomplete capture read')
    return raw


def save_json(path, value):
    path.write_text(json.dumps(value, indent=2) + '\n', encoding='utf-8')


def _stage_events(raw, env, finished_at):
    """Parse ORIGINAL log timestamps, separately from reader arrival times."""
    child_env = os.environ if env is None else env
    explicit_utc = child_env.get('TZ') in ('UTC', 'Etc/UTC', 'GMT', 'UTC0')
    events = []
    ansi = re.compile(rb'\x1b\[[0-?]*[ -/]*[@-~]')
    timestamp = re.compile(rb'(\d{4}-\d\d-\d\d[ T]\d\d:\d\d:\d\d(?:\.\d{1,6})?(?:Z|[+-]\d\d:?\d\d)?)')
    for line in raw.splitlines(keepends=True):
        clean = ansi.sub(b'', line)
        stage = re.search(rb'\[(statement|kernel|axioms|score)\] ok\b', clean)
        if not stage:
            continue
        event = {'stage': stage.group(1).decode('ascii'), 'raw_line_base64': base64.b64encode(line).decode('ascii'),
                 'emitted_at_utc': None, 'timestamp_basis': 'UNKNOWN'}
        match = timestamp.search(clean[:stage.start()])
        if match:
            stamp = match.group(1).decode('ascii')
            event['timestamp_text'] = stamp
            try:
                parsed = datetime.fromisoformat(stamp.replace('Z', '+00:00'))
                if parsed.tzinfo is not None:
                    event['timestamp_basis'] = 'explicit original log timezone'
                elif explicit_utc:
                    parsed = parsed.replace(tzinfo=timezone.utc)
                    event['timestamp_basis'] = 'original child environment explicitly sets TZ=' + child_env['TZ']
                if parsed.tzinfo is not None:
                    event['emitted_at_utc'] = parsed.astimezone(timezone.utc).isoformat()
            except ValueError:
                event['timestamp_basis'] = 'UNKNOWN: unparseable original timestamp'
        events.append(event)
    axioms = next((e for e in events if e['stage'] == 'axioms'), None)
    comparison = {'state': 'UNKNOWN', 'reason': 'capture finish or original axioms emission timestamp/timezone unavailable',
                  'reader_arrival_is_not_emission_time': True}
    if finished_at and axioms and axioms['emitted_at_utc']:
        finish = datetime.fromisoformat(finished_at)
        emitted_lower_bound = datetime.fromisoformat(axioms['emitted_at_utc'])
        before = finish <= emitted_lower_bound
        comparison = {'state': 'VERIFIED_BEFORE_RECORDED_AXIOMS_TIMESTAMP' if before else 'UNKNOWN_POSSIBLE_OVERLAP',
                      'capture_finished_at_utc': finished_at,
                      'axioms_emitted_timestamp_lower_bound_utc': axioms['emitted_at_utc'],
                      'seconds_to_recorded_axioms_lower_bound': (emitted_lower_bound - finish).total_seconds(),
                      'reader_arrival_is_not_emission_time': True}
    return {'events': events, 'capture_vs_axioms_emission': comparison}


def _snapshot(cwd, folder, private_dir, expected, record, staged, cancel):
    snap = record['snapshot']
    origin = record['_t0']
    snap.update(started_at_utc=utc(), started_seconds=time.monotonic() - origin)
    deadline = time.monotonic() + COPY_SECONDS
    try:
        require(not cancel.is_set(), 'snapshot cancelled before capture')
        require(folder is not None and private_dir is not None and expected is not None, 'capture setup/kernel identity unavailable')
        work = cwd / 'lean/work/Submission.lean'
        compiled = read_regular(work, 256000, deadline)
        snap['compiled_source'] = {'source': str(work), 'bytes': len(compiled), 'sha256': sha(compiled),
                                   'matches_kernel': sha(compiled) == expected}
        require(sha(compiled) == expected, 'compiled Submission.lean does not match exact requested kernel')
        (folder / 'compiled-Submission.lean').write_bytes(compiled)
        snap['compiled_source']['artifact'] = 'compiled-Submission.lean'
        upper = cwd / '.sandbox/layer/upper'
        candidates = []
        for directory in (upper / 'ir', upper / 'lib/lean'):
            if directory.is_dir():
                candidates.extend(p for p in directory.glob('Submission*')
                                  if p.name == 'Submission.c' or TRACE.fullmatch(p.name) or OBJECT.fullmatch(p.name))
        candidates = sorted(set(candidates), key=lambda p: (p.name != 'Submission.c', str(p)))
        total = 0
        for path in candidates[:MAX_FILES]:
            require(not cancel.is_set() and time.monotonic() <= deadline, 'snapshot stopped at time/cancellation limit')
            require(path.resolve().is_relative_to(upper.resolve()), 'source path leaves statement upper layer')
            raw = read_regular(path, min(FILE_LIMIT, TOTAL_LIMIT - total), deadline)
            total += len(raw)
            item = {'source': str(path), 'bytes': len(raw), 'sha256': sha(raw), 'state': 'VERIFIED_CAPTURED_BYTES'}
            if OBJECT.fullmatch(path.name):
                require(raw.startswith(b'\x7fELF'), 'Submission object is not ELF')
                require(not cancel.is_set(), 'object staging cancelled')
                fd, name = tempfile.mkstemp(prefix='.capture-object-', suffix='.tmp', dir=private_dir)
                private = Path(name)
                staged.append((private, item))  # Register before writing so finally can remove it.
                with os.fdopen(fd, 'wb') as stream:
                    write_all(stream, raw)
                item['temporary_copy_sha256'] = sha(raw)
                item['object_retained'] = False
                snap['objects'].append(item)
            else:
                name = f'file-{len(snap["files"])}-{path.name}'
                (folder / name).write_bytes(raw)
                item.update(artifact=name, kind='c' if path.name == 'Submission.c' else 'trace')
                snap['files'].append(item)
        require(len(candidates) <= MAX_FILES, 'statement own-file count exceeds capture limit')
        require(any(f['kind'] == 'c' for f in snap['files']), 'Submission.c absent at event (possibly already wiped)')
        require(any(f['kind'] == 'trace' for f in snap['files']), 'Submission trace absent at event')
        require(snap['objects'], 'own Submission ELF object absent at event')
        require(sha(read_regular(work, 256000, deadline)) == expected, 'compiled source changed during snapshot')
        snap.update(state='CAPTURED', total_c_trace_object_bytes=total)
    except Exception as exc:
        snap.update(state='UNKNOWN', error=str(exc))
    finally:
        snap.update(finished_at_utc=utc(), finished_seconds=time.monotonic() - origin)
        if folder is not None:
            try:
                save_json(folder / 'snapshot.json', snap)
            except Exception as exc:
                record['errors'].append('snapshot metadata: ' + str(exc))


def _bounded_tool(argv, artifact, seconds, limit):
    """Run a post-gate tool with a byte cap and timeout; no original gate involved."""
    started = time.monotonic()
    info = {'argv': argv, 'artifact': artifact.name, 'timeout_seconds': seconds, 'byte_limit': limit}
    try:
        proc = subprocess.Popen(argv, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        state = {'bytes': 0, 'limited': False, 'error': None}
        with artifact.open('wb') as stream:
            def drain():
                try:
                    while chunk := proc.stdout.read(65536):
                        available = max(0, limit - state['bytes'])
                        write_all(stream, chunk[:available])
                        state['bytes'] += min(len(chunk), available)
                        if len(chunk) > available:
                            state['limited'] = True
                            proc.kill()
                except Exception as exc:
                    state['error'] = str(exc)
                    proc.kill()
            reader = threading.Thread(target=drain, daemon=True)
            reader.start()
            try:
                proc.wait(timeout=max(.01, seconds))
                info['timed_out'] = False
            except subprocess.TimeoutExpired:
                info['timed_out'] = True
                proc.kill()
                proc.wait(timeout=2)
            reader.join(timeout=2)
            info.update(returncode=proc.returncode, output_limited=state['limited'], reader_error=state['error'],
                        reader_complete=not reader.is_alive())
        raw = artifact.read_bytes()
        info.update(bytes=len(raw), sha256=sha(raw))
        info['ok'] = proc.returncode == 0 and not info['timed_out'] and not state['limited'] and not state['error'] and not reader.is_alive()
    except Exception as exc:
        info.update(ok=False, error=str(exc))
    info['seconds'] = time.monotonic() - started
    return info


def _symbol_info(name):
    """Recognize a function boundary, including actual private specializations."""
    if '___boxed' in name:
        return None
    # Actual 911 globals differ from the private Array helpers below. Only the
    # exact Fin.foldl specialization encoding and named output chains qualify.
    fold = re.fullmatch(
        r'(?:lp_competition_Fin_foldl_loop|lp(?:_competition_)?__private_[A-Za-z0-9_]+__Fin_foldl_loop)'
        r'___at___00Submission_([A-Za-z0-9_]+)_spec__[0-9]+(?:___redArg)?', name)
    if fold is not None and fold.group(1) in FOLD_OUTPUT_STEMS:
        return {'stem': fold.group(1), 'priority': 0,
                'private': not name.startswith('lp_competition_Fin_foldl_loop___at___'),
                'short': name, 'specialized_output': True}
    encoded_fold = re.fullmatch(
        r'(?:lp_competition_Fin_foldl_loop|lp(?:_competition_)?__private_[A-Za-z0-9_]+__Fin_foldl_loop)'
        r'___at___00Submission_([A-Za-z0-9_]+)', name)
    if encoded_fold is not None and any(encoded_fold.group(1).startswith(stem + '_spec__')
                                       for stem in FOLD_OUTPUT_STEMS):
        return None  # Malformed owned fold suffix must not enter the old private fallback.
    prefix = 'lp_competition_Submission_'
    private = False
    if name.startswith(prefix):
        short = name[len(prefix):]
    else:
        # Source-private declarations and compiler-generated array/Fin helpers differ.
        match = re.fullmatch(r'lp(?:_competition_)?__private_[A-Za-z0-9_]+__Submission_([A-Za-z0-9_]+)', name)
        if match is None:
            match = re.fullmatch(r'lp(?:_competition_)?__private_[A-Za-z0-9_]+'
                                 r'___at___00Submission_([A-Za-z0-9_]+)', name)
        if match is None:
            return None
        short, private = match.group(1), True
    for priority, stems in enumerate((HOT_STEMS, OUTPUT_STEMS, LEGACY_STEMS, SCALAR_STEMS)):
        for stem in stems:
            if not short.startswith(stem):
                continue
            tail = short[len(stem):]
            if (not tail or tail.startswith('___') or
                    (private and re.fullmatch(r'_spec__[0-9]+(?:___[A-Za-z0-9_]+)?', tail)) or
                    (stem == 'LowZero' and re.fullmatch(r'_[A-Za-z][A-Za-z0-9_]*', tail))):
                return {'stem': stem, 'priority': priority, 'private': private, 'short': short}
    return None


def _selected(name):
    return _symbol_info(name) is not None


def _symbol_sort_key(name):
    info = _symbol_info(name)
    require(info is not None, 'sorting an unselected symbol')
    # Prefer computational redArg bodies to erased-argument wrappers.
    variant = (-2 if '___redArg' in info['short'] else -1) if info.get('specialized_output') else (
        0 if '___redArg' in info['short'] else 1 if '___lam__' in info['short'] else 2)
    return info['priority'], variant, info['stem'], name


def _disassemble(staged, folder, deadline, record):
    nm, objdump = shutil.which('nm'), shutil.which('objdump')
    result = {'state': 'UNKNOWN', 'nm': nm, 'objdump': objdump, 'objects': [], 'selected_symbols': 0,
              'selection_order': [], 'selection_priority': ['new-hot-loop', 'new-core-pack-output',
                                                          'legacy-native', 'legacy-scalar']}
    if not nm or not objdump or folder is None:
        result['error'] = 'nm/objdump or artifact directory unavailable'
        return result
    complete, pending, matched = True, [], set()
    # Read each existing object first so an old object's scalar names cannot consume
    # the global symbol cap before a later object's new hot loop is considered.
    for index, (private, obj) in enumerate(staged):
        if time.monotonic() >= deadline:
            complete = False
            result['objects_not_inspected'] = len(staged) - index
            break
        symbols_file = folder / f'nm-{index}.txt'
        tool = _bounded_tool([nm, '-S', '--defined-only', '--radix=x', str(private)], symbols_file,
                             min(4, deadline - time.monotonic()), 2 * 1024 * 1024)
        entry = {'object_sha256': obj['sha256'], 'source': obj['source'], 'nm': tool, 'symbols': [],
                 'matching_symbols': 0, 'omitted_symbols': [], 'selection_truncated': False}
        result['objects'].append(entry)
        if not tool['ok']:
            complete = False
            continue
        for line in symbols_file.read_text(encoding='utf-8', errors='replace').splitlines():
            fields = line.split()
            if len(fields) == 4 and fields[2] in 'TtWw' and _selected(fields[3]):
                try:
                    address, size, name = int(fields[0], 16), int(fields[1], 16), fields[3]
                except ValueError:
                    complete = False
                    continue
                info = _symbol_info(name)
                matched.add(info['stem'])
                entry['matching_symbols'] += 1
                pending.append((index, private, entry, address, size, name))
    result['nm_inventory_complete'] = complete
    result['stems_without_nm_matches'] = [stem for stem in STEMS if stem not in matched]
    pending.sort(key=lambda item: (_symbol_sort_key(item[5]), item[0]))
    for index, private, entry, address, size, name in pending:
        reason = ('symbol_budget' if result['selected_symbols'] >= MAX_SYMBOLS else
                  'deadline' if time.monotonic() >= deadline else None)
        info = _symbol_info(name)
        if reason is not None:
            complete = False
            entry['selection_truncated'] = True
            entry['omitted_symbols'].append({'symbol': name, 'size_bytes': size,
                                             'priority': info['priority'], 'reason': reason})
            continue
        artifact = folder / f'asm-{index}-{len(entry["symbols"])}.txt'
        assembly = _bounded_tool([objdump, '-dr', '--no-show-raw-insn', '-Mintel', '--disassemble=' + name, str(private)],
                                 artifact, min(4, deadline - time.monotonic()), 8 * 1024 * 1024)
        entry['symbols'].append({'symbol': name, 'address_hex': hex(address), 'size_bytes': size,
                                 'priority': info['priority'], 'assembly': assembly})
        result['selection_order'].append({'object_index': index, 'symbol': name, 'priority': info['priority']})
        result['selected_symbols'] += 1
        complete &= assembly['ok']
    if result['selected_symbols']:
        result['state'] = 'COMPLETE_SELECTED_SYMBOLS' if complete else 'PARTIAL'
    else:
        result['error'] = 'no requested live text symbols captured (or tool/budget failure)'
    return result


def _kill_group(proc):
    if os.name == 'posix':
        try:
            os.killpg(proc.pid, signal.SIGKILL)
        except ProcessLookupError:
            pass
    elif os.name == 'nt':
        try:
            subprocess.run(['taskkill', '/PID', str(proc.pid), '/T', '/F'], stdout=subprocess.DEVNULL,
                           stderr=subprocess.DEVNULL, timeout=2,
                           creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0))
        except (OSError, subprocess.TimeoutExpired):
            pass
        finally:
            if proc.poll() is None:
                proc.kill()
    else:
        proc.kill()


def run_gate(argv, cwd, env, log_path, timeout, output, kernel):
    """Run unchanged argv/cwd/env; return original nonzero codes, never a capture verdict."""
    t0 = time.monotonic()
    root = Path(cwd).resolve()
    log_path, output, kernel = Path(log_path), Path(output), Path(kernel)
    record = {'schema': 1, 'mode': 'original-gate-statement-side-capture', 'state': 'UNKNOWN', '_t0': t0,
              'argv': [os.fspath(a) for a in argv], 'cwd': str(root), 'log_path': str(log_path.resolve()),
              'kernel_path': str(kernel.resolve()), 'kernel_sha256': None, 'started_at_utc': utc(),
              'statement_events': 0, 'snapshot_attempts': 0, 'errors': [],
              'snapshot': {'state': 'UNKNOWN', 'files': [], 'objects': []},
              'limits': {'file_bytes': FILE_LIMIT, 'total_copy_bytes': TOTAL_LIMIT, 'files': MAX_FILES,
                         'copy_seconds_checked_between_chunks': COPY_SECONDS, 'post_seconds': POST_SECONDS, 'symbols': MAX_SYMBOLS},
              'scope': 'Same original gate process and statement outputs; no recompile/stage/argv/env/object/score modification. Observer overhead remains possible.',
              'environment_recorded': {k: env[k] for k in ('BENCH_SEED', 'BENCH_PAIRS', 'BENCH_ROUNDS', 'GATE_FULL_SUITE') if env is not None and k in env}}
    staged, folder, private_dir = [], None, None
    cancel = threading.Event()
    workers = []
    try:
        require(not output.resolve().is_relative_to(root), 'capture output must be outside official checkout')
        output.mkdir(parents=True, exist_ok=True)
        folder = output / ('capture-' + uuid.uuid4().hex)
        folder.mkdir()
        record['artifact_directory'] = str(folder.resolve())
        record['kernel_sha256'] = sha(read_regular(kernel, 256000, time.monotonic() + 2))
        gate = root / 'gate.py'
        if gate.is_file():
            record['gate_source_sha256'] = sha(read_regular(gate, FILE_LIMIT, time.monotonic() + 2))
        record['capture_module_sha256'] = sha(Path(__file__).read_bytes())
        child_env = os.environ if env is None else env
        temp_root = Path(child_env.get('RUNNER_TEMP') or tempfile.gettempdir())
        require(temp_root.is_absolute() and temp_root.is_dir(), 'temporary root is not an existing absolute directory')
        temp_root = temp_root.resolve()
        require(not temp_root.is_relative_to(root) and not temp_root.is_relative_to(output.resolve()),
                'private temporary root must be outside official checkout and artifact output')
        private_dir = Path(tempfile.mkdtemp(prefix='floatlib-codegen-private-', dir=temp_root)).resolve()
        require(private_dir.is_relative_to(temp_root) and not private_dir.is_relative_to(output.resolve())
                and not private_dir.is_relative_to(root), 'private object directory boundary failure')
        record['private_object_directory'] = str(private_dir)
        record['private_objects_outside_artifact_output'] = True
    except Exception as exc:
        record['errors'].append('capture setup: ' + str(exc))
    log_path.parent.mkdir(parents=True, exist_ok=True)
    options = {'start_new_session': True} if os.name == 'posix' else {
        'creationflags': getattr(subprocess, 'CREATE_NEW_PROCESS_GROUP', 0) | getattr(subprocess, 'CREATE_NO_WINDOW', 0)}
    record['process_launch_options'] = options.copy()
    caught = None
    proc = None
    reader = None
    try:
        with log_path.open('wb', buffering=0) as log:
            proc = subprocess.Popen(argv, cwd=cwd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, bufsize=0, **options)
            record['gate_pid'] = proc.pid
            state = {'eof': False, 'bytes': 0, 'log_error': None, 'read_error': None}

            def tee():
                tail = b''
                try:
                    while chunk := proc.stdout.read(65536):
                        state['bytes'] += len(chunk)
                        if state['log_error'] is None:
                            try:
                                write_all(log, chunk)
                            except Exception as exc:
                                state['log_error'] = str(exc)  # Continue draining; never break the original process's pipe.
                        view = tail + chunk
                        count = view.count(MARKER)
                        record['statement_events'] += count
                        if count and not record['snapshot_attempts']:
                            record.update(statement_seen_seconds=time.monotonic() - t0, snapshot_attempts=1)
                            worker = threading.Thread(target=_snapshot,
                                args=(root, folder, private_dir, record['kernel_sha256'], record, staged, cancel), daemon=True)
                            try:
                                worker.start()
                            except Exception as exc:
                                record['snapshot'].update(state='UNKNOWN', error='snapshot thread launch: ' + str(exc))
                                record['errors'].append('snapshot thread launch: ' + str(exc))
                            else:
                                workers.append(worker)
                        if SCORE in view and 'first_score_seen_seconds' not in record:
                            record['first_score_seen_seconds'] = time.monotonic() - t0
                        tail = view[-(len(MARKER) - 1):]
                    state['eof'] = True
                except Exception as exc:
                    state['read_error'] = str(exc)

            reader = threading.Thread(target=tee, daemon=True)
            reader.start()
            try:
                proc.wait(timeout=timeout)
                record['timed_out'] = False
            except subprocess.TimeoutExpired as exc:
                caught = exc
                record['timed_out'] = True
                _kill_group(proc)
                try:
                    proc.wait(timeout=3)
                except subprocess.TimeoutExpired:
                    record['errors'].append('original process kill did not finish in grace period')
            record.update(gate_returncode=proc.returncode, gate_exit_seconds=time.monotonic() - t0)
            reader.join(timeout=3)
            if reader.is_alive():
                record['errors'].append('stdout drain did not reach EOF within grace period')
                _kill_group(proc)
                reader.join(timeout=1)
            record.update(stdout_bytes=state['bytes'], log_complete=state['eof'] and not state['log_error'] and not state['read_error'],
                          log_error=state['log_error'], stdout_read_error=state['read_error'])
    except BaseException as exc:
        if caught is None:
            caught = exc
        if proc is not None and proc.poll() is None:
            _kill_group(proc)
            try:
                proc.wait(timeout=3)
            except subprocess.TimeoutExpired:
                record['errors'].append('original process cleanup exceeded grace period')
    finally:
        post_deadline = time.monotonic() + POST_SECONDS
        for worker in workers:
            try:
                worker.join(timeout=3)
            except RuntimeError as exc:
                record['errors'].append('snapshot join: ' + str(exc))
        if any(w.is_alive() for w in workers):
            cancel.set()
            for worker in workers:
                worker.join(timeout=1)
            record['errors'].append('snapshot worker exceeded grace period')
        try:
            if not any(w.is_alive() for w in workers) and staged:
                record['disassembly'] = _disassemble(staged, folder, post_deadline, record)
            else:
                record['disassembly'] = {'state': 'UNKNOWN', 'reason': 'no stable captured object or capture worker incomplete'}
        except Exception as exc:
            record['errors'].append('post-gate disassembly: ' + str(exc))
            record['disassembly'] = {'state': 'UNKNOWN', 'error': str(exc)}
        finally:
            cancel.set()
            removed = True
            for private, _ in staged:
                try:
                    require(private_dir is not None and private.resolve().parent == private_dir
                            and private.name.startswith('.capture-object-'), 'refusing out-of-private-directory cleanup')
                    private.unlink(missing_ok=True)
                except Exception as exc:
                    removed = False
                    record['errors'].append('private object cleanup: ' + str(exc))
            record['private_objects_removed'] = removed and not any(w.is_alive() for w in workers)
            if private_dir is not None:
                try:
                    require(private_dir.name.startswith('floatlib-codegen-private-') and
                            not private_dir.is_relative_to(root) and not private_dir.is_relative_to(output.resolve()),
                            'refusing unsafe temporary-directory removal')
                    private_dir.rmdir()  # Empty directory only. Never recursive deletion.
                    record['private_directory_removed'] = True
                except Exception as exc:
                    record['private_directory_removed'] = False
                    record['errors'].append('private directory cleanup: ' + str(exc))
        snap = record['snapshot']
        score = record.get('first_score_seen_seconds')
        finish = snap.get('finished_seconds')
        record['snapshot_finished_before_observed_score'] = finish <= score if finish is not None and score is not None else None
        record['performance_observer_overhead'] = 'UNKNOWN; even capture before observed score can perturb CPU/cache. Confirm performance with capture disabled.'
        record['safe_to_publish_capture_directory'] = record.get('private_objects_outside_artifact_output', False)
        record['state'] = 'CAPTURED' if snap['state'] == 'CAPTURED' else 'UNKNOWN'
        record.update(completed_at_utc=utc(), wrapper_seconds=time.monotonic() - t0)
        record.pop('_t0', None)
        try:
            if log_path.is_file() and record.get('log_complete'):
                raw_log = read_regular(log_path, 16 * 1024 * 1024, max(time.monotonic() + .1, post_deadline))
                record['log_sha256'] = sha(raw_log)
                record['original_stage_log'] = _stage_events(raw_log, env, snap.get('finished_at_utc'))
        except Exception as exc:
            record['errors'].append('log hash UNKNOWN: ' + str(exc))
        if folder is not None:
            try:
                save_json(folder / 'capture-record.json', record)
            except Exception as exc:
                record['errors'].append('final metadata: ' + str(exc))
    if caught is not None:
        try:
            caught.codegen_record = record
        except Exception:
            pass
        raise caught
    return subprocess.CompletedProcess(argv, proc.returncode), record


def selftest():
    global _disassemble
    original_post = _disassemble
    results = []
    scratch_root = Path(__file__).resolve().parent
    with tempfile.TemporaryDirectory(prefix='.capture-selftest-', dir=scratch_root) as scratch:
        base = Path(scratch).resolve()
        require(base.is_relative_to(scratch_root) and base.name.startswith('.capture-selftest-'),
                'selftest cleanup target outside owned scratch root')

        def fake_post(staged, folder, deadline, record):
            require(record['gate_exit_seconds'] >= 0, 'postprocess ran before original process exited')
            require(not (Path(record['cwd']) / '.sandbox/layer/upper').exists(), 'fake gate did not wipe its layer')
            require(staged and all(p.read_bytes().startswith(b'\x7fELF') for p, _ in staged), 'private ELF copy missing after wipe')
            if Path(record['cwd']).parent.name == 'postfail':
                raise RuntimeError('intentional selftest postprocessor failure')
            return {'state': 'SELFTEST_SKIPPED_DISASSEMBLY', 'selected_symbols': 0, 'not_actual_llvm': True}

        # Exercise the report seam with fake nm/objdump; no Linux tools are run.
        original_tool, original_which = _bounded_tool, shutil.which
        hot = 'lp_competition_Submission_R11RawIndex_loop___redArg'
        private_hot = 'lp__private_Submission_0__Submission_R11CrossRows_wordLoop___redArg'
        real_private = ('lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold'
                        '___at___00Submission_R11RawA_core_spec__0___redArg')
        new_symbols = [hot, private_hot, 'lp_competition_Submission_Packed8Index_loop___redArg',
                       'lp_competition_Submission_R11CrossRows_dot8',
                       'lp_competition_Submission_R11RawA_core', real_private,
                       'lp_competition_Submission_RowStream_emit',
                       'lp_competition_Submission_RowStream_group',
                       'lp_competition_Submission_RowStream_row',
                       'lp_competition_Submission_RowStream_output',
                       'lp_competition_Submission_RowStream_core',
                       'lp_competition___private_Init_Data_Fin_Fold_0__Fin_foldl_loop'
                       '___at___00Submission_RowStream_emit_spec__0___redArg',
                       'lp__private_Submission_0__Submission_R11CrossRows_core',
                       'lp_competition_Submission_R11CrossRows_packGeneral',
                       'lp_competition_Submission_R11CrossRows_packShared',
                       'lp_competition_Submission_R11CrossRows_finish8',
                       'lp_competition_Submission_R11CrossRows_words']
        bad_symbols = [hot + '___boxed', 'lp_competition_Submission_R11RawIndex_looping',
                       'lp_competition_Submission_R11RawIndex_loop_extra',
                       'lp__private_Submission_0__NotSubmission_R11CrossRows_wordLoop',
                       'lp_competition_Submission_R11CrossRows_wordLooper',
                       'lp_competition_Submission_R11RawA_core_extra',
                       'lp_competition_Submission_addition',
                       'lp_competition_Submission_Packed8Index_loops',
                       'lp__private_Submission_0__Submission_R11CrossRows_words_extra',
                       'lp_competition___private_Init_Data_Fin_Fold_0__Fin_foldl_loop'
                       '___at___00Submission_RowStream_emitExtra_spec__0']
        old_symbols = ['lp_competition_Submission_NativeFinal_dotLoop'] + [
            'lp_competition_Submission_add___lam__' + str(i) for i in range(24)]
        symbol_dir = base / 'symbol-selection'
        symbol_dir.mkdir()
        first, second = base / 'old-object', base / 'new-object'
        fixtures = {str(first): old_symbols, str(second): new_symbols + bad_symbols}

        def fake_tool(argv, artifact, timeout, limit):
            if argv[0] == 'fake-nm':
                raw = ''.join('00000000 00000020 T ' + n + '\n' for n in fixtures[argv[-1]]).encode()
            else:
                name = next(a.split('=', 1)[1] for a in argv if a.startswith('--disassemble='))
                raw = ('00000000 <' + name + '>:\n  0: ret\n').encode()
            artifact.write_bytes(raw)
            return {'ok': True, 'returncode': 0, 'bytes': len(raw), 'sha256': sha(raw),
                    'artifact': artifact.name}

        try:
            globals()['_bounded_tool'] = fake_tool
            shutil.which = lambda name: 'fake-' + name
            selected_report = original_post([(first, {'sha256': 'old', 'source': 'old'}),
                                             (second, {'sha256': 'new', 'source': 'new'})],
                                            symbol_dir, time.monotonic() + 5, {})
        finally:
            globals()['_bounded_tool'] = original_tool
            shutil.which = original_which
        captured = [x['symbol'] for obj in selected_report['objects'] for x in obj['symbols']]
        require(set(new_symbols) <= set(captured), 'new hot/output symbols lost behind old scalar budget')
        require(not set(bad_symbols) & set(captured), 'near-match/boxed symbols captured')
        require(selected_report['selected_symbols'] == MAX_SYMBOLS == 20, 'symbol budget changed')
        require(selected_report['state'] == 'PARTIAL' and
                sum(len(obj['omitted_symbols']) for obj in selected_report['objects']) == 22,
                'budget omission/truncation not reported')
        order = selected_report['selection_order']
        require(order[0]['symbol'] in (hot, private_hot,
                'lp_competition_Submission_Packed8Index_loop___redArg',
                'lp_competition_Submission_R11CrossRows_dot8'), 'old scalar precedes new hot loop')
        require(all(x['priority'] == 0 for x in order[:4]) and
                order[len(new_symbols)]['priority'] == 2 and
                all(x['priority'] == 3 for x in order[len(new_symbols) + 1:]), 'priority order drift')
        results.append({'test': 'new_symbol_priority_boundaries_and_budget', 'pass': True,
                        'captured': len(captured), 'omitted': 22, 'actual_llvm': 'NOT_RUN'})

        # Exact nm names from 911's fused-output object; these are the entry's
        # specialized loops, while the standalone group/row bodies are retained.
        output_loops = [
            'lp_competition_Fin_foldl_loop___at___00Submission_RowStream_output_spec__0',
            'lp_competition_Fin_foldl_loop___at___00Submission_RowStream_output_spec__1',
            'lp_competition_Fin_foldl_loop___at___00Submission_RowStream_output_spec__2']
        standalone = [
            'lp_competition_Submission_RowStream_group___redArg',
            'lp_competition_Submission_RowStream_group___redArg___lam__0',
            'lp_competition_Submission_RowStream_emit___lam__0',
            'lp_competition_Submission_RowStream_core',
            'lp_competition_Submission_RowStream_emit',
            'lp_competition_Submission_RowStream_group',
            'lp_competition_Submission_RowStream_output',
            'lp_competition_Submission_RowStream_row']
        fused = base / 'fused-911-object'
        fixtures[str(fused)] = output_loops + standalone + old_symbols
        fused_dir = base / 'fused-911-selection'
        fused_dir.mkdir()
        try:
            globals()['_bounded_tool'] = fake_tool
            shutil.which = lambda name: 'fake-' + name
            fused_report = original_post([(fused, {'sha256': 'fused911', 'source': 'fused911'})],
                                         fused_dir, time.monotonic() + 5, {})
        finally:
            globals()['_bounded_tool'] = original_tool
            shutil.which = original_which
        order = [x['symbol'] for x in fused_report['selection_order']]
        require(set(output_loops) <= set(order), '911 actual output specialized loops missing')
        require(set(order[:3]) == set(output_loops), 'standalone output helpers precede actual 911 loops')
        require(fused_report['selected_symbols'] == MAX_SYMBOLS == 20 and
                sum(len(obj['omitted_symbols']) for obj in fused_report['objects']) == 16,
                '911 replay did not retain bounded omission reporting')
        results.append({'test': 'actual_911_output_loops_before_standalone_helpers', 'pass': True,
                        'captured': 20, 'omitted': 16, 'actual_llvm': 'NOT_RUN'})

        # Source-backed names with the same strict compiler encoding. Actual
        # emission/LLVM for these new candidate paths is not claimed by this test.
        future_loops = [
            'lp_competition_Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__0',
            'lp_competition_Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__1',
            'lp_competition_Fin_foldl_loop___at___00Submission_DirectContinuous_row_spec__0___redArg',
            'lp__private_Init_Data_Fin_Fold_0__Fin_foldl_loop'
            '___at___00Submission_DirectContinuous_row_spec__0',
            'lp_competition_Fin_foldl_loop___at___00Submission_BatchLocalPacked_output_spec__0',
            'lp_competition_Fin_foldl_loop___at___00Submission_BatchLocalPacked_batchStep_spec__0',
            'lp_competition_Fin_foldl_loop___at___00Submission_BatchLocalPacked_group_spec__0',
            'lp_competition___private_Init_Data_Fin_Fold_0__Fin_foldl_loop'
            '___at___00Submission_BatchLocalPacked_row_spec__0___redArg']
        future_outputs = ['lp_competition_Submission_' + stem for stem in (
            'DirectContinuous_core', 'DirectContinuous_output', 'DirectContinuous_row',
            'BatchLocalPacked_core', 'BatchLocalPacked_output', 'BatchLocalPacked_batchStep',
            'BatchLocalPacked_row', 'BatchLocalPacked_group', 'BatchLocalPacked_packBatch')]
        invalid_outputs = [
            output_loops[0] + '___boxed', future_loops[0] + '___boxed',
            future_loops[-1] + '___boxed',
            future_loops[0].replace('output_spec', 'outputExtra_spec'),
            future_loops[4].replace('output_spec', 'output_extra_spec'),
            future_loops[0] + '_extra', future_loops[0] + '___redArgument',
            future_loops[-1].replace('___redArg', '___redArgument'),
            future_loops[0].replace('Fin_foldl_loop', 'List_foldl_loop'),
            future_loops[-1].replace('00Submission_', '00NotSubmission_'),
            'lp_competition_Submission_BatchLocalPacked_output_extra']
        future = base / 'future-output-object'
        fixtures[str(future)] = future_loops + future_outputs + invalid_outputs + old_symbols
        future_dir = base / 'future-output-selection'
        future_dir.mkdir()
        try:
            globals()['_bounded_tool'] = fake_tool
            shutil.which = lambda name: 'fake-' + name
            future_report = original_post([(future, {'sha256': 'future', 'source': 'future'})],
                                          future_dir, time.monotonic() + 5, {})
        finally:
            globals()['_bounded_tool'] = original_tool
            shutil.which = original_which
        order = [x['symbol'] for x in future_report['selection_order']]
        require(set(future_loops + future_outputs) <= set(order), 'new output/fold chain missing')
        require(set(order[:len(future_loops)]) == set(future_loops), 'new output loops not prioritized')
        require(not set(invalid_outputs) & set(order) and
                all(not _selected(x) for x in invalid_outputs), 'encoded output near-match/boxed captured')
        require(future_report['selected_symbols'] == MAX_SYMBOLS == 20 and
                sum(len(obj['omitted_symbols']) for obj in future_report['objects']) == 22,
                'new output replay budget/omission drift')
        results.append({'test': 'new_output_fold_encoding_and_rejection_boundaries', 'pass': True,
                        'captured': 20, 'omitted': 22, 'actual_emission_and_llvm': 'UNKNOWN_NOT_RUN'})

        # Exhaust the unchanged deadline after nm, before any objdump invocation.
        original_clock = time.monotonic
        clock = [0.0]
        deadline_dir = base / 'symbol-deadline'
        deadline_dir.mkdir()

        def expired_tool(argv, artifact, timeout, limit):
            value = fake_tool(argv, artifact, timeout, limit)
            if argv[0] == 'fake-nm' and argv[-1] == str(second):
                clock[0] = 10.0
            return value

        try:
            globals()['_bounded_tool'] = expired_tool
            shutil.which = lambda name: 'fake-' + name
            time.monotonic = lambda: clock[0]
            expired = original_post([(first, {'sha256': 'old', 'source': 'old'}),
                                     (second, {'sha256': 'new', 'source': 'new'})],
                                    deadline_dir, 5.0, {})
        finally:
            globals()['_bounded_tool'] = original_tool
            shutil.which = original_which
            time.monotonic = original_clock
        omitted = [x for obj in expired['objects'] for x in obj['omitted_symbols']]
        require(expired['selected_symbols'] == 0 and len(omitted) == 42 and
                all(x['reason'] == 'deadline' for x in omitted) and
                not list(deadline_dir.glob('asm-*')), 'deadline omissions not complete')
        results.append({'test': 'symbol_deadline_omissions', 'pass': True,
                        'captured': 0, 'omitted': 42, 'actual_llvm': 'NOT_RUN'})

        _disassemble = fake_post
        program = r'''
import json,os,sys,time,shutil,subprocess
from datetime import datetime,timezone
from pathlib import Path
root,out,mode=Path(sys.argv[1]),Path(sys.argv[2]),sys.argv[3]
assert Path.cwd()==root and os.environ['CAPTURE_TEST']=='unchanged'
upper=root/'.sandbox/layer/upper'
if mode=='timeout':
    os.write(1,b'before-timeout\xfe\n');time.sleep(20)
else:
    if mode=='after':
        assert upper.resolve().is_relative_to(root.resolve());shutil.rmtree(upper)
    os.write(2,b'stderr\xfd\r\n')
    os.write(1,b'raw\xff\r\n[stat');time.sleep(.03);os.write(1,b'ement] ok\n')
    if mode in ('before','mismatch','postfail'):
        deadline=time.monotonic()+3
        while not list(out.glob('capture-*/snapshot.json')) and time.monotonic()<deadline:time.sleep(.01)
        assert list(out.glob('capture-*/snapshot.json'))
        assert upper.resolve().is_relative_to(root.resolve());shutil.rmtree(upper)
    time.sleep(.01)  # Keep synthetic emission beyond timestamp truncation precision.
    stamp=datetime.now(timezone.utc).isoformat(timespec='milliseconds').encode('ascii')
    suffix=stamp+b' | INFO | [axioms] ok\n[statement] ok\n[score] original\nend\x00\n'
    (root/'expected-suffix').write_bytes(suffix)
    os.write(1,suffix)
    sys.exit(7)
'''
        try:
            for mode in ('before', 'after', 'mismatch', 'postfail', 'timeout'):
                case = base / mode
                cwd, output = case / 'official', case / 'output'
                upper = cwd / '.sandbox/layer/upper'
                (upper / 'ir').mkdir(parents=True)
                (cwd / 'lean/work').mkdir(parents=True)
                kernel = case / 'Kernel.lean'
                kernel.write_bytes(b'import ContractTensor\n-- fake kernel\n')
                (cwd / 'lean/work/Submission.lean').write_bytes(kernel.read_bytes())
                if mode == 'mismatch':
                    (cwd / 'lean/work/Submission.lean').write_bytes(b'-- different candidate\n')
                (upper / 'ir/Submission.c').write_bytes(b'/* fake generated C */\n')
                (upper / 'ir/Submission.c.o.export.trace').write_bytes(b'{"log":[]}\n')
                (upper / 'ir/Submission.c.o.export').write_bytes(b'\x7fELF' + bytes(range(64)))
                (upper / 'ir/SubmissionOther.trace').write_bytes(b'not our module\n')
                env = os.environ.copy()
                env['CAPTURE_TEST'] = 'unchanged'
                temp_root = case / 'runner-temp'
                temp_root.mkdir()
                env['RUNNER_TEMP'] = str(temp_root)
                original_env = env.copy()
                argv = [sys.executable, '-c', program, str(cwd), str(output), mode]
                log = case / 'original.log'
                started = time.monotonic()
                if mode == 'timeout':
                    try:
                        run_gate(argv, cwd, env, log, .4, output, kernel)
                    except subprocess.TimeoutExpired as exc:
                        record = exc.codegen_record
                    else:
                        raise AssertionError('timeout did not preserve TimeoutExpired')
                    require(time.monotonic() - started < 8 and record['timed_out'], 'timeout failed to exit promptly')
                    require(log.read_bytes() == b'before-timeout\xfe\n', 'timeout stdout bytes differ')
                else:
                    completed, record = run_gate(argv, cwd, env, log, 6, output, kernel)
                    require(completed.returncode == 7 and completed.args == argv, 'original argv/nonzero exit changed')
                    expected = b'stderr\xfd\r\nraw\xff\r\n[statement] ok\n' + (cwd / 'expected-suffix').read_bytes()
                    require(log.read_bytes() == expected, 'original stdout bytes changed')
                    require(record['statement_events'] == 2 and record['snapshot_attempts'] == 1, 'event split/once detection failed')
                    require(record['state'] == ('CAPTURED' if mode in ('before', 'postfail') else 'UNKNOWN'), 'cleanup race status incorrect')
                    require(record['original_stage_log']['events'][1]['stage'] == 'axioms', 'raw stage event missing')
                    require(record['original_stage_log']['events'][1]['emitted_at_utc'] is not None, 'emission timestamp not parsed')
                    if mode == 'before':
                        require(record['original_stage_log']['capture_vs_axioms_emission']['state'] ==
                                'VERIFIED_BEFORE_RECORDED_AXIOMS_TIMESTAMP', 'capture did not precede emitted axioms timestamp')
                    if mode == 'postfail':
                        require(record['disassembly']['state'] == 'UNKNOWN' and
                                any('intentional selftest' in e for e in record['errors']), 'postprocess failure not isolated')
                require(env == original_env and record['log_complete'], 'environment mutation or incomplete tee')
                require(record['private_objects_removed'] and not list(output.rglob('.capture-object-*')), 'private object leaked')
                require(record['private_directory_removed'] and not list(temp_root.iterdir()), 'private temporary directory leaked')
                require(all(not p.read_bytes().startswith(b'\x7fELF') for p in output.rglob('*') if p.is_file()),
                        'ELF bytes entered artifact output')
                results.append({'test': mode, 'pass': True, 'capture_state': record['state'], 'actual_llvm': 'NOT_RUN'})
            raw_event = b'2026-10-22 12:00:00.123 | INFO | [axioms] ok\n'
            finish = '2026-10-22T11:59:59+00:00'
            unknown = _stage_events(raw_event, {}, finish)
            require(unknown['capture_vs_axioms_emission']['state'] == 'UNKNOWN', 'assumed local log timezone')
            require(base64.b64decode(unknown['events'][0]['raw_line_base64']) == raw_event, 'stage raw bytes changed')
            require(_stage_events(raw_event, {'TZ': 'UTC'}, finish)['capture_vs_axioms_emission']['state'] ==
                    'VERIFIED_BEFORE_RECORDED_AXIOMS_TIMESTAMP', 'explicit UTC evidence not used')
            require(_selected('lp_competition_Submission_NativeFinal_dotLoop') and
                    _selected('lp_competition_Submission_NativeFinal_sumLoop') and
                    _selected('lp_competition_Submission_LowZero_core') and
                    not _selected('lp_competition_Submission_addition') and
                    not _selected('lp_competition_Submission_add___boxed'), 'symbol selection drift')
            results.append({'test': 'timestamp_and_symbol_boundaries', 'pass': True})
        finally:
            _disassemble = original_post
    print(json.dumps({'selftest': 'PASS', 'tests': results, 'scope': 'Lightweight Python children and fake ELF only; no Linux/Lean/compiler validation.'}, indent=2))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--selftest', action='store_true', required=True)
    parser.parse_args()
    selftest()
