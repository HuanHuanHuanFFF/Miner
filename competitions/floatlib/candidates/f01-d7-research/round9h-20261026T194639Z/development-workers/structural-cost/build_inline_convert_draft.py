"""Exact two-edit draft from frozen9f7; no Lean, Git, CI, or candidate mutation."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import difflib
import json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
PARENT=ROOT/'competitions/floatlib/candidates/f01-r19-dev-b2-index1/Kernel.lean'
sha=lambda b:hashlib.sha256(b).hexdigest()
raw=PARENT.read_bytes()
assert sha(raw)=='9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1'
text=raw.decode('utf-8')
start=text.index('namespace Indexed\n',text.index('namespace Submission.R15PackedB2\n'))
end=text.index('end Indexed',start)
prefix,scope,suffix=text[:start],text[start:end],text[end:]
edits=[dict(name='inline_certified_A_converter_only_in_Indexed_wordLoop',
            old='    let a := ExecFloat.Binary.toFloat32 (A.uget (baseA + k)\n      (by rw [Packed10Index.addNat baseA k (Nat.lt_trans ha hAS)]; exact ha))\n',
            new='    let a := R2W01b.convert (A.uget (baseA + k)\n      (by rw [Packed10Index.addNat baseA k (Nat.lt_trans ha hAS)]; exact ha)).raw.1\n'),
       dict(name='rewrite_existing_global_converter_equality_in_wordLoop_eq',
            old='    simp only [ugetA_getD, Packed10Index.addNat baseA k (Nat.lt_trans ha hAS), ugetB_get]\n',
            new='    simp only [R2W01c.convert_eq, ugetA_getD, Packed10Index.addNat baseA k (Nat.lt_trans ha hAS), ugetB_get]\n')]
for e in edits:
    assert scope.count(e['old'])==1,e['name']
    scope=scope.replace(e['old'],e['new'])
result=(prefix+scope+suffix).encode('utf-8')
inverse=result.decode('utf-8')
for e in reversed(edits):
    assert inverse.count(e['new'])==1,e['name']
    inverse=inverse.replace(e['new'],e['old'])
assert inverse.encode('utf-8')==raw
assert len(result)<=256000
assert result.count(b'import ContractTensor')==raw.count(b'import ContractTensor')==1
for token in (b'unsafe ',b'axiom ',b'sorry',b'implemented_by ',b'extern '):
    assert result.count(token)==raw.count(token)
assert result.count(b'A.toArray.map')==raw.count(b'A.toArray.map')
assert result.count(b'namespace R2W01b')==raw.count(b'namespace R2W01b')
target=HERE/'Kernel-index-inline-convert.draft.lean'
target.write_bytes(result)
(HERE/'inline-convert-exact.diff.txt').write_text(''.join(difflib.unified_diff(text.splitlines(keepends=True),result.decode().splitlines(keepends=True),
                                                                                  fromfile='frozen9f7',tofile=target.name)),encoding='utf-8')
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='EXACT_TWO_EDIT_UNCOMPILED_DRAFT',
            parent=dict(path=PARENT.relative_to(ROOT).as_posix(),sha256=sha(raw),bytes=len(raw)),
            draft=dict(path=target.relative_to(ROOT).as_posix(),sha256=sha(result),bytes=len(result)),
            edits=edits,inverse_reconstruction_sha256=sha(inverse.encode('utf-8')),inverse_byte_exact=True,
            namespace_binding='Existing root R2W01b.convert and root R2W01c.convert_eq; no Submission prefix or new namespace',
            unchanged=['packB','shape dispatch','output global range guard','NaN finish/replay','old fallback loop',
                       'A/B source representation','all public add/mul/sum definitions','all source outside Indexed.wordLoop/wordLoop_eq'],
            eligibility='magnitude=0 or 0x0c000000<=magnitude<0x7f800000; existing convert retains Float32.ofBits elsewhere',
            proof_reuse='Existing all-input R2W01c.convert_eq; new exact wordLoop_eq must be checked; no new arithmetic theorem',
            execution=dict(Lean='NOT_RUN',kernel_replay='NOT_RUN',helper_axioms='NOT_RUN',full_gate='NOT_RUN',
                           selected_MainFull_C='NOT_RUN',ASM='NOT_RUN',performance='NOT_RUN'),
            source_model_limit='Existing converter equality does not establish compilation or cost of this new source; calls/spills on eligible path remain UNKNOWN')
(HERE/'inline-convert-exact-delta.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:record[k]for k in ('state','parent','draft','inverse_byte_exact')},indent=2))
