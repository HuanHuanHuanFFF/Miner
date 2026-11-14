"""Apply an owned narrow patch to an exact separately fetched public predecessor.

The predecessor is not embedded here and is not licensed for republication by
this script. Keep reconstructed whole-source files local/private. Run the
original gate on the exact output; this script does not assert Lean acceptance.
"""
from __future__ import annotations
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

BASE_SHA256 = "e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521"


def once(s, old, new):
    assert s.count(old) == 1, (old, s.count(old))
    return s.replace(old, new)


def transform(source):
    start = source.index("@[inline] def Ya7G ")
    end = source.index("\nend\n", start)
    body = source[start:end]
    body = once(body, "ks <= 8", "ks <= 26")
    source = source[:start] + body + source[end:]
    start = source.index("lemma Ya7Ge ")
    end = source.index("\ndef MYbc ", start)
    proof = source[start:end]
    for old,new in [("ks ≤ 8", "ks ≤ 26"), ("ks.toNat ≤ 8", "ks.toNat ≤ 26"),
                    ("2^ks.toNat <= 2^8", "2^ks.toNat <= 2^26"),
                    ("2^36*2^8", "2^36*2^26")]:
        proof = once(proof, old, new)
    # The remainder shifted by at most 26 has < 62 bits. Its quotient by D
    # has fewer than 26 bits; this stronger bound replaces the loose old
    # quotient <= numerator bound when combining with a < 61-bit main part.
    assert proof.count("2^44") == 3
    proof = proof.replace("2^44", "2^62")
    anchor = "       have hqsb:"
    assert proof.count(anchor) == 1
    extra = """       have hR27q:ra.toNat/D.toNat < 2^26:=by
        apply (Nat.div_lt_iff_lt_mul hDp).mpr
        rw [hra]
        have ht:=Nat.mul_lt_mul_of_pos_right (Nat.mod_lt (cv.toNat%D.toNat*mantOf gw) hDp) (Nat.two_pow_pos ks.toNat)
        have hu:=Nat.mul_le_mul_left D.toNat hpk
        nlinarith
"""
    proof = proof.replace(anchor, extra + anchor)
    return source[:start] + proof + source[end:]


def main():
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,required=True)
    p.add_argument("--output",type=Path,required=True)
    p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args()
    raw=a.source.read_bytes()
    assert hashlib.sha256(raw).hexdigest()==BASE_SHA256
    # Official raw files are LF; preserve byte conventions deliberately.
    text=raw.decode("utf-8")
    assert "\r" not in text
    new=transform(text).encode("utf-8")
    assert len(new)<=256000
    assert [l for l in new.decode().splitlines() if l.startswith("import ")]==["import ContractExact"]
    a.output.parent.mkdir(parents=True,exist_ok=True)
    a.output.write_bytes(new)
    result={"created_utc":datetime.now(timezone.utc).isoformat(),"state":"GENERATED_NOT_COMPILED_NOT_GATE_PASSED",
            "official_source_submission":12,"official_source_sha256":BASE_SHA256,
            "patch_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
            "candidate_sha256":hashlib.sha256(new).hexdigest(),"candidate_bytes":len(new),
            "entry":"Submission.kernels / Submission.correct",
            "change":"Expand exact layernorm UInt64 shifted remainder support from 8 to 26 bits; prove quotient bound before unchanged final rounding",
            "required":"Original all12 gate plus complete normalized_mlp paired cost; convert predecessor12 timing only through fresh current23 report chain",
            "current_champion_direct_measurement":"UNKNOWN_SOURCE_WITHHELD",
            "publication":"Owned patch and receipt only; reconstructed whole source remains private"}
    a.receipt.write_text(json.dumps(result,indent=2),encoding="utf-8")
    print(json.dumps(result))


if __name__=="__main__":main()
