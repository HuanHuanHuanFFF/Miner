"""Owned structural GEMM graft recipe; whole retired sources remain private/ephemeral."""
from __future__ import annotations
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,os,re
HERE=Path(__file__).resolve().parent
BASE_SHA='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
DONOR_SHA='f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67'
COMPACT_SHA='4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129'
NAMES=['Yos','Yqs','Yoc','Gsn','Gcg','Ya3Q','Xg','Fw','Zg2','Zc0Q']
STOP=re.compile(r"(?m)^(?:(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected)\s+)*(?:def|theorem|lemma|structure|abbrev)\b|section\b|end\b|open\b|set_option\b|attribute\b|namespace\b)")
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected)\s+)*(?:def|theorem|lemma|structure|abbrev)\s+([\w.'?!]+)")
def sha(raw):return hashlib.sha256(raw).hexdigest()
def declarations(s):
 bounds=[m.start()for m in STOP.finditer(s)]
 return {m.group(1):s[m.start():next((x for x in bounds if x>m.start()),len(s))].rstrip()for m in DECL.finditer(s)}
def aliases(s):
 pre=s[:s.index('structure Acc')];out={}
 for g in re.finditer(r'\bopen\s+([\w.]+)\s+renaming\s+(.+?)(?=\s+open\s+|\s+local\s+notation|\s+local\s+postfix|$)',pre):
  for src,dst in re.findall(r"([\w.'?!]+)->([\w'?!]+)",g.group(2)):out[dst]=g.group(1)+'.'+src
 return out

def build(raw,donor):
 assert sha(raw)==BASE_SHA and sha(donor)==DONOR_SHA
 base=raw.decode();ds=donor.decode();a=declarations(ds);b=declarations(base)
 for name in NAMES:assert name in a and name not in b,name
 shared=['Yo','Yq','Zy','Yn','Zi','Z5']
 for name in shared:assert a[name]==b[name],name
 assert a['ZcC'].splitlines()[0]==b['ZcC'].splitlines()[0]=='lemma ZcC:YaV=linearSpec:=by'
 parts='\n'.join(a[n]for n in NAMES)+'\n'
 donor_alias=aliases(ds);base_alias=aliases(base);used=set(re.findall(r"[\w'?!]+",parts))&donor_alias.keys()
 differences={x:[donor_alias[x],base_alias.get(x)]for x in used if donor_alias[x]!=base_alias.get(x)}
 assert differences=={'CQ':['Nat.pos_of_mul_pos_right',None]},differences
 parts=re.sub(r"(?<![\w'?!])CQ(?![\w'?!])",'Nat.pos_of_mul_pos_right',parts)
 for typ in ['ػ','ؼ','ؽ','ٳ','ٴ','ف']:
  assert ('"'+typ+'"=>')in ds[:ds.index('structure Acc')]and('"'+typ+'"=>')in base[:base.index('structure Acc')]
 assert parts.count('then Ya3 batch m k n A B else')==1
 parts=parts.replace('then Ya3 batch m k n A B else','then gemmWith Yn batch m k n A B else')
 assert parts.count('· rw[Zc0]')==1
 parts=parts.replace('· rw[Zc0]','· simpa only[gemmSpec,Zi]')
 compactor=HERE/'compact_public23.py';assert sha(compactor.read_bytes())==COMPACT_SHA
 spec=importlib.util.spec_from_file_location('r27_compact_public23_frozen',compactor);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
 compact=m.recipe(raw).decode();assert sha(compact.encode())=='fc7b1e9e1b258f5254c75e046972fdc3bdc630b5b20fb35c9821839883c62019'
 anchor='def kernels:Kernels where';assert compact.count(anchor)==1
 result=compact.replace(anchor,parts+anchor)
 assert result.count('dense:=⟨YaV,kernels0.dense.2⟩')==1
 result=result.replace('dense:=⟨YaV,kernels0.dense.2⟩','dense:=⟨YaV,Ya3Q⟩')
 assert result.count('ZcC,T4b,Zdt]')==1
 result=result.replace('ZcC,T4b,Zdt]','ZcC,Zc0Q,T4b,Zdt]')
 out=result.encode();assert len(out)<=256000 and result.count('theorem correct:Obligation kernels:=')==1
 meta={'shared_declarations_byte_identical':{n:sha(a[n].encode())for n in shared},'reused_interface':'ZcC:YaV=linearSpec, original23 proof for actual stronger linear','new_declarations':NAMES,'new_declarations_bytes':len(parts.encode()),'alias_differences_resolved':differences,'small_k_or_nonfinite_fallback':'gemmWith Yn, proved via existing Zi; not sloweroriginalshipped dotSpec direct fallback','changed_runtime':['newYa3Q','kernels.dense.gemm binding'],'retained_23_runtime':'All oldruntime exceptkernels binding byte-identical afterproof-onlycompaction','old27_addRelu_not_copied':'Ybf/YaX nativeadd not present in23. WholeMixer must include this gap; no speculative componentgain.'}
 return out,meta

def transform(raw,submission=23,variant='gemm27-public23',donor_raw=None):
 assert submission==23 and variant=='gemm27-public23'
 if donor_raw is None:
  root=os.environ.get('TORCHLEAN_ROOT')
  donor_path=Path(root)/'r27-source-private/official-27.lean'if root else HERE.parent.parent/'competition-state/source-private/submission27-Kernel.lean'
  donor_raw=donor_path.read_bytes()
 return build(raw,donor_raw)[0]

if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--donor',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes());a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
 r={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'ACTUAL_ALL12_GEMM_GRAFT_CONNECTED_NOT_COMPILED','base23_sha256':BASE_SHA,'donor27_sha256':DONOR_SHA,'candidate_sha256':sha(result),'candidate_bytes':len(result),'free_bytes':256000-len(result),'recipe_sha256':sha(Path(__file__).read_bytes()),'compactor_sha256':COMPACT_SHA,'metadata':meta,'scope':'Fullall12 correct retained andactualgemmproof updated; originalfullgate required beforeacceptance; no nativecostobserved','cost_target':'CurrentMixer36 via exactpublic27reportchain; current-source directmeasurementUNKNOWN','publication':'Ownedrecipe/receipt only; wholethirdparty source private/ephemeral'};a.receipt.write_text(json.dumps(r,indent=2),encoding='utf8');print(json.dumps({k:v for k,v in r.items()if k!='metadata'}))
