"""Exact c972 statement C/caller audit; no recompilation and no timed-ELF claim."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
DIR=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40182114389/download-735a56e6ace44baba2c4cd4fe7168332/diagnostics/f01-d7-public-suite/public-suite'
DIAG=DIR/'diagnostics/f01-r16-dev-native-repack1'
SHA='c972fd72694d4d7db4660d2dbcd640d766d013d58bd9c9a27a6c68d47010b7ac'

def ident(p):
    b=p.read_bytes(); return {'path':str(p.relative_to(ROOT)),'sha256':hashlib.sha256(b).hexdigest(),'bytes':len(b)}
def body(s,symbol):
    m=re.search(r'^LEAN_EXPORT[^\n]*\b'+re.escape(symbol)+r'\([^;\n]*\)\{',s,re.M); assert m,symbol
    o=s.index('{',m.start()); e=o+1; depth=1
    while depth: depth+=(s[e]=='{')-(s[e]=='}'); e+=1
    return s[m.start():e]+'\n',s.count('\n',0,m.start())+1
def counts(s):
    return {f:len(re.findall(r'\b'+f+r'\(',s)) for f in ['lean_uint32_to_float32','lean_float32_mul','lean_array_fget_borrowed','lean_float32_of_bits','lean_float32_beq','lean_float32_to_bits','lean_alloc_ctor','lean_apply_2','lean_nat_add','lean_nat_mul']}

inputs=[DIR/'inputs/f01-r16-dev-native-repack1/Kernel.lean',HERE/'Kernel-native-repack.lean',ROOT/'competitions/floatlib/candidates/f01-r16-dev-native-repack1/Kernel.lean']
for p in inputs: assert ident(p)['sha256']==SHA
verdict=DIR/'f01-r16-dev-native-repack1-verdict.json'
v=json.loads(verdict.read_bytes()); assert v['passed'] and v['stage']=='statement' and v['mode']=='diagnostic-statement-only'
idx=json.loads((DIAG/'candidate-c-index.json').read_bytes()); src={}; checked=[]
for r in idx:
    p=DIAG/r['file']; i=ident(p); assert i['sha256']==r['sha256'] and r['kernel_sha256']==SHA
    checked.append(i); src[r['module']]=p.read_text(encoding='utf-8')
main,mainline=body(src['MainFull'],'_lean_main')
assert 'v___f_2685_ = ((lean_object*)(lp_competition_main___closed__5))' in main
assert 'lp_competition_Bench_Suite_run(v___f_2684_, v___f_2685_' in main
assert re.search(r'closed__5_value[^\n]*\.m_fun = \(void\*\)lp_competition_main___lam__3___boxed',src['MainFull'])
selected,line=body(src['MainFull'],'lp_competition_main___lam__3')
core,coreline=body(src['Submission'],'lp_competition_Submission_R14ExponentShift_core')
full,linefull=body(src['Submission'],'lp_competition_Submission_mul')
joins=selected[selected.index('v___jp_1402_:\n'):selected.index('v___jp_1441_:\n')]
mid=selected.index('v_mid_2648_ = lean_float32_to_bits')
faststart=selected.rfind('else\n{',0,mid)
fast=selected[faststart:]
assert counts(fast)['lean_float32_mul']==1 and counts(fast)['lean_array_fget_borrowed']==0
assert counts(fast)['lean_uint32_to_float32']==2 and counts(fast)['lean_float32_beq']==0
assert 'lean_float32' not in joins and 'lean_nat' not in fast+joins
assert 'v___x_2650_ = lean_uint32_dec_le(v___x_2649_, v___y_1400_)' in fast
assert 'v___x_2651_ = lean_uint32_dec_le(v___x_2649_, v___y_1401_)' in fast
assert 'v___y_1432_ = v___x_2618_' in fast and 'v___y_1435_ = v___x_2616_' in fast
excerpts=[]
for name,text in [('selected-main-mul.c',selected),('native-core.c',core),('public-mul.c',full),('fast-arm.c',fast),('fast-repack-joins.c',joins),('main-selection.c',main)]:
    p=HERE/('c972-'+name); p.write_bytes(text.encode()); excerpts.append(ident(p))
asmidx=json.loads((DIAG/'native-assembly-index.json').read_bytes()); asm=[]
for r in asmidx:
    p=DIAG/r['file']; assert ident(p)['sha256']==r['sha256']
    if r['kind']=='actual-built-object-disassembly':
        assert r['kernel_sha256']==SHA
        asm.append({'symbol':r['symbol'],'file':str(p.relative_to(ROOT)),'sha256':r['sha256']})
assert not any('main___lam__3' in r['symbol'] or 'ExponentShift_core' in r['symbol'] or r['symbol']=='lp_competition_Submission_mul' for r in asm)
previous_report=HERE/'c972-caller-review.json'
audit_created_at=(json.loads(previous_report.read_bytes())['at_utc'] if previous_report.exists()
                  else datetime.now(timezone.utc).isoformat())
report={'at_utc':audit_created_at,'state':'STATEMENT_PASS_SELECTED_C_CONFIRMED_SCALAR_ASM_MISSING',
  'kernel_sha256':SHA,'run':40182114389,'inputs':[ident(p) for p in inputs],'verdict':ident(verdict),
  'full_gate':False,'kernel_replay_helper_axiom_audit':'NOT_RUN','generated_C':checked,
  'selected_public_path':'BENCH_PLAN present -> Bench.Suite.run closed__5 -> main___lam__3___boxed -> main___lam__3',
  'selected_original_line':line,'selected_body_bytes':len(selected.encode()),'selected_body_sha256':hashlib.sha256(selected.encode()).hexdigest(),
  'selected_whole_body_static_sites':counts(selected),'selected_fast_arm_static_sites':counts(fast),
  'native_core_original_line':coreline,'native_core_static_sites':counts(core),
  'C_proven':['One rounded native product, two numeric casts, zero scale-table reads in reachable eligible arm','No duplicate middleWord evaluation in that arm','Native self-NaN guard removed only from eligible arm','After toBits, selected C still uses original raw u/v for sign tests and precomputed exponent values for repacking','Original normal-input test and exponent-sum wrap guard both precede native arm','Two inlined copies of original fallback appear in different guard-failure branches; fallback native paths retain 3 MUL/2 table reads each'],
  'machine_unknown':['actual tailcall in B2','actual scalar spills/register allocation in c972','whether clang merges the repeated fallback C','selected timed ELF identity','cycle cost/performance'],
  'archived_disassembly_symbols':asm,'scalar_asm_state':'NOT_CAPTURED; only Packed10Index and R15PackedB2 loops were archived',
  'scope':'No compilation, no new CI, no candidate edits, no current confirmation results; only the owner-provided diagnostic-statement archive was read.',
  'excerpts':excerpts}
(HERE/'c972-caller-review.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:report[k] for k in ['state','selected_body_bytes','selected_body_sha256','selected_whole_body_static_sites','selected_fast_arm_static_sites','scalar_asm_state']},indent=2))
