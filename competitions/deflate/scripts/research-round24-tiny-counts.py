"""Untimed rejected-repeat counts on the original once609 token-refinement loop."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(e for e in spec['entries'] if e['name']=='once');source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    text=raw.decode();marker='let bits=SFcost(&trial);if bits<best{ts=trial;best=bits;}round+=1;';assert text.count(marker)==1
    new='let bits=SFcost(&trial);r24_hit(0,1);r24_hit(1,(bits<best)as u64);if bits>=best && round+1<SFTOKROUNDS{r24_hit(2,1);r24_hit(3,ts.len()as u64);}if bits<best{ts=trial;best=bits;}round+=1;'
    text=text.replace(marker,new)+'''\nuse std::sync::atomic::{AtomicU64,Ordering};
static R24_COUNTS:[AtomicU64;4]=[const{AtomicU64::new(0)};4];
fn r24_hit(i:usize,x:u64){R24_COUNTS[i].fetch_add(x,Ordering::Relaxed);}
pub fn r24_take()->[u64;4]{std::array::from_fn(|i|R24_COUNTS[i].swap(0,Ordering::Relaxed))}
'''
    build=Path(os.environ['RUNNER_TEMP'])/'r24-tiny-counts';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-tiny-counts';out.mkdir(parents=True)
    observed=build/'observed.rs';observed.write_text(text);h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_TINY')
    driver=build/'main.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['rounds','improving_rounds','rejection_with_remaining_round','tokens_in_avoidable_repeat'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_TINY '):
            _,name,size,*vals=line.split();assert len(vals)==4;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28
    result={'status':'VERIFIED_UNTIMED_ORIGINAL_LOOP_COUNTS_TOKEN_AND_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(text.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Original algorithm retained in observer; finite equality and counts only, not speedup or proof.'}
    (out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result['totals']))
if __name__=='__main__':main()
