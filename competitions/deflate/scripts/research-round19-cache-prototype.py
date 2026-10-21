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
    marker = 'pub fn SFsmallmatches('
    assert text.count(marker) == 1
    text = text.replace(marker, 'pub fn SFsmallmatches_original(')
    text += r'''
use std::sync::Mutex;
static R19_CACHE:Mutex<Option<(Vec<u32>,Vec<u32>)>>=Mutex::new(None);
pub fn SFsmallmatches(input:&[u8],prev:&[u32],orig:&[u32],ct:&[u32;1024],a:usize,e:usize,items:&mut Vec<u32>,starts:&mut Vec<u32>){
 let cache=R19_CACHE.lock().unwrap();
 if let Some((mp,mb))=&*cache {
  if mp.len()==input.len()+1 {
   let mut p=a;
   while p<e {
    q9_push_guarded(starts,items.len() as u32);let mut best=[0u32;8];let ot=q9_get(orig,p.wrapping_sub(a));let mut count=0usize;
    if ot!=0{count=SFsmalladd(&mut best,count,ot);}
    let lo=q9_get(mp,p) as usize;let hi=q9_get(mp,p+1) as usize;
    for &m in &mb[lo.min(mb.len())..hi.min(mb.len())] {
     let l=((((m>>15)&255)+3)as usize).min(e-p);let d=((m&32767)+1)as usize;
     if l>=3 {count=SFsmalladd(&mut best,count,SFmt(d,l));}
    }
    let mut c=0usize;while c<count&&c<4{if SFsmallkeep(&best,count,c,ct){q9_push_guarded(items,best[c%8]);}c+=1;}p+=1;
   }
   q9_push_guarded(starts,items.len() as u32);return;
  }
 }
 SFsmallmatches_original(input,prev,orig,ct,a,e,items,starts)
}
'''
    build = Path(os.environ['RUNNER_TEMP']) / 'r19-cache-prototype'
    build.mkdir()
    spool = build / 'spool'
    spool.mkdir()
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r19-cache-prototype'
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
    harness = harness.replace('CASES', '("base603",baseline::parse),("cache_prototype",prototype::parse)')
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
    totals = {name: sum(r['output_bytes'] for r in rows if r['program'] == name) for name in ['base603', 'cache_prototype']}
    assert totals['base603'] == 4864300
    record = {'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'status': 'VERIFIED_DIAGNOSTIC_ORIGINAL_ENCODER_AND_DECODE',
        'frozen_source_sha256': entry['hashes']['parse.rs'], 'prototype_sha256': hashlib.sha256(prototype.read_bytes()).hexdigest(),
        'codec_sha256': hashlib.sha256(codec.read_bytes()).hexdigest(), 'rows': rows, 'totals': totals,
        'scope': 'Quality only: prototype uses diagnostic global Mutex and cloned caches, retains original SF search on non-A routes, and is NOT an eligible candidate or a proof. No timing, private quality or reward claim. A real implementation needs explicit cache lifetime and bounded proof-compatible interfaces.'}
    (out / 'quality.json').write_text(json.dumps(record, indent=2) + '\n')
    print(json.dumps(totals))


if __name__ == '__main__':
    main()
