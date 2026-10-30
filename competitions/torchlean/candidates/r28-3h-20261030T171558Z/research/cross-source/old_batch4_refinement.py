"""Frozen old cohort only: complete batch1/batch4 Mixer arithmetic refinement.

Honors the actual continuous LCG input stream and output concatenation. No
in-flight CI3 inputs/results are read; no frozen candidate is changed.
"""
from pathlib import Path
from datetime import datetime,timezone
import collections
import hashlib
import importlib.util
import json
import sys
import time
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path);module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module


base=load('batch4_base',HERE/'mixer_path_model.py')
lit=load('batch4_literal',HERE/'literal_centered_replay.py')
wide=load('batch4_wide',HERE/'public54_wide_singleton_model.py')
m=base.m;MASK=(1<<64)-1


def eligible(a,b,bias):
    if a is None or b is None:return None
    _,_,ea,_,ma=a;_,_,eb,_,mb=b
    if ea+eb>62:return None
    _,bm,bi=m.fields(bias)
    lo=min(ma[0]+mb[0],126+bi)if bm else ma[0]+mb[0]
    hi=max(ma[1]+mb[1],126+bi)if bm else ma[1]+mb[1]
    if hi<lo or hi-lo>15 or ma[0]+mb[0]-lo>=64:return None
    return lo,ma[0]+mb[0]-lo


def verify_center(a,b,d):
    av,sa,ea,oa,_=a;bv,sb,eb,ob,_=b;h=l=0
    for x,y in zip(av,bv):
        p=x*y;assert p<1<<64;next_low=(l+p)&MASK;h=(h+(next_low<l))&MASK;l=next_low
    assert lit.terminal(h,l,len(av),ea,eb,sa,sb,d)==lit.old_loop(oa,ob,d)


class Census(base.Census):
    def __init__(self):super().__init__();self.extra=collections.Counter()
    def linear(self,x,rows,k,out,w,b,relu,stage):
        result=super().linear(x,rows,k,out,w,b,relu,stage)
        left=[x[i*k:(i+1)*k]for i in range(rows)];right=[w[j*k:(j+1)*k]for j in range(out)]
        if rows>=2:
            pa=list(map(lit.actual_center,left));pb=list(map(lit.actual_center,right))
            for i in range(0,rows-1,2):
                for j in range(out):
                    one=eligible(pa[i],pb[j],b[j]);two=eligible(pa[i+1],pb[j],b[j])
                    if one is not None and two is not None:
                        verify_center(pa[i],pb[j],one[1]);verify_center(pa[i+1],pb[j],two[1]);self.extra['centered_paired_macs']+=2*k
        else:
            prepared=wide.prepare(x)
            if prepared is not None:self.extra['wide_singleton_prep_items']+=k
            for j,v in enumerate(right):
                value,state=wide.dot(x,v,b[j],prepared)
                self.extra['wide_singleton_'+state+'_macs']+=k
                if value is not None:assert value==result[j]
        return result
    def matrix(self,left,right,relu,stage):
        result=super().matrix(left,right,relu,stage);pa=list(map(lit.actual_center,left));pb=list(map(lit.actual_center,right))
        for a in pa:
            for b in pb:
                choice=eligible(a,b,0)
                if choice is not None:verify_center(a,b,choice[1]);self.extra['centered_gemm_macs']+=len(a[0])
        return result


def main():
    began=time.monotonic();req_path=base.r.E/'fp-word-conv6-26102901-request.json';measure_path=base.r.E/'fp-word-conv6-26102901-measurement.json'
    req=json.loads(req_path.read_bytes());measured=json.loads(measure_path.read_bytes())['result'];original_gen=m.gen
    result=[];total=collections.Counter();samples=0
    for w in req['workloads']:
        _,_,_,_,T,C=base.r.dimensions(w['seed'],w['profile']);size=T*C
        for kind in ['normal','wide','sparse']:
            for batch in [1,4]:
                assert time.monotonic()-began<60,'bounded local finite-work budget'
                flat=original_gen(kind,batch*size,w['seed']+999);output=[];counts=collections.Counter()
                for i in range(batch):
                    block=flat[i*size:(i+1)*size]
                    def injected(k,n,seed,block=block):
                        if (k,n,seed)==(kind,size,w['seed']+999):return block.copy()
                        return original_gen(k,n,seed)
                    m.gen=injected
                    census=Census();output.extend(base.r.run_cell('mixer',w['seed'],w['profile'],kind,census));counts.update(census.extra);samples+=1
                    m.gen=original_gen
                cell=f"{w['id']}|mixer:b{batch}:{kind}";actual=base.r.fnv(output);expected=measured['rounds'][0]['cells'][cell]['candidate_checksum'];assert actual==expected,(cell,actual,expected)
                result.append({'cell':cell,'samples':batch,'checksum':actual,'old_native_checksum':expected,'counts':counts});total.update(counts)
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'OLD_SEEN_COMPLETE_BATCH1_BATCH4_FINITE_REFINEMENT_NOT_NATIVE',
         'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'elapsed_seconds':time.monotonic()-began,'cells':result,'cell_count':len(result),'sample_count':samples,'totals':total,
         'request_sha256':hashlib.sha256(req_path.read_bytes()).hexdigest(),'measurement_sha256':hashlib.sha256(measure_path.read_bytes()).hexdigest(),
         'generator':'Original ExactSuite generates samples*size words once with seed+999. ContractExact runModel uses consecutive slices and concatenates outputs before FNV.',
         'candidate_bindings':{'centered64':'c5acf195 frozen; only terminal-word equality checked, no source change','wide_singleton54':'8de73c86 held; packed positive-offset math checked, no native proof'},
         'limits':['This is the same old26102901 cohort, not independent confirmation','No CI3input/result or timing was used','Finite arithmetic/source-model evidence, not Lean/all12 or native acceptance','No speed inferred from counts']}
    (HERE/'old-batch4-refinement.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps({k:out[k]for k in ['cell_count','sample_count','elapsed_seconds','totals']},indent=2))


if __name__=='__main__':main()
