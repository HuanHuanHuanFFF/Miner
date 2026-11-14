"""Owned proof-preserving R27 guard26 mechanism transplanted to complete source36.

The exact accepted old candidate is evidence for the mathematical proof idea,
not acceptance of this separately generated and re-aliased complete candidate.
Only full original all12 verification may establish this candidate's validity.
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


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def build(raw):
    assert sha(raw) == BASE
    source = raw.decode("utf-8")
    first = source.index("@[inline] def Ya7G ")
    end = source.index("\nend\n", first)
    source = source[:first] + once(source[first:end], "ks<=8", "ks<=26") + source[end:]
    first = source.index("lemma Ya7Ge ")
    end = source.index("\ndef Ybc ", first)
    proof = source[first:end]
    for old, new in [("ks ≤ 8", "ks ≤ 26"), ("ksڇ ≤ 8", "ksڇ ≤ 26"),
                     ("2^ksڇ<=2^8", "2^ksڇ<=2^26"), ("2^36*2^8", "2^36*2^26")]:
        proof = once(proof, old, new)
    assert proof.count("2^44") == 3
    proof = proof.replace("2^44", "2^62")
    extra = """       have hR28q:raڇ/Dڇ<2^26:=by
        apply (Nat.div_lt_iff_lt_mul hDp).mpr
        rw [hra]
        exact (Λ (Ρ _ hDp) (χ _)).trans_le ((ϥ Dڇ hpk).trans_eq (Μ _ _))
"""
    proof = once(proof, "       have hqsb:", extra + "       have hqsb:")
    source = source[:first] + proof + source[end:]
    # Byte budget only: remove optional ASCII spaces after two punctuation
    # tokens inside proof declarations. Runtime declarations are excluded.
    matches = list(DECL.finditer(source))
    chunks = []
    cursor = 0
    saved = 0
    compacted = []
    for index, match in enumerate(matches):
        next_start = matches[index+1].start() if index+1 < len(matches) else len(source)
        text = source[match.start():next_start]
        if text.startswith("lemma ") or text.startswith("theorem "):
            new_text = text.replace("-> ", "->").replace("<= ", "<=")
            if new_text != text:
                compacted.append(match.group(1))
                saved += len(text.encode()) - len(new_text.encode())
            chunks.append(source[cursor:match.start()] + new_text)
            cursor = next_start
    chunks.append(source[cursor:])
    result = "".join(chunks).encode("utf-8")
    assert len(result) <= 256000, len(result)
    assert result.count(b"import ") == 1 and b"import ContractExact\n" in result
    assert b"theorem correct:Obligation kernels" in result
    return result, {"proof_whitespace_bytes_saved": saved, "proof_whitespace_declarations": compacted,
                    "added_quotient_lemma_bytes": len(extra.encode())}


def transform(raw, submission=36, variant="norm26-36"):
    assert submission == 36 and variant == "norm26-36"
    return build(raw)[0]


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--source", type=Path, required=True)
    p.add_argument("--output", type=Path)
    p.add_argument("--receipt", type=Path, required=True)
    a = p.parse_args()
    raw = a.source.read_bytes()
    result, details = build(raw)
    if a.output:
        a.output.parent.mkdir(parents=True, exist_ok=True)
        a.output.write_bytes(result)
    receipt = {"at_utc": datetime.now(timezone.utc).isoformat(), "state": "ACTUAL_ALL12_SOURCE_NOT_COMPILED",
               "source_submission": 36, "base_sha256": sha(raw), "candidate_sha256": sha(result),
               "candidate_bytes": len(result), "free_bytes": 256000-len(result),
               "recipe_sha256": sha(Path(__file__).read_bytes()), **details,
               "mathematics": "ra=(r mod D)*2^ks, D<2^36, ks<=26 imply ra<2^62 and ra/D<2^26. Together with qq*2^ks<2^61 this restores qa<2^62 before unchanged exact bias combination and rounding.",
               "runtime_change": "Only Ya7G shifted-remainder admission widens8 to26. Every complete public36 strong runtime path remains, including smallK, prepared128, native add, native LayerNorm and original fallbacks.",
               "prior_evidence": "R27 dced7848 original all12 passed on source12; mathematical idea reused, this exact source36 proof/aliases still require original full gate.",
               "coverage": "Old seen Mixer batch1 finite model:8552 to11432 inner-fast candidates among12900 norm outputs; later rounding fallback and elapsed-time benefit UNKNOWN.",
               "speed": "UNKNOWN", "gate": "UNKNOWN", "publication": "Owned recipe/receipt only; full upstream/reconstructed Kernel private or ephemeral"}
    a.receipt.write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: receipt[k] for k in ("candidate_sha256", "candidate_bytes", "free_bytes", "proof_whitespace_bytes_saved", "state")}))


if __name__ == "__main__":
    main()
