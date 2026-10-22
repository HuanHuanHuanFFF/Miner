"""Adapt the preserved whole-call bound proof to the confirmed eight-lane package."""
from pathlib import Path
import hashlib, json

ROOT = Path(__file__).resolve().parents[1]
OUT = Path(__file__).resolve().parent
parent = ROOT / 'f01-d3-final-package' / 'Kernel.lean'
raw = parent.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7'
source = raw.decode()
source = source.replace('def bmm (batch', 'def bmmPacked8Base (batch', 1)
a = source.index('theorem bmm_spec :')
b = source.index('end Submission', a)
source = source[:a] + source[a:b].replace('bmm_spec', 'bmmPacked8Base_spec').replace('bmm batch', 'bmmPacked8Base batch').replace('unfold bmm\n', 'unfold bmmPacked8Base\n') + source[b:]
helper = (ROOT / 'f01-r3-packed4-global-guard' / 'Kernel.lean').read_text()
helper = helper[helper.index('namespace Submission.Packed4.MatrixBounds'):]
for old, new in [('Packed4','Packed8'),('F4','F8'),('dot4','dot8'),('Fin 4','Fin 8'),('4 * g.val','8 * g.val')]:
    helper = helper.replace(old,new)
helper = helper.replace('zero32 zero32 zero32 zero32', 'zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32')
data = (source + '\n' + helper).encode()
(OUT / 'Kernel.lean').write_bytes(data)
manifest = dict(candidate=OUT.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parent='f01-d3-final-package',helper='f01-r3-packed4-global-guard',validation_mode='full-gate',proof_status='NOT_RUN',mechanism='One whole-call matrix length guard supplies proof-erased eight-lane USize row bounds; same native ordered dot and final fallback.')
(OUT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps(manifest))
