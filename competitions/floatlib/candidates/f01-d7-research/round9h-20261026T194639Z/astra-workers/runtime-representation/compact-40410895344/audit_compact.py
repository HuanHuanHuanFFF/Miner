"""Exact compactScales interface and selected-caller audit. No new compilation."""
from pathlib import Path
from collections import Counter
import hashlib,json,re,datetime,importlib.util
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
STAGE=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40410895344/download-9af980463e0648dabd2d03b5c409c96e/diagnostics/f01-d7-public-suite/public-suite'
NAME='f01-r19-dev-compact-scales1';DIAG=STAGE/'diagnostics'/NAME
EXPECTED='9c4e9505702231fdb93f47f8d767ba0b2b0c2ad7ec48d8894b5a53ba87657645'
sha=lambda b:hashlib.sha256(b).hexdigest()
identity=lambda p:{'path':str(p),'bytes':p.stat().st_size,'sha256':sha(p.read_bytes())}
input=STAGE/'inputs'/NAME/'Kernel.lean';frozen=HERE.parent/'Kernel-compact-scales.lean'
assert input.read_bytes()==frozen.read_bytes() and sha(input.read_bytes())==EXPECTED
verdict_path=STAGE/(NAME+'-verdict.json');v=json.loads(verdict_path.read_text())
helper_path=DIAG/'helper-audit.json';h=json.loads(helper_path.read_text())
rawpath=DIAG/'helper-axioms.raw';raw=rawpath.read_bytes()
assert sha(raw)==h['output_sha256'] and h['kernel_sha256']==EXPECTED
assert h['kernel_replay'] and h['accepted'] and h['expected_count']==len(h['reports'])==10
assert all(set(x)<={'propext','Classical.choice','Quot.sound'} for x in h['reports'].values())
eval_lines=[x.strip() for x in raw.decode().splitlines() if x.strip() and 'depends on axioms:' not in x and 'does not depend on any axioms' not in x]
assert eval_lines==['true','512'],eval_lines
assert v['passed'] and v['mode']=='diagnostic-statement-only' and v['stage']=='helper-axioms' and not v['rounds'] and v['ratio'] is None
replay=DIAG/'replay.log';rp=replay.read_text()
assert 'Submission replays cleanly' in rp and 'VerifyFull replays cleanly' in rp
sp=importlib.util.spec_from_file_location('ccompare',HERE.parent/'compare_classifier_codegen.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
sources,cids=m.load(DIAG,EXPECTED);selected=m.select(sources)
def extract_any(text,symbol):
    x=re.search(r'^(?:LEAN_EXPORT |static )?[A-Za-z_][^\n;]*\b'+re.escape(symbol)+r'\([^\n]*\)\s*\{',text,re.M);assert x,symbol
    pos=x.end();depth=1
    while depth:
        if text[pos]=='{':depth+=1
        elif text[pos]=='}':depth-=1
        pos+=1
    return text[x.start():pos],text.count('\n',0,x.start())+1
functions={}
for op in ['add','mul']:
    body=selected[op]['body'];assert body.count('lp_competition_R19CompactScales_valid')==1
    assert 'lean_float_array_data' not in body
    assert '_init_' not in body and 'valid_spec__0(' not in body
    assert body.count('lean_float_array_fget(')==2 and body.count('lean_float_to_float32(')==2
    (HERE/(op+'-selected.c')).write_text(body+'\n',encoding='utf-8')
    functions[op]={'selected':{k:x for k,x in selected[op].items() if k!='body'},'sha256':sha(body.encode()),
      'static_sites':dict(Counter(re.findall(r'\b(lean_\w+)\(',body))),
      'valid_global_reads_C':1,'FloatArray_get_sites':2,'narrow_sites':2,'data_materialize_sites':0,'init_calls':0}
sub=sources['Submission'];main=sources['MainFull']
initnames=['_init_lp_competition_R19CompactScales_packed___closed__1',
 '_init_lp_competition_R19CompactScales_packed___closed__2',
 '_init_lp_competition_R19CompactScales_packed',
 '_init_lp_competition_R19CompactScales_valid___closed__3',
 '_init_lp_competition_R19CompactScales_valid',
 'lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R19CompactScales_packed_spec__0',
 'lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R19CompactScales_valid_spec__0',
 'initialize_competition_Submission']
initrecords=[]
for symbol in initnames:
    body,line=extract_any(sub,symbol)
    (HERE/(symbol+'.c')).write_text(body+'\n',encoding='utf-8')
    initrecords.append({'symbol':symbol,'line':line,'sha256':sha(body.encode()),'static_sites':dict(Counter(re.findall(r'\b(lean_\w+)\(',body)))})
for symbol in ['initialize_competition_MainFull','main','_lean_main']:
    body,line=extract_any(main,symbol);(HERE/(symbol+'.c')).write_text(body+'\n',encoding='utf-8')
    initrecords.append({'symbol':symbol,'line':line,'sha256':sha(body.encode())})
assert main.count('lean_float_array_data')==0
materializers=re.findall(r'^LEAN_EXPORT [^\n]+ (lp_competition___private_Submission_0__FloatArray_\w+splitter\w*)\(',sub,re.M)
matnames=sorted(set(materializers));assert len(matnames)==4
matrefs={n:len(re.findall(r'\b'+re.escape(n)+r'\b',sub)) for n in matnames}
assert all(n==2 for n in matrefs.values()),matrefs
asmindex=DIAG/'native-assembly-index.json';ai=json.loads(asmindex.read_text());asms={}
segments={'add':[(0,0x37),(0x5c,0xe0),(0x172,0x182)],'mul':[(0,0x62),(0x255,0x2d8),(0x3e2,0x3f1)]}
for op in ['add','mul']:
    symbol=selected[op]['unboxed'];row=next(x for x in ai if x.get('symbol')==symbol)
    path=DIAG/row['file'];data=path.read_bytes();assert sha(data)==row['sha256'] and row['kernel_sha256']==EXPECTED
    instr=[]
    for line in data.decode().splitlines():
        q=re.match(r'\s*([0-9a-f]+):\s+([a-z0-9]+)\s*(.*)',line)
        if q and any(lo<=int(q[1],16)<=hi for lo,hi in segments[op]):instr.append({'address':q[1],'op':q[2],'operands':q[3]})
    assert sum(x['op']=='cvtsd2ss' for x in instr)==2
    assert sum(x['op']=='movsd' for x in instr)==2
    assert not [x for x in instr if x['op']=='call']
    assert not [x for x in instr if '[rsp' in x['operands']]
    (HERE/(op+'-compact-accepted.asm.txt')).write_text('\n'.join(x['address']+': '+x['op']+' '+x['operands'] for x in instr)+'\n',encoding='utf-8')
    asms[op]={'binding':row,'accepted_segments':[[hex(x),hex(y)] for x,y in segments[op]],'instructions':instr,
      'condition':'valid=true, both numeric decoder guards accept, result nonNaN; MUL additionally exponent sum>=128. Actual helper eval established globalvalid=true.',
      'scope':'Original diagnostic MainFull, not cleaned timed object; tail toBits mapping from matching C, relocation records absent.'}
runtime=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/lean-object.cpp'
assert sha(runtime.read_bytes())=='b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a'
r={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'COMPACT_INTERFACE_AND_SELECTED_CODEGEN_VERIFIED_NO_TIMING',
 'run':40410895344,'source_commit':'d6b76ba0baa08dd2afa9ab775aee8ee27221feea','kernel_sha256':EXPECTED,
 'identities':[identity(p) for p in [input,verdict_path,helper_path,rawpath,replay,asmindex,runtime]],'C':cids,
 'proof':{'statement':True,'Submission_replay':True,'VerifyFull_replay':True,'ten_allowed_only_roots':True},
 'actual_evaluations':{'R19CompactScales.valid':True,'R19CompactScales.packed.size':512,'raw_remaining_lines':eval_lines},
 'selected_functions':functions,'initializers':initrecords,'unused_materializer_reference_counts':matrefs,'ASM':asms,
 'initialization_boundary':'Submission initializer constructs packed thenvalid before MainFull initializer returns and before lean_run_main/_lean_main/Bench. All static preparation remains present; no per-scalar check/map/data conversion.',
 'retained_initialization_cost':'Original boxed Float32 scaleTable stays persistent. packed.closed1 mapped Array Float is cached by lean_obj_once, whose cold primitive marks it persistent before FloatArray.mk consumes it; its512 boxed Float64 values and pointer array therefore are not freed by mk lean_dec. Packed512-double buffer is additional. All widening/boxing/copy/check/startup cost retained; optimized initialization cycles UNKNOWN.',
 'materialization_scope':'Four generated private match splitters call FloatArray.data, but each appears only as prototype+definition; no call to them and no data materialization in MainFull. Their mere text presence is not a hot-path call.',
 'remaining_cost':'Per native scalar: global flag load/test/branch; two cvtsd2ss on both-table hits; original decoder guards, FP arithmetic, result check/outputcodec, whole fallback, saves/frame retained. No speed inference from fewer pointer loads.',
 'full_gate':'NOT_RUN','performance':'UNKNOWN','candidate_source_changed':False,'new_variant':False,'CI_by_worker':0}
(HERE/'audit.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'proof':'statement+two replays+10roots PASS','eval':eval_lines,'selected':{k:v['selected']['unboxed'] for k,v in functions.items()},'hot_data_materializers':0,'mapped_float64_array_persistent':True,'full_gate':'NOT_RUN','performance':'UNKNOWN'}))
