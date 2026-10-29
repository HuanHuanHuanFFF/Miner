"""Small actual public23 runtime-only row-reciprocal cost candidate.

Original theorem is explicitly renamed retainedCorrect and binds retainedKernels.
The new kernels have NO correctness theorem. Only a native research screen may
use this source. No imported third-party source is saved by this recipe.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
PIN='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
def sha(data):return hashlib.sha256(data).hexdigest()
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def transform(raw,submission=23,variant='row-reciprocal23-native-cost-v1'):
    assert submission==23 and variant=='row-reciprocal23-native-cost-v1' and sha(raw)==PIN
    source=raw.decode('utf-8')
    start=source.index('@[inline] def Ya7G ');end=source.index('\nend\n',start)
    out=source[start:end]
    out=once(out,'def Ya7G ','def R27Ya7G ')
    out=once(out,'(S1a:UInt64):Word :=','(S1a R27R:UInt64):Word :=')
    out=once(out,'let q0:=cv/D\n   let r0:=cv%D*Yf gw\n   let qq:=q0*Yf gw+r0/D',
      'let qr0:=R27Cost.r cv D R27R\n   let q0:=qr0.1\n   let r0:=qr0.2*Yf gw\n   let qr1:=R27Cost.r r0 D R27R\n   let qq:=q0*Yf gw+qr1.1')
    out=once(out,'let ra:=(r0%D)<<<ks\n    let qa:=(qq<<<ks)+ra/D\n    let rr:=ra%D',
      'let ra:=qr1.2<<<ks\n    let qr2:=R27Cost.r ra D R27R\n    let qa:=(qq<<<ks)+qr2.1\n    let rr:=qr2.2')
    start=source.index('def MYbc ');end=source.index('\nlemma Zdt:',start)
    caller=source[start:end]
    caller=once(caller,'def MYbc ','def R27MYbc ')
    caller=once(caller,'  let nU:=if n < 4096 then n.toUInt64 else 0\n',
      '  let nU:=if n < 4096 then n.toUInt64 else 0\n  let recs:=Array.ofFn (n:=rows) fun r=>R27Cost.p (nU*Yf st[r.val]!.2.2)\n')
    caller=once(caller,'Ya7G n ','R27Ya7G n ')
    caller=once(caller,' nU u.2.2 u.1 u.2.1\n',' nU u.2.2 u.1 u.2.1 recs[r]!\n')
    oldtail=source.index('def kernels:Kernels where\n')
    head,tail=source[:oldtail],source[oldtail:]
    tail=once(tail,'def kernels:Kernels where','def retainedKernels:Kernels where')
    tail=once(tail,'theorem correct:Obligation kernels:=','theorem retainedCorrect:Obligation retainedKernels:=')
    tail=once(tail,'[Obligation,kernels,h,','[Obligation,retainedKernels,h,')
    runtime='''
namespace R27Cost
@[inline] def p (d:ػ):ػ:=0xffffffffffffffff/d
@[inline] def r (a d R:ػ):ػ×ػ:=
 if d==0 then(a/d,a%d)else
 let q:=(m64 a R).1
 let r:=a-q*d
 if d<=r then(q+1,r-d)else(q,r)
end R27Cost
'''
    final='\ndef kernels:Kernels:={retainedKernels with norm:=\u27e8Ybb2,R27MYbc\u27e9}\n'
    tail=once(tail,'end Submission\n',runtime+out+'\n'+caller+final+'end Submission\n')
    result=(head+tail).encode()
    assert 'theorem correct:' not in result.decode()
    assert result.decode().count('theorem retainedCorrect:Obligation retainedKernels:=')==1
    assert len(result)<=256000
    return result

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True)
    p.add_argument('--receipt',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();raw=a.source.read_bytes();result=transform(raw)
    if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    sp=importlib.util.spec_from_file_location('r27_cost23policy',HERE/'patch_public.py')
    m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'id':'public23-row-reciprocal-native-cost-v1',
      'source_sha256':PIN,'candidate_sha256':sha(result),'candidate_bytes':len(result),'delta_bytes':len(result)-len(raw),
      'recipe_sha256':sha(Path(__file__).read_bytes()),'policy':m.policy_check(result),
      'state':'NATIVE_RESEARCH_ONLY_NO_NEW_CORRECT_NOT_COMPILED',
      'actual_new_correct':False,'retainedCorrect_scope':'Original retainedKernels only, never new kernels',
      'runtime':'Three exact reciprocal q/r pairs and one cached reciprocal per row; same current23 final round/fallback',
      'proof':'No large helper proof imported. Existing m64 reused. Formal candidate9654b727 is separate',
      'current_target':'NormalizedMLP current43, .9072362322 time/public23, directcurrent source UNKNOWN',
      'publication':'Own runtime recipe/receipt only; whole source private/runner ephemeral'}
    a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps(receipt,indent=2))
