"""One mechanism: select exact raw NaNs before expensive native conversion."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4];C=ROOT/'competitions/floatlib/candidates'
source=C/'f01-d12-scalar-combined/Kernel.lean';raw=source.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
text=raw.decode();start=text.index('/-- Classify the native result;');middle=text.index('/-- Only a native NaN result',start);end=text.index('@[inline] def mul (x y : Binary32)',middle)
add=text[start:middle].replace('def add (','def addBeforeRawSelect (').replace('theorem add_spec :','theorem addBeforeRawSelect_spec :').replace('unfold add\n','unfold addBeforeRawSelect\n')
mul=text[middle:end].replace('nativeMul','nativeMulBeforeRawSelect')
new_add='''@[inline] def add (x y : Binary32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => addBeforeRawSelect x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  unfold add
  split
  · rename_i w hw
    exact DWordNaN.selected_add x y w hw
  · exact addBeforeRawSelect_spec x y

'''
new_mul='''@[inline] def nativeMul (x y : Binary32) : Binary32 :=
  match DWordNaN.rawChoose x.raw.1 y.raw.1 with
  | some w => FastMul.ofBits w
  | none => nativeMulBeforeRawSelect x y

theorem nativeMul_spec : ∀ x y : Binary32, nativeMul x y = ExecFloat.Spec.mul x y := by
  intro x y
  unfold nativeMul
  split
  · rename_i w hw
    exact DWordNaN.selected_mul x y w hw
  · exact nativeMulBeforeRawSelect_spec x y

'''
result=(text[:start]+add+new_add+mul+new_mul+text[end:]).encode()
folder=C/'f01-r14-dev-early-nan';assert not folder.exists();folder.mkdir()
assert len(result)<=256000
(folder/'Kernel.lean').write_bytes(result)
meta={'candidate':folder.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),'parent':'f01-d12-scalar-combined','parent_sha256':hashlib.sha256(raw).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'validation_mode':'full-gate','proof_status':'NOT_RUN','mechanism':'Hoist exact signaling-first raw NaN selection before native scalar add and nativeMul, using already verified selected_add/selected_mul; keep old paths and complete tensor tail unchanged. Different from R12 cold selector which only runs after native conversion/result detection.','performance':'UNKNOWN; targets expensive NaN conversions, ordinary inputs pay raw classification. No zero shortcut or change to arithmetic/order.'}
(folder/'manifest.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
(OUT/'development-early-nan-build.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(meta,ensure_ascii=False))
