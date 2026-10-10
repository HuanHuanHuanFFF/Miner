"""Freeze a fresh accepted-pair confirmation or a separate noise diagnosis."""
from pathlib import Path
import argparse,copy,json
ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round22'

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('candidate')
    ap.add_argument('--label',required=True)
    ap.add_argument('--mode',choices=['confirmation','diagnostic'],required=True)
    ap.add_argument('--blocks',type=int,default=2)
    a=ap.parse_args();assert 1<=a.blocks<=4
    s=json.loads((E/'screen-c.json').read_bytes())
    all_entries={e['name']:e for label in ('screen-c','screen-e') for e in json.loads((E/(label+'.json')).read_bytes())['entries']}
    assert a.candidate in all_entries and not all_entries[a.candidate].get('control')
    selected=all_entries[a.candidate]
    s['entries']=[copy.deepcopy(all_entries[n]) for n in ('probe3','r3-432-fast3','public432','public595','public595-shadow')]+[copy.deepcopy(selected)]
    s['r22_expected_candidates']=1
    s['screen_blocks']=a.blocks
    if a.mode=='confirmation':
        cert=json.loads((ROOT/selected['path']/'VERIFICATION.json').read_bytes())
        assert cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED' and cert['files']==selected['hashes']
        s.update(r22_mode='standard',r22_role='independent_confirmation',r18_role='independent_confirmation',r22_dispatch_after_gate_pair_known=True)
        s['description']='R22 fresh frozen accepted-pair original confirmation; discovery measurements excluded from independent statistics. Separate official595 and same-source shadow, original paired incumbent total timings and perfile receipts.'
    else:
        assert a.label.endswith('-diagnostic')
        s['entries'].append({**copy.deepcopy(selected),'name':a.candidate+'-shadow','control':True})
        s.update(r22_mode='diagnostic',r18_mode='diagnostic',r18_order_diagnostic=True,r18_order_blocks=a.blocks,r18_order_protocols=['original_fixed11','balanced20'],diagnostic_methods=['public595','public595-shadow',a.candidate,a.candidate+'-shadow'],isolated_blocks=2,multimethod_blocks=4)
        s['description']='R22 measurement diagnosis only: two exact595 aliases and two exactcandidate aliases share binary hashes. Compare original fixed11 and scratch balanced20 schedules on explicit CPU; preserve all methods/input/output/source/environment hashes. Exclude diagnostic axes from official-protocol projections.'
    names=[e['name'] for e in s['entries']]
    s['screen_orders']=[names if i%2==0 else names[::-1] for i in range(a.blocks)]
    dest=E/(a.label+'.json');assert not dest.exists()
    dest.write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'candidate':a.candidate,'files':selected['hashes'],'mode':a.mode,'gap':'Fresh source/control paired measurements must distinguish a real near-boundary gain from control disagreement. Discovery high shares alone do not establish stability or formal reward.','substantial_change':'New independent runner and declared block ordering, exact unchanged Rust/Lean bytes; diagnostic order schedules remain separate from original acceptance protocol.','minimum':s['description'],'decision':'Record each block/runner/control separately, target10pct counts and actual ranges; allocate final gate repair only if results warrant and collection remains within fixed deadline. Never add independent forecasts as joint share.','cost_cap_minutes':18,'evidence':'evidence/round22/<run>/'+a.label}
    (E/('preflight-'+a.label+'.json')).write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print('FROZEN',a.label,a.candidate,a.mode,a.blocks)

if __name__=='__main__':main()
