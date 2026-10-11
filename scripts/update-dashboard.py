"""Refresh the root submission dashboard from read-only official API snapshots."""
from datetime import datetime, timedelta, timezone
from decimal import Decimal
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

import requests
from dashboard_profit import calculate, read_ledger

ROOT = Path(__file__).resolve().parents[1]
BASE = 'https://conjectures.io/v1/competitions/deflate'
BJT = timezone(timedelta(hours=8))


def save_json(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


def beijing(value):
    return datetime.fromisoformat(value).astimezone(BJT).strftime('%Y-%m-%d %H:%M:%S') if value else 'UNKNOWN'


def number(value, suffix=''):
    return 'UNKNOWN' if value is None else f'{value:.6f}{suffix}'


def refresh(snapshot_id=None):
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
            latest_url = f'{BASE}/submissions/{ids[-1]}'
            if snapshot_id is not None:
                latest_url += f'?snapshot_id={snapshot_id}'
            latest = get(session, 'latest', latest_url)
            context = latest['context']
            snapshot = context['snapshot_id']
            assert snapshot and context['status'] == 'ready'
            assert snapshot_id is None or str(snapshot) == snapshot_id, 'Requested snapshot must be preserved'
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

    ledger = read_ledger(ROOT)
    for cost_entry in ledger['costs']:
        for sid in set(cost_entry['submission_ids']).intersection(ids):
            evidence_path = dest / f'{sid}.response.json'
            if not evidence_path.exists():
                evidence_path = dest / f'{sid}-pending.response.json'
            payload = json.loads(evidence_path.read_bytes())
            if payload is None:
                payload = json.loads((dest / f'{sid}-pending.response.json').read_bytes())
            assert payload['submission']['hotkey'] == cost_entry['hotkey'], 'Registration identity mismatch'
    price = None
    dependency_roots = [ROOT / '.registration-private/registration-watch/node_modules',
                        ROOT.parent.parent / '.registration-private/registration-watch/node_modules']
    dependencies = next((p for p in dependency_roots if (p / '@polkadot/api/index.js').exists()), None)
    node = shutil.which('node')
    if node is None:
        fallback = Path.home() / '.cache/codex-runtimes/codex-primary-runtime/dependencies/node/bin/node.exe'
        node = str(fallback) if fallback.exists() else None
    try:
        if dependencies is None or node is None:
            raise RuntimeError('Existing local Node/Polkadot read-only dependencies unavailable')
        result = subprocess.run([node, str(ROOT / 'scripts/read-dashboard-costs.mjs'), str(dependencies),
                                 '--price-only', str(dest / 'chain-price'), 'wss://archive.chain.opentensor.ai:443'],
                                capture_output=True, timeout=120)
        (dest / 'chain-price-command.json').write_text(json.dumps({'exit_code': result.returncode,
             'stdout': result.stdout.decode('utf-8', errors='replace'),
             'stderr': result.stderr.decode('utf-8', errors='replace')}, indent=2) + '\n', encoding='utf-8')
        result.check_returncode()
        price_path = dest / 'chain-price/chain-read.json'
        price = json.loads(price_path.read_bytes())
        save_json(dest / 'chain-price-receipt.json', {'file': 'chain-price/chain-read.json',
                  'sha256': hashlib.sha256(price_path.read_bytes()).hexdigest()})
    except Exception as exc:
        save_json(dest / 'price-failure.json', {'error': str(exc), 'net_profit_status': 'UNKNOWN'})
    profit = calculate(rows, ledger, price)
    summary = {'checked_at_utc': datetime.now(timezone.utc).isoformat(), 'context': context,
               'submissions': rows, 'registration_profit': profit}
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
    marked = profit['marked_reward_tao']
    net = profit['net_after_registration_tao']
    cost_alpha = profit['registration_cost_alpha_at_current_price']
    net_alpha = profit['net_after_registration_alpha']
    cost = Decimal(profit['registration_cost_tao'])
    profit_lines = ['', '## 扣除注册费用后的累计收益', '',
        f"- 已核实注册成本：**{cost:.9f} TAO**，包括对应提交的注册扣款及成功／失败交易手续费；同一交易只计一次。",
        f"- 注册成本按当前价格折算：**{number(Decimal(cost_alpha) if cost_alpha is not None else None)} α**。",
        f"- 扣除注册成本的累计净收益估算：**{number(Decimal(net_alpha) if net_alpha is not None else None)} α**（{profit['status']}；约 {number(Decimal(net) if net is not None else None)} TAO）。"]
    if profit['tao_per_alpha'] is not None:
        profit_lines += [f"- 兑换口径：SN66 池储备 `subnetTAO / subnetAlphaIn`，1 α ≈ {Decimal(profit['tao_per_alpha']):.9f} TAO；finalized 区块 **{profit['price_finalized_block']}**，查询北京时间 **{beijing(profit['price_checked_at_utc'])}**。"]
    if profit['missing_cost_submission_ids']:
        profit_lines += ['- 注册成本缺失：' + '、'.join('#' + sid for sid in profit['missing_cost_submission_ids']) + '；完整累计净收益保留 UNKNOWN。']
    failed_count = sum(c['type'] == 'failed_registration_fee' for c in ledger['costs'])
    profit_lines += ['', f'范围：本看板 {len(rows)} 笔已提交记录的注册成本，含 {failed_count} 次失败注册手续费；未使用注册额度、模型／CI成本不计入本项。净收益采用当前价格估值，不代表已经卖出或钱包已到账，未计兑换滑点及提现费用。未来新增提交若缺少成本记录，净收益显示 UNKNOWN。',
        '[注册成本登记与交易证据](docs/registration-costs.json) · ' + f'[折算储备与原始回执]({rel}/summary.json)', '']
    insert = lines.index('初始记录计算时间（北京）：')
    lines[insert:insert] = profit_lines
    for row in rows:
        first = row.get('first_observed')
        lines.append(f"- #{row['submission_id']}：{beijing(first['computed_at']) if first else 'UNKNOWN'}。")
    lines += ['', '研究方法与机制结论见 [DEFLATE 优化方法与实验结论](docs/research/optimization-methods.md)。', '']
    (ROOT / 'DASHBOARD.md').write_text('\n'.join(lines), encoding='utf-8')
    print(json.dumps({'snapshot_id': snapshot, 'submissions': len(rows), 'known_alpha_total': str(total), 'evidence': rel}))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--snapshot-id', help='Use this official snapshot for every row; default queries the latest snapshot.')
    args = parser.parse_args()
    if args.snapshot_id is not None and not args.snapshot_id.isdecimal():
        parser.error('--snapshot-id must contain only decimal digits')
    refresh(args.snapshot_id)
