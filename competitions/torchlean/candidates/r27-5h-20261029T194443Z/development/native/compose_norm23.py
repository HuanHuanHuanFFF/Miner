"""Prepare a separate exact RMS-terminal/LayerNorm-reciprocal composition.

Do not alter frozen batch6 or infer combined gate/performance from its parts.
This artifact is only a deterministic composition for a later queue decision.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
def sha(data):return hashlib.sha256(data).hexdigest()
def load(name):
 p=HERE/name;sp=importlib.util.spec_from_file_location('r27_compose_'+p.stem,p)
 m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);return m
def transform(raw,submission=23,variant='norm23-rms-reciprocal-compose-v1'):
 assert submission==23 and variant=='norm23-rms-reciprocal-compose-v1'
 assert sha((HERE/'public23_reciprocal_v3.py').read_bytes())=='080584fa0e222c95db517c92802177a405810aaca5020178f9934d08da3c9bb6'
 first=load('public23_reciprocal_v3.py').transform(raw,23,'row-reciprocal23-v3')
 assert sha(first)=='9654b727badce93d0727ece982a0ccedce99107ce98235b18e0e5cdc79e8944e'
 assert sha((HERE/'frozen_rms_native_finish.py').read_bytes())=='51b54a600701c19d03944a05d1d4529adf6dfcef79de2c41d12d313da1fe8e35'
 assert sha((HERE/'RmsNativeFinish.lean.inc').read_bytes())=='460d81146ce96b4a0681afa3df3e7530432b3e16cd937627c86f95dec0adc419'
 second=load('frozen_rms_native_finish.py');second.PIN=sha(first)
 return second.transform(first,23,'rms-native-finish')

if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True)
 p.add_argument('--receipt',type=Path,required=True);p.add_argument('--output',type=Path)
 a=p.parse_args();result=transform(a.source.read_bytes())
 if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
 receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),
  'free_bytes':256000-len(result),'recipe_sha256':sha(Path(__file__).read_bytes()),
  'policy':load('patch_public.py').policy_check(result),
  'state':'COMPOSITION_PREPARED_NOT_QUEUED_NOT_COMPILED_NO_COMBINED_GAIN_CLAIM',
  'actual_all12':'Original entry connects both Ya7Ge/Zdt and C R27RmsFinish_eq/T4b, all still uncompiled',
  'runtime':'Exact batch6 LayerNorm reciprocal mechanism plus C RMS native rrsG terminal; same original statistics/sqrt/fallbacks',
  'freeze':'Batch6 source9654 andc688 unchanged; this is a separate candidate requiring fresh all12 gate and complete measurement',
  'selection':'No default CI request; only after individual cost/profile evidence and D capacity decision',
  'current_target':'NormalizedMLP current43 only through exact report chain, directcurrent source UNKNOWN',
  'publication':'Own frozen helper/recipe/receipt only; whole source private/runner ephemeral'}
 a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps(receipt,indent=2))
