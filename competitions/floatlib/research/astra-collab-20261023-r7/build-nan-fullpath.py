from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
p=ROOT/'competitions/floatlib/candidates/f01-r7-nan-replay-nat/Kernel.lean';b=p.read_bytes()
assert hashlib.sha256(b).hexdigest()=='044c43d2c36ab9bbc4fc4178e733a8c4ce48e0412faad6c2f6bdfa882cf2bc8e'
s=b.decode();a=s.index('/-- The original exact software step, retaining the tuned scalar entry points. -/')
marker='/-- The result guard and exact fallback are the same as in the scalar implementation. -/'
z=s.index(marker,a);block=s[a:z];s=s[:a]+s[z:]
assert s.count('namespace NativeFinal')==1
s=s.replace('namespace NativeFinal','namespace R7NaNReplay\n\nopen FloatLib.Floats Competition\n\n'+block+'\nend R7NaNReplay\n\nnamespace NativeFinal')
s=s.replace('  else replay n baseA baseB p Araw Braw result','  else R7NaNReplay.replay n baseA baseB p Araw Braw result')
old='''  unfold finish
  simp only [replay_eq]
  rw [hs] <;> rfl'''
assert s.count(old)==1;s=s.replace(old,'  rw [hs] <;> rfl')
a=s.index('def dot (n baseA baseB p : Nat)');z=s.index('end NativeFinal',a)
piece=s[a:z]
old='''  else Fin.foldl n
    (fun a i => add a (mul (A.getD (baseA + i.val) posZero)
      (B.getD (baseB + i.val * p) posZero))) posZero'''
assert piece.count(old)==1
piece=piece.replace(old,'  else R7NaNReplay.replay n baseA baseB p A B result')
old='  · simp only [add_eq, mul_eq]'
assert piece.count(old)==1
piece=piece.replace(old,'  · rw [R7NaNReplay.replay_eq]\n    simp only [add_eq, mul_eq]')
s=s[:a]+piece+s[z:]
out=s.encode();d=ROOT/'competitions/floatlib/candidates/f01-r7-nan-replay-fullpath';d.mkdir(exist_ok=False)
(d/'Kernel.lean').write_bytes(out)
m=json.loads(p.with_name('manifest.json').read_text());m.update(candidate=d.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=p.parent.name,parent_sha256=hashlib.sha256(b).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),proof_status='NOT_RUN_INTEGRATED_SOURCE',mechanism='Exact quiet-NaN absorbing suffix early stop via ordered Nat loop, no index list, tuned Submission scalar steps. Shared replay affects both actual Packed10.finish and NativeFinal.dot; each uses it only for NaN endpoint. Covers packed path now and direct-small composition later. Scalar entries/sum/layout/native finite/infinity paths unchanged.',expected_gain='UNKNOWN; complete new-public-suite gate required. Original044c draft is packed-finish-only and is not requested as a duplicate queue item.')
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
