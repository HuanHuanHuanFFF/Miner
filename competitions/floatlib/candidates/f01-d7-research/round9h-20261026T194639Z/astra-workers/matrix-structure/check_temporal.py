from pathlib import Path
from types import SimpleNamespace
from datetime import datetime,timezone
import ast,hashlib,json,re,time
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
t0=time.monotonic()
sha=lambda b:hashlib.sha256(b).hexdigest()
base=(R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
src=(H/'Kernel-temporal-b2.lean').read_bytes()
frag=(H/'Temporal.lean.inc').read_bytes()
assert src.endswith(frag)
back=src[:-len(frag)].removesuffix(b'\n')
back=back.replace(b'def bmmBeforeTemporal (',b'def bmm (',1).replace(b'theorem bmmBeforeTemporal_spec',b'theorem bmm_spec',1).replace(b'(bmmBeforeTemporal batch',b'(bmm batch',1).replace(b'unfold bmmBeforeTemporal',b'unfold bmm',1)
assert back==base and sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text())
env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
    node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
    env[name]=re.compile(ast.literal_eval(node.value.args[0])) if name=='BANNED' else ast.literal_eval(node.value)
fs=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
checks={k:env[k](H/'Kernel-temporal-b2.lean',SimpleNamespace(slot='full')) for k in ('intake','policy')}
checks['options']=env['options'](src.decode())
assert all(x is None for x in checks.values()),checks

# Address and expression trace of this exact chosen k-block/control design.
# No floating-point values are substituted; preserves nested ordered expressions.
def raw(size,i): return ('input',i) if i<size else ('zero',)
shapes=lanes=terms=packreads=0
for batch in range(4):
 for n in range(17):
  for p in range(11):
   G=(p+1)//2;T=(n+3)//4;bs=batch*n*p
   prepared=[]
   for bt in range(batch*G):
    b,g=divmod(bt,G);baseB=b*n*p+2*g
    cells=[]
    for q in range(T):
     packet=[]
     for k in range(4*q,4*q+4):
      for j in range(2):
       packet.append(raw(bs,baseB+j+k*p) if k<n else ('padzero',))
       if k<n: packreads+=1
     cells.append(packet)
    prepared.append(cells)
   for m in range(9):
    output=[]
    for r in range(batch*m):
     b=r//m;baseA=r*n
     for g in range(G):
      baseB=b*n*p+2*g
      for j in range(2):
       old=new=('seed+0',)
       for k in range(n):
        old=('add',old,('mul',raw(batch*m*n,baseA+k),raw(bs,baseB+j+k*p)))
       for q in range(T):
        for offset in range(4):
         k=4*q+offset
         if k<n:
          new=('add',new,('mul',raw(batch*m*n,baseA+k),prepared[b*G+g][q][2*offset+j]))
          terms+=1
       assert old==new
       lanes+=1
      output.extend(r*p+2*g+j for j in range(min(2,p-2*g)))
    assert output==list(range(batch*m*p))
    shapes+=1
    assert time.monotonic()-t0<4.8
meta={'at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':sha(src),'source_bytes':len(src),'baseline_exact_inverse':True,'original_text_policy':checks,'gate_sha256':sha(gate.read_bytes()),'finite_expression_shapes':shapes,'both_lane_expressions':lanes,'ordered_mac_terms':terms,'prepared_valid_lane_reads':packreads,'domain':{'batch':'0..3','m':'0..8','n':'0..16','p':'0..10'},'elapsed_seconds':time.monotonic()-t0,'scope':'Static policy and finite opaque operation/address model only; not Lean or Float32 execution','lean':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN'}
(H/'temporal-check.json').write_text(json.dumps(meta,indent=2)+'\n')
print(json.dumps(meta))
