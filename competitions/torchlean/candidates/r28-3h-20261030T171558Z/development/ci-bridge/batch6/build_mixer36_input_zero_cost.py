"""One complete NativeOnly cost prototype requested in Root191300.

Keep norm26 and original public36 GEMM. A cheap per-call rawzero probe selects
the input-zero MD2 loop; dense nozero calls retain the original hot loop.
No extra preparation/correction/transpose. New correct is deliberately absent.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
ROUND=next(p for p in HERE.parents if p.name=="r28-3h-20261030T171558Z")
NORM_RECIPE="fe05b956373f898af7e09ca43924583af81c56a357e98f0b4e674f3c9de84c48"
NORM_SOURCE="79615bd5c5c697d27631b999d7211c41dc5d0c4374cd9604324b417b1ad417d7"
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(def|lemma|theorem|structure|abbrev)\s+([\w.'?!]+)")
STOP=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(?:def|lemma|theorem|structure|abbrev|section|end|open|namespace|set_option)\b")
ARGS="X W b inW outW relu i j n A1 A2 B hA1 hA2 hB d1 d2 lo1 lo2 bw"
def sha(x):return hashlib.sha256(x).hexdigest()
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def declarations(source):
    bounds=[m.start()for m in STOP.finditer(source)]
    return {m.group(2):{"kind":m.group(1),"start":m.start(),"end":next((b for b in bounds if b>m.start()),len(source))}for m in DECL.finditer(source)}
def norm_control(raw):
    path=HERE/"build_norm26_36.py";assert sha(path.read_bytes())==NORM_RECIPE
    sp=importlib.util.spec_from_file_location("r28_inputzero_norm_control",path);m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    source,_=m.build(raw);assert sha(source)==NORM_SOURCE
    return source
def prune(source):
    d=declarations(source);deleted={"ZMVj"}
    while True:
        more={name for name,row in d.items()if row["kind"]in["lemma","theorem"]and any(re.search(r"(?<![\w.'?!])"+re.escape(n)+r"(?![\w.'?!])",source[row["start"]:row["end"]])for n in deleted)}
        if more<=deleted:break
        deleted|=more
    for name,row in sorted(d.items(),key=lambda x:x[1]["start"],reverse=True):
        if name in deleted:source=source[:row["start"]]+source[row["end"]:]
    assert deleted=={"ZMVj","ZMVi","ZMV0","correct"},deleted
    return source,sorted(deleted)
def build(raw):
    control=norm_control(raw);source,deleted=prune(control.decode());d=declarations(source)
    old=source[d["MD2"]["start"]:d["MD2"]["end"]]
    marker=":Array ο :=\n";where=old.index(marker)
    header=old[:where+len(marker)].replace("def MD2 ","def R28MD2InputZero ",1)
    finish=old[old.index("\n else\n",where):old.index("\ntermination_by",where)]
    body=""" if hk:k<n then
  let a1:=(A1.uget k (by have:=υ.mp hk;omega))ڈ-4611686018427387904
  let a2:=(A2.uget k (by have:=υ.mp hk;omega))ڈ-4611686018427387904
  if a1=0 then
   if a2=0 then
    R28MD2InputZero ARGS h1 l1 h2 l2 (k+1) out
   else
    let w:=(B.uget k (by have:=υ.mp hk;omega))ڈ-4611686018427387904
    let p2:=(a2*w)<<<d2
    let m2:=l2+p2
    R28MD2InputZero ARGS h1 l1 (h2+((0:ו)-(p2>>>63))+(if m2<l2 then 1 else 0)) m2 (k+1) out
  else if a2=0 then
   let w:=(B.uget k (by have:=υ.mp hk;omega))ڈ-4611686018427387904
   let p1:=(a1*w)<<<d1
   let m1:=l1+p1
   R28MD2InputZero ARGS (h1+((0:ו)-(p1>>>63))+(if m1<l1 then 1 else 0)) m1 h2 l2 (k+1) out
  else
   let w:=(B.uget k (by have:=υ.mp hk;omega))ڈ-4611686018427387904
   let p1:=(a1*w)<<<d1
   let p2:=(a2*w)<<<d2
   let m1:=l1+p1
   let m2:=l2+p2
   R28MD2InputZero ARGS (h1+((0:ו)-(p1>>>63))+(if m1<l1 then 1 else 0)) m1
    (h2+((0:ו)-(p2>>>63))+(if m2<l2 then 1 else 0)) m2 (k+1) out""".replace("ARGS",ARGS)
    new=header+body+finish+"\ntermination_by nڇ-kڇ\ndecreasing_by all_goals exact ZI n k hk\n\n"
    source=once(source,"\ndef MVj ","\n"+new+"def MVj ")
    start=source.index("def MVj ");end=source.index("\ndef MVo ",start);piece=source[start:end]
    piece=once(piece,"def MVj ","def MVj (r28Z:Bool) ")
    piece=piece.replace("MVj X W b","MVj r28Z X W b")
    begin=piece.index("    MD2 X W b");finish_call=piece.index("\n   else ",begin);call=piece[begin:finish_call]
    nested=lambda text:"\n".join(" "+line for line in text.split("\n"))
    both="    if r28Z then\n"+nested(call.replace("MD2 X W b","R28MD2InputZero X W b",1))+"\n    else\n"+nested(call)
    piece=piece[:begin]+both+piece[finish_call:];source=source[:start]+piece+source[end:]
    start=source.index("def MVi ");end=source.index("\ndef MPx ",start);piece=source[start:end]
    piece=once(piece,"def MVi ","def MVi (r28Z:Bool) ")
    piece=piece.replace("MVi X W b","MVi r28Z X W b").replace("MVj X W b","MVj r28Z X W b")
    source=source[:start]+piece+source[end:]
    probe="""def R28HasInputZero (x:Array ο) (n j:Nat):Bool :=
 if j<n then if (x[j]! &&& 0x7FFFFFFF)=0 then true else R28HasInputZero x n (j+1)
 else false
termination_by n-j
"""
    source=once(source,"def YaVM ",probe+"def YaVM ")
    start=source.index("def YaVM ");end=source.index("\nlemma ZMD2 ",start);piece=source[start:end]
    piece=once(piece,"  MVi X W b","  MVi (R28HasInputZero X (rows*inW) 0) X W b")
    source=source[:start]+piece+source[end:]
    result=source.encode();assert len(result)<=256000,len(result)
    assert "theorem correct:" not in source
    return result,{"control_norm26_sha256":NORM_SOURCE,"norm_recipe_sha256":NORM_RECIPE,"pruned_proofs":deleted,
                   "runtime_changed":["MVj","MVi","YaVM"],"new_runtime":["R28MD2InputZero","R28HasInputZero"],
                   "new_loop":"ExactC0=2^62. Both inputfactors zero: skipWread/products/shifts/carries; onezero: updateonly other row; neither: originalpaired128 work. OriginalMD2 untouched for nozero calls, MVo tail/GEMM/nativeadd/LN/fallback all retained.",
                   "dispatch":"Rawzero probe once per alreadyadmitted YaVM call, earlyreturn; Boolthread through MVi/MVj and directcall branch only peroutputdot, no new perMACdenseflagcheck/function-valuedconditional.",
                   "model":"MIXER-INPUT-ZERO-CENSUS.json:18oldMixerhashmatches; linear1zero0/6186, linear2zero6187/12372;137559/274108secondnativeproducts removable,6211totalprobereads;16k arbitraryword identities.",
                   "proof":"UNPROVED_NATIVE_RESEARCH_ONLY, no correct. Newloop pureword equality via nonrecursive step + controlledwordzero rules; restore genericZMVj/ZMVi/ZMV0 with Boolparameter after positive cost and sourcebudget proof.",
                   "acceptance":"NativeOnly firstcompleteMixer discriminator with norm26 control; allocation/probe/branch/fallback/destruction included. No formal/champion claim. Root decides whether fits existingfinalbatch; Mobilepositiveproof/confirmation first.",
                   "publication":"Ownrecipe/receipt only; whole Kernelprivate/ephemeral"}
def transform(raw,submission=36,variant="mixer36-input-zero-cost"):
    assert submission==36 and variant=="mixer36-input-zero-cost"
    return build(raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,"state":"UNPROVED_NATIVE_RESEARCH_ONLY_NOT_COMPILED","full_gate":False,"declares_correct":False,"native_speed":"UNKNOWN"}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k]for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state"]}))
