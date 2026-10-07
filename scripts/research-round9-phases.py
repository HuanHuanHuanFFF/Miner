"""CI-only coarse parser phase attribution; separate from official paired timing."""
from pathlib import Path
import hashlib
import json
import os
import statistics
import subprocess
from round4 import ROOT, validate, save

PHASES = ['d_parse', 'd_tally', 'd_dp', 'd_extract', 'emit', 'emit_pos']
INSTRUMENT = '''
use std::sync::atomic::{AtomicU64, Ordering};
static R9_PHASE_NS: [AtomicU64; 6] = [const { AtomicU64::new(0) }; 6];
struct R9Phase(usize, std::time::Instant);
impl R9Phase { fn new(i: usize) -> Self { Self(i, std::time::Instant::now()) } }
impl Drop for R9Phase { fn drop(&mut self) { R9_PHASE_NS[self.0].fetch_add(self.1.elapsed().as_nanos() as u64, Ordering::Relaxed); } }
pub fn r9_reset() { for v in &R9_PHASE_NS { v.store(0, Ordering::Relaxed); } }
pub fn r9_times() -> Vec<u64> { R9_PHASE_NS.iter().map(|v| v.load(Ordering::Relaxed)).collect() }
'''
HARNESS = r'''
#![allow(dead_code)]
#[path="reference.rs"] mod reference;
#[path="instrumented.rs"] mod profiled;
fn main() {
    for (index, file) in std::env::args_os().skip(1).enumerate() {
        let input = std::fs::read(file).unwrap();
        for rep in 0..3 {
            let mut a = vec![0u32; input.len()]; let mut b = vec![0u32; input.len()];
            let (mut an, mut bn, mut at, mut bt) = (0, 0, 0u128, 0u128);
            profiled::r9_reset();
            for order in 0..2 {
                if (order + rep) % 2 == 0 {
                    let start = std::time::Instant::now(); an = reference::parse(&input, &mut a); at = start.elapsed().as_nanos();
                } else {
                    let start = std::time::Instant::now(); bn = profiled::parse(&input, &mut b); bt = start.elapsed().as_nanos();
                }
            }
            assert!(an <= input.len() && bn <= input.len());
            assert_eq!(&a[..an], &b[..bn], "instrumentation changed tokens");
            println!("R9_PHASE {{\"file_index\":{},\"rep\":{},\"reference_ns\":{},\"instrumented_ns\":{},\"phase_ns\":{:?},\"tokens_equal\":true}}", index, rep, at, bt, profiled::r9_times());
        }
    }
}
'''


def instrument(source):
    assert 'R9Phase' not in source
    for index, name in enumerate(PHASES):
        marker = 'pub fn ' + name + '('
        assert source.count(marker) == 1
        position = source.index('{', source.index(marker)) + 1
        source = source[:position] + f'\n    let _r9_phase = R9Phase::new({index});' + source[position:]
    return source + INSTRUMENT


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    assert os.environ.get('GITHUB_REPOSITORY') == 'HuanHuanHuanFFF/Miner'
    spec = validate(os.environ['ROUND4_SPEC'])
    if not spec.get('phase_diagnostics'):
        print('ROUND9_PHASES_NOT_REQUESTED'); return
    entry = next(e for e in spec['entries'] if e['name'] == 'r7-mid361-block1')
    raw = (ROOT / entry['path'] / 'parse.rs').read_bytes()
    assert hashlib.sha256(raw).hexdigest() == entry['hashes']['parse.rs']
    build = Path(os.environ['RUNNER_TEMP']) / 'round9-phase-build'
    output = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/phase-diagnostics'
    build.mkdir(exist_ok=True); output.mkdir(parents=True, exist_ok=True)
    files = sorted(p for p in (Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1').iterdir() if p.is_file())
    assert len(files) == 28 and sum(p.stat().st_size for p in files) == 15930000
    (build / 'reference.rs').write_bytes(raw)
    (build / 'instrumented.rs').write_text(instrument(raw.decode()))
    (build / 'main.rs').write_text(HARNESS)
    report = {'scope': 'Coarse instrumented parser-only phase attribution, no encoder and no competition axes; timers can perturb code generation.',
              'status': 'PENDING', 'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'],
              'candidate': entry['name'], 'source_sha256': entry['hashes']['parse.rs'], 'phases': PHASES,
              'corpus': [{'file': f.name, 'bytes': f.stat().st_size, 'sha256': hashlib.sha256(f.read_bytes()).hexdigest()} for f in files]}
    save(output / 'phases.json', report)
    binary = build / 'phase-profile'
    proc = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(build / 'main.rs'), '-o', str(binary)], capture_output=True, text=True, timeout=180)
    (output / 'build.log').write_text(proc.stdout + proc.stderr)
    if proc.returncode:
        raise RuntimeError('Phase diagnostic compilation failed; see retained build.log')
    cpu = str(min(os.sched_getaffinity(0)))
    proc = subprocess.run(['taskset', '-c', cpu, str(binary), *map(str, files)], capture_output=True, text=True, timeout=240)
    (output / 'runtime.log').write_text(proc.stdout + proc.stderr)
    rows = [json.loads(line.removeprefix('R9_PHASE ')) for line in proc.stdout.splitlines() if line.startswith('R9_PHASE ')]
    assert proc.returncode == 0 and len(rows) == 84 and all(r['tokens_equal'] for r in rows)
    assert {(r['file_index'], r['rep']) for r in rows} == {(i, j) for i in range(28) for j in range(3)}
    summary = []
    for i, file in enumerate(files):
        data = [r for r in rows if r['file_index'] == i]
        total = statistics.median(r['instrumented_ns'] for r in data)
        phases = {name: statistics.median(r['phase_ns'][j] for r in data) for j, name in enumerate(PHASES)}
        summary.append({'file': file.name, 'reference_ns': statistics.median(r['reference_ns'] for r in data), 'instrumented_ns': total,
                        'phase_ns': phases, 'phase_fraction_of_instrumented_parser': {k: v / total for k, v in phases.items()}})
    report.update(status='VERIFIED_FINITE_PHASE_DIAGNOSTIC', records=rows, files=summary, cpu_affinity=cpu,
                  instrumented_sha256=hashlib.sha256((build / 'instrumented.rs').read_bytes()).hexdigest())
    save(output / 'phases.json', report)
    print('ROUND9_PHASES', json.dumps({'status': report['status'], 'files': len(summary), 'token_comparisons': len(rows)}))


if __name__ == '__main__':
    main()
