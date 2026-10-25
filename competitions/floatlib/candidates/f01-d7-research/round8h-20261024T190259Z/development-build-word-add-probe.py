"""Freeze the independent pure-word add foundation; public add remains retained."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
parent = C / 'f01-r14-dev-compact-base/Kernel.lean'
raw = parent.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '3c6af73f9d679e9831ac8c4abb9f0e6d41b61718301dd045bedd2402e980632a'
model = (OUT / 'astra-exponent-shift-model-draft.lean').read_bytes()
normal = (OUT / 'astra-nat-normal-form-draft.lean').read_bytes()
bias = (OUT / 'astra-biased-rne1.lean').read_bytes()
assert hashlib.sha256(model).hexdigest() == 'b2bb153c1e20e2e7ab0046f0e25583c4645cc5fc69ce9f94a2bbd482909a86f8'
assert hashlib.sha256(normal).hexdigest() == 'e61ae47542207246b1861a59fcfa4e4bbb385758b0f3e46bf247f43ce082758f'
assert hashlib.sha256(bias).hexdigest() == '3515b1819897ad3d230f53d12375b85987fcf8678779e7428f4a78e693b65b0c'
text = model.decode()
fields = text[text.index('@[inline] def ex '):text.index('@[inline] def core ')]
fields = '''namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange
''' + fields + '\nend Submission.R14ExponentShift\n'
text = normal.decode()
basics = text[:text.index('theorem leading_bounds ')]
rounding = text[text.index('/-- A normal finite rounding'):text.index('theorem round_normal_decode ')]
decode = text[text.index('/-- Unlike the old NormalBand'):text.index('theorem raw_mkBits_decode ')]
normal_subset = basics + rounding + decode + '\nend Submission.R14NatNormal\n'
foundation = ('\nset_option maxRecDepth 8192\n' + fields + '\n' + normal_subset + '\n' + bias.decode()).encode()
foundation_path = OUT / 'development-word-add-foundation.lean'
assert not foundation_path.exists()
foundation_path.write_bytes(foundation)
components = [foundation_path, OUT / 'development-word-add-runtime2.lean', OUT / 'development-word-add-word-bridges-draft.lean']
result = raw + b'\n' + b'\n'.join(path.read_bytes() for path in components)
assert len(result) <= 256000
folder = C / 'f01-r14-dev-word-add-probe1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=hashlib.sha256(result).hexdigest(),
              candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(), validation_mode='statement-only',
              proof_status='FOUNDATION_AND_STRUCTURAL_WORD_BRIDGES_NOT_COMPILED', public_runtime_changed=False,
              parent='f01-r14-dev-compact-base', parent_sha256=hashlib.sha256(raw).hexdigest(),
              components=[dict(path=path.relative_to(ROOT).as_posix(), bytes=path.stat().st_size,
                               sha256=hashlib.sha256(path.read_bytes()).hexdigest()) for path in components],
              purpose='Independent smaller add diagnostic: exact original ex/sign and normal-RNE fragments, pure-word add runtime definitions, sorting/normal/gap/sign word lemmas. Avoid unrelated first-product/algebra/full-MUL dependencies. No actual public add optimization or closed new add_spec yet.',
              remaining='Natural aligned magnitude/model-add identity, one-bit leading estimate, small-shift RNE, fields/spec composition and public wrapper integration. All original four exported kernels are the compact retained baseline.',
              performance='NOT_RUN; source-level fragment only; not a speedup or eligibility result.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
(OUT / 'development-word-add-probe-build.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({key: record[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status', 'public_runtime_changed')}))
