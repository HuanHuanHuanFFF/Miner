from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
p=ROOT/'competitions/floatlib/candidates/f01-d5-stream-pack/Kernel.lean';b=p.read_bytes()
assert hashlib.sha256(b).hexdigest()=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
web=HERE/'web/R7-W01/original-extracted/R7-W01/R7W01.lean';wb=web.read_bytes()
assert hashlib.sha256(wb).hexdigest()=='9f534421b8dbf6ce852eb4218003567ee09cc42c399fac075f61c6edfa2a1fea'
proof=wb.decode().split('def execDotFold')[0]+'\nend R7W01\n'
removed_prints=len(re.findall(r'^#print.*$',proof,re.M))
proof=re.sub(r'^#print.*\n','',proof,flags=re.M)
assert proof.startswith('import ContractTensor\n')
proof=proof[len('import ContractTensor\n'):]
proof=re.sub(r'\bimport\b','dependency',proof)
proof='section R7NaNProof\n'+proof+'\nend R7NaNProof\n'
s=b.decode();s=s.replace('import ContractTensor\n','import ContractTensor\n\n'+proof+'\n',1)
marker='/-- The result guard and exact fallback are the same as in the scalar implementation. -/'
assert s.count(marker)==1
s=s.replace(marker,(HERE/'nan-replay-block.lean').read_text()+'\n'+marker)
old='''  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else Fin.foldl n
    (fun a i => Submission.add a
      (Submission.mul (Araw.getD (baseA + i.val) posZero)
        (Braw.getD (baseB + i.val * p) posZero))) posZero'''
new='''  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else replay n baseA baseB p Araw Braw result'''
assert s.count(old)==1;s=s.replace(old,new)
a=s.index('theorem finish_eq_dot ');z=s.index('theorem finish_eq_fold ',a)
piece=s[a:z];old='  rw [hs] <;> rfl';new='  unfold finish\n  simp only [replay_eq]\n  rw [hs] <;> rfl';assert piece.count(old)==1
s=s[:a]+piece.replace(old,new)+s[z:]
out=s.encode();d=ROOT/'competitions/floatlib/candidates/f01-r7-nan-replay-nat';d.mkdir(exist_ok=False)
(d/'Kernel.lean').write_bytes(out)
m={'candidate':d.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':'f01-d5-stream-pack','parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN_INTEGRATED_SOURCE','validation_mode':'full-gate','web_proof_original_sha256':hashlib.sha256(wb).hexdigest(),'web_evidence':'Supplied logs report exact Lean4.34 ContractTensor compile and27 allowed-axiom audits. This integrated source has not inherited gate/replay acceptance.','mechanism':'Only actual Packed10.finish NaN fallback: use an ordered Nat recursion, stop on exact quiet NaN before further array reads/multiply/add. Preserve tuned Submission scalar steps and raw payload/sign. No List.finRange allocation; finite and infinity endpoints retain prior behavior.','proof_derivation':f'Use web proof prefix through execQuietGuard, remove{removed_prints} audit commands and dependency keyword in comments, scope global opens with section; arithmetic theorem bodies unchanged. New Nat loop/fallback equality connects actual bmm_spec.','expected_gain':'UNKNOWN; target poisoned BMM suffix arithmetic, but finite prefix guard cost and NaN endpoint classifier included. Full current public-suite paired original cost and independent confirmation required.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
