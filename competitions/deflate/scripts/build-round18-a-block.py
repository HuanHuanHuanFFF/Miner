"""One bounded hybrid A reduction experiment with eight-cell block extrema."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]
HELPERS=r'''
pub fn r18_a_price_ends(lc: &[u32;512], ends: &mut [u32;512]) {
    let mut end = 258u32;
    ends[258] = end;
    let mut l = 258usize;
    while l > 0 && l <= 258 {
        l -= 1;
        if lc[l & 511] != lc[l.wrapping_add(1) & 511] { end = l as u32; }
        ends[l & 511] = end;
    }
}

// Completed blocks remain ahead of the descending DP cursor. Only 258 future
// cells can be queried, so 64 tags cover every live eight-cell block.
pub fn r18_a_block_build(cost: &[u32], mins: &mut [u32;64], maxs: &mut [u32;64],
    positions: &mut [u32;64], at: usize) {
    let mut low = get0(cost,at);
    let mut high = low;
    let mut pos = at as u32;
    let mut j = 1usize;
    while j < 8 {
        let p = at.wrapping_add(j);
        let c = get0(cost,p);
        if c < low { low = c; pos = p as u32; }
        if c > high { high = c; }
        j += 1;
    }
    let b = (at >> 3) & 63;
    mins[b] = low;
    maxs[b] = high;
    positions[b] = pos;
}

#[inline(never)]
pub fn r18_a_block_best(cost: &[u32], lc: &[u32;512], ends: &[u32;512],
    mins: &[u32;64], maxs: &[u32;64], positions: &[u32;64],
    p: usize, lo: usize, hi: usize, base: u32) -> u32 {
    let mut best = 4294967295u32;
    let mut l = lo;
    while l <= hi && l <= 258 {
        let limit = ends[l & 511] as usize;
        let stop = if limit >= l && limit <= 258 {
            if limit < hi { limit } else { hi }
        } else { l };
        let price = lc[l & 511].wrapping_add(base);
        while l <= stop && l <= 258 {
            let at = p.wrapping_add(l);
            let b = (at >> 3) & 63;
            let low = mins[b];
            let high = maxs[b];
            let pos = positions[b] as usize;
            let minv = low.wrapping_add(price) & 8388607;
            let maxv = high.wrapping_add(price) & 8388607;
            // The endpoint check excludes a wrap in the 23-bit packed cost.
            // All other states use the original scalar offers.
            if (at & 7) == 0 && stop.wrapping_sub(l) >= 7 && l <= 251
                && high >= low && high.wrapping_sub(low) < 8388608 && minv <= maxv
                && pos >= at && pos <= at.wrapping_add(7) {
                let value = (minv << 9) | pos.wrapping_sub(p) as u32;
                if value < best { best = value; }
                l = l.wrapping_add(8);
            } else {
                let value = (get0(cost,at).wrapping_add(price) << 9) | l as u32;
                if value < best { best = value; }
                l = l.wrapping_add(1);
            }
        }
    }
    best
}

'''

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-selective-rf';original=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text();a=original.index('pub fn a_dp_pass(');b=original.index('/// Follows the planned path',a);part=original[a:b]
    old='    let cl = cost.len();';assert part.count(old)==1;part=part.replace(old,'''    let mut mins = [0u32;64];
    let mut maxs = [0u32;64];
    let mut positions = [0u32;64];
    let mut ends = [258u32;512];
    r18_a_price_ends(lc,&mut ends);
'''+old)
    old='            cost[z] = 0;';assert part.count(old)==1;part=part.replace(old,old+'\n            if (z & 7) == 7 { r18_a_block_build(cost,&mut mins,&mut maxs,&mut positions,z.wrapping_sub(7)); }')
    old='''                    let mut at = prev + 1;
                    let mut l = at.wrapping_sub(i) as u32;
                    while at <= stop {
                        let c = (cost[at].wrapping_add(lc[(l % 512) as usize]).wrapping_add(base) << 9) | l;
                        mbest = if c < mbest { c } else { mbest };
                        at += 1;
                        l = l.wrapping_add(1);
                    }'''
    assert part.count(old)==2
    new='''                    if stop.wrapping_sub(prev) >= 32 {
                        mbest = r18_a_block_best(cost,lc,&ends,&mins,&maxs,&positions,i,
                            prev.wrapping_add(1).wrapping_sub(i),stop.wrapping_sub(i),base);
                    } else {
'''+old+'''
                    }'''
    part=part.replace(old,new)
    old='            a_store_choice(cost, ch, i, best, bd, nxt);';assert part.count(old)==1;part=part.replace(old,old+'\n            if (i & 7) == 0 { r18_a_block_build(cost,&mut mins,&mut maxs,&mut positions,i); }')
    rust=original[:a]+part+original[b:];at=rust.rfind('#[inline(never)]',0,a);rust=rust[:at]+HELPERS+rust[at:]
    e=m.write_candidate('r18-586-a-block8',p.name,rust,proof,
      'Keep the original input-sized cost vector and original short-range loops. For ranges of at least32terms, split on actual constant length prices and query cached eight-cell cost extrema when packed-cost wrap checks permit. Sixty-four tagged blocks cover the live258-cell horizon. Rebuild extrema when a backward block completes; keep original scalar offers at boundaries and unsafe packed-cost intervals.',
      'AU measured808367027variable terms across75848577queries, mean10.66;16aligned blocks cover only15.06percent. This single8-cell hybrid tests lower alignment waste without the failed A-ring storage change. Long-query dispatch and cache-build overhead may outweigh savings. Exact helper/public behavior and totaltime must decide before proof migration.',
      {'parent':'references/round18-public-586/source-receipt.json','evidence':'evidence/round18/37995550516/aranges-au-native/diagnostics/r18-a-ranges/ranges.json','ownership':'Original A/RF authors retained; hybrid block-extrema reduction is this research delta.'})
    e.update(anchor='public586',comparison_baseline='selective586',native_decode_reference='selective586',expected_equivalent_to='selective586')
    s=json.loads((ROOT/'evidence/round18/aring-ai-native.json').read_bytes());s.pop('r18_a_ring_check');s['entries']=[x for x in s['entries']if x.get('control')]+[e];s['screen_orders']=[[x['name']for x in s['entries']],[x['name']for x in reversed(s['entries'])]];s['r18_a_block_check']=e['name'];s['description']='AW one bounded A block-extrema hybrid. Keep fullcostvector and scalarwidth<32; use8-cell block extrema only inconstant-price segments with explicit23-bit wrap checks. Native original28file encoder and2400actualA-DP differential cases, including flat/grouped/random lengthprices andfullU32wrap costs, cap25job-minutes. Any mismatch blocks exact-output claim. If equivalent, originalpairedtotal decides; source/proof still draft and new exactgate/freshconfirmation required.';(ROOT/'evidence/round18/block-aw-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
