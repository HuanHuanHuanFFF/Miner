from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json

here = Path(__file__).resolve().parent
repo = next(p for p in here.parents if (p / 'AGENTS.md').is_file())
round_dir = here.parents[1]
archive = round_dir / 'ci-runs/40607316341/download-86f74aadcd134570a1c86bacf233a1b2'
suite = archive / 'diagnostics/f01-d7-public-suite/public-suite'
diag = suite / 'diagnostics/f01-r22-dev-multistatic-cost1'
cost = diag / 'runtime-cost'

def record(p):
    b = p.read_bytes()
    return {'path': p.relative_to(repo).as_posix(), 'sha256': sha256(b).hexdigest(), 'bytes': len(b)}

result = json.loads((cost / 'result.json').read_text())
prepare = json.loads((cost / 'prepare.json').read_text())
index = json.loads((diag / 'native-assembly-index.json').read_text())
assert result['complete'] and result['measurement_complete'] and result['official_originals_unchanged']
assert result['source_sha256'] == 'fd4e5b5144d00f3413b0b367a748e9be8f55d51017b4a8aaa5be53d404b1d6c1'
kernel = suite / 'inputs/f01-r22-dev-multistatic-cost1/Kernel.lean'
assert sha256(kernel.read_bytes()).hexdigest() == result['source_sha256']
runtime = (here / 'Runtime.lean.inc').read_bytes()
assert sha256(runtime).hexdigest() == 'e51a67d6188b2ec4c8701cd991e942296fdc7d6158fdb8d92c4e42852bd01709'
assert kernel.read_bytes().count(runtime) == 1
rows = []
for pair in result['pairs']:
    assert pair['same_seed_checksums_match']
    for block in (0, 1):
        item = pair[f'nativeprod_block_{block}']
        rows.append({'seed': pair['seed'], 'block': block,
                     'mul_ratio': item['mul']['variant_over_control'],
                     'whole_ratio': item['whole']['variant_over_control']})
assert len(rows) == 4 and all(r['mul_ratio'] > 1 for r in rows)
object_hash = next(v for p, v in prepare['original_build_before'].items() if p.endswith('/Submission.c.o.export'))
selected = [r for r in index if any(s in r.get('symbol', '') for s in
    ('R22OutlineMul_diagnosticEntry', 'R22OutlineMul_guardedMul', 'R22OutlineMul_retainedMul', 'R22Resident16_guarded'))]
assert len(selected) == 4
for item in selected:
    assert item['object_sha256'] == object_hash and item['exit_code'] == 0
    assert record(diag / item['file'])['sha256'] == item['sha256']
files = [kernel, cost / 'result.json', cost / 'prepare.json', cost / 'static-callback-audit.json',
         diag / 'native-assembly-index.json', round_dir / 'development-multistatic-first-summary.json']
out = {
    'checked_utc': datetime.now(timezone.utc).isoformat(),
    'run': 40607316341,
    'decision': 'PARK_EXACT_DIRECT_PRODUCT_SCALE_COMPLETE_COST_NEGATIVE',
    'native_product_blocks': rows,
    'runtime_sha256': sha256(runtime).hexdigest(),
    'source_sha256': result['source_sha256'],
    'files': [record(p) for p in files],
    'outer_capture_resolution': {
        'state': 'PREVIOUS_CONDITIONAL_GAP_CLOSED_BY_OUTER_ARTIFACTS',
        'submission_object_sha256': object_hash,
        'matching_original_build_before': True,
        'original_build_unchanged_after_timing': result['official_originals_unchanged'],
        'selected_asm': selected,
        'scope': 'Actual external-body evidence exists; this receipt does not repeat its semantic ASM review or attribute cycles.'
    },
    'new_math_fragments': 'GuardFields and A NativeScaleBridges remain NOT_RUN',
    'full_new_mul_spec': 'NOT_PROVED',
    'original25_round_score': 'NOT_RUN',
    'next': 'No new direct-product public assembly/proof/reseed; retain components and respond to real cold-outline typing feedback'
}
(here / 'cost-decision-40607316341.json').write_text(json.dumps(out, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'decision': out['decision'], 'blocks': rows, 'outer_capture_gap': 'CLOSED'}, ensure_ascii=False))
