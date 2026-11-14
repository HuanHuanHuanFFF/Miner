from pathlib import Path
import json,hashlib,re
from datetime import datetime,timezone
H=Path('competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key')
old=Path('competitions/torchlean/candidates/r25-90m-20261029T064916Z/research/order-key/target-bridge/ContractWordBridge.lean.inc').read_text(encoding='utf-8')
short=old.split('def inputWords',1)[0]+'end Submission.R25ContractWordBridge\n'
(H/'follow-on/ContractWordCore.lean').write_text('import ContractExact\n'+short,encoding='utf-8',newline='\n')
c=H/'follow-on/CheckerConsequences.lean.inc';t=c.read_text(encoding='utf-8-sig').replace('  simp only [negative, Bool.decide_eq_false]\n  omega','  simp [negative]\n  omega');c.write_text(t,encoding='utf-8',newline='\n')
combined=(H/'ActualCheckerContractOnly.lean').read_text(encoding='utf-8')+'\n'+t
(H/'follow-on/CheckerConsequencesContractOnly.lean').write_text(combined,encoding='utf-8',newline='\n')
roots={
'KeyCoreContractOnly.lean':['Submission.R25OrderKey.orderKey_nat','Submission.R25OrderKey.orderKey_lt_cases','Submission.R25OrderKey.finite64_iff_exp','Submission.R25OrderKey.finite64_model'],
'RealStrictContractOnly.lean':['Submission.R25OrderKey.raw_value','Submission.R25OrderKey.magnitudeReal_strictMono','Submission.R25OrderKey.orderKey_lt_real','Submission.R25OrderKey.native_ofBits','Submission.R25OrderKey.orderKey_native_endpoints'],
'ActualCheckerContractOnly.lean':['Submission.R25Checker.accepted_components','Submission.R25Checker.midpoint_finite_nonzero','Submission.R25Checker.accepted_native_bounds'],
'follow-on/ContractWordCore.lean':['Submission.R25ContractWordBridge.native_dyadic_word','Submission.R25ContractWordBridge.native_ratScaled_word','Submission.R25ContractWordBridge.finishWord_of_native_result','Submission.R25ContractWordBridge.finishWord_of_native_real_result','Submission.R25ContractWordBridge.finishWord_exact_zero_native','Submission.R25ContractWordBridge.zero_sign_cannot_be_erased'],
'follow-on/CheckerConsequencesContractOnly.lean':['Submission.R26CheckerConsequences.midpoint_signs','Submission.R26CheckerConsequences.accepted_contains_exact','Submission.R26CheckerConsequences.accepted_exact_nonzero','Submission.R26CheckerConsequences.accepted_total_nonzero']}
entries=[]
for n,rs in roots.items():
 p=H/n;b=p.read_bytes();entries.append(dict(name=p.stem,path=p.as_posix(),sha256=hashlib.sha256(b).hexdigest(),bytes=len(b),helper_roots=rs,priority=('primary' if '/' not in n else 'follow-on-not-extra-queue')))
(H/'probe-plan.json').write_text(json.dumps(dict(updated_utc=datetime.now(timezone.utc).isoformat(),probes=entries,imports=['ContractExact'],allowed_axioms=['propext','Classical.choice','Quot.sound'],local_Lean=False,full_gate='NOT_APPLICABLE_PROOF_ONLY',verification='NOT_RUN'),indent=2)+'\n',encoding='utf-8')
p=H/'status.json';s=json.loads(p.read_text(encoding='utf-8-sig'));s.update(state='REPAIR_READY_AWAITING_DIRECT_COMPILE_WORKING_FOLLOW_ON',updated_utc=datetime.now(timezone.utc).isoformat(),first_repair_ready_utc='2026-10-29T09:03:17Z',source='probe-plan.json',accepted_inbox_events=[],waiting_for='D minimal direct compile retaining full goal stdout/stderr',active_ci='D owns; no own jobs',independent_progress='Derived exact-nonzero guard consequence source; thin Contract output bridge');p.write_text(json.dumps(s,indent=2)+'\n',encoding='utf-8')
print(json.dumps(entries,indent=2))
