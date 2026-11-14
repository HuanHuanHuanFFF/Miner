"""Block/tail finite transport check. No concrete floating-point implementation."""
from pathlib import Path
from datetime import datetime, timezone
from itertools import product
import hashlib
import json

OUT=Path(__file__).resolve().parent
def sha(x):return hashlib.sha256(x).hexdigest()

def reference(batch,m,n,p):
    return [tuple(((b*m+i)*n+k,b*n*p+j+k*p) for k in range(n))
            for b in range(batch) for i in range(m) for j in range(p)]

def blocked(width,batch,m,n,p):
    out=[]
    for b in range(batch):
        for g in range(m//width):
            for lane in range(width):
                i=width*g+lane
                assert i<m and (b*m+i)//m==b
                out.extend(tuple(((b*m+i)*n+k,b*n*p+j+k*p) for k in range(n))
                           for j in range(p))
        for tail in range(m%width):
            i=width*(m//width)+tail
            assert i<m and (b*m+i)//m==b
            out.extend(tuple(((b*m+i)*n+k,b*n*p+j+k*p) for k in range(n))
                       for j in range(p))
    return out

def main():
    count=0
    for width in [1,2,3,4,5,8]:
        for shape in product(range(4),range(13),range(5),range(6)):
            assert blocked(width,*shape)==reference(*shape),(width,shape)
            count+=1
    shape=(2,5,2,3)
    batch,m,n,p=shape
    mutant=[]
    rows=batch*m
    for r in range(rows):
        shared_batch=(4*(r//4))//m if r<4*(rows//4) else r//m
        mutant.extend(tuple((r*n+k,shared_batch*n*p+j+k*p) for k in range(n))
                      for j in range(p))
    diffs=[i for i,(x,y) in enumerate(zip(reference(*shape),mutant)) if x!=y]
    assert diffs==list(range(15,24))
    src=(OUT/'BlockWriter.lean.inc').read_bytes()
    result={
        'at_utc':datetime.now(timezone.utc).isoformat(),'fragment_sha256':sha(src),'fragment_bytes':len(src),
        'state':'NOT_RUN_LEAN','scope':'Finite symbolic addresses, k ordering, row order and batch/tail boundaries; no Float32 or performance result.',
        'widths':[1,2,3,4,5,8],'shape_ranges_inclusive':{'batch':[0,3],'m':[0,12],'n':[0,4],'p':[0,5]},
        'shapes_per_width':1560,'total_shape_width_checks':count,'mismatches':0,
        'global_four_row_mutant':{'shape':shape,'rejected_output_indices':diffs},
        'roots':['Submission.R22BlockWriter.'+n for n in [
            'emitRows_four','emitRows_prefix','block_row_valid','tail_row_valid','four_tail_bound',
            'emitRows_point_prefix','blocks_tail_prefix','batch_fold_prefix']],
        'concrete_pointwise_hread_discharged':False,
        'CI_requested':False,
    }
    (OUT/'block-writer-manifest.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result))

if __name__=='__main__':main()
