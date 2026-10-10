"""Write the extension report only from complete frozen confirmation evidence."""
from pathlib import Path
from datetime import datetime, timezone, timedelta
import argparse
import hashlib
import json
import statistics as st
import re

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def read(p):
    return json.loads(p.read_bytes())


def write(p, value):
    p.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for flag in ('analysis', 'summary', 'sensitivity', 'payability', 'cost', 'capture', 'audit'):
        ap.add_argument('--' + flag, type=Path, required=True)
    args = ap.parse_args()
    a, s, f, pay, cost, audit = (read(getattr(args, k)) for k in ('analysis', 'summary', 'sensitivity', 'payability', 'cost', 'audit'))
    capture = read(args.capture / 'receipt.json')
    plan = read(E / 'extension-final-confirmation-plan.json')
    budget = read(E / 'budget.json')
    assert s['analysis_sha256'] == hashlib.sha256(args.analysis.read_bytes()).hexdigest()
    assert len(s['run_ids']) == 2 and s['blocks_per_runner'] == 3
    assert s['snapshot']['snapshot_id'] == capture['snapshot_id'] == f['snapshot']['snapshot_id']
    assert not cost['not_yet_collected_run_ids']
    rel = lambda p: p.resolve().relative_to(ROOT).as_posix()
    link = lambda p, title: '[' + title + '](../../' + rel(p) + ')'
    rows = []
    for c in s['candidates']:
        rows.append((c['role'] + '：' + c['name'], c['single'], c['path'], c['files'], c))
    extra = next(g for g in a['candidates'] if g['candidate'] == 'r18-539-csv-lazy-content')
    extra_target = plan['additional_validation_candidates'][0]
    rows.append(('补充：539 CSV 内容版', extra['independent_confirmation_summary'], extra_target['path'], extra_target['hashes'], None))
    now = datetime.now(timezone.utc)
    text = [
        '# 第十八轮追加三小时：冻结确认与交付', '',
        '**15% / 5% 正式可支付目标未完成。** 本轮没有正式上传、注册、链上支出或签名。公共份额均为固定快照、满足准入与支付资格假设后的条件估算。', '',
        '原起点北京时间 **2026-10-10 01:32:51**；用户追加3小时后，总预算11小时，固定截止 **12:32:51**（UTC04:32:51）。原8小时报告保持原样，见[原报告](round18.md)。新算法方向在UTC03:05:51前停止；此后只完成已启动验证、冻结确认与交付。', '',
        '## 独立确认结果', '',
        f'两台新 runner：{", ".join(s["run_ids"])}，每台3块，共6块。每块28文件，每文件1次预热、11次测量；使用配对 incumbent 的总压缩时间，保留全部原始重复值、环境和逐文件输出。两台作业都使用冻结提交 `{plan["dispatch_git_sha"]}`，顺序在派发前预声明，期间源码和证明未改。', '',
        f'以下统一使用官方快照 **{capture["snapshot_id"]}**，官方计算时间 `{capture["competition_context"]["computed_at"]}`，读取区间 `{capture["retrieval_start_utc"]}` 至 `{capture["retrieval_end_utc"]}`。榜单{capture["pagination"]["pareto"]["rows"]}条提交、{capture["pagination"]["leaderboard"]["rows"]}个账户；freshness为`{capture["competition_context"]["freshness"]}`，weights同快照：`{capture["weights_same_snapshot"]}`。', '',
        '| 候选 / 校准 | 中位份额 | 最佳 | 观测范围 | 零份额 | ≥5% | ≥15% |',
        '|---|---:|---:|---|---:|---:|---:|',
    ]
    for name, stats, path, hashes, c in rows:
        for cal in ('primary', 'shadow'):
            d = stats[cal]
            assert d['n'] == 6
            text.append(f'| {name} / {cal} | {d["median_pct"]:.6f}% | {d["best_pct"]:.6f}% | {d["range_pct"][0]:.6f}%–{d["range_pct"][1]:.6f}% | {d["zero_count"]}/6 | {d["at_least_5_count"]}/6 | {d["at_least_15_count"]}/6 |')
    text += ['', 'A为新增SF重规划候选，B为保留的旧RF选择版本；A追加了实际边界重规划机制，公共压缩结果改变，二者不是改名副本。A的目标仍为15%，B仍为5%，不能相加算达标。补充539版本是不同机制的已验收成果。以上样本比例不是正式成功概率；中心坐标算出的分数不是期望收益。', '',
             '## 两者同时加入', '', '| 校准 | A联合中位 / 范围 | B联合中位 / 范围 | 同时满足15%/5%的块数 |', '|---|---|---|---:|']
    for cal, j in s['joint_summary'].items():
        aa, bb = j['A'], j['B']
        text.append(f'| {cal} | {aa["median_pct"]:.6f}% / {aa["range_pct"][0]:.6f}%–{aa["range_pct"][1]:.6f}% | {bb["median_pct"]:.6f}% / {bb["range_pct"][0]:.6f}%–{bb["range_pct"][1]:.6f}% | {j["both_geometric_thresholds_met_count"]}/6 |')
    text += ['', '联合结果逐块重新插入两点并归一化，没有相加独立估算。它仍以不同且合格的hotkey、没有更早存活前沿提交为条件。当前用户注册归属、提交额度和实际付款资格未核验。', '']
    zero573 = [v for v in pay['scenarios'] if v['hypothetical_hotkey_is_the_public_hotkey_of_submission'] == '573']
    if zero573 and all(v['all_candidate_additional_shares_zero'] for v in zero573):
        text += ['**VERIFIED 规则重放**：在使用公开#573所属hotkey的假设下，旧提交仍存活，所有新候选的新增可支付份额均为0。这不说明该hotkey当前属于用户，也不授权注册或签名。', '']
    text += ['## 校准和测量限制', '',
             '主估算使用实际父族#586（539候选使用#539）；相同二进制的影子参照分列。下面保留同一计时块的#591整族迁移敏感性。这不是私有集误差上下界，也不能通过选一个校准宣布正式达标。', '', '| 候选 | #591替代校准中位 | 观测范围 | ≥5%观测数 |', '|---|---:|---|---:|']
    for c in s['candidates']:
        obs = [o['alternative_conditional_pool_pct'] for o in f['rows'] if o['candidate'] == c['name']]
        assert obs
        text.append(f'| {c["name"]} | {st.median(obs):.6f}% | {min(obs):.6f}%–{max(obs):.6f}% | {sum(v >= 5 for v in obs)}/{len(obs)} |')
    text += ['', '| 候选 | 主/影子零份额判断分歧 | 对应目标判断分歧 | 最大份额差 |', '|---|---:|---:|---:|']
    for c in s['candidates']:
        d = c['control_disagreement']
        text.append(f'| {c["name"]} | {d["zero_disagreement_count"]}/6 | {d["target_disagreement_count"]}/6 | {d["max_absolute_share_gap_pct"]:.6f}个百分点 |')
    text += ['', '每台runner统计、每块结果、逐文件时间和环境见下列原始分析。发现期、诊断协议与本次六块确认分开保存；没有把不同runner的绝对时间直接平均后当成收益。', '',
             '## 精确文件与完整 gate', '', '| 候选 | Rust SHA-256 | Lean SHA-256 | gate / 秒 |', '|---|---|---|---|']
    for name, stats, path, hashes, c in rows:
        certpath = ROOT / path / 'VERIFICATION.json'
        cert = read(certpath)
        assert cert['files'] == hashes and cert['status'] == 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
        text.append(f'| {name} | `{hashes["parse.rs"]}` | `{hashes["Parse.lean"]}` | [{cert["run_id"]}](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/{cert["run_id"]}) / {cert["gate_seconds"]} |')
        cert['extension_confirmation'] = {'analysis': rel(args.analysis), 'summary': rel(args.summary), 'run_ids': s['run_ids'],
                                          'snapshot_id': s['snapshot']['snapshot_id'], 'blocks_per_runner': 3,
                                          'single': stats, 'scope': 'Six fresh original-protocol blocks, two runners; conditional projections, not formal success probability.'}
        write(certpath, cert)
    text += ['', '每份验收均重新提取Rust，检查原始`LZ77.Obligation`、白名单公理`Classical.choice / Quot.sound / propext`和公共round trip，原Lean上限900秒、contract/encoder/pins未改。SF初次失败回执保留；修复仅连接外层输出长度等式，Rust没有改变。', '',
             '| 精确可审阅包 | ZIP SHA-256 |', '|---|---|']
    wanted = {path for _, _, path, _, _ in rows}
    for p in sorted((E / 'review-packages').glob('*.json')):
        m = read(p)
        if m['source_path'] in wanted:
            text.append(f'| {link(ROOT / m["payload_path"], m["candidate"])} | `{m["payload_sha256"]}` |')
    text += ['', 'ZIP只含精确`parse.rs`和`Parse.lean`，已逐项核对哈希；没有上传正式竞赛。旧DNA包和原8小时证据也继续保留。', '',
             '## 关键决策与保留的负面结果', '',
             '- BF同机矩阵曾给出自由文件拼接约17.33%的估算；同方案另一家族校准仅3.33%。它从未作为可运行候选或正式成绩。',
             '- 539哈希位宽假设被预检否定；前驱提示迁移仅0/3字节变化，搜索跳步迁移反而多3字节，均停止昂贵验证。实际路由观察找到CSV引擎差异，迁移后少25,588字节并通过完整gate，但份额窗口依旧窄于测量波动。',
             '- 实际RF+SF组合少1,244字节；内容守卫保留1,233字节收益。发现期内容版约9%、全量版约8%，但两者同时加入会变成约0.57%/7.63%，因此没有把它们当成相加的双候选收益。',
             '- 恢复10处原SF内联标记后库字节完全相同；两块时间分别约慢0.426%、快0.459%，没有编译收益。该版完整gate仍已收齐，负面结果保留；没有按单次更快值选择。',
             '- 原SF gate失败只剩最外层长度等式，修复后完整接受。全部原始失败、timing、提取文件和回执保留。', '',
             '## 实际消耗和后续动作', '',
             f'全11小时窗口累计手动派发并收齐 **{cost["dispatched_run_count"]}** 个作业：{cost["collected_conclusions"]}；原协议配对测量进程 **{cost["original_screen_confirmation_paired_processes"]}** 个；runner墙钟累计 **{cost["completed_runner_wall_seconds"]:.0f}秒**。这些累计值包含最初8小时，不是独立样本数或账单分钟。',
             f'相对原8小时记录，追加窗口新增{cost["dispatched_run_count"] - budget["extension"]["baseline_dispatched_runs"]}个作业、{cost["original_screen_confirmation_paired_processes"] - budget["extension"]["baseline_original_paired_processes"]}个原协议配对进程、{cost["completed_runner_wall_seconds"] - budget["extension"]["baseline_runner_wall_seconds"]:.0f}秒runner墙钟。账户最新观察已用{cost["latest_shared_account_observation"]["used_percent"]}%、剩余{cost["latest_shared_account_observation"]["remaining_percent"]}%，这是共享账户用量，不是本任务可归因费用。重置成功0次、购买0次；模型和云端实际金额UNKNOWN。', '',
             '最高价值后续工作是降低SF实际总时间开销，并优先验证按内容分配重规划预算、复用已有匹配信息的成本与质量交换。发现期同大小下达到15%仍需约20%的时间轴改善；这不是对未来实现收益的保证。私有集迁移仍缺正式校准，任何未来上传应先以当前登记、额度和精确包单独审阅。', '',
             '**VERIFIED**：精确文件、公有完整gate、原协议六块观测、原始回执与本地字节审计。**INFERRED**：单独/联合份额、跨家族校准、未来优化空间。**UNKNOWN**：私有集表现、正式admission、可支付份额、实际注册归属/额度、最终收益和可归因金额。', '',
             '## 证据入口', '',
             '- ' + link(args.analysis, '原始计时逐项复算') + '；' + link(args.summary, '主候选六块确认与联合分布') + '；' + link(args.sensitivity, '同块家族校准敏感性') + '。',
             '- ' + link(args.payability, '公开hotkey支付规则情景') + '；' + link(args.capture / 'receipt.json', '官方快照及分页回执') + '。',
             '- ' + link(args.cost, '作业/配对/runner消耗') + '；' + link(args.audit, '原始字节与精确包审计') + '；' + link(E / 'extension-final-confirmation-plan.json', '预声明冻结计划') + '。', '',
             f'报告生成北京时间：{now.astimezone(timezone(timedelta(hours=8))).isoformat()}。固定截止及实际关闭状态见[budget](../../evidence/round18/budget.json)。工作仅在`codex/round18-frontier`；main的其他任务提交没有合并或一起推送。执行规则仍以[AGENTS.md](../../AGENTS.md)为准。', '']
    report = ROOT / 'docs/rounds/round18-extension.md'
    report.write_bytes('\n'.join(text).encode())
    budget['phase'] = 'FINAL_EVIDENCE_REVIEW'
    budget['extension']['final_confirmation_summary'] = rel(args.summary)
    budget['extension']['report'] = rel(report)
    budget['formal_payable_objectives_established'] = False
    write(E / 'budget.json', budget)
    desc = '追加3小时，总11小时；精确SF/RF主包及539补充包完成原版gate、两台runner各3块新确认；15%/5%正式目标未完成，无正式上传。'
    p = ROOT / 'docs/TASK_INDEX.md'
    updated, count = re.subn(r'(?m)^\| round18-extension \|.*$', '| round18-extension | [第十八轮追加三小时](rounds/round18-extension.md) | ' + desc + ' |', p.read_text())
    assert count == 1
    p.write_bytes(updated.encode())
    p = ROOT / 'docs/tasks.json'
    tasks = read(p)
    next(t for t in tasks['tasks'] if t['id'] == 'round18-extension')['decision'] = desc
    write(p, tasks)
    print(json.dumps({'report': rel(report), 'snapshot': s['snapshot']['snapshot_id'], 'formal_goals_met': False}))


if __name__ == '__main__':
    main()
