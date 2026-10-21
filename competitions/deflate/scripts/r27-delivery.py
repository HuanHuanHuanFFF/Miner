"""Role-separated R27 delivery from audited original paired observations."""
from pathlib import Path
import argparse, datetime, hashlib, itertools, json, statistics as st, zipfile
ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round27'
LABELS={'r27-a-prefix-probe':'A1','r27-a-inline-chain':'A2','r27-b-prefix708':'B1','r27-b-priced-lazy':'B2','r27-b-extend-lazy':'B3','r27-b-extend-producer':'B4','r27-c-short673':'C1','r27-c-inline673':'C2'}
def read(p):return json.loads(p.read_bytes())
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def save(p,v):p.write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
def stats(obs):
    if not obs:return None
    vals=[o['single_pool_share_pct']for o in obs]
    return {'n_main_blocks':len(obs),'runner_count':len({o['run_id']for o in obs}),'min_share_pct':min(vals),'median_share_pct':st.median(vals),'best_share_pct':max(vals),'zero_count':sum(v==0 for v in vals),'at_least_5_count':sum(v>=5 for v in vals),'X_range':[min(o['projected_time']for o in obs),max(o['projected_time']for o in obs)],'Y_pct':obs[0]['projected_size_pct'],'public_X_range':[min(o['public_time']for o in obs),max(o['public_time']for o in obs)],'public_Y_pct':obs[0]['public_size_pct'],'observations':obs}
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--analysis',type=Path,required=True);ap.add_argument('--capture',type=Path,required=True);args=ap.parse_args()
    args.analysis=args.analysis.resolve();args.capture=args.capture.resolve()
    assert args.analysis.is_relative_to(E) and args.capture.is_relative_to(E)
    analysis=read(args.analysis);capture=read(args.capture/'receipt.json');assert capture['weights_same_snapshot']
    rows=[]
    for g in analysis['candidates']:
        name=g['candidate'];path=ROOT/'candidates'/name;cert=read(path/'VERIFICATION.json')if(path/'VERIFICATION.json').exists()else None
        records={}
        for role in ['discovery','measurement_diagnosis','independent_confirmation']:
            records[role]={cal:stats([o for o in g['observations']if o['role']==role and o['entry_role']=='candidate' and o['calibration']==cal])for cal in ['primary','shadow']}
        selected=next(role for role in ['independent_confirmation','measurement_diagnosis','discovery']if records[role]['primary'])
        copies=[o for o in g['observations']if o['entry_name'].endswith('-shadow')]
        rows.append({'name':name,'label':LABELS[name],'files':{n:sha(path/n)for n in ['parse.rs','Parse.lean']},'gate':cert or 'NOT_RUN','selected_reporting_role':selected,'by_role':records,'copy_observations_separate':copies,'public_and_calibrated_separate':True,'formal_payable_share':'UNKNOWN_NO_FORMAL_SUBMISSION'})
    rows.sort(key=lambda r:r['label'])
    cis=[]
    for dp in E.glob('dispatch-*.json'):
        dispatch=read(dp);run=str(dispatch['run']['databaseId']);paths=list((E/run).rglob('ci-run.json'))if(E/run).exists()else[]
        if paths:
            ci=read(paths[0]);seconds=sum((datetime.datetime.fromisoformat(j['completedAt'])-datetime.datetime.fromisoformat(j['startedAt'])).total_seconds()for j in ci['jobs']if j.get('completedAt')and j.get('startedAt'))
            cis.append({'run_id':run,'batch':dispatch['batch'],'conclusion':ci['conclusion'],'job_seconds':seconds,'metadata':paths[0].relative_to(ROOT).as_posix()})
        else:
            assert run=='38366557238'
            cis.append({'run_id':run,'batch':dispatch['batch'],'conclusion':'skipped','job_seconds':0,'scope':'No executed experiment/artifact; original metadata in route-first-skipped.'})
    # Joint coordinates are observed but from different jobs; do not call paired.
    import round10_payability as p
    p.SCORER_PATH=E/'official-rules-close/validator--scoring--pareto.py'
    comp,ctx,flat=p.load_flat_rows(args.capture);sc=p.load_official_scorer();front=[sc.Point(r['id'],r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])for r in flat if(r.get('score')or{}).get('on_frontier')];bounds=sc.Boundaries(comp['policy']['max_balanced_time_ratio'],comp['policy']['max_mean_file_compression_pct'])
    b1=next(r for r in rows if r['label']=='B1')['by_role']['independent_confirmation']['primary']['observations'];c2=next(r for r in rows if r['label']=='C2')['by_role']['measurement_diagnosis']['primary']['observations'];joint=[]
    for a,b in itertools.product(b1,c2):
        pts=[sc.Point('hypo-b1',a['projected_time'],a['projected_size_pct']),sc.Point('hypo-c2',b['projected_time'],b['projected_size_pct'])];f=sc.pareto_front(front+pts);w=sc.local_global_improvement_space_log_weights(f,bounds)
        joint.append({'B1_run':a['run_id'],'B1_block':a['block'],'C2_diagnostic_run':b['run_id'],'C2_block':b['block'],'B1_pct':100*w.get('hypo-b1',0),'C2_pct':100*w.get('hypo-c2',0),'total_pct':100*(w.get('hypo-b1',0)+w.get('hypo-c2',0))})
    packages=[]
    folder=E/'review-packages';folder.mkdir(exist_ok=True)
    for r in rows:
        if not isinstance(r['gate'],dict):continue
        dest=folder/(r['label']+'-source-proof.zip');source=ROOT/'candidates'/r['name']
        if not dest.exists():
            with zipfile.ZipFile(dest,'w',zipfile.ZIP_DEFLATED)as z:
                for n in ['parse.rs','Parse.lean']:z.write(source/n,n)
        with zipfile.ZipFile(dest)as z:
            assert set(z.namelist())=={'parse.rs','Parse.lean'}
            assert all(hashlib.sha256(z.read(n)).hexdigest()==h for n,h in r['files'].items())
        packages.append({'label':r['label'],'path':dest.relative_to(ROOT).as_posix(),'sha256':sha(dest),'files':r['files'],'scope':'Review package only, no formal upload; performance target unmet.'})
    save(folder/'manifest.json',packages)
    result={'status':'BUDGET_WINDOW_DELIVERY_OBJECTIVE_NOT_ACHIEVED','budget':read(E/'budget.json'),'snapshot_id':capture['snapshot_id'],'snapshot_context':capture['competition_context'],'capture':args.capture.relative_to(ROOT).as_posix(),'analysis':args.analysis.relative_to(ROOT).as_posix(),'candidates':rows,'ci':cis,'resource_job_seconds':sum(r['job_seconds']for r in cis),'paired_processes':analysis['paired_processes'],'joint_B1_C2':{'status':'INFERRED_UNPAIRED_OBSERVED_COORDINATE_CARTESIAN_REPLAY','assumptions':'Same latest snapshot; independently eligible identities; admission/private-set performance unknown. C2 data are diagnostic, not final confirmation; combinations are not samples or success probabilities.','rows':joint},'review_packages':packages,'UNKNOWN':['Formal admission/payable rank and private performance of new candidates','Wallet receipts, model token usage and attributable monetary invoice','Historical high-share/duration of new669/673/683 sources: requested historical snapshots unavailable']}
    save(E/'delivery.json',result)
    lines=['# 第27轮：90分钟新公开源码优化','', '执行规则见 [AGENTS.md](../../AGENTS.md)。','', '**未达到稳定5%目标。** 北京时间2026-10-13 15:50:55—17:20:55。全部实验、准备、排队、修复、证明、确认、收集及报告计入90分钟；本轮没有正式上传、注册、签名、重置卡或购买额度。', '',f'份额按官方快照 **{capture["snapshot_id"]}** 条件重放；该捕获的competition/Pareto/leaderboard/weights同快照，freshness={capture["competition_context"]["freshness"]}。评分源码最终重新查询，主提交6bf303f14e6c7bccc63e9a557e4ac83e032fa9e8；原版运行仍固定a356bbff18b60c4527fbcc85d5a28ef9c20214e0。公共与正式combined坐标分列，校准只作同族推断，未上传版本的正式可支付份额UNKNOWN。','', '## 最新快照：主候选逐块份额分布与对应两轴','', '表中优先展示冻结后独立确认；缺少时展示诊断，再展示发现。最低/中位/最高均来自逐块评分，不把中位X的评分当期望，也不将副本或样本达标比例当成功概率。每块实际评分X/Y、参照和run见[完整分层数据](../../evidence/round27/delivery.json)。','', '| 候选 | 数据角色/主块数 | 池份额最低/中位/最高% | X范围 | Y% | 零/达5%次数 | 完整公共gate |','|---|---|---|---|---:|---|---|']
    for r in rows:
        s=r['by_role'][r['selected_reporting_role']]['primary'];gate='PASS'if isinstance(r['gate'],dict)else'NOT_RUN'
        lines.append(f'| {r["label"]} [{r["name"]}](../../candidates/{r["name"]}) | {r["selected_reporting_role"]}/{s["n_main_blocks"]} | {s["min_share_pct"]:.6f}/{s["median_share_pct"]:.6f}/{s["best_share_pct"]:.6f} | {s["X_range"][0]:.9f}–{s["X_range"][1]:.9f} | {s["Y_pct"]:.9f} | {s["zero_count"]}/{s["at_least_5_count"]} | {gate} |')
    lines+=['','## 公共实测（未校准）','', '| 候选 | 同上角色公共X范围 | 公共Y% |','|---|---|---:|']
    for r in rows:
        s=r['by_role'][r['selected_reporting_role']]['primary'];lines.append(f'| {r["label"]} | {s["public_X_range"][0]:.9f}–{s["public_X_range"][1]:.9f} | {s["public_Y_pct"]:.9f} |')
    b=next(r for r in rows if r['label']=='B1');shadow=b['by_role']['independent_confirmation']['shadow']
    lines+=['','## 独立确认、对照与验收','',f'B1精确冻结后两台新runner各两块原协议确认，主参照最低0%、中位{b["by_role"]["independent_confirmation"]["primary"]["median_share_pct"]:.6f}%、最高{b["by_role"]["independent_confirmation"]["primary"]["best_share_pct"]:.6f}%，零{b["by_role"]["independent_confirmation"]["primary"]["zero_count"]}/4；同源码参照最低0%、中位{shadow["median_share_pct"]:.6f}%、最高{shadow["best_share_pct"]:.6f}%，零{shadow["zero_count"]}/4。两种参照均达5%次数0/4。其余同源码候选副本另列在完整数据，不合并为独立样本。','', 'C2单块主发现约1.18%曾是较高线索，切换同源码参照即0；另一个runner两块原协议反向外层顺序诊断主/复制参照均0，未建立稳定收益。C2有完整gate，但没有专门最终确认，不把诊断伪称最终确认。B1和C2的完整新gate分别153.9秒和516.5秒，独立性能状态另验。其余六份版本未安排完整gate。','', '精确源码与证明：','']
    for r in rows:
        if isinstance(r['gate'],dict):lines.extend([f'- {r["label"]} Rust `{r["files"]["parse.rs"]}`；Lean `{r["files"]["Parse.lean"]}`；run {r["gate"]["run_id"]}，原提取/原义务/白名单/roundtrip及原始树检查全部通过。'])
    totals=[j['total_pct']for j in joint];lines+=['','## 单独与联合加入','',f'B1单独条件估算见四块独立结果；C2单独使用两块诊断估算均0。以这些真实坐标组合同时加入后，共{len(joint)}个非配对笛卡尔组合，总份额观测坐标重放范围{min(totals):.6f}%–{max(totals):.6f}%；它们不是联合确认样本或成功概率，不直接相加单独估算。身份、admission、正式private坐标和payability仍UNKNOWN。','', '## 新公开源码与循环反馈','', '本轮取得683/669/673/707/708的官方Rust与Lean，作者、时间、原始响应和哈希保留。683/669/673在当前官方记录有正历史奖励；15次请求的历史snapshot均404，具体历史高份额/持续情况UNKNOWN。未将累计奖励或公共预测当历史高份额。669与683主要差异为记录预算，因此未分配无差异参数扫描。详见[source-learning](../../evidence/round27/source-learning.json)。','', '第一圈在683/708测三种字级/编译边界机制；第二圈在673测短匹配与内联；发现C参照分歧后做原协议顺序诊断，同时B继续价格选择、生产端连接。八个不同Rust均至少真实测量一次。A没有收益；B2只改变source.rs.txt的2个压缩字节；B3、B4全部28文件token/压缩输出相同，B4单次主测较实际父版约慢1.27%。这些只排除此批实现/条件，不证明价格选择机制永远无效。','', '评分不是全局单调：快照30183、固定Y=35.641944971%时，X=0.45重放约8.49%，X=0.42反而约0.887%。初始全局二分错误已明确失效并保留，随后改有限局部扫描。copy分歧按实际测量及分子/分母分解记录，未使用任意压力场景或噪声校正。','', '首次新增轮次CI因路由literal26被跳过，静态检查修复后实际测量才计入；本地gate绑定器字段兼容及缩进修复没有重新定义gate通过。Git push一次HTTP408后先查询远端再重试，未重复派发不确定作业。','', '## 消耗与交付','',f'共{len(cis)}次手动CI：{sum(c["conclusion"]=="success"for c in cis)}成功、{sum(c["conclusion"]=="skipped"for c in cis)}跳过；{analysis["paired_processes"]}个原协议配对进程。累计实际job时长{result["resource_job_seconds"]/60:.2f}分钟，为并行作业时长之和，不能当90分钟墙钟或账单。模型/CI可归因金额UNKNOWN；账户实际用量见usage-start/mid/close。','', '两份原版gate通过的精确源码包见[包清单](../../evidence/round27/review-packages/manifest.json)，只作审阅，没有正式上传。原始逐文件11rep、输入输出hash、runner环境、CI回执及独立确认均保留。看板按本轮同快照刷新，历史α不当成本轮新收入。','', 'VERIFIED：源码取得/哈希、真实公共测量、两个完整gate、B1四块新确认、C诊断反例及原始字节审计。INFERRED：同族正式坐标校准、单独/联合份额几何重放、部分成本解释。UNKNOWN：新候选正式可支付结果、private-set收益、历史高份额持续性和实际到账/账单。','', '最高价值后续动作：先取得能证实曾高份额的新公开源码，关注能改变token输出/encoder成本的机制；在708类研究同时比较两个合法hash-head候选的真实机会/频率，避免仅打磨首字微成本。先做有边界的机会计数/最小实测，核验证明迁移代价；没有源码调查或计数时保持proposal，不假定可达5%。本轮未完成，现有反例和正确文件包作为下一轮起点。','']
    (ROOT/'docs/rounds/round27.md').write_text('\n'.join(lines),encoding='utf-8',newline='\n')
    print(json.dumps({'snapshot':result['snapshot_id'],'candidates':len(rows),'ci_runs':len(cis),'paired_processes':analysis['paired_processes'],'runner_minutes':result['resource_job_seconds']/60,'goal':'UNMET'}))
if __name__=='__main__':main()
