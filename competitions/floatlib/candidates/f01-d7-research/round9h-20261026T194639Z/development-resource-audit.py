"""[DEBUG-R19-SEED] Remote proof isolation, never a score/adoption gate."""
from pathlib import Path
import hashlib
import importlib.util
import json
import re
import subprocess
import threading
import time


def stages(g, kernel, out, manifest):
    here = Path(__file__).resolve().parent
    base = here / 'development-helper-audit-v5.py'
    assert hashlib.sha256(base.read_bytes()).hexdigest() == manifest['resource_base_audit_sha256']
    spec = importlib.util.spec_from_file_location('r19_resource_base_audit', base)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    original = module.stages(g, kernel, out, manifest)
    request = manifest['resource_probe']
    assert request['tag'] == '[DEBUG-R19-SEED]' and request['cap_seconds'] == 180
    source = here / 'development-seed-isolation/marked-proof.lean.inc'
    assert hashlib.sha256(source.read_bytes()).hexdigest() == request['source_sha256']
    expected = request['declarations']
    assert 1 <= len(expected) <= 16 and len(expected) == len(set(expected))
    assert all(re.fullmatch(r'[0-9]+:[A-Za-z0-9_]+', name) for name in expected)

    def isolate(src, verdict):
        path = g.WORK.parent / 'R19SeedIsolation.lean'
        assert not path.exists()
        content = b'import Submission\n' + source.read_bytes()
        path.write_bytes(content)
        (out / 'seed-isolation-source.lean').write_bytes(content)
        record = {
            'diagnostic_only': True, 'performance': 'NOT_RUN',
            'scope': 'Separate helper importing byte-exact compiled B2. Original failed1180 gate remains failed; this is not its full module/spec replay.',
            'kernel_sha256': hashlib.sha256(kernel.read_bytes()).hexdigest(),
            'helper_source_sha256': hashlib.sha256(content).hexdigest(),
            'cap_seconds': min(180, g._BUILD_TIMEOUT), 'expected_declarations': expected,
            'resource_scope': 'Read-only /proc names/RSS and cgroup-v2 counters on the disposable runner, no arguments/environment; RSS sums may double-count shared pages.',
        }
        stop = threading.Event()
        samples = []
        errors = []
        scopes = set()
        started = time.monotonic()

        def watch():
            while not stop.is_set():
                processes, groups = [], {}
                try:
                    for item in Path('/proc').iterdir():
                        if not item.name.isdecimal():
                            continue
                        try:
                            name = (item / 'comm').read_text().strip()
                            if name not in ('lean', 'lake', 'systemd-run', 'bwrap'):
                                continue
                            fields = dict(line.split(':', 1) for line in (item / 'status').read_text().splitlines() if ':' in line)
                            rss = int(fields.get('VmRSS', '0 kB').split()[0])
                            processes.append({'pid': int(item.name), 'name': name, 'rss_kb': rss})
                            for line in (item / 'cgroup').read_text().splitlines():
                                if not line.startswith('0::'):
                                    continue
                                relative = line[3:].lstrip('/')
                                group = (Path('/sys/fs/cgroup') / relative).resolve()
                                if not group.is_relative_to(Path('/sys/fs/cgroup')):
                                    continue
                                values = {}
                                for metric in ('memory.current', 'memory.peak', 'memory.max', 'memory.events'):
                                    try:
                                        values[metric] = (group / metric).read_text().strip()
                                    except OSError:
                                        values[metric] = 'UNKNOWN'
                                groups[relative] = values
                                unit = group.name
                                if re.fullmatch(r'run-[A-Za-z0-9_.-]+\.scope', unit):
                                    scopes.add(unit)
                        except (OSError, ValueError):
                            continue
                    samples.append({'elapsed_seconds': time.monotonic() - started,
                                    'processes': processes, 'groups': groups})
                except OSError as error:
                    if len(errors) < 8:
                        errors.append(type(error).__name__ + ': ' + str(error))
                stop.wait(0.25)

        monitor = threading.Thread(target=watch, daemon=True)
        monitor.start()
        try:
            code, output = g.own([g.LAKE, 'env', 'lean', 'work/R19SeedIsolation.lean'],
                                 min(180, g._BUILD_TIMEOUT), build='read')
            raw = output.encode()
            (out / 'seed-isolation-output.raw').write_bytes(raw)
            markers = re.findall(r'^\[DEBUG-R19-SEED\] (BEFORE|AFTER) ([0-9]+:[A-Za-z0-9_]+)$', output, re.M)
            completed = [label for event, label in markers if event == 'AFTER']
            entered = [label for event, label in markers if event == 'BEFORE']
            record.update(exit_code=code, elapsed_seconds=time.monotonic() - started,
                          output_sha256=hashlib.sha256(raw).hexdigest(),
                          markers=markers, completed_declarations=completed,
                          active_at_end=[name for name in entered if name not in completed],
                          helper_typecheck_complete=code == 0 and completed == expected)
        except BaseException as error:
            record.update(error_type=type(error).__name__, error=str(error), helper_typecheck_complete=False)
            raise
        finally:
            stop.set()
            monitor.join(timeout=2)
            record['monitor_errors'] = errors
            record['max_observed_process_rss_sum_kb'] = max((sum(p['rss_kb'] for p in row['processes']) for row in samples), default=0)
            record['systemd_scopes'] = []
            for unit in sorted(scopes)[:8]:
                try:
                    response = subprocess.run(['systemctl', '--user', 'show', unit,
                        '--property=Result,MemoryPeak,MemoryMax,OOMPolicy,ActiveState,SubState'],
                        capture_output=True, text=True, timeout=3)
                    record['systemd_scopes'].append({'unit': unit, 'exit_code': response.returncode,
                        'properties': response.stdout if response.returncode == 0 else 'UNKNOWN_SCOPE_GONE_OR_QUERY_FAILED'})
                except (OSError, subprocess.TimeoutExpired):
                    record['systemd_scopes'].append({'unit': unit, 'properties': 'UNKNOWN_QUERY_UNAVAILABLE'})
            sampling = (json.dumps(samples, indent=2) + '\n').encode()
            (out / 'seed-isolation-resources.json').write_bytes(sampling)
            record['sampling_sha256'] = hashlib.sha256(sampling).hexdigest()
            (out / 'seed-isolation.json').write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
            path.unlink()
        return None if record['helper_typecheck_complete'] else 'Seed isolation incomplete: ' + str(record.get('exit_code', 'ERROR')) + ', active=' + ','.join(record.get('active_at_end', []))

    return original + [('seed-isolation', isolate)]
