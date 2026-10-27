"""Eight exact-integer scale/threshold discriminators; no runtime timing or broad sample rerun."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,time
H=Path(__file__).resolve().parent
t=time.perf_counter();M=2**23
pairs=[(M,M),(M,M+1),(M+1,2*M-2),(2*M-1,2*M-1),
       (M+2**11,M+2**11),(M+2**11,M+3*2**11),
       (3*2**22+2**11,3*2**22+2**12),(3*2**22+3*2**11,3*2**22+3*2**12)]
rows=[]
for a,b in pairs:
 p=a*b;s=p.bit_length()-1-23;q,r=divmod(p,1<<s);half=1<<(s-1)
 rounded=q+int(r>half or r==half and q%2==1);R=rounded<<s
 assert R%(1<<23)==0
 Z=R>>23;high=int(Z>=2**24);normalized=Z>>high
 assert 2**23<=Z<2**25 and Z<2**32
 assert Z<2**24 or Z%2==0
 assert high==int(R>=2**47) and normalized==R>>(23+high)
 rows.append(dict(a=a,b=b,P=p,R=R,Z=Z,high=high,q=normalized,
   target_float32_raw_exponent=150+high,scaled_float32_exact=True))
assert (104<<23)==0x34000000
wrong=rows[1]
record=dict(updated_utc=datetime.now(timezone.utc).isoformat(),state='EIGHT_DIRECTED_INTEGER_DISCRIMINATORS_PASS',
 rows=rows,constant_word='0x34000000',constant_value='2^-23',
 wrong_scale_counterexample=dict(P=wrong['P'],R=wrong['R'],correct_Z=wrong['Z'],
   wrong_2_pow_minus24_value=str(wrong['R'])+'/16777216',wrong_truncated_UInt32=wrong['R']//2**24),
 unscaled_UInt32_counterexample=dict(R=rows[0]['R'],saturated=2**32-1,correct_Z=rows[0]['Z']),
 elapsed_seconds=time.perf_counter()-t,script_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
 limits='Exact arithmetic only; representability criterion checked on eight chosen products. No Lean/native float execution, full-input proof, timing, holdout or general random sample.')
(H/'directed-check.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps({'state':record['state'],'cases':len(rows),'wrong_scale_counterexample':record['wrong_scale_counterexample'],'elapsed_seconds':record['elapsed_seconds']}))
