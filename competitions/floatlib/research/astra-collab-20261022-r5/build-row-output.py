from pathlib import Path
import datetime
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[4]
RESEARCH = Path(__file__).resolve().parent
PARENT = ROOT / 'competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean'
DEST = ROOT / 'competitions/floatlib/candidates/f01-r5-row-output'
raw = PARENT.read_bytes()
assert hashlib.sha256(raw).hexdigest() == 'ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630'
source = raw.decode('utf-8')
source = re.sub(r'\bbmm_spec\b', 'bmmR4_spec', source)
source = re.sub(r'\bbmm\b', 'bmmR4', source)
block = (RESEARCH / 'row-output-block.lean').read_text(encoding='utf-8')
candidate = (source + '\n\n' + block).encode('utf-8')
assert len(candidate) <= 256000
DEST.mkdir(exist_ok=True)
(DEST / 'Kernel.lean').write_bytes(candidate)
manifest = {
    'candidate': DEST.name,
    'candidate_file': 'Kernel.lean',
    'candidate_sha256': hashlib.sha256(candidate).hexdigest(),
    'candidate_bytes': len(candidate),
    'parent': str(PARENT.relative_to(ROOT)),
    'parent_sha256': hashlib.sha256(raw).hexdigest(),
    'official_commit': '978cc5b445edb9943fd9953b0a9037d97a9f33a8',
    'lean_toolchain': 'leanprover/lean4:v4.34.0',
    'mechanism': 'Build output per batch and row; hoist row bases and two tile lookups; flatten preserves exact row-major values.',
    'cost_tradeoff': 'Two flatten levels copy output references; per-row vectors and closure/allocation costs must be measured in complete call.',
    'preserved': 'Original bmm renamed only; all parent arithmetic, packed dot, finite fallback, scalar add/mul/sum remain unchanged.',
    'proof_status': 'NOT_RUN',
    'performance': 'NOT_RUN',
    'validation_mode': 'diagnostic-statement-only',
    'formal_submission': 'NOT_PERFORMED',
    'created_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
}
(DEST / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps(manifest, ensure_ascii=False, indent=2))
