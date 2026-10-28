"""Bounded exposed-input model for shared non-NaN input certificates.

No Lean, benchmark, hidden inputs, source tuning, or time-saving estimation.
Reference is a source transcription plus host binary32 arithmetic classification.
"""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import math
import struct
import time

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
GEN = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
tree = ast.parse(GEN.read_bytes())
nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in {'word', 'ctz', 'element'}
         or isinstance(n, ast.Assign) and any(isinstance(z, ast.Name) and z.id in {'M32', 'M64'} for z in n.targets)]
env = {}
exec(compile(ast.Module(body=nodes, type_ignores=[]), str(GEN), 'exec'), env)

def f32(bits):
    return struct.unpack('<f', struct.pack('<I', bits))[0]

def rounded(x):
    try:
        return struct.unpack('<f', struct.pack('<f', x))[0]
    except OverflowError:
        return math.copysign(float('inf'), x)

def main():
    begun = time.monotonic()
    budget, used = 100000, 0
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
            n, m, p, batch = (c[k] for k in ('n', 'm', 'p', 'batch'))
            # The transcribed generator's only NaN sources are raw mag=2 or
            # special kind 1. This is a source entailment, not a sampled all().
            guarantee = c['mag'] != 2 and (c['specRate'] == 0 or not (c['specMask'] & 2))
            row = {'name': c['name'], 'shape': [batch, m, n, p],
                   'recipe_guarantees_all_raw_inputs_nonNaN': guarantee,
                   'fixed_quad_domain': n > 1 and m >= 4 and p >= 2,
                   'case_share_whole_at_archived_control': times[c['name']]['best_ns'] / total,
                   'samples': []}
            if guarantee and row['fixed_quad_domain'] and batch:
                count = batch * (m // 4) * 4 * p
                ids = sorted({0, count - 1, env['word'](c['seed'], 0, 91) % count,
                              env['word'](c['seed'], 1, 91) % count})
                for q in ids:
                    if used + n > budget or time.monotonic() - begun > 4.5:
                        break
                    b, rest = divmod(q, (m // 4) * 4 * p)
                    i, j = divmod(rest, p)
                    acc = 0.0
                    first_nan = None
                    for k in range(n):
                        au = env['element'](c, (b * m + i) * n + k, 0, n)
                        bu = env['element'](c, b * n * p + k * p + j, 1, p)
                        a, value_b = f32(au), f32(bu)
                        assert not math.isnan(a) and not math.isnan(value_b)
                        acc = rounded(acc + rounded(a * value_b))
                        used += 1
                        if math.isnan(acc):
                            first_nan = k
                            break  # Native add/mul cannot recover a non-NaN accumulator.
                    row['samples'].append({'batch': b, 'row': i, 'column': j,
                                           'native_nan': math.isnan(acc), 'first_invalid_k': first_nan})
            cases.append(row)
        touched = [x for x in cases if x['recipe_guarantees_all_raw_inputs_nonNaN'] and x['fixed_quad_domain']]
        observed_nan_cases = [x for x in touched if any(s['native_nan'] for s in x['samples'])]
        runs.append({'seed': seed, 'plan_sha256': hashlib.sha256(plan_path.read_bytes()).hexdigest(),
                     'guaranteed_nonNaN_eligible_case_time_share': sum(x['case_share_whole_at_archived_control'] for x in touched),
                     'sample_native_nan_cases_whole_case_share': sum(x['case_share_whole_at_archived_control'] for x in observed_nan_cases),
                     'cases': cases})
    result = {'checked_utc': datetime.now(timezone.utc).isoformat(), 'state': 'BOUNDED_SOURCE_AND_HOST_MODEL',
              'MACs_evaluated': used, 'MAC_budget': budget, 'elapsed_seconds': time.monotonic() - begun,
              'generator_transcription_sha256': hashlib.sha256(GEN.read_bytes()).hexdigest(),
              'runs': runs,
              'limitations': 'Exposed discovery plans only. Generator transcription not freshly crosschecked against native input words. NaN classification ignores payload and is not a bitwise proof. Sample frequency is not a workload guarantee or removable-time bound. Whole-case shares include all original work and old guard overlap. No measured replay share or predicted saving.'}
    (HERE / 'native-image-exposure.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({'MACs': used, 'seconds': result['elapsed_seconds'], 'runs': [
        {k: r[k] for k in ('seed', 'guaranteed_nonNaN_eligible_case_time_share', 'sample_native_nan_cases_whole_case_share')}
        for r in runs]}, indent=2))

if __name__ == '__main__':
    main()
