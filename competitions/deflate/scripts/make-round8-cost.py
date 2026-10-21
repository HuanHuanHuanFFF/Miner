"""Fixed-finder distance-price experiments on public #361; no local toolchain."""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round7-public-361'

TOP = '''/// Choose between this candidate and the longest candidate by distance price.
#[inline(always)]
pub fn rc_pick_top(cands: &[u32; 16], nc: usize, k0: usize, dtab: &[u8; 512], dcc: &[u32; 32]) -> u32 {
    let a = cands[k0 % 16];
    let b = cands[nc.saturating_sub(1) % 16];
    let ad = a >> 9;
    let bd = b >> 9;
    let ac = dcc[dsym(dtab, ad as usize) % 32];
    let bc = dcc[dsym(dtab, bd as usize) % 32];
    if bc < ac || (bc == ac && bd < ad) { b } else { a }
}

'''

SUFFIX = '''/// Cheapest distance among candidates at k0 and later, with nearer-distance ties.
#[inline(always)]
pub fn rc_pick_suffix(cands: &[u32; 16], nc: usize, k0: usize, dtab: &[u8; 512], dcc: &[u32; 32]) -> u32 {
    let mut chosen = cands[k0 % 16];
    let mut price = dcc[dsym(dtab, (chosen >> 9) as usize) % 32];
    let mut k = k0;
    while k < nc && k < 16 {
        let c = cands[k];
        let ds = dsym(dtab, (c >> 9) as usize) % 32;
        let p = dcc[ds];
        if p < price || (p == price && (c >> 9) < (chosen >> 9)) {
            chosen = c;
            price = p;
        }
        k += 1;
    }
    chosen
}

'''


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    ap.add_argument('--refresh-generated', action='store_true')
    args = ap.parse_args()
    raw = {n: (BASE / n).read_bytes() for n in ('parse.rs', 'Parse.lean')}
    provenance = json.loads((BASE / 'PROVENANCE.json').read_text())
    assert all(sha(raw[n]) == provenance['hashes'][n] for n in raw)
    source = raw['parse.rs'].decode()
    begin = source.index('/// `relax_cands` with sequential lengths')
    end = source.index('/// The forward dynamic program with the knobs', begin)
    old_function = source[begin:end]
    old = '''        let bd = base.wrapping_add(dcc[ds]);
        relax_seq(pa, lc, i, lo, len, bd, c & !511u32);'''
    assert old_function.count(old) == 1
    recipes = {
        'full': ('Relax every retained candidate over 3..len; diagnostic reference for all-distance cost choices.', ''),
        'top': ('For each existing length interval compare the current and longest candidate distance prices.', TOP),
        'suffix': ('For each existing length interval use the cheapest covering suffix candidate distance.', SUFFIX),
    }
    for label, (mechanism, helper) in recipes.items():
        if label == 'full':
            replacement = old.replace('i, lo, len', 'i, 3, len')
        else:
            replacement = f'''        let chosen = rc_pick_{label}(cands, nc, k, dtab, dcc);
        let fds = dsym(dtab, (chosen >> 9) as usize) % 32;
        let bd = base.wrapping_add(dcc[fds]);
        relax_seq(pa, lc, i, lo, len, bd, chosen & !511u32);'''
        changed = old_function.replace(old, replacement, 1)
        rust = source[:begin] + helper + changed + source[end:]
        assert rust.replace(helper + changed, old_function, 1) == source
        name = 'r8-mid361-cost-' + label
        files = {'parse.rs': rust.encode(), 'Parse.lean': raw['Parse.lean']}
        # Proof adaptation is deliberately separate; copied proofs are not gate verdicts.
        manifest = {
            'candidate': name, 'base_submission_id': '361', 'parent': 'references/round7-public-361',
            'base_hashes': provenance['hashes'], 'hashes': {n: sha(b) for n, b in files.items()},
            'bytes': {n: len(b) for n, b in files.items()}, 'mechanism': mechanism,
            'attribution': {'author_hotkey': provenance['author_hotkey'], 'provenance': 'references/round7-public-361/PROVENANCE.json'},
            'audit': 'Reverse helper insertion and one rc_seq forward-relax replacement restores original Rust bytes. Search, candidate order, backward extension, routes, emitters and knobs unchanged.',
            'proof_status': 'UNKNOWN; reference proof copied, fresh extraction and full gate required.',
            'performance_status': 'UNKNOWN; paired public measurements and own-family formal transfer required.',
        }
        files['manifest.json'] = (json.dumps(manifest, indent=2) + '\n').encode()
        dest = ROOT / 'candidates' / name
        if args.check:
            assert all((dest / n).read_bytes() == b for n, b in files.items()), name
        else:
            dest.mkdir(parents=True, exist_ok=True)
            if args.refresh_generated and (dest / 'manifest.json').exists():
                previous = json.loads((dest / 'manifest.json').read_text())
                assert previous['candidate'] == name
                assert all(sha((dest / n).read_bytes()) == h for n, h in previous['hashes'].items())
            for n, b in files.items():
                assert args.refresh_generated or not (dest / n).exists() or (dest / n).read_bytes() == b
                (dest / n).write_bytes(b)
        print(json.dumps({'candidate': name, 'hashes': manifest['hashes']}))


if __name__ == '__main__':
    main()
