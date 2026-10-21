"""B10 controlled quality repair: endpoint entropy fitting then original full Huffman DP."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round24-public-552'
TARGET = ROOT / 'candidates/r26-b-552-endpoint-fit'
EXPECTED = {'parse.rs': '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9',
            'Parse.lean': '51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'}

FULL_LOOP = '''                    let mut at = prev + 1;
                    let mut l = at.wrapping_sub(i) as u32;
                    while at <= stop {
                        let c = (cost[at].wrapping_add(lc[(l % 512) as usize]).wrapping_add(base) << 9) | l;
                        mbest = if c < mbest { c } else { mbest };
                        at += 1;
                        l = l.wrapping_add(1);
                    }'''

HELPER = '''
// Statistical first-pass sampler only; the final original a_dp_pass remains full.
pub fn r26_a_endpoint_best(cost:&Vec<u32>,lc:&[u32;512],i:usize,lo:usize,hi:usize,base:u32)->u32 {
    let mut best=4294967295u32;let mut l=lo;
    while l<=hi&&l<=258 {
        let c=(get0(cost,i.wrapping_add(l)).wrapping_add(lc[l%512]).wrapping_add(base)<<9)|(l as u32);
        if c<best{best=c;}
        if l==hi{l=259;}else{
            let e=R26_A_LENGTH_END[l%259];
            l=if l<e{if e<hi{e}else{hi}}else{l+1};
        }
    }
    best
}
'''

NEW_ITERATION = '''        // One price-aware endpoint statistical fit using retained future costs.
        let fit_lim=if pe==n{n}else{pe-A_MARGIN};
        r26_a_endpoint_fit(input,&mp,&mb,p0,pe,&lit,&lc,&dc,&mut cost,ch);
        let fit=a_walk(input,ch,p0,fit_lim,need,&mut lf,&mut df);
        if fit.1>0&&fit.0>p0 {
            let span=(fit.0-p0).wrapping_mul(need)/fit.1;
            let grow=span.saturating_add(span/16).saturating_add(A_MARGIN);
            pe=if n-p0>grow{p0+grow}else{n};
        }
        a_add_counts(&mut sl,&bl,&lf,&mut sd,&bd,&df);
        a_set_costs_huff(&sl,&sd,&mut lit,&mut lc,&mut dc);
        // Unchanged original full DP retains all final length/candidate edges.
        let lim=if pe==n{n}else{pe-A_MARGIN};
        a_dp_pass(input,&mp,&mb,p0,pe,&lit,&lc,&dc,&mut cost,ch);
        let r=a_walk(input,ch,p0,lim,need,&mut lf,&mut df);
        p1=r.0;t=r.1;
        a_add_counts(&mut sl,&bl,&lf,&mut sd,&bd,&df);
        a_set_costs(&sl,&sd,&mut lit,&mut lc,&mut dc);
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def generate():
    raw = {name: (BASE / name).read_bytes() for name in EXPECTED}
    assert {name: sha(value) for name, value in raw.items()} == EXPECTED
    source = raw['parse.rs'].decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    old = fn(source, 'a_engine')
    start = old.index('        while k < passes {')
    stop = old.index('        used += t;', start)
    new = old[:start] + NEW_ITERATION + old[stop:]
    for unused in ['        let passes = if p0 == 0 { first_passes } else { passes_k };\n',
                   '        let sampled = if p0 == 0 { fspass } else { spn };\n',
                   '        let mut k = 0usize;\n']:
        assert new.count(unused) == 1
        new = new.replace(unused, '', 1)
    dp = fn(source, 'a_dp_pass')
    assert dp.count(FULL_LOOP) == 2
    fit = dp.replace('pub fn a_dp_pass(', 'pub fn r26_a_endpoint_fit(', 1).replace(
        FULL_LOOP, '                    mbest = r26_a_endpoint_best(cost,lc,i,prev+1-i,stop-i,base);')
    table = re.search(r'pub const LBASE: \[u32; 29\] = \[(.*?)\];', source, re.S)
    bases = list(map(int, re.findall(r'\d+', table.group(1))))
    assert bases == [3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258]
    ends = list(range(3))
    for length in range(3, 259):
        slot = max(index for index, base in enumerate(bases) if base <= length)
        ends.append(bases[slot+1]-1 if slot < 28 else 258)
    assert len(ends) == 259 and all(length <= ends[length] <= 258 for length in range(3, 259))
    extra = '\npub const R26_A_LENGTH_END:[usize;259]=[' + ','.join(map(str, ends)) + '];\n' + HELPER + '\n' + fit
    rust = (source.replace(old, new, 1) + extra).encode()
    assert rust.decode()[:-len(extra)].replace(new, old, 1).encode() == raw['parse.rs']
    spans = importlib.import_module('r26-b-fix-shared-cache').spans(rust.decode())
    assert 'r26_a_endpoint_fit' in spans and 'r26_a_endpoint_best' in spans
    files = {'parse.rs': rust, 'Parse.lean': raw['Parse.lean']}
    manifest = {
        'candidate': TARGET.name, 'parent': BASE.relative_to(ROOT).as_posix(), 'formal_parent_id': '552',
        'parent_hashes': EXPECTED, 'hashes': {name: sha(value) for name, value in files.items()},
        'bytes': {name: len(value) for name, value in files.items()},
        'attribution': 'Original public552 matcher/fullDP/emitter and source attribution retained. Length-code-end sampling is established original-family machinery, not new invention.',
        'mechanism': 'One entropy-cost endpoint DP derives a per-block fitted path; original a_walk/count context then original smoothed-Huffman constructor and unchanged full A DP. New first-pass retained endpoints are lo, hi and globalDEFLATE length-code ends only.',
        'cost': 'Statistical fit scans every fittedposition/cachedcandidate and writes full cost/ch; fixed259entry endpoint lookup replaces only statistical per-length loops. Original initialization/model/secondDP/walk/encoder costs remain.',
        'scope': 'Only A engine body plus cloned statistical DP and endpoint helper/table. Final original a_dp_pass, matcher/cache, routes/tables, otherengines and emitter retain exact bytes.',
        'quality_status': 'UNKNOWN: expectedtokens differ; this is not an equivalent firstpass or a guaranteed quality repair',
        'proof_status': 'UNADAPTED_PARENT_DRAFT; newhelpers/outerloop need actualextraction/full originalgate if useful',
        'performance_status': 'NOT_RUN native originalencoder/completecoarsecost checkpoint first; no pairedgain claim',
        'formal_status': 'NOT_SUBMITTED; formaladmission/private/reward UNKNOWN',
        'predeclared': 'evidence/round26/route-b/endpoint-b11-predeclared.md',
        'negative_predecessor': 'evidence/round26/route-b/b10-greedy-feedback.json',
        'source_reversal': 'Remove appended endpoint table/helper/clonedDP and restore oldAengine to exactpinnedsource.',
    }
    files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
    assert all(0 < len(value) <= 524288 for name, value in files.items() if name != 'manifest.json')
    return files, manifest


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    files, manifest = generate()
    TARGET.mkdir(exist_ok=True)
    for name, raw in files.items():
        path = TARGET / name
        if args.check:
            assert path.read_bytes() == raw
        else:
            assert not path.exists() or path.read_bytes() == raw
            path.write_bytes(raw)
    print(json.dumps({'candidate': TARGET.name, 'hashes': manifest['hashes'], 'bytes': manifest['bytes']}))


if __name__ == '__main__':
    main()
