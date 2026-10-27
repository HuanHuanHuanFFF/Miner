from pathlib import Path
import hashlib,json,re
from datetime import datetime,timezone
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').exists())
sha=lambda b:hashlib.sha256(b).hexdigest()
base=(R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
prior=(R/'competitions/floatlib/candidates/f01-r19-dev-column4-bbase1/Kernel.lean').read_bytes()
assert sha(prior)=='f49458b99475b1b7e4a368908c81590b7f357a06938f38d0df141ffa3df5dc5d'
txt=prior.decode();a=txt.index('namespace Submission.R19Temporal');b=txt.index('end Submission.R19Temporal',a)+len('end Submission.R19Temporal')
temporal=txt[a:b]+'\n'
assert 'R19DualTemporal' not in temporal and 'bmmBeforeTemporal' not in temporal
ss=' '.join('s'+str(j) for j in range(8));bs='B0 B1 B2 B3';zs=' '.join(['Packed10.zero32']*8)
o=['/- R20 diagnostic only. Raw A is decoded once per k across eight native scalar chains. NOT_RUN. -/','namespace Submission.R20RowBroadcast','open FloatLib.Floats Competition','structure F8 where']
o+=['  s'+str(j)+' : Float32' for j in range(8)]
o+=['','@[inline] def join (x0 x1 x2 x3 : R15ThinPairs.F2) : F8 :=','  ⟨'+', '.join(f'x{j//2}.s{j%2}' for j in range(8))+'⟩','',f'def loop (n baseA : Nat) (A : Array Binary32)',f'    ({bs} : Vector R19Temporal.B8 ((n+3)/4))',f'    (t : Nat) ({ss} : Float32) : F8 :=','  let k := 4*t','  if h3 : k+3<n then','    have ht : t<(n+3)/4 := by dsimp [k] at h3; omega']
def reads(ind):return [ind+f'let b{g} := B{g}.get ⟨t,ht⟩' for g in range(4)]
def step(d,ind):
 addr='baseA+k'+('+'+str(d) if d else '')
 return [ind+f'let a{d} := R19Temporal.read A ({addr})']+[ind+f'let s{j} := s{j}+a{d}*b{j//2}.k{d}c{j%2}' for j in range(8)]
ret='⟨'+', '.join('s'+str(j) for j in range(8))+'⟩'
o+=reads('    ')
for d in range(4):o+=step(d,'    ')
o+=[f'    loop n baseA A {bs} (t+1) {ss}','  else if h0 : k<n then','    have ht : t<(n+3)/4 := by dsimp [k] at h0; omega']+reads('    ')+step(0,'    ')
o+=['    if k+1<n then']+step(1,'      ')+['      if k+2<n then']+step(2,'        ')+['        '+ret,'      else '+ret,'    else '+ret,'  else '+ret,'termination_by n-4*t','decreasing_by all_goals omega','']
o+=['theorem loop_eq (n baseA : Nat) (A : Array Binary32)',f'    ({bs} : Vector R19Temporal.B8 ((n+3)/4))',f'    (t : Nat) ({ss} : Float32) :',f'    loop n baseA A {bs} t {ss} =','      join '+ ' '.join(f'(R19Temporal.loop n baseA A B{g} t s{2*g} s{2*g+1})' for g in range(4))+' := by']
o+=[f'  have eN := @loop.eq_def n baseA A {bs} t {ss}']+[f'  have e{g} := @R19Temporal.loop.eq_def n baseA A B{g} t s{2*g} s{2*g+1}' for g in range(4)]
eq='rw [eN, e0, e1, e2, e3]'
o+=['  by_cases h3 : 4*t+3<n','  · '+eq,'    simp only [h3, dite_true]',f'    exact loop_eq n baseA A {bs} (t+1) '+' '.join(['_']*8),'  · by_cases h0 : 4*t<n','    · by_cases h1 : 4*t+1<n','      · by_cases h2 : 4*t+2<n','        · '+eq,'          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true, join] <;> rfl','        · '+eq,'          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true, ite_false, join] <;> rfl','      · '+eq,'        simp only [h3, h0, h1, dite_false, dite_true, ite_false, join] <;> rfl','    · '+eq,'      simp only [h3, h0, dite_false, join] <;> rfl','termination_by n-4*t','decreasing_by all_goals omega','']
o+=['@[inline] def runDot (n baseA : Nat) (A : Array Binary32)',f'    ({bs} : Vector R19Temporal.B8 ((n+3)/4)) : F8 :=',f'  loop n baseA A {bs} 0 {zs}','',f'theorem runDot_eq (n baseA : Nat) (A : Array Binary32)',f'    ({bs} : Vector R19Temporal.B8 ((n+3)/4)) :',f'    runDot n baseA A {bs} =','      join '+ ' '.join(f'(R19Temporal.loop n baseA A B{g} 0 Packed10.zero32 Packed10.zero32)' for g in range(4))+' := by',f'  exact loop_eq n baseA A {bs} 0 {zs}','', '@[inline] def select (x : F8) (j : Nat) : Float32 :=','  '+''.join(f'if j={j} then x.s{j} else ' for j in range(7))+'x.s7','']
o+=['@[inline] def row8 (batch m n : Nat)', '    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*8))','    (PB : Vector (Vector R19Temporal.B8 ((n+3)/4)) (batch*R15ThinPairs.groups 8))','    (out : Array Binary32) (r : Fin (batch*m)) : Array Binary32 :=','  have hm : 0<m := Nat.pos_of_lt_mul_left r.isLt','  let bi : Fin batch := ⟨r.val/m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩','  let baseA := r.val*n','  let baseB := bi.val*n*8']
o += [f'  let B{g} := PB.get (R15PackedB2.tileIndex batch 8 bi ⟨{g},by decide⟩)' for g in range(4)]
o += [f'  let result := runDot n baseA A.toArray {bs}','  RowStream.emit 8 (fun j => Packed10.finish n baseA (baseB+j.val) 8','    A.toArray B.toArray (select result j.val)) out','','def diagnosticBmm8 (batch m n : Nat)','    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*8)) : Array Binary32 :=','  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then','    (UnderflowZero.zeros batch m 8).toArray','  else','    let PB := R19Temporal.packB batch n 8 B','    Fin.foldl (batch*m) (row8 batch m n A B PB) (Array.mkEmpty (batch*m*8))','','end Submission.R20RowBroadcast','']
fragment='\n'.join(o);(H/'RowBroadcast8.lean.inc').write_bytes(fragment.encode())
full=base+b'\n'+temporal.encode()+b'\n'+fragment.encode();assert len(full)<256000
path=H/'Probe-row-broadcast8.lean';path.write_bytes(full)
roots=['Submission.'+s+'_spec' for s in ('add','mul','sum','bmm')]+['Submission.R19Temporal.pack_get','Submission.R19Temporal.loop_eq','Submission.R19Temporal.packB_get','Submission.R20RowBroadcast.loop_eq','Submission.R20RowBroadcast.runDot_eq']
(H/'HelperAudit.lean.inc').write_text('\n'.join('#print axioms '+r for r in roots)+'\n')
m={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate':path.name,'sha256':sha(full),'bytes':len(full),'fragment_sha256':sha(fragment.encode()),'fragment_bytes':len(fragment.encode()),'base_sha256':sha(base),'base_bytes':len(base),'temporal_donor_sha256':sha(prior),'temporal_section_sha256':sha(temporal.encode()),'public_algorithms_unchanged':True,'roots':roots,'expected_count':len(roots),'diagnostic_entry':'Submission.R20RowBroadcast.diagnosticBmm8','actual_domain':'One full eight-column row, arbitrary batch/m/n; loop projection also works for four arbitrary B8 columns-pair vectors','changes':'No A prep/cache/container; each row/k converts A once; all eight independent accumulators retain original order; B8 prepared once per full call; original per-output finish/replay','formal':'NOT_RUN','full_public_new_bmm_spec':'NOT_DONE_PROBE_ONLY','performance':'UNKNOWN','local_Lean':False,'CI':False}
(H/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m))
