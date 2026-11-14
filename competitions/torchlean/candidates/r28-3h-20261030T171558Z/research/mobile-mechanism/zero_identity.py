"""Original finite modular oracle for the two accumulator-loop transformations."""
from pathlib import Path
import random,json,hashlib,datetime
HERE=Path(__file__).resolve().parent;MASK=(1<<64)-1;Z=1<<57
def low(x,w):return ((x&((1<<25)-1))*((w-(1<<31))&MASK))&MASK
def high(x,w):return ((((x>>25)-(1<<32))&MASK)*((w-(1<<31))&MASK))&MASK
def step(x,y,u,v,a):return tuple((z+t)&MASK for z,t in zip(a,[low(x,u),high(x,u),low(y,v),high(y,v)]))
def main():
 rng=random.Random(0x2853); cases=0
 edges=[0,1,Z-1,Z,Z+1,(1<<31)-1,1<<31,(1<<63)-1,1<<63,MASK]
 for i in range(200000):
  x=edges[i%len(edges)] if i<1000 else rng.getrandbits(64)
  y=Z if i%4==0 else rng.getrandbits(64);u=rng.getrandbits(64);v=rng.getrandbits(64);a=tuple(rng.getrandbits(64) for _ in range(4))
  if i%3==0:x=Z
  ch=a if x==Z else step(x,x,u,v,a)
  sp=a if x==Z and y==Z else step(x,y,u,u,a)
  assert ch==step(x,x,u,v,a)
  assert sp==step(x,y,u,u,a)
  cases+=2
 out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Finite arbitrary-UInt64 accumulator step equality; NOT Lean proof or all-input original contract verification','cases':cases,'mismatches':0,'seed':0x2853,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'algebra':'At x=2^57, x & (2^25-1)=0 and (x>>25)-2^32=0 exactly. Each skipped addend is modular zero for every UInt64 weight. Original finisher and exact-zero/negative-zero fallback are unchanged.'}
 (HERE/'zero-identity.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
if __name__=='__main__':main()
