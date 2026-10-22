"""Controlled scalar result guards using exact accepted nonNaN operation bridges."""
from pathlib import Path
import hashlib,json

root=Path(__file__).resolve().parents[1]
parent=root/'f01-d7-direct-nonnan';raw=(parent/'Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest()=='60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15'
guard_parent=root/'f01-r7-self-nonnan-guard-proof1/Kernel.lean'
guard_raw=guard_parent.read_bytes()
assert hashlib.sha256(guard_raw).hexdigest()=='3baa785ee05745d2929af7208c6105d7e2f645a8c46b87e6e631e2165aaa9a6c'
gs=guard_raw.decode();guard=gs[gs.index('namespace R7W04\n'):gs.index('end R7W04')+len('end R7W04')]
base=raw.decode()
# These three closed namespaces are pure proofs independent of exported scalar
# implementations. Move unchanged before scalar definitions; retain qualified names.
blocks=[]
for name in ['NativeBridge','NotNaNProbe','R7Native']:
    start=base.index('\nnamespace '+name+'\n',base.index('\nnamespace Submission\n'))
    end=base.index('\nend '+name,start)+len('\nend '+name)
    block=base[start:end];blocks.append(block)
    base=base[:start]+base[end:]
assert 'theorem modelMulFinite' in blocks[0]
anchor='/-- Raw exponent tests establish both native input conditions. -/'
assert base.count(anchor)==1;base=base.replace(anchor,'\n'.join(blocks)+'\n\n'+anchor)
base=base.replace('import ContractTensor\n','import ContractTensor\n\n'+guard+'\n',1)
mul_anchor='/-- Raw finite input guards retain the original multiplication fallback. -/'
add_start=base.index(anchor);add_end=base.index(mul_anchor,add_start)
old_add=base[add_start:add_end]
new_add='''/-- Classify the native result; raw NaN inputs/results retain exact fallback. -/
@[inline] def add (x y : Binary32) : Binary32 :=
  let result := R2W01b.convert x.raw.1 + R2W01b.convert y.raw.1
  if hn : R7W04.nonNaN result = true then ExecFloat.Binary.ofFloat32 result
  else TunedAdd.add x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  unfold add
  dsimp only
  split
  · rename_i hn
    rw [R2W01c.convert_eq, R2W01c.convert_eq] at hn ⊢
    change R7W04.nonNaN (ExecFloat.Binary.toFloat32 x + ExecFloat.Binary.toFloat32 y) = true at hn
    have hi := NotNaNProbe.add_inputs _ _ ((R7W04.nonNaN_eq_true_iff _).mp hn)
    rw [R7Native.ofFloat32Add _ _ hi.1 hi.2,
      NotNaNProbe.roundtrip x hi.1, NotNaNProbe.roundtrip y hi.2]
    exact ExecFloat.Proof.add_eq_spec x y
  · exact TunedAdd.add_spec x y

'''
mul_start=base.index(mul_anchor);mul_end=base.index('@[inline] def mul (x y : Binary32)',mul_start)
old_mul=base[mul_start:mul_end]
new_mul='''/-- Only a native NaN result requires the original raw-word fallback. -/
@[inline] def nativeMul (x y : Binary32) : Binary32 :=
  let result := ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y
  if hn : R7W04.nonNaN result = true then ExecFloat.Binary.ofFloat32 result
  else FastMul.mul x y

theorem nativeMul_spec : ∀ x y : Binary32, nativeMul x y = ExecFloat.Spec.mul x y := by
  intro x y
  unfold nativeMul
  dsimp only
  split
  · rename_i hn
    have hi := NotNaNProbe.mul_inputs _ _ ((R7W04.nonNaN_eq_true_iff _).mp hn)
    rw [R7Native.ofFloat32Mul _ _ hi.1 hi.2,
      NotNaNProbe.roundtrip x hi.1, NotNaNProbe.roundtrip y hi.2]
    exact ExecFloat.Proof.mul_eq_spec x y
  · exact FastMul.mul_spec x y

'''
for label,use_add,use_mul in [('add',True,False),('mul',False,True),('both',True,True)]:
    s=base
    if use_add: assert s.count(old_add)==1;s=s.replace(old_add,new_add)
    if use_mul: assert s.count(old_mul)==1;s=s.replace(old_mul,new_mul)
    out=root/('f01-d7-result-guard-'+label);out.mkdir(exist_ok=True);data=s.encode()
    assert len(data)<256000 and s.count('namespace R7Native\n')==1
    assert s.count('namespace NativeBridge\n')==2
    assert s[s.index('namespace R2W01b'):s.index('namespace Submission')] == raw.decode()[raw.decode().index('namespace R2W01b'):raw.decode().index('namespace Submission')]
    (out/'Kernel.lean').write_bytes(data)
    manifest={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'parent':parent.name,'parent_sha256':hashlib.sha256(raw).hexdigest(),'validation_mode':'statement-only','proof_status':'NOT_RUN','mechanism':'Classify actual native scalar '+label+' result by IEEE self-BEq instead of two exponent-field input classifiers. Accept infinity. A native NaN result takes the exact previous raw TunedAdd/FastMul fallback. Keep numeric add conversion, multiplication low-exponent route, tensor shapes/order and every unchanged proof.','proof_route':'Move exact closed NativeBridge/NotNaNProbe/R7Native namespaces earlier without edits; reuse nonNaN result inversion, concrete operation bridge and raw roundtrip. Copy exact W04 self-BEq theorem block; newly integrated full source still NOT_RUN.','source_attribution':'FloatLib Team MIT fixed0d918; R7W04 public Lean4.34 self-BEq proof from R researcher; all source hashes in parent manifest and R handoff.','guard_source_sha256':hashlib.sha256(guard_raw).hexdigest(),'moved_proof_blocks_sha256':{n:hashlib.sha256(b.encode()).hexdigest() for n,b in zip(['NativeBridge','NotNaNProbe','R7Native'],blocks)},'expected_gain':'UNKNOWN; normal scalar guards may be cheaper, Inf needs less fallback, NaN now pays initial native work. Measure affected full costs and keep losing families. Not a numeric-mul decoder retry.','formal_submission':'NOT_SUBMITTED'}
    (out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
    print(json.dumps({'candidate':out.name,'sha256':manifest['candidate_sha256'],'bytes':len(data)}))
