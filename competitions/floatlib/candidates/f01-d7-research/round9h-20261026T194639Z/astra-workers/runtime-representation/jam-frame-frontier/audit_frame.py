"""Actual public Jam17 frame/register evidence; no compiler or timing execution."""
from pathlib import Path
import hashlib,json,re,datetime,importlib.util
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=HERE.parents[2]
audit_path=ROUND/'astra-workers/exact-arithmetic/codegen-404042/audit.json'
a=json.loads(audit_path.read_text());sha=lambda b:hashlib.sha256(b).hexdigest()
for r in a['bindings']:
    p=ROOT/r['path'];assert p.stat().st_size==r['bytes'];assert sha(p.read_bytes())==r['sha256']
diag=(ROOT/a['bindings'][0]['path']).parent
sp=importlib.util.spec_from_file_location('ccompare',HERE.parent/'compare_classifier_codegen.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
src,ids=m.load(diag,a['kernel_sha256']);selected=m.select(src)['mul']
assert selected['unboxed']=='lp_competition_main___lam__3'
(HERE/'selected-public-mul.c').write_text(selected['body']+'\n',encoding='utf-8')
asm=(ROOT/a['bindings'][1]['path']).read_text();rows=[]
for line in asm.splitlines():
    v=re.match(r'\s*([0-9a-f]+):\s+([a-z0-9]+)\s*(.*)',line)
    if v:rows.append({'address':int(v[1],16),'hex':v[1],'op':v[2],'operands':v[3]})
segments=[(int(lo,16),int(hi,16)) for lo,hi in a['path_segments_inclusive']]
fast=[r for r in rows if any(lo<=r['address']<=hi for lo,hi in segments)]
def hits(rows,regex,semantic=False):
    return [r for r in rows if (not semantic or r['op'] not in ['push','pop']) and re.search(regex,r['operands'])]
registers={
 'r14':r'\br14(?:d|w|b)?\b','rbp':r'\b(?:rbp|ebp|bp|bpl)\b',
 'r15':r'\br15(?:d|w|b)?\b','r12':r'\br12(?:d|w|b)?\b','rbx':r'\b(?:rbx|ebx|bx|bl|bh)\b'}
usage={k:{'success_semantic_uses':hits(fast,rg,True),'all_semantic_uses':hits(rows,rg,True)} for k,rg in registers.items()}
stack=hits(rows,r'\[rsp');faststack=hits(fast,r'\[rsp');assert not faststack
assert not [r for r in fast if r['op']=='call']
assert not usage['r14']['success_semantic_uses']
trace=diag/'build-trace-0.txt';tr=json.loads(trace.read_text());command=tr['log'][0]['message']
assert 'MainFull.c.o.export' in command and '-O3' in command and '-flto' not in command
r={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'VERIFIED_DIAGNOSTIC_SELECTED_PATH_LIVENESS',
 'kernel_sha256':a['kernel_sha256'],'run':a['run'],'audit_path':str(audit_path),'audit_sha256':sha(audit_path.read_bytes()),
 'selected_C':{'symbol':selected['unboxed'],'sha256':sha(selected['body'].encode()),'bindings':ids},
 'ASM_binding':a['bindings'][1],'object_sha256_recorded':a['actual_object_sha256_reported'],'raw_object_rehashed':False,
 'success_path':fast,'register_usage':usage,'stack_memory_accesses_all':stack,'stack_memory_accesses_success':faststack,
 'compile_command':{'path':str(trace),'sha256':sha(trace.read_bytes()),'command':command,'separate_C_compile_no_LTO_flag':True},
 'observed':['r14 is pushed/popped but has no semantic use on accepted path','rbp holds the shifted second input through early guards; later accepted arithmetic does not use it','r15/r12 store exponents used in the guards and sum; accepted arithmetic no longer uses them after sum setup','rbx stores raw second input and participates in accepted mantissa/sign work','All six rsp+0xc float stores/loads lie outside accepted path; accepted path has no call'],
 'inference':'The frame and at least r14 preservation arise from other paths. Cold fallback inlining plausibly drives long-lived raw-input/exponent register choices, but all five saves being removable is not yet proven.',
 'hypothesis_test':'One ordinary noinline fallback wrapper, preserving guardedMul/guards/arithmetic/value. MainFull C must retain an external direct wrapper call on rejection and omit inlined R19Base.mul body; then inspect actual success path prologue/epilogue and tail miss.',
 'performance':'UNKNOWN; no cycle or whole-gain claim from pushes, body size or static instructions'}
(HERE/'frame-evidence.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'r14_fast_uses':len(usage['r14']['success_semantic_uses']),'cold_stack_memory_sites':len(stack),'fast_call_count':0,'fast_stack_memory_sites':0,'native_no_LTO_flag':True}))
