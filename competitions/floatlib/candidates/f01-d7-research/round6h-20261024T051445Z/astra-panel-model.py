"""Finite word/address check for the new shared row and local-panel/tail flow."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,random,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
sp=importlib.util.spec_from_file_location('oracle_model',CS/'f01-r11-crossrow-p2-pack12/model-check.py')
m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);o=m.o
get=lambda a,i:a[i] if 0<=i<len(a) else 0
def packed_b(batch,n,p,B):
    return [[[[o.canon(B[(b*n+k)*p+10*g+l]) if 10*g+l<p else 0 for l in range(10)]
              for k in range(n)] for g in range((p+9)//10)] for b in range(batch)]
def finish(n,p,rawA,rawB,A,B,s):
    return o.dot([get(A,rawA+k) for k in range(n)],
                 [get(B,rawB+k*p) for k in range(n)]) if o.nan(s) else s
def shared_row(n,p,numeric,rawA,rawB,A,B,native,rowB):
    out=[]
    for g in range((p+9)//10):
        s=[0]*10
        for k in range(n):
            av=get(native,numeric+k);bv=rowB[g][k]
            s=[o.native_model(o.add,s[l],o.native_model(o.mul,av,bv[l])) for l in range(10)]
        for l in range(min(10,p-10*g)):
            out.append(finish(n,p,rawA,rawB+10*g+l,A,B,s[l]))
    return out
def panel_core(batch,rows,n,p,A,B,c):
    pb=packed_b(batch,n,p,B);out=[];converted=0
    for b in range(batch):
        for h in range(rows//4):
            base=(b*rows+4*h)*n
            panel=[[o.canon(A[base+r*n+k]) for r in range(4)] for k in range(n)]
            converted+=4*n;c['F4_records']+=n
            tiles=[]
            for g in range((p+9)//10):
                s=[0]*40
                for k in range(n):
                    s=[o.native_model(o.add,s[4*l+r],o.native_model(o.mul,panel[k][r],pb[b][g][k][l]))
                       for l in range(10) for r in range(4)]
                tiles.append(s);c['wide_calls']+=1
            for r in range(4):
                for j in range(p):
                    out.append(finish(n,p,base+r*n,b*n*p+j,A,B,tiles[j//10][4*(j%10)+r]))
        first=4*(rows//4);rawbase=(b*rows+first)*n
        native=[o.canon(get(A,rawbase+i)) for i in range((rows-first)*n)]
        converted+=len(native);c['tail_native_values']+=len(native)
        for r in range(rows-first):
            out+=shared_row(n,p,r*n,rawbase+r*n,b*n*p,A,B,native,pb[b])
    assert converted==len(A)
    return out
def normal_core(batch,rows,n,p,A,B):
    native=list(map(o.canon,A));pb=packed_b(batch,n,p,B)
    return [w for b in range(batch) for r in range(rows)
            for w in shared_row(n,p,(b*rows+r)*n,(b*rows+r)*n,b*n*p,A,B,native,pb[b])]
def reference(batch,rows,n,p,A,B):
    return [o.dot(A[(b*rows+r)*n:(b*rows+r+1)*n],[B[(b*n+k)*p+j] for k in range(n)])
            for b in range(batch) for r in range(rows) for j in range(p)]
def main():
    rng=random.Random(202610241201);trace=hashlib.sha256()
    c={k:0 for k in ['matrices','outputs','F4_records','tail_native_values','wide_calls']}
    for batch in [0,1,2,3]:
      for rows in [0,1,3,4,5,7,8,9]:
       for n in [0,1,4,5,13]:
        for p in [0,1,2,3,9,10,11,21]:
          mode=c['matrices']%3
          def word():
              if mode==0:return rng.choice(m.EDGE)
              if mode==1:return rng.getrandbits(32)
              return rng.choice([0,0x80000000,1,0x800000,0x3f800000,0xbf800000])
          A=[word() for _ in range(batch*rows*n)];B=[word() for _ in range(batch*n*p)]
          want=reference(batch,rows,n,p,A,B)
          assert panel_core(batch,rows,n,p,A,B,c)==want,(batch,rows,n,p,'panel')
          assert normal_core(batch,rows,n,p,A,B)==want,(batch,rows,n,p,'normal')
          c['matrices']+=1;c['outputs']+=len(want)
          for w in want:trace.update(w.to_bytes(4,'little'))
    rec={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'PASS_FINITE_SHARED_ROW_PANEL_AND_TAIL_MODEL',
         'seed':202610241201,'counts':c,'trace_sha256':trace.hexdigest(),'oracle_sha256':m.EXPECTED,
         'model_script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
         'scope':'Finite source transcription with common exact-word oracle, not independent oracle, Lean, native execution or timing. Both normal/global numeric bases and localtail/raw replay separation checked; each inputA value converted exactly once onPanel model. Shapes outsideactualguard also test mathematicalcore.'}
    (HERE/'astra-panel-model.json').write_text(json.dumps(rec,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(rec))
if __name__=='__main__':main()
