"""Reproduce the frozen public proof repair without changing runtime wrappers."""
from pathlib import Path
import hashlib
import json

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'AGENTS.md').is_file())
HERE = Path(__file__).resolve().parent
OLD = ROOT / 'competitions/floatlib/candidates/f01-r22-dev-outline-public1/Kernel.lean'
HELPER = HERE / 'development-math/MathOutletR23Fix1.lean'
TARGET = ROOT / 'competitions/floatlib/candidates/f01-r23-dev-outline-public1/Kernel.lean'
sha = lambda value: hashlib.sha256(value).hexdigest()

old = OLD.read_bytes()
helper = HELPER.read_bytes()
assert sha(old) == '88cdf318d952d74df95ecabed5e2bbadeab76d4827af1c4e5fd88e43d9d8f054'
assert sha(helper) == '159e0633eee16fa1b054d2b0adcb0a99b0a5fc7dfe96e776097de6d9f4e467e9'
text = old.decode()
start = text.index('namespace BranchlessRNESeed')
end = text.index('namespace R19BiasBase.R19DirectBias\nopen Competition\n@[noinline] def retainedMul')
body = helper.decode().removeprefix('import Submission\n')
body = '\n'.join(line for line in body.splitlines() if not line.startswith('#print axioms ')) + '\n'
assembled = text[:start] + body.replace('Submission.', 'R19BiasBase.') + '\n' + text[end:]
license_start = assembled.index('/-\nMIT License')
license_end = assembled.index('-/', license_start) + 2
license_text = assembled[license_start:license_end]
assert len(license_text.encode()) == 4603 and assembled.count(license_text) == 2
duplicate = assembled.index(license_text, license_end)
result = (assembled[:duplicate] + '\n' + assembled[duplicate + len(license_text):]).encode()
assert result.decode().count(license_text) == 1
assert result.endswith(text[end:].encode())
assert len(result) == 253978 and sha(result) == 'f90d42e346a1634ffeb537ea7e9980e0a91baea8499dc6c2235da5ab8fe0e85f'
assert result == TARGET.read_bytes()
print(json.dumps({'reproduced_exact_frozen_source': True, 'sha256': sha(result),
                  'bytes': len(result), 'whole_original_license_retained': True,
                  'public_wrapper_byte_identical': True}))
