"""Resolve whether the narrow-block opportunity survives a production profile.

One published typical profile, seed42, first MLP layer, all 80 output neurons;
normal/wide/sparse. No new random seeds or performance measurements.
"""
from pathlib import Path
from collections import Counter
import datetime
import hashlib
import json
import model_span_probe as m
from bucket64_discriminator import checked

HERE=Path(__file__).resolve().parent
MASK=(1<<64)-1


def run():
    seed=42;r=m.lcg(8,seed^0x5bd1e995)
    ni=(32+r[0]%67)*8;no=(8+r[1]%25)*8
    records=[]
    for kind in ('normal','wide','sparse'):
        x=m.gen(kind,ni,seed+999)
        w=m.weights(kind,seed,0,ni,ni*no)
        b=m.biases(seed,1,no)
        for j in range(no):
            y=w[j*ni:(j+1)*ni]
            full,expected=m.span_probe(x+[m.ONE],y+[b[j]])
            body,_=m.span_probe(x,y)
            dx=[m.decode(a) for a in x];dy=[m.decode(a) for a in y]
            lx=min(e for _,v,e in dx if v);ly=min(e for _,v,e in dy if v)
            sx=max(e for _,v,e in dx if v)-lx;sy=max(e for _,v,e in dy if v)-ly
            base=lx+ly;termbits=48+sx+sy
            terms=[(sa*sb,ma*mb << (ia+ib-base)) if ma and mb else (1,0)
                   for (sa,ma,ia),(sb,mb,ib) in zip(dx,dy)]
            c=checked([(s<0,v) for s,v in terms]) if termbits<=64 else {'state':'static_term_reject'}
            block=1<<min(10,63-termbits) if termbits<=63 else 0
            row={'kind':kind,'output':j,'n':ni,'output_count':no,
                 'vector_base':base,'spans':[sx,sy],'termbits':termbits,
                 'full_pair63':full['pair63'],'full_l1_bits':full['l1_bits'],
                 'body_static_total64':body['old_guard_bits']<=64,
                 'checked_bucket':c,'block_length':block}
            if block:
                total128=0;merges=0
                for start in range(0,ni,block):
                    part=terms[start:start+block]
                    assert sum(v for _,v in part)<1<<63
                    low=sum(s*v for s,v in part)&MASK
                    signed=low if low<1<<63 else low-(1<<64)
                    assert signed==sum(s*v for s,v in part)
                    total128=(total128+signed)&((1<<128)-1)
                    merges+=1
                signed128=total128 if total128<1<<127 else total128-(1<<128)
                exact=sum(s*v for s,v in terms)
                assert signed128==exact
                sb,mb,ib=m.decode(b[j]);shift=ib+149-base
                assert 0<=shift<128 and (mb<<shift)<1<<127
                result=m.round_rat(m.Fraction(signed128+sb*(mb<<shift))*m.Fraction(2)**(base-298))
                assert result==expected
                row.update(block_merges=merges,bias_terminal_adds=1,
                           exact_sum_matches=True,complete_biased_word_matches=True)
            records.append(row)
    summaries=[]
    for kind in ('normal','wide','sparse'):
        rs=[q for q in records if q['kind']==kind]
        summaries.append({'kind':kind,'dots':len(rs),'n':ni,
                          'checked_states':dict(Counter(q['checked_bucket']['state'] for q in rs)),
                          'term_bound_bits':dict(Counter(q['termbits'] for q in rs)),
                          'block_lengths':dict(Counter(q['block_length'] for q in rs)),
                          'body_static_total64':sum(q['body_static_total64'] for q in rs),
                          'block_merges':dict(Counter(q.get('block_merges',0) for q in rs))})
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
             'status':'FINITE_PRODUCTION_PROFILE_MIRROR_NOT_LEAN_OR_BENCHMARK',
             'profile':'typical','seed':seed,'batch':1,'shape':[ni,no],
             'source_hashes':{str(p.name):hashlib.sha256(p.read_bytes()).hexdigest()
                              for p in (Path(__file__),HERE/'model_span_probe.py',
                                        HERE/'bucket64_discriminator.py',m.SUITE,m.CONTRACT)},
             'summaries':summaries,'records':records,
             'limits':['Only one public typical profile seed; fresh-seed deployment coverage remains UNKNOWN.',
                       'Generator equivalence is statically reviewed; not a Lean-executed fixture or full model gate.',
                       'All stated reduction counts are arithmetic operations, never measured nanoseconds.']}
    (HERE/'typical-first-layer-probe.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(summaries,indent=2))


if __name__=='__main__':run()
