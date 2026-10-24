"""Source-derived public-plan opportunity counts, NOT runtime measurements or Lean proof.

Own transcription of exact public BenchSuite word generator and integer binary32 oracle.
Reads a previously exposed discovery plan; never changes a final confirmation plan.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse, importlib.util, hashlib, json, time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
spec = importlib.util.spec_from_file_location('word_oracle', HERE/'nonfinite-oracle.py')
O = importlib.util.module_from_spec(spec); spec.loader.exec_module(O)
M64 = (1 << 64) - 1
M32 = (1 << 32) - 1

def word(seed, index, stream):
    z = (seed + index * 0x9e3779b97f4a7c15 + stream * 0xd1b54a32d192ed03) & M64
    z = ((z ^ (z >> 30)) * 0xbf58476d1ce4e5b9) & M64
    z = ((z ^ (z >> 27)) * 0x94d049bb133111eb) & M64
    return (z ^ (z >> 31)) & M32

def ctz(w):
    return (w & -w).bit_length()-1 if w else 32

def element(c, i, role, row):
    def draw(j, k): return word(c['seed'], j, role * 16 + k)
    if c['mag'] == 2: return draw(i, 0)
    special = False
    if c['specRate'] > 0:
        place = c['specPlace']
        if place == 1: special = (i+c['seed']+7*role) % c['specPeriod'] == 0
        elif place == 2: special = draw(i//c['specBurst'], 8) % 100000 < c['specRate']
        elif place == 3: special = i % row in (0, row-1) and draw(i, 9) % 100000 < c['specRate']
        else: special = draw(i, 9) % 100000 < c['specRate']
    if special:
        kinds = [k for k in range(5) if c['specMask'] & (1 << k)]
        kind = kinds[draw(i,5) % len(kinds)] if kinds else 1
        sign = draw(i,6) & 0x80000000
        low = draw(i,7) & 0x7fffff
        return sign | [0x7f800000, 0x7f800000 | low | 1, 0x7f7fffff, low | 1, 0][kind]
    if c['zeroPct'] > 0 and draw(i//c['zeroCluster'],11) % 100 < c['zeroPct']:
        w = draw(i,10)
        return {1:0x80000000,2:w & 0x80000000,3:(w & 0x807fffff) | ((1+w % 30)<<23)}.get(c['zeroKind'],0)
    if c['subPct'] > 0 and draw(i//c['subBlock'],12) % 100 < c['subPct']:
        return (draw(i,13) & 0x807fffff) | 1
    j = draw(i,14) % c['codebook'] if c['codebook'] > 0 else i
    w = draw(j,1)
    e = c['center'] - min(ctz(w), c['spread']) if c['mag']==1 else c['center']-c['spread']+w % (2*c['spread']+1)
    shift = draw(i//c['scaleBlock'],2) % (2*c['scaleShift']+1)-c['scaleShift'] if c['scaleBlock'] else 0
    keep = 0x7fffff if c['mantBits'] >= 23 else 0x7fffff ^ ((1 << (23-c['mantBits']))-1)
    sign = 0 if draw(j,4) % 100 < c['positive'] else 0x80000000
    return sign | (max(1,min(254,e+shift)) << 23) | (draw(j,3) & keep)

def empty():
    return dict(outputs=0,ordered_steps=0,nan_outputs=0,inf_outputs=0,nan_prefix_steps=0,
                nan_suffix_steps_saved=0,snan_override_outputs=0,reverse_snan_scan_words=0,
                snan_override_full_steps=0)

def run_case(c):
    r=empty();r.update(name=c['name'],kernel=c['kernel'],case=c,checksum32=0,reverse_suffix_scan_words=0)
    trace=hashlib.sha256(); checks=0
    def record(q,n,first,last_snan):
        r['outputs']+=1;r['ordered_steps']+=n
        assert not O.snan(q)
        if O.nan(q):
            assert first is not None
            r['nan_outputs']+=1;r['nan_prefix_steps']+=first+1
            r['nan_suffix_steps_saved']+=n-first-1
            if c['kernel']=='sum':
                r['reverse_snan_scan_words']+=n-last_snan if last_snan is not None else n
                r['reverse_suffix_scan_words']+=min(n-first-1,n-last_snan if last_snan is not None else n)
                if last_snan is not None:
                    r['snan_override_outputs']+=1;r['snan_override_full_steps']+=n
        else: assert first is None
        r['inf_outputs']+=int(O.inf(q));trace.update(q.to_bytes(4,'little'))
        r['checksum32']=((r['checksum32'] ^ q)*16777619) & M32
    if c['kernel']=='sum':
        n=c['length']
        for b in range(c['batch']):
            q=0;first=None;last=None;sample=[]
            for k in range(n):
                x=element(c,b*n+k,0,n)
                if checks < 2: sample.append(x)
                if O.snan(x): last=k
                if first is None:
                    q=O.add(q,x)
                    if O.nan(q): first=k
                elif O.snan(x): q=x | 0x400000
            if checks < 2:
                assert O.summation(sample)==q
                if last is not None: assert q==(sample[last] | 0x400000)
                checks+=1
            record(q,n,first,last)
    else:
        batch,m,n,p=(c[k] for k in ['batch','m','n','p'])
        A=[element(c,i,0,n) for i in range(batch*m*n)]
        B=[element(c,i,1,p) for i in range(batch*n*p)]
        for b in range(batch):
            for i in range(m):
                for j in range(p):
                    q=0;first=None;aa=(b*m+i)*n;bb=b*n*p+j
                    for k in range(n):
                        q=O.add(q,O.mul(A[aa+k],B[bb+k*p]))
                        if O.nan(q): first=k;break
                    if checks < 2:
                        assert q==O.dot(A[aa:aa+n],[B[bb+k*p] for k in range(n)])
                        checks+=1
                    record(q,n,first,None)
    r['derived_output_sha256']=trace.hexdigest()
    r['unoptimized_oracle_outputs_crosschecked']=checks
    return r

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--plan',required=True);ap.add_argument('--output',default='public-nonfinite-opportunity-805.json');args=ap.parse_args()
    planpath=ROOT/args.plan;plan=json.loads(planpath.read_text());start=time.monotonic()
    rows=[]
    for c in plan['cases']:
        if c['timed'] and c['kernel'] in ['sum','bmm']:
            row=run_case(c);rows.append(row)
            print(json.dumps({k:row[k] for k in ['name','outputs','nan_outputs','inf_outputs','snan_override_outputs']}) ,flush=True)
    totals={}
    for kernel in ['sum','bmm']:
        t=empty()
        for r in rows:
            if r['kernel']==kernel:
                for key in t:t[key]+=r[key]
        totals[kernel]=t
    out=dict(completed_at_utc=datetime.now(timezone.utc).isoformat(),plan=str(planpath.relative_to(ROOT)),plan_sha256=hashlib.sha256(planpath.read_bytes()).hexdigest(),generator_source_sha256=hashlib.sha256((HERE/'upstream/BenchSuite.lean').read_bytes()).hexdigest(),oracle_sha256=hashlib.sha256((HERE/'nonfinite-oracle.py').read_bytes()).hexdigest(),analysis_source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),python_analysis_seconds=time.monotonic()-start,totals=totals,cases=rows,scope='Derived finite public discovery-plan counts only; own source transcription, not actual Lean execution, benchmark timing, private-suite prevalence, success probability or independent confirmation. Saved steps omit first native pass/preparation/scan/repair overhead. Existing fixed public input plan unchanged.')
    dest=HERE/args.output;assert dest.resolve().is_relative_to(HERE.resolve());dest.write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(totals,indent=2))

if __name__=='__main__':main()
