"""Resolve compiler-observed name ambiguity in the actual high-N ADD source."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
BASE = ROOT / 'competitions/floatlib/candidates'
old = BASE / 'f01-r16-dev-native-add-high1'
source = (old / 'Kernel.lean').read_bytes()
assert hashlib.sha256(source).hexdigest() == '2f998811caa348ad7c0e66026b0d049c6ce0720549dd12622345777d24a1e13e'
partpath = HERE / 'development-add-native-high-complete-insertion.lean'
part = partpath.read_bytes()
begin = part.index(b'namespace Submission.A16I\n')
end = part.index(b'end Submission.A16I', begin)
section = part[begin:end]
assert section.count(b': Dyadic)') == 4
fixed = section.replace(b': Dyadic)', b': FloatLib.Numerics.Dyadic)')
changedpart = part[:begin] + fixed + part[end:]
assert source.count(part) == 1
changed = source.replace(part, changedpart)
assert len(changed) == 255985 <= 256000
targetpart = HERE / 'development-add-native-high-qualified-insertion.lean'
assert not targetpart.exists()
targetpart.write_bytes(changedpart)
name = 'f01-r16-dev-native-add-high2'
folder = BASE / name
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(changed)
manifest = json.loads((old / 'manifest.json').read_bytes())
manifest.update(candidate=name, candidate_sha256=hashlib.sha256(changed).hexdigest(),
                candidate_bytes=len(changed), created_at_utc=datetime.now(timezone.utc).isoformat(),
                parent=old.name, parent_sha256=hashlib.sha256(source).hexdigest(),
                components=[dict(path=targetpart.relative_to(ROOT).as_posix(), sha256=hashlib.sha256(changedpart).hexdigest(), bytes=len(changedpart))],
                source_policy=dict(state='PENDING_CI_AFTER_TYPE_QUALIFICATION', parent_policy=manifest['source_policy']),
                repair='Qualify four ambiguous Dyadic type annotations in A16I; runtime tokens unchanged. Compiler evidence40186471996.',
                repair_script=Path(__file__).resolve().relative_to(ROOT).as_posix())
(folder / 'manifest.json').write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name, sha256=manifest['candidate_sha256'], bytes=len(changed))))
