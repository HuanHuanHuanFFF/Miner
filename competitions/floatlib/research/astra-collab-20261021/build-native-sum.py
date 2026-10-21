from pathlib import Path
import hashlib, json, datetime

ROOT=Path(__file__).resolve().parents[4]
HERE=Path(__file__).resolve().parent
BASE=ROOT/'competitions/floatlib/references/official-incumbent/Kernel.lean'
OUT=ROOT/'competitions/floatlib/candidates/f01-r1-native-sum-acc'
assert hashlib.sha256(BASE.read_bytes()).hexdigest()=='5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
s=BASE.read_text(encoding='utf8')
s=s.replace('def sum {n : Nat}', 'def referenceSum {n : Nat}')
s=s.replace('theorem sum_spec :', 'theorem referenceSum_spec :')
s=s.replace('sum x = sumSpec x.get','referenceSum x = sumSpec x.get')
s=s.replace('rw [sum, add_eq,','rw [referenceSum, add_eq,')
fragment=(HERE/'native-sum-loop-fragment.lean').read_text(encoding='utf8')
fragment=fragment[fragment.index('namespace NativeTensor'):]
assert s.endswith('end Submission\n')
s=s.removesuffix('end Submission\n')+fragment+'\nend Submission\n'
OUT.mkdir(parents=True,exist_ok=True)
(OUT/'Kernel.lean').write_text(s,encoding='utf8',newline='\n')
data=(OUT/'Kernel.lean').read_bytes()
out={
 'candidate':OUT.name,'candidate_sha256':hashlib.sha256(data).hexdigest(),
 'kernel_sha256':hashlib.sha256(data).hexdigest(),'kernel_bytes':len(data),
 'baseline_sha256':hashlib.sha256(BASE.read_bytes()).hexdigest(),
 'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'mechanism':'Only sum: direct Option Float32 accumulator loop; finite guards and input raw round-trip check at each step; failure invokes unchanged referenceSum. Success proof follows same Fin.foldl.loop, final native overflow allowed. Scalar add/mul and bmm remain unchanged.',
 'proof_status':'DRAFT_NOT_COMPILED; existing public finite native-add theorem plus recursive success invariant',
 'performance':'NOT_RUN','validation_mode':'full-gate',
 'requested_by_D':'Development feedback at 11:02 UTC requested native sum package, keep unqueued until native-add passes.',
 'minimal_request':'D copy/freeze; first native-add feasibility then statement/full gate; inspect sumTry C for float accumulator and Option allocation only at exit/failure; collect full 12-class25-pair timing.'
}
(OUT/'manifest.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps(out,indent=2))
