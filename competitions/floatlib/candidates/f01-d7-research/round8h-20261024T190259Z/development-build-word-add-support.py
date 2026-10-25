"""Compose exact small-domain add support without unrelated mul proof code."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
base = (C / 'f01-r14-dev-compact-base/Kernel.lean').read_bytes()
assert hashlib.sha256(base).hexdigest() == '3c6af73f9d679e9831ac8c4abb9f0e6d41b61718301dd045bedd2402e980632a'
bias = (OUT / 'astra-biased-rne2.lean').read_bytes()
assert hashlib.sha256(bias).hexdigest() == 'e9abe15eaebf5dab13f717558292f49871f8fdde07b3075145915a493bb5db0a'
foundation2 = (OUT / 'development-word-add-foundation2.lean').read_bytes()
assert foundation2.count(bias) == 1
foundation3 = OUT / 'development-word-add-foundation3.lean'
assert not foundation3.exists()
foundation3.write_bytes(foundation2.replace(bias, b''))
runtime2 = (OUT / 'development-word-add-runtime2.lean').read_bytes()
assert hashlib.sha256(runtime2).hexdigest() == '4f141b411b419de2d3190412c0d97b924bfb29053c99c6389907696d0a43ce88'
runtime3 = OUT / 'development-word-add-runtime3.lean'
assert not runtime3.exists()
runtime3.write_bytes(runtime2.replace(b'R14BiasRNE', b'R14SmallShiftBias'))
frozen = {
    'astra-small-shift-bias2.lean':'e3de8acf9ec5ec3434419e1c7a1b46c2a1b92bdef495bd0d4e6ff9e1ff07e585',
    'astra-word-add-alignment2.lean':'eaa89fa496e6dad3d82d6c14b18503c918cec02b43876c134cc851daaf3d08f9',
    'astra-word-add-bounds1.lean':'c7fa39b51d238d0d5b99a7bed58dcf31f3a20b9da19e69c94ec447fe7dd5cfee',
    'astra-word-add-rounding1.lean':'b8e6674548e9ad8a4d8fcfb948f85ab48056c576b3289ece1829ddd91b69bff7',
}
for name, sha in frozen.items():
    assert hashlib.sha256((OUT / name).read_bytes()).hexdigest() == sha
order = [foundation3, OUT / 'astra-small-shift-bias2.lean', runtime3,
         OUT / 'development-word-add-word-bridges-draft.lean', OUT / 'astra-word-add-alignment2.lean',
         OUT / 'astra-word-add-bounds1.lean', OUT / 'astra-word-add-rounding1.lean', OUT / 'astra-word-add-model-bridge1.lean']
result = base + b'\n' + b'\n'.join(path.read_bytes() for path in order)
assert len(result) <= 256000
folder = C / 'f01-r14-dev-word-add-support1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=hashlib.sha256(result).hexdigest(),
              candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(), validation_mode='statement-only',
              proof_status='WORD_ADD_NAT_AND_MODEL_SUPPORT_NOT_COMPILED', public_runtime_changed=False,
              parent='f01-r14-dev-compact-base', parent_sha256=hashlib.sha256(base).hexdigest(),
              components=[dict(path=p.relative_to(ROOT).as_posix(), bytes=p.stat().st_size, sha256=hashlib.sha256(p.read_bytes()).hexdigest()) for p in order],
              purpose='Check actual add word runtime/sort/guard/sign skeleton together with exact small-shift RNE, aligned dyadic addition in both operand orders, magnitude/log/carry/fraction bounds, and normal Model.add bridge. Public four kernels remain retained; no new add_spec is claimed.',
              runtime_revision='Same arithmetic, using the source-identical small-shift biased runtime so its theorem applies directly; no Option/tuple introduced.',
              remaining='Lift the actual UInt32 alignment and one-bit leading computation into these Nat lemmas, bind word fields/result guard, then integrate the public add with original ordered fallback and full spec.',
              performance='NOT_RUN; support diagnostic only, not an optimization result.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
(OUT / 'development-word-add-support-build.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({key: record[key] for key in ('candidate','candidate_sha256','candidate_bytes','proof_status','public_runtime_changed')}))
