"""Finite formula and GRS-scale checks; not a Lean or all-Nat proof."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
H=Path(__file__).resolve().parent
def jam(p,D):
 q,r=divmod(p,D)
 return q+(0 if r==0 else 1-q%2)
def rne(p,k):
 D=1<<k;q,r=divmod(p,D)
 return q+int(2*r>D or (2*r==D and q%2==1))
counts={'add':0,'subtract':0,'scale':0,'GRS_bridge':0,'GRS_rounding':0}
for D in range(1,34):
 for X in range(0,65,2):
  for m in range(257):
   assert jam(X*D+m,D)==X+jam(m,D)
   counts['add']+=1
   if m<=X*D:
    assert jam(X*D-m,D)==X-jam(m,D)
    q,r=divmod(m,D)
    if r:
     assert q<X
     assert X*D-m==D*(X-(q+1))+(D-r)
     assert 0<D-r<D
    counts['subtract']+=1
   assert jam(8*m,8*D)==jam(m,D)
   counts['scale']+=1
values=[1<<23,(1<<23)+1,(1<<24)-2,(1<<24)-1]
for d in (4,5,6,25,31,32,33,253):
 D=1<<(d-3)
 for big in values:
  for small in values:
   X=8*big;J=jam(8*small,1<<d)
   assert J==jam(small,D)
   for sign in (-1,1):
    P=(big<<d)+sign*small
    T=X+sign*J
    assert P==X*D+sign*small and T==jam(P,D)
    counts['GRS_bridge']+=1
    for k in (2,3,4):
     assert rne(T,k)==rne(P,d-3+k)
     counts['GRS_rounding']+=1
odd={'D':2,'X':1,'m':1,'plus_lhs':jam(3,2),'plus_rhs':1+jam(1,2),
 'minus_lhs':jam(1,2),'minus_rhs':1-jam(1,2)}
assert odd['plus_lhs']!=odd['plus_rhs'] and odd['minus_lhs']!=odd['minus_rhs']
data={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'FINITE_FORMULA_CHECK_ONLY',
 'counts':counts,'small_domain':'D1..33; even X0..64; m0..256; subtraction only m<=X*D',
 'GRS_domain':'4 normal significand boundary values per side; gaps4,5,6,25,31,32,33,253; both signs; k2,3,4',
 'odd_X_counterexample':odd,'frozen_jam_sha256':hashlib.sha256((H/'JamVariable.lean').read_bytes()).hexdigest(),
 'translation_sha256':hashlib.sha256((H/'JamTranslate.lean.inc').read_bytes()).hexdigest(),
 'translation_bytes':len((H/'JamTranslate.lean.inc').read_bytes()),'Lean':'NOT_RUN','CI':0,
 'remaining':'Typed runtime align control, leading/k, exact Model.add bridge, Float32/fields, public specs, all cost'}
assert data['frozen_jam_sha256']=='a78a153405a2b4a5fd29ac704d77114a8f650ac6120591700f4d2ad05afe5595'
(H/'translation-check.json').write_text(json.dumps(data,indent=2)+'\n')
print(json.dumps(data))
