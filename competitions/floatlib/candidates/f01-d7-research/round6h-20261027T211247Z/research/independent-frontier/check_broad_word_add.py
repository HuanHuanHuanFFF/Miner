"""Fixed directed first discriminator, exact integer-unit oracle, no random expansion."""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,json,hashlib,time
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('oracle',D/'same_exponent_add.py');O=importlib.util.module_from_spec(spec);spec.loader.exec_module(O)
MASK=(1<<32)-1
def eligible(u,v):
 eu=(u>>23)&255;ev=(v>>23)&255
 return (u^v)<0x80000000 and ((eu-1)&MASK)<254 and ((ev-1)&MASK)<254
def core(hi,lo,eh,d):
 if d>=25:return hi,{'far':True,'carry':0,'rne_carry':0}
 a=((hi&0x7fffff)|0x800000)<<3;b=((lo&0x7fffff)|0x800000)<<3
 mask=(1<<d)-1;sticky=int((b&mask)!=0);t=a+((b>>d)|sticky)
 assert a<1<<27 and b<1<<27 and t<1<<28
 carry=t>>27;assert carry<=1
 if carry:t=(t>>1)|(t&1)
 e=eh+carry;s=hi&0x80000000
 if e>=255:return s|0x7f800000,{'far':False,'carry':carry,'rne_carry':0,'early_overflow':True}
 m=(t+3+((t>>3)&1))>>3
 assert 0x800000<=m<=0x1000000
 mag=((e-1)<<23)+m
 assert mag<=0x7f800000
 return s|mag,{'far':False,'carry':carry,'rne_carry':int(m==0x1000000),'early_overflow':False,'tie':(t&7)==4}
def trial(u,v):
 assert eligible(u,v)
 eu=(u>>23)&255;ev=(v>>23)&255
 return core(v,u,ev,ev-eu) if eu<ev else core(u,v,eu,eu-ev)

st=time.monotonic();cases=[]
# Deliberate second-stage RNE carry, overflow, tie-even/down/up and d25 absorption.
special=[(0x3fffffff,0x33800000),(0x7f7fffff,0x73000000),(0x3f800000,0x3f800001),(0x3f800001,0x3f800002),(0x3fffffff,0x337fffff),(0x00800000,0x00800000),(0x7f7fffff,0x7f7fffff)]
for u,v in special:
 for s in [0,0x80000000]:
  cases.extend([(u|s,v|s),(v|s,u|s)])
fra=[0,1,0x7ffffe,0x7fffff];frb=[0,1,0x400000,0x7fffff]
for eh in [1,2,24,25,26,64,127,128,253,254]:
 for d in [0,1,2,3,4,7,8,23,24,25,26,31,32,63,127,253]:
  if eh-d<1:continue
  for a in fra:
   for b in frb:
    for s in [0,0x80000000]:
     u=s|(eh<<23)|a;v=s|((eh-d)<<23)|b;cases.extend([(u,v),(v,u)])
cases=list(dict.fromkeys(cases));trace=hashlib.sha256();stats={'far':0,'leading_carry':0,'RNE_carry':0,'early_overflow':0,'ties':0};witnesses={}
for u,v in cases:
 z,info=trial(u,v);ref=O.oracle(u,v);assert z==ref,(hex(u),hex(v),hex(z),hex(ref),info)
 stats['far']+=info['far'];stats['leading_carry']+=info['carry'];stats['RNE_carry']+=info['rne_carry'];stats['early_overflow']+=info.get('early_overflow',False);stats['ties']+=info.get('tie',False)
 for key,yes in [('far',info['far']),('leading',info['carry']),('rounding',info['rne_carry']),('overflow',z&0x7fffffff==0x7f800000),('tie',info.get('tie',False))]:
  if yes and key not in witnesses:witnesses[key]={'u':f'{u:08x}','v':f'{v:08x}','result':f'{z:08x}',**info}
 trace.update(u.to_bytes(4,'little')+v.to_bytes(4,'little')+z.to_bytes(4,'little'))
rejected=[(0,0x3f800000),(0x80000000,0x80000000),(1,0x00800000),(0x007fffff,0x007fffff),(0x7f800000,0x7f800000),(0x7fc00001,0x3f800000),(0x3f800000,0xbf800000)]
assert all(not eligible(u,v) for u,v in rejected)
assert stats['RNE_carry']>0 and stats['early_overflow']>0 and stats['far']>0
runtime=D/'Runtime-broad-word-add.lean.inc';assert len(runtime.read_bytes())<=2048
out={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'PASS_FIXED_DIRECTED_INTEGER_ORACLE_ONLY','cases':len(cases),'differences':0,'branch_counts':stats,'witnesses':witnesses,'rejected_guard_examples':[[f'{u:08x}',f'{v:08x}'] for u,v in rejected],'trace_sha256':trace.hexdigest(),'runtime_sha256':hashlib.sha256(runtime.read_bytes()).hexdigest(),'runtime_bytes':len(runtime.read_bytes()),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'oracle_module_sha256':hashlib.sha256((D/'same_exponent_add.py').read_bytes()).hexdigest(),'elapsed_seconds':time.monotonic()-st,'limitations':'First finite integer oracle only. Directed fixed fractions/exponents/gaps, no random trials. Rejects preserve B2 by source; no new all-input theorem, Lean/compiler run, actual host Float32 comparison or performance.'}
(D/'broad-word-add-model.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps({k:out[k] for k in ['status','cases','branch_counts','runtime_sha256','runtime_bytes','elapsed_seconds']}))
