"""Native-only block16 reduction over the existing prepared QPa products.

Unlike a new factor32 preparation scheme, this uses the source23 P/I caches and
its per-dot exponent metadata. The narrower sumspan<=11 guard guarantees each
absolute term<2^59, hence each16-term block fits signed64. Formal endpoint is
not yet connected; actual kernels have no correct theorem.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
PIN='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
COMPACTOR='4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129'
def sha(data):return hashlib.sha256(data).hexdigest()
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def load(path,name):
 sp=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);return m
def transform(raw,submission=23,variant='prepared-block16-native-cost-v1'):
 assert submission==23 and variant=='prepared-block16-native-cost-v1' and sha(raw)==PIN
 cp=HERE/'frozen_compact_public23.py';assert sha(cp.read_bytes())==COMPACTOR
 compact,_,_=load(cp,'r27_block_compact').transform(raw,'proof')
 source=compact.decode('utf-8')
 start=source.index('@[inline] def QPa ');end=source.index('\n@[specialize] def QY6G2 ',start)
 scalar=source[start:end]
 scalar=once(scalar,'def QPa ','def R27BlockQPa ')
 scalar=once(scalar,'(QYF bx).toNat+(QYF bv).toNat<=15','(QYF bx).toNat+(QYF bv).toNat<=11')
 assert scalar.count('QY6G ')==2
 scalar=scalar.replace('QY6G ','R27Block16.run ')
 # The narrower guard routes other dots to the already compiled original path.
 scalar=once(scalar,' else YaU X W b inW i j bx bv',' else QPa X P I W b inW i j bx bv')
 start=source.index('def YaV ');end=source.index('\nlemma Zq ',start)
 dense=source[start:end]
 before,line_after=dense.split('\n if rows<2 then ',1)
 rowline=line_after.split('\n else YT4l ',1)[0]
 before=once(before,'def YaV ','def R27BlockDense ')
 before=once(before,'let F:=λ i j=>act relu (QPa ','let F:=λ i j=>act relu (R27BlockQPa ')
 first,*body=before.splitlines()
 dense=first+'\n if rows=1 then\n'+'\n'.join(' '+line for line in body)+'\n  '+rowline+'\n else YaV rows inW outW relu X W b\n'
 # Avoid mistaking the original theorem for correctness of the new kernels.
 pos=source.index('def kernels:Kernels where\n');head,tail=source[:pos],source[pos:]
 tail=once(tail,'def kernels:Kernels where','def retainedKernels:Kernels where')
 tail=once(tail,'theorem correct:Obligation kernels:=','theorem retainedCorrect:Obligation retainedKernels:=')
 tail=once(tail,'[Obligation,kernels,h,','[Obligation,retainedKernels,h,')
 helper=(HERE/'Block16Prepared.lean.inc').read_text(encoding='utf-8')
 actual='\ndef kernels:Kernels:={retainedKernels with dense:=\u27e8R27BlockDense,retainedKernels.dense.2\u27e9}\n'
 tail=once(tail,'end Submission\n',helper+'\n'+scalar+'\n'+dense+actual+'end Submission\n')
 result=(head+tail).encode()
 assert len(result)<=256000
 assert 'theorem correct:' not in result.decode()
 return result

if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True)
 p.add_argument('--receipt',type=Path,required=True);p.add_argument('--output',type=Path)
 a=p.parse_args();raw=a.source.read_bytes();result=transform(raw)
 if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
 policy=load(HERE/'patch_public.py','r27_block_policy').policy_check(result)
 receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),
  'recipe_sha256':sha(Path(__file__).read_bytes()),'helper_sha256':sha((HERE/'Block16Prepared.lean.inc').read_bytes()),
  'free_bytes':256000-len(result),'policy':policy,'state':'NATIVE_RESEARCH_ONLY_NO_NEW_CORRECT_NOT_COMPILED',
  'actual_correct':False,'retainedCorrect_scope':'Only original retainedKernels after proof-only alias compaction, never new kernels',
  'change':'Rows1 prepared QPa only; reuse existing P/I and BX/BV, sumspan<=11 enables16-term signed64 blocks; other dots/rows original paths',
  'bias_round':'Remainder uses original QY6G which adds bias via YL and finishes YD once; zero sentinel falls through original Yai',
  'bound':'Each term magnitude<2^(48+11)=2^59;16 terms total absolute mass<2^63. Never raise to12',
  'proof_interface':'B accepted WordMod3 block_exact is only generic modular64 root; no actual prepared-term bounds/carry/finish connection established',
  'cost':'Each full16group replaces16 high/sign carry merges with1; perMAC loads/preparation/product unchanged; extra inner recursion and lost scalar compiler optimization UNKNOWN',
  'selection':'Conditional second native cost route; do not add queues without D capacity; no new original-shipped performance comparison',
  'publication':'Own helper/recipe/receipt only, full source private/runner ephemeral'}
 a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps(receipt,indent=2))
