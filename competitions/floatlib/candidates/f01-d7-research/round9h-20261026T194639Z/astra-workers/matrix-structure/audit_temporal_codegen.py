"""Exact c70c diagnostic receipts, selected C chain and saved-object assembly only."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,time
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic();sha=lambda b:hashlib.sha256(b).hexdigest()
root=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40395429076/download-01d3ee43e7ff4ae088ca57488a71a0b2/diagnostics/f01-d7-public-suite/public-suite'
home=root/'diagnostics/f01-r19-dev-temporal-b2-1'
source=root/'inputs/f01-r19-dev-temporal-b2-1/Kernel.lean'
expected='c70cf9479ca48b4690990ebbd0b3781139cbeb94e46b28bbe61563e3eeaced1c'
assert sha(source.read_bytes())==expected and source.read_bytes()==(H/'Kernel-temporal-b2.lean').read_bytes()
verdict_path=root/'f01-r19-dev-temporal-b2-1-verdict.json'
assert sha(verdict_path.read_bytes())=='efa5dc72a18c342504c9c4e3ce83259626a16f7402bd799c0eb68f3b5ad80d04'
verdict=json.loads(verdict_path.read_bytes());assert verdict['passed'] and verdict['diagnostic_only'] and not verdict['rounds']
audit=json.loads((home/'helper-audit.json').read_bytes())
assert audit['kernel_sha256']==expected and audit['accepted'] and audit['kernel_replay'] and audit['exit_code']==0
assert audit['expected_count']==len(audit['reports'])==13
assert set(audit['names'])==set(json.loads((H/'temporal-helper-roots.json').read_bytes())['names'])
assert sha((home/'helper-axioms.raw').read_bytes())==audit['output_sha256']
assert sha((home/'helper-audit-source.lean').read_bytes())==audit['audit_source_sha256']
allowed={'propext','Classical.choice','Quot.sound'}
assert all(set(xs)<=allowed for xs in audit['reports'].values())
replay=(home/'replay.log').read_text()
assert 'Submission replays cleanly' in replay and 'VerifyFull replays cleanly' in replay
assert replay.count('leanchecker exit=0')==2
bindings=[]
for name in ('candidate-c-index.json','native-assembly-index.json'):
 for item in json.loads((home/name).read_bytes()):
  p=home/item['file'];raw=p.read_bytes();assert sha(raw)==item['sha256']
  if 'kernel_sha256' in item:assert item['kernel_sha256']==expected
  bindings.append({'path':str(p.relative_to(R)),'sha256':sha(raw),'bytes':len(raw)})
for p in (source,verdict_path,home/'helper-audit.json',home/'helper-axioms.raw',home/'helper-audit-source.lean',home/'replay.log'):
 bindings.append({'path':str(p.relative_to(R)),'sha256':sha(p.read_bytes()),'bytes':p.stat().st_size})
c=(home/'candidate-generated-0.c').read_text()
assert sha((home/'candidate-generated-0.c').read_bytes())=='a4087dc824db9a8dcb3de54a21b67bc6038028635f5cdbd5aa5e19a6d1cf519e'
def functions(text):
 result={}
 for m in re.finditer(r'^LEAN_EXPORT [^\n]+?\b(lp_competition_\w+)\([^\n]*\)\{',text,re.M):
  start=m.start();end=text.find('{',start)+1;depth=1
  while depth:
   depth+=(text[end]=='{')-(text[end]=='}');end+=1
  result[m[1]]=(start,end,text[start:end])
 return result
fs=functions(c)
selected=['Submission_bmm','Submission_R19Temporal_dispatch','Submission_R19Temporal_output',
 'Fin_foldl_loop___at___00Submission_R19Temporal_output_spec__1',
 'Fin_foldl_loop___at___00Submission_R19Temporal_output_spec__0___redArg',
 'Submission_R19Temporal_packB','Submission_R19Temporal_packB___lam__0',
 'Submission_R19Temporal_pack','Submission_R19Temporal_pack___lam__0',
 'Submission_R19Temporal_loop',
 'Fin_foldl_loop___at___00Submission_R15ThinPairs_output_spec__0',
 'Submission_Packed10_finish','Submission_R7NaNReplay_replayEarly',
 'Submission_R15PackedB2_loop','Submission_R15PackedB2_packB','Submission_R15PackedB2_packB___lam__1']
out=H/'temporal-codegen-evidence';out.mkdir(exist_ok=True);entries=[]
sites=['lean_alloc_ctor(','lean_alloc_closure(','lean_box_float32(','lean_array_fget_borrowed(',
 'lean_float32_of_bits(','lean_nat_add(','lean_nat_mul(','lean_nat_dec_lt(','lean_ctor_get_float32(']
for suffix in selected:
 symbol='lp_competition_'+suffix;begin,end,body=fs[symbol]
 (out/(suffix+'.c.txt')).write_text(body+'\n')
 entries.append({'symbol':symbol,'line_start':c.count('\n',0,begin)+1,'line_end':c.count('\n',0,end)+1,
 'body_sha256':sha(body.encode()),'static_sites':{x:body.count(x) for x in sites},
 'constructor_payloads':re.findall(r'lean_alloc_ctor\(0, 0, (\d+)\)',body),
 'closure_arity_and_captures':re.findall(r'lean_alloc_closure\([^;]+?, (\d+), (\d+)\)',body),
 'direct_calls':sorted(set(re.findall(r'\b(lp_competition_\w+)\(',body))-{symbol}),
 'excerpt':str((out/(suffix+'.c.txt')).relative_to(H))})
def get(s):return fs['lp_competition_'+s][2]
assert get('Submission_R19Temporal_output').count('Submission_R19Temporal_packB(')==1
assert 'Submission_R19Temporal_loop(' in get('Fin_foldl_loop___at___00Submission_R19Temporal_output_spec__0___redArg')
assert 'Submission_R19Temporal_dispatch(' in get('Submission_bmm')
assert 'Submission_R19Temporal_output(' in get('Submission_R19Temporal_dispatch')
prep=get('Submission_R19Temporal_pack___lam__0')
assert set(re.findall(r'lean_alloc_ctor\(0, 0, (\d+)\)',prep))=={'32'}
assert not prep.count('lean_box_float32(')
assert set(re.findall(r'lean_ctor_set_float32\([^,]+, (\d+),',prep))==set(map(str,range(0,32,4)))
assert set(re.findall(r'lean_alloc_ctor\(0, 0, (\d+)\)',get('Submission_R19Temporal_loop')))=={'8'}
assert get('Submission_Packed10_finish').count('Submission_R7NaNReplay_replayEarly(')==1
main=(home/'candidate-generated-1.c').read_text();assert '.m_fun = (void*)lp_competition_Submission_bmm' in main
asm=[]
for filename,symbol,frame in [('native-loop-2.asm.txt','lp_competition_Submission_R15PackedB2_loop','0x48'),('native-loop-3.asm.txt','lp_competition_Submission_R19Temporal_loop','0xc8')]:
 text=(home/filename).read_text();needle='<'+symbol+'>:';begin=text.index(needle);begin=text.rfind('\n',0,begin)+1
 end=text.find('\nDisassembly of section ',begin);body=text[begin:end if end!=-1 else len(text)]
 assert re.search(r'sub\s+rsp,'+frame+r'\b',body)
 target=out/(symbol+'.asm.txt');target.write_text(body)
 asm.append({'symbol':symbol,'source':filename,'body_sha256':sha(body.encode()),'stack_sub_bytes':int(frame,16),'saved_object_sha256':'3c064e376a22c8fb03c90fc12f694af8a033cf49be8707aca7f08b21c98c71bb','excerpt':str(target.relative_to(H))})
newasm=(out/'lp_competition_Submission_R19Temporal_loop.asm.txt').read_text()
oldasm=(out/'lp_competition_Submission_R15PackedB2_loop.asm.txt').read_text()
def instruction(text,offset):
 m=re.search(r'^\s*'+offset+r':\s+(.+)$',text,re.M);assert m;return m[1]
new_store=['1fb','206','211','21c','226','27b','47e','608']
new_load=['5a5','5aa','5af','5b4','5b9','5be','5d0','5e2']
assert all(instruction(newasm,x).startswith('movaps XMMWORD PTR [rsp+') for x in new_store)
assert all(re.match(r'movaps xmm\d+,XMMWORD PTR \[rsp\+',instruction(newasm,x)) for x in new_load)
assert all(instruction(oldasm,x).startswith('movaps XMMWORD PTR [rsp+') for x in ['14a','17d'])
assert all(re.match(r'movaps xmm\d+,XMMWORD PTR \[rsp\+',instruction(oldasm,x)) for x in ['169','175'])
report={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'EXACT_SOURCE_STATEMENT_REPLAY_AXIOMS_AND_SELECTED_CODEGEN_VERIFIED',
 'run':40395429076,'candidate_sha256':expected,'proof':{'statement':True,'Submission_and_VerifyFull_kernel_replay':True,'helper_roots':13,'allowed_axioms_only':True,'full_gate':False,'timing_rounds':0},
 'bindings':bindings,'functions':entries,'assembly':asm,
 'common_small_nat_inbounds_fullblock_stack_traffic':{'old_per_k_XMM_stores':2,'old_per_k_XMM_loads':2,'old_per_four_k_stores':8,'old_per_four_k_loads':8,'new_per_four_k_stores':8,'new_per_four_k_loads':8,'new_store_offsets':new_store,'new_load_offsets':new_load,'scope':'Manually selected normal full-block path only, excluding prologue/tail/big-Nat/default paths. Saved instructions verified, not dynamic profiling; larger stack frame is not more traffic on this path.'},
 'actual_preparation_change':{'old_inner_closure_captures':4,'new_inner_closure_captures':6,'old_outer_closure_captures':5,'new_outer_closure_captures':4,'conditional_extra_closure_bytes_per_tile':16,'conditional_outer_closure_delta_bytes':-8,'scope':'64-bit pointer request model from actual C captures; excludes allocator/capacity/RC and time'},
 'decision':'SUPPORT_ONE_ORIGINAL_FULL_COST_DISCOVERY_FOR_EXACT_C70C; preparation/object and loop representation premises realized, no wrong entry or extra numeric pass found. Net benefit cannot be selected from codegen because guards/closure size/packing control and changed live state compete with fewer packet objects/reads. No 10% prediction, no confirmation eligibility yet.',
 'limits':['Diagnostic object only; current timed binary not supplied','Saved objdump lacks relocations: call targets from offsets alone remain UNKNOWN; the 4 decoder calls per full block are explicit in matching C','No source change or new queue dispatched','Static total call/allocator sites include mutually exclusive tail/default branches and are not dynamic counts'],
 'elapsed_seconds':time.monotonic()-start}
(H/'temporal-codegen-review.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({'state':report['state'],'run':report['run'],'candidate':expected,'proof':report['proof'],'bindings_verified':len(bindings),'functions_extracted':len(entries),'assembly_frames':[x['stack_sub_bytes'] for x in asm],'elapsed_seconds':report['elapsed_seconds']}))
