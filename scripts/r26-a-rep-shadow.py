"""A15: previous emitted distance as a non-chain offer on frozen public641 trajectory; untimed."""
from pathlib import Path
import hashlib
import importlib
import json
import os

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round26-public-641/parse.rs'
RUST='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
UTIL=importlib.import_module('research-round25-len3-price')
FIELDS=['engine_calls','normal_queries','normal_previous_match','normal_usable_distance','rep_same_head','rep_same_prev1','rep_same_prev2',
 'normal_rep_match','normal_rep_longer','normal_rep_gain_better','normal_rep_gain_equal','normal_rep_gain_worse',
 'exchange_third_enabled','exchange_gain_better','exchange_gain_equal','exchange_gain_worse','exchange_length_extra','exchange_length_lost',
 'lazy_queries','lazy_previous_match','lazy_rep_same_head','lazy_rep_match','lazy_rep_beats_head','lazy_rep_changes_choice',
 'lazy_rep_length_extra','normal_rep_length_extra','normal_rep_distance_smaller','normal_rep_bytechecks',
 'lazy_exchange_eligible','lazy_exchange_gain_better','lazy_exchange_gain_equal','lazy_exchange_gain_worse',
 'lazy_exchange_length_extra','lazy_exchange_length_lost','exchange_distinct_source']

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,obj):p.write_bytes((json.dumps(obj,indent=2)+'\n').encode())
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def edit_fn(s,name,edit):
 a=s.index('pub fn '+name);end=s.index('{',a)+1;depth=1
 while depth:depth+=(s[end]=='{')-(s[end]=='}');end+=1
 return s[:a]+edit(s[a:end])+s[end:]

EXTRA=r'''
use std::sync::atomic::{AtomicU64,Ordering};
static A15_COUNTS:[AtomicU64;35]=[const{AtomicU64::new(0)};35];
fn a15_hit(i:usize,n:u64){A15_COUNTS[i].fetch_add(n,Ordering::Relaxed);}
pub fn a15_take()->[u64;35]{std::array::from_fn(|i|A15_COUNTS[i].swap(0,Ordering::Relaxed))}
fn a15_distance(out:&[u32],nt:usize)->usize{if nt==0{0}else{let t=out[nt-1];if t>=16777216&&t<25165824{((t-16777216)/256+1)as usize}else{0}}}
fn a15_normal(s:&[u8],out:&[u32],nt:usize,p:usize,c:usize,cl:usize,prev:&[u32;32768],f:(usize,usize),g:(usize,usize),dp:usize,minl:usize,km:u32){
 a15_hit(1,1);let d=a15_distance(out,nt);if d==0{return;}a15_hit(2,1);if d>p{return;}a15_hit(3,1);
 let source=p-d;let third=prev[cl%32768]as usize;
 a15_hit(4,(source==c)as u64);a15_hit(5,(source==cl)as u64);a15_hit(6,(source==third)as u64);
 let rep=pc_probe_m(s,source,pc_be8(s,source),p,km);a15_hit(27,1);
 if rep.0>=3{
  assert_eq!(pc_common_from(s,source,p,std::cmp::min(258,s.len()-p),0),rep.0);
  a15_hit(7,1);a15_hit(8,(rep.0>g.0)as u64);a15_hit(9,(pc_gain(rep.0,rep.1)>pc_gain(g.0,g.1))as u64);
  a15_hit(10,(pc_gain(rep.0,rep.1)==pc_gain(g.0,g.1))as u64);a15_hit(11,(pc_gain(rep.0,rep.1)<pc_gain(g.0,g.1))as u64);
  a15_hit(25,rep.0.saturating_sub(g.0)as u64);a15_hit(26,(rep.1<g.1)as u64);
 }
 if dp>=2&&cl<c{
  a15_hit(12,1);let second=pc_f_try(s,c,cl,p,f.0,f.1,minl);
  a15_hit(34,(source!=c&&source!=cl)as u64);
  let exchange=if source==c||source==cl{g}else{pc_f_try(s,p,source,p,second.0,second.1,minl)};
  let eg=pc_gain(exchange.0,exchange.1);let gg=pc_gain(g.0,g.1);
  a15_hit(13,(eg>gg)as u64);a15_hit(14,(eg==gg)as u64);a15_hit(15,(eg<gg)as u64);
  a15_hit(16,exchange.0.saturating_sub(g.0)as u64);a15_hit(17,g.0.saturating_sub(exchange.0)as u64);
 }
}
fn a15_lazy(s:&[u8],out:&[u32],nt:usize,q:usize,c2:usize,l:usize,d:usize,g:(usize,usize)){
 a15_hit(18,1);let previous=a15_distance(out,nt);if previous==0||previous>q{return;}a15_hit(19,1);
 let source=q-previous;a15_hit(20,(source==c2)as u64);if source==c2{return;}
 a15_hit(28,1);
 let rep=pc_probe_lazy(s,source,pc_be8(s,source),q,l);
 if rep.0>=4{
  assert_eq!(pc_common_from(s,source,q,std::cmp::min(258,s.len()-q),0),rep.0);a15_hit(21,1);
  let beats=g.0<4||pc_gain(rep.0,rep.1)>pc_gain(g.0,g.1);a15_hit(22,beats as u64);
  if beats&&pc_gain(rep.0,rep.1)>pc_gain(l,d){a15_hit(23,1);a15_hit(24,rep.0.saturating_sub(std::cmp::max(g.0,l))as u64);}
 }
 let old=if g.0>=4&&pc_gain(g.0,g.1)>pc_gain(l,d){g}else{(l,d)};
 let new=if rep.0>=4&&pc_gain(rep.0,rep.1)>pc_gain(l,d){rep}else{(l,d)};
 let ng=pc_gain(new.0,new.1);let og=pc_gain(old.0,old.1);
 a15_hit(29,(ng>og)as u64);a15_hit(30,(ng==og)as u64);a15_hit(31,(ng<og)as u64);
 a15_hit(32,new.0.saturating_sub(old.0)as u64);a15_hit(33,old.0.saturating_sub(new.0)as u64);
}
'''

def instrument(raw):
 assert sha(raw)==RUST;s=raw.decode()
 def core(b):
  b=once(b,'    let n = input.len();','    a15_hit(0,1);\n    let n = input.len();')
  line='                let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);'
  b=once(b,line,line+'\n                a15_normal(input,out,nt,p,c,cl,&prev,f,g,dp,minl,km);')
  line='                    let g = pc_probe_lazy(input, c2, w2, q, l);'
  return once(b,line,line+'\n                    a15_lazy(input,out,nt,q,c2,l,d,g);')
 return (edit_fn(s,'pc_run1c<',core)+EXTRA).encode()

HARNESS=r'''
#![allow(dead_code)]
#[path=FROZEN]mod frozen;
#[path=OBSERVED]mod observed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn main(){let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b,"{}",p.display());assert!(decode(&s,&b));let counts=observed::a15_take();
 let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();
 print!("A15_CORPUS {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
'''

def harness(observed):
 s=HARNESS
 for key,path in [('FROZEN',BASE),('OBSERVED',observed)]:s=once(s,'#[path='+key+']','#[path='+json.dumps(str(path))+']')
 assert '#[path=FROZEN]'not in s and '#[path=OBSERVED]'not in s
 return s

def preflight(spec):
 assert spec['r26_mode']=='native'and spec['native_encoder']is False and spec['r26_a_rep_shadow']is True
 assert all(e['control']for e in spec['entries'])and spec['r26_expected_candidates']==0
 e=next(e for e in spec['entries']if e['name']=='public641');assert e['hashes']['parse.rs']==RUST==sha(BASE.read_bytes())
 native_path=ROOT/spec['r26_a_rep_baseline'];native=json.loads(native_path.read_bytes())
 assert native['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
 assert native['source_hashes']['public641']['parse.rs']==RUST
 rows=[e for e in native['rows']if e['candidate']=='public641'];assert len(rows)==28
 return {'status':'VERIFIED_A15_OBSERVER_SOURCE_HARNESS_AND_PARENT_TOKENS_NOT_NATIVE','rust_sha256':RUST,'observer_sha256':sha(instrument(BASE.read_bytes())),'harness_preflight_sha256':sha(harness(Path('observed.rs')).encode()),'baseline_sha256':sha(native_path.read_bytes())}

def run():
 assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
 from round4 import validate
 spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
 build=Path(os.environ['RUNNER_TEMP'])/'r26-a-rep-shadow-build';build.mkdir();spool=build/'spool';spool.mkdir()
 out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-rep-shadow';out.mkdir(parents=True)
 observed=build/'observed.rs';raw=instrument(BASE.read_bytes());observed.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
 h=harness(observed);driver=build/'main.rs';driver.write_text(h);(out/'harness.rs').write_text(h)
 r={'status':'STARTED_PREVIOUS_DISTANCE_SHADOW','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
  'rust_sha256':RUST,'observer_sha256':sha(raw),'harness_sha256':sha(h.encode()),'baseline_sha256':checked['baseline_sha256'],
  'scope':'Frozen641 originaltrajectory, previousemittedmatch distance only. Normal/lazy shadowoffers and oldestnormalprobe exchange; no candidate mutation, no timing, no outputprediction.'}
 report=out/'receipt.json';dump(report,r)
 try:
  binary=build/'check';UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
  corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';process=UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',240)
  native=json.loads((ROOT/spec['r26_a_rep_baseline']).read_bytes());expected={e['file']:e for e in native['rows']if e['candidate']=='public641'};rows=[]
  for line in process.stdout.splitlines():
   if not line.startswith('A15_CORPUS '):continue
   _,file,n,nt,*vs=line.split();assert len(vs)==len(FIELDS);c=dict(zip(FIELDS,map(int,vs)));e=expected[file]
   data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes()
   assert len(data)==int(n)==e['raw_bytes']and len(ts)==4*int(nt)and int(nt)==e['tokens']
   assert sha(data)==e['input_sha256']and sha(ts)==e['tokens_sha256']
   assert c['exchange_third_enabled']==c['exchange_gain_better']+c['exchange_gain_equal']+c['exchange_gain_worse']
   assert c['normal_rep_match']==c['normal_rep_gain_better']+c['normal_rep_gain_equal']+c['normal_rep_gain_worse']
   assert c['lazy_exchange_eligible']==c['lazy_exchange_gain_better']+c['lazy_exchange_gain_equal']+c['lazy_exchange_gain_worse']
   rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'counts':c})
  assert len(rows)==28 and len({e['file']for e in rows})==28
  r.update(status='VERIFIED_PREVIOUS_DISTANCE_SHADOW_IDENTITY_DECODE_BYTECHECKS_AND_COUNTS',rows=rows,totals={f:sum(e['counts'][f]for e in rows)for f in FIELDS},quality='NOT_A_REAL_CANDIDATE_OUTPUT',performance='NOT_MEASURED',full_gate='NOT_RUN')
 except Exception as exc:r.update(status='FAILED_OR_INCOMPLETE_PREVIOUS_DISTANCE_SHADOW',error_type=type(exc).__name__,error=str(exc));dump(report,r);raise
 dump(report,r);print(json.dumps({'status':r['status'],'totals':r['totals']},indent=2))

if __name__=='__main__':run()
