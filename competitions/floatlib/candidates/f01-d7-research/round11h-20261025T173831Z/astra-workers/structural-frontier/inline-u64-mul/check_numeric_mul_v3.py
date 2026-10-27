"""Finite integer/host discriminator for the numeric UInt64 reverse cast. No benchmark."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json,random,runpy,struct,subprocess,sys,time
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
OLD=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/scalar-representation/native-repack-model.py'

def worker():
    start=time.perf_counter(); old=runpy.run_path(str(OLD))
    exact_mul,eligible,mant,ex=map(old.get,('exact_mul','eligible','mant','ex'))
    rng=random.Random(17261025)
    pairs=[]
    mm=[2**23,2**23+1,2**23+2,2**23+3,2**24-4,2**24-3,2**24-2,2**24-1,11863283,11863284]
    products={(a,b) for a in mm for b in mm}
    for a in mm+ [rng.randrange(2**23,2**24) for _ in range(100)]:
        for target in (2**47-2**22,2**47,2**47+2**23):
            for b in range(target//a-2,target//a+3):
                if 2**23<=b<2**24:products.add((a,b))
    for x in (1,3,5,7):
        for y in (1,3,5,7):
            products.add((2**23+x*2**11,2**23+y*2**11))
            products.add((3*2**22+x*2**11,3*2**22+y*2**12))
    for a,b in sorted(products):
        for s in (128,129,253,254,379,380):
            eu=max(1,s-254);ev=s-eu
            for signs in range(4):
                pairs.append(((eu<<23)|(a-2**23)|((signs&1)<<31),
                              (ev<<23)|(b-2**23)|((signs>>1)<<31)))
    for _ in range(5000):
        a,b=rng.randrange(1,255),rng.randrange(1,255)
        pairs.append((a<<23|rng.getrandbits(23)|rng.getrandbits(1)<<31,
                      b<<23|rng.getrandbits(23)|rng.getrandbits(1)<<31))
    assert len(pairs)<50000
    guard_checked=0
    for eu in range(256):
        for ev in range(256):
            actual=((eu-1)&0xffffffff)<=253 and ((ev-1)&0xffffffff)<=253 and ((eu+ev-128)&0xffffffff)<=252
            expected=1<=eu<=254 and 1<=ev<=254 and 128<=eu+ev<=380
            assert actual==expected
            guard_checked+=1
    failures=[];stats={'eligible':0,'rounding_carry_46_to_47':0,'tie_even':0,'tie_odd':0}
    extremes={'R_min':2**64,'R_max':0,'E_min':256,'E_max':0};trace=hashlib.sha256()
    for u,v in pairs:
        assert time.perf_counter()-start<4.5
        if not eligible(u,v):continue
        stats['eligible']+=1
        a,b=mant(u),mant(v);N=a*b;h=N.bit_length()-1;sh=h-23
        q,r=divmod(N,1<<sh);half=1<<(sh-1)
        if r==half:stats['tie_odd' if q&1 else 'tie_even']+=1
        Rint=(q+(r>half or r==half and q&1))<<sh
        # Inputs and the 48-bit product are exact binary64 integers; pack4 independently rounds.
        F=struct.unpack('<f',struct.pack('<f',float(a)*float(b)))[0]
        word_product=(a*b)&0xffffffffffffffff
        F_integer=struct.unpack('<f',struct.pack('<f',float(word_product)))[0]
        assert word_product==N and F_integer==F
        cast=int(F)
        high=int(cast>=2**47);Q=cast>>(23+high);E=ex(u)+ex(v)-127+high
        got=((u^v)&0x80000000)|(E<<23)|(Q-2**23)
        want=exact_mul(u,v)
        good=(cast==Rint and 2**46<=cast<2**48 and cast<2**64
              and 2**23<=Q<2**24 and 1<=E<=254 and got==want
              and cast==Q*(1<<(23+high)))
        if not good:failures.append(dict(u=hex(u),v=hex(v),N=N,R=cast,RNE=Rint,Q=Q,E=E,got=hex(got),want=hex(want)))
        stats['rounding_carry_46_to_47']+=int(N<2**47<=cast)
        for key,val in [('R',cast),('E',E)]:
            extremes[key+'_min']=min(extremes[key+'_min'],val);extremes[key+'_max']=max(extremes[key+'_max'],val)
        trace.update(struct.pack('<IIQII',u,v,cast,got,want))
    # Explicit negative control: using the unrounded product's leading bit misses a carry.
    a,b=2**23+1,2**24-2;N=a*b;F=struct.unpack('<f',struct.pack('<f',float(N)))[0];V=int(F)
    assert N<2**47 and V==2**47
    rightE=128-127+int(V>=2**47);wrongE=128-127+int(N>=2**47)
    u=64<<23|(a-2**23);v=64<<23|(b-2**23)
    right=(rightE<<23)|((V>>24)-2**23)
    wrong=(wrongE<<23)|((V>>23)-2**23)
    assert right==exact_mul(u,v) and right!=wrong
    report=dict(updated_utc=datetime.now(timezone.utc).isoformat(),state='FINITE_NUMERIC_U64_MODEL_PASS' if not failures else 'FAIL',
        pairs=len(pairs),guard_exponent_pairs=guard_checked,integer_and_FP_product_paths_equal=True,stats=stats,extremes=extremes,failures=failures,
        carry_negative_control=dict(u=hex(u),v=hex(v),N=N,R=V,right=hex(right),wrong_using_N=hex(wrong)),
        smallest_R=2**46,largest_R_from_endpoint=int(struct.unpack('<f',struct.pack('<f',float((2**24-1)**2)))[0]),
        trace_sha256=trace.hexdigest(),reference_path=str(OLD.relative_to(R)),
        reference_sha256=hashlib.sha256(OLD.read_bytes()).hexdigest(),
        script_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        elapsed_seconds=time.perf_counter()-start,external_timeout_seconds=5,
        scope='Constructed finite sample; Python host pack4 plus exact integer reference. No pinned Lean execution, C/ASM or performance; no official holdout used.')
    print(json.dumps(report,indent=2));return bool(failures)

if __name__=='__main__':
    if '--worker' in sys.argv:sys.exit(worker())
    start=time.perf_counter();r=subprocess.run([sys.executable,str(Path(__file__)),'--worker'],capture_output=True,text=True,timeout=5)
    (H/'numeric-model-v3.stdout.json').write_text(r.stdout)
    (H/'numeric-model-v3.stderr.txt').write_text(r.stderr)
    if r.returncode:print(r.stdout);print(r.stderr);sys.exit(r.returncode)
    j=json.loads(r.stdout);j['worker_exit_code']=r.returncode;j['controller_seconds']=time.perf_counter()-start
    (H/'numeric-model-v3.json').write_text(json.dumps(j,indent=2)+'\n')
    print(json.dumps({k:j[k] for k in ('state','pairs','stats','extremes','carry_negative_control','controller_seconds')}))
