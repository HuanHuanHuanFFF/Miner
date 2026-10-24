"""R12 observer tests using byte streams and fake ELF, never a Lean result."""
from pathlib import Path
import importlib.util
import json
import os
import subprocess
import sys
import tempfile
import time

spec = importlib.util.spec_from_file_location('r12_mainfull', Path(__file__).with_name('capture-mainfull.py'))
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)

PROGRAM = r'''
from pathlib import Path
import os, shutil, sys, time
root, output, mode = Path(sys.argv[1]), Path(sys.argv[2]), sys.argv[3]
os.write(1, b'raw\xff\r\n')
if mode == 'timeout':
    time.sleep(20)
    sys.exit(0)
os.write(1, b'[state')
time.sleep(.02)
os.write(1, b'ment] ok\n')
deadline = time.monotonic() + 6
while not list(output.glob('capture-*/snapshot.json')) and time.monotonic() < deadline:
    time.sleep(.01)
target = (root / '.sandbox/layer/upper').resolve()
assert target.is_relative_to(root.resolve())
shutil.rmtree(target)
os.write(1, b'[score] original\x00\n')
sys.exit(7)
'''


def main():
    results = []
    with tempfile.TemporaryDirectory(prefix='scalar-observer-test-', dir=Path(__file__).parent) as temporary:
        base = Path(temporary).resolve()
        for mode in ('valid', 'mismatch', 'postfail', 'timeout'):
            case = base / mode
            root, output = case / 'official', case / 'output'
            upper = root / '.sandbox/layer/upper'
            (upper / 'ir').mkdir(parents=True)
            (root / 'lean/work').mkdir(parents=True)
            kernel = case / 'Kernel.lean'
            kernel.write_bytes(b'import ContractTensor\n-- fake exact source\n')
            (root / 'lean/work/Submission.lean').write_bytes(kernel.read_bytes() if mode != 'mismatch' else b'-- stale\n')
            for module in ('MainFull', 'Submission'):
                (upper / ('ir/' + module + '.c')).write_bytes(b'LEAN_EXPORT unsigned lp_competition_main___lam__0(unsigned a){return a;}\n')
                (upper / ('ir/' + module + '.c.o.export')).write_bytes(b'\x7fELF fake object')
                (upper / ('ir/' + module + '.c.o.export.trace')).write_bytes(b'{"log":[],"inputs":[]}\n')
            temp_root = case / 'runner-temp'
            temp_root.mkdir()
            env = os.environ.copy()
            env['RUNNER_TEMP'] = str(temp_root)
            before_env = env.copy()
            old_post = m._disassemble
            def fake_post(legacy, staged, folder, deadline, record):
                assert record['gate_exit_seconds'] >= 0
                assert not upper.exists()
                assert all(p.read_bytes().startswith(b'\x7fELF') for p, _ in staged)
                if mode == 'postfail':
                    raise RuntimeError('intentional postprocess failure')
                return {'state': 'TEST_ONLY_FAKE_ELF', 'selected_symbols': 0}
            m._disassemble = fake_post
            argv = [sys.executable, '-c', PROGRAM, str(root), str(output), mode]
            log = case / 'original.log'
            try:
                if mode == 'timeout':
                    try:
                        m.run_gate(argv, root, env, log, .3, output, kernel)
                    except subprocess.TimeoutExpired as exc:
                        record = exc.codegen_record
                        assert record['timed_out']
                    else:
                        raise AssertionError('timeout semantics changed')
                else:
                    completed, record = m.run_gate(argv, root, env, log, 9, output, kernel)
                    assert completed.returncode == 7 and completed.args == argv
                    assert log.read_bytes() == b'raw\xff\r\n[statement] ok\n[score] original\x00\n'
                    assert record['statement_events'] == record['snapshot_attempts'] == 1
                    assert record['state'] == ('UNKNOWN' if mode == 'mismatch' else 'CAPTURED')
                    if mode != 'mismatch':
                        assert {x['module'] for x in record['snapshot']['objects']} == {'MainFull', 'Submission'}
                    if mode == 'postfail':
                        assert record['disassembly']['state'] == 'UNKNOWN'
                assert env == before_env
                assert record['private_objects_removed'] and record['private_directory_removed']
                assert not list(temp_root.iterdir())
                assert all(not p.read_bytes().startswith(b'\x7fELF') for p in output.rglob('*') if p.is_file())
                results.append({'case': mode, 'pass': True, 'capture': record['state']})
            finally:
                m._disassemble = old_post
    scan = m.c_functions(b'LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t a){\nreturn a;\n}\nstatic const X x={.m_fun = (void*)lp_competition_main___lam__0___boxed};\n')
    assert scan['defined_functions'] == ['lp_competition_main___lam__0']
    assert scan['closure_targets'] == ['lp_competition_main___lam__0___boxed']
    old_hot = 'lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runScalar_spec__0'
    assert m.bench_suite_symbol(old_hot)
    assert m.bench_suite_symbol(old_hot + '___boxed')
    assert m.bench_suite_symbol('lp_competition_Bench_Suite_runScalar___lam__1___boxed')
    assert not m.bench_suite_symbol('lp_competition_Bench_Suite_runScalarity')
    results.append({'case': 'actual_old_BenchSuite_private_loop_symbol_boundary', 'pass': True})
    print(json.dumps({'state': 'PASS', 'tests': results, 'actual_Lean_ELF_gate': 'NOT_RUN'}, indent=2))


if __name__ == '__main__':
    main()
