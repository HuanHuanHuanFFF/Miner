"""Lightweight safety checks; fake artifacts only, no Lean/toolchain validation."""
from pathlib import Path
import hashlib
import importlib.util
import json
import tempfile

spec = importlib.util.spec_from_file_location('mainfull_capture', Path(__file__).with_name('scalar-capture-existing.py'))
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)


def main():
    cases = []
    with tempfile.TemporaryDirectory(prefix='scalar-static-test-', dir=Path(__file__).parent) as temporary:
        base = Path(temporary)
        upstream = base / 'upstream'
        build = upstream / 'lean/.lake/build'
        (build / 'ir').mkdir(parents=True)
        (upstream / 'lean/work').mkdir()
        kernel = base / 'Kernel.lean'
        raw = b'import ContractTensor\n-- exact fake candidate\n'
        kernel.write_bytes(raw)
        expected = hashlib.sha256(raw).hexdigest()
        (upstream / 'lean/work/Submission.lean').write_bytes(raw)
        (build / 'ir/MainFull.c').write_bytes(b'/* cached baseline, not bound to candidate */\n')
        (build / 'ir/MainFull.c.o.export').write_bytes(b'\x7fELFfake object')
        (build / 'ir/MainFull.c.o.export.trace').write_text(json.dumps({'outputs': 'cached.o', 'inputs': [], 'log': []}))
        original_which = m.shutil.which
        m.shutil.which = lambda _: None
        try:
            output = base / 'captured'
            result = m.capture(upstream, kernel, output, expected)
            assert result['static_capture_state'] == 'CAPTURED_EXISTING_TEXT'
            assert result['last_work_source']['matches_requested']
            assert result['timed_candidate_mainfull']['state'] == 'UNKNOWN'
            assert result['objects'][0]['original_timed_candidate_identity'] == 'UNKNOWN'
            assert result['objects'][0]['unchanged_during_inspection']
            assert all(not p.read_bytes().startswith(b'\x7fELF') for p in output.iterdir() if p.is_file())
            cases.append('matching work plus stale shared MainFull stays UNKNOWN; no ELF exported')
            wrong = m.capture(upstream, kernel, base / 'wrong-sha', '0' * 64)
            assert wrong['errors'] and not wrong['files']
            cases.append('wrong exact candidate rejected before source capture')
            (upstream / 'lean/work/Submission.lean').write_bytes(b'-- another candidate\n')
            mismatch = m.capture(upstream, kernel, base / 'stale-work', expected)
            assert not mismatch['last_work_source']['matches_requested']
            assert mismatch['timed_candidate_mainfull']['state'] == 'UNKNOWN'
            cases.append('last source mismatch retained as evidence, never binds cached object')
            link = base / 'link'
            try:
                link.symlink_to(kernel)
            except OSError:
                cases.append('symlink check unavailable on this host')
            else:
                try:
                    m.read_regular(link, 256000)
                except ValueError:
                    cases.append('symlink read refused')
                else:
                    raise AssertionError('symlink accepted')
        finally:
            m.shutil.which = original_which
    assert m.selected_symbol('MainFull', 'lp_competition_main___lam__1___boxed')
    assert m.selected_symbol('BenchSuite', 'lp_competition_Bench_Suite_runScalar___redArg___lam__0')
    assert not m.selected_symbol('Submission', 'lp_competition_Submission_addition')
    print(json.dumps({'state': 'PASS', 'cases': cases, 'actual_Lean_ELF_gate': 'NOT_RUN'}, indent=2))


if __name__ == '__main__':
    main()
