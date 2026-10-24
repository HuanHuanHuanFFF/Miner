"""Minimal audited substitution on df5c. No proof pruning or runtime reordering."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
PARENT = CS/'f01-d12-scalar-combined/Kernel.lean'
DEST = CS/'f01-r13-preparation-convert'
EXPECTED = 'df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
sha = lambda b: hashlib.sha256(b).hexdigest()

raw=PARENT.read_bytes()
assert sha(raw)==EXPECTED and b'\r' not in raw
s=raw.decode('utf-8')
helper='''namespace R13NativePrep

@[inline] def toNative (x : Binary32) : Float32 := R2W01b.convert x.raw.1

theorem toNative_eq (x : Binary32) : toNative x = ExecFloat.Binary.toFloat32 x := by
  simpa only [toNative, ExecFloat.Binary.toFloat32, ExecFloat.Binary.toBits32] using
    R2W01c.convert_eq x.raw.1

theorem toNative_fun_eq : toNative = ExecFloat.Binary.toFloat32 := funext toNative_eq

end R13NativePrep

'''
ops=[
 ('insert_unconditional_value_bridge','namespace Packed10\n\nstructure F10 where',helper+'namespace Packed10\n\nstructure F10 where'),
 ('replace_valid_B_conversion','            ExecFloat.Binary.toFloat32 B.toArray[base + j]\n','            R13NativePrep.toNative B.toArray[base + j]\n'),
 ('preserve_original_packB_get_statement','  simp only [packB, vector_get_ofFn]\n','  simp only [packB, vector_get_ofFn, R13NativePrep.toNative_eq]\n'),
 ('replace_once_per_input_A_map','  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32\n','  let nativeA := A.toArray.map R13NativePrep.toNative\n'),
 ('preserve_original_output_prefix_statement','    Prefix (point batch m n p A B) (batch * m * p) (output batch m n p A B) := by\n  exact foldl_inv',
  '    Prefix (point batch m n p A B) (batch * m * p) (output batch m n p A B) := by\n  rw [output, R13NativePrep.toNative_fun_eq]\n  exact foldl_inv')
]
for name,old,new in ops:
    assert s.count(old)==1,(name,s.count(old))
    s=s.replace(old,new,1)
out=s.encode('utf-8')
assert len(out)<=256000 and b'\r' not in out
back=s
for name,old,new in reversed(ops):
    assert back.count(new)==1,(name,back.count(new))
    back=back.replace(new,old,1)
assert back.encode('utf-8')==raw
DEST.mkdir(exist_ok=True)
target=DEST/'Kernel.lean'
if target.exists():
    assert target.read_bytes()==out,'Frozen candidate bytes differ; use a new candidate directory.'
else:
    target.write_bytes(out)
manifest=dict(candidate=DEST.name,candidate_file='Kernel.lean',candidate_sha256=sha(out),candidate_bytes=len(out),
    parent='f01-d12-scalar-combined',parent_sha256=EXPECTED,parent_bytes=len(raw),
    at_utc=datetime.now(timezone.utc).isoformat(),official_commit='4b7e83841cc0c32c6529f533923c73d33b5ecf97',
    lean_toolchain='leanprover/lean4:v4.34.0',floatlib_commit='0d91825727839f597fd06b22fdd038ea21480f0c',
    mechanism='Existing all-input numeric converter only in once-per-input RowStream A map and valid Packed10 B preparation; all layout, padding, calls, dot order, guards, output and replay unchanged.',
    provenance='Reuse repository R2W01b numeric decoder and R2W01c.convert_eq already present in exact df5c. No new external source or claimed novel arithmetic.',
    proof_status='NOT_RUN_NEW_INTEGRATION',benchmark='NOT_RUN',dispatch_state='D_DECISION_PENDING_CURRENT_PROFILE',
    proof_bridge='Unconditional Float32 value equality via existing convert_eq, extensional function equality for Array.map, packB_get and output_prefix rewritten without weakening their statements.',
    first_falsifier='Affected preparation must have enough measured whole-call share; verify actual warm native conversion has no of_bits call, then complete original gate and clean candidate/df5c comparison. No timing inferred from exposure counts.',
    edits=[dict(name=n,old=o,new=v) for n,o,v in ops],inverse_reconstruction_sha256=sha(back.encode('utf-8')),
    validation_scope='Static exact-source reconstruction and byte limit only. No local Lean or heavy Linux toolchain used. Original full gate, actual lowering and timing remain NOT_RUN.',
    author_role='R / Astra; D owns Git, CI and adoption')
(DEST/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps({k:manifest[k] for k in ['candidate','candidate_sha256','candidate_bytes','proof_status','inverse_reconstruction_sha256']},indent=2))
