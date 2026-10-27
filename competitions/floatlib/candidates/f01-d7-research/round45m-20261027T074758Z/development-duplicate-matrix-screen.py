"""Screen exact row/column reuse on already-seen inputs; no timing claim."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import time

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('sum_screen', HERE / 'development-sum-absorption-screen.py')
helper = importlib.util.module_from_spec(spec)
spec.loader.exec_module(helper)


def main():
    g = helper.load_generator()
    started = time.monotonic()
    totals = {'sampled_words': 0, 'sampled_batches': 0, 'all_macs': 0,
              'potential_duplicate_macs': 0, 'already_underflow_fastpath_macs': 0,
              'non_underflow_macs': 0, 'non_underflow_duplicate_macs': 0}
    rows = []
    trace = hashlib.sha256()
    for case in json.loads(helper.PLAN.read_bytes())['cases']:
        if case['kernel'] != 'bmm' or not case['timed']:
            continue
        batches = []
        count = min(4, case['batch'])
        m, n, p = (case[k] for k in ('m', 'n', 'p'))
        for j in range(count):
            assert time.monotonic() - started < 8 and totals['sampled_words'] < 200000
            batch = j * case['batch'] // count
            a = [g.element(case, batch * m * n + i, 0, n) for i in range(m * n)]
            b = [g.element(case, batch * n * p + i, 1, p) for i in range(n * p)]
            for word in a + b:
                trace.update(word.to_bytes(4, 'little'))
            distinct_rows = len({tuple(a[i * n:(i + 1) * n]) for i in range(m)})
            distinct_cols = len({tuple(b[k * p + col] for k in range(n)) for col in range(p)})
            macs = m * n * p
            reusable = (m * p - distinct_rows * distinct_cols) * n
            small = all(((w >> 23) & 255) <= 43 for w in a + b)
            totals['sampled_words'] += len(a) + len(b)
            totals['sampled_batches'] += 1
            totals['all_macs'] += macs
            totals['potential_duplicate_macs'] += reusable
            totals['already_underflow_fastpath_macs'] += macs if small else 0
            if not small:
                totals['non_underflow_macs'] += macs
                totals['non_underflow_duplicate_macs'] += reusable
            batches.append({'batch': batch, 'distinct_rows': distinct_rows,
                            'distinct_columns': distinct_cols, 'rows': m, 'columns': p,
                            'macs': macs, 'potential_duplicate_macs': reusable,
                            'sampled_batch_all_underflow': small})
        rows.append({'case': case['name'], 'shape': [case['batch'], m, n, p], 'batches': batches})
    result = {'at_utc': datetime.now(timezone.utc).isoformat(),
              'scope': 'Four stratified complete batches per case from already-seen R15 discovery. Exact raw sequence identity permits sharing an ordered dot result, but scans/maps/copies/allocation and distribution stability are unmeasured.',
              'plan': helper.PLAN.relative_to(helper.ROOT).as_posix(),
              'plan_sha256': hashlib.sha256(helper.PLAN.read_bytes()).hexdigest(),
              'generator_sha256': hashlib.sha256(helper.GEN.read_bytes()).hexdigest(),
              'trace_sha256': trace.hexdigest(), 'counts': totals, 'cases': rows,
              'seconds': time.monotonic() - started,
              'limitation': 'MAC counts are not time shares or speedup. Per-sampled-batch underflow does not prove the complete matrix selects that existing fastpath.'}
    (HERE / 'development-duplicate-matrix-screen.json').write_text(
        json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'counts': totals, 'seconds': result['seconds']}))


if __name__ == '__main__':
    main()
