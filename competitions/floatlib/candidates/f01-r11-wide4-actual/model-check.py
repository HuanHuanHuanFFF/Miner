"""Finite word/address transcription; not Lean, hardware, or a performance test."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,random
HERE=Path(__file__).resolve().parent
MODEL=HERE.parent/'f01-r11-crossrow-p2-pack12/model-check.py'
sp=importlib.util.spec_from_file_location('old_model',MODEL)
m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);o=m.o

def reference(batch,rows,n,p,A,B):
    return [o.dot(A[(b*rows+r)*n:(b*rows+r+1)*n],
                  [B[(b*n+k)*p+j] for k in range(n)])
            for b in range(batch) for r in range(rows) for j in range(p)]

def actual_core(batch,rows,n,p,A,B,c):
    nativeA=list(map(o.canon,A))
    packedB=[[[[o.canon(B[(b*n+k)*p+10*g+l]) if 10*g+l<p else 0
                for l in range(10)] for k in range(n)] for g in range((p+9)//10)]
             for b in range(batch)]
    out=[]
    def finish(s,b,r,j):
        if o.nan(s):
            c['valid_nan_replays']+=1
            return o.dot(A[(b*rows+r)*n:(b*rows+r+1)*n],
                         [B[(b*n+k)*p+j] for k in range(n)])
        return s
    for b in range(batch):
        for h in range(rows//4):
            tiles=[]
            for g in range((p+9)//10):
                s=[0]*40
                for k in range(n):
                    a=[nativeA[(b*rows+4*h+r)*n+k] for r in range(4)]
                    v=packedB[b][g][k]
                    s=[o.native_model(o.add,s[4*l+r],o.native_model(o.mul,a[r],v[l]))
                       for l in range(10) for r in range(4)]
                tiles.append(s)
                c['wide_calls']+=1
                c['padding_nan_lanes']+=sum(o.nan(s[4*l+r]) for l in range(10)
                                           for r in range(4) if 10*g+l>=p)
            c['peak_block_F40s']=max(c['peak_block_F40s'],len(tiles))
            for r in range(4):
                for j in range(p):
                    out.append(finish(tiles[j//10][4*(j%10)+r],b,4*h+r,j))
        for r in range(4*(rows//4),rows):
            c['tail_rows']+=1
            for g in range((p+9)//10):
                s=[0]*10
                for k in range(n):
                    a=nativeA[(b*rows+r)*n+k];v=packedB[b][g][k]
                    s=[o.native_model(o.add,s[l],o.native_model(o.mul,a,v[l])) for l in range(10)]
                for l in range(min(10,p-10*g)):
                    out.append(finish(s[l],b,r,10*g+l))
    return out

def main():
    rng=random.Random(20261024040);trace=hashlib.sha256()
    c={k:0 for k in ['matrices','outputs','actual_shape_guard_hits','wide_calls','tail_rows','valid_nan_replays','padding_nan_lanes','peak_block_F40s']}
    for batch in [0,1,2,3]:
      for rows in [0,1,3,4,5,7,8,9]:
       for n in [0,1,4,5,13]:
        for p in [0,1,2,3,9,10,11,21]:
          mode=c['matrices']%3
          def word():
              if mode==0:return rng.choice(m.EDGE)
              if mode==1:return rng.getrandbits(32)
              return rng.choice([0,0x80000000,0x3f800000,0xbf800000,0x800000,1])
          A=[word() for _ in range(batch*rows*n)];B=[word() for _ in range(batch*n*p)]
          got=actual_core(batch,rows,n,p,A,B,c)
          want=reference(batch,rows,n,p,A,B)
          assert got==want,(batch,rows,n,p,mode)
          c['matrices']+=1;c['outputs']+=len(got)
          c['actual_shape_guard_hits']+=int(rows>=4 and n>4 and p>2)
          for w in got:trace.update(w.to_bytes(4,'little'))
    rec={'state':'PASS_FINITE_WORD_WIRING','at_utc':datetime.now(timezone.utc).isoformat(),
         'kernel_sha256':hashlib.sha256((HERE/'Kernel.lean').read_bytes()).hexdigest(),
         'model_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
         'oracle_sha256':m.EXPECTED,'base_model_sha256':hashlib.sha256(MODEL.read_bytes()).hexdigest(),
         'seed':20261024040,'counts':c,'trace_sha256':trace.hexdigest(),
         'scope':'Python source transcription sharing existing exact-word oracle. Tests complete core including shapes routed elsewhere by actual guard. Native arithmetic modeled canonically; no actual Lean/native execution, independent oracle, timing or full-gate claim.'}
    (HERE/'model-check.json').write_text(json.dumps(rec,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(rec))
if __name__=='__main__':main()
