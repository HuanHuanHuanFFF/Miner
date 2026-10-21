"""Exact finite binary32 model, generator replay and path frequencies; not Lean validation."""
from pathlib import Path
import collections, datetime, hashlib, json, platform, random, struct, time

HERE = Path(__file__).resolve().parent
MASK = (1 << 32) - 1
MAG = 0x7fffffff

def unpack(w):
    e = (w >> 23) & 255
    assert e != 255, hex(w)
    m = (w & 0x7fffff) | (0x800000 if e else 0)
    return (-m if w >> 31 else m), (e - 150 if e else -149)

def shift_round(v, k):
    if k <= 0:
        return v << -k
    q, r = divmod(v, 1 << k)
    half = 1 << (k - 1)
    return q + int(r > half or (r == half and q & 1))

def round_finite(v, e, zero_sign=0):
    if v == 0:
        return zero_sign
    sign = int(v < 0) << 31
    v = abs(v)
    leading = v.bit_length() - 1
    out_e = leading + e
    if out_e < -126:
        return sign | shift_round(v, -149 - e)
    m = shift_round(v, leading - 23)
    if m == 1 << 24:
        m >>= 1
        out_e += 1
    if out_e > 127:
        return sign | 0x7f800000
    return sign | ((out_e + 127) << 23) | (m & 0x7fffff)

def add(a, b):
    x, ex = unpack(a)
    y, ey = unpack(b)
    e = min(ex, ey)
    v = (x << (ex - e)) + (y << (ey - e))
    return round_finite(v, e, (a & b) & 0x80000000)

def mul(a, b):
    x, ex = unpack(a)
    y, ey = unpack(b)
    return round_finite(x * y, ex + ey, (a ^ b) & 0x80000000)

def lcg(n, seed):
    for _ in range(n):
        seed = (seed * 1664525 + 1013904223) & MASK
        yield seed

def gen(kind, w):
    if kind == 'relu':
        return 0 if w & 1 == 0 else (w & 0x7fffff) | ((124 + (w >> 23) % 7) << 23)
    return (w & 0x807fffff) | (((124 + (w >> 23) % 7) if kind == 'dense' else (102 + (w >> 23) % 50)) << 23)

def values(kind, salt, seed, count):
    return [gen(kind, w) for w in lcg(count, seed ^ ((salt * 0x9e3779b9) & MASK))]

def checked_add(a, b, stats):
    za, zb = (a & MAG) == 0, (b & MAG) == 0
    stats['add_steps'] += 1
    stats['zero_fallback'] += int(za or zb)
    stats['accumulator_zero'] += int(za)
    stats['rhs_zero'] += int(zb)
    stats['both_zero'] += int(za and zb)
    ea, eb = max((a >> 23) & 255, 1), max((b >> 23) & 255, 1)
    stats['nonzero_scale_gap_gt39'] += int(not za and not zb and abs(ea - eb) > 39)
    c = add(a, b)
    stats['nonzero_cancellation_to_zero'] += int(not za and not zb and c & MAG == 0)
    return c

def checksum(ws):
    s = 0
    for w in ws:
        s = ((s ^ w) * 16777619) & MASK
    return s

def sum_case(kind, salt, seed, pairs):
    ws = values(kind, salt, seed, pairs // 1000 * 1000)
    stats = collections.Counter()
    out = []
    for start in range(0, len(ws), 1000):
        acc = 0
        for w in ws[start:start+1000]:
            acc = checked_add(acc, w, stats)
        out.append(acc)
    return dict(stats, checksum=checksum(out), outputs=len(out), input_sha256=hashlib.sha256(b''.join(struct.pack('<I', x) for x in ws)).hexdigest())

def bmm_case(kind, salt, seed, pairs):
    m, n, p = 50, 100, 50
    batch = pairs // (m*n*p)
    aa = values(kind, salt, seed, batch*m*n)
    bb = values('dense' if kind == 'relu' else kind, salt+0x80, seed, batch*n*p)
    stats = collections.Counter()
    out = []
    for b in range(batch):
        for i in range(m):
            for j in range(p):
                acc = 0
                for k in range(n):
                    a, c = aa[(b*m+i)*n+k], bb[(b*n+k)*p+j]
                    product = mul(a, c)
                    stats['mul_steps'] += 1
                    stats['zero_product'] += int(product & MAG == 0)
                    acc = checked_add(acc, product, stats)
                out.append(acc)
    return dict(stats, checksum=checksum(out), outputs=len(out), input_sha256=hashlib.sha256(b''.join(struct.pack('<I', x) for x in aa+bb)).hexdigest())

def host_bits(v):
    try:
        return struct.unpack('<I', struct.pack('<f', v))[0]
    except OverflowError:
        return 0x7f800000 if v > 0 else 0xff800000

def selfcheck():
    rng = random.Random(20261021)
    total = 0
    for _ in range(30000):
        # Modest finite exponents keep the binary64 host oracle exact enough for both operations.
        a = rng.getrandbits(32) & 0x807fffff | (rng.randrange(95,160) << 23)
        b = rng.getrandbits(32) & 0x807fffff | (rng.randrange(95,160) << 23)
        x, y = (struct.unpack('<f', struct.pack('<I', w))[0] for w in (a,b))
        assert add(a,b) == host_bits(x+y), ('add',hex(a),hex(b))
        assert mul(a,b) == host_bits(x*y), ('mul',hex(a),hex(b))
        total += 2
    for a,b,want in [(0,0x80000000,0),(0x80000000,0,0),(0x80000000,0x80000000,0x80000000),(1,0x80000001,0),(0,1,1),(0x80000000,0x80000001,0x80000001)]:
        assert add(a,b) == want
        total += 1
    return total

def main():
    started = datetime.datetime.now(datetime.timezone.utc).isoformat()
    t0 = time.monotonic()
    checks = selfcheck()
    seeds = [211, 0x9e3779b9]
    pairs = 500000
    rows = []
    for seed in seeds:
        for k,kind in enumerate(['dense','relu','wide']):
            for op,fn,salt in [('sum',sum_case,0x51+k),('bmm',bmm_case,0x61+k)]:
                r = dict(op=op, kind=kind, seed=seed, pairs=pairs, **fn(kind,salt,seed,pairs))
                r['zero_fallback_fraction'] = r['zero_fallback']/r['add_steps']
                rows.append(r)
                print(json.dumps(r), flush=True)
    result = {
        'started_at_utc': started, 'finished_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'wall_seconds': time.monotonic()-t0, 'platform': platform.platform(), 'python': platform.python_version(),
        'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(), 'selfcheck_cases':checks,
        'source': 'Pinned Bench/BenchTensor/BenchBmm generators; finite exact-dyadic integer model',
        'scope': 'Finite path-frequency evidence only. No Lean equivalence, target timing or official checksum validation claimed. Frequencies are not time shares.',
        'rows': rows,
        'counterexamples': [
            {'claim':'Return rhs whenever lhs is zero', 'a':'0x00000000','b':'0x80000000','correct_add':'0x00000000','wrong':'0x80000000'},
            {'claim':'Skip a zero rhs unconditionally', 'a':'0x80000000','b':'0x00000000','correct_add':'0x00000000','wrong':'0x80000000'},
            {'claim':'Any zero factor implies zero product','a':'0x00000000','b':'0x7f800000','correct_category':'NaN','model_status':'Not executed by finite model; IEEE special case, must retain fallback'}
        ]}
    (HERE/'fallback-probe-result.json').write_text(json.dumps(result, indent=2)+'\n',encoding='utf8')
    print(json.dumps({'wall_seconds':result['wall_seconds'],'rows':len(rows),'selfcheck_cases':checks}))

if __name__ == '__main__':
    main()
