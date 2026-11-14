"""Check only source reuse and size for a conditional future public bridge patch."""
from pathlib import Path
import difflib
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
SHA = lambda x: hashlib.sha256(x).hexdigest()


def main():
    old = (ROOT / 'competitions/floatlib/candidates/f01-r19-dev-direct-bias-runtime1/Kernel.lean').read_bytes()
    public_path = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-direct-bias-public1/Kernel.lean'
    public = public_path.read_bytes()
    assert SHA(public) == 'fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5'
    a, b = old.decode(), public.decode()
    core_start = '@[inline] def normalCore (sum u v : UInt32) : UInt32 :='
    guard_start = '\n@[inline] def guardedMul'
    core_a = a[a.index(core_start):a.index(guard_start, a.index(core_start))]
    core_b = b[b.index(core_start):b.index(guard_start, b.index(core_start))]
    assert core_a == core_b
    # Change only the fallback's static boundary, leaving public1's unvalidated math intact.
    marker = '\nnamespace Submission\nopen FloatLib.Floats Competition\n@[inline] def add := R19BiasBase.add'
    assert b.count(marker) == 1
    cold = ('\nnamespace R19BiasBase.R19DirectBias\nopen Competition\n'
            '@[noinline] def retainedMul (x y : Binary32) : Binary32 :=\n'
            '  R19BiasBase.mul x y\nend R19BiasBase.R19DirectBias\n')
    draft = b.replace(marker, cold + marker)
    old_public_mul = 'R19BiasBase.R19DirectBias.guardedMul R19BiasBase.mul x y'
    new_public_mul = 'R19BiasBase.R19DirectBias.guardedMul R19BiasBase.R19DirectBias.retainedMul x y'
    assert draft.count(old_public_mul) == 1
    draft = draft.replace(old_public_mul, new_public_mul)
    old_spec = 'R19BiasBase.R19DirectBias.guardedMul_spec R19BiasBase.mul R19BiasBase.mul_spec x y'
    new_spec = 'R19BiasBase.R19DirectBias.guardedMul_spec R19BiasBase.R19DirectBias.retainedMul R19BiasBase.mul_spec x y'
    assert draft.count(old_spec) == 1
    draft = draft.replace(old_spec, new_spec)
    raw = draft.encode()
    assert len(raw) <= 256000
    patch = ''.join(difflib.unified_diff(b.splitlines(keepends=True), draft.splitlines(keepends=True),
                    fromfile='f01-r19-dev-direct-bias-public1/Kernel.lean',
                    tofile='CONDITIONAL-NOT_COMPILED-public-cold-outline/Kernel.lean', n=3))
    (HERE / 'conditional-public-portability.patch').write_text(patch, encoding='utf-8', newline='')
    data = {
        'base_path': str(public_path), 'base_bytes': len(public), 'base_sha256': SHA(public),
        'base_status': 'Whole public fa652 statement signal-15/empty output cause UNKNOWN; full replay/48 roots NOT_RUN. Not an accepted public multiplication proof.',
        'old_runtime_and_public_normalCore_text_byte_identical': True,
        'normalCore_text_sha256': SHA(core_a.encode()),
        'patch_sha256': SHA(patch.encode()), 'projected_bytes': len(raw),
        'projected_sha256': SHA(raw), 'projected_headroom_bytes': 256000 - len(raw),
        'projected_source_materialized': False,
        'purpose': 'Conditional low-cost integration interface only; do not open a public proof/cost run before actual outlined-caller evidence.',
        'new_arithmetic_obligation': 'None at source denotation level; noinline wrapper is definitionally old B2 fallback. Existing unvalidated public obligations remain all required.',
        'new_structural_proof': 'Definitionally equal hf is intended; elaboration NOT_RUN. Cold-wrapper hf may use explicit rfl transport if elaboration requires it.',
        'actual_new_public_caller_ABI_and_speed': 'NOT_RUN; diagnostic static-runner shape does not transfer automatically.',
        'compile': 'NOT_RUN', 'replay': 'NOT_RUN', 'helper_axioms': 'NOT_RUN'
    }
    (HERE / 'proof-portability.json').write_text(json.dumps(data, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'source_equality': True, 'base_bytes': len(public), 'projected_bytes': len(raw),
                      'headroom': 256000 - len(raw), 'status': 'CONDITIONAL_NOT_COMPILED'}))


if __name__ == '__main__':
    main()
