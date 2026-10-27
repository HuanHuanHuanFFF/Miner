"""Frozen-source diagnostic audit. Reads archived C/asm; writes audit artifacts only."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,time
OUT=Path(__file__).resolve().parent
ROOT=next(p for p in OUT.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic();sha=lambda b:hashlib.sha256(b).hexdigest()
SUITE=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168024176/download-97e5567f5b7c4fc2a261a6d6dac40edc/diagnostics/f01-d7-public-suite/public-suite'
D=SUITE/'diagnostics/f01-r15-dev-packed-b2-1'
OLD=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40166091242/download-28fddc7db9b44ad0af963b3257d6c11f/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r15-dev-column-pairs2'
expected='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
bindings=[]
for p in [SUITE/'inputs/f01-r15-dev-packed-b2-1/Kernel.lean',OUT/'Kernel-b2.lean']:
 b=p.read_bytes();assert sha(b)==expected
 bindings.append({'path':str(p.relative_to(ROOT)),'sha256':sha(b),'bytes':len(b)})
indexb=(D/'candidate-c-index.json').read_bytes();index=json.loads(indexb)
sources={}
for item in index:
 p=D/item['file'];b=p.read_bytes();assert sha(b)==item['sha256'] and item['kernel_sha256']==expected
 sources[item['module']]=(b.decode(),str(p.relative_to(ROOT)),sha(b))
 bindings.append({'path':str(p.relative_to(ROOT)),'sha256':sha(b),'bytes':len(b),'scope':item['scope']})
oldib=(OLD/'candidate-c-index.json').read_bytes();oldidx=json.loads(oldib);oldbytes=(OLD/'candidate-generated-0.c').read_bytes()
assert sha(oldbytes)==oldidx[0]['sha256']=='6641958150656005350082b2df705f35a234a9eb591e23cf0d822e062f2e40be'
assert oldidx[0]['kernel_sha256']=='b116067185626ccb758fbadd608ce7514cb1ddef70ddd0a07e1596f8c776952b'
vb=(SUITE/'f01-r15-dev-packed-b2-1-verdict.json').read_bytes();v=json.loads(vb)
assert sha(vb)=='da5e598636e33446cb653e9f552c3e9ed4643debb939146fbd5652eec66588b8'
assert v['passed'] and v['mode']=='diagnostic-statement-only' and v['stage']=='statement' and v['rounds']==[]
summary=json.loads((SUITE/'summary.json').read_bytes())
assert summary['source_commit']=='9fd0c42405e830cf76a87959d8bf1a4648b1dc98' and summary['seed']==1526006
asmib=(D/'native-assembly-index.json').read_bytes();asmi=json.loads(asmib)
ai=next(x for x in asmi if x.get('symbol')=='lp_competition_Submission_R15PackedB2_loop')
asmb=(D/ai['file']).read_bytes();assert sha(asmb)==ai['sha256']=='5fd2b8a7f3674d23140d7b49516e9665d0f6c6880c3077e30802dc6144329eb9'
trace=(D/'build-trace-3.txt').read_bytes();tracej=json.loads(trace)
assert sha(trace)==next(x['sha256'] for x in asmi if x.get('file')=='build-trace-3.txt')
assert 'lean4---v4.34.0' in trace.decode() and '-ffp-contract=off' in trace.decode()
def fn(text,symbol):
 ms=list(re.finditer(r'^LEAN_EXPORT [^\n]*\b'+re.escape(symbol)+r'\([^\n]*\)\{',text,re.M));assert len(ms)==1,(symbol,len(ms))
 a=ms[0].start();z=ms[0].end();depth=1
 while depth:
  if text[z]=='{':depth+=1
  elif text[z]=='}':depth-=1
  z+=1
 return text[a:z],text[:a].count('\n')+1,text[:z].count('\n')+1
c=sources['Submission'][0];main=sources['MainFull'][0]
P='lp_competition_Submission_R15PackedB2_'
symbols=[P+'packB___lam__0',P+'packB___lam__0___boxed',P+'packB___lam__1',P+'packB',P+'loop',P+'tileIndex___redArg',
 'lp_competition_Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__0___redArg',
 'lp_competition_Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__1',P+'output',P+'dispatch',
 'lp_competition_Submission_bmm','lp_competition_Fin_foldl_loop___at___00Submission_R15ThinPairs_output_spec__0']
records=[];bodies={}
tokens=['lean_alloc_ctor(','lean_box_float32(','lean_unbox_float32(','lean_ctor_get_float32(','lean_ctor_set_float32(','lean_float32_of_bits(',
 'lean_array_fget_borrowed(','lean_array_get_size(','lean_nat_mul(','lean_nat_div(','lean_nat_mod(','lean_nat_add(',
 'lean_alloc_closure(','lean_inc_ref(','lean_dec_ref(','lean_float32_mul(','lean_float32_add(']
extracts=OUT/'C-audit-401680';extracts.mkdir(exist_ok=True)
for s in symbols:
 body,lo,hi=fn(c,s);bodies[s]=body
 short=s.replace('lp_competition_','')
 (extracts/(short+'.txt')).write_bytes(body.encode())
 records.append({'symbol':s,'line_start':lo,'line_end':hi,'body_sha256':sha(body.encode()),'prototype':body.splitlines()[0],
                 'static_sites':{t:body.count(t) for t in tokens},'direct_competition_calls':sorted(set(re.findall(r'\b(lp_competition_[A-Za-z0-9_]+)\(',body))-{s})})
oldbody,oldlo,oldhi=fn(oldbytes.decode(),'lp_competition_Submission_R15ThinPairs_loop')
(extracts/'parent-b116-ThinPairs-loop.txt').write_bytes(oldbody.encode())
oldstats={t:oldbody.count(t) for t in tokens}
nb=bodies[P+'loop'];newstats={t:nb.count(t) for t in tokens}
assert nb.count('lean_alloc_ctor(')==1 and 'lean_alloc_ctor(' not in nb.split('else',1)[1]
assert 'lean_alloc_ctor(0, 0, 8)' in nb and nb.count('lean_ctor_get_float32(')==2 and nb.count('lean_box_float32(')==0
pack=bodies[P+'packB___lam__0'];assert pack.count('lean_alloc_ctor(0, 0, 8)')==1 and pack.count('lean_ctor_set_float32(')==2 and 'lean_box_float32(' not in pack
assert not any(t in pack for t in ['lean_nat_div(','lean_nat_mod('])
tile=bodies[P+'packB___lam__1'];assert tile.count('lean_nat_div(')==tile.count('lean_nat_mod(')==1
assert bodies[P+'output'].count(P+'packB(')==1
assert P+'output(' in bodies[P+'dispatch'] and P+'dispatch(' in bodies['lp_competition_Submission_bmm']
assert '.m_fun = (void*)lp_competition_Submission_bmm' in main
assert 'lp_competition_main___closed__4' in fn(main,'_lean_main')[0]
assert P+'loop(' in bodies['lp_competition_Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__0___redArg']
assert 'Packed10_finish(' in bodies['lp_competition_Fin_foldl_loop___at___00Submission_R15ThinPairs_output_spec__0']
assert all('mapMUnsafe' not in bodies[s] for s in symbols if s!= 'lp_competition_Submission_bmm')
asm=asmb.decode();a=asm.index('0000000000000000 <lp_competition_Submission_R15PackedB2_loop>:');z=asm.index('\nDisassembly of section',a)
loopasm=asm[a:z];(extracts/'B2-loop-diagnostic.asm.txt').write_bytes(loopasm.encode())
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'EXACT622D_STATEMENT_C_AUDIT_COMPLETE_NO_RUNTIME_MUTATION',
 'run':40168024176,'source_commit':summary['source_commit'],'plan_seed':1526006,'statement_verdict_seed':v['seed'],
 'candidate_sha256':expected,'bindings':bindings,'candidate_c_index_sha256':sha(indexb),'statement_verdict_sha256':sha(vb),
 'statement_pass':True,'full_gate':'NOT_RUN_OBSERVED','paired_timing':'NOT_RUN_OBSERVED','actual_timed_object':'UNKNOWN_NOT_PROVIDED',
 'mainfull_binding':{'sha256':sources['MainFull'][2],'closure_line':main[:main.index('static const lean_closure_object lp_competition_main___closed__4_value')].count('\n')+1,'_lean_main_lines':fn(main,'_lean_main')[1:3],
  'route':'main closed__4 points to Submission_bmm and is passed to both Bench_runFull and Bench_Suite_run; compiled BMM guard selects B2 only after underflow miss and2<=p<=8,n>1,m>=4. No dynamic timed path counts were collected.'},
 'functions':records,'parent_comparison':{'run':40166091242,'kernel_sha256':oldidx[0]['kernel_sha256'],'c_sha256':sha(oldbytes),
  'prototype':oldbody.splitlines()[0],'line_start':oldlo,'line_end':oldhi,'old_static_sites':oldstats,'new_static_sites':newstats,
  'limit':'Static C sites/prototypes, not ns, executed counts or causal speedup. Original failed first-D remains unchanged.'},
 'observed_representation':{'prepared_record_scalar_bytes':8,'prepared_field_offsets':[0,4],'per_field_Float32_box_sites':0,
  'B2_prepare_calls_in_active_output':1,'tile_div_mod_outside_inner_k':True,'one_borrowed_prepared_record_read_per_loop_source_step':True,
  'F2_return_constructor':'Only terminal C branch; no F2 ctor in recursive branch. Nat/foreign helpers may have other costs.'},
 'residual_costs':['Two Array.ofFn levels, outer closure fixed5 fields and per-tile inner closure fixed4 fields; sizes/lifetimes charged.',
  'Preparation still performs k*p once and base+1 in inner callback, two getD bounds/default paths and two native conversions, including unobserved odd tail.',
  'Active pair group still computes row/m, row*n, raw baseB and tileIndex per pair; output loop reuses shared ThinPairs emitter, not old ThinPairs numeric/map path.',
  'Both lane emit branches release result F2 after1/2outputs; output releases preparedB/rawB after row fold. External Array.ofFn/recursive final frees not captured as allocator lifetimes.',
  'A remains raw-decoded each k. Diagnostic asm has a common-path call at0x151 and stack traffic at0x14a/0x169/0x175/0x17d; no no-spill claim.'],
 'diagnostic_assembly':{'index_sha256':sha(asmib),'file_sha256':sha(asmb),'object_sha256_from_index':ai['object_sha256'],
  'scope':ai['scope'],'function_byte_size':'UNKNOWN; saved disassembly does not include raw instruction bytes or a symbol-size record',
  'two_field_load':'0x140 record pointer then0x145 movsd8B payload','arithmetic':['0x172 mulps','0x17a addps'],
  'stack_locations':['0x14a stores B vector at rsp+0x20','0x169 reloads B vector','0x175 loads accumulators from rsp+0x30','0x17d stores updated accumulators'],
  'call_target_limit':'Saved disassembly has unresolved call addresses without relocation names. Association of0x151 with raw conversion is inferred from matching C order, not a named relocation.',
  'terminal':'0x24f sets argument0x10 before0x254call, then0x270 stores low8B result. C independently identifies terminal ctor8B scalar payload.',
  'timed_object_and_actual_spill_cost':'UNKNOWN; this is separately captured diagnostic statement replay object'},
 'build_trace_sha256':sha(trace),'compiler_command':tracej['log'][0]['message'],
 'elapsed_seconds':time.monotonic()-start}
assert receipt['elapsed_seconds']<5
(OUT/'b2-C-audit-401680.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'state':receipt['state'],'candidate_sha256':expected,'functions':len(records),
 'loop_old_new_sites':{t:[oldstats[t],newstats[t]] for t in ['lean_array_fget_borrowed(','lean_array_get_size(','lean_nat_mul(','lean_nat_add(','lean_unbox_float32('] if t in oldstats},'elapsed_seconds':receipt['elapsed_seconds']}))
