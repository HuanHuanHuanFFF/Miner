"""Repair one banned token in a proof comment; retain the failed original."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
BASE = ROOT / 'competitions/floatlib/candidates'
old = BASE / 'f01-r16-dev-add-interface1'
raw = (old / 'Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest() == '41241a3353203ea581a365dfd4f2f6b39e35badd08030a1d4ea5b6dd32881625'
needle = b"must be proved from the real integer converter's rounding; it is not an axiom. -/"
assert raw.count(needle) == 1
changed = raw.replace(needle, b"must be proved from the real integer converter's rounding. -/")
assert not re.search(rb'\b(?:axiom|sorry|unsafe|admit)\b', changed)
name = 'f01-r16-dev-add-interface2'
folder = BASE / name
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(changed)
manifest = json.loads((old / 'manifest.json').read_bytes())
manifest.update(candidate=name, candidate_sha256=hashlib.sha256(changed).hexdigest(),
                candidate_bytes=len(changed), created_at_utc=datetime.now(timezone.utc).isoformat(),
                parent=old.name, parent_sha256=hashlib.sha256(raw).hexdigest(),
                repair='Remove one banned-token sentence from a comment at original line7124; every proof/runtime token unchanged.',
                repair_script=Path(__file__).resolve().relative_to(ROOT).as_posix(),
                prior_failure=dict(run=40185963461, stage='source-policy-before-compilation'))
(folder / 'manifest.json').write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name, sha256=manifest['candidate_sha256'], bytes=len(changed))))
