"""Publish the R19 evidence summary after fresh confirmation and full gates."""
from datetime import datetime, timedelta, timezone
from pathlib import Path
import hashlib
import json
import statistics as st
import zipfile

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round19'


def read(path):
    return json.loads(path.read_bytes())


def main():
    analysis = read(E / 'final-analysis.json')
    audit = read(E / 'audit-final.json')
    plan = read(E / 'confirmation-plan.json')
    assert not audit['uncollected_run_ids']
    assert {r['run_id'] for r in analysis['runs']} == {'38045333804', '38045342845'}
    assert all(r['ci_conclusion'] == 'success' and r['role'] == 'independent_confirmation' for r in analysis['runs'])
    expected = {c['name']: c for c in plan['candidates']}
    packages = E / 'review-packages'
    packages.mkdir(exist_ok=True)
    results = []
    for candidate in analysis['candidates']:
        name = candidate['candidate']
        source = ROOT / expected[name]['path']
        cert = read(source / 'VERIFICATION.json')
        assert cert['status'] == 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED' and cert['files'] == expected[name]['hashes']
        for file, digest in cert['files'].items():
            assert hashlib.sha256((source / file).read_bytes()).hexdigest() == digest
        stats = candidate['independent_confirmation_summary']
        assert all(stats[key]['n'] == 4 and stats[key]['runner_count'] == 2 for key in ('primary', 'shadow'))
        public_changes = [o['time_change_pct_vs_parent'] for o in candidate['observations'] if o['calibration'] == 'primary']
        archive = packages / f"{name}-{cert['files']['parse.rs'][:12]}.zip"
        package_files = ('parse.rs', 'Parse.lean', 'manifest.json', 'VERIFICATION.json')
        rebuild = not archive.exists()
        if not rebuild:
            with zipfile.ZipFile(archive) as z:
                rebuild = any(z.read(file) != (source / file).read_bytes() for file in package_files)
        if rebuild:
            with zipfile.ZipFile(archive, 'w', zipfile.ZIP_DEFLATED, compresslevel=9) as z:
                for file in package_files:
                    z.write(source / file, file)
        with zipfile.ZipFile(archive) as z:
            assert all(hashlib.sha256(z.read(file)).hexdigest() == digest for file, digest in cert['files'].items())
        results.append({'candidate': name, 'files': cert['files'], 'gate_run_id': cert['run_id'], 'gate_seconds': cert['gate_seconds'],
            'independent_confirmation': stats, 'by_runner': candidate['by_run_summary'],
            'public_time_change_pct': {'median': st.median(public_changes), 'range': [min(public_changes), max(public_changes)]},
            'review_package': archive.relative_to(ROOT).as_posix(), 'zip_sha256': hashlib.sha256(archive.read_bytes()).hexdigest(),
            'formal_admission': 'UNKNOWN_NOT_SUBMITTED', 'formal_payable_share': 'UNKNOWN_NOT_SUBMITTED'})
    results.sort(key=lambda r: r['independent_confirmation']['primary']['median_pct'], reverse=True)
    joint = analysis['joint'][0]['matched_observations']
    joint_summary = {cal: {r['candidate']: {'median_pct': st.median(o['simultaneous_geometric_pct'][r['candidate']] for o in joint if o['calibration'] == cal),
        'range_pct': [min(o['simultaneous_geometric_pct'][r['candidate']] for o in joint if o['calibration'] == cal),
                      max(o['simultaneous_geometric_pct'][r['candidate']] for o in joint if o['calibration'] == cal)]} for r in results} for cal in ('primary', 'shadow')}
    summary = {'created_at_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': analysis['snapshot'], 'confirmation_plan': 'evidence/round19/confirmation-plan.json',
        'candidates': results, 'joint': joint_summary, 'controls': analysis['same_source_controls'], 'cost': {k: audit[k] for k in ('runner_seconds', 'original_paired_processes', 'raw_file_count', 'raw_bytes', 'money_cost', 'reset_cards_used')},
        'goal_status': '15_PERCENT_STRETCH_NOT_REACHED; NO_NEW_FORMAL_SUBMISSION',
        'scope': 'VERIFIED exact public gates and fresh two-runner four-block observations. INFERRED public-to-formal projections, conditional on private transfer/admission/eligibility. UNKNOWN new formal share and actual payment; sample fractions are not probabilities.'}
    (E / 'final-summary.json').write_bytes((json.dumps(summary, indent=2) + '\n').encode())
    snapshot = analysis['snapshot']
    computed = datetime.fromisoformat(snapshot['computed_at']).astimezone(timezone(timedelta(hours=8))).isoformat()
    lines = ['# 第十九轮：90分钟高份额研究', '',
        '固定研究窗口：北京时间 **2026-10-10 17:43:57–19:13:57**，准备、排队、实验、修复、复测和交付均计入90分钟。执行规则见 [AGENTS.md](../../AGENTS.md)。', '',
        '**保留两个完整公共验收候选，未达到15%挑战目标，也没有本轮新正式上传。** 两台新runner各2块冻结确认，共4块；发现阶段另外统计。两份Lean均通过原版900秒限制、新提取、原始义务、公理白名单及stage1 round trip，公共输出均4,864,300B。', '',
        f"份额口径为竞赛奖励池。当前复算快照 **{snapshot['snapshot_id']}**，计算时间 **{computed}**，freshness=`{snapshot.get('freshness')}`。使用正式#603与同块原源码／同源码影子参照校准，保留当前榜单上的所有点。新候选份额为 **INFERRED 条件估算**，不是正式可支付结果。", '',
        '| 候选 | 主校准中位／最佳 | 主校准观测范围 | 影子中位／范围 | 零份额／≥5%／≥15%（主、影子各4块） | 完整gate |',
        '|---|---:|---:|---:|---|---|']
    for r in results:
        a, b = [r['independent_confirmation'][key] for key in ('primary', 'shadow')]
        counts = lambda s: f"{s['zero_count']}/4、{s['at_least_5_count']}/4、{s['at_least_15_count']}/4"
        lines.append(f"| [{r['candidate']}](../../candidates/{r['candidate']}) | {a['median_pct']:.6f}%／{a['best_pct']:.6f}% | {a['range_pct'][0]:.6f}–{a['range_pct'][1]:.6f}% | {b['median_pct']:.6f}%／{b['range_pct'][0]:.6f}–{b['range_pct'][1]:.6f}% | 主：{counts(a)}；影：{counts(b)} | {r['gate_run_id']}，{r['gate_seconds']}秒，通过 |")
    lines += ['', '主校准与影子是同一4块数据的两种配对参照，不是8块独立样本。公共语料仍是搜索用过的固定28文件；独立性只指冻结后的新运行。上述频数不表示正式成功概率。', '',
        '## 同时加入与测量边界', '']
    for cal, values in joint_summary.items():
        lines.append('- ' + cal + '：' + '；'.join(f"{name} 中位 {value['median_pct']:.6f}%" for name, value in values.items()) + '。')
    gaps = [x['relative_time_gap_pct'] for x in analysis['same_source_controls']]
    lines += ['', '两者公共大小相同，观测中较快者支配另一者；独立估算不能相加。以上仍以未来准入、私有迁移和独立可支付身份成立为条件；注册、额度、钱包和正式提交均未执行。',
        f'同源码同二进制参照时间分歧为 **{min(gaps):+.6f}% 至 {max(gaps):+.6f}%**。两种校准均保留，并按runner分层；逐文件总压缩时间、配对incumbent、全部原始重复及环境见[最终复算](../../evidence/round19/final-analysis.json)。CPU亲和记录实际为0–3，虽请求CPU0，仍沿用原版协议，没有把额外诊断替代官方计时。', '',
        '| 候选／runner／校准 | 中位 | 范围 |', '|---|---:|---:|']
    for r in results:
        for group in r['by_runner']:
            lines.append(f"| {r['candidate']}／{group['run_id']}／{group['calibration']} | {group['median_pct']:.6f}% | {group['range_pct'][0]:.6f}–{group['range_pct'][1]:.6f}% |")
    lines += ['', '## 精确交付文件', '']
    for r in results:
        lines += [f"- **{r['candidate']}**：[审阅包](../../{r['review_package']})；公共总时间相对同块#603中位变化 {r['public_time_change_pct']['median']:+.4f}%。",
            f"  Rust SHA-256：`{r['files']['parse.rs']}`；Lean SHA-256：`{r['files']['Parse.lean']}`。",
            f"  ZIP SHA-256：`{r['zip_sha256']}`。"]
    lines += ['', '## 实验反馈与保留的起点', '',
        '- 发现批J的nooverlap主范围6.7699%–6.8363%、影子6.7528%–6.8880%；nojson主6.4350%–6.4665%、影子6.4497%–6.4855%。这些是参与选择的旧两块，未混入最终四块统计。',
        '- 缩小局部重规划、仅复用旧匹配、减浅搜索、基础规划减半等实现失去太多质量；保留完整价格上下文的局部复核仍损失多数收益。没有把一次失败扩大成整类方法不可行。',
        '- 内容预算版快约8.8%，但稍大的坐标与既有#603竞争，发现预测仅约1.28%；“更快”不等于更高份额。',
        '- 四链SF多压小91B，却越过#585成为压缩端点，失去增量时间轴奖励；原协议发现预测约0.002811%。前沿切换与归一化已重放，不以更小或平均坐标宣布成功。',
        '- 同距离码端点剪枝保持28文件输出，但两块原协议未建立提速，份额均零；函数工作量和字节等价不替代端到端性能。',
        '- 基础缓存覆盖97.25%的额外SF匹配项，直接替换仍多675B；少量缺失项可能贡献重要收益。改成保留原搜索、只复用同距离已知前缀后，诊断保持逐token/输出相同。',
        '- [显式缓存生命周期草稿](../../candidates/r19-sf-shared-prefix-draft) Rust `26aa056b94098d0d22f13f1e0ca3f6e5af09ec044341e82391b4bfd886506ff0` 已编译、28文件逐token/输出相同，无全局Mutex或缓存clone。新helper和A引擎返回值的Lean证明尚未迁移；它不属于上述两个完整验收包。',
        '- 草稿的一块原协议发现见[单独分析](../../evidence/round19/analysis-s.json)，不属于冻结确认。它尚未显示高于冻结主候选的条件收益；下一轮先与nooverlap同场配对、检查缓存查询新增成本，确认优势后再投入证明。', '',
        '## 消耗与证据', '',
        f"已收齐 **{len(audit['jobs'])}** 个手动作业；原协议配对进程 **{audit['original_paired_processes']}** 个（包含对照，不是独立样本数）；runner墙钟累计 **{audit['runner_seconds']:.0f}秒**。原始artifact文件 **{audit['raw_file_count']}** 个、**{audit['raw_bytes']}字节**，均逐项SHA-256核对。另有14份Rust候选及单列的观察器／诊断原型。", '',
        '账户用量从已用22%开始，[收尾读取](../../evidence/round19/usage-close.json)为已用25%、剩余75%；属于共享账户读数，不能归因成本轮费用。重置0次、购买0次；实际模型与云端金额UNKNOWN。三次代理路径推送HTTP408后改用临时直连成功，未修改全局设置，故障耗时计入窗口。main的其他任务未推送提交保持原样。', '',
        '- [预算与截止](../../evidence/round19/budget.json)、[决策过程](../../evidence/round19/research-state.md)、[冻结确认计划](../../evidence/round19/confirmation-plan.json)、[仍距15%的有界坐标要求](../../evidence/round19/final-coordinate-gaps-29533.json)。',
        '- [最终结构化结果](../../evidence/round19/final-summary.json)、[原始字节与成本审计](../../evidence/round19/audit-final.json)、[当前官方快照](../../evidence/round19/official-final/receipt.json)。',
        '- [提交看板](../../DASHBOARD.md)、[可复用方法](../research/optimization-methods.md)。', '',
        '**VERIFIED**：精确文件、两份完整公共gate、两runner四块原协议观测与原始回执。**INFERRED**：单独／联合份额、私有迁移及缓存复用机会。**UNKNOWN**：新候选正式admission、正式可支付份额、实际到账，以及草稿的完整证明与独立确认。', '']
    late_path = E / 'analysis-s.json'
    if late_path.exists():
        late = read(late_path)
        if late.get('candidates'):
            c = late['candidates'][0]
            a, b = c['summary']['primary'], c['summary']['shadow']
            change = next(o['time_change_pct_vs_parent'] for o in c['observations'] if o['calibration'] == 'primary')
            text = f"共享缓存草稿S只有**1块发现数据**：相对同块#603总时间轴变化 {change:+.4f}%；主／影子条件份额 {a['median_pct']:.6f}%／{b['median_pct']:.6f}%。它仍缺独立确认、新Lean证明和完整gate，不能作为正式成绩或第三个完整验收包。"
        else:
            text = '共享缓存草稿S未取得可晋级的完整计时结果；失败或未完成记录保留在单独分析，性能结论仍为UNKNOWN。'
        lines.insert(lines.index('## 消耗与证据'), text + '\n')
    (ROOT / 'docs/rounds/round19.md').write_bytes(('\n'.join(lines)).encode())
    print(json.dumps({'candidates': [r['candidate'] for r in results], 'snapshot': snapshot['snapshot_id'], 'joint': joint_summary}))


if __name__ == '__main__':
    main()
