#!/usr/bin/env python3
"""Exhaust the public generator's low10-bit state; no IID/probability assumption."""
from pathlib import Path
import hashlib,json
P=Path(__file__).resolve().parent
def main():
 a=1664525;b=1013904223;mod=1024
 state=0;states=[]
 for _ in range(mod):
  state=(a*state+b)%mod;states.append(state)
 assert state==0 and len(set(states))==mod
 zeros=[((x>>9)&1)==0 for x in states]
 run=longest=0
 for x in zeros+zeros:
  run=run+1 if x else 0;longest=max(longest,run)
 lengths=[1,2,3,4,5,6,7,8,9,10,16,27,36,45,54,63,72]
 counts={str(k):sum(all(zeros[(i+j)%mod] for j in range(k)) for i in range(mod)) for k in lengths}
 assert all(counts[str(k)]==0 for k in [27,36,45,54,63,72])
 r={'state':'COMPLETE_LOW10_STATE_ENUMERATION_FOR_PINNED_PUBLIC_GENERATOR','official_commit':'9d4640e4d92b7f29611643e54601d5a114dc70b1','suite_path':'lean/bench/ExactSuite.lean','suite_git_blob':'f78b33ea5ac54b5210bcaa19a03b70e93f5c5f6d','generator':{'a':a,'b':b,'word_modulus':2**32,'mask_bit':9},'low10_orbit_length':len(states),'distinct_states':len(set(states)),'cycle_closes':True,'longest_cyclic_zero_run':longest,'all_zero_windows_by_length':counts,'cnn_3x3_fanins':[27,36,45,54,63,72],'cnn_all_zero_weight_row_from_mask':False,'mathematical_scope':'The fullUInt32 LCG modulo1024 obeys this exact low10 recurrence because1024 divides2^32. The single full1024state orbit covers every starting low10 seed, including wrap. This is finite exhaustive support-mask coverage, not a random sample.','weight_scaling_scope':'For currentCNN fanin27..72, isqrt(fanIn)<=8 and scale4/isqrt>=1/2. A kept normal generator word has magnitude>=2^-6, so positive finite scaling/rounding cannot make itzero. This analytic range connection is not a compiled Lean proof.','decision':'The preferred BW.min!=511 guard retains every currentCNN sparse weight row produced by this exact generator, while still checking arbitrary kernel inputs at runtime. Do not remove the real guard or hardcode kind/seed.','not_claimed':['all-input kernel proof','future generator coverage','native timing','success probability','official score'],'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
 (P/'sparse-mask-coverage.json').write_bytes((json.dumps(r,indent=2)+'\n').encode());print(json.dumps(r,indent=2))
if __name__=='__main__':main()
