from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,random,time
HERE=Path(__file__).resolve().parent;Q=1<<39;I=1<<20;MASK=(1<<64)-1
def packet(a,i):return(a+Q)*I+i
def state(h,l,p):
 low=(l+p)&MASK
 return(h-(p>>63)+(low<l))&MASK,low
def main():
 begin=time.monotonic();rng=random.Random(0x6339);cases=0;rows=0
 edges=[-Q+1,-1,0,1,Q-1]
 for n in range(12000):
  a=edges[n%len(edges)]if n<50 else rng.randrange(-Q+1,Q)
  i=[0,1,I-2,I-1][n%4]if n<50 else rng.randrange(I)
  p=packet(a,i);assert 0<=p<1<<60<1<<63
  assert p&(I-1)==i and(p>>20)-Q==a;cases+=1
 for n in[1,2,3,16,31,64,127,256]:
  for _ in range(100):
   aa=[0 if rng.randrange(2)==0 else rng.randrange(-Q+1,Q)for _ in range(n)]
   ww=[rng.randrange(-Q+1,Q)for _ in range(n)];shift=rng.randrange(16)
   packed=[packet(a,i)for i,a in enumerate(aa)if a]
   dense=sparse=(0,0)
   for a,w in zip(aa,ww):dense=state(*dense,(a*w<<shift)&MASK)
   for p in packed:
    index=p&(I-1);a=(p>>20)-Q
    sparse=state(*sparse,(a*ww[index]<<shift)&MASK)
   assert dense==sparse;rows+=1
 a,i=1,I;p=packet(a,i)
 index_bad={"case":"missingindexbound","a":a,"index":i,"packet":p,"decoded_index":p&(I-1),"decoded_a":(p>>20)-Q}
 assert index_bad["decoded_index"]!=i or index_bad["decoded_a"]!=a
 a=-Q-1;i=0;word=((((a+Q)&MASK)<<20)|i)&MASK
 coeff_bad={"case":"missingcoefficientbound","a":a,"index":i,"uint64packet_hex":f"{word:016x}","decoded_a":(word>>20)-Q}
 assert coeff_bad["decoded_a"]!=a
 # Old joint native-span admission does not universally imply a narrow X row.
 # X=[1,2^30], all-zero W, bias=1: joint lo=hi=252, X own span31.
 xwords=[0x3f800000,0x4e800000];lo=min((((v&0x7fffffff)-1)&0xffffffff)>>23 for v in xwords)-1
 hi=max((v&0x7fffffff)>>23 for v in xwords)-1
 a=1<<54;raw=((((a+Q)&MASK)<<20)|1)&MASK
 joint_bad={"case":"jointspan_does_not_bound_eachfactor","X_hex":[f"{v:08x}"for v in xwords],"W_hex":["00000000","00000000"],"bias_hex":"3f800000","input_metadata_base":lo,"input_metadata_top":hi,"input_row_span":hi-lo,"joint_lo":252,"joint_hi":252,"joint_span":0,"second_aligned_factor":a,"uint64_packet_hex":f"{raw:016x}","decoded_factor":(raw>>20)-Q,"classification":"Packing-premise counterexample, not a fullkernel output counterexample because these weights are zero"}
 assert hi-lo==31 and joint_bad["decoded_factor"]!=a
 helper=HERE/"PackedInput.lean"
 out={"at_utc":datetime.now(timezone.utc).isoformat(),"wall_seconds":time.monotonic()-begin,"state":"INDEPENDENT_POSTFREEZE_FINITE_ARITHMETIC_ONLY","packet_cases":cases,"sparse_dense_word128_rows":rows,"counterexamples":[index_bad,coeff_bad,joint_bad],"helper_sha256":hashlib.sha256(helper.read_bytes()).hexdigest(),"helper_bytes":helper.stat().st_size,
      "freeze":"NoCI6plan/seeds/inputs/results read or used. Genericrandomwordfixtures only, no newbenchmarkclaim.","open":["actualonepassproducer/getters","wholelinearallocation/prepare/gather/ILPcost","Leanhelperelaboration","fullcandidateproofandbytebudget","freshnewconfirmation"]}
 (HERE/"model-receipt.json").write_text(json.dumps(out,indent=2)+"\n",encoding="utf-8")
 print(json.dumps({"packet_cases":cases,"word128_rows":rows,"wall_seconds":out["wall_seconds"],"counterexamples":out["counterexamples"]}))
if __name__=="__main__":main()
