"""Freeze equal-repetition ordering controls for the actual high-potential pair."""
from pathlib import Path
import copy,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round23'

def main():
    s=json.loads((ROOT/'evidence/round22/screen-k.json').read_bytes())
    candidate=next(e for e in s['entries'] if not e.get('control'))
    assert candidate['name']=='r22-595-chain-halfhead'
    controls=[e for e in s['entries'] if e['name'] in ('probe3','r3-432-fast3','public432','public595','public595-shadow')]
    s['entries']=controls+[candidate,{**copy.deepcopy(candidate),'name':candidate['name']+'-shadow','control':True}]
    for k in list(s):
        if k.startswith('r22_'):del s[k]
    s.update(snapshot_pages='evidence/round23/official-start/pareto-pages.json',r23_mode='diagnostic',r23_expected_candidates=1,r18_mode='diagnostic',r18_order_diagnostic=True,r18_order_blocks=2,r18_order_protocols=['original_fixed11','original_fixed20','balanced20'],diagnostic_methods=['public595','public595-shadow',candidate['name'],candidate['name']+'-shadow'],isolated_blocks=2,multimethod_blocks=4,description='R23 B exactsame595/combination aliases with originalfixed11,fixed20,balanced20. Two reversed blocks, equal20repetitioncomparison identifies ordering separately from repcount; diagnostic only, not original isolated officialperformance or gate.')
    names=[e['name'] for e in s['entries']];s['screen_orders']=[names,names[::-1]]
    p=E/'order-b-diagnostic.json';assert not p.exists();p.write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'R22combination has one16.67/16.35percentblock and onezero. Earlierdifferentcandidate diagnostic changed11to20reps withorder, so order-only attributionremainedunknown.','substantial_change':'Actualfrozencombination pair, equal20repcontrol andtwo reverseprotocol blocks onone newrunner. Preserve isolatedoriginal resultsseparately.','minimum':'Fourhash-bound aliases, complete28file rawmedians for fixed11,fixed20,balanced20, explicitCPU, unchangedcodec/token/loader, libraryidentitychecked.','decision':'Ifmatched20order reducescontrolgap andchangescandidatecomparison, supportsaprotocol-specific effect withoutclaiming formalperformance. Ifdisagreementpersists, retainunknownmeasurementcause andprioritize largerrealquality/speed margin.','cost_cap_minutes':20,'evidence':'evidence/round23/<run>/order-b-diagnostic/diagnostics','full_gate_of_candidate':'Separate gate-combo run','final_confirmation':'Fresh accepted-pair original isolatedtimings required.'}
    (E/'preflight-b.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print('FROZEN_MATCHED_DIAGNOSTIC',candidate['hashes'])

if __name__=='__main__':main()
