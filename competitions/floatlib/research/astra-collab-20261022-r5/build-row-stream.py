from pathlib import Path
import datetime
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[4]
RESEARCH = Path(__file__).resolve().parent
PARENT = ROOT / 'competitions/floatlib/candidates/f01-r5-row-output/Kernel.lean'
DEST = ROOT / 'competitions/floatlib/candidates/f01-r5-row-stream'
raw = PARENT.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '97cbe074760474c7b04f549a508614c0ba3317ce192e1d9439632b930d77644d'
source = raw.decode('utf-8')
source = re.sub(r'\bbmm_spec\b', 'bmmRows_spec', source)
source = re.sub(r'\bbmm\b', 'bmmRows', source)
block = (RESEARCH / 'row-stream-block.lean').read_text(encoding='utf-8')
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
    'comparison_parent': 'f01-d4-final-lowmul',
    'comparison_parent_sha256': 'ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630',
    'mechanism': 'Stream complete rows with one flatMap; compute and consume each row tile buffer before the next; no global result tiles or second batch flatten.',
    'cost_tradeoff': 'One row-index vector and row arrays remain; dot and finish can interleave; complete-call performance unknown.',
    'preserved': 'Exact old ordered dot and per-output finite/raw fallback. Scalar kernels unchanged. Every row computed once.',
    'proof_status': 'NOT_RUN',
    'performance': 'NOT_RUN',
    'validation_mode': 'diagnostic-statement-only',
    'formal_submission': 'NOT_PERFORMED',
    'created_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
}
(DEST / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps(manifest, ensure_ascii=False, indent=2))
