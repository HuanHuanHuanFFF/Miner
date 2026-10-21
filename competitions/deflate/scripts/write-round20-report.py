"""Create hash-bound review packages and a report from audited R20 evidence."""
from pathlib import Path
from datetime import datetime,timezone,timedelta
import argparse,hashlib,io,json,statistics as st,zipfile
ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round20'
def read(p):return json.loads(p.read_bytes())
def dump(p,v):p.write_text(json.dumps(v,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
def sha(b):return hashlib.sha256(b).hexdigest()
def num(x):return f'{x:.6f}'
def when(x):return datetime.fromisoformat(x).astimezone(timezone(timedelta(hours=8))).strftime('%Y-%m-%d %H:%M:%S')
def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--analysis',type=Path,required=True);ap.add_argument('--impact',type=Path,required=True);ap.add_argument('--all-original',type=Path,required=True);ap.add_argument('--audit',type=Path,required=True);ap.add_argument('--closed',action='store_true');a=ap.parse_args()
    for key in ['analysis','impact','all_original','audit']:setattr(a,key,getattr(a,key).resolve())
    analysis,impact,allobs,audit=[read(p)for p in [a.analysis,a.impact,a.all_original,a.audit]]
    assert analysis['snapshot']['snapshot_id']==impact['snapshot']['snapshot_id']==allobs['snapshot']['snapshot_id']
    assert all(v['top1_count']==0 for v in impact['summaries']), 'New current-frontier Top1 signal requires a fresh interpretation, not this prior conclusion.'
    assert all(v['at_least_5_count']==0 for c in analysis['candidates']for v in c['summary'].values()), 'New high-share signal: revise the report conclusions.'
    if a.closed:assert not audit['uncollected_run_ids']
    budget=read(E/'budget.json');top=impact['current_top1'];snapshot=analysis['snapshot'];packages=[];out=E/'review-packages';out.mkdir(exist_ok=True)
    for c in analysis['candidates']:
        p=ROOT/c['path'];cert=read(p/'VERIFICATION.json');files={n:(p/n).read_bytes()for n in ['parse.rs','Parse.lean']};hashes={n:sha(b)for n,b in files.items()};assert hashes==cert['files']
        confirm={'plan':'evidence/round20/confirmation-plan-jk.json','analysis':a.analysis.relative_to(ROOT).as_posix(),'impact':a.impact.relative_to(ROOT).as_posix(),'snapshot_id':snapshot['snapshot_id'],'runs':[r['run_id']for r in analysis['runs']],'scope':'Four frozen original-protocol blocks on two new runners. All later counterexamples retained separately; public conditional projections are not formal performance.'}
        cert['independent_confirmation']=confirm;dump(p/'VERIFICATION.json',cert)
        manifest=read(p/'manifest.json');assert manifest['hashes']==hashes;manifest['performance_status']='FOUR_FROZEN_ORIGINAL_BLOCKS_OBSERVED; see final evidence and counterexamples';manifest['independent_confirmation']=confirm;dump(p/'manifest.json',manifest)
        buf=io.BytesIO()
        with zipfile.ZipFile(buf,'w',compression=zipfile.ZIP_DEFLATED,compresslevel=9)as z:
            for name,raw in files.items():
                info=zipfile.ZipInfo(name,date_time=(1980,1,1,0,0,0));info.compress_type=zipfile.ZIP_DEFLATED;z.writestr(info,raw)
        raw=buf.getvalue();path=out/f"{c['candidate']}-{hashes['parse.rs'][:12]}.zip"
        if path.exists():assert path.read_bytes()==raw
        else:path.write_bytes(raw)
        with zipfile.ZipFile(path)as z:assert set(z.namelist())==set(files)and all(z.read(n)==v for n,v in files.items())
        packages.append({'candidate':c['candidate'],'path':c['path'],'files':hashes,'zip':path.relative_to(ROOT).as_posix(),'zip_sha256':sha(raw),'exact_gate':cert,'confirmation_summary':c['summary']})
    joint={}
    for cal in ['primary','shadow']:
        rs=[r for r in impact['joint_observations']if r['calibration']==cal]
        joint[cal]={'candidate_shares':{n:{'median':st.median(r['candidate_shares_pct'][n]for r in rs),'range':[min(r['candidate_shares_pct'][n]for r in rs),max(r['candidate_shares_pct'][n]for r in rs)]}for n in rs[0]['candidate_shares_pct']},'top1_after':{'median':st.median(r['top1_after_pct']for r in rs),'range':[min(r['top1_after_pct']for r in rs),max(r['top1_after_pct']for r in rs)]}}
    summary={'created_at_utc':datetime.now(timezone.utc).isoformat(),'status':'DELIVERABLES_FROZEN_OBJECTIVE_NOT_FORMALLY_ACHIEVED'if a.closed else'DELIVERY_DRAFT_RESEARCH_WINDOW_ACTIVE','budget':budget,'snapshot':snapshot,'current_top1':top,'packages':packages,'single_candidate_impacts':impact['summaries'],'joint':joint,'all_original_singlehead':allobs['summaries'],'cost_audit':a.audit.relative_to(ROOT).as_posix(),'formal_submission_sent':False,'formal_top1':'UNKNOWN_NOT_SUBMITTED','formal_competitor_impact':'UNKNOWN_NOT_SUBMITTED','objective':'No stable own Top1 established. Frozen singlehead confirmation shows conditional competitor impact, contradicted by some other original-protocol observations.'}
    dump(E/'final-summary.json',summary);dump(out/'manifest.json',{'snapshot':snapshot,'packages':packages,'scope':'Exact reviewed sources and original public gates only; no upload authorization or formal qualification claim.'})
    lines=['# 第二十轮：90分钟冲击第一名与份额影响研究','',f"固定窗口：北京时间 **{when(budget['start_utc'])}–{when(budget['deadline_utc'])}**。"+('本轮交付材料已封存。'if a.closed else'交付整理中，窗口尚未结束。')+'执行规则见 [AGENTS.md](../../AGENTS.md)。','',
    '**未获得稳定的自身Top1，也没有完成正式竞赛上传或正式压低第一名。** 保留两份原版完整公共gate通过的精确候选。singlehead在冻结后的四块确认中显示明显的条件竞争影响；全部原协议观察仍有反例，不能把这四块解释为全环境稳定或正式成功概率。','',
    f"最终复算快照 **{snapshot['snapshot_id']}**，计算时间 **{when(snapshot['computed_at'])} 北京时间**，freshness=`{snapshot['freshness']}`。当前第一名 **#{top['id']}** 的竞赛池可支付份额为 **{num(top['payable_share_pct'])}%**。新候选数值均为 **INFERRED 条件估算**：按正式#539及同块公共原源码／同源码影子参照迁移，保留全部当前前沿，再插入新点重新评分。",'',
    '## 冻结独立确认','',
    '两台新runner各两块，共四块：38051540412、38051548407。冻结提交`1cafa22b20c4720543e20a5dd9804d07ab0f133d`；每块固定28文件、15,930,000原始字节，每文件1次预热＋11次计时，使用候选／配对incumbent总压缩时间中位数之比的等权平均。逐文件原始reps、工具链、二进制和环境信息均保留。固定公共语料已参与搜索，独立性限于新运行。','',
    '| 候选／参照 | 自身份额中位 | 最低–最佳 | 自身零／Top1次数 | 第一名加入后中位 | 第一名加入后范围 |','|---|---:|---:|---:|---:|---:|']
    for r in impact['summaries']:
        c=next(c for c in analysis['candidates']if c['candidate']==r['candidate']);own=r['new_share_pct'];after=r['top1_after_pct'];label=r['candidate'].removeprefix('r20-539-csv-')
        lines.append(f"| {label}／{r['calibration']} | {num(own['median'])}% | {num(own['min'])}–{num(own['max'])}% | {r['zero_count']}/4；{r['top1_count']}/4 | {num(after['median'])}% | {num(after['min'])}–{num(after['max'])}% |")
    gaps=[r['relative_time_gap_pct']for r in analysis['same_source_controls']]
    lines += ['', '| 候选／runner／参照 | 自身份额中位／范围 | 第一名加入后范围 |','|---|---:|---:|']
    for name in [c['candidate']for c in analysis['candidates']]:
        for run in [r['run_id']for r in analysis['runs']]:
            for cal in ['primary','shadow']:
                rr=[r for r in impact['observations']if r['candidate']==name and r['run_id']==run and r['calibration']==cal];vs=[r['new_share_pct']for r in rr];ts=[r['top1_after_pct']for r in rr]
                lines.append(f"| {name.removeprefix('r20-539-csv-')}／{run}／{cal} | {num(st.median(vs))}%／{num(min(vs))}–{num(max(vs))}% | {num(min(ts))}–{num(max(ts))}% |")
    lines += ['',f"四块确认中同源码同二进制参照差异为 **{min(gaps):+.6f}% 至 {max(gaps):+.6f}%**。两套校准是同四块的两个视图，不能计为八块。两候选在主／影子下达到5%或15%自身份额的次数均为0/4。样本次数不表示正式成功概率。",'',
    '## 全部原协议观察与后续反例','',
    'singlehead除冻结确认外还作为发现候选、后续批次对照及原协议诊断对象运行。下面纳入所有六台runner、十二个原协议块；额外同源码候选副本另保存在JSON，不重复算独立块。','',
    '| 参照 | 块／runner | 自身中位／范围 | 自身为零 | 对第一名无降低 | 曾预测Top1 |','|---|---:|---:|---:|---:|---:|']
    for r in allobs['summaries']:
        if r['role']!='all_primary_candidate_views':continue
        v=r['own_share_pct'];lines.append(f"| {r['calibration']} | {r['blocks']}／{r['runners']} | {num(v['median'])}%／{num(v['min'])}–{num(v['max'])}% | {r['zero_own_count']}/{r['blocks']} | {r['no_top1_reduction_count']}/{r['blocks']} | {r['top1_count']}/{r['blocks']} |")
    lines += ['', '发现期18.497129%峰值属于旧快照29540；当前快照已重新计算同一测量，不把竞争变化误记为算法变化。冻结确认没有复现高自身份额；后续H/P对照和G原协议诊断的失效视图全部保留。**最低成绩包含零，不能只展示成功的四块。**','',
    '## 同时加入','', '| 参照 | 候选 | 联合份额中位／范围 |','|---|---|---:|']
    for cal,v in joint.items():
        for n,z in v['candidate_shares'].items():lines.append(f"| {cal} | {n.removeprefix('r20-539-csv-')} | {num(z['median'])}%／{num(z['range'][0])}–{num(z['range'][1])}% |")
        z=v['top1_after'];lines.append(f"| {cal} | 原第一名#{top['id']} | {num(z['median'])}%／{num(z['range'][0])}–{num(z['range'][1])}% |")
    lines += ['', '联合结果使用同块坐标同时插入、重新归一化，未相加独立估算。支付仍须未来准入、注册、额度、bounty条件及hotkey唯一前沿支付规则成立；本轮未核验或执行这些正式操作。','', '## 精确可审阅包','']
    for p in packages:
        cert=p['exact_gate'];lines += [f"- **{p['candidate']}**：[源码与证明](../../{p['path']}) · [两文件ZIP](../../{p['zip']}) · [原始gate回执](../../{cert['receipt']})。",f"  Rust SHA-256：`{p['files']['parse.rs']}`。",f"  Lean SHA-256：`{p['files']['Parse.lean']}`。",f"  ZIP SHA-256：`{p['zip_sha256']}`。",f"  原版完整gate `{cert['run_id']}`，{cert['gate_seconds']}秒；原Lean900秒上限、新提取、原始`LZ77.Obligation`、公理白名单`Classical.choice / Quot.sound / propext`及公共round trip通过。"]
    lines += ['', '候选保留原作者路由，其中仍有输入长度条件；本轮没有证明未见输入分布上的迁移。公共stage1、正式stage2、admission、几何份额和实际到账分别验收。','',
    '## 机制反馈与暂停理由','',
    '- 单头文本路径：移除第二候选搜索，付出质量换速度。四块确认显示竞争影响，但自身份额低且其他原协议块有失效，保留精确包而不宣称稳定胜出。',
    '- 16位前驱：公共输出比CSV18少3字节，完整证明通过；确认份额低且有零值，没有稳定的大幅竞争收益。',
    '- 六符号DNA表示：在另一N匹配器多7623字节、16130个token，暂停该迁移版本。',
    '- 链＋惰性解析／单头＋惰性解析：分别少48058／16339字节，真实总时间增加，E两块主／影子均零，停止整组启用。',
    '- 距离成本比较：少1059字节、增加622个token；H主校准两块零，影子有小份额且同源码偏差达到2.482%，未晋升。',
    '- 二级搜索机会：930666次请求中110591次选到更长候选，收益遍布长度段；计数不足以支持大幅低损耗的长度剪枝，没有扫描一串阈值。',
    '- 缩小前驱保留环：相对完整16位环多1862字节；N主／影子对竞争影响显著分歧，性能信号未建立，未投入完整gate。',
    '- 移除反向合并：两版本分别增加142625／236141字节，真实总时间也未改善，P两块主／影子均零。parser少做工作不等于总压缩更快。',
    '- 新公开535／599：已通过普通官方source入口保存原字节和作者。相对514主要是表容量、既有路由和参数调整，未发现新匹配器；保留为参照，不算本轮算法或gate。','',
    '## 测量诊断','',
    'G区分原协议单候选、共享进程与实际绑核；顺序反转伴随信号反转，单核绑定未消除。M固定CPU和20次测量，仅均衡执行顺序：参照同源码绝对偏差中位从0.385742%降到0.049060%；候选副本仍有0.209262%差异。顺序效应得到这组受控诊断支持，剩余原因未由该实验闭合。',
    'R进一步比较均衡顺序下分别装载与共用物理库文件：参照绝对差异中位0.058120%→0.127375%，候选0.077687%→0.067898%，没有一致下降，未确认装载身份是主因。[装载诊断](../../evidence/round20/library-r-analysis.json)不得替换原协议计时或变成“修正后的官方分数”。'if(E/'library-r-analysis.json').exists()else'R装载布局诊断尚未形成已核验结论，最终状态见原始运行回执；没有将其转写为正式性能。',
    '固定singlehead大小坐标时，快照29551的#533／#595时间边界相对宽仅0.087091%；100个区间内采样点都预测几何Top1，跨端点则骤降。全部实际观测的投影时间相对跨度为2.821415%。这是[评分边界解释](../../evidence/round20/score-window-29551.json)，不是连续区间的数学证明、误差界或成功概率；没有通过人为延时追逐这个窄窗。',
    '诊断全部与正式协议成绩分列。原始证据：[G](../../evidence/round20/noise-g-analysis.json)、[M](../../evidence/round20/order-m-analysis.json)、[分子／配对分母分解](../../evidence/round20/control-components-b.json)。','',
    '## 消耗、工作区与下一步','',
    f"已收齐 **{len(audit['jobs'])}** 个手动作业，未收齐 `{audit['uncollected_run_ids']}`；原协议配对进程 **{audit['original_paired_processes']}**（标准批次{audit['standard_batch_paired_processes']}，原协议诊断{audit['original_protocol_diagnostic_processes']}），另有 **{audit['nonstandard_diagnostic_processes']}** 个非标准诊断进程。配对进程包含对照，不是独立样本数。原始文件 **{audit['raw_file_count']}** 个／**{audit['raw_bytes']}**字节逐项SHA核对；runner累计 **{audit['runner_seconds']}秒**，不是墙钟或已确认账单。共 **{audit['unique_new_rust_count']}** 份不同新Rust；证明副本未另算算法。",'',
    '账户开始已用26%，后续真实读数见[用量记录](../../evidence/round20/usage-close.json)。它是共享账户观察，不能归因费用；重置0次、购买0次，模型／云端金额UNKNOWN。',
    '实验分支`codex/round20-top1`；main的其他任务未推送提交b5cb035保持隔离。没有合并main、删除其他分支或正式竞赛上传。源码、证明和归档按既有实验分支授权推送。',
    '后续最高价值动作：先把官方同源码控制分歧和跨环境迁移区分清楚，再选择有更大真实速度／质量余量的机制。可复用已通过的16位前驱证明和完整单头包；不要靠重复寻找窄窗峰值或把竞争影响等同自身收入。任何正式提交须另行核对当时前沿、资格和精确文件。','',
    f"[结构化结果](../../evidence/round20/final-summary.json) · [全部原协议观察](../../{a.all_original.relative_to(ROOT).as_posix()}) · [独立确认](../../{a.analysis.relative_to(ROOT).as_posix()}) · [原始字节与消耗审计](../../{a.audit.relative_to(ROOT).as_posix()}) · [提交看板](../../DASHBOARD.md) · [研究状态](../../evidence/round20/research-state.md)", '',
    '**VERIFIED**：精确公共gate、原始测量／诊断、源文件与回执哈希。**INFERRED**：份额、私有迁移、竞争影响与机制解释。**UNKNOWN**：新候选正式私有评测、admission、可支付份额和实际到账。自身Top1与正式竞争影响均未完成。','']
    (ROOT/'docs/rounds/round20.md').write_text('\n'.join(lines),encoding='utf-8');print(json.dumps({'snapshot':snapshot,'packages':[p['zip']for p in packages],'report':'docs/rounds/round20.md','closed':a.closed}))
if __name__=='__main__':main()
