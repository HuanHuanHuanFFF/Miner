from pathlib import Path
import datetime, hashlib, json

here = Path(__file__).resolve().parent
root = here.parents[3]
base = root / 'competitions/floatlib/candidates/f01-d1-native-both-proof1/Kernel.lean'
assert hashlib.sha256(base.read_bytes()).hexdigest() == '707d22fed8443d883a183983397496492f9a09e071ffcf2715ef818384e44b85'
fragment = here / 'final-finite-preimage.lean'
out = root / 'competitions/floatlib/candidates/f01-r2-final-finite-preimage'
out.mkdir(exist_ok=True)
kernel = out / 'Kernel.lean'
assert not kernel.exists(), 'Frozen candidate exists; use a new name for revisions.'
source = base.read_text(encoding='utf-8') + '\n' + fragment.read_text(encoding='utf-8').removeprefix('import ContractTensor\n')
kernel.write_text(source, encoding='utf-8', newline='\n')
data = kernel.read_bytes()
manifest = {
 'candidate': out.name, 'candidate_file': 'Kernel.lean',
 'candidate_sha256': hashlib.sha256(data).hexdigest(), 'candidate_bytes': len(data),
 'parent': base.parent.name, 'parent_sha256': hashlib.sha256(base.read_bytes()).hexdigest(),
 'fragment_sha256': hashlib.sha256(fragment.read_bytes()).hexdigest(),
 'proof_status': 'NOT_RUN: key lemma feasibility draft',
 'runtime_change': 'NONE; append finite-result preimage lemmas to validated native-both package',
 'minimal_request': 'D copies frozen source to owned candidate, runs statement-only feasibility. No benchmark needed until production final-finite loop consumes the lemmas.',
 'created_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'formal_submission': 'NOT_SUBMITTED'
}
(out/'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
print(json.dumps(manifest, indent=2))
