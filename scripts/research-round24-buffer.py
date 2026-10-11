"""Untimed SF overflow opportunities on unchanged once609; no source performance claim."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(e for e in spec['entries'] if e['name']=='once');source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    text=raw.decode();needle='count=SFfastadd(&mut best,&mut codes,count,SFmt(d,l));';assert text.count(needle)==1;text=text.replace(needle,'r24_observe(&best,&codes,count,SFmt(d,l),ct);'+needle)
    text+=importlib.import_module('build-round24-buffer').HELPER+'''\nuse std::sync::atomic::{AtomicU64,Ordering};
static R24_BUFFER:[AtomicU64;3]=[const{AtomicU64::new(0)};3];
fn r24_observe(best:&[u32;4],codes:&[usize;4],count:usize,t:u32,ct:&[u32;1024]){
 R24_BUFFER[0].fetch_add(1,Ordering::Relaxed);if count<4{return;}
 let dc=Z353(SFdist(t));let mut i=0usize;while i<4{if codes[i]==dc{return;}i+=1;}
 R24_BUFFER[1].fetch_add(1,Ordering::Relaxed);if SFroom(best,codes,t,ct)<4{R24_BUFFER[2].fetch_add(1,Ordering::Relaxed);}
}
pub fn r24_take()->[u64;3]{std::array::from_fn(|i|R24_BUFFER[i].swap(0,Ordering::Relaxed))}
'''
    build=Path(os.environ['RUNNER_TEMP'])/'r24-buffer';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-buffer';out.mkdir(parents=True);observed=build/'observed.rs';observed.write_text(text)
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_BUFFER');driver=build/'main.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['candidate_additions','distinct_code_overflow','replaceable_dominated_slot'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_BUFFER '):
            _,name,size,*vals=line.split();assert len(vals)==3;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28
    result={'status':'VERIFIED_UNTIMED_OVERFLOW_COUNTS_TOKEN_AND_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(text.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Fixed-cost-model opportunity only; real candidate bytes are measured separately. No timing/proof/private guarantee.'}
    (out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result['totals']))
if __name__=='__main__':main()
