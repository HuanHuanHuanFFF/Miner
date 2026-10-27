"""Bounded input-domain check on already exposed old research inputs only."""
from pathlib import Path
from hashlib import sha256
from time import monotonic
import ast, json, random

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[6]
start = monotonic()

def functions(path, names, constants=()):
    tree = ast.parse(path.read_bytes())
    nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in names
             or isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in constants for t in n.targets)]
    env = {}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(path), 'exec'), env)
    return env

gen = ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
partner = ROOT/'competitions/floatlib/candidates/f01-d7-research/scalar-opportunity.py'
oracle = ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
assert sha256(gen.read_bytes()).hexdigest() == '28eb38c9388f595960ea039e18b5783984cb2a0b0cdb182011449a0cd146e7a1'
g = functions(gen, {'word','ctz','element'}, {'M32','M64'})
s = functions(partner, {'partner'}, {'M32'})
o = functions(oracle, {'exp','frac','nan','snan','inf','zero','canon','choose','unpack','rounded','add','mul'})
run = ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357'
idx = json.loads((run/'original-artifact-hashes.json').read_bytes())
plan_path = run/idx['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
plan = json.loads(plan_path.read_bytes())
rng = random.Random(192700001)
rows, checks, nonzero_hits, total = [], 0, 0, 0
for c in plan['cases']:
    if c['kernel'] != 'mul' or not c['timed']:
        continue
    length = c['work']
    positions = sorted(rng.sample(range(length), min(length, 256)))
    counts = dict(sum_le84=0, sum_le102=0, zero_input=0, low_lt128=0)
    fixed = g['element'](c, 0, 1, 31)
    for i in positions:
        total += 1
        assert total <= 12000 and monotonic()-start < 3
        a = g['element'](c,i,0,31)
        b = s['partner'](c,i,a,g['element'],g['word'],fixed)
        exp_sum = ((a>>23)&255) + ((b>>23)&255)
        iszero = (a & 0x7fffffff) == 0 or (b & 0x7fffffff) == 0
        counts['sum_le84'] += exp_sum <= 84
        counts['sum_le102'] += exp_sum <= 102
        counts['zero_input'] += iszero
        counts['low_lt128'] += exp_sum < 128
        if exp_sum <= 84:
            assert o['mul'](a,b) == ((a^b)&0x80000000)
            checks += 1
            nonzero_hits += not iszero
    rows.append(dict(case=c['name'],work=length,samples=len(positions),counts=counts))
weight = sum(r['work'] for r in rows)
out = dict(status='FINITE_INPUT_COUNTS_AND_INTEGER_ORACLE_ONLY', old_run=40124283357,
           input_plan_sha256=sha256(plan_path.read_bytes()).hexdigest(),
           sampled_pairs=total, zero_identity_checks=checks, nonzero_operand_hits=nonzero_hits,
           work_weighted_input_fraction={k:sum(r['work']*r['counts'][k]/r['samples'] for r in rows)/weight for k in rows[0]['counts']},
           elapsed_seconds=monotonic()-start,
           dependencies={str(p.relative_to(ROOT)):sha256(p.read_bytes()).hexdigest() for p in (gen,partner,oracle)},
           scope='Input counts are not time shares. Existing disclosed research inputs only; no fresh confirmation group. No Lean/full gate/native timing or guaranteed gain.', cases=rows)
(HERE/'exposure.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='cases'},indent=2))
