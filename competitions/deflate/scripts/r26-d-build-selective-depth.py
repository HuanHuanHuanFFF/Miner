"""D1: move U118 row9 residual search from a losing head to a lazy winning head."""
from pathlib import Path
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'references/round26-public-658'
OUT = ROOT / 'evidence/round26/extension90m/route-d'
NAME = 'r26-d-658-selective-depth'
RUST = '1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad'
LEAN = '354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494'
HELP = importlib.import_module('r26-a-rep-shadow')

EXTRA = r'''
// D1: complete the original depth budget after its first source was inspected.
// No state survives an insertion; current continuation happens before q is
// inserted, and lazy continuation happens after q's normal insertion.
#[inline(always)]
pub fn d1_continue<const W: usize>(s: &[u8], prev: &[u32; W], p: usize,
    st: usize, l: usize, d: usize, minl: usize, depth: usize,
    nice: usize, hlit: i32) -> (usize, usize) {
    if depth > 1 && l < nice && l < s.len() - p && st < p && p - st <= 32768 {
        let nx = prev[st % W] as usize;
        if nx < st {
            let g = u118_find(s, prev, p, nx, l, minl, depth - 1, nice, 0, hlit);
            if g.1 != 0 { return g; }
        }
    }
    (l, d)
}

// Compare two cheap heads before assigning the residual main-search budget.
// The q peek observes exactly the head that its next insertion will return.
// It does not mutate either hash table and is not a retained query snapshot.
#[inline(always)]
pub fn d1_current<const H: usize, const W: usize>(s: &[u8], head: &[u32; H],
    prev: &[u32; W], p: usize, st: usize, mask: u32, minl: usize,
    depth: usize, lazy: usize, nice: usize, hlit: i32, mode: usize) -> (usize, usize) {
    if mode != 0 || depth != 12 || lazy != 64 {
        return u118_find(s, prev, p, st, 0, minl, depth, nice, u118_MAIN_GM, hlit);
    }
    let f = u118_find(s, prev, p, st, 0, minl, 1, nice, u118_MAIN_GM, hlit);
    if f.0 >= minl && f.0 < lazy && p + 1 < s.len() - 8 {
        let q = p + 1;
        let k = (u118_be4(s, q) & mask) as u64;
        let a = (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - u118_HB)) as usize % H;
        let hq = head[a] as usize;
        // The bound is explicit so this helper needs no table-history invariant.
        if hq <= q {
            let have = f.0 - 1;
            let g = u118_find(s, prev, q, hq, have, minl, 1, nice, 1, hlit);
            if g.0 >= minl && u118_gain(g.0, g.1, hlit) > u118_gain(f.0, f.1, hlit) {
                return f;
            }
        }
    }
    d1_continue(s, prev, p, st, f.0, f.1, minl, depth, nice, hlit)
}

// Only a shallow lazy winner receives a residual main budget. The comparison
// itself stays the original gain rule; a losing shallow head costs no deep walk.
#[inline(always)]
pub fn d1_lazy<const W: usize>(s: &[u8], prev: &[u32; W], q: usize,
    st: usize, have: usize, minl: usize, ldep: usize, nice: usize,
    hlit: i32, l: usize, d: usize, lazy: usize, mode: usize) -> (usize, usize) {
    let g = u118_find(s, prev, q, st, have, minl, ldep, nice, 1, hlit);
    if mode == 0 && lazy == 64 && ldep == 1 && g.0 >= minl &&
       u118_gain(g.0, g.1, hlit) > u118_gain(l, d, hlit) {
        let h = d1_continue(s, prev, q, st, g.0, g.1, minl, 12, nice, hlit);
        if u118_gain(h.0, h.1, hlit) > u118_gain(g.0, g.1, hlit) { return h; }
    }
    g
}
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, data):
    path.write_bytes((json.dumps(data, indent=2, ensure_ascii=False) + '\n').encode())


def source():
    raw = (BASE / 'parse.rs').read_bytes()
    assert sha(raw) == RUST
    def edit(s):
        s = HELP.once(s,
            'let f = u118_find(input, &prev, p, hc, 0, minl, depth, nice, u118_MAIN_GM, hlit);',
            'let f = d1_current(input, &head, &prev, p, hc, mask, minl, depth, lazy, nice, hlit, L2);')
        return HELP.once(s,
            'let g = u118_find(input, &prev, q, hq, have, minl, ldep, nice, 1, hlit);',
            'let g = d1_lazy(input, &prev, q, hq, have, minl, ldep, nice, hlit, l, d, lazy, L2);')
    return (HELP.edit_fn(raw.decode(), 'u118_run<', edit) + EXTRA).encode()


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    path = ROOT / 'candidates' / NAME
    assert not path.exists(), path
    path.mkdir()
    raw = source()
    lean = (BASE / 'Parse.lean').read_bytes()
    assert sha(lean) == LEAN
    (path / 'parse.rs').write_bytes(raw)
    (path / 'Parse.lean').write_bytes(lean)
    hashes = {'parse.rs': sha(raw), 'Parse.lean': sha(lean)}
    dump(path / 'manifest.json', {
        'candidate': NAME, 'parent': 'references/round26-public-658', 'hashes': hashes,
        'attribution': {'source_receipt': 'references/round26-public-658/source-receipt.json',
                        'author_hotkey': '5G3YLL7PuDhRBoVoDBYKhAfTxFM4EouSDiYuFXeeWciNRzyK'},
        'mechanism': 'U118 row9 only: first probe current head; before residual search, read-only peek next-position head using original lazy gain. If next head wins, defer current remainder; original lazy winner then receives residual depth11. Otherwise finish current depth11. No persistent metadata or table-write change.',
        'difference': 'A8 added lazy search after full current search. D1 avoids full current search on a shallow-next-head win, reallocating that budget to the selected next start. Unlike A21 proposed one-shot choice, continuous original lazy loop remains. Unlike C4, lazy decisions and exact matching remain.',
        'risks': ['Shallow comparison can discard a uniquely valuable deeper current match.',
                  'Extra peek and repeated shallow-next search can outweigh saved current search.',
                  'New lazy winner deepening may itself be superseded by later lazy iterations.',
                  'Longer remaining match does not guarantee better whole-stream compression.'],
        'proof_status': 'PARENT_SCAFFOLD_ONLY. Three new helper specs must return existing FoundAt/bounds. Main/lazy loop state shape intentionally unchanged. Exact extraction and full gate NOT_RUN.',
        'measurement_status': 'Rust native compile, finite decode, public originalencoder and originalprotocol timing UNKNOWN. One actual originalprotocol screen required before route promotion or pause; counts are explanatory only.',
        'formal_submission_sent': False})
    entry = {'name': NAME, 'path': path.relative_to(ROOT).as_posix(), 'control': False,
             'anchor': 'public658', 'comparison_baseline': 'public658',
             'native_decode_reference': 'public658', 'hashes': hashes}
    dump(OUT / 'd1-entry.json', entry)
    print(json.dumps(entry, indent=2))


if __name__ == '__main__':
    main()
