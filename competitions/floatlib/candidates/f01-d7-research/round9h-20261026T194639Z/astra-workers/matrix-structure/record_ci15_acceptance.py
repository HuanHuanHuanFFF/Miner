"""Final targeted acceptance binding only. No source edits, builds, research or CI."""
from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40435830288'
iraw=(run/'original-artifact-hashes.json').read_bytes();idx=json.loads(iraw);aroot=run/idx['directory']
suite=aroot/'diagnostics/f01-d7-public-suite/public-suite'
now=datetime.now(timezone.utc).isoformat();accepted=[]
jobs=[('f01-r19-dev-dual-temporal-a4-5',H/'dual-temporal-frontier/proof5/Kernel-dual-temporal-a4-proof5.lean',H/'dual-temporal-frontier',18,'New Dual A4+B8 BMM all-input original specification; original add/mul/sum specs retained','c36bc2502904bf946d442de1a4646e09689f016643f09ab0b6788f9bdd375250'),
 ('f01-r19-dev-jam-variable-math1',H/'grs-jam-math/low-state-repair1/Probe-jam-variable-repair1.lean',H/'grs-jam-math',15,'New Nat variable-drop jam-RNE lemmas; public arithmetic remains original B2, not actual new public ADD','b3724bc5cb19a85fdae25187d8700bb43233ab4098a9c0a92b97a36d0eaac496')]
for name,local,folder,count,scope,expected in jobs:
 d=suite/'diagnostics'/name
 paths={'source':suite/'inputs'/name/'Kernel.lean','verdict':suite/(name+'-verdict.json'),'helper_audit':d/'helper-audit.json','helper_source':d/'helper-audit-source.lean','helper_axioms_raw':d/'helper-axioms.raw','replay':d/'replay.log','diagnostic_index':d/'index.json'}
 bind={}
 for key,p in paths.items():
  raw=p.read_bytes();rec=idx['files'][p.relative_to(aroot).as_posix()]
  assert sha(raw)==rec['sha256'] and len(raw)==rec['bytes']
  bind[key]={'path':str(p.resolve()),'sha256':sha(raw),'bytes':len(raw)}
 assert paths['source'].read_bytes()==local.read_bytes() and sha(local.read_bytes())==expected
 v=json.loads(paths['verdict'].read_bytes());a=json.loads(paths['helper_audit'].read_bytes());di=json.loads(paths['diagnostic_index'].read_bytes());log=paths['replay'].read_text()
 assert v['passed'] is True and v['stage']=='helper-axioms' and v['diagnostic_only'] is True
 assert v['ratio'] is None and v['rounds']==[]
 assert a['accepted'] is True and a['kernel_replay'] is True and a['exit_code']==0
 assert a['kernel_sha256']==expected and a['expected_count']==count and len(a['names'])==count
 assert set(a['reports'])==set(a['names'])
 allowed={'Classical.choice','Quot.sound','propext'}
 assert set(a['allowed_axioms'])==allowed and all(set(x)<=allowed for x in a['reports'].values())
 assert a['audit_source_sha256']==bind['helper_source']['sha256'] and a['output_sha256']==bind['helper_axioms_raw']['sha256']
 assert di['replay_exit_code']==0
 for marker in ('[statement] ok','Submission replays cleanly','VerifyFull replays cleanly','[helper-axioms] ok'):assert marker in log
 expected_roots=json.loads((folder/('proof5/repair-receipt.json' if count==18 else 'low-state-repair1/manifest.json')).read_bytes())
 roots=expected_roots['explicit_helper_roots'] if count==18 else expected_roots['roots']
 assert set(roots)==set(a['names'])
 item={'recorded_utc':now,'run':40435830288,'commit_prefix':'5ad212c8','candidate':name,'local_source':str(local.resolve()),'source_sha256':expected,'source_bytes':local.stat().st_size,'artifact_root':str(aroot.resolve()),'original_index_sha256':sha(iraw),'targeted_files_verified':len(paths),'bindings':bind,'statement':'PASS','Submission_replay':'PASS','VerifyFull_replay':'PASS','helper_roots':a['names'],'helper_count':count,'allowed_only_axioms':'PASS','allowed_axioms':sorted(allowed),'scope':scope,'fullscore':'NOT_RUN','full_performance_gate':'NOT_RUN','performance':'UNKNOWN','codegen':'GENERATED_NOT_AUDITED_IN_THIS_CLOSEOUT','verifier_fingerprint':v['verifier_fingerprint'],'verifier_fingerprint_end':v['verifier_fingerprint_end'],'historical_source_headers_unchanged':True,'prior_failures_preserved':True,'new_research':False,'local_Lean':False,'CI_dispatch':False}
 assert item['verifier_fingerprint']==item['verifier_fingerprint_end']
 (folder/'accepted.json').write_text(json.dumps(item,indent=2)+'\n')
 s=json.loads((folder/'status.json').read_bytes());s['status']='ACCEPTED_STATEMENT_REPLAY_ALLOWED_AXIOMS_NO_FULLSCORE';s['updated_utc']=now;s['formal']='PASS_EXACT_CI15_SOURCE_STATEMENT_SUBMISSION_VERIFYFULL_ALLOWED_AXIOMS';s['accepted_record']='accepted.json';s['performance']='UNKNOWN';s['fullscore']='NOT_RUN';s['next']='No new research/CI in R closeout; preserve accepted source and pending performance/bridge gaps';s['acceptance_scope']=scope
 (folder/'status.json').write_text(json.dumps(s,indent=2)+'\n');accepted.append(item)
(H/'accepted.json').write_text(json.dumps({'recorded_utc':now,'run':40435830288,'commit_prefix':'5ad212c8','original_index_sha256':sha(iraw),'scope':'Targeted source/verdict/helper/replay binding, not rehash of full135 artifacts','verified_files':14,'items':accepted,'fullscore':'NOT_RUN','new_research_or_CI':False},indent=2)+'\n')
print(json.dumps([{'candidate':x['candidate'],'source_sha256':x['source_sha256'],'verdict_sha256':x['bindings']['verdict']['sha256'],'helper_sha256':x['bindings']['helper_audit']['sha256'],'helper_count':x['helper_count'],'formal':'PASS','fullscore':x['fullscore']} for x in accepted]))
