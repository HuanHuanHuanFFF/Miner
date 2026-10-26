"""Declare one first clean cost test after independent selected-path review."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

here = Path(__file__).resolve().parent
root = here.parents[4]
sha = lambda raw: hashlib.sha256(raw).hexdigest()
read = lambda p: json.loads(p.read_bytes())
save = lambda p, value: p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())
state = read(root / 'competitions/floatlib/coordination/development-status.json')
assert state['research_round']['id'] == 'R19-20261026T194639Z' and not state['research_round']['active_ci']
path = root / 'competitions/floatlib/candidates/f01-r19-dev-compact-scales1/manifest.json'
manifest = read(path)
source = path.with_name('Kernel.lean')
assert sha(source.read_bytes()) == manifest['candidate_sha256'] == '9c4e9505702231fdb93f47f8d767ba0b2b0c2ad7ec48d8894b5a53ba87657645'
assert manifest['proof_status'] == 'STATEMENT_WHOLE_MODULE_AND_10_HELPERS_PASS'
assert manifest['activation']['valid'] is True and manifest['activation']['size'] == 512
review = here / 'development-workers/anchor-323/compact-scales-review/README.md'
assert review.is_file() and (review.parent / 'cost-review.json').is_file()
manifest.update(validation_mode='full-gate', performance='NOT_RUN_FIRST_CLEAN_D_PENDING',
    selected_path_review={'path': review.relative_to(root).as_posix(), 'sha256': sha(review.read_bytes()),
        'scope': 'Actual statement diagnostic MainFull path, not timed object. Added flag/narrowing costs retained; no predicted speed.'})
save(path, manifest)

# Reserve explicit diagnostic hook names before any clean D freezes execution.
# They are inactive for scored sources; later experiments need no gate-file change.
diagnostic = root / 'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
old = diagnostic.read_bytes()
before = b"'development-resource-audit.py')"
after = b"'development-resource-audit.py', 'development-resource-audit-v2.py', 'development-route-audit.py')"
assert old.count(before) == 1
new = old.replace(before, after)
diagnostic.write_bytes(new)
save(here / 'development-compact-first-cost-decision.json', {
    'at_utc': datetime.now(timezone.utc).isoformat(), 'candidate': manifest['candidate'], 'sha256': manifest['candidate_sha256'],
    'decision': 'One original clean full D with B2/control41, no observer or proof-only rows; no A/B before threshold',
    'selected_review': manifest['selected_path_review'],
    'new_diagnostic_names': ['development-resource-audit-v2.py', 'development-route-audit.py'],
    'old_diagnostic_sha256': sha(old), 'new_diagnostic_sha256': sha(new),
    'scope': 'Explicit diagnostic module hooks only; no candidate references them in this scored D, original official gate/flags/thresholds unchanged',
})
print(json.dumps({'candidate': manifest['candidate'], 'source': manifest['candidate_sha256'], 'new_diagnostic_sha256': sha(new)}))
