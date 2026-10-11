"""Distinct quality route: remove overwritten pure parsing from public609."""
from pathlib import Path
import importlib, json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
w=importlib.import_module('build-round18-start')
def main():
    p=ROOT/'references/round24-public-609'
    r,l=[(p/f).read_text() for f in ('parse.rs','Parse.lean')]
    old='pub fn parse(input:&[u8],out:&mut[u32])->usize{let route=Z469(input);if ZREPEAT[route%32]!=0{Zmain(input,out);}Zmain(input,out)}'
    new='pub fn parse(input:&[u8],out:&mut[u32])->usize{Zmain(input,out)}'
    assert r.count(old)==1
    e=w.write_candidate('r24-609-once','public609',r.replace(old,new),l,
        'Call the complete inherited parser once: remove the first full parse whose token count is discarded and whose output is overwritten by the second full parse. Preserve all actual quality work and routing within Zmain.',
        'Newly released609 differs from607 by quality allocation and this redundant complete parse. This is removal of work, not intentional slowing or a parameter sweep. Output independence from prior out contents must be established, not assumed.',
        {'source':'references/round24-public-609/source-receipt.json','related_source':'references/round24-public-607/source-receipt.json','authorship':'Original public author code and proof retained; no ownership claim over the inherited optimizer.'})
    e.update(anchor='public609',comparison_baseline='public609',native_decode_reference='public609',expected_equivalent_to='public609')
    s=json.loads((E/'gain-a-native.json').read_bytes());s['entries']=[x for x in s['entries'] if x['name'] in ('probe3','r3-432-fast3','public432','public514')]
    s['entries'] += [w.control('public607','references/round24-public-607','607'),w.control('public609','references/round24-public-609','609')]
    shadow=dict(s['entries'][-1]);shadow['name']='public609-shadow';shadow.pop('formal_id');s['entries'].append(shadow);s['entries'].append(e)
    s.update(r24_expected_candidates=1,native_encoder_references=['public607','public609'],description='R24 B distinct high-quality region. One complete parse versus overwritten duplicate parse in exact public609. Full28-file original byte/token/decode screen before total timing; different original output buffer state is explicitly checked in later finite validation.')
    ns=[x['name'] for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    (E/'quality-b-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Fastfamily high-share window remains narrow; current quality-family frontier offers another location. Public607/609 only became readable after dominance.',
        'change':'Use exact609quality work once rather than twice, with unchanged inner parser. Read a second607public anchor to measure quality route differences.',
        'minimum':'All28files original encoder, independentdecode and token/output equality609 versus once; then finite input/output-state equivalence and original total time if equality holds.',
        'decision':'If identical, measure actual avoided work and per-block formal609 calibration; if differing, do not claim dead-work removal, diagnose out state before timing. Existing parameter/quality differences609versus607 stay separate.',
        'cost_cap_runner_minutes':12,'proof':'Existing609Lean is draft. Original parse theorem must be adapted/reproved for the single-call wrapper and separately full-gated.',
        'evidence':'evidence/round24/<run>/quality-b-native/diagnostics'}
    (E/'preflight-b.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e)
if __name__=='__main__':main()
