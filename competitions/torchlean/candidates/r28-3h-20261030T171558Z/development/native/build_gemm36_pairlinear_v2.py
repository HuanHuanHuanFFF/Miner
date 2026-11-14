"""Source-only correction: native pairlinear for every nonempty finite k.

Unlike donor27, public36's prepared GEMM already handles small k. The first
recipe's copied k<20 dispatch discarded that path on typical/boundary Mixer.
This distinct v2 lowers only that dispatch to k<1; the copied proof uses k>0.
Frozen v1 is retained unchanged. Full new gate and end-to-end timing required.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
FROZEN_V1="80c7bbdd3a3042b4baed85a08ba46f55cb3e571251e4d1f037ba88a448347a96"
def sha(x):return hashlib.sha256(x).hexdigest()
def build(raw36,raw27):
    path=HERE/"build_gemm36_pairlinear.py"
    assert sha(path.read_bytes())==FROZEN_V1
    spec=importlib.util.spec_from_file_location("r28_pairlinear_v1_frozen",path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    original,meta=m.build(raw36,raw27)
    source=original.decode()
    old="if k<20||!(A.all finiteWord&&B.all finiteWord) then Ya3 batch m k n A B else"
    assert source.count(old)==1
    result=source.replace(old,old.replace("k<20","k<1"),1).encode()
    meta.update(previous_candidate_sha256=sha(original),dispatch="finite k>=1 uses public36 YaVM/MD2 pairlinear; k=0 or nonfinite uses original source36 Ya3",
                reason="Actual Mixer token GEMM k=T; typical T8..16 and boundaryT9..17. Donor27 threshold20 is not a valid source36 smallK preservation assumption.",
                proof="Identical R28Zc0Q proof except dispatch literal; it derives only k>0 via omega, originalall12 still requires new full gate")
    return result,meta
def transform(raw,submission=36,variant="gemm36-pairlinear-allk-v2",donor_raw=None):
    assert submission==36 and variant=="gemm36-pairlinear-allk-v2"
    if donor_raw is None:
        import os
        root=os.environ.get("TORCHLEAN_ROOT")
        path=Path(root)/"r28-source-private/official-27.lean" if root else HERE.parents[2]/"r27-5h-20261029T194443Z/competition-state/source-private/submission27-Kernel.lean"
        donor_raw=path.read_bytes()
    return build(raw,donor_raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--donor",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,
         "state":"PREFERRED_V2_ACTUAL_ALL12_NOT_COMPILED", "speed":"UNKNOWN","gate":"UNKNOWN",
         "publication":"Ownrecipe/receipt only; whole Kernel private/ephemeral"}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state"]}))
