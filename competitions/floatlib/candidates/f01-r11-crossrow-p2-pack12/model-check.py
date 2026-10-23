"""Finite wiring/word-model checks. Not Lean, hardware, or performance evidence."""
from pathlib import Path
import hashlib, importlib.util, json, random
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
ORACLE = ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
EXPECTED = '3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'
assert hashlib.sha256(ORACLE.read_bytes()).hexdigest() == EXPECTED
spec = importlib.util.spec_from_file_location('r11_word_oracle', ORACLE)
o = importlib.util.module_from_spec(spec)
spec.loader.exec_module(o)
EDGE = [0,0x80000000,1,0x80000001,0x7fffff,0x807fffff,0x800000,0x80800000,
        0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,
        0x7fc00000,0xffc00001,0x7f800001,0xff800002,0x7fffffff,0xffffffff]

def get(a, i): return a[i] if i < len(a) else 0

def reference(batch, m, n, A, B):
    return [o.dot(A[r*n:(r+1)*n], [B[(r//m)*n*2+k*2+j] for k in range(n)])
            for r in range(batch*m) for j in range(2)]

def candidate(batch, m, n, A, B, counts):
    words = []
    for g in range((batch*m+3)//4):
        rows = [4*g+i for i in range(4)]
        aa = [r*n for r in rows]
        bb = [r//m*n*2 for r in rows]
        shared = len(set(bb)) == 1
        counts['shared_b_groups' if shared else 'cross_batch_groups'] += 1
        counts['unused_tail_lanes'] += 2*sum(r >= batch*m for r in rows)
        packets = []
        for k in range(n):
            av = [o.canon(get(A, a+k)) for a in aa]
            bv = [o.canon(get(B, b+2*k+j)) for j in range(2) for b in bb]
            if shared:
                common = [o.canon(get(B, bb[0]+2*k+j)) for j in range(2)]
                assert bv == [common[j] for j in range(2) for _ in range(4)]
            packets.append((av,bv))
        acc = [0]*8
        for av,bv in packets:
            acc = [o.native_model(o.add, acc[l], o.native_model(o.mul, av[l%4], bv[l]))
                   for l in range(8)]
        w = []
        for i in range(4):
            for j in range(2):
                l = i+4*j
                if o.nan(acc[l]):
                    counts['nan_replays'] += 1
                    value = o.dot([get(A,aa[i]+k) for k in range(n)],
                                  [get(B,bb[i]+2*k+j) for k in range(n)])
                else:
                    value = acc[l]
                w.append(value)
        words.append(w)
    return [words[(q//2)//4][2*((q//2)%4)+(q%2)] for q in range(batch*m*2)]

def main():
    rng=random.Random(20261024011)
    trace=hashlib.sha256()
    counts={k:0 for k in ['matrices','outputs','shared_b_groups','cross_batch_groups','unused_tail_lanes','nan_replays']}
    for batch in [0,1,2,3,5]:
        for m in [0,1,2,3,4,5,7,8]:
            for n in [0,1,2,3,4,7,16,33]:
                for mode in ['random','edge','zeros','finite']:
                    def word():
                        if mode=='zeros': return rng.choice([0,0x80000000])
                        if mode=='edge': return rng.choice(EDGE)
                        w=rng.getrandbits(32)
                        return w if mode=='random' or o.exp(w)!=255 else w & 0xfeffffff
                    A=[word() for _ in range(batch*m*n)]
                    B=[word() for _ in range(batch*n*2)]
                    got=candidate(batch,m,n,A,B,counts)
                    want=reference(batch,m,n,A,B)
                    assert got==want, (batch,m,n,mode)
                    counts['matrices']+=1; counts['outputs']+=len(want)
                    for w in got:trace.update(w.to_bytes(4,'little'))
    report={'status':'PASS_FINITE_WORD_AND_WIRING_MODEL','at_utc':datetime.now(timezone.utc).isoformat(),
            'seed':20261024011,'kernel_sha256':hashlib.sha256((HERE/'Kernel.lean').read_bytes()).hexdigest(),
            'model_script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
            'oracle_sha256':EXPECTED,'counts':counts,'output_trace_sha256':trace.hexdigest(),
            'scope':'Python transcription, common source-derived oracle; validates finite address/lane/word behavior including tails and cross-batch groups. Native modeled canonically, not executed. Not Lean proof, independent oracle, hardware, or timing. Core n=0 tested mathematically although actual entry falls back.'}
    (HERE/'model-check.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report))

if __name__=='__main__':main()
