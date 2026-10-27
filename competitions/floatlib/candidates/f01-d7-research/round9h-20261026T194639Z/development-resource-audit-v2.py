"""Independent complete-prefix processes; diagnostic resource evidence only."""
from pathlib import Path
import hashlib
import importlib.util
import json
import re
import subprocess
import threading
import time

B2 = '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
ROOTS = ['Submission.add_spec', 'Submission.mul_spec', 'Submission.sum_spec', 'Submission.bmm_spec']
PREFIXES = [('import-only', 'ImportOnly.lean', '239175fe9907a272f0b9816f700dbc310b5b3e33ffca567fde220339d93ffa70', 18, 'R19ImportOnlyPrefix.lean'),
            ('quotient-only', 'QuotientOnly.lean', '014acd413d37ee012bdc55fb813591815ccb5dce0adf09f27dac9a17fd68573d', 1341, 'R19QuotientOnlyPrefix.lean')]
sha = lambda data: hashlib.sha256(data).hexdigest()


def save(path, value):
    path.write_bytes((json.dumps(value, indent=2) + '\n').encode())


def sample_proc():
    processes, groups, scopes = [], {}, set()
    for item in Path('/proc').iterdir():
        if not item.name.isdecimal(): continue
        try:
            name = (item / 'comm').read_text().strip()
            if name not in ('lean', 'lake', 'systemd-run', 'bwrap'): continue
            fields = dict(line.split(':', 1) for line in (item / 'status').read_text().splitlines() if ':' in line)
            processes.append({'pid': int(item.name), 'name': name, 'rss_kb': int(fields.get('VmRSS', '0 kB').split()[0])})
            for line in (item / 'cgroup').read_text().splitlines():
                if not line.startswith('0::'): continue
                relative = line[3:].lstrip('/')
                group = (Path('/sys/fs/cgroup') / relative).resolve()
                if not group.is_relative_to(Path('/sys/fs/cgroup')): continue
                values = {}
                for metric in ('memory.current', 'memory.peak', 'memory.max', 'memory.events'):
                    try: values[metric] = (group / metric).read_text().strip()
                    except OSError: values[metric] = 'UNKNOWN'
                groups[relative] = values
                if re.fullmatch(r'run-[A-Za-z0-9_.-]+\.scope', group.name): scopes.add(group.name)
        except (OSError, ValueError): continue
    return {'processes': processes, 'groups': groups}, scopes


def stages(g, kernel, out, manifest):
    started = time.monotonic()  # Includes original carrier stages after registration.
    here = Path(__file__).resolve().parent
    base = here / 'development-helper-audit-v5.py'
    assert sha(base.read_bytes()) == manifest['resource_base_audit_sha256']
    assert sha(kernel.read_bytes()) == manifest['candidate_sha256'] == manifest['helper_audit_source_sha256'] == B2
    assert manifest['explicit_helper_audit'] == ROOTS and manifest['helper_audit_expected_count'] == 4
    assert not manifest.get('diagnostic_evaluations')
    request = manifest['resource_probe']
    assert request['schema_version'] == 2 and request['mode'] == 'INDEPENDENT_COMPLETE_PREFIX_PROCESSES'
    assert request['cap_seconds'] == 180 and request['overall_budget_seconds'] == 110
    deadline = started + min(110, g._BUILD_TIMEOUT)
    sources = here / 'development-prefix-isolation'
    artifacts = out / 'prefix-isolation'
    artifacts.mkdir(parents=True, exist_ok=True)
    records = []
    for label, filename, expected, length, workname in PREFIXES:
        data = (sources / filename).read_bytes()
        assert len(data) == length and sha(data) == expected and data.startswith(b'import Submission\n')
        assert b'#eval' not in data and b'set_option' not in data
        directory = artifacts / label; directory.mkdir(exist_ok=True)
        (directory / 'source.lean').write_bytes(data)  # Complete module, no prepend.
        (directory / 'output.raw').write_bytes(b''); save(directory / 'resources.json', [])
        record = {'prefix': label, 'schema_version': 2, 'state': 'NOT_RUN_BASE_AUDIT_PENDING',
            'source_sha256': expected, 'source_bytes': length, 'exit_code': None, 'typecheck_process_complete': False,
            'output_sha256': sha(b''), 'output_bytes': 0, 'sampling_sha256': sha(b'[]\n'),
            'diagnostic_only': True, 'performance': 'NOT_RUN',
            'scope': 'This complete prefix only; never the1180 full Kernel/spec proof. Original g.own caps/build=read unchanged.'}
        save(directory / 'summary.json', record); records.append(record)
    summary = {'schema_version': 2, 'mode': request['mode'], 'kernel_sha256': B2, 'base_B2_audit': 'PENDING',
        'cap_seconds_ceiling': 180, 'overall_budget_seconds_from_stage_registration': min(110, g._BUILD_TIMEOUT),
        'outer_default_diagnostic_seconds': 120, 'prefixes': records,
        'scope': 'Independent process exits, not raw command markers. Whole original1180 proof remains NOT_RUN. Resource sampling records names/RSS/cgroups only, never argv/env.'}
    def persist():
        summary['elapsed_seconds_from_stage_registration'] = time.monotonic() - started
        save(artifacts / 'summary.json', summary)
    persist()
    spec = importlib.util.spec_from_file_location('r19_prefix_B2_base_audit', base)
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
    original = module.stages(g, kernel, out, manifest)
    assert [name for name, _ in original] == ['helper-kernel', 'helper-axioms']

    def wrap(name, action):
        def run(src, verdict):
            reason = action(src, verdict)  # Exactly one original call.
            if reason:
                summary['base_B2_audit'] = 'FAILED_' + name
                for record in records:
                    record['state'] = 'NOT_RUN_BASE_AUDIT_FAILED'
                    save(artifacts / record['prefix'] / 'summary.json', record)
            elif name == 'helper-axioms': summary['base_B2_audit'] = 'PASS_ORIGINAL_REPLAY_AND_FOUR_ROOTS'
            persist(); return reason
        return run

    def one_prefix(record, workname):
        directory = artifacts / record['prefix']; data = (directory / 'source.lean').read_bytes()
        cap = min(180, g._BUILD_TIMEOUT, int(deadline - time.monotonic() - 5))
        if cap < 1:
            record['state'] = 'NOT_RUN_OVERALL_BUDGET_EXHAUSTED'
            save(directory / 'summary.json', record); persist(); return False
        path = g.WORK.parent / workname
        assert not path.exists(); path.write_bytes(data)
        stop, lock = threading.Event(), threading.Lock()
        samples, errors, observed = [], [], set(); begin = time.monotonic()
        record.update(state='RUNNING', effective_call_cap_seconds=cap, resource_caps='UNCHANGED_ORIGINAL_G_OWN_BUILD_READ')
        save(directory / 'summary.json', record); persist()
        def watch():
            while not stop.is_set():
                try:
                    values, units = sample_proc(); values['elapsed_seconds'] = time.monotonic() - begin
                    with lock: samples.append(values); observed.update(units)
                except OSError as error:
                    if len(errors) < 8: errors.append(type(error).__name__)
                stop.wait(0.25)
        monitor = threading.Thread(target=watch, daemon=True); monitor.start(); raw = b''
        try:
            code, output = g.own([g.LAKE, 'env', 'lean', 'work/' + workname], cap, build='read')
            raw = output if isinstance(output, bytes) else output.encode()
            record.update(exit_code=code, typecheck_process_complete=code == 0,
                state='TYPECHECK_PROCESS_EXIT_ZERO' if code == 0 else 'PROCESS_NONZERO_CAUSE_UNCLASSIFIED')
        except BaseException as error:
            partial = getattr(error, 'output', None)
            if isinstance(partial, bytes): raw = partial
            elif isinstance(partial, str): raw = partial.encode()
            record.update(state='PROCESS_EXCEPTION', error_type=type(error).__name__, typecheck_process_complete=False)
        finally:
            stop.set(); monitor.join(timeout=1)
            record['monitor_join_incomplete'] = monitor.is_alive()
            with lock: captured, units = list(samples), sorted(observed)
            properties = []
            for unit in units[:4]:  # Only observed units; <=2s of read-only queries.
                allowance = min(0.5, deadline - time.monotonic() - 1)
                if allowance <= 0:
                    properties.append({'unit': unit, 'properties': 'UNKNOWN_BUDGET_EXHAUSTED'}); continue
                try:
                    response = subprocess.run(['systemctl', '--user', 'show', unit,
                        '--property=Result,MemoryPeak,MemoryMax,OOMPolicy,ActiveState,SubState'],
                        capture_output=True, text=True, timeout=allowance)
                    properties.append({'unit': unit, 'exit_code': response.returncode,
                        'properties': response.stdout if response.returncode == 0 else 'UNKNOWN_SCOPE_GONE_OR_QUERY_FAILED'})
                except (OSError, subprocess.TimeoutExpired): properties.append({'unit': unit, 'properties': 'UNKNOWN_QUERY_UNAVAILABLE'})
            record.update(elapsed_seconds=time.monotonic()-begin, output_bytes=len(raw), output_sha256=sha(raw),
                monitor_errors=errors, systemd_scopes=properties, observed_scope_count=len(units), queried_scope_count=len(properties),
                max_observed_process_rss_sum_kb=max((sum(p['rss_kb'] for p in s['processes']) for s in captured), default=None),
                resource_scope='Read-only names/RSS and cgroup counters; RSS sums may double-count shared pages. Observed scope association is evidence, not automatic causal attribution.')
            (directory / 'output.raw').write_bytes(raw)
            sampling = (json.dumps(captured, indent=2)+'\n').encode(); (directory / 'resources.json').write_bytes(sampling)
            record['sampling_sha256'] = sha(sampling); save(directory / 'summary.json', record)
            if path.exists(): path.unlink()
            persist()
        return record['typecheck_process_complete']

    def isolate(src, verdict):
        audit = json.loads((out / 'helper-audit.json').read_bytes())
        assert audit['accepted'] and audit['kernel_replay'] and audit['expected_count'] == 4 and audit['names'] == ROOTS
        for record in records:
            directory = artifacts / record['prefix']
            for filename in ('helper-audit.json', 'helper-audit-source.lean', 'helper-axioms.raw'):
                (directory / filename).write_bytes((out / filename).read_bytes())
        if not one_prefix(records[0], PREFIXES[0][4]):
            records[1]['state'] = 'NOT_RUN_IMPORT_CONTROL_FAILED_OR_BUDGET'
            save(artifacts / records[1]['prefix'] / 'summary.json', records[1]); persist()
            return 'ImportOnly positive control incomplete; QuotientOnly NOT_RUN'
        if not one_prefix(records[1], PREFIXES[1][4]): return 'QuotientOnly independent prefix incomplete: ' + records[1]['state']
        return None
    return [(name, wrap(name, action)) for name, action in original] + [('prefix-process-isolation', isolate)]
