"""Fixed sparse novel discarded-A-probe producer and unchanged-DP consumer observation."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import subprocess

ROOT = Path(__file__).resolve().parents[1]
EXPECTED = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
FIELDS = ['finder_calls','tree_search_positions','selected_tree_positions','sampled_near_probes',
          'sampled_tree_probes','discarded_near_candidates','discarded_tree_candidates',
          'discarded_slot_updates','discarded_codes_before_dedup','samecode_fullprefix_redundant_codes',
          'samecode_removed_prefix_terms','novel_codes_after_dedup','prefix_check_calls','prefix_check_bytes',
          'byte_valid_candidates','byte_invalid_candidates','stored_sparse_records','sparse_logical_bytes',
          'sum_final_capacity_bytes','slot_reset_writes','dp_calls','dp_positions','binary_seek_steps',
          'sampled_dp_positions_with_cache','consumer_sparse_record_visits','consumer_original_records_scanned',
          'novel_length_candidate_domains','cheaper_domain_pairs','query_terms','shift_high_discard_terms',
          'original_best_improving_positions','samecost_tie_positions','packed_gap_units','cache_position_key_reads',
          'inherited_samecode_removed_prefix_terms']

EXTRA = '''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_DISCARD:[AtomicU64;35]=[const{AtomicU64::new(0)};35];
fn r26_d_hit(i:usize,n:u64){R26_DISCARD[i].fetch_add(n,Ordering::Relaxed);}
pub fn r26_discard_take()->[u64;35]{std::array::from_fn(|i|R26_DISCARD[i].swap(0,Ordering::Relaxed))}
fn r26_d_selected(pos:usize)->bool{
    let mut x=pos as u32;x^=x>>16;x=x.wrapping_mul(0x7feb352d);x^=x>>15;
    x=x.wrapping_mul(0x846ca68b);x^=x>>16;(x>>27)==0
}
fn r26_d_offer(lengths:&mut[usize;32],distances:&mut[usize;32],l:usize,d:usize,c:&mut[u64;35]){
    let code=(a_slot_of((d-1)as u32)%32)as usize;
    if l>lengths[code]||(l==lengths[code]&&d<distances[code]){
        lengths[code]=l;distances[code]=d;c[7]+=1;
    }
}
fn r26_d_finish(s:&[u8],mb:&Vec<u32>,start:usize,pos:usize,lengths:&[usize;32],distances:&[usize;32],extra:&mut Vec<u64>,c:&mut[u64;35]){
    let mut old=[2usize;32];let mut j=start;
    while j<mb.len(){let m=mb[j];let code=((m>>23)%32)as usize;let l=(((m>>15)&255)+3)as usize;if l>old[code]{old[code]=l;}j+=1;}
    for code in 0..30{
        let l=lengths[code];if l<3{continue;}c[8]+=1;
        if l<=old[code]{c[9]+=1;c[10]+=(l-2)as u64;continue;}
        c[11]+=1;c[12]+=1;c[13]+=l as u64;
        let d=distances[code];
        if check(s,pos,l,d){
            c[14]+=1;let m=((d-1)as u32)|(((l-3)as u32)<<15)|((code as u32)<<23);
            extra.push(((pos as u64)<<32)|(m as u64));c[16]+=1;
        }else{c[15]+=1;}
    }
}
fn r26_d_seek(extra:&Vec<u64>,p:usize)->(usize,u64){
    let mut lo=0usize;let mut hi=extra.len();let mut steps=0u64;
    while lo<hi{let mid=lo+(hi-lo)/2;steps+=1;if (extra[mid]>>32)<p as u64{lo=mid+1;}else{hi=mid;}}
    (lo,steps)
}
fn r26_d_consume(cost:&Vec<u32>,lc:&[u32;512],dc:&[u32;32],mb:&Vec<u32>,extra:&Vec<u64>,i:usize,j0:usize,top:usize,b:usize,e:usize,bias:u32,oldbest:u32,il:usize,id:usize,c:&mut[u64;35]){
    c[23]+=1;let mut maxcode=[2usize;32];let mut j=j0;
    while j<top{c[25]+=1;let m=mb[j];let code=((m>>23)%32)as usize;let l=(((m>>15)&255)+3)as usize;if l>maxcode[code]{maxcode[code]=l;}j+=1;}
    if il>=3&&id>=1{let code=(a_slot_of((id-1)as u32)%32)as usize;let old=maxcode[code];
        if il>old{let mut x=b;while x<e{let m=extra[x]as u32;if ((m>>23)%32)as usize==code{let l=(((m>>15)&255)+3)as usize;let cap=if l<il{l}else{il};if cap>old{c[34]+=(cap-old)as u64;}}x+=1;}maxcode[code]=il;}}
    let mut proposal=4294967295u32;let mut prev=i+2;j=j0;
    while j<top{
        c[25]+=1;let m=mb[j];let stop=i+(((m>>15)&255)+3)as usize;
        if stop<cost.len()&&m<0x80000000{
            let oldprice=dc[((m>>23)%32)as usize];let mut x=b;
            while x<e{
                c[24]+=1;let item=extra[x]as u32;let code=((item>>23)%32)as usize;
                let len=(((item>>15)&255)+3)as usize;let mut lo=prev+1-i;
                if lo<=maxcode[code]{lo=maxcode[code]+1;}
                let hi=if len<stop-i{len}else{stop-i};
                if lo<=hi{c[26]+=1;let price=dc[code];if price<oldprice{
                    c[27]+=1;let base=price.wrapping_add(bias);let mut l=lo;
                    while l<=hi{
                        c[28]+=1;let sum=cost[i+l].wrapping_add(lc[l%512]).wrapping_add(base);
                        if sum>=8388608{c[29]+=1;}let v=(sum<<9)|(l as u32);if v<proposal{proposal=v;}l+=1;
                    }
                }}x+=1;
            }
        }
        if stop>prev{prev=stop;}j+=1;
    }
    if proposal<oldbest{c[30]+=1;c[32]+=(oldbest>>9).wrapping_sub(proposal>>9)as u64;if proposal>>9==oldbest>>9{c[31]+=1;}}
}
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw) == EXPECTED
    source = raw.decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    edits = {}
    tree = fn(source, 'a_tree_insert')
    tree = tree.replace('    mb: &mut Vec<u32>,\n', '    mb: &mut Vec<u32>,\n    r26_extra:&mut Vec<u64>,r26_lengths:&mut[usize;32],r26_distances:&mut[usize;32],\n', 1)
    anchor = '    let oldest = if pos > 32767'
    assert tree.count(anchor) == 1
    tree = tree.replace(anchor, '''    let r26_sel=r26_d_selected(pos);let r26_start=mb.len();let mut r26_c=[0u64;35];
    if r26_sel{r26_c[2]=1;for k in 0..32{r26_lengths[k]=0;r26_distances[k]=0;}r26_c[19]=64;}
''' + anchor, 1)
    anchor = '        let lr = a_probe(s, cr - 1, pos, 0).0;'
    assert tree.count(anchor) == 1
    tree = tree.replace(anchor, anchor+'''
        if r26_sel{r26_c[3]+=1;if lr>=3&&lr<=best{r26_c[5]+=1;r26_d_offer(r26_lengths,r26_distances,lr,pos-cr+1,&mut r26_c);}}''', 1)
    anchor = '        let l = r.0;'
    assert tree.count(anchor) == 1
    tree = tree.replace(anchor, anchor+'''
        if r26_sel{r26_c[4]+=1;if l>=3&&l<=best{r26_c[6]+=1;r26_d_offer(r26_lengths,r26_distances,l,pos-p,&mut r26_c);}}''', 1)
    anchor = '    best\n}'
    assert tree.count(anchor) == 1
    tree = tree.replace(anchor, '''    if r26_sel{r26_d_finish(s,mb,r26_start,pos,r26_lengths,r26_distances,r26_extra,&mut r26_c);for k in 0..35{r26_d_hit(k,r26_c[k]);}}
''' + anchor, 1)
    edits['a_tree_insert'] = tree
    finder = fn(source, 'a_find_all')
    finder = finder.replace('skip: usize) {', 'skip: usize,r26_extra:&mut Vec<u64>) {', 1)
    anchor = '    let n = s.len();'
    finder = finder.replace(anchor, anchor+'\n    let mut r26_lengths=[0usize;32];let mut r26_distances=[0usize;32];let mut r26_trees=0u64;\n', 1)
    anchor = 'let best = a_tree_insert(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb);'
    assert finder.count(anchor) == 1
    finder = finder.replace(anchor, 'r26_trees+=1;\n                let best = a_tree_insert(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb,r26_extra,&mut r26_lengths,&mut r26_distances);', 1)
    close = finder.rfind('}')
    finder = finder[:close]+'    r26_d_hit(0,1);r26_d_hit(1,r26_trees);\n'+finder[close:]
    edits['a_find_all'] = finder
    dp = fn(source, 'a_dp_pass')
    dp = dp.replace('    ch: &mut Vec<u32>,\n', '    ch: &mut Vec<u32>,\n    r26_extra:&Vec<u64>,\n', 1)
    anchor = '    let cl = cost.len();'
    dp = dp.replace(anchor, '    let mut r26_c=[0u64;35];r26_c[20]=1;let seek=r26_d_seek(r26_extra,pe);let mut r26_e=seek.0;r26_c[22]=seek.1;\n'+anchor, 1)
    anchor = '            let j0 = mp[i] as usize;'
    dp = dp.replace(anchor, '''            r26_c[21]+=1;let mut r26_b=r26_e;
            while r26_b>0{r26_c[33]+=1;if (r26_extra[r26_b-1]>>32)==i as u64{r26_b-=1;}else{break;}}
            let r26_el=if xl+1>258{258}else{xl+1};
            let r26_il=if xl>=3&&xd>=1&&xd<=i&&s[i]==s[i-xd]{r26_el}else{0};let r26_id=xd;
''' + anchor, 1)
    anchor = '            e = j0;'
    dp = dp.replace(anchor, '''            if r26_b<r26_e{r26_d_consume(cost,lc,dc,mb,r26_extra,i,j0,top,r26_b,r26_e,bias,best,r26_il,r26_id,&mut r26_c);}
            r26_e=r26_b;
''' + anchor, 1)
    close = dp.rfind('}')
    dp = dp[:close]+'    for k in 0..35{r26_d_hit(k,r26_c[k]);}\n'+dp[close:]
    edits['a_dp_pass'] = dp
    sample = fn(source, 'a_sample_pass')
    sample = sample.replace('    df: &mut [u32; 32],\n', '    df: &mut [u32; 32],\n    r26_extra:&Vec<u64>,\n', 1)
    anchor = 'a_dp_pass(s, mp, mb, a, a + A_SEG, lit, lc, dc, cost, ch);'
    assert sample.count(anchor) == 1
    sample = sample.replace(anchor, anchor[:-2]+',r26_extra);', 1)
    edits['a_sample_pass'] = sample
    engine = fn(source, 'a_engine')
    anchor = '    a_find_all(input, &mut mp, &mut mb, depth, skip);'
    engine = engine.replace(anchor, '    let mut r26_extra=Vec::<u64>::new();\n    a_find_all(input, &mut mp, &mut mb, depth, skip,&mut r26_extra);\n    r26_d_hit(17,(r26_extra.len()*8)as u64);r26_d_hit(18,(r26_extra.capacity()*8)as u64);', 1)
    for anchor in ['a_sample_pass(input, &mp, &mb, ps, pe, &lit, &lc, &dc, &mut cost, ch, &mut lf, &mut df);',
                   'a_dp_pass(input, &mp, &mb, p0, pe, &lit, &lc, &dc, &mut cost, ch);']:
        assert engine.count(anchor) == 1
        engine = engine.replace(anchor, anchor[:-2]+',&r26_extra);', 1)
    edits['a_engine'] = engine
    observed = source
    for name, new in edits.items():
        old = fn(source, name)
        assert new != old and observed.count(old) == 1
        observed = observed.replace(old, new, 1)
    result = (observed+'\n'+EXTRA).encode()
    importlib.import_module('r26-b-fix-shared-cache').spans(result.decode())
    for statement in ['xl = el;', 'xl = prev - i;', 'xd = pd;', 'a_store_choice(cost, ch, i, best, bd, nxt);']:
        assert statement in dp
    return result


def preflight(spec):
    assert spec.get('r26_b_a_discarded_counts') is True and spec.get('native_encoder') is False
    entry = next(row for row in spec['entries'] if row['name']=='public552')
    assert entry['hashes']['parse.rs'] == EXPECTED and len(FIELDS) == 35
    result = instrument((ROOT/entry['path']/'parse.rs').read_bytes())
    return {'status':'VERIFIED_SPARSE_FIXED_DISCARDED_SOURCE_AND_ORIGINAL_RECURRENCE_STRUCTURE_ONLY',
            'source_hashes':entry['hashes'], 'observer_sha256':sha(result), 'fields':FIELDS,
            'scope':'Read-only discarded-source cache and original DP shadow queries; no new edge/price/choice writes. Physical sample fixed; original samecode fullprefix and inherited source dedup. No native/proof/performance yet.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec = importlib.import_module('round4').validate(os.environ['ROUND4_SPEC'])
    preflight(spec)
    entry = next(row for row in spec['entries'] if row['name']=='public552')
    frozen = ROOT/entry['path']/'parse.rs'
    build = Path(os.environ['RUNNER_TEMP'])/'r26-b-discarded'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-a-discarded'
    out.mkdir(parents=True)
    observed = build/'observed.rs'
    observed.write_bytes(instrument(frozen.read_bytes()))
    harness = importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r26_discard_take()').replace('R13_COUNT','R26_DISCARD')
    driver = build/'driver.rs'
    driver.write_text(harness)
    binary = build/'check'
    compile = subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (out/'compile.log').write_text(compile.stdout+compile.stderr)
    assert compile.returncode==0
    corpus = Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    run = subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=720)
    (out/'run.log').write_text(run.stdout+run.stderr)
    assert run.returncode==0
    rows=[]
    for line in run.stdout.splitlines():
        if not line.startswith('R26_DISCARD '):continue
        _,name,size,*values=line.split()
        assert len(values)==len(FIELDS)
        data=(corpus/name).read_bytes()
        assert len(data)==int(size)
        rows.append({'file':name,'raw_bytes':len(data),'input_sha256':sha(data),'counts':dict(zip(FIELDS,map(int,values)))})
    assert len(rows)==28 and sum(row['raw_bytes'] for row in rows)==15930000
    totals={field:sum(row['counts'][field] for row in rows) for field in FIELDS}
    result={'status':'VERIFIED_FIXED_SPARSE_DISCARDED_OBSERVER_ORIGINAL_TOKEN_AND_DECODE_EQUAL',
            'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
            'source_hashes':entry['hashes'],'observer_sha256':sha(observed.read_bytes()),'driver_sha256':sha(driver.read_bytes()),
            'rows':rows,'totals':totals,'max_perfile_final_capacity_bytes':max(row['counts']['sum_final_capacity_bytes'] for row in rows),
            'proposal_byte_status':'ALL_RETAINED_NOVEL_PREFIXES_VALID' if totals['byte_invalid_candidates']==0 else 'INVALID_PREFIXES_REQUIRE_DIAGNOSIS',
            'selector':'Fixed physical-position avalanchehash high5bitszero; selected subset does not imply representative coverage.',
            'dedup':'Longest discarded prefix percode; exclude prefixes available from any original cached samecode max length, and in consumer also exclude original byte-eligible inherited samecode prefix. Novel lengths only.',
            'limits':['All28 frozen/observer fulltokens match and independentlydecode. No production candidate, encoder quality, originalpaired, extraction/proof/gate/formal result.',
                      'All producer/consumer counts reflect this fixed selected subset on original full/sample trajectory. No extrapolated outputbytes or speed.',
                      'Logical/cache-capacity bytes are not process RSS; sum_final_capacity is summed invocations/files, separate max is retained.',
                      'Modeled packedgap summed over positions/passes is not recoverable encodedbits. Samecosttie separate; no hotpair clocks.']}
    (out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps(totals))


if __name__=='__main__':
    main()
