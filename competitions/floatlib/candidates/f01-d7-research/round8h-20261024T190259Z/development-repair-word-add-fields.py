"""Versioned fixes from actual run40149766137, preserving every failed source."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT=Path(__file__).resolve().parent
sha=lambda b:hashlib.sha256(b).hexdigest()
rows=[]
def save(old_name,new_name,change,reason):
    old=(OUT/old_name).read_bytes();new=change(old)
    assert old!=new and not (OUT/new_name).exists()
    (OUT/new_name).write_bytes(new)
    rows.append(dict(parent=old_name,parent_sha256=sha(old),path=new_name,sha256=sha(new),bytes=len(new),reason=reason))

def runtime(old):
    pattern=b' - 23 + '
    assert old.count(pattern)==2
    return old.replace(pattern,b' - (23 : UInt32) + ')
save('development-word-add-runtime3.lean','development-word-add-runtime4.lean',runtime,
     'Actual HSub UInt32 Nat errors in complete result-exponent expressions: specify UInt32 subtraction literal explicitly. Fixed-width arithmetic is unchanged.')

def fields(old):
    wrong=b'  rw [UInt32.toNat_shiftLeft, Nat.mod_eq_of_lt (by omega)]'
    fixed=b'  rw [UInt32.toNat_shiftLeft, Nat.mod_eq_of_lt (show (gap u v).toNat < 32 by omega)]'
    assert old.count(wrong)==1
    result=old.replace(wrong,fixed)
    wrong=b'      have ht : sameSign u v = true := by rw [sameSign_sorted, heq]; rfl'
    fixed=b'      have ht : sameSign u v = true := by rw [sameSign_sorted, beq_iff_eq]; exact heq'
    assert result.count(wrong)==1
    result=result.replace(wrong,fixed)
    wrong=b'''  unfold leadingWord
  rw [UInt32.toNat_add, UInt32.toNat_shiftRight, hplus,
    Nat.mod_eq_of_lt (by omega), magnitudeWord_nat u v hd, base_word_nat u v hd]
  rw [\xe2\x86\x90 he]
  exact Nat.mod_eq_of_lt (by omega)'''
    fixed=b'''  have hshift :
      (magnitudeWord u v >>> (((if sameSign u v then (23 : UInt32) else 22) + gap u v) + 1)).toNat =
        magnitudeNat u v >>> (baseNat u v + 1) := by
    rw [UInt32.toNat_shiftRight, hplus,
      Nat.mod_eq_of_lt (show baseNat u v + 1 < 32 by omega), magnitudeWord_nat u v hd]
  unfold leadingWord
  rw [UInt32.toNat_add, base_word_nat u v hd, hshift, \xe2\x86\x90 he]
  exact Nat.mod_eq_of_lt (show (magnitudeNat u v).log2 < 4294967296 by omega)'''
    assert result.count(wrong)==1
    return result.replace(wrong,fixed)
save('development-word-add-fields2.lean','development-word-add-fields3.lean',fields,
     'Actual rewrite selected the outer modulus; bind the inner mod32 identities explicitly. Use Bool lawful BEq equality instead of definitional rfl.')

def spec(old):
    wrong=b'''    R7W02.exec_toModel_eq_rawModel, R7W02.exec_toModel_eq_rawModel]
  simpa only [R2W01c.rawModel_eq_native32] using core_model x.raw.1 y.raw.1 hd he'''
    fixed=b'''    R7W02.exec_toModel_eq_rawModel x, R7W02.exec_toModel_eq_rawModel y,
    \xe2\x86\x90 R2W01c.rawModel_eq_native32 x.raw.1, \xe2\x86\x90 R2W01c.rawModel_eq_native32 y.raw.1]
  exact core_model x.raw.1 y.raw.1 hd he'''
    assert old.count(wrong)==1
    return old.replace(wrong,fixed)
save('development-word-add-spec2.lean','development-word-add-spec3.lean',spec,
     'Actual simp type mismatch between configured carrier format and NativeBinary32 Value. Match the established explicit reverse raw-model rewrites before exact core_model.')
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),run=40149766137,
            state='ACTUAL_COMPILER_REPAIR_FRAGMENTS_NOT_COMPILED',runtime_math_changed=False,repairs=rows,
            remaining='Research fixes small-shift RNE/alignment/masked_fraction; integrate all actual errors together in new exact sources, then rerun original compilation.')
(OUT/'development-word-add-fields-repair3.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps(record))
