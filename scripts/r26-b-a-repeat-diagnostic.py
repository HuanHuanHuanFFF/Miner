"""Original #552 smoothed-Huffman A trajectory: full state repeats and complete guard cost."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import re
import subprocess

ROOT = Path(__file__).resolve().parents[1]
EXPECTED = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
FIELDS = ['a_engine_calls', 'full_dp_calls', 'full_dp_positions', 'same_prices_calls',
          'same_interval_calls', 'eligible_calls', 'eligible_positions', 'full_dp_ns',
          'eligible_dp_ns', 'price_comparison_and_copy_ns', 'price_words_compared_and_copied',
          'idempotence_checks', 'idempotence_snapshot_and_comparison_ns',
          'sample_parent_calls', 'sample_parent_ns', 'sample_invalidations',
          'a_engine_inclusive_ns', 'parse_inclusive_ns', 'adjacent_full_calls',
          'adjacent_same_interval_positions', 'adjacent_full_positions',
          'huff_input_full_calls', 'entropy_input_full_calls']
CONTEXT_FIELDS = ['input_bytes', 'depth', 'skip', 'first_passes', 'first_sampled',
                  'later_passes', 'later_sampled_raw', 'block_start', 'initial_block_end',
                  'passes', 'sampled', 'rotation_bytes']
FULLKEY_FIELDS = ['block_start', 'block_end', 'pass_index', 'passes', 'sampled',
                  'prior_full_valid', 'prior_same_interval', 'same_prices', 'eligible',
                  'incoming_huff_prices', 'original_full_dp_ns']

STATE = '''    let mut r26_lit=[0u32;256];let mut r26_lc=[0u32;512];let mut r26_dc=[0u32;32];
    let mut r26_valid=false;let mut r26_p0=0usize;let mut r26_pe=0usize;
'''

FULL = '''                let r26_compare_clock=std::time::Instant::now();
                let mut r26_prices=r26_valid;let mut r26_j=0usize;
                while r26_j<256 {if r26_lit[r26_j]!=lit[r26_j]{r26_prices=false;}r26_lit[r26_j]=lit[r26_j];r26_j+=1;}
                r26_j=0;while r26_j<512 {if r26_lc[r26_j]!=lc[r26_j]{r26_prices=false;}r26_lc[r26_j]=lc[r26_j];r26_j+=1;}
                r26_j=0;while r26_j<32 {if r26_dc[r26_j]!=dc[r26_j]{r26_prices=false;}r26_dc[r26_j]=dc[r26_j];r26_j+=1;}
                let r26_interval=r26_valid&&r26_p0==p0&&r26_pe==pe;
                let r26_same=r26_prices&&r26_interval;
                r26_a_hit(9,r26_compare_clock.elapsed().as_nanos()as u64);
                r26_a_hit(1,1);r26_a_hit(2,(pe-p0)as u64);r26_a_hit(3,r26_prices as u64);r26_a_hit(4,r26_interval as u64);
                r26_a_hit(5,r26_same as u64);if r26_same{r26_a_hit(6,(pe-p0)as u64);}r26_a_hit(10,800);
                r26_a_hit(18,r26_valid as u64);if r26_valid{r26_a_hit(20,(pe-p0)as u64);}
                if r26_interval{r26_a_hit(19,(pe-p0)as u64);}r26_a_hit(if k>sampled{21}else{22},1);
                let r26_snapshot_clock=std::time::Instant::now();
                let r26_old_cost=if r26_same{cost.clone()}else{Vec::new()};
                let r26_old_ch=if r26_same{ch.clone()}else{Vec::new()};
                r26_a_hit(12,r26_snapshot_clock.elapsed().as_nanos()as u64);
                let r26_dp_clock=std::time::Instant::now();
                a_dp_pass(input, &mp, &mb, p0, pe, &lit, &lc, &dc, &mut cost, ch);
                let r26_dp_ns=r26_dp_clock.elapsed().as_nanos()as u64;r26_a_hit(7,r26_dp_ns);
                if r26_same {
                    r26_a_hit(8,r26_dp_ns);r26_a_hit(11,1);
                    let r26_check_clock=std::time::Instant::now();
                    assert_eq!(cost.as_slice(),r26_old_cost.as_slice());assert_eq!(ch.as_slice(),r26_old_ch.as_slice());
                    r26_a_hit(12,r26_check_clock.elapsed().as_nanos()as u64);
                }
                println!("R26_A_FULLKEY {} {} {} {} {} {} {} {} {} {} {}",p0,pe,k,passes,sampled,r26_valid as u64,r26_interval as u64,r26_prices as u64,r26_same as u64,(k>sampled)as u64,r26_dp_ns);
                r26_valid=true;r26_p0=p0;r26_pe=pe;
'''

COUNTER = '''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_A_REPEAT:[AtomicU64;23]=[const{AtomicU64::new(0)};23];
fn r26_a_hit(i:usize,n:u64){R26_A_REPEAT[i].fetch_add(n,Ordering::Relaxed);}
pub fn r26_a_take()->[u64;23]{std::array::from_fn(|i|R26_A_REPEAT[i].swap(0,Ordering::Relaxed))}
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw) == EXPECTED
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    text = raw.decode()
    old = fn(text, 'a_engine')
    part = old
    marker = '    while p0 < n && mp.len() == n + 1 && cost.len() == n + 1 && ch.len() == n {'
    assert part.count(marker) == 1
    part = part.replace(marker, STATE + marker, 1)
    block = '        while k < passes {'
    assert part.count(block) == 1
    part = part.replace(block, '        println!("R26_A_CONTEXT {} {} {} {} {} {} {} {} {} {} {} {}",n,depth,skip,first_passes,fspass,passes_k,spass,p0,pe,passes,sampled,rot);\n' + block, 1)
    sample = '                let r = a_sample_pass(input, &mp, &mb, ps, pe, &lit, &lc, &dc, &mut cost, ch, &mut lf, &mut df);'
    observed_sample = '''                r26_a_hit(13,1);if r26_valid{r26_a_hit(15,1);}r26_valid=false;
                let r26_sample_clock=std::time::Instant::now();
''' + sample + '\n                r26_a_hit(14,r26_sample_clock.elapsed().as_nanos()as u64);'
    assert part.count(sample) == 1
    part = part.replace(sample, observed_sample, 1)
    call = '                a_dp_pass(input, &mp, &mb, p0, pe, &lit, &lc, &dc, &mut cost, ch);'
    assert part.count(call) == 1
    part = part.replace(call, FULL.rstrip(), 1)
    # State is local to one original parent invocation: n/input/mp/mb and all
    # engine knobs/initial seed model are fixed. A sampled DP invalidates it.
    text = text.replace(old, part, 1)
    wrappers = []
    for name, field in [('a_engine', 16), ('parse', 17)]:
        original = fn(text, name)
        head = original.split('{', 1)[0]
        args = re.findall(r'(?:\(|,)\s*(?:mut\s+)?([A-Za-z_][A-Za-z0-9_]*)\s*:', head)
        assert len(args) == head.count(':')
        inner = 'r26_a_inner_' + name
        text = text.replace(original, original.replace('pub fn ' + name + '(', 'pub fn ' + inner + '(', 1), 1)
        hit = 'r26_a_hit(0,1);' if name == 'a_engine' else ''
        wrappers.append(head + '{' + hit + 'let r26_clock=std::time::Instant::now();let r26_result=' +
                        inner + '(' + ','.join(args) + ');r26_a_hit(' + str(field) +
                        ',r26_clock.elapsed().as_nanos()as u64);r26_result}\n')
    observed = (text + '\n' + COUNTER + '\n' + ''.join(wrappers)).encode()
    syntax = importlib.import_module('r26-b-fix-shared-cache')
    syntax.spans(observed.decode())
    return observed


def preflight(spec):
    assert spec.get('r26_b_a_repeat_counts') is True and spec.get('native_encoder') is False
    entry = next(row for row in spec['entries'] if row['name'] == 'public552')
    raw = (ROOT / entry['path'] / 'parse.rs').read_bytes()
    assert entry['hashes']['parse.rs'] == EXPECTED
    observed = instrument(raw)
    importlib.import_module('research-round18-functions').instrument(raw, spec['r15_profile_functions'])
    return {'status': 'VERIFIED_ORIGINAL552_FULLSTATE_GUARD_STRUCTURE_ONLY',
            'source_sha256': EXPECTED, 'observer_sha256': sha(observed), 'fields': FIELDS,
            'context_fields': CONTEXT_FIELDS, 'full_key_fields': FULLKEY_FIELDS,
            'identity': 'Same parent invocation fixes input/match cache/knobs/seed. Exact p0,pe and all800prices; tail fixed0; sampled DP invalidates prior retained outputs.',
            'scope': 'No local Rust execution, candidate, proof or performance claim.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = importlib.import_module('round4').validate(os.environ['ROUND4_SPEC'])
    preflight(spec)
    entry = next(row for row in spec['entries'] if row['name'] == 'public552')
    frozen = ROOT / entry['path'] / 'parse.rs'
    build = Path(os.environ['RUNNER_TEMP']) / 'r26-b-a-repeat'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r26-b-a-repeat'
    out.mkdir(parents=True)
    observed = build / 'observed.rs'
    observed.write_bytes(instrument(frozen.read_bytes()))
    harness = importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN', str(frozen)).replace('OBSERVED', str(observed)).replace('observed::r13_take()', 'observed::r26_a_take()').replace('R13_COUNT', 'R26_A_REPEAT')
    driver = build / 'driver.rs'
    driver.write_text(harness)
    binary = build / 'check'
    compiled = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], capture_output=True, text=True, timeout=240)
    (out / 'compile.log').write_text(compiled.stdout + compiled.stderr)
    assert compiled.returncode == 0
    corpus = Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1'
    run = subprocess.run([str(binary), str(corpus)], capture_output=True, text=True, timeout=480)
    (out / 'run.log').write_text(run.stdout + run.stderr)
    assert run.returncode == 0
    rows, contexts, fullkeys = [], [], []
    for line in run.stdout.splitlines():
        if line.startswith('R26_A_CONTEXT '):
            values = list(map(int, line.split()[1:]));assert len(values) == len(CONTEXT_FIELDS)
            contexts.append(dict(zip(CONTEXT_FIELDS, values)));continue
        if line.startswith('R26_A_FULLKEY '):
            values = list(map(int, line.split()[1:]));assert len(values) == len(FULLKEY_FIELDS)
            fullkeys.append(dict(zip(FULLKEY_FIELDS, values)));continue
        if not line.startswith('R26_A_REPEAT '):
            continue
        _, name, size, *values = line.split()
        assert len(values) == len(FIELDS)
        data = (corpus / name).read_bytes()
        assert len(data) == int(size)
        counts = dict(zip(FIELDS, map(int, values)))
        assert len(fullkeys) == counts['full_dp_calls']
        assert sum(row['eligible'] for row in fullkeys) == counts['eligible_calls']
        assert sum(row['prior_full_valid'] for row in fullkeys) == counts['adjacent_full_calls']
        assert all(row['input_bytes'] == len(data) for row in contexts)
        rows.append({'file': name, 'raw_bytes': len(data), 'input_sha256': sha(data),
                     'counts': counts, 'block_contexts': contexts, 'full_key_trajectory': fullkeys})
        contexts, fullkeys = [], []
    assert len(rows) == 28 and sum(row['raw_bytes'] for row in rows) == 15930000
    assert not contexts and not fullkeys
    result = {
        'status': 'VERIFIED_ORIGINAL_A_TRAJECTORY_FULLSTATE_COUNTS_IDEMPOTENCE_AND_TOKEN_DECODE',
        'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'batch': os.environ['ROUND4_SPEC'],
        'source_hashes': entry['hashes'], 'observer_sha256': sha(observed.read_bytes()), 'driver_sha256': sha(driver.read_bytes()),
        'rows': rows, 'totals': {field: sum(row['counts'][field] for row in rows) for field in FIELDS},
        'identity': 'No skip performed. Full key covers parent epoch and immutable input/match cache/config/initial seed, p0/pe, all800prices, fixedtail0. Any sampled DP invalidates prior retained outputs. Eligible repeated calls compare entire before/after cost/ch buffers elementwise.',
        'scope': 'Frozen original552 versus observed552 exact token equality and independent decode on all28files. Coarse call clocks measure full/sample work and complete800word guard comparison/copy. Separate originalsource phase observer runs after this diagnostic.',
        'limits': ['Counts and instrumented nanoseconds are not originalpaired performance or a causal/achievable speedup bound.',
                   'Observer parent/parse clocks include diagnostic context printing and snapshots; originalsource coarsephase receipt is separate. FullDP clocks exclude those diagnostics.',
                   'Full cost/ch snapshot and comparison is diagnostic-only idempotence evidence, measured separately; a production skip still needs retained-output invariants and fullgate.',
                   'R18unsmoothed Z308 had0sameprices and is notretested. This observation covers552plain A with smoothed Huffman prices, not allinput convergence.',
                   'No candidate, new formalproof, admission or reward.'],
    }
    (out / 'receipt.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps(result['totals']))
    importlib.import_module('research-round18-functions').main()


if __name__ == '__main__':
    main()
