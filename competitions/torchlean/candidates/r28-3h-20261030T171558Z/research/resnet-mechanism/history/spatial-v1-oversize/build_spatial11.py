#!/usr/bin/env python3
"""Original restricted spatial F(2x2,3x3) complete-model native-only recipe.

Source11's entire old runtime/proof remains available as the fallback. New kernels
intentionally have no Submission.correct. Compile/native/full-proof are separate.
"""
from pathlib import Path
import hashlib,importlib.util,json,re
P=Path(__file__).resolve().parent
BASE_SHA='ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3'

def bform(a,b,c,d):return [f'{a}-{c}',f'{b}+{c}',f'{c}-{b}',f'{b}-{d}']
def gform(a,b,c):return [f'{a}+{a}',f'{a}+{b}+{c}',f'{a}-{b}+{c}',f'{c}+{c}']

def runtime():
 s='''@[inline] def R8J (a b:UInt64):UInt64×UInt64 :=
 let l:=b<<<25
 let lo:=l+a
 ((b>>>39)+(((0:UInt64)-(b>>>63))<<<25)+((0:UInt64)-(a>>>63))+(if lo<l then 1 else 0),lo)
@[inline] def R8A (a b:UInt64×UInt64):UInt64×UInt64 :=
 let l:=a.2+b.2
 (a.1+b.1+(if l<a.2 then 1 else 0),l)
@[inline] def R8S (a b:UInt64×UInt64):UInt64×UInt64 :=
 (a.1-b.1-(if a.2<b.2 then 1 else 0),a.2-b.2)
structure R8Ctx where
 hi:UInt64
 lo:UInt64
 e:UInt64
 neg:Bool
 deriving Inhabited
@[inline] def R8B (e:UInt64) (bw:UInt32):R8Ctx :=
 let sh:=Yd bw+126-e
 let m:=Yf bw<<<23
 ⟨if sh<64 then (m>>>1)>>>(63-sh) else m<<<(sh-64),if sh<64 then m<<<sh else 0,e,signOf bw⟩
@[inline] def R8F (s:ConvShape) (relu:Bool) (inp wts b:Array Word) (o y x:Nat) (cb:R8Ctx) (v:UInt64×UInt64):Word :=
 let a:=if cb.neg then v.2-cb.lo else v.2+cb.lo
 let h:=if cb.neg then v.1-cb.hi-(if v.2<cb.lo then 1 else 0) else v.1+cb.hi+(if v.2+cb.lo<v.2 then 1 else 0)
 let z:=(0:UInt64)-(h>>>63)
 act relu (if (a|||h|||z)==0 then
  if zW s inp wts b (s.cin*9) o 0 y x 0 (s.cin*9+1) then 0x80000000 else 0
  else YaTT z h a (fun _=>(cb.e.toNat:Int)-298) false true (cb.e-298))
def R8W (W:Array UInt32) (ci co:Nat):Array Nat := Id.run do
 let mut v:=Array.mkEmpty (co*ci*16)
 for o in [:co] do
  for c in [:ci] do
   let z:=o*(ci*9)+c*9
'''
 for r in range(3):
  for c in range(3):s+=f'   let a{r}{c}:=(W[z+{r*3+c}]!).toUInt64-0x80000000\n'
  for j,expr in enumerate(gform(*[f'a{r}{c}' for c in range(3)])):s+=f'   let r{r}{j}:={expr}\n'
 for j in range(4):
  for expr in gform(*[f'r{r}{j}' for r in range(3)]):s+=f'   v:=v.push (({expr}+0x800000000).toNat)\n'
 s+=''' return v
def R8I (s:ConvShape) (P:Array Nat) (y x:Nat):Array Nat := Id.run do
 let mut v:=Array.mkEmpty (s.cin*16)
 for c in [:s.cin] do
  let z:=(c*(s.h+2)+y)*(s.w+2)+x
'''
 for r in range(4):
  for c in range(4):s+=f'  let a{r}{c}:=(P[z+{r}*(s.w+2)+{c}]!).toUInt64-0x200000000000000\n'
  for j,expr in enumerate(bform(*[f'a{r}{c}' for c in range(4)])):s+=f'  let r{r}{j}:={expr}\n'
 for j in range(4):
  for expr in bform(*[f'r{r}{j}' for r in range(4)]):s+=f'  v:=v.push (({expr}+0x400000000000000).toNat)\n'
 s+=''' return v
def R8D (V U:Array Nat) (ci o:Nat) (fuel q c:Nat) (a0 a1:UInt64) (L H:Array Nat):Array Nat×Array Nat :=
 match fuel with
 | 0 => (L,H)
 | n+1 =>
  if c<ci then
   let x:=(V[c*16+q]!).toUInt64
   let w:=(U[(o*ci+c)*16+q]!).toUInt64-0x800000000
   R8D V U ci o n q (c+1) (a0+(x&&&0x1ffffff)*w) (a1+((x>>>25)-0x200000000)*w) L H
  else R8D V U ci o n (q+1) 0 0 0 (L.push ((a0+0x4000000000000000).toNat)) (H.push ((a1+0x4000000000000000).toNat))
@[inline] def R8O (s:ConvShape) (relu:Bool) (inp wts b:Array Word) (cb:R8Ctx)
 (o y x:Nat) (L H:Array Nat) (out:Array Word):Array Word :=
'''
 for i in range(16):s+=f' let m{i}:=R8J ((L[{i}]!).toUInt64-0x4000000000000000) ((H[{i}]!).toUInt64-0x4000000000000000)\n'
 for r in range(4):
  s+=f' let t{r}0:=R8A (R8A m{r} m{4+r}) m{8+r}\n'
  s+=f' let t{r}1:=R8S (R8S m{4+r} m{8+r}) m{12+r}\n'
 s+=''' let a:=R8A (R8A t00 t10) t20
 let b0:=R8A (R8A t01 t11) t21
 let c:=R8S (R8S t10 t20) t30
 let d:=R8S (R8S t11 t21) t31
 let j:=o*(s.h*s.w)+y*s.w+x
 let out:=out.set! j (R8F s relu inp wts b o y x cb a)
 let out:=out.set! (j+1) (R8F s relu inp wts b o y (x+1) cb b0)
 let out:=out.set! (j+s.w) (R8F s relu inp wts b o (y+1) x cb c)
 out.set! (j+s.w+1) (R8F s relu inp wts b o (y+1) (x+1) cb d)
def R8Run (s:ConvShape) (relu:Bool) (inp wts b:Array Word) (P:Array Nat) (W BW:Array UInt32) (xm:UInt64):Array Word := Id.run do
 let U:=R8W W s.cin s.cout
 let ctx:=Array.ofFn (n:=s.cout) (fun o=>R8B (xm+YG BW[o.val]! b[o.val]! xm-2) b[o.val]!)
 let mut out:=Array.replicate (s.cout*s.h*s.w) 0
 for y in [:s.h/2] do
  for x in [:s.w/2] do
   let V:=R8I s P (2*y) (2*x)
   for o in [:s.cout] do
    let z:=R8D V U s.cin o (16*(s.cin+1)) 0 0 0 0 (Array.mkEmpty 16) (Array.mkEmpty 16)
    out:=R8O s relu inp wts b ctx[o]! o (2*y) (2*x) z.1 z.2 out
 return out
def R8Conv (s:ConvShape) (relu:Bool) (inp wts b:Array Word):Array Word :=
 if s.kh==3&&s.kw==3&&s.stride==1&&s.pad==1&&0<s.cin&&s.cin<=8&&0<s.h&&0<s.w&&
   s.h%2==0&&s.w%2==0&&s.cout>=4&&wts.all (fun w=>Yf w!=0) then
  let k:=s.cin*9
  let bp:=Yc inp inp.size 0
  let BW:=Array.ofFn (n:=s.cout) (fun o=>Yc wts k o.val)
  let xm:=Ybh bp BW b
  if s.cout*k<=wts.size&&s.cin*((s.h+2)*(s.w+2))+(s.h+2)*(s.w+2)+inp.size+wts.size+
     s.cout*(s.ho*s.wo)+s.ho*s.wo+s.stride<=4294967295&&
     (Array.range s.cout).all (fun o=>
      let e:=xm+YG BW[o]! b[o]! xm
      Ybg BW[o]! b[o]! bp k xm&&2<=e&&e<=1000&&(Yf b[o]! ==0||Yd b[o]!+126-e<=76)) then
   R8Run s relu inp wts b (Ybi s inp xm) (YW2 wts BW b xm k) BW xm
  else Ybp s relu inp wts b
 else Ybp s relu inp wts b
'''
 constants={'0x4000000000000000':'R8C','0x400000000000000':'R8X','0x200000000000000':'R8Z','0x800000000':'R8Q'}
 for literal,name in constants.items():s=s.replace(literal,name)
 s=s.replace(' (','(').replace(') ',')').replace('=> ','=>')
 return ''.join(f'@[inline] def {name}:UInt64:={literal}\n' for literal,name in constants.items())+s

def transform(raw,submission=11,variant='spatial11-native'):
 assert submission==11 and variant=='spatial11-native'
 assert hashlib.sha256(raw).hexdigest()==BASE_SHA
 s=raw.decode();start=s.index('def kernels:Kernels where');tail=s[start:]
 record=tail[:tail.index('theorem correct:')]
 assert 'conv:=⟨Ybp,dwQ⟩' in record
 record=record.replace('conv:=⟨Ybp,dwQ⟩','conv:=⟨R8Conv,dwQ⟩')
 prior=re.sub(r'\bkernels\b','R8baseKernels',tail)
 prior=re.sub(r'\bcorrect\b','R8baseCorrect',prior)
 s=s[:start]+prior[:prior.rfind('end Submission')]+'\n'+runtime()+'\n'+record+'end Submission\n'
 for name in ['R8C','R8X','R8Z','R8Q','R8J','R8A','R8S','R8Ctx','R8B','R8F','R8W','R8I','R8D','R8O','R8Run','R8Conv']:
  assert not re.search(r'\b'+name+r'\b',raw.decode())
 spec=importlib.util.spec_from_file_location('compact11',P/'compact11.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
 result=m.compact(s.encode(),strict_base=False)
 assert len(result)<=256000,len(result)
 assert b'theorem correct:' not in result
 return result

def main():
 raw=(P.parents[1]/'competition-state/source-private/official-11.lean').read_bytes()
 result=transform(raw)
 (P/'private').mkdir(exist_ok=True)
 (P/'private/spatial11-native-only.lean').write_bytes(result)
 (P/'SpatialRuntime.lean.inc').write_text(runtime(),encoding='utf-8')
 r={'variant':'spatial11-native','source_sha256':hashlib.sha256(result).hexdigest(),'bytes':len(result),'base_sha256':BASE_SHA,'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'runtime_sha256':hashlib.sha256(runtime().encode()).hexdigest(),'compactor_sha256':hashlib.sha256((P/'compact11.py').read_bytes()).hexdigest(),'proof_state':'NOT_PROVED_NATIVE_ONLY_NO_SUBMISSION_CORRECT','declares_correct':False,'full_gate':False,'native_state':'UNKNOWN','scope':'Complete original kernels portfolio retained under base names; only new conv entry has restricted tile fast path. Every failed guard calls original Ybp. Other11kernel entries unchanged.','guards':'Original narrow/finite/size,3x3 stride1 pad1,1<=cin<=8,positive even h/w,cout>=4,real weights nonzero,B0>=2,B0<=1000,nonzero old bias shift<=76','layout':'One transformed weight cache, one16cin input cache per2x2tile, CHW out.set!, scalar128 inverse, B0-2 bias context. No ArrayUInt64 input/weight cache. Biased Nat partial caches may use bigNat at extreme valid spans; exact modulo64 decoding retained.','risk':'Source UNCOMPILED; new constructor/tuple lowering, Nat loops, partial/cache allocation and full fallback overhead need complete native cost. All12/size after full proof remains UNKNOWN.'}
 (P/'spatial11-native-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');print(json.dumps(r,indent=2))
if __name__=='__main__':main()
