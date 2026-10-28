from pathlib import Path
import hashlib, json
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[6]
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/matrix-structure/grs-jam-math'

def digest(p):
    b = p.read_bytes()
    return {'path': str(p), 'bytes': len(b), 'sha256': hashlib.sha256(b).hexdigest()}

accepted = json.loads((OLD / 'accepted.json').read_text())
checks = []
for name, item in accepted['bindings'].items():
    actual = digest(Path(item['path']))
    assert actual['sha256'] == item['sha256'] and actual['bytes'] == item['bytes'], name
    checks.append({'name': name, **actual})
verdict = json.loads(Path(accepted['bindings']['verdict']['path']).read_text())
audit = json.loads(Path(accepted['bindings']['helper_audit']['path']).read_text())
assert verdict['passed'] and verdict['mode'] == 'diagnostic-statement-only'
assert audit['accepted'] and audit['kernel_replay'] and len(audit['names']) == 15
assert 'R19JamVariableProbe.rne_jam' in audit['names']
assert 'R19JamVariableProbe.jam_add_even' not in audit['names']
source = Path(accepted['bindings']['source']['path']).read_text()
assert 'theorem rne_jam' in source and 'theorem jam_add_even' not in source
fragment = digest(OLD / 'JamTranslate.lean.inc')
assert fragment['sha256'] == 'c9e0cfb3b59f7eb45f8c5cdc281eb54b4598b080c2c43aae100e04df12237542'
frozen = []
for file, sha in [
    ('Runtime-broad-word-add.lean.inc', '5655df5c8a8fbfbf40101bba782788d4a59ee716a95ab8e2bd58bff05e715bf9'),
    ('Kernel-broad-word-add-probe.lean', '0274763264d760775e6a447848e873db418adc2e6fb651d117c5fc04b4b5d4a5')]:
    item = digest(HERE / file)
    assert item['sha256'] == sha
    frozen.append(item)
result = {
    'recorded_utc': datetime.now(timezone.utc).isoformat(),
    'script': digest(Path(__file__)), 'old_accepted_index': digest(OLD / 'accepted.json'),
    'old_run': accepted['run'], 'old_mode': verdict['mode'],
    'seven_originals_rehashed': checks, 'rne_jam': 'VERIFIED_OLD_NAT_HELPER',
    'jam_add_even': {'status': 'NOT_RUN_ABSENT_FROM_ACCEPTED_SOURCE_AND_ROOTS', **fragment},
    'carry1_interface': 'rne_jam T 1 3, then rne_jam P d 4; no new jam composition required',
    'new_broad_word_public_proof': 'NOT_PROVED', 'new_Lean': 'NOT_RUN',
    'frozen_sources': frozen, 'performance': 'UNKNOWN',
    'note': digest(HERE / 'BROAD-WORD-PROOF-INTERFACE.md')}
(HERE / 'broad-word-proof-interface-audit.json').write_text(json.dumps(result, indent=2)+'\n')
print(json.dumps({'old_run': accepted['run'], 'originals_rehashed': len(checks),
    'rne_jam': result['rne_jam'], 'jam_add_even': result['jam_add_even']['status'],
    'frozen_sources_unchanged': True}))
