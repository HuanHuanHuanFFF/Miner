"""NativeOnly fused BN/ReLU finish cost on exact combined70ee control.

No new correct theorem. The native finite FMA prefix is unchanged; negative
sum+relu returns0 before L-hint/round/pack, while positive uses original Ge.
This is complementary to the core-conv investigation, not another CI request.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
COMPOSE_PIN="5b547deba2190629b8c62a40bac205b4ab835045c9df6cddb1fdfc8529d18fab"
CONTROL_PIN="70eed3609e3985011c7c630010d77ada49812e961f966843d71491f938ab5a63"
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(def|lemma|theorem|structure|abbrev)\s+([\w.'?!]+)")
STOP=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(?:def|lemma|theorem|structure|abbrev|section|end|open|namespace|set_option)\b")
HELPER="""@[inline] def R28NativeYsxAct (r:Bool) (x y z:Word) (my iy mz iq:UInt64):Word :=
 if expOf x != 255 then
  let mp:=Yl x*my
  let p:=Yd x+iy
  let k:=if mp==0 then iq else if mz==0 then p else if p<=iq then p else iq
  let dp:=if k<=p then p-k else 0
  let dq:=if k<=iq then iq-k else 0
  if dp<=14 && dq<=38 then
   let neg:=(x^^^y)>>>31 != 0
   let tp:=mp<<<dp
   let tq:=mz<<<dq
   let ss:=(if neg then 0-tp else tp)+(if signOf z then 0-tq else tq)
   if r && ss>>>63 != 0 then 0 else
   let Lt:=(46:UInt64)+(mp>>>47)+dp
   let Lq:=(23:UInt64)+dq
   let M:=if Lt<=Lq then Lq else Lt
   act r (Ge ss (M+(1:UInt64)-(((x^^^y)^^^z)>>>31).toUInt64) (λ _=>((k.toNat:Int)-298)) (neg&&signOf z) true (k-298))
  else act r (YaYs x y z)
 else act r (YaYs x y z)
"""
def sha(x):return hashlib.sha256(x).hexdigest()
def prune(source):
    bounds=[m.start() for m in STOP.finditer(source)];decl=[]
    for m in DECL.finditer(source):
        end=next((b for b in bounds if b>m.start()),len(source));decl.append((m.group(1),m.group(2),m.start(),end,source[m.start():end]))
    deleted={"R28bCp"}
    while True:
        new={name for kind,name,a,b,text in decl if kind in ["lemma","theorem"] and any(re.search(r"(?<![\w.'?!])"+re.escape(n)+r"(?![\w.'?!])",text) for n in deleted)}
        if new<=deleted:break
        deleted|=new
    for kind,name,a,b,text in reversed(decl):
        if name in deleted:source=source[:a]+source[b:]
    assert "correct" in deleted
    return source,sorted(deleted)
def build(raw11,raw53):
    path=HERE/"build_resnet11_combined.py";assert sha(path.read_bytes())==COMPOSE_PIN
    spec=importlib.util.spec_from_file_location("r28_clip_cost_compose",path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    control,_=m.build(raw11,raw53);assert sha(control)==CONTROL_PIN
    source,deleted=prune(control.decode())
    assert "R28NativeYsxAct" not in source
    marker="def R28rBnChannels "
    assert source.count(marker)==1;source=source.replace(marker,HELPER+marker,1)
    old="fun w=>act av (Ysx w y z my iy mz iq)"
    new="fun w=>R28NativeYsxAct av w y z my iy mz iq"
    assert source.count(old)==1;source=source.replace(old,new,1)
    result=source.encode();assert len(result)<=256000
    assert "theorem correct:" not in source
    return result,{"control_sha256":CONTROL_PIN,"compose_recipe_sha256":COMPOSE_PIN,"pruned_proofs":deleted,
                   "runtime":"Negative native64 FMA total with relu=true returns0 before Lt/Lq/Ge; positive/relu-false original Ge hint and rounding; all slow/nonfinite fallbacks retained",
                   "preserved":"Original combined70ee convzero, in-placeBN traversal/cache, mapIdxadd, complete all12 runtime portfolio, source11 source53 biases/finish interfaces",
                   "proof":"UNPROVED_NATIVE_RESEARCH_ONLY. R28bCp/R28rBnCorrect/correct removed; no inherited gate. Source53clip model lemmas can prove helperpoint then restore BN/all12 after positive cost.",
                   "model":"BN11-CLIP-CENSUS.json:6oldCNNcells,70080source11fastoutputs,24861negativeReLUfinishshortcuts; countnotcost and BNonly11.7-13.1%instrumentedentryshare",
                   "measurement":"UNKNOWN; exactcombined70ee control and fullmodel checksums/timing required; no extraCI request or displacement of nearboard/finalconfirmation",
                   "publication":"Ownrecipe/receipt only; whole source private/ephemeral"}
def transform(raw,submission=11,variant="resnet11-clip-cost",donor_raw=None):
    assert submission==11 and variant=="resnet11-clip-cost"
    if donor_raw is None:
        import os
        root=os.environ.get("TORCHLEAN_ROOT");path=Path(root)/"r28-source-private/official-53.lean" if root else HERE.parents[1]/"competition-state/source-private/official-53.lean";donor_raw=path.read_bytes()
    return build(raw,donor_raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--donor",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,"state":"UNPROVED_NATIVE_RESEARCH_ONLY_NOT_COMPILED","full_gate":False,"declares_correct":False,"native_speed":"UNKNOWN","extra_CI_request":False}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state","pruned_proofs"]}))
