from pathlib import Path
from datetime import datetime,timezone
import re,json,hashlib
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
B=R/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/ci-runs/40607316341'
index=json.loads((B/'original-artifact-hashes.json').read_bytes());A=B/index['directory'];files=[]
pre='diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-multistatic-cost1/runtime-cost/'
def read(key):
    b=(A/key).read_bytes();sha=hashlib.sha256(b).hexdigest();assert sha==index['files'][key]['sha256']
    files.append({'path':str((A/key).relative_to(R)),'sha256':sha,'bytes':len(b)});return b
C=read(pre+'build-product-0-R22MultiStaticCostMain.c').decode()
ASM=read(pre+'own-object-0-asm.txt').decode();caller=read(pre+'caller.lean').decode()
kernel=read('diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r22-dev-multistatic-cost1/Kernel.lean')
base=(R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert hashlib.sha256(base).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert kernel.startswith(base)
assert '@[noinline] def runControl : IO UInt32' in caller
assert 'v___f_2386_ = ((lean_object*)(lp_competition_runControl___closed__1));' in C
assert 'lp_competition_Bench_Suite_run(v___f_2385_, v___f_2386_,' in C
assert '.m_fun = (void*)lp_competition_runControl___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0' in C
sym='lp_competition_runControl___lam__1'
m=re.search(r'^0+ <'+sym+r'>:\n',ASM,re.M);assert m
end=ASM.find('\nDisassembly of section ',m.end());body=ASM[m.start():end]
assert re.search(r'bf:\s+imul\s+rdi,rax',body)
assert re.search(r'2d3:\s+cmp\s+edx,0x56',body)
assert re.search(r'2ad:\s+mulss\s+xmm1,xmm0',body)
assert body==(D/'early-extreme-control-mul.asm.txt').read_text()
cm=re.search(r'LEAN_EXPORT uint32_t '+sym+r'\([^\n]*\)\{',C);assert cm
depth=1;j=cm.end()
while depth:
    if C[j]=='{':depth+=1
    elif C[j]=='}':depth-=1
    j+=1
(D/'early-extreme-control-mul.c').write_text(C[cm.start():j]+'\n')
out={'verified_utc':datetime.now(timezone.utc).isoformat(),'run':40607316341,'files':files,
     'chain':'runControl -> closed1 -> runControl.lam1.boxed -> runControl.lam1',
     'source':'Combined diagnostics source with exact B2 prefix and unchanged four public operations',
     'actual_work':'Low branch performs imul0xbf before scale-shortcut0x2d3/RSE0x2f6; high finite branch uses table decode0x1eb/0x284 and mulss0x2ad.',
     'new_fragment':'Runtime-extreme-cold-mul.lean.inc','new_codegen':'UNKNOWN','new_cost':'UNKNOWN',
     'scope':'Actual selected static control callback, no isolated leaf substituted and no cycle attribution. No new CI.'}
(D/'scalar-extreme-control-binding.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({'files_verified':len(files),'run':out['run'],'chain':out['chain']}))
