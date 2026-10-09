"""Untimed third-link usefulness by existing match length; exact source unchanged."""
from pathlib import Path
import hashlib, importlib.util, json, os, subprocess
from round4 import ROOT, validate

BUCKETS = ['0-3', '4-7', '8-15', '16-31', '32-63', '64-127', '128-257', '258+']
FIELDS = ['calls', 'c2_expired', 'c3_expired', 'c4_live', 'wins', 'added_length']

def instrument(raw):
    text = raw.decode()
    a = text.index('pub fn r15_deepen3(')
    head, body = text[:a], text[a:]
    old = '    let g = pc_f_deepen(s, prev, c, c2, p, l, d, dp, minl);'
    assert body.count(old) == 1
    body = body.replace(old, old + '''
    let b=if g.0<4{0}else if g.0<8{1}else if g.0<16{2}else if g.0<32{3}else if g.0<64{4}else if g.0<128{5}else if g.0<258{6}else{7};
    if dp>=3 {r15_hit(b,0,1);r15_hit(b,1,(p.wrapping_sub(c2).wrapping_sub(1)>=32768) as u64);}
''')
    old = '        let c3 = r13_prev_unwrap(c2, prev[c2 % 32768]);'
    assert body.count(old) == 1
    body = body.replace(old, old + '\n        r15_hit(b,2,(p.wrapping_sub(c3).wrapping_sub(1)>=32768) as u64);')
    old = '            pc_f_try(s, c3, c4, p, g.0, g.1, minl)'
    assert body.count(old) == 1
    body = body.replace(old, '''            let result=pc_f_try(s,c3,c4,p,g.0,g.1,minl);
            r15_hit(b,3,(c4<c3&&p.wrapping_sub(c4).wrapping_sub(1)<32768)as u64);
            r15_hit(b,4,(result.0>g.0)as u64);
            r15_hit(b,5,result.0.saturating_sub(g.0)as u64);
            result''')
    counters = '''
use std::sync::atomic::{AtomicU64,Ordering};
static R15_C:[AtomicU64;48]=[const{AtomicU64::new(0)};48];
fn r15_hit(b:usize,k:usize,v:u64){R15_C[b*6+k].fetch_add(v,Ordering::Relaxed);}
pub fn r15_take()->[u64;48]{std::array::from_fn(|i|R15_C[i].swap(0,Ordering::Relaxed))}
'''
    return (head + body + counters).encode()

def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = validate(os.environ['ROUND4_SPEC'])
    entry = next(e for e in spec['entries'] if e['name'] == 'r15-hash32-chain-depth3')
    frozen = ROOT / entry['path'] / 'parse.rs'
    raw = frozen.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == entry['hashes']['parse.rs']
    build = Path(os.environ['RUNNER_TEMP']) / 'r15-chain-build'
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r15-chain'
    build.mkdir(exist_ok=True); out.mkdir(parents=True, exist_ok=True)
    observed = build / 'observed.rs'
    observed.write_bytes(instrument(raw))
    loader = importlib.util.spec_from_file_location('counts_harness', ROOT / 'scripts/research-round13-counts.py')
    m = importlib.util.module_from_spec(loader); loader.loader.exec_module(m)
    text = m.HARNESS.replace('FROZEN', str(frozen)).replace('OBSERVED', str(observed)).replace('observed::r13_take()', 'observed::r15_take()').replace('R13_COUNT', 'R15_CHAIN')
    source = build / 'counts.rs'; source.write_text(text); binary = build / 'counts'
    c = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(source), '-o', str(binary)], capture_output=True, text=True, timeout=180)
    (out / 'compile.log').write_text(c.stdout + c.stderr); assert c.returncode == 0
    corpus = Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1'
    r = subprocess.run([str(binary), str(corpus)], capture_output=True, text=True, timeout=120)
    (out / 'run.log').write_text(r.stdout + r.stderr); assert r.returncode == 0
    rows = []
    for line in r.stdout.splitlines():
        if not line.startswith('R15_CHAIN '): continue
        _, name, size, *values = line.split(); v = list(map(int, values)); assert len(v) == 48
        data = (corpus / name).read_bytes(); assert len(data) == int(size)
        rows.append({'file': name, 'raw_bytes': len(data), 'input_sha256': hashlib.sha256(data).hexdigest(), 'buckets': {b: dict(zip(FIELDS, v[i*6:i*6+6])) for i,b in enumerate(BUCKETS)}})
    assert len(rows) == 28 and sum(r['raw_bytes'] for r in rows) == 15930000
    result = {'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'batch': os.environ['ROUND4_SPEC'], 'status': 'VERIFIED_OBSERVER_FROZEN_TOKEN_AND_DECODE_EQUAL', 'source_hashes': entry['hashes'], 'observer_sha256': hashlib.sha256(observed.read_bytes()).hexdigest(), 'harness_sha256': hashlib.sha256(text.encode()).hexdigest(), 'rows': rows, 'totals': {b: {f: sum(r['buckets'][b][f] for r in rows) for f in FIELDS} for b in BUCKETS}, 'scope': 'Untimed atomic observation on unchanged depth3. Counts and added match lengths are opportunities, not speed or encoded-byte savings. R13 expired-head rejection remains closed; this probes later links in a newly deeper chain.'}
    (out / 'counts.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'status': result['status'], 'totals': result['totals']}))

if __name__ == '__main__':
    main()
