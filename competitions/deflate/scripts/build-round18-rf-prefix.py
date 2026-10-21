"""Reuse the proven prefix of the previous RF position's longest match."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]
HELPER=r'''
// The immediately previous position's carried match proves a shifted prefix
// for the same distance. Only compare its extension; final emit still checks
// every selected match. Hints never alter chain traversal or offered lengths.
pub fn r18_rf_mlen(input: &[u8], a: usize, b: usize, cap: usize, previous: u32) -> usize {
    let n = input.len();
    if a > n || b > n || cap > n-a || cap > n-b { return 0; }
    let len = (previous & 511) as usize;
    let dist = ((previous >> 9) & 65535) as usize;
    let known = if len >= 4 && dist > 0 && a <= b && b-a == dist {
        if len-1 < cap { len-1 } else { cap }
    } else { 0 };
    known + mlen(input, a+known, b+known, cap-known)
}

'''

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-selective-rf';rust=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text();a=rust.index('pub fn rf_find(');b=rust.index('pub fn rf_dp_relax(',a);part=rust[a:b]
    for old,new in [('    while p < n {','    while p < n {\n        let previous_match = carry;'),('mlen(input, q, p, cap)','r18_rf_mlen(input, q, p, cap, previous_match)'),('mlen(input,q,p,cap)','r18_rf_mlen(input,q,p,cap,previous_match)')]:
        assert part.count(old)==1,old;part=part.replace(old,new)
    rust=rust[:a]+HELPER+part+rust[b:]
    e=m.write_candidate('r18-586-rf-prefix',p.name,rust,proof,
      'When a chain candidate has the same distance as the preceding position carried match, start byte comparison after its proven shifted prefix. Preserve both chains, insertion order, search depth, every offered match, all RF models, and final checked emission.',
      'Q profiling isolated1.045s in full586RF finder, distinct from DP relaxation. The prior longest match already certifies an overlapping prefix; repeated full comparisons waste work. This candidate tests exact reusable match information, not a shallower search or changed compression heuristic.',
      {'parent':'references/round18-public-586/source-receipt.json','evidence':'evidence/round18/refine-q-decision.json','ownership':'Original public586 authors retained. Shifted-prefix reuse is the research delta.'})
    e.update(anchor='public586',comparison_baseline='selective586',native_decode_reference='selective586',expected_equivalent_to='selective586')
    s=json.loads((ROOT/'evidence/round18/rank-ac-native.json').read_bytes());s['entries']=[x for x in s['entries']if x.get('control')]+[e];s['screen_orders']=[[x['name']for x in s['entries']],[x['name']for x in reversed(s['entries'])]];s['r18_rf_prefix_check']=e['name']
    s['description']='AF minimal RF finder mechanism check, independent of AE DP optimization: reuse same-distance previous-position prefix while retaining exact chain search and offers. Original encoder28files versus selective;20000 actualRust helper cases with explicitly valid preceding matches plus tail/overlap/invalid-range cases; wholeparse token equality and saved-prefix counts. Cap25job-minutes. A mismatch blocks equivalence; a material hit/saved-byte signal leads to original total time, not direct promotion. New proof and fullgate needed.'
    (ROOT/'evidence/round18/prefix-af-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
