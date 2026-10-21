"""A20: observe only this original engine subprocess tree, never score telemetry."""
from pathlib import Path
import dataclasses
import hashlib
import json
import os
import signal
import subprocess
import sys
import threading
import time

ROOT = Path(__file__).resolve().parents[1]
RUST = '1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad'

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def dump(p, value):
    p.write_text(json.dumps(value, indent=2) + '\n')

def preflight(spec):
    assert spec['r26_mode'] == 'diagnostic' and spec['r18_mode'] == 'diagnostic'
    assert spec['r26_a_engine_placement'] is True and spec['r26_expected_candidates'] == 0
    assert not spec['native_only'] and not spec['native_encoder']
    assert not spec['gate_candidates'] and not spec['extract_candidates']
    assert all(e['control'] for e in spec['entries'])
    assert spec['diagnostic_methods'] == ['public658']
    assert spec['isolated_blocks'] == 1 and spec['multimethod_blocks'] == 0
    e = next(e for e in spec['entries'] if e['name'] == 'public658')
    assert sha(ROOT / e['path'] / 'parse.rs') == e['hashes']['parse.rs'] == RUST
    return {'status':'VERIFIED_SINGLE_ORIGINAL_PAIR_READONLY_SUBTREE_OBSERVER_SPEC',
            'parser_sha256':RUST, 'poll_seconds':0.25, 'paired_processes':1,
            'scope':'No source, engine, sandbox, repetitions, call order, or scoring change. Diagnostic only.'}

def read_public(path):
    try:
        return Path(path).read_text().strip()
    except OSError as exc:
        return {'unavailable':type(exc).__name__}

def process_record(pid):
    base = Path('/proc') / str(pid)
    raw = (base / 'stat').read_text()
    tail = raw[raw.rfind(')')+2:].split()
    status = (base / 'status').read_text().splitlines()
    allowed = ('Name:', 'Pid:', 'PPid:', 'NSpid:', 'Cpus_allowed:', 'Cpus_allowed_list:',
               'Mems_allowed_list:', 'Threads:')
    return {'pid':pid, 'ppid':int(tail[1]), 'starttime_ticks':int(tail[19]),
            'sampled_cpu':int(tail[36]), 'status': [s for s in status if s.startswith(allowed)],
            'exe':os.readlink(base / 'exe')}

def descendants(root_pid):
    """Follow only children of the command we launched; never enumerate /proc."""
    todo = [root_pid]
    seen = set()
    rows = []
    while todo:
        pid = todo.pop()
        if pid in seen:
            continue
        seen.add(pid)
        try:
            rec = process_record(pid)
            rows.append(rec)
            children = (Path('/proc') / str(pid) / 'task' / str(pid) / 'children').read_text()
            todo.extend(int(s) for s in children.split())
        except (OSError, ValueError):
            pass  # Exit races are preserved as missing samples, never guessed PIDs.
    return rows

def engine_details(rec):
    pid, cpu = rec['pid'], rec['sampled_cpu']
    cg = read_public(f'/proc/{pid}/cgroup')
    result = {'cgroup':cg, 'effective_affinity':None, 'cgroup_files':{}, 'frequency_files':{}}
    try:
        result['effective_affinity'] = sorted(os.sched_getaffinity(pid))
    except OSError as exc:
        result['effective_affinity'] = {'unavailable':type(exc).__name__}
    if isinstance(cg, str):
        for line in cg.splitlines():
            pieces = line.split(':', 2)
            if len(pieces) == 3 and pieces[0] == '0':
                base = (Path('/sys/fs/cgroup') / pieces[2].lstrip('/')).resolve()
                if base.is_relative_to(Path('/sys/fs/cgroup')):
                    for name in ('cpuset.cpus','cpuset.cpus.effective','cpu.max','cpu.stat'):
                        result['cgroup_files'][str(base / name)] = read_public(base / name)
    for name in ('scaling_cur_freq','cpuinfo_cur_freq','scaling_governor','scaling_driver'):
        p = Path(f'/sys/devices/system/cpu/cpu{cpu}/cpufreq') / name
        result['frequency_files'][str(p)] = read_public(p)
    return result

def observe(root_pid, engine, stop, data):
    data['monitor_thread_id'] = threading.get_native_id()
    data['monitor_affinity_initial'] = sorted(os.sched_getaffinity(0))
    choices = [c for c in data['monitor_affinity_initial'] if c != 0]
    try:
        if choices:
            os.sched_setaffinity(0, {choices[0]})  # Linux calling thread only; engine already launched.
            data['monitor_affinity'] = sorted(os.sched_getaffinity(0))
        else:
            data['monitor_affinity'] = data['monitor_affinity_initial']
            data['monitor_pin_gap'] = 'No available non-requested CPU; observer shares allowed set.'
    except OSError as exc:
        data['monitor_pin_gap'] = type(exc).__name__
    known = {}
    while not stop.is_set():
        t = time.time_ns()
        rows = descendants(root_pid)
        engines = []
        for rec in rows:
            if rec['exe'] == str(engine):
                key = f"{rec['pid']}:{rec['starttime_ticks']}"
                try:
                    if key not in known:
                        known[key] = {'first_seen_unix_ns':t,'process':rec,
                                      'exe_sha256_via_proc':sha(Path(f"/proc/{rec['pid']}/exe")),
                                      'ancestor_snapshot':rows}
                    engines.append({**rec, **engine_details(rec)})
                except OSError as exc:
                    data.setdefault('exit_races',[]).append({'pid':rec['pid'],'unix_ns':t,'error':type(exc).__name__})
        data['samples'].append({'unix_ns':t,'tree_pid_start_pairs':[[r['pid'],r['starttime_ticks']] for r in rows],
                                'engines':engines})
        data['engine_identities'] = known
        stop.wait(0.25)

def pins(up):
    validator = up / 'validator'
    declared = json.loads((validator / 'verifier/PINS.json').read_bytes())
    actual = {p:sha(validator / p) for p in declared}
    assert actual == declared
    return actual

def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    from round4 import validate
    spec = validate(os.environ['ROUND4_SPEC'])
    checked = preflight(spec)
    up = Path(os.environ['DEFLATE_ROOT']).resolve()
    before = pins(up)
    sys.path.insert(0,str(up / 'validator'))
    from bench import driver, corpora
    from bench.results import INCUMBENT
    from sandbox import bwrap
    cfg = dataclasses.replace(driver.Config.from_env(up / 'validator'), reps=11, warmup=1,
                              cpus='0', keep=driver.Keep.ALWAYS, bars=False)
    assert cfg.timeout == 300.0
    driver.check(cfg)
    entry = next(e for e in spec['entries'] if e['name']=='public658')
    corpus = corpora.load(up / 'validator').by_name('corpus-stage1')
    workspace = driver._make_workspace(cfg, {'public658':ROOT / entry['path'] / 'parse.rs'})
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r26-a-engine-placement'
    out.mkdir(parents=True,exist_ok=True)
    identity_paths = ['bench/driver.py','sandbox/bwrap.py','verifier/PINS.json',
                      'measure/src/main.rs','measure/candidate/Cargo.toml','measure/candidate/lib.rs']
    receipt = {'status':'STARTED_DIAGNOSTIC_ONLY','run_id':os.environ['GITHUB_RUN_ID'],
               'git_sha':os.environ['GITHUB_SHA'],'preflight':checked,'pins_before':before,
               'public_source_sha256':{p:sha(up / 'validator' / p) for p in identity_paths},
               'engine_sha256':sha(cfg.engine), 'driver_provenance':driver.provenance(cfg),
               'observer_source_sha256':sha(Path(__file__)),
               'scope':'One original public658/incumbent pair with external read-only telemetry. Never promotion timing or historical A19 cause.'}
    dump(out / 'receipt.json',receipt)
    crates = driver._generate(cfg, workspace, {'public658':ROOT / entry['path'] / 'parse.rs'})
    driver._build(cfg, workspace, crates)
    rustc = driver._rustc_version(cfg, workspace, crates[INCUMBENT])
    cmd = [str(cfg.engine),str(corpus.path),f'{INCUMBENT}={crates[INCUMBENT]}',f'public658={crates["public658"]}',
           '--corpus-name',corpus.name,'--reps','11','--warmup','1','--rustc-version',rustc,'--no-bars']
    sandbox = driver.measure_sandbox(cfg,workspace,corpus)
    command = bwrap.argv(sandbox) + cmd
    receipt['original_command'] = command
    dump(out / 'receipt.json',receipt)
    telemetry = {'poll_seconds':0.25,'samples':[],'engine_identities':{}}
    stop = threading.Event()
    with subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True,
                          cwd=None, env=None, start_new_session=True) as process:
        telemetry['launched_pid'] = process.pid
        monitor = threading.Thread(target=observe,args=(process.pid,cfg.engine.resolve(),stop,telemetry),daemon=True)
        monitor.start()
        try:
            stdout, stderr = process.communicate(timeout=cfg.timeout)
        except subprocess.TimeoutExpired:
            try:
                os.killpg(process.pid,signal.SIGKILL)
            except ProcessLookupError:
                pass
            stdout, stderr = process.communicate()
            receipt['timeout_seconds'] = cfg.timeout
        finally:
            stop.set()
            monitor.join(timeout=5)
            dump(out / 'telemetry.json',telemetry)
        (out / 'original-engine.raw.jsonl').write_text(stdout)
        (out / 'original-engine.stderr.log').write_text(stderr)
        receipt['returncode'] = process.returncode
        dump(out / 'receipt.json',receipt)
    assert receipt['returncode'] == 0
    measured = driver.parse_results(stdout,corpus)
    meta = measured.raw_records[0]
    files = [r for r in measured.raw_records if r['kind']=='file']
    assert len(files)==28 and meta['measured_rounds']==11 and meta['warmup_rounds']==1
    assert meta['methods']['public658']['source_sha256']==RUST
    for method in (INCUMBENT,'public658'):
        assert not measured.failures(method)
    captured = list(telemetry['engine_identities'].values())
    assert len(captured)==1, 'Must identify one exact engine PID/starttime in only the launched subtree'
    assert captured[0]['exe_sha256_via_proc']==receipt['engine_sha256']
    receipt['pins_after'] = pins(up)
    assert receipt['pins_after']==before and sha(cfg.engine)==receipt['engine_sha256']
    subprocess.run(['git','diff','--exit-code'],cwd=up,check=True)
    receipt.update(status='COMPLETE_EXACT_ENGINE_PLACEMENT_OBSERVATION_NOT_A_SCORE',metadata=meta,
                   file_count=28,engine_identity=captured[0],engine_sample_count=sum(bool(s['engines']) for s in telemetry['samples']),
                   artifacts={p.name:sha(p) for p in out.iterdir() if p.is_file() and p.name!='receipt.json'},
                   limits=['Sampling observes CPU at 4Hz, not every call or migration.',
                           'Unavailable frequency is UNKNOWN; visible frequency is not necessarily instantaneous execution frequency.',
                           'Observer can perturb timing despite separate CPU; all times diagnostic only.',
                           'Current observed placement cannot identify placement or cause in historical runs.'])
    dump(out / 'receipt.json',receipt)
    print(receipt['status'],receipt['engine_sample_count'])

if __name__=='__main__':
    main()
