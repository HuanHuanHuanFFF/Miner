from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--nan',default='f01-r7-nan-replay-fullpath');ap.add_argument('--name',default='f01-r7-nonfinite-combined');args=ap.parse_args()
assert args.nan.startswith('f01-r7-') and args.name.startswith('f01-r7-')
base=ROOT/'competitions/floatlib/candidates'/args.nan/'Kernel.lean';b=base.read_bytes()
bm=json.loads(base.with_name('manifest.json').read_text());assert hashlib.sha256(b).hexdigest()==bm['candidate_sha256']
ancestor=(ROOT/'competitions/floatlib/candidates/f01-d5-stream-pack/Kernel.lean').read_bytes()
assert hashlib.sha256(ancestor).hexdigest()=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
probe=(ROOT/'competitions/floatlib/candidates/f01-r7-nonnan-bridge-probe/Kernel.lean').read_bytes()
assert hashlib.sha256(probe).hexdigest()=='bb199701f2b653192f15117c29da116eed50314b3949b3fff6c37cdaaf1a5517' and probe.startswith(ancestor)
extra=probe[len(ancestor):].decode()
extra=extra.replace('namespace Submission.NotNaNProbe','namespace NotNaNProbe').replace('end Submission.NotNaNProbe','end NotNaNProbe').replace('namespace Submission.R7Native','namespace R7Native').replace('end Submission.R7Native','end R7Native')
s=b.decode();marker='namespace R7NaNReplay';assert s.count(marker)==1
s=s.replace(marker,extra+'\n'+marker)
a=s.index('namespace NativeFinal');tail=s[a:];assert tail.count('.isFinite = true')==8
tail=tail.replace('.isFinite = true','.isNaN = false').replace('FinalFinite.add_finite_inputs','NotNaNProbe.add_inputs').replace('FinalFinite.mul_finite_inputs','NotNaNProbe.mul_inputs').replace('ExecFloat.Binary.ofFloat32_add_of_isFinite','R7Native.ofFloat32Add').replace('NativeBridge.ofFloat32Mul','R7Native.ofFloat32Mul').replace('GuardBridge.finiteRoundtrip','NotNaNProbe.roundtrip')
for arrays in ['A B','Araw Braw']:
    old='  else R7NaNReplay.replay n baseA baseB p '+arrays+' result'
    assert tail.count(old)==1
    tail=tail.replace(old,'  else R7NaNReplay.replayEarly n baseA baseB p '+arrays)
old='''  · rw [R7NaNReplay.replay_eq]
    simp only [add_eq, mul_eq]'''
new='''  · rw [R7NaNReplay.replayEarly_eq]
    simp only [R7NaNReplay.replayStep, add_eq, mul_eq]'''
assert tail.count(old)==1;tail=tail.replace(old,new)
out=(s[:a]+tail).encode();d=ROOT/'competitions/floatlib/candidates'/args.name;d.mkdir(exist_ok=False)
(d/'Kernel.lean').write_bytes(out)
m={'candidate':args.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parents':[{'candidate':args.nan,'sha256':hashlib.sha256(b).hexdigest()},{'candidate':'f01-r7-nonnan-runtime','sha256':'c76056882d69a1122da44b4bc0bb3ab5274251826f0677af2aec5771926d7435'}],'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN_NEW_COMBINATION','validation_mode':'full-gate','mechanism':'Combine exact non-NaN terminal acceptance for sum/dot with selected quiet-NaN dot suffix replay. Common8eb ancestor; no layout change. Both actual NativeFinal.dot/Packed10.finish call replayEarly directly after the non-NaN guard, removing the now-redundant second endpoint classifier by the full replayEarly_eq theorem.','expected_gain':'UNKNOWN; component gains cannot be added. Requires exact combined-source current-public full gate and paired complete cost.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
