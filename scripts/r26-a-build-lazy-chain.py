"""Expose existing PC predecessors to the already active lazy decision."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round26-public-641'
OUT = ROOT / 'evidence/round26/route-a'
NAME = 'r26-a-641-lazy-chain'
RUST = '97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
LEAN = '7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e'

HELPER = '''// R26: preserve the head offer, then inspect the existing bounded predecessors.
#[inline(always)]
pub fn r26_lc_probe(s: &[u8], prev: &[u32; 32768], c: usize, cw: u64,
                    q: usize, l: usize, dp: usize) -> (usize, usize) {
    let mut best = pc_probe_lazy(s, c, cw, q, l);
    let c2 = prev[c % 32768] as usize;
    if c2 < c {
        let w2 = pc_be8(s, c2);
        let g = pc_probe_lazy(s, c2, w2, q, l);
        if g.0 >= 4 && (best.0 < 4 || pc_gain(g.0, g.1) > pc_gain(best.0, best.1)) {
            best = g;
        }
        if dp >= 2 {
            let c3 = prev[c2 % 32768] as usize;
            if c3 < c2 {
                let w3 = pc_be8(s, c3);
                let h = pc_probe_lazy(s, c3, w3, q, l);
                if h.0 >= 4 && (best.0 < 4 || pc_gain(h.0, h.1) > pc_gain(best.0, best.1)) {
                    best = h;
                }
            }
        }
    }
    best
}

'''


def sha(raw): return hashlib.sha256(raw).hexdigest()
def dump(path, value): path.write_bytes((json.dumps(value, indent=2) + '\n').encode())


def generate():
    rust = (BASE / 'parse.rs').read_bytes(); lean = (BASE / 'Parse.lean').read_bytes()
    assert sha(rust) == RUST and sha(lean) == LEAN
    original = rust.decode()
    a = original.index('pub fn pc_run1c<const H: usize>')
    b = original.index('\n#[inline(always)] pub fn pc_put_match_checked', a)
    body = original[a:b]
    old = 'let g = pc_probe_lazy(input, c2, w2, q, l);'
    new = 'let g = r26_lc_probe(input, &prev, c2, w2, q, l, dp);'
    assert body.count(old) == 1
    changed = original[:a] + body.replace(old, new) + original[b:]
    marker = '#[inline(always)]\npub fn pc_run1c<const H: usize>'
    assert changed.count(marker) == 1
    changed = changed.replace(marker, HELPER + marker)
    assert changed.replace(HELPER, '', 1).replace(new, old, 1) == original
    assert len(changed.encode()) <= 524288 and len(lean) <= 524288
    return changed.encode(), lean


def main():
    predeclared = {
        'status': 'PREDECLARED_BEFORE_CANDIDATE_NATIVE',
        'gap': 'At a normal PC_chain position public641 searches head plus up to two predecessors, but at an already enabled lazy position only its head is considered. Existing head/prev and original insertion already contain older offers; their quality opportunity at lazy decisions is UNKNOWN.',
        'historical_boundary': 'R20 chain-lazy enabled original pc_run1c lazy parameters; inspection confirms its lazy body still calls pc_probe_lazy on head only. R25 dual8 replaces the retention structure, and duplicate-hop adds one normal-position chain read. Their negative total costs remain relevant but do not test this exact consumer of existing lazy-position predecessors.',
        'change': 'One helper and one pc_run1c call replacement. Preserve original head offer, probe one older hint plus a second only when original dp>=2, using unchanged pc_probe_lazy/window/byte checks. Choose strict greater original pc_gain, retaining head then nearer predecessor on ties. Final existing comparison against current match remains unchanged.',
        'target_space': 'Broad existing PC_chain lazy routes have access to more competing parse choices. The hypothesis is meaningful quality improvement without a new index or postpass; no measured magnitude or 5/10 claim exists. Latest geometric target mapping and actual native bytes must precede timing/proof allocation.',
        'minimum_operation': 'Original28file encoder and independent native decode against exact public641/public514. Untimed observed copy separately confirms candidate token identity and counts head/older offers plus accepted lazy choices. New trajectory and downstream Huffman cost are retained, not approximated by saved token counts.',
        'costs': 'Every actual chain lazy iteration adds one prev read; each live strictly older hint adds one source word and an original lazy validation, which can extend to258. dp>=2 may add a second of each. No new persistent arrays, hashing, insertion, postpass or route. Runtime cost remains UNKNOWN.',
        'stop': 'Any decode or identity failure requires diagnosis. Negligible or poor quality stops this fixed consumer; do not sweep depth/thresholds. Useful quality first gets original paired total time, not full proof by default.',
        'cap_runner_minutes': 12,
        'proof': 'Original PC.probe_lazy_spec returns FoundAt plus length/distance bounds from c<=q, coherent source word, q+8<=n, q+l<=n+1. Strict descending hints preserve c<=q; pc_be8_spec supplies coherent words. Select existing FoundAt offers. Adding dp to actual extracted lazy loop capture will require proof signature/call migration; copied Lean is DRAFT. No full proof or native result yet.'
    }
    dump(OUT / 'cycle-a8-predeclared.json', predeclared)
    rust, lean = generate()
    dest = ROOT / 'candidates' / NAME
    assert not dest.exists(); dest.mkdir()
    (dest / 'parse.rs').write_bytes(rust); (dest / 'Parse.lean').write_bytes(lean)
    hashes = {'parse.rs': sha(rust), 'Parse.lean': sha(lean)}
    manifest = {
        'candidate': NAME, 'parent': 'references/round26-public-641', 'hashes': hashes,
        'attribution': {'source_receipt': 'references/round26-public-641/source-receipt.json', 'author_hotkey': '5FYhJSAu4q86E2Yn8UjNvpbUQVZGzq5wB7W7YFqnmvz288yo', 'ownership': 'Derivative of public641; original author/source preserved.'},
        'mechanism': predeclared['change'], 'cost': predeclared['costs'],
        'proof_status': 'COPIED_ORIGINAL_LEAN_UNADAPTED_DRAFT',
        'quality_status': 'UNKNOWN', 'time_status': 'UNKNOWN', 'gate_status': 'NOT_RUN', 'formal_submission_sent': False,
        'preserved': 'All route/classifier/H/hash/normal-chain/record/fold/emitter code and existing near-distance guards; no A3/A5/A6/A7 combination.'
    }
    dump(dest / 'manifest.json', manifest)
    entry = {'name': NAME, 'path': dest.relative_to(ROOT).as_posix(), 'control': False, 'hashes': hashes,
             'anchor': 'public641', 'comparison_baseline': 'public641', 'native_decode_reference': 'public641'}
    dump(OUT / 'lazy-chain-entry.json', entry)
    dump(OUT / 'lazy-chain-build-audit.json', {'status': 'VERIFIED_EXACT_REVERSAL_NOT_NATIVE', 'parent_hashes': {'parse.rs': RUST, 'Parse.lean': LEAN}, 'hashes': hashes, 'added_helpers': 1, 'changed_calls': 1, 'source_reversal': True, 'proof_unchanged': True})
    spec = json.loads((OUT / 'quality-a7-native.json').read_bytes())
    spec['entries'] = [e for e in spec['entries'] if e['control']] + [entry]
    names = [e['name'] for e in spec['entries']]
    spec['screen_orders'] = [names, names[::-1]]
    spec['snapshot_pages'] = 'evidence/round26/official-hour1/pareto-pages.json'
    spec['r26_a_lazy_chain_counts'] = True
    spec['description'] = predeclared['gap'] + ' ' + predeclared['change'] + ' Native quality/untimed counters first; no threshold sweep or proof claim.'
    dump(OUT / 'quality-a8-native.json', spec)
    print(json.dumps({'candidate': NAME, 'hashes': hashes, 'batch_sha256': sha((OUT / 'quality-a8-native.json').read_bytes())}, indent=2))


if __name__ == '__main__': main()
