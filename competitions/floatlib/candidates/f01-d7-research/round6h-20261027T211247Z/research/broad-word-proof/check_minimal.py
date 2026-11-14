"""Finite integer falsification of the three small interfaces; not Lean/Float32 proof."""
from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re

OUT=Path(__file__).resolve().parent
def sha(x):return hashlib.sha256(x).hexdigest()
def rse(n,k):
    q,r=divmod(n,1<<k)
    return q+int(r>(1<<(k-1)) or (r==(1<<(k-1)) and q%2==1)) if k else n
def main():
    ns=set(range(4096))
    for k in range(3,29):
        ns.update(n for n in range((1<<k)-16,(1<<k)+16) if 0<=n<1<<28)
    for n in ns:
        assert n+3+((n>>3)&1)<1<<32
        assert ((n+3+((n>>3)&1))>>3)==rse(n,3)
    bad2=[n for n in sorted(ns) if ((n+2+((n>>3)&1))>>3)!=rse(n,3)]
    bad4=[n for n in sorted(ns) if ((n+4+((n>>3)&1))>>3)!=rse(n,3)]
    assert bad2 and bad4
    far=0
    for hi in [0,1,(1<<23),(1<<23)+1,(1<<24)-1,1<<24]:
        for lo in [0,1,(1<<23),(1<<24)-1]:
            for d in [25,26,31,64,253]:
                assert rse((hi<<d)+lo,d)==hi;far+=1
    hi=(1<<23)+1;lo=1<<23
    assert rse((hi<<24)+lo,24)==hi+1
    n=(1<<32)-4
    wrap=(((n+3+((n>>3)&1))&0xffffffff)>>3)
    assert wrap!=rse(n,3)
    t=(1<<27)-4;m=rse(t,3)
    assert m==1<<24
    carry=[]
    for e in [127,254]:
        good=((e-1)<<23)+m;bad=(e<<23)|(m&0x7fffff)
        assert good!=bad
        carry.append({'input_hi_raw':hex((e<<23)|0x7fffff),'input_lo_raw':hex((e-24)<<23),
                      'T':t,'first_carry':0,'rounded_m':m,'add_pack':hex(good),'wrong_mask_pack':hex(bad)})
    proof=(OUT/'MinimalRounding.lean.inc').read_bytes()
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'phase_start_utc':'2026-10-27T23:30:40Z',
      'phase_limit_utc':'2026-10-27T23:45:40Z','proof_sha256':sha(proof),'proof_bytes':len(proof),
      'roots':['Submission.R22BroadWordMath.'+x for x in re.findall(r'^theorem (\w+)',proof.decode(),re.M)],
      'formal':'NOT_RUN','runtime_5655_unchanged':True,'new_candidate':False,'CI':False,
      'bias_fixed_inputs':len(ns),'bias_mismatches':0,'far_boundary_cases':far,'far_mismatches':0,
      'bias2_mutant_first':bad2[0],'bias4_mutant_first':bad4[0],
      'd24_counterexample':{'hi':hi,'lo':lo,'expected_round':hi+1},
      'out_of_domain_wrap':{'n':n,'word_result':wrap,'Nat_RSE':rse(n,3)},
      'second_carry_examples':carry,
      'limits':['Finite exact integer checks only, not Lean or complete Float32 ADD proof',
                'far_round_absorb closes Nat RSE only; normal dyadic/Model.add bridge remains',
                'n<2^28 proves bias addition no-wrap, not m<=2^24 without normalized n bound']}
    (OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result))
if __name__=='__main__':main()
