"""Exact full-source composition for Root's next ResNet batch, not a new queue.

Combines three independently owned, hash-frozen transformations: the core
zero-pair loop, native in-place BN, and the repaired mapIdx residual add.
No inherited all12 result or added performance is claimed.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
PIN11="ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3"
PIN53="3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb"
DEPS={
    "bn":("development/native/build_resnet11_inplace_bn.py","77b9d783d0fa5425683c87a81e8fc2b93d11e0d5957182035ad710e015f10b0a"),
    "zero":("research/resnet-mechanism/build_zero_pair.py","97fa0af45234ef9e19b266d45221dd207d291ac2f7dab1d06f8c1194fce61b22"),
    "add":("development/elementwise/mapidx_add_v2.py","27ec14984df36fbdc2f94ff17b6c0db279ccdfab74d752b2b789183a399f5cfc"),
}
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(?:def|lemma|theorem|structure|abbrev)\s+([\w.'?!]+)")
STOP=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(?:def|lemma|theorem|structure|abbrev|section|end|open|namespace|set_option)\b")
def sha(x):return hashlib.sha256(x).hexdigest()
def load(role):
    name,digest=DEPS[role];path=ROUND/name;assert sha(path.read_bytes())==digest,(role,"dependency changed")
    spec=importlib.util.spec_from_file_location("r28_combined_"+role,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def declarations(source):
    bounds=[m.start() for m in STOP.finditer(source)]
    return {m.group(1):source[m.start():next((b for b in bounds if b>m.start()),len(source))] for m in DECL.finditer(source)}
def build(raw11,raw53):
    assert sha(raw11)==PIN11 and sha(raw53)==PIN53
    bn=load("bn");zero=load("zero");add=load("add")
    bnraw,bnmeta=bn.build(raw11,raw53)
    source=zero.apply(bnraw.decode())
    old=declarations(raw11.decode());added=declarations(add.transform(raw11,11,"mapidx-add-v2").decode())
    assert old.keys()==added.keys()
    changed=[n for n in old if old[n]!=added[n]];assert changed==["Ybf","ZdC"],changed
    for name in changed:
        assert source.count(old[name])==1,name
        source=source.replace(old[name],added[name],1)
    result=source.encode();assert len(result)<=256000
    assert source.count("theorem correct:Obligation kernels") == 1
    assert "R28rBnCorrect" in declarations(source)["correct"]
    assert "R28zeroPair_eq" in source and "a.mapIdx" in declarations(source)["Ybf"]
    return result,{"base_sha256":PIN11,"donor_sha256":PIN53,"dependencies":DEPS,
                   "BN_component_sha256":sha(bnraw),"mapidx_component_sha256":sha(add.transform(raw11,11,"mapidx-add-v2")),
                   "changed_add_declarations":changed,
                   "portfolio":"Original11 full conv/depthwise/linear/pool portfolio; core3x3 zero-pair, inplaceBN over unchanged exactYsx, repairedmapIdxadd. All12 correct remains actual, NOT_COMPILED.",
                   "profile_evidence":"RootCI1 original11 seven-entry profile conv76.2-79.4%,BN11.7-13.1%,add4.3-5.6%; instrumentedentry shares omit outside costs and are not candidate timings.",
                   "queue":"NoextraCIrequest; optional exact integration for Root's alreadyplanned Rescore batch. Use full newgate/completepairedmeasurements; do not add component gains.",
                   "publication":"Ownrecipe/receipts only; whole upstream/reconstructed Kernel private/ephemeral"}
def transform(raw,submission=11,variant="resnet11-zero-bn-add",donor_raw=None):
    assert submission==11 and variant=="resnet11-zero-bn-add"
    if donor_raw is None:
        import os
        root=os.environ.get("TORCHLEAN_ROOT")
        path=Path(root)/"r28-source-private/official-53.lean" if root else ROUND/"competition-state/source-private/official-53.lean"
        donor_raw=path.read_bytes()
    return build(raw,donor_raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--donor",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,
         "state":"COMBINED_ACTUAL_ALL12_NOT_COMPILED","gate":"UNKNOWN","native_speed":"UNKNOWN","extra_CI_request":False}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state"]}))
