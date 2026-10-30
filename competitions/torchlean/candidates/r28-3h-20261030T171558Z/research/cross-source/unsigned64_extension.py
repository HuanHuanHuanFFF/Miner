"""Sharp unsigned-product extension of the centered representation.

No runtime candidate is changed or added to the CI queue. The frozen diagnostic
uses offset sum<=61; this checks the larger mathematically valid<=62 domain and
gives an actual finite raw-word counterexample at63.
"""
from pathlib import Path
from datetime import datetime, timezone
import collections
import hashlib
import importlib.util
import json
import sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('literal_center',HERE/'literal_centered_replay.py')
lit=importlib.util.module_from_spec(spec);spec.loader.exec_module(lit)
model=lit.c.model;m=lit.m;MASK=(1<<64)-1


def unsigned_loop(a,b):
    h=l=0
    for x,y in zip(a,b):
        product=x*y
        assert product<1<<64
        low=(l+product)&MASK
        h=(h+(low<l))&MASK;l=low
    return h,l


def sharp_cases():
    make=lit.word
    a=[make(0,128,0x7fffff),make(0,121,1)]
    b62=[make(0,128,0x7fffff),make(0,121,1)]
    b63=[make(0,129,0x7fffff),make(0,121,1)]
    rows=[]
    for bound,b in [(62,b62),(63,b63)]:
        av,sa,ea,oa,ma=lit.actual_center(a)
        bv,sb,eb,ob,mb=lit.actual_center(b)
        assert ea+eb==bound
        lo=ma[0]+mb[0];hi=ma[1]+mb[1]
        assert hi-lo<=15
        exact=sum(m.key(x)*m.key(y) for x,y in zip(a,b))
        expected=m.round_ratio(exact,1,-298)
        raw_product=av[0]*bv[0]
        if bound==62:
            assert 1<<63 <= raw_product <1<<64
            pair=lit.terminal(*unsigned_loop(av,bv),len(a),ea,eb,sa,sb,0)
            assert pair==lit.old_loop(oa,ob,0)
            outcome='Valid unsigned product above signed63 limit; current61 guard unnecessarily excludes it'
        else:
            assert raw_product>=1<<64
            # The illegal larger guard would feed an already truncated low product.
            h=l=0
            for u,v in zip(av,bv):
                p=(u*v)&MASK;low=(l+p)&MASK;h=(h+(low<l))&MASK;l=low
            pair=lit.terminal(h,l,len(a),ea,eb,sa,sb,0)
            assert pair!=lit.old_loop(oa,ob,0)
            signed=(pair[0]<<64)|pair[1]
            if pair[0]>>63:signed-=1<<128
            wrong=m.round_ratio(signed,1,lo-298)
            assert wrong!=expected
            outcome=f'Illegal63 guard aliases product; expected0x{expected:08x}, computed0x{wrong:08x}'
        rows.append({'offset_bit_sum':bound,'a_words':[f'{x:08x}'for x in a],'b_words':[f'{x:08x}'for x in b],
                     'old_lo':lo,'old_hi':hi,'old_span_guard':True,'positive_first_product':raw_product,
                     'first_product_above_signed63':raw_product>=1<<63,'first_product_above_unsigned64':raw_product>=1<<64,
                     'expected_word':f'{expected:08x}','outcome':outcome})
    return rows


def main():
    counts=collections.Counter();decisions=[];cases=sharp_cases()
    original_trace=model.trace_dot

    def trace(a,b,bias,ma,mb):
        kind,out=original_trace(a,b,bias,ma,mb)
        accepted=0
        if out is not None:
            aa=lit.actual_center(a);bb=lit.actual_center(b)
            if aa is not None and bb is not None:
                av,sa,ea,oa,_=aa;bv,sb,eb,ob,_=bb
                _,mant,idx=m.fields(bias)
                lo=min(ma[0]+mb[0],126+idx) if mant else ma[0]+mb[0]
                d=ma[0]+mb[0]-lo
                if ea+eb<=62 and d<64:
                    pair=lit.terminal(*unsigned_loop(av,bv),len(a),ea,eb,sa,sb,d)
                    assert pair==lit.old_loop(oa,ob,d)
                    accepted=61 if ea+eb<=61 else 62
                    counts[f'representation_cap{accepted}_macs']+=len(a)
        decisions.append(accepted)
        return kind,out

    model.trace_dot=trace
    original_linear=model.Census.linear
    original_matrix=model.Census.matrix

    def linear(self,x,rows,k,out,w,b,relu,stage):
        start=len(decisions);result=original_linear(self,x,rows,k,out,w,b,relu,stage);local=decisions[start:]
        if rows>=2:
            for i in range(0,rows-1,2):
                for j in range(out):
                    left,right=local[i*out+j],local[(i+1)*out+j]
                    if left and right:
                        cap=max(left,right);counts[f'paired_cap{cap}_macs']+=2*k
        return result

    def matrix(self,left,right,relu,stage):
        start=len(decisions);result=original_matrix(self,left,right,relu,stage);local=decisions[start:]
        for cap in local:
            if cap:counts[f'gemm_cap{cap}_macs']+=len(left[0])
        return result

    model.Census.linear=linear;model.Census.matrix=matrix
    req=json.loads((model.r.E/'fp-word-conv6-26102901-request.json').read_bytes())
    measured=json.loads((model.r.E/'fp-word-conv6-26102901-measurement.json').read_bytes())['result']
    checked=0
    for w in req['workloads']:
        for kind in ['normal','wide','sparse']:
            c=model.Census();out=model.r.run_cell('mixer',w['seed'],w['profile'],kind,c)
            cell=f"{w['id']}|mixer:b1:{kind}"
            assert model.r.fnv(out)==measured['rounds'][0]['cells'][cell]['candidate_checksum'];checked+=1
    counts['actual_candidate61_macs']=counts['paired_cap61_macs']+counts['gemm_cap61_macs']
    counts['additional_cap62_macs']=counts['paired_cap62_macs']+counts['gemm_cap62_macs']
    counts['potential_candidate62_macs']=counts['actual_candidate61_macs']+counts['additional_cap62_macs']
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'FINITE_UNSIGNED64_EXTENSION_AND_SHARP_RAW_COUNTEREXAMPLE',
            'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'counts':counts,'old_native_matching_cells':checked,
            'sharp_cases':cases,'scope':'No frozen recipe modified; original centered51fd uses<=61. <=62 needs unsigned carry lemma, not the old signed63 Z128 premise. 63 is invalid even under the original source36 span<=15 gate.',
            'proof':'CenteredArithmetic.lean contains uncompiled product_unsigned64 and unsigned128_step interfaces. Actual producer/glue/all12 still OPEN.',
            'limits':['Counts not elapsed-time share','No runtime candidate or CI queue added','All inputs here old seen or independently constructed, no confirmation data']}
    (HERE/'unsigned64-extension.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'counts':counts,'sharp_cases':cases,'cells':checked},indent=2))


if __name__=='__main__':main()
