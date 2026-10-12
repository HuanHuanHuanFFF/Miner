"""Actual flattened DP call full-state equivalence and real fill/scan burden, no clocks."""
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
NAME = 'r26-b-552-a-flatten'
EXPECTED = 'e609a1aee215165a8df155ab124dbaa538fbd5111d956098cce4154431cd72f9'
PARENT = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
FIELDS = ['dp_calls', 'positions', 'normal_positions', 'odd_fallback_positions', 'inherited_extension_positions',
          'fill_calls', 'fill_requested_slots', 'fill_written_slot_pairs', 'rounded_scan_slots', 'valid_scan_slots',
          'normal_no_match_positions', 'cloned_cost_ch_bytes', 'asserted_complete_cost_ch_dp_calls',
          'unused', 'max_cost_words', 'complete_cost_ch_words_compared']
EXTRA = '''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_FLAT:[AtomicU64;16]=[const{AtomicU64::new(0)};16];
fn r26_flat_hit(i:usize,n:u64){R26_FLAT[i].fetch_add(n,Ordering::Relaxed);}
pub fn r26_flat_take()->[u64;16]{std::array::from_fn(|i|R26_FLAT[i].swap(0,Ordering::Relaxed))}
#[inline(never)]
pub fn a_dp_pass(s:&[u8],mp:&Vec<u32>,mb:&Vec<u32>,p0:usize,pe:usize,lit:&[u32;256],lc:&[u32;512],dc:&[u32;32],cost:&mut Vec<u32>,ch:&mut Vec<u32>) {
 let mut old_cost=cost.clone();let mut old_ch=ch.clone();
 r26_flat_hit(0,1);r26_flat_hit(11,((old_cost.len()+old_ch.len())*4)as u64);
 R26_FLAT[14].fetch_max(cost.len()as u64,Ordering::Relaxed);
 r26_a_dp_pass_core(s,mp,mb,p0,pe,lit,lc,dc,cost,ch);
 crate::parent::a_dp_pass(s,mp,mb,p0,pe,lit,lc,dc,&mut old_cost,&mut old_ch);
 assert_eq!(cost.as_slice(),old_cost.as_slice(),"cost entire DP p0={} pe={} n={}",p0,pe,s.len());
 assert_eq!(ch.as_slice(),old_ch.as_slice(),"choice entire DP p0={} pe={} n={}",p0,pe,s.len());
 r26_flat_hit(12,1);r26_flat_hit(15,(cost.len()+ch.len())as u64);
}
#[inline(always)]
pub fn a_fill(bl:&mut[u32;1024],dl:&mut[u32;1024],from:usize,to:usize,base:u32,d:u32) {
 r26_flat_hit(5,1);
 if to>=from{let n=to-from+1;r26_flat_hit(6,n as u64);r26_flat_hit(7,(((n+7)/8)*8)as u64);}
 r26_a_fill_core(bl,dl,from,to,base,d);
}
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw) == EXPECTED
    source = raw.decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    old = fn(source, 'a_dp_pass')
    part = old.replace('pub fn a_dp_pass(', 'pub fn r26_a_dp_pass_core(', 1)
    part = part.replace('    let cl = cost.len();', '    let cl = cost.len();let mut cnt=[0u64;16];', 1)
    part = part.replace('            i -= 1;', '            i -= 1;cnt[1]+=1;', 1)
    marker = '            let ext = xl >= 3 && xd >= 1 && xd <= i && i + el > prev && s[i] == s[i - xd];'
    assert part.count(marker) == 1
    part = part.replace(marker, marker+'\n            if ext{cnt[4]+=1;}', 1)
    marker = '            if p.2 {'
    assert part.count(marker) == 1
    part = part.replace(marker, '            if p.2 {\n                cnt[3]+=1;', 1)
    marker = '                let mut hi = prev - i;'
    assert part.count(marker) == 1
    part = part.replace(marker, '                cnt[2]+=1;\n'+marker, 1)
    marker = '                let r = a_dp_min(cost, lc, &bl, i, hi);'
    assert part.count(marker) == 1
    part = part.replace(marker, '''                if hi>=3&&hi<=258{cnt[8]+=(((hi-3)/8+1)*8)as u64;cnt[9]+=(hi-2)as u64;}else{cnt[10]+=1;}
''' + marker, 1)
    assert part.endswith('}\n')
    part = part[:-2]+'    for i in [1usize,2,3,4,8,9,10]{r26_flat_hit(i,cnt[i]);}\n}\n'
    source = source.replace(old, part, 1)
    old = fn(source, 'a_fill')
    source = source.replace(old, old.replace('pub fn a_fill(', 'pub fn r26_a_fill_core(', 1), 1)+EXTRA
    importlib.import_module('r26-b-fix-shared-cache').spans(source)
    return source.encode()


def preflight(spec):
    assert spec.get('r26_b_a_flatten_counts') is True and spec.get('native_encoder') is True
    assert spec.get('r18_function_profile') is True and spec['r15_profile_entry']==NAME
    entry = next(e for e in spec['entries'] if e['name']==NAME)
    parent = next(e for e in spec['entries'] if e['name']=='public552')
    assert parent['hashes']['parse.rs'] == PARENT
    assert sha((ROOT/parent['path']/'parse.rs').read_bytes()) == PARENT
    raw = (ROOT/entry['path']/'parse.rs').read_bytes()
    assert sha(raw) == entry['hashes']['parse.rs'] == EXPECTED
    observed = instrument(raw)
    return {'status': 'VERIFIED_ACTUAL_A_CALL_FULL_COST_CH_REFERENCE_OBSERVER_STRUCTURE_ONLY',
            'computed_utc': datetime.now(timezone.utc).isoformat(), 'source_hashes': entry['hashes'],
            'parent_hashes': parent['hashes'], 'observer_sha256': sha(observed),
            'scope': 'Every actual sampled/full invocation under actual costs/interval compares complete cost/ch arrays with original552; fill/scan operation counts are diagnostic only.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec = importlib.import_module('round4').validate(os.environ['ROUND4_SPEC'])
    preflight(spec)
    entry = next(e for e in spec['entries'] if e['name']==NAME)
    parent = next(e for e in spec['entries'] if e['name']=='public552')
    frozen = ROOT/entry['path']/'parse.rs'
    build = Path(os.environ['RUNNER_TEMP'])/'r26-b-a-flatten'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-a-flatten'
    out.mkdir(parents=True)
    observed = build/'observed.rs'
    observed.write_bytes(instrument(frozen.read_bytes()))
    h = importlib.import_module('research-round13-counts').HARNESS
    h = h.replace('#[path="FROZEN"] mod frozen;', '#[path="PARENT"] mod parent;\n#[path="FROZEN"] mod frozen;')
    h = h.replace('PARENT', str(ROOT/parent['path']/'parse.rs')).replace('FROZEN', str(frozen)).replace('OBSERVED', str(observed))
    h = h.replace('observed::r13_take()', 'observed::r26_flat_take()').replace('R13_COUNT', 'R26_A_FLATTEN')
    driver = build/'check.rs'
    driver.write_text(h)
    binary = build/'check'
    c = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], capture_output=True, text=True, timeout=240)
    (out/'compile.log').write_text(c.stdout+c.stderr)
    assert c.returncode==0
    corpus = Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    r = subprocess.run([str(binary), str(corpus)], capture_output=True, text=True, timeout=480)
    (out/'run.log').write_text(r.stdout+r.stderr)
    assert r.returncode==0
    rows = []
    for line in r.stdout.splitlines():
        if line.startswith('R26_A_FLATTEN '):
            _, name, size, *values = line.split()
            assert len(values)==len(FIELDS)
            data = (corpus/name).read_bytes()
            assert len(data)==int(size)
            counts = dict(zip(FIELDS, map(int,values)))
            assert counts['dp_calls']==counts['asserted_complete_cost_ch_dp_calls']
            assert counts['normal_positions']+counts['odd_fallback_positions']==counts['positions']
            rows.append({'file': name, 'raw_bytes': len(data), 'input_sha256': sha(data), 'counts': counts})
    assert len(rows)==28 and sum(r['raw_bytes'] for r in rows)==15930000
    totals = {f: (max(r['counts'][f] for r in rows) if f=='max_cost_words' else sum(r['counts'][f] for r in rows)) for f in FIELDS}
    result = {'status': 'VERIFIED_ACTUAL_ALL_A_DP_CALLS_FULL_COST_CH_PARENT_EQUAL_AND_TOKEN_DECODE_PARITY',
              'computed_utc': datetime.now(timezone.utc).isoformat(), 'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'],
              'source_hashes': entry['hashes'], 'parent_hashes': parent['hashes'],
              'observer_sha256': sha(observed.read_bytes()), 'harness_sha256': sha(driver.read_bytes()), 'rows': rows, 'totals': totals,
              'limits': ['Full original cost/ch arrays compared after every actual sampled/full call under same source input/mp/mb/interval/prices and cloned initial vectors.',
                         'Original DP recomputation/cloning/assertions/atomic counters exist only in observer; pure production profile is separately compiled from exact candidate.',
                         'Scratch pair slots count one slot in each of bl/dl; actual two U32 stores and overshoots remain production costs, including odd fallback.',
                         'Finite original28encoder/token/decode and full-state parity do not replace exact extraction/original obligation/fullgate or frozen total-time confirmation.']}
    (out/'receipt.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'status':result['status'],'totals':totals}))


if __name__=='__main__':
    main()
