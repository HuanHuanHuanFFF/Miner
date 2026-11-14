"""Owned cross-source recipe: #53's per-channel in-place map over #11 FMA.

Preserves source11's arithmetic, guards and fallback, adding only the exact
in-place output traversal. Donor full source is private input, not published.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,re
HERE=Path(__file__).resolve().parent
BASE_PIN="ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3"
DONOR_PIN="3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb"
def sha(x):return hashlib.sha256(x).hexdigest()
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def build(raw11,raw53):
    assert sha(raw11)==BASE_PIN
    assert sha(raw53)==DONOR_PIN
    base,donor=raw11.decode(),raw53.decode()
    begin=base.index("def Ysj ");end=base.index("def Ysm ",begin)
    removed=base[begin:end]
    start=donor.index("@[specialize] def rBnMap ");stop=donor.index("\ndef ao ",start)
    closure=donor[start:stop]
    closure=closure.replace("fun w=>YsxAct av w y z (Yl y) (Yd y) (Yl z) (Yd z+149)","fun w=>act av (Ysx w y z (Yl y) (Yd y) (Yl z) (Yd z+149))")
    closure=closure.replace("fun w=>YsxAct av w s[ch]! t[ch]! (Yl s[ch]!) (Yd s[ch]!) (Yl t[ch]!) (Yd t[ch]!+149)","fun w=>act av (Ysx w s[ch]! t[ch]! (Yl s[ch]!) (Yd s[ch]!) (Yl t[ch]!) (Yd t[ch]!+149))")
    closure=once(closure,"  let z:=t[ch]!\n  let xx:=", "  let z:=t[ch]!\n  let my:=Yl y\n  let iy:=Yd y\n  let mz:=Yl z\n  let iq:=Yd z+149\n  let xx:=")
    closure=once(closure,"fun w=>act av (Ysx w y z (Yl y) (Yd y) (Yl z) (Yd z+149))", "fun w=>act av (Ysx w y z my iy mz iq)")
    closure=once(closure,"simp only[clipPoint,G1 _ _ _ hff.1 hff.2]","simp only[YsxE _ _ _ hff.1 hff.2]")
    # #11's original YaY=exact fused multiply-add and fallback equalities.
    closure=closure.replace("X1]","ZcR]")
    closure=closure.replace(" E0 av)"," ZdBO av)")
    aliases={"δ":"Word","م":"USize","ل":"Array","ه":"Bool","ٽ":"Nat","ق":"UInt64","ك":"UInt32","QK":"R28BnIncrement"}
    expr=re.compile(r"(?<![\w.'?!])("+"|".join(map(re.escape,aliases))+r")(?![\w.'?!])")
    closure=expr.sub(lambda m:aliases[m.group()],closure)
    closure=closure.replace("چ",".size").replace("ڇ",".toNat")
    names=re.findall(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:def|lemma)\s+([\w']+)",closure)
    assert names==["rBnMap","bMp","rBnChannels","bCp","rBnInplace","rBnCorrect"]
    renames={name:"R28"+name for name in names}
    expr=re.compile(r"(?<![\w.'?!])("+"|".join(map(re.escape,names))+r")(?![\w.'?!])")
    closure=expr.sub(lambda m:renames[m.group()],closure)
    helper="""lemma R28BnIncrement (n k:USize) (h:k<n):(k+1).toNat=k.toNat+1:=by
 have:=USize.lt_iff_toNat_lt.mp h
 have:=USize.toNat_lt_size n
 rw[Zc _ _ (by simp;omega)]
 simp
"""
    base=base[:begin]+helper+closure+"\n"+base[end:]
    base=once(base,"elem:=⟨YbkF,Ybl,Ybf,Ybe⟩","elem:=⟨YbkF,Ybl,Ybf,R28rBnInplace⟩")
    base=once(base,"ZdSF,ZdC,ZdB,  ZdT]","ZdSF,ZdC,R28rBnCorrect,  ZdT]")
    assert not any(x in closure for x in ["YsxAct","clipPoint","G1 "," E0 ","QK","X1]","δ","م","ل","ه","ٽ","ق","ك","چ","ڇ"])
    result=base.encode()
    return result,{"base_sha256":sha(raw11),"donor_sha256":sha(raw53),"deleted_bytes":len(removed.encode()),
                   "new_closure_bytes":len((helper+closure).encode()),"removed_declarations":["Ysj","YsjL","Ysk","YskE","Ybe","ZdB"],
                   "runtime":"In-place USize array traversal with per-channel Yl/Yd caching; exact source11 Ysx/YaY arithmetic unchanged; source11 YbeO fallback for size mismatch/large domain",
                   "proof":"Donor53 generic map/channel extensional correctness over source11 YsxE/ZcR/ZdBO; new USize increment helper; actual all12 correct rebound; NOT_COMPILED",
                   "publication":"Own recipe/receipt only; whole upstream/reconstructed source private/ephemeral"}
def transform(raw,submission=11,variant="resnet11-inplace-bn",donor_raw=None):
    assert submission==11 and variant=="resnet11-inplace-bn"
    if donor_raw is None:
        import os
        root=os.environ.get("TORCHLEAN_ROOT")
        path=Path(root)/"r28-source-private/official-53.lean" if root else HERE.parents[1]/"competition-state/source-private/official-53.lean"
        donor_raw=path.read_bytes()
    return build(raw,donor_raw)[0]
if __name__=="__main__":
    p=argparse.ArgumentParser();p.add_argument("--source",type=Path,required=True);p.add_argument("--donor",type=Path,required=True);p.add_argument("--output",type=Path);p.add_argument("--receipt",type=Path,required=True)
    a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    out={"at_utc":datetime.now(timezone.utc).isoformat(),"candidate_sha256":sha(result),"candidate_bytes":len(result),"free_bytes":256000-len(result),"recipe_sha256":sha(Path(__file__).read_bytes()),**meta,
         "state":"ACTUAL_ALL12_DECLARED_NOT_COMPILED" if len(result)<=256000 else "OVER_SIZE_NOT_CI_READY", "gate":"UNKNOWN","native_speed":"UNKNOWN"}
    a.receipt.write_text(json.dumps(out,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
    print(json.dumps({k:out[k] for k in ["candidate_sha256","candidate_bytes","free_bytes","deleted_bytes","new_closure_bytes","state"]}))
