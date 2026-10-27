"""Final bounded exact-source C audit; no compilation, candidate mutation or CI."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'AGENTS.md').exists())
D=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40189703522/download-6480abc393984675972cc19005e1e7f9/diagnostics/f01-d7-public-suite/public-suite'
P=D/'diagnostics/f01-r16-dev-native-add-high3';SHA='f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd'
def identity(p):
 b=p.read_bytes();return {'path':str(p.relative_to(R)),'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()}
def body(s,symbol):
 m=re.search(r'^LEAN_EXPORT[^\n]*\b'+re.escape(symbol)+r'\([^;\n]*\)\{',s,re.M);assert m,symbol
 e=s.index('{',m.start())+1;depth=1
 while depth:depth+=(s[e]=='{')-(s[e]=='}');e+=1
 return s[m.start():e]+'\n',s.count('\n',0,m.start())+1
ip=D/'inputs/f01-r16-dev-native-add-high3/Kernel.lean';assert identity(ip)['sha256']==SHA
idx=json.loads((P/'candidate-c-index.json').read_bytes());sources={}
for x in idx:
 p=P/x['file'];assert identity(p)['sha256']==x['sha256'] and x['kernel_sha256']==SHA
 sources[x['module']]=(p,p.read_text())
s=sources['MainFull'][1];main,_=body(s,'_lean_main')
m=re.search(r'lp_competition_Bench_Suite_run\((\w+),',main);assert m
arg=m.group(1)
closure=re.search(re.escape(arg)+r' = \(\(lean_object\*\)\((\w+)\)\)',main).group(1)
boxed=re.search(re.escape(closure)+r'_value[^\n]*\.m_fun = \(void\*\)(\w+)',s).group(1)
symbol=boxed.removesuffix('___boxed');selected,line=body(s,symbol)
assert symbol=='lp_competition_main___lam__2' # Derived above, not assumed for selection.
assert 'v___x_1756_ = lean_uint32_to_float32(v___y_1745_);\nv_mid_1757_ = lean_float32_to_bits(v___x_1756_);' in selected
assert selected.count('v_mid_1757_ = lean_float32_to_bits(')==1
counts={f:len(re.findall(r'\b'+f+r'\(',selected)) for f in ['lean_uint32_to_float32','lean_float32_to_bits','lean_float32_add','lean_float32_mul','lean_array_fget_borrowed','lean_alloc_ctor','lean_alloc_closure','lean_apply_2']}
nat_calls=sorted(set(re.findall(r'\b(lean_nat_\w+)\(',selected)))
alloc_calls=sorted(set(re.findall(r'\b(lean_alloc_\w+)\(',selected)))
apply_calls=sorted(set(re.findall(r'\b(lean_apply_\w+)\(',selected)))
assert not nat_calls and not alloc_calls and not apply_calls
sort_sites=[1918,1901,1835,1827,1814,1800,1766,1743]
for v in sort_sites:assert re.search(r'v___x_'+str(v)+r'_ = lean_uint32_dec_lt\(',selected)
asm=[]
for x in json.loads((P/'native-assembly-index.json').read_bytes()):
 assert identity(P/x['file'])['sha256']==x['sha256']
 if x['kind']=='actual-built-object-disassembly':asm.append(x['symbol'])
assert all(symbol not in x and 'R16AddWord' not in x and not x.endswith('Submission_add') for x in asm)
(H/'final-selected-ADD.c').write_bytes(selected.encode())
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'EXACT_F7F_SELECTED_ADD_C_REVIEW_COMPLETE',
 'input':identity(ip),'C_sources':[identity(p) for p,s in sources.values()],
 'selection':{'BENCH_PLAN_argument':arg,'closure':closure,'boxed':boxed,'unboxed':symbol,'original_line':line},
 'selected_C_bytes':len(selected.encode()),'selected_C_sha256':hashlib.sha256(selected.encode()).hexdigest(),
 'whole_body_static_sites':counts,'Nat_calls':nat_calls,'allocation_calls':alloc_calls,'closure_apply_calls':apply_calls,
 'eligible_arm':{'native_casts':1,'toBits_calls':1,'native_float_add_mul':0,'scale_table_reads':0,'magnitude_evaluations_on_path':1,
 'same_sign_accepted_path_repeated_exponent_order_compare_C_sites':sort_sites,
 'toBits_postwork':'Re-extract both original input exponents and compare to select low exponent; E guard; re-extract/compare again to select high input sign; repack. Original u/v remain live across call.'},
 'fallback':'Four static inlined fallback ADD copies at distinct rejection paths; at most one fallback executes per call. Late E rejection pays conversion/toBits before fallback. No evidence of repeated fallback execution.',
 'scalar_ASM':'NOT_CAPTURED; archived symbols are matrix loops only','archived_ASM_symbols':asm,
 'limitations':'Generated C is not instruction/cycle attribution or timed ELF identity. Clang CSE, branch lowering, spills, machine code size and dominant cycle cost UNKNOWN. No new experiment or source change.'}
(H/'final-C-cost.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'selection':out['selection'],'bytes':out['selected_C_bytes'],'sha256':out['selected_C_sha256'],'sites':counts,'Nat':nat_calls,'alloc':alloc_calls,'apply':apply_calls},indent=2))
