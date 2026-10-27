from pathlib import Path
import hashlib
import json
import difflib

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[6]
PARENT = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-dual-temporal-a4-5/Kernel.lean'
EXPECTED = 'c36bc2502904bf946d442de1a4646e09689f016643f09ab0b6788f9bdd375250'

def sha(data):
    return hashlib.sha256(data).hexdigest()

parent = PARENT.read_bytes()
assert sha(parent) == EXPECTED, (PARENT, sha(parent))
lines = [
    '/- R19 single-row four-column temporal core. NOT_RUN / NOT_COMPILED.',
    '   Append to exact c36bc250 parent only. Public bmm remains byte-identical.',
    '   This is a core/packing equivalence probe, not a complete routed candidate.',
    '   No result cache, new A packing, FloatArray, USize, or padded k MAC. -/',
    'namespace Submission.R19Column4Temporal',
    'open FloatLib.Floats Competition',
    'open R19DualTemporal (A4 blocks)',
    '',
    'structure F4 where',
]
lines += [f'  s{c} : Float32' for c in range(4)]
lines += ['', 'structure B16 where']
lines += [f'  k{k}c{c} : Float32' for k in range(4) for c in range(4)]

def ctor(fields):
    return '⟨' + ', '.join(fields) + '⟩'

for name, cols in [('low', (0, 1)), ('high', (2, 3))]:
    lines += ['', f'@[inline] def {name} (b : B16) : R19Temporal.B8 :=',
              '  ' + ctor([f'b.k{k}c{c}' for k in range(4) for c in cols])]
lines += ['', '@[inline] def join (lo hi : R15ThinPairs.F2) : F4 :=',
          '  ⟨lo.s0, lo.s1, hi.s0, hi.s1⟩', '',
          '@[inline] def packet (n base p k : Nat) (B : Array Binary32) : B16 :=']
fields = []
for k in range(4):
    step = 'k' if k == 0 else f'(k+{k})'
    for c in range(4):
        base = 'base' if c < 2 else '(base+2)'
        if c % 2:
            base += '+1'
        fields.append(f'if {step}<n then R19Temporal.read B ({base}+{step}*p) else Packed10.zero32')
lines += ['  ⟨' + fields[0] + ',']
lines += ['   ' + f + (',' if i != 15 else '⟩') for i, f in enumerate(fields[1:], 1)]
lines += [
    '',
    'theorem low_packet (n base p k : Nat) (B : Array Binary32) :',
    '    low (packet n base p k B) = R19Temporal.packet n base p k B := by rfl',
    '',
    'theorem high_packet (n base p k : Nat) (B : Array Binary32) :',
    '    high (packet n base p k B) = R19Temporal.packet n (base+2) p k B := by rfl',
    '',
    'def pack (n base p : Nat) (B : Array Binary32) : Vector B16 (blocks n) :=',
    '  Vector.ofFn fun t => packet n base p (4*t.val) B',
    '',
    'theorem pack_low (n base p : Nat) (B : Array Binary32) (t : Fin (blocks n)) :',
    '    low ((pack n base p B).get t) = (R19Temporal.pack n base p B).get t := by',
    '  simp only [pack, R19Temporal.pack, Packed10.vector_get_ofFn, low_packet]',
    '',
    'theorem pack_high (n base p : Nat) (B : Array Binary32) (t : Fin (blocks n)) :',
    '    high ((pack n base p B).get t) = (R19Temporal.pack n (base+2) p B).get t := by',
    '  simp only [pack, R19Temporal.pack, Packed10.vector_get_ofFn, high_packet]',
    '',
    'def loop (n basePacket : Nat) (A : Array A4) (B : Vector B16 (blocks n))',
    '    (hA : basePacket+blocks n ≤ A.size)',
    '    (t : Nat) (s0 s1 s2 s3 : Float32) : F4 :=',
    '  let k := 4*t',
    '  if h3 : k+3<n then',
    '    have ht : t<blocks n := by dsimp [k] at h3; unfold blocks; omega',
    '    let a := A[basePacket+t]\'(by omega)',
    '    let b := B.get ⟨t,ht⟩',
]
for k in range(3):
    lines += [f'    let s{c} := s{c}+a.a{k}*b.k{k}c{c}' for c in range(4)]
lines += ['    loop n basePacket A B hA (t+1) ' + ' '.join(f'(s{c}+a.a3*b.k3c{c})' for c in range(4)),
          '  else if h0 : k<n then',
          '    have ht : t<blocks n := by dsimp [k] at h0; unfold blocks; omega',
          '    let a := A[basePacket+t]\'(by omega)',
          '    let b := B.get ⟨t,ht⟩']
lines += [f'    let s{c} := s{c}+a.a0*b.k0c{c}' for c in range(4)]
lines += ['    if k+1<n then']
lines += [f'      let s{c} := s{c}+a.a1*b.k1c{c}' for c in range(4)]
lines += ['      if k+2<n then ' + ctor([f's{c}+a.a2*b.k2c{c}' for c in range(4)]) + ' else ⟨s0,s1,s2,s3⟩',
          '    else ⟨s0,s1,s2,s3⟩',
          '  else ⟨s0,s1,s2,s3⟩',
          'termination_by n-4*t', 'decreasing_by all_goals omega', '']

common = [
    'theorem loop_eq (n basePacket : Nat) (A : Array A4) (B : Vector B16 (blocks n))',
    '    (L H : Vector R19Temporal.B8 (blocks n))',
    '    (hA : basePacket+blocks n ≤ A.size)',
    '    (hL : ∀ i : Fin (blocks n), low (B.get i) = L.get i)',
    '    (hH : ∀ i : Fin (blocks n), high (B.get i) = H.get i)',
    '    (t : Nat) (s0 s1 s2 s3 : Float32) :',
    '    loop n basePacket A B hA t s0 s1 s2 s3 =',
    '      join (R19DualTemporal.loop n basePacket A L hA t s0 s1)',
    '        (R19DualTemporal.loop n basePacket A H hA t s2 s3) := by',
    '  have eL := @R19DualTemporal.loop.eq_def n basePacket A L hA t s0 s1',
    '  have eH := @R19DualTemporal.loop.eq_def n basePacket A H hA t s2 s3',
    '  have eN := @loop.eq_def n basePacket A B hA t s0 s1 s2 s3',
    '  by_cases h3 : 4*t+3<n',
    '  · have ht : t<blocks n := by unfold blocks; omega',
    '    rw [eN, eL, eH]',
    '    simp only [h3, dite_true]',
    '    simp only [← hL ⟨t,ht⟩, ← hH ⟨t,ht⟩, low, high]',
    '    exact loop_eq n basePacket A B L H hA hL hH (t+1) _ _ _ _',
    '  · by_cases h0 : 4*t<n',
    '    · have ht : t<blocks n := by unfold blocks; omega',
    '      by_cases h1 : 4*t+1<n',
    '      · by_cases h2 : 4*t+2<n',
    '        · rw [eN, eL, eH]',
    '          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true]',
    '          simp only [← hL ⟨t,ht⟩, ← hH ⟨t,ht⟩, low, high, join]',
    '        · rw [eN, eL, eH]',
    '          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true, ite_false]',
    '          simp only [← hL ⟨t,ht⟩, ← hH ⟨t,ht⟩, low, high, join]',
    '      · rw [eN, eL, eH]',
    '        simp only [h3, h0, h1, dite_false, dite_true, ite_true, ite_false]',
    '        simp only [← hL ⟨t,ht⟩, ← hH ⟨t,ht⟩, low, high, join]',
    '    · rw [eN, eL, eH]',
    '      simp only [h3, h0, dite_false, join]',
    'termination_by n-4*t',
    'decreasing_by all_goals omega',
    '',
    'theorem loop_pack_eq (n basePacket baseB p : Nat) (A : Array A4) (B : Array Binary32)',
    '    (hA : basePacket+blocks n ≤ A.size) (t : Nat) (s0 s1 s2 s3 : Float32) :',
    '    loop n basePacket A (pack n baseB p B) hA t s0 s1 s2 s3 =',
    '      join (R19DualTemporal.loop n basePacket A (R19Temporal.pack n baseB p B) hA t s0 s1)',
    '        (R19DualTemporal.loop n basePacket A (R19Temporal.pack n (baseB+2) p B) hA t s2 s3) := by',
    '  apply loop_eq',
    '  · exact pack_low n baseB p B',
    '  · exact pack_high n baseB p B',
    '',
    '@[inline] def runDot (rows n : Nat) (r : Fin rows)',
    '    (A : Vector A4 (rows*blocks n)) (B : Vector B16 (blocks n)) : F4 :=',
    '  loop n (r.val*blocks n) A.toArray B (R19DualTemporal.row_bound rows n A r)',
    '    0 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32',
    '',
    'theorem runDot_pack_eq (rows n : Nat) (r : Fin rows)',
    '    (A : Vector A4 (rows*blocks n)) (baseB p : Nat) (B : Array Binary32) :',
    '    runDot rows n r A (pack n baseB p B) =',
    '      join (R19DualTemporal.runDot rows n r A (R19Temporal.pack n baseB p B))',
    '        (R19DualTemporal.runDot rows n r A (R19Temporal.pack n (baseB+2) p B)) := by',
    '  unfold runDot R19DualTemporal.runDot',
    '  exact loop_pack_eq n (r.val*blocks n) baseB p A.toArray B',
    '    (R19DualTemporal.row_bound rows n A r) 0 _ _ _ _',
    '',
    '/- Structural coverage only: no new phantom column MACs relative to B8 pairs.',
    '   This guard is NOT wired into public dispatch in this probe. -/',
    'def samePaddedWidth (p : Nat) : Prop := 4*((p+3)/4) = 2*((p+1)/2)',
    '',
    'theorem samePaddedWidth_small (p : Nat) (hp : 3≤p ∧ p≤8) :',
    '    samePaddedWidth p ↔ p=3 ∨ p=4 ∨ p=7 ∨ p=8 := by',
    '  unfold samePaddedWidth',
    '  omega',
    '',
    'end Submission.R19Column4Temporal',
]
lines += common
fragment = ('\n'.join(lines) + '\n').encode('utf-8')
source = parent + b'\n' + fragment
assert len(source) <= 256000, len(source)
(HERE / 'Column4Temporal.lean.inc').write_bytes(fragment)
(HERE / 'Kernel-core-probe.lean').write_bytes(source)
(HERE / 'inverse.patch').write_text(''.join(difflib.unified_diff(
    source.decode().splitlines(True), parent.decode().splitlines(True),
    fromfile='Kernel-core-probe.lean', tofile='Kernel-parent-c36bc250.lean')), encoding='utf-8', newline='\n')
roots = ['low_packet', 'high_packet', 'pack_low', 'pack_high', 'loop_eq',
         'loop_pack_eq', 'runDot_pack_eq', 'samePaddedWidth_small']
(HERE / 'HelperAudit.lean.inc').write_text('\n'.join(
    '#print axioms Submission.R19Column4Temporal.' + root for root in roots) + '\n', encoding='utf-8')
manifest = {
    'status': 'NOT_RUN', 'parent_path': str(PARENT), 'parent_sha256': sha(parent),
    'parent_bytes': len(parent), 'fragment_sha256': sha(fragment), 'fragment_bytes': len(fragment),
    'source_sha256': sha(source), 'source_bytes': len(source), 'remaining_bytes': 256000-len(source),
    'public_runtime': 'UNCHANGED_PARENT_BYTES; new core/packing symbols only',
    'roots': ['Submission.R19Column4Temporal.' + root for root in roots],
    'compile': 'NOT_RUN', 'kernel_replay': 'NOT_RUN', 'axiom_audit': 'NOT_RUN',
    'generated_C': 'NOT_RUN', 'timing': 'NOT_RUN', 'full_gate': 'NOT_RUN',
    'complete_routed_writer': 'NOT_IMPLEMENTED',
    'd17_or_confirmation_data_read': False,
}
(HERE / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
print(json.dumps(manifest, ensure_ascii=False, indent=2))
