"""Original flat-buffer channel-local exponent preparation for public53.

Native-only complete-model cost discriminator. No changed-kernel correct theorem.
"""
from pathlib import Path
import importlib.util,hashlib,json,datetime,argparse
HERE=Path(__file__).resolve().parent
BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
BASE_SHA='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb'
PREVIOUS=HERE/'build_channel128.py'
COMP=HERE.parent/'source-budget/compact53.py'
PREVIOUS_SHA='c483b6245cbfd3b19269e48a5404e79bf49ece33e59c4b4acece4d62d2aac27f'
COMP_SHA='cce4552bb4d9a52ae316a8c06a87675c7db049647064bcb0a74a91a22a75a480'

HELPER='''@[inline] def r28Merge (a b:ك):ك:=
 ((min (a>>>16) (b>>>16))<<<16)+max (a&&&0xFFFF) (b&&&0xFFFF)
@[inline] def r28YP (s:σ) (a:ل δ) (ms:ل ق):ل ٽ:=
 YO (Yb s).toUSize (Ya s).toUSize
  (fun c y x=>YV (YbsU s.pad.toUSize s.h.toUSize s.w.toUSize a c y x) ms[c.toNat]!)
  (s.cin*(Yb s*Ya s)).toUSize 0 0 0 (Array.mkEmpty (s.cin*(Yb s*Ya s)))
lemma r28YPsize (s:σ) (a:ل δ) (ms:ل ق) (d:0<Yb s*Ya s)
 (e:s.cin*(Yb s*Ya s)<4294967296) (f:Yb s*Ya s<4294967296):
 (r28YP s a ms).size=s.cin*(Yb s*Ya s):=by
 have j:0<Yb s:=Nat.pos_of_mul_pos_right d
 have k:0<Ya s:=Nat.pos_of_mul_pos_left d
 have hj:Yb s<4294967296:=lt_of_le_of_lt (Nat.le_mul_of_pos_right _ k) f
 have hk:Ya s<4294967296:=lt_of_le_of_lt (Nat.le_mul_of_pos_left _ j) f
 unfold r28YP
 rw[E1 _ _ _ (by rw[Za _ hj];exact j) (by rw[Za _ hk];exact k) _ _ e]
 simp
'''

def transform(raw,submission,variant):
    assert submission==53 and variant in ['local-channel128','local-channel-control']
    assert hashlib.sha256(raw).hexdigest()==BASE_SHA
    assert hashlib.sha256(PREVIOUS.read_bytes()).hexdigest()==PREVIOUS_SHA
    assert hashlib.sha256(COMP.read_bytes()).hexdigest()==COMP_SHA
    spec=importlib.util.spec_from_file_location('r28prev',PREVIOUS);prev=importlib.util.module_from_spec(spec);spec.loader.exec_module(prev)
    s=prev.transform(raw,53,'global128').decode()
    marker='@[inline] def ak ';s=s.replace(marker,HELPER+marker)
    a=s.index(marker);b=s.index('lemma ',a);part=s[a:b]
    bp=' let bp:=Yc aC aCچ 0\n';assert part.count(bp)==1
    part=part.replace(bp,''' let r28use:=dw && decide (aC.size=s.cin*(s.h*s.w) ∧ aC.size<=4294967295)
 let r28Bs:ل ك:=if r28use then Array.ofFn (n:=C) (fun c=>Yc aC (s.h*s.w) c.val) else #[]
 let bp:=if r28use then r28Bs.foldl r28Merge 0x01FF0000 else Yc aC aCچ 0
''')
    old='  let P2:=if g then Ybi s aC xm YV else Ybi s aC xm YVa\n';assert part.count(old)==1
    part=part.replace(old,'''  let r28local:=r28use && g
  let r28Ms:ل ق:=Array.ofFn (n:=C) (fun o=>
   if r28local then
    let bm:=r28Bs[o.val]!
    let mm:=Ybh bm #[BW[o.val]!] #[b[o.val]!]
    if Ybg BW[o.val]! b[o.val]! bm k mm false then mm else xm
   else xm)
  let P2:=if g then (if r28local then r28YP s aC r28Ms else Ybi s aC xm YV) else Ybi s aC xm YVa
''')
    old='''  have hP2:P2چ=s.cin*(Yb s*Ya s):=by
   simp only[P2];split<;>rw[B3 s aC xm _ hg.2.2.1 א א,Array.size_ofFn]
''';assert part.count(old)==1
    part=part.replace(old,'''  have hP2:P2چ=s.cin*(Yb s*Ya s):=by
   simp only[P2]
   split
   · split
     · exact r28YPsize s aC r28Ms hg.2.2.1 א א
     · rw[B3 s aC xm _ hg.2.2.1 א א,Array.size_ofFn]
   · rw[B3 s aC xm _ hg.2.2.1 א א,Array.size_ofFn]
''')
    old='let B0s:ل ق:=ډ C λ o=>xm+YG BW[o.val]! b[o.val]! xm';assert part.count(old)==1
    part=part.replace(old,'let B0s:ل ق:=ډ C λ o=>r28Ms[o.val]!+YG BW[o.val]! b[o.val]! r28Ms[o.val]!')
    old='(decide (Yk (bp&&&0xFFFF)-xm+YU BW[o.toNat]!<=15))';assert part.count(old)==1
    if variant=='local-channel128':
      part=part.replace(old,'(decide (Yk ((if r28local then r28Bs[o.toNat]! else bp)&&&0xFFFF)-r28Ms[o.toNat]!+YU BW[o.toNat]!<=15))')
    else:part=part.replace(old,'false')
    s=s[:a]+part+s[b:]
    spec=importlib.util.spec_from_file_location('r28localcompact',COMP);comp=importlib.util.module_from_spec(spec);spec.loader.exec_module(comp)
    out,_=comp.build(s.encode(),strict_base=False);assert len(out)<=256000,len(out)
    assert b'theorem correct:' not in out
    return out

def main():
    p=argparse.ArgumentParser();p.add_argument('--base',type=Path,default=BASE);a=p.parse_args();raw=a.base.read_bytes();rows=[]
    for variant in ['local-channel128','local-channel-control']:
      data=transform(raw,53,variant);dest=HERE/'private'/(variant+'53.lean');dest.write_bytes(data)
      rows.append({'variant':variant,'sha256':hashlib.sha256(data).hexdigest(),'bytes':len(data),'path':str(dest)})
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'base_sha256':BASE_SHA,'variants':rows,'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'dependencies':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in [PREVIOUS,COMP]},'proof_state':'UNPROVED_NATIVE_RESEARCH_ONLY; no changed correct root; original whole gate remains required after proof closure','improvement_over_split_probe':'Same flat padded buffer and output loop; no per-channel input slicing or output flatten/copy. One channel scan replaces global scan; per-channel bounds/scales/bias contexts prepared once.','guard':'Existing full array/shape/narrow guards plus exact <=15 product span; non-local/generic and all sparse paths retain original representation.','open':['r28YP size elaboration uncompiled','All-input merged-bounds and per-channel scale refinement','Signed64 product / signed128 carry / full dot proof','Native complete-path cost and checksum parity']}
    (HERE/'local-channel128-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n');print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
