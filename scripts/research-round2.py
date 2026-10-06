"""Finite token equivalence and diagnostic probe attribution, never timing data."""
from __future__ import annotations
import hashlib
import json
import os
from pathlib import Path
import subprocess


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true'
    assert os.environ.get('GITHUB_REPOSITORY') == 'HuanHuanHuanFFF/Miner'
    workspace = Path(os.environ['GITHUB_WORKSPACE'])
    root = Path(os.environ['RUNNER_TEMP']) / 'deflate-reports'
    baseline = workspace / 'candidates/probe2/parse.rs'
    source = baseline.read_text()
    a = source.index('pub fn walk<')
    b = source.index('/// Put position', a)
    walk = source[a:b]
    walk = walk.replace('    while k > 0 {', '''    let mut visited = 0usize;
    let mut first_len = 0usize;
    while k > 0 {
        visited += 1;
        if visited == 1 { FIRST.fetch_add(1, std::sync::atomic::Ordering::Relaxed); }
        if visited == 2 {
            first_len = if bd == 0 { 0 } else { best };
            SECOND[first_len].fetch_add(1, std::sync::atomic::Ordering::Relaxed);
        }''', 1)
    walk = walk.replace('                if take == 1 {', '''                if take == 1 {
                    if visited == 2 { IMPROVED[first_len].fetch_add(1, std::sync::atomic::Ordering::Relaxed); }''', 1)
    instrumented = source[:a] + walk + source[b:] + '''
pub static FIRST: std::sync::atomic::AtomicU64 = std::sync::atomic::AtomicU64::new(0);
pub static SECOND: [std::sync::atomic::AtomicU64; 259] = [const { std::sync::atomic::AtomicU64::new(0) }; 259];
pub static IMPROVED: [std::sync::atomic::AtomicU64; 259] = [const { std::sync::atomic::AtomicU64::new(0) }; 259];
'''
    (root / 'instrumented.rs').write_text(instrumented)
    harness = '''
#[path = "CONTROL"] mod control;
#[path = "BUCKET"] mod bucket;
#[path = "INSTRUMENTED"] mod instrumented;
use std::sync::atomic::Ordering;

fn tokens(data: &[u8], parse: fn(&[u8], &mut [u32]) -> usize) -> Vec<u32> {
    let mut out = vec![0; data.len()];
    let n = parse(data, &mut out);
    assert!(n <= data.len()); out.truncate(n); out
}
fn validate(data: &[u8], ts: &[u32]) {
    let mut decoded = Vec::with_capacity(data.len());
    for &t in ts {
        if t < 256 { decoded.push(t as u8); }
        else {
            assert!(t >= 16777216);
            let v = t - 16777216;
            let d = (v / 256 + 1) as usize;
            let l = (v % 256 + 3) as usize;
            assert!(d <= 32768 && d <= decoded.len() && l <= 258);
            for _ in 0..l { let x = decoded[decoded.len() - d]; decoded.push(x); }
        }
    }
    assert_eq!(data, decoded);
}
fn check(label: &str, data: &[u8], force: bool) {
    let left = if force {
        tokens(data, |s,o| control::run::<32768,32768>(s,o,6))
    } else { tokens(data, control::parse) };
    let right = if force {
        tokens(data, |s,o| bucket::bucket_run::<32768,32768>(s,o,6))
    } else { tokens(data, bucket::parse) };
    if left != right {
        let i = left.iter().zip(&right).position(|(a,b)| a != b).unwrap_or(left.len().min(right.len()));
        panic!("token divergence {} index={} lengths={}/{}", label, i, left.len(), right.len());
    }
    validate(data, &right);
    println!("EQUIVALENT {} bytes={} tokens={} force={}", label, data.len(), right.len(), force);
}
fn synthetic(n: usize, mode: usize, seed: u64) -> Vec<u8> {
    let mut state = seed;
    let text = b"the quick brown fox walks through the garden. const value = 0123456789;\\n";
    let mut data = Vec::with_capacity(n);
    for i in 0..n {
        state ^= state << 13; state ^= state >> 7; state ^= state << 17;
        let x = match mode {
            0 => (state >> 24) as u8,
            1 => text[i % text.len()],
            2 => if state % 97 == 0 { b'!' + (state % 90) as u8 } else { text[i % text.len()] },
            3 => if state % 11 == 0 { 0 } else { (state % 8) as u8 },
            4 => if i % 8191 < 2048 { (state % 95) as u8 + 32 } else { b'0' + (i % 10) as u8 },
            _ => b'0' + (state % 10) as u8,
        };
        data.push(x);
    }
    // Recent duplicate chunks separated by exact/adjacent window boundaries.
    if mode == 0 && n > 65536 {
        for d in [16383,16384,16385,32767,32768,32769] {
            let from = 1024; let to = from + d;
            for j in 0..512 { data[to+j] = data[from+j]; }
        }
    }
    data
}
fn main() {
    let dir = std::env::args().nth(1).unwrap();
    let mut paths: Vec<_> = std::fs::read_dir(dir).unwrap().map(|e| e.unwrap().path()).filter(|p| p.is_file()).collect();
    paths.sort();
    for path in paths {
        let data = std::fs::read(&path).unwrap();
        let label = path.file_name().unwrap().to_str().unwrap();
        check(label, &data, false);
        let ts = tokens(&data, instrumented::parse);
        assert_eq!(ts, tokens(&data, control::parse));
        let first = instrumented::FIRST.swap(0, Ordering::Relaxed);
        let second: Vec<_> = instrumented::SECOND.iter().map(|v| v.swap(0, Ordering::Relaxed)).collect();
        let improved: Vec<_> = instrumented::IMPROVED.iter().map(|v| v.swap(0, Ordering::Relaxed)).collect();
        println!("ATTRIBUTION {{\\"file\\":\\"{}\\",\\"class\\":{},\\"first_visits\\":{},\\"second_visits_by_first_len\\":{:?},\\"second_improvements_by_first_len\\":{:?}}}", label, control::sniff(&data), first, second, improved);
    }
    let sizes = [0,1,3,4,8,16,17,257,258,259,16383,16384,16385,32767,32768,32769,65535,65536,65537,98305,131073,262145];
    for n in sizes {
        for mode in 0..6 {
            for seed in [1, 123456789, 0x8f630] {
                let data = synthetic(n,mode,seed);
                check(&format!("synthetic-{}-{}-{}", n,mode,seed), &data, false);
                if n > 65536 { check(&format!("forced-{}-{}-{}", n,mode,seed), &data, true); }
            }
        }
    }
}
'''
    harness = harness.replace('CONTROL', str(baseline)).replace('BUCKET', str(workspace / 'candidates/bucket2/parse.rs')).replace('INSTRUMENTED', str(root / 'instrumented.rs'))
    (root / 'research.rs').write_text(harness)
    subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-Awarnings', '-O', str(root / 'research.rs'), '-o', str(root / 'research')], check=True)
    corpus = Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1'
    result = subprocess.run([str(root / 'research'), str(corpus)], capture_output=True, text=True)
    print(result.stdout, end='', flush=True)
    if result.stderr:
        print(result.stderr, end='', flush=True)
    result.check_returncode()
    traces = [json.loads(line.removeprefix('ATTRIBUTION ')) for line in result.stdout.splitlines() if line.startswith('ATTRIBUTION ')]
    report = {
        'scope': 'finite token equivalence + token decode; official Lean and DEFLATE round trip separate',
        'equivalence_cases': sum(line.startswith('EQUIVALENT ') for line in result.stdout.splitlines()),
        'public_files': len(traces),
        'probe2_source_sha256': hashlib.sha256(baseline.read_bytes()).hexdigest(),
        'bucket2_source_sha256': hashlib.sha256((workspace / 'candidates/bucket2/parse.rs').read_bytes()).hexdigest(),
        'instrumented_sha256': hashlib.sha256(instrumented.encode()).hexdigest(),
        'attribution_scope': 'regular walk visits and second-candidate selections only, not final emitted-token attribution; never timing evidence',
        'attribution': traces,
    }
    (root / 'research.json').write_text(json.dumps(report, indent=2) + '\n')
    print('RESEARCH ' + json.dumps(report), flush=True)


if __name__ == '__main__':
    main()
