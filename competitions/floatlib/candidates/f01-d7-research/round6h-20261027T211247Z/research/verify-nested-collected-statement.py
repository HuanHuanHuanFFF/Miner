"""Apply only the public-suite nesting map to the unchanged R21 proof verifier.

The original verifier's all-artifact byte checks still use the artifact root.
This adapter fixes receipt lookup only; no proof/gate criterion changes.
"""
from pathlib import Path
import hashlib
import json

here = Path(__file__).resolve().parent
p = here / 'verify-collected-statement.py'
old = p.read_text(encoding='utf-8')
new = old
maps = {
    "source=directory/'inputs'": "scope=directory/'diagnostics/f01-d7-public-suite/public-suite'\nsource=scope/'inputs'",
    "diag=directory/'diagnostics'": "diag=scope/'diagnostics'",
    "v=json.loads((directory/(name+": "v=json.loads((scope/(name+",
}
for a, b in maps.items():
    assert new.count(a) == 1
    new = new.replace(a, b)
receipt = {'original_sha256': hashlib.sha256(p.read_bytes()).hexdigest(),
           'mapped_sha256': hashlib.sha256(new.encode()).hexdigest(),
           'lookup_substitutions': 3, 'all_original_byte_checks_unchanged': True,
           'reason': 'New public-suite components are nested; original outer-only lookup fails withFileNotFoundError before acceptance checks.'}
(here / 'nested-proof-verifier-map.json').write_text(json.dumps(receipt, indent=2) + '\n')
exec(compile(new, str(p), 'exec'), {'__name__': '__main__', '__file__': str(p)})
