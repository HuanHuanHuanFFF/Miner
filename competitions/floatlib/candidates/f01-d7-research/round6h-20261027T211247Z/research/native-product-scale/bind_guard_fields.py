from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json

here = Path(__file__).resolve().parent
repo = next(p for p in here.parents if (p / 'AGENTS.md').is_file())

def record(path):
    p = repo / path
    data = p.read_bytes()
    return {'path': path, 'sha256': sha256(data).hexdigest(), 'bytes': len(data)}

prefix = here.relative_to(repo).as_posix()
refs = {
    'old_source': 'competitions/floatlib/candidates/f01-r17-dev-u64-public2/Kernel.lean',
    'old_terminal_receipt': 'competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/development-terminal-40309310448.json',
    'old_actual_verdict': 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40309310448/download-351304bef75240f984a500c00f034f6d/diagnostics/f01-d7-public-suite/public-suite/f01-r17-dev-u64-public2-verdict.json',
}
files = {n: record(f'{prefix}/{n}') for n in ['GuardFields.lean.inc', 'guard-fields-interface.md', 'Runtime.lean.inc', 'Kernel-probe1.lean']}
assert files['Runtime.lean.inc']['sha256'] == 'e51a67d6188b2ec4c8701cd991e942296fdc7d6158fdb8d92c4e42852bd01709'
assert files['Kernel-probe1.lean']['sha256'] == '92ff7182e76609c72a3f2a77a326e2fee86e70aad1c24fa4247e590e74b20f31'
verdict = json.loads((repo / refs['old_actual_verdict']).read_text())
assert verdict['passed'] is True and verdict['submission'] == 'f01-r17-dev-u64-public2'
out = {
    'checked_utc': datetime.now(timezone.utc).isoformat(),
    'start_utc': '2026-10-28T00:04:09Z',
    'bound_utc': '2026-10-28T00:14:09Z',
    'state': 'ONE_PROOF_ONLY_GUARD_ROOT_NOT_RUN',
    'roots': ['Submission.R22NativeProductGuard.guard_fields'],
    'files': files,
    'references': {k: record(v) for k, v in refs.items()},
    'old_decode_root': 'R18.R14NatNormal.raw_normal_decode',
    'old_decode_lines': [6999, 7008],
    'old_scope': '00ab public full gate passed; new guard root is separate and uncompiled',
    'runtime_unchanged': True,
    'probe_unchanged': True,
    'Lean': 'NOT_RUN',
    'CI': 'NOT_RUN',
    'full_new_mul_spec': 'NOT_PROVED',
}
(here / 'guard-fields-manifest.json').write_text(json.dumps(out, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'guard': files['GuardFields.lean.inc'], 'checked_utc': out['checked_utc'], 'Lean': out['Lean']}, ensure_ascii=False))
