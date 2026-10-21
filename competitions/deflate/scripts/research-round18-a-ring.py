"""Call old/new real A planners on varied bounded match lists and cost windows."""
from pathlib import Path
import hashlib,json,os,subprocess
from round4 import ROOT,validate

HARNESS=r'''
#![allow(dead_code)]
#[path=SOURCE]mod candidate;
#[path=PARENT]mod parent;
fn next(s:&mut u64)->u64{*s=s.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);*s}
fn main(){let mut seed=0x18a15eedu64;let sizes=[0,1,2,3,257,258,259,510,511,512,513,1023,1024,1025,4095,4096];
for case in 0..2400usize{
 let n=sizes[case%sizes.len()];let mut input=vec![0u8;n];for v in &mut input{*v=if case%3==0{7}else{(next(&mut seed)>>56)as u8};}
 let mut mp=Vec::with_capacity(n+1);let mut mb=Vec::new();mp.push(0);
 for i in 0..n {let room=(n-i).min(258);if room>=3&&i>0 {let count=if case%4==0{1}else{(next(&mut seed)as usize)%4};let mut last=2;
 for _ in 0..count {if last>=room{break;}let l=last+1+(next(&mut seed)as usize)%(room-last);let d=1+(next(&mut seed)as usize)%i.min(32767);let x=(d-1)as u32;let mut record=x|(((l-3)as u32)<<15)|(parent::a_slot_of(x)<<23);if case%4==0{record|=0x80000000;}mb.push(record);last=l;}}
 mp.push(mb.len()as u32);}
 let mut lit=[0u32;256];let mut lc=[0u32;512];let mut dc=[0u32;32];for v in lit.iter_mut().chain(lc.iter_mut()).chain(dc.iter_mut()){*v=(next(&mut seed)&2047)as u32;}
 let pe=if case%2==0{n}else{(next(&mut seed)as usize)%(n+1)};let p0=if case%3==0{0}else{(next(&mut seed)as usize)%(pe+1)};
 let mut oldcost=vec![0u32;n+1];let mut newcost=vec![0u32;512];let mut a=vec![0u32;n];let mut b=a.clone();
 parent::a_dp_pass(&input,&mp,&mb,p0,pe,&lit,&lc,&dc,&mut oldcost,&mut a);
 candidate::a_dp_pass(&input,&mp,&mb,p0,pe,&lit,&lc,&dc,&mut newcost,&mut b);
 assert!(a==b,"choice case={} n={} p0={} pe={}",case,n,p0,pe);
 for i in p0..pe.min(p0+258){assert_eq!(oldcost[i],newcost[i&511],"cost case={} at={}",case,i);}
}println!("R18_A_RING_DIFFERENTIAL_OK 2400");}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    s=validate(os.environ['ROUND4_SPEC']);e=next(x for x in s['entries']if x['name']==s['r18_a_ring_check']);parent=next(x for x in s['entries']if x['name']==e['expected_equivalent_to'])
    build=Path(os.environ['RUNNER_TEMP'])/'r18-a-ring-check';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-a-ring-check';out.mkdir(parents=True)
    paths=[]
    for entry in(e,parent):
        p=ROOT/entry['path']/'parse.rs';assert hashlib.sha256(p.read_bytes()).hexdigest()==entry['hashes']['parse.rs'];paths.append(p)
    text=HARNESS.replace('SOURCE',json.dumps(str(paths[0]))).replace('PARENT',json.dumps(str(paths[1])));driver=build/'driver.rs';driver.write_text(text);binary=build/'driver'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    rr=subprocess.run([str(binary)],capture_output=True,text=True,timeout=120);(out/'run.log').write_text(rr.stdout+rr.stderr);assert rr.returncode==0 and 'R18_A_RING_DIFFERENTIAL_OK 2400'in rr.stdout
    result={'status':'VERIFIED_FINITE_ACTUAL_RUST_A_DP_WINDOW_DIFFERENTIAL','cases':2400,'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_hashes':e['hashes'],'parent_hashes':parent['hashes'],'harness_sha256':hashlib.sha256(text.encode()).hexdigest(),'scope':'Actual old/new A-DP helpers compared on finite valid match-list layouts and window bounds; choice vectors and live cost cells equal. No universal equivalence, performance or fullgate from this result.'};(out/'differential.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))

if __name__=='__main__':main()
