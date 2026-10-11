"""Reuse verified equal-distance match prefixes across increasing SF positions."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
HELPER='''#[inline(always)]
pub fn SFcachedmatch(input:&[u8],a:usize,b:usize,cap:usize,known:usize,cache:&mut[u64;256])->usize {
 let d=b.wrapping_sub(a);let slot=d%256;let v=cache[slot];let end=(v as u32)as usize;
 let safe=b<=2147483000 && d>0 && d<=32768;
 let hint=if safe && (v>>32)==d as u64 && end>b {Z248(cap,end.wrapping_sub(b))}else{0};
 let l=SFmatchlen(input,a,b,cap,Z457(known,hint));
 if safe {cache[slot]=((d as u64)<<32)|(b.wrapping_add(l)as u64);}
 l
}

'''
def transform(r):
    for name,nextname in [('SFsmallmatches','SFpriced'),('SFmorematches','SFheavy')]:
        a=r.index('pub fn '+name+'(');b=r.index('pub fn '+nextname+'(',a);s=r[a:b]
        assert s.count('let mut p=a;')==1;s=s.replace('let mut p=a;','let mut cache=[0u64;256];let mut p=a;')
        old='SFmatchlen(input,j,p,cap,known)';assert s.count(old)==1;s=s.replace(old,'SFcachedmatch(input,j,p,cap,known,&mut cache)');r=r[:a]+s+r[b:]
    at=r.index('pub fn SFsmallmatches(');return r[:at]+HELPER+r[at:]
def main():
    p=ROOT/'candidates/r24-609-once';r=transform((p/'parse.rs').read_text());l=(p/'Parse.lean').read_text()
    e=w.write_candidate('r24-609-match-cache',p.name,r,l,'Cache the end of a previously verified match at the same distance. Because each SF collector visits increasing positions, its overlap is already known; extend only the remaining suffix with the original matcher. A256-slot direct map stores distance and end, with fallback on misses and bounds.','R19 transferred base-engine candidate prefixes across stages and added large cache plumbing; this cache is local to each SF collector and reuses exact prior SF comparisons. It never replaces the search or changes candidate admission. Extra read/write cost is measured.',{'parent':p.name,'related':'docs/rounds/round19.md','proof':'DRAFT: new bounded helper and loop cache state need actual extraction. General correctness still enforced by original final emission; finite equivalence does not establish all-input equivalence.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s.update(r24_match_cache_counts=True,description='U local equal-distance verified prefix reuse. Count actual skipped prefix opportunity and verify all28original token/output/decode results before paired timing.')
    s['entries']=[x for x in s['entries']if x['control']]+[e];ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('match-u-native',s),('preflight-u',{'gap':'SF matching is a significant observed cost; same-distance matches at adjacent positions may reread the same long equal region. Seed-tail checks slowed previously, so work saved must be observed before timing.','change':'Small collector-local endpoint cache with exact-distance tag, monotone positions and original matcher fallback. No new search or corpus routing.','minimum':'Untimed counts of calls, useful cache-prefix hits and extra known bytes; observed tokens/decode plus actual original encoder equality on28files.','decision':'If prefix hits are substantial and actual outputs equal, one total-time screen. If opportunity tiny or maintenance erases savings, stop this exact version. No inference from hit ratio alone.','cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/match-u-native/diagnostics','proof_status':'DRAFT'})]:
        path=E/(name+'.json');assert not path.exists();path.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'])
if __name__=='__main__':main()
