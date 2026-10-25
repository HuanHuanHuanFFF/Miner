"""Repair one independently confirmed proof reference in versioned sources."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
fragment = OUT / 'development-integer-normal-draft.lean'
raw_fragment = fragment.read_bytes()
old, new = b'FastMul.mkW_eq _ _ _', b'FastMul.mkW_ofNat _ _ _'
assert raw_fragment.count(old) == 1
fixed_fragment = raw_fragment.replace(old, new)
fragment2 = OUT / 'development-integer-normal-proof2.lean'
assert not fragment2.exists()
fragment2.write_bytes(fixed_fragment)
sources = [
    ('f01-r14-dev-integer-exponent1', '6f8808d0a6ea0c05e0ba2416a583e5ce388fa75f2ce62b04c408d2699b048dc3', 'f01-r14-dev-integer-exponent2'),
    ('f01-r14-dev-combined-slim1', 'd94060b28aa4d374c16cdd0b8ee26ee7ba570155476bbf743877e4e3212ff277', 'f01-r14-dev-combined-slim2'),
    ('f01-r14-dev-combined-headroom1', '9215865d83513fceea2f036cb138bd13764ff60196b0416150281b67fa667882', 'f01-r14-dev-combined-headroom2'),
]
rows = []
for parent_name, digest, name in sources:
    parent = C / parent_name
    original = (parent / 'Kernel.lean').read_bytes()
    assert hashlib.sha256(original).hexdigest() == digest
    assert original.count(old) == 1 and b'theorem mkW_ofNat (sign : Bool) (e f : Nat)' in original
    result = original.replace(old, new)
    assert len(result) - len(original) == 3 and len(result) <= 256000
    if parent_name == 'f01-r14-dev-integer-exponent1':
        assert hashlib.sha256(result).hexdigest() == 'b8a11a6a1c647df5031505b7effa5c3d21e653631db0638815a3062c7d20b6c2'
    folder = C / name
    assert not folder.exists()
    folder.mkdir()
    (folder / 'Kernel.lean').write_bytes(result)
    record = json.loads((parent / 'manifest.json').read_bytes())
    record.update(candidate=name, candidate_sha256=hashlib.sha256(result).hexdigest(), candidate_bytes=len(result),
                  created_at_utc=datetime.now(timezone.utc).isoformat(), parent=parent_name, parent_sha256=digest,
                  proof_status='CONFIRMED_REFERENCE_FIX_NOT_COMPILED', performance='NOT_RUN',
                  bytes_remaining=256000 - len(result),
                  repair={'old_reference':'FastMul.mkW_eq','actual_existing_theorem':'FastMul.mkW_ofNat',
                          'replacement_count':1,'independently_checked_original_declaration_line':2206,
                          'runtime_definition_source_changed':False,'all_other_kernel_bytes_preserved':True,
                          'scope':'Confirmed source name/type match, not Lean execution or acceptance.'})
    for component in record.get('components', []):
        if component['path'] == fragment.relative_to(ROOT).as_posix():
            component.update(path=fragment2.relative_to(ROOT).as_posix(), bytes=len(fixed_fragment), sha256=hashlib.sha256(fixed_fragment).hexdigest())
    if 'source_budget' in record:
        record['source_budget'] = {**record['source_budget'], 'candidate_bytes':len(result)}
    (folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
    rows.append({key: record[key] for key in ('candidate','candidate_sha256','candidate_bytes','bytes_remaining','parent','proof_status')})
receipt = dict(at_utc=datetime.now(timezone.utc).isoformat(), scope='Versioned proof-only name repair; originals, runtime statements and full evidence preserved.',
               old_fragment_sha256=hashlib.sha256(raw_fragment).hexdigest(), new_fragment_sha256=hashlib.sha256(fixed_fragment).hexdigest(), rows=rows)
(OUT / 'development-mkw-reference-repair2.json').write_bytes((json.dumps(receipt, indent=2) + '\n').encode())
print(json.dumps(receipt))
