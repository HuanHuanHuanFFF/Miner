"""Runner-only untimed opportunity counts; require frozen/observed tokens to agree."""
from pathlib import Path
import hashlib, json, os, subprocess, sys
from round4 import validate, ROOT

FIELDS = ['stride_searches','stride_key_passes','stride_extension_bytes',
          'stride_extension_comparisons','stride_length_ge11','stride_length_ge19',
          'stride_full_cap','stride_total_match_bytes','run1_searches','run1_ahead_calls',
          'run1_matches','run1_lazy_searches']

HARNESS = r'''
#![allow(dead_code)]
#[path="FROZEN"] mod frozen;
#[path="OBSERVED"] mod observed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn main(){let mut files:Vec<_>=std::fs::read_dir(std::env::args().nth(1).unwrap()).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b,"{}",p.display());assert!(decode(&s,&b));let counts=observed::r12_take();print!("R12_COUNT {} {}",p.file_name().unwrap().to_str().unwrap(),s.len());for x in counts{print!(" {}",x)}println!();}}
'''

def instrument(raw):
    text = raw.decode()
    start = text.index('pub fn st_find(')
    end = text.index('/// Record position', start)
    body = text[start:end]
    edits = [
        ('    let n = s.len();','    r12_hit(0,1);\n    let n = s.len();'),
        ('        let mut cap = n - p;','        r12_hit(1,1);\n        let mut cap = n - p;'),
        ('        (l, p - c)', '''        r12_hit(2,(l-3)as u64);
        r12_hit(3,(l-3+(l<cap)as usize)as u64);
        r12_hit(4,(l>=11)as u64);
        r12_hit(5,(l>=19)as u64);
        r12_hit(6,(l==cap)as u64);
        r12_hit(7,l as u64);
        (l, p - c)''')]
    for a,b in edits:
        assert body.count(a)==1
        body=body.replace(a,b,1)
    changed=text[:start]+body+text[end:]
    start=changed.index('pub fn run1<const H: usize>')
    end=changed.index('/// The class itself when',start)
    body=changed[start:end]
    edits2=[('            let c = pre_c;','            r12_hit(8,1);\n            let c = pre_c;'),
        ('                let mut l = f.0;','                r12_hit(10,1);\n                let mut l = f.0;'),
        ('                    let q = p + 1;','                    r12_hit(11,1);\n                    let q = p + 1;')]
    for a,b in edits2:
        assert body.count(a)==1
        body=body.replace(a,b,1)
    changed=changed[:start]+body+changed[end:]
    start=changed.index('pub fn ahead_m<const H: usize>')
    end=changed.index('/// `ahead_if`',start)
    body=changed[start:end];a='    let a = slot_of_m::<H>(s, i, km);';b='    r12_hit(9,1);\n'+a
    assert body.count(a)==1
    changed=changed[:start]+body.replace(a,b,1)+changed[end:]
    counters='''
use std::sync::atomic::{AtomicU64,Ordering};
static R12_COUNTS:[AtomicU64;12]=[const{AtomicU64::new(0)};12];
fn r12_hit(i:usize,x:u64){R12_COUNTS[i].fetch_add(x,Ordering::Relaxed);}
pub fn r12_take()->[u64;12]{std::array::from_fn(|i|R12_COUNTS[i].swap(0,Ordering::Relaxed))}
'''
    return (changed+counters).encode()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC'])
    entry=next(e for e in spec['entries']if e['name']=='r3-432-fast3')
    frozen=ROOT/entry['path']/'parse.rs';raw=frozen.read_bytes()
    assert hashlib.sha256(raw).hexdigest()==entry['hashes']['parse.rs']
    build=Path(os.environ['RUNNER_TEMP'])/'r12-counts-build';build.mkdir(exist_ok=True)
    output=Path(os.environ['RUNNER_TEMP'])/'round4-receipts'/'r12-counts';output.mkdir(parents=True,exist_ok=True)
    observed=build/'observed.rs';observed.write_bytes(instrument(raw))
    harness=HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed))
    source=build/'counts.rs';source.write_text(harness)
    binary=build/'counts'
    compile=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True)
    (output/'compile.log').write_text(compile.stdout+compile.stderr)
    assert compile.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    run=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=120)
    (output/'run.log').write_text(run.stdout+run.stderr);assert run.returncode==0
    files=[]
    for line in run.stdout.splitlines():
        if line.startswith('R12_COUNT '):
            _,name,n,*values=line.split();assert len(values)==len(FIELDS)
            p=corpus/name;assert p.stat().st_size==int(n)
            files.append({'file':name,'bytes':int(n),'input_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),
                          'counts':dict(zip(FIELDS,map(int,values)))})
    assert len(files)==28 and sum(f['bytes']for f in files)==15930000
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
        'status':'VERIFIED_FINITE_FROZEN_OBSERVED_TOKEN_AND_DECODE_EQUAL',
        'scope':'Untimed atomic observation copy; counts are not speed savings. Actual frozen candidates are timed separately.',
        'source_sha256':hashlib.sha256(raw).hexdigest(),'observer_sha256':hashlib.sha256(observed.read_bytes()).hexdigest(),
        'harness_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'files':files,
        'totals':{f:sum(x['counts'][f]for x in files)for f in FIELDS}}
    (output/'counts.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'run_id':result['run_id'],'totals':result['totals'],'scope':result['scope']}))

if __name__=='__main__':
    main()
