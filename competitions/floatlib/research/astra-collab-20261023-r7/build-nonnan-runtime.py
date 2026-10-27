from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,argparse
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--probe',default='f01-r7-nonnan-bridge-probe');ap.add_argument('--name',default='f01-r7-nonnan-runtime');args=ap.parse_args()
assert args.probe.startswith('f01-r7-') and args.name.startswith('f01-r7-')
base=ROOT/'competitions/floatlib/candidates/f01-d5-stream-pack/Kernel.lean'
b=base.read_bytes();assert hashlib.sha256(b).hexdigest()=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
probe=ROOT/'competitions/floatlib/candidates'/args.probe/'Kernel.lean';pb=probe.read_bytes();assert pb.startswith(b)
block=pb[len(b):].decode()
block=block.replace('namespace Submission.NotNaNProbe','namespace NotNaNProbe').replace('end Submission.NotNaNProbe','end NotNaNProbe')
block=block.replace('namespace Submission.R7Native','namespace R7Native').replace('end Submission.R7Native','end R7Native')
s=b.decode();a=s.index('namespace NativeFinal')
tail=s[a:]
assert tail.count('.isFinite = true')==8
tail=tail.replace('.isFinite = true','.isNaN = false')
tail=tail.replace('FinalFinite.add_finite_inputs','NotNaNProbe.add_inputs').replace('FinalFinite.mul_finite_inputs','NotNaNProbe.mul_inputs')
tail=tail.replace('ExecFloat.Binary.ofFloat32_add_of_isFinite','R7Native.ofFloat32Add').replace('NativeBridge.ofFloat32Mul','R7Native.ofFloat32Mul').replace('GuardBridge.finiteRoundtrip','NotNaNProbe.roundtrip')
out=(s[:a]+block+'\n'+tail).encode();dest=ROOT/'competitions/floatlib/candidates'/args.name
dest.mkdir(exist_ok=False)
(dest/'Kernel.lean').write_bytes(out)
m={'candidate':args.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':'f01-d5-stream-pack','parent_sha256':hashlib.sha256(b).hexdigest(),'proof_source':args.probe,'proof_source_sha256':hashlib.sha256(pb).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN','validation_mode':'full-gate','mechanism':'Extend NativeFinal sum/dot, actual Packed10.finish and actual word-sum terminal guards from finite to non-NaN, backed by concrete operation bridges and result-preimage induction. Preserve raw fallback for every NaN, all original layouts, ordered multiplication/addition and scalar entry points.','expected_gain':'UNKNOWN; saves exact replay only for infinity endpoints. Full original new public-suite paired cost required, including unchanged finite path and all NaN fallbacks.','formal_submission':'NOT_SUBMITTED'}
(dest/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
