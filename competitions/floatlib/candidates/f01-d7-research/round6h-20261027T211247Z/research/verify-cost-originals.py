"""Independent receipt/raw-row verification, without compilation or benchmark."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
RUN = HERE.parent / 'ci-runs/40586463637'
EXPECTED = '22c60285eb3eb0222f063dfca1b8df31fb489cf44575a29dfd71d7075ac0b869'

def digest(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    index_path = RUN / 'original-artifact-hashes.json'
    index = json.loads(index_path.read_bytes())
    base = (RUN / index['directory']).resolve()
    total = 0
    for name, meta in index['files'].items():
        path = (base / name).resolve()
        assert path.is_relative_to(base) and path.is_file(), name
        assert path.stat().st_size == meta['bytes'] and digest(path) == meta['sha256'], name
        total += meta['bytes']
    target = base / 'diagnostics/f01-d7-public-suite/public-suite'
    assert digest(target / 'inputs/f01-r22-dev-runtime-cost1/Kernel.lean') == EXPECTED
    cost = target / 'diagnostics/f01-r22-dev-runtime-cost1/runtime-cost'
    result = json.loads((cost / 'result.json').read_bytes())
    assert result['source_sha256'] == EXPECTED
    assert result['complete'] and result['measurement_complete'] and result['official_originals_unchanged']
    assert result['full_gate'] is False and result['original25_round_score'] == 'NOT_RUN'
    assert all(v['equal_after_only_root_target_path_mapping'] for v in result['flags_and_link'].values())
    assert len(result['runs']) == 16
    order = ['control', 'streamed', 'streamed', 'control', 'control', 'scaled', 'scaled', 'control']
    summaries = []
    for seed in (2220001, 2220003):
        plan = json.loads((cost / f'plan-{seed}.json').read_bytes())
        cases = {c['name']: c for c in plan['cases']}
        assert len(cases) == 156 and sum(c['timed'] for c in cases.values()) == 152
        runs = []
        for i, variant in enumerate(order):
            log = cost / f'{seed}-{i}-{variant}.log'
            rows = {}
            for line in log.read_text().splitlines():
                match = re.fullmatch(r'(\S+) (true|false) ([0-9]+) ([0-9]+)', line)
                assert match, line
                name, timed, elapsed, checksum = match.groups()
                assert name not in rows
                rows[name] = {'timed': timed == 'true', 'best_ns': int(elapsed), 'checksum': int(checksum)}
            assert set(rows) == set(cases)
            assert all(rows[n]['timed'] == cases[n]['timed'] for n in cases)
            assert rows == json.loads((cost / f'{seed}-{i}-{variant}-rows.json').read_bytes())
            if runs:
                assert all(rows[n]['checksum'] == runs[0][n]['checksum'] for n in cases)
            runs.append(rows)
        blocks = {}
        for name, control, trial in [('streamed_block_0', 0, 1), ('streamed_block_1', 3, 2),
                                     ('scaled_block_0', 4, 5), ('scaled_block_1', 7, 6)]:
            ratios = {}
            for op in ('add', 'mul', 'sum', 'bmm', 'whole'):
                selected = [n for n, c in cases.items() if c['timed'] and (op == 'whole' or c['kernel'] == op)]
                ratios[op] = sum(runs[trial][n]['best_ns'] for n in selected) / sum(runs[control][n]['best_ns'] for n in selected)
            blocks[name] = ratios
            published = next(x for x in result['pairs'] if x['seed'] == seed)[name]
            assert all(abs(ratios[op] - published[op]['variant_over_control']) < 1e-14 for op in ratios)
        summaries.append({'seed': seed, 'blocks': blocks, 'all_156_checksums_match': True})
    caller = cost / 'build-product-0-R22RuntimeCostMain.c'
    c = caller.read_text()
    assert 'R21ScaledU32_diagnosticEntry' not in c
    assert 'lp_competition_Submission_R22StreamingCost_guarded' in c
    assert 'BENCH_VARIANT' in c and 'lean_uint64_to_float32' in c and 'lean_float32_to_uint32' in c
    assert (cost / 'caller.lean').read_bytes() == (HERE.parent / 'development-cost/R22RuntimeCostMain.lean').read_bytes()
    receipt = {'checked_utc': datetime.now(timezone.utc).isoformat(), 'run': 40586463637,
               'source_sha256': EXPECTED, 'index_sha256': digest(index_path),
               'original_files_verified': len(index['files']), 'original_bytes_verified': total,
               'independent_raw_log_parser_rows': 16 * 156, 'raw_and_stored_rows_identical': True,
               'fixed_plan_coverage_and_checksums': True, 'recomputed_blocks': summaries,
               'actual_Main_C_sha256': digest(caller), 'full_gate': False,
               'scope': 'Exact diagnostic artifact identity, raw-row sums and actual complete entry routing. No all-input proof, 25-round adoption, or official score inference.'}
    (HERE / 'originals-verified-40586463637.json').write_text(json.dumps(receipt, indent=2) + '\n')
    print(json.dumps(receipt, indent=2))

if __name__ == '__main__':
    main()
