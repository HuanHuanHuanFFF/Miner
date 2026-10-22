"""Checksum-anchored finite scalar-domain counts for exposed discovery seed 807 only.

No Lean execution, benchmark, upload or confirmation-plan access. R functions are
loaded verbatim from cached AST definitions, without executing their mains/imports.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import ast
import hashlib
import json
import time
import traceback

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
R = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7'
BASE = HERE.parent / 'f01-mul-log2-proof1/ci-runs/39840672791/download-81e3479e9e2b47249bf76c8d44eb2e62/diagnostics/f01-d7-public-suite/public-suite'
PROFILE = BASE / 'parent-stage-profile'
OUTPUT = HERE / 'scalar-opportunity-807.json'
FULL60F = '60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15'
M32 = (1 << 32) - 1
KEYS = ('pairs', 'finite_pairs', 'nonfinite_pairs', 'zero_pairs', 'both_zero_pairs',
        'exp_sum_lt_128_pairs', 'mul_outer_low_pairs', 'mul_low_zero_hits',
        'input_nan_words', 'input_nan_pairs', 'input_snan_words', 'input_snan_pairs',
        'input_inf_words', 'input_inf_pairs', 'output_nonnan', 'output_nan', 'output_inf',
        'nonfinite_input_nonnan_outputs', 'finite_input_inf_outputs',
        'output_snan', 'native_mul_path_pairs', 'native_mul_old_finite_accept_pairs',
        'native_mul_old_reject_finite_guard_pairs', 'native_mul_new_nonnan_accept_pairs',
        'native_mul_new_inf_accept_old_rejected_pairs', 'native_mul_existing_finite_input_inf_outputs')


def require(ok, message):
    if not ok:
        raise RuntimeError(message)


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def label(path):
    return path.relative_to(ROOT).as_posix()


def load_functions(raw, path, wanted, constants=()):
    tree = ast.parse(raw.decode('utf-8'))
    nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in wanted
             or isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in constants for t in n.targets)]
    require({n.name for n in nodes if isinstance(n, ast.FunctionDef)} == set(wanted), 'dependency function set differs')
    env = {}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(path), 'exec'), env)
    return env


def partner(c, i, a, element, word, fixed_b):
    w = word(c['seed'], i, 31)  # draw c i 1 15
    relation = c['relation']
    if relation == 1:
        return a
    if relation == 2:
        return a ^ 0x80000000
    if relation in (3, 7):
        mask = (1 << min(23, c['relParam'])) - 1
        b = (a & (M32 ^ mask)) | (w & mask)
        return b ^ 0x80000000 if relation == 3 else b
    if relation == 4:
        return fixed_b
    if relation == 5:
        if w % 100 < c['relParam']:
            return (w & 0x80000000) | (0 if c['kernel'] == 'add' else 0x3f800000)
        return element(c, i, 1, 31)
    if relation == 6:
        exponent = (a >> 23) & 255
        if exponent in (0, 255):
            return element(c, i, 1, 31)
        return (w & 0x807fffff) | (max(1, min(254, exponent - c['relParam'])) << 23)
    return element(c, i, 1, 31)


def analyze_case(c, generator, oracle, deadline):
    stats = dict.fromkeys(KEYS, 0)
    element, word, op = generator['element'], generator['word'], oracle[c['kernel']]
    fixed_b = element(c, 0, 1, 31) if c['relation'] == 4 else None
    checksum = 0
    inputs, outputs = hashlib.sha256(), hashlib.sha256()
    witnesses = {}
    for i in range(c['work']):
        if i % 8192 == 0:
            require(time.monotonic() < deadline, 'local analysis time limit reached')
        a = element(c, i, 0, 31)
        b = partner(c, i, a, element, word, fixed_b)
        q = op(a, b)
        ea, eb = (a >> 23) & 255, (b >> 23) & 255
        fa, fb = a & 0x7fffff, b & 0x7fffff
        na, nb = ea == 255 and fa != 0, eb == 255 and fb != 0
        sa, sb = na and (a & 0x400000) == 0, nb and (b & 0x400000) == 0
        ia, ib = ea == 255 and fa == 0, eb == 255 and fb == 0
        za, zb = (a & 0x7fffffff) == 0, (b & 0x7fffffff) == 0
        finite = ea != 255 and eb != 255
        low = ea + eb < 128
        out_nan = (q & 0x7f800000) == 0x7f800000 and (q & 0x7fffff) != 0
        out_inf = (q & 0x7fffffff) == 0x7f800000
        out_snan = out_nan and (q & 0x400000) == 0
        is_mul = c['kernel'] == 'mul'
        hit = is_mul and low and (za or zb)
        native = is_mul and not low
        new_inf = native and not finite and out_inf
        stats['pairs'] += 1
        stats['finite_pairs'] += finite
        stats['nonfinite_pairs'] += not finite
        stats['zero_pairs'] += za or zb
        stats['both_zero_pairs'] += za and zb
        stats['exp_sum_lt_128_pairs'] += low
        stats['mul_outer_low_pairs'] += is_mul and low
        stats['mul_low_zero_hits'] += hit
        stats['input_nan_words'] += na + nb
        stats['input_nan_pairs'] += na or nb
        stats['input_snan_words'] += sa + sb
        stats['input_snan_pairs'] += sa or sb
        stats['input_inf_words'] += ia + ib
        stats['input_inf_pairs'] += ia or ib
        stats['output_nonnan'] += not out_nan
        stats['output_nan'] += out_nan
        stats['output_inf'] += out_inf
        stats['nonfinite_input_nonnan_outputs'] += not finite and not out_nan
        stats['finite_input_inf_outputs'] += finite and out_inf
        stats['output_snan'] += out_snan
        stats['native_mul_path_pairs'] += native
        stats['native_mul_old_finite_accept_pairs'] += native and finite
        stats['native_mul_old_reject_finite_guard_pairs'] += native and not finite
        stats['native_mul_new_nonnan_accept_pairs'] += native and not out_nan
        stats['native_mul_new_inf_accept_old_rejected_pairs'] += new_inf
        stats['native_mul_existing_finite_input_inf_outputs'] += native and finite and out_inf
        if hit:
            require(finite and q == ((a ^ b) & 0x80000000), 'low-zero exact-word identity failed')
            witnesses.setdefault('mul_low_zero', {'index': i, 'a': hex(a), 'b': hex(b), 'output': hex(q)})
        if new_inf:
            witnesses.setdefault('new_inf_accept_old_rejected', {'index': i, 'a': hex(a), 'b': hex(b), 'output': hex(q)})
        require(not out_snan, 'oracle produced a signaling NaN')
        checksum = ((checksum ^ q) * 16777619) & M32
        inputs.update(a.to_bytes(4, 'little') + b.to_bytes(4, 'little'))
        outputs.update(q.to_bytes(4, 'little'))
    require(stats['pairs'] == c['work'], 'incomplete case')
    require(stats['finite_pairs'] + stats['nonfinite_pairs'] == stats['pairs'], 'input partition failed')
    require(stats['output_nan'] + stats['output_nonnan'] == stats['pairs'], 'output partition failed')
    return {'name': c['name'], 'kernel': c['kernel'], 'timed': c['timed'], 'case': c, 'counts': stats,
            'checksum32': checksum, 'input_pairs_le_sha256': inputs.hexdigest(),
            'output_words_le_sha256': outputs.hexdigest(), 'witnesses': witnesses}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--max-seconds', type=int, default=600)
    args = ap.parse_args()
    require(1 <= args.max_seconds <= 720, 'local budget must be 1..720 seconds')
    started = time.monotonic()
    dependencies = [R / 'public-nonfinite-opportunity.py', R / 'nonfinite-oracle.py', R / 'upstream/BenchSuite.lean']
    cached = {p: p.read_bytes() for p in dependencies}
    before = {label(p): sha(raw) for p, raw in cached.items()}
    plan_path = BASE / 'public-drawn-plan.json'
    verdict_path = BASE / 'f01-d7-direct-nonnan-verdict.json'
    source_paths = [plan_path, verdict_path, PROFILE / 'profile-current-plan.json', PROFILE / 'profile-current-control-0.json']
    source_paths += [PROFILE / f'profile-current-instrumented-{i}.json' for i in range(3)]
    raw_inputs = {p: p.read_bytes() for p in source_paths}
    plan = json.loads(raw_inputs[plan_path])
    require(sha(raw_inputs[plan_path]) == '9cc5d7368749c369172b019d66bc4cd8455ae4323d0b9a175bd031f936e78622', 'frozen 807 discovery plan hash differs')
    verdict = json.loads(raw_inputs[verdict_path])
    profile_plan = json.loads(raw_inputs[PROFILE / 'profile-current-plan.json'])
    require(verdict['seed'] == profile_plan['seed'] == 807, 'only exposed discovery seed 807 is allowed')
    require(verdict['submission'] == 'f01-d7-direct-nonnan' and verdict['passed'] and verdict['stage'] == 'score'
            and verdict['mode'] == 'gate' and len(verdict['rounds']) == 25, 'missing original FULL60f full-gate evidence')
    stored_kernel = BASE / 'inputs/f01-d7-direct-nonnan/Kernel.lean'
    require(sha(stored_kernel.read_bytes()) == FULL60F, 'FULL60f exact input hash differs')
    require(plan['version'] == 'suite-v2', 'expected suite-v2 plan')
    expected = {c['name'] for c in plan['cases']}
    require(len(expected) == len(plan['cases']), 'duplicate plan case names')
    logs = {'control': json.loads(raw_inputs[PROFILE / 'profile-current-control-0.json'])}
    for i in range(3):
        logs[f'instrumented_{i}'] = json.loads(raw_inputs[PROFILE / f'profile-current-instrumented-{i}.json'])['benchmark_rows']
    require(all(len(rows) == len(expected) and set(rows) == expected for rows in logs.values()), 'saved benchmark row coverage differs')
    generator = load_functions(cached[dependencies[0]], dependencies[0], ('word', 'ctz', 'element'), ('M64', 'M32'))
    oracle = load_functions(cached[dependencies[1]], dependencies[1],
                            ('exp', 'frac', 'nan', 'snan', 'inf', 'zero', 'canon', 'choose', 'unpack', 'rounded', 'add', 'mul'))
    work = {cell: sum(c['work'] for c in plan['cases'] if c['timed'] and c['name'].rsplit(':', 1)[0] == cell)
            for cell in verdict['classes']}
    cells = {cell: verdict['classes'][cell]['submission_ns'] * units for cell, units in work.items()}
    total_ns = sum(cells.values())
    result = {'status': 'RUNNING', 'complete': False, 'discovery_seed': 807, 'started_at_utc': datetime.now(timezone.utc).isoformat(),
              'scope': 'Finite exact-integer/transcribed-generator model on exposed 807 inputs, checksum-anchored to actual Lean output. No Lean proof, native Float32 execution, new timing, private prevalence, future confirmation or gain claim.',
              'loading': 'Cached AST function definitions only; R mains/imports never executed; no bytecode files.',
              'native_domain_model': 'Output nonNaN uses exact oracle output classification, corresponding to the source-derived canonical-native model, not measured hardware.',
              'dependencies_before': before, 'inputs_sha256': {label(p): sha(raw) for p, raw in raw_inputs.items()},
              'full60f_kernel_sha256': FULL60F, 'analysis_source_sha256': sha(Path(__file__).read_bytes()),
              'full60f_input': label(stored_kernel),
              'benchmark_cases_total': len(expected),
              'benchmark_timed_cases': sum(c['timed'] for c in plan['cases']),
              'benchmark_untimed_cases': sum(not c['timed'] for c in plan['cases']),
              'scalar_cases_expected': 86, 'scalar_timed_cases': 84, 'scalar_untimed_cases': 2,
              'case_count_scope': '156 total output cases = 152 timed scoring cases + 4 raw checksum cases. Scalars contain 43 add and 43 mul cases, including one raw per operation.',
              'pass_counting': 'One original checksum pass per scalar case (seed0). Timed cases repeat the same operand domain for inner3; these counts are not time shares.',
              'checksum_scope': '86 rolling 32-bit checksums checked against four repeated actual records, not per-output Lean comparison or independent confirmation. Equality does not replace a proof.',
              'counter_definitions': {'finite_pairs': 'Both raw input exponents differ from255.',
                                      'nonfinite_pairs': 'At least one raw input exponent equals255.',
                                      'zero_pairs': 'At least one signed-zero input word.',
                                      'exp_sum_lt_128_pairs': 'Input attribute on both operations; only mul actually dispatches on this condition.',
                                      'mul_low_zero_hits': 'Actual outer mul low path and at least one signed-zero operand.',
                                      'native_mul_old_reject_finite_guard_pairs': 'exSum>=128 and at least one input NaN/Inf; counts rejected pairs, not predicate invocations.',
                                      'native_mul_new_inf_accept_old_rejected_pairs': 'Old nativeMul input-finite guard rejects, but exact/canonical-native output is Inf and a nonNaN output guard would accept.'},
              'full60f_time_ceiling': {'verdict': label(verdict_path), 'total_submission_ns': total_ns,
                                       'cell_submission_total_ns': cells,
                                       'cell_all_timed_share': {cell: value / total_ns for cell, value in cells.items()},
                                       'note': 'Each cell is an upper bound shared by all its cases. Counts do not allocate any fraction of that time to an opportunity.'},
              'cases': []}
    error = None
    try:
        for case in plan['cases']:
            if case['kernel'] not in ('add', 'mul'):
                continue
            row = analyze_case(case, generator, oracle, started + args.max_seconds)
            row['checksum_comparisons'] = {name: {'expected': rows[case['name']]['checksum'],
                                                  'actual': row['checksum32'],
                                                  'match': rows[case['name']]['checksum'] == row['checksum32']}
                                            for name, rows in logs.items()}
            cell = case['name'].rsplit(':', 1)[0]
            row['shared_cell_time_ceiling_ns'] = cells[cell] if case['timed'] else None
            result['cases'].append(row)
            require(all(c['match'] for c in row['checksum_comparisons'].values()), f"actual Lean checksum mismatch: {case['name']}")
            print(json.dumps({'case': case['name'], 'checksum': 'MATCH_ALL4', 'pairs': row['counts']['pairs'],
                              'low_zero_hits': row['counts']['mul_low_zero_hits'],
                              'new_inf_accept': row['counts']['native_mul_new_inf_accept_old_rejected_pairs']}), flush=True)
        require(len(result['cases']) == 86, 'not all scalar cases were processed')
        totals = {}
        for op in ('add', 'mul'):
            totals[op] = {phase: {k: sum(r['counts'][k] for r in result['cases'] if r['kernel'] == op and (phase == 'all' or r['timed'] == (phase == 'timed')))
                                  for k in KEYS} for phase in ('all', 'timed', 'raw')}
        result['totals'] = totals
        ceilings = {}
        for metric in ('mul_low_zero_hits', 'native_mul_old_reject_finite_guard_pairs', 'native_mul_new_inf_accept_old_rejected_pairs', 'output_nan'):
            affected = sorted({r['name'].rsplit(':', 1)[0] for r in result['cases'] if r['timed'] and r['counts'][metric]})
            ceilings[metric] = {'affected_timed_cells': affected, 'whole_cell_total_ns_upper_bound': sum(cells[c] for c in affected),
                                'whole_cell_all_timed_share_upper_bound': sum(cells[c] for c in affected) / total_ns,
                                'gain': 'UNKNOWN', 'note': 'Entire affected-cell exposure ceiling, not the time used by counted pairs.'}
        result['opportunity_exposure_ceilings'] = ceilings
        result.update(status='PASS_FINITE_MODEL_CHECKSUMS', complete=True, checksum_comparisons=86 * 4,
                      all_scalar_checksums_match_actual_lean=True, lean_proof='NOT_RUN_BY_THIS_ANALYSIS', gain='UNKNOWN')
    except Exception as exc:
        error = exc
        result.update(status='FAILED_OR_INCOMPLETE', complete=False, error=str(exc), traceback=traceback.format_exc())
    finally:
        after = {label(p): sha(p.read_bytes()) for p in dependencies}
        result['dependencies_after'] = after
        result['dependencies_unchanged'] = before == after
        result['inputs_unchanged'] = all(p.read_bytes() == raw for p, raw in raw_inputs.items())
        if not result['dependencies_unchanged'] or not result['inputs_unchanged']:
            result.update(status='FAILED_SOURCE_DRIFT', complete=False)
            error = RuntimeError('dependency or exact input changed during analysis')
        result['completed_at_utc'] = datetime.now(timezone.utc).isoformat()
        result['analysis_seconds'] = time.monotonic() - started
        OUTPUT.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    if error:
        raise error
    print(json.dumps({'status': result['status'], 'analysis_seconds': result['analysis_seconds'],
                      'scalar_cases': len(result['cases']), 'checksum_comparisons': result['checksum_comparisons'],
                      'totals': result['totals'], 'opportunity_exposure_ceilings': result['opportunity_exposure_ceilings']}, indent=2))


if __name__ == '__main__':
    main()
