"""Reuse the already loaded query word at zero-prefix tree comparisons."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
HELPER='''#[inline(always)]
pub fn Afirstword(s:&[u8],p:usize,q:usize,k:usize,word:u64)->(usize,usize) {
 if k==0 {
  let other=Z164(s,p);
  if other!=word {return (((other^word).leading_zeros()/8)as usize,if other<word{1}else{0});}
  Z153(s,p,q,8)
 }else{Z153(s,p,q,k)}
}

'''
def main():
    p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    for n in ['Z162','Z189']:
        old=fn(r,n);s=old
        needle='Z153(s, cr - 1, pos, 0)';assert s.count(needle)==1;s=s.replace(needle,'Afirstword(s, cr - 1, pos, 0, q)')
        needle='Z153(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len })';assert s.count(needle)==1;s=s.replace(needle,'Afirstword(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len }, q)')
        assert r.count(old)==1;r=r.replace(old,s)
    at=r.index('pub fn Z162(');r=r[:at]+HELPER+r[at:]
    e=w.write_candidate('r24-609-word-reuse',p.name,r,l,'At tree comparisons with zero known prefix, use the query first word already supplied in pre. Compare only the candidate word; if equal continue original comparison from8. Nonzero-prefix comparisons use the original function.','R longkey6 lost quality by changing search neighborhoods. This preserves hash/search/insert policies and uses an existing value; no key change, speculative prefetch or search-depth adjustment. An extra branch may still cost more than the saved load.',{'parent':p.name,'profile':'evidence/round24/weighted-stage-priority.json','proof':'DRAFT: new helper bounded result and queryword argument in extracted tree loops need migration; actual complete gate still required.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(r24_word_reuse_counts=True,description='Y reuse already available query firstword in A tree comparisons at knownprefix0. Count actual trigger and confirm original28filetoken/output/decode before timing.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    for name,d in [('word-y-native',s),('preflight-y',{'gap':'A tree matching remains a material observed cost. Longkey changes lost quality; retaining the tree while reusing a supplied query word may avoid duplicate work.','change':'Only zero-prefix comparison firstword reuse; original continuation, lexical tie and search order.','minimum':'Untimed calls/zero-prefix/firstword-mismatch counts on token-equivalent observer, plus actual28-file original encoder/decode equality.','decision':'Substantial applicablecalls with actual parity earns one original total-time screen. Counts/assembly are diagnostic only; lack of time margin or parity failure stops or diagnoses.','cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/word-y-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'])
if __name__=='__main__':main()
