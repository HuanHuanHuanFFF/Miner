"""Freeze equal-count order diagnosis for observed609 calibration disagreement."""
from pathlib import Path
import copy,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def main():
    s=json.loads((E/'screen-b.json').read_bytes());candidate=next(e for e in s['entries'] if not e['control'])
    s['entries']=[e for e in s['entries'] if e['name'] in ('probe3','r3-432-fast3','public432','public609','public609-shadow')]+[candidate,{**copy.deepcopy(candidate),'name':candidate['name']+'-shadow','control':True}]
    s.update(r24_mode='diagnostic',r24_expected_candidates=1,r18_mode='diagnostic',r18_order_diagnostic=True,r18_order_blocks=2,r18_order_protocols=['original_fixed20','balanced20'],diagnostic_methods=['public609','public609-shadow',candidate['name'],candidate['name']+'-shadow'],isolated_blocks=2,multimethod_blocks=4,description='R24 J equal20-repeat fixed versus balanced ordering for the actual609/once pair. Two reversed blocks, CPU and code identity retained. Isolated original11-repeat observations remain separate; diagnostic scores cannot replace them.')
    ns=[e['name']for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    p=E/'order-j-diagnostic.json';assert not p.exists();p.write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Once609 has four original blocks; primary0-2.9794percent with3zeros, shadow0-2.9799with2zeros at29611. Same-source reference change can flip whether it enters frontier, although both target10and15remain unmet.',
        'change':'Discriminate order effects at equal20 repetitions on actualslow-quality family; earlier fastfamily diagnostics do not establish this pair. Both source aliases must compile to identical corresponding libraries.',
        'minimum':'Two reversed fixed20/balanced20 blocks on a fresh runner, explicit CPU binding, full per-file raw times, original encoder/token/loader and source hashes; no change to actual submitted candidate.',
        'decision':'If balanced ordering narrows alias gaps, retain measured protocol-specific evidence and continue original independent confirmation only for credible candidates. If gaps persist, keep causes unresolved and prioritize larger real improvements. No diagnostic measurement promotes a target.',
        'cost_cap_runner_minutes':55,'evidence':'evidence/round24/<run>/order-j-diagnostic/diagnostics/r18-order','original_protocol':'Unchanged original isolated1warmup11reps receipts B/D remain scored separately.'}
    (E/'preflight-j.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print('J_FROZEN_EQUAL_REPEAT_ORDER_DIAGNOSTIC')
if __name__=='__main__':main()
