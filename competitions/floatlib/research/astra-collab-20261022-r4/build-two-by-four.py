from pathlib import Path
import hashlib
import json
import re
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent
sha = lambda b: hashlib.sha256(b).hexdigest()
parent = ROOT / 'competitions/floatlib/candidates/f01-d3-final-package/Kernel.lean'
packed4 = ROOT / 'competitions/floatlib/candidates/f01-d2-web-packed4-proof1/Kernel.lean'
pb = parent.read_bytes()
qb = packed4.read_bytes()
assert sha(pb) == '6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7'
assert sha(qb) == 'bb1f783fd3103fba89e1e072459d7fdcff9ffdb5edc3e2983b39f1eafced2f18'
s = pb.decode()
assert 'namespace Packed4\n' not in s
start = s.index('\ndef bmm (batch m n p')
end = s.index('\nend Submission', start)
original = s[start:end]
renamed = re.sub(r'\bbmm_spec\b', 'bmmBase_spec', original)
renamed = re.sub(r'\bbmm\b', 'bmmBase', renamed)
s = s[:start] + renamed + s[end:]
q = qb.decode()
p4start = q.index('namespace Packed4\n')
p4end = q.index('\ndef bmm (batch m n p', p4start)
reused = q[p4start:p4end]
data = (s + '\nnamespace Submission\n\nopen FloatLib.Floats Competition\n\n' +
        reused + '\nend Submission\n\n' +
        (HERE / 'tile2x4-block.lean').read_text(encoding='utf-8')).encode()
out = ROOT / 'competitions/floatlib/candidates/f01-r4-tile2x4'
out.mkdir(exist_ok=False)
(out / 'Kernel.lean').write_bytes(data)
manifest = {
    'candidate': out.name, 'candidate_file': 'Kernel.lean',
    'candidate_sha256': sha(data), 'candidate_bytes': len(data),
    'parent': str(parent.relative_to(ROOT)), 'parent_sha256': sha(pb),
    'reused_packed4_source': str(packed4.relative_to(ROOT)), 'reused_source_sha256': sha(qb),
    'reused_packed4_module_sha256': sha(reused.encode()),
    'official_commit': '978cc5b445edb9943fd9953b0a9037d97a9f33a8',
    'lean_toolchain': 'leanprover/lean4:v4.34.0',
    'mechanism': 'Two rows by four columns,8 independent Float32 accumulators sharing4 B values; USize loop with two A spans and exact Nat fallback',
    'proof_route': 'Low/high projections to existing Packed4.dot4, reused lane/finite bridges, wordLoop=Nat reference, per-batch rowPair/columnBlock output mapping',
    'preserved': 'Parent add/mul/decoded sum unchanged; old bmm renamed bmmBase. Copied original verified Packed4 module unchanged.',
    'odd_row_policy': 'Unobserved second row may total-read the next batch; independent states and output mapping ignore it. If its array span is invalid, use Nat reference loop.',
    'validation_mode': 'diagnostic-statement-only', 'proof_status': 'NOT_RUN',
    'performance': 'NOT_RUN', 'formal_submission': 'NOT_PERFORMED',
    'created_at_utc': datetime.now(timezone.utc).isoformat(),
}
(out / 'manifest.json').write_text(json.dumps(manifest, indent=2, ensure_ascii=False)+'\n', encoding='utf-8')
print(json.dumps(manifest, indent=2, ensure_ascii=False))
