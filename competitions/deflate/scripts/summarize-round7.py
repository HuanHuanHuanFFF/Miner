"""Reconcile completed middle experiments against one fixed official snapshot."""
from pathlib import Path
import argparse
import hashlib
import json
import statistics
from round3 import load_scorer

ROOT=Path(__file__).resolve().parents[1]
RUNS=[('37636716596','middle-a'),('37636990183','middle-cpu'),
      ('37641161339','middle-block'),('37642665812','middle-seed')]

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--snapshot',type=Path,required=True)
    args=ap.parse_args()
    pages=json.loads(args.snapshot.read_text())
    rows=[r for p in pages for r in p['items']]
    formal=next(r['metrics'] for r in rows if r['id']=='361')
    front=[r for r in rows if (r.get('score') or {}).get('on_frontier')]
    sc=load_scorer(ROOT/'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py')
    bounds=sc.Boundaries(10,40)
    points=[sc.Point(r['id'],r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct']) for r in front]
    ws=sc.local_global_improvement_space_log_weights(sc.pareto_front(points),bounds)
    replay_error=max(abs(ws[r['id']]-r['score']['pareto_weight']) for r in front)
    assert replay_error<1e-10
    def geometry(x,y):
        dominators=[v.name for v in points if v.time_s<=x and v.ratio_pct<=y]
        ok=x<=10 and y<=40 and not dominators
        w=sc.local_global_improvement_space_log_weights(sc.pareto_front(points+[sc.Point('hypothetical',x,y)]),bounds)
        return {'time_ratio':x,'compressed_pct':y,'on_geometric_frontier':ok,
            'conditional_share_pct':w.get('hypothetical',0)*100 if ok else 0,'dominating_ids':dominators}
    grouped={};runs=[];processes=0;checks=[]
    for rid,batch in RUNS:
        p=ROOT/'evidence/round7'/rid/batch/'gate'
        ci=json.loads((p/'ci-run.json').read_text());state=json.loads((p/'state.json').read_text())
        assert ci['status']=='completed' and ci['conclusion']=='success'
        assert state['run_id']==rid and state['git_sha']==ci['headSha'] and not state['failures']
        by={(m['candidate'],m['round']):m for m in state['metrics']}
        processes+=len(by)
        runs.append({'run_id':rid,'batch':batch,'commit':ci['headSha'],'conclusion':ci['conclusion'],
            'public_paired_processes':len(by),'url':ci['url']})
        for e in state['spec']['entries']:
            name=e['name']
            if not name.startswith('r7-mid361-'):continue
            assert hashlib.sha256((ROOT/e['path']/'parse.rs').read_bytes()).hexdigest()==e['hashes']['parse.rs']
            assert hashlib.sha256((ROOT/e['path']/'Parse.lean').read_bytes()).hexdigest()==e['hashes']['Parse.lean']
            blocks=sorted(b for n,b in by if n==name)
            assert len(blocks)>=2
            relative=[by[name,b]['time']/by['public361',b]['time'] for b in blocks]
            size=by[name,blocks[0]]['size_pct'];base_size=by['public361',blocks[0]]['size_pct']
            assert all(by[name,b]['size_pct']==size for b in blocks)
            g=grouped.setdefault(name,{'candidate':name,'files':e['hashes'],'public_size_pct':size,'runs':[],'gates':[]})
            assert g['public_size_pct']==size and g['files']==e['hashes']
            g['runs'].append({'run_id':rid,'blocks':blocks,'public_time':statistics.mean(by[name,b]['time'] for b in blocks),
                'relative_times':relative,'relative_time_change_pct':100*(statistics.mean(relative)-1),
                'projected_size_pct':formal['mean_file_compression_pct']*size/base_size})
            gate=state['gates'].get(name)
            if gate:
                for f,h in e['hashes'].items():
                    assert hashlib.sha256((p/('input-'+name)/f).read_bytes()).hexdigest()==h
                g['gates'].append({'run_id':rid,'accepted':gate.get('accepted',False)})
        eq=p/'equivalence-research.json'
        if eq.exists():
            for c in json.loads(eq.read_text()).get('cases',[]):checks.append({'run_id':rid,**c})
    candidates=[]
    for g in grouped.values():
        rr=g['runs'];x=formal['balanced_time_ratio']*statistics.mean(statistics.mean(r['relative_times']) for r in rr)
        y=rr[0]['projected_size_pct'];assert all(abs(r['projected_size_pct']-y)<1e-12 for r in rr)
        worst_x=formal['balanced_time_ratio']*max(t for r in rr for t in r['relative_times'])*1.02
        g.update(independent_jobs=len(rr),public_blocks=sum(len(r['blocks']) for r in rr),
            public_time=statistics.mean(r['public_time'] for r in rr),
            same_family_projection=geometry(x,y),
            conservative_projection=geometry(worst_x,max(y+0.01,g['public_size_pct']*1.008)),
            full_public_gate_passed=any(v['accepted'] for v in g['gates']))
        candidates.append(g)
    candidates.sort(key=lambda g:(-g['conservative_projection']['conditional_share_pct'],
        -g['same_family_projection']['conditional_share_pct'],g['public_size_pct']))
    result={'status':'COMPLETE_PUBLIC_EXPERIMENT_ROUND','snapshot':pages[0]['context'],
        'scorer_replay_max_error':replay_error,'formal_anchor':{'submission_id':'361','metrics':formal},
        'completed_ci_runs':runs,'candidate_count':len(candidates),'public_paired_processes':processes,
        'full_public_gates_passed':sum(g['full_public_gate_passed'] for g in candidates),
        'finite_equivalence_checks':checks,'candidates':candidates,
        'conservative_frontier_candidates':[g['candidate'] for g in candidates if g['conservative_projection']['on_geometric_frontier']],
        'limits':['Public measurements and proof results are VERIFIED; all formal projections are INFERRED.',
            'Conservative scenario is a declared stress test, not a statistical confidence interval.',
            'No round7 candidate has been submitted to the competition; private stage2, admission and rewards UNKNOWN.'],
        'new_formal_submissions':0,'new_chain_transactions':0}
    dest=ROOT/'evidence/round7/final-summary.json';dest.write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'candidate_count':len(candidates),'processes':processes,'full_gates':result['full_public_gates_passed'],
        'frontier':result['conservative_frontier_candidates'],'candidates':[{'name':g['candidate'],'public_time':g['public_time'],'public_size':g['public_size_pct'],'jobs':g['independent_jobs'],'blocks':g['public_blocks'],'projection':g['same_family_projection'],'conservative_share_pct':g['conservative_projection']['conditional_share_pct'],'gate':g['full_public_gate_passed']} for g in candidates]}))

if __name__=='__main__':main()
