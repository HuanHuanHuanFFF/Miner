"""Untimed coverage of SF alternatives by the actual base A match cache."""
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
    marker = 'a_find_all(input, &mut mp, &mut mb, depth, skip);'
    assert text.count(marker) == 1
    text = text.replace(marker, marker + '\n    *R19_CACHE.lock().unwrap()=Some((mp.clone(),mb.clone()));')
    marker = 'pub fn parse(input: &[u8], out: &mut [u32]) -> usize {'
    assert text.count(marker) == 1
    text = text.replace(marker, marker + '\n    *R19_CACHE.lock().unwrap()=None;')
    marker = 'q9_push_guarded(items,best[c%8]);'
    assert text.count(marker) == 1
    text = text.replace(marker, 'r19_cover(input,p,best[c%8],ot);' + marker)
    text += r'''
use std::sync::{Mutex,atomic::{AtomicU64,Ordering}};
static R19_CACHE:Mutex<Option<(Vec<u32>,Vec<u32>)>>=Mutex::new(None);
static R19_COUNTS:[AtomicU64;7]=[const{AtomicU64::new(0)};7];
fn r19_hit(i:usize,n:u64){R19_COUNTS[i].fetch_add(n,Ordering::Relaxed);}
pub fn r19_take()->[u64;7]{std::array::from_fn(|i|R19_COUNTS[i].swap(0,Ordering::Relaxed))}
fn r19_cover(input:&[u8],p:usize,t:u32,ot:u32){
 r19_hit(0,1);let cache=R19_CACHE.lock().unwrap();
 if let Some((mp,mb))=&*cache {
  if mp.len()!=input.len()+1||p+1>=mp.len(){return;}r19_hit(1,1);
  let l=SFlen(t);let d=SFdist(t);let dc=q9_dslot(d);
  if ot!=0&&SFlen(ot)>=l&&q9_dslot(SFdist(ot))==dc {r19_hit(2,1);return;}
  r19_hit(3,1);let mut exact=false;let mut same=false;
  for &m in &mb[(mp[p] as usize).min(mb.len())..(mp[p+1] as usize).min(mb.len())] {
   let ml=(((m>>15)&255)+3)as usize;let md=((m&32767)+1)as usize;
   if ml>=l&&md<=p&&p+l<=input.len()&&input[p-md..p-md+l]==input[p..p+l] {
    if md==d{exact=true;}if q9_dslot(md)==dc{same=true;}
   }
  }
  if exact{r19_hit(4,1);}if same{r19_hit(5,1);}else{r19_hit(6,1);}
 }
}
'''
    build = Path(os.environ['RUNNER_TEMP']) / 'r19-cache-build'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r19-sf-cache'
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
            rows.append({'file': name, 'raw_bytes': int(size), 'counts': v})
    assert len(rows) == 28
    fields=['retained_sf_items','on_A_engine_inputs','covered_by_seed_same_code','extra_items','base_cache_exact_distance','base_cache_same_distance_code','not_covered_by_base_cache']
    totals={field:sum(row['counts'][i] for row in rows) for i,field in enumerate(fields)}
    result = {'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'source_hashes': entry['hashes'],
        'observer_sha256': hashlib.sha256(text.encode()).hexdigest(), 'status': 'VERIFIED_UNTIMED_COUNTER_TOKEN_AND_DECODE_EQUAL',
        'rows': rows, 'totals': totals, 'scope': 'Actual frozen603 base A cache captured in an observer; coverage checked against input bytes, original full-parser tokens and decode equal. Only A-engine inputs are eligible; seed-covered items are excluded from extra-match coverage. Counter evidence is not a candidate, proof, or timing improvement; state-transfer cost and quality preservation remain untested.'}
    (out / 'counts.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(totals))


if __name__ == '__main__':
    main()
