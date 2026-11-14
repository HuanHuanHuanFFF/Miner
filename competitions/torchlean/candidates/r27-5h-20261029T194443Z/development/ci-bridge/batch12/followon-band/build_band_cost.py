"""Isolated native-only public23 band consumer, no CI request by default."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent;NATIVE=HERE.parent
PIN='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
def sha(data):return hashlib.sha256(data).hexdigest()
def load(path,name):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def transform(raw,submission=23,variant='band64-native-cost-v1'):
 assert submission==23 and variant=='band64-native-cost-v1' and sha(raw)==PIN
 cp=NATIVE/'frozen_compact_public23.py'
 assert sha(cp.read_bytes())=='4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129'
 source=load(cp,'r27_band_cp').transform(raw,'proof')[0].decode()
 piece=(HERE/'BandRuntime.lean.inc').read_bytes()
 assert sha(piece)=='5214b64ae10f5699d4d386c440aecf2e8c2944b1004d0a804ddbf812ca353c8b'
 start=source.index('def kernels:Kernels where\n');head,tail=source[:start],source[start:]
 tail=once(tail,'def kernels:Kernels where','def retainedKernels:Kernels where')
 tail=once(tail,'theorem correct:Obligation kernels:=','theorem retainedCorrect:Obligation retainedKernels:=')
 tail=once(tail,'[Obligation,kernels,h,','[Obligation,retainedKernels,h,')
 tail=once(tail,'end Submission\n',piece.decode()+'\ndef kernels:Kernels:={retainedKernels with dense:=\u27e8R27Band.dense,retainedKernels.dense.2\u27e9}\nend Submission\n')
 result=(head+tail).encode();assert len(result)<=256000
 assert 'theorem correct:' not in result.decode()
 return result
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True)
 a=p.parse_args();result=transform(a.source.read_bytes())
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),
  'free_bytes':256000-len(result),'helper_bytes':len((HERE/'BandRuntime.lean.inc').read_bytes()),
  'helper_sha256':sha((HERE/'BandRuntime.lean.inc').read_bytes()),'recipe_sha256':sha(Path(__file__).read_bytes()),
  'policy':load(NATIVE/'patch_public.py','r27_band_policy').policy_check(result),
  'state':'ISOLATED_FOLLOWON_NATIVE_ONLY_NOT_COMPILED_NOT_QUEUED','actual_correct':False,
  'retainedCorrect':'Only old retainedKernels after proof-only alias compaction',
  'source_evidence':'R26 owned WideBandRuntime and B07914782 pre-freeze sixcell model; this new consumer has no inherited proof or measurement',
  'scope':'Rows>=4; Xspan<=52, Wspan<=6; per-dot biased rawrange<=58, n<=2^20; other calls/dots fallback original',
  'prepare':'Two-pass counting partition once perinputrow; factors once perweightrow/call; all preparation/output included in future cost',
  'MAC':'Input local factor<2^27 and Wfactor<2^30,64-product block mass<2^63; gathered weight reads/lost4rowsharing/Natloop cost UNKNOWN',
  'finish':'Decode final signed128 once, add exact bias with idx+149-base, one officialfinishWord; exactzero uses original callback',
  'selection':'No queue by default. Do not mutate frozenbatch8 or consume its confirmation inputs. Cost before broad proof',
  'publication':'Own fragment/recipe/receipt only; whole public23 source private/ephemeral'}
 a.receipt.write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
