"""Integer-only replay of the actual R26 FP certificate on old seen cohorts.
No Lean/native build or benchmark; output hashes are checked against old native evidence.
"""
from pathlib import Path
import argparse,collections,hashlib,importlib.util,json,math,platform,struct,sys,time
from datetime import datetime,timezone
sys.dont_write_bytecode=True
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
H=Path(__file__).resolve().parent
UTIL=H/'formula_snapshot.py'
spec=importlib.util.spec_from_file_location('r27_finite_formula',UTIL);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
E=ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/evidence/40852769757/download-988ea0459868494bb525e3d8f8795129'
SUITE=ROOT/'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/development-broad/torchlean-source/lean/bench/ExactSuite.lean'
MASK64=(1<<64)-1;SIGN64=1<<63;EMASK64=0x7ff0000000000000
HOSTCHECK_LIMIT=32

def rnd53(n):
    if n==0:return 0
    s=-1 if n<0 else 1;a=abs(n);shift=a.bit_length()-53
    if shift<=0:return n
    q,r=divmod(a,1<<shift);half=1<<(shift-1)
    return s*((q+(r>half or (r==half and q&1)))<<shift)

def bits64(n):
    if n==0:return 0
    sign=SIGN64 if n<0 else 0;a=abs(n);b=a.bit_length();e=b+719
    assert 0<e<2047
    sig=(a>>(b-53)) if b>=53 else (a<<(53-b))
    assert b<=53 or (a&((1<<(b-53))-1))==0
    assert 1<<52<=sig<1<<53
    return sign|(e<<52)|(sig-(1<<52))

def okey(w):return w^MASK64 if w&SIGN64 else w^SIGN64

def proposal(w):
    mag=((((((w&0x7fffffffffffffff)+0x10000000)&MASK64)>>29)&0xffffffff)-0xc0000000)&0x7fffffff
    return ((w>>32)&0x80000000)|mag

def classify(w):
    e=(w>>23)&255;f=w&0x7fffff
    return 'nan' if e==255 and f else 'infinity' if e==255 else 'zero' if not(e or f) else 'subnormal' if not e else 'normal'

def finite(w):return (w&EMASK64)!=EMASK64

def certify(sw,lo,hi,q):
    mag=q&0x7fffffff;e=(mag>>23)&255
    if e in (0,255):return False,'guess_e0' if e==0 else 'guess_e255'
    if not(finite(sw) and finite(lo) and finite(hi)):return False,'nonfinite_guard'
    base=((e+896)<<52)|((mag&0x7fffff)<<29)
    below=base-(0x20000000 if mag==0x00800000 else 0x10000000);above=base+0x10000000
    lower=(above|SIGN64) if q>>31 else below
    upper=(below|SIGN64) if q>>31 else above
    hl=okey(lower)<okey(lo);hu=okey(hi)<okey(upper)
    return hl and hu,('accept' if hl and hu else 'both_bounds' if not hl and not hu else 'lower_bound' if not hl else 'upper_bound')

class Census:
    def __init__(self):
        self.macs=0;self.host_checks=0;self.rows=[];self.counter=collections.Counter();self.examples=[];self.max_error_ratio=(0,1)
    def dot(self,a,b,ka,kb,H):
        n=len(a);assert n==len(b) and n>0 and n<=1<<30
        acc=0;exact=0
        for x,y in zip(ka,kb):
            prod=x*y;exact+=prod;acc=rnd53(acc+(prod<<5))
        self.macs+=n
        L=(n-1).bit_length();R=1<<(H+2*L)
        sw=bits64(acc);lo=bits64(rnd53(acc-R));hi=bits64(rnd53(acc+R));q=proposal(sw)
        accepted,reason=certify(sw,lo,hi,q)
        expected=m.round_ratio(exact,1,-298)
        if exact==0 and all((x==0 or y==0) and bool((u^v)>>31) for x,y,u,v in zip(ka,kb,a,b)):expected=0x80000000
        err=abs(acc-(exact<<5));assert err<=R,(err,R)
        if err*self.max_error_ratio[1]>self.max_error_ratio[0]*R:self.max_error_ratio=(err,R)
        if accepted:assert q==expected,(q,expected)
        old_accepted=accepted
        operand_ok=self.input_domain_by_id[id(a)] and self.input_domain_by_id[id(b)]
        proposal_ok=2<=((q>>23)&255)<=253 and (q&0x7fffff)!=0
        self.counter['old_checker_accept']+=old_accepted
        if old_accepted and not operand_ok:
            accepted=False;reason='narrow_operand_domain';self.counter['additional_reject']+=1
        elif old_accepted and not proposal_ok:
            accepted=False;reason='narrow_proposal_domain';self.counter['additional_reject']+=1
        self.counter['proposal_outside_interior_nonpower']+=not proposal_ok
        self.counter[reason]+=1;self.counter['exact_'+classify(expected)]+=1
        self.counter['proposal_exact']+=q==expected;self.counter['sum_exact']+=err==0
        if not accepted:self.counter['reject_exact_'+classify(expected)]+=1
        if self.host_checks<HOSTCHECK_LIMIT:
            fs=0.0
            for u,v in zip(a,b):
                x=struct.unpack('<f',struct.pack('<I',u))[0];y=struct.unpack('<f',struct.pack('<I',v))[0]
                fs=fs+x*y
            assert struct.unpack('<Q',struct.pack('<d',fs))[0]==sw
            rr=math.ldexp(1.0,H+2*L-303)
            assert struct.unpack('<Q',struct.pack('<d',fs-rr))[0]==lo
            assert struct.unpack('<Q',struct.pack('<d',fs+rr))[0]==hi
            self.host_checks+=1
        if not accepted and len(self.examples)<24:self.examples.append(dict(reason=reason,n=n,H=H,L=L,guess=hex(q),expected=hex(expected),sum_word=hex(sw),error_over_radius=[err,R]))
        return expected,accepted,reason
    def linear(self,x,rows,k,out,w,b,relu,stage):
        left=[x[r*k:(r+1)*k]+[0x3f800000] for r in range(rows)]
        right=[w[j*k:(j+1)*k]+[b[j]] for j in range(out)]
        return self.matrix(left,right,relu,stage)
    def matrix(self,left,right,relu,stage):
        def domain(v):
            return all((1<=((w>>23)&255)<=254) or (w&0x7fffffff)==0 for w in v)
        self.input_domain_by_id={id(v):domain(v)for v in left+right}
        self.counter['outside_operand_vectors']+=sum(not self.input_domain_by_id[id(v)] for v in left+right)
        self.counter['prepared_operand_vectors']+=len(left)+len(right)
        ka=[list(map(m.key,a))for a in left];kb=[list(map(m.key,b))for b in right]
        ha=[max((m.fields(w)[2] for w in a),default=0)for a in left];hb=[max((m.fields(w)[2]for w in b),default=0)for b in right]
        failrows=set();failcols=set();count=collections.Counter();result=[]
        for i,a in enumerate(left):
            for j,b in enumerate(right):
                word,ok,reason=self.dot(a,b,ka[i],kb[j],ha[i]+hb[j]);count[reason]+=1
                if not ok:failrows.add(i);failcols.add(j)
                result.append(0 if relu and word>>31 else word)
        n=len(left[0]);eager=(len(left)+len(right))*n;lazy=(len(failrows)+len(failcols))*n
        self.rows.append(dict(stage=stage,shape=[len(left),n,len(right)],counts=count,eager_word_prepare_terms=eager,word_prepare_terms_if_lazy_cached=lazy,failed_left_caches=len(failrows),failed_right_caches=len(failcols)))
        return result

def dimensions(seed,profile):
    r=m.lcg(8,seed^0x5bd1e995);draw=lambda i,n:r[i]%n;edge=lambda b,i:b-1 if not(r[i]&0x1000) else b+1
    n=(edge((32+draw(0,67))*8,2) if profile=='boundary' else (8+draw(0,57))*16 if profile=='scale' else (32+draw(0,67))*8)
    ni,h,h2=m.dimensions(seed,profile)
    t=9+2*draw(6,5) if profile=='boundary' else 20+2*draw(6,7) if profile=='scale' else 8+draw(6,9)
    c=15+2*draw(7,10) if profile=='boundary' else 12+draw(7,9) if profile=='scale' else 16+4*draw(7,9)
    return n,ni,h,h2,t,c

def fnv(words):
    z=2166136261
    for w in words:z=((z^w)*16777619)&0xffffffff
    return z

def run_cell(model,seed,profile,kind,c):
    i,ni,h,h2,T,C=dimensions(seed,profile)
    if model=='mlp':
        x=m.gen(kind,i,seed+999);widths=[i,h,h2,10]
        for j,(a,b)in enumerate(zip(widths,widths[1:])):x=c.linear(x,1,a,b,m.weights(kind,seed,2*j,a,a*b),m.bias(seed,2*j+1,b),j<2,f'linear{j}')
    elif model=='normalized_mlp':
        x=m.gen(kind,ni,seed+999)
        x=c.linear(x,1,ni,h,m.weights(kind,seed,1,ni,h*ni),m.bias(seed,2,h),True,'linear0')
        x=m.norm(x,1,h,m.scale(seed+3,h))
        x=c.linear(x,1,h,h2,m.weights(kind,seed,4,h,h2*h),m.bias(seed,5,h2),True,'linear1')
        x=m.norm(x,1,h2,m.scale(seed+6,h2),m.bias(seed,7,h2))
        x=c.linear(x,1,h2,10,m.weights(kind,seed,8,h2,10*h2),m.bias(seed,9,10),False,'linear2')
    else:
        x=m.gen(kind,T*C,seed+999);saved=x
        x=m.norm(x,T,C,m.scale(seed+1,C),m.bias(seed,2,C))
        a=m.weights(kind,seed,3,T,T*T)
        x=c.matrix([a[i*T:(i+1)*T]for i in range(T)],[[x[i*C+j]for i in range(T)]for j in range(C)],False,'gemm')
        x=[m.round_ratio(m.key(a)+m.key(b),1,-149)for a,b in zip(x,saved)];saved=x
        x=m.norm(x,T,C,m.scale(seed+4,C),m.bias(seed,5,C))
        x=c.linear(x,T,C,2*C,m.weights(kind,seed,6,C,2*C*C),m.bias(seed,7,2*C),True,'linear0')
        x=c.linear(x,T,2*C,C,m.weights(kind,seed,8,2*C,2*C*C),m.bias(seed,9,C),False,'linear1')
        x=[m.round_ratio(m.key(a)+m.key(b),1,-149)for a,b in zip(x,saved)]
        x=c.linear(x,1,T*C,10,m.weights(kind,seed,10,T*C,10*T*C),m.bias(seed,11,10),False,'classifier')
    return x

def main():
    p=argparse.ArgumentParser();p.add_argument('--root',type=int,default=26102901);p.add_argument('--max-seconds',type=float,default=60);a=p.parse_args()
    expected=json.loads((E/'summary.json').read_bytes())['protected_before']['lean/bench/ExactSuite.lean'];assert hashlib.sha256(SUITE.read_bytes()).hexdigest()==expected
    req=json.loads((E/f'fp-word-conv6-{a.root}-request.json').read_bytes());old=json.loads((E/f'fp-word-conv6-{a.root}-measurement.json').read_bytes())['result']
    began=datetime.now(timezone.utc).isoformat();t=time.monotonic();rows=[];allc=Census();complete=True
    for w in req['workloads']:
        for model in ['mlp','normalized_mlp','mixer']:
            for kind in ['normal','wide','sparse']:
                if time.monotonic()-t>a.max_seconds:complete=False;break
                c=Census();out=run_cell(model,w['seed'],w['profile'],kind,c);cell=f"{w['id']}|{model}:b1:{kind}";observed=old['rounds'][0]['cells'][cell]['candidate_checksum'];actual=fnv(out)
                assert actual==observed,(cell,actual,observed)
                rows.append(dict(cell=cell,seed=w['seed'],profile=w['profile'],checksum=actual,old_native_checksum=observed,checksum_match=True,counts=c.counter,stages=c.rows,macs=c.macs,host_crosschecks=c.host_checks,max_error_over_radius=c.max_error_ratio,rejections=c.examples))
                allc.counter.update(c.counter);allc.macs+=c.macs
            if not complete:break
        if not complete:break
    result=dict(status='CONDITIONAL_NARROW_GUARD_COVERAGE_OLD_SEEN_COHORT',start_utc=began,end_utc=datetime.now(timezone.utc).isoformat(),elapsed_seconds=time.monotonic()-t,complete=complete,root_seed=a.root,cells=rows,total_counts=allc.counter,total_macs=allc.macs,source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),formula_utility_path=str(UTIL.relative_to(ROOT)),formula_utility_sha256=hashlib.sha256(UTIL.read_bytes()).hexdigest(),official_generator_sha256=expected,old_request_sha256=hashlib.sha256((E/f'fp-word-conv6-{a.root}-request.json').read_bytes()).hexdigest(),old_runtime_sha256='ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540',unit='Integers in units2^-303; each exactproduct rawkey*rawkey<<5; RNE64 at every addition and both endpoints; all finite here. No host float needed except independent first32dot crosschecks percell.',limits=['Formula replay, not actual Lean branch instrumentation','No Lean proof or full12 gate','New guards are only replayed here; frozen runtime unchanged','Only oldseen batch1 MLP/nMLP/Mixer cells; no CNN or largerbatch coverage','Lazy cache terms are workload counts, not measured cost','No current champion timing'],platform=platform.platform(),python=platform.python_version())
    dest=H/f'fp-census-narrow-{a.root}.json';dest.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8');print(json.dumps({k:result[k]for k in ['complete','elapsed_seconds','root_seed','total_counts','total_macs']},indent=2));print(f'cells={len(rows)} all_output_hashes_match=True')

if __name__=='__main__':main()

