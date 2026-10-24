"""Post-run, read-only inventory/capture of existing official MainFull artifacts.

This helper never runs Lean, a benchmark, or a gate, and never retains ELF bytes.
It deliberately does not infer candidate identity from work/Submission.lean alone.
Call only after all original gate processes in this checkout have exited.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import os
import re
import shutil
import stat
import subprocess
import time

MODULES = ('MainFull', 'BenchSuite', 'Submission')
TEXT_LIMIT = 12 * 1024 * 1024
OBJECT_LIMIT = 16 * 1024 * 1024
TOTAL_LIMIT = 32 * 1024 * 1024
SECONDS = 50
MAX_SYMBOLS = 24


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def utc():
    return datetime.now(timezone.utc).isoformat()


def read_regular(path, limit):
    before = path.lstat()
    if not stat.S_ISREG(before.st_mode) or path.is_symlink() or before.st_size > limit:
        raise ValueError('not a bounded regular non-symlink file: ' + str(path))
    flags = os.O_RDONLY | getattr(os, 'O_BINARY', 0) | getattr(os, 'O_NOFOLLOW', 0)
    with os.fdopen(os.open(path, flags), 'rb') as stream:
        first = os.fstat(stream.fileno())
        raw = stream.read(limit + 1)
        last = os.fstat(stream.fileno())
    identity = lambda s: (s.st_size, s.st_mtime_ns, s.st_ino, s.st_dev)
    if len(raw) > limit or identity(first) != identity(last) or len(raw) != first.st_size:
        raise ValueError('file changed or grew while reading: ' + str(path))
    return raw


def selected_symbol(module, name):
    if module == 'MainFull':
        return bool(re.search(r'(?:^|_)main(?:___|$)', name)) or name.startswith('initialize_')
    if module == 'BenchSuite':
        return bool(re.search(r'(?:runScalar|measure|Suite_run)(?:___|$)', name))
    return bool(re.fullmatch(r'lp_competition_Submission_(?:add|mul|nativeMul)(?:___[A-Za-z0-9_]+)?', name))


def trace_summary(raw):
    try:
        value = json.loads(raw)
    except (ValueError, UnicodeDecodeError):
        return {'state': 'UNKNOWN_NOT_JSON'}
    return {'state': 'PARSED', 'outputs': value.get('outputs'), 'inputs': value.get('inputs'),
            'depHash': value.get('depHash'), 'commands': [r.get('message') for r in value.get('log', [])
            if isinstance(r, dict) and str(r.get('message', '')).startswith('.> ')]}


def capture(upstream, kernel, out, expected_sha256, verdict=None, original_capture=None):
    started = time.monotonic()
    deadline = started + SECONDS
    root, kernel, out = Path(upstream).resolve(), Path(kernel).resolve(), Path(out).resolve()
    if out.is_relative_to(root):
        raise ValueError('artifact output must be outside the official checkout')
    out.mkdir(parents=True, exist_ok=False)
    record = {'schema': 1, 'mode': 'post-run-existing-mainfull-static-capture',
              'started_at_utc': utc(), 'upstream': str(root), 'kernel': str(kernel),
              'expected_kernel_sha256': expected_sha256, 'files': [], 'objects': [], 'errors': [],
              'artifact_bytes': 0, 'limits': {'seconds': SECONDS, 'artifact_bytes': TOTAL_LIMIT,
              'text_file_bytes': TEXT_LIMIT, 'object_inspection_bytes': OBJECT_LIMIT, 'symbols': MAX_SYMBOLS},
              'scope': 'Existing bytes only; no compilation, gate hooks, benchmark, environment change, '
                       'measurement observer, binary copy, or background process.',
              'timed_candidate_mainfull': {'state': 'UNKNOWN', 'reason':
                  'Original gate deletes its candidate overlay in finally. Shared cached outputs '
                  'are not bound to the last work/Submission.lean merely because that source remains.'}}

    def save(name, raw):
        if record['artifact_bytes'] + len(raw) > TOTAL_LIMIT:
            raise ValueError('total artifact byte cap')
        if raw.startswith(b'\x7fELF'):
            raise ValueError('ELF export prohibited')
        (out / name).write_bytes(raw)
        record['artifact_bytes'] += len(raw)
        return {'artifact': name, 'bytes': len(raw), 'sha256': sha(raw)}

    def text_file(path, name):
        raw = read_regular(path, TEXT_LIMIT)
        info = {'source': str(path), **save(name, raw)}
        if path.suffix == '.trace':
            info['trace'] = trace_summary(raw)
        record['files'].append(info)
        return raw

    def tool(argv, name, limit):
        if time.monotonic() >= deadline:
            return {'state': 'UNKNOWN', 'reason': 'post-run deadline'}
        executable = shutil.which(argv[0])
        if not executable:
            return {'state': 'UNKNOWN', 'reason': 'tool unavailable', 'argv': argv}
        target = out / name
        # A regular output file avoids retaining unbounded process output in memory.
        with target.open('wb') as stream:
            try:
                p = subprocess.run([executable, *argv[1:]], stdout=stream, stderr=subprocess.STDOUT,
                                   timeout=max(.01, min(5, deadline - time.monotonic())))
            except subprocess.TimeoutExpired:
                p = None
        size = target.stat().st_size
        if size > limit or record['artifact_bytes'] + size > TOTAL_LIMIT:
            target.unlink()
            return {'state': 'UNKNOWN', 'reason': 'output byte cap', 'argv': argv, 'bytes': size}
        raw = read_regular(target, limit)
        record['artifact_bytes'] += len(raw)
        return {'state': 'CAPTURED' if p is not None and p.returncode == 0 else 'UNKNOWN',
                'argv': argv, 'artifact': name, 'bytes': len(raw), 'sha256': sha(raw),
                'returncode': p.returncode if p is not None else None, 'timed_out': p is None}

    try:
        raw = read_regular(kernel, 256000)
        record['kernel_sha256'] = sha(raw)
        if record['kernel_sha256'] != expected_sha256:
            raise ValueError('requested exact Kernel SHA-256 mismatch')
        save('requested-Kernel.lean', raw)
        work = root / 'lean/work/Submission.lean'
        if work.exists():
            source = text_file(work, 'last-work-Submission.lean')
            record['last_work_source'] = {'sha256': sha(source), 'matches_requested': sha(source) == expected_sha256,
                                          'sufficient_for_object_identity': False}
        for name in ('gate.py', 'lean/lean-toolchain', 'lean/lake-manifest.json', 'lean/lakefile.lean',
                     'lean/MainFull.lean', 'lean/bench/BenchSuite.lean', 'suites/public-v2.json'):
            path = root / name
            if path.exists():
                text_file(path, 'official-' + name.replace('/', '-'))
        if verdict is not None:
            text_file(Path(verdict), 'original-verdict.json')
        if original_capture is not None:
            original = Path(original_capture)
            for name in ('capture-record.json', 'snapshot.json', 'compiled-Submission.lean'):
                path = original / name
                if path.exists():
                    text_file(path, 'original-capture-' + name)
            record['original_capture_reference'] = str(original.resolve())
            record['original_capture_mainfull_binding'] = 'UNKNOWN: previous observer only selected Submission'
        roots = [('candidate-upper', root / '.sandbox/layer/upper'),
                 ('shared-cache', root / 'lean/.lake/build')]
        record['build_roots'] = [{'kind': kind, 'path': str(build), 'exists': build.exists()} for kind, build in roots]
        selected_count = 0
        for kind, build in roots:
            if not build.is_dir():
                continue
            for module in MODULES:
                paths = []
                for subdir in ('ir', 'lib/lean'):
                    directory = build / subdir
                    if directory.is_dir():
                        paths.extend(p for p in directory.glob(module + '*') if p.name == module + '.c'
                                     or p.suffix == '.trace' or p.name.endswith(('.hash', '.setup.json'))
                                     or re.fullmatch(re.escape(module) + r'(?:\.c)?\.o(?:\.(?:export|noexport))?', p.name))
                for index, path in enumerate(sorted(set(paths))):
                    if time.monotonic() >= deadline:
                        raise TimeoutError('post-run inspection deadline')
                    if not path.resolve().is_relative_to(build.resolve()):
                        raise ValueError('artifact path leaves build root')
                    prefix = f'{kind}-{module}-{index}'
                    raw = read_regular(path, OBJECT_LIMIT if '.o' in path.name else TEXT_LIMIT)
                    if not raw.startswith(b'\x7fELF'):
                        text_file(path, prefix + '-' + path.name)
                        continue
                    obj = {'source': str(path), 'build_kind': kind, 'module': module,
                           'bytes': len(raw), 'sha256_before': sha(raw), 'binary_retained': False,
                           'original_timed_candidate_identity': 'UNKNOWN'}
                    record['objects'].append(obj)
                    obj['nm'] = tool(['nm', '-S', '--defined-only', '--radix=x', str(path)], prefix + '-nm.txt', 3*1024*1024)
                    obj['relocations'] = tool(['objdump', '-r', str(path)], prefix + '-relocations.txt', 6*1024*1024)
                    obj['header'] = tool(['readelf', '-h', str(path)], prefix + '-elf-header.txt', 65536)
                    obj['symbols'] = []
                    if obj['nm']['state'] == 'CAPTURED':
                        names = []
                        for line in (out / obj['nm']['artifact']).read_text(encoding='utf-8', errors='replace').splitlines():
                            parts = line.split()
                            if len(parts) == 4 and parts[2] in 'TtWw' and selected_symbol(module, parts[3]):
                                names.append((parts[3], parts[1]))
                        names.sort(key=lambda x: ('___boxed' in x[0], '___lam__' not in x[0], x[0]))
                        obj['matching_symbols'] = len(names)
                        for symbol, size in names:
                            if selected_count >= MAX_SYMBOLS or time.monotonic() >= deadline:
                                break
                            result = tool(['objdump', '-dr', '--no-show-raw-insn', '-Mintel',
                                           '--disassemble=' + symbol, str(path)],
                                          prefix + f'-asm-{len(obj["symbols"])}.txt', 3*1024*1024)
                            obj['symbols'].append({'symbol': symbol, 'size_hex': size, 'assembly': result})
                            selected_count += 1
                    obj['sha256_after'] = sha(read_regular(path, OBJECT_LIMIT))
                    obj['unchanged_during_inspection'] = obj['sha256_before'] == obj['sha256_after']
            binary_trace = build / 'bin/benchFull.trace'
            if binary_trace.exists():
                text_file(binary_trace, kind + '-benchFull.trace')
            binary = build / 'bin/benchFull'
            if binary.exists():
                # The linked executable can exceed the object cap. Hash it by bounded reads.
                first = binary.stat()
                digest = hashlib.sha256()
                with binary.open('rb') as stream:
                    while chunk := stream.read(1024*1024):
                        if time.monotonic() >= deadline:
                            raise TimeoutError('linked binary hashing deadline')
                        digest.update(chunk)
                last = binary.stat()
                record.setdefault('linked_binary_metadata', []).append({'source': str(binary), 'sha256': digest.hexdigest(),
                    'bytes': first.st_size, 'binary_retained': False,
                    'unchanged_during_hash': (first.st_size, first.st_mtime_ns) == (last.st_size, last.st_mtime_ns),
                    'original_timed_candidate_identity': 'UNKNOWN'})
        if work.exists():
            record['last_work_source']['sha256_after'] = sha(read_regular(work, 256000))
        record['static_capture_state'] = 'CAPTURED_EXISTING_TEXT' if record['files'] else 'UNKNOWN'
    except Exception as exc:
        record['errors'].append(type(exc).__name__ + ': ' + str(exc))
        record['static_capture_state'] = 'PARTIAL' if record['files'] else 'UNKNOWN'
    record.update(finished_at_utc=utc(), seconds=round(time.monotonic() - started, 6),
                  binary_artifacts_exported=False, lean_or_benchmark_execution='NOT_RUN')
    (out / 'mainfull-capture.json').write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
    return record


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--upstream', required=True, type=Path)
    ap.add_argument('--kernel', required=True, type=Path)
    ap.add_argument('--out', required=True, type=Path)
    ap.add_argument('--expected-sha256', required=True)
    ap.add_argument('--verdict', type=Path)
    ap.add_argument('--original-capture', type=Path)
    a = ap.parse_args()
    result = capture(a.upstream, a.kernel, a.out, a.expected_sha256, a.verdict, a.original_capture)
    print(json.dumps({k: result[k] for k in ('static_capture_state', 'timed_candidate_mainfull', 'errors', 'seconds')}, indent=2))
