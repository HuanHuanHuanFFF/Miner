"""One scratch-engine endpoint-CPU measurement verification; never candidate scores."""
from pathlib import Path
import dataclasses
import difflib
import hashlib
import importlib
import json
import os
import shutil
import signal
import subprocess
import sys
import threading
import time

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
PUBLIC = '1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad'
ORIGINAL_ENGINE = 'ab202460691492f48d5c632375f5df2a74fc3769a81337e876607e9326a46fac'
A20 = importlib.import_module('r26-a-engine-placement')
MARKER = 'R26_CALL_CPU_DIAGNOSTIC '
HELPER = r'''use serde::Serialize;
use std::cell::RefCell;
use std::time::Instant;
extern "C" { fn sched_getcpu() -> std::os::raw::c_int; }
#[derive(Clone, Copy, Serialize)]
struct Context { file: usize, method: usize, round: usize, phase: &'static str, order_index: u64 }
#[derive(Serialize)]
struct Event { context: Context, stage: &'static str, cpu_before: i32, cpu_after: i32,
    cpu_endpoint_changed: Option<bool>, before_mono_ns: u64, after_mono_ns: u64, original_elapsed_s: f64 }
#[derive(Serialize)]
struct Trace { status: &'static str, files: Vec<String>, methods: Vec<String>, capacity: usize,
    #[serde(skip)] origin: Instant, #[serde(skip)] context: Context, events: Vec<Event> }
thread_local! { static TRACE: RefCell<Option<Trace>> = RefCell::new(None); }
pub struct Stamp { cpu: i32, mono_ns: u64 }
pub fn init(files: Vec<String>, methods: Vec<String>, capacity: usize) {
    TRACE.with(|t| *t.borrow_mut() = Some(Trace { status: "measurement_verification", files, methods,
        capacity, origin: Instant::now(), context: Context { file: 0, method: 0, round: 0,
        phase: "unset", order_index: 0 }, events: Vec::with_capacity(capacity) }));
}
pub fn file_index(name: &str) -> usize {
    TRACE.with(|t| t.borrow().as_ref().unwrap().files.iter().position(|f| f == name).unwrap())
}
pub fn context(file: usize, method: usize, round: usize, phase: &'static str, order_index: u64) {
    TRACE.with(|t| t.borrow_mut().as_mut().unwrap().context = Context { file, method, round, phase, order_index });
}
pub fn before() -> Stamp {
    let cpu = unsafe { sched_getcpu() };
    let mono_ns = TRACE.with(|t| t.borrow().as_ref().unwrap().origin.elapsed().as_nanos() as u64);
    Stamp { cpu, mono_ns }
}
pub fn after(before: Stamp, stage: &'static str, original_elapsed_s: f64) {
    let cpu_after = unsafe { sched_getcpu() };
    TRACE.with(|t| { let mut state = t.borrow_mut(); let trace = state.as_mut().unwrap();
        let after_mono_ns = trace.origin.elapsed().as_nanos() as u64;
        assert!(trace.events.len() < trace.capacity);
        assert!(trace.events.capacity() >= trace.capacity);
        trace.events.push(Event { context: trace.context, stage, cpu_before: before.cpu, cpu_after,
            cpu_endpoint_changed: if before.cpu >= 0 && cpu_after >= 0 { Some(before.cpu != cpu_after) } else { None },
            before_mono_ns: before.mono_ns, after_mono_ns, original_elapsed_s });
    });
}
pub fn flush() {
    TRACE.with(|t| { let state = t.borrow(); let trace = state.as_ref().unwrap();
        assert_eq!(trace.events.len(), trace.capacity);
        eprintln!("R26_CALL_CPU_DIAGNOSTIC {}", serde_json::to_string(trace).unwrap());
    });
}
'''


def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()


def dump(p, value):
    p.write_text(json.dumps(value, indent=2)+'\n')


def patch_sources(method, main):
    changes = [
        ('                let t0 = Instant::now();\n                let n = p.parse(input, toks);',
         '                let cpu_parse_before = crate::callcpu::before();\n                let t0 = Instant::now();\n                let n = p.parse(input, toks);'),
        ('                let parse_s = t0.elapsed().as_secs_f64();\n                if n == PANICKED',
         '                let parse_s = t0.elapsed().as_secs_f64();\n                crate::callcpu::after(cpu_parse_before, "parser", parse_s);\n                if n == PANICKED'),
        ('                let t1 = Instant::now();\n                let encoded',
         '                let cpu_encode_before = crate::callcpu::before();\n                let t1 = Instant::now();\n                let encoded'),
        ('                let encode_s = Some(t1.elapsed().as_secs_f64());',
         '                let encode_s = Some(t1.elapsed().as_secs_f64());\n                crate::callcpu::after(cpu_encode_before, "encoder", encode_s.unwrap());')]
    original = method
    for old, new in changes:
        assert method.count(old) == 1
        method = method.replace(old, new, 1)
    reverted = method
    for old, new in reversed(changes):
        reverted = reverted.replace(new, old, 1)
    assert reverted == original
    main_changes = [
        ('mod deflate;', 'mod callcpu;\nmod deflate;'),
        ('    for round in 0..(warmup + reps) {',
         '    let cpu_file = crate::callcpu::file_index(&name);\n    for round in 0..(warmup + reps) {'),
        ('        for m in methods {', '        for (cpu_method, m) in methods.iter().enumerate() {'),
        ('            let once = m.run_once(&input, &mut toks, first);',
         '            crate::callcpu::context(cpu_file, cpu_method, round, phase, *order + 1);\n            let once = m.run_once(&input, &mut toks, first);'),
        ('    let meta = Meta {',
         '    crate::callcpu::init(files.iter().map(|f| f.file_name().unwrap().to_string_lossy().to_string()).collect(),\n        methods.iter().map(|m| m.name.clone()).collect(), files.len() * (args.warmup + args.reps) * methods.len() * 2);\n    let meta = Meta {'),
        ('    Ok(())\n}\n\nfn main()', '    crate::callcpu::flush();\n    Ok(())\n}\n\nfn main()')]
    original = main
    for old, new in main_changes:
        assert main.count(old) == 1
        main = main.replace(old, new, 1)
    reverted = main
    for old, new in reversed(main_changes):
        reverted = reverted.replace(new, old, 1)
    assert reverted == original
    return method, main


def preflight(spec):
    assert spec['r26_v_call_cpu'] is True and spec['r18_role'] == 'measurement_verification'
    assert spec['r26_mode'] == spec['r18_mode'] == 'diagnostic'
    assert spec['r26_expected_candidates'] == 0 and not spec['gate_candidates'] and not spec['extract_candidates']
    assert not spec['native_only'] and not spec['native_encoder'] and all(e['control'] for e in spec['entries'])
    assert spec['diagnostic_methods'] == ['public658'] and spec['isolated_blocks'] == 2 and spec['multimethod_blocks'] == 0
    assert spec['verification_job_cap_minutes'] == 25 and spec['verification_dispatch_hard_utc'] == '2026-10-12T10:05:00Z'
    e = next(e for e in spec['entries'] if e['name'] == 'public658')
    assert sha(ROOT/e['path']/'parse.rs') == e['hashes']['parse.rs'] == PUBLIC
    return {'status': 'measurement_verification', 'scope': 'Two sequential scratch-engine paired processes; endpoint CPU telemetry only; no scores.',
            'parser_sha256': PUBLIC, 'warmup': 1, 'measured_reps': 11, 'poll_seconds': 0.25}


def ancestor_details(rec):
    result = BASE_DETAILS(rec)
    membership = result['cgroup']
    result['cgroup_ancestor_files'] = {}
    if isinstance(membership, str):
        for line in membership.splitlines():
            parts = line.split(':', 2)
            if len(parts) == 3 and parts[0] == '0':
                root = Path('/sys/fs/cgroup').resolve()
                base = (root/parts[2].lstrip('/')).resolve()
                if not base.is_relative_to(root):
                    continue
                while True:
                    for name in ('cgroup.controllers', 'cgroup.subtree_control', 'cpuset.cpus', 'cpuset.cpus.effective',
                                 'cpuset.mems', 'cpuset.mems.effective', 'cpu.max', 'cpu.stat'):
                        result['cgroup_ancestor_files'][str(base/name)] = A20.read_public(base/name)
                    if base == root:
                        break
                    base = base.parent
    return result


BASE_DETAILS = A20.engine_details


def verify_trace(trace, records):
    assert trace['status'] == 'measurement_verification' and trace['methods'] == ['incumbent', 'public658']
    files = [r for r in records if r['kind'] == 'file']
    assert [r['file'] for r in files] == trace['files'] and trace['capacity'] == len(trace['events']) == 1344
    expected = {}
    for file in files:
        for name in trace['methods']:
            method = file['methods'][name]
            assert not method['errors'] and method['deterministic'] and len(method['reps']) == 12
            for rep in method['reps']:
                for stage, field in [('parser', 'time_s'), ('encoder', 'encode_s')]:
                    key = (file['file'], name, rep['phase'], rep['order_index'], stage)
                    expected[key] = rep[field]
    seen = set()
    for event in trace['events']:
        ctx = event['context']
        key = (trace['files'][ctx['file']], trace['methods'][ctx['method']], ctx['phase'], ctx['order_index'], event['stage'])
        assert key not in seen and key in expected
        assert ctx['phase'] == ('warmup' if ctx['round'] == 0 else 'measured') and 0 <= ctx['round'] < 12
        assert ctx['order_index'] % 2 == (1 if ctx['method'] == 0 else 0)
        assert event['original_elapsed_s'] == expected[key] and event['before_mono_ns'] <= event['after_mono_ns']
        seen.add(key)
    assert seen == expected.keys()


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    from round4 import validate
    spec = validate(os.environ['ROUND4_SPEC'])
    checked = preflight(spec)
    up = Path(os.environ['DEFLATE_ROOT']).resolve()
    before = A20.pins(up)
    sys.path.insert(0, str(up/'validator'))
    from bench import driver, corpora
    from bench.results import INCUMBENT
    from sandbox import bwrap
    cfg = dataclasses.replace(driver.Config.from_env(up/'validator'), reps=11, warmup=1, cpus='0', keep=driver.Keep.ALWAYS, bars=False)
    assert cfg.timeout == 300.0 and sha(cfg.engine) == ORIGINAL_ENGINE
    driver.check(cfg)
    temp = Path(os.environ['RUNNER_TEMP']).resolve()
    scratch = temp/'r26-v-callcpu-engine'
    out = temp/'round4-receipts/r26-v-call-cpu'
    assert not scratch.exists()
    shutil.copytree(up/'validator/measure', scratch, ignore=shutil.ignore_patterns('target'))
    shutil.copy2(up/'validator/rust-toolchain.toml', scratch/'rust-toolchain.toml')
    out.mkdir(parents=True, exist_ok=True)
    source_paths = ['src/method.rs', 'src/main.rs', 'src/record.rs', 'Cargo.toml', 'Cargo.lock']
    source_before = {p: sha(up/'validator/measure'/p) for p in source_paths}
    assert source_before == spec['verification_original_measure_sources']
    old_method = (scratch/'src/method.rs').read_text()
    old_main = (scratch/'src/main.rs').read_text()
    new_method, new_main = patch_sources(old_method, old_main)
    (scratch/'src/method.rs').write_text(new_method)
    (scratch/'src/main.rs').write_text(new_main)
    (scratch/'src/callcpu.rs').write_text(HELPER)
    diff = ''.join(difflib.unified_diff(old_method.splitlines(True), new_method.splitlines(True), fromfile='original/src/method.rs', tofile='scratch/src/method.rs'))
    diff += ''.join(difflib.unified_diff(old_main.splitlines(True), new_main.splitlines(True), fromfile='original/src/main.rs', tofile='scratch/src/main.rs'))
    diff += ''.join(difflib.unified_diff([], HELPER.splitlines(True), fromfile='/dev/null', tofile='scratch/src/callcpu.rs'))
    (out/'scratch-engine.diff').write_text(diff)
    receipt = {'status': 'measurement_verification', 'completion': 'STARTED', 'run_id': os.environ['GITHUB_RUN_ID'],
               'git_sha': os.environ['GITHUB_SHA'], 'preflight': checked, 'pins_before': before,
               'original_engine_sha256': sha(cfg.engine), 'original_driver_provenance': driver.provenance(cfg),
               'original_measure_sources': source_before, 'scratch_sources': {p: sha(scratch/p) for p in source_paths+['src/callcpu.rs']},
               'script_sha256': sha(Path(__file__)), 'diff_sha256': sha(out/'scratch-engine.diff'), 'processes': []}
    dump(out/'receipt.json', receipt)
    build = bwrap.run(driver.build_sandbox(cfg, scratch), ['cargo', 'build', '--release', '--offline', '--locked', '-q'], cwd=scratch, timeout=cfg.timeout)
    (out/'scratch-build.log').write_text(build.stdout+build.stderr)
    assert build.returncode == 0, 'scratch engine build failed; no retry'
    engine = (scratch/'target/release/measure').resolve()
    receipt['scratch_engine_sha256'] = sha(engine)
    entry = next(e for e in spec['entries'] if e['name'] == 'public658')
    corpus = corpora.load(up/'validator').by_name('corpus-stage1')
    workspace = driver._make_workspace(cfg, {'public658': ROOT/entry['path']/'parse.rs'})
    crates = driver._generate(cfg, workspace, {'public658': ROOT/entry['path']/'parse.rs'})
    driver._build(cfg, workspace, crates)
    rustc = driver._rustc_version(cfg, workspace, crates[INCUMBENT])
    dso_hashes = {name: sha(p/'target/release/libcandidate.so') for name, p in crates.items()}
    receipt['dso_sha256'] = dso_hashes
    cmd = [str(engine), str(corpus.path), f'{INCUMBENT}={crates[INCUMBENT]}', f'public658={crates["public658"]}',
           '--corpus-name', corpus.name, '--reps', '11', '--warmup', '1', '--rustc-version', rustc, '--no-bars']
    sandbox = dataclasses.replace(driver.measure_sandbox(cfg, workspace, corpus), ro_binds=(cfg.validator, workspace, corpus.path, scratch))
    command = bwrap.argv(sandbox)+cmd
    receipt['diagnostic_command'] = command
    A20.engine_details = ancestor_details
    prior_path = ROOT/'evidence/round26/38227767865/placement-a20-diagnostic/diagnostics/r26-a-engine-placement/original-engine.raw.jsonl'
    prior = {r['file']: r for r in [json.loads(s) for s in prior_path.read_text().splitlines()] if r['kind'] == 'file'}
    receipt['A20_original_results_sha256'] = sha(prior_path)
    for number in (1, 2):
        telemetry = {'poll_seconds': 0.25, 'samples': [], 'engine_identities': {}}
        stop = threading.Event()
        with subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, env=None, start_new_session=True) as process:
            telemetry['launched_pid'] = process.pid
            monitor = threading.Thread(target=A20.observe, args=(process.pid, engine, stop, telemetry), daemon=True)
            monitor.start()
            try:
                stdout, stderr = process.communicate(timeout=cfg.timeout)
            except subprocess.TimeoutExpired:
                try:
                    os.killpg(process.pid, signal.SIGKILL)
                except ProcessLookupError:
                    pass
                stdout, stderr = process.communicate()
            finally:
                stop.set()
                monitor.join(timeout=5)
                dump(out/f'process{number}.observer.json', telemetry)
            (out/f'process{number}.raw.jsonl').write_text(stdout)
            (out/f'process{number}.stderr.log').write_text(stderr)
            assert process.returncode == 0, 'diagnostic process failed; no retry'
        markers = [s[len(MARKER):] for s in stderr.splitlines() if s.startswith(MARKER)]
        assert len(markers) == 1
        trace = json.loads(markers[0])
        dump(out/f'process{number}.call-cpu.json', trace)
        measured = driver.parse_results(stdout, corpus)
        records = measured.raw_records
        verify_trace(trace, records)
        meta = records[0]
        assert meta['measured_rounds'] == 11 and meta['warmup_rounds'] == 1
        identities = list(telemetry['engine_identities'].values())
        assert len(identities) == 1 and identities[0]['exe_sha256_via_proc'] == receipt['scratch_engine_sha256']
        for row in records:
            if row['kind'] == 'file':
                assert row['sha256'] == prior[row['file']]['sha256']
                for name in (INCUMBENT, 'public658'):
                    for key in ('tokens_sha256', 'output_sha256', 'output_bytes'):
                        assert row['methods'][name][key] == prior[row['file']]['methods'][name][key]
        assert meta['methods']['public658']['source_sha256'] == PUBLIC
        assert {n: meta['methods'][n]['lib_sha256'] for n in dso_hashes} == dso_hashes
        assert all(sha(p/'target/release/libcandidate.so') == dso_hashes[n] for n, p in crates.items())
        receipt['processes'].append({'number': number, 'metadata': meta, 'engine_identity': identities[0], 'event_count': len(trace['events'])})
        dump(out/'receipt.json', receipt)
    receipt['pins_after'] = A20.pins(up)
    assert before == receipt['pins_after'] and sha(cfg.engine) == receipt['original_engine_sha256']
    assert {p: sha(up/'validator/measure'/p) for p in source_paths} == source_before
    subprocess.run(['git', 'diff', '--exit-code'], cwd=up, check=True)
    receipt.update(completion='COMPLETE', artifacts={p.name: sha(p) for p in out.iterdir() if p.is_file() and p.name != 'receipt.json'},
                   limits=['Endpoint CPU equality does not rule out intermediate migration; differing endpoints cannot locate a change inside the timed interval. Negative sched_getcpu is UNKNOWN.',
                           'Clock/CPU probes outside the original timers can perturb scheduling/cache. All timings are diagnostic.',
                           'External 4Hz observer and ancestor cgroup aggregate counters do not identify a per-call cause.',
                           'Scratch engine differs from original; two processes share the exact scratch binary and DSOs, not independent confirmation.',
                           'No scoring, gate, admission, reward or candidate source/proof change.'])
    dump(out/'receipt.json', receipt)
    print('measurement_verification COMPLETE', len(receipt['processes']))


if __name__ == '__main__':
    main()
