"""Read the adopted frozen model; never modify estimates, gates or dashboard."""
from datetime import datetime,timezone
import hashlib,json,statistics
from pathlib import Path

HERE=Path(__file__).resolve().parent
MODEL=HERE.parent/'champion-time-estimate.json'
SOURCE='6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d'

def derive(model):
    assert model['kernel_sha256']==SOURCE and model['status']=='INFERRED'
    samples=model['samples'];assert len(samples)==6
    def scenario(bmm_speedup,other_cost_factor):
        values=[]
        for sample in samples:
            c=sample['candidate_total_ns'];ch=sum(sample['champion_projected_total_ns'].values())
            values.append((c['bmm']/bmm_speedup+sum(c[k] for k in ('add','mul','sum'))*other_cost_factor)/ch)
        return {'bmm_speedup':bmm_speedup,'other_three_remaining_cost_factor':other_cost_factor,
                'whole_champion_relative_median':statistics.median(values),'all_six_projections':values}
    current=scenario(1,1)
    assert abs(current['whole_champion_relative_median']-model['whole']['ratio_median'])<1e-12
    scenarios=[scenario(b,o) for b,o in ((1,1),(1.5,1),(2,1),(3,1),(4,1),(2,.9),(2,.8),(2,.75),(3,.85),(4,.85))]
    zero=[sum(s['candidate_total_ns'][k] for k in ('add','mul','sum'))/sum(s['champion_projected_total_ns'].values()) for s in samples]
    # Largest remaining non-BMM cost factor compatible with the planning target.
    lo,hi=0.,1.
    for _ in range(60):
        mid=(lo+hi)/2
        if scenario(2,mid)['whole_champion_relative_median']<=.97:lo=mid
        else:hi=mid
    shares={op:statistics.median(s['candidate_total_ns'][op]/sum(s['candidate_total_ns'].values()) for s in samples) for op in ('add','mul','sum','bmm')}
    return {'scope':'INFERRED planning sensitivity on all six original frozen workloads. No new measurement or candidate; component speedups are hypothetical, not success probabilities or performance promises.',
            'source_sha256':SOURCE,'champion':model['champion_submission'],'champion_digest':model['champion_digest'],
            'anchor_sha256':model['anchor_sha256'],'estimator_sha256':model['estimator_sha256'],
            'model_sha256':hashlib.sha256(MODEL.read_bytes()).hexdigest(),
            'model_path':MODEL.relative_to(HERE.parents[4]).as_posix(),
            'modeled_time_share_medians':shares,'scenarios':scenarios,
            'bmm_zero_cost_limit':{'whole_median':statistics.median(zero),'all_six_projections':zero},
            'with_bmm_twofold_to_reach_0_97':{'other_three_remaining_cost_factor_max':lo,'required_uniform_other_three_cost_reduction':1-lo},
            'engineering_costs':'UNKNOWN; use this only to screen opportunity, then compare concrete proof/implementation/verification costs.',
            'decision':'GeneralPanel4 and removal of actual redundant guards remain BMM structural priorities. Reserve a bounded scalar investigation because BMM-only2x does not close the current whole gap; do not expand the failed normal-band or dynamic-max grids.'}

if __name__=='__main__':
    result=derive(json.loads(MODEL.read_bytes()));result['recorded_at_utc']=datetime.now(timezone.utc).isoformat()
    destination=HERE/'next-investment-sensitivity.json'
    with destination.open('x',encoding='utf-8',newline='\n') as output:output.write(json.dumps(result,ensure_ascii=False,indent=2)+'\n')
    print(json.dumps({'scenarios':[{k:v for k,v in s.items() if k!='all_six_projections'} for s in result['scenarios']],
                      'zero_limit':result['bmm_zero_cost_limit']['whole_median'],
                      'required_other_reduction':result['with_bmm_twofold_to_reach_0_97']['required_uniform_other_three_cost_reduction']}))
