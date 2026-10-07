"""Round5 independent algorithm hypotheses; no toolchain, CI, or submission actions.

Only writes candidates/r5-opt-* named in RECIPES. All proofs are explicitly
NOT_ADAPTED reference text until a real extraction is available.
"""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'candidates/r4-hybrid-h3r-smallc299'
LOCK = {'parse.rs':'6814b45429d9dbbb66a94a2a18abca39bd23790756490e8acbb62e79306d18d9',
        'Parse.lean':'eec49d582853cddf843c33b950f444520561bbb40ef0197ee64ce9acfbb92791'}
RECIPES = ['r5-opt-small-select', 'r5-opt-a-best299']
spec = importlib.util.spec_from_file_location('hybrid_generator', ROOT/'scripts/make-round4-hybrid.py')
hybrid = importlib.util.module_from_spec(spec)
spec.loader.exec_module(hybrid)

def sha(b): return hashlib.sha256(b).hexdigest()
def once(s,a,b):
    assert s.count(a)==1,(a,s.count(a))
    return s.replace(a,b,1)

HELPERS = r'''
// Research cost model: package-merge for every alphabet, original H RLE and
// fixed/dynamic/stored selection; final byte padding is accounted for below.
// Exact agreement with the official encoder remains a CI diagnostic obligation.
pub fn r5_token_bytes(tokens: &[u32], count: usize) -> u64 {
    let end = if count < tokens.len() { count } else { tokens.len() };
    let mut fr = [0u32; 320];
    let mut lens = [0u32; 320];
    let mut bits = 0u64;
    let mut i = 0usize;
    let mut used = 0usize;
    while i < end {
        let token = tokens[i];
        if token >= 16777216 {
            let value = token.wrapping_sub(16777216);
            let len = (value % 256) as usize + 3;
            let dist = (value / 256) as usize + 1;
            h_walk_bump(&mut fr, 0, len, dist, 0);
        } else {
            h_walk_bump(&mut fr, 0, 1, 0, (token % 256) as usize);
        }
        used += 1;
        i += 1;
        if used == 16384 && i < end {
            let r = r5_block_bits(&mut fr, 0, &mut lens);
            let padding = if r % 4 == 2 { (8 - bits.wrapping_add(3) % 8) % 8 } else { 0 };
            bits = bits.wrapping_add(r / 4).wrapping_add(padding);
            h_clear(&mut fr, 0, 320);
            used = 0;
        }
    }
    let r = r5_block_bits(&mut fr, 0, &mut lens);
    let padding = if r % 4 == 2 { (8 - bits.wrapping_add(3) % 8) % 8 } else { 0 };
    bits = bits.wrapping_add(r / 4).wrapping_add(padding);
    bits.wrapping_add(7) / 8
}

// Histograms include an EOB in the original A walker. Clear its accumulated
// pseudo-count here; r5_block_bits inserts exactly one EOB for this block.
pub fn r5_hist_bits(lf: &[u32; 512], df: &[u32; 32], raw: usize) -> u64 {
    let mut fr = [0u32; 320];
    let mut lens = [0u32; 320];
    h_copy32(lf, 0, &mut fr, 0, 286);
    h_copy32(df, 0, &mut fr, 288, 30);
    fr[256] = 0;
    let mut extra = 0u32;
    let mut c = 0usize;
    while c < 29 {
        extra = extra.wrapping_add(lf[257 + c].wrapping_mul(h_lextra(c)));
        c += 1;
    }
    c = 0;
    while c < 30 {
        extra = extra.wrapping_add(df[c].wrapping_mul(h_dextra(c)));
        c += 1;
    }
    fr[318] = extra;
    fr[319] = raw as u32;
    r5_block_bits(&mut fr, 0, &mut lens) / 4
}
'''

ENTRY = '''pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    if input.len() < 65536 {
        let mut other = zeros(input.len());
        let s_count = s_parse(input, out);
        let h_count = h_parse_mode(input, &mut other, 3);
        let s_bytes = r5_token_bytes(out, s_count);
        let h_bytes = r5_token_bytes(&other, h_count);
        if h_bytes < s_bytes {
            h_copy32(&other, 0, out, 0, h_count);
            return h_count;
        }
        return s_count;
    }
    let c = classify(input);
    if c >= 1 && c <= 3 {
        s_parse(input, out)
    } else {
        h_parse_mode(input, out, 3)
    }
}'''


def best_engine(src, fs):
    a=fs['a_engine']['text']
    a=once(a,'    let mut p0 = 0usize;','''    let mut r5_saved = zeros(n);
    let mut r5_block_start = 0usize;
    let mut p0 = 0usize;''')
    a=once(a,'        let mut k = 0usize;','''        let mut r5_best_bits = 0u64;
        let mut r5_best_raw = 0usize;
        let mut r5_best_end = p0;
        let mut r5_best_tokens = 0usize;
        let mut k = 0usize;''')
    a=once(a,'                t = r.1;','''                t = r.1;
                // Only actual full DP paths participate; sampled plans do not.
                if t > 0 && p1 > p0 && p1 > r5_block_start {
                    a_add_counts(&mut sl, &bl, &lf, &mut sd, &bd, &df);
                    let raw = p1 - r5_block_start;
                    let bits = r5_hist_bits(&sl, &sd, raw);
                    if r5_best_raw == 0 || bits.wrapping_mul(r5_best_raw as u64) < r5_best_bits.wrapping_mul(raw as u64) {
                        r5_best_bits = bits;
                        r5_best_raw = raw;
                        r5_best_end = p1;
                        r5_best_tokens = t;
                        h_copy32(ch, p0, &mut r5_saved, p0, p1 - p0);
                    }
                }''')
    a=once(a,'        used += t;','''        if r5_best_tokens > 0 && r5_best_end > p0 {
            h_copy32(&r5_saved, p0, ch, p0, r5_best_end - p0);
            let chosen = a_walk(input, ch, p0, r5_best_end, r5_best_tokens, &mut lf, &mut df);
            p1 = chosen.0;
            t = chosen.1;
            a_add_counts(&mut sl, &bl, &lf, &mut sd, &bd, &df);
            a_set_costs(&sl, &sd, &mut lit, &mut lc, &mut dc);
        }
        used += t;''')
    a=once(a,'            used = 0;','''            used = 0;
            r5_block_start = p1;''')
    return once(src,fs['a_engine']['text'],a)


def generate(name,check):
    frozen={n:(BASE/n).read_bytes() for n in LOCK}
    for n,h in LOCK.items(): assert sha(frozen[n])==h,(n,'parent drift')
    source=frozen['parse.rs'].decode()
    fs,cs,ts=hybrid.declarations(source)
    block=fs['h_block_bits']['text'].replace('pub fn h_block_bits(', 'pub fn r5_block_bits(',1)
    block=block.replace('h_pkg_merge(', 'h_pkg_merge_pm(')
    assert block.count('h_pkg_merge_pm(')==3
    changed={'parse'}
    if name=='r5-opt-small-select':
        source=once(source,fs['parse']['text'],ENTRY)
        mechanism='For n<65536, run original S and H mode3, compare complete token stream byte-cost models, preserve S on ties; larger inputs keep the complete original h3r-smallc299 dispatcher.'
    else:
        source=best_engine(source,fs)
        source=once(source,fs['parse']['text'],'''pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    s_parse(input, out)
}''')
        changed.add('a_engine')
        mechanism='Original public299 routing/budgets; after each full A DP pass, compare estimated complete encoder-block bits per decoded byte, save the best prefix and endpoint, restore it and rebuild counts/model before continuing. Sampled passes never compete. Ratio objective is a heuristic when endpoints differ, not global optimality.'
    source+='\n\n'+block+'\n'+HELPERS
    nf,nc,nt=hybrid.declarations(source)
    for n,d in fs.items():
        if n not in changed: assert nf[n]['text']==d['text'],('unexpected function change',n)
    assert nc==cs and nt==ts,'constant/type drift'
    assert set(nf)-set(fs)=={'r5_block_bits','r5_token_bytes','r5_hist_bits'}
    plain=hybrid.mask(source)
    assert not re.search(r'\b(?:n|input\.len\(\))\s*==\s*(?:[1-9][0-9_]{3,})',plain)
    proof=b'-- RESEARCH ONLY: NOT_ADAPTED. Frozen parent proof is retained for migration, not acceptance.\n'+frozen['Parse.lean']
    assert not re.search(r'(?m)^\s*(?:axiom|sorry|admit)\b',proof.decode())
    files={'parse.rs':source.encode(),'Parse.lean':proof}
    assert all(len(v)<524288 for v in files.values())
    manifest={'candidate':name,'parent':{'path':BASE.relative_to(ROOT).as_posix(),'hashes':LOCK},
        'hashes':{n:sha(v) for n,v in files.items()},'bytes':{n:len(v) for n,v in files.items()},
        'mechanism':mechanism,'proof_status':'NOT_ADAPTED: old parent proof retained with explicit research-only comment; new functions/loops and changed entry need actual Charon/Aeneas Funs before migration.',
        'gate_policy':'Research compilation/round-trip/performance only. gate_candidates must omit these candidates. Request exact freshly extracted Funs before proof work.',
        'attribution':'External public299 and public402 via frozen h3r-smallc299; original sources and ownership retained in references/round4-public-299/PROVENANCE.json and references/round4-public-402/PROVENANCE.json.',
        'static_audit':{'changed_parent_functions':sorted(changed),'added_functions':['r5_block_bits','r5_hist_bits','r5_token_bytes'],'all_other_parent_functions_constants_types':'Exact declaration text preserved; generator asserts this.'},
        'cost_model':'H package-merge path forced for all three alphabets, original H code-length RLE/header/fixed/stored model, 16384 token blocks; token scorer adds stored alignment and final byte padding. Exact Rust agreement with official encoder UNKNOWN until CI differential check.',
        'verification':'VERIFIED generation/hash/declaration checks only. Rust build, cost/encoder differential, decode, formal totality, axiom whitelist, public paired coordinates, private stage2, admission and rewards UNKNOWN.'}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode()
    dest=ROOT/'candidates'/name
    if check:
        for n,b in files.items(): assert (dest/n).read_bytes()==b,(name,n)
    else:
        dest.mkdir(exist_ok=True,parents=True)
        for n,b in files.items(): (dest/n).write_bytes(b)
    print(json.dumps({'candidate':name,'hashes':manifest['hashes'],'bytes':manifest['bytes'],'proof_status':'NOT_ADAPTED'}))


def model_check():
    # Independent lightweight Python models; not execution of either Rust parser.
    import random
    rng = random.Random(506299)
    def direct(freq, bits):
        order=sorted((i for i,f in enumerate(freq) if f),key=lambda i:(freq[i],i))
        result=[0]*len(freq)
        if len(order)<2:
            if order: result[order[0]]=1
            return result
        leaves=[(freq[i],[j]) for j,i in enumerate(order)]
        cur=leaves
        for _ in range(1,bits):
            packages=[(cur[j][0]+cur[j+1][0],cur[j][1]+cur[j+1][1]) for j in range(0,len(cur)-1,2)]
            out=[];a=b=0
            while a<len(leaves) or b<len(packages):
                if b>=len(packages) or (a<len(leaves) and leaves[a][0]<=packages[b][0]): out.append(leaves[a]);a+=1
                else: out.append(packages[b]);b+=1
            cur=out
        for _,syms in cur[:2*len(order)-2]:
            for j in syms:result[order[j]]+=1
        return result
    def flags_back(freq,bits):
        order=sorted((i for i,f in enumerate(freq) if f),key=lambda i:(freq[i],i))
        result=[0]*len(freq);k=len(order)
        if k<2:
            if order:result[order[0]]=1
            return result
        leaves=[freq[i] for i in order];cur=leaves;flags=[]
        for _ in range(1,bits):
            packages=[cur[j]+cur[j+1] for j in range(0,len(cur)-1,2)]
            out=[];fl=[];a=b=0
            while a<k or b<len(packages):
                if b>=len(packages) or (a<k and leaves[a]<=packages[b]):out.append(leaves[a]);fl.append(1);a+=1
                else:out.append(packages[b]);fl.append(0);b+=1
            assert len(out)<=576
            flags.append(fl);cur=out
        counts=[0]*k;s=2*k-2
        for fl in reversed(flags):
            leaf_count=sum(fl[:s])
            for j in range(leaf_count):counts[j]+=1
            s=2*(s-leaf_count)
        for j in range(s):counts[j]+=1
        for j,i in enumerate(order):result[i]=counts[j]
        return result
    cases=0
    for n,bits in [(19,7),(30,15),(288,15)]:
        presets=[[0]*n,[1]*n,[16384]+[0]*(n-1),[1<<min(i,20) for i in range(n)]]
        for trial in range(60):
            presets.append([0 if rng.randrange(4)==0 else rng.choice([1,2,3,4,255,65536,rng.randrange(1,16385)]) for _ in range(n)])
        for fr in presets:
            assert flags_back(fr,bits)==direct(fr,bits),(n,bits,fr)
            cases+=1
    runs=0
    for value in range(16):
        for run in range(1,321):
            count=[0]*19;extra=0;rest=run
            if value==0:
                while rest>=3:
                    if rest>=11:take=min(rest,138);count[18]+=1;extra+=7
                    else:take=min(rest,10);count[17]+=1;extra+=3
                    rest-=take
                count[0]+=rest
                q,r=divmod(run,138)
                expected=[0]*19;expected[18]=q+(r>=11);expected[17]=int(3<=r<11);expected[0]=r if r<3 else 0
                exp_extra=expected[18]*7+expected[17]*3
            else:
                count[value]+=1;rest-=1
                while rest>=3:
                    take=min(rest,6);count[16]+=1;extra+=2;rest-=take
                count[value]+=rest
                q,r=divmod(run-1,6)
                expected=[0]*19;expected[16]=q+(r>=3);expected[value]=1+(r if r<3 else 0)
                exp_extra=expected[16]*2
            assert (count,extra)==(expected,exp_extra),(value,run)
            runs+=1
    return {'scope':'Python model comparison only; no Rust execution or formal proof', 'seed':506299,'package_merge_cases':cases,'rle_run_cases':runs,'mismatches':0}


def diagnostic_source(upstream):
    upstream=Path(upstream).resolve()
    modules=[]
    for name,p in [('token',upstream/'validator/measure/src/token.rs'),('deflate',upstream/'validator/measure/src/deflate.rs'),('candidate',ROOT/'candidates/r5-opt-small-select/parse.rs')]:
        modules.append(f'#[path={json.dumps(str(p))}] mod {name};')
    driver=r"""
#![allow(dead_code)]
MODULES
fn check(ts:&[u32],n:usize,label:&str,checks:&mut usize){
    let encoded=deflate::encode(ts,n).expect("legal diagnostic tokens");
    let estimated=candidate::r5_token_bytes(ts,ts.len());
    assert_eq!(estimated,encoded.len()as u64,"cost mismatch {}",label);
    *checks+=1;
}
fn main(){
    let mut checks=0usize;
    let mut z=506299u64;
    for n in [0,1,2,3,16,31,32,255,256,257,16383,16384,16385,32767,32768,32769,65535,65536,65537]{
        for mode in 0..5{
            let mut ts=Vec::new();
            for i in 0..n{z^=z<<13;z^=z>>7;z^=z<<17;ts.push(match mode{0=>0,1=>(i%256)as u32,2=>(z%256)as u32,3=>(z%5+65)as u32,_=>if z%31==0{z as u32%256}else{0}});}
            check(&ts,n,&format!("literals-{}-{}",n,mode),&mut checks);
        }
    }
    for len in 3..259{
        let mut ts=vec![65u32;32768];
        ts.push(16777216u32+32767*256+(len-3)as u32);
        check(&ts,32768+len,&format!("length-{}",len),&mut checks);
    }
    for distance in [1usize,2,3,4,5,6,7,8,9,16,17,32,33,64,65,128,129,256,257,512,513,1024,1025,2048,2049,4096,4097,8192,8193,16384,16385,32768]{
        let mut ts=vec![65u32;32768];
        for i in 0..16385{let len=3+i%256;ts.push(16777216+((distance-1)as u32)*256+(len-3)as u32);}
        let n=32768+(0..16385).map(|i|3+i%256).sum::<usize>();
        check(&ts,n,&format!("distance-{}",distance),&mut checks);
    }
    println!("COST_DIFFERENTIAL_OK {}",checks);
}
"""
    return driver.replace('MODULES','\n'.join(modules))

if __name__=='__main__':
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check',action='store_true')
    ap.add_argument('--model-check',action='store_true')
    ap.add_argument('--diagnostic-source',metavar='OFFICIAL_ROOT')
    ap.add_argument('--only',action='append',choices=RECIPES,default=[])
    args=ap.parse_args()
    if args.diagnostic_source: print(diagnostic_source(args.diagnostic_source))
    elif args.model_check: print(json.dumps(model_check()))
    else:
        for n in args.only or RECIPES: generate(n,args.check)
