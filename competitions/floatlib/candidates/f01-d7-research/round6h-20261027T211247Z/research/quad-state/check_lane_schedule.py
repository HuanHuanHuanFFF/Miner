"""Bounded symbolic order/address discriminator, not Float32 or Lean execution."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json

HERE=Path(__file__).resolve().parent
RUNTIME=HERE.parents[1]/'development-cost/StreamingQuad.lean.inc'
EXPECTED='e4bf61260eb03b6e578a5e1410cd446d4f7b9585e5a819059ac5f5a899c795ea'
assert hashlib.sha256(RUNTIME.read_bytes()).hexdigest()==EXPECTED

def term(s,a,b):return ('add',s,('mul',('A',a),('B',b)))
def quad(p,n,baseA,baseB,k,zero=False,mutant=None):
    s=[[('positive_zero',) if zero else ('state',lane,j) for lane in range(4)] for j in range(p)]
    order=list(range(k,n))
    if mutant=='reverse_k':order.reverse()
    for t in order:
        for j in range(p):
            for lane in range(4):
                a=baseA+(n if mutant=='lane2_reuses_lane1' and lane==2 else lane*n)+t
                b=baseB+t*(n if mutant=='B_stride_n' else p)+j
                s[j][lane]=('mul',('A',a),('B',b)) if mutant=='skip_initial_add' and zero and t==k else term(s[j][lane],a,b)
    return s
def reference(p,n,baseA,baseB,k,zero=False):
    s=[]
    for j in range(p):
        lanes=[]
        for lane in range(4):
            acc=('positive_zero',) if zero else ('state',lane,j)
            for t in range(k,n):acc=term(acc,baseA+lane*n+t,baseB+j+t*p)
            lanes.append(acc)
        s.append(lanes)
    return s

checked=0; outputs=0; trace=hashlib.sha256(); caught={}
for p in range(8):
 for n in range(8):
  for baseA in (0,1,17):
   for baseB in (0,5):
    for k in (0,n//2,n,n+1):
     for zero in (False,True):
      expected=reference(p,n,baseA,baseB,k,zero)
      actual=quad(p,n,baseA,baseB,k,zero)
      assert expected==actual,(p,n,baseA,baseB,k,zero)
      checked+=1;outputs+=p*4
      trace.update(repr((p,n,baseA,baseB,k,zero,actual)).encode())
      for mutation in ('reverse_k','lane2_reuses_lane1','B_stride_n','skip_initial_add'):
       if mutation not in caught and quad(p,n,baseA,baseB,k,zero,mutation)!=expected:
        caught[mutation]={'p':p,'n':n,'baseA':baseA,'baseB':baseB,'k':k,'zero':zero}
assert len(caught)==4
result={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'SYMBOLIC_LANE_SCHEDULE_DISCRIMINATOR_PASS',
 'runtime_sha256':EXPECTED,'configurations_checked':checked,'lane_outputs_checked':outputs,
 'domain':{'p':'0..7','n':'0..7','baseA':[0,1,17],'baseB':[0,5],'k':['0','floor(n/2)','n','n+1'],'initial':['arbitrary lane state','explicit positive zero']},
 'detected_mutations':caught,'trace_sha256':trace.hexdigest(),
 'scope':'Exact symbolic Float32 operation ordering and raw input addresses only. Runtime/source reviewed manually and hash-bound; not native execution, Float32 semantic evaluation, full-input proof or Lean acceptance.'}
(HERE/'lane-schedule-check.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(result,indent=2))
