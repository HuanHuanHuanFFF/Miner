"""Carry the fixed per-block distance price with retained SF match items."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
HELPER='''#[inline(always)]
pub fn SFpriceditem(t:u32,ct:&[u32;1024])->u32 {
 let c=ct[Z353(SFdist(t)).wrapping_add(512)%1024]>>4;
 (t&33554431)|((c&31)<<27)
}
#[inline(always)]
pub fn SFitemprice(t:u32)->u32 {(t>>27)<<4}
'''
def main():
    p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    for name,mod in [('SFsmallmatches',8),('SFmorematches',4)]:
        old=fn(r,name);needle=f'Z430(items,best[c%{mod}]);';assert old.count(needle)==1;r=r.replace(old,old.replace(needle,f'Z430(items,SFpriceditem(best[c%{mod}],ct));'))
    for name in ['SFsolve','SFseed','SFprefix']:
        old=fn(r,name);needle='let t=Z168(items,k);let l=SFlen(t);let d=SFdist(t);let dcs=(ct[Z353(d).wrapping_add(512)%1024] as u64)<<32;';assert old.count(needle)==1
        new=old.replace(needle,'let item=Z168(items,k);let t=item&33554431;let l=SFlen(t);let d=SFdist(t);let dcs=(SFitemprice(item) as u64)<<32;');r=r.replace(old,new)
    at=r.index('pub fn SFsmallmatches(');r=r[:at]+HELPER+'\n'+r[at:]
    e=w.write_candidate('r24-609-item-price',p.name,r,l,'Store the fixed SF distance cost in five unused high bits of each retained match item, in integer bits. Unpack the original token before length/distance use. The ordinary, seed and repeatedprefix solvers consume the storedprice instead of recomputing distancecode and loading its cost each time.','The SFtable producer uses16-unit prices andatmost15Huffman+13extra bits; the encoding carries0..31bit costs. This is immutable per-block edge metadata, not anotherlookupcache or changedprice objective. Actual runtime range and priceidentity are checked before timing.',{'parent':p.name,'query_count_evidence':'evidence/round24/38085691541/groups-n-native/diagnostics/r24-groups/receipt.json','proof':'DRAFT: newtotalhelpers and exactsolver/builder interfaces must pass originalgate; finite parity doesnotprove universalheuristic equivalence.'});e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(r24_item_price_counts=True,description='AS immutableperblock distanceprice inretainedSFitems, original28filetoken/output andactualeveryuse priceidentity/range checks. No size-speed prediction fromquery counts.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('item-as-native',s),('preflight-as',{'gap':'ActualSFsolver uses18.3Mmatchitems across ordinary/seed/prefix passes. Per-block ct isfixed during thosepasses but each use repeats distancecode andprice lookup.','change':'Five sparebits carry0..31bit distance cost; builder computes it once perretaineditem. Originaltoken low25bits preserved andunpackedbeforeall tokenfunctions.','minimum':'Actualeveryemission asserts ct divisibility/range andtokenbitbound; everyquery checks exact cachedversusoriginalprice; full28filetoken/encoder/decode parity.','decision':'Any price/range/token discrepancy stops this representation. Meaningful reuse andparity earns one originaltotal-time test; no impliedgain fromnumberofqueries.','cost_cap_runner_minutes':20,'evidence':'evidence/round24/<run>/item-as-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['hashes'])
if __name__=='__main__':main()
