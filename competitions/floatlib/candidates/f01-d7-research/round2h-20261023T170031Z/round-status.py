"""Refresh the single round entry from exact source-bound local result receipts."""
from pathlib import Path
import datetime, hashlib, json, subprocess

out=Path(__file__).resolve().parent
root=out.parents[4]
state=json.loads((root/'competitions/floatlib/coordination/development-status.json').read_bytes())
plan=json.loads((out/'round-plan.json').read_bytes())
now=datetime.datetime.now(datetime.timezone.utc)
start=datetime.datetime.fromisoformat(plan['start_utc'])
rows=[]
for entry in state['research_round']['experiments']:
    path=out/f'result-{entry["seed"]}-{entry["candidate"]}.json'
    row=dict(entry)
    if path.exists():
        result=json.loads(path.read_bytes())
        source_sha=entry.get('sha256')
        if source_sha is None:
            relative=f'competitions/floatlib/candidates/{entry["candidate"]}/Kernel.lean'
            source_sha=hashlib.sha256(subprocess.check_output(['git','cat-file','blob',entry['source_commit']+':'+relative],cwd=root)).hexdigest()
        assert result['run']==entry['run'] and result['seed']==entry['seed'] and result['sha256']==source_sha
        row['sha256']=source_sha
        row.update(result_receipt=path.name,result_receipt_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
                   full_gate_both=result.get('full_gate_both',False),
                   whole_ratio=result.get('relative_normalized_ratio','UNKNOWN'),
                   bmm_ratio=result.get('per_operation_normalized',{}).get('bmm','UNKNOWN'),
                   gain_p05=result.get('gain_p05','UNKNOWN'),
                   discovery_screen_passed=result.get('local_discovery_screen_passed',False),
                   failure=result.get('reason'))
    rows.append(row)
result={'as_of_utc':now.isoformat(),'start_utc':plan['start_utc'],'deadline_utc':plan['deadline_utc'],
        'elapsed_wall_seconds':(now-start).total_seconds(),'round_state':state['research_round']['state'],
        'completed_ci':state['research_round'].get('completed_ci',[]),'active_ci':state['research_round']['active_ci'],
        'experiments':rows,'champion_goal':'UNACHIEVED_UNTIL_ACTUAL_CHAMPION_ACCEPTANCE',
        'source_rule':'Every row binds run,seed,Kernel SHA and the complete result receipt; same run with multiple candidates is one input group.',
        'selection_policy':plan['selection_policy'],'final_three_group_requirement':plan['additional_inputs'],
        'dashboard':'../../../../../dashboard.md'}
(out/'round-results.json').write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode())
def change(value):
    if not isinstance(value,(int,float)):return '待结果'
    return ('快' if value<1 else '慢')+f'{abs(1-value)*100:.2f}%'
lines=['# R10两小时矩阵探索','',
       '北京时间2026-10-24 01:00:31—03:00:31。目标仍是新冠军；根看板统一使用现任冠军乘数。',
       '',f'截至 {now.isoformat()}，已完成 {len(result["completed_ci"])} 个CI，运行中 {len(result["active_ci"])} 个。',
       '', '| 候选 | 矩阵变化 | 整体变化 | 验收状态 |', '|---|---:|---:|---|']
for row in rows:
    status='待完整结果'
    if row.get('full_gate_both'):
        status='完整gate通过；发现门槛通过' if row['discovery_screen_passed'] else '完整gate通过；未达采纳门槛'
    elif row.get('failure'):status='statement失败，无性能结论'
    lines.append(f'| {row["candidate"]} | {change(row.get("bmm_ratio"))} | {change(row.get("whole_ratio"))} | {status} |')
lines += ['', '变化量是相对本轮已保留41的同组参照归一化完整入口成本；冠军差距只见根看板。',
          '', '同一候选的最终确认要求冻结源码、两个未参与选择的新输入组，与发现组共同逐组通过。负面结果与慢组全部保留；一轮三份候选的853只计一个输入组。',
          '', '[精确结果索引](round-results.json) · [事前计划](round-plan.json) · [三组验收规则](three-group-design.md) · [固定冠军基准](anchor-design.md) · [阶段诊断](profile-integration.md)',
          '', '正式参赛提交未授权、未执行；公开Git推送只用于开发与标准runner验证。']
(out/'README.md').write_bytes(('\n'.join(lines)+'\n').encode())
print(json.dumps({'completed_ci':len(result['completed_ci']),'active_ci':result['active_ci'],'experiments':len(rows),'elapsed_wall_seconds':result['elapsed_wall_seconds']}))
