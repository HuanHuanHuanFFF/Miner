"""Compare signed64, checked unsigned sign buckets and short signed64 blocks.

This is a derived finite discriminator over model-span-probe.json. Magnitude
oracle acceptance is deliberately separated from implementable static guards.
"""
from pathlib import Path
from collections import Counter
import datetime
import hashlib
import json
import model_span_probe as mirror

HERE=Path(__file__).resolve().parent
INPUT=HERE/'model-span-probe.json'
M=1<<64


def classify(r):
    if not r['active']:
        return {'zero_body':True}
    absolute=int(r['sum_abs']); total=int(r['exact_total'])
    pos=(absolute+total)//2; neg=(absolute-total)//2
    assert pos-neg==total and pos+neg==absolute
    L=(r['n']-1).bit_length()
    termbits=r['old_guard_bits']-L
    # A prealigned body uses one vector minimum on either side, which can be
    # lower than the nonzero pair minimum. The original pair-base buckets alone
    # cannot establish success at this shared vector base.
    return {'pos_bits':pos.bit_length(),'neg_bits':neg.bit_length(),
            'oracle_bucket64':max(pos,neg)<M,
            'static_vector64':r['old_guard_bits']<=64,
            'static_pair64':r['pair_guard_bits']<=64,
            'vector_term64':termbits<=64,
            'vector_term63':termbits<=63,
            'vector_term_bound_bits':termbits,
            'block_length':1 << min(10,max(0,63-termbits)) if termbits<=63 else 0,
            'signed64_oracle':-(1<<63)<=total<(1<<63)}


def checked(sign_magnitudes):
    p=n=0
    for i,(negative,mag) in enumerate(sign_magnitudes):
        if not 0<=mag<M:
            return {'state':'term_reject','index':i}
        prior=n if negative else p
        after=(prior+mag)%M
        if after<prior:
            return {'state':'bucket_overflow','index':i}
        if negative:n=after
        else:p=after
    return {'state':'ok','value':str(p-n),'positive':str(p),'negative':str(n)}


def shared_base_first_layer():
    """Resolve the pair-base versus actually cacheable base ambiguity only.

    Repeat just the two narrow first layers; wide first-layer term bound is
    already 93 bits and cannot be a UInt64 encoder. No seed expansion.
    """
    seed=42;ni=537;no=243
    records=[]
    for kind in ('normal','sparse'):
        x=mirror.gen(kind,ni,seed+999)
        weights=mirror.weights(kind,seed,0,ni,ni*no)
        bias=mirror.biases(seed,1,no)
        for j in range(no):
            y=weights[j*ni:(j+1)*ni]
            dx=[mirror.decode(w) for w in x];dy=[mirror.decode(w) for w in y]
            lx=min(k for _,m,k in dx if m);ly=min(k for _,m,k in dy if m)
            base=lx+ly
            terms=[(sa*sb,ma*mb << (ia+ib-base)) if ma and mb else (1,0)
                   for (sa,ma,ia),(sb,mb,ib) in zip(dx,dy)]
            chk=checked([(s<0,m) for s,m in terms])
            exact=sum(s*m for s,m in terms)
            if chk['state']=='ok':assert int(chk['value'])==exact
            block_sums=[]
            for start in range(0,len(terms),16):
                part=terms[start:start+16]
                bound=sum(m for _,m in part)
                assert bound<1<<63
                word=sum((s*m)%M for s,m in part)%M
                signed=word if word<1<<63 else word-M
                assert signed==sum(s*m for s,m in part)
                block_sums.append(signed)
            assert sum(block_sums)==exact
            sb,mb,ib=mirror.decode(bias[j])
            shift=ib+149-base
            assert shift>=0
            with_bias=exact+sb*(mb<<shift)
            full,expected=mirror.span_probe(x+[mirror.ONE],y+[bias[j]])
            result=mirror.round_rat(mirror.Fraction(with_bias)*mirror.Fraction(2)**(base-298))
            assert result==expected
            records.append({'kind':kind,'output':j,'vector_base':base,
                            'pair_base_delta':full['pair_base']-base,
                            'checked_body':chk['state'],
                            'pos_bits':int(chk['positive']).bit_length() if chk['state']=='ok' else None,
                            'neg_bits':int(chk['negative']).bit_length() if chk['state']=='ok' else None,
                            'body_terms':ni,'block16_merges':len(block_sums),
                            'bias_shift_from_body_base':shift,
                            'block_integer_equal':True,'biased_word_equal':True})
    return {'scope':'normal/sparse, seed42, legacy MLP first layer only',
            'records':records,
            'summaries':[{'kind':kind,'dots':sum(r['kind']==kind for r in records),
                          'checked_states':dict(Counter(r['checked_body'] for r in records if r['kind']==kind)),
                          'pair_base_delta':dict(Counter(r['pair_base_delta'] for r in records if r['kind']==kind)),
                          'block16_body_merges':34,'former_per_term_merges':537,
                          'bias_terminal_adds':1}
                         for kind in ('normal','sparse')]}


def run():
    source=json.loads(INPUT.read_bytes())
    records=[{'kind':r['kind'],'layer':r['layer'],'output':r['output'],'n':r['n'],
              'full':classify(r),'body':classify(r['body'])} for r in source['records']]
    summary=[]
    for kind in ('normal','wide','sparse'):
        for layer in range(3):
            rs=[r for r in records if r['kind']==kind and r['layer']==layer]
            a={'kind':kind,'layer':layer,'dots':len(rs),'terms_per_dot':rs[0]['n']}
            for scope in ('full','body'):
                keys=('oracle_bucket64','static_vector64','static_pair64','vector_term64','vector_term63','signed64_oracle')
                a[scope]={'accepted':{k:sum(r[scope].get(k,False) for r in rs) for k in keys},
                          'block_lengths':dict(Counter(r[scope].get('block_length',0) for r in rs)),
                          'zero_bodies':sum(r[scope].get('zero_body',False) for r in rs)}
            summary.append(a)
    cases=[('zero',[]),('max_bucket',[(False,M-1)]),
           ('unsigned_more_than_signed',[(False,1<<63)]),
           ('opposite_max_cancel',[(False,M-1),(True,M-1)]),
           ('positive_overflow',[(False,M-1),(False,1)]),
           ('negative_overflow',[(True,M-1),(True,1)]),
           ('overflow_despite_small_final',[(False,M-1),(False,1),(True,M-1)]),
           ('oversize_term',[(False,M)]),
           ('ordinary_small',[(False,17),(True,9),(False,4)])]
    tests=[]
    for name,terms in cases:
        r=checked(terms)
        if r['state']=='ok':
            assert int(r['value'])==sum(-m if neg else m for neg,m in terms)
        tests.append({'name':name,'terms':terms,'result':r})
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
             'status':'FINITE_MODEL_AND_FIXED_FALSIFIERS_NOT_BENCHMARK',
             'source_sha256':hashlib.sha256(INPUT.read_bytes()).hexdigest(),
             'probe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
             'summaries':summary,'boundary_cases':tests,'records':records,
             'shared_base_first_layer':shared_base_first_layer(),
             'limits':['Oracle buckets use the nonzero-pair base, and cannot be treated as a free per-vector-prepared guard.',
                       'Static pair bound costs pair scanning; static vector bounds are cheaply cacheable but looser.',
                       'Short-block lengths use the shared vector base and conservative 48-bit mantissa product bound.',
                       'Checked bucket runtime must perform overflow comparison every active term and retain fallback on overflow.',
                       'No current champion, native performance, Lean build, all-kernel obligation or full-model gate claim.']}
    (HERE/'bucket64-discriminator.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(summary,indent=2))


if __name__=='__main__':run()
