"""Freeze public23 block16 native screen with fixed16 word sum.

Only self-authored provider changes; no added all12 correctness assertion.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,types
HERE=Path(__file__).resolve().parent
def sha(data):return hashlib.sha256(data).hexdigest()
def transform(raw,submission=23,variant='prepared-block16-unrolled-native-cost-v2'):
 assert submission==23 and variant=='prepared-block16-unrolled-native-cost-v2'
 original=(HERE/'public23_block16_cost.py').read_bytes()
 assert sha(original)=='e63fa1eab138db7bdea0f71cf520fe246287e2ee1798dc2c4f6debc5f33f196a'
 source=original.decode().replace("HERE/'Block16Prepared.lean.inc'","HERE/'Block16PreparedUnrolled.lean.inc'")
 m=types.ModuleType('r27_block16_unroll_frozen');m.__file__=str(HERE/'public23_block16_cost.py')
 exec(compile(source,m.__file__,'exec'),m.__dict__)
 return m.transform(raw,23,'prepared-block16-native-cost-v1')

if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True)
 p.add_argument('--receipt',type=Path,required=True);p.add_argument('--output',type=Path)
 a=p.parse_args();result=transform(a.source.read_bytes())
 if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
 sp=importlib.util.spec_from_file_location('r27_block2_policy',HERE/'patch_public.py')
 m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
 receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'name':'public23-prepared-block16-unrolled-native-cost-v2',
  'source_sha256':'1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe',
  'candidate_sha256':sha(result),'candidate_bytes':len(result),'free_bytes':256000-len(result),
  'recipe_sha256':sha(Path(__file__).read_bytes()),'helper_sha256':sha((HERE/'Block16PreparedUnrolled.lean.inc').read_bytes()),
  'policy':m.policy_check(result),'state':'NATIVE_RESEARCH_ONLY_NO_NEW_CORRECT_NOT_COMPILED',
  'actual_correct':False,'old_proof':'retainedCorrect binds only retainedKernels after proof-only alias compaction',
  'scope':'Rows1 prepared dense dots, per-dot sumspan<=11. Existing P/I/BX/BV caches, sparse pruning, remaining dot/native paths, bias YL+YD endpoint reused',
  'mechanism':'Fixed16 sum of existing signed products, one high/sign merge per block; remaining<16 terms go through original QY6G',
  'model':'block16-model.json,228cases/79308terms,0mismatch; span12 witness fails as expected. Finite only',
  'v1_status':'Nat-fuel sum not compiled or timed, not claimed negative; unrolled v2 preferred to remove obvious per-MAC fuel overhead',
  'formal_interface':'B WordMod3 block_exact accepted generic root only; actual factor/guard/carry/finish connection remains UNKNOWN',
  'whole_model_gain':'UNKNOWN. Conditional second cost route after primary norm reciprocal; no default extra queue',
  'publication':'Own source fragment/recipes/receipts only; whole source private/runner ephemeral'}
 a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps(receipt,indent=2))
