"""Observe exact/lower-bound A tree edge prefixes without changing original decisions."""
from pathlib import Path
import argparse
from datetime import datetime, timezone
import hashlib
import importlib
import json
import os
import subprocess
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
EXPECTED = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
FIELDS = ['finder_calls', 'finder_bytes', 'tree_calls', 'probe_calls', 'probe_word_pairs',
          'incoming_links', 'shortcut_calls', 'shortcut_word_pairs', 'shortcut_edge_shorter',
          'shortcut_query_shorter', 'equal_prefix_fallback', 'lower_bound_fallback',
          'edge_reads', 'edge_writes', 'copy_downgrades', 'expired_links']

EXTRA = '''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_EDGE_COUNTS:[AtomicU64;16]=[const{AtomicU64::new(0)};16];
fn r26_edge_hit(i:usize,v:u64){R26_EDGE_COUNTS[i].fetch_add(v,Ordering::Relaxed);}
pub fn r26_edge_take()->[u64;16]{std::array::from_fn(|i|R26_EDGE_COUNTS[i].swap(0,Ordering::Relaxed))}
fn r26_edge_join(l:usize,tag:u32)->u32 {
 let t=(tag&511)as usize;let low=if l<t{l}else{t};
 let exact=(l<t&&l<258)||(t<l&&(tag&512)!=0);
 (low as u32)|if exact{512}else{0}
}
fn r26_edge_pair(l:usize,p:usize)->u32 {
 let low=if l<p{l}else{p};(low as u32)|if l!=p&&low<258{512}else{0}
}
'''


def sha(data):
    return hashlib.sha256(data).hexdigest()


def instrument(raw):
    assert sha(raw) == EXPECTED
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    source = raw.decode()
    old = fn(source, 'a_tree_insert')
    part = old.replace('    pos: usize,', '    edge: &mut [u32; 65536],\n    pos: usize,', 1)
    needle = '    let mut steps = 0usize;'
    assert part.count(needle) == 1
    part = part.replace(needle, needle + '\n    let mut incoming=0u32;let mut last_l=0usize;let mut last_cmp=0usize;let mut linked=false;\n    let mut cnt=[0u64;16];cnt[2]=1;')
    probe = '        let r = a_probe(s, p, pos, if lo_len < hi_len { lo_len } else { hi_len });'
    assert part.count(probe) == 1
    replacement = '''        let seed=if lo_len<hi_len{lo_len}else{hi_len};
        let r = a_probe(s, p, pos, seed);
        cnt[3]+=1;
        let pairs=if r.0<258{1+(r.0-seed)/8}else{1+if seed<250{(250-seed+7)/8}else{0}};
        cnt[4]+=pairs as u64;
        if linked {
            cnt[5]+=1;let t=(incoming&511)as usize;
            let shortcut=((incoming&512)!=0&&t<last_l)||t>last_l;
            if shortcut {
                let predicted=if t<last_l{(t,1-last_cmp)}else{(last_l,last_cmp)};
                assert_eq!(r,predicted,"edge={} last={} cmp={} pos={} p={} seed={}",incoming,last_l,last_cmp,pos,p,seed);
                assert!(predicted.0>=seed);
                cnt[6]+=1;cnt[7]+=pairs as u64;cnt[if t<last_l{8}else{9}]+=1;
            }else if t==last_l{cnt[10]+=1;}else{cnt[11]+=1;}
        }
'''
    part = part.replace(probe, replacement.rstrip())
    copy = '            kid[lo_at % 65536] = kid[pk % 65536];\n            kid[hi_at % 65536] = kid[(pk + 1) % 65536];'
    assert part.count(copy) == 1
    part = part.replace(copy, '''            let t0=edge[pk%65536];let t1=edge[(pk+1)%65536];
            let pl0=if lo_at==2*(pos%32768){258}else{lo_len};
            let pl1=if hi_at==2*(pos%32768)+1{258}else{hi_len};
            let e0=r26_edge_join(pl0,r26_edge_join(l,t0));let e1=r26_edge_join(pl1,r26_edge_join(l,t1));
            cnt[12]+=2;cnt[13]+=2;cnt[14]+=((t0&512)!=0&&(e0&512)==0)as u64;cnt[14]+=((t1&512)!=0&&(e1&512)==0)as u64;
            edge[lo_at%65536]=e0;edge[hi_at%65536]=e1;
''' + copy)
    lower = '            kid[lo_at % 65536] = cur as u32;\n            lo_at = pk + 1;\n            lo_len = l;\n            cur = kid[lo_at % 65536] as usize;'
    upper = '            kid[hi_at % 65536] = cur as u32;\n            hi_at = pk;\n            hi_len = l;\n            cur = kid[hi_at % 65536] as usize;'
    for original, at, length, nxt in [(lower, 'lo_at', 'lo_len', 'pk + 1'), (upper, 'hi_at', 'hi_len', 'pk')]:
        assert part.count(original) == 1
        root_at = '2*(pos%32768)' if at == 'lo_at' else '2*(pos%32768)+1'
        part = part.replace(original, f'''            let parent_l=if {at}=={root_at}{{258}}else{{{length}}};
            edge[{at}%65536]=r26_edge_pair(l,parent_l);cnt[13]+=1;
            kid[{at} % 65536] = cur as u32;
            {at} = {nxt};
            {length} = l;
            incoming=edge[{at}%65536];cnt[12]+=1;last_l=l;last_cmp=r.1;linked=true;
            cur = kid[{at} % 65536] as usize;''')
    ending = '        kid[lo_at % 65536] = 0;\n        kid[hi_at % 65536] = 0;'
    assert part.count(ending) == 1
    part = part.replace(ending, ending + '\n        edge[lo_at%65536]=0;edge[hi_at%65536]=0;cnt[13]+=2;')
    assert part.count('    best\n}') == 1
    part = part.replace('    best\n}', '    if cur>0&&(cur<=oldest||cur>pos){cnt[15]+=1;}\n    let mut ci=2usize;while ci<16{r26_edge_hit(ci,cnt[ci]);ci+=1;}\n    best\n}', 1)
    source = source.replace(old, part, 1)
    old = fn(source, 'a_find_all')
    part = old.replace('    let n = s.len();', '    let n = s.len();\n    r26_edge_hit(0,1);r26_edge_hit(1,n as u64);\n    let mut edge=[0u32;65536];', 1)
    needle = 'a_tree_insert(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb)'
    assert part.count(needle) == 1
    part = part.replace(needle, 'a_tree_insert(s, &mut head, &mut kid, &mut h3, &mut rct, &mut edge, i, pre, depth, mb)', 1)
    source = source.replace(old, part, 1) + EXTRA
    importlib.import_module('r26-b-fix-shared-cache').spans(source)
    return source.encode()


def preflight(spec):
    assert spec['r26_b_tree_edge_counts'] is True and spec['native_encoder'] is False
    assert spec['native_only'] is True and all(e['control'] for e in spec['entries'])
    entry = next(e for e in spec['entries'] if e['name'] == 'public552')
    raw = (ROOT / entry['path'] / 'parse.rs').read_bytes()
    assert sha(raw) == entry['hashes']['parse.rs'] == EXPECTED
    observed = instrument(raw)
    result = {'status': 'VERIFIED_INSTRUMENTATION_STRUCTURE_ONLY', 'computed_utc': datetime.now(timezone.utc).isoformat(),
              'source_sha256': sha(raw), 'observer_sha256': sha(observed), 'observer_bytes': len(observed),
              'scope': 'No native compilation, query equality or complete gate yet. Original matcher still determines every result.'}
    return result


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', type=Path)
    ap.add_argument('--output', type=Path)
    a = ap.parse_args()
    if a.check:
        result = preflight(json.loads(a.check.read_bytes()))
        if a.output:
            assert not a.output.exists()
            a.output.write_text(json.dumps(result, indent=2) + '\n')
        print(json.dumps(result))
        return
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    from round4 import validate
    spec = validate(os.environ['ROUND4_SPEC'])
    preflight(spec)
    entry = next(e for e in spec['entries'] if e['name'] == 'public552')
    frozen = ROOT / entry['path'] / 'parse.rs'
    raw = frozen.read_bytes()
    build = Path(os.environ['RUNNER_TEMP']) / 'r26-b-tree-edge'
    build.mkdir(exist_ok=False)
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r26-b-tree-edge'
    out.mkdir(parents=True, exist_ok=False)
    observed = build / 'observed.rs'
    observed.write_bytes(instrument(raw))
    harness = importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN', str(frozen)).replace('OBSERVED', str(observed))
    harness = harness.replace('observed::r13_take()', 'observed::r26_edge_take()').replace('R13_COUNT', 'R26_TREE_EDGE')
    driver = build / 'check.rs'
    driver.write_text(harness)
    binary = build / 'check'
    c = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], capture_output=True, text=True, timeout=240)
    (out / 'compile.log').write_text(c.stdout + c.stderr)
    assert c.returncode == 0
    corpus = Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1'
    run = subprocess.run([str(binary), str(corpus)], capture_output=True, text=True, timeout=480)
    (out / 'run.log').write_text(run.stdout + run.stderr)
    assert run.returncode == 0
    rows = []
    for line in run.stdout.splitlines():
        if line.startswith('R26_TREE_EDGE '):
            _, name, size, *values = line.split()
            assert len(values) == len(FIELDS)
            data = (corpus / name).read_bytes()
            assert len(data) == int(size)
            rows.append({'file': name, 'raw_bytes': len(data), 'input_sha256': sha(data), 'counts': dict(zip(FIELDS, map(int, values)))})
    assert len(rows) == 28 and sum(r['raw_bytes'] for r in rows) == 15930000
    totals = {f: sum(r['counts'][f] for r in rows) for f in FIELDS}
    assert totals['shortcut_calls'] == totals['shortcut_edge_shorter'] + totals['shortcut_query_shorter']
    result = {'status': 'VERIFIED_ORIGINAL_A_EDGE_SHORTCUT_TUPLES_AND_TOKEN_DECODE_PARITY',
              'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'source_hashes': entry['hashes'],
              'observer_sha256': sha(observed.read_bytes()), 'harness_sha256': sha(driver.read_bytes()),
              'totals': totals, 'rows': rows,
              'limits': ['Original a_probe still executes and determines every tree decision; no candidate speed/quality/gate claim.',
                         'Shortcut tuples are asserted at each eligible active link; metadata only follows original rewiring and capped NICE copying.',
                         'Word pair counts model the original a_probe loop from exact returned length and seed; these are operations, not measured nanoseconds.',
                         'Edge reads/writes, extra 256KiB array clearing and packing are production burdens if later implemented.',
                         'Original28 tokens plus independent decode are finite checks; original encoder total-time and exact Rust/Lean gate still required.']}
    (out / 'receipt.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({'status': result['status'], 'totals': totals}))


if __name__ == '__main__':
    main()
