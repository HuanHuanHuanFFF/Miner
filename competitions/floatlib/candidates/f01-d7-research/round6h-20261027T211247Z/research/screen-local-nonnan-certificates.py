"""Small source-model screen of row/column certificates, not runtime evidence."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import math
import time

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('native_image_screen', HERE / 'screen-native-image-exposure.py')
S = importlib.util.module_from_spec(spec)
spec.loader.exec_module(S)

def nan_word(u):
    return (u & 0x7fffffff) > 0x7f800000

def main():
    begun = time.monotonic()
    reads = macs = 0
    cap = 100000
    base = HERE.parent / 'ci-runs/40586463637'
    index = json.loads((base / 'original-artifact-hashes.json').read_bytes())
    cost = base / index['directory'] / 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-runtime-cost1/runtime-cost'
    runs = []
    for seed in (2220001, 2220003):
        plan_path = cost / f'plan-{seed}.json'
        plan = json.loads(plan_path.read_bytes())
        times = json.loads((cost / f'{seed}-0-control-rows.json').read_bytes())
        total = sum(v['best_ns'] for v in times.values() if v['timed'])
        cases = []
        for c in plan['cases']:
            if c['kernel'] != 'bmm' or not c['timed']:
                continue
            batch, m, n, p = (c[k] for k in ('batch', 'm', 'n', 'p'))
            if not (batch and m >= 4 and n > 1 and p >= 2):
                continue
            row = {'name': c['name'], 'shape': [batch, m, n, p],
                   'case_share_whole': times[c['name']]['best_ns'] / total,
                   'global_B_NaN_witness': None, 'samples': []}
            for i in range(min(64, batch * n * p)):
                value = S.env['element'](c, i, 1, p)
                reads += 1
                if nan_word(value):
                    row['global_B_NaN_witness'] = {'index': i, 'word': hex(value)}
                    break
            count = batch * (m // 4) * 4 * p
            ids = sorted({0, count - 1, S.env['word'](c['seed'], 0, 91) % count,
                          S.env['word'](c['seed'], 1, 91) % count})
            for q in ids:
                if reads + 2 * n > cap or time.monotonic() - begun > 4.5:
                    break
                b, rest = divmod(q, (m // 4) * 4 * p)
                i, j = divmod(rest, p)
                aa = [S.env['element'](c, (b * m + i) * n + k, 0, n) for k in range(n)]
                bb = [S.env['element'](c, b * n * p + k * p + j, 1, p) for k in range(n)]
                reads += 2 * n
                certificate = not any(map(nan_word, aa)) and not any(map(nan_word, bb))
                sample = {'batch': b, 'row': i, 'column': j, 'local_input_certificate': certificate,
                          'native_nan': None, 'first_invalid_k': None}
                if certificate:
                    acc = 0.0
                    for k, (au, bu) in enumerate(zip(aa, bb)):
                        acc = S.rounded(acc + S.rounded(S.f32(au) * S.f32(bu)))
                        macs += 1
                        if math.isnan(acc):
                            sample['first_invalid_k'] = k
                            break
                    sample['native_nan'] = math.isnan(acc)
                row['samples'].append(sample)
            cases.append(row)
        positives = [r for r in cases if any(s['native_nan'] for s in r['samples'])]
        missed = [r for r in positives if r['global_B_NaN_witness'] is not None]
        runs.append({'seed': seed, 'plan_sha256': hashlib.sha256(plan_path.read_bytes()).hexdigest(),
                     'sampled_outputs': sum(len(r['samples']) for r in cases),
                     'certified_native_nan_outputs': sum(s['native_nan'] is True for r in cases for s in r['samples']),
                     'native_nan_case_names': [r['name'] for r in positives],
                     'whole_case_share_of_sample_positive_cases': sum(r['case_share_whole'] for r in positives),
                     'whole_case_share_also_missed_by_global_B_certificate': sum(r['case_share_whole'] for r in missed),
                     'cases': cases})
    result = {'checked_utc': datetime.now(timezone.utc).isoformat(), 'state': 'BOUNDED_SOURCE_AND_HOST_MODEL',
              'word_reads': reads, 'word_read_cap': cap, 'MACs': macs, 'elapsed_seconds': time.monotonic() - begun,
              'generator_transcription_sha256': hashlib.sha256(S.GEN.read_bytes()).hexdigest(), 'runs': runs,
              'limitations': 'Exposed discovery only; source generator not freshly checked against actual native input words. NaN flags ignore payload, not bitwise proof. Whole-case shares include all original work and are not predicted saved time. Samples are not frequency guarantees or an upper bound on all reachable NaN cases. Global witness is a model counterexample to a global certificate, not native output evidence.'}
    (HERE / 'local-nonnan-certificate-exposure.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({k: result[k] for k in ('word_reads', 'MACs', 'elapsed_seconds')}))
    for r in runs:
        print(json.dumps({k: v for k, v in r.items() if k != 'cases'}))

if __name__ == '__main__':
    main()
