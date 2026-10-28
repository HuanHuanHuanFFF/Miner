"""Generate one 4-row x 4-column diagnostic, never compile or run it locally."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
BASE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
BASE_SHA = '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
EMIT = HERE.parent / 'development-pair8/EmitSizeOnly.lean.inc'
EMIT_SHA = 'b0d96ba793d9bb74069bde3754cef2b877c454271f2b20c1ecec228074e02675'
sha = lambda b: hashlib.sha256(b).hexdigest()


def fragment():
    s = '''/- Diagnostic only: A4 per four-row panel, B4 per column-group/k.
   Sixteen independent original-order scalar chains, no temporal unrolling.
   Complete new Float32/Lean/cost validation remains NOT_RUN. -/
namespace Submission.R22Resident16
open FloatLib.Floats Competition

def groups (p : Nat) : Nat := (p + 3) / 4

structure A4 where
  r0 : Float32
  r1 : Float32
  r2 : Float32
  r3 : Float32

structure B4 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32

'''
    for structure, typ, prefix in [('Acc', 'Float32', 'q'), ('Words', 'UInt32', 'w')]:
        s += 'structure ' + structure + ' where\n'
        s += ''.join(f'  {prefix}{r}{c} : {typ}\n' for c in range(4) for r in range(4)) + '\n'
    s += '''def packA (n base : Nat) (A : Array Binary32) : Vector A4 n :=
  Vector.ofFn fun k =>
    ⟨ExecFloat.Binary.toFloat32 (A.getD (base + k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (base + n + k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (base + 2 * n + k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (base + 3 * n + k.val) posZero)⟩

def packBGroup (n p base : Nat) (B : Array Binary32) (valid : Nat) : Vector B4 n :=
  Vector.ofFn fun k =>
    let i := base + k.val * p
    ⟨ExecFloat.Binary.toFloat32 (B.getD i posZero),
     if 1 < valid then ExecFloat.Binary.toFloat32 (B.getD (i + 1) posZero) else Packed10.zero32,
     if 2 < valid then ExecFloat.Binary.toFloat32 (B.getD (i + 2) posZero) else Packed10.zero32,
     if 3 < valid then ExecFloat.Binary.toFloat32 (B.getD (i + 3) posZero) else Packed10.zero32⟩

def packBBatch (n p b : Nat) (B : Array Binary32) (out : Array (Vector B4 n)) :
    Array (Vector B4 n) :=
  Fin.foldl (groups p) (fun acc g =>
    acc.push (packBGroup n p (b * n * p + 4 * g.val) B (min 4 (p - 4 * g.val)))) out

theorem packBBatch_size (n p b : Nat) (B : Array Binary32) (out : Array (Vector B4 n)) :
    (packBBatch n p b B out).size = out.size + groups p := by
  unfold packBBatch
  apply RowStream.foldl_inv (groups p) _
    (fun k (acc : Array (Vector B4 n)) => acc.size = out.size + k)
  · intro g acc h
    simp only [Array.size_push, h]
    omega
  · simp

def packBData (batch n p : Nat) (B : Array Binary32) : Array (Vector B4 n) :=
  Fin.foldl batch (fun acc b => packBBatch n p b.val B acc)
    (Array.mkEmpty (batch * groups p))

theorem packBData_size (batch n p : Nat) (B : Array Binary32) :
    (packBData batch n p B).size = batch * groups p := by
  unfold packBData
  exact RowStream.foldl_inv batch (fun acc b => packBBatch n p b.val B acc)
    (fun k (acc : Array (Vector B4 n)) => acc.size = k * groups p)
    (by
      intro b acc h
      rw [packBBatch_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * groups p)) (by simp)

abbrev PackedB (batch n p : Nat) := Vector (Vector B4 n) (batch * groups p)

def packB (batch n p : Nat) (B : Array Binary32) : PackedB batch n p :=
  ⟨packBData batch n p B, packBData_size batch n p B⟩

def tileIndex (batch p : Nat) (b : Fin batch) (g : Fin (groups p)) :
    Fin (batch * groups p) :=
  ⟨b.val * groups p + g.val, by
    have h := Nat.mul_le_mul_right (groups p) b.isLt
    rw [Nat.succ_mul] at h
    have hg := g.isLt
    omega⟩

def wordLoop {n : Nat} (count : USize) (A : Vector A4 n) (B : Vector B4 n)
    (hn : count.toNat = n) (k : USize)
'''
    s += ''.join('    (' + ' '.join(f'q{r}{c}' for r in range(4)) + ' : Float32)\n' for c in range(4))
    s += '''    : Acc :=
  if hk : k < count then
    have hkn : k.toNat < n := by rw [←hn]; exact USize.lt_iff_toNat_lt.mp hk
    let a := A.toArray.uget k (by simpa only [A.size_toArray] using hkn)
    let b := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    wordLoop count A B hn (k + 1)
'''
    s += ''.join('      ' + ' '.join(f'(q{r}{c} + a.r{r} * b.s{c})' for r in range(4)) + '\n' for c in range(4))
    s += '  else ⟨' + ', '.join(f'q{r}{c}' for c in range(4) for r in range(4)) + '⟩\n'
    s += '''termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

def runDot (n : Nat) (A : Vector A4 n) (B : Vector B4 n) (hn : n < USize.size) : Acc :=
  wordLoop (USize.ofNat n) A B (USize.toNat_ofNat_of_lt' hn) 0
'''
    s += ''.join('    ' + ' '.join(['Packed10.zero32'] * 4) + '\n' for _ in range(4))
    s += '''
@[noinline] def tile (p n baseA baseB valid : Nat) (A B : Array Binary32)
    (PA : Vector A4 n) (PB : Vector B4 n) (hn : n < USize.size) : Words :=
  let q := runDot n PA PB hn
'''
    for c in range(4):
        for r in range(4):
            base_a = 'baseA' if r == 0 else f'(baseA + {r} * n)'
            base_b = 'baseB' if c == 0 else f'(baseB + {c})'
            expr = f'(Packed10.finish n {base_a} {base_b} p A B q.q{r}{c}).raw.1'
            if c > 0:
                expr = f'if {c} < valid then {expr} else (0 : UInt32)'
            s += f'  let w{r}{c} := {expr}\n'
    s += '  ⟨' + ', '.join(f'w{r}{c}' for c in range(4) for r in range(4)) + '⟩\n\n'
    s += '''def tiles (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (first : Nat) : Vector Words (groups p) :=
  let baseA := (b.val * m + first) * n
  let PA := packA n baseA A
  Vector.ofFn (fun g => tile p n baseA (b.val * n * p + 4 * g.val)
    (min 4 (p - 4 * g.val)) A B PA (PB.get (tileIndex batch p b g)) hn)

@[inline] def getTile {p : Nat} (t : Vector Words (groups p)) (j : Fin p) : Words :=
  t.get ⟨j.val / 4, by have hj := j.isLt; unfold groups; omega⟩

'''
    for r in range(4):
        s += f'''@[inline] def read{r} {{p : Nat}} (t : Vector Words (groups p)) (j : Fin p) : Binary32 :=
  let w := getTile t j
  FastMul.ofBits (match j.val % 4 with
    | 0 => w.w{r}0 | 1 => w.w{r}1 | 2 => w.w{r}2 | _ => w.w{r}3)
'''
    s += '''
@[noinline] def rows4 (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (first : Nat) (out : Array Binary32) : Array Binary32 :=
  if p = 0 then out else
    let t := tiles batch m n p A B PB hn b first
    let out := RowStream.emit p (read0 t) out
    let out := RowStream.emit p (read1 t) out
    let out := RowStream.emit p (read2 t) out
    RowStream.emit p (read3 t) out

theorem rows4_size (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (first : Nat) (out : Array Binary32) :
    (rows4 batch m n p A B PB hn b first out).size = out.size + 4 * p := by
  unfold rows4
  split
  · rename_i hp
    subst p
    simp
  · simp only [R21StreamingPair.emit_size]
    omega

def blocks (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m / 4) (fun acc r => rows4 batch m n p A B PB hn b (4 * r.val) acc) out

theorem blocks_size (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (out : Array Binary32) :
    (blocks batch m n p A B PB hn b out).size = out.size + (m / 4) * (4 * p) := by
  unfold blocks
  apply RowStream.foldl_inv (m / 4) _
    (fun k (acc : Array Binary32) => acc.size = out.size + k * (4 * p))
  · intro r acc h
    rw [rows4_size, h, Nat.add_mul]
    simp only [Nat.one_mul, Nat.add_assoc]
  · simp

def rows (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (out : Array Binary32) : Array Binary32 :=
  let out := blocks batch m n p A B PB hn b out
  RowStream.emit ((m % 4) * p) (fun j => NativeFinal.dot n
    ((b.val * m + m / 4 * 4 + j.val / p) * n) (b.val * n * p + j.val % p) p A B) out

theorem rows_size (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) (b : Fin batch) (out : Array Binary32) :
    (rows batch m n p A B PB hn b out).size = out.size + m * p := by
  have hd : m / 4 * 4 + m % 4 = m := by omega
  simp only [rows, R21StreamingPair.emit_size, blocks_size]
  calc
    out.size + m / 4 * (4 * p) + m % 4 * p =
        out.size + (m / 4 * 4 + m % 4) * p := by
      simp only [Nat.add_mul, Nat.mul_assoc, Nat.add_assoc]
    _ = out.size + m * p := by rw [hd]

def output (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) : Array Binary32 :=
  Fin.foldl batch (fun acc b => rows batch m n p A B PB hn b acc)
    (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat) (A B : Array Binary32) (PB : PackedB batch n p)
    (hn : n < USize.size) : (output batch m n p A B PB hn).size = batch * m * p := by
  unfold output
  have h := RowStream.foldl_inv batch (fun acc b => rows batch m n p A B PB hn b acc)
    (fun k (acc : Array Binary32) => acc.size = k * (m * p))
    (by
      intro b acc h
      rw [rows_size, h, Nat.add_mul]
      simp)
    (Array.mkEmpty (batch * m * p)) (by simp)
  simpa only [Nat.mul_assoc] using h

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) :
    Vector Binary32 (batch * m * p) :=
  let PB := packB batch n p B.toArray
  ⟨output batch m n p A.toArray B.toArray PB hn,
    output_size batch m n p A.toArray B.toArray PB hn⟩

def guarded (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if h : 1 < n ∧ 4 ≤ m ∧ 4 ≤ p ∧ n < USize.size then core batch m n p A B h.2.2.2
  else Submission.bmm batch m n p A B

end Submission.R22Resident16
'''
    return s.encode()


def main():
    original = BASE.read_bytes()
    assert sha(original) == BASE_SHA and len(original) == 226829
    emit = EMIT.read_bytes()
    assert sha(emit) == EMIT_SHA and b'theorem emit_size' in emit and b'def ' not in emit
    new = fragment()
    (HERE / 'Resident16.lean.inc').write_bytes(new)
    source = original + b'\n' + emit + b'\n' + new
    assert len(source) <= 256000
    assert source.count(b'import ') == 1 and source.startswith(b'import ContractTensor')
    loop = new.split(b'def wordLoop', 1)[1].split(b'def runDot', 1)[0]
    assert loop.count(b' + a.r') == 16 and loop.count(b' * b.s') == 16
    assert loop.count(b'.uget k') == 2
    assert not any(x in loop for x in (b'toFloat32', b'convert', b'ofBits', b'.push', b'.map', b' Array.'))
    (HERE / 'KernelResident16Cost.lean').write_bytes(source)
    data = {'source': 'KernelResident16Cost.lean', 'sha256': sha(source), 'bytes': len(source),
            'base': str(BASE.relative_to(ROOT)).replace('\\', '/'), 'base_sha256': sha(original),
            'base_bytes': len(original), 'emit_size_sha256': sha(emit), 'emit_size_bytes': len(emit),
            'fragment': 'Resident16.lean.inc', 'fragment_sha256': sha(new), 'fragment_bytes': len(new),
            'builder_sha256': sha(Path(__file__).read_bytes()),
            'caller': 'R22Resident16CostMain.lean',
            'caller_sha256': sha((HERE / 'R22Resident16CostMain.lean').read_bytes()),
            'caller_source_scope': 'Separate noinline Suite runners; actual static callback ABI remains NOT_RUN.',
            'public_four_roots': 'B2 exact prefix; diagnostic caller must name R22Resident16.guarded.',
            'status': 'SOURCE_ONLY_NOT_RUN', 'new_BMM_equivalence': 'UNKNOWN',
            'statement': 'NOT_RUN', 'replay': 'NOT_RUN', 'axioms': 'NOT_RUN',
            'C_ASM': 'NOT_RUN', 'full_cost': 'NOT_RUN', 'full_gate': 'NOT_RUN',
            'guard': 'underflow-zero first; n>1,m>=4,p>=4,n<USize.size; otherwise exact B2',
            'source_checks': {'two_borrow_inputs_syntax': True, 'sixteen_mul_add_chains': True,
                              'no_hot_codec_or_container_syntax': True},
            'limits': 'Source checks do not establish lowering, IEEE equivalence, allocation, caller lifetime or speed.'}
    (HERE / 'resident16-source-manifest.json').write_text(json.dumps(data, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(data))


if __name__ == '__main__':
    main()
