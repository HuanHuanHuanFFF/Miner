"""Finite shifted-prefix invariant checks and native mechanism counts."""
from pathlib import Path
import hashlib,json,os,subprocess
from round4 import ROOT,validate

HARNESS=r'''
#![allow(dead_code)]
#[path=SOURCE]mod candidate;
#[path=PARENT]mod parent;
fn next(s:&mut u64)->u64{*s=s.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);*s}
fn main(){let args:Vec<_>=std::env::args().collect();let mut seed=0x18af5eedu64;
for case in 0..20000usize{
 let n=768usize;let mut input=vec![0u8;n];for v in &mut input{*v=(next(&mut seed)>>56)as u8;}
 let p=300+(next(&mut seed)as usize)%100;let d=1+(next(&mut seed)as usize)%280;let len=3+(next(&mut seed)as usize)%256;let q=p-d;
 // Sequential copy is also valid for overlapping matches.
 for i in 0..len{input[p-1+i]=input[q-1+i];}
 let original_cap=(n-p).min(258);let cap=if case%5==0{(next(&mut seed)as usize)%259}else{original_cap};
 let hint=(len as u32)|((d as u32)<<9)|((next(&mut seed)as u32&31)<<25);
 let a=candidate::mlen(&input,q,p,cap);let b=candidate::r18_rf_mlen(&input,q,p,cap,hint);assert!(a==b,"case={} p={} q={} cap={} len={}",case,p,q,cap,len);
 let q2=if q>1{q-1}else{q+1};let a2=candidate::mlen(&input,q2,p,cap);let b2=candidate::r18_rf_mlen(&input,q2,p,cap,hint);assert_eq!(a2,b2);
 assert_eq!(candidate::r18_rf_mlen(&input,n+1,p,cap,hint),0);
}
println!("R18_RF_PREFIX_DIFFERENTIAL_OK 20000");candidate::r18_take();
let mut paths:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|e|e.unwrap().path()).filter(|p|p.is_file()).collect();paths.sort();
for p in paths{let data=std::fs::read(&p).unwrap();let mut a=vec![0u32;data.len()];let mut b=a.clone();let na=parent::parse(&data,&mut a);let nb=candidate::parse(&data,&mut b);assert!(na==nb&&a[..na]==b[..nb],"tokens {:?}",p);let c=candidate::r18_take();
println!("R18_RF_PREFIX {} {} {} {}",p.file_name().unwrap().to_str().unwrap(),c[0],c[1],c[2]);}
}
'''

def instrument(raw):
    s=raw.decode();old='    known + mlen(input, a+known, b+known, cap-known)';assert s.count(old)==1
    s=s.replace(old,'    R18_PREFIX[0].fetch_add(1,std::sync::atomic::Ordering::Relaxed);\n    if known>0 { R18_PREFIX[1].fetch_add(1,std::sync::atomic::Ordering::Relaxed); R18_PREFIX[2].fetch_add(known as u64,std::sync::atomic::Ordering::Relaxed); }\n'+old)
    return (s+'\nstatic R18_PREFIX:[std::sync::atomic::AtomicU64;3]=[const{std::sync::atomic::AtomicU64::new(0)};3];\npub fn r18_take()->[u64;3]{std::array::from_fn(|i|R18_PREFIX[i].swap(0,std::sync::atomic::Ordering::Relaxed))}\n').encode()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    s=validate(os.environ['ROUND4_SPEC']);e=next(x for x in s['entries']if x['name']==s['r18_rf_prefix_check']);parent=next(x for x in s['entries']if x['name']==e['expected_equivalent_to'])
    build=Path(os.environ['RUNNER_TEMP'])/'r18-prefix-check';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-prefix-check';out.mkdir(parents=True)
    raw=(ROOT/e['path']/'parse.rs').read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs'];observed=build/'observed.rs';observed.write_bytes(instrument(raw));p=ROOT/parent['path']/'parse.rs';assert hashlib.sha256(p.read_bytes()).hexdigest()==parent['hashes']['parse.rs']
    text=HARNESS.replace('SOURCE',json.dumps(str(observed))).replace('PARENT',json.dumps(str(p)));driver=build/'driver.rs';driver.write_text(text);binary=build/'driver'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    rr=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=300);(out/'run.log').write_text(rr.stdout+rr.stderr);assert rr.returncode==0 and 'R18_RF_PREFIX_DIFFERENTIAL_OK 20000'in rr.stdout
    rows=[]
    for line in rr.stdout.splitlines():
        if line.startswith('R18_RF_PREFIX '):
            _,file,calls,hits,saved=line.split();rows.append({'file':file,'calls':int(calls),'prefix_hits':int(hits),'prefix_bytes_reused':int(saved)})
    assert len(rows)==28
    result={'status':'VERIFIED_FINITE_VALID_HINT_AND_WHOLE_PARSE_TOKEN_EQUAL','cases':20000,'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_hashes':e['hashes'],'parent_hashes':parent['hashes'],'harness_sha256':hashlib.sha256(text.encode()).hexdigest(),'rows':rows,'scope':'Valid preceding matches are explicitly constructed, including overlap and tail. Extra different-distance/invalid-range branches checked. All28 wholeparse tokens equal parent. Prefix-byte counters are not measured time savings or a fullgate.'};(out/'differential.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({'status':result['status'],'totals':{k:sum(r[k]for r in rows)for k in('calls','prefix_hits','prefix_bytes_reused')}}))

if __name__=='__main__':main()
