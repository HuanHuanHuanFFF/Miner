"""One controlled #552 A model-source change; keep complete cache and final DP."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round24-public-552'
TARGET = ROOT / 'candidates/r26-b-552-greedy-fit'
EXPECTED = {'parse.rs': '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9',
            'Parse.lean': '51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'}

HELPER = '''
// R26 statistical fit only. The original full A match graph is retained below.
pub fn r26_a_greedy_fit(s:&[u8],mp:&Vec<u32>,mb:&Vec<u32>,p0:usize,lim:usize,need:usize,lf:&mut[u32;512],df:&mut[u32;32])->(usize,usize) {
    let mut z=0usize;while z<512{lf[z]=0;z+=1;}
    z=0;while z<32{df[z]=0;z+=1;}
    let mut p=p0;let mut t=0usize;
    while p<lim&&p<s.len()&&t<need {
        let mut best=0usize;let mut dist=0usize;
        let mut j=get0(mp,p)as usize;let e=d_min(get0(mp,p.wrapping_add(1))as usize,mb.len());
        while j<e {
            let m=get0(mb,j);let l=(((m>>15)&255)+3)as usize;let d=((m&32767)+1)as usize;
            if d<=p&&l<=s.len()-p&&(l>best||(l==best&&(dist==0||d<dist))){best=l;dist=d;}
            j+=1;
        }
        if best>=3 {
            let ls=(257+a_len_slot(best))%512;lf[ls]=lf[ls].wrapping_add(1);
            let ds=(a_slot_of((dist.wrapping_sub(1))as u32)as usize)%32;df[ds]=df[ds].wrapping_add(1);
            p+=best;
        }else{let b=s[p]as usize;lf[b]=lf[b].wrapping_add(1);p+=1;}
        t+=1;
    }
    lf[256]=1;(p,t)
}
'''

NEW_ITERATION = '''        // Fit one fresh block statistic from the complete original cache.
        let fit_lim=if pe==n{n}else{pe-A_MARGIN};
        let fit=r26_a_greedy_fit(input,&mp,&mb,p0,fit_lim,need,&mut lf,&mut df);
        if fit.1>0&&fit.0>p0 {
            let span=(fit.0-p0).wrapping_mul(need)/fit.1;
            let grow=span.saturating_add(span/16).saturating_add(A_MARGIN);
            pe=if n-p0>grow{p0+grow}else{n};
        }
        a_add_counts(&mut sl,&bl,&lf,&mut sd,&bd,&df);
        a_set_costs_huff(&sl,&sd,&mut lit,&mut lc,&mut dc);
        // Preserve the original full-range DP and actual block-context tally.
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
    rust = (source.replace(old, new, 1) + '\n' + HELPER).encode()
    restored = rust.decode()[:-len('\n' + HELPER)].replace(new, old, 1)
    assert restored.encode() == raw['parse.rs']
    spans = importlib.import_module('r26-b-fix-shared-cache').spans(rust.decode())
    assert 'r26_a_greedy_fit' in spans
    files = {'parse.rs': rust, 'Parse.lean': raw['Parse.lean']}
    manifest = {
        'candidate': TARGET.name, 'parent': BASE.relative_to(ROOT).as_posix(), 'formal_parent_id': '552',
        'parent_hashes': EXPECTED, 'hashes': {name: sha(value) for name, value in files.items()},
        'bytes': {name: len(value) for name, value in files.items()},
        'attribution': {'source': 'Original public552 source and original author attribution retained verbatim outside A engine; reference provenance remains at parent.',
                        'original_cache_and_final_dp': ['a_find_all', 'a_dp_pass', 'a_walk', 'a_set_costs_huff', 'a_set_costs', 'emit_pos']},
        'mechanism': 'Fresh per-block greedy longest-match histogram over complete unchanged A cache replaces sampled DP and entropy full-fit iterations. Original smoothed-Huffman cost constructor then original full A DP; actual final counts retain complete encoder-block bl/bd context and next-block model.',
        'scope': 'Only a_engine body and one statistical helper. All routes/tables/other engines/matcher/final DP/emitter retain exact bytes. Token/quality changes expected.',
        'guard_cost': 'New token-start cache scan, fresh512/32hist initialization, one cost fit per block and original final DP/walk; no claimed free statistic or 11percent time gain.',
        'source_reversal': 'Remove exact appended helper and restore original a_engine function to recover pinned source bytes.',
        'proof_status': 'UNADAPTED_PARENT_DRAFT; fresh extraction/new helper and A loop proof/full original gate NOT_RUN',
        'performance_status': 'NOT_RUN: native original encoder quality and coarse complete work checkpoint first; no paired total gain yet',
        'formal_status': 'NOT_SUBMITTED; admission/private metrics/payment UNKNOWN',
        'negative_predecessors': ['evidence/round18/model-aa-native-decision.json', 'evidence/round18/shared-aj-decision.json', 'evidence/round18/repeat-e-decision.json'],
        'predeclared': 'evidence/round26/route-b/greedy-b10-predeclared.md',
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
