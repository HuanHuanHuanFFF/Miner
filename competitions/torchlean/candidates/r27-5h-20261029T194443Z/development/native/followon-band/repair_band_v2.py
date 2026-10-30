"""Actual CI11 two-literal type repair only; frozen4a9 source untouched."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,types
HERE=Path(__file__).resolve().parent
def sha(x):return hashlib.sha256(x).hexdigest()
def transform(raw,submission=23,variant='band64-native-cost-v2-types'):
 assert submission==23 and variant=='band64-native-cost-v2-types'
 old=(HERE/'build_band_cost.py').read_bytes();assert sha(old)=='3df1c74bbd5c695df3b464d70ac75c36b368c00e5c1371b4d4359311c76dbe7f'
 code=old.decode().replace("HERE/'BandRuntime.lean.inc'","HERE/'BandRuntime-v2.lean.inc'")
 code=code.replace('32d8265764f818866634a2d4be978e5629767cb6c6ee643801512664784a5a26','5214b64ae10f5699d4d386c440aecf2e8c2944b1004d0a804ddbf812ca353c8b')
 m=types.ModuleType('r27_band_actual_type_repair');m.__file__=str(HERE/'build_band_cost.py')
 exec(compile(code,m.__file__,'exec'),m.__dict__)
 return m.transform(raw,23,'band64-native-cost-v1')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True)
 a=p.parse_args();result=transform(a.source.read_bytes())
 sp=importlib.util.spec_from_file_location('r27_band_repair_policy',HERE.parent/'patch_public.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),
  'recipe_sha256':sha(Path(__file__).read_bytes()),'helper_sha256':sha((HERE/'BandRuntime-v2.lean.inc').read_bytes()),
  'policy':m.policy_check(result),'state':'ACTUAL_CI11_TWO_LITERAL_TYPE_REPAIR_NOT_COMPILED_NO_NEW_CORRECT',
  'actual_errors':[{'line':2973,'message':'HSub Nat UInt64; annotate merge signextension0 as UInt64'},
                   {'line':3055,'message':'literal1 forces Nat comparison; annotate weightminimum1 as UInt64'}],
  'original_run':40975355668,'original_source_sha256':'4a9cb398cb45df02c977604e7968648716250af5e0a0dfa99a8068e8b00b8f9b',
  'original_build_log_sha256':'826540a56170aab0544ca08a559f45cdd8995abf539fc7e40d35b143f1f7aa29',
  'original_result':'Owned build failed, no candidate native timings or checksums; not algorithm negative',
  'runtime_delta':'Only two constant type annotations; intended UInt64 carrier/guard matches pre-freeze model, no algorithm/threshold/preparation change',
  'selection':'No newlong CI request after00:00. D alone decides any bounded continuation of alreadybegun11; otherwise retain nextwindow. Changed source needs exact build/freshgroup ifmeasured',
  'proof':'NativeOnly, retainedCorrect only oldkernels, actualall12 theorem absent',
  'publication':'Own fragments/recipe/receipts; fullsource private/ephemeral'}
 a.receipt.write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
