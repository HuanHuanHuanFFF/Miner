#!/usr/bin/env python3
"""One-character lexical repairs to two frozen, native-only source intentions.
The old builders/sources are not edited. No arithmetic/guard/layout change.
"""
from pathlib import Path
import hashlib,importlib.util,json
P=Path(__file__).resolve().parent
BASE_SHA='ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3'
COMMON={'compact11.py':'8863afd1e3d0ec254ad0ac5a55250e18916848c6a6e6ee340a3f9c517a11c167'}
VARIANTS={
 'packed-support11-v3':{
  'builder':'build_packed_support.py','old_variant':'packed-support11-v2',
  'pins':{'build_packed_support.py':'0ce2c751a776ee5957e9ecefdfbea4b5fd484944128284d612d2c03d5b2f7c07','PackedSupportRuntime.lean.inc':'18f1fb2097e55be175990a7b95312c524ad8b7024fcff5e5ba923c02fe63ce99'},
  'old_sha256':'a498d9b70f9892a671943c6a726c36e2e745baae33fb986b899012ccf3f8b6c2',
  'before':b'if v!=0x200000000000000 then','after':b'if v !=0x200000000000000 then',
  'old_runtime':'PackedSupportRuntime.lean.inc','new_runtime':'PackedSupportRuntime-v3.lean.inc'},
 'spatial11-native-v2':{
  'builder':'build_spatial11.py','old_variant':'spatial11-native',
  'pins':{'build_spatial11.py':'ef44083d1faceac3360092a3d945ba5d0d8981b60af468a19be0f48ce3826fee'},
  'old_sha256':'8e5b27c03926667b2d4398f21519be91dc39b84a9097e24844af8657f0f1e1d3',
  'before':b'Yf w!=0','after':b'Yf w !=0',
  'old_runtime':'SpatialRuntime.lean.inc','new_runtime':'SpatialRuntime-v2.lean.inc'}
}
def transform(raw,submission,variant):
 assert submission==11 and hashlib.sha256(raw).hexdigest()==BASE_SHA
 item=VARIANTS[variant]
 for name,digest in (COMMON|item['pins']).items():
  assert hashlib.sha256((P/name).read_bytes()).hexdigest()==digest,('dependency drift',name)
 spec=importlib.util.spec_from_file_location('frozen_builder_'+variant.replace('-','_'),P/item['builder'])
 module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
 old=module.transform(raw,11,item['old_variant'])
 assert hashlib.sha256(old).hexdigest()==item['old_sha256']
 assert old.count(item['before'])==1
 result=old.replace(item['before'],item['after'])
 assert len(result)==len(old)+1 and len(result)<=256000
 assert result.replace(item['after'],item['before'])==old
 return result
def main():
 raw=(P.parents[1]/'competition-state/source-private/official-11.lean').read_bytes()
 results=[]
 for variant,item in VARIANTS.items():
  result=transform(raw,11,variant)
  (P/'private'/f'{variant}.lean').write_bytes(result)
  old_runtime=(P/item['old_runtime']).read_bytes()
  assert old_runtime.count(item['before'])==1
  (P/item['new_runtime']).write_bytes(old_runtime.replace(item['before'],item['after']))
  results.append({'variant':variant,'source_sha256':hashlib.sha256(result).hexdigest(),'bytes':len(result),'old_source_sha256':item['old_sha256'],'delta_bytes':1,'before':item['before'].decode(),'after':item['after'].decode(),'dependencies':COMMON|item['pins'],'declares_correct':False,'full_gate':False,'proof_state':'NOT_PROVED_NATIVE_ONLY','compile_native':'NOT_RUN'})
 r={'state':'EXACT_BYTE_REPAIR_READY_NOT_COMPILED','recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'base_sha256':BASE_SHA,'variants':results,'reason':'Pinned Lean4.34 isIdRest includes bang, so w!= is the identifier w! followed by equality. Insert one separator before !=. Frozen sources retained unchanged.','model_scope':'Existing arithmetic models describe the intended != guard; actual Lean compilation was never established. No new performance/independence claim.'}
 (P/'lexical-repair-receipt.json').write_bytes((json.dumps(r,indent=2)+'\n').encode())
 print(json.dumps(r,indent=2))
if __name__=='__main__':main()
