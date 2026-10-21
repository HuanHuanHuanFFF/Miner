"""A14 untimed native checks for exact tagged-head production; original encoder identities required."""
from pathlib import Path
import hashlib
import importlib
import json
import os

ROOT=Path(__file__).resolve().parents[1]
BUILD=importlib.import_module('r26-a-build-tagged')
UTIL=importlib.import_module('research-round25-len3-price')
NAME=BUILD.NAME
RUST='f5350f86643ca65b955b4739165c6f04b27ef673a6e986c1614257687618e04c'
FIELDS=['engine_calls','fallback_calls','ahead_calls','head_zero_reads','tag_miss_skips','nonzero_tag_hits','tag_false_positives',
        'out_of_window_ahead','links','normal_queries','normal_tag_misses','lazy_queries','lazy_tag_misses',
        'cache_reuse','cache_reload','cache_reuse_miss','fresh_preinsert_checks','masked_equal_nonzero_hits']

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(path,obj):path.write_bytes((json.dumps(obj,indent=2)+'\n').encode())
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def edit_fn(s,name,edit):
 start=s.index('pub fn '+name);end=s.index('{',start)+1;depth=1
 while depth:depth+=(s[end]=='{')-(s[end]=='}');end+=1
 return s[:start]+edit(s[start:end])+s[end:]

EXTRA=r'''
use std::sync::atomic::{AtomicU64,Ordering};
static A14_COUNTS:[AtomicU64;18]=[const{AtomicU64::new(0)};18];
fn a14_hit(i:usize,n:u64){A14_COUNTS[i].fetch_add(n,Ordering::Relaxed);}
pub fn a14_take()->[u64;18]{std::array::from_fn(|i|A14_COUNTS[i].swap(0,Ordering::Relaxed))}
fn a14_check<const H:usize>(s:&[u8],head:&[u32;H],p:usize,km:u32,a:usize,c:usize,w:u64){
 let k=at_key(s,p,km);assert_eq!(a&0x007F_FFFF,k);
 let old=head[k&32767];assert_eq!((c&0x00FF_FFFF)as u32|((((a>>23)&255)as u32)<<24),old);
 let miss=old!=0&&(old>>24)!=((k>>15)&255)as u32;assert_eq!(c>=0x0100_0000,miss);
 if !miss{assert_eq!(w,pc_be8(s,(old&0x00FF_FFFF)as usize));}a14_hit(16,1);
}
'''

def instrument(raw):
 assert sha(raw)==RUST;s=raw.decode()
 def ahead(b):
  return once(b,' let w=if miss{0}else{pc_be8(s,c)};',r''' let eq=(pc_be4(s,c)&km)==(pc_be4(s,p)&km);
 assert!(!miss||!eq,"false tag rejection at {} source {}",p,c);
 a14_hit(2,1);a14_hit(3,(old==0)as u64);a14_hit(4,miss as u64);
 a14_hit(5,(old!=0&&!miss)as u64);a14_hit(6,(old!=0&&!miss&&!eq)as u64);
 a14_hit(7,(!(c<p&&p-c<=32768))as u64);a14_hit(17,(old!=0&&!miss&&eq)as u64);
 let w=if miss{0}else{pc_be8(s,c)};''')
 s=edit_fn(s,'at_ahead<',ahead)
 s=edit_fn(s,'at_link<',lambda b:once(b,' let slot=a&32767;',' a14_hit(8,1);assert!(p<0x0100_0000);\n let slot=a&32767;'))
 def probe(b):
  return once(b,' if c>=0x0100_0000{(0,0)}else{pc_probe_m(s,c,w,p,km)}',r''' a14_hit(9,1);a14_hit(10,(c>=0x0100_0000)as u64);
 let expected=pc_probe_m(s,c&0x00FF_FFFF,pc_be8(s,c&0x00FF_FFFF),p,km);
 let got=if c>=0x0100_0000{(0,0)}else{pc_probe_m(s,c,w,p,km)};
 assert_eq!(got,expected,"normal tagged probe at {}",p);got''')
 s=edit_fn(s,'at_probe(',probe)
 def lazy(b):
  return once(b,' if c>=0x0100_0000{(0,0)}else{pc_probe_lazy(s,c,w,p,l)}',r''' a14_hit(11,1);a14_hit(12,(c>=0x0100_0000)as u64);
 let expected=pc_probe_lazy(s,c&0x00FF_FFFF,pc_be8(s,c&0x00FF_FFFF),p,l);
 let got=if c>=0x0100_0000{(0,0)}else{pc_probe_lazy(s,c,w,p,l)};
 assert_eq!(got,expected,"lazy tagged probe at {}",p);got''')
 s=edit_fn(s,'at_lazy(',lazy)
 s=edit_fn(s,'at_ahead_fix<',lambda b:once(once(b,'head[a&32767]==old{(a,c,w)}',
  'head[a&32767]==old{a14_hit(13,1);a14_hit(15,(c>=0x0100_0000)as u64);(a,c,w)}'),
  ' else{at_ahead_if(s,head,p,lim,a0,c0,w0,km)}',' else{a14_hit(14,1);at_ahead_if(s,head,p,lim,a0,c0,w0,km)}'))
 def core(b):
  b=once(b,'    let n = input.len();','    a14_hit(0,1);\n    let n = input.len();')
  b=once(b,'        return pc_run1c::<H>','        a14_hit(1,1);\n        return pc_run1c::<H>')
  b=once(b,'            let c = pre_c;','            a14_check(input,&head,p,km,pre_slot,pre_c,pre_w);\n            let c = pre_c;')
  return once(b,'                    let c2 = pre_c;','                    a14_check(input,&head,q,km,pre_slot,pre_c,pre_w);\n                    let c2 = pre_c;')
 return (edit_fn(s,'at_run1c<',core)+EXTRA).encode()

HARNESS=r'''
#![allow(dead_code)]
#[path=FROZEN]mod frozen;
#[path=OBSERVED]mod observed;
#[path=PARENT]mod parent;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn direct<const H:usize>(s:&[u8],km:u32){let mut a=vec![0;s.len()];let mut b=vec![0;s.len()];let mut c=vec![0;s.len()];
 let na=parent::pc_run1c::<H>(s,&mut a,4,258,1000000,km,2,if km==0xFFFF_FFFF{4}else{3});
 let nb=frozen::at_run1c::<H>(s,&mut b,4,258,1000000,km,2,if km==0xFFFF_FFFF{4}else{3});
 let nc=observed::at_run1c::<H>(s,&mut c,4,258,1000000,km,2,if km==0xFFFF_FFFF{4}else{3});
 a.truncate(na);b.truncate(nb);c.truncate(nc);assert_eq!(a,b,"parent/direct H{} n{} km{}",H,s.len(),km);assert_eq!(b,c);assert!(decode(s,&a));
 let counts=observed::a14_take();let fallback=s.len()>=0x0100_0000||H<32768||H==65536||H==131072||H==262144;
 assert_eq!(counts[0],1);assert_eq!(counts[1],fallback as u64);println!("A14_DIRECT {} {} {} {}",H,s.len(),km,counts[1]);}
fn helpers(){let s:Vec<u8>=(0..128).map(|i|(i%7)as u8).collect();
 for km in [0xFFFF_FFFF,0xFFFF_FF00]{let mut head=[0u32;32768];let mut prev=[0u32;32768];
 for p in [0,1,15]{let a=frozen::at_ahead(&s,&head,p,km);assert_eq!(a.0&32767,parent::pc_slot_of_m::<32768>(&s,p,km));assert_eq!(a.1,0);assert_eq!(a.2,parent::pc_be8(&s,0));}
 let k=frozen::at_key(&s,0,km);frozen::at_link(&mut head,&mut prev,k,0);assert_eq!(prev[0],0);
 let a=frozen::at_ahead(&s,&head,7,km);assert_eq!(a.1,0);assert_eq!(a.2,parent::pc_be8(&s,0));
 // Synthetic high positions test exact packing/link projection only; no out-of-range byte read.
 for p in [0x00FF_FFFE,0x00FF_FFFF]{let old=head[k&32767];frozen::at_link(&mut head,&mut prev,k,p);
 assert_eq!(head[k&32767]&0x00FF_FFFF,p as u32);assert_eq!(head[k&32767]>>24,((k>>15)&255)as u32);assert_eq!(prev[p%32768],old&0x00FF_FFFF);}
 }
 let mut s3=vec![0u8;64];s3[0..4].copy_from_slice(&[11,22,33,44]);s3[16..20].copy_from_slice(&[11,22,33,99]);
 assert_eq!(frozen::at_key(&s3,0,0xFFFF_FF00),frozen::at_key(&s3,16,0xFFFF_FF00));
 println!("A14_HELPERS source0_km3_maxpos PASS");}
fn main(){helpers();for n in 0..65{let s:Vec<u8>=(0..n).map(|i|(i%7)as u8).collect();for km in [0xFFFF_FFFF,0xFFFF_FF00]{direct::<32768>(&s,km);}}
 for period in [1,2,7,17,251]{for n in [257,1024,32784]{let s:Vec<u8>=(0..n).map(|i|(i%period)as u8).collect();for km in [0xFFFF_FFFF,0xFFFF_FF00]{direct::<32781>(&s,km);}}}
 let mut x=7u32;let mut s=Vec::new();for _ in 0..66000{x=x.wrapping_mul(1664525).wrapping_add(1013904223);s.push((x>>24)as u8);}for i in 0..258{s[33040+i]=s[272+i];}
 for km in [0xFFFF_FFFF,0xFFFF_FF00]{direct::<131100>(&s,km);direct::<65536>(&s,km);direct::<16384>(&s,km);}
 // Exercise actual original-kernel fallback and just-below-boundary tagged execution.
 for n in [0x00FF_FFFF,0x0100_0000,0x0100_0001]{let s:Vec<u8>=(0..n).map(|i|(i%7)as u8).collect();direct::<32768>(&s,0xFFFF_FFFF);}
 let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);let c=tokens(&s,parent::parse);
 assert_eq!(a,b,"observer {}",p.display());assert_eq!(a,c,"parent {}",p.display());assert!(decode(&s,&b));let counts=observed::a14_take();
 let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();
 print!("A14_CORPUS {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
'''

def harness(frozen,observed,parent):
 s=HARNESS
 for key,path in [('FROZEN',frozen),('OBSERVED',observed),('PARENT',parent)]:s=once(s,'#[path='+key+']','#[path='+json.dumps(str(path))+']')
 assert not any('#[path='+x+']'in s for x in ['FROZEN','OBSERVED','PARENT'])
 return s

def preflight(spec):
 assert spec['r26_mode']=='native'and spec['native_encoder']is True and spec['r26_a_tagged_counts']is True
 e=next(e for e in spec['entries']if e['name']==NAME);raw=(ROOT/e['path']/'parse.rs').read_bytes()
 assert sha(raw)==RUST==e['hashes']['parse.rs']and BUILD.source()==raw
 assert e['expected_equivalent_to']=='public641'and spec['r26_finite_equivalence']is True
 return {'status':'VERIFIED_SOURCE_AND_HARNESS_PREFLIGHT_NOT_NATIVE','rust_sha256':RUST,'observer_sha256':sha(instrument(raw)),
  'harness_preflight_sha256':sha(harness(ROOT/e['path']/'parse.rs',Path('observed.rs'),BUILD.PARENT/'parse.rs').encode())}

def run():
 assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
 from round4 import validate
 spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
 build=Path(os.environ['RUNNER_TEMP'])/'r26-a-tagged-build';build.mkdir();spool=build/'spool';spool.mkdir()
 out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-tagged';out.mkdir(parents=True)
 frozen=ROOT/'candidates'/NAME/'parse.rs';observer=build/'observed.rs';raw=instrument(frozen.read_bytes());observer.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
 h=harness(frozen,observer,BUILD.PARENT/'parse.rs');driver=build/'main.rs';driver.write_text(h);(out/'harness.rs').write_text(h)
 r={'status':'STARTED_NATIVE_TAGGED_CHECKS','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
  'rust_sha256':RUST,'observer_sha256':sha(raw),'harness_sha256':sha(h.encode()),'scope':'Untimed original-parent/frozen/observer tokens, decode, every actual normal/lazy rejected probe oracle, source0/km3/maxpos helpers and actual 2^24 fallback boundary.'}
 report=out/'receipt.json';dump(report,r)
 try:
  binary=build/'check';UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
  corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';process=UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',240)
  native_path=out.parent/'r13-encoder/encoder.json';native=json.loads(native_path.read_bytes());expected={e['file']:e for e in native['rows']if e['candidate']==NAME};assert len(expected)==28
  parent={e['file']:e for e in native['rows']if e['candidate']=='public641'};assert len(parent)==28
  rows=[];direct=[];helpers=False
  for line in process.stdout.splitlines():
   if line.startswith('A14_HELPERS '):helpers=line=='A14_HELPERS source0_km3_maxpos PASS'
   if line.startswith('A14_DIRECT '):
    _,H,n,km,fallback=line.split();direct.append(dict(H=int(H),n=int(n),km=int(km),fallback=bool(int(fallback))))
   if not line.startswith('A14_CORPUS '):continue
   _,file,n,nt,*vs=line.split();assert len(vs)==len(FIELDS);c=dict(zip(FIELDS,map(int,vs)));e=expected[file];p=parent[file]
   data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes()
   assert len(data)==int(n)==e['raw_bytes']and len(ts)==4*int(nt)and int(nt)==e['tokens']==p['tokens']
   assert sha(data)==e['input_sha256']and sha(ts)==e['tokens_sha256']==p['tokens_sha256']and e['output_sha256']==p['output_sha256']
   assert c['ahead_calls']==c['head_zero_reads']+c['tag_miss_skips']+c['nonzero_tag_hits']
   assert c['nonzero_tag_hits']==c['tag_false_positives']+c['masked_equal_nonzero_hits']
   assert c['fresh_preinsert_checks']==c['normal_queries']+c['lazy_queries']
   rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'output_sha256':e['output_sha256'],'counts':c})
  assert len(rows)==28 and len({e['file']for e in rows})==28 and len(direct)==169 and helpers
  r.update(status='VERIFIED_NATIVE_TAGGED_PARENT_IDENTITY_DECODE_ORACLES_AND_BOUNDARIES',native_encoder_sha256=sha(native_path.read_bytes()),direct=direct,helpers=helpers,
   rows=rows,totals={f:sum(e['counts'][f]for e in rows)for f in FIELDS},performance='NOT_MEASURED',full_gate='NOT_RUN')
 except Exception as exc:r.update(status='FAILED_OR_INCOMPLETE_NATIVE_TAGGED_CHECKS',error_type=type(exc).__name__,error=str(exc));dump(report,r);raise
 dump(report,r);print(json.dumps({'status':r['status'],'totals':r['totals']},indent=2))

if __name__=='__main__':run()
