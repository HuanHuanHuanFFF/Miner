"""Generate a projection proof asset only; do not modify the frozen codegen probe."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
probe=CS/'f01-r11-wide4-codegen-probe/Kernel.lean'
assert hashlib.sha256(probe.read_bytes()).hexdigest()=='eb9e76393b13448bd031134035706d3b05ce08b018f7d81dd5614db0c9ac007f'
names=[f'c{j}r{i}' for j in range(10) for i in range(4)]
lines=['/- NOT_RUN proof asset for exact eb9e codegen probe; no active entry is added. -/',
       'namespace Submission.R11WideRows4','open FloatLib.Floats Competition','',
       '/-- Proof projection only; runtime output should read F40 lanes without constructing F10 rows. -/',
       'def projectRow (s : F40) (r : Fin 4) : Packed10.F10 :=','  match r.val with']
for i in range(4):lines.append('  | '+(str(i) if i<3 else '_')+' => ⟨'+', '.join(f's.c{j}r{i}' for j in range(10))+'⟩')
lines+=['','def baseAt (a0 a1 a2 a3 : USize) (r : Fin 4) : USize :=',
        '  match r.val with | 0 => a0 | 1 => a1 | 2 => a2 | _ => a3','',
        'theorem row_bound (count a0 a1 a2 a3 : USize) (A : Array Float32)']
for i in range(4):lines.append(f'    (h{i} : a{i}.toNat + (count.toNat - 1) < A.size)')
lines+=['    (r : Fin 4) : (baseAt a0 a1 a2 a3 r).toNat + (count.toNat - 1) < A.size := by',
        '  rcases r with ⟨r,hr⟩','  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
        '  rcases h with rfl|rfl|rfl|rfl <;> first | exact h0 | exact h1 | exact h2 | exact h3','',
        'theorem wordLoop_row {n : Nat} (count a0 a1 a2 a3 : USize)',
        '    (A : Array Float32) (B : Vector Packed10.F10 n) (hn : count.toNat = n)']
for i in range(4):lines.append(f'    (h{i} : a{i}.toNat + (count.toNat - 1) < A.size)')
lines+=['    (hAS : A.size < USize.size) (k : USize)']
for j in range(10):lines.append('    ('+' '.join(f'c{j}r{i}' for i in range(4))+' : Float32)')
lines+=['    (r : Fin 4) :','    projectRow (wordLoop count a0 a1 a2 a3 A B hn h0 h1 h2 h3 hAS k']
for j in range(10):lines.append('      '+' '.join(f'c{j}r{i}' for i in range(4)))
lines+=['      ) r =','    let s := projectRow (⟨'+', '.join(names)+'⟩ : F40) r',
        '    Packed10Index.loop count (baseAt a0 a1 a2 a3 r) A B hn',
        '      (row_bound count a0 a1 a2 a3 A h0 h1 h2 h3 r) hAS k',
        '      s.s0 s.s1 s.s2 s.s3 s.s4 s.s5 s.s6 s.s7 s.s8 s.s9 := by',
        '  rw [wordLoop]','  split','  · rename_i hk',
        '    dsimp only','    rw [Packed10Index.loop, dif_pos hk]',
        '    dsimp only','    rw [wordLoop_row]',
        '    rcases r with ⟨r,hr⟩','    have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
        '    rcases h with rfl|rfl|rfl|rfl <;> rfl',
        '  · rename_i hk','    dsimp only','    rw [Packed10Index.loop, dif_neg hk] <;> rfl',
        'termination_by count.toNat - k.toNat',
        'decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)','',
        '/-- The projection theorem entails all forty lanes, not an abstract read assumption. -/',
        'theorem lane_of_row_eq (s t : F40) (h : ∀ r : Fin 4, projectRow s r = projectRow t r)',
        '    (r : Fin 4) (j : Fin 10) :',
        '    Packed10.lane (projectRow s r) j = Packed10.lane (projectRow t r) j := by',
        '  rw [h r]','',
        'end Submission.R11WideRows4','']
payload='\n'.join(lines).encode();(HERE/'astra-wide4-projection.lean').write_bytes(payload)
report={'at_utc':datetime.now(timezone.utc).isoformat(),'probe_sha256':hashlib.sha256(probe.read_bytes()).hexdigest(),
        'projection_file':'astra-wide4-projection.lean','projection_sha256':hashlib.sha256(payload).hexdigest(),
        'projection_bytes':len(payload),'new_Kernel_written':False,'Lean':'NOT_RUN','active_bmm_changed':False,
        'proof_target':'Eachactual40paramUSize loop projectedrow equalsactualexistingPacked10Index.loop withactualA.uget/B.uget; fourrows imply40lanes.',
        'reuse_next':'Packed10Index.loop_eq -> Packed10.dot10; existingdot10_lane/finish_dot10_lane needconcretePacked10.packB laneidentity, not anunclosedhb assumption.',
        'known_compile_risks':'Recursive rw underprojectRow/let and goalclosure dependon exactelaboration; no compileravailable locally. RetainexplicitUSizeboundpremises; no resourceincrease.'}
(HERE/'astra-wide4-projection.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report))
