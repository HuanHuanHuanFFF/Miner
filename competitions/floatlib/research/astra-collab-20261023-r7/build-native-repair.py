from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--parent',default='f01-r7-nonfinite-combined');ap.add_argument('--name',default='f01-r7-native-repair');args=ap.parse_args()
assert args.parent.startswith('f01-r7-') and args.name.startswith('f01-r7-')
p=ROOT/'competitions/floatlib/candidates'/args.parent/'Kernel.lean';b=p.read_bytes();pm=json.loads(p.with_name('manifest.json').read_text());assert hashlib.sha256(b).hexdigest()==pm['candidate_sha256']
s=b.decode();a=s.index('namespace R7NaNReplay');z=s.index('end R7NaNReplay',a);block=s[a:z]
assert 'namespace R7Native' in s[:a]
addition=(HERE/'native-repair-block.lean').read_text()
if 'R7W01b.rawExecQuietGuard' in block:addition=addition.replace('R7W01.execQuietGuard','R7W01b.rawExecQuietGuard')
marker='def replayEarly (n baseA baseB p : Nat)';assert block.count(marker)==1
block=block.replace(marker,addition+'\n'+marker)
old='''def replayEarly (n baseA baseB p : Nat) (Araw Braw : Array Binary32) : Binary32 :=
  replayLoop n baseA baseB p Araw Braw 0 posZero'''
new='''def replayEarly (n baseA baseB p : Nat) (Araw Braw : Array Binary32) : Binary32 :=
  nativeReplay n baseA baseB p Araw Braw'''
assert block.count(old)==1;block=block.replace(old,new)
old='  exact replayLoop_eq n baseA baseB p Araw Braw 0 posZero';new='  exact nativeReplay_eq n baseA baseB p Araw Braw'
assert block.count(old)==1;block=block.replace(old,new)
out=(s[:a]+block+s[z:]).encode();d=ROOT/'competitions/floatlib/candidates'/args.name;d.mkdir(exist_ok=False)
(d/'Kernel.lean').write_bytes(out)
m={'candidate':args.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':args.parent,'parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN_NEW_MECHANISM','validation_mode':'full-gate','mechanism':'NaN endpoint fallback replays native prefix and converts only at a first NaN event; compute one exact raw step, stop if quiet, otherwise retain exact old suffix fold. Accepted non-NaN per-step bridges prove native prefix equality, actual quiet absorption proves stop. First full native pass remains; no index list or reordered arithmetic.','expected_gain':'UNKNOWN; includes first native pass plus prefix predicate/conversion/array costs and exact repair, not only saved scalar operations. Full current-public paired gate required.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
