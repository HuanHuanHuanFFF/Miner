"""Finite exact-integer oracle, not Lean/native verification."""
from pathlib import Path
import hashlib,json,random,datetime
HERE=Path(__file__).resolve().parent

def old(p,s,sign):
 b=p+(0x3fffff+((p>>23)&1) if p<(1<<47) else 0x7fffff+((p>>24)&1))
 h=b>>47;q=b>>(23+h)
 return sign|((s-127+h)<<23)|(q-(1<<23))
def fused(p,s,sign):
 h=p>>47
 b=p+(0x3fffff+((p>>23)&1) if p<(1<<47) else 0x7fffff+((p>>24)&1))
 return sign|(((s-128+h)<<23)+(b>>(23+h)))
def oracle(p,s,sign):
 k=p.bit_length()-24;q,r=divmod(p,1<<k);half=1<<(k-1)
 if r>half or (r==half and q&1):q+=1
 if q==(1<<24):q>>=1;k+=1
 return sign|((s-150+k)<<23)|(q-(1<<23))
def main():
 raw=(HERE/'Runtime.lean.inc').read_bytes()
 assert hashlib.sha256(raw).hexdigest()=='5806bb2591dccff00d59b6720360f4c74a1082d4899bf73e4180dfff418e4b2b'
 assert b'let high := p >>> 47' in raw and b'((e <<< 23) + q)' in raw
 values=[(1<<23)+x for x in [0,1,2,3,7,15,31,127,255,1023,4095,65535,4194303,4194304,4194305,8388605,8388606,8388607]]
 pairs=[(a,b) for a in values for b in values]+[(0x800001,0xfffffe),(0x800001,0xc00000)]
 rng=random.Random(222212);pairs +=[(rng.randrange(1<<23,1<<24),rng.randrange(1<<23,1<<24)) for _ in range(12000)]
 trace=hashlib.sha256();count=carry=0
 for a,b in pairs:
  p=a*b
  for s in [128,129,130,173,174,253,254,255,379,380]:
   for sign in [0,1<<31]:
    actual=fused(p,s,sign);expected=oracle(p,s,sign)
    assert actual==expected==old(p,s,sign),(a,b,s,sign,actual,expected)
    assert (actual&0x7fffffff)<0x7f800000
    carry+=int(p<(1<<47) and (p+0x3fffff+((p>>23)&1))>=(1<<47))
    trace.update(json.dumps([a,b,s,sign,actual],separators=(',',':')).encode()+b'\n');count+=1
 witnesses=[]
 for a,b,s in [(0x800001,0xfffffe,130),(0x800000,0x800000,129)]:
  p=a*b;h=p>>47;bb=p+(0x3fffff+((p>>23)&1) if h==0 else 0x7fffff+((p>>24)&1));wrong=((s-128+h)<<23)|(bb>>(23+h));assert wrong!=oracle(p,s,0);witnesses.append({'a':a,'b':b,'s':s,'wrong_OR':wrong,'correct':oracle(p,s,0)})
 result={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'runtime_sha256':hashlib.sha256(raw).hexdigest(),'cases':count,'differences':0,'carry46_to47_cases':carry,'trace_sha256':trace.hexdigest(),'wrong_OR_mutations':witnesses,'scope':'Finite exactinteger oracle andoldbody, not publicMUL proof/native cost. Shapes,seeds/results from frozen confirmation not used.'}
 (HERE/'model-result.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))
if __name__=='__main__':main()
