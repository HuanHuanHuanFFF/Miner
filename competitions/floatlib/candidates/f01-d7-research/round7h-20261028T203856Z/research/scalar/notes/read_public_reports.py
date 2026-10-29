"""Summarize already-retrieved public reports. No API calls, CI or benchmark."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,math,statistics
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
S=R/'competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z/competition-state-check'

def geo(values):
    den=sum(w for _,w in values)
    return math.exp(sum(math.log(v)*w for v,w in values)/den)

def score(measure,weights,predicate=lambda _:True):
    values=[]
    for w in measure['workloads']:
        scores=[]
        for rnd in measure['rounds']:
            ratios=[]
            for key,v in rnd['cells'].items():
                workload,cell=key.split('|',1)
                if workload==w['id'] and predicate(cell):
                    assert v['reference_checksum']==v['candidate_checksum']
                    ratios.append((v['candidate_ns']/v['reference_ns'],weights[cell]))
            assert ratios
            scores.append(geo(ratios))
        values.append((statistics.median(scores),w['weight']))
    return geo(values)

def main():
    receipts=json.loads((S/'torchlean-report-readonly-receipts.json').read_bytes());reports=[]
    for ident in ['2','5']:
        p=S/f'torchlean-report-{ident}.raw';raw=p.read_bytes();digest=hashlib.sha256(raw).hexdigest()
        assert digest==receipts[ident]['sha256'] and receipts[ident]['http_status']==200
        report=json.loads(raw);item={'submission':int(ident),'source_sha256':report['submission']['source_sha256'],
          'report_path':p.relative_to(R).as_posix(),'report_sha256':digest,'fetched_at_utc':receipts[ident]['at_utc'],
          'official_board_decisions':[{'board':e['board'],'reference_hash':e['reference_hash'],'reference_promotion_id':e['reference_promotion_id'],'decision':e['decision']} for e in report['evaluations']]}
        e=next(e for e in report['evaluations'] if e['board']=='overall');weights=e['cells'];families=sorted({x.split(':')[0] for x in weights});kind=['normal','wide','sparse'];rows=[]
        for m in e['measurements']:
            recomputed=score(m,weights);assert math.isclose(recomputed,m['score'],rel_tol=1e-12,abs_tol=1e-12),(ident,m['environment'],recomputed,m['score'])
            rows.append({'environment':m['environment'],'seed':m['seed'],'rounds':len(m['rounds']),'reported_score':m['score'],'recomputed_score':recomputed,
                         'derived_family_projections':{f:score(m,weights,lambda c,f=f:c.startswith(f+':')) for f in families},
                         'derived_kind_projections':{k:score(m,weights,lambda c,k=k:c.endswith(':'+k)) for k in kind},
                         'workloads':m['workloads']})
        combined=geo([(r['recomputed_score'],0.5) for r in rows]);assert math.isclose(combined,e['decision']['score'],rel_tol=1e-12,abs_tol=1e-12)
        item.update(overall_reference_hash=e['reference_hash'],overall_score_recomputed=combined,environment_rows=rows,
                    derived_two_environment_family_projections={f:geo([(r['derived_family_projections'][f],0.5) for r in rows]) for f in families},
                    derived_two_environment_kind_projections={k:geo([(r['derived_kind_projections'][k],0.5) for r in rows]) for k in kind})
        reports.append(item)
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'PUBLIC_REPORT_HASH_AND_SCORE_RECOMPUTATION_PASS',
         'scope':'Historical official complete-model measurements, not current rankings or layer profiles. Projections reweight subsets of the overall evaluation; they are not the separate family-board evaluations. Raw CPU nanoseconds are never pooled.',
         'read_only':True,'network_calls':0,'new_benchmarks':0,'layer_timing':'UNKNOWN_NOT_PRESENT',
         'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'reports':reports}
    (D/'public-report-analysis.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
    print(json.dumps([{'submission':r['submission'],'score':r['overall_score_recomputed'],'family_projections':r['derived_two_environment_family_projections'],'kind_projections':r['derived_two_environment_kind_projections']} for r in reports]))
if __name__=='__main__':main()
