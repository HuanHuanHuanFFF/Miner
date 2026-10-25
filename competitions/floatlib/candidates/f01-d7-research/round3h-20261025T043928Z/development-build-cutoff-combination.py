"""Integrate only the reviewed scalar proof fragment with a distinct matrix source."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
WORKER = HERE / 'astra-workers/scalar-sum-domain'
sha = lambda raw: hashlib.sha256(raw).hexdigest()
review = json.loads((HERE / 'astra-cutoff84-independent-review.json').read_bytes())
donor = WORKER / 'Kernel-cutoff84.lean'
donor_raw = donor.read_bytes()
assert sha(donor_raw) == review['candidate_sha256'] == '837341a52575cffa9b5dfee6a44ba9369d1ee7ae4f6bb47fa47af11ae1f5831b'
fragment_raw = (WORKER / 'LowCutoff84-complete-fragment.lean').read_bytes()
fragment = fragment_raw.replace(b'\r\n', b'\n')
assert donor_raw.count(fragment) == 1
parent = C / 'f01-r15-dev-shortn-inline-decode1/Kernel.lean'
raw = parent.read_bytes()
assert sha(raw) == 'f65e4aa5baf0b38a808f1e57e0ded26d71870d8b61b993a80ab92aeef77e8d8c'
prefix = b'@[inline] def mul (x y : Binary32) : Binary32 :=\n  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField'
assert raw.count(prefix) == 1
start = raw.index(prefix)
proof_end = b'  \xc2\xb7 exact nativeMul_spec x y\n'
end = raw.index(proof_end, start) + len(proof_end)
old = raw[start:end]
df = (C / 'f01-d12-scalar-combined/Kernel.lean').read_bytes()
assert df.count(old) == 1 and donor_raw.replace(fragment, old) == df
source_path = HERE / 'development-cutoff84-reviewed-fragment.lean'
assert not source_path.exists()
source_path.write_bytes(fragment)
result = raw[:start] + fragment + raw[end:]
assert result.replace(fragment, old) == raw
folder = C / 'f01-r15-dev-shortn-decode-cutoff1'
assert not folder.exists() and len(result) <= 256000
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=sha(result),
    candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(),
    parent=parent.parent.name, parent_sha256=sha(raw),
    donor_math_candidate_sha256=sha(donor_raw), donor_review_sha256=sha((HERE / 'astra-cutoff84-independent-review.json').read_bytes()),
    donor_original_fragment_sha256=sha(fragment_raw), donor_original_fragment_bytes=len(fragment_raw),
    original_preservation='Worker original fragment remains byte unchanged; integrated copy uses LF to match exact donor Kernel.',
    components=[dict(path=source_path.relative_to(ROOT).as_posix(), sha256=sha(fragment), bytes=len(fragment))],
    mechanism='Precise combination: expanded short-n B reuse, cached-loop exact numeric A decode, and conservative exponent-sum<=84 XOR-signed-zero scalar MUL shortcut inside the old <128 branch.',
    invariant='Original ordered folds and all other parent bytes unchanged. Math donor inverted byte-exactly to DF; combination inverted byte-exactly to f65e.',
    proof_status='NOT_COMPILED_THIS_EXACT_COMBINATION', performance='NOT_RUN',
    acceptance='Own first full D and frozen independent confirmation required. No addition of component savings; donor review/model is not a Lean gate.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({k: record[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}))
