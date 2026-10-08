"""Untimed expired nonzero PC word-lookups; original output differential checked."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess
from round4 import ROOT,validate

FIELDS=['ahead_calls','expired_candidates','expired_nonzero','fresh_window_candidates','same_or_future_candidates']

def instrument(raw):
    original=raw.decode();a=original.index('pub fn pc_ahead_m<const H: usize>');b=original.index('/// `pc_ahead_if`',a);body=original[a:b]
    old='    let c = head[a] as usize;';add='''
    r13_exp_hit(0,1);
    if c<i && i-c>32768 {r13_exp_hit(1,1);r13_exp_hit(2,(c!=0)as u64);}
    else if c<i {r13_exp_hit(3,1);}else{r13_exp_hit(4,1);}
'''
    assert body.count(old)==1;body=body.replace(old,old+add,1);changed=original[:a]+body+original[b:];assert changed.replace(add,'',1)==original
    counters='''
use std::sync::atomic::{AtomicU64,Ordering};
static R13_EXPIRED:[AtomicU64;5]=[const{AtomicU64::new(0)};5];
fn r13_exp_hit(i:usize,x:u64){R13_EXPIRED[i].fetch_add(x,Ordering::Relaxed);}
pub fn r13_take()->[u64;5]{std::array::from_fn(|i|R13_EXPIRED[i].swap(0,Ordering::Relaxed))}
'''
    return(changed+counters).encode()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(e for e in spec['entries']if e['name']=='public514');frozen=ROOT/e['path']/'parse.rs';raw=frozen.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    l=importlib.util.spec_from_file_location('r13_exp_harness',ROOT/'scripts/research-round13-counts.py');m=importlib.util.module_from_spec(l);l.loader.exec_module(m)
    build=Path(os.environ['RUNNER_TEMP'])/'r13-exp-build';build.mkdir(exist_ok=True);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-expired';out.mkdir(parents=True,exist_ok=True)
    observed=build/'observed.rs';observed.write_bytes(instrument(raw));source=build/'counts.rs';source.write_text(m.HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)));binary=build/'counts'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=120);(out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    rows=[]
    for line in r.stdout.splitlines():
        if line.startswith('R13_COUNT '):
            _,name,n,*vs=line.split();assert len(vs)==len(FIELDS);p=corpus/name;assert p.stat().st_size==int(n)
            row={'file':name,'raw_bytes':int(n),'input_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'counts':dict(zip(FIELDS,map(int,vs)))};assert row['counts']['ahead_calls']==sum(row['counts'][f]for f in('expired_candidates','fresh_window_candidates','same_or_future_candidates'));rows.append(row)
    assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'VERIFIED_FINITE_FROZEN_OBSERVED_TOKEN_AND_DECODE_EQUAL','source_sha256':hashlib.sha256(raw).hexdigest(),'observer_sha256':hashlib.sha256(observed.read_bytes()).hexdigest(),'harness_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'files':rows,'totals':{f:sum(x['counts'][f]for x in rows)for f in FIELDS},'scope':'Logical original ahead calls with atomic observer, not measured machine instructions or speed. Expired nonzero distinguishes potentially cold old bytes from already-hot sentinel0 reads.'}
    (out/'counts.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result['totals']))

if __name__=='__main__':main()
