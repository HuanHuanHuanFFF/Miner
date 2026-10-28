from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import importlib.util
import itertools
import json

here=Path(__file__).resolve().parent
repo=next(p for p in here.parents if (p/'AGENTS.md').is_file())
round_dir=here.parents[1]
oracle_path=repo/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
assert sha256(oracle_path.read_bytes()).hexdigest()=='3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'
spec=importlib.util.spec_from_file_location('old_oracle',oracle_path)
o=importlib.util.module_from_spec(spec);spec.loader.exec_module(o)

def fast(w):
    a=w&0x7fffffff
    return 0x0bffffff<=((a-1)&0xffffffff) and a<0x7f800000

def eligible(u,v): return ((u|v)&0x7f800000)==0

def words(u,v):
    a=u&0x7fffff; b=v&0x7fffff; s=u&0x80000000
    if ((u^v)&0x80000000)==0:return s|(a+b)
    if a==b:return 0
    return (s|(a-b)) if b<a else ((v&0x80000000)|(b-a))

def entry(u,v):
    if fast(u) and fast(v): return o.native_model(o.add,u,v),'unchanged_hot'
    if eligible(u,v):return words(u,v),'new_cold_E0'
    return o.add(u,v),'old_cold_fallback'

fractions=[0,1,2,3,0x3fffff,0x400000,0x7ffffe,0x7fffff]
trace=sha256(); rows=[]; core_cases=0
for a,b,s,t in itertools.product(fractions,fractions,[0,0x80000000],[0,0x80000000]):
    u=a|s;v=b|t;expected=o.add(u,v)
    assert words(u,v)==expected
    got,path=entry(u,v);assert got==expected
    trace.update(f'{u:08x} {v:08x} {got:08x} {path}\n'.encode());core_cases+=1
boundary=[('minnormal_pair',0x00800000,0x00800000),
 ('low_normal_cancel',0x0b800001,0x8b800000),('normal_hot',0x3f800000,0xbf800000),
 ('overflow_hot',0x7f7fffff,0x7f7fffff),('infinity_invalid',0x7f800000,0xff800000),
 ('qnan_payload',0x7fc00001,0x3f800000),('snan_priority',0x7fc00042,0xff800123),
 ('mixed_subnormal_normal',1,0x00800000)]
for name,u,v in boundary:
    got,path=entry(u,v);ref=o.add(u,v);assert got==ref
    rows.append({'name':name,'u':f'{u:08x}','v':f'{v:08x}','path':path,'result':f'{got:08x}'})
mutations=[
 {'name':'mask_sum_loses_normal_carry','u':'007fffff','v':'00000001','correct':'00800000','wrong':'00000000'},
 {'name':'opposite_equal_keeps_left_sign','u':'80000001','v':'00000001','correct':'00000000','wrong':'80000000'},
 {'name':'opposite_difference_keeps_left_sign','u':'00000001','v':'80000002','correct':'80000001','wrong':'00000001'},
 {'name':'xor_exponent_guard_admits_low_normal_pair','u':'00800000','v':'00800000','correct':'01000000','wrong':'00000000'}]
for row in mutations:
    u=int(row['u'],16);v=int(row['v'],16)
    assert o.add(u,v)==int(row['correct'],16) and row['correct']!=row['wrong']
runtime=(here/'Runtime.lean.inc').read_bytes()
parent=round_dir/'development-nativecold/NativeColdAdd.lean.inc'
parent_bytes=parent.read_bytes()
assert sha256(parent_bytes).hexdigest()=='21cd91284ee5bc31fed0e7aaa3b1cf35e6a705cbe2e680d8095baf2388551f50'
hot=parent_bytes[parent_bytes.index(b'  if R2W01b.fastOK'):parent_bytes.index(b'  else coldAdd x y')]
assert runtime.count(hot)==1 and len(runtime)<=1000
refs=[repo/'competitions/floatlib/candidates/f01-d7-research/round1h-20261027T103538Z/research/scalar-frontier/LOW-LATTICE-NEXT.md',
      round_dir/'research/independent-frontier/Runtime-same-exponent.lean.inc',
      round_dir/'development-cost3-summary.json',parent]
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'first_tool_utc':'2026-10-28T02:32:16Z',
 'bound_utc':'2026-10-28T02:47:16Z','common_deadline_utc':'2026-10-28T03:12:47Z',
 'runtime':{'sha256':sha256(runtime).hexdigest(),'bytes':len(runtime)},
 'original_primary_predicate_and_hot_body_byte_identical':True,
 'fixed_E0_core_cases':core_cases,'other_boundary_cases':len(rows),'mismatches':0,'trace_sha256':trace.hexdigest(),
 'boundary_rows':rows,'falsifiable_mutations':mutations,
 'references':[{'path':p.relative_to(repo).as_posix(),'sha256':sha256(p.read_bytes()).hexdigest(),'bytes':p.stat().st_size} for p in refs],
 'scope':'Fixed source-derived word model, not native/Lean/exhaustive proof or timing. No random/domain/threshold sweep.',
 'history':'R21 E0 exact integer formula paper only. Old measured R22 same-exponent source includes same-sign E0, but also normal frontdoor and inline B2 miss; its aggregate negative does not isolate E0 and is not this complete cold body.',
 'same_complete_cold_body_negative':'NOT_FOUND_IN_BOUNDED_SEARCH; no universal novelty claim',
 'Lean':'NOT_RUN','CI':'NOT_RUN','performance':'UNKNOWN','public_proof':'NOT_ASSEMBLED'}
(here/'manifest.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'runtime':out['runtime'],'fixed_cases':core_cases+len(rows),'same_primary_hot':True,'Lean':'NOT_RUN'}))
