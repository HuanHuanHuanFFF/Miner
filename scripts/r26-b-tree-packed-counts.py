"""Actual fixed31 packed tree-prefix consumer audit and lost long-prefix coverage."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import os
import subprocess
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
NAME = 'r26-b-552-tree-packed'
EXPECTED = '8d048a0797943c307501c7fb14eb92822668875d39c0e531e0c0f7396c99d682'
FIELDS = ['probe_calls', 'original_word_pairs', 'shortcut_calls', 'shortcut_word_pairs',
          'raised_seed_calls', 'raised_seed_bytes', 'raised_seed_saved_word_pairs', 'fallback_word_pairs',
          'capped258_unused_direction_differences', 'prefix31_bound_queries', 'prefix31_exact_queries',
          'prefix31_bound_longmatch_queries', 'pack_calls', 'unpack_calls', 'max_low26_timestamp', 'finder_calls']
EXTRA = '''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_PACKED:[AtomicU64;16]=[const{AtomicU64::new(0)};16];
fn r26_packed_hit(i:usize,n:u64){R26_PACKED[i].fetch_add(n,Ordering::Relaxed);}
pub fn r26_packed_take()->[u64;16]{std::array::from_fn(|i|R26_PACKED[i].swap(0,Ordering::Relaxed))}
#[inline(always)]
pub fn a_edge_probe(s:&[u8],p:usize,q:usize,seed:usize,tag:u16,last_l:usize,last_cmp:usize)->(usize,usize) {
 assert!(s.len()<67108864);
 let old=a_probe(s,p,q,seed);
 let result=a_edge_probe_core(s,p,q,seed,tag,last_l,last_cmp);
 assert_eq!(result.0,old.0,"packed length p={} q={} seed={} tag={}",p,q,seed,tag);
 if old.0<258{assert_eq!(result.1,old.1,"packed side p={} q={} seed={} tag={}",p,q,seed,tag);}
 assert!(old.0>=seed);
 let pairs=if old.0<258{1+(old.0-seed)/8}else{1+if seed<250{(250-seed+7)/8}else{0}};
 r26_packed_hit(0,1);r26_packed_hit(1,pairs as u64);
 r26_packed_hit(8,((old.0==258)&&(old.1!=result.1))as u64);
 let t=(tag&511)as usize;let exact=(tag&512)!=0;
 if t==31{r26_packed_hit(if exact{10}else{9},1);if !exact&&old.0>31{r26_packed_hit(11,1);}}
 let shortcut=(exact&&t<last_l)||t>last_l;
 if shortcut{r26_packed_hit(2,1);r26_packed_hit(3,pairs as u64);}
 else{
  let low=if t<last_l{t}else{last_l};let raised=if low>seed{low}else{seed};
  let raised=if raised>258{258}else{raised};
  let nowpairs=if result.0<258{1+(result.0-raised)/8}else{1+if raised<250{(250-raised+7)/8}else{0}};
  assert!(nowpairs<=pairs);r26_packed_hit(7,nowpairs as u64);
  if raised>seed{r26_packed_hit(4,1);r26_packed_hit(5,(raised-seed)as u64);r26_packed_hit(6,(pairs-nowpairs)as u64);}
 }
 result
}
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw) == EXPECTED
    source = raw.decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    old = fn(source, 'a_edge_probe')
    source = source.replace(old, old.replace('pub fn a_edge_probe(', 'pub fn a_edge_probe_core(', 1), 1)
    for name, marker in [('a_edge_pack', 'r26_packed_hit(12,1);R26_PACKED[14].fetch_max((child&67108863)as u64,Ordering::Relaxed);'),
                         ('a_edge_unpack', 'r26_packed_hit(13,1);')]:
        old = fn(source, name)
        at = old.index('{')+1
        source = source.replace(old, old[:at]+'\n '+marker+'\n'+old[at:], 1)
    old = fn(source, 'a_find_all')
    source = source.replace(old, old.replace('    let n = s.len();', '    let n = s.len();\n    assert!(n<67108864);r26_packed_hit(15,1);', 1), 1)+EXTRA
    importlib.import_module('r26-b-fix-shared-cache').spans(source)
    return source.encode()


def preflight(spec):
    assert spec.get('r26_b_tree_packed_counts') is True and spec.get('native_encoder') is True
    assert spec.get('r18_function_profile') is True and spec['r15_profile_entry'] == NAME
    entry = next(e for e in spec['entries'] if e['name'] == NAME)
    raw = (ROOT/entry['path']/'parse.rs').read_bytes()
    assert sha(raw) == entry['hashes']['parse.rs'] == EXPECTED
    observed = instrument(raw)
    return {'status': 'VERIFIED_FIXED31_PACKED_CONSUMER_OBSERVER_STRUCTURE_ONLY',
            'computed_utc': datetime.now(timezone.utc).isoformat(), 'source_hashes': entry['hashes'],
            'observer_sha256': sha(observed), 'scope': 'Every real helper consumer compared to exact original a_probe, capped258 direction separately retained; actual coverage not run yet.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = importlib.import_module('round4').validate(os.environ['ROUND4_SPEC'])
    preflight(spec)
    entry = next(e for e in spec['entries'] if e['name'] == NAME)
    frozen = ROOT/entry['path']/'parse.rs'
    build = Path(os.environ['RUNNER_TEMP'])/'r26-b-tree-packed'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-tree-packed'
    out.mkdir(parents=True)
    observed = build/'observed.rs'
    observed.write_bytes(instrument(frozen.read_bytes()))
    h = importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN', str(frozen)).replace('OBSERVED', str(observed)).replace('observed::r13_take()', 'observed::r26_packed_take()').replace('R13_COUNT', 'R26_TREE_PACKED')
    driver = build/'check.rs'
    driver.write_text(h)
    binary = build/'check'
    c = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], capture_output=True, text=True, timeout=240)
    (out/'compile.log').write_text(c.stdout+c.stderr)
    assert c.returncode == 0
    corpus = Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    r = subprocess.run([str(binary), str(corpus)], capture_output=True, text=True, timeout=480)
    (out/'run.log').write_text(r.stdout+r.stderr)
    assert r.returncode == 0
    prior_path = ROOT/'evidence/round26/38216239816/tree-b20-native/diagnostics/r26-b-tree-edge/receipt.json'
    prior = json.loads(prior_path.read_bytes())
    prior_rows = {r['file']: r for r in prior['rows']}
    rows = []
    for line in r.stdout.splitlines():
        if line.startswith('R26_TREE_PACKED '):
            _, name, size, *values = line.split()
            assert len(values) == len(FIELDS)
            data = (corpus/name).read_bytes()
            assert len(data) == int(size)
            counts = dict(zip(FIELDS, map(int, values)))
            old = prior_rows[name]
            assert sha(data) == old['input_sha256'] and counts['probe_calls'] == old['counts']['probe_calls']
            assert counts['original_word_pairs'] == old['counts']['probe_word_pairs']
            saved = counts['shortcut_word_pairs'] + counts['raised_seed_saved_word_pairs']
            full_saved = old['counts']['shortcut_word_pairs']+old['counts']['seed_saved_word_pairs']
            rows.append({'file': name, 'raw_bytes': len(data), 'input_sha256': sha(data), 'counts': counts,
                         'saved_word_pairs': saved, 'full_prefix_B20_saved_word_pairs': full_saved,
                         'lost_word_pairs_after_fixed31_cap': full_saved-saved})
    assert len(rows) == 28 and sum(r['raw_bytes'] for r in rows) == 15930000
    totals = {f: (max(r['counts'][f] for r in rows) if f=='max_low26_timestamp' else sum(r['counts'][f] for r in rows)) for f in FIELDS}
    saved, full_saved = sum(r['saved_word_pairs'] for r in rows), sum(r['full_prefix_B20_saved_word_pairs'] for r in rows)
    assert totals['max_low26_timestamp'] < 67108864
    result = {'status': 'VERIFIED_ACTUAL_FIXED31_CONSUMPTION_ORIGINAL_QUERY_AND_TOKEN_DECODE_PARITY',
              'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'source_hashes': entry['hashes'],
              'observer_sha256': sha(observed.read_bytes()), 'harness_sha256': sha(driver.read_bytes()),
              'rows': rows, 'totals': totals, 'saved_word_pairs': saved, 'full_prefix_B20_saved_word_pairs': full_saved,
              'lost_word_pairs_after_fixed31_cap': full_saved-saved,
              'B20_receipt_sha256': sha(prior_path.read_bytes()),
              'limits': ['All frozen/observed28tokens and independent decode match; per-helper length/direction below258 matches exact original a_probe.',
                         'Production retains only original kid memory operations, plus mask/pack/join cost; this observer adds atomics and original probe solely for correctness/counts.',
                         'Actual opportunity losses use same per-file input hashes and exact original probe/wordpair counts as B20; counts are not net original total speed.',
                         'Capped258 direction is unused by NICE-copy; timestamps domain tied to original s_plan2^26 guard. Finite parity is not complete gate/admission.']}
    (out/'receipt.json').write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({'status': result['status'], 'saved_word_pairs': saved, 'lost_word_pairs_after_fixed31_cap': full_saved-saved, 'totals': totals}))


if __name__ == '__main__':
    main()
