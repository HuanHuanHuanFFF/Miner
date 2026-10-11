"""Close R24 research inside its final delivery reserve without marking unmet targets achieved."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, subprocess

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'


def read(p):
    return json.loads(p.read_bytes())


def save(p, d):
    p.write_bytes((json.dumps(d, ensure_ascii=False, indent=2) + '\n').encode())


def main():
    now = datetime.now(timezone.utc)
    budget = read(E / 'budget.json')
    deadline = datetime.fromisoformat(budget['deadline_utc'])
    remaining = (deadline - now).total_seconds()
    assert 0 <= remaining <= 120, 'Only close in the final two-minute delivery reserve'
    assert not (E / 'closure.json').exists()
    check = read(E / 'official-last-check/receipt.json')
    assert check['latest_snapshot_matches'] and check['policy_matches']
    sid = str(check['current_snapshot_id'])
    summary = read(E / f'confirmation-{sid}/summary.json')
    assert str(summary['snapshot']['snapshot_id']) == sid
    assert not summary['public_target_pair_established_over_observed_scope']
    plan = read(E / 'confirm-final-plan.json')
    for name, pair in plan['files'].items():
        for filename, digest in pair.items():
            assert hashlib.sha256((ROOT / 'candidates' / name / filename).read_bytes()).hexdigest() == digest
        cert = read(ROOT / 'candidates' / name / 'VERIFICATION.json')
        assert cert['files'] == pair and cert['status'] == 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
    audit = read(E / 'audit-delivery.json')
    assert not audit['uncollected_or_unfinished']
    primary_head = subprocess.check_output(['git', '-C', 'D:/CodingProject/Bitget', 'rev-parse', 'HEAD'], text=True).strip()
    primary_status = subprocess.check_output(['git', '-C', 'D:/CodingProject/Bitget', 'status', '--porcelain'], text=True)
    closure = {'status': 'RESEARCH_WINDOW_CLOSED_TARGETS_UNMET_DELIVERY_RESERVED', 'research_closed_utc': now.isoformat(), 'fixed_start_utc': budget['start_utc'], 'fixed_deadline_utc': budget['deadline_utc'], 'elapsed_before_final_delivery_minutes': (now - datetime.fromisoformat(budget['start_utc'])).total_seconds() / 60, 'remaining_delivery_seconds': remaining, 'goal_achieved': False, 'public_stable_targets': 'UNMET', 'formal_objective': 'UNKNOWN_NOT_SUBMITTED', 'latest_snapshot_id': sid, 'final_snapshot_check': 'evidence/round24/official-last-check/receipt.json', 'confirmation': f'evidence/round24/confirmation-{sid}/summary.json', 'exact_pairs': plan['files'], 'package_manifest': 'evidence/round24/review-packages/packages.json', 'evidence_git_sha': subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip(), 'raw_audit': 'evidence/round24/audit-delivery.json', 'committed_byte_audit': 'evidence/round24/git-byte-audit-delivery.json', 'dispatches': audit['dispatch_count'], 'original_paired_processes': audit['original_paired_processes'], 'runner_minutes': audit['runner_minutes'], 'primary_head': primary_head, 'primary_status_porcelain': primary_status, 'successful_resets': 0, 'purchases': 0, 'formal_uploads': 0, 'stop_reason': 'Fixed research budget reached final delivery reserve. No further implementation, CI or research is started; only final verification/commit/push/report remains within the original deadline.'}
    save(E / 'closure.json', closure)
    budget['status'] = 'RESEARCH_CLOSED_TARGETS_UNMET'
    budget['research_closed_utc'] = now.isoformat()
    budget['closure'] = 'evidence/round24/closure.json'
    save(E / 'budget.json', budget)
    schedule = read(E / 'schedule.json')
    schedule.update(updated_utc=now.isoformat(), current_best=f'Frozen A/B accepted fullgate and9mainblocks each; latest{sid} publicconditional targetsUNMET; formalUNKNOWN.', active_known_runs=[], collected_runs=sorted(audit['run_conclusions']), prepared_next=[], closure='evidence/round24/closure.json')
    save(E / 'schedule.json', schedule)
    report = ROOT / 'docs/rounds/round24.md'
    text = report.read_text(encoding='utf-8').replace('当前 **ACTIVE**', '状态 **研究窗口结束，双目标未完成**').replace('本轮仍在进行；最新队列、暂停理由和下一步见', '本轮研究已进入最终交付收尾；保留成果、暂停理由和下一步见').replace('最终独立确认结果（交付核验中）', '最终独立确认结果').replace('截止前仍会查询最新榜单并同步更新最终汇总和看板。', '截止前最后查询已确认当前快照与评分政策一致，见[最终查询回执](../../evidence/round24/official-last-check/receipt.json)；[窗口关闭记录](../../evidence/round24/closure.json)保留实际研究结束时间与交付余量。').replace('audit-closing-diagnostics.json', 'audit-delivery.json')
    text = text.replace('本任务未兑换重置，读数不连续的原因UNKNOWN，不能将前后差值当作本任务消耗。', '最终账户读数为2%used／98%remaining，见[实时回执](../../evidence/round24/usage-final.json)。本任务未兑换重置，读数不连续的原因UNKNOWN，不能将前后差值当作本任务消耗。')
    text = text.replace('runner时间是并发作业之和，不等于10小时墙钟或账单。', '提交后另核对2034份Git对象，共232,139,415字节，原始回执、所有R24源码和两份ZIP保持原字节：[Git审计](../../evidence/round24/git-byte-audit-delivery.json)。runner时间是并发作业之和，不等于10小时墙钟或账单。')
    report.write_bytes(text.encode())
    p = ROOT / 'docs/TASK_INDEX.md'
    text = p.read_text(encoding='utf-8').replace('ACTIVE收尾：两份原版完整gate通过，各3runner共9主块；', '窗口结束，双目标未完成：两份原版完整gate通过，各3runner共9主块；')
    p.write_bytes(text.encode())
    p = ROOT / 'docs/tasks.json'
    tasks = read(p)
    entry = next(t for t in tasks['tasks'] if t['id'] == 'round24')
    entry['decision'] = f'窗口结束，稳定10%／15%未完成；两份原版完整gate及各3runner共9主块已收齐；快照{sid}条件估算已重放，无正式上传。'
    save(p, tasks)
    p = ROOT / 'docs/research/optimization-methods.md'
    text = p.read_text(encoding='utf-8').replace('完整研究收尾仍在固定窗口内。', '研究窗口已结束，两个稳定份额目标未完成。')
    p.write_bytes(text.encode())
    state = f'''# R24 终态

固定窗口：北京时间2026-10-11 03:28:08–13:28:08。研究结束，最后交付在原截止内进行；**稳定10%／15%目标未完成**。未正式上传，admission／私有／可支付份额UNKNOWN。不可从上下文压缩或额度窗口变化重新计时；继续研究需用户新预算。

最终保留A `r24-609-root-word-price-proof1`、B `r24-609-fast-adaptive-proof1`。精确Rust/Lean及完整gate、3runner各3块（每候选9主块）、原版1warmup/11measured和两文件ZIP均已核验。冻结后未改源码；新基础端点只是编码诊断，未计时／未完整证明，不能混作第三份已验收候选。

最新官方快照{sid}，最终短查询已确认仍是当前快照且政策一致。主分析／anchors／summary及CSV见`confirmation-{sid}`、`analysis-confirmation-{sid}.json`、`anchors-confirmation-{sid}.json`。A主609最低3.142733%、中位3.199050%；607最低0.170855%、中位0.333928%。B主609最低2.713093%、中位3.590919%；607最低2.593366%、中位3.227289%。每个视图0/9零、0/9达10或15；视图和副本不增加独立块。联合609中位A0.280486%、B3.488968%，不能相加独立估算。详情及完整范围见报告。

82次手动CI全部结束并收集，79成功／3失败；444原协议配对进程，944.3并发runner分钟，1248原始artifact141780700B。40种归档Rust中32种有原协议主候选测量；其余未计时草稿不赋分。2034份Git对象232139415B字节审计通过。最终账户共享用量2%used／98%remaining；中途读数／重置时间不连续、原因UNKNOWN，本任务0重置／0购买，现金成本UNKNOWN。

主工作树及远端main仍为5bd2a57597aa92219a39a28edace88bc059587f2，主工作区干净。成果在`codex/round24-stable-dual`，不自动merge或删除worktree。原始回执含空白字符，保留字节；源码／文档diff检查和project检查分列。

完整报告`docs/rounds/round24.md`；最终机器记录`closure.json`；完整验收`confirm-final-plan.json`；来源包`review-packages/packages.json`；最新历史提交看板`DASHBOARD.md`。`next-actions.md`保留当前B跨阶段共享的首个判别实验、弱种子和精确DP缓存旧反例，以及快速端窄峰、基础端点质量损失和未解决分母波动。不自动授权正式提交、注册、签名或资金动作。
'''
    (E / 'research-state.md').write_bytes(state.encode())
    print(json.dumps({k: closure[k] for k in ['status', 'research_closed_utc', 'elapsed_before_final_delivery_minutes', 'remaining_delivery_seconds', 'latest_snapshot_id', 'goal_achieved']}, ensure_ascii=False))


if __name__ == '__main__':
    main()
