"""Owned recipe: public36 native-pair linear replaces scalar prepared GEMM.

Do not publish reconstructed upstream Kernel. Supply exact public36 and public27
source bytes privately. Original small-k/nonfinite Ya3 stays the fallback; all
other public36 entry points, native add and native LayerNorm remain connected.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, json, re

HERE = Path(__file__).resolve().parent
BASE_PIN = "595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b"
DONOR_PIN = "f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67"

def sha(data):
    return hashlib.sha256(data).hexdigest()

def once(source, before, after):
    assert source.count(before) == 1, (before, source.count(before))
    return source.replace(before, after, 1)

def donor_aliases(source):
    prelude = source[:source.index("structure Acc")]
    groups = re.finditer(r"\bopen\s+([\w.]+)\s+renaming\s+(.+?)(?=\s+open\s+|\s+local\s+notation|\s+local\s+postfix|$)", prelude)
    result = {}
    for group in groups:
        for name, alias in re.findall(r"([\w.'?!]+)->([\w'?!]+)", group.group(2)):
            qualified = group.group(1)+"."+name
            assert alias not in result or result[alias] == qualified
            result[alias] = qualified
    result.update({"ٳ":"Nat", "ٴ":"Int", "ؼ":"UInt32", "ػ":"UInt64", "ؽ":"Array", "ف":"Bool"})
    return result

def build(raw36, raw27):
    assert sha(raw36) == BASE_PIN, "public36 pin mismatch"
    assert sha(raw27) == DONOR_PIN, "public27 pin mismatch"
    base, donor = raw36.decode(), raw27.decode()
    begin = base.index("def MPc ")
    end = base.index("lemma ZLj ", begin)
    removed = base[begin:end]
    assert removed.count("def Ya3M ") == 1
    closure = donor[donor.index("lemma Yos "):donor.index("\ndef kernels:Kernels where")]
    closure = once(closure, "YaV m k n false", "YaVM m k n false")
    closure = once(closure, "rw[Zg2 _ _ _ hb,ZcC]", "rw[Zg2 _ _ _ hb,ZMV0,ZcC]")
    aliases = donor_aliases(donor)
    expression = re.compile(r"(?<![\w.'?!])("+"|".join(re.escape(k) for k in sorted(aliases,key=len,reverse=True))+r")(?![\w.'?!])")
    closure = expression.sub(lambda m:aliases[m.group()], closure)
    closure = closure.replace("ٽ", ".size")
    for old,new in [("ڀ (batch)","Array.ofFn (n:=batch)"), ("ڀ (n*k)","Array.ofFn (n:=n*k)"), ("ڀ (batch*(m*n))", "Array.ofFn (n:=batch*(m*n))")]:
        assert old in closure
        closure = closure.replace(old,new)
    names = re.findall(r"(?m)^(?:def|lemma)\s+([\w']+)", closure)
    renamed = {name:"R28"+name for name in names}
    tokens = re.compile(r"(?<![\w.'?!])("+"|".join(map(re.escape, names))+r")(?![\w.'?!])")
    closure = tokens.sub(lambda m:renamed[m.group()], closure)
    base = base[:begin]+closure+"\n"+base[end:]
    base = once(base,"dense:=⟨YaVM,Ya3M⟩","dense:=⟨YaVM,R28Ya3Q⟩")
    base = once(base,"ZMV0,ZcC,ZM3,Zc0,ZdC,ZdN,Zdt]","ZMV0,ZcC,R28Zc0Q,ZdC,ZdN,Zdt]")
    assert "def Ya3M " not in base and "lemma ZM3:" not in base
    assert not any(character in closure for character in ["ڀ","ٽ","ؽ","ٳ","ؼ"])
    result = base.encode()
    assert len(result) <= 256000
    return result, {
        "base_sha256":sha(raw36),"donor_sha256":sha(raw27),
        "removed_scalar_prepared_gemm_bytes":len(removed.encode()),
        "pair_linear_closure_bytes":len(closure.encode()),
        "removed_range":"def MPc through lemma ZM3; exclusive old Ya3M helpers/proofs",
        "retained_runtime":"YaVM native128 paired rows, original Ya3 small-k/nonfinite fallback, Ybf native add, YbcN LayerNorm",
        "new_runtime":"For finite k>=20 transpose each B batch, extract each A batch, call native128 paired-row YaVM with exact negative-zero bias, flatten outputs",
        "proof_interface":"public27 finite dot extension/coordinate proof closure requalified; YaVM rewritten through ZMV0 and ZcC; original all12 correct connected",
        "renamed_declarations":renamed,
    }

def transform(raw, submission=36, variant="gemm36-pairlinear", donor_raw=None):
    assert submission == 36 and variant == "gemm36-pairlinear"
    if donor_raw is None:
        import os
        root = os.environ.get("TORCHLEAN_ROOT")
        path = Path(root)/"r28-source-private/official-27.lean" if root else HERE.parents[2]/"r27-5h-20261029T194443Z/competition-state/source-private/submission27-Kernel.lean"
        donor_raw = path.read_bytes()
    return build(raw,donor_raw)[0]

if __name__ == "__main__":
    p=argparse.ArgumentParser()
    p.add_argument("--source",type=Path,required=True)
    p.add_argument("--donor",type=Path,required=True)
    p.add_argument("--output",type=Path)
    p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args()
    result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
    if a.output:
        a.output.parent.mkdir(parents=True,exist_ok=True)
        a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),
         "free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,
         "state":"ACTUAL_ALL12_DECLARED_NOT_COMPILED", "speed":"UNKNOWN", "gate":"UNKNOWN",
         "acceptance":"Exact original all12 gate, complete Mixer paired screen against current champion56, then frozen fresh confirmation",
         "publication":"Owned recipe/receipts only; whole upstream and reconstructed Kernel private/ephemeral"}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state"]}))
