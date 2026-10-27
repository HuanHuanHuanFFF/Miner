"""Write future proof fragments only. Never write a candidate Kernel or dispatch CI."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
sha=lambda b:hashlib.sha256(b).hexdigest()
WIDE=CS/'f01-r11-wide4-inline-proof3/Kernel.lean'
PANEL=CS/'f01-d11-panel4-codegen-probe/Kernel.lean'
assert sha(WIDE.read_bytes())=='28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b'
assert sha(PANEL.read_bytes())=='9a40118eae28c92c1abeca7f6a141fb0fbfe963cbf40321681b8013782f9f7ac'
source=WIDE.read_text(encoding='utf-8')
a=source.index('def projectRow (s : F40)');z=source.index('\ndef baseAt ',a)
required='namespace Submission.R11WideRows4\nopen FloatLib.Floats Competition\n'+source[a:z]+'\nend Submission.R11WideRows4\n'

guard='''/- NOT_RUN future proof asset. Requires the exact28b819 declarations.
No runtime entry or dispatcher is replaced. -/
namespace Submission.R11WideGuardBridge
open FloatLib.Floats Competition

theorem block_span (batch m n : Nat) (A : Vector Binary32 (batch*m*n))
    (b : Fin batch) (h : Fin (m/4)) (hn : 0<n) :
    (b.val*m+4*h.val)*n + 3*n + (n-1) < (A.toArray.map ExecFloat.Binary.toFloat32).size := by
  have hb : 4*h.val+4≤m := by have hh:=h.isLt; omega
  have hs := R11WideLayout.nativeA_span batch m n A b (4*h.val) hb ⟨3,by decide⟩ hn
  simpa only [Nat.add_mul] using hs

theorem sized_block_span (batch m n : Nat) (A : Vector Binary32 (batch*m*n))
    (nativeA : Array Float32) (hsize : nativeA.size=A.toArray.size)
    (b : Fin batch) (h : Fin (m/4)) (hn : 0<n) :
    (b.val*m+4*h.val)*n + 3*n + (n-1) < nativeA.size := by
  rw [hsize]
  simpa only [Array.size_map] using block_span batch m n A b h hn

theorem sized_array_fits (batch m n : Nat) (A : Vector Binary32 (batch*m*n))
    (nativeA : Array Float32) (hsize : nativeA.size=A.toArray.size)
    (hA : A.toArray.size<USize.size) : nativeA.size<USize.size := by
  rw [hsize]
  exact hA

/-- Concrete prepared A/B, not an unclosed Projects premise. This vector occurs only in a theorem. -/
theorem direct_within_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn0 : 0<n) (hn : n<USize.size) (hA : A.toArray.size<USize.size)
    (b : Fin batch) (h : Fin (m/4)) :
    R11WideLayout.Projects batch m n p A B R11WideRows4.lane40 b (4*h.val)
      (Vector.ofFn fun g => R11WideRows4.within n ((b.val*m+4*h.val)*n)
        (A.toArray.map ExecFloat.Binary.toFloat32) (((Packed10.packB batch n p B).get b).get g)
        hn (block_span batch m n A b h hn0) (by simpa only [Array.size_map] using hA)) := by
  apply R11WideLayout.Projects_of_row_projection batch m n p A B
    R11WideRows4.projectRow R11WideRows4.lane40 R11WideRows4.lane40_eq
  intro g r
  simp only [Packed10.vector_get_ofFn, R11WideRows4.within_row, Nat.add_mul]

end Submission.R11WideGuardBridge
'''

names=[f'c{j}r{r}' for j in range(10) for r in range(4)]
lines=['/- NOT_RUN future proof fragment; requires Panel4 from9a and the retained projectRow definition. -/',
       'namespace Submission.Panel4Bridge','open FloatLib.Floats Competition','open R11WideRows4','',
       '/-- Proof-only selection of one prepared row. No row array is built. -/',
       'def laneA (a : Panel4.F4) (r : Fin 4) : Float32 :=',
       '  match r.val with | 0 => a.r0 | 1 => a.r1 | 2 => a.r2 | _ => a.r3','',
       'def baseFor (b0 b1 b2 b3 : Nat) (r : Fin 4) : Nat :=',
       '  match r.val with | 0 => b0 | 1 => b1 | 2 => b2 | _ => b3','',
       'theorem packA_read (n b0 b1 b2 b3 : Nat) (Araw : Array Binary32)',
       '    (r : Fin 4) (k : Fin n) :',
       '    laneA ((Panel4.packA n b0 b1 b2 b3 Araw).get k) r =',
       '      (Araw.map ExecFloat.Binary.toFloat32).getD (baseFor b0 b1 b2 b3 r+k.val) Packed10.zero32 := by',
       '  rw [Panel4.packA_get, Packed10.nativeA_getD]',
       '  rcases r with ⟨r,hr⟩',
       '  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
       '  rcases h with rfl|rfl|rfl|rfl <;> rfl','',
       '/-- Exact native recurrence; hread is closed by packA_read below. -/',
       'theorem wordLoop_row {n : Nat} (count : USize) (panel : Vector Panel4.F4 n)',
       '    (B : Vector Packed10.F10 n) (hn : count.toNat=n)',
       '    (source : Array Float32) (base : Nat) (r : Fin 4)',
       '    (hread : ∀ i : Fin n, laneA (panel.get i) r = source.getD (base+i.val) Packed10.zero32)',
       '    (k : USize)']
for j in range(10):lines.append('    ('+' '.join(f'c{j}r{r}' for r in range(4))+' : Float32)')
lines += ['    : projectRow (Panel4.wordLoop count panel B hn k',
          '        '+' '.join(names)+') r =',
          '      let s := projectRow (⟨'+', '.join(names)+'⟩ : F40) r',
          '      Packed10.dot10 n base source B k.toNat s.s0 s.s1 s.s2 s.s3 s.s4 s.s5 s.s6 s.s7 s.s8 s.s9 := by',
          '  rw [Panel4.wordLoop]', '  split', '  · rename_i hk',
          '    have hkn : k.toNat<n := by rw [←hn]; exact USize.lt_iff_toNat_lt.mp hk',
          '    dsimp only', '    rw [Packed10.dot10, dif_pos hkn]', '    dsimp only',
          '    rw [wordLoop_row count panel B hn source base r hread, Packed10Index.stepNat hk]',
          '    have ha : panel.toArray.uget k (by simpa only [panel.size_toArray] using hkn) =',
          '        panel.get ⟨k.toNat,hkn⟩ := by rfl',
          '    rw [ha, Packed10Index.ugetB_get B k hkn]',
          '    have hh := hread ⟨k.toNat,hkn⟩',
          '    rcases r with ⟨r,hr⟩',
          '    have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
          '    rcases h with rfl|rfl|rfl|rfl <;>',
          '      simp only [projectRow, laneA] at hh ⊢ <;> simp only [hh]',
          '  · rename_i hk',
          '    have hkn : ¬ k.toNat<n := by',
          '      rw [←hn]', '      simpa only [USize.lt_iff_toNat_lt] using hk',
          '    dsimp only', '    rw [Packed10.dot10, dif_neg hkn]', '    rfl',
          'termination_by count.toNat-k.toNat',
          'decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)','',
          'theorem runDot_row (n b0 b1 b2 b3 : Nat) (Araw : Array Binary32)',
          '    (B : Vector Packed10.F10 n) (hn : n<USize.size) (r : Fin 4) :',
          '    projectRow (Panel4.runDot n (Panel4.packA n b0 b1 b2 b3 Araw) B hn) r =',
          '      Packed10Index.runDot n (baseFor b0 b1 b2 b3 r) (Araw.map ExecFloat.Binary.toFloat32) B := by',
          '  have h := wordLoop_row (USize.ofNat n) (Panel4.packA n b0 b1 b2 b3 Araw) B',
          "    (USize.toNat_ofNat_of_lt' hn) (Araw.map ExecFloat.Binary.toFloat32)",
          '    (baseFor b0 b1 b2 b3 r) r (packA_read n b0 b1 b2 b3 Araw r) 0',
          '    '+' '.join(['Packed10.zero32']*40),
          '  change projectRow (Panel4.runDot n (Panel4.packA n b0 b1 b2 b3 Araw) B hn) r = _ at h',
          '  rw [h]', '  clear h', '  dsimp only', '  rw [Packed10Index.runDot_eq]',
          '  rcases r with ⟨r,hr⟩', '  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
          '  rcases h with rfl|rfl|rfl|rfl <;> simp only [projectRow, USize.toNat_zero]','',
          'theorem block_row (n p b0 b1 b2 b3 : Nat) (Araw : Array Binary32)',
          '    (packedB : Vector (Vector Packed10.F10 n) (Packed10.groups p)) (hn : n<USize.size)',
          '    (g : Fin (Packed10.groups p)) (r : Fin 4) :',
          '    projectRow ((Panel4.block n p b0 b1 b2 b3 Araw packedB hn).get g) r =',
          '      Packed10Index.runDot n (baseFor b0 b1 b2 b3 r)',
          '        (Araw.map ExecFloat.Binary.toFloat32) (packedB.get g) := by',
          '  unfold Panel4.block', '  dsimp only', '  rw [Packed10.vector_get_ofFn, runDot_row]','',
          'theorem baseFor_rows (n base : Nat) (r : Fin 4) :',
          '    baseFor base (base+n) (base+2*n) (base+3*n) r = base+r.val*n := by',
          '  rcases r with ⟨r,hr⟩', '  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
          '  rcases h with rfl|rfl|rfl|rfl <;> simp only [baseFor, Nat.zero_mul, Nat.one_mul, Nat.add_zero]','',
          'end Submission.Panel4Bridge','']
panel='\n'.join(lines)
files={'astra-wide-guard-proof.lean':guard,'astra-panel4-projectRow-required.lean':required,
       'astra-panel4-loop-projection.lean':panel}
receipts=[]
for name,text in files.items():
    target=HERE/name;assert not target.exists(), 'Keep each proof draft immutable after delivery'
    raw=text.encode();target.write_bytes(raw)
    receipts.append({'path':name,'bytes':len(raw),'sha256':sha(raw),'Lean':'NOT_RUN'})
rec={'at_utc':datetime.now(timezone.utc).isoformat(),'files':receipts,'current_runtime_unchanged':True,
     'new_Kernel_written':False,'CI_dispatched_by_R':False,
     'scope':'Future proof fragments only. Concrete packA closes hread; no current entry replacement or performance claim. Projects glue/output/tail lifetime and exact compilation remain separate obligations.',
     'minimal_projection_statement_bytes':len(PANEL.read_bytes())+len(required.encode())+len(panel.encode())}
(HERE/'astra-next-proof-assets.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(rec,ensure_ascii=False))
