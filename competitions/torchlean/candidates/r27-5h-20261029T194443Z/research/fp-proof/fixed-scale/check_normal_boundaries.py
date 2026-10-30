from pathlib import Path
import csv,hashlib,importlib.util,json,sys,datetime,time
sys.dont_write_bytecode=True
H=Path(__file__).parent
spec=importlib.util.spec_from_file_location('r27_own_formula',(H.parent/'census/formula_snapshot.py'))
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
start=time.perf_counter();rows=[];fail=[];counts={}
fractions=[0,1,2,1<<22,(1<<23)-2,(1<<23)-1]
for E in range(1,255):
 for F in fractions:
  D=1<<(E+148);M=(1<<23)+F
  low=D*(4*M-1)//4 if F==0 and E>1 else D*(2*M-1)//2
  high=D*(2*M+1)//2
  branch='minnormal' if E==1 and F==0 else 'power' if F==0 else 'nonpower'
  for sign in [0,1]:
   q=(sign<<31)|(E<<23)|F
   for tag,num in [('below_lower',low-1),('lower_tie',low),('above_lower',low+1),('below_q',M*D-1),('at_q',M*D),('above_q',M*D+1),('below_upper',high-1),('upper_tie',high),('above_upper',high+1)]:
    got=m.round_ratio(-num if sign else num,1,-298)
    strict=low<num<high
    # Exact neighbors: q has even LSB for ties iff F even.
    expected=q if strict or (tag in ['lower_tie','upper_tie'] and F%2==0) else ((sign<<31)|((E<<23)|F)-1) if tag in ['below_lower','lower_tie'] else ((sign<<31)|(((E<<23)|F)+1))
    ok=got==expected
    if not ok:fail.append(dict(E=E,F=F,sign=sign,tag=tag,num=hex(num),got=hex(got),expected=hex(expected)))
    key=branch+':'+tag;counts[key]=counts.get(key,0)+1
    rows.append((E,F,sign,branch,tag,hex(num),hex(got),hex(expected),int(strict),int(ok)))
out=H/'normal-boundaries.csv'
with out.open('w',encoding='utf-8',newline='') as f:
 w=csv.writer(f);w.writerow(['E','fraction','sign','branch','position','integer_magnitude','rounded_word','expected_word','strict_cell','matches']);w.writerows(rows)
r={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'FINITE_EXACT_BOUNDARY_REPLAY_NOT_FORMAL_PROOF','tested_exponents':'Every normal binary32 biased exponent1..254','tested_fractions':fractions,'both_signs':True,'point_count':len(rows),'failures':fail,'branch_counts':counts,'data':out.name,'data_bytes':out.stat().st_size,'data_sha256':hashlib.sha256(out.read_bytes()).hexdigest(),'formula_sha256':hashlib.sha256((H.parent/'census/formula_snapshot.py').read_bytes()).hexdigest(),'elapsed_seconds':time.perf_counter()-start,'scope':'Constructed exact integer totals at fixed2^-298; endpoints/neighbor probes. No benchmark inputs, no cost or probability claim. Covers six fractions per exponent, not all binary32 words.'}
(H/'NORMAL-BOUNDARY-RECEIPT.json').write_text(json.dumps(r,indent=2)+'\n');print(json.dumps(r,indent=2));assert not fail
