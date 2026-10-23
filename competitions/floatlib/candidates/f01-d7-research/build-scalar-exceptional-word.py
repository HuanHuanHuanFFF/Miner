"""Replace only existing rejected-finite scalar cold paths with exact words.

One mechanism rather than a field/shape grid. All new Lean integration is NOT_RUN.
"""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent / "f01-d7-scalar-nan-select"


def sha(data):
    return hashlib.sha256(data).hexdigest()


raw = (PARENT / "Kernel.lean").read_bytes()
original_math = (HERE / "exceptional-word-block.lean").read_bytes()
assert sha(raw) == "4a30c99f8230aae6d1b0cd238d1a6b1c9ac0aac0c448ca67d3005d3a6d00d528"
assert sha(original_math) == "b884fff04a3353c02d37a824e57aa43ea3b79834569b47601b225441023c79f1"
text = raw.decode()
start = text.index("namespace ScalarNaN\n")
end = text.index("end ScalarNaN", start) + len("end ScalarNaN")
old_helper = text[start:end]
adapted = original_math.decode()
old_scope = """The new namespace is global. Do not insert it inside Submission without
adjusting the documented namespace context and rechecking the exact file."""
new_scope = """This copy is nested under Submission for the actual scalar cold callers.
The global prototype is retained separately; this new namespace port is NOT_RUN."""
assert adapted.count(old_scope) == 1
adapted = adapted.replace(old_scope, new_scope, 1)
old_comment = "are written below. Existing context/options are retained; no Submission export."
assert adapted.count(old_comment) == 1
adapted = adapted.replace(old_comment, "are written below. Existing context/options are retained; no earlier operation change.", 1)
assert b"namespace DExceptionalWord" not in raw
text = text[:start] + adapted.rstrip() + text[end:]
changes = [
    ("else ScalarNaN.add x y", "else DExceptionalWord.addCold x y"),
    ("else ScalarNaN.mul x y", "else DExceptionalWord.mulCold x y"),
    ("  · exact ScalarNaN.add_spec x y", "  · rename_i hf\n    exact DExceptionalWord.addCold_spec x y hf"),
    ("  · exact ScalarNaN.mul_spec x y", "  · rename_i hf\n    exact DExceptionalWord.mulCold_spec x y hf"),
]
for before, after in changes:
    assert text.count(before) == 1, before
    text = text.replace(before, after, 1)
restored = text
for before, after in reversed(changes):
    assert restored.count(after) == 1
    restored = restored.replace(after, before, 1)
assert restored.count(adapted.rstrip()) == 1
restored = restored.replace(adapted.rstrip(), old_helper, 1)
assert restored.encode() == raw
data = text.encode()
assert len(data) < 256000 and "ScalarNaN." not in text
out = HERE.parent / "f01-d7-scalar-exceptional-word"
out.mkdir(exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": out.name, "candidate_file": "Kernel.lean",
    "candidate_sha256": sha(data), "candidate_bytes": len(data),
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "parent": PARENT.name, "parent_sha256": sha(raw),
    "original_math_block_sha256": sha(original_math),
    "adapted_nested_math_block_sha256": sha(adapted.encode()),
    "removed_scalar_nan_helper_sha256": sha(old_helper.encode()),
    "validation_mode": "statement-only", "proof_status": "NOT_RUN_NEW_NESTED_WORD_PROOF_AND_ACTUAL_SCALAR_COLD_CALLERS",
    "mechanism": "Only the existing nonfinite/rejected-finite cold branches of scalar add/nativeMul use direct UInt32 NaN priority/quieting and exact Inf/zero/invalid/sign construction. The runtime word helpers allocate no Option in source. All original finite/native/numeric/low-exponent branches and tensor order/layout remain byte-identical to the parent.",
    "proof_boundary": "The word helper is correct only if at least one original raw exponent is0xff; each existing false finite-guard branch now passes its actual rejected premise. General finite-input use is not permitted. Namespace port, two branch premise transports and the complete candidate remain uncompiled.",
    "source_inverse": "Removing only the nested exceptional block and restoring the original ScalarNaN helpers, two cold calls and two proof leaves reconstructs exact4a30 bytes. The separately retained global17331 proof prototype does not establish this nested-source acceptance.",
    "selection_basis": "New exposed807 frontier counts indicate many no-NaN Inf/zero/invalid cold misses remain after quiet-stop and singlepasssum; NaN-only selection cannot remove their generic decode cost. This is a full exceptional alternative, not an additional NaN parameter grid or an additive gain claim.",
    "cost_boundary": "Actual C/object shape and all cold hit/miss timings remain UNKNOWN. The parent4a30 and this candidate both need their own original statement/fullgate. Ordinary-path source preservation does not prove identical binary layout or zero overhead.",
    "gain": "UNKNOWN", "full_gate": "NOT_RUN", "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"candidate": out.name, "sha256": sha(data), "bytes": len(data), "status": "NOT_RUN"}))
