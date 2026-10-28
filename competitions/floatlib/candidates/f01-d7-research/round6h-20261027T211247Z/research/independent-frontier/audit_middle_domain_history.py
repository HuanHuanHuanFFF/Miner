"""Bind historical ADD joint-domain caller and original full-score evidence."""
from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
B=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40037275281';idx=json.loads((B/'original-artifact-hashes.json').read_bytes());A=B/idx['directory'];pre='diagnostics/f01-d7-public-suite/public-suite/'
checks=[]
def get(name):
 key=pre+name;p=A/key;b=p.read_bytes();h=hashlib.sha256(b).hexdigest();assert h==idx['files'][key]['sha256'];checks.append({'path':str(p.relative_to(R)),'sha256':h,'bytes':len(b)});return json.loads(b)
work=get('public-cell-work.json');cand=get('f01-d11-scalar-normal-band-verdict.json');base=get('f01-r8-combined-result-guard-verdict.json');parent=get('f01-d10-bmm-direct-rows-verdict.json')
assert cand['passed'] and cand['stage']=='score'
def time_sum(v,prefix,field):return sum(work[k]*c[field] for k,c in v['classes'].items() if prefix is None or k.startswith(prefix+':'))
def compare(x,y):
 out={}
 for op in [None,'add','mul','sum','bmm']:
  raw=time_sum(x,op,'submission_ns')/time_sum(y,op,'submission_ns');norm=(time_sum(x,op,'submission_ns')/time_sum(x,op,'incumbent_ns'))/(time_sum(y,op,'submission_ns')/time_sum(y,op,'incumbent_ns'))
  out['whole' if op is None else op]={'raw':raw,'reference_normalized':norm}
 return out
src=R/'competitions/floatlib/candidates/f01-d11-scalar-normal-band/Kernel.lean';sb=src.read_bytes();assert hashlib.sha256(sb).hexdigest()=='e279b35413de1a753dc38edafcca3f476745390ede518ddeab93f0ccc1b8ef1d'
Cpath=D/'historical-e279-MainFull.c';cb=Cpath.read_bytes();assert hashlib.sha256(cb).hexdigest()=='9fb8629f377d79989105422cedc5030dd23283db57eee04bfa167c0addb83542';C=cb.decode()
assert '.m_fun = (void*)lp_competition_main___lam__0___boxed' in C and 'v___f_1020_ = ((lean_object*)(lp_competition_main___closed__1));' in C and 'lp_competition_Bench_Suite_run(v___f_1020_,' in C
start=C.index('LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1_');end=C.index('LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(',start);body=C[start:end]
hstart=body.index('uint32_t v___x_66_;');hend=body.index('return v___x_87_;',hstart)+len('return v___x_87_;');hit=body[hstart:hend]
assert hit.count('lean_uint32_to_float32(')==2 and hit.count('lean_float32_mul(')==2 and hit.count('lean_float32_add(')==1 and hit.count('lean_float32_to_bits(')==1
assert not any(x in hit for x in ['lean_float32_beq','lean_float32_of_bits','lean_uint32_dec_lt','lean_uint32_dec_le'])
(D/'historical-e279-selected-add.c').write_text(body,encoding='utf8',newline='\n');(D/'historical-e279-add-accepted.c').write_text(hit+'\n',encoding='utf8',newline='\n')
# The proposed predicate depends only on E's top two bits; sign and fraction cannot affect bit30.
truth=[]
for a in range(4):
 for b in range(4):
  u=a<<29;v=b<<29
  bit=((u^((u<<1)&0xffffffff))&(v^((v<<1)&0xffffffff))&0x40000000)!=0
  old=((((u&0x7fffffff)-0x20000000)&0xffffffff)|(((v&0x7fffffff)-0x20000000)&0xffffffff))<0x40000000
  expected=a in [1,2] and b in [1,2]
  assert bit==old==expected
  truth.append({'Etop2_A':a,'Etop2_B':b,'joint':bit})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'first_tool_utc':'2026-10-27T22:43:55Z','stage_deadline_utc':'2026-10-27T23:03:55Z','decision':'CLOSE_NO_NEW_ADD_ENTRY_HISTORICAL_MECHANISM_ALREADY_NEGATIVE','source_sha256':hashlib.sha256(sb).hexdigest(),'source_bytes':len(sb),'historical_full_run':40037275281,'historical_statement_C_run':40030324309,'original_C_sha256':hashlib.sha256(cb).hexdigest(),'selected_ADD_chain':'BENCH_PLAN -> closed1 -> main.lam0.boxed -> main.lam0','hit_code_sha256':hashlib.sha256((hit+'\n').encode()).hexdigest(),'hit_mechanism':'two bare tableProduct decodes, native ADD, ofFloat32; both converter eligibility guards and result self-BEq absent in actual selected C','old_guard':'two sign masks, two wrapped subtractions, OR, one compare; optimized scalar ASM not retained','proposed_guard':'two shift-left/xor bit tests, AND and bit30 test, same E64..191 domain. This is a guard-expression change, not a new ADD domain/body or new three-guard deletion. No current machine-cost claim.','top_two_bit_truth_table':truth,'comparison_vs_41':compare(cand,base),'comparison_vs_actual_a066_parent':compare(cand,parent),'checked_original_files':checks,'R19_scope':'aeaae postguard continuation was MUL-only, ADD unchanged there because its same mechanism already existed/tested in R11. B2 MUL decoder parent changed materially; that does not reopen the old ADD arm.','limitations':'Recovered generated C comes from accepted diagnostic statement object, not a retained timed scalar ELF. Whole-score negative and source identity are separately bound. No fresh compile, prototype, full proof or CI. Compiler equivalence of the new bit-expression remains UNKNOWN.'}
(D/'middle-domain-history-audit.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps({'decision':out['decision'],'vs41':out['comparison_vs_41'],'vsParent':out['comparison_vs_actual_a066_parent']}))
