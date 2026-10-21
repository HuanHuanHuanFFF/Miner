"""Joint observed-point portfolios: matched blocks and an explicitly optimistic cross-run search."""
from pathlib import Path
from datetime import datetime, timezone
from collections import defaultdict
import argparse, hashlib, itertools, json, math, statistics as st
from round3 import load_scorer
from round10_payability import load_flat_rows, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'


def read(p):
    return json.loads(p.read_bytes())


def distribution(values):
    return {'n': len(values), 'minimum_pct': min(values), 'median_pct': st.median(values), 'best_pct': max(values), 'zero_count': sum(v == 0 for v in values), 'at_least_10_count': sum(v >= 10 for v in values)}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', required=True, type=Path)
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args()
    assert not a.output.exists()
    comp, ctx, formal_rows = load_flat_rows(a.capture)
    sc = load_scorer(E / 'official-rules-portfolio/validator--scoring--pareto.py')
    policy = validate_policy_for_replay(comp['policy'], formal_rows, sc)
    formal = {str(r['id']): r for r in formal_rows}
    bounds = sc.Boundaries(comp['policy']['max_balanced_time_ratio'], comp['policy']['max_mean_file_compression_pct'])
    front = [sc.Point(str(r['id']), r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct']) for r in formal_rows if (r.get('score') or {}).get('on_frontier')]
    names, certificates = {}, {}
    for p in sorted((ROOT / 'candidates').glob('r24-*/manifest.json')):
        d = read(p)
        sha = d['hashes']['parse.rs']
        names.setdefault(sha, p.parent.name)
        if (p.parent / 'VERIFICATION.json').exists():
            cert = read(p.parent / 'VERIFICATION.json')
            assert cert['files'] == d['hashes']
            assert cert['status'] == 'VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
            certificates[sha] = cert
            names[sha] = p.parent.name
    assert len(certificates) == 7
    registry_ids = [r['submission_id'] for r in read(ROOT / 'docs/submissions.json')['submissions']]
    owned_keys = {formal[str(i)]['hotkey'] for i in registry_ids}
    existing_payable = [r for r in formal_rows if r.get('hotkey') in owned_keys and (r.get('score') or {}).get('payable_weight', 0) > 0]
    owned_ids = [str(r['id']) for r in existing_payable]

    def evaluate(points):
        eligible = [sc.Point(p['source_sha256'], p['x'], p['y']) for p in points if 0 < p['x'] <= bounds.time_s and 0 < p['y'] <= bounds.ratio_pct and not any(q.time_s <= p['x'] and q.ratio_pct <= p['y'] for q in front)]
        nf = sc.pareto_front(front + eligible)
        weights = sc.local_global_improvement_space_log_weights(nf, bounds)
        shares = {p['source_sha256']: 100 * weights.get(p['source_sha256'], 0) for p in points}
        current = {i: 100 * weights.get(i, 0) for i in owned_ids}
        return {'candidate_total_pct': sum(shares.values()), 'with_existing_payable_total_pct': sum(shares.values()) + sum(current.values()), 'candidate_shares_pct': shares, 'existing_shares_pct': current}

    observations, audits, cohort = [], [], defaultdict(lambda: defaultdict(list))
    for path in sorted(E.glob('[0-9]*/*/gate/state.json')):
        s = read(path)
        folder = path.parent
        ci = read(folder / 'ci-run.json')
        assert ci['status'] == 'completed' and ci['headSha'] == s['git_sha']
        inv = read(folder / 'raw-artifact-files.json')['files']
        entries = {e['name']: e for e in s['spec']['entries']}
        by = {(m['candidate'], m['round']): m for m in s['metrics']}
        for (name, block), metric in by.items():
            entry = entries[name]
            sha = entry['hashes']['parse.rs']
            if sha not in names:
                continue
            family = names[sha].split('-')[1]
            anchors = [n for n, e in entries.items() if str(e.get('formal_id')) == family]
            anchors += [n + '-shadow' for n in anchors if n + '-shadow' in entries]
            if family == '609' and 'public607' in entries:
                anchors.append('public607')
            used = [(name, block)] + [(n, block) for n in anchors if (n, block) in by]
            for n, b in used:
                raw = folder / f'round{b}-{n}.jsonl'
                assert hashlib.sha256(raw.read_bytes()).hexdigest() == inv[raw.name]['sha256']
                lines = [json.loads(x) for x in raw.read_text().splitlines()]
                assert lines[0]['measured_rounds'] == 11 and lines[0]['warmup_rounds'] == 1
                files = [r for r in lines if r['kind'] == 'file']
                assert len(files) == 28
                ratios, sizes = [], []
                for f in files:
                    med = {}
                    for method in [n, 'incumbent']:
                        d = f['methods'][method]
                        assert d['deterministic'] and not d['errors']
                        reps = [r['total_s'] for r in d['reps'] if r['phase'] == 'measured']
                        assert len(reps) == 11
                        med[method] = st.median(reps)
                    ratios.append(med[n] / med['incumbent'])
                    sizes.append(100 * f['methods'][n]['output_bytes'] / f['raw_bytes'])
                assert abs(st.mean(ratios) - by[n, b]['time']) < 1e-12 and abs(st.mean(sizes) - by[n, b]['size_pct']) < 1e-12
            audits.append({'run_id': s['run_id'], 'block': block, 'entry': name, 'source_sha256': sha})
            for anchor in anchors:
                if (anchor, block) not in by:
                    continue
                fid = entries[anchor].get('formal_id') or entries[anchor.removesuffix('-shadow')]['formal_id']
                ref = by[anchor, block]
                fm = formal[str(fid)]['metrics']
                r = {'candidate': names[sha], 'source_sha256': sha, 'gate_verified': sha in certificates, 'run_id': s['run_id'], 'batch': s['batch'], 'block': block, 'entry': name, 'entry_control': bool(entry.get('control')), 'role': s['spec'].get('r18_role', 'discovery'), 'anchor': anchor, 'x': fm['balanced_time_ratio'] * metric['time'] / ref['time'], 'y': fm['mean_file_compression_pct'] * metric['size_pct'] / ref['size_pct']}
                observations.append(r)
                if sha in certificates:
                    cohort[s['run_id'], block, anchor][sha].append(r)
    matched, ambiguity = [], []
    for key, grouped in cohort.items():
        points = []
        for sha, rs in grouped.items():
            candidates = [r for r in rs if not r['entry_control']]
            choices = candidates or [r for r in rs if not r['entry'].endswith('-shadow')]
            if len(choices) != 1:
                ambiguity.append({'cohort': key, 'sha': sha, 'entries': [r['entry'] for r in choices]})
                continue
            points.append(choices[0])
        for n in range(1, len(points) + 1):
            for group in itertools.combinations(points, n):
                score = evaluate(group)
                matched.append({'run_id': key[0], 'block': key[1], 'anchor': key[2], 'batch': group[0]['batch'], 'role': group[0]['role'], 'sources': sorted(p['source_sha256'] for p in group), 'candidates': sorted(p['candidate'] for p in group), 'entries': [p['entry'] for p in group], **score})
    summaries = []
    for sources, anchor, role in sorted({(tuple(r['sources']), r['anchor'], r['role']) for r in matched}):
        rs = [r for r in matched if tuple(r['sources']) == sources and r['anchor'] == anchor and r['role'] == role]
        summaries.append({'candidates': [names[s] for s in sources], 'anchor': anchor, 'role': role, 'runners': len({r['run_id'] for r in rs}), 'candidate_total': distribution([r['candidate_total_pct'] for r in rs]), 'including_existing': distribution([r['with_existing_payable_total_pct'] for r in rs]), 'per_candidate': {names[s]: distribution([r['candidate_shares_pct'][s] for r in rs]) for s in sources}})
    print('matched_summaries', len(summaries), flush=True)
    searches = []
    for gated_only in [True, False]:
        levels = defaultdict(dict)
        for p in observations:
            if p['anchor'] == 'public607' or (gated_only and not p['gate_verified']):
                continue
            if not (0 < p['x'] <= bounds.time_s and 0 < p['y'] <= bounds.ratio_pct) or any(q.time_s <= p['x'] and q.ratio_pct <= p['y'] for q in front):
                continue
            levels[p['y']].setdefault((p['source_sha256'], p['x']), p)
        options = [[None] + list(v.values()) for _, v in sorted(levels.items())]
        count = math.prod(map(len, options))
        print('optimistic_search', gated_only, 'levels', [(y, len(v)) for y, v in sorted(levels.items())], 'cases', count, flush=True)
        assert count <= 5000000, 'Bounded Cartesian enumeration cap; no sampling substitution'
        best = None
        best_including_existing = None
        by_count = {}
        scored = 0
        dominated_combinations_skipped = 0
        for choice in itertools.product(*options):
            points = [p for p in choice if p is not None]
            if not points:
                continue
            # Options are ordered by strictly improving quality. A better-quality
            # point must be slower for both to survive. Otherwise removing the
            # dominated point gives the identical frontier, already enumerated
            # through that level's None option. This is exact, not a speed grid.
            if any(points[i]['x'] <= points[i+1]['x'] for i in range(len(points)-1)):
                dominated_combinations_skipped += 1
                continue
            assert len({p['source_sha256'] for p in points}) == len(points)
            scored += 1
            assert scored <= 600000, 'Exact scorer-call cap exceeded'
            score = evaluate(points)
            record = {'points': points, **score}
            n = len(points)
            if n not in by_count or score['candidate_total_pct'] > by_count[n]['candidate_total_pct']:
                by_count[n] = record
            if best is None or score['candidate_total_pct'] > best['candidate_total_pct']:
                best = record
            if best_including_existing is None or score['with_existing_payable_total_pct'] > best_including_existing['with_existing_payable_total_pct']:
                best_including_existing = record
        searches.append({'only_gate_verified': gated_only, 'quality_levels': [{'y': y, 'observed_options': len(v)} for y, v in sorted(levels.items())], 'enumerated_cases_including_empty': count, 'scorer_calls': scored, 'dominated_combinations_skipped_exactly': dominated_combinations_skipped, 'best': best, 'best_including_existing': best_including_existing, 'best_by_candidate_count': by_count, 'scope': 'Optimistic cross-run mixing of actually observed primary/shadow coordinates, including aliases. Not a simultaneously measured portfolio or expected reward. Equalqualitypoints cancontribute onlythefastest; hence atmostonepointperqualitylevel exhausts allsubsets overthis finite observedpoint set. Dominated combinations have the samefrontier as an enumeratedsmaller subset.'})
        print('best_optimistic_total', gated_only, best['candidate_total_pct'], 'including_existing', best['with_existing_payable_total_pct'], flush=True)
    result = {'status': 'VERIFIED_REPLAY_WITH_CONDITIONAL_PORTFOLIO_SEARCH', 'computed_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': ctx, 'policy_check': policy, 'gate_verified_sources': {names[s]: certificates[s] for s in certificates}, 'existing_payable_submissions': [{'id': r['id'], 'share_pct': 100 * r['score']['payable_weight']} for r in existing_payable], 'observations': observations, 'measurement_audit': audits, 'ambiguous_cohort_aliases_excluded': ambiguity, 'matched_results': matched, 'matched_summaries': summaries, 'optimistic_searches': searches, 'assumptions': ['New candidates individuallyadmitted, registered, belowbountycap andassigned distincteligiblehotkeys without oldsurvivingfrontierpoints; currentownpayable573 retained.', 'A portfolio optimum over searched public observations is selectionbiased and not stabilityconfirmation; differentrunnercoordinates cannotbeadded as observations.', 'No sourcechange, newCI, formalupload, registration, signing orspending. Unmeasured8Rust versions have no coordinate andcannotreceivea score.', 'Primary/shadowcalibrations includedinoptimisticsearch;607views reportedseparately onlywhereactuallypaired. Actualprivateerror andfuturefrontier UNKNOWN.']}
    a.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())


if __name__ == '__main__':
    main()
