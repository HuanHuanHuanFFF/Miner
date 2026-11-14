"""Full Mixer portfolio: paired GEMM, norm26, selective complete-call prepare.

Closed original interfaces: YaVM's correctness proof quantifies over the
dispatch predicate and uses only the inW bound. A rejected cache call uses
the unchanged original YaU output path. The exact new full gate is required.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent;ROUND=HERE.parents[1]
PINS={
 "pair":(HERE/"build_gemm36_pairlinear_v2.py","8a59c56f8c92d9f62d85375f3606224cd5bb9c756d4168519940fc4381391e08"),
 "norm":(ROUND/"research/cross-source/build_norm26_36.py","fe05b956373f898af7e09ca43924583af81c56a357e98f0b4e674f3c9de84c48"),
 "single":(ROUND/"research/cross-source/build_single_row36.py","faeae0cb57787e0a156accb8c800f033fbe05a2f9979658af0eda1bdf270dfb1"),
}
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(?:def|lemma|theorem|structure|abbrev)\s+([\w.'?!]+)")
STOP=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:noncomputable\s+)?(?:def|lemma|theorem|structure|abbrev|section|end|open|namespace|set_option)\b")
def sha(x):return hashlib.sha256(x).hexdigest()
def load(role):
    path,pin=PINS[role];assert sha(path.read_bytes())==pin,(role,"frozenrecipechanged")
    s=importlib.util.spec_from_file_location("r28_portfolio_"+role,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def declarations(source):
    bounds=[m.start() for m in STOP.finditer(source)]
    return {m.group(1):source[m.start():next((b for b in bounds if b>m.start()),len(source))] for m in DECL.finditer(source)}
def build(raw36,raw27):
    pair=load("pair");norm=load("norm");single=load("single")
    control,_=pair.build(raw36,raw27);assert sha(control)=="7b6e0cbaa7165488eef9fdd2f482bef522bb9b6d165649a88494e210f2a06ae3"
    normal,_=norm.build(raw36)
    source=control.decode();old=declarations(raw36.decode());nd=declarations(normal.decode())
    for name in ["Ya7G","Ya7Ge"]:
        assert source.count(old[name])==1
        source=source.replace(old[name],nd[name],1)
    assert source.count(single.OLD)==1;source=source.replace(single.OLD,single.NEW,1)
    probe="""def R28FastProbe (bx:ז) (BV:Array ז) (b:Array ο) (outW j:Nat):Bool :=
 if j<outW then
  let bv:=BV[j]!
  let bw:=b[j]!
  let lo:=Yp bx bv bw
  let hi:=Yu bx bv bw
  if (bx&&&0xFFFF)=255 || (bv&&&0xFFFF)=255 || Ξ bw=255 || hi<lo || hi-lo>15 then
   R28FastProbe bx BV b outW (j+1)
  else true
 else false
termination_by outW-j
"""
    assert "R28FastProbe" not in source
    source=source.replace("def YaVM ",probe+"def YaVM ",1)
    start=source.index("def YaVM ");end=source.index("\nlemma ZMD2 ",start)
    body=source[start:end]
    singleton="rows=1 && 64<=inW"
    assert body.count(singleton)==1
    body=body.replace(singleton,singleton+" && R28FastProbe BX[0]! BV b outW 0",1)
    marker=" && outW*inW<=4294967295 then"
    assert body.count(marker)==1
    predicate=" && BX.any (λ v=>Yk (v&&&0xFFFF)-Yk (v>>>16)<=15)"
    body=body.replace(marker,marker.replace(" then",predicate+" then"),1)
    source=source[:start]+body+source[end:]
    result=source.encode();assert len(result)<=256000
    return result,{"pairlinear_control_sha256":sha(control),"norm_component_sha256":sha(normal),
                   "dependencies":{role:{"path":str(path.relative_to(ROUND)),"sha256":pin} for role,(path,pin) in PINS.items()},
                   "runtime_changes":["finitepositivek paired128GEMM fromv2","Ya7G guard8to26 with quotientboundproof","YaVM singleton64+ precise fastdot probe and BX.any narrowmetadata filter"],
                   "exact_filter":"BX.any (lambda v=>Yk(v&0xffff)-Yk(v>>16)<=15), unsigned64. If no inputrow passes, skip XP/WP/MVi and execute original YaU fallback over alreadycomputed BX/BV.",
                   "singleton_probe":"R28FastProbe checks original MaU finite/bias-inclusive span metadata for at least one classifier output before preparing any cache; pure Bool dispatch, no new arithmetic assertion in ZMV0.",
                   "proof":"Norm26 changes Ya7Ge with required ra/D<2^26 bound. YaVM dispatch change retains original ZMV0 theorem body, which extracts only inW<1048576; all12actualcorrect connected. NOT_COMPILED.",
                   "scope":"Do not call this public36champion or approvedgate. Complete model cost includes metadata any scan, all admitted cache prep, transpose, extraction, output and fallback.",
                   "source_choice":"After currentRes64gap grew to19.015%, preserve frozenRescombo but make this stronger complete Mixer candidate available for the planned Mixer batch; no extraCI request.",
                   "publication":"Ownrecipe/receipt only; whole upstream/reconstructed source private/ephemeral"}
def transform(raw,submission=36,variant="mixer36-portfolio",donor_raw=None):
    assert submission==36 and variant=="mixer36-portfolio"
    if donor_raw is None:
        import os
        root=os.environ.get("TORCHLEAN_ROOT");path=Path(root)/"r28-source-private/official-27.lean" if root else HERE.parents[2]/"r27-5h-20261029T194443Z/competition-state/source-private/submission27-Kernel.lean";donor_raw=path.read_bytes()
    return build(raw,donor_raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--donor",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,"state":"FULL_PORTFOLIO_ACTUAL_ALL12_NOT_COMPILED","gate":"UNKNOWN","native_speed":"UNKNOWN","extra_CI_request":False}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","recipe_sha256","state"]}))
