"""Spend bounded extra predecessor work only while all found matches stay short."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
def main():
    p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    for name in ['SFsmallmatches','SFmorematches']:
        old=fn(r,name);s=old
        needle='let mut k=0usize;';assert s.count(needle)==1
        s=s.replace(needle,'let mut k=0usize;let limit=depth.saturating_add(depth);let mut longest=if ot==0{0}else{SFlen(ot)};')
        needle='while k<depth&&q>0';assert s.count(needle)==1;s=s.replace(needle,'while k<limit&&(k<depth||longest<8)&&q>0')
        needle='let l=SFmatchlen(input,j,p,cap,known);';assert s.count(needle)==1;s=s.replace(needle,needle+'if l>longest{longest=l;}')
        assert r.count(old)==1;r=r.replace(old,s)
    e=w.write_candidate('r24-609-adaptive-search',p.name,r,l,'Extend each SF predecessor budget up to twice its original bound only while the longest seed or found match remains below8bytes. Reaching a longer match ends the extra-budget phase; original search, distance-code retention and final cost acceptance remain.','V larger storage recovered only22bytes. This tests missing short-match search opportunity instead of retaining more already-found candidates. Bounded work follows current matching evidence rather than input identity; no uniform depth sweep.',{'parent':p.name,'prior':'docs/research/optimization-methods.md','capacity_negative':'evidence/round24/38090058012/wide-v-native/diagnostics/r13-encoder/encoder.json','proof':'DRAFT: loop states and termination bound changed; exact extraction and original full gate required.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(description='X bounded adaptive extra search only for still-short matches. Native original quality/decode first; no uniform depth sweep or file-specific routing.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('adaptive-x-native',s),('preflight-x',{'gap':'N offers modest stable-looking discovery headroom; L/V quality shifts are too small for10/15. More retained slots did not expose much quality, so test missing candidates at weak-match positions.','change':'At most2xoldchainwork, only while no8-byte match exists. No other search or output changes.','minimum':'Actual28-file original encoder/decode, per-file quality and latest-frontier replay before expensive timing.','decision':'Useful observed quality displacement earns original total-time screen; negligible gain or endpoint reward collapse stops this version. Extra work cannot be assumed free.','cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/adaptive-x-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'])
if __name__=='__main__':main()
