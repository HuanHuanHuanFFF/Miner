"""Measure the actual combination of two independently byte-checked SF representations."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
def main():
    p=ROOT/'candidates/r24-609-inline-slot';r,l=[(p/f).read_text()for f in ('parse.rs','Parse.lean')]
    h=importlib.import_module('build-round24-pricegroups').HELPER
    assert 'pub fn SFprice_bend(' not in r
    a=r.index('pub fn SFsolve(');b=r.index('pub fn SFpatch(',a);part=r[a:b];assert part.count('Z330(&mut bend)')==1;part=part.replace('Z330(&mut bend)','SFprice_bend(ct,&mut bend)');r=r[:a]+h+part+r[b:]
    a=r.index('pub fn SFheavy(');b=r.index('pub fn SFweak(',a);part=r[a:b];assert part.count('Z330(&mut bend)')==1;part=part.replace('Z330(&mut bend)','SFprice_bend(&ct,&mut bend)');r=r[:a]+part+r[b:]
    np=(ROOT/'candidates/r24-609-price-groups/Parse.lean').read_text();a=np.index('@[local step]\ntheorem SFprice_bend_loop_spec');b=np.index('@[local step]\ntheorem SFsolve',a);proof=np[a:b];at=l.index('theorem SFsolve');at=l.rfind('@[local step]',0,at);l=l[:at]+proof+l[at:]
    e=w.write_candidate('r24-609-slot-groups',p.name,r,l,
        'Actual combination of direct single-match slots and equal-price SF query intervals, preserving both mechanisms and the original cost/search model. New combined bytes, timing and proof must be verified.',
        'N reduced observed long-query group counts17.5percent; O removed common-case item indirection and kept28filetokens/output. These are component observations, not additive speed estimates. This combination is screened together with both components.',
        {'parent':p.name,'group_component':'candidates/r24-609-price-groups/manifest.json','original_source':'references/round24-public-609/source-receipt.json','proof':'Combined producer/consumer helper proof is stillDRAFT; exactpairfullgate notinherited.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'seedtail-d-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]
    for name,path in [('groups','candidates/r24-609-price-groups'),('slots','candidates/r24-609-inline-slot')]:
        c=w.control(name,path,'609');c.pop('formal_id');c['anchor']='public609';s['entries'].append(c)
    s['entries'].append(e);s.update(native_encoder_references=['public609','once','groups','slots'],description='R24 Q exact component combination, native28-file parity versusonce and both components. These are quality/equivalence observations only; three-way actual total-time comparison follows.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]];(E/'combo-q-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'N and O show real work/layout changes and original public token equality, but their interaction and total-time effect are unmeasured.',
        'change':'Compose the actual two code changes without changing search or cost values; retain both component baselines.',
        'minimum':'Full28file original native encoding/token/decode equality for the combinedRust alongside both components; then controlledN/O/Q original-time screen.',
        'decision':'Any parity failure prevents presumed composition. If parity holds, measure allthree; do not add component gains. Proof/extraction must bind combinedpair separately.',
        'cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/combo-q-native/diagnostics'};(E/'preflight-q.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode());print(e['name'])
if __name__=='__main__':main()
