from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent
R25=Path('competitions/torchlean/candidates/r25-90m-20261029T064916Z/research/widen/finite-bridge')
R26=Path('competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/finite-producer')
s=(R25/'FiniteWidenCarrier.lean').read_text(encoding='utf-8-sig')
changes=[]
def replace(old,new,label):
 global s
 assert s.count(old)==1,(label,s.count(old));s=s.replace(old,new);changes.append(label)
replace('    simp only [widenBits, he, ite_false, expWide, expWord, fracWord]','    simp only [widenBits, beq_iff_eq, he, ite_false, expWide, expWord, fracWord, he\', ite_false]','normal actual guard BEq->Prop before expanding expWord')
replace('  simpa only [one_mul] using Nat.mod_eq_of_lt hp','  simpa only [one_mul, show (2 ^ 64 : Nat) = 18446744073709551616 by decide] using\n    Nat.mod_eq_of_lt hp','normalize 2^64 modulus in one_shift_nat')
replace('  simpa only [lead_nat] using UInt64.toNat_sub_of_le (52 : UInt64) (lead u) hle','  have hh := UInt64.toNat_sub_of_le (52 : UInt64) (lead u) hle\n  change ((52 : UInt64) - lead u).toNat = 52 - (lead u).toNat at hh\n  simpa only [lead_nat] using hh','normalize literal UInt64.toNat in count_nat')
replace('    simp [Submission.R24PortableF64.widenBits, he, frac, lead, hf0]','    simp only [Submission.R24PortableF64.widenBits, he, beq_self_eq_true,\n      ite_true, hf0, Bool.false_eq_true, ite_false, frac, lead]','narrow hbody simplifier preserves cast UInt32 fraction')
replace('  simpa only [hm, hexp] using hd','  change Model.toDyadic? (Model.ofFields F64 (decide (2147483648 ≤ u.toNat))\n    (ell u + 874) (remWide u)) =\n    some ⟨decide (2147483648 ≤ u.toNat), 4503599627370496 + remWide u,\n      ((ell u + 874 : Nat) : Int) - 1023 - 52⟩ at hd\n  simpa only [hm, hexp] using hd','concrete binary64 field type before rewrite in subnormal_decode')
replace('    rw [hexp, shift_value, Model.Dyadic.toReal_eq_signedSignificand]','    change (FloatLib.Numerics.Dyadic.mk (decide (2147483648 ≤ u.toNat))\n      (n u * 2 ^ (52 - ell u)) ((ell u : Int) - 201)).toReal = _\n    rw [hexp, shift_value, Model.Dyadic.toReal_eq_signedSignificand]','reduce Option match before Dyadic shift theorem')
replace('  by_cases hsign : 2147483648 ≤ u.toNat <;>\n    simp [wordSign, hsign, n_eq_wordFrac]','  rw [n_eq_wordFrac]\n  have hexp : FloatFormat.binary32.minSubnormalExponent = (-149 : Int) := rfl\n  rw [hexp]\n  by_cases hsign : 2147483648 ≤ u.toNat <;>\n    simp [wordSign, hsign]','rewrite n_eq_wordFrac before simp unfolds n; expose pinned min-subnormal exponent')
(H/'producer-v1').mkdir(exist_ok=True)
p=H/'producer-v1/FiniteWidenContractOnly.lean';p.write_text(s,encoding='utf-8',newline='\n')
for name,rel in [('PrepareCoreContractOnly','prepare-v1/PrepareCoreContractOnly.lean'),('PrepareAgreementContractOnly','prepare-v1/PrepareAgreementContractOnly.lean'),('PreparePeakContractOnly','prepare-v1/PreparePeakContractOnly.lean'),('TailContractOnly','tail-v1/TailContractOnly.lean')]:
 (H/'producer-v1'/(name+'.lean')).write_bytes((R26/rel).read_bytes())
roots={
'FiniteWidenContractOnly':['Submission.R25ActualWiden.actual_widenBits_eq','Submission.R24SubnormalWiden.subnormal_finite_value','Submission.R25FiniteWiden.finite_actual_value'],
'PrepareCoreContractOnly':['Submission.R25PrepareAgreement.prepare_eq_forIn','Submission.R25PrepareAgreement.prepare_eq_fold'],
'PrepareAgreementContractOnly':['Submission.R25PrepareAgreement.prepare_valid_rawfinite','Submission.R25PrepareAgreement.prepare_getter_interface'],
'PreparePeakContractOnly':['Submission.R26PreparePeak.prepare_peak_bound','Submission.R26PreparePeak.prepare_index_bound','Submission.R26PreparePeak.prepare_full_interface'],
'TailContractOnly':['Submission.R26TailAgreement.sumRemaining_eq_loop','Submission.R26TailAgreement.sumRemaining_zero_eq_sum']}
rows=[]
for n,rs in roots.items():
 p=H/'producer-v1'/(n+'.lean');b=p.read_bytes()
 rows.append(dict(name=n,path=p.as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),helper_roots=rs,stage=1 if n in ['FiniteWidenContractOnly','PrepareCoreContractOnly','TailContractOnly'] else 2,depends_on=['PrepareCoreContractOnly'] if n=='PrepareAgreementContractOnly' else ['PrepareAgreementContractOnly'] if n=='PreparePeakContractOnly' else []))
request=dict(request_id='R27-FP-002',updated_at_utc=datetime.now(timezone.utc).isoformat(),state='READY_AFTER_FP001_THROUGHPUT',owner='fp-proof',executor='Droot',purpose='Actual producer structural agreement and finite widening repairs; statement/axiom only, not gate/performance',candidates=rows,priority='Run stage1 after FP001; stage2 only once actual prepare core passes. FiniteWiden imports only ContractExact and is standalone reduced support, 37KB class not old105KB producer.',changes=changes,proof='NOT_RUN',formal_submission=False,measurement=False,allow_private=False,local_Lean=False,command='Same raw statement/helper audit commands as FP001, exact byte/hash checked, full logs preserved',resources={'compile_seconds_per_source':180,'memory_mib':4096})
(H/'CI-REQUEST-002.json').write_text(json.dumps(request,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
(H/'producer-v1/repair-map.json').write_text(json.dumps(dict(source=(R25/'FiniteWidenCarrier.lean').as_posix(),source_sha256=hashlib.sha256((R25/'FiniteWidenCarrier.lean').read_bytes()).hexdigest(),full_old_CI_source_sha256='e5613ee190d4185d665b0cd52482e37dc0770ac468c19ee676cac7a6ba964ab6',changes=changes,verification='NOT_RUN_LEAN',sources=rows),ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
with (H/'HANDOFF.md').open('a',encoding='utf-8') as f:
 f.write('\n第二请求 `CI-REQUEST-002.json` 准备完毕，按吞吐排在FP001之后：FiniteWiden独立reduced support修7类已见报错（两个sign分支共8error），prepare core与Tail独立；扩展getter/peak须先core通过。没有拼105KB闭包。\n')
print(json.dumps({'changes':changes,'sources':rows},ensure_ascii=False,indent=2))
