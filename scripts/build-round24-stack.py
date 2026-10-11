"""Combine only measured positive mechanisms; retain a distinct quality variant."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
def main():
    parent=ROOT/'candidates/r24-609-root-prune';r=(parent/'parse.rs').read_text();lean=(parent/'Parse.lean').read_text()
    # Apply the same firstword reuse to retained fallbacks and specialized trees.
    for name in ['Z162','Z189','Aroot162','Aroot189']:
        old=fn(r,name);part=old;needle='Z153(s, cr - 1, pos, 0)';assert part.count(needle)==(0 if name.startswith('Aroot') else 1)
        part=part.replace(needle,'Afirstword(s, cr - 1, pos, 0, q)');needle='Z153(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len })';assert part.count(needle)==1;part=part.replace(needle,'Afirstword(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len }, q)');r=r.replace(old,part)
    at=r.index('pub fn Z162(');r=r[:at]+importlib.import_module('build-round24-word-reuse').HELPER+r[at:]
    for name in ['SFsolve','SFheavy']:
        old=fn(r,name);assert old.count('Z330(&mut bend)')==1;part=old.replace('Z330(&mut bend)','SFprice_bend('+('ct'if name=='SFsolve'else'&ct')+',&mut bend)');r=r.replace(old,part)
    at=r.index('pub fn SFsolve(');r=r[:at]+importlib.import_module('build-round24-pricegroups').HELPER+r[at:]
    inline=json.loads((ROOT/'candidates/r24-609-route-inline/manifest.json').read_bytes())['attribution']['changed_wrappers']
    for n in inline:
        needle='pub fn '+n+'(';assert r.count(needle)==1;r=r.replace(needle,'#[inline(always)]\n'+needle)
    components=['r24-609-root-prune','r24-609-word-reuse','r24-609-price-groups','r24-609-route-inline'];entries=[]
    e=w.write_candidate('r24-609-root-word-price',parent.name,r,lean,'Compose conditionallyunused tree-state removal, cachedqueryword, equalactualprice groups and17smallrouteinline wrappers. Keep full32bit children after their measured regression.','Only individually measured positive mechanisms are composed; overlap, code layout and cache effects can erase gains, so actualcombinednative/time/gate confirmation is required.',{'components':components,'time_evidence':['evidence/round24/analysis-ai.json','evidence/round24/analysis-xy.json','evidence/round24/analysis-noq-lm.json'],'proof':'DRAFT: changed queryword loop argument plus root/N interfaces require fresh extraction and fullgate.'});e.update(anchor='public609',comparison_baseline='root-prune',native_decode_reference='root-prune',expected_equivalent_to='root-prune');entries.append(e)
    high=(ROOT/'candidates/r24-609-buffer-split-proof1/parse.rs').read_text();old=fn(r,'SFfastadd');new=fn(high,'SFfastadd');assert r.count(old)==1;r=r.replace(old,new)
    at=r.index('pub fn SFfastadd(');attr=r.rfind('#[inline(always)]',0,at);assert r[attr:at].strip()=='#[inline(always)]';r=r[:attr]+'#[inline(always)]\n'+fn(high,'SFroom')+'\n'+r[attr:]
    for call in ['SFfastadd(&mut best,&mut codes,count,ot)','SFfastadd(&mut best,&mut codes,count,SFmt(d,l))']:
        assert r.count(call)==1;r=r.replace(call,call[:-1]+',ct)')
    e=w.write_candidate('r24-609-root-word-price-buffer',entries[0]['name'],r,lean,'Add the actuallygated L dominated-slot replacement to the measured-positive mechanism composition, preserving its firstreplaceable-slot policy.','Behaviorallydistinctquality variant, not a renamed copy. PriorL proof/score cannot be inherited by this new Rust/Lean pair; nativequality and originaltotal-time are measured anew.',{'components':components+['r24-609-buffer-split-proof1'],'quality_evidence':'evidence/round24/analysis-z-v2.json','proof':'DRAFT until actualnewextraction/migration and completeoriginalgate.'});e.update(anchor='public609',comparison_baseline=entries[0]['name'],native_decode_reference='buffer-original',expected_equivalent_to='buffer-original');entries.append(e)
    s=json.loads((E/'child-ad-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']]
    for alias,path in [('root-prune','candidates/r24-609-root-prune'),('buffer-original','candidates/r24-609-buffer-split-proof1')]:
        x=w.control(alias,path,'609');x.pop('formal_id');x['anchor']='public609';s['entries'].append(x)
    s['entries']+=entries;s.update(r24_expected_candidates=2,native_encoder_references=['public609','root-prune','buffer-original'],description='AK twoactualcompositions afterpositivecomponenttiming: commonquality version and Lquality variant. Native6programencoder/decode first. No compactchildren, no cachedmatch/Uregression, no assumedadded speed.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('compose-ak-native',s),('preflight-ak',{'gap':'Eachpositivecomponent is onlyabout1-1.5percent; stable10/15need substantially more improvement. Need realcomposition effect and a differentquality point before furtherselection.','change':'Compose N/Y/AE/AC, then add actualLpolicy as secondvariant. Exclude measurednegativechild16 andmatchcache.','minimum':'Original28fileencoder/decode for bothactualcompositions and exactAE/Lparents; token equality hypotheses checked before originaltime.','decision':'Parity earns same-run total-time with AJ32bit solver as a separate candidate; failedparity diagnosesinteraction. No sums of component speed/share and no inheritedgate.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/compose-ak-native/diagnostics','proof_status':'DRAFT'})]:
        p=E/(name+'.json');assert not p.exists();p.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print([e['name']for e in entries])
if __name__=='__main__':main()
