from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,re
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--parent',default='f01-r7-nonfinite-combined');ap.add_argument('--name',default='f01-r7-sum-native-repair');args=ap.parse_args()
assert args.parent.startswith('f01-r7-') and args.name.startswith('f01-r7-')
p=ROOT/'competitions/floatlib/candidates'/args.parent/'Kernel.lean';b=p.read_bytes();pm=json.loads(p.with_name('manifest.json').read_text());assert hashlib.sha256(b).hexdigest()==pm['candidate_sha256']
w=HERE/'web/R7-W02/original-extracted/R7-W02/R7W02Append.lean';wb=w.read_bytes();assert hashlib.sha256(wb).hexdigest()=='7f2ebdf61b60cc51bbb0a9d27eff5447dedc304cc43c2fd4f64f8511aaa710f4'
proof=wb.decode().split('/- Append after the concretely proved Raw.lean and Step.lean.')[0]
assert proof.rstrip().endswith('end R7W02') and '#print' not in proof
proof=re.sub(r'\bimport\b','dependency',proof)
proof='section R7SumProof\n'+proof+'\nend R7SumProof\n'
s=b.decode();marker='end R7NaNProof';assert s.count(marker)==1;s=s.replace(marker,marker+'\n\n'+proof)
assert s.count('namespace NativeFinal')==1
s=s.replace('namespace NativeFinal',(HERE/'sum-native-repair-block.lean').read_text()+'\nnamespace NativeFinal')
assert s.count('  else referenceSum x')==2;s=s.replace('  else referenceSum x','  else R7SumRepair.run x')
assert s.count('  · exact referenceSum_spec n x')==1;s=s.replace('  · exact referenceSum_spec n x','  · exact R7SumRepair.run_spec n x')
out=s.encode();d=ROOT/'competitions/floatlib/candidates'/args.name;d.mkdir(exist_ok=False)
(d/'Kernel.lean').write_bytes(out)
m={'candidate':args.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':args.parent,'parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN_NEW_MECHANISM','validation_mode':'full-gate','web_proof_original_sha256':hashlib.sha256(wb).hexdigest(),'proof_derivation':'W02 concrete raw/classifier/codec and step prefix only; namespace section contains opens, no arithmetic proof body changes; new Nat vector loops use concrete nonNaN bridges and preserve original sumSpec order.','mechanism':'Only NaN endpoint sum fallback: native second prefix, one exact raw repair at first NaN, then exact raw signaling scan of all remaining inputs. Original first native USize loop untouched. Quiet premise explicitly proved at scan handoff; otherwise full exact cold suffix retained. BMM/scalars unchanged from parent.','expected_gain':'UNKNOWN; complete cost includes original native pass, native second-prefix predicates/conversion and full remaining raw scan. Not ordinary-sum early absorption and no List construction.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
