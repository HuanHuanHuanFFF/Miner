"""Real Rust RF envelope differential and eliminated-transition diagnostic."""
from pathlib import Path
import hashlib,json,os,subprocess
from round4 import ROOT,validate

HARNESS=r'''
#![allow(dead_code)]
#[path=SOURCE]mod candidate;
#[path=PARENT]mod parent;
fn next(s:&mut u64)->u64{*s=s.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);*s}
fn main(){let args:Vec<_>=std::env::args().collect();let mut seed=0x185eedu64;
for case in 0..20000usize{
 let p=1+(next(&mut seed)as usize)%8192;let previous_max=3+(next(&mut seed)as usize)%256;
 let lo=3+(next(&mut seed)as usize)%256;let hi=3+(next(&mut seed)as usize)%256;
 let base=next(&mut seed)&0xffffffff;let previous_base=if case%2==0{base.saturating_sub(next(&mut seed)&65535)}else{base.wrapping_add(next(&mut seed)&65535)};
 let choice=(next(&mut seed)as u32)&!511;let previous_choice=(next(&mut seed)as u32)&!511;
 let mut prices=[0u32;1024];let mut last=0u32;for(i,x)in prices.iter_mut().enumerate(){if case%3==0||i%8==0{last=(next(&mut seed)&1023)as u32;}*x=last;}
 let mut cuts=[258u32;512];candidate::r18_rf_cuts(&prices,&mut cuts);
 let mut a=[0u64;512];for x in &mut a{*x=if case%2==0{0xffffffff00000000}else{((next(&mut seed)&0xffffffff)<<32)|(next(&mut seed)&0xffffffff)};}
 candidate::rf_dp_relax(&mut a,&prices,p-1,previous_max,previous_base,previous_choice,3);
 let mut b=a;candidate::rf_dp_relax(&mut a,&prices,p,hi,base,choice,lo);
 candidate::r18_rf_dominance(&mut b,&prices,&cuts,p,hi,base,choice,lo,previous_max,previous_base);
 assert!(a==b,"case={} p={} lo={} hi={} prevmax={}",case,p,lo,hi,previous_max);
}
println!("R18_RF_DOMINANCE_DIFFERENTIAL_OK 20000");
candidate::r18_take();
let mut paths:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|e|e.unwrap().path()).filter(|p|p.is_file()).collect();paths.sort();
for p in paths{let data=std::fs::read(&p).unwrap();let mut a=vec![0u32;data.len()];let mut b=a.clone();let na=parent::parse(&data,&mut a);let nb=candidate::parse(&data,&mut b);assert!(na==nb&&a[..na]==b[..nb],"tokens {:?}",p);
println!("R18_RF_OFFERS {} {} {}",p.file_name().unwrap().to_str().unwrap(),parent::r18_take(),candidate::r18_take());}
}
'''

def instrument(raw):
    s=raw.decode();a=s.index('pub fn rf_dp_relax(');b=s.index('\n}',a);part=s[a:b]
    old='        let v = base.wrapping_add(prices[(256+l) & 1023] as u64);';assert part.count(old)==1
    part=part.replace(old,'        R18_OFFERS.fetch_add(1,std::sync::atomic::Ordering::Relaxed);\n'+old)
    return (s[:a]+part+s[b:]+'\nstatic R18_OFFERS:std::sync::atomic::AtomicU64=std::sync::atomic::AtomicU64::new(0);\npub fn r18_take()->u64{R18_OFFERS.swap(0,std::sync::atomic::Ordering::Relaxed)}\n').encode()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    s=validate(os.environ['ROUND4_SPEC']);e=next(x for x in s['entries']if x['name']==s['r18_rf_dominance_check']);parent=next(x for x in s['entries']if x['name']==e['expected_equivalent_to'])
    build=Path(os.environ['RUNNER_TEMP'])/'r18-dominance-check';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-dominance-check';out.mkdir(parents=True)
    observed=[]
    for label,entry in [('candidate',e),('parent',parent)]:
        raw=(ROOT/entry['path']/'parse.rs').read_bytes();assert hashlib.sha256(raw).hexdigest()==entry['hashes']['parse.rs'];p=build/(label+'.rs');p.write_bytes(instrument(raw));observed.append(p)
    text=HARNESS.replace('SOURCE',json.dumps(str(observed[0]))).replace('PARENT',json.dumps(str(observed[1])));driver=build/'driver.rs';driver.write_text(text);binary=build/'driver'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    rr=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=300);(out/'run.log').write_text(rr.stdout+rr.stderr);assert rr.returncode==0 and 'R18_RF_DOMINANCE_DIFFERENTIAL_OK 20000'in rr.stdout
    rows=[]
    for line in rr.stdout.splitlines():
        if line.startswith('R18_RF_OFFERS '):
            _,file,old,new=line.split();rows.append({'file':file,'parent_offers':int(old),'candidate_offers':int(new)})
    assert len(rows)==28
    result={'status':'VERIFIED_FINITE_RUST_ENVELOPE_AND_WHOLE_PARSE_TOKEN_EQUAL','cases':20000,'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_hashes':e['hashes'],'parent_hashes':parent['hashes'],'harness_sha256':hashlib.sha256(text.encode()).hexdigest(),'rows':rows,'scope':'Finite helper states satisfy the explicitly constructed previous-envelope invariant. All28 wholeparse token streams equal frozen parent. Instrumented offer counts are diagnostic, not timing, universal equivalence, fullgate or promotion.'};(out/'differential.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({'status':result['status'],'totals':{k:sum(r[k]for r in rows)for k in('parent_offers','candidate_offers')}}))

if __name__=='__main__':main()
