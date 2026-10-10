"""Refresh the root submission dashboard from read-only official API snapshots."""
from datetime import datetime, timedelta, timezone
from decimal import Decimal
import hashlib
import json
from pathlib import Path

import requests

ROOT = Path(__file__).resolve().parents[1]
BASE = 'https://conjectures.io/v1/competitions/deflate'
BJT = timezone(timedelta(hours=8))


def save_json(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


def beijing(value):
    return datetime.fromisoformat(value).astimezone(BJT).strftime('%Y-%m-%d %H:%M:%S') if value else 'UNKNOWN'


def number(value, suffix=''):
    return 'UNKNOWN' if value is None else f'{value:.6f}{suffix}'


def refresh():
    registry_path = ROOT / 'docs/submissions.json'
    registry = json.loads(registry_path.read_bytes())
    entries = registry['submissions']
    ids = [entry['submission_id'] for entry in entries]
    assert entries and len(ids) == len(set(ids)) and all(sid.isdecimal() for sid in ids)
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    dest = ROOT / 'evidence/dashboard' / stamp
    dest.mkdir(parents=True)
    receipts = []

    def get(session, name, url, allow_missing_snapshot=False):
        response = session.get(url, timeout=40)
        raw = response.content
        file = dest / (name + '.response.json')
        file.write_bytes(raw)
        receipts.append({'url': url, 'read_at_utc': datetime.now(timezone.utc).isoformat(),
                         'http_status': response.status_code, 'sha256': hashlib.sha256(raw).hexdigest(),
                         'raw_file': file.name, 'bytes': len(raw)})
        save_json(dest / 'receipts.json', receipts)
        if response.status_code == 404 and allow_missing_snapshot:
            return None
        response.raise_for_status()
        return response.json()

    rows = []
    try:
        with requests.Session() as session:
            latest = get(session, 'latest', f'{BASE}/submissions/{ids[-1]}')
            context = latest['context']
            snapshot = context['snapshot_id']
            assert snapshot and context['status'] == 'ready'
            for entry in entries:
                sid = entry['submission_id']
                body = get(session, sid, f'{BASE}/submissions/{sid}?snapshot_id={snapshot}', True)
                in_snapshot = body is not None
                if not in_snapshot:
                    # New uploads can exist before the selected scoring pass includes them.
                    body = get(session, sid + '-pending', f'{BASE}/submissions/{sid}')
                sub = body['submission']
                assert sub['id'] == sid
                assert not in_snapshot or body['context']['snapshot_id'] == snapshot
                source = ROOT / 'candidates' / entry['candidate'] / 'parse.rs'
                assert hashlib.sha256(source.read_bytes()).hexdigest() == body['source_sha256'], sid
                score = (sub.get('score') or {}) if in_snapshot else {}
                assert not score or score['snapshot_id'] == snapshot
                weight = score.get('payable_weight')
                share = None if weight is None else 100 * weight
                admission = sub.get('admission') or {}
                if not entry.get('first_observed') and share is not None and admission.get('admitted') is not None:
                    entry['first_observed'] = {'share_pct': share, 'snapshot_id': snapshot,
                        'computed_at': context['computed_at'], 'evidence': (dest / f'{sid}.response.json').relative_to(ROOT).as_posix()}
                rows.append({**entry, 'submitted_at': sub['submitted_at'], 'gate_status': sub['gate_status'],
                    'admission': admission, 'current_share_pct': share,
                    'bounty_earned_alpha': score.get('bounty_earned_alpha'),
                    'on_frontier': score.get('on_frontier'), 'unpaid_reason': score.get('unpaid_reason'),
                    'digest': body['digest'], 'source_sha256': body['source_sha256']})
    except Exception as exc:
        save_json(dest / 'failure.json', {'error_type': type(exc).__name__, 'message': str(exc),
                                         'dashboard_preserved': True})
        raise

    summary = {'checked_at_utc': datetime.now(timezone.utc).isoformat(), 'context': context, 'submissions': rows}
    save_json(dest / 'summary.json', summary)
    save_json(registry_path, registry)
    rel = dest.relative_to(ROOT).as_posix()
    lines = ['# DEFLATE 提交看板', '',
        f"最近查询：北京时间 **{beijing(summary['checked_at_utc'])}**。官方快照 **{snapshot}**，计算时间 **{beijing(context['computed_at'])}**；官方 freshness=`{context.get('freshness', 'UNKNOWN')}`。",
        '', '汇总本项目已核验的正式提交；研究中的未提交候选见[任务索引](docs/TASK_INDEX.md)。执行与更新规则见 [AGENTS.md](AGENTS.md#提交看板维护)。', '',
        '- **初始份额**：目前归档可核验的早期正式评分记录，固定保留原快照；不保证恰为服务端首次评分。提交瞬间、排队状态与公共预测不作为初始成绩。',
        '- **当前份额**：本次同一官方快照的竞赛奖励池可支付份额 `payable_weight × 100%`。',
        '- **累计 α**：官方按该提交记录的 `bounty_earned_alpha`，截至该快照；不同于本看板核验的钱包到账。钱包当前到账状态为 UNKNOWN。',
        '- **VERIFIED** 表示已核对官方原始响应及本地源码；缺失字段保留 UNKNOWN，不补零。', '',
        '| 正式提交 | 轮次／候选 | 提交时间（北京） | 初始份额／快照 | 当前份额 | 累计 α | 当前状态 |',
        '|---|---|---|---:|---:|---:|---|']
    for row in rows:
        sid = row['submission_id']
        first = row.get('first_observed')
        initial = (f"[{number(first['share_pct'], '%')} · {first['snapshot_id']}]({first['evidence']})" if first else 'UNKNOWN')
        if row['gate_status'] not in ('passed', 'accepted'):
            state = f"gate={row['gate_status']}；正式成绩待定"
        elif row['admission'].get('admitted') is False:
            state = 'gate 通过；准入未通过'
        elif row['admission'].get('admitted') is None:
            state = 'gate 通过；准入待定'
        else:
            position = '前沿状态 UNKNOWN' if row['on_frontier'] is None else ('在前沿' if row['on_frontier'] else '已退出前沿')
            state = '准入通过；' + position
        lines.append(f"| [#{sid}](https://conjectures.io/competitions/deflate/submissions/{sid}) | {row['round']} · [{row['candidate']}](candidates/{row['candidate']}) | {beijing(row['submitted_at'])} | {initial} | {number(row['current_share_pct'], '%')} | {number(row['bounty_earned_alpha'])} | {state} |")
    known = [Decimal(str(row['bounty_earned_alpha'])) for row in rows if row['bounty_earned_alpha'] is not None]
    total = sum(known, Decimal(0))
    lines += ['', f'已知累计奖励合计：**{total:.6f} α**（{len(known)}/{len(rows)} 条具有官方数值；VERIFIED API 记录，非钱包余额或净利润）。', '',
              f'[本次完整数据]({rel}/summary.json) · [原始响应 SHA-256 与查询时间]({rel}/receipts.json) · [提交登记表](docs/submissions.json)', '',
              '初始记录计算时间（北京）：', '']
    for row in rows:
        first = row.get('first_observed')
        lines.append(f"- #{row['submission_id']}：{beijing(first['computed_at']) if first else 'UNKNOWN'}。")
    lines += ['', '研究方法与机制结论见 [DEFLATE 优化方法与实验结论](docs/research/optimization-methods.md)。', '']
    (ROOT / 'DASHBOARD.md').write_text('\n'.join(lines), encoding='utf-8')
    print(json.dumps({'snapshot_id': snapshot, 'submissions': len(rows), 'known_alpha_total': str(total), 'evidence': rel}))


if __name__ == '__main__':
    refresh()
