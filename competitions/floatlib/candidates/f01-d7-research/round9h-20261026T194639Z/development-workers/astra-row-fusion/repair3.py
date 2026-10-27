from pathlib import Path
import hashlib
import json
import difflib
from datetime import datetime, timezone

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[6]
OUT=HERE/'repair3'
OUT.mkdir(exist_ok=True)
def sha(x): return hashlib.sha256(x).hexdigest()
before=b'@[inline] def blocks (n : Nat) : Nat := (n+3)/4'
after=b'@[inline] abbrev blocks (n : Nat) : Nat := (n+3)/4'
inputs=[
 ('core',HERE/'repair2/Kernel-core-repair2.lean',
  '036372fd3fdca079ef36e6ee2773c9ce27d8aeddc3f29d01257772f29c931e20','Kernel-core-repair3.lean'),
 ('retained-broad',HERE/'repair2/Kernel-column4-broad-retained-repair2.lean',
  '386b5fec7a2595b1fa7e47b283abb3bdbd75066a4591ab3a5740e1cf0106741d','Kernel-column4-broad-retained-repair3.lean'),
]
outputs=[]
for name,path,expected,filename in inputs:
    old=path.read_bytes()
    assert sha(old)==expected,(name,sha(old))
    assert old.count(before)==1
    start=old.index(b'namespace Submission.R19DualTemporal')
    end=old.index(b'end Submission.R19DualTemporal',start)
    assert before in old[start:end]
    new=old.replace(before,after)
    assert new.count(after)==1 and new.replace(after,before)==old
    assert len(new)<=256000
    (OUT/filename).write_bytes(new)
    for suffix,a,b,fa,fb in [
      ('reducibility-only.patch',old,new,path.name,filename),
      ('inverse.patch',new,old,filename,path.name)]:
        (OUT/(name+'-'+suffix)).write_text(''.join(difflib.unified_diff(
          a.decode().splitlines(True),b.decode().splitlines(True),fromfile=fa,tofile=fb)),
          encoding='utf-8',newline='\n')
    assert path.read_bytes()==old
    outputs.append({'kind':name,'input':str(path),'input_sha256':sha(old),'input_bytes':len(old),
                    'output':filename,'sha256':sha(new),'bytes':len(new),'remaining_bytes':256000-len(new),
                    'one_def_to_abbrev_keyword_change_only':True,
                    'computational_RHS_and_all_other_bytes_exact':True,
                    'all_proof_bodies_including_repair2_exact':True,
                    'inverse_exact':True,'original_unchanged':True})
for name in ['CoreHelperAudit.lean.inc','BroadHelperAudit.lean.inc']:
    (OUT/name).write_bytes((HERE/'repair2'/name).read_bytes())
logs=[]
for candidate in ['f01-r19-dev-column4-core3','f01-r19-dev-column4-broad1']:
    rel=('competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40443955689/'
         'download-499e562a2b2a403e95869602f2cfd5c4/diagnostics/f01-d7-public-suite/public-suite/'
         'diagnostics/'+candidate+'/full-build-output.txt')
    data=(ROOT/rel).read_bytes()
    assert b'not type-correct under the `implicit` transparency level' in data
    assert b'Fin (blocks n)' in data and b'Fin ((n + 3) / 4)' in data
    logs.append({'candidate':candidate,'path':rel,'bytes':len(data),'sha256':sha(data)})
receipt={
 'at_utc':datetime.now(timezone.utc).isoformat(),'status':'INTERFACE_REDUCIBILITY_REPAIR_NOT_RUN',
 'window_start_utc':'2026-10-27T03:34:35Z','deadline_utc':'2026-10-27T03:44:35Z',
 'failure_run':40443955689,'failure':'Two packing goals and broad finish_select fail implicit-transparency type checking of the same semireducible Nat length alias.',
 'one_changed_declaration':'Submission.R19DualTemporal.blocks',
 'old_header':before.decode(),'new_header':after.decode(),
 'reason':'abbrev makes this definitional length alias reducible for implicit-transparency matching at every Fin and Vector interface; retain repair2 proofs as the fixed test rather than substituting more rw/simp rules.',
 'no_added_axioms_options_or_compiler_flags':True,
 'runtime_expression':'Same (n+3)/4; existing inline attribute unchanged. Generated C identity is not yet measured.',
 'outputs':outputs,'original_logs':logs,
 'compile':'NOT_RUN','kernel_replay':'NOT_RUN','axiom_audit':'NOT_RUN','generated_C':'NOT_RUN','timing':'NOT_RUN',
 'cost_boundary':'New prior-DC odd-column phantom MAC and complete A4/B16 preparation/residency/destruction remain costs; this metadata repair does not change them.',
 'D17_or_confirmation_read':False,'worker_Git_CI_local_Lean':0,
}
(OUT/'receipt.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,ensure_ascii=False,indent=2))
