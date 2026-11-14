from pathlib import Path
import datetime,hashlib,json

HERE=Path(__file__).resolve().parent
old=HERE/'WordBlockComplete.lean'
s=old.read_text(encoding='utf-8')
patches=[(
'''    · exact le_trans (le_of_lt h) (ih (i + 1) (magnitude32 (f i)))
    · exact ih (i + 1) mx''',
'''    · have ht := ih (i + 1) (magnitude32 (f i))
      rw [UInt32.le_iff_toNat_le] at ht ⊢
      rw [UInt32.lt_iff_toNat_lt] at h
      omega
    · exact ih (i + 1) mx'''),(
'''      · exact le_trans (le_of_not_gt h) (maxMagnitude_initial f fuel (i + 1) mx)''',
'''      · have ht := maxMagnitude_initial f fuel (i + 1) mx
        rw [UInt32.le_iff_toNat_le] at ht ⊢
        rw [UInt32.lt_iff_toNat_lt] at h
        omega'''),(
'''    simp only [Except.map, h1, h2, hLs]''',
'''    simp [Except.map, h1, h2, hLs]''')]
for before,after in patches:
    assert s.count(before)==1
    s=s.replace(before,after)
out=HERE/'WordBlockStaticV2.lean'
out.write_text(s,encoding='utf-8',newline='\n')
record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'status':'STATIC_API_REPAIR_NOT_COMPILER_FEEDBACK',
        'input':old.name,'input_sha256':hashlib.sha256(old.read_bytes()).hexdigest(),
        'output':out.name,'output_sha256':hashlib.sha256(out.read_bytes()).hexdigest(),
        'bytes':out.stat().st_size,
        'repairs':['Use explicit UInt32.toNat order transport instead of assuming a Mathlib Preorder UInt32 instance',
                   'Match original finite-zero endpoint simplification after state flags'],
        'api_evidence':'astra-Lean-UInt-Lemmas.lean primary snapshot at pin293d5d0c, protected UInt32.le_trans and toNat comparison iff',
        'remaining':'NOT_COMPILED; actual datatype/tactic goals remain unknown',
        'new_CI_request':False}
(HERE/'static-v2-receipt.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,indent=2))
