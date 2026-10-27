from pathlib import Path
import json,random,time,hashlib
D=Path(__file__).resolve().parent;start=time.perf_counter()
def rne(p,k):
 q,r=divmod(p,1<<k);h=1<<(k-1)
 return q+int(r>h or r==h and q&1)
def canonical(a,b):
 p=a*b;k=p.bit_length()-24;q=rne(p,k);carry=int(q==1<<24)
 return k-23+carry,((1<<23) if carry else q)
def direct(a,b):
 p=a*b;k=23+int(p>=1<<47);B=p+(1<<(k-1))-1+((p>>k)&1);h=B>>47;q=B>>(23+h)
 return h,q,B
def jam32(a,b):
 p=a*b;j=(p>>17)|int(p&131071!=0);h=j>>30;z=j<<(1-h)
 q=(z+63+((z>>7)&1))>>7
 # Unnormalizedq is deliberately packed by addition, allowing carry.
 return h,q,(z+63+((z>>7)&1))
rng=random.Random(190103)
pairs=[(8388609,16777214),(16777215,16777215),(8388608,8388608),(8388609,12582913)]
pairs += [(rng.randrange(1<<23,1<<24),rng.randrange(1<<23,1<<24)) for _ in range(50000)]
wrong=[];carry=0;maxB=0
for a,b in pairs:
 h,q=canonical(a,b);hd,qd,B=direct(a,b);hj,qj,_=jam32(a,b)
 maxB=max(maxB,B);carry+=int((a*b<1<<47) and hd==1)
 if (h,q)!=(hd,qd):wrong.append(('direct',a,b,h,q,hd,qd))
 # Sign-independentraw magnitude with fixedS=254; original publicguard variesS only by additive exponent.
 expected=((254-127+h)<<23)+(q-(1<<23))
 jamraw=((254-128+hj)<<23)+qj
 if expected!=jamraw:wrong.append(('jam32',a,b,expected,jamraw))
 if not 0<=hd<=1 or not (1<<23)<=qd<(1<<24) or B>=1<<48:wrong.append(('bound',a,b,hd,qd,B))
maxP=((1<<24)-1)**2;maxTheoreticalB=maxP+((1<<23)-1)+1
out={'status':'FINITE_MATH_DISCRIMINATOR_PASS' if not wrong else 'COUNTEREXAMPLE','selected_runtime':'directP64 literal23/24 with postbias high; oneprototype only','pairs':len(pairs),'mismatches':wrong[:5],'mismatch_count':len(wrong),'carry46_to47':carry,'max_B_observed':maxB,'safe_B_bound':maxTheoreticalB,'safe_B_bound_lt2pow48':maxTheoreticalB<1<<48,'boundary_rows':[{'a':a,'b':b,'P':a*b,'reference':canonical(a,b),'direct':direct(a,b),'jam32':jam32(a,b)} for a,b in pairs[:4]],'elapsed_seconds':time.perf_counter()-start,'limits':'Exact Python integers, finite actualmantissa pairs. NoLean/C/ASM/timing/fullcandidate/CI; oldnegative gatesunchanged.','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
(D/'math-discriminator.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps(out,indent=2))
