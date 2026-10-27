"""Compose the one actual four-row candidate; no Git/CI or external actions."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, importlib.util, json

HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
OUT = CS / 'f01-r11-wide4-actual'
sha = lambda b: hashlib.sha256(b).hexdigest()

def wrapper():
    s = ['namespace Submission.R11WideRows4', 'open FloatLib.Floats Competition', '']
    s += ['@[inline] def lane40 (s : F40) (r : Fin 4) (l : Fin 10) : Float32 :=', '  match r.val with']
    for r in range(4):
        s += [f'  | {r if r < 3 else "_"} => match l.val with']
        s += [f'    | {j if j < 9 else "_"} => s.c{j}r{r}' for j in range(10)]
    s += ['', 'theorem lane40_eq (s : F40) (r : Fin 4) (l : Fin 10) :',
          '    lane40 s r l = Packed10.lane (projectRow s r) l := by',
          '  rcases r with ⟨r,hr⟩', '  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
          '  rcases h with rfl|rfl|rfl|rfl <;> rfl', '',
          'def joinRows (s0 s1 s2 s3 : Packed10.F10) : F40 :=',
          '  ⟨' + ', '.join(f's{r}.s{j}' for j in range(10) for r in range(4)) + '⟩', '',
          'def within (n base : Nat) (A : Array Float32) (B : Vector Packed10.F10 n)',
          '    (hn : n < USize.size) (hA : base + 3*n + (n-1) < A.size)',
          '    (hAS : A.size < USize.size) : F40 :=']
    bases = ['base', 'base+n', 'base+2*n', 'base+3*n']
    for r, base in enumerate(bases):
        s.append(f'  have h{r} : {base} < USize.size := by omega')
    s += ['  wordLoop (USize.ofNat n) ' + ' '.join(f'(USize.ofNat ({b}))' for b in bases),
          '    A B (USize.toNat_ofNat_of_lt\' hn)']
    for r in range(4):
        s.append(f'    (by simp only [USize.toNat_ofNat_of_lt\' hn, USize.toNat_ofNat_of_lt\' h{r}]; omega)')
    s += ['    hAS 0 ' + ' '.join(['zero32']*40), '',
          'theorem within_row (n base : Nat) (A : Array Float32) (B : Vector Packed10.F10 n)',
          '    (hn : n < USize.size) (hA : base + 3*n + (n-1) < A.size)',
          '    (hAS : A.size < USize.size) (r : Fin 4) :',
          '    projectRow (within n base A B hn hA hAS) r =',
          '      Packed10Index.runDot n (base + r.val*n) A B := by']
    for r, base in enumerate(bases):
        s.append(f'  have h{r} : {base} < USize.size := by omega')
    s += ['  rw [Packed10Index.runDot_eq]', '  rcases r with ⟨r,hr⟩',
          '  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
          '  rcases h with rfl|rfl|rfl|rfl <;>',
          '    simp only [within, wordLoop_row, Packed10Index.loop_eq, projectRow, baseAt,',
          "      USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' h0,",
          "      USize.toNat_ofNat_of_lt' h1, USize.toNat_ofNat_of_lt' h2,",
          "      USize.toNat_ofNat_of_lt' h3, USize.toNat_zero, Nat.zero_mul, Nat.one_mul, Nat.add_zero]",
          '', 'def run (n base : Nat) (A : Array Float32) (B : Vector Packed10.F10 n) : F40 :=',
          '  if h : n < USize.size ∧ base + 3*n + (n-1) < A.size ∧ A.size < USize.size then',
          '    within n base A B h.1 h.2.1 h.2.2',
          '  else joinRows ' + ' '.join(f'(Packed10Index.runDot n ({b}) A B)' for b in bases), '',
          'theorem run_row (n base : Nat) (A : Array Float32) (B : Vector Packed10.F10 n)',
          '    (r : Fin 4) : projectRow (run n base A B) r =',
          '      Packed10Index.runDot n (base + r.val*n) A B := by',
          '  unfold run', '  split', '  · exact within_row n base A B _ _ _ r',
          '  · rcases r with ⟨r,hr⟩', '    have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega',
          '    rcases h with rfl|rfl|rfl|rfl <;>',
          '      simp only [joinRows, projectRow, Nat.zero_mul, Nat.one_mul, Nat.add_zero]',
          '', 'end Submission.R11WideRows4', '']
    return '\n'.join(s)

ACTUAL = '''namespace Submission.R11WideActual
open FloatLib.Floats Competition

def buildTiles (batch m n p : Nat) (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (b : Fin batch) (h : Fin (m / 4)) : R11WideLayout.Tiles p :=
  Vector.ofFn fun g => R11WideRows4.run n ((b.val*m + 4*h.val)*n)
    nativeA ((packedB.get b).get g)

theorem buildTiles_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (h : Fin (m / 4)) :
    R11WideLayout.Projects batch m n p A B R11WideRows4.lane40 b (4*h.val)
      (buildTiles batch m n p (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) b h) := by
  apply R11WideLayout.Projects_of_row_projection batch m n p A B
    R11WideRows4.projectRow R11WideRows4.lane40 R11WideRows4.lane40_eq
  intro g r
  simp only [buildTiles, Packed10.vector_get_ofFn, R11WideRows4.run_row, Nat.add_mul]

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) : Array Binary32 :=
  R11WideLayout.output batch m n p A B R11WideRows4.lane40 (buildTiles batch m n p)

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p) (output batch m n p A B) := by
  exact R11WideLayout.output_prefix batch m n p A B R11WideRows4.lane40
    (buildTiles batch m n p) (buildTiles_projects batch m n p A B)

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    Vector Binary32 (batch*m*p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch*m*p) (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.R11WideActual
'''
ENTRY = '''
def bmmBeforeUnderflowZero (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if 4 ≤ m ∧ 4 < n ∧ 2 < p ∧ n < USize.size ∧ A.toArray.size < USize.size then
    R11WideActual.core batch m n p A B
  else bmmBeforeWideRows batch m n p A B

theorem bmmBeforeUnderflowZero_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmmBeforeUnderflowZero batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmmBeforeUnderflowZero
  split
  · rw [R11WideActual.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeWideRows_spec batch m n p A B
'''

def generate():
    inputs = [(CS/'f01-d11-bmm-wide-backbone/Kernel.lean', '749bc933597ec15b200e8146899f7a055e25b4eef425e156bca337a13c38ca28'),
              (HERE/'astra-wide4-projection.lean', 'afd8d0bf8598f2f7eb612d2b53f8c318a8f4eb0b6eec41502c135db060774291'),
              (HERE/'review-output-wide-layout.lean', '42a3547cd310297a2f79c636b8eb152547c8d4118f3bb66893b4762fd808bab1')]
    for path, digest in inputs: assert sha(path.read_bytes()) == digest, str(path)
    base = inputs[0][0].read_bytes().decode()
    projection = inputs[1][0].read_text(encoding='utf-8')
    writer = inputs[2][0].read_text(encoding='utf-8')
    # Known Nat.succ multiplication normalization issue in earlier batch-local proof.
    writer = writer.replace('rw [Nat.add_mul] at hb', 'rw [Nat.succ_mul] at hb')
    writer = writer.replace('rw [Nat.add_mul, Nat.one_mul] at hs', 'rw [Nat.succ_mul] at hs')
    writer = writer.replace('rw [Nat.add_mul] at h\n', 'rw [Nat.succ_mul] at h\n')
    probe = (CS/'f01-r11-wide4-codegen-probe/increment.lean').read_text(encoding='utf-8')
    # Original probe bytes remain frozen; only its informational opening comment changes here.
    probe = probe.replace('CODEGEN_ONLY: unused machine-loop probe; original four entry points remain unchanged.',
                          'Four-row machine loop now called by the concrete wide BMM entry below.')
    blockstart = base.index('namespace Submission\nopen FloatLib.Floats Competition\n\ndef bmmBeforeUnderflowZero')
    blockend = base.index('end Submission', blockstart)
    old = base[blockstart:blockend]
    renamed = old.replace('bmmBeforeUnderflowZero', 'bmmBeforeWideRows')
    addition = '\n\n'.join([probe, projection, wrapper(), writer, ACTUAL])+'\n\n'
    result = base[:blockstart]+addition+renamed+ENTRY+'\n'+base[blockend:]
    assert result.replace(addition,'',1).replace(renamed+ENTRY+'\n',old,1)==base
    outer = base[base.index('/-- Both short-circuiting scans'):]
    assert result.endswith(outer)
    sp = importlib.util.spec_from_file_location('policy',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    policy=importlib.util.module_from_spec(sp);sp.loader.exec_module(policy);policy.static_check(result)
    data=result.encode()
    assert len(data)<=256000, len(data)
    return data, addition, inputs, sha(outer.encode())

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');a=ap.parse_args()
    data,addition,inputs,outer=generate()
    rec={'candidate':OUT.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
         'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':'f01-d11-bmm-wide-backbone',
         'parent_sha256':inputs[0][1],'validation_mode':'full-gate','proof_status':'NOT_RUN',
         'full_gate':'NOT_RUN','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED',
         'mechanism':'4rows x existingF10B,40orderedscalarMACs,block-localF40cache,row-majorcontinuousoutput,oldtail',
         'outer_underflow_suffix_sha256':outer,'outer_underflow_suffix_byte_identical':True,
         'guard':'underflow miss AND m>=4 AND n>4 AND p>2 AND n<USize.size AND rawA.size<USize.size before new prep; run also proves actual spans or exact four-dot fallback',
         'proof_inputs':[{'path':str(p),'sha256':h} for p,h in inputs],
         'writer_local_proof_repairs':'Nat.succ_mul at three formerly Nat.add_mul sites; originals unchanged',
         'static_policy':'PASS','size_margin':256000-len(data),'inverse_parent_identity':True,
         'new_global_axioms':False,'build_script_sha256':sha(Path(__file__).read_bytes())}
    if a.write:
        OUT.mkdir(exist_ok=True)
        assert not (OUT/'Kernel.lean').exists()
        (OUT/'Kernel.lean').write_bytes(data)
        (OUT/'increment.lean').write_bytes(addition.encode())
        (OUT/'manifest.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    else:
        if (OUT/'Kernel.lean').exists():assert (OUT/'Kernel.lean').read_bytes()==data
    print(json.dumps({k:rec[k] for k in ['candidate','candidate_sha256','candidate_bytes','size_margin','static_policy','proof_status']}))
if __name__=='__main__': main()
