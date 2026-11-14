from pathlib import Path
from collections import Counter
import datetime
import hashlib
import importlib.util
import json
import struct
import sys
import time

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
C = HERE.parent/'board-frontier'


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main():
    started=time.perf_counter()
    f=load('r27_word_norm_source',C/'norm_frontier.py')
    c=load('r27_word_typed_cert',HERE/'checked_division_u32_model.py')
    original_guard=f.guard_state
    records=[]
    context={}

    def observe(n,w,gw,bw,b0,S1,dw,cap):
        state,ks=original_guard(n,w,gw,bw,b0,S1,dw,cap)
        if cap==26 and state not in ('row_guard','input_span'):
            sw,mw,iw=f.fields(w);sg,mg,ig=f.fields(gw);sb,mb,ib=f.fields(bw)
            sd,md,idd=f.fields(dw)
            cv=abs(n*sw*(mw<<max(0,iw-b0))-S1)
            denominator=n*md
            r0=(cv%denominator)*mg
            pairs=[('cv',cv),('r0',r0)]
            if state=='inner_fast':
                shift=b0+ig-min(b0+ig,ib+idd)
                pairs.append(('ra',(r0%denominator)<<shift))
            for stage,numerator in pairs:
                assert 0<=numerator<1<<64 and 0<denominator<1<<64
                got,branch=c.proposal_path(numerator,denominator,1.0/float(denominator))
                assert got==divmod(numerator,denominator)
                records.append(dict(**context,n=n,stage=stage,a=numerator,d=denominator,
                                    quotient=numerator//denominator,branch=branch,
                                    current_state=state))
        return state,ks

    f.guard_state=observe
    cells=[]
    seed=27051001
    expected=json.loads((C/'norm-frontier-result.json').read_text())['cells']
    for kind in ('normal','wide','sparse'):
        context.clear();context.update(kind=kind,seed=seed,profile='typical',rows=1)
        i,h,h2=f.dimensions(seed,'typical')
        census=dict(rows=0,stats_fast_nlt256=0,row_lengths=Counter(),ks_distribution=Counter(),
                    **{f'cap{k}':Counter() for k in (8,26,28)})
        x=f.gen(kind,i,seed+999)
        x=f.linear(x,1,i,h,f.weights(kind,seed,1,i,h*i),f.bias(seed,2,h),True)
        x=f.norm(x,1,h,f.scale(seed+3,h),census=census)
        x=f.linear(x,1,h,h2,f.weights(kind,seed,4,h,h2*h),f.bias(seed,5,h2),True)
        x=f.norm(x,1,h2,f.scale(seed+6,h2),f.bias(seed,7,h2),census=census)
        x=f.linear(x,1,h2,10,f.weights(kind,seed,8,h2,10*h2),f.bias(seed,9,10),False)
        digest=hashlib.sha256(b''.join(struct.pack('<I',w) for w in x)).hexdigest()
        prior=next(r for r in expected if r['seed']==seed and r['profile']=='typical' and r['kind']==kind and r['rows']==1)
        assert digest==prior['output_sha256']
        rr=[r for r in records if r['kind']==kind]
        cells.append(dict(**context,shape=[i,h,h2,10],output_sha256=digest,
                          previous_model_hash_matches=True,pairs=len(rr),
                          branches=dict(Counter(r['branch'] for r in rr)),
                          stages=dict(Counter(r['stage'] for r in rr))))
    result=dict(at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                status='EXACT_SEEN_FORMULA_CALL_CENSUS_WITH_FLOAT_PROPOSAL_MODEL_NOT_NATIVE',
                scope='PreviouslyseenCseed27051001 typical rows1 normal/wide/sparse only; no newconfirmationinputs',
                wall_seconds=time.perf_counter()-started,cells=cells,records=records,
                source_hashes={p.name:hashlib.sha256(p.read_bytes()).hexdigest()
                               for p in (Path(__file__),C/'norm_frontier.py',C/'norm-frontier-result.json',
                                         HERE/'checked_division_u32_model.py',HERE/'CheckedFloatDivision.lean')},
                limits=['Formula omits downstream rrsG path, which is untouched',
                        'No native cost, hitrate or speed guarantee',
                        'No Lean/full12 acceptance', 'Counts are not production probabilities'])
    (HERE/'checked-division-norm-census.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(dict(wall_seconds=result['wall_seconds'],cells=cells),indent=2))


if __name__=='__main__':
    main()
