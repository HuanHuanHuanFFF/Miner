"""Deduplicate actual registration costs and mark rewards at current pool price."""
from decimal import Decimal
import hashlib
import json

RAO = Decimal(1_000_000_000)


def calculate(rows, ledger, price):
    ids = {r['submission_id'] for r in rows}
    costs = ledger['costs']
    assert len({c['cost_id'] for c in costs}) == len(costs), 'Duplicate registration cost'
    relevant = [c for c in costs if ids.intersection(c['submission_ids'])]
    total_cost = sum((Decimal(c['total_rao']) / RAO for c in relevant), Decimal(0))
    successful = [c for c in relevant if c['type'] == 'successful_registration']
    covered = set().union(*(set(c['submission_ids']) for c in successful)) if successful else set()
    missing = sorted(ids - covered)
    for c in relevant:
        assert int(c['total_rao']) == int(c['registration_charge_rao']) + int(c['network_fee_rao'])
        assert int(c['total_rao']) >= 0
    rewards_known = all(r['bounty_earned_alpha'] is not None for r in rows)
    alpha = sum((Decimal(str(r['bounty_earned_alpha'])) for r in rows if r['bounty_earned_alpha'] is not None), Decimal(0))
    pool = price.get('pools', {}) if price else {}
    ratio = None
    if int(pool.get('subnetAlphaIn', 0)) > 0 and int(pool.get('subnetTAO', 0)) > 0:
        ratio = Decimal(pool['subnetTAO']) / Decimal(pool['subnetAlphaIn'])
    marked = alpha * ratio if ratio is not None and rewards_known else None
    net = marked - total_cost if marked is not None and not missing else None
    cost_alpha = total_cost / ratio if ratio is not None else None
    net_alpha = alpha - cost_alpha if net is not None else None
    return {'status': 'INFERRED_SPOT_MARK_TO_MARKET' if net is not None else 'UNKNOWN',
            'registration_cost_tao': str(total_cost), 'missing_cost_submission_ids': missing,
            'reward_records_complete': rewards_known, 'alpha_reward': str(alpha),
            'tao_per_alpha': str(ratio) if ratio is not None else None,
            'marked_reward_tao': str(marked) if marked is not None else None,
            'net_after_registration_tao': str(net) if net is not None else None,
            'registration_cost_alpha_at_current_price': str(cost_alpha) if cost_alpha is not None else None,
            'net_after_registration_alpha': str(net_alpha) if net_alpha is not None else None,
            'price_finalized_block': price.get('finalized_block') if price else None,
            'price_checked_at_utc': price.get('checked_at_utc') if price else None,
            'scope': ledger['scope'], 'limits': 'Spot valuation, not realized withdrawal proceeds; no slippage, withdrawal fee, or wallet receipt claim.'}


def read_ledger(root):
    path = root / 'docs/registration-costs.json'
    ledger = json.loads(path.read_bytes())
    for c in ledger['costs']:
        evidence = (root / c['evidence']).resolve()
        assert evidence.is_relative_to(root.resolve())
        assert hashlib.sha256(evidence.read_bytes()).hexdigest() == c['evidence_sha256']
    return ledger
