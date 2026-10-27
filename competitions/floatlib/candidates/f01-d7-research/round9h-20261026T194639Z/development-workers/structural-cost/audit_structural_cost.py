"""Bounded, read-only source / retained-C / completed-B2 cost audit. No compilation."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re
import time

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
R15 = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z'
R16 = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/matrix-architecture'
KERNEL = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
EXPECTED = '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
start = time.monotonic()
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(KERNEL) == EXPECTED

old_audit_path = R15 / 'astra-workers/matrix-structure/b2-C-audit-401680.json'
old_audit = json.loads(old_audit_path.read_text(encoding='utf-8'))
bindings = []
original_index = json.loads((ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168024176/original-artifact-hashes.json').read_text())
for row in old_audit['bindings']:
    path = ROOT / row['path']
    assert sha(path) == row['sha256']
    if 'download-97e5567f5b7c4fc2a261a6d6dac40edc' in str(path):
        download = next(p for p in path.parents if p.name == 'download-97e5567f5b7c4fc2a261a6d6dac40edc')
        assert original_index['files'][path.relative_to(download).as_posix()]['sha256'] == sha(path)
    bindings.append(dict(path=str(path.relative_to(ROOT)), sha256=sha(path), bytes=path.stat().st_size))
cp = next(ROOT / row['path'] for row in old_audit['bindings'] if row['path'].endswith('candidate-generated-0.c'))
mp = next(ROOT / row['path'] for row in old_audit['bindings'] if row['path'].endswith('candidate-generated-1.c'))
lines = cp.read_text(encoding='utf-8').splitlines(keepends=True)
functions = {}
for i, line in enumerate(lines):
    m = re.match(r'(?:LEAN_EXPORT |static )?[^;\n]*\b([A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\{\s*$', line)
    if not m:
        continue
    depth = 0
    for j in range(i, len(lines)):
        depth += lines[j].count('{') - lines[j].count('}')
        if depth == 0:
            break
    functions[m.group(1)] = (i+1, j+1, ''.join(lines[i:j+1]))
tokens = ('lean_nat_add', 'lean_nat_mul', 'lean_nat_div', 'lean_nat_mod', 'lean_nat_dec_lt',
          'lean_array_get_size', 'lean_array_fget_borrowed', 'lean_array_uget_borrowed',
          'lean_float32_of_bits', 'lean_alloc_ctor', 'lean_alloc_closure',
          'lean_ctor_get_float32', 'lean_float32_mul', 'lean_float32_add')
selected = ('Submission_R15PackedB2_loop', 'Submission_R15PackedB2_packB___lam__0',
            'Submission_R15PackedB2_packB___lam__1', 'Submission_R15PackedB2_packB',
            'Submission_R15PackedB2_tileIndex___redArg',
            'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__0___redArg',
            'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__1',
            'Fin_foldl_loop___at___00Submission_R15ThinPairs_output_spec__0',
            'Submission_R15PackedB2_output', 'Submission_R15PackedB2_dispatch',
            'Submission_Packed10_finish', 'Submission_bmm')
frows = []
for name in selected:
    symbol = 'lp_competition_' + name
    lo, hi, body = functions[symbol]
    frows.append(dict(symbol=symbol, line_start=lo, line_end=hi,
                      body_sha256=hashlib.sha256(body.encode()).hexdigest(),
                      static_sites={t: body.count(t+'(') for t in tokens},
                      competition_calls=sorted(set(re.findall(r'\b(lp_competition_[A-Za-z0-9_]+)\(', body)[1:]))))
loop = functions['lp_competition_Submission_R15PackedB2_loop'][2]
assert loop.count('lean_float32_of_bits(') == 1
assert loop.count('lean_nat_add(') == 2
assert loop.count('lean_float32_mul(') == loop.count('lean_float32_add(') == 2
assert 'lean_alloc_ctor(0, 0, 8)' in loop
mainrefs = [dict(line=i+1, text=l) for i,l in enumerate(mp.read_text().splitlines())
            if 'Submission_bmm' in l or 'main___closed__4' in l or 'Bench_runFull(' in l or 'Bench_Suite_run(' in l]

groups = []
analysis = json.loads((R16 / 'analysis.json').read_text())
for group in analysis['groups']:
    paths = {k: ROOT / r['path'] for k,r in group['evidence'].items()}
    paths['input_kernel'] = paths['plan'].parent / 'inputs/f01-r15-dev-packed-b2-1/Kernel.lean'
    assert sha(paths['input_kernel']) == EXPECTED
    download = next(p for p in paths['plan'].parents if p.name.startswith('download-'))
    run_index_path = download.parent / 'original-artifact-hashes.json'
    run_index = json.loads(run_index_path.read_text())
    for k,p in paths.items():
        if k != 'input_kernel':
            assert sha(p) == group['evidence'][k]['sha256']
        assert run_index['files'][p.relative_to(download).as_posix()]['sha256'] == sha(p)
    plan, work, verdict = (json.loads(paths[k].read_text()) for k in ('plan','work','verdict'))
    assert verdict['passed'] and len(verdict['rounds']) == 25
    costs = {k: work[k] * c['submission_ns'] for k,c in verdict['classes'].items()}
    whole = sum(costs.values())
    bmm = sum(v for k,v in costs.items() if k.startswith('bmm:'))
    cases = [c for c in plan['cases'] if c['timed'] and c['kernel'] == 'bmm']
    target = [c for c in cases if 2 <= c['p'] <= 8 and c['n'] > 1 and c['m'] >= 4]
    cells = {':'.join(c['name'].split(':')[:2]) for c in target}
    b2upper = sum(costs[k] for k in cells) / whole
    events = dict(k_iterations=0, A_raw_reads=0, A_bitcasts=0, B2_record_reads=0,
                  scalar_mul_add_pairs=0, B2_results=0, B2_pack_records=0,
                  unchanged_raw_finish_calls=0, output_groups=0)
    shapes = []
    for c in target:
        b,m,n,p = (c[k] for k in ('batch','m','n','p'))
        G = (p+1)//2
        steps = b*m*G*n
        for key in ('k_iterations', 'A_raw_reads', 'A_bitcasts', 'B2_record_reads'):
            events[key] += steps
        events['scalar_mul_add_pairs'] += 2*steps
        events['B2_results'] += b*m*G
        events['B2_pack_records'] += b*G*n
        events['unchanged_raw_finish_calls'] += b*m*p
        events['output_groups'] += b*m*G
        shapes.append(dict(name=c['name'], shape={k:c[k] for k in ('batch','m','n','p')}, k_iterations=steps))
    groups.append(dict(run=group['run'], seed=group['seed'],
                       evidence={k:dict(path=str(p.relative_to(ROOT)),sha256=sha(p)) for k,p in paths.items()},
                       BMM_whole_measured_share=bmm/whole,
                       BMM_local_reduction_needed_for_10pct_whole=.10/(bmm/whole),
                       BMM_whole_reduction_if_2x=.5*bmm/whole,
                       B2_touched_class_whole_upper=b2upper,
                       B2_local_reduction_needed_for_10pct_at_upper=.10/b2upper,
                       B2_actual_time_lower=0,
                       target_shapes=len(target), target_classes=sorted(cells),
                       conditional_source_event_totals=events, target_rows=shapes))

record = dict(at_utc=datetime.now(timezone.utc).isoformat(),
              state='EXACT622D_STATIC_C_AND_COMPLETED_B2_COST_AUDIT',
              kernel=dict(path=str(KERNEL.relative_to(ROOT)),sha256=sha(KERNEL),bytes=KERNEL.stat().st_size),
              read_only_source_bindings=bindings,
              retained_audit=dict(path=str(old_audit_path.relative_to(ROOT)),sha256=sha(old_audit_path)),
              selected_functions=frows, mainfull_references=mainrefs,
              completed_groups=groups,
              proposal='B2_USize_raw_A_loop_without_A_panel_or_cross_row_tiles',
              exact_delta=dict(unchanged=['B packing', 'two independent ordered accumulators', 'all raw finish/replay calls',
                                           'output order', 'B2 dispatcher domain', 'all add/mul/sum code'],
                               per_k_remove=['two small-Nat additions', 'Nat comparison/tag handling',
                                             'A getD size/default branch', 'Nat index reference operations'],
                               per_k_keep=['raw A read', 'Float32.ofBits conversion', 'B2 borrowed read',
                                          'two original Float32 multiply/add chains'],
                               per_k_add=['USize comparison', 'two USize additions'],
                               new_preparation_allocations=0,
                               new_guard='n, baseA and A.size word-range plus end-of-row bound; fallback is exact old loop'),
              evidence_limits=['C source sites are not executed instruction counts or measured stage times',
                               'C was captured from statement/bench-build layer, not the timed ELF',
                               'Saved B2 ASM is diagnostic only and is not used as MainFull timing evidence',
                               'B2 event counts assume each shape enters B2 after underflow guard; actual entries UNKNOWN',
                               'Current public score aggregates classes, so target-path/stage time lower bound is zero',
                               'No claim of attainable 10pct whole gain; 10pct requires very large BMM-local reduction'],
              elapsed_seconds=time.monotonic()-start)
assert record['elapsed_seconds'] < 5
(HERE/'source-cost-audit.json').write_text(json.dumps(record, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
print(json.dumps(dict(state=record['state'],seconds=record['elapsed_seconds'],functions=len(frows),
                     groups=[{k:g[k] for k in ('run','BMM_whole_measured_share','BMM_local_reduction_needed_for_10pct_whole',
                                               'B2_touched_class_whole_upper','B2_local_reduction_needed_for_10pct_at_upper','target_shapes')}
                             for g in groups]), indent=2))
