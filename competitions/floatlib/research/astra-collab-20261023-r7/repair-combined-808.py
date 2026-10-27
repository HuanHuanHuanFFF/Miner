from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
ROOT=Path(__file__).resolve().parents[4]
p=ROOT/'competitions/floatlib/candidates/f01-r7-nonfinite-combined/Kernel.lean';b=p.read_bytes();assert hashlib.sha256(b).hexdigest()=='b1696ff9a51a112c5e34e1a86ef2634c58548492e452199ee041927c6cb5a18d'
old='''  · rw [R7NaNReplay.replayEarly_eq]
    simp only [R7NaNReplay.replayStep, add_eq, mul_eq]'''
new='''  · simpa only [R7NaNReplay.replayStep, Submission.add_eq, Submission.mul_eq] using
      (R7NaNReplay.replayEarly_eq n baseA baseB p A B)'''
s=b.decode();assert s.count(old)==1;s=s.replace(old,new);out=s.encode();d=ROOT/'competitions/floatlib/candidates/f01-r7-nonfinite-combined-proof1';d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(out)
m=json.loads(p.with_name('manifest.json').read_text());m.update(candidate=d.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=p.parent.name,parent_sha256=hashlib.sha256(b).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),proof_status='NOT_RUN_PROOF_REPAIR_AFTER_ACTUAL_808_FAILURE',repair='808 exactb169 failed only NativeFinal.dot_eq line3262 simp made no progress. Use direct simpa of the concrete replayEarly_eq theorem with fully qualified scalar equivalences instead of rewriting the goal then requiring a simplifier progress step. Runtime definitions unchanged; original failure preserved.',expected_gain='UNKNOWN; original combined source did not reach timing. Full original gate required.')
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
