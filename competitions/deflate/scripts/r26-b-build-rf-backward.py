"""One structural RF DP experiment; source/model construction without Rust execution."""
from pathlib import Path
import argparse
import datetime as dt
import hashlib
import json
import math
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT/'references/round25-public-628'
OUT = ROOT/'candidates/r26-b-628-rf-backward'
E = ROOT/'evidence/round26/route-b'
EXPECTED = {
    'parse.rs': '784e02703c98a32f85753cae4f3b62aea3f505d91088869f327e0ad646629c14',
    'Parse.lean': '7c909191f2801e76ac5080966d6df5339191ce48a97a16a3e66ee2a0ca4c636e',
}

HELPER = '''// R26 B: suffix DP on the original RF candidate DAG and token-block prices.
// The existing SF range minima cover the constant-price DEFLATE length domains.
pub fn r26_b_rf_backward(input: &[u8], off: &[u32], cand: &[u32], ends: &[u32], tab: &[u32], back: &mut [u32], out: &mut [u32]) -> usize {
    let n = input.len();
    if n == 0 { return 0; }
    let mut rm = [18446744073709551615u64; 4096];
    let mut ct = [0u32; 1024];
    let mut bend = [0u32; 512];
    Z330(&mut bend);
    let mut b = 0usize;
    while b.wrapping_add(1) < ends.len() && (Z168(ends, b) as usize) < n { b += 1; }
    Z400(tab, b.wrapping_mul(576), &mut ct, 0);
    Z443(&mut rm, n, n as u64);
    let mut p = n;
    while p > 0 {
        p -= 1;
        while b > 0 && p < Z168(ends, b.wrapping_sub(1)) as usize {
            b -= 1;
            Z400(tab, b.wrapping_mul(576), &mut ct, 0);
        }
        let lit = rf_byte(input, p) as usize;
        let mut bc = rm[p.wrapping_add(1) % 512].wrapping_add((ct[lit.wrapping_add(768) % 1024] as u64) << 32);
        let mut bt = 0u32;
        let mut j = Z168(off, p) as usize;
        let end = Z168(off, p.wrapping_add(1)) as usize;
        while j < end {
            let x = Z168(cand, j);
            let maxlen = Z248(Z248((x & 511) as usize, 258), n - p);
            let dc = ((x >> 25) & 31) as usize;
            let dcs = (ct[dc.wrapping_add(512) % 1024] as u64) << 32;
            let v = Z440(&rm, &ct, p, 3, Z248(10, maxlen), dcs, bc);
            let v = Z437(&rm, &ct, &bend, p, 11, maxlen, dcs, v);
            if v < bc {
                bc = v;
                let stop = (v as u32) as usize;
                bt = (x & 0x1ffffff & !511) | (stop.wrapping_sub(p) as u32);
            }
            j += 1;
        }
        Z304(back, p, bt);
        Z443(&mut rm, p, (bc & 0xffffffff00000000u64) | (p as u64));
    }
    let mut nt = 0usize;
    while p < n {
        let x = Z168(back, p);
        let l = (x & 511) as usize;
        let len = if l < 3 || l > n - p { 1 } else { l };
        Z304(out, nt, if len == 1 { 0 } else { x });
        nt += 1;
        p += len;
    }
    nt
}

'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def domain_end(length):
    if length < 11 or length >= 258:
        return length
    bases = [3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258]
    return next(b-1 for b in bases if b > length)


def rm_put(rm, pos, packed):
    rm[pos % 512] = packed
    for level in range(1, 5):
        half = 1 << (level-1)
        rm[level*512+pos%512] = min(rm[(level-1)*512+pos%512], rm[(level-1)*512+(pos+half)%512])


def rm_query(rm, pos, lo, hi, price):
    level = min(4, (hi-lo+1).bit_length()-1)
    width = 1 << level
    packed = min(rm[level*512+(pos+lo)%512], rm[level*512+(pos+hi+1-width)%512])
    return packed + (price << 32)


def finite_model():
    rng = random.Random(26628)
    cases = []
    query_checks = 0
    for case, n in enumerate([rng.randrange(4,150) for _ in range(90)] + [511,512,513,767,1023,1024,1025]):
        ends = list(range(37, n, 37)) + [n]
        litprices = [[rng.randrange(1,241) for _ in range(256)] for _ in ends]
        lenprices, distprices = [], []
        for _ in ends:
            lens = [0]*259
            for lo in range(3,259):
                if lo == 3 or domain_end(lo-1) == lo-1:
                    price = rng.randrange(16,241)
                lens[lo] = price
            lenprices.append(lens)
            distprices.append([rng.randrange(16,241) for _ in range(10)])
        data = [rng.randrange(256) for _ in range(n)]
        buckets, offers = [], []
        for p in range(n):
            b = next(b for b,e in enumerate(ends) if p < e)
            buckets.append(b)
            offers.append([(rng.randrange(10),rng.randrange(3,min(258,n-p)+1)) for _ in range(rng.randrange(4))] if n-p>=3 else [])
        # Independent forward shortest-path enumeration, including every length.
        forward = [math.inf]*(n+1)
        forward[0] = 0
        for p in range(n):
            b = buckets[p]
            forward[p+1] = min(forward[p+1], forward[p]+litprices[b][data[p]])
            for dc, maxlen in offers[p]:
                for length in range(3,maxlen+1):
                    forward[p+length] = min(forward[p+length], forward[p]+lenprices[b][length]+distprices[b][dc])
        # Independently enumerate suffix recurrence for every length.
        suffix = [0]*(n+1)
        for p in range(n-1,-1,-1):
            b = buckets[p]
            suffix[p] = suffix[p+1]+litprices[b][data[p]]
            for dc,maxlen in offers[p]:
                suffix[p] = min(suffix[p], min(suffix[p+l]+lenprices[b][l]+distprices[b][dc] for l in range(3,maxlen+1)))
        assert suffix[0] == forward[n]
        assert max(suffix) < 2**32
        # Packed rolling sparse minima, matching the reused SF coverage/argmin.
        rm = [2**64-1]*4096
        rm_put(rm,n,n)
        choices = [1]*n
        for p in range(n-1,-1,-1):
            b = buckets[p]
            best = rm[(p+1)%512]+(litprices[b][data[p]]<<32)
            for dc,maxlen in offers[p]:
                lo = 3
                while lo <= maxlen:
                    hi = min(domain_end(lo),maxlen)
                    v = rm_query(rm,p,lo,hi,lenprices[b][lo]+distprices[b][dc])
                    truth = min((suffix[p+l]+lenprices[b][lo]+distprices[b][dc])<<32 | (p+l) for l in range(lo,hi+1))
                    assert v == truth, (case,p,lo,hi,v,truth)
                    query_checks += 1
                    best = min(best,v)
                    lo = hi+1
            assert best>>32 == suffix[p]
            choices[p] = (best&0xffffffff)-p
            assert 1 <= choices[p] <= min(258,n-p)
            rm_put(rm,p,(suffix[p]<<32)|p)
        p = nt = 0
        while p < n:
            p += choices[p]
            nt += 1
        assert p == n and nt <= n
        cases.append({'bytes':n,'token_blocks':len(ends),'minimum_cost':forward[n], 'emission_count':nt})
    return {'status': 'VERIFIED_BOUNDED_PYTHON_DAG_AND_PACKED_RMQ_MODEL_ONLY',
            'seed':26628,'graphs':len(cases),'exact_range_argmin_checks':query_checks,
            'cases':cases,
            'scope':'Synthetic nonnegative acyclic match-offer graphs with DEFLATE piecewise length prices, 37-byte block changes and 511/512/513/1023/1024/1025 ring boundaries. This checks minimum cost and packed endpoint representation without 32bit cost wrap. It is not real Rust, token validity, byte equivalence, performance, Lean or official gate evidence.',
            'known_difference':'Forward first-arrival and backward lexicographic endpoint tie handling can produce different equal-cost token plans. Actual iterative original encoder quality remains UNKNOWN.'}


def build():
    raw = {f:(BASE/f).read_bytes() for f in EXPECTED}
    assert {f:sha(b) for f,b in raw.items()} == EXPECTED
    source = raw['parse.rs'].decode()
    old = 'let nt = rf_dp(input,&off,&cand,&ends,&tab,&mut back,&mut cur);'
    new = old.replace('rf_dp(', 'r26_b_rf_backward(')
    assert source.count(old) == 1
    at = source.index('pub fn rf_dp(')
    rust = source[:at]+HELPER+source[at:]
    rust = rust.replace(old,new,1)
    assert rust.replace(new,old,1).replace(HELPER,'',1) == source
    files = {'parse.rs':rust.encode(),'Parse.lean':raw['Parse.lean']}
    manifest = {
        'candidate':OUT.name,'parent':'public628','parent_hashes':EXPECTED,
        'hashes':{f:sha(b) for f,b in files.items()},
        'mechanism':'Replace RF forward per-length relaxation with suffix DP over unchanged cached match offers, using existing SF range minima on constant-price length-code domains. Original RF token-block model, candidate discovery, two iteration budget and internal estimate acceptance remain unchanged. Existing validating Z271 emits the resulting plan.',
        'difference_from_old_work':'R18 span/prefix/ring/previous-position dominance retained forward transition relaxation and either changed layout or skipped covered offers. This changes the DAG recurrence direction and performs range-minimum queries instead of all-length writes. Existing SF solver/RMQ machinery is reused with attribution; this is not a new RMQ invention.',
        'attribution':{'source_receipt':'references/round25-public-628/source-receipt.json',
                       'author_hotkey':'5DM8HSJ17XPGKYTERQUbQuhqWJm3RtpJqTSUH7Dn8m5MVuJ6',
                       'SF_base_source':'references/round24-public-609/source-receipt.json',
                       'SF_base_author_hotkey':'5DPo51y7zmk2WfnkvU4MxAqw66ouW9KonrUGguLRWtPqiP9t',
                       'prior_counterexamples':'docs/rounds/round18.md RF optimization table'},
        'proof_status':'INHERITED_PROOF_UNCHANGED_DRAFT_MISSING_NEW_HELPER_SPECS',
        'proof_dependency':'Need new helper-loop totality and return nt<=input.length; no optimality proof needed for LZ77 correctness because original Z271 revalidates final matches. Existing rf_dp remains defined, so its proof declarations remain valid. The 523018-byte Lean file has only1270B headroom; replace unreferenced original rf_dp proof declarations after real extraction to make room for the new helper specifications. Do not raise official size/recursion/time limits.',
        'semantic_status':'Intentional equal-cost tie differences and altered iterative final token plans possible. No real Rust/encoder/decode run yet. No claim of equivalence with original forward DP on cost-wrapping inputs.',
        'performance_status':'UNKNOWN; SF min structure needs five updates per position and queries per candidate, which may lose to shallow RF despite fewer theoretical length writes.',
        'source_reversal':'Remove exact HELPER bytes and reverse the single refine rf_dp call; complete public628 source restored.',
        'formal_submission_sent':False,
    }
    assert all(len(b)<=524288 for b in files.values())
    files['manifest.json']=(json.dumps(manifest,indent=2,ensure_ascii=False)+'\n').encode()
    return files,manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check',action='store_true')
    args = parser.parse_args()
    files,manifest = build()
    model = finite_model()
    if args.check:
        assert all((OUT/f).read_bytes()==b for f,b in files.items())
        oldmodel=json.loads((E/'rf-backward-finite-model.json').read_bytes())
        assert model==oldmodel
    else:
        OUT.mkdir(exist_ok=False)
        for f,b in files.items():
            (OUT/f).write_bytes(b)
        E.mkdir(exist_ok=True,parents=True)
        (E/'rf-backward-finite-model.json').write_bytes((json.dumps(model,indent=2)+'\n').encode())
        plan = {
            'written_utc':dt.datetime.now(dt.timezone.utc).isoformat(),
            'gap_and_prior':'Old RF work counts showed130.96M per-length updates and only2.48M ordering comparisons. Prior layout and dominance attempts did not establish total-time gains. Actual628 RF per-file quality/cost is pending B1.',
            'substantial_change':'Backward recurrence plus existing SF range-minimum on complete unchanged candidate DAG; not a forward loop-layout/threshold retry.',
            'minimum_operation':'The97 finite DAG/packed RMQ models precede any native dispatch. If B1 demonstrates actualRF quality/cost worth pursuing, compare exact original28-file encoder/decode to628 and its noRF variant, then original paired total-time only after a useful quality tradeoff.',
            'decision':'A useful original encoded result with measured RF work may justify native and original time. A dominated tradeoff, invalid decode or unreachable opportunity pauses this exact candidate. Fewer model operations do not establish speed or reward.',
            'runner_cost_cap_minutes':20,
            'first_valid_test_dependencies':'Root-reviewed B1 quality/cost, root manual native dispatch. Source is prepared; inherited Lean deliberately remains unadapted until actual extraction and justified proof spend.',
            'model_status':model['status'],'graphs':model['graphs'],'range_queries':model['exact_range_argmin_checks'],
            'evidence':'evidence/round26/route-b/rf-backward-finite-model.json and future native original encoder receipts',
        }
        (E/'rf-backward-predeclared.json').write_bytes((json.dumps(plan,indent=2,ensure_ascii=False)+'\n').encode())
    print(json.dumps({'status':'VERIFIED_SOURCE_REVERSAL_AND_BOUNDED_MODEL_ONLY','candidate':OUT.name,
                      'hashes':manifest['hashes'],'graphs':model['graphs'],'range_queries':model['exact_range_argmin_checks']}))


if __name__=='__main__':
    main()
