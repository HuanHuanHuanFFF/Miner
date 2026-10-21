"""Differentially call old/new realRust helpers on ring and integer boundaries."""
from pathlib import Path
import hashlib,json,os,subprocess
from round4 import ROOT,validate

HARNESS=r'''
#![allow(dead_code)]
#[path=SOURCE]mod candidate;
fn next(s:&mut u64)->u64{*s=s.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);*s}
fn main(){let mut seed=0x5eed18u64;for case in 0..6000usize{
 let ps=[0,1,255,256,257,510,511,512,1023,usize::MAX,usize::MAX-128];let p=if case%3==0{ps[case%ps.len()]}else{(next(&mut seed)as usize)%4096};
 let ls=[0,1,3,8,10,127,255,258,259,usize::MAX];let lo=ls[case%ls.len()];let hi=if case%5==0{usize::MAX}else{(next(&mut seed)as usize)%300};
 let base=if case%3==0{u64::MAX-(next(&mut seed)&65535)}else{next(&mut seed)&65535};let choice=next(&mut seed)as u32;
 let mut prices=[0u32;1024];for x in &mut prices{*x=if case%7==0{0}else{(next(&mut seed)&1023)as u32};}
 let mut a=[0u64;512];for x in &mut a{*x=if case%2==0{0xffffffff00000000}else{((next(&mut seed)&131071)<<32)|(next(&mut seed)&0xffffffff)};}
 let mut b=a;candidate::rf_dp_relax(&mut a,&prices,p,hi,base,choice,lo);candidate::r18_rf_relax(&mut b,&prices,p,hi,base,choice,lo);
 assert!(a==b,"case={} p={} lo={} hi={} base={}",case,p,lo,hi,base);
 }println!("R18_RF_SPAN_DIFFERENTIAL_OK 6000");}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    s=validate(os.environ['ROUND4_SPEC']);e=next(x for x in s['entries']if x['name']==s['r18_rf_span_equiv']);source=ROOT/e['path']/'parse.rs';assert hashlib.sha256(source.read_bytes()).hexdigest()==e['hashes']['parse.rs']
    build=Path(os.environ['RUNNER_TEMP'])/'r18-span-diff';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-span-diff';out.mkdir(parents=True)
    text=HARNESS.replace('SOURCE',json.dumps(str(source)));driver=build/'driver.rs';driver.write_text(text);binary=build/'driver'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    rr=subprocess.run([str(binary)],capture_output=True,text=True,timeout=120);(out/'run.log').write_text(rr.stdout+rr.stderr);assert rr.returncode==0 and 'R18_RF_SPAN_DIFFERENTIAL_OK 6000'in rr.stdout
    result={'status':'VERIFIED_FINITE_ACTUAL_RUST_HELPER_DIFFERENTIAL','cases':6000,'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_hashes':e['hashes'],'harness_sha256':hashlib.sha256(text.encode()).hexdigest(),'scope':'Actualold/newhelper arrays equal on declaredfinitewrap/integer/tie cases. Not universal proof, fullgate or performance evidence.'};(out/'differential.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))

if __name__=='__main__':main()
