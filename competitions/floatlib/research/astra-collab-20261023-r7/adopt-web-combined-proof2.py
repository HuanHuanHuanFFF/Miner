from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
p=ROOT/'competitions/floatlib/candidates/f01-r7-nonfinite-combined/Kernel.lean';old=p.read_bytes();assert hashlib.sha256(old).hexdigest()=='b1696ff9a51a112c5e34e1a86ef2634c58548492e452199ee041927c6cb5a18d'
web=HERE/'web/R7-W09/original-extracted/R7-W09';new=(web/'fixed/Kernel.lean').read_bytes();assert hashlib.sha256(new).hexdigest()=='0e8bc05ce954e3e8213fbef05ac6041f8f882673c88c1071a3c9d4254a3064cd'
before='''  · rw [R7NaNReplay.replayEarly_eq]
    simp only [R7NaNReplay.replayStep, add_eq, mul_eq]'''
after='''  · refine (R7NaNReplay.replayEarly_eq n baseA baseB p A B).trans ?_
    apply congrArg (fun step : Binary32 → Fin n → Binary32 => Fin.foldl n step posZero)
    funext acc i
    simp only [R7NaNReplay.replayStep, Submission.add_eq, Submission.mul_eq]'''
assert old.decode().replace(before,after).encode()==new
attempt=(web/'logs/Kernel-attempt2.lean').read_bytes();p1=ROOT/'competitions/floatlib/candidates/f01-r7-nonfinite-combined-proof1/Kernel.lean';p1b=p1.read_bytes();assert attempt.decode().split()==p1b.decode().split()
d=ROOT/'competitions/floatlib/candidates/f01-r7-nonfinite-combined-proof2';d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(new)
m=json.loads(p.with_name('manifest.json').read_text());m.update(candidate=d.name,candidate_sha256=hashlib.sha256(new).hexdigest(),candidate_bytes=len(new),parent=p1.parent.name,parent_sha256=hashlib.sha256(p1b).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),proof_status='WEB_FIXED_LEAN_FOUR_ORIGINAL_SPECS_AXIOMS_PASS_FULLGATE_NOT_RUN',repair='Actual independent W09 compile reproduced originalfailure and same-token two-line simpa failure. ExactnewKernel uses explicit congrArg/funext to saturate step before simp. Bytes outside originaldot_eq proof unchanged; fixed file is byte-identical to suppliedsuccessful compile snapshot.',web_evidence='web/R7-W09/original-extracted/R7-W09/verification.json and logs/Kernel-attempt3.*, SpecAudit*; no currentoriginal fullgate/timing claim',expected_gain='UNKNOWN; exactcombined runtime has not reached originalfullgate timing.')
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'original_sha256':hashlib.sha256(old).hexdigest(),'local_proof1_sha256':hashlib.sha256(p1b).hexdigest(),'web_failed_same_token_attempt_sha256':hashlib.sha256(attempt).hexdigest(),'proof1_difference':'Only placement of newline beforeusing; whitespace-token strings identical. This is not a claim that exact39a bytes were compiled.','fixed_sha256':hashlib.sha256(new).hexdigest(),'fixed_bytes':len(new),'exact_four_line_replacement_only':True,'plain_Lean':'SUPPLIED_ACTUAL_FIXED_COMPILER_PASS_WITH_FOUR_SPECS_AXIOMS','fullgate':'NOT_RUN'}
(HERE/'web-proof2-identity.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(m,indent=2))
