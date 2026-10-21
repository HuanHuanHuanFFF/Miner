"""Untimed counts on the exact A8 consumer, with frozen-token and decode checks."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
NAME = 'r26-a-641-lazy-chain'
RUST = '29eeab8a83b7c22d56d5c28986198b735ced2ee3199aebf71164b5198eb71ec4'
UTIL = importlib.import_module('research-round25-len3-price')
BUILD = importlib.import_module('r26-a-build-lazy-chain')
FIELDS = ['queries', 'head_valid', 'first_read', 'first_descending', 'first_valid', 'first_replaced',
          'second_read', 'second_descending', 'second_valid', 'second_replaced', 'changed_offer',
          'accepted_lazy', 'rejected_lazy', 'newly_accepted_lazy', 'different_accepted_offer']


def sha(raw): return hashlib.sha256(raw).hexdigest()
def dump(path, value): path.write_bytes((json.dumps(value, indent=2) + '\n').encode())
def once(text, old, new):
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def instrument(raw):
    assert sha(raw) == RUST
    text = raw.decode(); helper = BUILD.HELPER
    changed = once(helper, '    let mut best = pc_probe_lazy(s, c, cw, q, l);',
                   '    r26_lc_hit(0, 1);\n    let mut best = pc_probe_lazy(s, c, cw, q, l);\n    let original = best;\n    r26_lc_hit(1, (best.0 >= 4) as u64);')
    changed = once(changed, '    let c2 = prev[c % 32768] as usize;', '    r26_lc_hit(2, 1);\n    let c2 = prev[c % 32768] as usize;')
    changed = once(changed, '    if c2 < c {', '    if c2 < c {\n        r26_lc_hit(3, 1);')
    changed = once(changed, '        let g = pc_probe_lazy(s, c2, w2, q, l);', '        let g = pc_probe_lazy(s, c2, w2, q, l);\n        r26_lc_hit(4, (g.0 >= 4) as u64);')
    changed = once(changed, '            best = g;', '            r26_lc_hit(5, 1);\n            best = g;')
    changed = once(changed, '            let c3 = prev[c2 % 32768] as usize;', '            r26_lc_hit(6, 1);\n            let c3 = prev[c2 % 32768] as usize;')
    changed = once(changed, '            if c3 < c2 {', '            if c3 < c2 {\n                r26_lc_hit(7, 1);')
    changed = once(changed, '                let h = pc_probe_lazy(s, c3, w3, q, l);', '                let h = pc_probe_lazy(s, c3, w3, q, l);\n                r26_lc_hit(8, (h.0 >= 4) as u64);')
    changed = once(changed, '                    best = h;', '                    r26_lc_hit(9, 1);\n                    best = h;')
    changed = once(changed, '    best\n}', '    r26_lc_hit(10, (best != original) as u64);\n    best\n}')
    text = once(text, helper, changed)
    call = '                    let g = r26_lc_probe(input, &prev, c2, w2, q, l, dp);'
    addition = '''
                    // Observer-only pure replay of the original head offer at this new trajectory.
                    let old_offer = pc_probe_lazy(input, c2, w2, q, l);
                    let new_accept = g.0 >= 4 && pc_gain(g.0, g.1) > pc_gain(l, d);
                    let old_accept = old_offer.0 >= 4 && pc_gain(old_offer.0, old_offer.1) > pc_gain(l, d);
                    r26_lc_hit(11, new_accept as u64);
                    r26_lc_hit(12, (!new_accept) as u64);
                    r26_lc_hit(13, (new_accept && !old_accept) as u64);
                    r26_lc_hit(14, (new_accept && g != old_offer) as u64);'''
    text = once(text, call, call + addition)
    counters = '''
use std::sync::atomic::{AtomicU64, Ordering};
static R26_LC_COUNTS: [AtomicU64; 15] = [const { AtomicU64::new(0) }; 15];
fn r26_lc_hit(i: usize, n: u64) { R26_LC_COUNTS[i].fetch_add(n, Ordering::Relaxed); }
pub fn r26_lc_take() -> [u64; 15] { std::array::from_fn(|i| R26_LC_COUNTS[i].swap(0, Ordering::Relaxed)) }
'''
    return (text + counters).encode()


HARNESS = r'''
#![allow(dead_code)]
#[path=FROZEN] mod frozen;
#[path=OBSERVED] mod observed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn main(){let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b,"{}",p.display());assert!(decode(&s,&b));let counts=observed::r26_lc_take();let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();print!("R26_LAZY {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
'''


def preflight(spec=None):
    source = ROOT / 'candidates' / NAME / 'parse.rs'; raw = source.read_bytes()
    assert sha(raw) == RUST and BUILD.generate()[0] == raw
    observer = instrument(raw)
    assert observer.count(b'r26_lc_probe(') == 2
    if spec is not None:
        entry = next(e for e in spec['entries'] if e['name'] == NAME)
        assert entry['hashes']['parse.rs'] == RUST and spec['native_encoder'] is True
    # The head remains eligible, strict-score replacement preserves original-head wins and ties.
    checks = 0
    for old in range(-3, 4):
        for a in range(-3, 4):
            for b in range(-3, 4):
                for present in range(8):
                    offers = [old, a, b]; best = None; chosen = None
                    for i, score in enumerate(offers):
                        if present & (1 << i) and (best is None or score > best): best = score; chosen = i
                    available = [(score, i) for i, score in enumerate(offers) if present & (1 << i)]
                    expected = min(available, key=lambda t: (-t[0], t[1])) if available else None
                    assert (best, chosen) == (expected if expected else (None, None)); checks += 1
    return {'status': 'VERIFIED_SOURCE_REVERSAL_OBSERVER_GENERATION_AND_FINITE_SELECTION_ONLY', 'rust_sha256': RUST,
            'observer_sha256': sha(observer), 'selection_cases': checks, 'native': 'NOT_RUN', 'proof': 'NOT_RUN'}


def run():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    from round4 import validate
    spec = validate(os.environ['ROUND4_SPEC']); checked = preflight(spec)
    build = Path(os.environ['RUNNER_TEMP']) / 'r26-a-lazy-chain-build'; build.mkdir(); spool = build / 'spool'; spool.mkdir()
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r26-a-lazy-chain'; out.mkdir(parents=True)
    frozen = ROOT / 'candidates' / NAME / 'parse.rs'; observer = build / 'observer.rs'
    raw = instrument(frozen.read_bytes()); observer.write_bytes(raw); (out / 'observer.rs').write_bytes(raw)
    harness = HARNESS.replace('FROZEN', json.dumps(str(frozen))).replace('OBSERVED', json.dumps(str(observer)))
    driver = build / 'main.rs'; driver.write_text(harness); (out / 'harness.rs').write_text(harness)
    result = {'status': 'STARTED_UNTIMED_A8_COUNTS', 'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'],
              'batch': os.environ['ROUND4_SPEC'], 'rust_sha256': RUST, 'observer_sha256': sha(raw), 'harness_sha256': sha(harness.encode()),
              'scope': 'Counts follow the candidate trajectory. Original head offer is replayed at those positions, not along the parent trajectory. Observer has extra atomics and pure probes; no performance claim.'}
    report = out / 'receipt.json'; dump(report, result)
    try:
        binary = build / 'check'
        UTIL.captured(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], out / 'compile.log', 240)
        corpus = Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1'
        process = UTIL.captured([str(binary), str(corpus), str(spool)], out / 'run.log', 240)
        encoder = out.parent / 'r13-encoder/encoder.json'; native = json.loads(encoder.read_bytes())
        expected = {r['file']: r for r in native['rows'] if r['candidate'] == NAME}; assert len(expected) == 28
        rows = []
        for line in process.stdout.splitlines():
            if not line.startswith('R26_LAZY '): continue
            _, file, n, nt, *values = line.split(); assert len(values) == len(FIELDS)
            data = (corpus / file).read_bytes(); tokens = (spool / (file + '.tokens')).read_bytes()
            counts = dict(zip(FIELDS, map(int, values)))
            assert len(data) == int(n) and len(tokens) == 4 * int(nt)
            assert sha(data) == expected[file]['input_sha256'] and sha(tokens) == expected[file]['tokens_sha256']
            assert counts['queries'] == counts['first_read'] == counts['accepted_lazy'] + counts['rejected_lazy']
            assert counts['first_replaced'] <= counts['first_valid'] <= counts['first_descending'] <= counts['first_read']
            assert counts['second_replaced'] <= counts['second_valid'] <= counts['second_descending'] <= counts['second_read'] <= counts['first_descending']
            assert counts['newly_accepted_lazy'] <= counts['different_accepted_offer'] <= counts['accepted_lazy']
            assert counts['different_accepted_offer'] <= counts['changed_offer'] <= counts['first_replaced'] + counts['second_replaced']
            rows.append({'file': file, 'raw_bytes': len(data), 'input_sha256': sha(data), 'tokens': int(nt), 'tokens_sha256': sha(tokens), 'counts': counts})
        assert len(rows) == 28 and sum(r['raw_bytes'] for r in rows) == 15930000
        result.update(status='VERIFIED_FROZEN_OBSERVED_NATIVE_TOKEN_IDENTITY_AND_DECODE', native_encoder_sha256=sha(encoder.read_bytes()),
                      rows=rows, totals={f: sum(r['counts'][f] for r in rows) for f in FIELDS})
    except Exception as exc:
        result.update(status='FAILED_OR_INCOMPLETE_A8_COUNTS', error_type=type(exc).__name__, error=str(exc)); dump(report, result); raise
    dump(report, result); print(json.dumps({'status': result['status'], 'totals': result['totals']}, indent=2))


if __name__ == '__main__':
    if sys.argv[1:] == ['--self-check']:
        result = preflight(); dump(ROOT / 'evidence/round26/route-a/lazy-chain-counts-preflight.json', result); print(json.dumps(result, indent=2))
    else: run()
