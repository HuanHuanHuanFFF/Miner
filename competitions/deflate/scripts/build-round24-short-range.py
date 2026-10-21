"""Specialize short scalar reductions without changing the long-range algorithm."""
from pathlib import Path
import importlib,json,random
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start');fn=importlib.import_module('prepare-round24-extract-repro').fn
def main():
    p=ROOT/'candidates/r24-609-once';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();old=fn(r,'Z314')
    branch='''    if hi-start<3 {
        let mut best=(cost[i+start].wrapping_add(lc[start]).wrapping_add(base)<<9)|((start as u32)^511);
        if start<hi {
            let k=start+1;
            let c=(cost[i+k].wrapping_add(lc[k]).wrapping_add(base)<<9)|((k as u32)^511);
            best=if c<best {c}else{best};
        }
        if hi-start>=2 {
            let k=start+2;
            let c=(cost[i+k].wrapping_add(lc[k]).wrapping_add(base)<<9)|((k as u32)^511);
            best=if c<best {c}else{best};
        }
        return best;
    }
'''
    needle='    let mut l=start;';assert old.count(needle)==1;new=old.replace(needle,branch+needle);assert r.count(old)==1;r=r.replace(old,new)
    e=w.write_candidate('r24-609-short-range',p.name,r,l,'Directly evaluate one to three length offers in the A reduction kernel; preserve packed cost wrap/tie ordering and the original scalar loop for wider ranges.','Current Z314 is already inline(always), so this targets loop control rather than an inlining guess. Its body matches the historical mean-span3.54 engine. Earlier RMQ/block caches paid maintenance on mostly short queries; no persistent data structure is introduced.',{'parent':p.name,'old_distribution':'evidence/round18/ranges-c-decision.json','same_core':'evidence/round24/revisit-core-comparison.json','proof':'Inherited proof is DRAFT for the changed exact body; fresh extraction and original gate still required.'})
    e.update(anchor='public609',comparison_baseline='once',native_decode_reference='once',expected_equivalent_to='once')
    s=json.loads((E/'groups-n-native.json').read_bytes());s.pop('r24_group_counts');s['entries']=[x for x in s['entries']if x['control']]+[e];s.update(description='W short scalar range specialization, actual28-file native parity first. Long ranges and all match/cost decisions unchanged. Historical counts prioritize but do not predict speed.')
    ns=[x['name']for x in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    rng=random.Random(242323);cases=0
    for span in [1,2,3,4,8,32,128,258]:
        for _ in range(2000):
            lo=rng.randrange(0,512-span);hi=lo+span-1;width=rng.choice([0,1,2,3,5,258]);start=hi-width+1 if width>=1 and hi-lo>=width else lo
            vals=[rng.getrandbits(32)for _ in range(512)];prices=[rng.getrandbits(32)for _ in range(512)];base=rng.getrandbits(32)
            def term(k):return (((vals[k]+prices[k]+base)&0xffffffff)<<9&0xffffffff)|(k^511)
            expected=min(term(k)for k in range(start,hi+1))
            if hi-start<3:
                got=term(start)
                if start<hi:got=min(got,term(start+1))
                if hi-start>=2:got=min(got,term(start+2))
            else:got=min(term(k)for k in range(start,hi+1))
            assert got==expected;cases+=1
    for name,d in [('short-w-native',s),('preflight-w',{'gap':'A dynamic programming remains material; heavy caches were unattractive for its short reductions. No claim that branch specialization will beat compiler output.','change':'At most3offers evaluated directly; wider ranges use unchanged loop. No cost model/search/route change.','minimum':'16000 finite packed-cost wrap/tie/width checks and actual28-file original encoder/decode equivalence.','decision':'Parity earns one controlled original total-time screen; identical quality alone is not speed evidence. Regression or immaterial timing stops this exact fast path.','model_checks':cases,'model_scope':'Finite arithmetic reduction model, not universal Rust equivalence or Lean proof.','cost_cap_runner_minutes':15,'evidence':'evidence/round24/<run>/short-w-native/diagnostics','proof_status':'DRAFT'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['name'],cases)
if __name__=='__main__':main()
