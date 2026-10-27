"""Bounded exact-cancellation diagnostic; only completed R15 exposed plans.
Python bit model, not Lean, generated target code, or performance evidence.
"""
from pathlib import Path
from datetime import datetime, timezone
from collections import defaultdict
import hashlib, json, random, runpy, struct, subprocess, sys, time

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p/'AGENTS.md').exists())
GEN = ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-public-input-domain.py'
RUNS = (40168687803, 40169957447, 40171180249)
BASE = ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
BASE_SHA = '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
B = 1 << 23

def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
def exp(u): return (u >> 23) & 255
def mant(u): return (u & (B-1)) | B

def exact_integer_units(u):
    e, f = exp(u), u & (B-1)
    assert e != 255
    q = f if e == 0 else (B+f) << (e-1)
    return -q if u >> 31 else q

def reference(u, v):
    # Independent exact units of 2^-149, followed by general integer RNE.
    z = exact_integer_units(u) + exact_integer_units(v)
    if z == 0: return 0
    s = (1 << 31) if z < 0 else 0
    q = abs(z)
    if q < B: return s | q
    h = q.bit_length()-1
    k = h-23
    m, r = divmod(q, 1 << k)
    if k and (r > 1 << (k-1) or (r == 1 << (k-1) and m & 1)): m += 1
    if m == 2*B: m >>= 1; h += 1
    E = h-22
    return s | (255 << 23) if E >= 255 else s | E << 23 | (m-B)

def proposed(u, v):
    eu, ev = exp(u), exp(v)
    if not (1 <= eu <= 254 and 1 <= ev <= 254 and (u ^ v) >> 31): return None
    if (u & 0x7fffffff) >= (v & 0x7fffffff): hi, lo = u, v
    else: hi, lo = v, u
    elo, d = exp(lo), exp(hi)-exp(lo)
    if d > 1: return None
    N = (mant(hi) << d)-mant(lo)
    assert 0 <= N < 1 << 25
    if N >= 1 << 24: return None
    if N == 0: return (0, {'N': 0, 'd': d, 'elo': elo, 'class': 'zero'})
    h = N.bit_length()-1
    s = hi & 0x80000000
    if h+elo >= 24:
        E = h+elo-23
        sig = N << (23-h)
        assert 1 <= E <= 253 and B <= sig < 2*B
        out = s | (E << 23) | (sig-B)
        cls = 'normal'
    else:
        frac = N << (elo-1)
        assert 1 <= elo <= 23 and 0 < frac < B
        out = s | frac
        cls = 'subnormal'
    return out, {'N': N, 'd': d, 'elo': elo, 'h': h, 'class': cls}

def worker():
    t = time.perf_counter()
    assert sha(BASE) == BASE_SHA
    checks, failures, cats = 0, [], defaultdict(int)
    trace = hashlib.sha256()
    def check(u, v):
        nonlocal checks
        checks += 1
        assert checks <= 165000 and time.perf_counter()-t < 4.5
        got = proposed(u,v)
        if got is None: cats['reject'] += 1; return
        out, info = got
        ref = reference(u,v)
        cats[info['class']] += 1
        cats['gap'+str(info['d'])] += 1
        cats['low_nonzero'] += 0 < info['N'] < B
        cats['h23'] += B <= info['N'] < 2*B
        if out != ref: failures.append([hex(u),hex(v),hex(out),hex(ref),info])
        trace.update(struct.pack('<IIII',u,v,out,ref))
    ns = sorted({0,1,2,3,B-1,B,B+1,2*B-1,2*B,2*B+1,3*B-2} |
                {2**k+j for k in range(1,24) for j in (-1,0,1)})
    for elo in range(1,255):
        for d in (0,1):
            if elo+d > 254: continue
            for N in ns:
                if d == 0:
                    if N >= B: continue
                    mh, ml = B+N, B
                else:
                    if not 1 <= N <= 3*B-2: continue
                    mh = max(B, (N+B+1)//2)
                    ml = 2*mh-N
                    assert B <= mh < 2*B and B <= ml < 2*B
                u, v = (elo+d)<<23 | (mh-B), 1<<31 | elo<<23 | (ml-B)
                for a,b in ((u,v),(v,u),(u^0x80000000,v^0x80000000),(v^0x80000000,u^0x80000000)):
                    check(a,b)
    rng = random.Random(202610251850)
    for _ in range(10000):
        elo=rng.randrange(1,255); d=rng.randrange(min(4,255-elo))
        u=(elo+d)<<23 | rng.getrandbits(23) | rng.getrandbits(1)<<31
        v=elo<<23 | rng.getrandbits(23) | rng.getrandbits(1)<<31
        check(u,v)
    rejects = [(0,0x80000000),(0x7f800000,0xff800000),(0x7fc00001,0x3f800000),
               (1,0x80800000),(0x3f800000,0x3f800000),(0x40000000,0xbf000000)]
    for u,v in rejects:
        assert proposed(u,v) is None
        check(u,v)
    witnesses=[]
    for name,u,v in [
        ('same_exp_wrong_sign_if_sort_exponent_only',0x3f800000,0xbfc00000),
        ('exact_zero_positive',0x4b800000,0xcb800000),
        ('negative_min_subnormal',0x80800001,0x00800000),
        ('largest_subnormal',0x00ffffff,0x80800000),
        ('minimum_normal_boundary',0x01000000,0x80800000),
        ('elo23_subnormal',0x0b800001,0x8b800000),
        ('d1_N_equals_2pow24_excluded',0x3fc00000,0xbf000000),
        ('d1_high_N_odd_needs_rounding',0x3fc00001,0xbf000001)]:
        got=proposed(u,v)
        witnesses.append({'name':name,'u':hex(u),'v':hex(v),'result':None if got is None else hex(got[0]),
                          'reference':hex(reference(u,v)),'domain':None if got is None else got[1]})
    model={'cases':checks,'counts':dict(cats),'failures':failures,'trace_sha256':trace.hexdigest(),
           'witnesses':witnesses,'state':'FINITE_INTEGER_MODEL_ONLY'}
    g=runpy.run_path(str(GEN)); coverage=[]; reads=0
    for run in RUNS:
        rr=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
        pp=next(rr.glob('download-*/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'))
        vp=pp.parent/'f01-r15-dev-packed-b2-1-verdict.json'; wp=pp.parent/'public-cell-work.json'
        ip=pp.parent/'inputs/f01-r15-dev-packed-b2-1/Kernel.lean'
        plan=json.loads(pp.read_bytes()); verdict=json.loads(vp.read_bytes());work=json.loads(wp.read_bytes())
        assert sha(ip)==BASE_SHA and verdict['passed'] and verdict['submission']=='f01-r15-dev-packed-b2-1'
        costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()}; total=sum(costs.values())
        groups=defaultdict(lambda:defaultdict(int)); case_rows=[]
        for c in plan['cases']:
            if not c['timed'] or c['kernel']!='add': continue
            group=':'.join(c['name'].split(':')[:2]); cnt=defaultdict(int); n=min(256,c['work'])
            for j in range(n):
                reads+=1; assert reads<=33000 and time.perf_counter()-t<4.5
                lo,hi=j*c['work']//n,(j+1)*c['work']//n
                i=lo+g['word'](c['seed'],j,63)%(hi-lo)
                u=g['element'](c,i,0,31); v=g['partner'](c,i,u); cnt['samples']+=1
                got=proposed(u,v)
                if got is not None:
                    out,info=got
                    assert out==reference(u,v)
                    cnt['eligible']+=1;cnt[info['class']]+=1;cnt['gap'+str(info['d'])]+=1
                    cnt['low_nonzero']+=0<info['N']<B;cnt['h23']+=B<=info['N']<2*B
                    cnt['eligible_requires_B2_general_decode']+=min(exp(u),exp(v))<24
                    if info['N']:
                        cnt['uint32_log2_source_iterations']+=info['h']
                        cnt['h_'+str(info['h'])]+=1
            for k,v in cnt.items():groups[group][k]+=v
            case_rows.append({'name':c['name'],'relation':c['relation'],'relParam':c['relParam'],**cnt})
        for k,v in groups.items():
            v['fraction']=v['eligible']/v['samples']
            v['B2_cell_share_whole']=costs[k]/total
            v['equal_pair_cost_proxy_whole']=v['fraction']*costs[k]/total
            v['mean_uint32_log2_iterations_nonzero']=v['uint32_log2_source_iterations']/(v['eligible']-v['zero']) if v['eligible']>v['zero'] else None
        coverage.append({'run':run,'plan_path':str(pp.relative_to(ROOT)),'plan_sha256':sha(pp),'verdict_sha256':sha(vp),
                         'work_sha256':sha(wp),'archived_input_sha256':sha(ip),'groups':dict(groups),'cases':case_rows,
                         'B2_ADD_share_whole':sum(v for k,v in costs.items() if k.startswith('add:'))/total,
                         'equal_pair_cost_proxy_whole':sum(v['equal_pair_cost_proxy_whole'] for v in groups.values())})
    print(json.dumps({'created_utc':datetime.now(timezone.utc).isoformat(),'model':model,'coverage':coverage,
        'coverage_pairs':reads,'elapsed_seconds':time.perf_counter()-t,'script_sha256':sha(Path(__file__)),
        'generator_sha256':sha(GEN),'baseline_sha256':sha(BASE),'external_timeout_seconds':5,'internal_seconds':4.5,
        'limits':'Exact integer model and named completed R15 source-model exposure only. Python generator is not independently checked against Lean. The equal-pair-cost proxy is NOT a strict upper bound, removable time, speedup, or measured eligible-subset cost. No future holdouts, no Lean/CI, no claim about SUM/BMM exposure.'},indent=2))
    return bool(failures)

if __name__=='__main__':
    if '--worker' in sys.argv: sys.exit(worker())
    t=time.perf_counter()
    p=subprocess.run([sys.executable,str(Path(__file__)),'--worker'],capture_output=True,text=True,timeout=5)
    (HERE/'check.stdout.json').write_text(p.stdout,encoding='utf-8')
    (HERE/'check.stderr.txt').write_text(p.stderr,encoding='utf-8')
    if p.returncode: raise RuntimeError(p.stderr or p.stdout)
    r=json.loads(p.stdout);r['controller_seconds']=time.perf_counter()-t;r['worker_exit_code']=p.returncode
    (HERE/'exposure.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'model_cases':r['model']['cases'],'counts':r['model']['counts'],'failures':r['model']['failures'],
      'coverage_pairs':r['coverage_pairs'],'seconds':r['controller_seconds'],'runs':[{'run':x['run'],
      'ADD_share':x['B2_ADD_share_whole'],'equal_pair_cost_proxy':x['equal_pair_cost_proxy_whole'],
      'groups':{k:{z:v.get(z,0) for z in ('samples','eligible','zero','subnormal','low_nonzero','h23','fraction')}
      for k,v in x['groups'].items()}} for x in r['coverage']]},indent=2))
