"""Conditional request arithmetic and old-source hashes; no runtime benchmark."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
R=ROOT/'competitions/floatlib/candidates/f01-d7-research'
sha=lambda b:hashlib.sha256(b).hexdigest()
def rec(p):
 b=p.read_bytes();return dict(path=str(p.relative_to(ROOT)),bytes=len(b),sha256=sha(b))
def model(T,n):
 N=T*n;old=24+32*T+24*N;new=24+32*T+16*N
 opts=16*(T+1);closures=64+56*T
 return dict(T=T,n=n,N=N,old_persistent_request=old,new_persistent_request=new,
  ordinary_some_cumulative_request=opts,old_diagnostic_closure_requests=closures,
  difference_excluding_old_closures=new+opts-old,
  conditional_difference_including_old_closures=new+opts-old-closures,
  explicit_prepare_native_bits_expressions=4*N)
tiny=[model(T,n) for T in [1,2,1000] for n in [2,3,4,8]]
assert all(x['difference_excluding_old_closures']==16+x['T']*(16-8*x['n']) for x in tiny)
assert all(x['conditional_difference_including_old_closures']==-48-40*x['T']-8*x['N'] for x in tiny)
exposure=json.loads((HERE.parent/'cache-lifetime-exposure.json').read_bytes());groups=[]
for g in exposure['groups']:
 cases=[model(r['batch']*((r['p']+1)//2),r['n']) for r in g['rows']]
 groups.append(dict(run=g['run'],seed=g['seed'],shapes=len(cases),
  totals={k:sum(r[k] for r in cases) for k in ['T','N','old_persistent_request','new_persistent_request',
   'ordinary_some_cumulative_request','old_diagnostic_closure_requests',
   'difference_excluding_old_closures','conditional_difference_including_old_closures',
   'explicit_prepare_native_bits_expressions']}))
old=R/'round3h-20261025T043928Z/astra-workers/matrix-structure'
sources=[old/'b2-C-audit-401680.json']+[old/'C-audit-401680'/(n+'.txt') for n in [
 'Submission_R15PackedB2_packB','Submission_R15PackedB2_packB___lam__1','Submission_R15PackedB2_packB___lam__0']]
index=json.loads(sources[0].read_bytes())
for p in sources[1:]:
 expected=next(x['body_sha256'] for x in index['functions'] if x['symbol']=='lp_competition_'+p.stem)
 assert sha(p.read_bytes())==expected
primary=ROOT/'competitions/floatlib/research/materials/20261024-r11/originals/W03/original-extracted/R11-W03/agent-runtime/primary'
for rel in ['src/runtime/object.cpp','src/include/lean/lean.h','src/Lean/Compiler/LCNF/MonoTypes.lean','src/Lean/Compiler/LCNF/EmitC.lean']:
 p=primary/rel;manifest=json.loads((primary/'manifest.json').read_bytes());expected=next(x['sha256'] for x in manifest if x['path']==rel);assert sha(p.read_bytes())==expected;sources.append(p)
c=HERE.parents[1]/'independent-frontier'; idx=json.loads((c/'codec-source-index.json').read_bytes())
for name in ['codec-LCNF-Irrelevant.lean','codec-LCNF-ToImpure.lean']:
 p=c/name;expected=next(x['sha256'] for x in idx['files'] if x['name']==name);assert sha(p.read_bytes())==expected;sources.append(p)
frozen={n:rec(HERE/n) for n in ['Runtime.lean.inc','Kernel-probe.lean','CheckedPrefix.lean.inc']}
assert [v['sha256'] for v in frozen.values()]==[
'f5a6cbc6a89ccccd1e08cb861ce483d447d9b8dc30feed21ef24a2f30e5cacf8',
'303a239716b2521a72093453f7d363553055bc2702f481a09837a6ed53724da1',
'91ac9aa73ad8ae2a29bed7d08a901da27af45c1324d6854aa56ef6eacd4a6b93']
out=dict(at_utc=datetime.now(timezone.utc).isoformat(),phase_start_utc='2026-10-28T01:32:01Z',
 phase_limit_utc='2026-10-28T01:47:01Z',tiny_boundaries=tiny,old_exposed_plan_models=groups,
 sources=[rec(p) for p in sources],frozen_sources=frozen,report=rec(HERE/'ALLOCATION-PREMISE.md'),
 validation='SOURCE_AND_CONDITIONAL_REQUEST_MODEL_ONLY',
 actual_new_C='UNKNOWN',actual_allocation='UNKNOWN',actual_failure_cleanup_timing='UNKNOWN',
 scope='64bit exact capacity, no shared copies/allocator rounding. Option ordinary-allocation scenario and old diagnostic closure scenario are separate. No new benchmark/CI/confirmation inputs/source variant.')
(HERE/'allocation-premise.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(at_utc=out['at_utc'],report=out['report'],groups=groups),ensure_ascii=False))
