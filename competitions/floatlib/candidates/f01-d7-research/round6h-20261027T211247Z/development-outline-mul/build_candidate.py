"""Build a diagnostic-only cold-outline MUL carrier, without Lean or native tools."""
from pathlib import Path
import ast
import difflib
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-direct-bias-runtime1/Kernel.lean'
B2 = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
GATE = ROOT / 'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw'
OLD_SHA = '74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc'
B2_SHA = '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
GATE_SHA = '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def save(name, value):
    (HERE / name).write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


def main():
    old, b2, gate = OLD.read_bytes(), B2.read_bytes(), GATE.read_bytes()
    assert sha(old) == OLD_SHA and sha(b2) == B2_SHA and sha(gate) == GATE_SHA
    assert old.startswith(b2) and len(b2) == 226829
    old_suffix = old[len(b2):].decode('utf-8')
    start = old_suffix.index('@[inline] def normalCore')
    stop = old_suffix.index('\n@[inline] def guardedMul', start)
    core = old_suffix[start:stop]
    suffix = (
        '\nnamespace Submission.R22OutlineMul\nopen Competition\n\n'
        '/-- Diagnostic only: cold B2 fallback is isolated; no new public MUL theorem. -/\n'
        '@[noinline] def retainedMul (x y : Binary32) : Binary32 :=\n'
        '  Submission.mul x y\n\n'
        '@[inline] def guardedMul (x y : Binary32) : Binary32 :=\n'
        '  Submission.R19DirectBias.guardedMul retainedMul x y\n\n'
        '@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=\n'
        '  guardedMul x y\n'
        'end Submission.R22OutlineMul\n'
    )
    candidate = old + suffix.encode('utf-8')
    assert len(candidate) <= 256000
    assert candidate.startswith(b2)
    assert core.encode() in candidate
    assert suffix.count('Submission.mul') == 1
    assert suffix.count('retainedMul x y') == 1
    assert 'fallback :' not in suffix
    assert candidate.count(b'normalCore s u v') == 1
    assert not re.search(r'\b(unsafe|extern|implemented_by|axiom|sorry|admit)\b', suffix)
    # Inspect the exact original policy AST without importing or running gate.py.
    parsed = ast.parse(gate)
    attrs = next(ast.literal_eval(n.value) for n in parsed.body
                 if isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id == 'ATTRIBUTES' for t in n.targets))
    assert {'inline', 'noinline'} <= attrs
    target = HERE / 'Kernel.lean'
    if target.exists() and sha(target.read_bytes()) == '1de584efcb6fc8d74ed3ec2fe30d4c69ff5db6027823839c71fa03075cfbe486':
        (HERE / 'Kernel-v1-1de584.lean').write_bytes(target.read_bytes())
    target.write_bytes(candidate)
    patch = ''.join(difflib.unified_diff(old.decode().splitlines(keepends=True),
                    candidate.decode().splitlines(keepends=True),
                    fromfile='f01-r19-dev-direct-bias-runtime1/Kernel.lean',
                    tofile='development-outline-mul/Kernel.lean', n=3))
    (HERE / 'minimal.patch').write_text(patch, encoding='utf-8', newline='')
    roots = ['Submission.add_spec', 'Submission.mul_spec', 'Submission.sum_spec',
             'Submission.bmm_spec', 'Submission.R22OutlineMul.retainedMul',
             'Submission.R19DirectBias.normalCore', 'Submission.R22OutlineMul.guardedMul',
             'Submission.R22OutlineMul.diagnosticEntry']
    caller = HERE / 'R22OutlineCostMain.lean'
    aliases = HERE / 'CallerAliases.lean.inc'
    caller_text = caller.read_text(encoding='utf-8')
    assert all('@[noinline] def ' + x + ' : IO UInt32' in caller_text
               for x in ('runControl', 'runInlineOld', 'runOutline'))
    assert caller_text.count('Bench.Suite.run') == 3
    assert caller_text.count('IO.getEnv') == 1
    save('source-manifest.json', {
        'candidate': {'path': str(HERE / 'Kernel.lean'), 'bytes': len(candidate), 'sha256': sha(candidate)},
        'baseline': {'path': str(B2), 'bytes': len(b2), 'sha256': B2_SHA, 'prefix_byte_identical': True},
        'previous_runtime': {'path': str(OLD), 'bytes': len(old), 'sha256': OLD_SHA},
        'policy': {'path': str(GATE), 'sha256': GATE_SHA, 'inline_noinline_allowed_in_exact_gate': True},
        'normalCore_text_byte_identical': True,
        'normalCore_text_sha256': sha(core.encode()),
        'guard_change': 'Exact old748999 is a byte-identical prefix, including generic guardedMul. New inline alias applies it to static noinline retainedMul; both original misses are unchanged.',
        'previous_runtime_entire_prefix_byte_identical': True,
        'caller': {'path': str(caller), 'bytes': caller.stat().st_size, 'sha256': sha(caller.read_bytes()),
                   'variant_values': ['control', 'inlineOld', 'outline'],
                   'Suite_runner_entrypoints': ['runControl', 'runInlineOld', 'runOutline'],
                   'actual_static_arity2_callbacks': 'NOT_RUN; source intent only, verify actual selected C/ASM'},
        'structural_bridge_fragment': {'path': str(aliases), 'sha256': sha(aliases.read_bytes()), 'status': 'NOT_COMPILED'},
        'public_endpoints': 'All four public endpoints and four specs remain exact B2 prefix. Diagnostic not integrated into public MUL.',
        'diagnostic_entry': 'Submission.R22OutlineMul.diagnosticEntry',
        'static_cold_fallback': 'Submission.R22OutlineMul.retainedMul : Binary32 -> Binary32 -> Binary32',
        'suggested_helper_audit_roots': roots,
        'correctness': 'NOT_RUN; old public specs present, no new equality theorem',
        'compilation': 'NOT_RUN', 'actual_caller_ASM': 'NOT_RUN', 'performance': 'NOT_RUN',
        'local_check_scope': 'Source/hash/prefix/interface/policy-allowlist only; no Lean or native compiler invoked.',
        'patch': {'path': str(HERE / 'minimal.patch'), 'sha256': sha(patch.encode())},
        'token_usage': 'UNKNOWN', 'cache_token_usage': 'UNKNOWN'
    })
    print(json.dumps({'sha256': sha(candidate), 'bytes': len(candidate), 'prefix': B2_SHA,
                      'normalCore_text_sha256': sha(core.encode()), 'policy_noinline': True}))


if __name__ == '__main__':
    main()
