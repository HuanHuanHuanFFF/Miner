from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
B=R/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/ci-runs/40607316341'
idx=json.loads((B/'original-artifact-hashes.json').read_bytes());A=B/idx['directory'];files=[]
pre='diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-multistatic-cost1/'
def read(key):
    b=(A/key).read_bytes();sha=hashlib.sha256(b).hexdigest();assert sha==idx['files'][key]['sha256']
    files.append({'path':str((A/key).relative_to(R)),'sha256':sha,'bytes':len(b)});return b
assembly=read(pre+'native-loop-5.asm.txt').decode();items=json.loads(read(pre+'native-assembly-index.json'))
item=next(x for x in items if x.get('file')=='native-loop-5.asm.txt')
assert item['symbol']=='lp_competition_Submission_R15PackedB2_loop' and item['exit_code']==0
C=read(pre+'runtime-cost/original-statement-Submission.c').decode()
main=read(pre+'runtime-cost/build-product-0-R22MultiStaticCostMain.c').decode()
kernel=read('diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r22-dev-multistatic-cost1/Kernel.lean')
base=(R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert kernel.startswith(base) and hashlib.sha256(kernel).hexdigest()==item['kernel_sha256']
assert '.m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0' in main
assert 'lp_competition_Submission_R15PackedB2_dispatch(v_batch_14554_' in C
assert 'lp_competition_Submission_R15PackedB2_loop(v_n_14269_' in C
m=re.search(r'^0+ <lp_competition_Submission_R15PackedB2_loop>:\n',assembly,re.M);assert m
e=assembly.find('\nDisassembly of section ',m.end());body=assembly[m.start():e]
assert body==(D/'current-b2-pair-loop.asm.txt').read_text()
assert len(re.findall(r'\bmulps\b',body))==1 and len(re.findall(r'\baddps\b',body))==1
assert body.count('R_X86_64_PLT32\tlean_float32_of_bits-0x4')==1
assert re.search(r'189:\s+jne\s+40 ',body)
hot=[]
for line in body.splitlines():
    match=re.match(r'\s*([0-9a-f]+):\s+([a-z][a-z0-9]*)\s*(.*)',line)
    if match and 0x135<=int(match[1],16)<=0x189:hot.append(line)
stores=[x for x in hot if re.search(r'movaps\s+XMMWORD PTR \[rsp',x)]
loads=[x for x in hot if re.search(r'movaps\s+xmm\d+,XMMWORD PTR \[rsp',x)]
assert len(stores)==len(loads)==2
out={'verified_utc':datetime.now(timezone.utc).isoformat(),'state':'CURRENT_B2_NOT_K_UNROLLED; K2_INTERFACE_HOLD',
     'files':files,'actual_object_producer_record':item,
     'backedge':'0x189->0x40 once per k','paired_mulps_sites':1,'paired_addps_sites':1,
     'input_ofBits_sites':1,'normal_per_k_XMM_stores':stores,'normal_per_k_XMM_loads':loads,
     'scope':'Bound diagnostic statement object and selected public BMM call chain; object binary not locally retained/rehashed, not a new gate or cycle profile.',
     'new_K2_Lean_codegen_performance':'NOT_RUN/UNKNOWN','no_new_CI':True}
(D/'pair-k2-source-binding.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({k:out[k] for k in ['state','backedge','paired_mulps_sites','input_ofBits_sites']}))
