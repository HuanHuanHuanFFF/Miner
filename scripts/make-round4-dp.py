"""Research-only bucket RMQ variant of public299's A planner.

Writes only candidates/r4-dp299-rmq/. The old proof is a migration reference:
new cache/loop state is NOT proved, so this candidate must not be gated or
submitted as ready. Rust compilation, finite equivalence and timing need CI.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import random
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "references/round4-public-299"
NAME = "r4-dp299-rmq"
HASHES = {
    "parse.rs": "71314c4da7ccd29331a360bce9be8697857109c66adc87d3480eeaa22930625d",
    "Parse.lean": "9b77b3523cbf7044aaffa11b6fd9676b3615ca4bf148b43b3cb92da4073b3e3d",
}
STARTS = [3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258]
ENDS = [x-1 for x in STARTS[1:]] + [258]

HELPERS = r'''
// Research RMQ: keys are (cost modulo 2^23, absolute position). The original
// u32 packed comparison discards cost's upper nine bits. Position breaks ties
// toward shorter length. Full-bucket queries use both extrema: crossing the
// modular-order cut falls back to the original scalar comparison.
pub const R4_LSTART: [usize; 29] = [3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258];
pub const R4_LEND: [usize; 29] = [3,4,5,6,7,8,9,10,12,14,16,18,22,26,30,34,42,50,58,66,82,98,114,130,162,194,226,257,258];

#[inline(always)]
pub fn r4_rmq_update(mn: &mut [u64; 3072], mx: &mut [u64; 3072], pos: usize, value: u32) {
    let slot = pos % 512;
    let key = (((value & 8388607) as u64) << 32) | ((pos as u32) as u64);
    mn[slot] = key;
    mx[slot] = key;
    let mut level = 1usize;
    let mut half = 1usize;
    while level < 6 {
        let lower = (level - 1) * 512;
        let other = pos.wrapping_add(half) % 512;
        let a = mn[(lower + slot) % 3072];
        let b = mn[(lower + other) % 3072];
        let x = mx[(lower + slot) % 3072];
        let y = mx[(lower + other) % 3072];
        mn[(level * 512 + slot) % 3072] = if a < b { a } else { b };
        mx[(level * 512 + slot) % 3072] = if x > y { x } else { y };
        half *= 2;
        level += 1;
    }
}

pub fn r4_rmq_init(mn: &mut [u64; 3072], mx: &mut [u64; 3072], pe: usize, cl: usize) {
    if pe < cl {
        let cap = pe.saturating_add(258);
        let last = if cap < cl { cap } else { cl - 1 };
        let mut left = last - pe + 1;
        while left > 0 {
            left -= 1;
            r4_rmq_update(mn, mx, pe + left, 0);
        }
    }
}

// Do not rely on the caller's cost model being bucket-constant: check it once
// per DP pass. Nonuniform buckets always retain the scalar path.
pub fn r4_uniform_buckets(lc: &[u32; 512]) -> u32 {
    let mut flags = 0u32;
    let mut code = 0usize;
    while code < 29 {
        let low = R4_LSTART[code];
        let high = R4_LEND[code];
        let value = lc[low % 512];
        let mut same = 1usize;
        let mut len = low;
        while len <= high && len < 259 {
            if lc[len % 512] != value { same = 0; }
            len += 1;
        }
        if same == 1 { flags |= 1u32.wrapping_shl(code as u32); }
        code += 1;
    }
    flags
}

#[inline(always)]
pub fn r4_rmq_best(cost: &Vec<u32>, lc: &[u32; 512], mn: &[u64; 3072], mx: &[u64; 3072], uniform: u32, i: usize, from: usize, stop: usize, base: u32) -> u32 {
    if from > stop || stop >= cost.len() || from < i || stop.wrapping_sub(i) > 258 {
        return 4294967295;
    }
    let maxlen = stop - i;
    let mut at = from;
    let mut best = 4294967295u32;
    while at <= stop {
        let len = at - i;
        let code = a_len_slot(len) % 29;
        let low = R4_LSTART[code];
        let high = R4_LEND[code];
        let width = high - low + 1;
        let mut used = 0usize;
        if len == low && high <= maxlen && width >= 4 && (uniform.wrapping_shr(code as u32) & 1) == 1 {
            let level = if width == 4 { 2usize } else if width == 8 { 3usize } else if width == 16 || width == 31 { 4usize } else { 5usize };
            let index = (level * 512 + at % 512) % 3072;
            let mut minkey = mn[index];
            let mut maxkey = mx[index];
            // The final ordinary length bucket is 227..257 (31 values),
            // because 258 has its own code. Two overlapping 16-ranges cover
            // exactly those 31 positions without including length 258.
            if width == 31 {
                let other = (2048 + at.wrapping_add(15) % 512) % 3072;
                let a = mn[other];
                let b = mx[other];
                minkey = if a < minkey { a } else { minkey };
                maxkey = if b > maxkey { b } else { maxkey };
            }
            let add = lc[len % 512].wrapping_add(base);
            let vmin = ((minkey >> 32) as u32).wrapping_add(add) & 8388607;
            let vmax = ((maxkey >> 32) as u32).wrapping_add(add) & 8388607;
            let chosen = (minkey as u32) as usize;
            let end = i + high;
            if vmin <= vmax && chosen >= at && chosen <= end {
                let c = (vmin << 9) | (chosen - i) as u32;
                best = if c < best { c } else { best };
                at = end + 1;
                used = 1;
            }
        }
        if used == 0 {
            let c = (cost[at].wrapping_add(lc[len % 512]).wrapping_add(base) << 9) | len as u32;
            best = if c < best { c } else { best };
            at += 1;
        }
    }
    best
}
'''


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def once(text: str, old: str, new: str) -> str:
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old,new,1)


def model_check() -> dict:
    # Arithmetic/RMQ translation checks only, not execution of candidate Rust.
    rng = random.Random(429966)
    mask = (1 << 23) - 1
    count = 0
    wrapped = 0
    queries = 0
    for trial in range(80):
        n = 900
        values = [rng.getrandbits(32) for _ in range(n)]
        if trial % 3 == 0:
            start = rng.getrandbits(32)
            values = [(start + rng.randrange(3000)) & 0xffffffff for _ in range(n)]
        if trial % 8 == 0:
            values = [rng.getrandbits(32)] * n
        lc = [0] * 512
        for low, high in zip(STARTS, ENDS):
            value = rng.getrandbits(32)
            lc[low:high+1] = [value] * (high-low+1)
        if trial % 5 == 0:
            lc[20] ^= 1  # An intentionally nonuniform bucket must fall back.
        uniform = [len(set(lc[lo:hi+1])) == 1 for lo,hi in zip(STARTS,ENDS)]
        mn = [0]*3072; mx = [0]*3072
        for pos in range(n-1,-1,-1):
            slot = pos%512; key = ((values[pos]&mask)<<32)|pos
            mn[slot]=mx[slot]=key
            half=1
            for level in range(1,6):
                lower=(level-1)*512; other=(pos+half)%512
                mn[level*512+slot]=min(mn[lower+slot],mn[lower+other])
                mx[level*512+slot]=max(mx[lower+slot],mx[lower+other]);half*=2
            if pos+32<=n:
                for width in (4,8,16,31,32):
                    level=width.bit_length()-1;span=1<<level;other=(pos+width-span)%512
                    a=min(mn[level*512+slot],mn[level*512+other]);b=max(mx[level*512+slot],mx[level*512+other])
                    keys=[((v&mask)<<32)|(pos+k)for k,v in enumerate(values[pos:pos+width])]
                    assert a==min(keys) and b==max(keys)
                    add=rng.getrandbits(32); vm=((a>>32)+add)&mask;vx=((b>>32)+add)&mask
                    scalar=min((((v+add)&mask)<<9)|k for k,v in enumerate(values[pos:pos+width]))
                    if vm<=vx:
                        predicted=(vm<<9)|((a&0xffffffff)-pos)
                        assert predicted==scalar,(trial,pos,width)
                    else:wrapped+=1
                    count+=1
            if pos+258<n and pos%13==0:
                low=rng.randrange(3,259);high=rng.randrange(low,259);base=rng.getrandbits(32)
                expected=min(((((values[pos+l]+lc[l]+base)&mask)<<9)|l)for l in range(low,high+1))
                best=0xffffffff;l=low
                while l<=high:
                    code=max(c for c in range(29)if STARTS[c]<=l)
                    lo,hi=STARTS[code],ENDS[code];width=hi-lo+1;used=False
                    if l==lo and hi<=high and width>=4 and uniform[code]:
                        level=width.bit_length()-1;span=1<<level;idx=level*512+(pos+l)%512
                        idx2=level*512+(pos+l+width-span)%512
                        a,b=min(mn[idx],mn[idx2]),max(mx[idx],mx[idx2]);add=(lc[l]+base)&0xffffffff
                        vm=((a>>32)+add)&mask;vx=((b>>32)+add)&mask;chosen=a&0xffffffff
                        if vm<=vx and pos+l<=chosen<=pos+hi:
                            best=min(best,(vm<<9)|(chosen-pos));l=hi+1;used=True
                    if not used:
                        best=min(best,(((values[pos+l]+lc[l]+base)&mask)<<9)|l);l+=1
                assert best==expected,(trial,pos,low,high)
                queries+=1
    return {"kind":"Python arithmetic model only", "seed":429966,"range_checks":count,
        "wrap_fallbacks":wrapped,"mixed_partial_and_nonuniform_queries":queries,"mismatches":0}


def main() -> None:
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check',action='store_true')
    ap.add_argument('--model-check',action='store_true')
    args=ap.parse_args()
    if args.model_check:
        print(json.dumps(model_check()));return
    base={n:(BASE/n).read_bytes()for n in HASHES}
    for n,h in HASHES.items():assert sha(base[n])==h,n
    src=base['parse.rs'].decode();assert '\r\n' not in src
    a=src.index('pub fn a_dp_pass(');b=src.index('\n/// Follows the planned path',a)
    body=src[a:b]
    body=once(body,'        let mut i = pe;','''        let mut r4_min = [0u64; 3072];
        let mut r4_max = [0u64; 3072];
        r4_rmq_init(&mut r4_min, &mut r4_max, pe, cl);
        let r4_uniform = r4_uniform_buckets(lc);
        let mut i = pe;''')
    scan='''                    let mut at = prev + 1;
                    let mut l = at.wrapping_sub(i) as u32;
                    while at <= stop {
                        let c = (cost[at].wrapping_add(lc[(l % 512) as usize]).wrapping_add(base) << 9) | l;
                        mbest = if c < mbest { c } else { mbest };
                        at += 1;
                        l = l.wrapping_add(1);
                    }'''
    assert body.count(scan)==2
    body=body.replace(scan,'                    mbest = r4_rmq_best(cost, lc, &r4_min, &r4_max, r4_uniform, i, prev + 1, stop, base);')
    old='            cost[i] = ((best >> 9).wrapping_add(nxt)).wrapping_sub(1048576);'
    body=once(body,old,old+'\n            r4_rmq_update(&mut r4_min, &mut r4_max, i, cost[i]);')
    text=src[:a]+body+src[b:]+HELPERS
    files={'parse.rs':text.encode(),'Parse.lean':base['Parse.lean']}
    metadata={'candidate':NAME,'parent':{'path':BASE.relative_to(ROOT).as_posix(),'hashes':HASHES},
        'hashes':{n:sha(v)for n,v in files.items()},'bytes':{n:len(v)for n,v in files.items()},
        'mechanism':'Backward-maintained 512-slot sparse min/max table over cost modulo 2^23; full uniform DEFLATE length buckets of width >=4 use RMQ only when the base translation does not cross modular order. Partial/nonuniform/wrapping buckets retain exact original scalar packing and comparison.',
        'tie_break':'RMQ key packs low-23-bit cost then absolute position, so equal translated costs select shorter length. Existing outer strict comparisons preserve earlier-distance ties.',
        'proof_status':'NOT_ADAPTED: Parse.lean is the exact old public299 reference, not a proof for this new parser. New r4 helpers/cache state and changed a_dp_pass extracted loop signatures still need totality/loop proofs. Do not select an official gate as ready or submit.',
        'gate_policy':'Research screen and finite token/decode equivalence only; gate_candidates must be empty until proof migration is completed.',
        'proof_migration_needed':['r4_rmq_update/initialization totality','uniform-bucket loop totality','r4_rmq_best loop progress/index safety','new min/max arrays and uniform capture in a_dp_pass loop specs','removed scalar-loop extraction references must be replaced by helper spec'],
        'preserved':'Original routing, effort settings, token packing, checked emitter, official encoder and all other public299 functions; fixed sentinel matches stay scalar.',
        'attribution':'Derived from public299; see references/round4-public-299/PROVENANCE.json. Ring sparse-table organization follows the inspected public402 H approach, extended with max and modular-order fallback.',
        'verification':'UNKNOWN Rust compilation, finite token equivalence, time/size, fresh extraction/proof/gate, stage2/admission/rewards. Local model-check is arithmetic only and cannot certify the Rust.'}
    assert all(len(v)<=524288 for v in files.values())
    files['manifest.json']=(json.dumps(metadata,indent=2)+'\n').encode()
    dest=ROOT/'candidates'/NAME
    if args.check:
        for n,v in files.items():assert (dest/n).read_bytes()==v,(NAME,n)
    else:
        dest.mkdir(parents=True,exist_ok=True)
        for n,v in files.items():(dest/n).write_bytes(v)
    print(json.dumps({'candidate':NAME,'hashes':metadata['hashes'],'bytes':metadata['bytes'],'proof_status':'NOT_ADAPTED'}))


if __name__=='__main__':main()
