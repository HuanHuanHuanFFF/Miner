"""Two proof-only line deletions requested by R; preserve frozen b962 source."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, difflib, time
OUT = Path(__file__).resolve().parent
sha = lambda b: hashlib.sha256(b).hexdigest()
start = time.monotonic()
old = (OUT / "Kernel-pairs.lean").read_bytes()
expected = "b9629b37f47ed8b5c169de213ccec2a67a2b3b2737803c5814e996c1a1cc16b3"
assert sha(old) == expected
eol = b"\r\n" if b"\r\n" in old else b"\n"
begin = old.index(b"namespace Submission.R15ThinPairs")
end = old.index(b"end Submission.R15ThinPairs", begin) + len(b"end Submission.R15ThinPairs")
fragment = old[begin:end]
newfragment = fragment
changes = []
for name, following in [("loop_s0", "loop_s1"), ("loop_s1", "select")]:
    left = b"theorem " + name.encode() + b" "
    right = (b"theorem " if following.startswith("loop") else b"@[inline] def ") + following.encode() + b" "
    i = newfragment.index(left); j = newfragment.index(right, i)
    theorem = newfragment[i:j]
    target = b"    dsimp only" + eol
    assert theorem.count(target) == 1
    removed_line = old[:begin].count(b"\n") + newfragment[:i].count(b"\n") + theorem[:theorem.index(target)].count(b"\n") + 1
    revised = theorem.replace(target, b"", 1)
    newfragment = newfragment[:i] + revised + newfragment[j:]
    changes.append({"theorem":name,"removed":"    dsimp only","scope":"after simp only [dif_pos hk]; no other edits"})
new = old[:begin] + newfragment + old[end:]
assert len(old)-len(new) == 2*len(b"    dsimp only"+eol)
# Prove exact inverse at the unique two tactic sequences.
needle = b"    simp only [dif_pos hk]"+eol+b"    simp only [Packed10.nativeA_getD]"
assert newfragment.count(needle) == 2
inversefragment = newfragment.replace(needle,b"    simp only [dif_pos hk]"+eol+b"    dsimp only"+eol+b"    simp only [Packed10.nativeA_getD]")
assert inversefragment == fragment
assert old[:begin] + inversefragment + old[end:] == old
(OUT / "Kernel-pairs-proof2.lean").write_bytes(new)
(OUT / "ThinPairs-proof2.lean").write_bytes(newfragment + eol)
diff = "".join(difflib.unified_diff(old.decode().splitlines(keepends=True),new.decode().splitlines(keepends=True),
             fromfile="Kernel-pairs.lean",tofile="Kernel-pairs-proof2.lean"))
(OUT / "pairs-proof2.diff").write_text(diff,encoding="utf-8",newline="")
assert sha((OUT / "Kernel-pairs.lean").read_bytes()) == expected
receipt = {"at_utc":datetime.now(timezone.utc).isoformat(),"source":"Kernel-pairs.lean","source_sha256":expected,
           "candidate":"Kernel-pairs-proof2.lean","candidate_sha256":sha(new),"candidate_bytes":len(new),
           "changes":changes,"exact_inverse_to_frozen_b962":True,"runtime_definitions":"BYTE_IDENTICAL",
           "reason":"Potential redundant dsimp tactic compatibility risk identified by D; no current candidate Lean error has been observed. Following simp only already performs zeta/projection simplification; this remains a proof attempt.",
           "status":"PROOF_ONLY_VARIANT_NOT_COMPILED","gate":"NOT_RUN","performance":"UNKNOWN; same runtime source does not imply same generated binary",
           "selection":"Alternative proof of the same runtime; not an additional runtime discovery trial or a reseed reset",
           "elapsed_seconds":time.monotonic()-start}
assert receipt["elapsed_seconds"] < 5
(OUT / "pairs-proof2-receipt.json").write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps(receipt,ensure_ascii=False))
