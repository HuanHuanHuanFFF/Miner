"""Original native-only local-pixel pointwise kernel retaining public53 fallbacks."""
from pathlib import Path
import importlib.util,hashlib,json,datetime,argparse,re
HERE=Path(__file__).resolve().parent
BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
BASE_SHA='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb'
COMP=HERE.parent/'source-budget/compact53.py'
PREV=HERE/'build_channel128.py'
PREV_SHA='c483b6245cbfd3b19269e48a5404e79bf49ece33e59c4b4acece4d62d2aac27f'
COMP_SHA='cce4552bb4d9a52ae316a8c06a87675c7db049647064bcb0a74a91a22a75a480'
HELPER='''@[inline] def r28PMerge (a b:UInt32):UInt32:=
 ((min (a>>>16) (b>>>16))<<<16)+max (a&&&0xFFFF) (b&&&0xFFFF)
def r28PixScan (x:Array UInt32) (hw p n i:Nat) (v:UInt32):UInt32:=
 if h:i<n then
  let w:=x[i*hw+p]!&&&0x7fffffff
  r28PixScan x hw p n (i+1) (r28PMerge v ((((w-1)>>>23)<<<16)+(w>>>23)))
 else v
termination_by n-i
@[inline] def r28PixP (x:Array UInt32) (ms:Array UInt64) (hw k:Nat):Array Nat:=
 YO 1 k.toUSize (fun p _ t=>YV x[t.toNat*hw+p.toNat]! ms[p.toNat]!)
  (hw*k).toUSize 0 0 0 (Array.mkEmpty (hw*k))
lemma r28PixSize (x:Array UInt32) (ms:Array UInt64) (hw k:Nat) (hp:0<hw) (hk:0<k)
 (hn:hw*k<4294967296):(r28PixP x ms hw k).size=hw*k:=by
 have hk32:k<4294967296:=lt_of_le_of_lt (Nat.le_mul_of_pos_left _ hp) hn
 unfold r28PixP
 rw[E1 _ _ _ (by decide) (by rw[Za _ hk32];exact hk) _ _ hn]
 simp
lemma r28Ix (a b c:Nat) (hc:0<c) (ha:a<b) (hn:b*c<4294967296)
 (t:USize) (ht:t<c.toUSize):((a*c).toUSize+t).toNat<b*c:=by
 have hb:0<b:=by omega
 have hc32:c<4294967296:=lt_of_le_of_lt (Nat.le_mul_of_pos_left _ hb) hn
 have hac:a*c<4294967296:=lt_trans (Nat.mul_lt_mul_of_pos_right ha hc) hn
 have htN:t.toNat<c:=by have hh:=USize.lt_iff_toNat_lt.mp ht;simpa only[Za _ hc32] using hh
 apply A9
 constructor
 · rw[Za _ hac]
   nlinarith
 · exact hn
@[specialize] def r28PC128 (n:USize) (f u v:(t:USize)→t<n→UInt64)
 (B C:UInt64) (bw cw:UInt32) (cb db:qCtx0) (z0 z1:UInt64→UInt32)
 (h0 l0 h1 l1:UInt64) (k:USize):UInt64:=
 if ht:k<n then
  let x:=f k ht-0x200000000000000
  let p:=x*(u k ht-0x80000000)
  let q:=x*(v k ht-0x80000000)
  let m:=l0+p
  let z:=l1+q
  r28PC128 n f u v B C bw cw cb db z0 z1
   (h0+(0-(p>>>63))+(if m<l0 then 1 else 0)) m
   (h1+(0-(q>>>63))+(if z<l1 then 1 else 0)) z (k+1)
 else (z0 (qCtx2 B bw cb h0 l0)).toUInt64 ||| ((z1 (qCtx2 C cw db h1 l1)).toUInt64<<<32)
termination_by n.toNat-k.toNat
decreasing_by exact ZI n k ht
def r28PW (s:ConvShape) (relu:Bool) (x w b:Array UInt32):Array UInt32:=
 if hs:s.kh=1 ∧ s.kw=1 ∧ s.stride=1 ∧ s.pad=0 ∧ 0<s.h ∧ 0<s.w ∧ 0<s.cin ∧ 0<s.cout ∧
  x.size=(s.h*s.w)*s.cin ∧ w.size=s.cout*s.cin ∧ s.cout<=b.size ∧
  (s.h*s.w)*s.cin<4294967296 ∧ s.cout*s.cin<4294967296 ∧ s.cout*(s.h*s.w)<4294967296 ∧
  s.cin<256 ∧ w.any (fun a=>a&&&0x7fffffff==0)=false then
  let hw:=s.h*s.w
  let k:=s.cin
  let C:=s.cout
  have hh:0<hw:=by dsimp[hw];exact Nat.mul_pos (by omega) (by omega)
  have hk:0<k:=by dsimp[k];omega
  have hN:hw*k<4294967296:=by dsimp[hw,k];omega
  have hNW:C*k<4294967296:=by dsimp[C,k];omega
  have hk32:k<4294967296:=lt_of_le_of_lt (Nat.le_mul_of_pos_left _ hh) hN
  let BX:=Array.ofFn (n:=hw) (fun p=>r28PixScan x hw p.val k 0 0x01FF0000)
  let bp:=BX.foldl r28PMerge 0x01FF0000
  let BW:=Array.ofFn (n:=C) (fun o=>Yc w k o.val)
  let xm:=Ybh bp BW b
  if hg:(Array.range C).all (fun o=>Ybg BW[o]! b[o]! bp k xm false) then
   let cap:UInt64:=(Array.range C).foldl (fun m o=>
    if Yf b[o]! == 0 then m else min m ((Yd oneW+Yd b[o]!)-Yk (BW[o]!>>>16))) 510
   let MS:=BX.map (fun v=>min (Yk (v>>>16)) cap)
   let mlo:=MS.foldl min 510
   let mhi:=MS.foldl max 0
   let width:Nat:=(mhi-mlo+1).toNat
   if hc:mlo<=mhi ∧ mhi<=510 ∧ C*width<1048576 then
    let P:=r28PixP x MS hw k
    have hP:P.size=hw*k:=r28PixSize x MS hw k hh hk hN
    let W:=YW2 w BW b xm k
    have hW:W.size=C*k:=by
     rw[B7 w BW b xm k (by dsimp[C,k] at hNW;omega) hk32]
     simp only[Array.size_ofFn]
     dsimp[C,k];omega
    let BC:=Array.ofFn (n:=C*width) (fun z=>
     let o:=z.val/width
     let mm:=mlo+(z.val%width).toUInt64
     qCtx1 (mm+Yk (BW[o]!>>>16)) b[o]!)
    YOC C.toUSize s.h.toUSize s.w.toUSize (fun o y z=>
     if ho:o.toNat<C ∧ y.toNat<s.h ∧ z.toNat<s.w then
      let p:=y.toNat*s.w+z.toNat
      have hp:p<hw:=by dsimp[p,hw];nlinarith[ho.2.1,ho.2.2]
      let f: (t:USize)→t<k.toUSize→UInt64:=fun t ht=>
       (P.uget ((p*k).toUSize+t) (by rw[hP];exact r28Ix p hw k hk hp hN t ht)).toUInt64
      let u: (t:USize)→t<k.toUSize→UInt64:=fun t ht=>
       (W.uget ((o.toNat*k).toUSize+t) (by rw[hW];exact r28Ix o.toNat C k hk ho.1 hNW t ht)).toUInt64
      let mm:=MS[p]!
      let B:=mm+Yk (BW[o.toNat]!>>>16)
      let cb:=BC[o.toNat*width+(mm-mlo).toNat]!
      let done0:=fun a:UInt64=>if a<0x100000000 then a.toUInt32 else Ybz s x w b k o y z false
      if ho2:o.toNat+1<C then
       let v: (t:USize)→t<k.toUSize→UInt64:=fun t ht=>
        (W.uget (((o.toNat+1)*k).toUSize+t) (by rw[hW];exact r28Ix (o.toNat+1) C k hk ho2 hNW t ht)).toUInt64
       let D:=mm+Yk (BW[o.toNat+1]!>>>16)
       let db:=BC[(o.toNat+1)*width+(mm-mlo).toNat]!
       let done1:=fun a:UInt64=>if a<0x100000000 then a.toUInt32 else Ybz s x w b k (o+1) y z false
       let empty:=BX[p]!>>>16==511
       let fast:=(empty || Yk (BX[p]!&&&0xFFFF)-mm+YU BW[o.toNat]!<=15) &&
        (empty || Yk (BX[p]!&&&0xFFFF)-mm+YU BW[o.toNat+1]!<=15)
       let ans:=if fast then r28PC128 k.toUSize f u v B D b[o.toNat]! b[o.toNat+1]! cb db done0 done1 0 0 0 0 0
        else qCtx7 k.toUSize f u v B D b[o.toNat]! b[o.toNat+1]! cb db done0 done1 0 0 0 0 0
       (act relu ans.toUInt32).toUInt64 ||| ((act relu (ans>>>32).toUInt32).toUInt64<<<32)
      else (act relu (done0 (Y5 k.toUSize f u B b[o.toNat]! 0 0 0))).toUInt64
     else 0) (((C+1)/2)*hw).toUSize 0 0 0 (Array.mkEmpty (C*hw)) (Array.mkEmpty hw)
   else ao s relu x w b
  else ao s relu x w b
 else ao s relu x w b
'''

def transform(raw,submission,variant):
    assert submission==53 and variant=='pointwise128'
    assert hashlib.sha256(raw).hexdigest()==BASE_SHA
    assert hashlib.sha256(PREV.read_bytes()).hexdigest()==PREV_SHA
    assert hashlib.sha256(COMP.read_bytes()).hexdigest()==COMP_SHA
    spec=importlib.util.spec_from_file_location('r28remove',PREV);prev=importlib.util.module_from_spec(spec);spec.loader.exec_module(prev)
    s=raw.decode(); removed=['correct','rBnCorrect','bCp','aq','ar','ax','av','au','az','poolProvedZero','an','aj','al']
    for name in removed:s=prev.remove_decl(s,name)
    for name in removed:
      if len(name)>=4:assert not re.search(r'\b'+re.escape(name)+r'\b',s),name
    mark='def kernels:Kernels where';assert s.count(mark)==1;s=s.replace(mark,HELPER+mark)
    assert s.count('conv:=⟨ao,ap⟩')==1;s=s.replace('conv:=⟨ao,ap⟩','conv:=⟨r28PW,ap⟩')
    spec=importlib.util.spec_from_file_location('r28pcompact',COMP);comp=importlib.util.module_from_spec(spec);spec.loader.exec_module(comp)
    out,_=comp.build(s.encode(),strict_base=False);assert len(out)<=256000,len(out)
    return out

def main():
    p=argparse.ArgumentParser();p.add_argument('--base',type=Path,default=BASE);a=p.parse_args();data=transform(a.base.read_bytes(),53,'pointwise128')
    dest=HERE/'private/pointwise12853.lean';dest.write_bytes(data)
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'variant':'pointwise128','base_sha256':BASE_SHA,'candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'dependencies':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in [PREV,COMP]},'helper_bytes':len(HELPER.encode()),'proof_state':'UNPROVED_NATIVE_RESEARCH_ONLY; no correct for changed kernels; dependent acceptance proofs removed for bounded cost exploration','mechanism':'Pixel-local exact scales; input transpose once; common bias cap hoisted; cache bias contexts across actual min-to-max scale interval; paired signed64 products+signed128 carry under fixed <=15, original split2 on misses and original full ao on all excluded shapes/sparse/wide cases','native_cost':'UNKNOWN'}
    (HERE/'pointwise128-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n');print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
