"""Read-only audit of D's collected original receipts; writes only this research directory."""
from pathlib import Path
import ast, datetime, hashlib, json, re

ROOT=Path(__file__).resolve().parents[4]
HERE=Path(__file__).resolve().parent
RUNS=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
START_RUN=39585884968
ALLOWED={'propext','Classical.choice','Quot.sound'}

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def rel(p):return str(p.relative_to(ROOT)).replace('\\','/')

def main():
 rows=[]
 for sf in sorted(RUNS.glob('[0-9]*/download-*/summary.json')):
  run=int(sf.parent.parent.name)
  if run<START_RUN:continue
  s=json.loads(sf.read_text(encoding='utf8'))
  for declared in s.get('results',[]):
   name=declared['candidate']
   if not name.startswith('f01-d1-'):continue
   vf=sf.parent/declared['verdict']
   if not vf.exists():continue
   v=json.loads(vf.read_text(encoding='utf8'))
   inp=sf.parent/'inputs'/name/'Kernel.lean'
   if not inp.exists():continue
   digest=sha(inp)
   assert digest==declared['kernel_sha256'],(run,name,'input digest mismatch')
   lf=sf.parent/(name+'-gate.log')
   log=lf.read_text(encoding='utf8') if lf.exists() else ''
   matches=re.findall(r'\[axioms\]\s+(\[[^\n]*?\])',log)
   axioms=ast.literal_eval(matches[-1]) if matches else None
   full=bool(declared.get('full_gate'))
   if full:
    assert v['passed'] and v['mode']=='gate' and v['stage']=='score'
    assert len(v['classes'])==12 and len(v['rounds'])==25
    assert axioms is not None and set(axioms)<=ALLOWED
    assert 'Submission replays cleanly' in log and 'VerifyFull replays cleanly' in log
    ratio=sum(c['submission_ns'] for c in v['classes'].values())/sum(c['incumbent_ns'] for c in v['classes'].values())
    assert abs(ratio-v['ratio'])<1e-10
   operations={}
   for op in ['add','mul','sum','bmm']:
    cc=[c for k,c in v.get('classes',{}).items() if k.startswith(op+':')]
    if cc:
     operations[op]={'ratio_vs_shipped':sum(c['submission_ns'] for c in cc)/sum(c['incumbent_ns'] for c in cc),
       'mean_class_candidate_ns_per_scalar_step':sum(c['submission_ns'] for c in cc)/len(cc)}
   artifacts=[p for p in [inp,vf,lf] if p.exists()]
   row={'run':run,'candidate':name,'kernel_sha256':digest,'kernel_bytes':inp.stat().st_size,
    'source_commit':s.get('source_commit'),'official_commit':s.get('official_commit'),
    'validation_mode':declared.get('validation_mode'),'stage':v.get('stage'),'passed':v.get('passed'),
    'full_gate':full,'reason':v.get('reason'),'allowed_axiom_audit':axioms,
    'ratio_vs_shipped':v.get('ratio'),'rounds':len(v.get('rounds',[])),
    'operations':operations,'seed':declared.get('seed'),'wall_seconds':declared.get('wall_seconds'),
    'champion_direct_ratio':'UNKNOWN',
    'artifacts':[{'path':rel(p),'sha256':sha(p),'bytes':p.stat().st_size} for p in artifacts]}
   rows.append(row)
 result={'audited_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
  'scope':'Independent receipt/hash audit of D collected runs. Does not rerun Lean or benchmarks. Full official runs and statement-only diagnostics remain distinct.',
  'window_start_utc':'2026-10-21T10:32:09Z','window_end_utc':'2026-10-21T11:32:09Z',
  'rows':rows}
 (HERE/'window-audit.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
 print(json.dumps({'audited_at_utc':result['audited_at_utc'],'rows':len(rows),
  'results':[{'candidate':r['candidate'],'run':r['run'],'full_gate':r['full_gate'],'stage':r['stage'],'passed':r['passed'],'ratio_vs_shipped':r['ratio_vs_shipped'],'operations':r['operations']} for r in rows]},indent=2))

if __name__=='__main__':main()
