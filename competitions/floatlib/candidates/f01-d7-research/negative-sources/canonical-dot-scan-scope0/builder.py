"""One actual BMM NaN-cold scanner composition; keep original normal branch.

No theorem or timing in this new namespace integration has been run in Lean.
"""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
R = ROOT / "competitions/floatlib/research/astra-collab-20261023-r7"


def sha(data):
    return hashlib.sha256(data).hexdigest()


parent = HERE.parent / "f01-d7-direct-nonfinite"
raw = (parent / "Kernel.lean").read_bytes()
word_source = (HERE / "nan-choice-block.lean").read_bytes()
scan = (HERE / "dot-nonnan-scan-block.lean").read_bytes()
closure = (R / "canonical-image-minimal-block.lean").read_bytes()
glue = (HERE / "canonical-dot-block.lean").read_bytes()
assert sha(raw) == "97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26"
assert sha(word_source) == "584ace5443838454b3687f7a93cfca07be4f9cce2c889c7196b171b7cfd4c93c"
assert sha(scan) == "5e46e932fb8483792c42a79d59e887e32af15e236100cbb8253ca82d3212ea8f"
assert sha(closure) == "61d49494b764bc433312202f3928a3dc6986eb91f4f64d2fb309ccf7370e0aed"
assert b"DWordNaN" not in raw and b"namespace R7W05" not in raw
raw_definition = word_source[word_source.index(b"@[inline] def rawNaN "):word_source.index(b"@[inline] def rawSNaN ")]
raw_bridge = word_source[word_source.index(b"theorem rawNaN_eq "):word_source.index(b"theorem rawSNaN_eq ")]
codec = b"""theorem exec_toModel_eq_rawModel (q : Competition.Binary32) :
    FloatLib.Floats.ExecFloat.Binary.toModel q = Model.NativeBinary32.ofUInt32 q.raw.1 := by
  change Model.ofBits (fmt := FloatFormat.binary32)
      (BitVec.ofNatLT q.raw.1.toNat q.raw.2) =
    Model.ofBits (fmt := FloatFormat.binary32) q.raw.1.toBitVec
  apply congrArg (Model.ofBits (fmt := FloatFormat.binary32))
  apply BitVec.eq_of_toNat_eq
  rfl
"""
classification = (b"namespace DWordNaN\n\nopen FloatLib.Floats.Formats.BinaryInterchange\n\n"
                  + raw_definition + raw_bridge + codec + b"\nend DWordNaN\n")
text = raw.decode()
marker = "namespace NativeFinal\n"
assert text.count(marker) == 1
insertion = ("end Submission\n\n" + classification.decode() + "\n" + scan.decode()
             + "\n\nnamespace Submission\n\n" + closure.decode() + "\n\n")
text = text.replace(marker, insertion + marker, 1)
dot_marker = "def dot (n baseA baseB p : Nat) (A B : Array Binary32) : Binary32 :=\n"
assert text.count(dot_marker) == 1
text = text.replace(dot_marker, glue.decode() + "\n\n" + dot_marker, 1)

# Keep the two finishing bodies definitionally identical, preserving the
# existing Packed10.finish_eq_dot proof and both actual execution routes.
old_dot = """  if hf : result.isNaN = false then ExecFloat.Binary.ofFloat32 result
  else R7NaNReplay.replayEarly n baseA baseB p A B"""
new_dot = """  if hf : result.isNaN = false then ExecFloat.Binary.ofFloat32 result
  else if hs : DDotNonNaNScan.whole n baseA baseB p A B = true then
    ExecFloat.Binary.ofFloat32 result
  else R7NaNReplay.replayEarly n baseA baseB p A B"""
assert text.count(old_dot) == 1
text = text.replace(old_dot, new_dot, 1)
old_finish = old_dot.replace("p A B", "p Araw Braw")
new_finish = new_dot.replace("p A B", "p Araw Braw")
assert text.count(old_finish) == 1
text = text.replace(old_finish, new_finish, 1)
old_proof = """  · refine (R7NaNReplay.replayEarly_eq n baseA baseB p A B).trans ?_
    apply congrArg (fun step : Binary32 → Fin n → Binary32 => Fin.foldl n step posZero)
    funext acc i
    simp only [R7NaNReplay.replayStep, Submission.add_eq, Submission.mul_eq]"""
new_proof = """  · split
    · rename_i hscan
      exact dot_eq_of_whole_nonNaN n baseA baseB p A B hscan
    · refine (R7NaNReplay.replayEarly_eq n baseA baseB p A B).trans ?_
      apply congrArg (fun step : Binary32 → Fin n → Binary32 => Fin.foldl n step posZero)
      funext acc i
      simp only [R7NaNReplay.replayStep, Submission.add_eq, Submission.mul_eq]"""
assert text.count(old_proof) == 1
text = text.replace(old_proof, new_proof, 1)

# Independently reversible exact text changes: retain all parent bytes,
# including its original normal path, add/mul/sum and address/layout proofs.
restored = text.replace(new_proof, old_proof, 1).replace(new_finish, old_finish, 1).replace(new_dot, old_dot, 1)
restored = restored.replace(glue.decode() + "\n\n" + dot_marker, dot_marker, 1)
restored = restored.replace(insertion + marker, marker, 1)
assert restored.encode() == raw
data = text.encode()
assert len(data) < 256000
out = HERE.parent / "f01-d7-canonical-dot-scan"
out.mkdir(exist_ok=True)
(out / "Kernel.lean").write_bytes(data)
manifest = {
    "candidate": out.name, "candidate_file": "Kernel.lean",
    "candidate_sha256": sha(data), "candidate_bytes": len(data),
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "parent": parent.name, "parent_sha256": sha(raw),
    "minimal_classifier_sha256": sha(classification), "codec_source": "W02 exec_toModel_eq_rawModel, only actual ExecFloat namespace made explicit",
    "scanner_block_sha256": sha(scan), "canonical_image_block_sha256": sha(closure),
    "canonical_dot_block_sha256": sha(glue),
    "validation_mode": "statement-only", "proof_status": "NOT_RUN_NEW_RAW_SCAN_CANONICAL_OPERATION_AND_ACTUAL_LOOP_COMPOSITION",
    "mechanism": "Only when the native BMM dot endpoint is NaN, scan exactly the actual Nat A-row/B-column inputs. If every original word is nonNaN including Inf, return the existing native endpoint import; otherwise retain exact quiet-stop replay. DirectSmall.dot and Packed10.finish use identical finishing expressions.",
    "proof_boundary": "The actual Nat loop is connected by induction using unrestricted imported-native add/mul closure plus exact original-input nonNaN codec/roundtrip. Arbitrary native seed is permitted there because its raw seed is explicitly ofFloat32 acc. Exported dot refinement then uses original +0; arbitrary noncanonical raw seeds are not accepted.",
    "source_preservation": "Inverse removal of only the inserted classifiers/scan/closure/refinement and two matching cold hooks plus dot proof reconstructs exact97f bytes. Existing finish_eq_dot and all later address/lane/layout/four operation proofs remain unchanged.",
    "cost_boundary": "Normal endpoints have no scan. Rejected NaN endpoints still pay scanning then old replay. Exposed807 quiet-stop comparison saves at most2412 prefix arithmetic steps on671 outputs but adds15102 eligible and9533 rejected word reads; these are counts, not time or gain. Native first passes and preparation remain costs.",
    "gain": "UNKNOWN", "new_lean": "NOT_RUN", "full_gate": "NOT_RUN", "formal_submission": "NOT_SUBMITTED",
}
(out / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"candidate": out.name, "sha256": sha(data), "bytes": len(data), "status": "NOT_RUN"}))
