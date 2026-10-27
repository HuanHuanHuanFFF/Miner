"""Exact small-integer witness against globally pairing rows across batches.
Every individual multiply/add here is an exactly representable binary32 integer.
"""
from pathlib import Path
import datetime,json
HERE=Path(__file__).resolve().parent
batch,m,n,p=2,3,2,3
A=[v for row in range(batch*m) for v in (row+1,row+1)]
B=[v for scale in (7,11) for k in range(n) for v in ([scale]*p if k==0 else [0]*p)]
def row(r,b):
    return [sum(A[r*n+k]*B[b*n*p+k*p+j] for k in range(n)) for j in range(p)]
reference=[x for r in range(batch*m) for x in row(r,r//m)]
naive=[]
for r in range(0,batch*m,2):
    bi=r//m
    naive+=row(r,bi)
    if r+1<batch*m: naive+=row(r+1,bi)
assert reference!=naive
diff=[{'output_index':i,'reference':a,'naive':b} for i,(a,b) in enumerate(zip(reference,naive)) if a!=b]
assert [x['output_index'] for x in diff]==[9,10,11]
out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Finite exact counterexample to a proposed global-row pairing transport, not to frozenstreamingPair/controlPair or existingB2. All products, partials and outputs <=66 and integral, so Float32 rounding cannot explain the mismatch.',
 'shape':{'batch':batch,'m':m,'n':n,'p':p},'A':A,'B':B,'reference':reference,'globally_paired':naive,'differences':diff,
 'decision':'A two-row publicBMM dispatcher must form pairs inside eachbatch, with an odd localrow fallback. It must not use total row parity across batch boundaries; sharingB requires floor(r/m)=floor((r+1)/m). No threshold/value grid or newCI.'}
(HERE/'pair-batch-boundary-counterexample.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out))
