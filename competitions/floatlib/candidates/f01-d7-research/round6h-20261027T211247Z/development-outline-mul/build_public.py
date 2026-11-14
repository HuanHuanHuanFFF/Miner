"""Materialize the conditional209-byte public integration after real cost signal.
No Lean, Git, CI, official file or source outside this owned directory is changed.
"""
from pathlib import Path
from types import SimpleNamespace
import ast
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
BASE = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-direct-bias-public1'
SHA = lambda raw: hashlib.sha256(raw).hexdigest()


def main():
    raw = (BASE / 'Kernel.lean').read_bytes()
    assert SHA(raw) == 'fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5'
    text = raw.decode()
    marker = '\nnamespace Submission\nopen FloatLib.Floats Competition\n@[inline] def add := R19BiasBase.add'
    cold = ('\nnamespace R19BiasBase.R19DirectBias\nopen Competition\n'
            '@[noinline] def retainedMul (x y : Binary32) : Binary32 :=\n'
            '  R19BiasBase.mul x y\nend R19BiasBase.R19DirectBias\n')
    assert text.count(marker) == 1
    draft = text.replace(marker, cold + marker)
    for old, new in (
        ('R19BiasBase.R19DirectBias.guardedMul R19BiasBase.mul x y',
         'R19BiasBase.R19DirectBias.guardedMul R19BiasBase.R19DirectBias.retainedMul x y'),
        ('R19BiasBase.R19DirectBias.guardedMul_spec R19BiasBase.mul R19BiasBase.mul_spec x y',
         'R19BiasBase.R19DirectBias.guardedMul_spec R19BiasBase.R19DirectBias.retainedMul R19BiasBase.mul_spec x y')):
        assert draft.count(old) == 1
        draft = draft.replace(old, new)
    source = draft.encode()
    assert len(source) == 255520 and SHA(source) == '88cdf318d952d74df95ecabed5e2bbadeab76d4827af1c4e5fd88e43d9d8f054'
    old_manifest = json.loads((BASE / 'manifest.json').read_bytes())
    roots = old_manifest['explicit_helper_audit'][:]
    assert 'R19BiasBase.R19DirectBias.retainedMul' not in roots
    roots.append('R19BiasBase.R19DirectBias.retainedMul')
    gate_path = ROOT / 'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw'
    gate = gate_path.read_bytes()
    assert SHA(gate) == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree = ast.parse(gate)
    selected = [n for n in tree.body if (isinstance(n, ast.FunctionDef) and n.name in ('intake', 'options', 'policy'))
                or (isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in ('OPTIONS', 'ATTRIBUTES', 'BANNED') for t in n.targets))]
    env = {'Path': Path, 're': re, '_MAX_BYTES': 256000, 'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
    code = ast.Module(body=[ast.ImportFrom(module='__future__', names=[ast.alias(name='annotations')], level=0), *selected], type_ignores=[])
    exec(compile(ast.fix_missing_locations(code), str(gate_path) + ':read-only-extract', 'exec'), env)
    out = HERE / 'public'
    out.mkdir(exist_ok=True)
    target = out / 'Kernel.lean'
    target.write_bytes(source)
    policy = {n: env[n](target, SimpleNamespace(slot='full')) for n in ('intake', 'policy')}
    assert all(v is None for v in policy.values()), policy
    manifest = {
        'candidate': 'f01-r22-outline-public-draft1', 'candidate_file': 'Kernel.lean',
        'candidate_sha256': SHA(source), 'candidate_bytes': len(source), 'headroom_bytes': 256000 - len(source),
        'validation_mode': 'statement-only', 'proof_status': 'NOT_RUN_NEW_PUBLIC_SOURCE; oldfa652 wholeproof/48roots remained NOT_RUN',
        'performance': 'NOT_RUN_FOR_THIS_SOURCE_OR_ORIGINAL_MainFull', 'full_gate': 'NOT_RUN',
        'formal_submission': 'NOT_SUBMITTED', 'official_submission_inherited': False,
        'explicit_helper_audit': roots,
        'origin': {'base_candidate': 'f01-r19-dev-direct-bias-public1', 'base_sha256': SHA(raw),
                   'base_bytes': len(raw), 'delta_bytes': len(source) - len(raw),
                   'normalCore_and_guard': 'Exact unchanged text; onlyB2 fallback global boundary changes.',
                   'new_math': 'No new arithmetic lemma intended; retainedMul unfolds definitionally to oldB2fallback. Existing fullfa652 arithmetic proofs still require original verification.'},
        'cost_evidence_scope': {'run': 40607316341, 'diagnostic_kernel_sha256': 'fd4e5b5144d00f3413b0b367a748e9be8f55d51017b4a8aaa5be53d404b1d6c1',
                                'relation': 'Positive full-diagnostic coldoutline signal only. No score or timing inherited into this exact newpublic source.'},
        'source_policy_preflight': {'gate_sha256': SHA(gate), 'intake_policy': policy,
                                    'scope': 'Exact saved function AST only; not gate/build/replay/axiom verification.'},
        'required_next': 'Original statement plusallhelper axiom/replay roots; actual originalMainFull selected publicMUL C/ASM and complete originalD beforeany source adoption.'
    }
    (out / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'sha256': SHA(source), 'bytes': len(source), 'headroom': 256000 - len(source),
                      'helper_roots': len(roots), 'policy': policy, 'status': 'NOT_RUN_PUBLIC_DRAFT'}))


if __name__ == '__main__':
    main()
