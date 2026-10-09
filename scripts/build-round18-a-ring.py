"""Bound the A planner's backward-cost working storage to its 258-byte horizon."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-selective-rf';rust=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text()
    a=rust.index('pub fn a_store_choice(');b=rust.index('/// Follows the planned path',a);part=rust[a:b]
    old='if i < cost.len() { cost[i] = value; }';assert part.count(old)==1;part=part.replace(old,'if (i & 511) < cost.len() { cost[i & 511] = value; }')
    old='let cl = cost.len();';assert part.count(old)==1;part=part.replace(old,'let cl = s.len().saturating_add(1);')
    old='if pe < cl && pe < mp.len() && pe <= s.len() && pe <= ch.len() {';assert part.count(old)==1;part=part.replace(old,'if cost.len() == 512 && pe < cl && pe < mp.len() && pe <= s.len() && pe <= ch.len() {')
    for old,new,count in [('cost[z]','cost[z & 511]',1),('cost[i + 1]','cost[(i + 1) & 511]',1),('cost[stop]','cost[stop & 511]',1),('cost[at]','cost[at & 511]',2)]:
        assert part.count(old)==count,(old,part.count(old));part=part.replace(old,new)
    rust=rust[:a]+part+rust[b:]
    a=rust.index('pub fn a_engine(');b=rust.index('// ───────────────────────────── engine C',a);part=rust[a:b]
    for old,new in [('let mut cost: Vec<u32> = Vec::with_capacity(n + 1);','let mut cost: Vec<u32> = Vec::with_capacity(512);'),('while i <= n {','while i < 512 {'),('cost.len() == n + 1','cost.len() == 512')]:
        assert part.count(old)==1,old;part=part.replace(old,new)
    rust=rust[:a]+part+rust[b:]
    e=m.write_candidate('r18-586-a-ring',p.name,rust,proof,
      'Represent A backward dynamic-program costs by a512-cell rolling vector, retaining the original logical input bound, endpoint resets, match offers and tie rules. A pass only reads the next258 positions; full positional choices remain unchanged.',
      'Z profiling places0.893s inclusive in A DP, separate from RF. The old vector is input-sized and zeroed once per parse though only a bounded future window is live. This tests working-set and initialization reduction; the added index masks may offset it. No prior A-cost-ring experiment was found in task methods/build scripts; prior contiguous-ring negative concerned forward relax layout.',
      {'parent':'references/round18-public-586/source-receipt.json','evidence':'evidence/round18/37982889694','ownership':'Original public586 authors retained; bounded cost-storage transformation is this research.'})
    e.update(anchor='public586',comparison_baseline='selective586',native_decode_reference='selective586',expected_equivalent_to='selective586')
    s=json.loads((ROOT/'evidence/round18/rank-ac-native.json').read_bytes());s['entries']=[x for x in s['entries']if x.get('control')]+[e];s['screen_orders']=[[x['name']for x in s['entries']],[x['name']for x in reversed(s['entries'])]];s['r18_a_ring_check']=e['name']
    s['description']='AI minimal A-cost-ring check: preserve logical window and all decisions while reducing storage from input+1 to512. Original encoder28files versus selective;2400 direct actualRust A-DP calls with varying valid match-record layouts, short/tail/wrap lengths, offsets and packed costs. Compare full positional choices and live suffix costs. Cap25job-minutes. Any difference blocks equivalence. Only after finite checks run original total-time; Lean invariants must be adapted and exact fullgate rerun.'
    (ROOT/'evidence/round18/aring-ai-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
