from pathlib import Path
import hashlib
import json
import difflib
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[6]
OUT = HERE/'repair1'
OUT.mkdir(exist_ok=True)
old = (HERE/'Kernel-core-probe.lean').read_bytes()
fragment = (HERE/'Column4Temporal.lean.inc').read_bytes()
assert hashlib.sha256(old).hexdigest() == '8adff3a04e9f30b6416b4c192276d704b88ea20b34d2bbafcbaa6987d20df9ef'
source = old
new_fragment = fragment
edits=[]
for lane in ['low','high']:
    before=f'  simp only [pack, R19Temporal.pack, Packed10.vector_get_ofFn, {lane}_packet]'.encode()
    after=f'  rw [R19Temporal.pack_get]\n  simp only [pack, Packed10.vector_get_ofFn, {lane}_packet]'.encode()
    assert source.count(before)==1 and new_fragment.count(before)==1
    source=source.replace(before,after)
    new_fragment=new_fragment.replace(before,after)
    edits.append({'root':'Submission.R19Column4Temporal.pack_'+lane,
                  'old_body':before.decode(),'new_body':after.decode()})
assert len(source)<=256000
assert source.replace(edits[0]['new_body'].encode(),edits[0]['old_body'].encode()).replace(
    edits[1]['new_body'].encode(),edits[1]['old_body'].encode())==old
assert source[:-len(new_fragment)]==old[:-len(fragment)]
(OUT/'Kernel-core-repair1.lean').write_bytes(source)
(OUT/'Column4Temporal-repair1.lean.inc').write_bytes(new_fragment)
(OUT/'HelperAudit.lean.inc').write_bytes((HERE/'HelperAudit.lean.inc').read_bytes())
for name,a,b,fa,fb in [
    ('proof-only.patch',old,source,'Kernel-core-probe.lean','Kernel-core-repair1.lean'),
    ('inverse.patch',source,old,'Kernel-core-repair1.lean','Kernel-core-probe.lean')]:
    (OUT/name).write_text(''.join(difflib.unified_diff(a.decode().splitlines(True),b.decode().splitlines(True),
                                                   fromfile=fa,tofile=fb)),encoding='utf-8',newline='\n')
log_rel='competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40440668379/download-63278b5c14e6432fb4b0ae072cc3a18e/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-column4-core1/full-build-output.txt'
log=(ROOT/log_rel).read_bytes()
receipt={
    'at_utc':datetime.now(timezone.utc).isoformat(),
    'original_run':40440668379,'original_status':'FAIL_STATEMENT_TWO_PACKING_BRIDGE_GOALS',
    'original_source_sha256':hashlib.sha256(old).hexdigest(),'original_source_bytes':len(old),
    'new_source_sha256':hashlib.sha256(source).hexdigest(),'new_source_bytes':len(source),
    'new_fragment_sha256':hashlib.sha256(new_fragment).hexdigest(),'new_fragment_bytes':len(new_fragment),
    'remaining_bytes':256000-len(source),'two_proof_bodies_only':True,'inverse_exact':True,
    'frozen_source_unchanged':(HERE/'Kernel-core-probe.lean').read_bytes()==old,
    'runtime_and_parent_public_unchanged':True,
    'edits':edits,'log_path':log_rel,'log_sha256':hashlib.sha256(log).hexdigest(),
    'repair_compilation':'NOT_RUN','repair_C':'NOT_RUN','repair_timing':'NOT_RUN',
    'full_entry_integration':'STOPPED_AFTER_SCOPE_SCREEN',
}
(OUT/'receipt.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,ensure_ascii=False,indent=2))
