"""Original constant-nine spatial dot expansion; existing #53 portfolio retained."""
from pathlib import Path
import hashlib,json,importlib.util,datetime,argparse
HERE=Path(__file__).resolve().parent
BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
BASE_SHA='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb'
COMPACTOR=HERE.parent/'source-budget/compact53.py'
COMP_SHA=''

def helper():
    sig=''' (f g w:(t:م)→t<(9:م)→ق) (B:ق) (bw:ك) (cb:qCtx0)
 (z0 z1:ق→ك) (a0 a1 b0 b1:ق)'''
    out='@[inline] def r28N9'+sig+':ق:=\n'
    for i in range(9):
      out+=f' let x{i}:=f {i} (by decide)\n let y{i}:=g {i} (by decide)\n let w{i}:=w {i} (by decide)\n'
      prev=['a0','a1','b0','b1'] if i==0 else [f's{i-1}a',f's{i-1}b',f's{i-1}c',f's{i-1}d']
      for suffix,acc,fn,x in zip('abcd',prev,['Y9','cq1','Y9','cq1'],[f'x{i}',f'x{i}',f'y{i}',f'y{i}']):
        out+=f' let s{i}{suffix}:={acc}+{fn} {x} w{i}\n'
    out+=' (z0 (qCtx4 B bw cb s8a s8b)).toUInt64 ||| ((z1 (qCtx4 B bw cb s8c s8d)).toUInt64<<<32)\n'
    out+='lemma r28N9_eq'+sig+':\n r28N9 f g w B bw cb z0 z1 a0 a1 b0 b1=qCtx13 9 f g w B bw cb z0 z1 a0 a1 b0 b1 0:=by\n simp [r28N9,qCtx13]\n'
    wsig=''' (n:م) (f g w:(t:م)→t<n→ق) (B:ق) (bw:ك) (cb:qCtx0)
 (z0 z1:ق→ك) (a0 a1 b0 b1:ق) (k:م)'''
    out+='@[inline] def r28Q9'+wsig+''':ق:=
 if hn:n=9 ∧ k=0 then
  r28N9 (fun t ht=>f t (by simpa [hn.1] using ht))
   (fun t ht=>g t (by simpa [hn.1] using ht))
   (fun t ht=>w t (by simpa [hn.1] using ht)) B bw cb z0 z1 a0 a1 b0 b1
 else qCtx13 n f g w B bw cb z0 z1 a0 a1 b0 b1 k
'''
    out+='lemma r28Q9_eq'+wsig+''':
 r28Q9 n f g w B bw cb z0 z1 a0 a1 b0 b1 k=qCtx13 n f g w B bw cb z0 z1 a0 a1 b0 b1 k:=by
 unfold r28Q9
 split
 · rename_i h
   rcases h with ⟨rfl,rfl⟩
   exact r28N9_eq f g w B bw cb z0 z1 a0 a1 b0 b1
 · rfl
'''
    return out

def transform(raw,submission,variant):
    assert submission==53 and variant=='unroll9'
    assert hashlib.sha256(raw).hexdigest()==BASE_SHA
    s=raw.decode();mark='@[inline] def YbjPPacked '
    assert s.count(mark)==1;s=s.replace(mark,helper()+mark)
    a=s.index(mark);b=s.index('@[inline] def ak ',a)
    part=s[a:b];assert part.count('  qCtx13 k.toUSize')==1
    part=part.replace('  qCtx13 k.toUSize','  r28Q9 k.toUSize');s=s[:a]+part+s[b:]
    a=s.index('lemma YbjPPackedEq ');b=s.index('lemma al ',a)
    part=s[a:b];assert part.count('rw[qCtx14 (hc:=hc)]')==1
    part=part.replace('rw[qCtx14 (hc:=hc)]','rw[r28Q9_eq,qCtx14 (hc:=hc)]');s=s[:a]+part+s[b:]
    spec=importlib.util.spec_from_file_location('r28compact',COMPACTOR);mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    result,_=mod.build(s.encode(),strict_base=False)
    assert len(result)<=256000,len(result)
    return result

def main():
    p=argparse.ArgumentParser();p.add_argument('--base',type=Path,default=BASE);a=p.parse_args()
    raw=a.base.read_bytes();data=transform(raw,53,'unroll9');dest=HERE/'private/unroll9-53.lean';dest.parent.mkdir(exist_ok=True);dest.write_bytes(data)
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'base_sha256':BASE_SHA,'candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'compactor_sha256':hashlib.sha256(COMPACTOR.read_bytes()).hexdigest(),'helper_bytes':len(helper().encode()),'proof_state':'UNCOMPILED_DEFINITIONAL_EXPANSION; all12 gate required','native_cost':'UNKNOWN','coverage':'Only existing dense spatial-pair narrow path with n=9 and initial k=0; all sparse and wide paths untouched. No new numerical preconditions. Same term order and same bias finalizer.'}
    (HERE/'unroll9-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n');print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
