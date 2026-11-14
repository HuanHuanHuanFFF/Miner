from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
B=R/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/ci-runs/40611570030'
ix=json.loads((B/'original-artifact-hashes.json').read_bytes());A=B/ix['directory'];files=[]
pre='diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-indexed8-cost1/'
def read(key):
    p=A/key;b=p.read_bytes();sha=hashlib.sha256(b).hexdigest();assert sha==ix['files'][key]['sha256']
    files.append({'path':str(p.relative_to(R)),'sha256':sha,'bytes':len(b)});return b
items=json.loads(read(pre+'native-assembly-index.json'))
sym='lp_competition_Submission_R22IndexedResident8_wordLoop___redArg'
item=next(x for x in items if x.get('symbol')==sym)
raw=read(pre+item['file']);assert hashlib.sha256(raw).hexdigest()==item['sha256']
source=read('diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r22-dev-indexed8-cost1/Kernel.lean')
assert hashlib.sha256(source).hexdigest()==item['kernel_sha256']=='8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
asm=raw.decode().split('<'+sym+'>:',1)[1].split('\nDisassembly of section ',1)[0]
assert len(re.findall(r'R_X86_64_PLT32\s+lean_float32_of_bits-0x4',asm))==4
for address in ['10e','115','120','128']:
    assert re.search(r'\n\s*'+address+r':[^\n]*\[rsp',asm)
prep=json.loads(read(pre+'runtime-cost/prepare.json'))
old=prep['original_build_before'];obj=next(v for k,v in old.items() if k.endswith('/ir/Submission.c.o.export'))
assert obj==item['object_sha256']
out={'verified_utc':datetime.now(timezone.utc).isoformat(),'state':'CONDITIONAL_PREMISE_NO_NEW_RUNTIME',
     'files':files,'actual_object_producer_record':item,'decoder_call_sites':4,
     'q_common_stack_sites':['0x10e','0x115','0x120','0x128'],
     'causality':'q is live across possible caller-clobbering calls; unconditional warm stack allocation is observed. Sole causal attribution remains INFERRED, not verified by an ablation.',
     'first_falsifier':'A distinct allfast qualified bare loop still keeps q stack recurrence -> stop before large proof.',
     'new_codegen':'NOT_RUN','new_CI':False,'freeze_isolation':'Only old R15 and released406115 evidence; no new confirmation input/result read.'}
(D/'warm-a-source-binding.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({'verified_files':len(files),'kernel':item['kernel_sha256'],'object':obj,'q_sites':out['q_common_stack_sites']}))
