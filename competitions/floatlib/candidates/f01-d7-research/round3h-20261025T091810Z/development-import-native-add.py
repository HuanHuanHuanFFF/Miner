"""Import the reviewed high-N ADD entry exactly, preserving B2 MUL suffix."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
WORKER = HERE / 'astra-workers/scalar-representation/next-add-u32'
sha = lambda raw: hashlib.sha256(raw).hexdigest()
record = json.loads((WORKER / 'public-add-draft1-manifest.json').read_bytes())
policy = json.loads((WORKER / 'public-add-draft1-policy.json').read_bytes())
raw = (WORKER / record['candidate']['path']).read_bytes()
assert sha(raw) == record['candidate']['sha256'] == policy['source_sha256'] == '2f998811caa348ad7c0e66026b0d049c6ce0720549dd12622345777d24a1e13e'
assert len(raw) == policy['source_bytes'] == 255913 < 256000
assert policy['state'] == 'PASS_ORIGINAL_TEXT_POLICY_ONLY'
base = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
parent = base.read_bytes()
assert sha(parent) == record['parent']['sha256'] == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
suffix = parent[parent.index(b'@[inline] def nativeMul '):]
assert raw.endswith(suffix), 'B2 MUL and later source must remain exact'
part = record['insertion']
fragment = (WORKER / part['path']).read_bytes()
assert sha(fragment) == part['sha256'] and len(fragment) == part['bytes']
component = HERE / 'development-add-native-high-complete-insertion.lean'
assert not component.exists()
component.write_bytes(fragment)
name = 'f01-r16-dev-native-add-high1'
folder = ROOT / 'competitions/floatlib/candidates' / name
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(raw)
manifest = dict(candidate=name, candidate_file='Kernel.lean', candidate_sha256=sha(raw),
                candidate_bytes=len(raw), created_at_utc=datetime.now(timezone.utc).isoformat(),
                parent=base.parent.name, parent_sha256=sha(parent),
                components=[dict(path=component.relative_to(ROOT).as_posix(), sha256=sha(fragment), bytes=len(fragment))],
                mechanism='Guarded high-N aligned ADD using one UInt32 native conversion and field repack; original B2 fallback and MUL source suffix retained.',
                key_review='Research controller source/guard review and one bounded source-model check; not Lean/full-gate/performance acceptance.',
                source_policy=dict(state=policy['state'], gate_sha256=policy['gate_sha256']),
                proof_status='NOT_COMPILED; new helpers are reached by public ADD proof', full_gate='NOT_RUN', performance='NOT_RUN',
                scope='Pure source and proof import only; no private research conversation or held old R14 export.')
(folder / 'manifest.json').write_bytes((json.dumps(manifest, ensure_ascii=False, indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name, sha256=sha(raw), bytes=len(raw), original_mul_suffix_bytes=len(suffix))))
