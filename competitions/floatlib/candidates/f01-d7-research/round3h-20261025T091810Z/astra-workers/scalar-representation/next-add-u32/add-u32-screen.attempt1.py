"""Independent ADD one-native-UInt32-cast feasibility. Local finite source-model only.
Reads only named completed R15 runs; never current R16 validation data.
Worker has subprocess timeout=5 seconds and finite count bounds.
"""
from pathlib import Path
from datetime import datetime,timezone
from collections import defaultdict
import hashlib,json,random,runpy,struct,subprocess,sys,time

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
GEN=ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-public-input-domain.py'
RUNS=(40168687803,40169957447,40171180249)
U32=(1<<32)-1
def exp(u): return (u>>23)&255
def mant(u): return (u&0x7fffff)|0x800000
def sign(u): return bool(u>>31)
def f32(u): return struct.unpack('<f',struct.pack('<I',u))[0]
def bits(x):
    try: return struct.unpack('<I',struct.pack('<f',x))[0]
    except OverflowError: return (0x80000000 if x<0 else 0)|0x7f800000
def rse(n,k):
    if k<=0:return n<<-k
    q,r=divmod(n,1<<k); h=1<<(k-1)
    return q+(r>h or (r==h and q&1))
def round_exact(s,n,e):
    if not n:return 0
    signbit=0x80000000 if s else 0
    h=n.bit_length()-1
    if h+e < -126:return signbit|rse(n,-149-e)
    q=rse(n,h-23); c=q==(1<<24)
    if c:q>>=1
    E=h+e+c+127
    return signbit|0x7f800000 if E>=255 else signbit|(E<<23)|(q&0x7fffff)
def raw_alignment(u,v,wrap=False):
    a=min(exp(u),exp(v)); du,dv=exp(u)-a,exp(v)-a
    L,R=mant(u)<<du,mant(v)<<dv
    if wrap:L&=U32;R&=U32
    if sign(u)==sign(v):return a,(L+R)&U32 if wrap else L+R,sign(u)
    return (a,L-R,sign(u)) if L>=R else (a,R-L,sign(v))
def initial_guard(u,v):return 1<=exp(u)<=254 and 1<=exp(v)<=254 and abs(exp(u)-exp(v))<=7
def proposed(u,v,force=False,skip_zero=False):
    if not force and not initial_guard(u,v):return None
    a,n,s=raw_alignment(u,v,wrap=True)
    if n==0 and not skip_zero:return 0
    mid=bits(float(n)); E=(exp(mid)+a-150)&U32
    if not force and ((E-1)&U32)>253:return None
    return (0x80000000 if s else 0)|((E&255)<<23)|(mid&0x7fffff)

def worker():
    t=time.perf_counter(); rng=random.Random(202610251020); pairs=[]
    ms=(0,1,2,0x3fffff,0x400000,0x7ffffe,0x7fffff)
    for a in (1,2,22,23,24,126,127,150,151,247,252,253,254):
        for d in (0,1,2,7,8):
            if a+d>254:continue
            for x in ms:
                for y in ms:
                    for s in range(4):pairs.append((((a+d)<<23)|x|((s&1)<<31),(a<<23)|y|((s>>1)<<31)))
    for _ in range(2048):
        a=rng.randrange(1,255);d=rng.randrange(min(8,255-a));b=a+d
        pairs.append((a<<23|rng.getrandbits(23)|rng.getrandbits(1)<<31,b<<23|rng.getrandbits(23)|rng.getrandbits(1)<<31))
    assert len(pairs)<=15000
    counts=defaultdict(int); failures=[];trace=hashlib.sha256()
    for u,v in pairs:
        assert time.perf_counter()-t<4.5
        a,n,s=raw_alignment(u,v)
        ref=round_exact(s,n,a-150); host=bits(f32(u)+f32(v))
        if ref!=host:failures.append(['oracle-host',hex(u),hex(v),hex(ref),hex(host)])
        if initial_guard(u,v):
            aw,nw,sw=raw_alignment(u,v,True)
            if (aw,nw,sw)!=(a,n,s):failures.append(['word-alignment',hex(u),hex(v)])
            counts['initial_guard']+=1
            counts['zero']+=n==0;counts['small_cancellation']+=0<n<(1<<23)
            if n:
                h=n.bit_length()-1;mid=bits(float(n));c=exp(mid)-127-h
                counts['carry']+=c==1
                E=exp(mid)+a-150
                if 1<=E<=254:
                    assert h+a>=24 # Carries from integer conversion cannot violate original normal lower bound.
            got=proposed(u,v)
            if got is None:counts['normal_postguard_reject']+=1
            else:
                counts['accepted']+=1
                if got!=ref:failures.append(['candidate',hex(u),hex(v),hex(ref),hex(got)])
                trace.update(struct.pack('<IIII',u,v,ref,got))
    witnesses=[]
    for label,u,v,skip in [
      ('zero must precede exponent postguard',0x4b800000,0xcb800000,True),
      ('a23 tiny cancellation becomes subnormal',0x0b800001,0x8b800000,False),
      ('d8 UInt32 overflow can still pass exponent guard',(135<<23)|0x7fffff,(127<<23)|0x7fffff,False),
      ('overflow exponent cannot retain fraction',0x7f7fffff,0x7f7fffff,False),
      ('same exponent magnitude determines result sign',0x3f800000,0xbfc00000,False)]:
        a,n,s=raw_alignment(u,v);ref=round_exact(s,n,a-150)
        witnesses.append({'label':label,'u':hex(u),'v':hex(v),'a':a,'d':abs(exp(u)-exp(v)),
          'N_exact':n,'reference':hex(ref),'forced_wrong_or_diagnostic':hex(proposed(u,v,True,skip)),
          'actual_guarded_result':None if proposed(u,v) is None else hex(proposed(u,v))})
    g=runpy.run_path(str(GEN)); coverage=[];reads=0
    for run in RUNS:
        rr=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
        planpath=next(rr.glob('download-*/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'))
        vp=planpath.parent/'f01-r15-dev-packed-b2-1-verdict.json';wp=planpath.parent/'public-cell-work.json'
        plan=json.loads(planpath.read_bytes()); verdict=json.loads(vp.read_bytes());work=json.loads(wp.read_bytes())
        assert verdict['incumbent_sha256']=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
        costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()};total=sum(costs.values())
        groups=defaultdict(lambda:defaultdict(int))
        for c in plan['cases']:
            if not c['timed'] or c['kernel']!='add':continue
            k=':'.join(c['name'].split(':')[:2]);ns=min(256,c['work'])
            for j in range(ns):
                reads+=1;assert reads<=33000 and time.perf_counter()-t<4.5
                lo,hi=j*c['work']//ns,(j+1)*c['work']//ns
                i=lo+g['word'](c['seed'],j,63)%(hi-lo)
                u=g['element'](c,i,0,31);v=g['partner'](c,i,u);groups[k]['samples']+=1
                if initial_guard(u,v):
                    groups[k]['initial_guard']+=1
                    a,n,s=raw_alignment(u,v,True);got=proposed(u,v)
                    if got is not None:
                        groups[k]['accepted']+=1;groups[k]['zero']+=n==0
                        groups[k]['small_cancellation']+=0<n<(1<<23)
                        groups[k]['old_software_domain']+=int(n>0 and (sign(u)==sign(v) or abs(exp(u)-exp(v))>=2))
                    else:groups[k]['normal_postguard_reject']+=1
        for k,x in groups.items():
            x['accepted_fraction']=x['accepted']/x['samples']
            x['zero_fraction']=x['zero']/x['samples']
            x['small_cancellation_fraction']=x['small_cancellation']/x['samples']
            x['B2_cell_share_whole']=costs[k]/total
        coverage.append({'run':run,'groups':dict(groups),'B2_ADD_share_whole':sum(v for k,v in costs.items() if k.startswith('add:'))/total,
          'plan_sha256':hashlib.sha256(planpath.read_bytes()).hexdigest(),'verdict_sha256':hashlib.sha256(vp.read_bytes()).hexdigest(),
          'work_sha256':hashlib.sha256(wp.read_bytes()).hexdigest()})
    report={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'FINITE_MODEL_AND_COMPLETED_B2_SOURCE_COVERAGE_ONLY',
      'model_cases':len(pairs),'model_counts':dict(counts),'model_failures':failures,'model_trace_sha256':trace.hexdigest(),
      'witnesses':witnesses,'coverage_pairs':reads,'coverage':coverage,'elapsed_seconds':time.perf_counter()-t,
      'limits':{'model_pairs':15000,'coverage_pairs':33000,'external_worker_timeout':5,'internal_seconds':4.5},
      'generator_sha256':hashlib.sha256(GEN.read_bytes()).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
      'limitations':'Search-stage host pack4/exact integer model only. No Lean proof/runtime or performance for ADD. Coverage uses an unverified Python transcription of official fixed generator on named COMPLETED R15 draws. B2 measured class costs are kept separate; no time is assigned to eligible subsets. No40183711165 input/result was read.'}
    print(json.dumps(report,indent=2));return bool(failures)

if __name__=='__main__':
    if '--worker' in sys.argv:sys.exit(worker())
    t=time.perf_counter();p=subprocess.run([sys.executable,str(Path(__file__)),'--worker'],capture_output=True,text=True,timeout=5)
    (HERE/'screen.stdout.txt').write_text(p.stdout,encoding='utf-8');(HERE/'screen.stderr.txt').write_text(p.stderr,encoding='utf-8')
    if p.returncode:raise RuntimeError(p.stderr or p.stdout)
    r=json.loads(p.stdout);r['controller_seconds']=time.perf_counter()-t;r['worker_exit_code']=p.returncode
    (HERE/'screen.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'model_cases':r['model_cases'],'model_counts':r['model_counts'],'model_failures':r['model_failures'],
      'coverage_pairs':r['coverage_pairs'],'coverage':[{'run':x['run'],'ADD_share':x['B2_ADD_share_whole'],'fractions':{k:v['accepted_fraction'] for k,v in x['groups'].items()}} for x in r['coverage']],
      'seconds':r['controller_seconds']},indent=2))
