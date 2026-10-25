"""Refresh authenticated same-champion metadata while preserving numeric bytes."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];D7=HERE.parent
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
read=lambda p:json.loads(p.read_bytes())
save=lambda p,x:p.write_bytes((json.dumps(x,ensure_ascii=False,indent=2)+'\n').encode())
snap=D7/'official-20261025T121232Z';r=read(snap/'receipts.json')
assert r['status']=='VERIFIED_SNAPSHOT' and r['compatible_frozen_protocol']
for row in r['responses'].values():
    p=snap/row['file'];assert sha(p)==row['sha256'] and p.stat().st_size==row['bytes']
detail=read(snap/'champion-detail.raw');report=read(snap/'champion-report.raw')['report']
if isinstance(report,str):report=json.loads(report)
champion=next(x for x in read(snap/'champions.raw') if x['current'])
competition=read(snap/'competition.raw');model=D7/'champion-time-estimate.json';before=model.read_bytes();m=json.loads(before)
assert sha(model)=='9222bdf6edec6efe75c009203405357155045f75028727a2e1fc237b9a343e53'
assert detail['id']==r['champion']==champion['submission']==int(report['submission'])==309
assert detail['digest']==m['champion_digest'] and detail['verification_current'] and detail['state']=='accepted' and report['passed'] and detail['classes']==report['classes']
view_path=D7/'multiplier-comparison.json';view=read(view_path)
assert view['champion']['submission']==detail['id'] and view['kernel_sha256']==m['kernel_sha256']
view['champion'].update(snapshot=competition['current_snapshot_id'],receipts=(snap/'receipts.json').relative_to(ROOT).as_posix(),checked_at_utc=r['queried_at_utc'],official_cumulative_speedup_vs_shipped=champion['speedup_vs_shipped'],official_speedup_basis=champion['speedup_basis'])
save(view_path,view)
pointer=read(D7/'current-official-snapshot.json');pointer.update(queried_at_utc=r['queried_at_utc'],directory=snap.name,champion=detail['id'],official_commit=r['official_commit'],policy_snapshot=competition['current_snapshot_id']);save(D7/'current-official-snapshot.json',pointer)
assert model.read_bytes()==before
save(HERE/'development-closing-official-metadata.json',dict(at_utc=datetime.now(timezone.utc).isoformat(),snapshot=snap.relative_to(ROOT).as_posix(),receipt_sha256=sha(snap/'receipts.json'),champion=detail['id'],digest=detail['digest'],model_sha256_unchanged=sha(model)))
print(json.dumps(dict(champion=detail['id'],snapshot=snap.name,numeric_model_unchanged=True)))
