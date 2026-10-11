"""Untimed exact fixed-point coverage on the actual candidate; token checked."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(x for x in spec['entries']if x['name']=='r24-609-heavy-fixedpoint');source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs'];t=raw.decode()
    t=t.replace('pub fn SFsame(','pub fn r24_inner_same(',1).replace('pub fn SFheavy(','pub fn r24_inner_heavy(',1)
    t+='''
use std::sync::atomic::{AtomicU64,Ordering};
static R24_FIXED:[AtomicU64;3]=[const{AtomicU64::new(0)};3];
pub fn SFsame(a:&[u32],b:&[u32])->bool{let yes=r24_inner_same(a,b);R24_FIXED[0].fetch_add(1,Ordering::Relaxed);R24_FIXED[1].fetch_add(yes as u64,Ordering::Relaxed);yes}
pub fn SFheavy(input:&[u8],old:&[u32],prev:&[u32])->Vec<u32>{R24_FIXED[2].fetch_add(1,Ordering::Relaxed);r24_inner_heavy(input,old,prev)}
pub fn r24_take()->[u64;3]{std::array::from_fn(|i|R24_FIXED[i].swap(0,Ordering::Relaxed))}
'''
    build=Path(os.environ['RUNNER_TEMP'])/'r24-heavy-fixed';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-heavy-fixed';out.mkdir(parents=True);obs=build/'observed.rs';obs.write_text(t)
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(obs)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_FIXED');driver=build/'main.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['exact_state_checks','equal_state_checks','remaining_heavy_calls'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_FIXED '):
            _,name,size,*vals=line.split();assert len(vals)==3;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28;result={'status':'VERIFIED_UNTIMED_FIXEDPOINT_COUNTS_OBSERVER_TOKEN_AND_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(t.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Checks only where anotherheavycall exists; counts are not speed evidence. Separate native receipt compares candidate toonce.'};(out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result['totals']))
if __name__=='__main__':main()
