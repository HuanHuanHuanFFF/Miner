"""Render R25's evidence-based report from a specified official snapshot replay."""
from pathlib import Path
from datetime import datetime, timezone, timedelta
import argparse
import json
import statistics as st
from round10_payability import load_flat_rows

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round25'


def read(path):
    return json.loads(path.read_bytes())


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', required=True, type=Path)
    ap.add_argument('--outcome', required=True, type=Path)
    ap.add_argument('--closed', action='store_true')
    a = ap.parse_args()
    if a.closed:
        budget = read(E / 'budget.json')
        remaining = (datetime.fromisoformat(budget['deadline_utc']) - datetime.now(timezone.utc)).total_seconds()
        assert 0 <= remaining <= 120, 'Only close inside the final two-minute delivery reserve'
    data = read(a.outcome)
    competition, context, rows = load_flat_rows(a.capture)
    assert data['snapshot'] == context
    sid = context['snapshot_id']
    parent = read(E / f'parent-summary-{sid}.json')
    assert parent['snapshot'] == context
    parent_views = {s['calibration']: s for s in parent['summary'] if s['era'] == 'r25_incidental_control'}
    parent_example = {s['calibration']: s for s in parent['same_candidate_same_source_anchor_switch_example']}
    parent_anchors = read(E / f'parent-anchors-{sid}.json')
    assert parent_anchors['snapshot'] == context
    related_parent = next(s for s in parent_anchors['summary'] if s['anchor'] == 'public578')
    capture = read(a.capture / 'receipt.json')
    costs = read(E / 'luna/ci-cost-final.json')
    packages = read(E / 'review-packages/packages.json')
    by_id = {str(r['id']): r for r in rows}
    top = max(rows, key=lambda r: (r.get('score') or {}).get('payable_weight') or 0)
    measured = {c['rust_sha256']: c for c in data['candidates']}
    descriptions = {
        'r25-astra-end4': '末端完整四字节索引',
        'r25-astra-gap1': '补一处未覆盖位置',
        'r25-sol-backtie': '反向合并同长择距',
        'r25-root-tail4': '尾键替换 T',
        'r25-astra-tiny-tail': '短文件余数修补',
        'r25-astra-dual8': '四／八字节双头',
        'r25-sol-end4-wordtail': '同字节 wordtail',
        'r25-astra-dual8-mainonly': '双头只留主插入 H',
        'r25-astra-tiny-pc8-proof1': '短文件 PC I',
        'r25-sol-duplicate-hop': '重复前缀有条件多看一跳 J',
        'r25-astra-tiny-pc-sparse-proof1': '稀疏发射 M',
        'r25-root-end4-budget': '等记录次数交换 N',
    }
    selected = {}
    for s in data['source_pairs']:
        if Path(s['path']).name in descriptions:
            selected[s['files']['parse.rs']] = s
    assert len(selected) == 12
    combo = next(r for s in data['source_pairs'] for r in s['native_quality_observations']
                 if r['parent'] == 'combo')
    base_bytes = combo['total_bytes'] - combo['delta_bytes_vs_parent']
    base_quality = combo['public_size_pct'] - combo['delta_balanced_pp_vs_parent']
    table = []
    for h, source in selected.items():
        name = Path(source['path']).name
        native = source['native_quality_observations'][0]
        db = native['total_bytes'] - base_bytes
        dq = native['public_size_pct'] - base_quality
        if h in measured:
            mains = [o for o in measured[h]['observations']
                     if o['entry_role'] == 'candidate' and o['calibration'] == 'primary']
            times = [o['time_change_pct_vs_parent'] for o in mains]
            values = [o['single_pool_share_pct'] for o in mains]
            timing = f'{min(times):+.3f}%～{max(times):+.3f}%'
            shares = f'{min(values):.6f} / {st.median(values):.6f} / {max(values):.6f}%'
            zeros = f'{sum(v == 0 for v in values)}/{len(values)}'
        else:
            timing = shares = zeros = 'UNKNOWN（未计时）'
        proof = '完整 gate 通过' if source['proof_status'] == 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED' else '未完整验收'
        table.append(f'| [{descriptions[name]}](../../{source["path"]}) | {db:+,} B / {dq:+.6f} pp | {timing} | {shares} | {zeros} | {proof} |')
    phase = '研究窗口结束，稳定榜首目标未完成' if a.closed else '确认已收齐，交付核验中；稳定榜首目标未完成'
    start_bjt = '2026-10-11 16:06:21'
    end_bjt = '2026-10-11 21:06:21'
    cap_rel = a.capture.relative_to(ROOT) if a.capture.is_absolute() else a.capture
    outcome_rel = a.outcome.relative_to(ROOT) if a.outcome.is_absolute() else a.outcome
    text = f'''# 第二十五轮：五小时快速端低成本压缩研究

北京时间 **{start_bjt}–{end_bjt}**。状态：**{phase}**。本轮实现12种不同Rust，完成34个手动作业（30成功、4失败）、180个原协议配对进程；两份精确Rust／Lean通过完整原版gate，并各完成2个新runner、4个主确认块。按快照 **{sid}** 重算，这两份的独立确认份额最低／中位／最高均为 **0%**，联合加入也均为0。未取得稳定正份额，更未取得榜首。

本轮保留的是两个已验证正确性的质量组件，不是建议立即提交的收益候选。全部份额为公共测量迁移到正式坐标后的条件估算；正式admission、私有结果和可支付收益为 **UNKNOWN**。没有正式上传、注册、签名或资金操作。

执行规则见 [AGENTS.md](../../AGENTS.md)。[固定预算](../../evidence/round25/budget.json)、[逐块汇总](../../{outcome_rel.as_posix()})、[原始证据审计](../../evidence/round25/git-byte-audit-checkpoint.json)、[阶段决策](../../evidence/round25/feedback-nt-confirmation-decision.json)保留完整边界。

## 最新官方依据与目标缺口

[完整官方捕获](../../{cap_rel.as_posix()}/receipt.json)：快照{sid}，官方计算UTC `{context['computed_at']}`；查询UTC `{capture['retrieval_start_utc']}` 至 `{capture['retrieval_end_utc']}`。官方freshness为`{context['freshness']}`，不能冒称实时私有验证器状态已知。政策为`{context['policy_version']}`，pool内Pareto权重1、improvement权重0；竞赛占验证者总权重的20%不是本报告份额的分母。

当前捕获可支付榜首为 **#{top['id']}，{100 * top['score']['payable_weight']:.6f}%**。它的正式坐标是时间比 `{top['metrics']['balanced_time_ratio']:.10f}`、平均压缩比例 `{top['metrics']['mean_file_compression_pct']:.10f}%`。本轮先后捕获626、627与628的竞争变化，旧快照值独立保留，不沿用旧高份额。原scorer与该快照权重的重放误差见机器分析；源码捕获与部署身份是两个问题。

[独立代数复算](../../evidence/round25/score-algebra-{sid}.json)从前沿扫描、局部／全局系数、增量对数轴预算和统一归一化重新计算，不调用原scorer实现。128个单独观测视图及56组对齐联合案例与原重放一致；这些视图包含校准和控制，不能当独立样本数。

逆向网格用于判断投入空间：[晚期几何及坐标纠正](../../evidence/round25/luna/late-target-note.md)。在其明示的29690快照中，平均压缩比例36.5%的取样榜首速度区间只有0.42860–0.43045；降到35.5%时取样区间才扩展到0.42860–0.43750。它既不是连续边界，也不是实现成绩。最终保留版投影大小约36.519%和36.452%，且新确认速度仍落在这些区域之外。不能把原始public坐标直接与正式前沿比较，也不能把极窄窗口当稳定收益。

## 12种实现的真实结果

质量统一相对combo `r22-595-chain-halfhead`（公共输出{base_bytes:,}B、平均压缩比例{base_quality:.9f}%）。时间列相对各批**实际父版本**：wordtail／N对end4，H对dual8，M对I，其余对combo。份额列只统计声明主候选、595主校准；发现与确认合并展示范围，但两类的逐块统计分列于机器汇总。副本与校准视图不增加样本。

| 实现 | 相对combo字节／均衡质量差 | 原协议总时间相对实际父版 | 主份额最低／中位／最高 | 主块零值 | 完整验收 |
|---|---:|---:|---:|---:|---|
''' + '\n'.join(table) + f'''

所有主块的严格榜首次数、达到10%／15%次数均为0。I在发现期的微小正值未在4个新确认主块中复现；后续同源码控制的正值、零值及与影子校准的分歧仍保留在[全部观测](../../{outcome_rel.as_posix()})，没有因为角色不同而删除。未计时的tiny-tail不赋零分；M的新证明草稿虽已对照实际提取接口迁移，仍未运行完整gate。

H比dual8快，但仍比combo慢1.120%–1.155%；M比I快，却仍比combo慢0.467%–0.723%；N保持记录次数但比combo慢0.943%–1.031%。这些结果不能用“比自己的较慢父版本快”宣传成总体收益。T的同源码副本曾比combo快0.169%，另一块又慢0.080%；原主测更慢，所有校准下都没有份额，保留为测量分歧而不挑选副本。

### 旧快速父版仍需保留，但峰值不代表稳定

旧父版`r22-595-chain-halfhead`在本轮9个runner的18个块中作为对照测量。[按同一当前快照的补充重放](../../evidence/round25/parent-summary-{sid}.json)给出：595主校准最低{parent_views['primary']['minimum_pct']:.6f}%、中位{parent_views['primary']['median_pct']:.6f}%、最高{parent_views['primary']['maximum_pct']:.6f}%，零值{parent_views['primary']['zero_count']}/18，严格第一{parent_views['primary']['strict_first_count']}/18；影子校准最高{parent_views['shadow']['maximum_pct']:.6f}%，中位{parent_views['shadow']['median_pct']:.6f}%，零值{parent_views['shadow']['zero_count']}/18，严格第一{parent_views['shadow']['strict_first_count']}/18。它保留了高潜力线索，但没有稳定性证据。这18块是既有对照记录的重算，不是额外新增的独立确认作业。

例如HI运行38130275592的块1，同一父版测量只换595同源码参照，预测从{parent_example['primary']['share_pct']:.6f}%变为{parent_example['shadow']['share_pct']:.6f}%。[独立公式及邻居项](../../evidence/round25/parent-algebra-{sid}.json)保留前沿切换与归一化；原候选测量没有改变。旧R23四块冻结确认也按新快照重放并单列，未计入本轮180配对进程；保留该父版作为替代起点，不选峰值代替本轮目标。

另有4个runner具备同块578相关父族参照：[额外校准视图](../../evidence/round25/parent-anchors-{sid}.json)共8块，最低{related_parent['minimum_pct']:.6f}%、中位{related_parent['median_pct']:.6f}%、最高{related_parent['maximum_pct']:.6f}%，零值{related_parent['zeros']}/8。它复用既有候选测量，不新增样本；不按哪个参照报酬高来选校准。

## 冻结后独立确认与联合估算

精确pair于UTC `2026-10-11T11:12:41.401932+00:00`冻结；原三次作业因缺失已提交快照依赖，在计时前失败，修复后使用相同源码和协议重跑。成功作业为[38135739022](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/38135739022)和[38135751559](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/38135751559)，每个runner各2主块，原版每文件1预热／11测量，逐文件总时间与配对incumbent全部保留。

| 独立运行 | 环境 | end4相对combo总时间，块1／2 | tinyPC相对combo总时间，块1／2 | 各自单独／两者联合份额 |
|---|---|---:|---:|---|
| 38135739022 | AMD EPYC 7763；governor未报告 | +1.240% / +0.995% | +2.075% / +2.214% | 每块两者均0%／0% |
| 38135751559 | Intel Xeon 6973P-C；performance | +1.143% / +1.294% | +1.638% / +2.845% | 每块两者均0%／0% |

两个候选各4主块：最低0%、中位0%、最高0%、零值4次、严格第一0次。595影子校准、578相关父族校准以及候选同源码副本也均为0。联合估算按同一runner／块／校准重新加入前沿及归一化，未直接相加独立估算。[独立pair审计](../../evidence/round25/astra/final-pair-audit.md)核对了44份JSONL，Rust／Lean、source hash、记录的binary hash和全部token／output身份一致。

同源码与环境分歧仍存在。确认阶段595对照间相对时间差为-0.319%～+0.362%；end4副本为-0.500%～+0.028%，tinyPC副本为-0.821%～+0.426%。这些是观测范围，不是误差保证。请求cpus=0与host affinity=[0,1,2,3]均保留；sandbox子进程实际mask未独立验出。不同runner不混成一个独立样本，样本零值次数不解释为未来归零概率。

## 两个保留包的正确性与身份

'''
    for p in packages['packages']:
        cert = read(ROOT / p['source_path'] / 'VERIFICATION.json')
        text += f'''- **{p['candidate']}**：Rust SHA-256 `{p['files']['parse.rs']}`；Lean SHA-256 `{p['files']['Parse.lean']}`。原gate `{p['gate_run_id']}`，验证{cert['gate_seconds']}秒。[两文件ZIP](../../{p['archive']})，ZIP SHA-256 `{p['archive_sha256']}`。
'''
    text += f'''
两份均使用官方重新提取、原LZ77 obligation、原900秒Lean限制、三允许公理与公共round trip。原pins／encoder／contract未修改；临时观察副本与正式计时分开。gate本身没有性能确认块，其smoke时间不计入正式两轴成绩。二进制实物和gate score逐文件JSONL未归档；后续确认已保留完整逐文件测量。私有stage2未运行，不能由完整公共gate推断正式通过。

## 实验如何改变路线

1. **额外索引有质量收益，但成本必须实测。** end4保留7397B；双头dual8省14674B，却慢约3%。E/F将额外哈希／写入分成主插入与匹配内记录；后者贡献53017次有效提示，删除后真实多17230B，不能把大量记录都视为冗余。[诊断E](../../evidence/round25/38127500920/counts-e-native/diagnostics/r25-dual8-counts/counts.json)、[F](../../evidence/round25/38128787484/origins-f-native/diagnostics/r25-dual8-origins/counts.json)。
2. **只读机会计数不能直接兑换字节或份额。** G暴露短匹配重复前缀机会，也发现长匹配依赖同前缀链；J只做一跳受控改变，12目标文件更小，却没有总耗时收益。停止这个实现，保留真实覆盖与负结果。[G](../../evidence/round25/38129145575/prefix-g-native/diagnostics/r25-prefix-diversity-counts/counts.json)、[J](../../evidence/round25/feedback-j-native.json)。
3. **更少token也可能让原encoder更慢。** I的tiny-config从2487降到2155B，token从3094降到2276；两个流仍各一个dynamic block。长度活码从5增至27、距离活码7增至23，部分树复制和查表工作上升。新确认中，该文件编码额外时间对总评分轴的描述性贡献仍为+1.497～+1.949个百分点。解析、编码和独立配对分母分别核对，未用分解替换原成绩。[K原观察](../../evidence/round25/38132193695/counts-k2-native/diagnostics/r25-tiny-encoder/receipt.json)、[新确认A分解](../../evidence/round25/cost-confirm-a-vs-combo.json)、[B分解](../../evidence/round25/cost-confirm-b-vs-combo.json)。
4. **固定稀疏发射确实降低代价，但损失了大部分质量。** M将编码成本大幅压回，最终只比combo省46B；对I的速度改善不等于可支付位置。离线改写I最终token得到3010个token，真实M为2954，说明发射会改变future fold轨迹；不能用终态重写替代真实parser。[M决定](../../evidence/round25/feedback-m-decision.json)、[反例](../../evidence/round25/sparse-offline-replay.json)。
5. **真实调用路由与混合正负覆盖决定是否开实现。** L在84个原编码组合核验后发现，PC路径三字节匹配局部亏损仅627bit，所有距离码均有获益反例；bfraw／EF32亏损不归给PC，缺失literal码保留未知。不重开无证据的距离阈值扫。[L反馈](../../evidence/round25/sol/len3-price-feedback.json)。R13已有同族AoS双头表示的直接实验，因此停止重复实现；也撤回public584调用路由的早期静态误判。[历史起点审计](../../evidence/round25/sol/packed-head-preaudit.md)。
6. **保留公共语料外的反例。** O用预先固定生成器、3结构族、两种有效路由长度和4种seed，另加3个不进入修改路径的控制。27输入、81次原编码与Rust/zlib解码均通过。tinyPC的12个active样本都更小，差额-1272～-828B、中位-1015B；end4为3小／4同体积／5大，-25～+103B、中位0。4个同体积中只有3个token／output完全相同。相同seed的长短样本共享前缀，不是24次独立抽样；本诊断没有时间或官方份额。[固定输入与独立审计](../../evidence/round25/sol/heldout-quality-feedback.md)。

## 失败、资源与交付边界

四个CI失败全部保留：K首轮依赖本机未跟踪的sources阅读副本；另外三轮漏提交评分快照，在540有限decode后、原计时前失败。修复分别加严准备后身份核验和派发前Git树内依赖字节核验；旧失败不覆盖，不计性能样本。[回归复现](../../evidence/round25/snapshot-dependency-repair-check.json)。报告阶段也更正了原始public坐标／正式投影坐标混用，以及旧CI检查点派生UTC端点误减8小时；原始回执均未改写。

[实际CI消耗](../../evidence/round25/luna/ci-cost-final.md)：{costs['totals']['runner_cumulative_minutes']:.2f} runner分钟，排队累计{costs['totals']['queue_minutes_sum']:.2f}分钟；计入setup／checkout，剔除所有skipped job，失败作业计入消耗。它们是并发作业之和，不等于5小时研究墙钟或现金账单。账户共享用量单独记录；未重置、未购买，任务独占token／金额成本UNKNOWN。

用户授权最多4子线程，工具实际支持root加3子线程，因此使用Astra/xhigh、Sol/xhigh、Luna/max三个角色并行，根线程负责CI、Git和最终复核；无嵌套、无额外worktree。起点main／origin/main均为`48baf622466792f4d505c5c06d5696f784e27b7a`；成果留在`codex/round25-fast-quality`，不自动合并或清分支。普通提交跳过CI。

**VERIFIED**：公共真实字节、原协议逐文件计时、两个精确完整gate、跨runner独立确认与原回执哈希。**INFERRED**：快照{sid}下的单独／联合份额以及机制投入判断。**UNKNOWN**：未测实现的速度、私有迁移、正式准入／奖励、任务独占现金成本。

下一轮优先判别如何在匹配接受阶段保留短文件质量、减少新增长度／距离符号集合的编码成本；其次考察带真实收益归因的稀疏索引记录。先测最小质量／成本端点，避免继续扫掩码、盲加搜索或重跑已失败的相同实现。具体判别实验和停止条件见[后续路线评估](../../evidence/round25/sol/next-route-assessment.md)。本轮经验已汇入[优化方法与实验结论](../research/optimization-methods.md)；历史正式提交及累计α另见根目录[看板](../../DASHBOARD.md)。
'''
    (ROOT / 'docs/rounds/round25.md').write_text(text, encoding='utf-8')
    decision = ('窗口结束' if a.closed else '核验收尾中') + f'，稳定榜首未完成；12种Rust／34作业／180原协议配对，两份完整gate及各2runner四主块确认；快照{sid}独立确认单独及联合均0，无正式上传。'
    index_path = ROOT / 'docs/TASK_INDEX.md'
    index_lines = index_path.read_text(encoding='utf-8').splitlines()
    matches = [i for i, line in enumerate(index_lines) if line.startswith('| round25 |')]
    assert len(matches) == 1
    index_lines[matches[0]] = f'| round25 | [第二十五轮：五小时快速端压缩研究](rounds/round25.md) | {decision} |'
    index_path.write_text('\n'.join(index_lines) + '\n', encoding='utf-8')
    tasks_path = ROOT / 'docs/tasks.json'
    tasks = read(tasks_path)
    next(t for t in tasks['tasks'] if t['id'] == 'round25')['decision'] = decision
    tasks['updated_on'] = '2026-10-11'
    tasks_path.write_text(json.dumps(tasks, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'report': 'docs/rounds/round25.md', 'snapshot': sid,
                      'source_variants': len(selected), 'closed': a.closed}, ensure_ascii=False))


if __name__ == '__main__':
    main()
