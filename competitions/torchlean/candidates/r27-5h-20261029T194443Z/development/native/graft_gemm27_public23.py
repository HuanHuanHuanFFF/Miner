"""Reuse donor27's exact linear-to-GEMM proof over strong public23 YaV.

Only recipe/receipts are published; complete upstream source stays private.
Small-k/nonfinite fallback is original kernels0.dense.2, never gemmSpec.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
PIN23='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
PIN27='f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67'
def sha(x):return hashlib.sha256(x).hexdigest()
def load(path,name):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def build(raw,donor):
 assert sha(raw)==PIN23
 assert sha(donor)==PIN27
 cp=HERE/'frozen_compact_public23.py';assert sha(cp.read_bytes())=='4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129'
 c=load(cp,'r27_gemm_compactor');source=c.transform(raw,'proof')[0].decode()
 d=donor.decode();piece=d[d.index('lemma Yos '):d.index('\ndef kernels:Kernels where')]
 assert piece.count('def Ya3Q ')==1 and piece.count('lemma Zc0Q:')==1
 piece=once(piece,'then Ya3 batch m k n A B else','then kernels0.dense.2 batch m k n A B else')
 piece=once(piece,' · rw[Zc0]',' · exact congrArg (fun(z:Kernels)=>z.dense.2 batch m k n A B) ZbZ')
 # Resolve donor aliases from their explicit qualified origins, never by guess.
 aliases27=c.aliases(d[:d.index('structure Acc')]);aliases23=c.aliases(source[:source.index('structure Acc')])
 replacements={}
 for qualified,alias in aliases27.items():
  if aliases23.get(qualified)!=alias and re.search(r'(?<![\w\'])'+re.escape(alias)+r'(?![\w\'])',piece):
   replacements[alias]=qualified
 for alias,qualified in sorted(replacements.items(),key=lambda x:-len(x[0])):
  piece=re.sub(r'(?<![\w\'])'+re.escape(alias)+r'(?![\w\'])',qualified,piece)
 assert not re.search(r'(?m)^(?:lemma|def|theorem) (?:Yos|Yqs|Yoc|Gsn|Gcg|Ya3Q|Xg|Fw|Zg2|Zc0Q)\b',source)
 source=once(source,'def kernels:Kernels where',piece+'\ndef kernels:Kernels where')
 source=once(source,'dense:=⟨YaV,kernels0.dense.2⟩','dense:=⟨YaV,Ya3Q⟩')
 source=once(source,'specNorm,ZcC,T4b,Zdt]','specNorm,ZcC,Zc0Q,T4b,Zdt]')
 result=source.encode();assert len(result)<=256000
 return result,{'donor_sha256':sha(donor),'closure_bytes':len(piece.encode()),'resolved_aliases':replacements}
def transform(raw,submission=23,variant='gemm27-on-public23'):
 assert submission==23 and variant=='gemm27-on-public23'
 donor_path=HERE/'source-private/official-27.lean'
 assert donor_path.exists(),'Provide exact donor27 privately at recipe HERE/source-private/official-27.lean or call build(raw,donor)'
 return build(raw,donor_path.read_bytes())[0]
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--donor',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True)
 a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),'free_bytes':256000-len(result),
  'recipe_sha256':sha(Path(__file__).read_bytes()),'policy':load(HERE/'patch_public.py','r27_gemm_policy').policy_check(result),
  'state':'ACTUAL_ALL12_DECLARED_NOT_COMPILED','base_sha256':PIN23,**meta,
  'runtime':'Donor Ya3Q transpose/call of public23 YaV, finite k>=20; original kernels0.dense.2 fallback for small k/nonfinite',
  'proof':'Donor Gsn/Gcg/Yos/Yqs/Yoc/Xg/Fw/Zg2/Zc0Q closure; strong23 ZcC reused; actual dense.2/finalcorrect updated',
  'comparison':'CurrentMixer36 via exact public27 calibration chain; no originalshipped performance comparison',
  'boundary':'Fresh original all12 gate and complete Mixer native cost required; no inherited current champion or fullgate claim',
  'publication':'Own recipe/receipt only, whole donor/base/reconstructed source private/ephemeral'}
 a.receipt.write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
