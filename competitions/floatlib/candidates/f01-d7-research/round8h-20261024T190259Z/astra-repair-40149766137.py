"""Version only research-owned proof repairs; never change frozen D sources."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json

base=Path(__file__).resolve().parent;root=base.parents[4]
changes=[
 ('astra-biased-rne2.lean','astra-biased-rne3.lean',[(b'    simp only [beq_iff_eq]\r\n',b''),(b'    simp only [beq_iff_eq]\n',b'')]),
 ('astra-small-shift-bias2.lean','astra-small-shift-bias3.lean',[(b'    simp only [beq_iff_eq] <;>\n',b'')]),
 ('astra-word-add-alignment2.lean','astra-word-add-alignment3.lean',[
  (b'    simpa only [Int.ofNat_eq_natCast] using\n',b'    exact\n'),
  (b'simpa only [magnitude, if_pos rfl] using', 'simpa only [magnitude, ↓reduceIte] using'.encode()),
  (b'simpa only [magnitude, if_neg hs] using', 'simpa only [magnitude, if_neg hs, ↓reduceIte] using'.encode())]),
 ('astra-word-add-rounding1.lean','astra-word-add-rounding2.lean',[
  (b'  have hrhi := roundShiftRightEven_le_shiftRight_add1 n k\n',
   b'  have hrhi := roundShiftRightEven_le_shiftRight_add1 n k\n  change n >>> k <= roundShiftRightEven n k at hrlo\n  change roundShiftRightEven n k <= (n >>> k) + 1 at hrhi\n  rw [Nat.shiftRight_eq_div_pow] at hrlo hrhi\n'.replace(b'<=','≤'.encode()))])]
files=[]
for src,dst,replacements in changes:
    old=(base/src).read_bytes();new=old; applied=[]
    for before,after in replacements:
        count=new.count(before)
        if count:
            assert count==1,(src,count)
            new=new.replace(before,after);applied.append(before.decode().strip())
    assert applied and new!=old
    path=base/dst
    if path.exists():assert path.read_bytes()==new
    else:path.write_bytes(new)
    files.append(dict(original=src,original_sha256=sha256(old).hexdigest(),
        path=dst,bytes=len(new),sha256=sha256(new).hexdigest(),edits=applied))
path=base/'astra-integer-core-model2.lean';raw=path.read_bytes()
files.append(dict(path=path.name,bytes=len(raw),sha256=sha256(raw).hexdigest(),
    replaces='Submission.R14ExponentShift.core_model in exact5556 source; statement unchanged'))
align3=(base/'astra-word-add-alignment3.lean').read_bytes()
needle=b'  \xc2\xb7 simpa only [Int.ofNat_eq_natCast] using\n'
assert align3.count(needle)==1
align4=align3.replace(needle,b'  \xc2\xb7 exact\n')
target=base/'astra-word-add-alignment4.lean'
if target.exists():assert target.read_bytes()==align4
else:target.write_bytes(align4)
files.append(dict(path=target.name,bytes=len(align4),sha256=sha256(align4).hexdigest(),
    replaces='alignment2; version3 preserves intermediate same-sign fix but still had offset simplification. Use4 in next source.'))
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
    state='EXACT_COMPILER_FEEDBACK_REPAIR_DRAFT_NOT_RUN',run=40149766137,
    source_commit='e5b2f2d3da9b420f4b470e6841cd0778a7e72173',files=files,
    rationale=['norm_num already normalized beq; redundant simp-only caused actual no-progress errors',
      'Explicit record-projection nonzero types and concrete roundDyadic magnitude in MUL bridge',
      'Direct alignLeftOffset term avoids the failed partial Nat-to-Int literal simplification',
      'Explicit reduceIte closes residual if True in same-sign record',
      'Normalize Nat.shiftRight and shift notation before omega ties quotient and RNE bounds'],
    scope='Only astra new versions. D rebuilds exact integer/ADD/combined candidates; no frozen source, runtime, gate or CI changes by R.')
(base/'astra-repair-40149766137.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,ensure_ascii=False,indent=2))
