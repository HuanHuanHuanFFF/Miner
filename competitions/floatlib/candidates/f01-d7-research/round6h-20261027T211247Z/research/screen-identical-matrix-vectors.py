"""Finite public-source screen for exact row/column reuse, without timing or Lean."""
from pathlib import Path
from datetime import datetime, timezone
import importlib.util
import hashlib
import json
import time

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('old_model', HERE / 'screen-native-image-exposure.py')
old = importlib.util.module_from_spec(spec)
spec.loader.exec_module(old)
ROOT = old.ROOT
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def scan(run_id):
    run = ROOT / f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run_id}'
    ix = json.loads((run / 'original-artifact-hashes.json').read_bytes())
    base = run / ix['directory'] / 'diagnostics/f01-d7-public-suite/public-suite'
    plan_path = base / 'public-drawn-plan.json'
    plan = json.loads(plan_path.read_bytes())
    rows = []
    reads = 0
    for c in plan['cases']:
        if not c['timed'] or c['kernel'] != 'bmm':
            continue
        n, m, p, batch = (c[k] for k in ('n', 'm', 'p', 'batch'))
        row_dups = col_dups = adjacent_rows = all_equal_row_batches = all_equal_col_batches = 0
        removed_macs = total_macs = 0
        all_old_small = True
        first = None
        for b in range(batch):
            aa = [tuple(old.env['element'](c, (b * m + i) * n + k, 0, n)
                        for k in range(n)) for i in range(m)]
            bb = [tuple(old.env['element'](c, (b * n + k) * p + j, 1, p)
                        for k in range(n)) for j in range(p)]
            reads += n * (m + p)
            all_old_small &= all((u & 0x7fffffff) < 0x16000000 for v in aa + bb for u in v)
            dupr, dupc = m - len(set(aa)), p - len(set(bb))
            if first is None and (dupr or dupc):
                first = {'batch': b, 'row_duplicate_count': dupr, 'column_duplicate_count': dupc}
            row_dups += dupr
            col_dups += dupc
            adjacent_rows += sum(aa[i] == aa[i - 1] for i in range(1, m))
            all_equal_row_batches += bool(m > 1 and dupr == m - 1)
            all_equal_col_batches += bool(p > 1 and dupc == p - 1)
            total_macs += m * n * p
            removed_macs += n * (m * p - (m - dupr) * (p - dupc))
        rows.append({'name': c['name'], 'group': c['name'].split(':')[1], 'shape': [batch, m, n, p],
                     'duplicate_rows_anywhere': row_dups, 'duplicate_columns_anywhere': col_dups,
                     'adjacent_duplicate_rows': adjacent_rows,
                     'all_equal_row_batches': all_equal_row_batches,
                     'all_equal_column_batches': all_equal_col_batches,
                     'all_inputs_inside_old_whole_underflow_domain': all_old_small,
                     'MACs': total_macs, 'MACs_potentially_omittable_with_full_exact_vector_dictionary': removed_macs,
                     'first_duplicate_batch': first})
    return {'run': run_id, 'plan_sha256': sha(plan_path), 'cases': rows, 'input_words_read': reads,
            'MACs': sum(c['MACs'] for c in rows),
            'raw_MAC_fraction': sum(c['MACs_potentially_omittable_with_full_exact_vector_dictionary'] for c in rows) / max(1, sum(c['MACs'] for c in rows)),
            'new_MACs_outside_old_whole_underflow': sum(c['MACs_potentially_omittable_with_full_exact_vector_dictionary'] for c in rows if not c['all_inputs_inside_old_whole_underflow_domain'])}


if __name__ == '__main__':
    start = time.monotonic()
    out = {'utc': datetime.now(timezone.utc).isoformat(), 'state': 'SOURCE_MODEL_ONLY',
           'generator_transcription_sha256': sha(old.GEN), 'runs': [],
           'semantics': 'Bit-identical complete A rows or B columns within the same batch yield the same ordered product/add fold, including signed zeros and NaN payload rules. No reassociation or numerical equality test is used.',
           'limits': 'Finite public generator transcription, not native input replay or all-workload coverage. MAC fractions are arithmetic-work counts, not removable-time bounds or predicted whole savings. Dictionary building, raw comparison, output allocation, fallback and shape cost are unmeasured. No new Kernel, Lean, CI, or confirmation data.'}
    for run_id in (40168687803, 40169957447, 40171180249):
        out['runs'].append(scan(run_id))
        if time.monotonic() - start > 45:
            out['state'] = 'PARTIAL_SOURCE_MODEL_45S_STOP'
            break
    out['elapsed_seconds'] = time.monotonic() - start
    (HERE / 'identical-matrix-vectors-screen.json').write_text(json.dumps(out, indent=2) + '\n')
    print(json.dumps({'state': out['state'], 'seconds': out['elapsed_seconds'], 'runs': [{k: r[k] for k in ('run', 'input_words_read', 'MACs', 'raw_MAC_fraction', 'new_MACs_outside_old_whole_underflow')} for r in out['runs']]}))
