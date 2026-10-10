"""Skip RF transitions dominated by the preceding position's first envelope."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]
HELPERS=r'''
// Previous-position dominance: prices are unchanged within one block.
// A previous first bucket offered all lengths 3..previous_max. At current
// length l<previous_max its offer reached the same destination with l+1.
// If its base was no higher and price[l]>=price[l+1], the current offer
// cannot beat the already-present state. Keep every price rise and tail.
pub fn r18_rf_cuts(prices: &[u32; 1024], cuts: &mut [u32; 512]) {
    let mut next = 258u32;
    cuts[258] = 258;
    let mut l = 258usize;
    while l > 3 && l <= 258 {
        l -= 1;
        if prices[(256+l) & 1023] < prices[(257+l) & 1023] { next = l as u32; }
        cuts[l & 511] = next;
    }
}

pub fn r18_rf_dominance(ring: &mut [u64; 512], prices: &[u32; 1024],
    cuts: &[u32; 512], p: usize, maxlen: usize, base: u64, choice: u32,
    lo: usize, previous_max: usize, previous_base: u64) {
    if lo >= 3 && lo <= 258 && previous_max > lo && previous_max <= 258
        && previous_base <= base {
        let mut l = cuts[lo & 511] as usize;
        while l < previous_max && l <= maxlen && l <= 258 {
            rf_dp_relax(ring, prices, p, l, base, choice, l);
            let next = cuts[l.wrapping_add(1) & 511] as usize;
            if next <= l { break; }
            l = next;
        }
        rf_dp_relax(ring, prices, p, maxlen, base, choice, previous_max);
    } else {
        rf_dp_relax(ring, prices, p, maxlen, base, choice, lo);
    }
}

'''

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-selective-rf';rust=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text();a=rust.index('pub fn rf_dp(');b=rust.index('pub fn refine(',a);part=rust[a:b]
    replacements={
      'let mut prices = [0u32; 1024];':'let mut prices = [0u32; 1024];\n    let mut cuts = [258u32; 512];\n    let mut previous_max = 0usize;\n    let mut previous_base = 0u64;',
      'q9_copy32(tab, 0, &mut prices, 0, 545);':'q9_copy32(tab, 0, &mut prices, 0, 545);\n    r18_rf_cuts(&prices, &mut cuts);',
      'q9_copy32(tab, b.wrapping_mul(576), &mut prices, 0, 545);':'q9_copy32(tab, b.wrapping_mul(576), &mut prices, 0, 545);\n            r18_rf_cuts(&prices, &mut cuts);\n            previous_max = 0;',
      'let mut lo = 3usize;':'let mut current_max = 0usize;\n        let mut current_base = 0u64;\n        let mut lo = 3usize;',
      'rf_dp_relax(&mut ring, &prices, p, maxlen, base, choice, lo);':'r18_rf_dominance(&mut ring, &prices, &cuts, p, maxlen, base, choice, lo, previous_max, previous_base);\n            if t == 0 { current_max = maxlen; current_base = base; }',
      '        p += 1;':'        previous_max = current_max;\n        previous_base = current_base;\n        p += 1;'
    }
    for old,new in replacements.items():assert part.count(old)==1,old;part=part.replace(old,new)
    rust=rust[:a]+HELPERS+part+rust[b:]
    e=m.write_candidate('r18-586-rf-dominance',p.name,rust,proof,
      'Eliminate forward RF relaxations already dominated by the previous position first distance-cost envelope. Precompute actual price-rise boundaries, retain all uncovered tails and price rises, and clear the envelope on a block-model change. Search, prices, iteration budgets and tie handling are unchanged.',
      'V measured130.96million RF length updates. Failed span changed their access pattern without removing work. This version removes provably redundant offers under an explicit same-block envelope condition; actual token equivalence, speed and proof migration remain to be tested.',
      {'parent':'references/round18-public-586/source-receipt.json','research_evidence':'evidence/round18/rf-counts-v-decision.json','ownership':'Public586 algorithms and original attribution retained; new transition-dominance optimization is this research.'})
    e.update(anchor='public586',comparison_baseline='selective586',native_decode_reference='selective586',expected_equivalent_to='selective586')
    s=json.loads((ROOT/'evidence/round18/rank-ac-native.json').read_bytes());s['entries']=[x for x in s['entries']if x.get('control')]+[e];s['screen_orders']=[[x['name']for x in s['entries']],[x['name']for x in reversed(s['entries'])]];s['r18_rf_dominance_check']=e['name']
    s['description']='AE minimal mechanism check: previous-position dominance removes RF work rather than changing loop layout. Original encoder28files versus frozen selective parent; actual Rust helper differential on20000 invariant-satisfying randomized envelope/ring/price cases; count eliminated offers with wholeparse token/decode check. Cap25job-minutes. Any mismatch blocks equivalence claim. Only a material removed-work signal justifies original total-time screening; new helper/loop proofs and exact fullgate remain required.'
    (ROOT/'evidence/round18/dominance-ae-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
