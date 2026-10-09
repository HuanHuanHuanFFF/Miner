"""Split long RF ring updates into two contiguous spans, preserving every update."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]
HELPER='''
pub fn r18_rf_relax(ring: &mut [u64;512], prices: &[u32;1024],
    p: usize, maxlen: usize, base: u64, choice: u32, lo: usize) {
    let stop = if maxlen < 258 { maxlen } else { 258 };
    if lo > stop { return; }
    let mut l = lo;
    let mut at = p.wrapping_add(l) & 511;
    let remaining = stop - l + 1;
    let space = 512 - at;
    let take = if remaining < space { remaining } else { space };
    let first_end = l + take;
    while l < first_end {
        let v = base.wrapping_add(prices[256+l] as u64);
        if v < ring[at] >> 32 { ring[at] = (v << 32) | choice as u64 | l as u64; }
        l += 1;
        at += 1;
    }
    at = 0;
    while l <= stop {
        let v = base.wrapping_add(prices[256+l] as u64);
        if v < ring[at] >> 32 { ring[at] = (v << 32) | choice as u64 | l as u64; }
        l += 1;
        at += 1;
    }
}
'''

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-selective-rf';rust=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text()
    needle='            rf_dp_relax(&mut ring, &prices, p, maxlen, base, choice, lo);';assert rust.count(needle)==1
    rust=rust.replace(needle,needle.replace('rf_dp_relax','r18_rf_relax'))+HELPER
    e=m.write_candidate('r18-586-rf-span',p.name,rust,proof,
        'Split the RFforward relaxation at the512-slot wrap into at mosttwo contiguousloops. Preserve every length, unsignedwrapped price, strict comparison and tokenchoice. Keeporiginalhelper alongside newone for direct differential checks.',
        'ActualselectiveRF has130964766length updates butonly2482532sortingcomparisons. Do notoptimize sorting. R7contiguousforwardD lostperformance; thisrevisits a differentRFworkload with22.58relaxedterms perposition and noalgorithmchange. Exactnative differential andtotal-time evidence required.',json.loads((p/'manifest.json').read_bytes())['attribution'])
    e.update(anchor='public586',comparison_baseline='selective586',expected_equivalent_to='selective586',native_decode_reference='selective586')
    s=json.loads((ROOT/'evidence/round18/refine-s-native.json').read_bytes());s['entries']=[x for x in s['entries']if x.get('control')and x['name']!='base586']
    control=m.control('selective586','candidates/r18-586-selective-rf','586');control.pop('formal_id');control['anchor']='public586';s['entries'] += [control,e]
    s.update(native_encoder_references=['public586','selective586'],r18_rf_span_equiv=e['name'],description='Wnative: actualRFworkload dominatedbylength updates, notbucketsorting. Oneexactcontiguous-span representation; requireall28tokens/outputequalparent plus6000directRust helpercases with512wrap,Usizeextremes,wrappedU64costs andties. Cap20job-minutes. Cost-model/opcount isnotperformance; onlyifallchecks pass allocatepairedtotal time. Newhelperproofpending.')
    s['screen_orders']=[[x['name']for x in s['entries']],[x['name']for x in reversed(s['entries'])]];(ROOT/'evidence/round18/span-w-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(e))

if __name__=='__main__':main()
