"""Verify exact original bytes + one candidate's statement/replay/helper scope.
Read-only on D evidence; no official validator, candidate or CI mutation.
"""
from pathlib import Path
import datetime, hashlib, json, sys
HERE=Path(__file__).resolve().parent
run,name,source_sha,head,count=sys.argv[1:]; count=int(count)
root=HERE.parent/'ci-runs'/run
ip=root/'original-artifact-hashes.json'; index=json.loads(ip.read_bytes())
directory=(root/index['directory']).resolve()
assert directory.is_relative_to(root.resolve())
assert str(index['artifact']['workflow_run']['id'])==run
assert index['artifact']['workflow_run']['head_sha']==head
total=0
for rel,meta in index['files'].items():
    p=(directory/rel).resolve(); assert p.is_relative_to(directory)
    raw=p.read_bytes(); assert len(raw)==meta['bytes'] and hashlib.sha256(raw).hexdigest()==meta['sha256'],rel
    total+=len(raw)
source=directory/'inputs'/name/'Kernel.lean'
assert hashlib.sha256(source.read_bytes()).hexdigest()==source_sha
diag=directory/'diagnostics'/name
v=json.loads((directory/(name+'-verdict.json')).read_bytes())
assert v['verifier_fingerprint']==v['verifier_fingerprint_end']
result={'verified_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'run':run,'head':head,'candidate':name,'source_sha256':source_sha,'original_files':len(index['files']),'original_bytes':total,'index_sha256':hashlib.sha256(ip.read_bytes()).hexdigest(),'passed':v['passed'],'stage':v['stage'],'new_Lean_run':False,'scope':'Original statement/module/helper evidence only; no performance/adoption inherited.'}
if v['passed']:
    a=json.loads((diag/'helper-audit.json').read_bytes())
    assert a['kernel_sha256']==source_sha and a['expected_count']==count
    assert a['accepted'] and a['kernel_replay'] and a['exit_code']==0
    assert len(a['names'])==len(set(a['names']))==count and set(a['reports'])==set(a['names'])
    allowed={'propext','Classical.choice','Quot.sound'}
    assert all(set(row)<=allowed for row in a['reports'].values())
    raw=(diag/'helper-axioms.raw').read_bytes()
    assert hashlib.sha256(raw).hexdigest()==a['output_sha256']
    log=(diag/'replay.log').read_text(encoding='utf-8')
    assert '[kernel] Submission replays cleanly' in log and '[kernel] VerifyFull replays cleanly' in log
    assert v['stage']=='helper-axioms' and v['diagnostic_only'] and v['ratio'] is None
    result.update(helper_count=count,roots=a['names'],modules=['Submission','VerifyFull'],allowed_axioms_only=True)
else:
    result.update(reason=v.get('reason'),helper_acceptance='NOT_ESTABLISHED')
out=HERE/f'originals-verified-{run}-{name}.json'
out.write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(result,ensure_ascii=False))
