"""Independent inverse patch, structural contracts and finite opaque A-layout traces."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,time
H=Path(__file__).resolve().parent;start=time.monotonic()
sha=lambda b:hashlib.sha256(b).hexdigest()
base=(H.parent/'Kernel-temporal-b2.lean').read_bytes()
src=(H/'Kernel-dual-temporal-a4.lean').read_bytes();frag=(H/'DualTemporal.lean.inc').read_bytes()
meta=json.loads((H/'build-receipt.json').read_bytes())
assert sha(src)==meta['source_sha256'] and sha(frag)==meta['fragment_sha256']
assert src.endswith(b'\n'+frag)
pruned=src[:-len(frag)-1].decode();newlines=pruned.splitlines(keepends=True)
patch=(H/'pruning.patch').read_text().splitlines(keepends=True)
# Apply the recorded unified diff in reverse, checking every consumed context/addition.
i=2;cursor=0;restored=[];hunks=0
while i<len(patch):
 m=re.match(r'@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@',patch[i]);assert m
 new_start=int(m[3]);new_count=int(m[4] or 1);position=new_start if new_count==0 else new_start-1
 assert position>=cursor;restored.extend(newlines[cursor:position]);cursor=position;i+=1;hunks+=1
 while i<len(patch) and not patch[i].startswith('@@ '):
  line=patch[i];i+=1
  if line.startswith(' '):
   assert newlines[cursor]==line[1:];restored.append(line[1:]);cursor+=1
  elif line.startswith('+'):
   assert newlines[cursor]==line[1:];cursor+=1
  elif line.startswith('-'):restored.append(line[1:])
  else:raise ValueError(line)
restored.extend(newlines[cursor:]);assert ''.join(restored).encode()==base
assert sha(base)=='c70cf9479ca48b4690990ebbd0b3781139cbeb94e46b28bbe61563e3eeaced1c'
def block(s,begin,end):
 a=s.index(begin);b=s.index(end,a)+len(end);return s[a:b]
assert block(src.decode(),'namespace Submission.R19Temporal\n','end Submission.R19Temporal')==block(base.decode(),'namespace Submission.R19Temporal\n','end Submission.R19Temporal')
body=frag.decode();runtime_loop=body[body.index('def loop ('):body.index('theorem loop_eq (')]
assert all(x not in runtime_loop for x in ('ofBits','toFloat32','R19Temporal.read','Array.map','Array.ofFn'))
packrow=body[body.index('def packRow '):body.index('theorem packRow_prefix')]
assert 'mkEmpty' not in packrow and 'Vector.ofFn' not in packrow and '.push ' in packrow
output=body[body.index('def output ('):body.index('theorem output_eq (')]
assert output.count('packA ')==1 and output.count('R19Temporal.packB ')==1
assert set(re.findall(r'R15PackedB2\.(\w+)',src.decode()))=={'tileIndex'}
public=body[body.rindex('namespace Submission\n'):].strip()
old_public=(H/'removed-current-public.txt').read_text().strip()
normalize=lambda s:re.sub(r'\s+','',s)
assert normalize(public.replace('R19DualTemporal.dispatch','R19Temporal.dispatch'))==normalize(old_public)
reads=chains=shapechecks=0
def raw(size,i):return ('A',i) if i<size else ('positive-zero-default',)
for rows in range(10):
 for n in range(14):
  T=(n+3)//4
  for length in sorted({0,1,max(0,rows*n-1),rows*n}):
   flat=[]
   for r in range(rows):
    for t in range(T):flat.append(tuple(raw(length,r*n+4*t+j) if 4*t+j<n else ('padzero',) for j in range(4)))
   assert len(flat)==rows*T
   for r in range(rows):
    for t in range(T):
     for j in range(4):
      if 4*t+j<n:assert flat[r*T+t][j]==raw(length,r*n+4*t+j);reads+=1
    for lane in range(2):
     old=new=('seed+0',)
     for k in range(n):old=('add',old,('mul',raw(length,r*n+k),('B',k,lane)))
     for t in range(T):
      for j in range(4):
       k=4*t+j
       if k<n:new=('add',new,('mul',flat[r*T+t][j],('B',k,lane)))
     assert old==new;chains+=1
   shapechecks+=1
   assert time.monotonic()-start<4.5
report={'at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':sha(src),'source_bytes':len(src),'inverse_patch_to_exact_c70c':True,'inverse_hunks':hunks,'c70c_namespace_byte_identical':True,'public_underflow_and_miss_shape_unchanged_except_new_dispatch':True,'runtime_loop_has_no_raw_conversions_at_source':True,'single_flat_A_buffer_source':True,'finite_layout_shapes':shapechecks,'valid_prepared_A_reads':reads,'ordered_lane_expressions':chains,'domain':{'rows':'0..9','n':'0..13','raw_A_length':'0,1,rows*n-1,rows*n'},'scope':'Finite opaque address/order and source checks only; no Float32 execution, local Lean, codegen or speed. Actual no-spill/no-closure claim still requires selected C/ASM.','formal':'NOT_RUN','full_gate':'NOT_RUN','elapsed_seconds':time.monotonic()-start}
(H/'check-receipt.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report))
