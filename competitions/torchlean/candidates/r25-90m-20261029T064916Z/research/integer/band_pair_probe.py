"""Next-route exact finite discriminator: wide X split into exponent bands.

Frozen narrow C/Lean sources are untouched. This uses one public typical MLP
first layer (wide, seed42) and compares four fixed grouping widths for work
counts only. Counts do not measure cost and cannot rank these choices by time.
"""
from pathlib import Path
from collections import Counter
import datetime
import hashlib
import json
import model_span_probe as m

HERE=Path(__file__).resolve().parent
MASK64=(1<<64)-1
MASK128=(1<<128)-1


def signed(word,bits):
    return word if word < 1<<(bits-1) else word-(1<<bits)


def prepare_bands(raw,width):
    ds=[m.decode(w) for w in raw]
    low=min(e for _,v,e in ds if v)
    groups={}
    for index,(s,v,e) in enumerate(ds):
        if v: groups.setdefault((e-low)//width,[]).append((index,s,v,e))
    result=[]
    for _,items in sorted(groups.items()):
        base=min(e for _,_,_,e in items)
        span=max(e for _,_,_,e in items)-base
        result.append({'base':base,'span':span,
                       'items':[(i,s*(v<<(e-base))) for i,s,v,e in items]})
    assert sorted(i for g in result for i,_ in g['items'])==[i for i,(_,v,_) in enumerate(ds) if v]
    return low,result


def evaluate(x,y,bias,width):
    lowx,bands=prepare_bands(x,width)
    dy=[m.decode(w) for w in y]
    lowy=min(e for _,v,e in dy if v);spany=max(e for _,v,e in dy if v)-lowy
    aligned_y=[s*(v<<(e-lowy)) if v else 0 for s,v,e in dy]
    global_base=lowx+lowy
    global_word=0;block_merges=0;band_info=[]
    for group in bands:
        bound_bits=48+group['span']+spany
        assert bound_bits<=63
        block_size=1<<min(10,63-bound_bits)
        exact_terms=[a*aligned_y[i] for i,a in group['items']]
        words=[((a&MASK64)*(aligned_y[i]&MASK64))&MASK64 for i,a in group['items']]
        assert all(signed(w,64)==t for w,t in zip(words,exact_terms))
        local_word=0;merges=0
        for start in range(0,len(words),block_size):
            part=exact_terms[start:start+block_size]
            assert sum(abs(t) for t in part)<1<<63
            low=sum(words[start:start+block_size])&MASK64
            block_total=signed(low,64)
            assert block_total==sum(part)
            local_word=(local_word+block_total)&MASK128
            merges+=1
        assert signed(local_word,128)==sum(exact_terms)
        delta=group['base']-lowx
        global_word=(global_word+(local_word<<delta))&MASK128
        block_merges+=merges
        band_info.append({'length':len(words),'base_delta':delta,'span_x':group['span'],
                          'term_bound_bits':bound_bits,'block_size':block_size,'block_merges':merges})
    exact=sum(m.rational(a)*m.rational(b) for a,b in zip(x,y))
    assert m.Fraction(signed(global_word,128))*m.Fraction(2)**(global_base-298)==exact
    sb,mb,ib=m.decode(bias);shift=ib+149-global_base
    assert shift>=0
    total=signed(global_word,128)+sb*(mb<<shift)
    got=m.round_rat(m.Fraction(total)*m.Fraction(2)**(global_base-298))
    _,expected=m.span_probe(x+[m.ONE],y+[bias])
    assert got==expected
    return {'width':width,'n':len(x),'input_active':sum(len(g['items']) for g in bands),
            'span_y':spany,'global_base':global_base,'bands':band_info,
            'total_block_merges':block_merges,'cross_band_shift_adds':len(bands),
            'bias_terminal_adds':1,'word_matches':True,
            'inner_low64_multiplications':len(x),
            'per_mac_index_reads':len(x),
            'input_extra_index_bytes':4*len(x),
            'input_extra_band_metadata_words':3*len(bands)}


def run():
    seed=42;r=m.lcg(8,seed^0x5bd1e995)
    ni=(32+r[0]%67)*8;no=(8+r[1]%25)*8
    x=m.gen('wide',ni,seed+999);w=m.weights('wide',seed,0,ni,ni*no);b=m.biases(seed,1,no)
    records=[]
    for width in (1,2,4,8):
        for j in range(no):
            rec=evaluate(x,w[j*ni:(j+1)*ni],b[j],width);rec['output']=j;records.append(rec)
    summaries=[]
    for width in (1,2,4,8):
        rs=[r for r in records if r['width']==width]
        summaries.append({'width':width,'dots':len(rs),
                          'block_merge_counts':dict(Counter(r['total_block_merges'] for r in rs)),
                          'cross_band_shift_add_counts':dict(Counter(r['cross_band_shift_adds'] for r in rs)),
                          'baseline_per_term_128_updates':ni,
                          'new_per_term_low64_multiplies':ni,
                          'extra_per_term_index_reads':ni,
                          'extra_index_bytes_per_input':4*ni})
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
             'status':'EXACT_FINITE_REORDERING_MODEL_NOT_NATIVE_OR_LEAN',
             'profile':'typical','seed':seed,'kind':'wide','shape':[ni,no],
             'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest()
                              for p in (Path(__file__),HERE/'model_span_probe.py',m.SUITE,m.CONTRACT)},
             'summaries':summaries,'records':records,
             'limits':['All inputs and the four grouping choices are exploratory and seen.',
                       'Operation counts do not estimate elapsed time, vectorization, latency or full-model gain.',
                       'The native loop requires an indexed weight gather and per-call X grouping; preparation is not free.',
                       'No exact Lean producer/index-partition/rounding proof or production fallback integration.']}
    (HERE/'band-pair-probe.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(summaries,indent=2))


if __name__=='__main__':run()
