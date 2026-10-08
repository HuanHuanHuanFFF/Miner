"""One fixed D gap candidate; run this lightweight source builder locally.

Native/official extraction and proof gate run only on the authorized runner.
The original public loader/block/gap helpers are retained byte for byte.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-finder-pipeline-proof"
NAME = "r11-gap-meta"
PINS = {"parse.rs": "b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf",
        "Parse.lean": "e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db"}

HELPERS = r'''

// R11 D-only loaded-table metadata. All original public helpers remain above.
// 511 is unreachable by d_dp prices: gap rem <= top_len - 1 <= 510;
// accepted candidate endpoints and pushes are explicitly bounded by 258.
// Zero disables batching; otherwise this is the exact maximum of a positive table.
pub fn d_gap_positive_max(litc: &[u32; 256]) -> u32 {
    let mut i = 0usize;
    let mut maximum = 0u32;
    let mut positive = true;
    while i < 256 {
        let price = litc[i];
        if price > maximum { maximum = price; }
        if price == 0 { positive = false; }
        i += 1;
    }
    if positive { maximum } else { 0 }
}

pub fn d_load_meta(tabs: &[u32], tb: usize, litc: &mut [u32; 256], lc: &mut [u32; 512], dcc: &mut [u32; 32]) {
    d_load(tabs, tb, litc, lc, dcc);
    lc[511] = d_gap_positive_max(litc);
}

#[inline(always)]
pub fn d_block_meta(tabs: &[u32], bstart: &[u32], litc: &mut [u32; 256], lc: &mut [u32; 512], dcc: &mut [u32; 32], bs: &mut [usize; 2], pos: usize) {
    if pos < bs[1] && bs[0] > 0 {
        let b = bs[0] - 1;
        d_load_meta(tabs, b.wrapping_mul(D_TS), litc, lc, dcc);
        bs[0] = b;
        bs[1] = get0(bstart, b) as usize;
    }
}

// Internal loaded-table path. The cached bound comes from d_load_meta on the
// same litc/lc pair; arbitrary stand-alone metadata is NOT self-authenticating.
// The original d_gap stays the generic API and fallback.
pub fn d_gap_meta(s: &[u8], litc: &[u32; 256], lc: &[u32; 512], ring: &mut [u64; D_RING], out: &mut [u32], hi: usize, stop: usize, end: usize, kcd: u64, chd: u64, lo: usize, nxt0: u64, dlit: u64) -> u64 {
    let maximum = lc[511] as u64;
    // Together with rem <= 258 this keeps the natural choice below 2^32.
    if maximum == 0 || chd > 0xFFFF_FEFD || dlit >= 0x1_0000_0000 {
        return d_gap(s, litc, lc, ring, out, hi, stop, end, kcd, chd, lo, nxt0, dlit);
    }
    let mut q = hi;
    let mut nxt = nxt0;
    let mid = d_clip(end.saturating_sub(2), stop, hi);
    while q > mid && q <= s.len() && q <= out.len() {
        q -= 1;
        let mut v = (nxt >> 32).wrapping_add(litc[s[q] as usize] as u64) << 32 | dlit;
        if q >= lo {
            let o = ring[q % D_RING];
            if o < v { v = o; }
        }
        ring[q % D_RING] = v;
        out[q] = v as u32;
        nxt = v;
    }
    let kc = (d_cell(ring, end) >> 32).wrapping_add(kcd);
    let s1 = d_clip(lo, stop, q);
    while q > s1 && q <= s.len() && q <= out.len() && end >= q {
        q -= 1;
        let rem = end - q;
        let vl = (nxt >> 32).wrapping_add(litc[s[q] as usize] as u64) << 32 | dlit;
        let vc = (kc.wrapping_add(lc[rem % 512] as u64) << 32) | (chd.wrapping_add(rem as u64));
        let mut v = if vc < vl { vc } else { vl };
        let o = ring[q % D_RING];
        if o < v { v = o; }
        ring[q % D_RING] = v;
        out[q] = v as u32;
        nxt = v;
    }
    while q > stop && q <= s.len() && q <= out.len() && end >= q {
        // Original scalar seed. A price transition or failed guard resumes here.
        q -= 1;
        let rem = end - q;
        let length_price = lc[rem % 512];
        let vl = (nxt >> 32).wrapping_add(litc[s[q] as usize] as u64) << 32 | dlit;
        let vc = (kc.wrapping_add(length_price as u64) << 32) | (chd.wrapping_add(rem as u64));
        let v = if vc < vl { vc } else { vl };
        ring[q % D_RING] = v;
        out[q] = v as u32;
        nxt = v;
        if vc < vl && rem >= 3 && rem <= 258 && (vc >> 32).wrapping_add(maximum) < 0x1_0000_0000 {
            let high = vc & 0xFFFF_FFFF_0000_0000;
            // No pre-scan: each following lc value is checked once, then filled.
            // Cached kc stays fixed even if writes wrap through the ring.
            while q > stop && q <= s.len() && q <= out.len() && end >= q {
                let q1 = q - 1;
                let rem1 = end - q1;
                if rem1 > 258 || lc[rem1 % 512] != length_price { break; }
                let v1 = high | chd.wrapping_add(rem1 as u64);
                ring[q1 % D_RING] = v1;
                out[q1] = v1 as u32;
                q = q1;
                nxt = v1;
            }
        }
    }
    nxt
}
'''

BOUNDARY_HARNESS = r'''
#![allow(dead_code, unused_variables)]
#[path="frozen.rs"] mod base;
#[path="candidate.rs"] mod new;

fn table(mode: usize) -> Vec<u32> {
    let mut tabs = vec![0u32; base::D_TS];
    for i in 0..256 { tabs[i] = match mode { 0 => 1, 1 => 0, 2 => u32::MAX,
        3 => if i % 3 == 0 { 0 } else { 3 }, _ => 1_000_000 }; }
    for i in 0..264 { tabs[256+i] = (i/4 + 2) as u32; }
    for i in 520..552 { tabs[i] = 17; }
    tabs
}
fn main() {
    let mut loader_cases = 0;
    for mode in 0..5 {
        let tabs = table(mode); let mut a = [0;256]; let mut b = [0;256];
        let mut la = [0;512]; let mut lb = [0;512]; let mut da = [0;32]; let mut db = [0;32];
        base::d_load(&tabs,0,&mut a,&mut la,&mut da);
        new::d_load_meta(&tabs,0,&mut b,&mut lb,&mut db);
        assert_eq!(a,b); assert_eq!(da,db); assert_eq!(la[..511],lb[..511]);
        let expected = if b.iter().any(|&x|x==0) {0} else {*b.iter().max().unwrap()};
        assert_eq!(lb[511],expected); loader_cases += 1;
        let mut oldlc = [7;512]; let mut newlc = [7;512];
        base::d_load(&tabs,usize::MAX,&mut a,&mut oldlc,&mut da);
        new::d_load(&tabs,usize::MAX,&mut b,&mut newlc,&mut db);
        assert_eq!(a,b); assert_eq!(oldlc,newlc); assert_eq!(da,db); loader_cases += 1;
    }
    let mut dp_cases = 0;
    for n in [0usize,1,2,3,16,259,511,600,1025] {
        let src: Vec<u8> = (0..n).map(|i|(i%256)as u8).collect();
        for mode in 0..5 { for pmode in 0..4 { for len in [0u32,2,3,258,259,264,510,511] {
            let tabs = table(mode); let bs = vec![0]; let dt = [0;512];
            let rs = vec![len | (32767<<9) | (255<<24),0,1];
            let mut a=vec![0;n]; let mut b=vec![0;n];
            base::d_dp(&src,&rs,&tabs,&bs,&dt,&mut a,pmode);
            new::d_dp(&src,&rs,&tabs,&bs,&dt,&mut b,pmode);
            assert_eq!(a,b,"malformed len={} n={} mode={} pmode={}",len,n,mode,pmode);
            dp_cases += 1;
        } } }
    }
    // Multi-block reload, malformed records and differing dtab entries.
    for mode in 0..5 { for pmode in 0..4 {
        let src:Vec<u8>=(0..1200).map(|i|(i%256)as u8).collect();
        let mut tabs=table(mode); tabs.extend(table((mode+1)%5));
        let bs=vec![0,550]; let dt=[29;512];
        for rs in [vec![511,0,1,258 | (7<<9),600,1],vec![0,0,0],vec![3,0,999],vec![511,1100,1],vec![]] {
            let mut a=vec![0;1200]; let mut b=vec![0;1200];
            base::d_dp(&src,&rs,&tabs,&bs,&dt,&mut a,pmode);
            new::d_dp(&src,&rs,&tabs,&bs,&dt,&mut b,pmode);
            assert_eq!(a,b,"multi-block mode={} pmode={}",mode,pmode); dp_cases+=1;
        }
    } }
    // Witness that 510 is an actual generic gap price, while only 511 is reserved.
    let src=vec![0u8;600]; let lit=[1_000_000;256];
    let mut lc=[0u32;512]; for i in 264..512 {lc[i]=0x00ff_ffff;}
    let mut meta=lc; meta[511]=new::d_gap_positive_max(&lit);
    let mut ra=[0u64;base::D_RING]; let mut rb=ra; let mut oa=vec![0;600]; let mut ob=oa.clone();
    let va=base::d_gap(&src,&lit,&lc,&mut ra,&mut oa,509,1,511,0,512,600,0,base::D_LIT);
    let vb=new::d_gap_meta(&src,&lit,&meta,&mut rb,&mut ob,509,1,511,0,512,600,0,new::D_LIT);
    assert_eq!(va,vb); assert_eq!(ra,rb); assert_eq!(oa,ob);
    let mut changed=lc; changed[510]=0;
    let mut rc=[0u64;base::D_RING]; let mut oc=vec![0;600];
    let vc=base::d_gap(&src,&lit,&changed,&mut rc,&mut oc,509,1,511,0,512,600,0,base::D_LIT);
    assert_ne!(va,vc,"510 witness failed to observe its price");
    // False stand-alone metadata is deliberately NOT an equivalence claim.
    let mut s=vec![0u8;9]; s[4]=1; let mut prices=[1u32;256]; prices[1]=3;
    let mut honest=[0u32;512]; honest[511]=3; let mut fake=honest; fake[511]=1;
    let mut ra=[0u64;base::D_RING]; ra[8]=(0xffff_fffeu64)<<32; let mut rb=ra; let mut rc=ra;
    let mut oa=vec![0;9]; let mut ob=oa.clone(); let mut oc=oa.clone();
    let nxt=0xffff_fffeu64<<32;
    let va=base::d_gap(&s,&prices,&honest,&mut ra,&mut oa,6,3,8,0,512,100,nxt,base::D_LIT);
    let vb=new::d_gap_meta(&s,&prices,&honest,&mut rb,&mut ob,6,3,8,0,512,100,nxt,new::D_LIT);
    assert_eq!(va,vb); assert_eq!(ra,rb); assert_eq!(oa,ob);
    let vc=new::d_gap_meta(&s,&prices,&fake,&mut rc,&mut oc,6,3,8,0,512,100,nxt,new::D_LIT);
    assert!(vc!=va || oc!=oa,"expected false-metadata counterexample absent");
    println!("R11_GAP_BOUNDARY {{\"loader_cases\":{},\"dp_cases\":{},\"slot510_witness\":true,\"honest_wrap_fallback\":true,\"false_metadata_counterexample_expected\":true}}",loader_cases,dp_cases);
}
'''


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def function(source: str, name: str) -> str:
    start = source.index("pub fn " + name + "(")
    brace = source.index("{", start); depth = 1; i = brace + 1
    while depth:
        depth += (source[i] == "{") - (source[i] == "}"); i += 1
    return source[start:i]


def generate() -> dict[str, bytes]:
    raw = {f: (BASE / f).read_bytes() for f in PINS}
    assert {f: sha(v) for f, v in raw.items()} == PINS
    source = raw["parse.rs"].decode("utf-8")
    before = function(source, "d_dp")
    after = before
    edits = []
    for old, new, count in (("d_load(", "d_load_meta(", 1), ("d_block(", "d_block_meta(", 2), ("d_gap(", "d_gap_meta(", 1)):
        assert after.count(old) == count
        after = after.replace(old, new); edits.append((old, new, count))
    restored = after
    for old, new, count in reversed(edits):
        assert restored.count(new) == count; restored = restored.replace(new, old)
    assert restored == before
    assert source.count(before) == 1
    changed = source.replace(before, after, 1)
    rust = (changed + HELPERS).encode("utf-8")
    for name in ("d_load", "d_block", "d_gap", "d_bcost", "d_best_len_scalar", "d_best_len_old", "d_best_len", "d_push", "d_cand", "d_back"):
        assert function(rust.decode(), name) == function(source, name), name
    files = {"parse.rs": rust, "Parse.lean": raw["Parse.lean"], "native-helper-check.rs": BOUNDARY_HARNESS.encode()}
    parent = json.loads((BASE / "manifest.json").read_text(encoding="utf-8"))
    manifest = {
        "candidate": NAME, "parent": "candidates/r10-finder-pipeline-proof", "base_submission_id": "361",
        "parent_hashes": PINS, "hashes": {f: sha(files[f]) for f in PINS},
        "bytes": {f: len(files[f]) for f in PINS}, "attribution": parent["attribution"],
        "mechanism": "D-only positive maxlit in unreachable slot511; direct same-lc continuation fill after strict scalar seed, with cost32/choice/length guards and original scalar fallback",
        "expected_equivalent_to": "r10-finder-pipeline-proof",
        "equivalence_status": "INFERRED_SOURCE_CALLER_INVARIANT; native444/public tokens/bytes and malformed rs/slot510 runner tests PENDING. No stand-alone arbitrary-metadata helper equivalence claim.",
        "proof_status": "UNADAPTED_PARENT_DRAFT / NOT_RUN; fresh Aeneas plus original obligation/axioms/full gate required",
        "proof_scope": "Planner totality, not all-input token equivalence. New helper data-origin semantic invariant must not be added as an original gate premise.",
        "proof_cost": "New positive-max/load/block/gap nested loops and specs; d_dp inner/outer nine-state tuples expected unchanged, only function bindings migrate; scalar seed guarantees outer q decrease and bulk q can only decrease further.",
        "performance_status": "UNKNOWN; 55.1% observed third-loop opportunity is not elapsed time or a promised gain. Mean safe B=3.92 makes start/check/code-size cost a major risk.",
        "evidence": "evidence/round11/37722786008/probe-a/diagnostics/gap-diagnostics/gap-diagnostics.json",
        "cost_scope": "One additional256-entry max/positive scan per actual load; every following lc entry checked once, no platform prescan; original ring/out writes preserved",
        "stop": "Any native/public mismatch or slot510/malformed-rs failure stops. Stop if paired total time has no useful gain after short-segment overhead; no parameter/cache expansion.",
        "native_helper_harness_sha256": sha(files["native-helper-check.rs"]),
    }
    audit = {"status": "VERIFIED_LOCAL_REVERSIBLE_SOURCE_EDITS_ONLY", "parent_hashes": PINS,
             "candidate_hashes": manifest["hashes"], "d_dp_call_replacements": edits,
             "unchanged_public_helpers": ["d_load", "d_block", "d_gap", "d_bcost", "d_best_len_scalar", "d_best_len_old", "d_best_len", "d_push", "d_cand", "d_back"],
             "slot": 511, "retained_prices": "0..510", "native_status": "UNCOMPILED / NOT_RUN",
             "range_argument": "p<hi<=n; cl=top%512<=511; cl<=room ensures end=p+cl<=n without wrap, otherwise end=p and no continuation; q_after>=stop>=p+1 gives rem<=cl-1<=510. Candidate and push paths explicitly <=258.",
             "data_origin_limit": "Metadata only trustworthy after d_load_meta on the same litc/lc arrays; falsified stand-alone metadata fixture included and must not be reported equivalent."}
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode()
    files["SOURCE_AUDIT.json"] = (json.dumps(audit, indent=2, ensure_ascii=False) + "\n").encode()
    files["PROOF_PLAN.md"] = ("# Actual-extraction proof pending\n\nOriginal helpers/theorems remain. Add totality specs for d_gap_positive_max, d_load_meta, d_block_meta and d_gap_meta loops. Rebind d_dp initial/inner/node calls, expected unchanged9-state tuples. Outer scalar seed q decrements before nested fill, so prove nested q_out<=q_seed and out.length equality, then q_out<q_entry. Original obligation, axiom whitelist and checked emitter unchanged. This copied Lean is UNADAPTED and must not be gated as accepted. Stand-alone false metadata has a known semantic counterexample; loaded-source invariant is separate from totality.\n").encode()
    assert all(0 < len(files[f]) <= 524288 for f in PINS)
    return files


def main():
    parser = argparse.ArgumentParser(); parser.add_argument("--check", action="store_true"); args = parser.parse_args()
    files = generate(); dest = ROOT / "candidates" / NAME
    if args.check:
        assert all((dest / f).read_bytes() == data for f, data in files.items())
    else:
        dest.mkdir(parents=True, exist_ok=True)
        for f, data in files.items():
            path = dest / f
            if path.exists(): assert path.read_bytes() == data, f"Refusing to mutate frozen candidate {path}"
            else: path.write_bytes(data)
    print(json.dumps({"candidate": NAME, "status": "SOURCE_READY_NATIVE_UNCOMPILED", "hashes": {f: sha(data) for f, data in files.items()}, "builder_sha256": sha(Path(__file__).read_bytes())}))


if __name__ == "__main__":
    main()
