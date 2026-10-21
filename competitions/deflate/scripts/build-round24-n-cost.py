"""One controlled transfer of DNA match economics to the actual595 N engine."""
from pathlib import Path
import importlib,json,re
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
HELPER='''#[inline(always)]
pub fn n_worth(l:usize,d:usize)->bool {
 let mut c=168u32;
 if l>10 && l<258 {c=c.wrapping_add(16u32.wrapping_mul(29u32.wrapping_sub(((l-3)as u32).leading_zeros())));}
 if d>4 {c=c.wrapping_add(16u32.wrapping_mul(30u32.wrapping_sub(((d-1)as u32).leading_zeros())));}
 (l as u32).wrapping_mul(40)>c
}

'''
def main():
    p=ROOT/'candidates/r22-595-chain-halfhead';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    calls=re.findall(r'n_run::<[^\n]+',r);assert len(calls)==1 and '65536,6,0,0,0,16,0,8,1' in calls[0]
    a=r.index('pub fn n_eval(');b=r.index('pub fn n_choose<',a);part=r[a:b]
    needle='if l>=3 {l|(p.wrapping_sub(a)<<9)} else {0}';assert part.count(needle)==1;part=part.replace(needle,'if l>=3 && n_worth(l,p.wrapping_sub(a)) {l|(p.wrapping_sub(a)<<9)} else {0}')
    attr=r.rfind('#[inline(always)]',0,a);assert r[attr:a].strip()=='#[inline(always)]'
    r=r[:attr]+HELPER+r[attr:a]+part+r[b:]
    e=w.write_candidate('r24-595-n-cost40',p.name,r,l,'Transfer the previously explicit2.5bit literal-cost criterion into actual595 N-match admission. Reject a suggested match whose fixedlength/distance model costs at least40/16bits per covered literal. Preserve the one N route, hash/search/insertion policy, checked emitter and all other families.','R18 PC-based DNA cost40 saved9932B but increasedtokens and slowed about1percent, yieldingzero. R20 N radix6 transfer worsenedbytes; this changes match economics, not that failed hash. Current595 N matcher and inheritedchain-halfhead base differ from PC582. One bounded transfer, not a costparameter sweep.',{'parent':p.name,'source':'references/round21-public-595/source-receipt.json','prior_cost_negative':'evidence/round18/dna-av-decision.json','prior_N_representation_negative':'docs/rounds/round20.md','proof':'DRAFT: n_worth totality and changed exact N admission need original extraction/fullgate.'})
    e.update(anchor='public595',comparison_baseline='combo',native_decode_reference='combo')
    s=json.loads((E/'gain-a-native.json').read_bytes());s['entries']=[x for x in s['entries']if x['control']and x['name']!='chain3']+[e]
    s.update(r24_expected_candidates=1,native_encoder_references=['public595','combo'],description='AB one DNA economic admission transfer on actual595Nengine, with oldPCnegative evidence retained. Original28fileencoder/decode; inspect tokeninflation before any total-time spend.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('ncost-ab-native',s),('preflight-ab',{'gap':'Fast family remains the alternate reward position but former peaks were unstable. ExistingDNA cost filtering has a realbyte/extra-token tradeoff on a different PC engine; currentN transfer is unmeasured.','change':'Use40/16=2.5literalbits and168/16base plus actual length/distance extra-bit model only in the soleNengine route. No hash or iteration sweep.','minimum':'Actual28file original bytes/tokens/decode, named595andactualcombo parents; confirm other files unchanged and calculate current opportunity before timing.','decision':'If tokeninflation and actualquality do not offer a plausible new reward position, stop. If useful, actualoriginal paired time must decide; no private guarantee or highsharefrompriorPCresult.','cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/ncost-ab-native/diagnostics','model_units':{'literal':40,'units_per_bit':16,'base':168},'proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'])
if __name__=='__main__':main()
