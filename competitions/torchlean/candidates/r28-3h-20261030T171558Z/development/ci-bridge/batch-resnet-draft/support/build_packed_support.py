#!/usr/bin/env python3
"""Source11 + own exact support-cache prototype; explicitly native-only.
Never use this variant as a proved or formally submittable candidate.
"""
from pathlib import Path
import hashlib,json,re,importlib.util
P=Path(__file__).resolve().parent
BASE_SHA='ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3'
def transform(raw,submission=11,variant='packed-support11-v2'):
    assert submission==11 and variant=='packed-support11-v2'
    assert hashlib.sha256(raw).hexdigest()==BASE_SHA
    s=raw.decode('utf-8')
    start=s.index('def kernels:Kernels where')
    ending=s[start:]
    runtime_record=ending[:ending.index('theorem correct:')]
    assert 'conv:=⟨Ybp,dwQ⟩' in runtime_record
    runtime_record=runtime_record.replace('conv:=⟨Ybp,dwQ⟩','conv:=⟨R28packedConv,dwQ⟩')
    original_end=re.sub(r'\bkernels\b','R28baseKernels',ending)
    original_end=re.sub(r'\bcorrect\b','R28baseCorrect',original_end)
    assert original_end.rstrip().endswith('end Submission')
    s=s[:start]+original_end[:original_end.rfind('end Submission')]
    s+='\n'+(P/'PackedSupportRuntime.lean.inc').read_text(encoding='utf-8')+'\n'+runtime_record+'end Submission\n'
    spec=importlib.util.spec_from_file_location('compact11',P/'compact11.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    result=m.compact(s.encode('utf-8'),strict_base=False)
    assert len(result)<=256000,len(result)
    assert b'theorem correct:' not in result
    return result
def main():
    base=P.parents[1]/'competition-state/source-private/official-11.lean'
    out=transform(base.read_bytes())
    (P/'private').mkdir(exist_ok=True)
    (P/'private/packed-support11-v2-native-only.lean').write_bytes(out)
    receipt={'variant':'packed-support11-v2','base_sha256':BASE_SHA,'sha256':hashlib.sha256(out).hexdigest(),'bytes':len(out),'proof_state':'NOT_PROVED_NATIVE_ONLY_NO_SUBMISSION_CORRECT','native_state':'UNKNOWN','recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'runtime_sha256':hashlib.sha256((P/'PackedSupportRuntime.lean.inc').read_bytes()).hexdigest(),'compactor_sha256':hashlib.sha256((P/'compact11.py').read_bytes()).hexdigest(),'guards':'source11 numerical conditions + 3x3 stride1 pad1 K<128 cout>=4 input-zero fraction>=1/4','preserved':'source11 original all12 implementation/proof retained under base names; every unsupported case calls original Ybp','v2_fix':'Odd final output channel now reads valid o1=o for unused second bias/BW instead of out-of-bounds o+1. Original v1 recipe/runtime/receipt retained under history/packed-v1, full v1 generated source retained privately. No measured data used.','risks':['uncompiled source','native-only new entry lacks all12 proof','Nat-loop/array/preparation overhead','source spelling compaction must elaborate'],'CI_request':'Conditional Droot native-only follow-on; full_gate=false and declares_correct=false mandatory'}
    (P/'packed-support11-v2-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
