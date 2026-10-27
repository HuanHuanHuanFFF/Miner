"""Read exact completed R16 C evidence; bounded extraction, no compilation/timing."""
from pathlib import Path
from datetime import datetime,timezone
import json,re,hashlib,time
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic()
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40185444601'
DOWN=RUN/'download-c771d48102cb40c88dd116e5043790ce'
SUITE=DOWN/'diagnostics/f01-d7-public-suite/public-suite'
DIAG=SUITE/'diagnostics/f01-r16-dev-a4b2-entry3'
SHA='2a937bb02ece438cb129e65f7e18ce6c7b30658fcdf5f8a204e8da9208a4afc6'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
rawindex=json.loads((RUN/'original-artifact-hashes.json').read_text())['files']
bindings=[]
def bind(p):
 h=sha(p);rel=p.relative_to(DOWN).as_posix()
 assert rawindex[rel]['sha256']==h
 bindings.append(dict(path=str(p.relative_to(ROOT)),sha256=h,bytes=p.stat().st_size))
 return h
assert bind(SUITE/'inputs/f01-r16-dev-a4b2-entry3/Kernel.lean')==SHA
assert sha(ROOT/'competitions/floatlib/candidates/f01-r16-dev-a4b2-entry3/Kernel.lean')==SHA
for p in (DIAG/'candidate-c-index.json',DIAG/'native-assembly-index.json',DIAG/'diagnostic-only-verdict.json',SUITE/'f01-r16-dev-a4b2-entry3-verdict.json'):bind(p)
ci=json.loads((DIAG/'candidate-c-index.json').read_text())
for x in ci:
 assert x['kernel_sha256']==SHA and bind(DIAG/x['file'])==x['sha256']
ai=json.loads((DIAG/'native-assembly-index.json').read_text())
for x in ai:
 assert bind(DIAG/x['file'])==x['sha256']
 if 'kernel_sha256'in x:assert x['kernel_sha256']==SHA
assert json.loads((DIAG/'diagnostic-only-verdict.json').read_text())['passed']
discovery=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40183711165'
dp=list(discovery.glob('download-*/diagnostics/f01-d7-public-suite/public-suite'))
assert len(dp)==1
assert sha(dp[0]/'inputs/f01-r16-dev-a4b2-entry3/Kernel.lean')==SHA
dv=dp[0]/'f01-r16-dev-a4b2-entry3-verdict.json';d=json.loads(dv.read_text())
assert d['passed'] and d['mode']=='gate' and len(d['rounds'])==25
text=(DIAG/'candidate-generated-0.c').read_text();lines=text.splitlines(keepends=True)
names={}
for i,line in enumerate(lines):
 m=re.match(r'(?:LEAN_EXPORT |static )?[^;\n]*\b([A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\{\s*$',line)
 if not m:continue
 depth=0
 for j in range(i,len(lines)):
  depth+=lines[j].count('{')-lines[j].count('}')
  if depth==0:break
 names[m.group(1)]=(i+1,j+1,''.join(lines[i:j+1]))
prefix='lp_competition_'
selected=['Submission_bmm','Submission_R16A4B2_dispatch','Submission_R16A4B2_core___redArg',
 'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__5',
 'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__3___redArg',
 'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__3___redArg___lam__0',
 'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__3___redArg___lam__0___boxed',
 'Submission_R16A4B2_runDot___redArg','Submission_R16A4B2_wordLoop___redArg',
 'Submission_R16A4B2_packA','Submission_R16A4B2_packA___lam__0','Submission_R16A4B2_packA___lam__0___boxed',
 'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__2',
 'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__1',
 'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__0',
 'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__4___redArg',
 'Submission_R15PackedB2_loop',
 'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__0___redArg',
 'Fin_foldl_loop___at___00Submission_R15ThinPairs_output_spec__0']
out=HERE/'cost-review-401854-excerpts';out.mkdir(exist_ok=True)
tokens=['lean_float32_of_bits','lean_alloc_ctor','lean_box_float32','lean_apply','lean_alloc_closure','l_Array_ofFn','lean_nat_mul','lean_nat_add','lean_nat_dec_eq','lean_nat_dec_lt','lean_nat_div','lean_array_uget_borrowed','lean_array_fget_borrowed','lean_array_get_size','lean_ctor_get_float32','lean_dec_ref','lean_inc_ref','lean_float32_mul','lean_float32_add']
functions=[]
for short in selected:
 name=prefix+short;lo,hi,body=names[name]
 p=out/(short+'.txt');p.write_text(body)
 functions.append(dict(symbol=name,line_start=lo,line_end=hi,body_sha256=hashlib.sha256(body.encode()).hexdigest(),
  prototype=body.splitlines()[0],static_sites={t:body.count(t+'(') if t!='lean_apply' else len(re.findall(r'\blean_apply_\d+\(',body)) for t in tokens},
  calls=sorted(set(re.findall(r'\b(lp_competition_[A-Za-z0-9_]+)\(',body)[1:])),excerpt=str(p.relative_to(HERE))))
word=names[prefix+'Submission_R16A4B2_wordLoop___redArg'][2]
hot=word.split('else\n{',1)[1]
assert hot.count('lean_array_uget_borrowed(')==2
assert hot.count('lean_float32_mul(')==8 and hot.count('lean_float32_add(')==8
for token in ('lean_nat_','lean_alloc_','lean_float32_of_bits','lean_box_','lean_apply_','lean_dec','lean_inc','lp_competition_'):assert token not in hot
assert 'lean_alloc_ctor(0, 0, 32)' in word
pack=names[prefix+'Submission_R16A4B2_packA___lam__0'][2]
assert pack.count('lean_float32_of_bits(')==4 and 'lean_alloc_ctor(0, 0, 16)'in pack
assert 'lean_box_float32('not in pack
block=names[prefix+'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__3___redArg'][2]
assert block.count('Submission_R16A4B2_packA(')==1
assert block.index('Submission_R16A4B2_packA(')<block.index('l_Array_ofFn___redArg(')<block.index('R16A4B2_core_spec__2(')
emit=names[prefix+'Fin_foldl_loop___at___00Submission_R16A4B2_core_spec__0'][2]
assert 'wordLoop'not in emit and 'runDot'not in emit and 'lean_box_float32'not in emit and 'lean_apply'not in emit
old=ROOT/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/matrix-structure/C-audit-401680'
prior=[]
for short in selected[-3:]:
 p=old/(short+'.txt');a=p.read_text();b=names[prefix+short][2]
 prior.append(dict(symbol=prefix+short,old_path=str(p.relative_to(ROOT)),old_sha256=sha(p),
   exact_text_equal=a==b,normalized_variable_equal=re.sub(r'_\d+_', '_N_',a).rstrip()==re.sub(r'_\d+_', '_N_',b).rstrip(),
   normalization='SSA numeric identifiers and trailing excerpt newlines only'))
main=(DIAG/'candidate-generated-1.c').read_text().splitlines()
main_refs=[dict(line=i+1,text=s) for i,s in enumerate(main) if 'Submission_bmm'in s or 'main___closed__4'in s or 'Bench_runFull('in s or 'Bench_Suite_run('in s]
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='EXACT_ACTIVE_C_COST_REVIEW',run=40185444601,kernel_sha256=SHA,
 bindings=bindings,discovery=dict(run=40183711165,source_sha256=sha(dp[0]/'inputs/f01-r16-dev-a4b2-entry3/Kernel.lean'),verdict_sha256=sha(dv),passed=True,rounds=25,relative_whole=1.0078502102726012,relative_bmm=1.043437385237051,qualifies=False),
 functions=functions,mainfull_refs=main_refs,prior_B2_comparison=prior,
 actual_new_wordLoop_assembly_available=any('R16A4B2'in x.get('symbol','') for x in ai),
 asm_limit='Selector captured only old Packed10Index and B2 fallback; A4B2 SIMD, spills, final instruction counts remain UNKNOWN. Saved objects are diagnostic, not timed gate objects.',
 hot_C_verified=dict(two_borrowed_reads=True,eight_ordered_mul_add_pairs=True,raw_conversion=False,Nat=False,allocation=False,RC=False,indirect_apply=False,terminal_F8_payload_bytes=32),
 new_prep_C_verified=dict(A4_payload_bytes=16,per_field_float_box=False,four_conversions=True,four_getD_bounds=True,two_Nat_multiplications_per_packet=True,packA_once_per_block=True),
 elapsed_seconds=time.monotonic()-start,scope='Static C and completed discovery only; dynamic attribution UNKNOWN; no new source/compile/CI/timing')
assert time.monotonic()-start<4.5
(HERE/'cost-review-401854.json').write_text(json.dumps(record,indent=2)+'\n')
print(json.dumps(dict(status=record['state'],functions=len(functions),bindings=len(bindings),new_asm=record['actual_new_wordLoop_assembly_available'],prior=prior,seconds=record['elapsed_seconds'])))
