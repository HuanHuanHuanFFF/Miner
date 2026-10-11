"""One cheap length-frequency boundary pass after public641PC engines."""
from pathlib import Path
import hashlib
import json
import random
import re

ROOT=Path(__file__).resolve().parents[1]
PARENT=ROOT/'references/round26-public-641'
OUT=ROOT/'evidence/round26/route-a'
NAME='r26-a-641-boundary-log'
RUST_SHA='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
LEAN_SHA='7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e'
LBASE=[3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258]

HELPERS=r'''
// R26: a single in-place adjacent-match boundary pass. The existing parser
// keeps all matching/search decisions; no extra dictionary lookup is added.
// Length prices use the original block histogram, not rebuilt Huffman trees.
#[inline(always)]
pub fn r26_bl_length(t: u32) -> usize {
    if t >= 16777216 && t < 25165824 { ((t - 16777216) % 256 + 3) as usize } else { 1 }
}

#[inline(never)]
pub fn r26_bl_prices(out: &[u32], start: usize, end: usize) -> [u32; 260] {
    let mut freq = [0u32; 32];
    let mut prices = [255u32; 260];
    let mut i = start;
    while i < end && i < out.len() {
        let t = out[i];
        if t >= 16777216 && t < 25165824 {
            let l = ((t - 16777216) % 256 + 3) as usize;
            let code = (q4_TF_LSYM[l] as usize) % 32;
            freq[code] = freq[code].wrapping_add(1);
        }
        i += 1;
    }
    let mut l = 3usize;
    while l <= 258 {
        let code = (q4_TF_LSYM[l] as usize) % 32;
        let count = freq[code];
        if count > 0 {
            let mut extra = 0u32;
            if code >= 8 && code < 28 { extra = ((code - 4) / 4) as u32; }
            prices[l] = count.leading_zeros() + extra;
        }
        l += 1;
    }
    prices
}

#[inline(always)]
pub fn r26_bl_pair(s: &[u8], previous: u32, current: u32, p: usize, prices: &[u32; 260]) -> (u32, u32) {
    if previous < 16777216 || previous >= 25165824 || current < 16777216 || current >= 25165824 {
        return (previous, current);
    }
    let w = ((previous - 16777216) % 256 + 3) as usize;
    let l = ((current - 16777216) % 256 + 3) as usize;
    let d = ((current - 16777216) / 256 + 1) as usize;
    if p > s.len() || w > p || d > p || l > s.len() - p { return (previous, current); }
    if prices[w] == 255 || prices[l] == 255 { return (previous, current); }
    let mut cap = w - 3;
    if cap > 258 - l { cap = 258 - l; }
    if cap > p - d { cap = p - d; }
    let mut best = prices[w].wrapping_add(prices[l]);
    let mut shift = 0usize;
    let mut k = 1usize;
    let mut go = true;
    while go && k <= cap {
        if s[p - k] != s[p - k - d] {
            go = false;
        } else {
            let a = prices[w - k];
            let b = prices[l + k];
            if a != 255 && b != 255 {
                let cost = a.wrapping_add(b);
                if cost < best { best = cost; shift = k; }
            }
            k += 1;
        }
    }
    // Bounds above keep both low-byte lengths legal; the distances are intact.
    (previous.wrapping_sub(shift as u32), current.wrapping_add(shift as u32))
}

#[inline(never)]
pub fn r26_bl_finish(input: &[u8], out: &mut [u32], nt: usize) -> usize {
    let mut start = 0usize;
    let mut p = 0usize;
    while start < nt && start < out.len() {
        let mut end = start.saturating_add(16384);
        if end > nt { end = nt; }
        if end > out.len() { end = out.len(); }
        let prices = r26_bl_prices(out, start, end);
        let mut i = start;
        while i < end {
            let t = out[i];
            if i > start {
                let changed = r26_bl_pair(input, out[i - 1], t, p, &prices);
                out[i - 1] = changed.0;
                out[i] = changed.1;
            }
            p = p.saturating_add(r26_bl_length(t));
            i += 1;
        }
        start = end;
    }
    nt
}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())
def lc(n):return max(i for i,b in enumerate(LBASE)if b<=n)
def length(t):return (t-16777216)%256+3 if 16777216<=t<25165824 else 1
def token(l,d):return 16777216+(d-1)*256+l-3


def decode(ts):
    s=bytearray()
    for t in ts:
        if t<256:s.append(t)
        else:
            assert 16777216<=t<25165824
            l=length(t);d=(t-16777216)//256+1
            assert d<=len(s)
            for _ in range(l):s.append(s[-d])
    return bytes(s)


def model(ts,s):
    result=ts[:];p=0;changed=0
    for start in range(0,len(ts),16384):
        end=min(start+16384,len(ts));freq=[0]*32
        for t in result[start:end]:
            if t>=16777216:freq[lc(length(t))]+=1
        prices=[255]*260
        for l in range(3,259):
            c=lc(l)
            if freq[c]:prices[l]=32-freq[c].bit_length()+(0 if c<8 or c==28 else(c-4)//4)
        for i in range(start,end):
            t=result[i];l=length(t)
            if i>start and result[i-1]>=16777216 and t>=16777216:
                previous=result[i-1];w=length(previous);d=(t-16777216)//256+1
                assert w<=p and d<=p and p+l<=len(s)
                if prices[w]!=255 and prices[l]!=255:
                    cap=min(w-3,258-l,p-d);best=prices[w]+prices[l];shift=0
                    for k in range(1,cap+1):
                        if s[p-k]!=s[p-k-d]:break
                        a,b=prices[w-k],prices[l+k]
                        if a!=255 and b!=255 and a+b<best:best=a+b;shift=k
                    if shift:
                        result[i-1]-=shift;result[i]+=shift;changed+=1
                        assert length(result[i-1])+length(result[i])==w+l
                        assert (result[i-1]-16777216)//256==(previous-16777216)//256
                        assert (result[i]-16777216)//256==(t-16777216)//256
            p+=l
    assert p==len(s)and len(result)==len(ts)and decode(result)==s
    return result,changed


def finite_model():
    tests=mutations=0;boundaries=[]
    for count in [0,1,2,16383,16384,16385,32768]:
        ts=[65]*max(8,count)
        if count>=2:ts[-2:]=[token(19,1),token(3,1)]
        if count==0:ts=[]
        elif count<8:ts=[65]*count
        data=decode(ts);new,n=model(ts,data);tests+=1;mutations+=n
        boundaries.append({'tokens':len(ts),'changed_pairs':n,'decode_equal':True})
    for seed in range(32):
        rng=random.Random(seed);ts=list(b'ABCDXYZABCDABCDXYZABCD');produced=len(ts)
        for _ in range(1024):
            if rng.randrange(4)==0:ts.append(rng.randrange(65,73));produced+=1
            else:
                l=rng.choice([3,4,5,6,7,8,9,10,11,12,13,18,19,22,34,35,66,67,130,131,194,195,226,227,257,258])
                d=rng.randrange(1,min(produced,32768)+1);ts.append(token(l,d));produced+=l
        s=decode(ts);new,n=model(ts,s);tests+=1;mutations+=n
    assert mutations>0
    return {'status':'VERIFIED_FINITE_PYTHON_TOKEN_BOUNDARY_MODEL_NOT_RUST','cases':tests,'mutated_pairs':mutations,'block_boundaries':boundaries,
            'scope':'Legal token streams, overlap, lengths3..258, distances1..32768, existingcode-only prices and same-block pair rules. Native Rust, all-input proof and performance not established.'}


def main():
    raw=(PARENT/'parse.rs').read_bytes();lean=(PARENT/'Parse.lean').read_bytes()
    assert sha(raw)==RUST_SHA and sha(lean)==LEAN_SHA
    original=raw.decode();text=original
    edits=[]
    for name in ['pc_run1','pc_run1c']:
        start=text.index('pub fn '+name+'<');opening=text.index('{',start);end=opening+1;depth=1
        while depth:depth+=(text[end]=='{')-(text[end]=='}');end+=1
        body=text[start:end];assert body.endswith('    nt\n}')
        replacement=body[:-len('    nt\n}')]+'    r26_bl_finish(input, out, nt)\n}'
        text=text[:start]+replacement+text[end:];edits.append({'function':name,'change':'Only final nt return replaced by same-count postprocess call.'})
    new=(text+'\n'+HELPERS).encode();assert len(new)<=524288 and len(lean)<=524288
    reversed_source=text.replace('    r26_bl_finish(input, out, nt)\n}','    nt\n}')
    assert reversed_source==original
    # Existing table is the same RFC1951length-code partition for every validlen.
    values=original.split('pub const q4_TF_LSYM:',1)[1].split('= [',1)[1].split('];',1)[0]
    codes=list(map(int,re.findall(r'\d+',values)));assert len(codes)==512
    assert all(codes[l]%32==lc(l)for l in range(3,259))
    model_result=finite_model();dump(OUT/'boundary-log-finite-model.json',model_result)
    dest=ROOT/'candidates'/NAME;assert not dest.exists(),'Do not overwrite a frozen candidate';dest.mkdir()
    (dest/'parse.rs').write_bytes(new);(dest/'Parse.lean').write_bytes(lean)
    hashes={'parse.rs':sha(new),'Parse.lean':sha(lean)}
    manifest={'candidate':NAME,'parent':'references/round26-public-641','hashes':hashes,
        'attribution':{'source_receipt':'references/round26-public-641/source-receipt.json','author_hotkey':'5FYhJSAu4q86E2Yn8UjNvpbUQVZGzq5wB7W7YFqnmvz288yo','ownership':'Derivative of public641; original source retained; new boundary helper is this experiment.'},
        'mechanism':'After actualPCrun1/run1c only, one in-place token-block pass counts32slots for29validlengthcodes. Price leading_zeros(freq)+length-extra-bits approximates relative length-code cost. Missingcodes unavailable. Move the legal previous-match suffix to currentdistance only for strictpairpriceimprovement; two tokens and their distances are unchanged.',
        'difference_from_A4':'Replaces originalHuffman tableconstruction by oneinteger frequencyapproximation and fuses suffixvalidation with optionevaluation. Full frequency pass, pricearraybuilding, pairvalidation/search and writes remain paid by the candidate.',
        'routing':'No new classifier/length/filename gate. Called solely from existingPC engine returns; composite row16dx1 branch unaffected.',
        'proof_status':'UNADAPTED_PUBLIC641_LEAN; four new helpers and two new postprocess calls require fresh extraction/proof; oldgate not inherited.',
        'proof_interface':'r26_bl_finish must preserveDec/Valid on fullprefix and outlength, return the same nt. Pair lemma shortens valid previousmatch, transfers a checked suffix into currentmatch, preserves distances and combinedspan; mainpass must relate pre/postpair prefix positions. Price values require only bounds/totality, not Huffmanoptimality.',
        'native_status':'NOT_RUN','time_status':'NOT_RUN','full_gate_status':'NOT_RUN','formal_submission_sent':False}
    dump(dest/'manifest.json',manifest)
    entry={'name':NAME,'path':dest.relative_to(ROOT).as_posix(),'control':False,'hashes':hashes,'anchor':'public641','comparison_baseline':'public641','native_decode_reference':'public641'}
    dump(OUT/'boundary-log-entry.json',entry)
    dump(OUT/'boundary-log-build-audit.json',{'status':'VERIFIED_EXACT_PATCH_AND_FINITE_MODEL_NOT_RUST','hashes':hashes,'parent_hashes':{'parse.rs':RUST_SHA,'Parse.lean':LEAN_SHA},'edits':edits,'helpers':4,'source_reversal':True,'old_length_table256_valid_entries_verified':True,'model':model_result,'native':'NOT_RUN','gate':'NOT_RUN'})
    print(json.dumps({'candidate':NAME,'hashes':hashes,'model':model_result},indent=2))


if __name__=='__main__':main()
