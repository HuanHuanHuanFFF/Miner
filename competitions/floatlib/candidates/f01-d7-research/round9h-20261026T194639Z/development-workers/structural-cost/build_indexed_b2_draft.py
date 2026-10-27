"""Build an uncompiled structural source draft inside this worker's directory."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
SOURCE = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
sha = lambda b: hashlib.sha256(b).hexdigest()
original = SOURCE.read_bytes()
assert sha(original) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
text = original.decode('utf-8')
namespace = 'namespace Submission.R15PackedB2\n'
begin = text.index(namespace)
end = text.index('end Submission.R15PackedB2', begin)
before, middle, after = text[:begin], text[begin:end], text[end:]
fragment = (HERE / 'indexed-b2.lean.inc').read_text(encoding='utf-8')
anchor = '@[inline] def group (batch m n p : Nat)\n'
assert middle.count(anchor) == 1
old_call = ('  let result := loop n baseA A.toArray (packedB.get (tileIndex batch p b g))\n'
            '    0 Packed10.zero32 Packed10.zero32\n')
new_call = '  let result := Indexed.runDot n baseA A.toArray (packedB.get (tileIndex batch p b g))\n'
assert middle.count(old_call) == 1
old_proof = '  simp only [group, R15ThinPairs.group, packed_loop_eq]\n'
new_proof = '  simp only [group, R15ThinPairs.group, Indexed.runDot_eq, packed_loop_eq]\n'
assert middle.count(old_proof) == 1
middle = middle.replace(anchor, fragment + anchor).replace(old_call, new_call).replace(old_proof, new_proof)
output = (before + middle + after).encode('utf-8')
assert len(output) <= 256000
assert output.count(b'sorry') == original.count(b'sorry')
assert output.count(b'axiom ') == original.count(b'axiom ')
assert output.count(b'unsafe ') == original.count(b'unsafe ')
target = HERE / 'Kernel-indexed-b2.draft.lean'
target.write_bytes(output)
manifest = dict(at_utc=datetime.now(timezone.utc).isoformat(), status='UNCOMPILED_DRAFT_NOT_CANDIDATE_OR_GATE_RESULT',
                source=dict(path=str(SOURCE.relative_to(ROOT)), sha256=sha(original), bytes=len(original)),
                draft=dict(path=str(target.relative_to(ROOT)), sha256=sha(output), bytes=len(output)),
                fragment=dict(path=str((HERE/'indexed-b2.lean.inc').relative_to(ROOT)),
                              sha256=sha((HERE/'indexed-b2.lean.inc').read_bytes())),
                edits=['insert Indexed namespace before R15PackedB2.group',
                       'group calls Indexed.runDot instead of loop initialized to zero',
                       'group_eq rewrites Indexed.runDot_eq before existing packed_loop_eq'],
                unchanged_ranges=['all source before namespace Submission.R15PackedB2',
                                  'all source after end Submission.R15PackedB2',
                                  'all B2 source except three listed edits'],
                lean_execution='NOT_RUN', full_gate='NOT_RUN', codegen='NOT_RUN', timing='NOT_RUN')
(HERE / 'draft-manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
print(json.dumps(manifest, ensure_ascii=False, indent=2))
