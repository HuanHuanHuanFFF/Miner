"""Integer address/order and arbitrary checked-token oracle only; no Float32."""
from pathlib import Path
import json
from datetime import datetime,timezone
HERE=Path(__file__).resolve().parent
shapes=0; outputs=0; reads=0; failures=0; caught=set()
for batch in range(4):
 for m in range(8):
  for n in range(6):
   for p in range(11):
    G=(p+1)//2; size=batch*n*p
    native=lambda addr: ('native',addr) if addr<size else ('zero',0)
    cache=[]
    for t in range(batch*G):
     b,g=divmod(t,G);base=b*n*p+2*g
     tile=[]
     for k in range(n):
      tile.extend([native(base+k*p),native(base+1+k*p)]);reads+=2
     assert len(tile)==2*n
     cache.append(tile)
    assert len(cache)==batch*G
    for b in range(batch):
     for i in range(m):
      for j in range(p):
       t=b*G+j//2
       original=[(((b*m+i)*n+k),native((b*n+k)*p+j)) for k in range(n)]
       actual=[(((b*m+i)*n+k),cache[t][2*k+j%2]) for k in range(n)]
       assert actual==original
       outputs+=1
       if n and cache[j//2][j%2]!=original[0][1]:caught.add('drop_batch_from_tile_index')
       if n and cache[t][1-j%2]!=original[0][1]:caught.add('swap_pair_fields')
    # Check failures at first/middle/last stored field terminate before output.
    count=batch*G*n*2
    for bad in set([0,count//2,count-1]):
     if 0<=bad<count:
      seen=[];ok=True
      for q in range(count):
       source=('native-token',q);stored=('encoded-token',q)
       back=source if q!=bad else ('different-token',q)
       seen.append((source,stored,back))
       if back!=source:ok=False;break
      assert not ok and len(seen)==bad+1
      failures+=1
    shapes+=1
assert caught=={'drop_batch_from_tile_index','swap_pair_fields'}
report=dict(at_utc=datetime.now(timezone.utc).isoformat(),shapes=shapes,
 valid_output_order_comparisons=outputs,prepared_field_address_checks=reads,
 failed_prefix_oracle_cases=failures,mutations_caught=sorted(caught),
 scope='Finite integer addresses and arbitrary checked token identities only. No Float32, Lean, allocation, compiled behavior or performance claim.')
(HERE/'address-screen.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report))
