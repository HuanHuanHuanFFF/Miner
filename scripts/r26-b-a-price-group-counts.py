"""Original552 current-price contiguous offer-run coverage and real owner-mapping burden."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import os
import subprocess
import sys

sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1]
EXPECTED='5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
FIELDS=['dp_calls','positions','variable_queries','variable_terms','price_groups','merged_query_setups',
        'grouped_terms','different_distance_groups','different_distance_merged_queries','original_width8_terms',
        'grouped_width8_terms','winning_different_distance_groups','winner_original_record_visits','fixed_only_queries',
        'inherited_variable_queries','merged_groups_containing_inheritance','old_same_distance_merged_queries','width8_groups']
EXTRA='''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_GROUP:[AtomicU64;18]=[const{AtomicU64::new(0)};18];
pub fn r26_group_take()->[u64;18]{std::array::from_fn(|i|R26_GROUP[i].swap(0,Ordering::Relaxed))}
fn r26_group_flush(cnt:&mut[u64;18],active:&mut bool,start:usize,end:usize,n:usize,same:bool,min:u32,entry:u32,winner:usize,has_ext:bool){
 if *active{
  let width=end-start+1;cnt[4]+=1;cnt[5]+=(n-1)as u64;cnt[6]+=width as u64;
  if width>=8{cnt[10]+=width as u64;cnt[17]+=1;}
  if n>1{if same{cnt[16]+=(n-1)as u64;}else{cnt[7]+=1;cnt[8]+=(n-1)as u64;}if has_ext{cnt[15]+=1;}}
  if n>1&&!same&&min<entry{assert!(winner>=1&&winner<=n);cnt[11]+=1;cnt[12]+=winner as u64;}
  *active=false;
 }
}
fn r26_group_offer(cnt:&mut[u64;18],active:&mut bool,price:&mut u32,start:&mut usize,end:&mut usize,n:&mut usize,dist:&mut u32,same:&mut bool,min:&mut u32,entry:&mut u32,winner:&mut usize,has_ext:&mut bool,from:usize,to:usize,base:u32,d:u32,best:u32,ext:bool){
 if from>to{return;}
 let width=to-from+1;cnt[2]+=1;cnt[3]+=width as u64;if width>=8{cnt[9]+=width as u64;}if ext{cnt[14]+=1;}
 if *active&&*price==base&&*end+1==from{
  *end=to;*n+=1;if *dist!=d{*same=false;}*has_ext|=ext;
 }else{
  r26_group_flush(cnt,active,*start,*end,*n,*same,*min,*entry,*winner,*has_ext);
  *active=true;*price=base;*start=from;*end=to;*n=1;*dist=d;*same=true;*min=4294967295;*entry=best;*winner=0;*has_ext=ext;
 }
}
fn r26_group_result(min:&mut u32,winner:&mut usize,n:usize,value:u32){if value<*min{*min=value;*winner=n;}}
'''
STATE='''            let mut ga=false;let mut gb=0u32;let mut gs=0usize;let mut ge=0usize;let mut gn=0usize;let mut gd=0u32;
            let mut gsame=true;let mut gmin=4294967295u32;let mut gentry=best;let mut gwinner=0usize;let mut gext=false;
'''
FLUSH='r26_group_flush(&mut cnt,&mut ga,gs,ge,gn,gsame,gmin,gentry,gwinner,gext);'


def sha(raw):return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw)==EXPECTED
    source=raw.decode();fn=importlib.import_module('prepare-round24-extract-repro').fn
    old=fn(source,'a_dp_pass');part=old
    part=part.replace('    let cl = cost.len();','    let cl = cost.len();let mut cnt=[0u64;18];cnt[0]=1;',1)
    part=part.replace('            i -= 1;','            i -= 1;cnt[1]+=1;',1)
    marker='            let top = if e < mb.len() { e } else { mb.len() };'
    assert part.count(marker)==1;part=part.replace(marker,marker+'\n'+STATE,1)
    marker='                if stop < cl && m >= 0x80000000 {'
    assert part.count(marker)==1
    part=part.replace(marker,'                if stop>=cl{'+FLUSH+'}\n'+marker+'\n                    '+FLUSH+'cnt[13]+=1;',1)
    marker='                    let mut at = prev + 1;'
    assert part.count(marker)==2
    ordinary='                    r26_group_offer(&mut cnt,&mut ga,&mut gb,&mut gs,&mut ge,&mut gn,&mut gd,&mut gsame,&mut gmin,&mut gentry,&mut gwinner,&mut gext,prev+1,stop,base,m&32767,best,false);\n'
    extension='                    r26_group_offer(&mut cnt,&mut ga,&mut gb,&mut gs,&mut ge,&mut gn,&mut gd,&mut gsame,&mut gmin,&mut gentry,&mut gwinner,&mut gext,prev+1,stop,base,x,best,true);\n'
    first=part.index(marker);part=part[:first]+ordinary+part[first:]
    second=part.index(marker,first+len(ordinary)+len(marker));part=part[:second]+extension+part[second:]
    marker='                if mbest < best {'
    assert part.count(marker)==2
    part=part.replace(marker,'                if ga{r26_group_result(&mut gmin,&mut gwinner,gn,mbest);}\n'+marker)
    marker='            e = j0;'
    assert part.count(marker)==1;part=part.replace(marker,'            '+FLUSH+'\n'+marker,1)
    assert part.endswith('}\n');part=part[:-2]+'    let mut k=0usize;while k<18{R26_GROUP[k].fetch_add(cnt[k],Ordering::Relaxed);k+=1;}\n}\n'
    source=source.replace(old,part,1)+EXTRA
    importlib.import_module('r26-b-fix-shared-cache').spans(source)
    return source.encode()


def preflight(spec):
    assert spec.get('r26_b_a_price_group_counts') is True and spec.get('native_encoder') is False
    assert spec['native_only'] and all(e['control'] for e in spec['entries'])
    entry=next(e for e in spec['entries'] if e['name']=='public552')
    raw=(ROOT/entry['path']/'parse.rs').read_bytes();assert sha(raw)==entry['hashes']['parse.rs']==EXPECTED
    observed=instrument(raw)
    return {'status':'VERIFIED_ORIGINAL_CURRENT_PRICE_GROUP_OBSERVER_STRUCTURE_ONLY','computed_utc':datetime.now(timezone.utc).isoformat(),
            'source_hashes':entry['hashes'],'observer_sha256':sha(observed),
            'scope':'All original per-record and inherited scans/globalbest/prev/pd/XL/XD/cost/ch writes execute unchanged. Only shadow grouping/owner ordinal counts, no production grouping or performance.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=importlib.import_module('round4').validate(os.environ['ROUND4_SPEC']);preflight(spec)
    entry=next(e for e in spec['entries'] if e['name']=='public552');frozen=ROOT/entry['path']/'parse.rs'
    build=Path(os.environ['RUNNER_TEMP'])/'r26-b-a-price-group';build.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-a-price-group';out.mkdir(parents=True)
    observed=build/'observed.rs';observed.write_bytes(instrument(frozen.read_bytes()))
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r26_group_take()').replace('R13_COUNT','R26_A_GROUP')
    driver=build/'check.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    rr=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=480);(out/'run.log').write_text(rr.stdout+rr.stderr);assert rr.returncode==0
    prior_path=ROOT/'evidence/round26/38217519276/compiler-b22-native/diagnostics/r26-b-a-compiler/receipt.json'
    prior=json.loads(prior_path.read_bytes());by={r['file']:r for r in prior['rows']};rows=[]
    for line in rr.stdout.splitlines():
        if line.startswith('R26_A_GROUP '):
            _,name,size,*vals=line.split();assert len(vals)==len(FIELDS);data=(corpus/name).read_bytes();assert len(data)==int(size)
            counts=dict(zip(FIELDS,map(int,vals)));old=by[name]
            assert sha(data)==old['input_sha256']
            assert counts['variable_queries']==old['counts']['variable_queries'] and counts['variable_terms']==old['counts']['variable_terms']
            assert counts['grouped_terms']==counts['variable_terms'] and counts['merged_query_setups']==counts['variable_queries']-counts['price_groups']
            assert counts['old_same_distance_merged_queries']+counts['different_distance_merged_queries']==counts['merged_query_setups']
            rows.append({'file':name,'raw_bytes':len(data),'input_sha256':sha(data),'counts':counts})
    assert len(rows)==28 and sum(r['raw_bytes'] for r in rows)==15930000
    totals={f:sum(r['counts'][f] for r in rows) for f in FIELDS}
    result={'status':'VERIFIED_ORIGINAL_CURRENT_PRICE_RUN_COUNTS_TOKEN_AND_DECODE_PARITY','computed_utc':datetime.now(timezone.utc).isoformat(),
            'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_hashes':entry['hashes'],
            'observer_sha256':sha(observed.read_bytes()),'harness_sha256':sha(driver.read_bytes()),'rows':rows,'totals':totals,
            'B22_receipt_sha256':sha(prior_path.read_bytes()),
            'limits':['Original packed comparisons, costs/choices and all tree/cache/DP/fitter work unchanged; only shadow groups on actual per-pass current dc values.',
                      'Fixed-only or invalid records break groups; ordinary and existing inherited variable domains merge only with equal actualbase and exactly contiguous lengths.',
                      'Different-distance equal-price groups are separated from same-distanceAN precedent; actual winner ordinal models original-record recovery after groupmin.',
                      'Group formation/lookup implementation costs are not measured; no new scratch or production grouping exists. Counts/SIMD-eligible width are not net speed or a full gate.']}
    (out/'receipt.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({'status':result['status'],'totals':totals}))


if __name__=='__main__':main()
