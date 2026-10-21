"""Every actual triangle query is compared with the original byte matcher."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux';s=validate(os.environ['ROUND4_SPEC']);e=next(x for x in s['entries']if x['name']=='r24-609-chain-lcp8');p=ROOT/e['path']/'parse.rs';raw=p.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs'];t=raw.decode()
    needle='let hint=SFmatchlen(input,j,p,cap,0);';assert t.count(needle)==1;t=t.replace(needle,needle+'R24_CHAIN[0].fetch_add(1,Ordering::Relaxed);')
    t=t.replace('pub fn SFchainlen(','pub fn r24_inner_chain(',1)
    t+='''
use std::sync::atomic::{AtomicU64,Ordering};
static R24_CHAIN:[AtomicU64;5]=[const{AtomicU64::new(0)};5];
pub fn SFchainlen(input:&[u8],prev:&[u32],from:usize,j:usize,p:usize,cap:usize,prior:usize,seed:usize)->usize{
 let answer=r24_inner_chain(input,prev,from,j,p,cap,prior,seed);let original=SFmatchlen(input,j,p,cap,seed);assert_eq!(answer,original,"query p={} j={} from={}",p,j,from);
 let hint=((Z168(prev,from)>>16)&15)as usize;let low=Z248(prior,hint);let exact=prior!=hint&&low<8&&low<cap;let known=Z248(cap,low);
 R24_CHAIN[1].fetch_add(1,Ordering::Relaxed);R24_CHAIN[2].fetch_add(exact as u64,Ordering::Relaxed);R24_CHAIN[3].fetch_add((!exact&&known>seed)as u64,Ordering::Relaxed);R24_CHAIN[4].fetch_add(if !exact{known.saturating_sub(seed)as u64}else{0},Ordering::Relaxed);answer
}
pub fn r24_take()->[u64;5]{std::array::from_fn(|i|R24_CHAIN[i].swap(0,Ordering::Relaxed))}
'''
    b=Path(os.environ['RUNNER_TEMP'])/'r24-chain-prefix';b.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-chain-prefix';out.mkdir(parents=True);obs=b/'observed.rs';obs.write_text(t)
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(p)).replace('OBSERVED',str(obs)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_CHAIN');driver=b/'main.rs';driver.write_text(h);binary=b/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=300);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['precomputed_edges','actual_queries_checked','exact_without_matcher','extra_known_queries','extra_known_bytes'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_CHAIN '):
            _,name,size,*vals=line.split();assert len(vals)==5;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28;d={'status':'VERIFIED_FINITE_EVERY_CHAIN_QUERY_EQUAL_AND_OBSERVER_TOKEN_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(t.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Perquery equality andoperation counts onactualpublicpaths; originalencoderreceipt separately comparescandidate toonce. Extraindexbuild/decodecosts mustbe measured. No universalproof orperformanceclaim.'};(out/'receipt.json').write_bytes((json.dumps(d,indent=2)+'\n').encode());print(json.dumps(d['totals']))
if __name__=='__main__':main()
