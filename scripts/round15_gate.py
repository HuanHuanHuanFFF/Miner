"""Optional fresh-confirmation allocation for a competition-pool share target."""
import statistics

def share_confirmation_gates(state,names,pages,scorer):
    policy=state['spec'].get('confirmation_share_gate_policy')
    if not policy:return names,[]
    assert state['spec']['screen_blocks']==4 and state['spec']['refine_blocks']==0
    target=float(policy['minimum_pool_fraction']);assert 0<target<=1 and policy['minimum_passing_blocks']==3
    entries={e['name']:e for e in state['spec']['entries']};parent=policy['parent'];shadow=policy['shadow']
    assert entries[parent]['control'] and entries[shadow]['control']and entries[parent]['hashes']==entries[shadow]['hashes']
    rows=[r for p in pages for r in p['items']];reference=next(r for r in rows if r['id']==entries[parent]['formal_id'])
    metrics=reference['metrics'];bounds=reference['bounds'];max_time=bounds['max_balanced_time_ratio'];max_size=bounds['max_mean_file_compression_pct']
    frontier=[r for r in rows if(r.get('score')or{}).get('on_frontier')];points=[scorer.Point(r['id'],r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])for r in frontier]
    weights=scorer.local_global_improvement_space_log_weights(points)
    assert max(abs(weights[r['id']]-r['score']['pareto_weight'])for r in frontier)<1e-10,'Published current geometry must replay exactly'
    by={(m['candidate'],m['round']):m for m in state['metrics']};selected=[];decisions=[]
    def geometry(x,y):
        if not (0<x<=max_time and 0<y<=max_size):return 0.0
        front=scorer.pareto_front(points+[scorer.Point('__r15_candidate__',x,y)])
        return scorer.local_global_improvement_space_log_weights(front).get('__r15_candidate__',0.0)
    for name in names:
        assert entries[name]['anchor']==parent and not entries[name]['control']
        y=metrics['mean_file_compression_pct']*by[name,1]['size_pct']/by[parent,1]['size_pct'];calibrations={}
        for anchor in(parent,shadow):
            xs=[metrics['balanced_time_ratio']*by[name,b]['time']/by[anchor,b]['time']for b in range(1,5)]
            ss=[geometry(x,y)for x in xs];center=geometry(statistics.mean(xs),y)
            calibrations[anchor]={'block_time_coordinates':xs,'block_pool_fractions':ss,'center_time_coordinate':statistics.mean(xs),'center_pool_fraction':center,'blocks_at_least_target':sum(v>=target for v in ss)}
        checks={anchor+'_center_at_least_target':v['center_pool_fraction']>=target for anchor,v in calibrations.items()}
        checks.update({anchor+'_three_blocks_at_least_target':v['blocks_at_least_target']>=3 for anchor,v in calibrations.items()})
        permit=all(checks.values())
        if permit:selected.append(name)
        decisions.append({'candidate':name,'run_id':state['run_id'],'minimum_pool_fraction':target,'calibrations':calibrations,'projected_size_pct':y,'checks':checks,'full_gate_allocated':permit,'scope':'Four fresh blocks only, both original anchor and identical-source shadow transfer. Allows real speed/size tradeoffs; does not require faster-than-parent when compression improves. Conditional geometry is not private admission or actual payment.'})
    return selected,decisions
