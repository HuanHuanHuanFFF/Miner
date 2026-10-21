"""Untimed SF query partitions/cardinality; original solver result is retained."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
WRAPPER='''
use std::sync::atomic::{AtomicU64,Ordering};
static R24_GROUP:[AtomicU64;8]=[const{AtomicU64::new(0)};8];
fn r24_slots(n:usize){R24_GROUP[n.min(4)].fetch_add(1,Ordering::Relaxed);}
pub fn r24_take()->[u64;8]{std::array::from_fn(|i|R24_GROUP[i].swap(0,Ordering::Relaxed))}
fn R24query(rm:&[u64;4096],ct:&[u32;1024],bend:&[u32;512],i:usize,lo:usize,hi:usize,dcs:u64,best:u64)->u64 {
 let result=Z437(rm,ct,bend,i,lo,hi,dcs,best);let mut x=lo;let mut old=0usize;
 while old<32 && x<=hi && x<259 {let e=Z248(Z457(bend[x%512]as usize,x),hi);x=e.wrapping_add(1);old+=1;}
 x=lo;let mut new=0usize;
 while new<32 && x<=hi && x<259 {let mut e=x;while e<hi && e<258 && e-x<31 && ct[(e+1)%1024]==ct[x%1024]{e+=1;}x=e+1;new+=1;}
 R24_GROUP[5].fetch_add(1,Ordering::Relaxed);R24_GROUP[6].fetch_add(old as u64,Ordering::Relaxed);R24_GROUP[7].fetch_add(new as u64,Ordering::Relaxed);result
}
'''
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(e for e in spec['entries']if e['name']=='once');source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs'];text=raw.decode()
    for name,nextname in [('SFsolve','SFpatch'),('SFseed','SFprefix')]:
        a=text.index('pub fn '+name+'(');b=text.index('pub fn '+nextname+'(',a);part=text[a:b];assert part.count('Z437(')==1;part=part.replace('Z437(','R24query(');needle='let end=Z168(starts,i.wrapping_add(1)) as usize;';assert part.count(needle)==1;part=part.replace(needle,needle+'r24_slots(end.saturating_sub(k));');text=text[:a]+part+text[b:]
    a=text.index('pub fn SFprefix(');b=text.index('pub const SFTOKDEPTH',a);part=text[a:b];assert part.count('Z437(')==1;part=part.replace('Z437(','R24query(');needle='let end=Z168(starts,i.wrapping_add(1)) as usize;';assert part.count(needle)==1;part=part.replace(needle,needle+'r24_slots(end.saturating_sub(k));');text=text[:a]+part+text[b:]+WRAPPER
    build=Path(os.environ['RUNNER_TEMP'])/'r24-groups';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-groups';out.mkdir(parents=True);obs=build/'observed.rs';obs.write_text(text)
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(obs)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_GROUP');driver=build/'main.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=360);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['slots0','slots1','slots2','slots3','slots4','long_queries','old_groups','equal_price_groups'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_GROUP '):
            _,name,size,*vals=line.split();assert len(vals)==8;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28
    result={'status':'VERIFIED_UNTIMED_ORIGINAL_QUERY_COUNTS_TOKEN_AND_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(text.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Actual old-path counts; new grouping counts model only. Candidate bytes separately tested; no timing or gate claim.'};(out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result['totals']))
if __name__=='__main__':main()
