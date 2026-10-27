from pathlib import Path
from datetime import datetime,timezone
import json
H=Path(__file__).resolve().parent
def rne(n,k):
 q,r=divmod(n,1<<k);h=1<<(k-1)
 return q+int(r>h or r==h and q%2)
def biased(n,k):return (n+((1<<(k-1))-1)+((n>>k)&1))>>k
even=((1<<23)<<23)+(1<<22)
odd=(((1<<23)+1)<<23)+(1<<22)
mx=((1<<24)-1)**2
cases=[]
for name,n,k in [('even_tie',even,23),('odd_tie',odd,23),('max_product',mx,24)]:
 s=n+((1<<(k-1))-1)+((n>>k)&1)
 assert biased(n,k)==rne(n,k) and s < 1<<48
 cases.append(dict(name=name,N=n,k=k,biased_sum=s,result=rne(n,k)))
assert ((even+(1<<22))>>23)!=rne(even,23)
assert ((odd+((1<<22)-1))>>23)!=rne(odd,23)
n=(1<<64)-1;k=23
wrapped=((n+((1<<(k-1))-1)+((n>>k)&1))&((1<<64)-1))>>k
assert wrapped!=rne(n,k)
j=dict(created_utc=datetime.now(timezone.utc).isoformat(),state='THREE_DIRECTED_BOUNDARIES_PASS',cases=cases,
 counterexamples={'even_tie_without_minus1':(even+(1<<22))>>23,'odd_tie_without_parity':(odd+((1<<22)-1))>>23,
  'outside_domain_uint64_wrap':dict(N=n,k=k,wrapped=wrapped,correct=rne(n,k))},
 upper_bound_biased_sum=281474943156225+8388608,
 UInt64_limit=1<<64,shift_domain=[23,24],half_shift_domain=[22,23],
 limits='Three exact integer cases plus deliberate outside-domain wrap. No Lean, native compiler or benchmark, no full candidate.')
(H/'boundaries.json').write_bytes((json.dumps(j,indent=2)+'\n').encode())
print(json.dumps({'state':j['state'],'cases':len(cases),'max_bias_sum':j['upper_bound_biased_sum'],'wrap_counterexample':j['counterexamples']['outside_domain_uint64_wrap']}))
