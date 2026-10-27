from pathlib import Path
import hashlib
import json
import difflib
from datetime import datetime, timezone

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[6]
OUT=HERE/'repair2'
OUT.mkdir(exist_ok=True)
def sha(b): return hashlib.sha256(b).hexdigest()
core_path=HERE/'repair1/Kernel-core-repair1.lean'
broad_path=ROOT/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-column4-broad-retained.lean'
inputs=[
 ('core',core_path,'118d8efc9e8c3d92189913c0aae3d66bca1394a677ec09957174c9d9e97eb1fc','Kernel-core-repair2.lean'),
 ('retained-broad',broad_path,'7f1d4ec3f724526b83b17c28a6b392c7d4acb31e830fd141fae5ba5ea7429084','Kernel-column4-broad-retained-repair2.lean'),
]
edits=[]
for lane in ['low','high']:
    before=(f'  rw [R19Temporal.pack_get]\n'
            f'  simp only [pack, Packed10.vector_get_ofFn, {lane}_packet]').encode()
    after=(f'  dsimp only [R19DualTemporal.blocks, pack, R19Temporal.pack] at *\n'
           f'  simp only [Packed10.vector_get_ofFn, {lane}_packet]').encode()
    edits.append({'root':'Submission.R19Column4Temporal.pack_'+lane,
                  'old_body':before.decode(),'new_body':after.decode()})

outputs=[]
for name,path,expected,out_name in inputs:
    old=path.read_bytes()
    assert sha(old)==expected,(name,sha(old))
    new=old
    for edit in edits:
        before=edit['old_body'].encode(); after=edit['new_body'].encode()
        assert new.count(before)==1,(name,edit['root'])
        # The replacement must be in the exact expected theorem body.
        theorem=('theorem '+edit['root'].split('.')[-1]+' ').encode()
        start=new.index(theorem)
        stop=new.index(b'\ntheorem ',start+len(theorem)) if b'\ntheorem ' in new[start+len(theorem):] else len(new)
        assert before in new[start:stop]
        new=new.replace(before,after)
    restored=new
    for edit in edits:
        restored=restored.replace(edit['new_body'].encode(),edit['old_body'].encode())
    assert restored==old
    assert len(new)<=256000,(name,len(new))
    (OUT/out_name).write_bytes(new)
    for suffix,a,b,fa,fb in [
      ('proof-only.patch',old,new,path.name,out_name),
      ('inverse.patch',new,old,out_name,path.name)]:
        (OUT/(name+'-'+suffix)).write_text(''.join(difflib.unified_diff(
          a.decode().splitlines(True),b.decode().splitlines(True),fromfile=fa,tofile=fb)),
          encoding='utf-8',newline='\n')
    assert path.read_bytes()==old
    outputs.append({'kind':name,'original_path':str(path),'original_sha256':sha(old),
                    'original_bytes':len(old),'output':out_name,'sha256':sha(new),'bytes':len(new),
                    'remaining_bytes':256000-len(new),'only_two_proof_bodies_changed':True,
                    'inverse_exact':True,'original_file_unchanged':True,
                    'runtime_and_other_proofs_byte_identical':True})
fragment=(HERE/'repair1/Column4Temporal-repair1.lean.inc').read_bytes()
for edit in edits:
    assert fragment.count(edit['old_body'].encode())==1
    fragment=fragment.replace(edit['old_body'].encode(),edit['new_body'].encode())
(OUT/'Column4Temporal-repair2.lean.inc').write_bytes(fragment)
(OUT/'CoreHelperAudit.lean.inc').write_bytes((HERE/'repair1/HelperAudit.lean.inc').read_bytes())
(OUT/'BroadHelperAudit.lean.inc').write_bytes((HERE/'broad-draft/HelperAudit.lean.inc').read_bytes())
log_rel='competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40442288468/download-8092dcfe5ed54ed9a9c4468707e0243d/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-column4-core2/full-build-output.txt'
log=(ROOT/log_rel).read_bytes()
assert b'not type-correct under the `implicit` transparency level' in log
assert b'Fin (blocks n)' in log and b'Fin ((n + 3) / 4)' in log
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'PROOF_ONLY_REPAIR_NOT_RUN',
         'window_start_utc':'2026-10-27T03:17:16Z','deadline_utc':'2026-10-27T03:31:00Z',
         'actual_failure_run':40442288468,'actual_failure_source':inputs[0][2],
         'log_path':log_rel,'log_sha256':sha(log),
         'cause':'The rewrite target itself fails implicit-transparency type checking: t has Fin(blocks n), while old pack.get requires Fin((n+3)/4).',
         'change':'Explicitly normalize blocks in all local types and the goal, and expose both pack producers before applying the shared ofFn getter lemma. No rewrite-lemma substitution.',
         'edits':edits,'outputs':outputs,'fragment_sha256':sha(fragment),'fragment_bytes':len(fragment),
         'compilation':'NOT_RUN','kernel_replay':'NOT_RUN','axiom_audit':'NOT_RUN','generated_C':'NOT_RUN','timing':'NOT_RUN',
         'cost_boundary':'For new DirectContinuous odd p=3/7, phantom MACs are additional versus its old exact p-column loop; same ceil guard only avoids extra phantom MACs relative to a B2-pair baseline.',
         'D17_or_confirmation_input_results_accessed':False,'own_Git_CI_Lean_operations':0}
(OUT/'receipt.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,ensure_ascii=False,indent=2))
