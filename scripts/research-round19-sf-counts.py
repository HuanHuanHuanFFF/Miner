"""Untimed opportunity count for sharing SF length queries across distance choices."""
from pathlib import Path
import hashlib
import importlib.util
import json
import os
import subprocess
from round4 import ROOT, validate


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = validate(os.environ['ROUND4_SPEC'])
    entry = next(e for e in spec['entries'] if e['name'] == 'base603')
    source = ROOT / entry['path'] / 'parse.rs'
    raw = source.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == entry['hashes']['parse.rs']
    text = raw.decode()
    marker = 'let end=q9_get(starts,i.wrapping_add(1)) as usize;'
    assert text.count(marker) == 1
    observation = '''
  let mut probe=k;let mut total=0usize;let mut longest=0usize;
  while probe<end {let l=SFlen(q9_get(items,probe));total+=l;longest=longest.max(l);probe+=1;}
  r19_hit(end.saturating_sub(k).min(4),1);r19_hit(5,total as u64);r19_hit(6,longest as u64);
'''
    text = text.replace(marker, marker + observation) + '''
use std::sync::atomic::{AtomicU64,Ordering};
static R19_COUNTS:[AtomicU64;7]=[const{AtomicU64::new(0)};7];
fn r19_hit(i:usize,n:u64){R19_COUNTS[i].fetch_add(n,Ordering::Relaxed);}
pub fn r19_take()->[u64;7]{std::array::from_fn(|i|R19_COUNTS[i].swap(0,Ordering::Relaxed))}
'''
    build = Path(os.environ['RUNNER_TEMP']) / 'r19-count-build'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r19-sf-counts'
    out.mkdir(parents=True)
    observed = build / 'observed.rs'
    observed.write_text(text)
    sp = importlib.util.spec_from_file_location('h', ROOT / 'scripts/research-round13-counts.py')
    h = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(h)
    harness = h.HARNESS.replace('FROZEN', str(source)).replace('OBSERVED', str(observed)).replace('observed::r13_take()', 'observed::r19_take()').replace('R13_COUNT', 'R19_COUNT')
    driver = build / 'driver.rs'
    driver.write_text(harness)
    binary = build / 'driver'
    c = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], capture_output=True, text=True, timeout=240)
    (out / 'compile.log').write_text(c.stdout + c.stderr)
    assert c.returncode == 0
    corpus = Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1'
    r = subprocess.run([str(binary), str(corpus)], capture_output=True, text=True, timeout=480)
    (out / 'run.log').write_text(r.stdout + r.stderr)
    assert r.returncode == 0
    rows = []
    for line in r.stdout.splitlines():
        if line.startswith('R19_COUNT '):
            _, name, size, *values = line.split()
            v = list(map(int, values))
            assert len(v) == 7
            rows.append({'file': name, 'raw_bytes': int(size), 'match_count_histogram': v[:5], 'sum_candidate_lengths': v[5], 'sum_longest_length': v[6]})
    assert len(rows) == 28
    totals = {'match_count_histogram': [sum(row['match_count_histogram'][i] for row in rows) for i in range(5)],
              'sum_candidate_lengths': sum(row['sum_candidate_lengths'] for row in rows),
              'sum_longest_length': sum(row['sum_longest_length'] for row in rows)}
    result = {'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'source_hashes': entry['hashes'],
        'observer_sha256': hashlib.sha256(text.encode()).hexdigest(), 'status': 'VERIFIED_UNTIMED_COUNTER_TOKEN_AND_DECODE_EQUAL',
        'rows': rows, 'totals': totals, 'scope': 'Duplicate length-search coverage only; original query uses grouped prices and RMQ, so scalar coverage is not expected time gain. Use count frequency to accept or reject a shared-prefix design.'}
    (out / 'counts.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(totals))


if __name__ == '__main__':
    main()
