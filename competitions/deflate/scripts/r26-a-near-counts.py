"""A16b: untimed actual write-suppression coverage after A16 original encoder quality."""
from pathlib import Path
import hashlib
import importlib
import json
import os

ROOT=Path(__file__).resolve().parents[1]
NAME='r26-a-641-near-retain'
BASE=ROOT/'candidates'/NAME/'parse.rs'
RUST='83ae95175233346aebacbadadb0440d78b19e97676104626ce1fa76422d4fe72'
UTIL=importlib.import_module('research-round25-len3-price')
HELP=importlib.import_module('r26-a-rep-shadow')
FIELDS=['link_calls','skipped_links','gap_one_links','query_links','query_skips','record_links','record_skips','exception_links','exception_would_skip']

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,obj):p.write_bytes((json.dumps(obj,indent=2)+'\n').encode())

EXTRA=r'''
use std::sync::atomic::{AtomicU64,Ordering};
static A16_MODE:AtomicU64=AtomicU64::new(0);
static A16_COUNTS:[AtomicU64;9]=[const{AtomicU64::new(0)};9];
fn a16_hit(i:usize,n:u64){A16_COUNTS[i].fetch_add(n,Ordering::Relaxed);}
pub fn a16_take()->[u64;9]{assert_eq!(A16_MODE.load(Ordering::Relaxed),0);std::array::from_fn(|i|A16_COUNTS[i].swap(0,Ordering::Relaxed))}
'''

def instrument(raw):
 assert sha(raw)==RUST;s=raw.decode()
 def link(b):
  return HELP.once(b,' if n!=500000&&gap>=2&&gap<=8{return;}',r''' let skip=n!=500000&&gap>=2&&gap<=8;let rec=A16_MODE.load(Ordering::Relaxed)==1;
 a16_hit(0,1);a16_hit(1,skip as u64);a16_hit(2,(gap==1)as u64);
 a16_hit(if rec{5}else{3},1);a16_hit(if rec{6}else{4},skip as u64);
 a16_hit(7,(n==500000)as u64);a16_hit(8,(n==500000&&gap>=2&&gap<=8)as u64);
 if skip{return;}''')
 s=HELP.edit_fn(s,'a16_link<',link)
 def record(b):
  b=HELP.once(b,'    let mut ins = ins0;','    assert_eq!(A16_MODE.swap(1,Ordering::Relaxed),0);\n    let mut ins = ins0;')
  assert b.endswith('\n}');return b[:-2]+'\n    assert_eq!(A16_MODE.swap(0,Ordering::Relaxed),1);\n}'
 return (HELP.edit_fn(s,'pc_f_record3<',record)+EXTRA).encode()

HARNESS=r'''
#![allow(dead_code)]
#[path=FROZEN]mod frozen;
#[path=OBSERVED]mod observed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn helpers(){for n in [100000,500000]{for gap in [0,1,2,3,8,9,32768]{
 let mut head=[0u32;32768];let mut prev=[77u32;32768];let p=32769usize;let old=(p-gap)as u32;head[0]=old;head[1]=1;
 frozen::a16_link(&mut head,&mut prev,0,p,n);let skip=n!=500000&&gap>=2&&gap<=8;
 assert_eq!(head[0],if skip{old}else{p as u32});assert_eq!(head[1],1);assert_eq!(prev[p%32768],if skip{77}else{old});}}
 println!("A16_HELPERS 14");}
fn main(){helpers();let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b,"{}",p.display());let counts=observed::a16_take();
 let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();
 print!("A16_CORPUS {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
'''

def harness(observed):
 s=HARNESS
 for key,path in [('FROZEN',BASE),('OBSERVED',observed)]:s=HELP.once(s,'#[path='+key+']','#[path='+json.dumps(str(path))+']')
 return s

def preflight(spec):
 assert spec['r26_mode']=='native'and spec['native_encoder']is False and spec['r26_a_near_counts']is True
 assert all(e['control']for e in spec['entries'])and spec['r26_expected_candidates']==0
 e=next(e for e in spec['entries']if e['name']==NAME);assert e['hashes']['parse.rs']==RUST==sha(BASE.read_bytes())
 native_path=ROOT/spec['r26_a_near_baseline'];native=json.loads(native_path.read_bytes())
 assert native['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'and native['source_hashes'][NAME]['parse.rs']==RUST
 assert len([e for e in native['rows']if e['candidate']==NAME])==28
 return {'status':'VERIFIED_A16_COUNTER_SOURCE_HARNESS_AND_CANDIDATE_TOKEN_BINDING_NOT_NATIVE','rust_sha256':RUST,'observer_sha256':sha(instrument(BASE.read_bytes())),'harness_sha256':sha(harness(Path('observed.rs')).encode()),'baseline_sha256':sha(native_path.read_bytes())}

def run():
 assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
 from round4 import validate
 spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
 build=Path(os.environ['RUNNER_TEMP'])/'r26-a-near-counts-build';build.mkdir();spool=build/'spool';spool.mkdir()
 out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-near-counts';out.mkdir(parents=True)
 observed=build/'observed.rs';raw=instrument(BASE.read_bytes());observed.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
 h=harness(observed);driver=build/'main.rs';driver.write_text(h);(out/'harness.rs').write_text(h)
 r={'status':'STARTED_ACTUAL_RETAIN_WRITE_COUNTS','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
  'rust_sha256':RUST,'observer_sha256':sha(raw),'harness_sha256':sha(h.encode()),'baseline_sha256':checked['baseline_sha256'],'scope':'Exact A16 trajectory and frozen token identity. Link suppression coverage separated by real query/record context; 14 direct ring/gap/exception checks. Not timing.'}
 report=out/'receipt.json';dump(report,r)
 try:
  binary=build/'check';UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
  corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';process=UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',240)
  native=json.loads((ROOT/spec['r26_a_near_baseline']).read_bytes());expected={e['file']:e for e in native['rows']if e['candidate']==NAME};rows=[];helpers=False
  for line in process.stdout.splitlines():
   if line=='A16_HELPERS 14':helpers=True
   if not line.startswith('A16_CORPUS '):continue
   _,file,n,nt,*vs=line.split();assert len(vs)==len(FIELDS);c=dict(zip(FIELDS,map(int,vs)));e=expected[file]
   data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes();assert len(data)==int(n)==e['raw_bytes']and len(ts)==4*int(nt)and int(nt)==e['tokens']
   assert sha(data)==e['input_sha256']and sha(ts)==e['tokens_sha256']
   assert c['link_calls']==c['query_links']+c['record_links']and c['skipped_links']==c['query_skips']+c['record_skips']
   rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'counts':c})
  assert len(rows)==28 and len({e['file']for e in rows})==28 and helpers
  r.update(status='VERIFIED_ACTUAL_RETAIN_WRITE_COVERAGE_AND_FROZEN_TOKEN_IDENTITY',rows=rows,helper_cases=14,totals={f:sum(e['counts'][f]for e in rows)for f in FIELDS},performance='NOT_MEASURED',full_gate='NOT_RUN')
 except Exception as exc:r.update(status='FAILED_OR_INCOMPLETE_ACTUAL_RETAIN_COUNTS',error_type=type(exc).__name__,error=str(exc));dump(report,r);raise
 dump(report,r);print(json.dumps({'status':r['status'],'totals':r['totals']},indent=2))

if __name__=='__main__':run()
