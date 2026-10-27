"""Read-only source identity check; outputs only in this worker's directory."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
def item(rel):
    p=ROOT/rel;b=p.read_bytes()
    return {'path':rel,'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()}

b2='competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
r16='competitions/floatlib/candidates/f01-r16-dev-native-add-high3/Kernel.lean'
runtime='competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/public-source-runtime/sources/'
fixed='competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-upstream/FloatLib/'
evidence=[item(x) for x in [b2,r16,runtime+'lean-header.txt',runtime+'lean-object.txt',
  fixed+'Floats/ExecFloat/Backends/Generic/AddDyadic/Proof.lean',
  fixed+'Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean',
  fixed+'Floats/ExecFloat/Backends/Word/Narrow/Agreement.lean',
  'competitions/floatlib/candidates/f01-same-scale-add-proof1/Kernel.lean',
  'competitions/floatlib/candidates/f01-same-scale-add-proof1/manifest.json',
  'competitions/floatlib/candidates/f01-grs-normal-add-prototype/manifest.json',
  'competitions/floatlib/candidates/f01-r14-dev-word-add-entry2/Kernel.lean',
  'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/scalar-representation/final-C-cost.json',
  'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40186471996/download-f5591c4b0dae4beba81dc9eb7e7babc6/diagnostics/f01-d7-public-suite/public-suite/f01-r16-dev-add-interface2-verdict.json']]
assert evidence[0]['sha256']=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert evidence[1]['sha256']=='f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd'
assert evidence[2]['sha256']=='982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
assert evidence[3]['sha256']=='b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a'
cbase='competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168024176/download-97e5567f5b7c4fc2a261a6d6dac40edc/diagnostics/f01-d7-public-suite/public-suite/'
ip=item(cbase+'inputs/f01-r15-dev-packed-b2-1/Kernel.lean');assert ip['sha256']==evidence[0]['sha256']
cp=cbase+'diagnostics/f01-r15-dev-packed-b2-1/candidate-generated-1.c'
ci=item(cp); assert ci['sha256']=='94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb'
src=(ROOT/cp).read_text(encoding='utf-8')
sig='LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t '
start=src.index(sig);brace=src.index('{',start); depth=1;i=brace+1
while depth:
    depth+=(src[i]=='{')-(src[i]=='}');i+=1
body=src[start:i]
(HERE/'b2-selected-add.c').write_text(body+'\n',encoding='utf-8')
assert 'lp_competition_Bench_Suite_run(v___f_1220_, v___f_1221_' in src
assert 'v___f_1220_ = ((lean_object*)(lp_competition_main___closed__1))' in src
assert '.m_fun = (void*)lp_competition_main___lam__0___boxed' in src
calls={n:len(re.findall(r'\b'+n+r'\s*\(',body)) for n in ('lean_uint32_to_float32','lean_array_fget_borrowed',
    'lean_float32_mul','lean_float32_add','lean_float32_beq','lean_float32_to_bits','lean_float32_of_bits')}
evidence += [ip,ci]
report={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'SOURCE_IDENTITY_AND_SELECTED_C_ONLY',
    'sources':evidence,'B2_selected_add':{'run':40168024176,'selection':'BENCH_PLAN -> Bench.Suite.run first argument -> closed__1 -> lam__0___boxed -> lam__0',
    'original_line':src[:start].count('\n')+1,'function_sha256':hashlib.sha256(body.encode()).hexdigest(),'static_sites':calls,
    'limitations':'Static C sites, not dynamic cycles or assembly/timed ELF identity. General decode and NaN fallback are alternative paths.'},
    'log2':{'UInt32':'static inline C while(a>=2), floor(log2 a) loop iterations at source level',
            'Nat':'LEAN_EXPORT external function; scalar input and scalar output here, not a necessary heap allocation',
            'fixed_commit':'293d5d0c0c3f3dded4688b3ccd6a33939ac5102b',
            'authors':'Leonardo de Moura / Microsoft; Apache-2.0',
            'assembly':'UNKNOWN; no local compilation'},'new_kernel':'NONE','Lean':'NOT_RUN','CI':'NOT_RUN'}
(HERE/'evidence.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'source_files':len(evidence),'selected_add':report['B2_selected_add'],'log2':report['log2']},indent=2))
