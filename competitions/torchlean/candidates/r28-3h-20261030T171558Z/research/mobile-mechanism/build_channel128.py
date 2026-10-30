"""Original native-cost experiment: local-channel exponents + signed128 accumulation.

This deliberately has NO Submission.correct for the changed kernels. It is only
a complete-path cost discriminator, never a competition/adoption artifact.
"""
from pathlib import Path
import hashlib,json,datetime,argparse,importlib.util,re
HERE=Path(__file__).resolve().parent
BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
BASE_SHA='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb'
COMP=HERE.parent/'source-budget/compact53.py'

LOOP='''@[specialize] def r28D128 (n:م) (f g w:(t:م)→t<n→ق) (B:ق) (bw:ك) (cb:qCtx0)
 (z0 z1:ق→ك) (h0 l0 h1 l1:ق) (k:م):ق:=
 if ht:k<n then
  let wt:=w k ht-0x80000000
  let p:=(f k ht-0x200000000000000)*wt
  let q:=(g k ht-0x200000000000000)*wt
  let m:=l0+p
  let v:=l1+q
  r28D128 n f g w B bw cb z0 z1
   (h0+(0-(p>>>63))+(if m<l0 then 1 else 0)) m
   (h1+(0-(q>>>63))+(if v<l1 then 1 else 0)) v (k+1)
 else (z0 (qCtx2 B bw cb h0 l0)).toUInt64 ||| ((z1 (qCtx2 B bw cb h1 l1)).toUInt64<<<32)
termination_by n.toNat-k.toNat
decreasing_by exact ZI n k ht
'''

SPLIT='''def r28DwSplit (s:ConvShape) (r:Bool) (x w b:Array UInt32):Array UInt32:=
 if s.cin>1 ∧ x.size=s.cin*(s.h*s.w) ∧ w.size=s.cin*(s.kh*s.kw) ∧ b.size=s.cin ∧
   x.size+w.size+b.size+s.cin*(s.ho*s.wo)<4294967296 ∧
   w.any (fun v=>v&&&0x7fffffff==0)=false then Id.run do
  let sh:ConvShape:=⟨1,s.h,s.w,1,s.kh,s.kw,s.stride,s.pad⟩
  let mut out:Array UInt32:=Array.mkEmpty (s.cin*(s.ho*s.wo))
  for ch in [0:s.cin] do
   let xx:=Array.ofFn (n:=s.h*s.w) (fun t=>x[ch*(s.h*s.w)+t.val]!)
   let ww:=Array.ofFn (n:=s.kh*s.kw) (fun t=>w[ch*(s.kh*s.kw)+t.val]!)
   let yy:=ap sh r xx ww #[b[ch]!]
   for v in yy do out:=out.push v
  return out
 else ap s r x w b
'''

def remove_decl(s,name):
    pat=re.compile(r'(?m)^(?:@\[[^\n]+\]\s+)?(?:lemma|theorem) '+re.escape(name)+r'\b')
    matches=list(pat.finditer(s));assert len(matches)==1,(name,len(matches))
    a=matches[0].start();nxt=re.search(r'(?m)^(?:@\[[^\n]+\]\s+)?(?:def|lemma|theorem|set_option|structure|local|end)\b',s[matches[0].end():])
    assert nxt; b=matches[0].end()+nxt.start()
    return s[:a]+s[b:]

def transform(raw,submission,variant):
    assert submission==53 and hashlib.sha256(raw).hexdigest()==BASE_SHA
    assert variant in ['split-channel128','split-control','global128']
    s=raw.decode(); removed=['correct']
    if variant!='split-control':
      marker='@[inline] def YbjPPacked ';s=s.replace(marker,LOOP+marker)
      a=s.index(marker);b=s.index('@[inline] def ak ',a);part=s[a:b]
      key='(w:ه)\n';assert part.count(key)==1;part=part.replace(key,'(w:ه) (r28fast:Bool)\n')
      call=part.index(' else\n  qCtx13 k.toUSize')
      tail=part[call+len(' else\n'):]
      part=part[:call]+' else if r28fast then\n'+tail.replace('qCtx13','r28D128',1)+' else\n'+tail
      s=s[:a]+part+s[b:]
      a=s.index('@[inline] def ak ');b=s.index('lemma packShiftLow ',a);part=s[a:b]
      key='(BCs.uget o (by simp only[BCs,Array.size_ofFn];exact Z4 h.1 (by omega))) (!g) א'
      assert part.count(key)==1
      part=part.replace(key,'(BCs.uget o (by simp only[BCs,Array.size_ofFn];exact Z4 h.1 (by omega))) (!g)\n      (decide (Yk (bp&&&0xFFFF)-xm+YU BW[o.toNat]!<=15)) א')
      s=s[:a]+part+s[b:]
      removed+=['YbjPPackedEq','al','ar']
    for name in removed:s=remove_decl(s,name)
    if variant!='global128':
      marker='def kernels:Kernels where';assert s.count(marker)==1
      s=s.replace(marker,SPLIT+marker)
      assert s.count('conv:=⟨ao,ap⟩')==1;s=s.replace('conv:=⟨ao,ap⟩','conv:=⟨ao,r28DwSplit⟩')
    spec=importlib.util.spec_from_file_location('r28c128compact',COMP);mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    result,_=mod.build(s.encode(),strict_base=False)
    assert len(result)<=256000,len(result)
    assert not re.search(rb'(?:theorem|lemma) correct\b',result)
    return result

def main():
    p=argparse.ArgumentParser();p.add_argument('--base',type=Path,default=BASE);a=p.parse_args();raw=a.base.read_bytes();rows=[]
    for variant in ['split-channel128','split-control','global128']:
      data=transform(raw,53,variant);dest=HERE/'private'/(variant+'53.lean');dest.parent.mkdir(exist_ok=True);dest.write_bytes(data)
      rows.append({'variant':variant,'sha256':hashlib.sha256(data).hexdigest(),'bytes':len(data),'path':str(dest)})
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'base_sha256':BASE_SHA,'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'compactor_sha256':hashlib.sha256(COMP.read_bytes()).hexdigest(),'variants':rows,'proof_state':'UNPROVED_NATIVE_RESEARCH_ONLY; changed kernels have no correct theorem; selected dependent correctness proofs removed only for explicit cost discriminator','cost_state':'UNKNOWN','guard':'Exact original narrow guards plus Yk(bp.high)-xm+YU(BW[row])<=15; local channel split only full-sized, bounded arrays, cin>1 and no zero weights. All sparse/invalid/wide scalar paths retained. Same cached bias finalizer and exact-zero fallback.','proof_obligations':['Signed64 per-product exactness under actual <=15 producer bounds','Signed128 modular carry accumulation and final dot mapping','All-input per-channel depthwise split equivalence','Fresh complete original all12 gate after proofs are restored']}
    (HERE/'channel128-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n');print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
