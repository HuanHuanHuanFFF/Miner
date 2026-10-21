"""Count identical full-DP inputs within unchanged high-compression planning."""
from pathlib import Path
import hashlib, importlib.util, json, os, subprocess
from round4 import ROOT, validate

def instrument(text):
    start=text.index('pub fn Z308(');end=text.index('pub fn Z314(',start);part=text[start:end]
    marker='    while p0 < n && mp.len() == n + 1 && cost.len() == n + 1 && ch.len() == n {'
    state='''    let mut r18_lit=[0u32;256];let mut r18_lc=[0u32;512];let mut r18_dc=[0u32;32];
    let mut r18_valid=false;let mut r18_p0=0usize;let mut r18_pe=0usize;let mut r18_tail=0usize;
'''
    assert part.count(marker)==1;part=part.replace(marker,state+marker)
    call='                Z307(input, &mp, &mb, p0, pe, &lit, &lc, &dc, &mut cost, ch, Z161(k, passes, tail, final_tail));'
    observation='''                let r18_ct=Z161(k,passes,tail,final_tail);
                let mut r18_prices=r18_valid;let mut r18_j=0usize;
                while r18_j<256 {if r18_lit[r18_j]!=lit[r18_j]{r18_prices=false;}r18_lit[r18_j]=lit[r18_j];r18_j+=1;}
                r18_j=0;while r18_j<512 {if r18_lc[r18_j]!=lc[r18_j]{r18_prices=false;}r18_lc[r18_j]=lc[r18_j];r18_j+=1;}
                r18_j=0;while r18_j<32 {if r18_dc[r18_j]!=dc[r18_j]{r18_prices=false;}r18_dc[r18_j]=dc[r18_j];r18_j+=1;}
                let r18_same=r18_prices && r18_p0==p0 && r18_pe==pe && r18_tail==r18_ct;
                r18_hit(0,1);r18_hit(1,(pe-p0) as u64);r18_hit(2,r18_same as u64);if r18_same{r18_hit(3,(pe-p0) as u64);}
                r18_hit(4,r18_prices as u64);r18_hit(5,(r18_valid && r18_p0==p0 && r18_pe==pe)as u64);
                r18_valid=true;r18_p0=p0;r18_pe=pe;r18_tail=r18_ct;
'''
    assert part.count(call)==1;part=part.replace(call,observation+call)
    return text[:start]+part+text[end:]+'''
use std::sync::atomic::{AtomicU64,Ordering};
static R18_REPEAT:[AtomicU64;6]=[const{AtomicU64::new(0)};6];
fn r18_hit(i:usize,n:u64){R18_REPEAT[i].fetch_add(n,Ordering::Relaxed);}
pub fn r18_take()->[u64;6]{std::array::from_fn(|i|R18_REPEAT[i].swap(0,Ordering::Relaxed))}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);entry=next(e for e in spec['entries'] if e['name']==spec['r18_dp_repeat_counts'])
    source=ROOT/entry['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==entry['hashes']['parse.rs']
    text=instrument(raw.decode());build=Path(os.environ['RUNNER_TEMP'])/'r18-repeat-build';build.mkdir(exist_ok=True)
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-repeat';out.mkdir(parents=True,exist_ok=True)
    observed=build/'observed.rs';observed.write_text(text)
    ls=importlib.util.spec_from_file_location('counts_harness',ROOT/'scripts/research-round13-counts.py');m=importlib.util.module_from_spec(ls);ls.loader.exec_module(m)
    harness=m.HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r18_take()').replace('R13_COUNT','R18_REPEAT')
    driver=build/'driver.rs';driver.write_text(harness);binary=build/'driver'
    record={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'candidate':entry['name'],'source_hashes':entry['hashes'],'status':'STARTED','observer_sha256':hashlib.sha256(text.encode()).hexdigest(),'scope':'Untimed exact parameter-array equality counts insideZ308, same retained input/mp/mb, with original fullparse token/decode equivalence. Identical workload count is an opportunity, not measured acceleration.'}
    path=out/'repeat.json';path.write_text(json.dumps(record,indent=2)+'\n')
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=480);(out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    fields=['full_dp_calls','full_dp_positions','same_input_calls','same_input_positions','same_prices_calls','same_interval_calls'];rows=[]
    for line in r.stdout.splitlines():
        if not line.startswith('R18_REPEAT '):continue
        _,name,size,*values=line.split();assert len(values)==len(fields);data=(corpus/name).read_bytes();assert len(data)==int(size)
        rows.append({'file':name,'raw_bytes':len(data),'input_sha256':hashlib.sha256(data).hexdigest(),**dict(zip(fields,map(int,values)))})
    assert len(rows)==28
    record.update(status='VERIFIED_UNTIMED_REPEAT_COUNTS_TOKEN_AND_DECODE_EQUAL',rows=rows,totals={f:sum(r[f]for r in rows)for f in fields})
    path.write_text(json.dumps(record,indent=2)+'\n');print(json.dumps(record['totals']))

if __name__=='__main__':
    main()
