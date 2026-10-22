"""Close the authorized window only after every started CI artifact is recovered."""
from pathlib import Path
from statistics import median
import datetime,hashlib,json,os,subprocess,sys
ROOT=Path.cwd();OWN=Path(__file__).resolve().parent;STATE=ROOT/'competitions/floatlib/coordination/development-status.json'
def save(p,v):
    t=p.with_name(p.name+'.update-tmp');t.write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode());os.replace(t,p)
def write(p,s):
    t=p.with_name(p.name+'.update-tmp');t.write_bytes(s.encode());os.replace(t,p)
old=json.loads(STATE.read_bytes());summary=json.loads((OWN/'summary.json').read_bytes());collab=old['collaboration'];choice=collab['provisional_selection'];name=choice['candidate']
assert all(j['collected'] for j in summary['jobs']) and all(j['status']=='completed' for j in collab['active_ci'])
xs=[r for r in summary['records'] if r['candidate']==name and r['full_gate'] and r['passed']]
assert len(xs)>=3 and any(r['seed']==choice['confirmation_seed'] for r in xs)
kernel=ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean';raw=kernel.read_bytes();digest=hashlib.sha256(raw).hexdigest();assert digest==choice['kernel_sha256'] and all(r['kernel_sha256']==digest and r['matches_current_official_fingerprint'] for r in xs)
now=datetime.datetime.now(datetime.timezone.utc);start=datetime.datetime.fromisoformat(collab['start_utc']);end=datetime.datetime.fromisoformat(collab['end_utc']);assert now>=end
save(OWN/'preclose-state.json',old);collab.update(state='COMPLETE_ALL_STARTED_CI_COLLECTED',confirmed_candidate=name,confirmation_run=next(r['run'] for r in xs if r['seed']==choice['confirmation_seed']),closed_at_utc=now.isoformat())
state=dict(state='R4_COMPLETE_FROZEN_FULL_PACKAGE_CONFIRMED_CHAMPION_NOT_ACHIEVED',updated_at_utc=now.isoformat(),owner='development chat',branch='codex/multi-track-floatlib',candidate='competitions/floatlib/candidates/'+name,kernel=kernel.relative_to(ROOT).as_posix(),kernel_sha256=digest,kernel_bytes=len(raw),manifest=kernel.with_name('manifest.json').relative_to(ROOT).as_posix(),official_commit=old['official_commit'],lean_toolchain='leanprover/lean4:v4.34.0',floatlib_commit='0d91825727839f597fd06b22fdd038ea21480f0c',baseline_sha256=old['baseline_sha256'],baseline_reference=old['baseline_reference'],proof_status='PASS_FULL_OFFICIAL_GATE_WITH_FROZEN_INDEPENDENT_CONFIRMATION',benchmark='VERIFIED_PUBLIC_FIXED_REFERENCE',formal_submission='NOT_SUBMITTED',acceptance_target=old['acceptance_target'],acceptance_target_status='UNACHIEVED',active_jobs=[],collaboration=collab,current_report=(OWN/'README.md').relative_to(ROOT).as_posix(),receipt_auditor=(OWN/'audit-window.py').relative_to(ROOT).as_posix(),performance=dict(full_gate_runs=[r['run'] for r in xs],seeds=[r['seed'] for r in xs],cpus=[r['cpu'] for r in xs],ratio_vs_shipped=[r['ratio_vs_shipped'] for r in xs],kernels_vs_shipped=[r['kernels_vs_shipped'] for r in xs],paired_gain_p05=[r['paired_gain_p05'] for r in xs]),history=dict(previous_round_state=(OWN/'previous-state.json').relative_to(ROOT).as_posix(),preclose_state=(OWN/'preclose-state.json').relative_to(ROOT).as_posix()),remaining=['Current-champion promotion not achieved','Prioritize remaining bmm gap; investigate measured preparation/output/hot-loop cost before further tile widening','Formal upload, registration and funds remain outside this window'])
save(STATE,state)
r=subprocess.run([sys.executable,str(OWN/'build-dashboard.py')],capture_output=True,text=True,encoding='utf-8');assert r.returncode==0,r.stderr
comparison=json.loads((OWN/'operation-comparisons.json').read_bytes());values=[r['whole_entry_inferred'] for r in comparison['records'] if r['candidate']==name]
state['current_champion_comparison']=dict(submission=comparison['champion_submission'],source_digest=comparison['champion_sha256'],policy_snapshot=comparison['policy_snapshot'],queried_at_utc=comparison['queried_at_utc'],candidate=name,candidate_over_champion_time_inferred=median(values),direct_paired_ratio='UNKNOWN',method=comparison['method'],evidence=(OWN/'operation-comparisons.json').relative_to(ROOT).as_posix())
state['payload_integrity']=dict(status='PASS_ALL_ORIGINAL_PAYLOADS',verified_payloads=summary['payload_files_verified'],evidence=(OWN/'summary.json').relative_to(ROOT).as_posix())
completion=dict(start_utc=start.isoformat(),deadline_utc=end.isoformat(),closed_at_utc=now.isoformat(),elapsed_minutes=(now-start).total_seconds()/60,ci_drain_minutes=max(0,(now-end).total_seconds()/60),all_started_ci_terminal_and_collected=True,jobs=len(summary['jobs']),payload_files_verified=summary['payload_files_verified'],selected_candidate=name,kernel_sha256=digest,full_gate_runs=[r['run'] for r in xs],independent_confirmation_run=collab['confirmation_run'],champion_submission=comparison['champion_submission'],championship_achieved=False,formal_submission='NOT_SUBMITTED')
save(OWN/'completion.json',completion)
for nm in ['f01-d4-final-native','f01-d4-final-lowmul']:
    p=ROOT/'competitions/floatlib/candidates'/nm/'manifest.json';m=json.loads(p.read_bytes());runs=[r['run'] for r in summary['records'] if r['candidate']==nm and r['full_gate']];m.update(proof_status=('PASS_FULL_GATE_FROZEN_INDEPENDENT_CONFIRMATION' if nm==name else 'PASS_FULL_GATE_COMPARISON'),full_gate_runs=runs);save(p,m)
cpus='、'.join(dict.fromkeys(r['cpu'] for r in xs));ratio=min(r['ratio_vs_shipped'] for r in xs),max(r['ratio_vs_shipped'] for r in xs)
text=f'''# R4 两小时协作结果

窗口：北京时间2026-10-22 15:52:04—17:52:04。已推进完整两小时；已启动CI自然收齐后结束，额外回收{completion['ci_drain_minutes']:.1f}分钟。

最终完整包：[Kernel.lean](../../{name}/Kernel.lean)，SHA-256 `{digest}`。同一源码完整验收通过{len(xs)}次，含选择后的新runner独立确认；四项规格、内核重放、3公理、12类25轮及checksum均通过。

采用内联数值解码加法、机器字有序求和、十列矩阵及等价坐标内联；极小数乘法走已证明的软件舍入，避免Intel原生下溢开销。固定公开参照比值范围{ratio[0]:.6f}—{ratio[1]:.6f}；机器：{cpus}。

| 方向 | 结果与决定 |
|---|---|
| 加法／求和 | 同批组件实验约快20%／18%，组合后完整确认 |
| 十列矩阵／坐标内联 | 十列两次约快4%；同批坐标内联再快约12%，采用组合 |
| 两行四列／两行八列 | 完整正确性均通过；同批约慢9%／0.6%，保留负例 |
| 极小数软件乘法 | AMD有小幅成本；Intel完整包比原生版本快约28%，采用并独立确认 |
| 显式双步展开 | 同批矩阵慢约4%，停放；诊断对象确认原版已自动展开及SIMD |

现任冠军#{comparison['champion_submission']}；当前仍不能取代冠军。四项首选见[看板](../../../../../dashboard.md)。

全部{completion['jobs']}批CI已结束并收齐，{completion['payload_files_verified']}份原始产物完成哈希核对；未取消。原始失败和慢样本保留。[完整验收汇总](summary.json)、[同批比较](same-batch-comparisons.json)、[冠军比较](operation-comparisons.json)、[完成回执](completion.json)、[研究交接](../../../research/astra-collab-20261022-r4/checkpoint-04-final.md)、[网页原件核对](web-recovery-audit.json)。没有正式上传或资金操作。
'''
write(OWN/'README.md',text)
experience=ROOT/'competitions/floatlib/docs/first-candidate.md';s=experience.read_text();s+='''\n\n## R4：2026-10-22 两小时协作\n\n最终完整包和全部原始证据见[本轮报告](../candidates/f01-d4-global8/window2h-20261022/README.md)。当前状态以development-status.json为准。两行微块均完成全输入证明和真实gate，但没有完整调用收益；实际SIMD或字段复用不等于提速。十列与坐标内联减少了尾列和输出临时对象，已纳入最终整合确认。Intel极小数开销使最终乘法选择改变，冻结同源后重新独立确认。生成脚本必须锚定明确命名空间，组合求和时同步处理Packed8Index/Packed10Index证明引用；原错误源码与回执保留。\n''';write(experience,s)
save(STATE,state)
print(json.dumps(completion,ensure_ascii=False))
