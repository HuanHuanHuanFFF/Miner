"""Prepared optional mechanism; run only after baseline sum-prefix feedback warrants it."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--parent',default='f01-r7-sum-native-repair');ap.add_argument('--name',default='f01-r7-sum-reverse-suffix');args=ap.parse_args()
assert args.parent.startswith('f01-r7-') and args.name.startswith('f01-r7-')
p=ROOT/'competitions/floatlib/candidates'/args.parent/'Kernel.lean';b=p.read_bytes();pm=json.loads(p.with_name('manifest.json').read_text());assert hashlib.sha256(b).hexdigest()==pm['candidate_sha256']
s=b.decode();a=s.index('namespace R7SumRepair');z=s.index('end R7SumRepair',a);block=s[a:z]
marker='theorem nativeStep_eq (acc : Float32)';assert block.count(marker)==1
block=block.replace(marker,(HERE/'sum-reverse-suffix-block.lean').read_text()+'\n'+marker)
old='if R7W01.execQuietGuard repaired then suffixLoop x (k + 1) repaired';assert block.count(old)==1;block=block.replace(old,old.replace('then suffixLoop','then reverseSuffix'))
old='        exact suffixLoop_eq x (k + 1) _ hquiet';assert block.count(old)==1;block=block.replace(old,'        rw [reverseSuffix_eq]\n'+old)
out=(s[:a]+block+s[z:]).encode();d=ROOT/'competitions/floatlib/candidates'/args.name;d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(out)
m={'candidate':args.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':args.parent,'parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN_NEW_MECHANISM','validation_mode':'full-gate','mechanism':'Only after sum native-prefix exact repair establishes quiet seed, scan remaining originalVector backwards; last signaling word stops scan, otherwise retain seed. Exact new scanner-to-forward-scanner proof plus existing actual addition bridge; no listconstruction, original nativepass/prefix unchanged.','expected_gain':'UNKNOWN; baselineforwardscan must pass first, then full cost pairedcomparison required.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
