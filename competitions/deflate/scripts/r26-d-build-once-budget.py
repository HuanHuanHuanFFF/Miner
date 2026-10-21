"""D2: consume a transferred D1 residual budget once, using the existing go state."""
from pathlib import Path
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/extension90m/route-d'
BASE = ROOT / 'candidates/r26-d-658-selective-depth'
NAME = 'r26-d-658-once-budget'
HELP = importlib.import_module('r26-a-rep-shadow')
D1_SHA = 'f6c7f97f9fb275d5a27ff4a52d02f065bb9c4cfd39e73e311c5a7f5a3ea8e0a8'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, data):
    path.write_bytes((json.dumps(data, indent=2, ensure_ascii=False) + '\n').encode())


def source():
    raw = (BASE / 'parse.rs').read_bytes()
    assert sha(raw) == D1_SHA
    s = raw.decode().replace('d1_continue', 'd2_continue').replace('d1_current', 'd2_current').replace('d1_lazy', 'd2_lazy')
    def current(f):
        f = HELP.once(f, 'mode: usize) -> (usize, usize)', 'mode: usize) -> (usize, usize, u32)')
        f = HELP.once(f,
            'return u118_find(s, prev, p, st, 0, minl, depth, nice, u118_MAIN_GM, hlit);',
            'let f = u118_find(s, prev, p, st, 0, minl, depth, nice, u118_MAIN_GM, hlit);\n        return (f.0, f.1, 0);')
        f = HELP.once(f, 'return f;', 'return (f.0, f.1, 1);')
        return HELP.once(f,
            '    d2_continue(s, prev, p, st, f.0, f.1, minl, depth, nice, hlit)',
            '    let h = d2_continue(s, prev, p, st, f.0, f.1, minl, depth, nice, hlit);\n    (h.0, h.1, 0)')
    s = HELP.edit_fn(s, 'd2_current<', current)
    def lazy(f):
        f = HELP.once(f, 'lazy: usize, mode: usize)', 'lazy: usize, mode: usize, budget: u32)')
        return HELP.once(f, 'if mode == 0 && lazy == 64', 'if budget == 2 && mode == 0 && lazy == 64')
    s = HELP.edit_fn(s, 'd2_lazy<', lazy)
    def run(f):
        f = HELP.once(f, 'let mut go = 1u32;',
            '// D2: 2 owns one deferred residual budget; 1 is ordinary shallow lazy.\n                let mut go = if f.2 == 1 { 2u32 } else { 1u32 };')
        f = HELP.once(f, 'while go == 1 && l < lazy', 'while go > 0 && l < lazy')
        return HELP.once(f,
            'let g = d2_lazy(input, &prev, q, hq, have, minl, ldep, nice, hlit, l, d, lazy, L2);',
            'let g = d2_lazy(input, &prev, q, hq, have, minl, ldep, nice, hlit, l, d, lazy, L2, go);\n                    // Consume the budget at the first attempted lazy step, even if rejected.\n                    go = 1;')
    return HELP.edit_fn(s, 'u118_run<', run).encode()


def main():
    target = ROOT / 'candidates' / NAME
    assert not target.exists(), target
    target.mkdir()
    rust = source()
    lean = (BASE / 'Parse.lean').read_bytes()
    (target / 'parse.rs').write_bytes(rust)
    (target / 'Parse.lean').write_bytes(lean)
    hashes = {'parse.rs': sha(rust), 'Parse.lean': sha(lean)}
    manifest = json.loads((BASE / 'manifest.json').read_bytes())
    manifest.update(candidate=NAME, parent='references/round26-public-658',
        direct_parent='candidates/r26-d-658-selective-depth', hashes=hashes,
        mechanism='D1 current helper returns whether current residual depth was deferred. Reuse existing lazy go state:2 owns one residual budget,1 ordinary shallow,0 stopped. Only budget2 lazy may call residual depth11; resetgo to1 immediately after first lazy call. Continuous lazy thereafter uses original depth1.',
        difference='D1 gave every shallow lazy winner residual11 even when current had already completed its residual search or an earlier lazy had consumed it. D2 gates exactly this added work with the originating current deferral; no new depth/threshold values and no new persistent table or lazy loop state tuple.',
        risks=['The deferral can still discard a better deep current match.',
               'Peek and repeated shallow evaluation remain additional costs.',
               'One nominal residual budget does not guarantee equal actual chain work or elapsed time.',
               'Ordinary shallow lazy may later supersede the one deepened winner.'],
        proof_status='PARENT_SCAFFOLD_ONLY. Need triple result d2_current spec and budget argument d2_lazy spec. Existing go loop variable reused; guard changes equality1 topositive and control resets1. Exact extraction/fullgate NOT_RUN.',
        measurement_status='D1 real screen negative triggered this specific work-budget correction. D2 compile/decode/publicquality/time UNKNOWN; actual originalprotocol screen required before promotion or pause.')
    dump(target / 'manifest.json', manifest)
    entry = json.loads((OUT / 'd1-entry.json').read_bytes())
    entry.update(name=NAME, path=target.relative_to(ROOT).as_posix(), hashes=hashes)
    dump(OUT / 'd2-entry.json', entry)
    print(json.dumps(entry, indent=2))


if __name__ == '__main__':
    main()
