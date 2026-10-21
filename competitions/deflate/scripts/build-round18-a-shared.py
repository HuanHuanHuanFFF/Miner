"""Test one shared A match cache feeding a lightweight seed and exact RF models."""
from pathlib import Path
import importlib.util,json

ROOT=Path(__file__).resolve().parents[1]
HELPER=r'''
// One A search supplies both the seed and the exact-model refitter. The old
// public engines and RF implementation remain below as attributable references.
pub fn r18_a_shared_plan(input: &[u8], ak: usize, rk: usize) -> Vec<u32> {
    let n = input.len();
    if n == 0 || n >= 16777216 { return Vec::new(); }
    let ac = CFG[ak % 16];
    let conf = RF_CONFIG[rk % 64];
    let mut mp = Vec::with_capacity(n+1);
    let mut mb = Vec::with_capacity(n*3+16);
    a_find_all(input, &mut mp, &mut mb, ac[1], ac[2]);
    let mut choice = zeros(n);
    let mut cost = zeros(n+1);
    let mut lit = [0u32;256];
    let mut lc = [0u32;512];
    let mut dc = [0u32;32];
    a_first_model(input, &mut lit, &mut lc, &mut dc);
    a_dp_pass(input, &mp, &mb, 0, n, &lit, &lc, &dc, &mut cost, &mut choice);
    let mut seed = zeros(n);
    let nseed = emit_pos(input, &choice, &mut seed);
    let mut cur = zeros(n);
    let mut i = 0usize;
    while i < nseed {
        let t = get0(&seed,i);
        let v = if t < 256 { 0 } else {
            let x = t.wrapping_sub(16777216);
            ((x & 255)+3) | ((x.wrapping_shr(8).wrapping_add(1)) << 9)
        };
        set_in(&mut cur,i,v);
        i += 1;
    }
    let mut off = zeros(n+1);
    let mut cand = Vec::with_capacity(n);
    let mut p = 0usize;
    let mut si = 0usize;
    let mut seedleft = 0usize;
    let mut seeddist = 0usize;
    while p < n {
        if seedleft == 0 && si < nseed {
            let x = get0(&cur,si);
            let l = (x & 511) as usize;
            seedleft = if l >= 3 { l } else { 1 };
            seeddist = (x >> 9) as usize;
            si += 1;
        }
        let start = cand.len();
        set_in(&mut off,p,start as u32);
        let mut j = get0(&mp,p) as usize;
        let end = get0(&mp,p+1) as usize;
        while j < end && j < mb.len() {
            let x = get0(&mb,j);
            let len = ((x >> 15) & 255)+3;
            let dist = (x & 32767)+1;
            let bucket = (x >> 23) & 31;
            rf_cache_push(&mut cand,start,len | (dist << 9) | (bucket << 25));
            j += 1;
        }
        if seedleft >= 3 && seeddist > 0 && seeddist <= p {
            let cap = if n-p < 258 { n-p } else { 258 };
            let l = if seedleft < cap { seedleft } else { cap };
            rf_cache_push(&mut cand,start,l as u32 | ((seeddist as u32) << 9) | ((q9_dslot(seeddist) as u32) << 25));
        }
        seedleft = seedleft.saturating_sub(1);
        p += 1;
    }
    set_in(&mut off,n,cand.len() as u32);
    let mut ends = zeros(n/16384+1);
    let mut tab = zeros((n/16384+1)*576);
    let mut w = rf_zeros64(16384);
    let mut r = zeros(16384);
    let mut c = zeros(16384);
    let seedbytes = rf_exact(input,&cur,nseed,&mut ends,&mut tab,&mut w,&mut r,&mut c,conf[5],conf[6]);
    let mut back = zeros(n+1);
    let mut best = zeros(n);
    q9_copy32(&cur,0,&mut best,0,nseed);
    let mut bestbytes = seedbytes;
    let mut bestnt = nseed;
    let mut rng = 0x9E3779B97F4A7C15u64;
    let mut it = 0usize;
    while it < conf[1] && it < 16 {
        let nt = rf_dp(input,&off,&cand,&ends,&tab,&mut back,&mut cur);
        let bytes = rf_exact(input,&cur,nt,&mut ends,&mut tab,&mut w,&mut r,&mut c,conf[5],conf[6]);
        if bytes < bestbytes {
            bestbytes = bytes;
            bestnt = nt;
            q9_copy32(&cur,0,&mut best,0,nt);
        } else if conf[3] > 0 {
            rf_exact(input,&best,bestnt,&mut ends,&mut tab,&mut w,&mut r,&mut c,conf[5],conf[6]);
            rng = rf_perturb(&mut tab,bestnt.wrapping_add(16383)/16384,rng);
        }
        it += 1;
    }
    best
}

'''

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r18-586-selective-rf';original=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text();needle='    let e = CLASS_TAB[cls % 32];';assert original.count(needle)==1
    entries=[]
    for name,all_a in [('r18-586-a-shared-rf',False),('r18-586-a-refit',True)]:
        condition='e[0] == 0 && CFG[e[1] % 16][0] == 0'+(''if all_a else' && REFINE[cls % 32] != 0')
        text=needle+f'''
    if {condition} {{
        let rk = if REFINE[cls % 32] != 0 {{ REFINE[cls % 32] }} else {{ 28 }};
        let plan = r18_a_shared_plan(input,e[1],rk);
        return emit(input,&plan,out);
    }}'''
        rust=original.replace(needle,text)+HELPER
        e=m.write_candidate(name,p.name,rust,proof,
          'Build A matches once; use one initial-model A pass for a checked seed, convert the same matches into RF cache format, then refit exact block costs while retaining the seed as a competing plan. '+('Apply to every existing A router class; use released RF row28 for previously unrefined A classes.'if all_a else'Apply only to already A-plus-RF routes; preserve the released RF configuration for each route.'),
          'Q/Z profiles show duplicate matching and multiple planning passes. D-only weak seeds lost0.0615pp, but they discarded A match quality as well. This keeps A deep search and its candidate list while removing duplicate RF search and A model iterations. Minimum native byte screen decides whether total time and substantial new Lean migration are worth doing.',
          {'parent':'references/round18-public-586/source-receipt.json','evidence':['evidence/round18/refine-q-decision.json','evidence/round18/seed-u-decision.json','evidence/round18/37982889694'],'ownership':'Original A and RF algorithms retained with attribution; new shared-cache pipeline is a derived composition, not invention of the engines.'})
        e.update(anchor='public586',comparison_baseline='selective586',native_decode_reference='selective586');entries.append(e)
    s=json.loads((ROOT/'evidence/round18/rank-ac-native.json').read_bytes());s['entries']=[x for x in s['entries']if x.get('control')]+entries;s['screen_orders']=[[x['name']for x in s['entries']],[x['name']for x in reversed(s['entries'])]]
    s['description']='AJ shared-search feasibility: compare existing A+RF routes only against applying the shared A-cache/exact-RF pipeline to all A routes. One initial A pass, same deep match candidates, existing RF row28 where no old row exists; checked seed competes with refinements. This is a structural work/quality tradeoff, not a pass-count sweep. Original encoder28files and decode; cap25job-minutes. Inspect actual quality and target-space cost budget before timing or new Lean implementation. Neither variant has an adapted proof.'
    (ROOT/'evidence/round18/shared-aj-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps(entries))

if __name__=='__main__':main()
