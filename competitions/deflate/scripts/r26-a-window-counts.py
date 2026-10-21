"""A18 native necessary-window oracle, short-match/tail/overlap helpers, and actual common cancellation."""
from pathlib import Path
import hashlib
import importlib
import json
import os

ROOT=Path(__file__).resolve().parents[1]
BUILD=importlib.import_module('r26-a-build-window-filter')
HELP=importlib.import_module('r26-a-rep-shadow')
UTIL=importlib.import_module('research-round25-len3-price')
NAME=BUILD.NAME
RUST='aa07317a57e1089ca8a9fc88acb11c4a61f3fe94f4c379831474db15e4ae9d8b'
FIELDS=['walk_calls','walk_iterations','valid_candidates','old_byte_passes','window_checks','window_passes','common_canceled','common_calls','filter_initial_active','filter_updates','length_stops','next_link_loads','final_link_depth1','final_link_depth_gt1','final_link_length_stop','query_word_loads']

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,obj):p.write_bytes((json.dumps(obj,indent=2)+'\n').encode())
EXTRA=r'''
use std::sync::atomic::{AtomicU64,Ordering};
static A18_COUNTS:[AtomicU64;16]=[const{AtomicU64::new(0)};16];
pub fn a18_take()->[u64;16]{std::array::from_fn(|i|A18_COUNTS[i].swap(0,Ordering::Relaxed))}
'''

def instrument(raw):
 assert sha(raw)==RUST
 def edit(b):
  b=HELP.once(b,'    let n = s.len();','    let mut cnt=[0u64;16];cnt[0]=1;\n    let n = s.len();')
  b=HELP.once(b,'    let mut filter=a18_filter(s,p,b8,best);','    let mut filter=a18_filter(s,p,b8,best);cnt[8]=(filter.2!=0)as u64;cnt[15]=(p<=n.saturating_sub(8)&&n>=8)as u64+(filter.2!=0&&best>=8)as u64;')
  b=HELP.once(b,'    while k > 0 {','    while k > 0 {\n        cnt[1]+=1;let mut length_stop=false;')
  b=HELP.once(b,'        if d.wrapping_sub(1) < 32768 && c + best < n {','        if d.wrapping_sub(1) < 32768 && c + best < n {\n            cnt[2]+=1;')
  b=HELP.once(b,'            if s[c + best] == pb && a18_pass(s,c,filter) {',r'''            let oldbyte=s[c+best]==pb;let pass=oldbyte&&a18_pass(s,c,filter);
            cnt[3]+=oldbyte as u64;cnt[4]+=(oldbyte&&filter.2!=0)as u64;cnt[5]+=pass as u64;
            if oldbyte&&!pass{assert!(u118_common(s,c,p,cap)<=best,"false window rejection at {} source {} best {}",p,c,best);cnt[6]+=1;}
            if pass {''')
  b=HELP.once(b,'                let l = u118_common(s, c, p, cap);','                cnt[7]+=1;\n                let l = u118_common(s, c, p, cap);')
  b=HELP.once(b,'                    if l >= stop || p + l >= n {','                    if l >= stop || p + l >= n {\n                        cnt[10]+=1;length_stop=true;')
  b=HELP.once(b,'                        filter=a18_filter(s,p,b8,l);','                        filter=a18_filter(s,p,b8,l);cnt[9]+=1;cnt[15]+=(filter.2!=0&&l>=8)as u64;')
  b=HELP.once(b,'            let nx = prev[c % W] as usize;','            cnt[11]+=1;if k<=1{cnt[if length_stop{14}else if depth==1{12}else{13}]+=1;}\n            let nx = prev[c % W] as usize;')
  return HELP.once(b,'    (best, bd)','    for i in 0..16{A18_COUNTS[i].fetch_add(cnt[i],Ordering::Relaxed);}\n    (best, bd)')
 return (HELP.edit_fn(raw.decode(),'u118_walk<',edit)+EXTRA).encode()

HARNESS=r'''
#![allow(dead_code)]
#[path=FROZEN]mod frozen;
#[path=OBSERVED]mod observed;
#[path=PARENT]mod parent;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn common(s:&[u8],a:usize,b:usize)->usize{let mut k=0;while k<258&&a+k<s.len()&&b+k<s.len()&&s[a+k]==s[b+k]{k+=1;}k}
fn helpers(){let mut cases=0usize;
 for n in [0,1,7,8,9,16,17,31,64,300]{for period in [1,3,7,17]{let s:Vec<u8>=(0..n).map(|i|(i%period)as u8).collect();
 for p in [0,n/2,n,n+1]{for best in [0,1,2,3,4,5,6,7,8,9,15,31,257,258]{let b8=frozen::a18_word(&s,p);let f=frozen::a18_filter(&s,p,b8,best);
 let active=n>=8&&p<=n-8&&best<n-p;assert_eq!(f.2!=0,active);
 if p<=n{for c in [0,p.saturating_sub(1),p.saturating_sub(8)]{if common(&s,c,p)>best{assert!(frozen::a18_pass(&s,c,f));}cases+=1;}}
 }}}}
 // Critical non-full8 short case: best+1 bytes agree, the immediately following byte differs.
 for best in 0..7{let mut s=vec![0u8;512];for i in 0..8{s[i]=(i+11)as u8;s[256+i]=(i+11)as u8;}s[256+best+1]^=1;
 let f=frozen::a18_filter(&s,256,frozen::a18_word(&s,256),best);assert_eq!(common(&s,0,256),best+1);assert!(frozen::a18_pass(&s,0,f));cases+=1;}
 let prev:[u32;32768]=std::array::from_fn(|i|i.saturating_sub(7)as u32);
 for period in [1,3,7,17]{let s:Vec<u8>=(0..300).map(|i|(i%period)as u8).collect();for p in [16,31,64,257,290]{let cap=std::cmp::min(258,s.len()-p);for have in [0,3,7,cap]{if have>cap{continue;}for dep in [1,6,12]{for gm in [0,1]{
 let a=parent::u118_walk(&s,&prev,p,p-9,cap,have,dep,128,gm,64);let b=frozen::u118_walk(&s,&prev,p,p-9,cap,have,dep,128,gm,64);assert_eq!(a,b);cases+=1;
 }}}}}
 println!("A18_HELPERS {}",cases);}
fn main(){helpers();let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);let c=tokens(&s,parent::parse);assert_eq!(a,b,"observer {}",p.display());assert_eq!(a,c,"parent {}",p.display());assert!(decode(&s,&b));let counts=observed::a18_take();
 let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();
 print!("A18_CORPUS {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
'''

def harness(observed):
 s=HARNESS
 for key,path in [('FROZEN',ROOT/'candidates'/NAME/'parse.rs'),('OBSERVED',observed),('PARENT',BUILD.BASE/'parse.rs')]:s=HELP.once(s,'#[path='+key+']','#[path='+json.dumps(str(path))+']')
 return s

def preflight(spec):
 assert spec['r26_mode']=='native'and spec['native_encoder']is True and spec['r26_a_window_counts']is True and spec['r26_finite_equivalence']is True
 e=next(e for e in spec['entries']if e['name']==NAME);raw=(ROOT/e['path']/'parse.rs').read_bytes();assert sha(raw)==e['hashes']['parse.rs']==RUST and raw==BUILD.source()
 return {'status':'VERIFIED_WINDOW_SOURCE_OBSERVER_AND_HELPER_HARNESS_NOT_NATIVE','rust_sha256':RUST,'observer_sha256':sha(instrument(raw)),'harness_sha256':sha(harness(Path('observed.rs')).encode()),'critical_short_prefix_cases':7}

def run():
 assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
 from round4 import validate
 spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
 build=Path(os.environ['RUNNER_TEMP'])/'r26-a-window-build';build.mkdir();spool=build/'spool';spool.mkdir()
 out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-window';out.mkdir(parents=True)
 observed=build/'observed.rs';raw=instrument((ROOT/'candidates'/NAME/'parse.rs').read_bytes());observed.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
 h=harness(observed);driver=build/'main.rs';driver.write_text(h);(out/'harness.rs').write_text(h)
 r={'status':'STARTED_WINDOW_NATIVE_ORACLES','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'rust_sha256':RUST,'observer_sha256':sha(raw),'harness_sha256':sha(h.encode()),'scope':'Actual A18 tokens exactly equal public658; every canceled common independently checked <=best. Fixed short-prefix/tail/overlap/directwalk helpers. Untimed.'};report=out/'receipt.json';dump(report,r)
 try:
  binary=build/'check';UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',300)
  corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';process=UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',300)
  encpath=out.parent/'r13-encoder/encoder.json';native=json.loads(encpath.read_bytes());expected={e['file']:e for e in native['rows']if e['candidate']==NAME};parent={e['file']:e for e in native['rows']if e['candidate']=='public658'};rows=[];helpers=0
  for line in process.stdout.splitlines():
   if line.startswith('A18_HELPERS '):helpers=int(line.split()[1])
   if not line.startswith('A18_CORPUS '):continue
   _,file,n,nt,*vs=line.split();assert len(vs)==len(FIELDS);c=dict(zip(FIELDS,map(int,vs)));e=expected[file];p=parent[file];data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes()
   assert len(data)==int(n)==e['raw_bytes']and len(ts)==4*int(nt)and int(nt)==e['tokens']==p['tokens']
   assert sha(data)==e['input_sha256']and sha(ts)==e['tokens_sha256']==p['tokens_sha256']and e['output_sha256']==p['output_sha256']
   assert c['old_byte_passes']==c['common_canceled']+c['common_calls']and c['common_calls']==c['window_passes']
   rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'output_sha256':e['output_sha256'],'counts':c})
  assert len(rows)==28 and len({e['file']for e in rows})==28 and helpers>5000
  r.update(status='VERIFIED_WINDOW_NATIVE_IDENTITY_NECESSARY_REJECTIONS_AND_HELPERS',rows=rows,helper_cases=helpers,totals={f:sum(e['counts'][f]for e in rows)for f in FIELDS},encoder_sha256=sha(encpath.read_bytes()),performance='NOT_MEASURED',full_gate='NOT_RUN')
 except Exception as exc:r.update(status='FAILED_OR_INCOMPLETE_WINDOW_NATIVE_ORACLES',error_type=type(exc).__name__,error=str(exc));dump(report,r);raise
 dump(report,r);print(json.dumps({'status':r['status'],'helper_cases':helpers,'totals':r['totals']},indent=2))

if __name__=='__main__':run()
