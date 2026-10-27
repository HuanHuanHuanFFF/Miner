"""Cheap falsifier for a distinct exact fixed-point SUM/BMM certificate route.

Uses only old disclosed draws and a source-derived integer oracle. No Lean,
timing, future confirmation, or claim that input frequency equals cost.
"""
from pathlib import Path
from hashlib import sha256
from time import monotonic
import ast, json, random

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
start = monotonic()

def functions(path, names, constants=()):
    tree = ast.parse(path.read_bytes())
    nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in names
             or isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in constants for t in n.targets)]
    env = {}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(path), 'exec'), env)
    return env

gen = ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
oracle = ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
assert sha256(gen.read_bytes()).hexdigest() == '28eb38c9388f595960ea039e18b5783984cb2a0b0cdb182011449a0cd146e7a1'
g = functions(gen, {'word','ctz','element'}, {'M32','M64'})
o = functions(oracle, {'exp','frac','nan','snan','inf','zero','canon','choose','unpack','rounded','add','mul','summation','dot'})
run = ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357'
idx = json.loads((run/'original-artifact-hashes.json').read_bytes())
plan_path = run/idx['directory']/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
plan = json.loads(plan_path.read_bytes())
rng = random.Random(192700002)
rows, checks, terms = [], 0, 0

def normalized(m,e):
    if not m:
        return 0,0
    tz = (abs(m)&-abs(m)).bit_length()-1
    return m>>tz,e+tz

def certificate(xs,ys=None):
    global terms
    if any(o['exp'](x)==255 for x in xs) or ys is not None and any(o['exp'](y)==255 for y in ys):
        return dict(eligible=False,reason='nonfinite')
    unpacked = [o['unpack'](x) for x in xs]
    if ys is not None:
        unpacked = [(a*b,ea+eb) for (a,ea),(b,eb) in zip(unpacked,map(o['unpack'],ys))]
    parts = [normalized(m,e) for m,e in unpacked if m]
    terms += len(unpacked)
    # The exact old plan has at most151254 planned terms for these three outputs.
    assert terms <= 160000 and monotonic()-start < 3
    if not parts:
        emin,bound,qsum = 0,0,0
    else:
        emin = min(e for m,e in parts)
        qs = [m<<(e-emin) for m,e in parts]
        bound,qsum = sum(map(abs,qs)),sum(qs)
    eligible = bound <= 2**24 and -149 <= emin <= 103
    record = dict(eligible=eligible,reason='fits' if eligible else 'quantum_or_prefix_bound',
                  quantum=emin,absolute_bound_bits=bound.bit_length(),length=len(xs))
    if eligible:
        expected = o['rounded'](qsum,emin)
        actual = o['summation'](xs) if ys is None else o['dot'](xs,ys)
        assert actual == expected, (record,hex(actual),hex(expected))
        record.update(original_oracle=hex(actual),exact_integer_result=hex(expected))
    return record

for c in plan['cases']:
    if c['kernel'] not in ('sum','bmm') or not c['timed']:
        continue
    if c['kernel']=='sum':
        count,n = c['batch'],c['length']
    else:
        count,n = c['batch']*c['m']*c['p'],c['n']
    if not count:
        continue
    positions = sorted({0,count-1,rng.randrange(count)})
    samples = []
    for q in positions:
        if c['kernel']=='sum':
            xs = [g['element'](c,q*n+k,0,n) for k in range(n)]
            row = certificate(xs)
        else:
            b,r = divmod(q,c['m']*c['p'])
            i,j = divmod(r,c['p'])
            xs = [g['element'](c,(b*c['m']+i)*n+k,0,n) for k in range(n)]
            ys = [g['element'](c,(b*n+k)*c['p']+j,1,c['p']) for k in range(n)]
            row = certificate(xs,ys)
        row['output_index'] = q
        samples.append(row)
        checks += row['eligible']
    rows.append(dict(case=c['name'],kernel=c['kernel'],work=c['work'],length=n,samples=samples))

summary={}
for op in ('sum','bmm'):
    rs=[r for r in rows if r['kernel']==op]
    total_work=sum(r['work'] for r in rs)
    summary[op]=dict(sampled_outputs=sum(len(r['samples']) for r in rs),
                     eligible_outputs=sum(s['eligible'] for r in rs for s in r['samples']),
                     work_weighted_sampled_eligible_fraction=sum(r['work']*sum(s['eligible'] for s in r['samples'])/len(r['samples']) for r in rs)/total_work,
                     eligible_cases=[r['case'] for r in rs if any(s['eligible'] for s in r['samples'])],
                     long_eligible_cases=[r['case'] for r in rs if r['length']>1 and any(s['eligible'] for s in r['samples'])])
counterexample=[0x4b800000,0x3f800000,0xcb800000]
record=dict(status='FINITE_CERTIFICATE_PREFLIGHT_ONLY',old_run=40124283357,
            plan_sha256=sha256(plan_path.read_bytes()).hexdigest(),
            source_hashes={str(p.relative_to(ROOT)):sha256(p.read_bytes()).hexdigest() for p in (gen,oracle)},
            certificate='Terms=q_i*2^e, -149<=e<=103, sum(abs(q_i))<=2^24; then every product and sequential prefix exactly representable.',
            guard_implementation='UNKNOWN; per-output best quantum is more permissive than a global prepared-array guard; preparation and failures must be paid.',
            summary=summary,terms_examined=terms,eligible_identity_checks=checks,
            unconstrained_round_elimination_counterexample=dict(words=[hex(x) for x in counterexample],sequential=hex(o['summation'](counterexample)),exact_sum_once=hex(o['rounded'](1,0))),
            elapsed_seconds=monotonic()-start,
            scope='3 old disclosed outputs per case at most. Input coverage only, not time/whole gain/probability. Common integer oracle, not independent Float32/Lean. No new candidate or CI.',cases=rows)
(HERE/'astra-quantized-certificate.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in record.items() if k!='cases'},indent=2))
