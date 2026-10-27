"""Finite exact-word checks only; the existing Lean proof supplies general route.
No native execution, no speed claim, and no new authority for CI.
"""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,random,time
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
oracle=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
raw=oracle.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'
needed={'exp','frac','nan','snan','inf','zero','canon','choose','unpack','rounded','mul'}
env={};tree=ast.parse(raw)
exec(compile(ast.Module(body=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in needed],type_ignores=[]),str(oracle),'exec'),env)
start=time.perf_counter(); count=0; trace=hashlib.sha256()
def check(a,b):
    global count
    assert count<15000 and time.perf_counter()-start<4.4
    assert env['exp'](a)+env['exp'](b)<=84
    old=env['mul'](a,b);new=(a^b)&0x80000000
    assert old==new,(hex(a),hex(b),hex(old),hex(new))
    for x in (a,b,old): trace.update(x.to_bytes(4,'little'))
    count+=1
fracs=[0,1,0x3fffff,0x400000,0x7ffffe,0x7fffff]
for e in (0,1,2,42,83,84):
    for f in sorted({0,min(84-e,1),84-e}):
        for ma in fracs:
            for mb in fracs:
                for sa in (0,0x80000000):
                    for sb in (0,0x80000000):check(sa|(e<<23)|ma,sb|(f<<23)|mb)
rng=random.Random(15250084)
for _ in range(4096):
    ea=rng.randrange(85);eb=rng.randrange(85-ea)
    check((rng.randrange(2)<<31)|(ea<<23)|rng.randrange(1<<23),
          (rng.randrange(2)<<31)|(eb<<23)|rng.randrange(1<<23))
edges=[]
for a,b in [(0x00000000,0x7f800000),(0x80000000,0x7f800001),
            (0x19ffffff,0x1a7fffff),(0x00000000,0xff800000),
            (0x80000001,0x00000001),(0x00000001,0x80000001)]:
    hit=env['exp'](a)+env['exp'](b)<=84
    edges.append({'a':hex(a),'b':hex(b),'shortcut_guard':hit,'original':hex(env['mul'](a,b))})
assert not edges[0]['shortcut_guard'] and not edges[1]['shortcut_guard']
assert edges[2]['original']=='0x1' and not edges[2]['shortcut_guard']
result={'state':'PASS_FINITE_MODEL_ONLY','created_at_utc':datetime.now(timezone.utc).isoformat(),
 'cases':count,'max_cases':15000,'external_timeout_ms':5000,'internal_seconds':4.4,
 'elapsed_seconds':time.perf_counter()-start,'trace_sha256':trace.hexdigest(),
 'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
 'oracle_sha256':hashlib.sha256(raw).hexdigest(),'edges':edges,
 'scope':'Arbitrary sign and selected/random mantissas under raw exponent sum<=84. Not exhaustive, not Lean, no performance.'}
(HERE/'cutoff84-model.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(result))
