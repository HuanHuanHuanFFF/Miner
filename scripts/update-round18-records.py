"""Bind final candidate metadata and project index to one verified summary."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def write(path, data):
    path.write_bytes((json.dumps(data, ensure_ascii=False, indent=2) + '\n').encode())


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--summary', type=Path, required=True)
    parser.add_argument('--analysis', type=Path, required=True)
    parser.add_argument('--window-ended', action='store_true')
    args = parser.parse_args()
    summary = json.loads(args.summary.read_bytes())
    assert summary['analysis_sha256'] == hashlib.sha256(args.analysis.read_bytes()).hexdigest()
    assert summary['formal_payable_goal_status'] == 'NOT_ESTABLISHED'
    rel = lambda p: p.resolve().relative_to(ROOT).as_posix()
    medians = {}
    for candidate in summary['candidates']:
        path = ROOT / candidate['path']
        for filename, sha in candidate['files'].items():
            assert hashlib.sha256((path / filename).read_bytes()).hexdigest() == sha
        certificate = json.loads((path / 'VERIFICATION.json').read_bytes())
        assert certificate['files'] == candidate['files']
        assert certificate['status'] == 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
        no_target_hits = all(d['at_least_5_count'] == 0 and d['at_least_15_count'] == 0
                             for d in candidate['single'].values())
        certificate['performance_status'] = ('Two predeclared fresh runners, four original-protocol blocks each, '
                                             'exact frozen pair. See per-control observed target counts. '
                                             'Conditional geometry only, no formal payability established.')
        certificate['confirmation'] = {
            'analysis': rel(args.analysis), 'summary_file': rel(args.summary),
            'snapshot_id': summary['snapshot']['snapshot_id'],
            'runner_count': 2, 'blocks_per_runner': 4, 'run_ids': summary['run_ids'],
            'summary': candidate['single'],
            'zero_control_disagreements': candidate['control_disagreement']['zero_disagreement_count'],
            'formal_admission': 'UNKNOWN_NOT_SUBMITTED',
        }
        write(path / 'VERIFICATION.json', certificate)
        manifest = json.loads((path / 'manifest.json').read_bytes())
        assert manifest['hashes'] == candidate['files']
        manifest['proof_status'] = certificate['status']
        manifest['verification'] = 'VERIFICATION.json'
        manifest['performance_status'] = ('VERIFIED_PUBLIC_FINAL_CONFIRMATION_CONDITIONAL_SCORES_BELOW_TARGETS'
                                           if no_target_hits else
                                           'VERIFIED_PUBLIC_FINAL_CONFIRMATION_CONDITIONAL_TARGET_HITS_NOT_FORMAL')
        manifest['performance_evidence'] = rel(args.summary)
        write(path / 'manifest.json', manifest)
        medians[candidate['role']] = candidate['single']['primary']['median_pct']
    budget = json.loads((E / 'budget.json').read_bytes())
    now = datetime.now(timezone.utc)
    deadline = datetime.fromisoformat(budget['deadline_utc'])
    if args.window_ended:
        assert now >= deadline, 'Do not declare the fixed research window ended early'
        budget['status'] = 'WINDOW_ENDED_OBJECTIVES_UNMET'
        budget['phase'] = 'DELIVERED_WITH_UNMET_REWARD_TARGETS'
        budget['closeout_recorded_at_utc'] = now.isoformat()
        budget['research_actions_cease_at_utc'] = budget['deadline_utc']
    else:
        budget['phase'] = 'FINAL_EVIDENCE_REVIEW'
    budget['final_confirmation_summary'] = rel(args.summary)
    budget['formal_payable_objectives_established'] = False
    write(E / 'budget.json', budget)
    description = (f'两个不同Rust通过完整公共gate和两台runner八块冻结确认；快照{summary["snapshot"]["snapshot_id"]}'
                   f'下A主中位{medians["A"]:.6f}%、B{medians["B"]:.6f}%，15%/5%目标未完成，无正式提交。')
    index = ROOT / 'docs/TASK_INDEX.md'
    text = index.read_text(encoding='utf-8')
    text, count = re.subn(r'(?m)^\| round18 \|.*$',
                         '| round18 | [第十八轮：八小时双候选与计时诊断](rounds/round18.md) | ' + description + ' |', text)
    assert count == 1
    index.write_bytes(text.encode())
    tasks_path = ROOT / 'docs/tasks.json'
    tasks = json.loads(tasks_path.read_bytes())
    task = next(item for item in tasks['tasks'] if item['id'] == 'round18')
    task['decision'] = ('固定北京时间01:32:51至09:32:51。' + description +
                        ('八小时窗口结束，原始证据、支付条件及替代起点已保留。' if args.window_ended else
                         '当前收尾复核仍在固定时间窗口内。'))
    write(tasks_path, tasks)
    print(json.dumps({'snapshot': summary['snapshot']['snapshot_id'], 'medians': medians,
                      'budget_status': budget['status'], 'source_and_proof_bytes_unchanged': True}))


if __name__ == '__main__':
    main()
