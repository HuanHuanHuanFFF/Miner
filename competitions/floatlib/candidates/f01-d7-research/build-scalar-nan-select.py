"""One cold-path candidate: exact raw NaN priority, ordinary paths unchanged."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parent
PARENT = CANDIDATES / "f01-d7-direct-nonnan"
raw = (PARENT / "Kernel.lean").read_bytes()
assert hashlib.sha256(raw).hexdigest() == "60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15"
text = raw.decode("utf-8")
block_raw = (HERE / "nan-choice-block.lean").read_bytes()
assert hashlib.sha256(block_raw).hexdigest() == "584ace5443838454b3687f7a93cfca07be4f9cce2c889c7196b171b7cfd4c93c"
blocks = []
for name in ("NativeBridge", "NotNaNProbe", "R7Native"):
    start = text.index("\nnamespace " + name + "\n", text.index("\nnamespace Submission\n"))
    end = text.index("\nend " + name, start) + len("\nend " + name)
    block = text[start:end]
    blocks.append((name, block))
    text = text[:start] + text[end:]

# DWordNaN is nested inside Submission here. Its unchanged qualified references
# depend only on the three closed proof namespaces and earlier FastMul.ofBits.
helper = """
namespace ScalarNaN

@[inline] def add (x y : Binary32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => TunedAdd.add x y

theorem add_spec (x y : Binary32) : add x y = ExecFloat.Spec.add x y := by
  unfold add
  split
  · rename_i w hw
    exact DWordNaN.selected_add x y w hw
  · exact TunedAdd.add_spec x y

@[inline] def mul (x y : Binary32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => FastMul.mul x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  split
  · rename_i w hw
    exact DWordNaN.selected_mul x y w hw
  · exact FastMul.mul_spec x y

end ScalarNaN

"""
anchor = "/-- Raw exponent tests establish both native input conditions. -/"
assert text.count(anchor) == 1
add_start = text.index(anchor)
mul_anchor = "/-- Raw finite input guards retain the original multiplication fallback. -/"
mul_start = text.index(mul_anchor, add_start)
mul_end = text.index("@[inline] def mul (x y : Binary32)", mul_start)
old_add, old_mul = text[add_start:mul_start], text[mul_start:mul_end]
assert old_add.count("else TunedAdd.add x y") == 1
assert old_add.count("exact TunedAdd.add_spec x y") == 1
assert old_mul.count("else FastMul.mul x y") == 1
assert old_mul.count("exact FastMul.mul_spec x y") == 1
new_add = old_add.replace("else TunedAdd.add x y", "else ScalarNaN.add x y")
new_add = new_add.replace("exact TunedAdd.add_spec x y", "exact ScalarNaN.add_spec x y")
new_mul = old_mul.replace("else FastMul.mul x y", "else ScalarNaN.mul x y")
new_mul = new_mul.replace("exact FastMul.mul_spec x y", "exact ScalarNaN.mul_spec x y")
text = text.replace(old_add, new_add).replace(old_mul, new_mul)
insert = "\n".join(block for _, block in blocks) + "\n\n" + block_raw.decode("utf-8") + helper
text = text.replace(anchor, insert + anchor, 1)

prefix_end = raw.decode().index("\nnamespace Submission\n")
assert text[:prefix_end] == raw.decode()[:prefix_end]
for name, block in blocks:
    assert text.count(block) == 1, name
assert text.count(block_raw.decode()) == 1
# Prove the builder changed only placement, two cold calls and their proofs.
reverse = text.replace(insert, "", 1).replace(new_add, old_add).replace(new_mul, old_mul)
for name, block in blocks:
    original_start = raw.decode().index("\nnamespace " + name + "\n", prefix_end)
    before = raw.decode()[:original_start]
    # Locate the exact original preceding text after removing other moved blocks.
    predecessor = before[-120:]
    assert reverse.count(predecessor) == 1, name
    reverse = reverse.replace(predecessor, predecessor + block, 1)
assert reverse.encode() == raw, "Unexpected change outside explicitly moved proofs/cold paths"

out = CANDIDATES / "f01-d7-scalar-nan-select"
out.mkdir(exist_ok=True)
data = text.encode("utf-8")
assert len(data) < 256000
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": out.name, "candidate_file": "Kernel.lean",
    "candidate_sha256": hashlib.sha256(data).hexdigest(), "candidate_bytes": len(data),
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "parent": PARENT.name, "parent_sha256": hashlib.sha256(raw).hexdigest(),
    "validation_mode": "statement-only", "proof_status": "NOT_RUN_NEW_INTEGRATION",
    "mechanism": "Only the existing nonfinite scalar fallback tries raw signaling-first NaN selection. Preserve selected operand sign/payload and set quiet bit; if neither input is NaN use the unchanged TunedAdd/FastMul fallback. All ordinary input guards, low-exponent multiplication and tensor order/layout remain unchanged.",
    "proof_route": "Reuse exact nan-choice probe theorem block under Submission.DWordNaN; move three unchanged closed proof namespaces before exported scalar definitions. Two helper match proofs and two cold-call substitutions are new and require actual Lean validation.",
    "proof_block_sha256": hashlib.sha256(block_raw).hexdigest(),
    "moved_proof_blocks_sha256": {name: hashlib.sha256(block.encode()).hexdigest() for name, block in blocks},
    "gain": "UNKNOWN; targets selected-NaN generic decode cost, while no-NaN exceptional inputs now pay extra classification. Tensor fallback exposure overlaps existing suffix routes; no additive gain claim.",
    "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"candidate": out.name, "sha256": manifest["candidate_sha256"], "bytes": len(data)}))
