"""Measure real high-end DP range lengths before choosing a range data structure."""
from pathlib import Path
import hashlib, importlib.util, json, os, subprocess
from round4 import ROOT, validate

WRAPPER = r'''
use std::sync::atomic::{AtomicU64,Ordering};
static R18_RANGE:[AtomicU64;264]=[const{AtomicU64::new(0)};264];
pub fn r18_take()->[u64;264]{std::array::from_fn(|i|R18_RANGE[i].swap(0,Ordering::Relaxed))}
#[inline(always)]
pub fn Z314(cost:&[u32],lc:&[u32;512],i:usize,lo:usize,hi:usize,base:u32,width:usize)->u32 {
 let result=r18_inner_Z314(cost,lc,i,lo,hi,base,width);
 if lo<=hi && hi<512 && i<cost.len() && hi<cost.len()-i {
  let start=if width>=1 && hi-lo>=width {hi-width+1} else {lo};
  let span=hi-start+1;
  R18_RANGE[span.min(258)].fetch_add(1,Ordering::Relaxed);
  R18_RANGE[259].fetch_add(span as u64,Ordering::Relaxed);
  let mut groups=0usize;let mut l=start;let mut last=0u32;
  while l<=hi {if l==start || lc[l]!=last{groups+=1;last=lc[l];}l+=1;}
  R18_RANGE[260].fetch_add(groups as u64,Ordering::Relaxed);
  if start>=11 {R18_RANGE[261].fetch_add(1,Ordering::Relaxed);}
  if width==0 {R18_RANGE[262].fetch_add(1,Ordering::Relaxed);}
 }else{R18_RANGE[263].fetch_add(1,Ordering::Relaxed);}
 result
}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);entry=next(e for e in spec['entries'] if e['name']==spec['r18_range_counts'])
    source=ROOT/entry['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==entry['hashes']['parse.rs']
    text=raw.decode();needle='pub fn Z314(';assert text.count(needle)==1
    text=text.replace(needle,'pub fn r18_inner_Z314(',1)+WRAPPER
    build=Path(os.environ['RUNNER_TEMP'])/'r18-range-build';build.mkdir(exist_ok=True)
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-ranges';out.mkdir(parents=True,exist_ok=True)
    observed=build/'observed.rs';observed.write_text(text)
    ls=importlib.util.spec_from_file_location('counts_harness',ROOT/'scripts/research-round13-counts.py');m=importlib.util.module_from_spec(ls);ls.loader.exec_module(m)
    harness=m.HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r18_take()').replace('R13_COUNT','R18_RANGE')
    driver=build/'driver.rs';driver.write_text(harness);binary=build/'driver'
    record={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'candidate':entry['name'],'source_hashes':entry['hashes'],'status':'STARTED','observer_sha256':hashlib.sha256(text.encode()).hexdigest(),'scope':'Untimed instrumented counts with full-parent token/decode equivalence. Range distributions decide whether selective range queries deserve implementation; operations saved are not measured time savings.'}
    path=out/'ranges.json';path.write_text(json.dumps(record,indent=2)+'\n')
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    r=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=480)
    (out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    rows=[]
    for line in r.stdout.splitlines():
        if not line.startswith('R18_RANGE '):continue
        _,name,size,*values=line.split();assert len(values)==264
        counts=list(map(int,values));data=(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'/name).read_bytes();assert len(data)==int(size)
        rows.append({'file':name,'raw_bytes':len(data),'input_sha256':hashlib.sha256(data).hexdigest(),'span_histogram':counts[:259],'scalar_terms':counts[259],'constant_price_groups':counts[260],'starts_at_least_11':counts[261],'unlimited_width_calls':counts[262],'invalid_calls':counts[263]})
    assert len(rows)==28
    total=[sum(r['span_histogram'][i] for r in rows) for i in range(259)]
    record.update(status='VERIFIED_UNTIMED_RANGE_COUNTS_TOKEN_AND_DECODE_EQUAL',rows=rows,span_histogram=total,scalar_terms=sum(r['scalar_terms'] for r in rows),constant_price_groups=sum(r['constant_price_groups'] for r in rows))
    path.write_text(json.dumps(record,indent=2)+'\n')
    print(json.dumps({k:record[k] for k in ('status','span_histogram','scalar_terms','constant_price_groups')}))

if __name__=='__main__':
    main()
