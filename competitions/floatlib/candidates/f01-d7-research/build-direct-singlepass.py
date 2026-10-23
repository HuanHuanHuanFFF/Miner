"""Mechanically compose the frozen sum draft and direct-layout draft; no execution claim."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parent
EXPECTED = {
    'f01-r7-nonfinite-combined-proof2': '0e8bc05ce954e3e8213fbef05ac6041f8f882673c88c1071a3c9d4254a3064cd',
    'f01-r7-sum-singlepass-fused-proof1': '3d9b1ea94ec105073334b793adcb5a9fecc4eda37dd2a5809e715b5584a54576',
    'f01-d7-direct-nonfinite': '97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26',
}

def sha(data):
    return hashlib.sha256(data).hexdigest()

sources = {}
for name, digest in EXPECTED.items():
    raw = (CANDIDATES / name / 'Kernel.lean').read_bytes()
    assert sha(raw) == digest, name
    sources[name] = raw
base, parent, direct = (sources[n] for n in EXPECTED)
start = base.rindex(b'\ndef bmm (batch m n p : Nat)')
old_tail = base[start:]
assert old_tail.count(b'theorem bmm_spec') == 1
assert old_tail.rstrip().endswith(b'end Submission')
assert parent.count(old_tail) == 1
assert direct[:start] == base[:start]
replacement = direct[start:]
assert replacement.count(b'def bmmPackedBase ') == 1
assert replacement.count(b'def bmm ') == 1
assert replacement.count(b'namespace Submission.DirectSmall\n') == 1
assert b'R7SinglePassSum' not in replacement
assert b'R7SinglePassSum' in parent
data = parent.replace(old_tail, replacement, 1)
assert data.count(replacement) == 1
assert data.replace(replacement, old_tail, 1) == parent
assert data.count(b'\ndef bmm (') == 1
assert data.count(b'\ndef sum {') == 1
assert data.count(b'\ntheorem bmm_spec ') == 1
assert data.count(b'\ntheorem sum_spec ') == 1
assert data.endswith(parent[parent.rindex(b'namespace R7SinglePassSum'):])
assert len(data) == len(parent) + len(direct) - len(base)
assert len(data) <= 256000
out = CANDIDATES / 'f01-d7-direct-singlepass'
out.mkdir(exist_ok=True)
kernel = out / 'Kernel.lean'
if kernel.exists():
    assert kernel.read_bytes() == data, 'Never overwrite a different draft'
else:
    with kernel.open('xb') as stream:
        stream.write(data)
manifest = {
    'candidate': out.name, 'candidate_file': 'Kernel.lean',
    'candidate_sha256': sha(data), 'candidate_bytes': len(data),
    'created_at_utc': datetime.now(timezone.utc).isoformat(),
    'parent': 'f01-r7-sum-singlepass-fused-proof1', 'parent_sha256': EXPECTED['f01-r7-sum-singlepass-fused-proof1'],
    'layout_parent': 'f01-d7-direct-nonfinite', 'layout_parent_sha256': EXPECTED['f01-d7-direct-nonfinite'],
    'common_base': 'f01-r7-nonfinite-combined-proof2', 'common_base_sha256': EXPECTED['f01-r7-nonfinite-combined-proof2'],
    'proof_status': 'NOT_RUN_EXACT_COMPOSITION', 'validation_mode': 'statement-only-first',
    'mechanism': 'Exact3d9 single-native-prefix sum plus exact97f direct-small BMM dispatch on their common0e8 base. One entire unchanged parent BMM tail is replaced with the already prepared direct tail; all sum additions and scalar declarations remain byte-identical. No new runtime algorithm or proof body is authored.',
    'byte_inverse': {'restores_parent': True, 'old_tail_sha256': sha(old_tail), 'replacement_sha256': sha(replacement), 'delta_bytes': len(replacement)-len(old_tail)},
    'size_preparation': 'Fits original256000-byte limit without removing any comments or attribution.',
    'component_evidence': '60f direct+nonnan full807/809 and9a quiet-NaN full806/808; exact0e8 ordinary public proof only. Exact97f and3d9 remain uncompiled; their gate results cannot be inherited by this combination.',
    'expected_gain': 'UNKNOWN; sum/BMM complete-cost effects require this exact source, not multiplied standalone gains.',
    'next_validation': 'Compile exact source and four original obligations first; then original public-v2 fullgate against retained60f. If useful, freeze and confirm on independent newseed/newrunner with all observers off.',
    'formal_submission': 'NOT_SUBMITTED',
}
manifest_path = out / 'manifest.json'
if not manifest_path.exists():
    manifest_path.write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n', encoding='utf8')
else:
    existing = json.loads(manifest_path.read_bytes())
    assert existing['candidate_sha256'] == manifest['candidate_sha256']
print(json.dumps({'candidate': out.name, 'sha256': sha(data), 'bytes': len(data), 'byte_inverse': manifest['byte_inverse'], 'compile_fullgate_performance': 'NOT_RUN'}))
