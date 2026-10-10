"""Separate observed same-source timing drift and paired normalization drift."""
from pathlib import Path
import argparse,json,statistics as st
ROOT=Path(__file__).resolve().parents[1]

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('folder',type=Path)
    ap.add_argument('--output',type=Path,required=True)
    a=ap.parse_args();folder=a.folder.resolve()
    state=json.loads((folder/'state.json').read_bytes());entries={e['name']:e for e in state['spec']['entries']}
    assert entries['public595']['hashes']==entries['public595-shadow']['hashes']
    result={'status':'VERIFIED_OBSERVED_TIMING_DECOMPOSITION_DIAGNOSTIC_ONLY','run_id':state['run_id'],'source_pair':entries['public595']['hashes'],'blocks':[],'scope':'Actual perfile measured medians and their fixed-reference diagnostic recombination. Counterfactual normalization is not a new official performance protocol, formal coordinate or additional sample.'}
    for block in range(1,state['spec']['screen_blocks']+1):
        files={}
        for name in ('public595','public595-shadow'):
            rows=[json.loads(s) for s in (folder/f'round{block}-{name}.jsonl').read_text().splitlines()]
            files[name]={f['file']:f for f in rows if f['kind']=='file'}
        names=sorted(files['public595']);assert len(names)==28 and set(names)==set(files['public595-shadow'])
        per=[]
        def med(m):
            reps=[r['total_s'] for r in m['reps'] if r['phase']=='measured'];assert len(reps)==11
            return st.median(reps)
        for f in names:
            p,s=files['public595'][f],files['public595-shadow'][f]
            assert p['sha256']==s['sha256']
            pc,sc=p['methods']['public595'],s['methods']['public595-shadow']
            assert (pc['output_sha256'],pc['tokens_sha256'])==(sc['output_sha256'],sc['tokens_sha256'])
            pt,si=med(pc),med(s['methods']['incumbent'])
            pi,ss=med(p['methods']['incumbent']),med(sc)
            per.append({'file':f,'primary_candidate_total_s':pt,'shadow_candidate_total_s':ss,'primary_incumbent_total_s':pi,'shadow_incumbent_total_s':si,'primary_axis':pt/pi,'shadow_official_axis':ss/si,'shadow_fixed_primary_incumbent_axis_DIAGNOSTIC':ss/pi,'axis_gap_contribution':(ss/si-pt/pi)/28,'candidate_total_delta_pct':100*(ss/pt-1),'incumbent_total_delta_pct':100*(si/pi-1)})
        paxis=st.mean(r['primary_axis'] for r in per)
        saxis=st.mean(r['shadow_official_axis'] for r in per)
        fixed=st.mean(r['shadow_fixed_primary_incumbent_axis_DIAGNOSTIC'] for r in per)
        result['blocks'].append({'block':block,'primary_axis':paxis,'shadow_official_axis':saxis,'shadow_axis_delta_pct':100*(saxis/paxis-1),'fixed_primary_incumbent_candidate_delta_pct_DIAGNOSTIC':100*(fixed/paxis-1),'residual_normalization_delta_pp_DIAGNOSTIC':100*(saxis-fixed)/paxis,'raw_candidate_sum_delta_pct':100*(sum(r['shadow_candidate_total_s'] for r in per)/sum(r['primary_candidate_total_s'] for r in per)-1),'raw_incumbent_sum_delta_pct':100*(sum(r['shadow_incumbent_total_s'] for r in per)/sum(r['primary_incumbent_total_s'] for r in per)-1),'per_file':per,'largest_axis_contributors':sorted(per,key=lambda r:abs(r['axis_gap_contribution']),reverse=True)[:5]})
    a.output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps([{k:v for k,v in b.items() if k not in ('per_file','largest_axis_contributors')} for b in result['blocks']],indent=2))

if __name__=='__main__':main()
