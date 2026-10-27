"""Finite representation/tail probe only; no candidate Kernel or machine timing."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,random
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
BASE=ROOT/'competitions/floatlib/candidates/f01-r11-crossrow-p2-pack12'
sp=importlib.util.spec_from_file_location('r11_baseline_model',BASE/'model-check.py')
m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);o=m.o
def two_streams(batch,rows,n,A,B,counts):
    packed=[]
    for b in range(batch):
        bbase=b*n*2
        bp=[(o.canon(m.get(B,bbase+2*k)),o.canon(m.get(B,bbase+2*k+1))) for k in range(n)]
        counts['B2_records']+=n
        groups=[]
        for g in range((rows+3)//4):
            aa=[(b*rows+4*g+i)*n for i in range(4)]
            ap=[[o.canon(m.get(A,a+k)) for a in aa] for k in range(n)]
            counts['A4_records']+=n
            counts['extra_MACs']+=2*n*max(0,4*g+4-rows)
            s=[0]*8
            for k in range(n):
                s=[o.native_model(o.add,s[l],o.native_model(o.mul,ap[k][l%4],bp[k][l//4])) for l in range(8)]
            w=[]
            for i in range(4):
                for j in range(2):
                    v=s[i+4*j]
                    if o.nan(v):
                        v=o.dot([m.get(A,aa[i]+k) for k in range(n)],
                                [m.get(B,bbase+2*k+j) for k in range(n)])
                    w.append(v)
            groups.append(w)
        packed.append(groups)
    return [packed[q//(rows*2)][((q//2)%rows)//4][2*((q//2)%rows%4)+q%2]
            for q in range(batch*rows*2)]
def main():
    rng=random.Random(20261024013);count=0;outputs=0;trace=hashlib.sha256()
    counts={'B2_records':0,'A4_records':0,'extra_MACs':0}
    for batch in [0,1,2,3,5]:
        for rows in [0,1,2,3,4,5,6,7,8,9,15,16,17,118]:
            for n in [0,1,2,3,7,29]:
                for mode in ['raw','edges','zero']:
                    def word():
                        return rng.getrandbits(32) if mode=='raw' else rng.choice(m.EDGE if mode=='edges' else [0,0x80000000])
                    A=[word() for _ in range(batch*rows*n)]
                    B=[word() for _ in range(batch*n*2)]
                    got=two_streams(batch,rows,n,A,B,counts)
                    want=m.reference(batch,rows,n,A,B)
                    assert got==want,(batch,rows,n,mode)
                    count+=1;outputs+=len(got)
                    for w in got:trace.update(w.to_bytes(4,'little'))
    report={'state':'PASS_FINITE_TWO_STREAM_SHAPE_WORD_MODEL','at_utc':datetime.now(timezone.utc).isoformat(),
            'seed':20261024013,'cases':count,'outputs':outputs,'logical_operations':counts,
            'trace_sha256':trace.hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
            'base_model_sha256':hashlib.sha256((BASE/'model-check.py').read_bytes()).hexdigest(),
            'scope':'Exploratory by-batch A4/B2 representation, including partial groups whose unused A lanes may point into nextbatch. Common exact-word model only; no Lean, actual C, allocations, runtime, speed or full-gate claim. No newKernel/CI.'}
    (HERE/'astra-a4b2-shape-model.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report))
if __name__=='__main__':main()
