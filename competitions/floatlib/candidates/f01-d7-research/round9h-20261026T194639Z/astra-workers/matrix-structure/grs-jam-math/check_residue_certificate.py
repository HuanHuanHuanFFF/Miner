"""Exact 28-state coefficient check; no d sampling and no Lean claim."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
H=Path(__file__).resolve().parent
sgn=lambda n:(n>0)-(n<0)
rows=[]
for C in (4,8,16):
 for v in range(C):
  a=2*v-C
  # D>0, 0<r<D: if a<=-2 then a*D+2*r <= -2;
  # a=0 gives 2*r>0; a>=2 gives positive. D=1 has no nonzero r.
  assert a%2==0
  nonzero_original=(-1 if a<0 else 1)
  j0=v
  j1=v+1-v%2
  assert 0<=j0<C and 0<=j1<C
  assert sgn(2*j0-C)==sgn(a)
  assert sgn(2*j1-C)==nonzero_original
  rows.append({'C':C,'v':v,'a':a,'r_zero':{'j':j0,'comparison_sign':sgn(a)},
   'r_positive':{'j':j1,'comparison_sign':nonzero_original}})
def rq(p,D):
 q,r=divmod(p,D)
 return q+(2*r>D or (2*r==D and q%2==1))
def jam(p,D):
 q,r=divmod(p,D)
 return q+(0 if r==0 else 1-q%2)
assert rq(jam(3,2),2)==0 and rq(3,4)==1
assert rq(jam(17,2),6)==2 and rq(17,12)==1
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'EXACT_28_STATE_COEFFICIENT_CHECK; NOT_LEAN',
 'assumptions':'D>0 and 0<=r<D; only branch r=0 vs r>0. q parity retained at equal midpoint.',
 'general_integer_argument':'For negative even a, a<=-2; r<D implies a*D+2*r<=-2. For a=0,r>0 expression>0; for positive a expression>0. At r=0 sign equals sign(a).',
 'states':rows,'count':len(rows),'d_values_enumerated':0,'p_values_enumerated':0,
 'necessary_k2_boundary':{'p':3,'d':1,'k':1,'jam_then_rne':0,'one_round':1},
 'even_C_alone_is_insufficient':{'p':17,'D':2,'C':6,'jam_then_rne':2,'one_round':1},
 'lean_sha256':hashlib.sha256((H/'JamVariable.lean').read_bytes()).hexdigest(),
 'lean_bytes':len((H/'JamVariable.lean').read_bytes()),'formal':'NOT_RUN','CI':0,'local_Lean':0}
(H/'residue-certificate.json').write_text(json.dumps(receipt,indent=2)+'\n')
print(json.dumps({k:receipt[k] for k in ('status','count','d_values_enumerated','p_values_enumerated','necessary_k2_boundary','lean_sha256','lean_bytes','formal')}))
