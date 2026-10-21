"""Recompute every completed R24 candidate measurement on one captured official frontier."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, json, statistics as st
from round3 import load_scorer
from round10_payability import load_flat_rows, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'


def read(p):
    return json.loads(p.read_bytes())


def dist(rs):
    v = [r['share_pct'] for r in rs]
    return {'observations': len(v), 'runners': len({r['run_id'] for r in rs}), 'minimum_pct': min(v), 'median_pct': st.median(v), 'best_pct': max(v), 'zero_count': sum(x == 0 for x in v), 'at_least_10_count': sum(x >= 10 for x in v), 'at_least_15_count': sum(x >= 15 for x in v)}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', required=True, type=Path)
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args()
    assert not a.output.exists()
    comp, ctx, formal_rows = load_flat_rows(a.capture)
    sc = load_scorer(E / 'official-rules-start/validator--scoring--pareto.py')
    check = validate_policy_for_replay(comp['policy'], formal_rows, sc)
    formal = {str(r['id']): r for r in formal_rows}
    bounds = sc.Boundaries(comp['policy']['max_balanced_time_ratio'], comp['policy']['max_mean_file_compression_pct'])
    front = [sc.Point(str(r['id']), r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct']) for r in formal_rows if (r.get('score') or {}).get('on_frontier')]

    def score(name, x, y):
        if not (0 < x <= bounds.time_s and 0 < y <= bounds.ratio_pct) or any(p.time_s <= x and p.ratio_pct <= y for p in front):
            return 0.0
        nf = sc.pareto_front(front + [sc.Point(name, x, y)])
        return 100 * comp['policy']['pareto_share'] * sc.local_global_improvement_space_log_weights(nf, bounds).get(name, 0)

    observations, audit, batches = [], [], []
    for p in sorted(E.glob('[0-9]*/*/gate/state.json')):
        state = read(p)
        folder = p.parent
        ci = read(folder / 'ci-run.json')
        assert ci['status'] == 'completed' and ci['headSha'] == state['git_sha'] and str(ci['databaseId']) == state['run_id']
        inv = read(folder / 'raw-artifact-files.json')['files']
        es = {e['name']: e for e in state['spec']['entries']}
        metrics = {}
        for m in state['metrics']:
            name, block = m['candidate'], m['round']
            raw = folder / f'round{block}-{name}.jsonl'
            assert hashlib.sha256(raw.read_bytes()).hexdigest() == inv[raw.name]['sha256']
            items = [json.loads(line) for line in raw.read_text().splitlines()]
            meta = items[0]
            assert meta['measured_rounds'] == 11 and meta['warmup_rounds'] == 1 and meta['methods'][name]['source_sha256'] == es[name]['hashes']['parse.rs']
            xs, ys = [], []
            for f in [x for x in items if x['kind'] == 'file']:
                med = {}
                for n in [name, 'incumbent']:
                    d = f['methods'][n]
                    assert d['deterministic'] and not d['errors']
                    reps = [r['total_s'] for r in d['reps'] if r['phase'] == 'measured']
                    assert len(reps) == 11 and min(reps) > 0
                    med[n] = st.median(reps)
                xs.append(med[name] / med['incumbent'])
                ys.append(100 * f['methods'][name]['output_bytes'] / f['raw_bytes'])
            assert len(xs) == 28 and abs(st.mean(xs) - m['time']) < 1e-12 and abs(st.mean(ys) - m['size_pct']) < 1e-12
            metrics[name, block] = (st.mean(xs), st.mean(ys))
            audit.append({'file': raw.relative_to(ROOT).as_posix(), 'sha256': inv[raw.name]['sha256']})
        for name, entry in es.items():
            if entry.get('control'):
                continue
            own = entry['anchor']
            available = [n for n, e in es.items() if e.get('formal_id') in ['607', '609'] or n == own or n == own + '-shadow']
            for (n, block), (x, y) in metrics.items():
                if n != name:
                    continue
                for anchor in available:
                    if (anchor, block) not in metrics:
                        continue
                    fid = es[anchor].get('formal_id') or es[anchor.removesuffix('-shadow')]['formal_id']
                    fm = formal[str(fid)]['metrics']
                    ax, ay = metrics[anchor, block]
                    tx, ty = fm['balanced_time_ratio'] * x / ax, fm['mean_file_compression_pct'] * y / ay
                    observations.append({'run_id': state['run_id'], 'batch': state['batch'], 'ci_conclusion': ci['conclusion'], 'phase': state['phase'], 'evidence_role': state['spec'].get('r18_role', 'discovery'), 'block': block, 'candidate_entry': name, 'source_sha256': entry['hashes']['parse.rs'], 'proof_sha256': entry['hashes']['Parse.lean'], 'anchor': anchor, 'declared_primary': anchor == own, 'public_time': x, 'public_size_pct': y, 'projected_time': tx, 'projected_size_pct': ty, 'share_pct': score(name, tx, ty)})
        batches.append({'run_id': state['run_id'], 'batch': state['batch'], 'ci_conclusion': ci['conclusion'], 'phase': state['phase'], 'failures': state['failures'], 'recorded_original_paired_processes': len(metrics)})
    summaries = []
    for hs in sorted({r['source_sha256'] for r in observations}):
        rs = [r for r in observations if r['source_sha256'] == hs]
        summaries.append({'source_sha256': hs, 'candidate_entries': sorted({r['candidate_entry'] for r in rs}), 'proof_hashes': sorted({r['proof_sha256'] for r in rs}), 'by_anchor_and_role': [{'anchor': anchor, 'role': role, **dist([r for r in rs if r['anchor'] == anchor and r['evidence_role'] == role])} for anchor, role in sorted({(r['anchor'], r['evidence_role']) for r in rs})], 'declared_primary_all_roles_FOR_RETRIEVAL_NOT_STABILITY': dist([r for r in rs if r['declared_primary']]), 'maximum_of_any_observed_view_pct_NOT_EXPECTATION': max(r['share_pct'] for r in rs)})
    summaries.sort(key=lambda r: r['maximum_of_any_observed_view_pct_NOT_EXPECTATION'], reverse=True)
    out = {'status': 'VERIFIED_ALL_RECORDED_ORIGINAL_MEASUREMENTS_CURRENT_SNAPSHOT_REPLAY', 'computed_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': ctx, 'policy_check': check, 'batches': batches, 'raw_audit': audit, 'distinct_measured_rust_hashes': len(summaries), 'original_paired_processes': len(audit), 'candidate_summaries': summaries, 'observations': observations, 'limits': ['Includes all recorded complete28file original-protocol candidate measurements, even from partially failed batches; absent measurements remain absent.', 'Discovery, checkpoint and final independent_confirmation are reported separately. Differentcalibrations reuse measurements. Samehash acrossproof-only names is grouped only for retrieval.', 'Any-view maximum is a retrieval aid, never expected reward, stability evidence or a reason to hide zeros.', 'Unmeasured native-only/proof drafts are excluded from score claims; no formal result or private transfer guarantee.']}
    a.output.write_bytes((json.dumps(out, indent=2) + '\n').encode())
    print(json.dumps({'snapshot': ctx, 'measured_rust_hashes': len(summaries), 'paired_processes': len(audit), 'top_retrieval_rows_NOT_STABILITY': [{k: r[k] for k in ['candidate_entries', 'maximum_of_any_observed_view_pct_NOT_EXPECTATION', 'declared_primary_all_roles_FOR_RETRIEVAL_NOT_STABILITY']} for r in summaries[:8]]}, indent=2))


if __name__ == '__main__':
    main()
