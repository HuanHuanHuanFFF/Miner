"""Observe normal-chain consumers and lazy rejection costs on frozen A8 only."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import sys

ROOT = Path(__file__).resolve().parents[1]
BASE = importlib.import_module('r26-a-lazy-chain-counts')
UTIL = importlib.import_module('research-round25-len3-price')
NAME = BASE.NAME
RUST = BASE.RUST
EXPECTED = 'evidence/round26/38181265447/quality-a8-native/diagnostics/r13-encoder/encoder.json'
EXPECTED_SHA = 'c0c25078d27b7a7abe3759e3a7bbafd8fb001cd8eb465cabb41fc3544512d860'
OLD_COUNTS = 'evidence/round26/38181265447/quality-a8-native/diagnostics/r26-a-lazy-chain/receipt.json'
OLD_COUNTS_SHA = '28318de738421813eac190b31f44b8ff25f1fa2480b23f1658817b034b8628fb'
FIELDS = ['normal_queries', 'normal_first_calls', 'normal_first_wins', 'normal_first_extra',
          'normal_second_calls', 'normal_second_wins', 'normal_second_extra',
          'normal_final_head', 'normal_final_first', 'normal_final_second',
          'normal_surviving_head', 'normal_surviving_first', 'normal_surviving_second',
          'normal_surviving_first_extra', 'normal_surviving_second_extra', 'normal_replaced_by_lazy',
          'lazy_accepted_first', 'lazy_accepted_second', 'lazy_ancestor_calls',
          'lazy_near_reject', 'lazy_window_reject', 'lazy_first4_reject', 'lazy_end_reject',
          'lazy_tail_reject', 'lazy_xlen_entered', 'lazy_prefix_known_before_tail',
          'lazy_prefix_known_but_entered_xlen', 'lazy_long_reject_after_xlen', 'lazy_valid']


def sha(raw): return hashlib.sha256(raw).hexdigest()
def dump(path, value): path.write_bytes((json.dumps(value, indent=2) + '\n').encode())
def once(text, old, new): return BASE.once(text, old, new)


def instrument(raw):
    text = BASE.instrument(raw).decode()
    a = text.index('pub fn r26_lc_probe(')
    b = text.index('#[inline(always)]\npub fn pc_run1c', a)
    helper = text[a:b]
    helper = once(helper, '    let original = best;', '    let original = best;\n    let mut r26_origin = 0usize;')
    helper = once(helper, 'pc_probe_lazy(s, c2, w2, q, l)', 'r26_bu_lazy(s, c2, w2, q, l)')
    helper = once(helper, 'pc_probe_lazy(s, c3, w3, q, l)', 'r26_bu_lazy(s, c3, w3, q, l)')
    helper = once(helper, '            best = g;', '            r26_origin = 1;\n            best = g;')
    helper = once(helper, '                    best = h;', '                    r26_origin = 2;\n                    best = h;')
    helper = once(helper, '    best\n}', '    R26_BU_LAST.store(r26_origin as u64, Ordering::Relaxed);\n    best\n}')
    text = text[:a] + helper + text[b:]
    a = text.index('pub fn pc_run1c<const H: usize>')
    b = text.index('\n#[inline(always)] pub fn pc_put_match_checked', a)
    body = text[a:b]
    original = '                let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);'
    extra = '''
                // Pure observer replay of the first normal link, not a new parse choice.
                let r26_first = pc_f_try(input, c, cl, p, f.0, f.1, minl);
                let r26_origin = if g.0 == f.0 { 0usize } else if g == r26_first { 1usize } else { 2usize };
                assert!(r26_first.0 >= f.0 && g.0 >= r26_first.0);
                r26_bu_hit(0, 1); r26_bu_hit(1, 1);
                r26_bu_hit(2, (r26_first.0 > f.0) as u64);
                r26_bu_hit(3, (r26_first.0 - f.0) as u64);
                r26_bu_hit(4, (dp >= 2 && cl < c) as u64);
                r26_bu_hit(5, (g.0 > r26_first.0) as u64);
                r26_bu_hit(6, (g.0 - r26_first.0) as u64);
                r26_bu_hit(7 + r26_origin, 1);
                let r26_original_p = p;
                let r26_normal_length = g.0;'''
    body = once(body, original, original + extra)
    marker = '                    r26_lc_hit(14, (new_accept && g != old_offer) as u64);'
    extra = '''
                    if new_accept {
                        let source = R26_BU_LAST.load(Ordering::Relaxed) as usize;
                        if source > 0 { assert!(source <= 2); r26_bu_hit(15 + source, 1); }
                    }'''
    body = once(body, marker, marker + extra)
    marker = '                let e = p + l;'
    extra = '''                if p == r26_original_p {
                    assert_eq!(l, r26_normal_length);
                    r26_bu_hit(10 + r26_origin, 1);
                    if r26_origin == 1 { r26_bu_hit(13, (l - f.0) as u64); }
                    if r26_origin == 2 { r26_bu_hit(14, (l - r26_first.0) as u64); }
                } else { r26_bu_hit(15, 1); }
'''
    body = once(body, marker, extra + marker)
    text = text[:a] + body + text[b:]
    extra = r'''
static R26_BU_COUNTS: [AtomicU64; 29] = [const { AtomicU64::new(0) }; 29];
static R26_BU_LAST: AtomicU64 = AtomicU64::new(0);
fn r26_bu_hit(i: usize, n: u64) { R26_BU_COUNTS[i].fetch_add(n, Ordering::Relaxed); }
pub fn r26_bu_take() -> [u64; 29] { std::array::from_fn(|i| R26_BU_COUNTS[i].swap(0, Ordering::Relaxed)) }
fn r26_bu_lazy(s: &[u8], c: usize, cw: u64, q: usize, l: usize) -> (usize, usize) {
    let result = pc_probe_lazy(s, c, cw, q, l);
    r26_bu_hit(18, 1);
    let d = q.wrapping_sub(c);
    let lo = pc_lazy_lo(l);
    let x = cw ^ pc_be8(s, q);
    if d >= 2 && d <= 8 && s.len() != 500000 { r26_bu_hit(19, 1); }
    else if d.wrapping_sub(1) >= 32768 { r26_bu_hit(20, 1); }
    else if (x >> 32) != 0 { r26_bu_hit(21, 1); }
    else if q + lo >= s.len() { r26_bu_hit(22, 1); }
    else {
        // A mismatch within the already loaded word can prove m<=lo.
        let known = x != 0 && (x.leading_zeros() / 8) as usize <= lo;
        r26_bu_hit(25, known as u64);
        if s[c + lo] != s[q + lo] { r26_bu_hit(23, 1); }
        else {
            r26_bu_hit(24, 1);
            if known { assert_eq!(result, (0, 0)); r26_bu_hit(26, 1); }
            else if result.0 == 0 { r26_bu_hit(27, 1); }
            else { r26_bu_hit(28, 1); }
        }
    }
    result
}
'''
    return (text + extra).encode()


def preflight(spec=None):
    raw = (ROOT / 'candidates' / NAME / 'parse.rs').read_bytes()
    assert sha(raw) == RUST
    native = (ROOT / EXPECTED).read_bytes(); assert sha(native) == EXPECTED_SHA
    expected = json.loads(native)
    assert expected['source_hashes'][NAME]['parse.rs'] == RUST
    assert len([r for r in expected['rows'] if r['candidate'] == NAME]) == 28
    assert sha((ROOT / OLD_COUNTS).read_bytes()) == OLD_COUNTS_SHA
    observer = instrument(raw)
    if spec is not None:
        assert spec['r26_mode'] == 'standard'
        assert next(e for e in spec['entries'] if e['name'] == NAME)['hashes']['parse.rs'] == RUST
    return {'status': 'VERIFIED_FROZEN_OBSERVER_GENERATION_AND_EXPECTED_NATIVE_DEPENDENCY_NOT_RUNTIME',
            'rust_sha256': RUST, 'observer_sha256': sha(observer), 'expected_native_sha256': EXPECTED_SHA, 'old_counts_sha256': OLD_COUNTS_SHA,
            'extra_compile_timeout_s': 100, 'extra_run_timeout_s': 60, 'outer_cost_cap_seconds': 180}


def run():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    from round4 import validate
    spec = validate(os.environ['ROUND4_SPEC']); checked = preflight(spec)
    build = Path(os.environ['RUNNER_TEMP']) / 'r26-a-pc-budget-build'; build.mkdir(); spool = build / 'spool'; spool.mkdir()
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r26-a-pc-budget'; out.mkdir(parents=True)
    frozen = ROOT / 'candidates' / NAME / 'parse.rs'; observer = build / 'observer.rs'
    raw = instrument(frozen.read_bytes()); observer.write_bytes(raw); (out / 'observer.rs').write_bytes(raw)
    harness = BASE.HARNESS.replace('let counts=observed::r26_lc_take();', 'let counts=observed::r26_lc_take();let budget=observed::r26_bu_take();')
    harness = harness.replace('for x in counts{print!(" {}",x)}println!();', 'for x in counts{print!(" {}",x)}for x in budget{print!(" {}",x)}println!();')
    harness = harness.replace('FROZEN', json.dumps(str(frozen))).replace('OBSERVED', json.dumps(str(observer)))
    driver = build / 'main.rs'; driver.write_text(harness); (out / 'harness.rs').write_text(harness)
    result = {'status': 'STARTED_UNTIMED_FROZEN_A8_BUDGET_OBSERVER', 'run_id': os.environ['GITHUB_RUN_ID'],
              'git_sha': os.environ['GITHUB_SHA'], 'batch': os.environ['ROUND4_SPEC'], **checked,
              'harness_sha256': sha(harness.encode()),
              'scope': 'Same A8 trajectory only. Normal survival is through lazy before fold, not byte savings or a counterfactual budget transfer. Extra observer probes/atomics never enter timing candidates.'}
    result['status'] = 'STARTED_UNTIMED_FROZEN_A8_BUDGET_OBSERVER'
    report = out / 'receipt.json'; dump(report, result)
    try:
        binary = build / 'check'
        UTIL.captured(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], out / 'compile.log', 100)
        corpus = Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1'
        process = UTIL.captured([str(binary), str(corpus), str(spool)], out / 'run.log', 60)
        native = json.loads((ROOT / EXPECTED).read_bytes()); expected = {r['file']: r for r in native['rows'] if r['candidate'] == NAME}
        prior_counts = {r['file']: r['counts'] for r in json.loads((ROOT / OLD_COUNTS).read_bytes())['rows']}
        rows = []
        for line in process.stdout.splitlines():
            if not line.startswith('R26_LAZY '): continue
            _, file, n, nt, *values = line.split(); assert len(values) == len(BASE.FIELDS) + len(FIELDS)
            old = dict(zip(BASE.FIELDS, map(int, values[:len(BASE.FIELDS)]))); counts = dict(zip(FIELDS, map(int, values[len(BASE.FIELDS):])))
            assert old == prior_counts[file], file
            data = (corpus / file).read_bytes(); tokens = (spool / (file + '.tokens')).read_bytes()
            assert len(data) == int(n) == expected[file]['raw_bytes'] and len(tokens) == 4 * int(nt)
            assert sha(data) == expected[file]['input_sha256'] and sha(tokens) == expected[file]['tokens_sha256']
            assert counts['normal_queries'] == counts['normal_first_calls'] == sum(counts['normal_final_' + x] for x in ['head', 'first', 'second'])
            assert counts['normal_queries'] == counts['normal_replaced_by_lazy'] + sum(counts['normal_surviving_' + x] for x in ['head', 'first', 'second'])
            assert counts['normal_second_wins'] <= counts['normal_second_calls'] <= counts['normal_queries']
            assert counts['lazy_ancestor_calls'] == old['first_descending'] + old['second_descending']
            assert counts['lazy_accepted_first'] + counts['lazy_accepted_second'] == old['different_accepted_offer']
            assert counts['lazy_ancestor_calls'] == sum(counts['lazy_' + x] for x in ['near_reject', 'window_reject', 'first4_reject', 'end_reject', 'tail_reject', 'xlen_entered'])
            assert counts['lazy_xlen_entered'] == sum(counts['lazy_' + x] for x in ['prefix_known_but_entered_xlen', 'long_reject_after_xlen', 'valid'])
            assert counts['lazy_valid'] == old['first_valid'] + old['second_valid']
            rows.append({'file': file, 'input_sha256': sha(data), 'tokens_sha256': sha(tokens), 'old_counts': old, 'counts': counts})
        assert len(rows) == 28
        result.update(status='VERIFIED_FROZEN_NATIVE_TOKENS_DECODE_AND_CONSUMER_ACCOUNTING', rows=rows,
                      totals={f: sum(r['counts'][f] for r in rows) for f in FIELDS}, old_totals={f: sum(r['old_counts'][f] for r in rows) for f in BASE.FIELDS})
    except Exception as exc:
        result.update(status='FAILED_OR_INCOMPLETE_PC_BUDGET_OBSERVER', error_type=type(exc).__name__, error=str(exc)); dump(report, result); raise
    dump(report, result); print(json.dumps({'status': result['status'], 'totals': result['totals']}, indent=2))


if __name__ == '__main__':
    if sys.argv[1:] == ['--self-check']:
        result = preflight(); dump(ROOT / 'evidence/round26/route-a/pc-budget-counts-preflight.json', result); print(json.dumps(result, indent=2))
    else: run()
