from pathlib import Path
import datetime, hashlib, json
import importlib.util

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('finite_model',HERE/'fallback-probe.py')
m=importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)

def fold(ws):
    acc=0
    for w in ws: acc=m.add(acc,w)
    return acc

def fused_finite(a,b,c):
    x,ex=m.unpack(a); y,ey=m.unpack(b); z,ez=m.unpack(c)
    e=min(ex+ey,ez)
    exact=((x*y) << (ex+ey-e)) + (z << (ez-e))
    return m.round_finite(exact,e)

a,b,c=0x3f800001,0x3f7ffffe,0xbf800000
separate=m.add(m.mul(a,b),c)
fused=fused_finite(a,b,c)
assert separate==0 and fused==0xa8800000
ws=[0x4b800000,0x3f800000,0xcb800000]
sequential=fold(ws)
reordered=fold([ws[0],ws[2],ws[1]])
assert sequential==0 and reordered==0x3f800000
rows=[
 {'claim':'Reordering the k reduction is harmless','input_bits':[f'0x{w:08x}' for w in ws],
  'sequential_bits':f'0x{sequential:08x}','order_0_2_1_bits':f'0x{reordered:08x}',
  'bmm_embedding':'batch=1,m=1,n=3,p=1; A=input_bits, B=[1,1,1]'},
 {'claim':'FMA can replace separately rounded multiplication and addition',
  'a':f'0x{a:08x}','b':f'0x{b:08x}','c':f'0x{c:08x}',
  'rounded_product':f'0x{m.mul(a,b):08x}',
  'separate':f'0x{separate:08x}','fused':f'0x{fused:08x}'},
 {'claim':'Return rhs whenever lhs is zero','a':'0x00000000','b':'0x80000000',
  'correct':f'0x{m.add(0,0x80000000):08x}','wrong':'0x80000000'},
 {'claim':'Skip every zero rhs for an arbitrary accumulator','a':'0x80000000','b':'0x00000000',
  'correct':f'0x{m.add(0x80000000,0):08x}','wrong':'0x80000000'}
]
result={'checked_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
 'model_sha256':hashlib.sha256((HERE/'fallback-probe.py').read_bytes()).hexdigest(),
 'scope':'Exact finite integer model counterexamples, not Lean proof or official target execution',
 'rows':rows}
(HERE/'counterexamples.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
print(json.dumps(result,indent=2))
