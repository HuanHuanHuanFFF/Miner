"""Independent raw-log arithmetic and actual caller intake; no original parser."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
RUN = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40436948264'
matches = list(RUN.glob('download-*/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-add-cost1/add-cost/result.json'))
assert len(matches) == 1
folder = matches[0].parent
original = json.loads(matches[0].read_bytes())
assert original['complete'] and original['measurement_complete'] and original['official_originals_unchanged']
assert original['source_sha256'] == 'd3c550da05a3e91b5b037bed77623545dbe72af385d826ebc73236d2ed7ec2b5'
sha = lambda raw: hashlib.sha256(raw).hexdigest()
samples = {}
blocks = []
for seed in (1927003, 1927005):
    for order, variant in enumerate(('control', 'guarded', 'guarded', 'control')):
        path = folder / f'{seed}-{order}-{variant}.log'
        data = path.read_bytes()
        rows = {}
        for line in data.decode().splitlines():
            parts = line.split()
            assert len(parts) == 4 and parts[1] in ('true', 'false')
            label, timed, elapsed, checksum = parts
            assert label not in rows
            rows[label] = dict(timed=timed == 'true', ns=int(elapsed), checksum=int(checksum))
        assert len(rows) == 156 and sum(item['timed'] for item in rows.values()) == 152
        assert all(item['ns'] > 0 if item['timed'] else item['ns'] == 0 for item in rows.values())
        samples[(seed, order)] = rows
        baseline = samples[(seed, 0)]
        assert {key: (value['timed'], value['checksum']) for key, value in rows.items()} == {
            key: (value['timed'], value['checksum']) for key, value in baseline.items()}
    for block, (control, guarded) in enumerate(((0, 1), (3, 2))):
        values = {}
        expected = next(item for item in original['pairs'] if item['seed'] == seed)[f'block_{block}']
        for operation in ('add', 'mul', 'sum', 'bmm', 'whole'):
            labels = [key for key, item in samples[(seed, control)].items()
                      if item['timed'] and (operation == 'whole' or key.startswith(operation + ':'))]
            c = sum(samples[(seed, control)][key]['ns'] for key in labels)
            g = sum(samples[(seed, guarded)][key]['ns'] for key in labels)
            assert (c, g, len(labels)) == (expected[operation]['control_ns_sum'], expected[operation]['guarded_ns_sum'], expected[operation]['cases'])
            values[operation] = dict(control_ns=c, guarded_ns=g, ratio=g/c, cases=len(labels))
        blocks.append(dict(seed=seed, block=block, operations=values))
main = (folder / 'actual-new-main.c').read_text()
for name in ('r19CostControlAdd', 'r19CostGuardedAdd'):
    lines = [line for line in main.splitlines() if 'static const lean_closure_object' in line and name in line]
    assert len(lines) == 1 and '.m_arity = 2,' in lines[0] and '.m_num_fixed = 0,' in lines[0]
assert 'diagnosticEntry' not in main and 'lean_apply_' not in main
assert main.count('lp_competition_Bench_Suite_run(v_add_') == 1
result = dict(as_of_utc=datetime.now(timezone.utc).isoformat(), run=40436948264,
    source_sha256=original['source_sha256'], original_result_sha256=sha(matches[0].read_bytes()),
    caller_sha256=sha((folder/'actual-new-main.c').read_bytes()),
    raw_logs=[dict(file=path.name, sha256=sha(path.read_bytes())) for path in sorted(folder.glob('*.log')) if path.name != 'build.log'],
    independent_checks=['8 original logs parsed without driver parser', '156 unique rows and 152 timed per process',
        'all checksums preserved', 'all 4 operation and whole sums match published derived data',
        'two actual static arity2 zero-capture callbacks', 'single Suite invocation, no diagnosticEntry or dynamic apply'],
    blocks=blocks, decision='PARK_EXACT_D3_NO_LARGE_PUBLIC_ADD_PROOF_OR_RESEED',
    scope='One runner, two already exposed plans. Diagnostic relative cost; not original 25-round score or all-input ADD proof. Full caller/ASM cause audit separately retained.')
(HERE/'development-add-cost-parent-review.json').write_bytes((json.dumps(result, indent=2)+'\n').encode())
print(json.dumps(dict(run=result['run'], decision=result['decision'], blocks=[dict(seed=x['seed'], block=x['block'], add=x['operations']['add']['ratio'], whole=x['operations']['whole']['ratio']) for x in blocks])))
