"""Independent exact redundant 64/32 accumulator model, no native timing."""
from pathlib import Path
import random,json,hashlib
from datetime import datetime,timezone
MASK=(1<<64)-1
def s64(p):
 p&=MASK
 return p-(1<<64) if p>>63 else p
def s128(h,l):
 v=(h<<64)|l
 return v-(1<<128) if h>>63 else v
def accum(values,signed):
 l=q=0
 for p in values:
  w=p&MASK;l=(l+w)&MASK
  term=(s64(w)>>32) if signed else w>>32
  q=(q+term)&MASK
 a=(q<<32)&MASK
 h=(((s64(q)>>32) if signed else q>>32)+int(l<a))&MASK
 return h,l
def main():
 rng=random.Random(0x2832);checks=0;cross=0
 ends=[-(1<<63),-(1<<63)+1,-(1<<32)-1,-1,0,1,(1<<32)-1,(1<<63)-1]
 for signed in [True,False]:
  for n in [0,1,2,3,7,16,31,128,1024]:
   for _ in range(128):
    vals=[rng.randrange(-(1<<63),1<<63) if signed else rng.getrandbits(64) for _ in range(n)]
    if n and checks%2==0:vals=[ends[i%len(ends)] if signed else ends[i%len(ends)]&MASK for i in range(n)]
    h,l=accum(vals,signed);v=s128(h,l) if signed else (h<<64)|l
    assert v==sum(vals);checks+=1;cross+=bool(sum(vals)>=1<<64 or sum(vals)<0)
 # Logical shift in signed version loses negative product sign information.
 good=s128(*accum([-1],True));wrong=s128(*accum([MASK],False));assert good==-1 and wrong==MASK
 # Closed form requires no multi-billion-element allocation: R can exceed64 ifn istoo large.
 n=(1<<32)+2;p=(1<<32)-1;total=n*p
 l=total&MASK;bad_high=0
 assert total>=(1<<64) and ((bad_high<<64)|l)!=total
 out={'state':'EXACT_INTEGER_WORD_MODEL_NOT_LEAN_NATIVE','at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'array_checks':checks,'negative_or_above64_sums':cross,'wrong_logical_signed_example':{'signed_sum':good,'wrong_unsigned_interpretation':str(wrong)},'length_control':{'n':n,'p':p,'true_sum':str(total),'wrong_truncated_sum':l},'required_n_bound':'n<2^32; source36n<2^20 qualifies','producer_condition':'Eachp must already be the intended signed64 orunsigned64 product, not truncated widerinteger','actual_getters_loop_correct':'OPEN','Lean':'NOT_COMPILED','native':'NOT_RUN'}
 Path(__file__).with_name('overlap-result.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out))
if __name__=='__main__':main()
