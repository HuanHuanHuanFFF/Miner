"""Count repeated price ordering work in the actual selective-RF candidate."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess
from round4 import ROOT,validate

def instrument(text):
    a=text.index('pub fn rf_dp(');b=text.index('pub fn refine(',a);part=text[a:b]
    needle='                    if op < pr || (op == pr && ob < bucket) { break; }'
    assert part.count(needle)==1;part=part.replace(needle,'                    r18_hit(33,1);\n'+needle)
    needle='        let mut lo = 3usize;';assert part.count(needle)==1
    part=part.replace(needle,'        r18_hit(k.min(32),1);\n        r18_hit(34,k as u64);\n'+needle)
    a2=text.index('pub fn rf_dp_relax(');b2=text.index('pub fn rf_dp(',a2);relax=text[a2:b2]
    needle='    let mut l = lo;'
    assert relax.count(needle)==1
    relax=relax.replace(needle,'    if maxlen >= lo { r18_hit(35,(maxlen-lo+1) as u64); }\n'+needle)
    text=text[:a2]+relax+text[b2:a]+part+text[b:]
    return text+'''
use std::sync::atomic::{AtomicU64,Ordering};
static R18_RF:[AtomicU64;36]=[const{AtomicU64::new(0)};36];
fn r18_hit(i:usize,n:u64){R18_RF[i].fetch_add(n,Ordering::Relaxed);}
pub fn r18_take()->[u64;36]{std::array::from_fn(|i|R18_RF[i].swap(0,Ordering::Relaxed))}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(x for x in spec['entries']if x['name']==spec['r18_rf_counts']);source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    build=Path(os.environ['RUNNER_TEMP'])/'r18-rf-counts';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-rf-counts';out.mkdir(parents=True)
    text=instrument(raw.decode());observed=build/'observed.rs';observed.write_text(text)
    sp=importlib.util.spec_from_file_location('harness',ROOT/'scripts/research-round13-counts.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    driver=build/'driver.rs';h=m.HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r18_take()').replace('R13_COUNT','R18_RFCOUNT');driver.write_text(h);binary=build/'driver'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';rr=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=480);(out/'run.log').write_text(rr.stdout+rr.stderr);assert rr.returncode==0
    rows=[]
    for line in rr.stdout.splitlines():
        if line.startswith('R18_RFCOUNT '):
            _,name,n,*vals=line.split();v=list(map(int,vals));assert len(v)==36;inp=(corpus/name).read_bytes();assert len(inp)==int(n)
            rows.append({'file':name,'raw_bytes':len(inp),'input_sha256':hashlib.sha256(inp).hexdigest(),'bucket_count_histogram':v[:33],'insertion_comparisons':v[33],'active_buckets':v[34],'relaxed_length_terms':v[35]})
    assert len(rows)==28
    result={'status':'VERIFIED_UNTIMED_RF_COUNTS_TOKEN_AND_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'candidate':e['name'],'source_hashes':e['hashes'],'observer_sha256':hashlib.sha256(text.encode()).hexdigest(),'rows':rows,'totals':{'histogram':[sum(r['bucket_count_histogram'][i]for r in rows)for i in range(33)],**{k:sum(r[k]for r in rows)for k in ('insertion_comparisons','active_buckets','relaxed_length_terms')}},'scope':'Untimed whole-parser observer with exacttoken equality. Decide whether per-block price-rank work can replace repeated per-position insertion sort; counts are not timegain.'}
    (out/'counts.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result['totals']))

if __name__=='__main__':main()
