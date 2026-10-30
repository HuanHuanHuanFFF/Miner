from pathlib import Path
import json,hashlib,ast,re
from datetime import datetime,timezone
H=Path('competitions/torchlean/candidates/r27-5h-20261029T194443Z/research/fp-proof')
OLD=Path('competitions/torchlean/candidates/r26-1h-20261029T085515Z/research/key')
now=datetime.now(timezone.utc).isoformat()
(H/'sources-v1').mkdir(exist_ok=True)
for n in ['KeyCoreContractOnly','RealStrictContractOnly','ActualCheckerContractOnly']:
 s=(OLD/(n+'.lean')).read_text(encoding='utf-8-sig')
 if n!='KeyCoreContractOnly':
  s=s.replace('FloatLib.Numerics.Radix.toReal, sub_sub, neg_mul]\n','FloatLib.Numerics.Radix.toReal, sub_sub, neg_mul] <;> ring\n')
 (H/'sources-v1'/(n+'.lean')).write_text(s,encoding='utf-8',newline='\n')
strict=Path('competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/research/controller/StrictEnclosure-v2.lean.inc')
(H/'sources-v1/StrictEnclosureContractOnly.lean').write_text('import ContractExact\n\n'+strict.read_text(encoding='utf-8-sig'),encoding='utf-8',newline='\n')
roots={
'KeyCoreContractOnly':['Submission.R25OrderKey.orderKey_nat','Submission.R25OrderKey.orderKey_lt_cases','Submission.R25OrderKey.finite64_iff_exp','Submission.R25OrderKey.finite64_model'],
'RealStrictContractOnly':['Submission.R25OrderKey.raw_value','Submission.R25OrderKey.magnitudeReal_strictMono','Submission.R25OrderKey.orderKey_lt_real','Submission.R25OrderKey.native_ofBits','Submission.R25OrderKey.orderKey_native_endpoints'],
'ActualCheckerContractOnly':['Submission.R25Checker.accepted_components','Submission.R25Checker.midpoint_finite_nonzero','Submission.R25Checker.accepted_native_bounds'],
'StrictEnclosureContractOnly':['Submission.R24StrictEnclosure.strict_lower_pullback','Submission.R24StrictEnclosure.strict_upper_pullback','Submission.R24StrictEnclosure.strict_enclosure_of_rounded_bounds']}
rows=[]
for n,rs in roots.items():
 p=H/'sources-v1'/(n+'.lean');b=p.read_bytes()
 rows.append(dict(name=n,path=p.as_posix(),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),helper_roots=rs,depends_on=[] if n in ['KeyCoreContractOnly','StrictEnclosureContractOnly'] else ['KeyCoreContractOnly'] if n=='RealStrictContractOnly' else ['RealStrictContractOnly'],imports=['ContractExact']))
request=dict(request_id='R27-FP-001',updated_at_utc=now,owner='fp-proof',executor='Droot',state='READY_FOR_PUBLIC_CI',priority='compile core first; Real then checker if preceding source passes; StrictEnclosure is independent',purpose='Small raw-statement proof diagnostics plus exact helper axiom audit. Not candidate full gate or measurement.',official_commit='accb82b6e2adeda1b41a57a260d68fb3879c427e',toolchain='leanprover/lean4:v4.34.0',candidates=rows,command='Copy each exact source to lean/work/Submission.lean, lake build Submission with full untruncated diagnostics, then lake env lean audit file appending #print axioms for all named roots; preserve original contract/gate/bench.',allowed_axioms=['propext','Classical.choice','Quot.sound'],allow_private=False,measurement=False,formal_submission=False,resources={'compile_seconds_per_source':180,'memory_mib':4096,'local_Lean':False},full_gate='NOT_REQUESTED_HELPER_ONLY',request_full_logs=True,negative_evidence='R26 run40852769757 full order-key-policy1 and finite-widen logs read. v1 recovers explicit UInt64.toNat bridge/Nat-mod casts/Bool cases, adds ring to residual signed normal decoding.',completion='All named roots compile and axiom audit exact-source; failure preserve full goal/source hash. D reports to research/inbox/fp-proof.md or request/evidence.')
(H/'CI-REQUEST.json').write_text(json.dumps(request,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
status=dict(role='R27 fp-proof',state='ACTIVE_SMALL_PROOF_REQUEST_READY',first_clock_utc='2026-10-29T19:47:45Z',updated_at_utc=now,common_start_utc='2026-10-29T19:44:43Z',deadline_utc='2026-10-30T00:44:43Z',branch='huan/codex-gpt',base_head='84253fee9f251d955e0d426e46851acd6f9d5650',write_scope=H.as_posix(),request='CI-REQUEST.json',active_work='Exact raw field/order and RNE midpoint fixed point; next derive actual endpoint producer semantics independently of compile.',verification='NOT_RUN_LEAN; policy pending',actual_tokens='UNKNOWN',cached_input_tokens='UNKNOWN',continuous_model_CPU='UNKNOWN',actual_CI_occupancy='Droot owned UNKNOWN',no_direct_messages=True,no_local_build=True,no_nested_agents=True,original_user_requirement='Any current TorchLean board champion, only per-board current champions comparisons; first executable feedback target20:10UTC;22:15proof milestone;23:20freeze;00:00stopnewlong;00:44:43stopnewresearch')
(H/'status.json').write_text(json.dumps(status,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
(H/'HANDOFF.md').write_text('# R27 FP proof 当前交接\n\n实际开始19:47:45 UTC，共同截止00:44:43 UTC；ACTIVE。仅本目录写，严格文件协作，无本机Lean/native、Git、CI。\n\nR26完整原goal已读；最小源码与精确hash/根见 `CI-REQUEST.json`，请求R27-FP-001：core→Real→实际checker，独立StrictEnclosure可同runner编译。保留R26修复，补有符号normal实数展开末尾ring；本轮尚未Lean接受。\n\n现在继续检查实际producer的RNE endpoint语义及forward error接口；绝不把误差界+RNE端点当作向外舍入。核心已具备不额外假定midpoint固定点的回推小源。请求D保留完整goals并落回执到inbox；接受根不等于新Kernel/all12通过。当前冠军性能 UNKNOWN。\n\n资源token/cache/CPU与CI占用UNKNOWN；源草稿、静态policy、Lean、全gate、正式冠军分别验收。\n',encoding='utf-8')
print(json.dumps({'request':request['request_id'],'files':rows},indent=2))
