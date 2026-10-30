"""Actual centered64 producer work versus an admissible cheap prefilter.

No candidate is changed. Counts honor R28CPrep's bits<=39 rejection and the
paired consumer's odd tail. Original broad counts84348 were an upper bound,
not all successful cache writes; this script makes that distinction explicit.
"""
from pathlib import Path
from datetime import datetime,timezone
import collections
import hashlib
import importlib.util
import json
import sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('mixer_for_prepare',HERE/'mixer_path_model.py')
model=importlib.util.module_from_spec(spec);spec.loader.exec_module(model)
m=model.m


def bits(meta):
    lo,hi,expmax=meta
    value=0 if hi<lo else 24+hi-lo
    return value if value<=39 and expmax!=255 else None


def eligible(mx,mw,bias):
    bx,bw=bits(mx),bits(mw)
    if bx is None or bw is None or bx+bw>62:return False
    _,mant,idx=m.fields(bias)
    lo=min(mx[0]+mw[0],126+idx) if mant else mx[0]+mw[0]
    hi=max(mx[1]+mw[1],126+idx) if mant else mx[1]+mw[1]
    return hi>=lo and hi-lo<=15 and mx[0]+mw[0]-lo<64


def work(left,right,bias,paired):
    a=list(map(model.metadata,left));b=list(map(model.metadata,right))
    ab=list(map(bits,a));bb=list(map(bits,b));k=len(left[0]);ua=set();ub=set()
    if paired:
        pairs=[(i,i+1) for i in range(0,len(left)-1,2)]
        for i,ii in pairs:
            for j in range(len(right)):
                if eligible(a[i],b[j],bias[j]) and eligible(a[ii],b[j],bias[j]):
                    ua.update((i,ii));ub.add(j)
        pbits=[max(ab[i],ab[ii]) if ab[i] is not None and ab[ii] is not None else None for i,ii in pairs]
        min_b=min((v for v in bb if v is not None),default=999)
        min_a=min((v for v in pbits if v is not None),default=999)
        pa=set()
        for pair,v in zip(pairs,pbits):
            if v is not None and v+min_b<=62:pa.update(pair)
        pb={j for j,v in enumerate(bb)if v is not None and v+min_a<=62}
    else:
        for i in range(len(left)):
            for j in range(len(right)):
                if eligible(a[i],b[j],bias[j]):ua.add(i);ub.add(j)
        min_a=min((v for v in ab if v is not None),default=999);min_b=min((v for v in bb if v is not None),default=999)
        pa={i for i,v in enumerate(ab)if v is not None and v+min_b<=62}
        pb={j for j,v in enumerate(bb)if v is not None and v+min_a<=62}
    assert ua<=pa and ub<=pb
    prepared=sum(v is not None for v in ab+bb)
    return {'vectors_considered':len(a)+len(b),'empty_rejected_vectors':len(a)+len(b)-prepared,
            'upper_prepare_items':(len(a)+len(b))*k,'actual_prepare_items':prepared*k,
            'useful_prepare_items':(len(ua)+len(ub))*k,'unused_prepare_items':(prepared-len(ua)-len(ub))*k,
            'safe_minbits_prefilter_prepare_items':(len(pa)+len(pb))*k,
            'safe_prefilter_saves_items':(prepared-len(pa)-len(pb))*k}


def main():
    records=[];totals=collections.Counter();current=None
    original_linear=model.Census.linear;original_matrix=model.Census.matrix
    def linear(self,x,rows,k,out,w,b,relu,stage):
        if rows>=2:
            detail=work([x[i*k:(i+1)*k]for i in range(rows)],[w[j*k:(j+1)*k]for j in range(out)],b,True)
            records.append({'cell':current,'stage':stage,'work':detail});totals.update(detail)
        return original_linear(self,x,rows,k,out,w,b,relu,stage)
    def matrix(self,left,right,relu,stage):
        if len(left)>=2 and len(right)>=2:
            detail=work(left,right,[0]*len(right),False)
            records.append({'cell':current,'stage':stage,'work':detail});totals.update(detail)
        return original_matrix(self,left,right,relu,stage)
    model.Census.linear=linear;model.Census.matrix=matrix
    req=json.loads((model.r.E/'fp-word-conv6-26102901-request.json').read_bytes());measured=json.loads((model.r.E/'fp-word-conv6-26102901-measurement.json').read_bytes())['result']
    checked=0
    for w in req['workloads']:
        for kind in ['normal','wide','sparse']:
            current=f"{w['id']}|mixer:b1:{kind}";c=model.Census();out=model.r.run_cell('mixer',w['seed'],w['profile'],kind,c)
            assert model.r.fnv(out)==measured['rounds'][0]['cells'][current]['candidate_checksum'];checked+=1
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'SOURCE_BRANCH_PREPARATION_COUNT_NOT_TIMING',
            'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'candidate':'c5acf195 centered64 cost only',
            'old_native_matching_cells':checked,'totals':totals,'records':records,
            'correction':'84348 earlier quoted extra prepareitems is the all-vector upper bound. R28CPrep rejects bits>39 before walking, so actual successful cache visits are counted separately here.',
            'prefilter':'For paired linear, rowpair max offsetbits+minimum weight offsetbits<=62; weight bits+minimum rowpair max<=62. Omit odd row. For scalarGEMM use row/column minbits. This cannot remove a true positive branch; proof/cost/implementation not yet supplied.',
            'limits':['No frozen candidate changed','Finite oldseen shapes only','Preparation visits/allocations are not elapsed time','Possible future prefilter, no CI request']}
    (HERE/'centered-prepare-census.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'cells':checked,'totals':totals},indent=2))


if __name__=='__main__':main()
