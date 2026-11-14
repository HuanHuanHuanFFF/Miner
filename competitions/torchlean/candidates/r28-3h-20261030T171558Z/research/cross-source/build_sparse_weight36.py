"""Owned source36 patch: skip a shared exactly-zero weight in paired signed128.

The single-row loop, scalar GEMM, small-K and all fallbacks stay as upstream.
The structural loop proof uses a zero-word identity for arbitrary accumulators.
Generated complete upstream source is private; this is an uncompiled recipe.
"""
from pathlib import Path
import argparse
from datetime import datetime, timezone
import hashlib
import json
import re

BASE = "595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b"
DECL = re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:def|lemma|theorem|structure|abbrev)\s+([\w.']+)")


def once(source, old, new):
    assert source.count(old) == 1, (old, source.count(old))
    return source.replace(old, new)


def compact_proof_space(source):
    matches = list(DECL.finditer(source))
    chunks = []
    cursor = 0
    for index, match in enumerate(matches):
        end = matches[index+1].start() if index+1 < len(matches) else len(source)
        text = source[match.start():end]
        if text.startswith(("lemma ", "theorem ")):
            chunks.append(source[cursor:match.start()] + text.replace("-> ", "->").replace("<= ", "<="))
            cursor = end
    chunks.append(source[cursor:])
    return "".join(chunks)


def transform(raw, submission=36, variant="sparse-weight36"):
    assert submission == 36 and variant == "sparse-weight36"
    assert hashlib.sha256(raw).hexdigest() == BASE
    source = raw.decode("utf-8")
    a = source.index("def MD2 ")
    b = source.index("\ndef MVj ", a)
    body = source[a:b]
    anchor = "  let w:=(B.uget k (by have:=υ.mp hk;omega))ڈ-4611686018427387904\n"
    body = once(body, anchor, anchor + "  if hz:w=0 then\n   MD2 X W b inW outW relu i j n A1 A2 B hA1 hA2 hB d1 d2 lo1 lo2 bw h1 l1 h2 l2 (k+1) out\n  else\n")
    start = body.index("  let p1:=")
    end = body.index("\n else\n  let r1:=", start)
    body = body[:start] + "\n".join(" " + line for line in body[start:end].split("\n")) + body[end:]
    body = once(body, "decreasing_by exact ZI n k hk", "decreasing_by all_goals exact ZI n k hk")
    source = source[:a] + body + source[b:]
    a = source.index("lemma ZMD2 ")
    b = source.index("\nlemma ZSb ", a)
    proof = source[a:b]
    old = "  rw [MD2,MD,MD];simp only [dif_pos h0];exact ih (k+1) _ _ _ _ א"
    new = """  rw [MD2,MD,MD];simp only [dif_pos h0]
  by_cases hz:(B.uget k (by have:=υ.mp h0;omega))ڈ-4611686018427387904=0
  . simp only [dif_pos hz]
    simpa [hz] using ih (k+1) h1 l1 h2 l2 (by omega)
  . simp only [dif_neg hz];exact ih (k+1) _ _ _ _ א"""
    proof = once(proof, old, new)
    source = source[:a] + proof + source[b:]
    result = compact_proof_space(source).encode("utf-8")
    assert len(result) <= 256000, len(result)
    assert result.count(b"import ") == 1 and result.startswith(b"import ContractExact\n")
    return result


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--source", type=Path, required=True)
    p.add_argument("--output", type=Path)
    p.add_argument("--receipt", type=Path, required=True)
    a = p.parse_args()
    raw = a.source.read_bytes()
    result = transform(raw)
    if a.output:
        a.output.parent.mkdir(parents=True, exist_ok=True)
        a.output.write_bytes(result)
    receipt = {"at_utc": datetime.now(timezone.utc).isoformat(), "state": "ALL12_CONNECTED_UNCOMPILED_NEXT_ROUTE",
               "source_submission": 36, "base_sha256": hashlib.sha256(raw).hexdigest(),
               "candidate_sha256": hashlib.sha256(result).hexdigest(), "candidate_bytes": len(result),
               "recipe_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
               "mechanism": "Existing MD2 loads one shared prepared weight, tests decoded value zero, and directly recurs with all four accumulator words unchanged; eliminates both input loads/products/shifts/carry updates for this term. Original finish/bias/zero fallback unchanged.",
               "proof_interface": "ZMD2 structural induction splits on exact wordzero. A zero product has no carry or sign-extension contribution for arbitrary UInt64 h/l. Exact new proof and all12 require compile.",
               "not_changed": "Scalar MD/GEMM, singleton path, source36 native LayerNorm/add, all existing guards/fallbacks, all12 endpoints",
               "risk": "Adds a predictable not-taken branch on dense weights, potentially unpredictable on sparse weights. Need complete paired cost; operation counts are not speed.",
               "request": "No immediate extra CI request; keep as isolated next-route until planned Mixer feedback. If exercised, original all12 gate and complete model cost.",
               "publication": "Own recipe/receipt only; full source private/ephemeral"}
    a.receipt.write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: receipt[k] for k in ("candidate_sha256", "candidate_bytes", "state")}))


if __name__ == "__main__":
    main()
