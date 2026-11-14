"""Exact public23 reciprocal candidate with proof-only existing-alias compaction.

The whole upstream source stays ephemeral. No proof or original runtime
declaration is deleted. The actual candidate requires a fresh all12 gate.
"""
from pathlib import Path
import argparse
from datetime import datetime,timezone
import hashlib
import importlib.util
import json
import types

HERE=Path(__file__).resolve().parent
BASE=HERE.parents[1]
SOURCE_SHA='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
HELPER_SHA='013a5fd2e87c4da32bf791529564b587d67f8a94d096fe9f058826f2a8873dda'
COMPACT_SHA='0b50cfd3470de2e4ddbb39a158af49bb055278b4570765b04ba497af50c57029'

def sha(data): return hashlib.sha256(data).hexdigest()
def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path)
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

def build(data):
    assert sha(data)==SOURCE_SHA
    compactor_path=BASE/'research/board-frontier/compact_public23.py'
    assert sha(compactor_path.read_bytes())==COMPACT_SHA
    compact,changes,skipped=load(compactor_path,'r27_23_compact').transform(data,'proof')
    assert sha(compact)=='fc7b1e9e1b258f5254c75e046972fdc3bdc630b5b20fb35c9821839883c62019'
    # Freeze the exact previous owned recipe and change only its helper input.
    source=(HERE/'public23_reciprocal.py').read_text(encoding='utf-8')
    assert sha(source.encode())=='884e9bb53ec4fb4bc051860a969dbde4e679af5678ec64e0ebb6bd0de5dfa8b8'
    source=source.replace('"ReciprocalUInt64ContractOnly-v3.lean"','"ReciprocalUInt64ContractOnly-v4.lean"')
    m=types.ModuleType('r27_23_reciprocal_v2_frozen');m.__file__=str(HERE/'public23_reciprocal.py')
    exec(compile(source,m.__file__,'exec'),m.__dict__)
    m.PIN=sha(compact);m.OLD_HELPER=HELPER_SHA
    result,helper,metadata=m.transform(compact)
    return result,helper,{'proof_alias_changes':len(changes),'proof_alias_bytes_saved':len(data)-len(compact),
      'proof_alias_skipped':skipped,'helper_compaction':metadata}

def transform(data,submission=23,variant='row-reciprocal23-v2'):
    assert submission==23 and variant=='row-reciprocal23-v2'
    return build(data)[0]

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True)
    p.add_argument('--receipt',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();raw=a.source.read_bytes();result,helper,meta=build(raw)
    if a.output: a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    policy=load(HERE/'patch_public.py','r27_23_policy').policy_check(result)
    receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'id':'public23-row-reciprocal-v2',
      'source23_sha256':SOURCE_SHA,'candidate_sha256':sha(result),'candidate_bytes':len(result),
      'helper_bytes':len(helper.encode()),'free_bytes':256000-len(result),'policy':policy,
      'state':'EXACT_RECIPE_FITS_ORIGINAL_ALL12_DECLARED_NOT_COMPILED',
      'current_normalized_mlp_champion':43,'current43_over_public23_time':.9072362322024092,
      'actual_changed_runtime':['Ya7G three q/r pairs','MYbc one reciprocal per row'],
      'proof':'B explicit Nat cancellation repair plus m64_v bridge; actual Ya7Ge/Zdt changed, no deleted declarations',
      'full_correct':'Original all12 entry retained, actual new theorem paths must elaborate; no accepted-source claim',
      'metadata':meta,'publication':'Own recipe/helper/receipt only; whole source private/ephemeral'}
    a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:v for k,v in receipt.items() if k!='metadata'},indent=2))
