"""Finite guard comparison + exact integer overflow counterexamples; no Lean/CI."""
from pathlib import Path
from collections import Counter
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
OLD=ROOT/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z'
PUB=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
f7=(PUB/'f01-r22-dev-nativecombo-public1/Kernel.lean').read_bytes()
f90=(PUB/'f01-r23-dev-outline-public1/Kernel.lean').read_bytes()
assert sha(f7)=='f7ba2ddb12939f518e5beb60daf927d9d9d80d24262edd740eefd5e8e917cc03'
assert sha(f90)=='f90d42e346a1634ffeb537ea7e9980e0a91baea8499dc6c2235da5ab8fe0e85f'
MASK=(1<<32)-1
def native(u,v):return ((((u&0x7fffffff)-0x20000000)&MASK)|(((v&0x7fffffff)-0x20000000)&MASK))<0x40000000
def integer(u,v):
    eu,ev=(u>>23)&255,(v>>23)&255
    return ((eu-1)&MASK)<=253 and ((ev-1)&MASK)<=253 and (((eu+ev)-128)&MASK)<=252
counts=Counter(); native_only=[]
for eu in range(256):
  for ev in range(256):
    n,i=native(eu<<23,ev<<23),integer(eu<<23,ev<<23)
    assert n==(64<=eu<=191 and 64<=ev<=191)
    for fu,fv in [(0,0x7fffff),(0x7fffff,0),(0x7fffff,0x7fffff)]:
        assert native((eu<<23)|fu,(ev<<23)|fv)==n
        assert integer((eu<<23)|fu,(ev<<23)|fv)==i
    category='both' if n and i else 'native_only' if n else 'integer_only' if i else 'neither'
    counts[category]+=1
    if n and not i:native_only.append([eu,ev])
assert native_only==[[190,191],[191,190],[191,191]]
def normal_core(s,u,v):
    p=((u&0x7fffff)|0x800000)*((v&0x7fffff)|0x800000)
    t=23 if p<(1<<47) else 24
    b=p+((1<<(t-1))-1)+((p>>t)&1)
    high=b>>47;q=b>>(23+high);e=(s-127+high)&MASK
    return (((u^v)&0x80000000)|(e<<23)|(q-0x800000))&MASK,p
examples=[]
for u,v in [(0x00800000,0x3f800000),(0x7f000000,0x00800000),
            (0x5f000000,0x5f800000),(0x5f7fffff,0x5fffffff),(0x5fffffff,0x5fffffff)]:
    s=((u>>23)&255)+((v>>23)&255)
    out,p=normal_core(s,u,v)
    # Exact positive normal value is p*2^(s-300). RNE overflow threshold is 2^128-2^103.
    exp=s-300
    overflow=(p<<max(exp,0))>=(((1<<25)-1)<<(103+max(-exp,0)))
    examples.append({'u':hex(u),'v':hex(v),'sum':s,'native_guard':native(u,v),'integer_guard':integer(u,v),
        'normalCore_if_unconditionally_used':hex(out),'exact_RNE_overflow_proved_by_integer_threshold':overflow,
        'reference_if_overflow':'0x7f800000' if overflow else 'not inferred here'})
assert examples[3]['normalCore_if_unconditionally_used']=='0x7ffffffe' and examples[3]['exact_RNE_overflow_proved_by_integer_threshold']
assert examples[4]['normalCore_if_unconditionally_used']=='0x807ffffe' and examples[4]['exact_RNE_overflow_proved_by_integer_threshold']

newdir=HERE.parent/'ci-runs/40708758777/download-287146acc0e241ddbe29b6ef4f217408/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r23-dev-outline-public1'
asm=(newdir/'native-loop-6.asm.txt').read_bytes();c=(newdir/'candidate-generated-1.c').read_bytes()
index=json.loads((newdir/'native-assembly-index.json').read_bytes())
binding=next(x for x in index if x.get('file')=='native-loop-6.asm.txt')
assert binding['kernel_sha256']==sha(f90) and binding['sha256']==sha(asm)
instructions=[(m.group(1),m.group(2)) for m in re.finditer(rb'(?m)^\s*[0-9a-f]+:\s+([A-Za-z][A-Za-z0-9_]*)\s*([^\n]*)',asm) if not m.group(1).startswith(b'R_')]
assert len(instructions)==45
assert not any(op in [b'push',b'pop',b'call'] for op,args in instructions)
boxed=c.decode().split('LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(',2)[-1]
boxed=boxed[:boxed.index('LEAN_EXPORT lean_object* _lean_main')]
assert boxed.count('lean_unbox_uint32(')==2 and boxed.count('lean_dec(')==2 and boxed.count('lean_box_uint32(')==1
assert 'lp_competition_main___lam__1(' in boxed and 'lp_competition_Bench_Suite_run(' in c.decode()
oldcost=json.loads((OLD/'development-outline-mul/actual406073-review.json').read_bytes())
cost=[{'seed':r['seed'],'block':r['block'],'mul_share_in_old_diagnostic':r['control_ns']['mul']/r['control_ns']['whole'],
       'mul_ratio':r['ratios']['mul'],'whole_ratio':r['ratios']['whole']} for r in oldcost['blocks'] if r['variant']=='outline']
record={'native_source_sha256':sha(f7),'integer_source_sha256':sha(f90),'exponent_pair_counts':dict(counts),
    'native_only_pairs':native_only,'examples':examples,'guard_scope':'All 65536 exponent pairs, exact source guard algebra; fractions endpoint checked; signs masked. Counts are not workload probabilities.',
    'new_f90_actual_MainFull':{'asm_sha256':sha(asm),'main_C_sha256':sha(c),'object_sha256':binding['object_sha256'],
        'typed_instructions':45,'no_push_pop_call':True,'boxed_boundary':'2 unbox + 2 lean_dec + typed call + 1 lean_box_uint32; actual Bench.Suite.run selected closure',
        'scope':binding['scope']},'old_integer_diagnostic_cost':cost,
    'native_F7_stability':'40615975642 25 rounds: ratio0.9555001521; p05=-0.0041730576; NOT_ADOPTED; no same-source seed chase',
    'new_f90_performance':'UNKNOWN; 40708758777 statement/replay/49AX passed, no checksum/timing gate',
    'minimal_composition_interface':'guardedMul fallback (hf : forall x y, fallback x y = Spec.mul x y); can use an already proved native fallback, but new assembled source needs cap/AX/replay/runtime/timing checks',
    'composition_cap':'UNKNOWN until exact deduplicated assembly; f90 has2022B headroom, cannot append full F7 source',
    'decision':'Native-first may service31878 additional integer-only field pairs; integer-first leaves only3 native-only field pairs. Both have large overlap and common boxed ABI. Measure actual selected callbacks, full guard/miss cost and whole boundary before proof expansion or full25.',
    'benefit_bound':'Whole reduction = f_changed_path * local reduction only under fixed remaining costs. Current public sum/BMM retained; no addition of old F7 and old integer ratios.'}
(HERE/'mul-domain-crossing.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'counts':dict(counts),'native_only':native_only,'counterexamples':examples[3:], 'actual_f90_instructions':45,'old_cost':cost}))
