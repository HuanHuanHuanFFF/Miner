"""Render the R18 handoff from exact frozen confirmations and current capture."""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def read(path):
    return json.loads(path.read_bytes())


def link(path, label):
    return f'[{label}](../../{path})'


def number(value):
    return f'{value:.6f}'.rstrip('0').rstrip('.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--summary', type=Path, required=True)
    parser.add_argument('--analysis', type=Path, required=True)
    parser.add_argument('--capture', type=Path, required=True)
    parser.add_argument('--cost', type=Path, required=True)
    parser.add_argument('--gaps', type=Path, required=True)
    parser.add_argument('--payability', type=Path, required=True)
    parser.add_argument('--ended', action='store_true')
    args = parser.parse_args()
    summary, analysis = read(args.summary), read(args.analysis)
    capture, cost = read(args.capture / 'receipt.json'), read(args.cost)
    gaps, payability = read(args.gaps), read(args.payability)
    budget = read(E / 'budget.json')
    snapshot = summary['snapshot']['snapshot_id']
    assert {snapshot, analysis['snapshot']['snapshot_id'], capture['snapshot_id'],
            gaps['snapshot']['snapshot_id'], payability['snapshot']['snapshot_id']} == {snapshot}
    assert summary['analysis_sha256'] == hashlib.sha256(args.analysis.read_bytes()).hexdigest()
    candidates = {c['role']: c for c in summary['candidates']}
    for c in candidates.values():
        for filename, sha in c['files'].items():
            assert hashlib.sha256((ROOT / c['path'] / filename).read_bytes()).hexdigest() == sha
        assert c['single']['primary']['n'] == 8 and c['single']['shadow']['n'] == 8
    assert summary['formal_payable_goal_status'] == 'NOT_ESTABLISHED'
    rel = lambda p: p.resolve().relative_to(ROOT).as_posix()
    text = [
        '# 第十八轮：八小时双候选研究交付',
        '',
        ('**八小时窗口已结束，15% / 5% 目标未完成。**' if args.ended else
         '**最终两个精确候选及八块独立确认已收齐；固定八小时窗口尚未结束，15% / 5% 目标未完成。**'),
        '交付两份不同算法的公共 gate 通过包：A 为 DNA 前缀域分离，B 为按内容类别保留 RF 规划。没有正式竞赛上传；正式 admission、私有集成绩、注册归属、额度与实际可支付份额均为 **UNKNOWN**。',
        '',
        f'固定北京时间 **2026-10-10 01:32:51—09:32:51**（UTC 17:32:51—次日 01:32:51），上下文压缩和额度重置没有重计时间。执行规则见 [AGENTS.md](../../AGENTS.md)。逐阶段原始判断见 {link("evidence/round18/research-state.md", "研究状态") }；早期峰值和负面结果保留，没有用最后快照改写历史观察。',
        '',
        '## 结果与口径',
        '',
        f'本表固定在官方快照 **{snapshot}**，官方计算时间 **{capture["competition_context"]["computed_at"]}**；读取区间 {capture["retrieval_start_utc"]} 至 {capture["retrieval_end_utc"]}。共有 {capture["pagination"]["pareto"]["rows"]} 条提交、{capture["pagination"]["leaderboard"]["rows"]} 个榜单账户。竞赛 context freshness 为 `{capture["competition_context"]["freshness"]}`；另外读取的 weights/current freshness 为 `{capture["weights_context"]["freshness"]}`，没有提升为实时一致性保证。',
        '',
        '以下均为 **INFERRED 公共条件估算**，单位是竞赛奖励池百分比；没有乘验证者总权重中的 20%。使用各自同场正式参照 #582 / #586 校准，分别插入当前前沿、重新归一化。主对照与 shadow 使用相同源码和二进制，但独立配对测量；shadow 不是新算法。达标次数是观测计数，不是正式成功概率。',
        '',
        '| 候选 / 对照 | 单独份额中位数 | 观测范围 | 最佳值 | 零份额 | ≥5% | ≥15% |',
        '|---|---:|---:|---:|---:|---:|---:|',
    ]
    for role in ('A', 'B'):
        for calibration in ('primary', 'shadow'):
            d = candidates[role]['single'][calibration]
            text.append(f'| {role} / {calibration} | {number(d["median_pct"])}% | {number(d["range_pct"][0])}%—{number(d["range_pct"][1])}% | {number(d["best_pct"])}% | {d["zero_count"]}/8 | {d["at_least_5_count"]}/8 | {d["at_least_15_count"]}/8 |')
    text += [
        '',
        'A 对应单候选 15% 目标，B 对应另一个单候选 5% 目标。两份 Rust 不同，A 的多个 proof 修复版本仍只算一个候选。',
        '',
        '| 同时插入前沿 | A 中位数（范围） | B 中位数（范围） | 同时达到 A≥15%、B≥5% |',
        '|---|---:|---:|---:|',
    ]
    for calibration, row in summary['joint_summary'].items():
        cells = []
        for role in ('A', 'B'):
            d = row[role]
            cells.append(f'{number(d["median_pct"])}%（{number(d["range_pct"][0])}%—{number(d["range_pct"][1])}%）')
        text.append(f'| {calibration} | {cells[0]} | {cells[1]} | {row["both_geometric_thresholds_met_count"]}/8 |')
    text += [
        '',
        '联合值由同一 runner、同一计时块、同一对照类型的两个点共同插入后计算，不能把单独份额相加。几何份额还以两者使用无旧前沿提交的不同合格 hotkey、通过正式 admission 且奖励未封顶为条件。',
        '',
        f'**VERIFIED 规则重放**：若使用公开 #573 的 hotkey，#573 在所有上述插入情景中仍存活，新 A/B 的新增可支付份额均为 0。#453 所属公开归属组的另一组情景也已保存。当前用户是否拥有这些注册、可用槽位与额度没有重新核验，不作当前事实；本轮未读取私密注册材料。{link(rel(args.payability), "支付条件逐块重放")}。',
        '',
        f'完整入口：{link(rel(args.summary), "最终汇总")}、{link(rel(args.analysis), "逐文件原协议复算与联合几何")}、{link(rel(args.capture / "receipt.json"), "官方快照原始回执")}。',
        '',
        '## 精确文件、证明和审阅包',
        '',
    ]
    for role in ('A', 'B'):
        c = candidates[role]
        cert = read(ROOT / c['path'] / 'VERIFICATION.json')
        manifest_path = next(p for p in (E / 'review-packages').glob('*.json') if read(p)['candidate'] == c['name'])
        manifest = read(manifest_path)
        text += [
            f'### {role}：{c["name"]}',
            '',
            ('保留 65,536 个 heads，把 A/C/G/T/N/换行的六字符前缀放入 46,656 个无碰撞槽，其余前缀使用剩余槽。公共实际输出 5,339,229 B，比 #582 少 1,622 B；改善只出现在 genome。' if role == 'A' else
             '保留 #586 原有基础引擎和分类器，仅在类别 13/25/26/29 继续 RF 规划。公共实际输出 4,865,533 B，比 #586 多 678 B；这是质量与总时间的交换。'),
            '',
            f'- Rust：`{c["files"]["parse.rs"]}`',
            f'- Lean：`{c["files"]["Parse.lean"]}`',
            f'- 完整原版公共 gate：run **{cert["run_id"]}**，**{cert["gate_seconds"]} 秒**；Git `{cert["git_sha"]}`。',
            f'- {link(c["path"] + "/parse.rs", "源码")} · {link(c["path"] + "/Parse.lean", "证明")} · {link(cert["receipt"], "原始完整 gate 回执")} · {link(manifest["payload_path"], "两文件审阅 ZIP")}。',
            f'- ZIP SHA-256：`{manifest["payload_sha256"]}`；{link(rel(manifest_path), "包清单")}。',
            '',
        ]
    text += [
        '两次成功 gate 均重新进行官方 Charon/Aeneas 提取、检查原始 `LZ77.Obligation slot.parse`、公理白名单和完整公共 corpus-stage1 round trip；官方源码、contract、encoder、pins 未改动。公理只有 `Classical.choice`、`Quot.sound`、`propext`。本地有限等价或 proof 复用没有替代完整验收。',
        '',
        'A 第一次 gate 的掩码转换边界及 WP 续体证明失败、第二次宽泛简化触发原 900 秒超时，均保留原始失败；最终通过版本改为局部边界引理与续体证明，Lean 主体 418.9 秒，没有提高超时或添加公理。这三版 Rust 相同。',
        '',
        '## 冻结后的独立确认',
        '',
        '先冻结两个精确文件对，再启动 AT 与 BA。BA 在查看 AT 结果前登记，未按高低点选择性补跑。两台各四块，共八块；不是八台 runner。',
        '',
        '| Runner / run | CPU | 原协议配对进程 | A 主 / shadow 中位 | B 主 / shadow 中位 |',
        '|---|---|---:|---:|---:|',
    ]
    for run in summary['environments']:
        medians = {}
        for role, candidate in candidates.items():
            medians[role] = {r['calibration']: r['median_pct'] for r in candidate['by_runner'] if r['run_id'] == run['run_id']}
        text.append(f'| {run["batch"]} / {run["run_id"]} | {run["environment"]["cpu_model"]} | {run["paired_processes"]} | {number(medians["A"]["primary"])}% / {number(medians["A"]["shadow"])}% | {number(medians["B"]["primary"])}% / {number(medians["B"]["shadow"])}% |')
    text += [
        '',
        '每个进程包含 28 个固定公共文件、15,930,000 原始字节；每文件 1 次预热、11 次计时，取每文件候选/配对 incumbent 总压缩时间中位数之比，再等权平均。原始所有 reps、文件哈希、token/输出哈希和环境均保留；两个 runner 的统计分列。没有用 parser 单独耗时或总字节加权比替代两轴。',
        '',
        '两个 runner 均为 Linux x86_64、rustc 1.100.0-nightly（2026-08-17，固定 nightly-2026-08-18 工具链）。原测量入口记录请求 CPU 0，但实际进程 affinity 为 0–3；原协议结果如实保留。显式 CPU0 / 平衡顺序的另行诊断与原协议分列，不宣称原确认已严格绑单核。',
        '',
        f'A 在 {candidates["A"]["control_disagreement"]["zero_disagreement_count"]}/8 块更换同源码参照后发生零/非零切换；B 为 {candidates["B"]["control_disagreement"]["zero_disagreement_count"]}/8。两者都没有 5%/15% 达标判断分歧，因为本次所有逐块值均低于门槛。DNA 同源码时间差实测范围 −0.6131%—+0.6906%，#586 同源码范围 −0.3310%—+0.5284%。',
        '',
        f'{link("evidence/round18/final-confirmation-plan.json", "预先冻结计划")}；早期 Y 的一台四块确认、AP 的发现块及之后作为 control 的测量仍分别保存，未混入本节八块。',
        '',
        '## 评分敏感性与目标缺口',
        '',
    ]
    a_group = next(c for c in analysis['candidates'] if c['rust_sha256'] == candidates['A']['files']['parse.rs'])
    center = a_group['summary']['shadow']['score_at_center_NOT_expected_reward_pct']
    text += [
        f'**VERIFIED 复算，INFERRED 收益**：A 的 shadow 平均坐标在该快照得到 **{number(center)}%**，但八个实际 shadow 块的最大值只有 **{number(candidates["A"]["single"]["shadow"]["best_pct"])}%**。平均坐标落入邻居切换的狭窄位置，不能当成期望收益。AP 历史单块 18.27497% 与其余低值、shadow 全零仍保留，不作最终达标证据。',
        '',
        '同一最终测量从旧快照 29434 换到 29456，B 的主中位预测由 2.35364% 降到 1.66765%；这是竞争前沿变化，不是代码测量变慢。两次快照及同测量对比在 [前沿变化重放](../../evidence/round18/confirmation-frontier-change.json)。后续新快照的值见本文首表，不覆盖这个历史观察。',
        '',
        'A 的最后八块逐文件分解中，唯一输出变化的 genome 对相对时间轴始终是正贡献（变慢）；看似变快的块由其他 27 个输出未变文件的计时贡献推动。程序、编码器与配对分母均参与变化。输出不变并不能证明执行路径不变，这只是观测分解，不把噪声宣布为唯一因果原因。[最终分解](../../evidence/round18/base6-final-time-components.json)。',
        '',
        '| 固定另一轴的有限坐标搜索 | 5% 最近样本 | 15% 最近样本 |',
        '|---|---:|---:|',
    ]
    for row in gaps['candidates']:
        role = 'A' if row['candidate'].startswith('r18-dna') else 'B'
        for axis in ('time', 'size'):
            values = []
            for goal in ('5', '15'):
                sample = row['targets'][goal]['closest_sample_' + axis]
                values.append('所查范围无样本' if sample is None else
                              (f'{number(sample["time_change_pct"])}% 时间' if axis == 'time' else f'{number(sample["size_delta_pp"])} pp 大小'))
            text.append(f'| {role} / {"改时间" if axis == "time" else "改大小"} | {values[0]} | {values[1]} |')
    text += [
        '',
        '这里以实际观测的描述性中心为坐标参照，时间搜索 0.5—1.5 倍、大小搜索降低最多 0.1 pp，并检查每个已知前沿切换的两侧。它不是可实现算法、穷尽证明、压力测试或正式成功概率；更快也可能因删除邻居而获得更低份额。A 的实际时间跨度约 1.612%，远大于其近邻 15% 窗口约 0.0945%。',
        '',
        f'{link(rel(args.gaps), "全部采样点与分段")}。对 B 的七处原 RF 质量收益做 128 种固定文件选择，每种固定选择应用于全部八块，而非逐块挑赢家；快照 29456 下没有任何组合/对照达到 5%。最好混合的对照变体中位约 1.8271%、最大约 2.8207%。这是零路由开销的文件级机会模型，不是可运行分类器，也不是任意新机制不可能的证明。[已有 RF 恢复机会](../../evidence/round18/final-rf-restoration-options-current.json)。',
        '',
        '## 已完成的路线取舍',
        '',
        '| 路线 | 直接反馈与当前取舍 | 证据 |',
        '|---|---|---|',
        '| DNA 早期 dense4^6、字面量、成本、浅链 | 缩表版多 16,312 B；字面量少字节却大增 token；修正为真实 2.5 bit 成本后少 9,932 B 但最终筛选仍 0；多一个前驱少 321 B，筛选仍 0。暂停这些精确版本，未永久排除 DNA。 | [D](../../evidence/round18/mechanisms-d-decision.json)、[AR](../../evidence/round18/dna-ar-decision.json)、[AV](../../evidence/round18/dna-av-decision.json) |',
        '| DNA 前缀分区 | 保留原表容量后 split4/base6 分别少 1,637/1,622 B，base6 出现高峰后完成诊断、证明修复及八块确认；高份额不稳定。 | [AL](../../evidence/round18/dna-al-native-decision.json)、[AP](../../evidence/round18/dna-ap-decision.json) |',
        '| RF 支配裁剪 | 实际更新减少 62.7435%，原协议两块 +0.504% / −0.153%；同进程诊断 +0.033% / +0.064%，没有建立提速，不投入新证明。 | [AE](../../evidence/round18/dominance-ae-decision.json)、[AN](../../evidence/round18/noise-an-decision.json) |',
        '| RF 前缀复用 / span / A ring | 输出相同但总压缩时间回退：prefix +0.322% / +0.805%，span +0.890% / +1.444%，ring 约 +9.8%。操作减少和有限等价不等于收益。 | [AG/AH](../../evidence/round18/rf-ag-ah-decision.json)、[X](../../evidence/round18/screen-x-decision.json)、[AK](../../evidence/round18/aring-ak-decision.json) |',
        '| A block8 范围最小值 | 2,400 个真实 DP 差分与 28 文件相同；原协议约慢 27%、预测 0，停止该实现。 | [AW](../../evidence/round18/block-aw-decision.json)、[AX](../../evidence/round18/block-ax-decision.json) |',
        '| 共享匹配 / 强种子 / 模型沿用 | 弱共享损失 1,949 B，保留强种子降到 290 B 但故意重复搜索；额外匹配仅省 136 B。模型沿用也有大小回退，均未证明总时间收益。 | [AJ](../../evidence/round18/shared-aj-decision.json)、[AM](../../evidence/round18/strongseed-am-native-decision.json)、[AY](../../evidence/round18/cache-extra-ay-decision.json) |',
        '| 旧底座组合 | #361 加 RF 质量改善 0.055739 pp，但约慢至原来的 4.1 倍；#579 去高成本阶段快约 15.6%但多 1,025 B，仍 0 份额；#573 short-range 微小变化被对照分歧覆盖。 | [AD](../../evidence/round18/screen-ad-decision.json)、[I](../../evidence/round18/alternatives-h-decision.json)、[R](../../evidence/round18/short-p-decision.json) |',
        '',
        '本轮发现并纠正了预检解释错误：原 gain40 减 24，对实际 `pc_HLIT=80` 是 3.5 bit，并非 2.5 bit。原源码和负面回执未删除；另建减 40 的真实 2.5 bit 候选重新检查。[更正记录](../../evidence/round18/dna-cost-preflight-correction.json)。',
        '',
        '## 替代起点与下一步',
        '',
        '1. **优先研究低成本的真实质量改善。** B 离 5% 的当前坐标缺口已量化；恢复原有 RF 开关的免费组合仍不够。下一次实验应证明新增匹配、成本模型或共享阶段能在所需质量上保住总时间，再付完整证明成本。先做有限语料的原 encoder 字节和阶段归因；不能以少循环次数晋升。',
        '2. **把 DNA 作为保留路线，先解决可辨识性。** 精确 radix6 包和完整证明已留存；若改键计算成本或其他质量机制，先对新点重放邻居切换，再用原协议及同源码对照判断。已有观测不支持仅移动平均速度约 0.1% 就宣布 15% 可支付。',
        '3. **检查新公开 #591 的 SF 家族。** 本轮首次取得其源码时间是 00:13:41 UTC；实际公开释放时间未知。它与旧 #550 的基础引擎路由、候选缓存宽度/深度及编码块边界价格不同。原始来源及作者保留；精确长度条件仍是原作者代码，其私有迁移能力未验证。[来源和差分](../../evidence/round18/new-public-reference-check/receipt.json)、[有界诊断预检](../../evidence/round18/shape-bb-preflight.json)。',
        '',
    ]
    late = E / 'shape-bb-decision.json'
    if late.exists():
        data = read(late)
        text.append(data['report_paragraph'] + ' ' + link('evidence/round18/shape-bb-decision.json', '完整诊断结论'))
    else:
        text.append('这次单独的 25 分钟原生诊断尚在收集；只改变外层为 SFbase 的端点没有本轮完整 Lean gate，不列为第三份可提交成果。最终 A/B 文件保持冻结。')
    text += [
        '',
        '这些是后续最高价值动作，不是已执行实现或新授权；正式上传仍需另行审阅精确文件、当时官方要求、注册归属和额度。',
        '',
        '## 资源、可复核性与工作区',
        '',
        f'截至 {cost["recorded_at_utc"]}，派发 **{cost["dispatched_run_count"]}** 次手动云端运行，收齐 **{cost["collected_completed_run_count"]}** 次；结论 {cost["collected_conclusions"]}。已完成 runner 作业累计 **{int(cost["completed_runner_wall_seconds"])} 秒**（{cost["completed_runner_wall_seconds"] / 3600:.3f} 小时，允许并行，不能当作研究墙钟时间或账单分钟）。原协议筛选/确认共 **{cost["original_screen_confirmation_paired_processes"]}** 个配对进程，另列原生、诊断及完整 gate。',
        '',
        f'账户初始用量 0%，最新已用 {cost["latest_shared_account_observation"]["used_percent"]}%、剩余 {cost["latest_shared_account_observation"]["remaining_percent"]}%；这是共享账户观察，不是本任务费用。成功兑换重置卡 **{cost["successful_resets"]}** 次，没有购买额度；没有达到剩余≤1%的授权触发点。工具不支持指定某张卡，未试兑。实际云端账单和可归属于本任务的模型金额 **UNKNOWN**。{link(rel(args.cost), "逐运行耗时与资源回执")}。',
        '',
        '原始 artifact、所有逐文件 reps、失败、官方响应均保留字节和 SHA-256。审阅 ZIP 仅含 `parse.rs` / `Parse.lean`，不含密钥、钱包、私密配置或正式上传动作。最终审计索引见 [研究状态](../../evidence/round18/research-state.md)。',
        '',
        '官方主分支复核到 `6bf303f14e6c7bccc63e9a557e4ac83e032fa9e8`，比本轮固定 pin `a356bbff18b60c4527fbcc85d5a28ef9c20214e0` 多一个发生在本轮之前的数据库保留/发布变更。SCORING、MINER、pareto 字节与开场相同，contract、encoder、verifier 和工具链未改变；线上实际部署字节身份仍 UNKNOWN。[完整比对](../../evidence/round18/official-code-final-check/receipt.json)。官方 API 旧快照可被清理，本仓库原始捕获不依赖旧 URL 长期可用。',
        '',
        '工作仅位于隔离分支 `codex/round18-frontier`，从 `e000933527c41b9c5881401731d863b9898f571a` 开始。main 上其他任务的 `b5cb035d44ce7da96fe3b309373203bfde369396` 被排除，没有一起推送、合并或删除。最新远端核对与收尾提交见研究状态。',
        '',
        '**VERIFIED**：精确完整公共 gate、原始测量、哈希、公开规则重放和保存的快照。**INFERRED**：族内校准、当前单独/联合几何估算、坐标要求和机制取舍。**UNKNOWN**：正式上传后的 gate/admission、私有语料迁移、当前注册/额度、未来榜单与实际支付。八小时研究交付不能改写为两个奖励目标已完成。',
        '',
    ]
    (ROOT / 'docs/rounds/round18.md').write_bytes(('\n'.join(text)).encode())
    print(json.dumps({'report': 'docs/rounds/round18.md', 'snapshot': snapshot,
                      'window_ended': args.ended, 'reward_targets': 'NOT_ESTABLISHED'}))


if __name__ == '__main__':
    main()
