"""One isolated maintenance replay from actual frozen A12 events; not production timing."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import struct

ROOT=Path(__file__).resolve().parents[1]
UTIL=importlib.import_module('research-round25-len3-price')
RUST='9c42e665cfdb8831e2c7f4dbe0a2de6012e59bc8ae9bd6918d540ea71704e2ac'
PARENT_RUST='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
SOURCE=ROOT/'candidates/r26-a-641-row8/parse.rs'
PARENT=ROOT/'references/round26-public-641/parse.rs'
EXPECTED='evidence/round26/38188567532/quality-a12-native/diagnostics/r13-encoder/encoder.json'
EXPECTED_SHA='9b47e2f70a8149a7904b6fa35f32f322166be53890337ab3a436346ef0f81277'
COUNTS='evidence/round26/38188567532/quality-a12-native/diagnostics/r26-a-real-row/receipt.json'
FLAGS=['--edition=2021','-C','opt-level=3','-C','lto=fat','-C','codegen-units=1','-C','debug-assertions=no','-C','overflow-checks=yes','-C','panic=unwind']

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def edit_fn(text,name,edit):
    start=text.index('pub fn '+name);end=text.index('{',start)+1;depth=1
    while depth:depth+=(text[end]=='{')-(text[end]=='}');end+=1
    return text[:start]+edit(text[start:end])+text[end:]

TRACE=r'''
use std::cell::RefCell;
use std::sync::atomic::{AtomicU64,Ordering};
static R26_L_H:AtomicU64=AtomicU64::new(0);
static R26_L_KM:AtomicU64=AtomicU64::new(0);
static R26_L_PHASE:AtomicU64=AtomicU64::new(0);
std::thread_local!{static R26_L_EVENTS:RefCell<Vec<u64>>=const{RefCell::new(Vec::new())};}
fn r26_l_begin(h:usize,km:u32){assert_eq!(R26_L_H.swap(h as u64,Ordering::Relaxed),0);R26_L_KM.store(km as u64,Ordering::Relaxed);}
fn r26_l_event(row:usize,tag:u64,p:usize){
 assert!(row<4096&&tag<256&&p<=u32::MAX as usize);
 let rt=(row as u64)|(tag<<12);let query=(R26_L_PHASE.load(Ordering::Relaxed)==0)as u64;
 let e=(p as u64)|(rt<<32)|(query<<52);R26_L_EVENTS.with(|v|v.borrow_mut().push(e));
}
pub fn r26_l_take()->(Vec<u64>,usize,u32){assert_eq!(R26_L_PHASE.load(Ordering::Relaxed),0);
 let ev=R26_L_EVENTS.with(|v|std::mem::take(&mut*v.borrow_mut()));let h=R26_L_H.swap(0,Ordering::Relaxed)as usize;
 let km=R26_L_KM.swap(0,Ordering::Relaxed)as u32;(ev,h,km)
}
'''

def instrument(raw):
    assert sha(raw)==RUST;s=raw.decode()
    s=edit_fn(s,'ar_link(',lambda b:once(b,' let r=row%4096;',' r26_l_event(row,tag,p);\n let r=row%4096;'))
    s=edit_fn(s,'ar_record(',lambda b:once(once(b,' let mut ins=ins0;',' assert_eq!(R26_L_PHASE.swap(1,Ordering::Relaxed),0);\n let mut ins=ins0;'),' }dirty\n}',' }R26_L_PHASE.store(0,Ordering::Relaxed);dirty\n}'))
    s=edit_fn(s,'ar_run1c<',lambda b:once(b,' let n=input.len();',' r26_l_begin(H,km);\n let n=input.len();'))
    return (s+TRACE).encode()

HARNESS=r'''
#![allow(dead_code)]
#[path=FROZEN]mod frozen;
#[path=PARENT]mod parent;
#[path=OBSERVED]mod observed;
use std::hint::black_box;
use std::time::Instant;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn mix(d:u64,v:u64)->u64{(d^v).wrapping_mul(0x100000001b3)}
fn used(v:u32,p:usize)->u64{(v as u64).wrapping_mul(0x9e3779b97f4a7c15)^(p as u64)}
fn old_digest(head:&[u32],prev:&[u32])->u64{let mut d=0xcbf29ce484222325;for&v in head{d=mix(d,v as u64);}for&v in prev{d=mix(d,v as u64);}d}
fn row_digest(pos:&[u32],tags:&[u64],cur:&[u8])->u64{let mut d=0xcbf29ce484222325;for&v in pos{d=mix(d,v as u64);}for&v in tags{d=mix(d,v);}for&v in cur{d=mix(d,v as u64);}d}
// Timing encloses only the event loop and final black_box barrier, not zeroing/digest.
// MODE0 discards every return, MODE1 consumes every return, MODE2 uses actual event flags.
#[inline(never)]
fn link_parent<const H:usize,const MODE:usize>(events:&[u64])->(u128,u64,u64){
 let mut head=[0u32;H];let mut prev=[0u32;32768];black_box((&mut head,&mut prev));
 let mut sum=0u64;let start=Instant::now();
 for &e in black_box(events){let p=(e as u32)as usize;let rt=((e>>32)&0xfffff)as usize;
  let slot=((rt&4095)<<3)|((rt>>12)>>5);
  let old=head[slot];parent::pc_f_link::<H>(&mut head,&mut prev,slot,p);
  if MODE==1||(MODE==2&&((e>>52)&1)!=0){sum=sum.wrapping_add(used(old,p));}
 }black_box((&head,&prev,sum));let ns=start.elapsed().as_nanos();(ns,old_digest(&head,&prev),sum)
}
#[inline(never)]
fn link_row<const MODE:usize>(events:&[u64])->(u128,u64,u64){
 let mut pos=[0u32;32768];let mut tags=[0u64;4096];let mut cur=[0u8;4096];black_box((&mut pos,&mut tags,&mut cur));
 let mut sum=0u64;let start=Instant::now();
 for &e in black_box(events){let p=(e as u32)as usize;let rt=(e>>32)&0xfffff;
  let old=frozen::ar_link(&mut pos,&mut tags,&mut cur,(rt&4095)as usize,rt>>12,p);
  if MODE==1||(MODE==2&&((e>>52)&1)!=0){sum=sum.wrapping_add(used(old,p));}
 }black_box((&pos,&tags,&cur,sum));let ns=start.elapsed().as_nanos();(ns,row_digest(&pos,&tags,&cur),sum)
}
fn reference<const H:usize>(s:&[u8],events:&[u64],km:u32)->(u64,u64,[u64;3],[u64;3]){
 let mut head=vec![0u32;H];let mut prev=vec![0u32;32768];let mut pos=vec![0u32;32768];let mut tags=vec![0u64;4096];let mut cur=vec![0u8;4096];
 let mut oldsum=[0u64;3];let mut rowsum=[0u64;3];
 for&e in events{assert_eq!(e>>53,0);let p=(e as u32)as usize;let rt=(e>>32)&0xfffff;let row=(rt&4095)as usize;let tag=rt>>12;
  assert_eq!(frozen::ar_key(s,p,km),(row,tag));let slot=(row<<3)|((tag as usize)>>5);
  assert_eq!(parent::pc_slot_of_m::<H>(s,p,km),slot);
  let old=head[slot];prev[p%32768]=old;head[slot]=p as u32;
  let cursor=cur[row]as usize;let idx=row*8+cursor;let victim=pos[idx];pos[idx]=(p as u32).wrapping_add(1);
  tags[row]=(tags[row]&!(255u64<<(cursor*8)))|(tag<<(cursor*8));cur[row]=((cursor+1)%8)as u8;
  oldsum[1]=oldsum[1].wrapping_add(used(old,p));rowsum[1]=rowsum[1].wrapping_add(used(victim,p));
  if ((e>>52)&1)!=0{oldsum[2]=oldsum[2].wrapping_add(used(old,p));rowsum[2]=rowsum[2].wrapping_add(used(victim,p));}
 }(old_digest(&head,&prev),row_digest(&pos,&tags,&cur),oldsum,rowsum)
}
fn bench<const H:usize>(name:&str,s:&[u8],events:&[u64],km:u32){
 let expected=reference::<H>(s,events,km);println!("R26_MODEL {} {:016x} {:016x} {:?} {:?}",name,expected.0,expected.1,expected.2,expected.3);
 for block in 0..2{for rep in 0..12{for order in 0..6{let kernel=if block==0{order}else{5-order};
  let (r,method,mode)=match kernel{
   0=>(link_parent::<H,0>(events),"parent",0),1=>(link_row::<0>(events),"row",0),
   2=>(link_parent::<H,1>(events),"parent",1),3=>(link_row::<1>(events),"row",1),
   4=>(link_parent::<H,2>(events),"parent",2),_=>(link_row::<2>(events),"row",2)};
  assert_eq!(r.1,if method=="parent"{expected.0}else{expected.1});assert_eq!(r.2,if method=="parent"{expected.2[mode]}else{expected.3[mode]});
  println!("R26_TIME {} {} {} {} {} {} {} {} {:016x} {:016x}",name,block+1,rep,order,method,mode,events.len(),r.0,r.1,r.2);
 }}}
}
fn main(){let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b);assert!(decode(&s,&b));
  let(events,h,km)=observed::r26_l_take();let name=p.file_name().unwrap().to_str().unwrap();let query=events.iter().filter(|&&e|((e>>52)&1)!=0).count();
  let tr:Vec<u8>=events.iter().flat_map(|e|e.to_le_bytes()).collect();let ts:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();let spool=std::path::Path::new(&args[2]);
  std::fs::write(spool.join(format!("{}.events",name)),tr).unwrap();std::fs::write(spool.join(format!("{}.tokens",name)),ts).unwrap();
  println!("R26_TRACE {} {} {} {} {} {} {}",name,s.len(),b.len(),h,km,events.len(),query);
  if events.is_empty(){assert_eq!(h,0);}else{match h{
   32768=>bench::<32768>(name,&s,&events,km),32769=>bench::<32769>(name,&s,&events,km),32781=>bench::<32781>(name,&s,&events,km),
   32785=>bench::<32785>(name,&s,&events,km),131100=>bench::<131100>(name,&s,&events,km),_=>panic!("unexpectedH {}",h)}}
 }
}
'''

def build_harness(frozen,parent,observed):
    s=HARNESS
    for k,p in [('FROZEN',frozen),('PARENT',parent),('OBSERVED',observed)]:s=once(s,'#[path='+k+']','#[path='+json.dumps(str(p))+']')
    assert not any('#[path='+k+']'in s for k in ['FROZEN','PARENT','OBSERVED'])and s.count('#[path=')==3
    return s

def preflight(spec):
    assert spec['r26_mode']=='native'and spec['native_encoder']is False and all(e['control']for e in spec['entries'])
    assert spec['r26_a_link_replay']is True and spec['r26_expected_candidates']==0
    assert spec['r26_a_link_expected_encoder']=={'path':EXPECTED,'sha256':EXPECTED_SHA}
    assert sha(SOURCE.read_bytes())==RUST and sha(PARENT.read_bytes())==PARENT_RUST
    assert sha((ROOT/EXPECTED).read_bytes())==EXPECTED_SHA
    previous=json.loads((ROOT/COUNTS).read_bytes());assert previous['rust_sha256']==RUST and previous['totals']['links']==3917583
    assert spec['r26_a_link_expected_counts']['path']==COUNTS and spec['r26_a_link_expected_counts']['sha256']==sha((ROOT/COUNTS).read_bytes())
    # All public engine H values use the original15-bit key: row12 + tag's top3.
    for high20 in range(1<<20):
        row=high20>>8;tag=high20&255;assert (row<<3)|(tag>>5)==high20>>5
    return {'status':'VERIFIED_FROZEN_REPLAY_SOURCE_AND_PACKED_KEY_MODEL_NOT_NATIVE','source_sha256':RUST,'parent_sha256':PARENT_RUST,
       'observer_sha256':sha(instrument(SOURCE.read_bytes())),'harness_preflight_sha256':sha(build_harness(SOURCE,PARENT,Path('observed.rs')).encode()),
       'packed_hash_cases':1<<20,'expected_encoder_sha256':EXPECTED_SHA,'expected_counts_sha256':sha((ROOT/COUNTS).read_bytes()),'compile_flags':FLAGS}

def run():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    from round4 import validate
    spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
    build=Path(os.environ['RUNNER_TEMP'])/'r26-a-link-replay-build';build.mkdir();spool=build/'spool';spool.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-link-replay';out.mkdir(parents=True)
    obs=build/'observed.rs';raw=instrument(SOURCE.read_bytes());obs.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
    harness=build_harness(SOURCE,PARENT,obs);driver=build/'main.rs';driver.write_text(harness);(out/'harness.rs').write_text(harness)
    r={'status':'STARTED_ISOLATED_MAINTENANCE_REPLAY','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
       **checked,'harness_sha256':sha(harness.encode()),'scope':'Isolatedsame-event maintenance kernels, notactualparser timing. Eventarrayreads, noqueryinterleaving, resetcache state, resultchecksum andmixedflagbranch canchange cost. No production speedupperbound orcausal attribution.'}
    r['status']='STARTED_ISOLATED_MAINTENANCE_REPLAY';report=out/'receipt.json';dump(report,r)
    try:
        UTIL.captured(['rustc','+nightly-2026-08-18','--version','--verbose'],out/'rustc-version.log',30)
        (out/'cpuinfo.txt').write_bytes(Path('/proc/cpuinfo').read_bytes())
        binary=build/'replay';compile_args=['rustc','+nightly-2026-08-18',*FLAGS,str(driver),'-o',str(binary)];r['compile_argv']=compile_args
        UTIL.captured(compile_args,out/'compile.log',240);r['binary_sha256']=sha(binary.read_bytes())
        UTIL.captured(['nm','-S','--size-sort','-C',str(binary)],out/'symbols.txt',30)
        UTIL.captured(['objdump','-Cd','--no-show-raw-insn',str(binary)],out/'assembly.txt',60)
        corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';args=[str(binary),str(corpus),str(spool)]
        r['run_argv']=args;r['affinity_before']=sorted(os.sched_getaffinity(0))
        os.sched_setaffinity(0,{r['affinity_before'][0]});r['affinity']=sorted(os.sched_getaffinity(0))
        process=UTIL.captured(args,out/'run.log',300)
        expected={e['file']:e for e in json.loads((ROOT/EXPECTED).read_bytes())['rows']if e['candidate']=='r26-a-641-row8'}
        previous={e['file']:e['counts']for e in json.loads((ROOT/COUNTS).read_bytes())['rows']};traces=[];timings=[];models=[]
        for line in process.stdout.splitlines():
            if line.startswith('R26_TRACE '):
                _,file,n,nt,h,km,count,query=line.split();n,nt,h,km,count,query=map(int,[n,nt,h,km,count,query]);e=expected[file]
                data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes();events=(spool/(file+'.events')).read_bytes()
                assert n==len(data)==e['raw_bytes']and len(ts)==nt*4 and nt==e['tokens']and len(events)==8*count
                assert sha(data)==e['input_sha256']and sha(ts)==e['tokens_sha256']
                assert count==previous[file]['links']and query==previous[file]['normal_queries']+previous[file]['lazy_queries']
                assert query==sum((v[0]>>52)&1 for v in struct.iter_unpack('<Q',events))
                traces.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'H':h,'km':km,'events':count,'query_events':query,'record_events':count-query,'trace_sha256':sha(events),'trace_bytes':len(events)})
            elif line.startswith('R26_TIME '):
                _,file,block,rep,order,method,mode,count,ns,digest,checksum=line.split()
                timings.append({'file':file,'block':int(block),'rep':int(rep),'phase':'warmup'if rep=='0'else'measured','order':int(order),'method':method,'mode':['discard_all','consume_all','actual_mixed'][int(mode)],'events':int(count),'elapsed_ns':int(ns),'result_digest':digest,'return_checksum':checksum})
            elif line.startswith('R26_MODEL '):models.append(line)
        assert len(traces)==28 and sum(x['events']for x in traces)==3917583 and len(models)==13 and len(timings)==13*2*12*6
        assert len({(x['file'],x['block'],x['rep'],x['method'],x['mode'])for x in timings})==len(timings)
        for t in timings:assert t['elapsed_ns']>0 and t['events']>0
        r.update(status='VERIFIED_REAL_TRACE_IDENTITY_AND_ISOLATED_MAINTENANCE_REPLAY',traces=traces,models=models,timings=timings,
          trace_files_archived=False,trace_storage='GeneratedonlyunderRUNNER_TEMP/spool; nofulltraceartifact orGitfile.',
          assembly_sha256=sha((out/'assembly.txt').read_bytes()),symbols_sha256=sha((out/'symbols.txt').read_bytes()))
    except Exception as exc:
        r.update(status='FAILED_OR_INCOMPLETE_MAINTENANCE_REPLAY',error_type=type(exc).__name__,error=str(exc));dump(report,r);raise
    dump(report,r);print(json.dumps({'status':r['status'],'traces':len(traces),'events':sum(t['events']for t in traces),'timings':len(timings)},indent=2))

if __name__=='__main__':run()
