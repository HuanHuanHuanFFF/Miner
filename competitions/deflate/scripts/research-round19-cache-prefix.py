"""Runner-only quality experiment; cloned global cache is NOT a submit-ready implementation."""
from pathlib import Path
import hashlib
import importlib.util
import json
import os
import subprocess
import zlib
from round4 import ROOT, validate


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = validate(os.environ['ROUND4_SPEC'])
    entry = next(e for e in spec['entries'] if e['name'] == 'base603')
    frozen = ROOT / entry['path'] / 'parse.rs'
    raw = frozen.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == entry['hashes']['parse.rs']
    text = raw.decode()
    marker = 'a_find_all(input, &mut mp, &mut mb, depth, skip);'
    assert text.count(marker) == 1
    text = text.replace(marker, marker + '\n    *R19_CACHE.lock().unwrap()=Some((mp.clone(),mb.clone()));')
    marker = 'pub fn parse(input: &[u8], out: &mut [u32]) -> usize {'
    assert text.count(marker) == 1
    text = text.replace(marker, marker + '\n    *R19_CACHE.lock().unwrap()=None;')
    marker = 'let known=SFknown(ot,d,cap);'
    assert text.count(marker) == 1
    text = text.replace(marker, 'let known=r19_known(p,d,cap,SFknown(ot,d,cap));')
    text += r'''
use std::sync::{Mutex,atomic::{AtomicU64,Ordering}};
static R19_CACHE:Mutex<Option<(Vec<u32>,Vec<u32>)>>=Mutex::new(None);
static R19_COUNTS:[AtomicU64;4]=[const{AtomicU64::new(0)};4];
fn r19_known(p:usize,d:usize,cap:usize,known:usize)->usize{
 R19_COUNTS[0].fetch_add(1,Ordering::Relaxed);let cache=R19_CACHE.lock().unwrap();let mut k=known;
 if let Some((mp,mb))=&*cache {
  if p+1<mp.len(){R19_COUNTS[1].fetch_add(1,Ordering::Relaxed);
   for &m in &mb[(mp[p]as usize).min(mb.len())..(mp[p+1]as usize).min(mb.len())]{
    if ((m&32767)+1)as usize==d{k=k.max(((((m>>15)&255)+3)as usize).min(cap));}
   }
  }
 }
 if k>known{R19_COUNTS[2].fetch_add(1,Ordering::Relaxed);R19_COUNTS[3].fetch_add((k-known)as u64,Ordering::Relaxed);}k
}
pub fn r19_take()->[u64;4]{std::array::from_fn(|i|R19_COUNTS[i].swap(0,Ordering::Relaxed))}
'''
    build = Path(os.environ['RUNNER_TEMP']) / 'r19-cache-prefix'
    build.mkdir()
    spool = build / 'spool'
    spool.mkdir()
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r19-cache-prefix'
    out.mkdir(parents=True)
    prototype = out / 'diagnostic-only.rs'
    prototype.write_text(text)
    sp = importlib.util.spec_from_file_location('encoder', ROOT / 'scripts/research-round13-encoder-native.py')
    m = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(m)
    upstream = Path(os.environ['DEFLATE_ROOT'])
    codec = upstream / 'validator/measure/src/deflate.rs'
    token = codec.with_name('token.rs')
    harness = m.HARNESS.replace('TOKEN', json.dumps(str(token))).replace('CODEC', json.dumps(str(codec)))
    harness = harness.replace('MODULES', f'#[path={json.dumps(str(frozen))}]mod baseline;\n#[path={json.dumps(str(prototype))}]mod prototype;')
    harness = harness.replace('CASES', '("base603",baseline::parse),("prefix_prototype",prototype::parse)')
    at=harness.rfind('}');harness=harness[:at]+'let c=prototype::r19_take();println!(\"CACHE_PREFIX {} {} {} {}\",c[0],c[1],c[2],c[3]);'+harness[at:]
    driver = build / 'driver.rs'
    driver.write_text(harness)
    binary = build / 'driver'
    c = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], capture_output=True, text=True, timeout=240)
    (out / 'compile.log').write_text(c.stdout + c.stderr)
    assert c.returncode == 0
    corpus = upstream / 'data/benchmark/corpus-stage1'
    r = subprocess.run([str(binary), str(corpus), str(spool)], capture_output=True, text=True, timeout=240)
    (out / 'run.log').write_text(r.stdout + r.stderr)
    assert r.returncode == 0
    rows = []
    for line in r.stdout.splitlines():
        if line.startswith('ENCODER_NATIVE '):
            _, index, name, program, nb, nt = line.split()
            inp = (corpus / name).read_bytes()
            encoded = (spool / f'{index}-{program}.deflate').read_bytes()
            tokens = (spool / f'{index}-{program}.tokens').read_bytes()
            assert len(encoded) == int(nb) and len(tokens) == 4 * int(nt) and zlib.decompress(encoded, -15) == inp
            rows.append({'file': name, 'program': program, 'raw_bytes': len(inp), 'input_sha256': hashlib.sha256(inp).hexdigest(),
                'output_bytes': len(encoded), 'tokens_sha256': hashlib.sha256(tokens).hexdigest(), 'output_sha256': hashlib.sha256(encoded).hexdigest()})
    assert len(rows) == 56
    totals = {name: sum(r['output_bytes'] for r in rows if r['program'] == name) for name in ['base603', 'prefix_prototype']}
    assert totals['base603'] == 4864300
    base={row['file']:row for row in rows if row['program']=='base603'}
    assert all(all(row[key]==base[row['file']][key] for key in ('output_bytes','tokens_sha256','output_sha256'))for row in rows if row['program']=='prefix_prototype')
    count_line=next(line for line in r.stdout.splitlines()if line.startswith('CACHE_PREFIX '))
    counts=dict(zip(('queries','A_cache_queries','longer_known_prefix','additional_known_prefix_bytes'),map(int,count_line.split()[1:])))
    record = {'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'status': 'VERIFIED_DIAGNOSTIC_ORIGINAL_ENCODER_AND_DECODE',
        'frozen_source_sha256': entry['hashes']['parse.rs'], 'prototype_sha256': hashlib.sha256(prototype.read_bytes()).hexdigest(),
        'codec_sha256': hashlib.sha256(codec.read_bytes()).hexdigest(), 'rows': rows, 'totals': totals, 'prefix_counts': counts,
        'scope': 'Exact28-file quality and query-count diagnostic only: originalSFchain/search retained; same-distance base matches increase known prefix, uncached searches unchanged. GlobalMutex/clones make this NOT an eligible candidate or proof. Need explicitcache-lifetime implementation, realtotal timings, newproof and independentconfirmation before promotion.'}
    (out / 'quality.json').write_text(json.dumps(record, indent=2) + '\n')
    print(json.dumps({'totals':totals,'counts':counts}))


if __name__ == '__main__':
    main()
