"""Bounded local-only source-model coverage on three completed, already-exposed R14 draws.
References the preserved R14 Python translation; does not publish or copy that helper.
No R16 plan/results, Lean, benchmark, or final confirmation involved.
"""
from pathlib import Path
from datetime import datetime, timezone
from collections import defaultdict
import hashlib, json, runpy, subprocess, sys, time

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
GEN=ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-public-input-domain.py'
RUNS=(40129155932,40152158687,40155753018)
MAX_PAIRS=30000

def worker():
    start=time.perf_counter(); n=0; rows=[]
    g=runpy.run_path(str(GEN))
    element,partner,word=g['element'],g['partner'],g['word']
    for run in RUNS:
        root=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
        planpath=next(root.glob('download-*/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'))
        verdictpath=planpath.parent/'f01-d12-scalar-combined-verdict.json'
        workpath=planpath.parent/'public-cell-work.json'
        plan=json.loads(planpath.read_bytes()); verdict=json.loads(verdictpath.read_bytes()); work=json.loads(workpath.read_bytes())
        costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()}
        total=sum(costs.values()); groups=defaultdict(lambda:{'samples':0,'eligible':0,'zero_input':0,'special_input':0})
        for c in plan['cases']:
            if not c['timed'] or c['kernel']!='mul': continue
            group=':'.join(c['name'].split(':')[:2]); count=min(256,c['work'])
            for j in range(count):
                n+=1; assert n<=MAX_PAIRS and time.perf_counter()-start<4.5
                lo,hi=j*c['work']//count,(j+1)*c['work']//count
                i=lo+word(c['seed'],j,63)%(hi-lo)
                a=element(c,i,0,31); b=partner(c,i,a)
                ea,eb=(a>>23)&255,(b>>23)&255
                groups[group]['samples']+=1
                groups[group]['eligible']+=int(1<=ea<=254 and 1<=eb<=254 and 128<=ea+eb<=380)
                groups[group]['zero_input']+=int((a&0x7fffffff)==0 or (b&0x7fffffff)==0)
                groups[group]['special_input']+=int(ea==255 or eb==255)
        for k,v in groups.items():
            v['fraction']=v['eligible']/v['samples']
            v['old_df_cell_share_whole']=costs[k]/total
            v['count_weighted_cell_share_proxy']=v['fraction']*costs[k]/total
        rows.append({'run':run,'plan_sha256':hashlib.sha256(planpath.read_bytes()).hexdigest(),
          'groups':dict(groups),'old_df_mul_share_whole':sum(v for k,v in costs.items() if k.startswith('mul:'))/total,
          'count_weighted_whole_proxy':sum(v['count_weighted_cell_share_proxy'] for v in groups.values())})
    report={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'SOURCE_MODEL_ONLY_LOCAL_RESEARCH',
      'runs':rows,'pairs':n,'maximum_pairs':MAX_PAIRS,'external_timeout_seconds':5,'internal_seconds':4.5,
      'elapsed_seconds':time.perf_counter()-start,'generator_sha256':hashlib.sha256(GEN.read_bytes()).hexdigest(),
      'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
      'limits':'256 deterministic jittered strata per timed scalar MUL case; source translation not independently compared with Lean operands; counts are not cycles. Cell weighting uses old DF and assumes equal cost per pair solely as an opportunity proxy, not current B2 share, removable time, guarantee or admission evidence.'}
    print(json.dumps(report,indent=2))

if __name__=='__main__':
    if '--worker' in sys.argv: worker()
    else:
        t=time.perf_counter()
        result=subprocess.run([sys.executable,str(Path(__file__)),'--worker'],capture_output=True,text=True,timeout=5)
        (HERE/'exposed-coverage.stdout.txt').write_text(result.stdout,encoding='utf-8')
        (HERE/'exposed-coverage.stderr.txt').write_text(result.stderr,encoding='utf-8')
        if result.returncode: raise RuntimeError(result.stderr)
        report=json.loads(result.stdout); report['controller_elapsed_seconds']=time.perf_counter()-t
        (HERE/'exposed-coverage.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
        print(json.dumps({'pairs':report['pairs'],'seconds':report['controller_elapsed_seconds'],'runs':[
          {'run':r['run'],'mul_share':r['old_df_mul_share_whole'],'count_weighted_proxy':r['count_weighted_whole_proxy'],
            'groups':{k:v['fraction'] for k,v in r['groups'].items()}} for r in report['runs']]},indent=2))
