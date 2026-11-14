"""Exact one-sided affine dot and word-carry checks, no FP approximate probe."""
from pathlib import Path
import hashlib,importlib.util,json,random
from datetime import datetime,timezone
MASK=(1<<64)-1
M128=(1<<128)-1

def signed128(h,l):
 z=(h<<64)|l
 return z-(1<<128) if h>>63 else z

def run(a,b,sw,signed_product_wrong=False):
 q=1<<(24+sw);h=l=0
 for x,y in zip(a,b):
  p=x*(y+q);assert 0<=p<(1<<64)
  nl=(l+p)&MASK
  h=(h+int(nl<l)-(int(p>>63) if signed_product_wrong else 0))&MASK;l=nl
 # Exact two-word subtraction of Q*sum(a); upper word includes shift spill.
 z=q*sum(a);zl=z&MASK;zh=(z>>64)&MASK
 nl=(l-zl)&MASK;h=(h-zh-int(l<zl))&MASK;l=nl
 return signed128(h,l)

def main():
 rng=random.Random(0x28AFF);checks=0;above63=0
 for sx in range(16):
  for sw in range(min(6,15-sx)+1):
   for n in [1,2,7,9,31,128,257]:
    for mode in ['random','endpoints','zero','negative_weights']:
     a=[];b=[]
     for i in range(n):
      x=rng.randrange(1<<(24+sx));y=rng.randrange(-(1<<(24+sw))+1,1<<(24+sw))
      if mode=='endpoints':x=(1<<(24+sx))-1;y=((1<<(24+sw))-1)*(-1 if i%2 else 1)
      elif mode=='zero':x=0
      elif mode=='negative_weights':y=-abs(y)
      a.append(x);b.append(y)
     assert run(a,b,sw)==sum(x*y for x,y in zip(a,b));checks+=1
     above63+=sum(x*(y+(1<<(24+sw)))>=(1<<63) for x,y in zip(a,b))
 # Raw-word witness in the original full span15 domain: positive product needs unsigned carry.
 m=(1<<24)-1;a=[m<<15,(1<<23)+1];b=[m,(1<<23)+1]
 direct=sum(x*y for x,y in zip(a,b));good=run(a,b,0);bad=run(a,b,0,True)
 assert good==direct and bad==direct-(1<<64)
 here=Path(__file__).resolve().parent;root=next(p for p in here.parents if (p/'AGENTS.md').is_file())
 helper=root/'competitions/torchlean/candidates/r27-5h-20261029T194443Z/research/board-frontier/norm_frontier.py'
 sp=importlib.util.spec_from_file_location('r28_oneside_round',helper);f=importlib.util.module_from_spec(sp);sp.loader.exec_module(f)
 word=f.round_ratio(direct,1,-58);wrong=f.round_ratio(bad,1,-58)
 assert word!=wrong
 # Guard sharpness: span16 can exceed UInt64 even though factors themselves fit.
 overflow=(m<<16)*(m+(1<<24));assert overflow>=(1<<64)
 out={'state':'FINITE_EXACT_INTEGER_WORD_MODEL_NOT_KERNEL','at_utc':datetime.now(timezone.utc).isoformat(),
  'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
  'array_checks':checks,'positive_products_above_signed63_in_checks':above63,
  'unsigned_required_witness':{'input_raw_words':['447fffff','3c800001'],'weight_raw_words':['3cffffff','3c800001'],'xm':120,'wm':120,'sx':15,'sw':0,'correct_word':f'{word:08x}','wrong_signed_carry_word':f'{wrong:08x}','first_positive_product':str(a[0]*(b[0]+(1<<24)))},
  'span16_rejected_product':str(overflow),
  'zero_provenance':'Not discharged by integer model, oldrawfallback retained',
  'real_array_producer':'OPEN','all12':'NOT_IMPLEMENTED','Lean':'NOT_COMPILED','native':'NOT_RUN'}
 (here/'one-sided-result.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out))
if __name__=='__main__':main()
