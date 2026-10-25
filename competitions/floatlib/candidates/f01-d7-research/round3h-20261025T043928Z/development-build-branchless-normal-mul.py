"""Materialize one explicit branchless/literal rounder candidate, not a seed retry."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
sha = lambda b: hashlib.sha256(b).hexdigest()
parent = C / 'f01-r14-dev-mul-cache-rse2/Kernel.lean'
raw = parent.read_bytes()
assert sha(raw) == '9038f8d653f030a8812c3187733488f70995253a1a7b284759c4f58b96378c19'
needle = b'''@[inline] def mul (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul mulBeforeExponent x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  exact R14ExponentShift.guardedMul_spec mulBeforeExponent mulBeforeExponent_spec x y
'''
assert raw.count(needle) == 1
piece = HERE / 'development-branchless-normal-mul1.lean'
fragment = piece.read_bytes()
result = raw.replace(needle, fragment)
assert result.replace(fragment, needle) == raw and len(result) <= 256000
folder = C / 'f01-r15-dev-mul-branchless1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=sha(result),
    candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(),
    parent=parent.parent.name, parent_sha256=sha(raw), parent_actual_full_run=40155753018,
    parent_negative_preserved='R14 whole1.047144/MUL1.290801 vsDF; full correctness passed but first D failed. This exact new runtime has not been measured.',
    components=[dict(path=piece.relative_to(ROOT).as_posix(), sha256=sha(fragment), bytes=len(fragment))],
    mechanism='Normal-MUL rounder uses explicit 0/1 UInt64 comparison flags and bitwise combine, literal shifts23/24, and one shared rounded result for carry/fraction. Old normal eligibility and DF fallback are unchanged.',
    proof_route='Boolean/0-1 case equality to existing FastMul.rse, existing shiftWord_values, pack equality to the accepted R14 core, then existing complete guardedMul_spec. No new biased RNE/Nat normal proof.',
    cost_hypothesis='Remove nested data-dependent round-return decisions and generic variable-shift boundary work. Old machine code may already optimize some of it; actual C and benefit UNKNOWN. Stop if no distinct compiled work or first clean D fails.',
    unchanged='All non-MUL runtime and every old proof byte outside the exported mul/spec splice retained.',
    inverse_splice_exact=True, proof_status='NOT_COMPILED', full_gate='NOT_RUN', performance='NOT_RUN')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({k: record[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
