"""Build uncompiled draft with one output-wide range guard, no per-group guard."""
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
begin = text.index('namespace Submission.R15PackedB2\n')
end = text.index('end Submission.R15PackedB2', begin)
before, middle, after = text[:begin], text[begin:end], text[end:]
raw_fragment = (HERE / 'indexed-b2.lean.inc').read_text(encoding='utf-8')
fragment = raw_fragment[:raw_fragment.index('@[inline] def runDot')] + 'end Indexed\n\n'
entry = (HERE / 'hoisted-b2-entry.lean.inc').read_text(encoding='utf-8')
group_anchor = '@[inline] def group (batch m n p : Nat)\n'
output_anchor = 'def output (batch m n p : Nat)\n'
assert middle.count(group_anchor) == middle.count(output_anchor) == 1
middle = middle.replace(group_anchor, fragment + group_anchor)
middle = middle.replace(output_anchor, entry + output_anchor)
old_output = ('  let packedB := packB batch n p B\n'
              '  Fin.foldl (batch * m) (row batch m n p A B packedB)\n'
              '    (Array.mkEmpty (batch * m * p))\n')
new_output = ('  let packedB := packB batch n p B\n'
              '  if h : 0 < n ∧ A.toArray.size < USize.size then\n'
              '    Fin.foldl (batch * m) (rowWithin batch m n p A B h.1 h.2 packedB)\n'
              '      (Array.mkEmpty (batch * m * p))\n'
              '  else\n'
              '    Fin.foldl (batch * m) (row batch m n p A B packedB)\n'
              '      (Array.mkEmpty (batch * m * p))\n')
old_proof = ('  unfold output R15ThinPairs.output\n'
             '  apply congrArg (fun step : Array Binary32 → Fin (batch * m) → Array Binary32 =>\n'
             '    Fin.foldl (batch * m) step (Array.mkEmpty (batch * m * p)))\n'
             '  funext out r\n'
             '  exact row_eq batch m n p A B out r\n')
new_proof = ('  unfold output R15ThinPairs.output\n'
             '  split\n'
             '  · rename_i h\n'
             '    apply congrArg (fun step : Array Binary32 → Fin (batch * m) → Array Binary32 =>\n'
             '      Fin.foldl (batch * m) step (Array.mkEmpty (batch * m * p)))\n'
             '    funext out r\n'
             '    exact (rowWithin_eq batch m n p A B h.1 h.2 (packB batch n p B) out r).trans\n'
             '      (row_eq batch m n p A B out r)\n'
             '  · apply congrArg (fun step : Array Binary32 → Fin (batch * m) → Array Binary32 =>\n'
             '      Fin.foldl (batch * m) step (Array.mkEmpty (batch * m * p)))\n'
             '    funext out r\n'
             '    exact row_eq batch m n p A B out r\n')
assert middle.count(old_output) == middle.count(old_proof) == 1
middle = middle.replace(old_output, new_output).replace(old_proof, new_proof)
output = (before + middle + after).encode('utf-8')
assert len(output) <= 256000
for token in (b'sorry', b'axiom ', b'unsafe ', b'implemented_by ', b'extern '):
    assert output.count(token) == original.count(token)
assert b'Indexed.runDot' not in output
target = HERE / 'Kernel-hoisted-b2.draft.lean'
target.write_bytes(output)
manifest = dict(at_utc=datetime.now(timezone.utc).isoformat(), status='UNCOMPILED_DRAFT_NOT_CANDIDATE_OR_GATE_RESULT',
                source=dict(path=str(SOURCE.relative_to(ROOT)), sha256=sha(original), bytes=len(original)),
                draft=dict(path=str(target.relative_to(ROOT)), sha256=sha(output), bytes=len(output)),
                fragments=[dict(path=str((HERE/n).relative_to(ROOT)), sha256=sha((HERE/n).read_bytes()))
                           for n in ('indexed-b2.lean.inc', 'hoisted-b2-entry.lean.inc')],
                edits=['insert indexed raw-A wordLoop/within and exact equality before old group',
                       'insert row bound, rowDot, groupWithin, rowWithin and exact equalities before output',
                       'output makes one global 0<n and A.size<USize.size decision after unchanged B packing',
                       'output_eq reduces fast rows to unchanged old rows then existing row_eq'],
                unchanged_ranges=['all source before namespace Submission.R15PackedB2',
                                  'all source after end Submission.R15PackedB2',
                                  'old B2 loop/packing/group/row/dispatcher and their proofs'],
                added_runtime_guards='two comparisons once per B2 output; no new per-group or per-k range test',
                new_preparation_allocations=0,
                new_helper_theorems=['Indexed.ugetA_getD','Indexed.ugetB_get','Indexed.wordLoop_eq',
                                     'Indexed.within_eq','Indexed.row_last_lt','Indexed.rowDot_eq',
                                     'groupWithin_eq','rowWithin_eq'],
                lean_execution='NOT_RUN', full_gate='NOT_RUN', codegen='NOT_RUN', timing='NOT_RUN')
(HERE / 'hoisted-draft-manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
print(json.dumps(manifest, ensure_ascii=False, indent=2))
