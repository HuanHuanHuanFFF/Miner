"""Close the bounded R25 window in its final delivery reserve, preserving unmet targets."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round25'


def read(path):
    return json.loads(path.read_bytes())


def save(path, value):
    path.write_bytes((json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode())


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ('capture', 'outcome', 'dashboard', 'latest-check', 'git-audit', 'geometry'):
        ap.add_argument('--' + name, type=Path, required=True)
    a = ap.parse_args()
    now = datetime.now(timezone.utc)
    budget = read(E / 'budget.json')
    remaining = (datetime.fromisoformat(budget['deadline_utc']) - now).total_seconds()
    assert 0 <= remaining <= 120, 'Only close in the final two-minute delivery reserve'
    assert not (E / 'closure.json').exists()
    outcome, dashboard, latest, audit = [read(p) for p in
                                        (a.outcome, a.dashboard, a.latest_check, a.git_audit)]
    sid = str(outcome['snapshot']['snapshot_id'])
    assert str(dashboard['context']['snapshot_id']) == sid
    assert latest['latest_snapshot_matches'] and latest['policy_matches']
    assert str(latest['current_snapshot_id']) == sid
    assert (now - datetime.fromisoformat(latest['request_end_utc'])).total_seconds() <= 600
    assert audit['committed_bytes']['status'] == 'VERIFIED_EXACT_COMMITTED_BYTES'
    assert audit['run_count'] == 34 and audit['ci_conclusions'] == {'success': 30, 'failure': 4}
    assert outcome['original_paired_processes'] == 180 and outcome['distinct_rust_count'] == 12
    assert not outcome['stable_first_established'] and not outcome['formal_submission_sent']
    for package in read(E / 'review-packages/packages.json')['packages']:
        for name, digest in package['files'].items():
            assert hashlib.sha256((ROOT / package['source_path'] / name).read_bytes()).hexdigest() == digest
    subprocess.run([sys.executable, str(ROOT / 'scripts/write-round25-report.py'),
                    '--capture', str(a.capture), '--outcome', str(a.outcome),
                    '--audit', str(a.git_audit), '--geometry', str(a.geometry), '--closed'],
                   cwd=ROOT, check=True)
    costs = read(E / 'luna/ci-cost-final.json')
    head = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip()
    closure = {'status': 'RESEARCH_WINDOW_CLOSED_STABLE_FIRST_UNMET',
               'research_closed_utc': now.isoformat(), 'fixed_start_utc': budget['start_utc'],
               'fixed_deadline_utc': budget['deadline_utc'],
               'elapsed_before_final_delivery_minutes': (now - datetime.fromisoformat(budget['start_utc'])).total_seconds() / 60,
               'remaining_delivery_seconds': remaining, 'stable_first_achieved': False,
               'snapshot_id': sid, 'outcome': a.outcome.as_posix(),
               'dashboard_summary': a.dashboard.as_posix(), 'latest_official_check': a.latest_check.as_posix(),
               'source_packages': 'evidence/round25/review-packages/packages.json',
               'git_byte_audit': a.git_audit.as_posix(), 'evidence_git_sha_before_close': head,
               'distinct_rust_count': 12, 'original_paired_processes': 180,
               'ci_runs': 34, 'ci_success': 30, 'ci_failure': 4,
               'runner_minutes': costs['totals']['runner_cumulative_minutes'],
               'queue_minutes': costs['totals']['queue_minutes_sum'],
               'formal_uploads': 0, 'registration_or_signing_actions': 0,
               'resets_redeemed': 0, 'purchases': 0, 'formal_payable_result': 'UNKNOWN_NOT_SUBMITTED',
               'stop_reason': 'Fixed five-hour budget reached its final delivery reserve. No new implementation, CI or research; only final checks, commit, push and report remain inside the original deadline.'}
    save(E / 'closure.json', closure)
    budget.update(status='RESEARCH_CLOSED_STABLE_FIRST_UNMET', research_closed_utc=now.isoformat(),
                  closure='evidence/round25/closure.json')
    save(E / 'budget.json', budget)
    state = f'''# R25 终态

固定北京时间窗口2026-10-11 16:06:21–21:06:21。研究窗口已进入最后交付阶段，**稳定榜首未完成**；截止时间未延长。12种Rust、34个CI全部收齐（30成功、4失败），180原协议配对；实际runner201.25分钟、排队1.90分钟。无活动CI、无下一批待派发，继续新研究需用户新预算。

最终保留end4(03ec0aa4/4ff09d16)与tinyPC proof1(5c20b99c/3bd53694)两个精确完整原gate组件，source-only ZIP在review-packages/packages.json。各2runner四个新主确认块；最新快照{sid}下595主/影子/578校准全部0，联合也0。正确性和质量收益不能当稳定奖励，正式admission/私有/可支付份额UNKNOWN，未正式上传、注册、签名或购买。

旧父版combo仍有本轮对照高峰，但大量零值且同源码参照可将高峰变微小值；parent-summary-{sid}.json与parent-anchors-{sid}.json分列历史和本轮incidental controls，不加入新候选确认次数。M证明仍DRAFT；tiny-tail未计时；其他负结果与失败均保留。

报告docs/rounds/round25.md、optimization-methods.md、DASHBOARD.md与任务索引已更新。完整机器结论{a.outcome.as_posix()}；最后官方身份检查{a.latest_check.as_posix()}；Git原字节核验{a.git_audit.as_posix()}。看板使用同一快照，注册净收益为公开池价折算，非钱包到账，未扣模型CI。

一个工作树，研究分支codex/round25-fast-quality；main基线48baf622保持不变，不自动merge/清分支。最新证据基准提交{head}；closure之后仅有最后状态/核验/报告提交，最终push SHA从Git读取。无重置/购买，真实共享账户读数单列usage-final.json，独占模型成本UNKNOWN。

下轮最高价值的两条未实现机制与停止条件见sol/next-route-assessment.md；用强匹配覆盖与原encoder符号集合成本作区分，避免掩码盲扫、重开AoS或宽泛len3阈值。原始回执字节保留，阶段记录可从Git历史追溯。研究goal完成只指限定窗口执行与诚实交付，不表示榜首目标已达成。
'''
    (E / 'research-state.md').write_bytes(state.encode())
    print(json.dumps({k: closure[k] for k in ('status', 'research_closed_utc',
                      'remaining_delivery_seconds', 'snapshot_id', 'stable_first_achieved')}, ensure_ascii=False))


if __name__ == '__main__':
    main()
