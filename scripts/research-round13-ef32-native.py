"""Direct EF32 function cases, supplementing the whole-parser finite checks."""
from pathlib import Path
import hashlib,json,os,subprocess
from round4 import ROOT,validate

HARNESS=r'''
#![allow(dead_code)]
#[path=CANDIDATE]mod candidate;
#[path=REFERENCE]mod reference;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut v=Vec::new();for&t in ts{if t<256{v.push(t as u8);}else{if !(16777216..25165824).contains(&t){return false;}let x=t-16777216;let d=(x/256+1)as usize;let l=(x%256+3)as usize;if d>v.len()||v.len()+l>s.len(){return false;}for _ in 0..l{let b=v[v.len()-d];v.push(b);}}}v==s}
fn sample(n:usize,mode:usize,mut z:u64)->Vec<u8>{let mut v=Vec::new();while v.len()<n{z^=z<<13;z^=z>>7;z^=z<<17;let zero=mode==0||z%4!=0;v.extend([if zero{0}else{z as u8},if zero{0}else{(z>>8)as u8},(z>>16)as u8,(0x3b+(z%5)as u8)|if z&32!=0{128}else{0}]);}v.truncate(n);v}
fn main(){let mut count=0;let mut changes=0;for n in [0,1,15,16,17,31,32,32767,32768,32769,65535,65536,65537,131072,262144,350000]{for mode in 0..2{for seed in [1,987654321]{let s=sample(n,mode,seed);let a=tokens(&s,reference::ef32_run);let b=tokens(&s,candidate::ef32_run);assert!(decode(&s,&a)&&decode(&s,&b),"EF32 decode n={} mode={} seed={}",n,mode,seed);count+=1;if a!=b{changes+=1;}println!("EF32_NATIVE {} {} {} {} {} {}",n,mode,seed,a.len(),b.len(),a==b);}}}println!("EF32_NATIVE_RESULT {} {}",count,changes);}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);entries=[e for e in spec['entries']if e.get('native_function_check')=='ef32_run'];assert len(entries)==1
    candidate=entries[0];reference=next(e for e in spec['entries']if e['name']==candidate['comparison_baseline'])
    paths={k:ROOT/e['path']/'parse.rs'for k,e in [('CANDIDATE',candidate),('REFERENCE',reference)]}
    assert all(hashlib.sha256(paths[k].read_bytes()).hexdigest()==e['hashes']['parse.rs']for k,e in [('CANDIDATE',candidate),('REFERENCE',reference)])
    build=Path(os.environ['RUNNER_TEMP'])/'r13-ef32-direct-build';build.mkdir(exist_ok=True);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-ef32-direct';out.mkdir(parents=True,exist_ok=True)
    text=HARNESS
    for k,p in paths.items():text=text.replace(k,json.dumps(str(p)))
    source=build/'direct.rs';source.write_text(text);binary=build/'direct'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    r=subprocess.run([str(binary)],capture_output=True,text=True,timeout=120);(out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    lines=[s for s in r.stdout.splitlines()if s.startswith('EF32_NATIVE_RESULT ')];assert len(lines)==1;_,n,changed=lines[0].split();assert int(n)==64
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'candidate':candidate['name'],'reference':reference['name'],'source_hashes':{e['name']:e['hashes']for e in(candidate,reference)},
        'status':'VERIFIED_FINITE_DIRECT_EF32_DECODE','function':'ef32_run','cases':64,'token_changes':int(changed),'harness_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
        'scope':'Direct element-aligned function exercised on two floating-byte patterns, two seeds,16 boundary lengths including32/64KiB wraps and350000B. Token changes permitted. Supplements540 whole-parser checks; not all-input proof or performance.'}
    (out/'direct.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))

if __name__=='__main__':main()
