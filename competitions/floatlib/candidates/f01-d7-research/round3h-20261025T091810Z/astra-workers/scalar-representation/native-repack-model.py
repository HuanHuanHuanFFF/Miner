"""Finite R16 native product/repack check, externally enforced 5-second worker timeout.
No Lean, no compilation, no benchmark. Two independent rounding implementations:
source-derived exact integer nearest-even versus host C pack4 of exact binary64 products.
"""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, math, random, struct, subprocess, sys, time

HERE = Path(__file__).resolve().parent
LIMIT = 5
MAX_CASES = 18000
SEED = 202610250933

def ex(u): return (u >> 23) & 255
def mant(u): return (u & 0x7fffff) | 0x800000
def eligible(u, v): return 1 <= ex(u) <= 254 and 1 <= ex(v) <= 254 and 128 <= ex(u)+ex(v) <= 380
def f32(u): return struct.unpack('<f', struct.pack('<I', u))[0]
def bits(x):
    try: return struct.unpack('<I', struct.pack('<f', x))[0]
    except OverflowError: return (0x80000000 if x < 0 else 0) | 0x7f800000

def rse(n, shift):
    if shift <= 0: return n << -shift
    q, r = divmod(n, 1 << shift)
    half = 1 << (shift - 1)
    return q + (r > half or (r == half and (q & 1)))

def exact_mul(u, v):
    # Full finite words, including signed zero/subnormal; tests never supply nonfinite.
    sign = (u ^ v) & 0x80000000
    a = (u & 0x7fffff) | (0x800000 if ex(u) else 0)
    b = (v & 0x7fffff) | (0x800000 if ex(v) else 0)
    n = a*b
    if not n: return sign
    e = (ex(u)-150 if ex(u) else -149) + (ex(v)-150 if ex(v) else -149)
    h = n.bit_length()-1
    if h+e < -126:
        q = rse(n, -149-e)
        return sign | q
    q = rse(n,h-23)
    carry = q == (1<<24)
    if carry: q >>= 1
    E = h + e + carry + 127
    if E >= 255: return sign | 0x7f800000
    return sign | (E<<23) | (q & 0x7fffff)

def repack(u,v):
    # Integer mantissas convert exactly. Their 48-bit product is exact in binary64;
    # pack4 executes the independent host binary32 rounding.
    mid = bits(float(mant(u))*float(mant(v)))
    E = ex(mid)+ex(u)+ex(v)-300
    return ((u^v)&0x80000000) | ((E&255)<<23) | (mid&0x7fffff)

def work():
    start = time.perf_counter()
    pairs=[]
    ms=[0,1,2,3,0x3fffff,0x400000,0x7ffffe,0x7fffff]
    for s in (127,128,129,173,174,254,299,300,379,380,381):
        es={(max(1,s-254),s-max(1,s-254)),(s//2,s-s//2),(min(254,s-1),s-min(254,s-1))}
        for a,b in sorted(es):
            if not (1<=a<=254 and 1<=b<=254): continue
            for x in ms:
                for y in ms:
                    for sign in range(4): pairs.append(((a<<23)|x|((sign&1)<<31),(b<<23)|y|((sign>>1)<<31)))
    rng=random.Random(SEED)
    for _ in range(2048):
        a,b=rng.randrange(1,255),rng.randrange(1,255)
        pairs.append(((a<<23)|rng.getrandbits(23)|(rng.getrandbits(1)<<31),(b<<23)|rng.getrandbits(23)|(rng.getrandbits(1)<<31)))
    pairs.extend([(0x1f800000,0x20000000),(0x5f7fffff,0x5fffffff),(0x00000000,0x3f800000),
      (0x80000000,0x3f800000),(1,0x3f800000),(0x00800000,0x3f800000)])
    assert len(pairs)<=MAX_CASES
    failures=[]; excluded=[]; eligible_count=0; trace=hashlib.sha256()
    for u,v in pairs:
        assert time.perf_counter()-start < 4.5
        ref=exact_mul(u,v)
        host=bits(f32(u)*f32(v))
        if ref!=host: failures.append({'kind':'oracle_vs_host','u':hex(u),'v':hex(v),'ref':hex(ref),'host':hex(host)})
        if eligible(u,v):
            eligible_count+=1; got=repack(u,v)
            if got!=ref: failures.append({'kind':'repack','u':hex(u),'v':hex(v),'ref':hex(ref),'got':hex(got)})
            trace.update(struct.pack('<IIII',u,v,ref,got))
        elif (u,v) in [(0x1f800000,0x20000000),(0x5f7fffff,0x5fffffff)]:
            excluded.append({'u':hex(u),'v':hex(v),'sum':ex(u)+ex(v),'ref':hex(ref),'unguarded_repack':hex(repack(u,v))})
    report={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'FINITE_HOST_MODEL_ONLY',
      'cases':len(pairs),'eligible_cases':eligible_count,'max_cases':MAX_CASES,'seed':SEED,
      'external_worker_timeout_seconds':LIMIT,'internal_check_seconds':4.5,'elapsed_seconds':time.perf_counter()-start,
      'failures':failures,'excluded_domain_counterexamples':excluded,'trace_sha256':trace.hexdigest(),
      'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
      'limitations':'Not all 2^64 input pairs; no pinned Lean runtime execution, theorem checking, machine-code timing or final independent confirmation.'}
    print(json.dumps(report,indent=2))
    return 1 if failures else 0

if __name__=='__main__':
    if '--worker' in sys.argv: sys.exit(work())
    start=time.perf_counter()
    try:
        result=subprocess.run([sys.executable,str(Path(__file__)),'--worker'],capture_output=True,text=True,timeout=LIMIT)
        (HERE/'native-repack-model.stdout.txt').write_text(result.stdout,encoding='utf-8')
        (HERE/'native-repack-model.stderr.txt').write_text(result.stderr,encoding='utf-8')
        report=json.loads(result.stdout)
        report['controller_elapsed_seconds']=time.perf_counter()-start
        report['worker_exit_code']=result.returncode
        (HERE/'native-repack-model.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
        print(json.dumps({k:report[k] for k in ('state','cases','eligible_cases','failures','controller_elapsed_seconds','worker_exit_code')},indent=2))
        sys.exit(result.returncode)
    except subprocess.TimeoutExpired:
        (HERE/'native-repack-model.json').write_text(json.dumps({'state':'TIMEOUT','external_worker_timeout_seconds':LIMIT,'controller_elapsed_seconds':time.perf_counter()-start})+'\n',encoding='utf-8')
        raise
