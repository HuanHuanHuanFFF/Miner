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
HERE=Path(__file__).resolve().parent
C=HERE.parent/'board-frontier'


def metadata(words):
    low_raw=0xffffffff
    high_raw=0
    finite=True
    decoded=[]
    for w in words:
        a=w&0x7fffffff
        low_raw=min(low_raw,(a-1)&0xffffffff)
        high_raw=max(high_raw,a)
        e=(w>>23)&255
        m=(w&0x7fffff)+(0x800000 if e else 0)
        decoded.append((-1 if w>>31 else 1,m,max(0,e-1)))
        finite=finite and e!=255
    lo=max(0,(low_raw>>23)-1)
    hi=max(0,(high_raw>>23)-1)
    values=[s*(m<<max(0,i-lo)) for s,m,i in decoded]
    aligned=all(m==0 or lo<=i for _,m,i in decoded)
    return dict(base=lo,upper=hi,span=max(0,hi-lo),reversed=hi<lo,finite=finite,
                aligned=aligned,strict_factor32=all(-(1<<31)<v<(1<<31) for v in values),
                maximum=max(map(abs,values),default=0))


def main():
    started=time.perf_counter()
    spec=importlib.util.spec_from_file_location('r27_word_model_parent',C/'norm_frontier.py')
    f=importlib.util.module_from_spec(spec);spec.loader.exec_module(f)
    original_linear=f.linear
    rows_out=[]
    context={}
    layer=0

    def observe(x,rows,k,out,w,b,relu):
        nonlocal layer
        assert time.perf_counter()-started<20, '20second local discriminator budget'
        layer+=1
        xa=[metadata(x[i*k:(i+1)*k]) for i in range(rows)]
        wa=[metadata(w[j*k:(j+1)*k]) for j in range(out)]
        counts=Counter();active_x=set();active_w=set()
        for i,a in enumerate(xa):
            for j,z in enumerate(wa):
                counts['pairs']+=1
                body=(k<=1<<20 and a['finite'] and z['finite'] and a['aligned'] and z['aligned']
                      and a['strict_factor32'] and z['strict_factor32']
                      and a['maximum']*z['maximum']<1<<59)
                span=(body and not a['reversed'] and not z['reversed']
                      and a['span']<=7 and z['span']<=7 and a['span']+z['span']<=11)
                sw,mb,ib=f.fields(b[j]);finite_bias=((b[j]>>23)&255)!=255
                bs=a['base']+z['base']
                int_bias=finite_bias and (mb==0 or bs<=ib+149)
                yl_bias=finite_bias and (mb==0 or bs<=ib+126<bs+128)
                counts['body_block']+=body
                counts['body_span_sufficient']+=span
                counts['body_and_int_bias']+=body and int_bias
                counts['body_and_YL_bias']+=body and yl_bias
                if body and yl_bias:
                    active_x.add(i);active_w.add(j)
        rows_out.append(dict(**context,layer=layer,rows=rows,k=k,out=out,
                             counts=dict(counts),logical_MACs=rows*k*out,
                             eligible_MACs=counts['body_and_YL_bias']*k,
                             conditional_prepared_elements=(len(active_x)+len(active_w))*k,
                             x_span_counts=dict(Counter(a['span'] for a in xa)),
                             w_span_counts=dict(Counter(a['span'] for a in wa))))
        return original_linear(x,rows,k,out,w,b,relu)

    f.linear=observe
    seed=27051001
    expected=json.loads((C/'norm-frontier-result.json').read_text())['cells']
    cells=[]
    for kind in ('normal','wide','sparse'):
        for rows in (1,8):
            context.clear();context.update(kind=kind,seed=seed,profile='typical')
            layer=0
            i,h,h2=f.dimensions(seed,'typical')
            x=f.gen(kind,rows*i,seed+999)
            x=f.linear(x,rows,i,h,f.weights(kind,seed,1,i,h*i),f.bias(seed,2,h),True)
            x=f.norm(x,rows,h,f.scale(seed+3,h))
            x=f.linear(x,rows,h,h2,f.weights(kind,seed,4,h,h2*h),f.bias(seed,5,h2),True)
            x=f.norm(x,rows,h2,f.scale(seed+6,h2),f.bias(seed,7,h2))
            x=f.linear(x,rows,h2,10,f.weights(kind,seed,8,h2,10*h2),f.bias(seed,9,10),False)
            digest=hashlib.sha256(b''.join(struct.pack('<I',a) for a in x)).hexdigest()
            prior=next(c for c in expected if c['seed']==seed and c['profile']=='typical' and c['kind']==kind and c['rows']==rows)
            assert digest==prior['output_sha256']
            rr=[r for r in rows_out if r['kind']==kind and r['rows']==rows]
            total=sum(r['logical_MACs'] for r in rr);eligible=sum(r['eligible_MACs'] for r in rr)
            cells.append(dict(kind=kind,rows=rows,logical_MACs=total,eligible_MACs=eligible,
                              eligible_MAC_fraction=eligible/total,output_sha256=digest,
                              original_formula_fixture_hash_matches=True))
    result=dict(at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                status='SEEN_FULL_FORMULA_GUARD_CENSUS_NOT_NEWKERNEL_OR_NATIVE',
                scope='SixalreadyseenCcells:27051001/typical,normalwide_sparse,rows1and8; no confirmationinputs',
                wall_seconds=time.perf_counter()-started,cells=cells,layers=rows_out,
                metadata='LiteralUInt32v-1/min andv/max replayofpredecessorYc description; actualLeangetter/metadata proof still required',
                source_hashes={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in
                               (Path(__file__),C/'norm_frontier.py',C/'norm-frontier-result.json')},
                limits=['Observer keeps originalrational model outputs; hashesbindfixtureonly',
                        'Eligibility is not a speed estimate','Preparation/getter/carry/rounding costs unmeasured',
                        'Pairmetadata is not a provedactualcachecaller','No all12gate/currentchampionclaim'])
    (HERE/'word-model-coverage.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(dict(wall_seconds=result['wall_seconds'],cells=cells),indent=2))


if __name__=='__main__':
    main()
