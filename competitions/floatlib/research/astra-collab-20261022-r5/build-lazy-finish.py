from pathlib import Path
import datetime
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[4]
RESEARCH = Path(__file__).resolve().parent
PARENT = ROOT / 'competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean'
DEST = ROOT / 'competitions/floatlib/candidates/f01-r5-lazy-finish'
raw = PARENT.read_bytes()
assert hashlib.sha256(raw).hexdigest() == 'ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630'
source = raw.decode('utf-8')
source = re.sub(r'\bbmm_spec\b', 'bmmR4_spec', source)
source = re.sub(r'\bbmm\b', 'bmmR4', source)
block = (RESEARCH / 'lazy-finish-block.lean').read_text(encoding='utf-8')
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
    'mechanism': 'Place original raw A/B fallback address arithmetic inside the nonfinite branch; finite output only converts native result to bits.',
    'evidence': 'Pinned-parent diagnostic C executes 5 Nat multiplications and 2 additions per output before finish guard; 1 multiplication is coordinate rowSize and remains, 4 raw-address multiplications and 2 additions can move to fallback.',
    'cost_tradeoff': 'Coordinate divmod and global tile layout remain; no additional output buffers. Real codegen and performance unknown.',
    'preserved': 'Parent add/mul/sum, native dot, zero cases and exact raw fallback unchanged; all bridges definitionally equal.',
    'proof_status': 'NOT_RUN',
    'performance': 'NOT_RUN',
    'validation_mode': 'diagnostic-statement-only',
    'formal_submission': 'NOT_PERFORMED',
    'created_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
}
(DEST / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
print(json.dumps(manifest, ensure_ascii=False, indent=2))
