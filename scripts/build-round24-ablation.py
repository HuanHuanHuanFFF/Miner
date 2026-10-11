"""Bound the actual value of SF on the newly captured609 base, before new routing."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
def main():
    p=ROOT/'candidates/r24-609-once';r,l=[(p/f).read_text() for f in ('parse.rs','Parse.lean')]
    old='pub fn parse(input:&[u8],out:&mut[u32])->usize{Zmain(input,out)}';assert r.count(old)==1
    e=w.write_candidate('r24-609-base-ablation',p.name,r.replace(old,'pub fn parse(input:&[u8],out:&mut[u32])->usize{SFbase(input,out)}'),l,
        'Diagnostic ablation: return the existing base parser output before the entire SF correction stage. No new content/length router is introduced.',
        'The newly public609base has distinct base allocation and corrections. Its actual per-file marginal SF output was not yet established; older603/nooverlap conclusions cannot substitute for this source. This is an opportunity measurement, not a promised final candidate.',
        {'parent':p.name,'source':'references/round24-public-609/source-receipt.json','priority_model':'evidence/round24/weighted-stage-priority.json','earlier_different_parent':'docs/rounds/round19.md'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once')
    s=json.loads((E/'seedtail-d-native.json').read_bytes());s['entries']=[x for x in s['entries'] if x['control']]+[e]
    s.update(description='R24 K diagnostic SF ablation on exact609base: actual per-file marginal quality of each enabled path. No new route, no timing claim, no full-proof claim.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (E/'ablation-k-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Weighted-stage priority roughly places substantial cost in SF. Need actual quality loss/gain on this exactbase before deciding which structure or eligibility signal merits implementation.',
        'change':'Remove the entire correction only for a diagnostic parser, retaining baseexactly; compare whole outputs on28publicfiles.',
        'minimum':'Original encoder and independentdecode, per-file token/output differences against frozenonce609.',
        'decision':'If benefits concentrate in identifiable structural cases, investigate a cheap general eligibility condition and retain the remaining quality work. If SF is broadly necessary, optimize its mechanism instead. No file-identity oracle is a candidate or private-performance guarantee.',
        'cost_cap_runner_minutes':12,'proof':'Inherited top-level proof is deliberately a draft for this ablation; no gate is inherited. Finalimplementation requires its own complete gate.',
        'evidence':'evidence/round24/<run>/ablation-k-native/diagnostics'}
    (E/'preflight-k.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e['name'])
if __name__=='__main__':main()
