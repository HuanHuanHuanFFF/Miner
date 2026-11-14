#!/usr/bin/env python3
"""One preferred domain refinement after the parser repair, as requested in1854.
Ordinary zero weights are allowed, but every output row must have a nonzero weight.
No kernel-kind/seed tests; no new correctness theorem; old sources stay unchanged.
"""
from pathlib import Path
import hashlib,importlib.util,json,re
P=Path(__file__).resolve().parent
PINS={
 'build_spatial_parser_repair.py':'71ae6d94a57292c9d195651dcd8496bba772404f8e7576e9841d84c8ec214e92',
 'history/spatial-v0-oversize/build_spatial11.py':'d96205b64b9d9f51e7ba2584b21bbf6efad102baaa5b59ad0bf92a684d837496',
 'compact11.py':'8863afd1e3d0ec254ad0ac5a55250e18916848c6a6e6ee340a3f9c517a11c167'}
OLD_SHA='5a43cf03c9ede92d7f28299acd8c99614f6155e5c04dfacca262352ca7400f1c'
REM=b'&&wts.all (fun w=>Yf w !=0)'
BEFORE=b'Ybg BW[o]! b[o]! bp k xm&&2<=e'
AFTER=b'((BW[o]! >>>16) !=511)&&Ybg BW[o]! b[o]! bp k xm&&2<=e'
def parent():
 for f,h in PINS.items():assert hashlib.sha256((P/f).read_bytes()).hexdigest()==h,f
 spec=importlib.util.spec_from_file_location('frozen_spatial_parser_repair',P/'build_spatial_parser_repair.py')
 m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def delta(old):
 assert old.count(REM)==1 and old.count(BEFORE)==1
 return old.replace(REM,b'').replace(BEFORE,AFTER)
def transform(raw,submission,variant):
 assert submission==11 and variant=='spatial11-mixed-native'
 module=parent();old=module.transform(raw,11,'spatial11-native-v3')
 assert hashlib.sha256(old).hexdigest()==OLD_SHA
 identifiers=set(re.findall(r'\w+',raw.decode()))
 assert not (identifiers&set(module.RENAMES.values())),'short name appeared in base'
 result=delta(old)
 assert len(result)<=256000
 assert b'theorem correct:' not in result
 return result
def runtime():return delta(parent().runtime().encode())
def main():
 raw=(P.parents[1]/'competition-state/source-private/official-11.lean').read_bytes()
 result=transform(raw,11,'spatial11-mixed-native')
 (P/'private/spatial11-mixed-native.lean').write_bytes(result)
 (P/'SpatialRuntime-mixed.lean.inc').write_bytes(runtime())
 r={'state':'PREFERRED_MIXED_ZERO_NATIVE_SOURCE_UNCOMPILED','variant':'spatial11-mixed-native','source_sha256':hashlib.sha256(result).hexdigest(),'bytes':len(result),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'dependencies':PINS,'previous_source_sha256':OLD_SHA,'runtime_sha256':hashlib.sha256(runtime()).hexdigest(),'source_delta':'Remove all-weights-nonzero scan; add BW[o].min!=511 to each existing per-output admission predicate. No transform/accumulator/bias/cache/output/layout change.','requested_by':'research/requests/1854-spatial-mixed-zero-guard.md and1911 preflight','freeze_check':'At19:16 local development/ci-bridge plan files contained no8e5/f59/5a43/spatial11 reference; this is a new preferred source, not mutation of an existing plan.','guard':'Originalnarrow/finite/size,3x3 stride1 pad1,positiveevenh/w,cin<=8,cout>=4,B0>=2,old nonzero-bias shift<=76,eachBW.min!=511. Individual zero weights allowed; allzero row or any failed guard uses original Ybp.','new_entry':'Submission.rV','declares_correct':False,'full_gate':False,'compile_native':'NOT_RUN','all12_full_proof_fit':'UNKNOWN','new_independent_evidence':False}
 (P/'spatial-mixed-native-receipt.json').write_bytes((json.dumps(r,indent=2)+'\n').encode());print(json.dumps(r,indent=2))
if __name__=='__main__':main()
