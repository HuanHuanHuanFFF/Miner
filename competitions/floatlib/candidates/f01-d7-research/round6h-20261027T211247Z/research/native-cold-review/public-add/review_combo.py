from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json

here = Path(__file__).resolve().parent
repo = next(p for p in here.parents if (p/'AGENTS.md').is_file())
round_dir = here.parents[2]
old = (here/'Kernel.lean').read_bytes()
path = repo/'competitions/floatlib/candidates/f01-r22-dev-nativecombo-public1/Kernel.lean'
new = path.read_bytes()
assert sha256(old).hexdigest() == '75da1c417a77ab03135897d0c4778f4dece80af3919084db9bd08dad80ae10fa'
assert sha256(new).hexdigest() == 'f7ba2ddb12939f518e5beb60daf927d9d9d80d24262edd740eefd5e8e917cc03'
anchor = b'\nend R22NativeAddBase\n\n'
old_end, new_end = old.index(anchor), new.index(anchor)
assert new[:old_end] == old[:old_end]
insert = new[old_end:new_end]
parts = {}
for name in ['NativeCold.lean.inc','PairDomain.lean.inc','MulEntryProof.lean.inc']:
    p = round_dir/'development-native-public-combo'/name
    raw = p.read_bytes()
    assert insert.count(raw) == 1
    parts[name] = {'sha256':sha256(raw).hexdigest(),'bytes':len(raw)}
    insert = insert.replace(raw,b'',1)
assert not insert.strip()
old_mul = b'@[inline] def mul := R22NativeAddBase.Submission.mul\ntheorem mul_spec : \xe2\x88\x80 x y : Binary32, mul x y = ExecFloat.Spec.mul x y :=\n  R22NativeAddBase.Submission.mul_spec'
new_mul = b'@[inline] def mul (x y : Binary32) : Binary32 :=\n  R22NativeAddBase.Submission.R22NativeCold.coldMul x y\ntheorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=\n  R22NativeAddBase.Submission.R22NativeCold.coldMul_spec x y'
assert new[new_end:].replace(new_mul,old_mul,1) == old[old_end:]
out = {'checked_utc':datetime.now(timezone.utc).isoformat(), 'first_tool_utc':'2026-10-28T01:28:04Z',
       'source':{'path':path.relative_to(repo).as_posix(),'sha256':sha256(new).hexdigest(),'bytes':len(new)},
       'parts':parts,'original75da_body_unchanged':True,'inverse_splice_exact':True,
       'review_scope':'Only added native-MUL runtime, PairDomain, MulEntryProof and public MUL alias/spec; no repeated ADD review',
       'finding':'NO_DEFINITE_INTERFACE_ERROR_FOUND_STATIC_ONLY',
       'checked':['relative namespace binds to R22NativeAddBase.Submission inner modules',
                  'pairOK wrapping OR implies both NormalBand then fastOK',
                  'hotMul unfolds to existing native_mul_spec_of_fastOK',
                  'cold retainedMul unfolds to old carrier Submission.mul, not new outside public MUL',
                  'public MUL alias/spec targets matching coldMul/coldMul_spec; ADD/SUM/BMM suffix otherwise exact'],
       'parent_metadata_notice':'Root separately identified stale files.Kernel path/hash/bytes and other_public_operations/carrier strings; D owns metadata repair. Not independently re-audited here.',
       'Lean':'NOT_RUN','CI':'NOT_RUN','performance':'NOT_RUN_FOR_COMBINED_PUBLIC_SOURCE'}
(here/'combo-static-review.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'finding':out['finding'],'parts':parts,'checked_utc':out['checked_utc']}))
