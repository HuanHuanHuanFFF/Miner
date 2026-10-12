"""Summarize already-collected R26 evidence without measuring or selecting peaks."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'evidence/round26'


def read(path):
    return json.loads(path.read_bytes())


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def rel(path):
    return path.resolve().relative_to(ROOT).as_posix()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ('analysis', 'roles', 'ledger', 'audit', 'output'):
        ap.add_argument('--' + name, type=Path, required=True)
    args = ap.parse_args()
    assert not args.output.exists(), 'Preserve earlier summaries; use a fresh output filename'
    data, roles, ledger, audit = [read(getattr(args, k)) for k in ('analysis', 'roles', 'ledger', 'audit')]
    assert data['snapshot'] == roles['snapshot'] == ledger['projection_snapshot']
    for path, expected in ledger['inputs'].items():
        assert sha(ROOT / path) == expected, path
    assert sha(args.analysis) in roles['inputs'].values()
    budget_path = BASE / 'extension4h/budget.json'
    budget = read(budget_path)
    old = read(BASE / 'candidate-ledger-29864.json')
    old_rust = {s['rust_sha256'] for s in old['sources']}
    new_rust = {s['rust_sha256'] for s in ledger['sources']} - old_rust
    selected_runs = []
    for run in audit['runs']:
        dispatch = read(ROOT / run['dispatch'])
        if dispatch.get('budget_path') == rel(budget_path):
            assert dispatch['budget_sha256'] == sha(budget_path)
            assert datetime.fromisoformat(budget['start_utc']) <= datetime.fromisoformat(dispatch['dispatch_utc']) < datetime.fromisoformat(budget['deadline_utc'])
            selected_runs.append(run)
    extension_ids = {r['run_id'] for r in selected_runs}
    main = [s for s in roles['summaries'] if s['entry_role'] == 'candidate' and s['calibration'] == 'primary']
    new_main = [s for s in main if s['rust_sha256'] in new_rust]
    by_role = {(s['rust_sha256'], s['entry_role'], s['calibration']): s for s in roles['summaries']}
    assert len(main) == len({s['rust_sha256'] for s in main})
    assert all(s['role'] == 'discovery' for s in main), 'Update summary policy if confirmed candidates exist'
    # Source/Lean proof declarations are not acceptance certificates.
    assert all(p['exact_gate'] == 'NOT_RUN' for s in ledger['sources'] for p in s['packages']), 'Do not hard-code missing gates after a real acceptance'
    assert all(s['independent_confirmation'] == 'NOT_RUN' for s in ledger['sources'])
    snapshot = data['snapshot']['snapshot_id']
    out = {
        'status': 'VERIFIED_RETAINED_RESULTS_WITH_CONDITIONAL_PUBLIC_PROJECTIONS_TARGETS_UNMET',
        'generated_utc': datetime.now(timezone.utc).isoformat(),
        'fixed_window': budget,
        'snapshot': data['snapshot'],
        'inputs': {rel(p): sha(p) for p in [args.analysis, args.roles, args.ledger, args.audit, budget_path, BASE / 'candidate-ledger-29864.json']},
        'extension': {
            'distinct_new_rust': len(new_rust),
            'original_protocol_main_candidates': len(new_main),
            'unmeasured_new_rust': len(new_rust) - len(new_main),
            'main_blocks': sum(s['observations'] for s in new_main),
            'main_zero_blocks': sum(s['zero_count'] for s in new_main),
            'main_target5_blocks': sum(s['at_least_5_count'] for s in new_main),
            'main_target10_blocks': sum(s['at_least_10_count'] for s in new_main),
            'ci_runs': len(selected_runs),
            'ci_conclusions': dict(Counter(r['conclusion'] for r in selected_runs)),
            'ci_modes': dict(Counter(r['mode'] for r in selected_runs)),
            'recorded_runner_seconds': sum(r['recorded_runner_seconds'] for r in selected_runs),
            'original_paired_processes': sum(r['paired_processes'] for r in data['runs'] if r['run_id'] in extension_ids),
            'runs': selected_runs,
        },
        'whole_round': {
            'distinct_rust': ledger['distinct_rust_count'],
            'original_protocol_main_candidates': len(main),
            'unmeasured_rust': ledger['distinct_rust_count'] - len(main),
            'original_paired_processes': data['paired_processes'],
            'main_blocks': sum(s['observations'] for s in main),
            'main_zero_blocks': sum(s['zero_count'] for s in main),
            'main_target5_blocks': sum(s['at_least_5_count'] for s in main),
            'main_target10_blocks': sum(s['at_least_10_count'] for s in main),
            'ci_runs': audit['run_count'], 'ci_conclusions': audit['ci_conclusions'],
        },
        'exact_full_gates': 0, 'frozen_independent_confirmation_blocks': 0,
        'recommended_submission_packages': [],
        'conditional_main_summaries': main,
        'joint_on_matching_run_block_calibration': [j for j in data['joint'] if j['matched_observations']],
        'limits': [
            'This is a snapshot-specific evidence summary, not a declaration that the fixed window has ended.',
            'Each measured main candidate has discovery observations only. Copies and calibration views are not extra independent confirmations.',
            'Unmeasured share is UNKNOWN. Public projection is conditional on calibration, admission and eligible independent identities, not formal reward.',
            'Observed target counts are not success probabilities; coordinate averages are not expected reward.',
            'Job wall time excludes an exact billing interpretation; account usage is shared and reported separately.',
            'No formal upload, registration, wallet signing, purchase, merge or deletion is performed by this script.',
        ],
    }
    args.output.write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
    lines = [f'# R26 候选对比：快照 {snapshot}', '',
        f'生成UTC {out["generated_utc"]}；官方计算 {data["snapshot"]["computed_at"]}，freshness={data["snapshot"]["freshness"]}。', '',
        '以下份额均为条件公共估算，未获得本轮正式准入或支付结果。主候选与同源码副本、主参照与影子参照分列；每个已计时主候选仅一runner两发现块，没有冻结后独立确认或完整公共gate。', '',
        f'追加阶段新增{len(new_rust)}份不同Rust，{len(new_main)}份已做原协议总时间，{len(new_rust)-len(new_main)}份未计时。全R26共{ledger["distinct_rust_count"]}份Rust，{len(main)}份已计时。', '',
        '## 原协议主候选', '',
        '负时间变化表示比实际父版更快；两块顺序保留，不按峰值挑选。份额的最低／中位／最高均按块计算，不能解释为正式成功概率。', '',
        '| 候选 | 追加 | 两块时间变化 | 主参照最低／中位／最高 | 零／总块 | ≥5%／≥10%块 | 影子参照最低／中位／最高 |',
        '|---|---|---|---|---|---|---|']
    def stats(s):
        return '／'.join(f'{s[k]:.6f}%' for k in ('minimum_pct', 'median_pct', 'maximum_pct'))
    for s in main:
        source = next(r for r in ledger['sources'] if r['rust_sha256'] == s['rust_sha256'])
        path = Path(source['packages'][0]['path']).as_posix()
        shadow = by_role[(s['rust_sha256'], 'candidate', 'shadow')]
        times = '／'.join(f'{b["time_change_pct_vs_parent"]:+.6f}%' for b in s['blocks'])
        lines.append(f'| [{Path(path).name}](../../../{path}) | {"是" if s["rust_sha256"] in new_rust else "原窗"} | {times} | {stats(s)} | {s["zero_count"]}/{s["observations"]} | {s["at_least_5_count"]}／{s["at_least_10_count"]} | {stats(shadow)} |')
    lines += ['', '## 未计时版本', '', '| 候选 | 追加 | 原编码证据 | 份额 |', '|---|---|---|---|']
    for source in ledger['sources']:
        if source['original_protocol_main_observations']:
            continue
        p = Path(source['packages'][0]['path']).as_posix()
        quality = source['native_quality']
        q = '；'.join(f'{v["output_bytes"]}B，质量轴{v["public_size_pct"]:.8f}%' for v in quality) or '该台账无原编码汇总；见原始阶段回执'
        lines.append(f'| [{Path(p).name}](../../../{p}) | {"是" if source["rust_sha256"] in new_rust else "原窗"} | {q} | UNKNOWN |')
    lines += ['', '## 联合加入', '',
        '仅下表组合有匹配run／块／校准记录，每次加入两点后重新计算前沿和归一化；其中带控制角色的点只是同场辅助观测。其他组合缺少共同测量，未把独立份额相加。', '',
        '| 组合／run／块／参照 | 实际角色 | 分别加入 | 同时加入 |', '|---|---|---|---|']
    for j in out['joint_on_matching_run_block_calibration']:
        for row in j['matched_observations']:
            names = j['candidates']
            choices = '／'.join(row['selected_entries'][n]['role'] for n in names)
            fmt = lambda key: '／'.join(f'{row[key][n]:.6f}%' for n in names)
            lines.append(f'| {" + ".join(names)}；{row["run_id"]}；{row["block"]}；{row["calibration"]} | {choices} | {fmt("separate_pct")} | {fmt("simultaneous_geometric_pct")} |')
    lines += ['', '## 精确文件身份', '',
        '下面Lean只是实际保留文件，不表示已适配或通过gate。详细声明、原始数据路径、逐文件总时间与对照见同目录机器台账、角色统计及原始分析。', '',
        '| 候选 | Rust SHA-256 | Lean SHA-256 |', '|---|---|---|']
    for s in ledger['sources']:
        for p in s['packages']:
            lines.append(f'| {Path(p["path"]).name} | `{p["files"]["parse.rs"]}` | `{p["files"]["Parse.lean"]}` |')
    lines += ['', f'依据：[{args.analysis.name}]({args.analysis.name})、[{args.roles.name}]({args.roles.name})、[{args.ledger.name}]({args.ledger.name})、[{args.audit.name}]({args.audit.name})。']
    report = args.output.with_suffix('.md')
    assert not report.exists()
    report.write_text('\n'.join(lines) + '\n', encoding='utf-8')
    print(json.dumps({'snapshot': snapshot, 'extension': {k: v for k, v in out['extension'].items() if k != 'runs'}, 'whole_round': out['whole_round'], 'report': rel(report)}, ensure_ascii=False))


if __name__ == '__main__':
    main()
