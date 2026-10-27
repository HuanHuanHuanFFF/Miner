"""Bounded exposed-input opportunity map; no runtime candidate or timing claim."""
from pathlib import Path
from hashlib import sha256
from time import monotonic
from datetime import datetime, timezone
import ast
import json
import random

base = Path(__file__).resolve().parent
root = base.parents[4]
start, budget_seconds, max_pairs = monotonic(), 3.0, 12000

def functions(path, names, constants):
    tree = ast.parse(path.read_bytes())
    nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in names
             or isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in constants
                                                  for t in n.targets)]
    env = {}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(path), 'exec'), env)
    return env

generator = root / 'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
assert sha256(generator.read_bytes()).hexdigest() == '28eb38c9388f595960ea039e18b5783984cb2a0b0cdb182011449a0cd146e7a1'
partner = root / 'competitions/floatlib/candidates/f01-d7-research/scalar-opportunity.py'
g = functions(generator, {'word', 'ctz', 'element'}, {'M32', 'M64'})
s = functions(partner, {'partner'}, {'M32'})
run = root / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357'
idx = json.loads((run / 'original-artifact-hashes.json').read_bytes())
plan_path = run / idx['directory'] / 'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
plan = json.loads(plan_path.read_bytes())
rng = random.Random(202610242300)
rows, count = [], 0
for case in plan['cases']:
    if case['kernel'] != 'add' or not case['timed']:
        continue
    length = case['work']
    size = min(length, 256)
    positions = list(range(length)) if length <= size else [0, length-1] + rng.sample(range(1, length-1), size-2)
    counts = dict(current_domain=0, same_exponent_same_sign=0,
                  same_exponent_same_sign_finite_result=0,
                  opposite_gap1_h_ge24=0, opposite_gap1_h_ge23=0)
    fixed_b = g['element'](case, 0, 1, 31)
    for pos in positions:
        count += 1
        assert count <= max_pairs and monotonic() - start < budget_seconds
        a = g['element'](case, pos, 0, 31)
        b = s['partner'](case, pos, a, g['element'], g['word'], fixed_b)
        ea, eb = (a >> 23) & 255, (b >> 23) & 255
        if not (1 <= ea <= 254 and 1 <= eb <= 254):
            continue
        gap, same = abs(ea-eb), ((a^b) >> 31) == 0
        hi, lo = (a,b) if ea >= eb else (b,a)
        n = (((hi & 0x7fffff)|0x800000) << gap)
        n = n + ((lo&0x7fffff)|0x800000) if same else n - ((lo&0x7fffff)|0x800000)
        counts['same_exponent_same_sign'] += gap == 0 and same
        counts['same_exponent_same_sign_finite_result'] += gap == 0 and same and ea <= 253
        counts['opposite_gap1_h_ge24'] += gap == 1 and not same and n >= 2**24
        counts['opposite_gap1_h_ge23'] += gap == 1 and not same and n >= 2**23
        if gap <= 7 and (same or gap >= 2):
            h = n.bit_length()-1
            t = h - 23
            q,r = divmod(n,2**t)
            rounded=q+int(2*r>2**t or (2*r==2**t and q%2==1))
            exponent=h+min(ea,eb)-23+int(rounded==2**24)
            counts['current_domain'] += exponent <= 254
    rows.append(dict(case=case['name'], work=length, samples=size, counts=counts))
weight = sum(r['work'] for r in rows)
fractions = {key:sum(r['work']*r['counts'][key]/r['samples'] for r in rows)/weight
             for key in rows[0]['counts']}
prior = json.loads((base / 'development-word-add-screen.json').read_bytes())
assert abs(fractions['current_domain'] - prior['work_weighted_input_fractions']['accepted']) < 1e-15
receipt = dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
               script_sha256=sha256(Path(__file__).read_bytes()).hexdigest(),
               plan_sha256=sha256(plan_path.read_bytes()).hexdigest(),
               generator_sha256=sha256(generator.read_bytes()).hexdigest(),
               partner_sha256=sha256(partner.read_bytes()).hexdigest(),
               run=40124283357, seed_scope='same already-exposed D1 positions as development screen',
               budget_seconds=budget_seconds, max_pairs=max_pairs,
               elapsed_seconds=monotonic()-start, pairs=count,
               state='INPUT_DIAGNOSTIC_ONLY_NO_RUNTIME_OR_CI',
               work_weighted_input_fractions=fractions, cases=rows,
               scope='Input counts are not operation cost, speed, all-input proof or independent confirmation. Additional domains are paper options; do not expand D runtime queue.')
Path(__file__).with_suffix('.json').write_text(json.dumps(receipt,indent=2)+'\n', encoding='utf-8')
print(json.dumps({k:v for k,v in receipt.items() if k!='cases'}, indent=2))
