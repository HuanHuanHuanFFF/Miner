"""AST/hash and mocked g.own checks only. NEVER executes local Lean."""
import ast
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
from types import SimpleNamespace
import subprocess
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
R19 = HERE.parent
ROOT = R19.parents[4]
CARRIER = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-prefix-isolation1'
V2 = R19 / 'development-resource-audit-v2.py'
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def module():
    spec = importlib.util.spec_from_file_location('prefix_fixture', V2)
    value = importlib.util.module_from_spec(spec); spec.loader.exec_module(value)
    return value


def main():
    before = json.loads((HERE / 'draft-before.json').read_bytes())
    assert sha(HERE / 'resource-audit-v2.before.py') == before['before_sha256']
    assert sha(V2) == sha(HERE / 'resource-audit-v2.impl.py')
    tree = ast.parse(V2.read_text('utf-8'))
    manifest = json.loads((CARRIER / 'manifest.json').read_bytes())
    assert sha(V2) == manifest['helper_audit_module_sha256']
    assert sha(CARRIER / 'Kernel.lean') == manifest['candidate_sha256'] == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    assert sha(R19 / 'development-resource-audit.py') == '6b33457f634b18213dcc2fb36a10fcdfc2fef84c2238dc77f62c45b2e8b524e1'
    assert sha(R19 / 'development-helper-audit-v5.py') == 'd2d7621ed97c73783d6402251c04b793a08d9c6c171e137735a07806c243a99a'
    assert manifest['diagnostic_evaluations'] == [] and len(manifest['explicit_helper_audit']) == 4
    cases = []
    for label, import_code, quotient_code, exhausted, raises in [
        ('both-zero', 0, 0, False, False), ('control-failed', 1, 0, False, False),
        ('quotient-nonzero', 0, 137, False, False), ('budget-exhausted', 0, 0, True, False),
        ('quotient-timeout', 0, 0, False, True)]:
        implementation = module()
        implementation.sample_proc = lambda: ({'processes': [], 'groups': {}}, set())
        clock = [0.0]; implementation.time = SimpleNamespace(monotonic=lambda: clock[0])
        work = HERE / 'mock-fixtures' / label / 'work'; work.mkdir(parents=True, exist_ok=True)
        out = work.parent / 'output'; out.mkdir(exist_ok=True)
        class FakeG:
            LAKE = 'MOCK_LAKE_NEVER_EXECUTED'
            WORK = work / 'Submission'
            _BUILD_TIMEOUT = 180
            AXIOMS = {'propext', 'Classical.choice', 'Quot.sound'}
            def __init__(self): self.calls = []; self.kernel_calls = 0
            def kernel(self, src, verdict): self.kernel_calls += 1; return None
            def own(self, argv, cap, build):
                self.calls.append((argv[-1], cap, build)); assert 0 < cap <= 180 and build == 'read'
                clock[0] += 1
                if argv[-1].endswith('R16HelperAudit.lean'):
                    return 0, '\n'.join("'"+name+"' depends on axioms: [propext, Classical.choice, Quot.sound]" for name in manifest['explicit_helper_audit'])
                filename = 'ImportOnly.lean' if 'ImportOnly' in argv[-1] else 'QuotientOnly.lean'
                actual = self.WORK.parent / Path(argv[-1]).name
                assert actual.read_bytes() == (HERE / filename).read_bytes()
                assert actual.read_bytes().count(b'import Submission\n') == 1
                if filename == 'QuotientOnly.lean' and raises:
                    raise subprocess.TimeoutExpired(argv, cap, output=b'MOCK_PARTIAL_STDOUT_NO_LEAN')
                return (import_code if filename == 'ImportOnly.lean' else quotient_code), 'MOCK_NO_LEAN_EXECUTION\n'
        fake = FakeG()
        callbacks = implementation.stages(fake, CARRIER / 'Kernel.lean', out, manifest)
        assert [name for name, _ in callbacks] == ['helper-kernel', 'helper-axioms', 'prefix-process-isolation']
        assert callbacks[0][1](CARRIER / 'Kernel.lean', None) is None
        assert callbacks[1][1](CARRIER / 'Kernel.lean', None) is None
        if exhausted: clock[0] = 200
        reason = callbacks[2][1](CARRIER / 'Kernel.lean', None)
        summary = json.loads((out / 'prefix-isolation/summary.json').read_bytes())
        prefix_calls = [c for c in fake.calls if not c[0].endswith('R16HelperAudit.lean')]
        expected = 0 if exhausted else 1 if import_code else 2
        assert fake.kernel_calls == 1 and len(fake.calls)-len(prefix_calls) == 1 and len(prefix_calls) == expected
        assert (reason is None) == (label == 'both-zero')
        assert summary['prefixes'][0]['typecheck_process_complete'] == (not exhausted and import_code == 0)
        assert summary['prefixes'][1]['typecheck_process_complete'] == (label == 'both-zero')
        for record in summary['prefixes']:
            directory = out / 'prefix-isolation' / record['prefix']
            assert sha(directory / 'source.lean') == record['source_sha256']
            assert sha(directory / 'output.raw') == record['output_sha256']
            assert sha(directory / 'resources.json') == record['sampling_sha256']
            for name in ('helper-audit.json', 'helper-audit-source.lean', 'helper-axioms.raw'):
                assert (directory/name).read_bytes() == (out/name).read_bytes()
        if raises: assert (out/'prefix-isolation/quotient-only/output.raw').read_bytes() == b'MOCK_PARTIAL_STDOUT_NO_LEAN'
        cases.append({'case': label, 'kernel_replay_calls': fake.kernel_calls, 'four_root_own_calls': 1,
            'prefix_process_calls': expected, 'states': [r['state'] for r in summary['prefixes']], 'reason': reason,
            'scope': 'MOCK ONLY; no Lean/process/cgroup measurement was executed.'})
    report = {'status': 'PASS_AST_HASH_AND_MOCK_ONLY', 'verified_at_utc': datetime.now(timezone.utc).isoformat(),
        'v2_sha256': sha(V2), 'manifest_sha256': sha(CARRIER/'manifest.json'),
        'carrier_sha256': sha(CARRIER/'Kernel.lean'), 'AST_parse': True,
        'stages_functions': sum(isinstance(n, ast.FunctionDef) and n.name == 'stages' for n in tree.body),
        'source_modules': [{'file': n, 'bytes': (HERE/n).stat().st_size, 'sha256': sha(HERE/n)} for n in ('ImportOnly.lean','QuotientOnly.lean')],
        'cases': cases, 'real_Lean_execution': 'NOT_RUN', 'CI': 'NOT_DISPATCHED',
        'scope': 'Mocks verify control ordering, strict stop, per-prefix persistence, partial failure output, base audit once, and immutable bytes. No prefix theorem acceptance claimed.'}
    (HERE/'local-verification.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    print(json.dumps({'status':report['status'],'cases':len(cases),'v2_sha256':report['v2_sha256'],'real_Lean_execution':'NOT_RUN'}))


if __name__ == '__main__': main()
