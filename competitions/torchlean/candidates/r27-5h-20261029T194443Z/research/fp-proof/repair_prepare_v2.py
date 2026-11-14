from pathlib import Path
import json,hashlib,re
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd();E=ROOT/'competitions/torchlean/candidates/r27-5h-20261029T194443Z/evidence/40945451009/download-b99ae08657c2480f99ece8b5894ffd2f'
summary=json.loads((E/'summary.json').read_bytes());logs=[]
for n in ['old_key_core','old_prepare_core']:
 p=E/(n+'-helper.log');b=p.read_bytes();s=b.decode();axs=re.findall(r'depends on axioms: \[([^\]]*)\]',s)
 logs.append(dict(name=n,path=p.relative_to(ROOT).as_posix(),sha256=hashlib.sha256(b).hexdigest(),bytes=len(b),error_count=len(re.findall(r': error:',s)),axiom_roots=len(axs),allowed_only=all(set(v.strip() for v in a.split(','))<={'propext','Classical.choice','Quot.sound'} for a in axs) if axs else 'NOT_AUDITED'))
receipt=dict(at_utc=datetime.now(timezone.utc).isoformat(),run_id=40945451009,source_commit=summary['source_commit'],official_commit=summary['official_commit'],finished_at_utc=summary['finished_at_utc'],helper_diagnostics=summary.get('helper_diagnostics'),logs=logs,key_core='STANDALONE_ELABORATION_AND_4_ALLOWED_AXIOM_ROOTS_PASS_EXACT4e1ed0b4',prepare_core='FOUR_UNSIMPLIFIED_LET_ID_RUN_GOALS',full_gate='NOT_RUN',native_or_champion_claim=False)
(H/'batch1-proof-receipt.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
(H/'producer-v2').mkdir(exist_ok=True)
changes=[]
for n in ['PrepareCoreContractOnly','PrepareAgreementContractOnly','PreparePeakContractOnly']:
 s=(H/'producer-v1'/(n+'.lean')).read_text(encoding='utf-8-sig')
 assert '  unfold step body\n  split_ifs <;> rfl' in s
 s=s.replace('  unfold step body\n  split_ifs <;> rfl','  unfold step body\n  dsimp only\n  split_ifs <;> rfl')
 s=s.replace('  simp only [prepare, h, ite_true]','  simp only [prepare, h, ite_true] <;> rfl')
 s=s.replace('  simpa only [prepare, hlarge, ite_false, body]','  simp only [prepare, hlarge, ite_false]\n  rfl')
 s=s.replace('  simpa only [hb, Array.forIn_pure_yield_eq_foldl]','  simp only [hb, Array.forIn_pure_yield_eq_foldl] <;> rfl')
 s=s.replace('  unfold step body stored expWord\n  split_ifs','  unfold step body stored expWord\n  dsimp only\n  split_ifs')
 s=s.replace('  unfold step body expWord\n  split_ifs','  unfold step body expWord\n  dsimp only\n  split_ifs')
 p=H/'producer-v2'/(n+'.lean');p.write_text(s,encoding='utf-8',newline='\n');b=p.read_bytes()
 roots=['Submission.R25PrepareAgreement.body_yields','Submission.R25PrepareAgreement.prepare_overflow','Submission.R25PrepareAgreement.prepare_eq_forIn','Submission.R25PrepareAgreement.prepare_eq_fold']
 if n!='PrepareCoreContractOnly':roots+=['Submission.R25PrepareAgreement.prepare_getter_interface']
 if n=='PreparePeakContractOnly':roots+=['Submission.R26PreparePeak.prepare_full_interface']
 changes.append(dict(name=n,path=p.relative_to(ROOT).as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),helper_roots=roots,depends_on=[] if n=='PrepareCoreContractOnly' else ['PrepareCoreContractOnly']))
(H/'producer-v2/repair-receipt.json').write_text(json.dumps(dict(at_utc=datetime.now(timezone.utc).isoformat(),prior_raw_log=logs[1],changes='Reduce local lets before split_ifs; finish definitional Id.run/pure/bind equalities using rfl. Original runtime/statements unchanged. Apply identical let exposure to later step_values/step_valid.',sources=changes,proof='NOT_RUN'),ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
p=H/'CI-REQUEST.json';d=json.loads(p.read_bytes());d['state']='READY_NEXT_WAVE_CORE_ACCEPTED_PREPARE_REPAIRED';d['updated_at_utc']=datetime.now(timezone.utc).isoformat();d['first_batch_result']='key core4roots PASS allowed-only; prepare core4let/Id.run errors logged';d['candidates']=[x for x in d['candidates'] if x['name']!='PrepareAgreementContractOnly'];d['candidates']+=changes[:2];d['independent_optional']='CI-REQUEST-003.json numerical primitives prepared; producer-v2/PreparePeak after agreement passes';p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
p=H/'status.json';d=json.loads(p.read_bytes());d.update(updated_at_utc=datetime.now(timezone.utc).isoformat(),state='ACTIVE_KEY_CORE_ACCEPTED_PREPARE_REPAIRED',verification='key4e1ed0b4 standalone elaboration+4axiomroots PASS; prepare14034d10 fourerrors; other sources NOT_RUN',milestone_2010='First run completed20:09:48; key4rootsPASS + fullpreparegoals collected byD and readlocally20:13',active_work='Next exact proof wave request ready; repair Id.run/let on actual prepare, continue endpoint/core interface');(H/'status.json').write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'receipt':receipt,'repairs':changes},ensure_ascii=False,indent=2))
