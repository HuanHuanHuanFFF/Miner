"""Small two-seed generic dot-bank oracle, no Lean/native/benchmark execution."""
from pathlib import Path
import hashlib,importlib.util,json,random
HERE=Path(__file__).resolve().parent;SCALAR=HERE.parent
def load(name,path):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def hash_words(words):
    h=2166136261
    for w in words:h=((h^w)*16777619)&0xffffffff
    return h
def word(rng,lo=116,hi=138):return (rng.getrandbits(1)<<31)|(rng.randint(lo,hi)<<23)|rng.getrandbits(23)
def pair_cache(left,right):
    active=left['has']and right['has'];lo=left['lo']+right['lo']if active else 0;hi=left['hi']+right['hi']if active else 0
    n=len(left['raw']);matched=n==len(right['raw']);normal=left['normal']and right['normal'];finite=left['finite']and right['finite']
    L=(n-1).bit_length()if n>1 else 0
    return {'left':left,'right':right,'lo':lo,'hi':hi,'matched':matched,'normal':normal,'finite':finite,
        'eligible':matched and normal and n<=1<<20 and 48+hi-lo+L<=128}
def main():
    fp=load('bank_fp_model',SCALAR/'portable-f64-dot-model.py');ref=fp.load_ref()
    exact=load('bank_exact_tiered',SCALAR.parent/'development-broad/exact_dot_tiered_model.py')
    cases=[];total_macs=0;trace=hashlib.sha256()
    for seed in (24282601,24282603):
        rng=random.Random(seed)
        for n,m,c in ((32,4,8),(64,6,12),(128,8,16)):
            A=[[word(rng)for _ in range(n)]for _ in range(m)]
            B=[[word(rng)for _ in range(n)]for _ in range(c)]
            A[0]=[0x3f800000 if i%2==0 else 0xbf800000 for i in range(n)]
            A[1]=[0x80000000 for _ in range(n)]
            A[2]=[(0 if i%7==0 else (rng.getrandbits(1)<<31)|((80 if i%2==0 else 180)<<23)|rng.getrandbits(23))for i in range(n)]
            B[0]=[0x3f800000 for _ in range(n)]
            B[1]=[0 for _ in range(n)]
            B[2]=[(rng.getrandbits(1)<<31)|((180 if i%2==0 else 80)<<23)|rng.getrandbits(23)for i in range(n)]
            B[3]=[0x3f800000 if i%2==0 else 0xbf800000 for i in range(n)]
            # Every primary row cache is built once in this model, matching the source boundary.
            ea=[exact.m.prepare_operand(a)for a in A];eb=[exact.m.prepare_operand(b)for b in B]
            fa=[fp.prepare(a)for a in A];fb=[fp.prepare(b)for b in B]
            expected=[];attempts=[];tiers={};accepts=0;reason={}
            for i,a in enumerate(A):
                for j,b in enumerate(B):
                    truth,value=fp.exact_dot(a,b,ref) # one Fraction only for this completed output
                    q,obs=fp.attempt(fa[i],fb[j]);cache=pair_cache(ea[i],eb[j])
                    nz=bool(a)and all(((wa&0x7fffffff)==0 or(wb&0x7fffffff)==0)and bool((wa^wb)>>31)for wa,wb in zip(a,b))
                    control=exact.m.rne(value,nz) # independent rounding, Fraction only per completed output
                    assert truth==control
                    tier='word64'if exact.eligible64(cache)else'word128'if cache['eligible']else'replay'
                    actual=exact.model64(cache)if tier=='word64'else exact.m.native_model(cache)if tier=='word128'else control
                    assert actual==truth
                    if q:assert q==truth
                    assert (q if q else control)==truth # eager uses cached exact fallback
                    assert (q if q else control)==truth # lazy fallback remains inside caller; cost is not modeled
                    expected.append(truth);attempts.append(q);tiers[tier]=tiers.get(tier,0)+1;accepts+=bool(q)
                    reason[obs['reason']]=reason.get(obs['reason'],0)+1
                    trace.update(f'{seed},{n},{i},{j},{truth},{q}\n'.encode())
            assert expected[0]==0 and expected[c]==0x80000000
            assert len(expected)==m*c
            macs=m*c*n;total_macs+=macs
            cases.append({'name':f'bank-s{seed}-n{n}-r{m}-c{c}','group':str(seed),'inner':n,'rows':m,'cols':c,
                'rowsA':A,'rowsB':B,'expected':expected,'expected_fnv32':hash_words(expected),'fast_results_model':attempts,
                'model_observer':{'fp_accepted':accepts,'fp_miss':m*c-accepts,'miss_reasons':reason,'exact_tiers':tiers},
                'frame':{'primary_operand_rows_prepared':m+c,'dot_calls':m*c,'macs':macs,'output_words':m*c,
                    'exact_primary_cache_rows':m+c,'eager_primary_cache_rows':m+c,'eager_underlying_cache_builds':2*(m+c),
                    'lazy_primary_cache_rows':m+c,'lazy_exact_fallback_row_builds':2*(m*c-accepts)},
                'directed_rows':{'A0':'alternating+1/-1','A1':'all-negative-zero','A2':'finite mixed spans+zeros','B0':'all+1','B1':'all+0','B2':'opposed mixed spans','B3':'alternating+1/-1'}})
    assert total_macs==44032 and total_macs<=200000
    source=HERE/'GenericDotBank.lean.inc';raw=source.read_bytes();assert raw.count(b'@[noinline] def')==3
    for name in ('exactBank','eagerBank','lazyBank'):assert ('def '+name+' (rowsA rowsB : Array (Array UInt32)) : Array UInt32').encode()in raw
    assert b'ContractExact'not in raw and b'Kernels'not in raw
    fixtures={'schema':'generic-dot-bank-oracle-v1','status':'UNPROVED_NATIVE_NOT_RUN','seeds':[24282601,24282603],
        'source_sha256':hashlib.sha256(raw).hexdigest(),'total_macs':total_macs,'cases':cases,
        'scope':'Generic all-pairs exact finite dyadic dot research only. No competition matrix/kernel/oldBMM equivalence or score claim. Primary preparation once per input row occurs inside each bank call; output allocation and cache releases are inside that call. Lazy miss fallback retains its full preparation cost.'}
    data=(json.dumps(fixtures,separators=(',',':'))+'\n').encode();p=HERE/'fixtures.json'
    if p.exists():assert p.read_bytes()==data,'Frozen bank fixtures require a new version'
    else:p.write_bytes(data)
    report={'status':'SOURCE_AND_SMALL_EXACT_BANK_MODEL_READY_UNPROVED_NATIVE_COST_NOT_RUN','source_sha256':hashlib.sha256(raw).hexdigest(),
        'source_bytes':len(raw),'fixture_sha256':hashlib.sha256(data).hexdigest(),'fixture_bytes':len(data),'seed_groups':2,'bank_cases':len(cases),
        'dot_outputs':sum(c['rows']*c['cols']for c in cases),'total_macs':total_macs,'trace_sha256':trace.hexdigest(),
        'groups':[{'name':c['name'],'frame':c['frame'],'observer':c['model_observer']}for c in cases],
        'Lean':'NOT_RUN','universal_bank_equivalence':'UNPROVED','native':'NOT_RUN','cost':'NOT_RUN','CI':'NOT_REQUESTED',
        'activation':'Only parent may compile/benchmark if complete Tail pilot is positive and before03:15 runtime freeze. No Bool engine selection in hot dot; selected engine is bound by Root Probe implementation.'}
    root=next(p for p in HERE.parents if(p/'AGENTS.md').is_file());adapter=SCALAR.parent/'development-dot-cost/Adapters.lean.inc'
    assert hashlib.sha256(adapter.read_bytes()).hexdigest()=='4ac3cf62b0a66bcc82acec505e2ee9dc54eb1d507dfd424cb33777cf83e337cf'
    report['prerequisite_adapter']={'path':adapter.relative_to(root).as_posix(),'sha256':hashlib.sha256(adapter.read_bytes()).hexdigest()}
    report['engine_binding']={'namespace':'Submission.R24PortableF64 selected by Root at source composition',
        'original_source':'5bf2a8893b01a5ed44393e80065fbd91e9b3686133e9ddd5d4dfb633379d4d2a',
        'tail_source':'e50bf8769d0bef3cc7883d9c1285fd26439282d7c1fd8c141cb84073f90a7f78','hot_engine_Bool_or_function_argument':False}
    report['whole_frame']='Raw banks in; primary row caches/prep+output allocation+all cache release within call; returned output hash/release must be inside outer timed caller.'
    report['lowest_C_ABI']='three concrete lean_object* return functions, two raw bank object arguments; row preparation outside row-pair loop, concrete prepared callback inside; actual C NOT_RUN'
    report['components']=[{'path':p.relative_to(root).as_posix(),'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()}for p in(source,HERE/'build-fixtures.py',HERE/'fixtures.json',HERE/'README.md')]
    (HERE/'READY.json').write_bytes((json.dumps(report,indent=2)+'\n').encode());print(json.dumps({k:report[k]for k in ('status','source_sha256','source_bytes','fixture_sha256','fixture_bytes','bank_cases','dot_outputs','total_macs')}))
if __name__=='__main__':main()
