"""Execute only the reviewed run() AST with fake processes; no subprocess launch."""
from pathlib import Path
from types import SimpleNamespace
from enum import IntEnum
import ast
import hashlib
import json
import subprocess
import time

HERE = Path(__file__).resolve().parent
PROFILE = HERE.parent / 'readonly-reference-profile.py'
sha = lambda data: hashlib.sha256(data).hexdigest()

class PosixSignal(IntEnum):
    SIGTERM = 15
    SIGKILL = 9


def exercise(mode, function, exception_class):
    output = HERE / 'reference-review-mock-output' / mode
    output.mkdir(parents=True, exist_ok=True)
    events = []
    state = {'alive': True, 'wait_calls': 0}

    def wait(timeout):
        state['wait_calls'] += 1
        if mode == 'nonzero_parent_child_alive':
            state['alive'] = False
            return 1
        if state['alive']:
            raise subprocess.TimeoutExpired('fake-workload', timeout)
        return -9

    def fake_systemctl(argv, **kwargs):
        events.append({'event': 'systemctl', 'argv': argv})
        if mode == 'cleanup_command_timeout':
            raise subprocess.TimeoutExpired('fake-systemctl', kwargs['timeout'])
        return SimpleNamespace(returncode=1, stdout=b'', stderr=b'unit kill failed')

    def fake_killpg(pid, sig):
        events.append({'event': 'killpg', 'pid': pid, 'signal': getattr(sig, 'name', str(sig))})
        if sig == 0 and not state['alive']:
            raise ProcessLookupError('mock process group gone')
        if mode == 'cleanup_command_timeout' and sig == PosixSignal.SIGKILL:
            state['alive'] = False
        # Simulate a task that remains alive, e.g. uninterruptible exit or a
        # descendant left outside this process group. This must be detected.

    summary = {}
    scope = {'DEADLINE': time.monotonic() + 1000, 'OUT': output, 'ENV': {},
             'summary': summary, 'save': lambda: None, 'time': time, 'sha': sha, 'Path': Path,
             'signal': PosixSignal,
             'os': SimpleNamespace(environ={'GITHUB_RUN_ID': 'mock'}, killpg=fake_killpg),
             'subprocess': SimpleNamespace(Popen=lambda *a, **k: SimpleNamespace(pid=42, wait=wait, poll=lambda: None if state['alive'] else -9),
                                           TimeoutExpired=subprocess.TimeoutExpired,
                                           STDOUT=subprocess.STDOUT,
                                           run=fake_systemctl)}
    exec(compile(ast.Module(body=[exception_class, function], type_ignores=[]), str(PROFILE), 'exec'), scope)
    caught = None
    try:
        scope['run'](['fake'], mode, HERE, 30, True)
    except Exception as error:
        caught = type(error).__name__
    recorded = summary.get('commands', [])
    post_hash_mismatch = None
    if recorded:
        path = output / (mode + '.log')
        if state['alive']:
            with path.open('ab') as stream:
                stream.write(b'possible late workload output\n')
            post_hash_mismatch = sha(path.read_bytes()) != recorded[0]['log_sha256']
    return {'mode': mode, 'caught': caught, 'workload_still_alive': state['alive'],
            'descendant_can_remain_alive': mode in ('kill_does_not_finish_workload', 'nonzero_parent_child_alive'),
            'wait_calls': state['wait_calls'],
            'killpg_calls': sum(x['event'] == 'killpg' and x['signal'] != '0' for x in events),
            'command_record_saved_before_verified_exit': bool(recorded),
            'cleanup_confirmed': recorded[0].get('cleanup_confirmed') if recorded else None,
            'abort_after_timeout': summary.get('abort_after_timeout'),
            'later_append_invalidates_recorded_log_hash': post_hash_mismatch,
            'events': events}


def main():
    source = PROFILE.read_bytes()
    tree = ast.parse(source)
    function = next(n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name == 'run')
    exception_class = next(n for n in tree.body if isinstance(n, ast.ClassDef) and n.name == 'ObservationTimeout')
    tests = [exercise(mode, function, exception_class) for mode in
             ('cleanup_command_timeout', 'kill_does_not_finish_workload', 'nonzero_parent_child_alive')]
    assert tests[0]['killpg_calls'] == 2
    assert not tests[0]['workload_still_alive']
    assert all(test['caught'] == 'ObservationTimeout' for test in tests[:2])
    assert all(test['abort_after_timeout'] for test in tests[:2])
    assert all(test['cleanup_confirmed'] is False for test in tests[:2])
    assert tests[2]['caught'] == 'RuntimeError' and tests[2]['killpg_calls'] == 0
    assert tests[1]['command_record_saved_before_verified_exit']
    assert tests[1]['later_append_invalidates_recorded_log_hash']
    report = {'reviewed_profile_sha256': sha(source),
              'source_sha256': sha(Path(__file__).read_bytes()),
              'scope': 'Only run() AST executed with fake Popen/systemctl/killpg. No native build, network or process.',
              'tests': tests}
    (HERE / 'reference-run-falsifier-results.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
