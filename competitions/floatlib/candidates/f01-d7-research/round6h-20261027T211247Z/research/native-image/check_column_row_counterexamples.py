from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
ORACLE=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
sp=importlib.util.spec_from_file_location('old_word_model',ORACLE);O=importlib.util.module_from_spec(sp);sp.loader.exec_module(O)
q=0xffc01234;inf=0x7f800000;one=0x3f800000
def summary(raw,batch,n,p,wrong_batch=False):
    values=[];flags=[True]*(batch*p);row=col=flagBase=0
    for v in raw:
        values.append(O.canon(v))
        index=(col if wrong_batch else flagBase+col)
        flags[index]=flags[index] and not O.nan(v)
        if col+1<p:col+=1
        elif row+1<n:row+=1;col=0
        else:row=col=0;flagBase+=p
    return values,flags
checked=0;mutant=None
for batch in range(4):
 for n in range(5):
  for p in range(6):
   size=batch*n*p
   for pos in sorted({-1,0,size//2,size-1}):
    raw=[one]*size
    if 0<=pos<size:raw[pos]=q
    vals,flags=summary(raw,batch,n,p)
    expected=[all(not O.nan(raw[b*n*p+k*p+j]) for k in range(n)) for b in range(batch) for j in range(p)]
    assert vals==list(map(O.canon,raw)) and flags==expected
    checked+=1
    if mutant is None and size and summary(raw,batch,n,p,True)[1]!=expected:
      mutant={'batch':batch,'n':n,'p':p,'NaN_flat_index':pos,'expected':expected,'wrong':summary(raw,batch,n,p,True)[1]}
assert mutant
n=2;m=4;p=2;A=[inf,one]*m;B=[q,0,one,one]
_,flags=summary(B,1,n,p)
rows=[]
for r in range(m):
 a=A[r*n:(r+1)*n]
 for j in range(p):
  b=[B[k*p+j] for k in range(n)]
  raw=O.dot(a,b)
  native=O.dot(a,b,lambda x,y:O.native_model(O.add,x,y),lambda x,y:O.native_model(O.mul,x,y))
  rows.append({'row':r,'col':j,'certificate':all(not O.nan(x) for x in a) and flags[j],
               'raw':f'{raw:08x}','native_import_model':f'{native:08x}'})
assert not all(flags) and sum(r['certificate'] for r in rows)==4
assert all(r['raw']==r['native_import_model'] for r in rows if r['certificate'])
# A mask must retain separate row identity and never restore a failed bit.
initial=15;first=14;next_all_safe=15
assert (initial&first&next_all_safe)==14 and ((initial&first)|next_all_safe)==15
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'COLUMN_ROW_CONSERVATISM_AND_ADDRESS_DISCRIMINATORS',
 'prototype_sha256':hashlib.sha256((HERE/'ColumnRowSummary.lean.inc').read_bytes()).hexdigest(),
 'structural_configurations':checked,'wrong_batch_flag_counterexample':mutant,
 'actual_quad_guard_coverage_example':{'batch':1,'m':m,'n':n,'p':p,'A':[f'{x:08x}' for x in A],
  'B':[f'{x:08x}' for x in B],'global_B_safe':all(flags),'column_safe':flags,'row_mask':15,'outputs':rows},
 'row_mask_AND_required':{'initial':initial,'after_bad_row0':first,'next_inputs_all_safe_mask':next_all_safe,'correct':14,'wrong_OR_restores_bad_row':15},
 'scope':'GlobalBool remains correct but is less selective: the example refutes equivalent coverage, not correctness. Symbolic indices/old source-word model only; no current workload coverage, native/Lean execution, or performance.'}
(HERE/'column-row-counterexamples.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='actual_quad_guard_coverage_example'},indent=2))
