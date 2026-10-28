"""Only the two theorem bodies implicated by the three real CI errors change."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json,difflib,re

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[6]
def sha(x):return hashlib.sha256(x).hexdigest()

def main():
    old=(OUT/'v2-guarded/Kernel.lean').read_bytes()
    assert sha(old)=='ebfb6408b3ee5639ff1d800fa1385f87b40a891bb649311449caa9418b9a26ef'
    text=old.decode('utf-8')
    cursor_old='have hcursor : r*p+2*p=(r+2)*p := by rw [Nat.add_mul]'
    cursor_new='have hcursor : r*p+2*p=(r+2)*p := by simp only [r, Nat.add_mul]'
    assert text.count(cursor_old)==1
    text=text.replace(cursor_old,cursor_new)
    start=text.index('theorem rows_eq_batchStep ')
    end=text.index('theorem output_eq_matrixOutput ',start)
    old_proof=text[start:end]
    new_proof=(OUT/'RowsEqRepair.lean.inc').read_text(encoding='utf-8')+'\n'
    text=text[:start]+new_proof+text[end:]
    new=text.encode('utf-8')
    restored=text.replace(new_proof,old_proof).replace(cursor_new,cursor_old).encode('utf-8')
    assert restored==old
    dest=OUT/'v3-proof-repair'
    dest.mkdir(exist_ok=True)
    (dest/'Kernel.lean').write_bytes(new)
    for name,a,b,ap,bp in [('forward.patch',old,new,'v2-guarded/Kernel.lean','v3-proof-repair/Kernel.lean'),
                          ('inverse.patch',new,old,'v3-proof-repair/Kernel.lean','v2-guarded/Kernel.lean')]:
        patch=''.join(difflib.unified_diff(a.decode().splitlines(keepends=True),b.decode().splitlines(keepends=True),fromfile=ap,tofile=bp))
        (dest/name).write_bytes(patch.encode())
    manifest=json.loads((OUT/'v2-guarded/manifest.json').read_text())
    manifest.update({
        'candidate':'r22-streaming-public-v3-proof-repair','created_at_utc':datetime.now(timezone.utc).isoformat(),
        'parent_sha256':sha(old),'candidate_sha256':sha(new),'candidate_bytes':len(new),
        'helper_audit_source_sha256':sha(new),'source_size_limit_pass':len(new)<=256000,
        'size_headroom_bytes':256000-len(new),'proof_status':'NOT_RUN',
        'repair_origin_run':40588875685,'repair_origin_commit':'069706669f43c2f08701a1dc734ee8b9c14f1a09',
        'observed_error_locations':[6938,7137,7141],
        'proof_bodies_changed':['R21ConcretePairPrefix.streamed_pair_prefix','R22StreamingCost.rows_eq_batchStep'],
        'runtime_guard_threshold_changes':False,'inverse_reconstruction_sha256':sha(restored),
        'explanation':'Explicitly unfold local r in cursor equality; prove pair fold definitional equality separately; transport dependent emit length through explicit equality; remove odd conditional before remainder rewriting.',
    })
    (dest/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    (dest/'HelperAudit.lean.inc').write_bytes((OUT/'v2-guarded/HelperAudit.lean.inc').read_bytes())
    print(json.dumps({k:manifest[k] for k in ['candidate_sha256','candidate_bytes','size_headroom_bytes','helper_audit_expected_count','inverse_reconstruction_sha256']},ensure_ascii=False))

if __name__=='__main__':main()
