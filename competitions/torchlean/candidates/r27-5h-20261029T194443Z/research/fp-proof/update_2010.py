from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent
(H/'request-history').mkdir(exist_ok=True)
p=H/'CI-REQUEST.json';(H/'request-history/R27-FP-001.json').write_bytes(p.read_bytes())
(H/'HANDOFF-20261029T2010-history.md').write_bytes((H/'HANDOFF.md').read_bytes())
r=json.loads((H/'boundary-v1/nonzero-receipt.json').read_bytes())
p2=json.loads((H/'CI-REQUEST-002.json').read_bytes())
entries=[dict(name='GuardedNonzeroContractOnly',path=r['path'],bytes=r['bytes'],sha256=r['sha256'],helper_roots=r['helper_roots'],depends_on=['batch1 old_key_core accepted'])]
for name in ['FiniteWidenContractOnly','PrepareAgreementContractOnly','TailContractOnly']:
 entries.append(next(x for x in p2['candidates'] if x['name']==name))
req=dict(request_id='R27-FP-004',updated_at_utc=datetime.now(timezone.utc).isoformat(),state='NEXT_WAVE_WAITING_BATCH1_CORE_FEEDBACK',owner='fp-proof',executor='Droot',purpose='Next exact small helper diagnostic wave. Prioritize guarded actual checker36.6KB once core passes, finite-widen38.5KB and prepare agreement8.1KB once rawfeedback supports. Do not cancel or modify batch1.',candidates=entries,independent_optional='CI-REQUEST-003.json numerical primitives remain prepared not queued; stage2 PreparePeak inCI-REQUEST-002',completed_requests='First source request delivered19:49, core/prepcore selected unchanged inD run40945451009; initial request archived request-history/R27-FP-001.json',new_result='Actual checker finite guards imply native endpoint RNE equations; derive exact total nonzero from accepted strict normalcell. No producer endpoint-real or outward premise remains in final new helper root.',allowed_axioms=['propext','Classical.choice','Quot.sound'],official_commit='accb82b6e2adeda1b41a57a260d68fb3879c427e',toolchain='leanprover/lean4:v4.34.0',resources={'compile_seconds_per_source':180,'memory_mib':4096,'local_Lean':False},allow_private=False,measurement=False,formal_submission=False,proof='NOT_RUN',command='Standalone import ContractExact: preserve complete stdout/goals; exact helper axioms append to same source; no all12/gate claim.')
(H/'CI-REQUEST.json').write_text(json.dumps(req,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
(H/'HANDOFF.md').write_text('''# R27 FP proof 当前交接

20:10 UTC；实际开始19:47:45，共同截止00:44:43不延；ACTIVE，严格文件，仅本目录写。无本机Lean/native、Git、CI、nested agent。

- 首组19:49交付；D首批40945451009 /2da31f12已选key-core4e1ed0b4与prepare-core14034d10，均与本次源同字节；完整反馈尚未落本地，不能称Lean接受。
- **新实质归约**：实际certify检查sum与两端finite，所以可直接推出native±的RNE等式；`boundary-v1/GuardedNonzeroContractOnly.lean`36599B/dfa924ad含真实checker→严格cell→精确total非零，producer只剩实际radius finite＋forward error。根/完整SHA在`CI-REQUEST.json`，仍NOT_RUN。
- 下一波同runner优先：guarded boundary36.6KB→finite widening38.5KB（按旧完整goal修7类8error）→prepare getter8.1KB；Tail1.6KB独立。数值SUM3/Radius/NativeMul和官方total/finish已拆小，`CI-REQUEST-003.json`仅prepared，不堆105KB未验闭包。
- `CELL-AUDIT.md`核signed-zero唯一key例外、minnormal/power/maxfinite单元；`INTEGRATION-BOUNDARY.md`核实际cache构造来源、bias同一次舍入及独立fallback证明。最大finite的上半cell不能用abs≤maxFinite快捷条件代替。
- 已处理父19:51与20:05inbox；退任12/27无native64/roundAt桥（hash/全源扫描见`retired-source-fp-survey.json`）。整源只读未复制。新旧config_hash不同，现任冠军倍数UNKNOWN。

静态原intake/policy通过；Lean/replay/AX/完整all12/性能均未获本轮接受。token/cache/CPU UNKNOWN；完整历史见`HANDOFF-20261029T2010-history.md`。下一步收到原goal定点修复，冻结时只转独立后续材料。
''',encoding='utf-8')
s=json.loads((H/'status.json').read_bytes());s.update(updated_at_utc=datetime.now(timezone.utc).isoformat(),active_work='Guard-derived endpoint/strict-cell/nonzero helper prepared; pending exact firstCI feedback before integration or repairs',request_id='R27-FP-004',milestone_2010='Small source delivered19:49 andrun20:02; raw feedback locallyNOT_YET_AVAILABLE',processed_inbox=['父R 19:51方向更新','父R 20:05比较边界更新']);(H/'status.json').write_text(json.dumps(s,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print('Current handoff and next-wave request updated; source snapshots unchanged')
