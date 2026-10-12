"""Read-only original A continuation overlaps, byte validity and original packed-best gaps."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import subprocess

ROOT = Path(__file__).resolve().parents[1]
EXPECTED = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
FIELDS = ['dp_calls', 'positions', 'inherited_guard_positions', 'byte_valid_positions',
          'byte_invalid_positions', 'byte_checked_terms', 'overlap_variable_domains',
          'overlap_original_length_terms', 'overlap_fixed_points',
          'strict_cheaper_covered_domains', 'strict_cheaper_covered_terms',
          'fixed_only_missing_domains', 'fixed_only_missing_terms', 'candidate_query_terms',
          'query_shift_high_discard_terms', 'lowprice_best_improving_positions',
          'lowprice_samecost_tie_positions', 'lowprice_packed_gap_units',
          'fixedgap_best_improving_positions', 'fixedgap_packed_gap_units',
          'either_best_improving_positions', 'either_packed_gap_units',
          'original_uncovered_extension_positions', 'eligible_intersection_positions',
          'all_record_visits', 'full_match_check_calls', 'fixedgap_samecost_tie_positions',
          'either_samecost_tie_positions']

EXTRA = '''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_A_OVERLAP:[AtomicU64;28]=[const{AtomicU64::new(0)};28];
pub fn r26_a_overlap_take()->[u64;28]{std::array::from_fn(|i|R26_A_OVERLAP[i].swap(0,Ordering::Relaxed))}
fn r26_a_overlap_query(cost:&Vec<u32>,lc:&[u32;512],i:usize,lo:usize,hi:usize,base:u32,kind:usize,counts:&mut[u64;28],proposals:&mut[u32;2]) {
    let mut l=lo;
    while l<=hi&&l<=258 {
        let sum=cost[i+l].wrapping_add(lc[l%512]).wrapping_add(base);
        let v=(sum<<9)|(l as u32);
        counts[13]+=1;if sum>=8388608{counts[14]+=1;}
        if v<proposals[kind]{proposals[kind]=v;}
        l+=1;
    }
}
fn r26_a_overlap_record(cost:&Vec<u32>,lc:&[u32;512],i:usize,prev:usize,stop:usize,m:u32,owner_price:u32,el:usize,xprice:u32,bias:u32,counts:&mut[u64;28],proposals:&mut[u32;2]) {
    if stop>=cost.len()||stop<i{return;}
    let lo=prev+1-i;let hi=stop-i;let end=if hi<el{hi}else{el};let base=xprice.wrapping_add(bias);
    if m>=0x80000000 {
        if hi<=el {
            counts[8]+=1;
            if xprice<owner_price{counts[9]+=1;counts[10]+=1;r26_a_overlap_query(cost,lc,i,hi,hi,base,0,counts,proposals);}
        }
        // The fixed-only record did not offer these lengths at all.
        let missing_end=if hi>0&&hi-1<end{hi-1}else{end};
        if lo<=missing_end{counts[11]+=1;counts[12]+=(missing_end-lo+1)as u64;r26_a_overlap_query(cost,lc,i,lo,missing_end,base,1,counts,proposals);}
    }else if lo<=end {
        counts[6]+=1;counts[7]+=(end-lo+1)as u64;
        if xprice<owner_price{counts[9]+=1;counts[10]+=(end-lo+1)as u64;r26_a_overlap_query(cost,lc,i,lo,end,base,0,counts,proposals);}
    }
}
'''

BEFORE_RECORDS = '''            r26_counts[1]+=1;
            let r26_el=if xl+1>258{258}else{xl+1};let r26_xd=xd;
            let mut r26_valid=false;
            if xl>=3&&r26_xd>=1&&r26_xd<=i&&r26_el<=s.len()-i&&s[i]==s[i-r26_xd] {
                r26_counts[2]+=1;r26_counts[25]+=1;r26_counts[5]+=r26_el as u64;
                r26_valid=check(s,i,r26_el,r26_xd);
                if r26_valid{r26_counts[3]+=1;}else{r26_counts[4]+=1;}
            }
            let r26_price=if r26_valid{dc[(a_slot_of((r26_xd-1)as u32)%32)as usize]}else{0};
            let mut r26_proposals=[4294967295u32;2];
'''

AFTER_EXTENSION = '''            if r26_valid&&i+r26_el>prev{r26_counts[22]+=1;}
            if r26_proposals[0]!=4294967295||r26_proposals[1]!=4294967295{r26_counts[23]+=1;}
            if r26_proposals[0]<best{r26_counts[15]+=1;r26_counts[17]+=(best>>9).wrapping_sub(r26_proposals[0]>>9)as u64;if best>>9==r26_proposals[0]>>9{r26_counts[16]+=1;}}
            if r26_proposals[1]<best{r26_counts[18]+=1;r26_counts[19]+=(best>>9).wrapping_sub(r26_proposals[1]>>9)as u64;if best>>9==r26_proposals[1]>>9{r26_counts[26]+=1;}}
            let r26_p=if r26_proposals[0]<r26_proposals[1]{r26_proposals[0]}else{r26_proposals[1]};
            if r26_p<best{r26_counts[20]+=1;r26_counts[21]+=(best>>9).wrapping_sub(r26_p>>9)as u64;if best>>9==r26_p>>9{r26_counts[27]+=1;}}
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw) == EXPECTED
    source = raw.decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    old = fn(source, 'a_dp_pass')
    new = old
    anchor = '    let cl = cost.len();'
    assert new.count(anchor) == 1
    new = new.replace(anchor, '    let mut r26_counts=[0u64;28];r26_counts[0]=1;\n' + anchor, 1)
    anchor = '            let j0 = mp[i] as usize;'
    assert new.count(anchor) == 1
    new = new.replace(anchor, BEFORE_RECORDS + anchor, 1)
    anchor = '                let base = dc[((m >> 23) % 32) as usize].wrapping_add(bias);'
    assert new.count(anchor) == 1
    observation = '''                r26_counts[24]+=1;
                if r26_valid{r26_a_overlap_record(cost,lc,i,prev,stop,m,dc[((m>>23)%32)as usize],r26_el,r26_price,bias,&mut r26_counts,&mut r26_proposals);}
'''
    new = new.replace(anchor, anchor + '\n' + observation.rstrip(), 1)
    anchor = '            e = j0;'
    assert new.count(anchor) == 1
    new = new.replace(anchor, AFTER_EXTENSION + anchor, 1)
    close = new.rfind('}')
    new = new[:close] + '    for r26_j in 0..28{R26_A_OVERLAP[r26_j].fetch_add(r26_counts[r26_j],Ordering::Relaxed);}\n' + new[close:]
    observed = (source.replace(old, new, 1) + '\n' + EXTRA).encode()
    importlib.import_module('r26-b-fix-shared-cache').spans(observed.decode())
    assert all(statement in new for statement in ['xl = el;', 'xl = prev - i;', 'xd = pd;', 'a_store_choice(cost, ch, i, best, bd, nxt);'])
    return observed


def preflight(spec):
    assert spec.get('r26_b_a_overlap_counts') is True and spec.get('native_encoder') is False
    entry = next(row for row in spec['entries'] if row['name'] == 'public552')
    raw = (ROOT / entry['path'] / 'parse.rs').read_bytes()
    assert entry['hashes']['parse.rs'] == EXPECTED and len(FIELDS) == 28
    observed = instrument(raw)
    return {'status': 'VERIFIED_ORIGINAL_A_RECURRENCE_PRESERVED_OBSERVER_STRUCTURE_ONLY',
            'source_hashes': entry['hashes'], 'observer_sha256': sha(observed), 'fields': FIELDS,
            'scope': 'Only extra read-only candidates/counters. Every original XL/XD, record and best/cost/ch update retained. No native/gate/performance yet.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = importlib.import_module('round4').validate(os.environ['ROUND4_SPEC'])
    preflight(spec)
    entry = next(row for row in spec['entries'] if row['name'] == 'public552')
    frozen = ROOT / entry['path'] / 'parse.rs'
    build = Path(os.environ['RUNNER_TEMP']) / 'r26-b-a-overlap'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r26-b-a-overlap'
    out.mkdir(parents=True)
    observed = build / 'observed.rs'
    observed.write_bytes(instrument(frozen.read_bytes()))
    harness = importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN', str(frozen)).replace('OBSERVED', str(observed)).replace('observed::r13_take()', 'observed::r26_a_overlap_take()').replace('R13_COUNT', 'R26_A_OVERLAP')
    driver = build / 'driver.rs'
    driver.write_text(harness)
    binary = build / 'check'
    compiled = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], capture_output=True, text=True, timeout=240)
    (out / 'compile.log').write_text(compiled.stdout + compiled.stderr)
    assert compiled.returncode == 0
    corpus = Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1'
    run = subprocess.run([str(binary), str(corpus)], capture_output=True, text=True, timeout=480)
    (out / 'run.log').write_text(run.stdout + run.stderr)
    assert run.returncode == 0
    rows = []
    for line in run.stdout.splitlines():
        if not line.startswith('R26_A_OVERLAP '):
            continue
        _, name, size, *values = line.split()
        assert len(values) == len(FIELDS)
        data = (corpus / name).read_bytes()
        assert len(data) == int(size)
        rows.append({'file': name, 'raw_bytes': len(data), 'input_sha256': sha(data),
                     'counts': dict(zip(FIELDS, map(int, values)))})
    assert len(rows) == 28 and sum(row['raw_bytes'] for row in rows) == 15930000
    totals = {field: sum(row['counts'][field] for row in rows) for field in FIELDS}
    result = {
        'status': 'VERIFIED_ORIGINAL_A_OVERLAP_OBSERVER_TOKEN_AND_DECODE_EQUAL',
        'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'batch': os.environ['ROUND4_SPEC'],
        'source_hashes': entry['hashes'], 'observer_sha256': sha(observed.read_bytes()), 'driver_sha256': sha(driver.read_bytes()),
        'rows': rows, 'totals': totals,
        'proposal_byte_status': 'ALL_OBSERVED_PREFIXES_VALID' if totals['byte_invalid_positions'] == 0 else 'INVALID_PREFIXES_PRESENT_REQUIRES_DIAGNOSIS',
        'price_unit': 'A uses64cost units per modeledbit; packed gaps are modular objective observations, not encoderbits or recoverablebytes.',
        'scope': 'No new edge is written. Full original XL/XD/cached-record recurrence and original best/cost/ch writes retained. Ordinary offered ranges, fixed-only offered points and fixed-only missingprefixes are separate. Only strictlower distanceprice reselects covered lengths; newlyprovided fixedgaps are separately observed.',
        'limits': ['All28frozenparse/observer tokens match and independentlydecode; no encodercandidate, originalpaired timing, formalproof/admission/reward.',
                   'Local counters flush per whole DP call, no hot pair clocks. Prefixverification/extraqueries are diagnostic work, not assumed productionfreecost.',
                   'Potential packedbest gaps overpositions/passes cannot be summed into outputbytes. Samecostties and shift-discard states retained separately.',
                   'Existing R8D reselect negative result retained; actual coverage must justify any future fullencoder variant.'],
    }
    (out / 'receipt.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps(totals))


if __name__ == '__main__':
    main()
