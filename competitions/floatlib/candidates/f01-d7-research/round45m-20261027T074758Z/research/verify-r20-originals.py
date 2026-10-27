"""Read-only verification of collected original bytes and exact diagnostic scope."""
from pathlib import Path
import datetime, hashlib, json, re, sys
HERE=Path(__file__).resolve().parent
ROUND=HERE.parent
CASES={
 '40471664006':('f01-r20-dev-row-broadcast8-probe1','ec40e88eb85730520a1cd1e6adcbaea3c8161fc5c0f7e4b2f5795e178d24a5a6','a0724a5bbe97b9cf819b3c4bde05083c22bcb2c5',9),
 '40472418849':('f01-r20-dev-terminal-pair-probe1','b6b77553d49e968db27639b84f104783a9cf474ed963ec9cff7753a7adb17962','f83ab58684d0f7dd627fcad56c36ac0e881fc14d',8)
}
run=sys.argv[1]; name,sha,head,count=CASES[run]
root=ROUND/'ci-runs'/run
index_path=root/'original-artifact-hashes.json'
index=json.loads(index_path.read_bytes()); directory=(root/index['directory']).resolve()
assert directory.is_relative_to(root.resolve())
assert str(index['artifact']['workflow_run']['id'])==run
assert index['artifact']['workflow_run']['head_sha']==head
total=0
for rel,info in index['files'].items():
    path=(directory/rel).resolve(); assert path.is_relative_to(directory)
    raw=path.read_bytes(); assert len(raw)==info['bytes'] and hashlib.sha256(raw).hexdigest()==info['sha256'],rel
    total+=len(raw)
assert hashlib.sha256((directory/'inputs'/name/'Kernel.lean').read_bytes()).hexdigest()==sha
diag=directory/'diagnostics'/name
audit=json.loads((diag/'helper-audit.json').read_bytes())
assert audit['kernel_sha256']==sha and audit['expected_count']==count
assert audit['accepted'] and audit['kernel_replay'] and audit['exit_code']==0
assert len(audit['names'])==len(set(audit['names']))==count
assert set(audit['reports'])==set(audit['names'])
allowed={'propext','Classical.choice','Quot.sound'}
assert all(set(v)<=allowed for v in audit['reports'].values())
rawaudit=(diag/'helper-axioms.raw').read_bytes()
assert hashlib.sha256(rawaudit).hexdigest()==audit['output_sha256']
found=re.findall(r"'([^']+)' depends on axioms: \[([^]]*)\]",rawaudit.decode())
assert [n for n,_ in found]==audit['names']
assert all(set(x.strip() for x in a.split(','))<=allowed for _,a in found)
log=(diag/'replay.log').read_text(encoding='utf-8')
assert '[kernel] Submission replays cleanly' in log and '[kernel] VerifyFull replays cleanly' in log
verdict=json.loads((directory/(name+'-verdict.json')).read_bytes())
assert verdict['passed'] and verdict['stage']=='helper-axioms' and verdict['diagnostic_only']
assert verdict['ratio'] is None and verdict['rounds']==[]
assert verdict['verifier_fingerprint']==verdict['verifier_fingerprint_end']
out={'verified_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'run':run,'head':head,'source_sha256':sha,'original_files':len(index['files']),'original_bytes':total,'index_sha256':hashlib.sha256(index_path.read_bytes()).hexdigest(),'helper_roots':audit['names'],'kernel_replay_modules':['Submission','VerifyFull'],'allowed_axioms_only':True,'scope':'Exact diagnostic source statement, complete-module replay, explicit helper roots. Four public algorithms are still B2; no new public BMM specification, full gate, or performance result.','native_cost_review':'SEPARATE_NOT_ESTABLISHED_BY_THIS_RECEIPT'}
(HERE/('originals-verified-'+run+'.json')).write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,ensure_ascii=False))
