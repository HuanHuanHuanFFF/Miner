"""Separate old fast-parent confirmation from its incidental R25 control samples."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import statistics as st

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round25'
NAME = 'r22-595-chain-halfhead'


def read(path):
    return json.loads(path.read_bytes())


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ('analysis', 'rank', 'algebra', 'output'):
        ap.add_argument('--' + name, type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    data, rank, algebra = [read(p) for p in (a.analysis, a.rank, a.algebra)]
    assert data['snapshot'] == rank['snapshot'] == algebra['snapshot']
    c = next(c for c in data['candidates'] if c['candidate'] == NAME)
    ranked = next(c for c in rank['candidates'] if c['candidate'] == NAME)
    current_ids = {r['run_id'] for r in read(E / 'raw-audit-confirmation.json')['runs']}
    old_ids = {r['run_id'] for r in data['runs']} - current_ids
    assert old_ids == {'38073624911', '38074189783', '38074200026'}
    summaries = []
    for era in ('historical_main_confirmation', 'historical_incidental_control', 'r25_incidental_control'):
        for calibration in ('primary', 'shadow'):
            if era == 'r25_incidental_control':
                rows = [o for o in c['observations'] if o['run_id'] in current_ids and o['calibration'] == calibration]
                assert len(rows) == 18 and all(o['entry_role'] == 'control' for o in rows)
            else:
                role = 'candidate' if era == 'historical_main_confirmation' else 'control'
                rows = [o for o in c['observations'] if o['run_id'] in old_ids and o['entry_role'] == role and o['calibration'] == calibration]
            values = [o['single_pool_share_pct'] for o in rows]
            keys = {(o['run_id'], o['block'], o['entry_name'], calibration) for o in rows}
            ranks = [o for o in ranked['observations'] if (o['run_id'], o['block'], o['entry_name'], o['calibration']) in keys]
            assert len(ranks) == len(rows)
            summaries.append({'era': era, 'calibration': calibration, 'n': len(values),
                              'run_count': len({o['run_id'] for o in rows}),
                              'minimum_pct': min(values), 'median_pct': st.median(values),
                              'maximum_pct': max(values), 'zero_count': sum(v == 0 for v in values),
                              'at_least_10_count': sum(v >= 10 for v in values),
                              'at_least_15_count': sum(v >= 15 for v in values),
                              'strict_first_count': sum(o['strict_geometric_first'] for o in ranks)})
    compact_keys = ('run_id', 'block', 'role', 'entry_role', 'entry_name', 'calibration',
                    'projected_time', 'projected_size_pct', 'single_pool_share_pct')
    peak_example = [r for r in algebra['single_effects'] if r['candidate'] == NAME and
                    r['run_id'] == '38130275592' and r['block'] == 1]
    assert len(peak_example) == 2
    out = {'status': 'INFERRED_PARENT_PEAKS_WITH_OBSERVED_ZEROS_NOT_STABLE_TARGET',
           'computed_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': data['snapshot'],
           'candidate': NAME, 'rust_sha256': c['rust_sha256'],
           'summary': summaries, 'observations': [{k: o[k] for k in compact_keys} for o in c['observations']],
           'same_candidate_same_source_anchor_switch_example': peak_example,
           'input_sha256': {str(p): hashlib.sha256(p.read_bytes()).hexdigest()
                            for p in (a.analysis, a.rank, a.algebra)},
           'decision': 'Retain the parent as a high-potential but unstable alternative. Do not replace failed R25 candidates with a selected historical peak or relabel control blocks as new candidate confirmation.',
           'limits': ['Historical timing blocks are replayed against the new snapshot, not new measurements.',
                      'R25 observations here are incidental same-source parent controls across9runner jobs, not predeclared frozen-parent confirmation.',
                      'Reference views reuse the same measured candidate; peak and zero frequencies are not private success probabilities.',
                      'All forecasts assume private-coordinate transfer and admission; no new formal submission was made.']}
    a.output.write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'snapshot': data['snapshot']['snapshot_id'], 'summary': summaries}, indent=2))


if __name__ == '__main__':
    main()
