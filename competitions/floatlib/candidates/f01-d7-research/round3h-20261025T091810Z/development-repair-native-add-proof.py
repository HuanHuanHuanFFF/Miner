"""Repair the two compiler-observed proof failures, with runtime unchanged."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
BASE = ROOT / 'competitions/floatlib/candidates'
old = BASE / 'f01-r16-dev-native-add-high2'
source = (old / 'Kernel.lean').read_bytes()
assert hashlib.sha256(source).hexdigest() == '95d7fb8f04aedb739f7f97f1d72c1cb48092217afb6f7ad907523a38e0316539'
partpath = HERE / 'development-add-native-high-qualified-insertion.lean'
part = partpath.read_bytes()
needle = b'    simpa only [magW_nat u v hd] using h\n'
assert part.count(needle) == 1
changedpart = part.replace(needle, b'    simpa [magW_nat u v hd] using h\n')
begin = changedpart.index(b'theorem guardedAdd_spec ')
end = changedpart.index(b'end Submission.R16AddWord', begin)
proof = changedpart[begin:end]
assert proof.count(b'dsimp only') == 3
proof = proof.replace(b'dsimp only', b'try dsimp only')
changedpart = changedpart[:begin] + proof + changedpart[end:]
assert source.count(part) == 1
changed = source.replace(part, changedpart)
assert len(changed) <= 256000
targetpart = HERE / 'development-add-native-high-proof3-insertion.lean'
assert not targetpart.exists()
targetpart.write_bytes(changedpart)
name = 'f01-r16-dev-native-add-high3'
folder = BASE / name
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(changed)
manifest = json.loads((old / 'manifest.json').read_bytes())
manifest.update(candidate=name, candidate_sha256=hashlib.sha256(changed).hexdigest(),
                candidate_bytes=len(changed), created_at_utc=datetime.now(timezone.utc).isoformat(),
                parent=old.name, parent_sha256=hashlib.sha256(source).hexdigest(),
                components=[dict(path=targetpart.relative_to(ROOT).as_posix(), sha256=hashlib.sha256(changedpart).hexdigest(), bytes=len(changedpart))],
                source_policy=dict(state='PENDING_CI_AFTER_PROOF_TACTICS_ONLY'),
                repair='Enable default literal simplification for hN; make three normalization steps tolerant of already-normal goals. Runtime tokens unchanged.',
                repair_script=Path(__file__).resolve().relative_to(ROOT).as_posix(),
                prior_failure=dict(run=40187127847, stage='statement', original_lines=[3629, 3682]))
(folder / 'manifest.json').write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name, sha256=manifest['candidate_sha256'], bytes=len(changed))))
