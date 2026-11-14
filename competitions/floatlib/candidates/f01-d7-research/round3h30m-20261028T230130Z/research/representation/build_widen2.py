"""Single fixed-API spelling correction; preserve the prior frozen source."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
CANDIDATES=ROOT/'competitions/floatlib/candidates'
OLD=CANDIDATES/'f01-d7-research/round7h-20261028T203856Z/research/representation'
sha=lambda b:hashlib.sha256(b).hexdigest()
old=(OLD/'WidenNormal.lean.inc').read_bytes()
assert sha(old)=='8c2d18971875d2618aca70209aee4cf44a75f232594554ecd2c8f12152107a32'
before=b'FloatLib.Floats.Formats.Flocq.bpow_add'
after=b'FloatLib.Floats.Formats.Flocq.bpow.add_exp'
assert old.count(before)==1
fragment=old.replace(before,after)
assert fragment.replace(after,before)==old
(HERE/'WidenNormal.lean.inc').write_bytes(fragment)
base=(CANDIDATES/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
prior=(CANDIDATES/'f01-r24-research-representation-widen1/Kernel.lean').read_bytes()
assert sha(prior)=='75a1c0ae7d1f1db2836becfe8d26e9fd1e881013a2f427b4ec669b5fcf521c55'
blob=base+b'\n'+fragment
assert len(blob)<=256000
assert blob.replace(after,before)==prior
out=CANDIDATES/'f01-r24-research-representation-widen2'
out.mkdir(exist_ok=True)
(out/'Kernel.lean').write_bytes(blob)
m=json.loads((CANDIDATES/'f01-r24-research-representation-widen1/manifest.json').read_bytes())
m.update(candidate=out.name,candidate_sha256=sha(blob),candidate_bytes=len(blob),
         created_at_utc=datetime.now(timezone.utc).isoformat(),fragment_sha256=sha(fragment),
         fragment_bytes=len(fragment),helper_audit_source_sha256=sha(blob),
         components=[dict(path=(HERE/'WidenNormal.lean.inc').relative_to(ROOT).as_posix(),sha256=sha(fragment),bytes=len(fragment))],
         current_window='R24 original7h',window_start_utc='2026-10-28T20:38:56Z',
         shared_deadline_utc='2026-10-29T03:38:56Z',deadline_status='Restored original R24 after parent verified historical message timestamp',
         parent_source_sha256=sha(prior),single_change='Flocq.bpow_add -> Flocq.bpow.add_exp, fixed Core.lean line83',
         fixed_api_source_ref='0d91825727839f597fd06b22fdd038ea21480f0c',
         fixed_api_source_blob='acb14121ee0fea6812c16648cbe070d61a430e36',proof_status='NOT_RUN')
assert m['diagnostic_timeout_seconds']==180
assert hashlib.sha256((CANDIDATES/m['helper_audit_module_path']).read_bytes()).hexdigest()==m['helper_audit_module_sha256']
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf-8')
receipt=dict(created_at_utc=datetime.now(timezone.utc).isoformat(),candidate=m['candidate'],
    candidate_sha256=sha(blob),candidate_bytes=len(blob),fragment_sha256=sha(fragment),
    parent_sha256=sha(prior),single_replacement_inverse_verified=True,old_source_unchanged=True,
    full_B2_prefix_identical=blob[:len(base)]==base,helper_path_convention='candidates relative',
    component_path_convention='repository root relative',diagnostic_timeout_seconds=180,
    Lean='NOT_RUN',native='NOT_RUN',CI_owner='D',shared_deadline_utc=m['shared_deadline_utc'])
(HERE/'widen2-source-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt))
