"""Prefer fully qualified donor constants to late unrestricted namespace opens.

Proof-only punctuation savings make the safer spelling fit without broadening
name resolution for the new closure. No current9 feedback is used.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,types
HERE=Path(__file__).resolve().parent
def sha(x):return hashlib.sha256(x).hexdigest()
def build(raw23,raw27):
 original=(HERE/'graft_native_add_portfolio10.py').read_bytes()
 assert sha(original)=='6d4f12349641bbb6587d844414cf1a5209c7f874a7ca4a1f1a51f2aec2123943'
 code=original.decode();start=code.index(' groups={}\n');end=code.index(" source=once(source,'elem:=kernels0.elem'",start)
 replacement=''' opens=''
 for alias,(qualified,_) in differences.items():
  closure=re.sub(r"(?<![\\w'?!])"+re.escape(alias)+r"(?![\\w'?!])",qualified,closure)
 source=once(source,'def kernels:Kernels where',closure+'\\ndef kernels:Kernels where')
'''
 code=code[:start]+replacement+code[end:]
 m=types.ModuleType('r27_portfolio10_qualified');m.__file__=str(HERE/'graft_native_add_portfolio10.py')
 exec(compile(code,m.__file__,'exec'),m.__dict__)
 result,meta=m.build(raw23,raw27)
 meta['alias_differences_fully_qualified']=meta.pop('alias_differences_locally_opened')
 return result,meta
def transform(raw,submission=23,variant='mixer-native-add-portfolio10-qualified-v2',donor_raw=None):
 assert submission==23 and variant=='mixer-native-add-portfolio10-qualified-v2'
 if donor_raw is None:
  import os
  root=os.environ.get('TORCHLEAN_ROOT')
  path=Path(root)/'r27-source-private/official-27.lean' if root else HERE.parents[1]/'competition-state/source-private/submission27-Kernel.lean'
  donor_raw=path.read_bytes()
 return build(raw,donor_raw)[0]
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--donor',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True)
 a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
 sp=importlib.util.spec_from_file_location('r27_portfolio2_policy',HERE/'patch_public.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),'free_bytes':256000-len(result),
  'recipe_sha256':sha(Path(__file__).read_bytes()),'policy':m.policy_check(result),**meta,
  'state':'PREFERRED_QUALIFIED_ACTUAL_ALL12_NOT_COMPILED',
  'why':'LateopenNat/Model would also open unrelated unrenamed constants; qualify9needed names instead.579Bproof-only horizontalpunctuation savings allowthissafe spelling',
  'actual_binding':'Same native64add+positiveGEMM+MYbc with originalkernel0RMS, all12correct connected. No runtime algorithm change fromv1',
  'scope':'PRE9 source only, no9nativeoutputs/inputread, no tuning. Fresh originalgate andnewstandardgroup required',
  'freeze':'e45v1 retained, do notmutatealreadydispatchedsource. Preferthisv2ifnotdispatched orifnamespace-resolutionrepairneeded',
  'publication':'Ownrecipe/receipts only; wholesource private/ephemeral'}
 a.receipt.write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
