"""Untimed real-row trajectory counters and fresh-preinsert oracle, separate from production timing."""
from pathlib import Path
import hashlib
import importlib
import json
import os

ROOT=Path(__file__).resolve().parents[1]
BUILD=importlib.import_module('r26-a-build-row')
UTIL=importlib.import_module('research-round25-len3-price')
NAME=BUILD.NAME
RUST='9c42e665cfdb8831e2c7f4dbe0a2de6012e59bc8ae9bd6918d540ea71704e2ac'
FIELDS=['engine_calls','ahead_calls','ahead_empty','ahead_position_reads','links',
        'normal_queries','lazy_queries','normal_validators','lazy_validators','offer_position_reads',
        'record_calls','record_dirty','end_cache_reused','end_cache_fallback','fresh_ahead_checks','oracle_offer_checks','end_cache_actual_reload']

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def edit_fn(text,name,edit):
    start=text.index('pub fn '+name);opening=text.index('{',start);end=opening+1;depth=1
    while depth:depth+=(text[end]=='{')-(text[end]=='}');end+=1
    return text[:start]+edit(text[start:end])+text[end:]

EXTRA=r'''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_AR_MODE:AtomicU64=AtomicU64::new(0);
static R26_AR_COUNTS:[AtomicU64;17]=[const{AtomicU64::new(0)};17];
fn r26_ar_hit(i:usize,n:u64){if R26_AR_MODE.load(Ordering::Relaxed)==0{R26_AR_COUNTS[i].fetch_add(n,Ordering::Relaxed);}}
fn r26_ar_oracle(s:&[u8],pos:&[u32;32768],tags:&[u64;4096],cur:&[u8;4096],p:usize,km:u32,
 budget:usize,minl:usize,threshold:usize,lazy:bool,a:(usize,u64,usize,u64,u32,u64))->(usize,usize){
 R26_AR_MODE.store(1,Ordering::Relaxed);
 assert_eq!(a,ar_ahead(s,pos,tags,cur,p,km),"stale ahead state at {}",p);
 let k=ar_key(s,p,km);let cursor=(cur[k.0]as usize)%8;
 let mut mask=ar_rotate(ar_mask(tags[k.0],k.1),cursor);let mut best=(0usize,0usize);
 let mut tried=0usize;let mut fuel=8usize;
 while mask!=0&&fuel>0&&tried<budget&&best.0<258{
  fuel-=1;let logical=7-(mask.leading_zeros()/8)as usize;
  mask&=!(128u64<<((logical*8)as u32));let old=pos[k.0*8+(cursor+logical)%8];
  if old>0{let c=old as usize-1;if c<p&&p-c<=32768{
   tried+=1;let got=if lazy{pc_probe_lazy(s,c,pc_be8(s,c),p,threshold)}
     else if best.0>=3{pc_f_try(s,p,c,p,best.0,best.1,minl)}else{pc_probe_m(s,c,pc_be8(s,c),p,km)};
   if got.0>=3&&got.0>best.0{best=got;}
  }}
 }R26_AR_MODE.store(0,Ordering::Relaxed);r26_ar_hit(14,1);best
}
pub fn r26_ar_take()->[u64;17]{assert_eq!(R26_AR_MODE.load(Ordering::Relaxed),0);std::array::from_fn(|i|R26_AR_COUNTS[i].swap(0,Ordering::Relaxed))}
'''

def instrument(raw):
    assert sha(raw)==RUST;s=raw.decode()
    def ahead(b):
        b=once(b,' let k=ar_key(s,p,km);',' r26_ar_hit(1,1);\n let k=ar_key(s,p,km);')
        b=once(b,'  let old=pos[row*8+slot];','  r26_ar_hit(3,1);\n  let old=pos[row*8+slot];')
        return once(b,' (row,k.1,cursor,mask,first,word)',' r26_ar_hit(2,(first==0)as u64);\n (row,k.1,cursor,mask,first,word)')
    s=edit_fn(s,'ar_ahead(',ahead)
    s=edit_fn(s,'ar_link(',lambda b:once(b,' let r=row%4096;',' r26_ar_hit(4,1);\n let r=row%4096;'))
    def offer(b):
        b=once(b,' let mut mask=a.3;',' r26_ar_hit(if lazy{6}else{5},1);\n let mut mask=a.3;')
        b=once(b,'   old=if slot==a.2%8','   r26_ar_hit(9,1);\n   old=if slot==a.2%8')
        return once(b,'    tried+=1;','    tried+=1;r26_ar_hit(if lazy{8}else{7},1);')
    s=edit_fn(s,'ar_offer(',offer)
    s=edit_fn(s,'ar_record(',lambda b:once(once(b,' let mut ins=ins0;',' r26_ar_hit(10,1);\n let mut ins=ins0;'),' }dirty\n}',' }r26_ar_hit(11,dirty as u64);dirty\n}'))
    def main(b):
        b=once(b,' let n=input.len();',' r26_ar_hit(0,1);\n let n=input.len();')
        b=once(b,'   fuel-=1;let old=pre;','   fuel-=1;let old=pre;\n   let expected=r26_ar_oracle(input,&pos,&tags,&cur,p,km,if dp>=2{3}else{2},minl,0,false,old);')
        f='   let f=ar_offer(input,&pos,p,km,if dp>=2{3}else{2},minl,0,false,old,victim);'
        b=once(b,f,f+'\n   assert_eq!(f,expected,"normal row offer at {}",p);r26_ar_hit(15,1);')
        b=once(b,'     let q=p+1;let old=pre;','     let q=p+1;let old=pre;\n     let expected=r26_ar_oracle(input,&pos,&tags,&cur,q,km,1,minl,l,true,old);')
        g='     let g=ar_offer(input,&pos,q,km,1,minl,l,true,old,victim);'
        b=once(b,g,g+'\n     assert_eq!(g,expected,"lazy row offer at {}",q);r26_ar_hit(15,1);')
        return once(b,'    pre=if p==e&&p<lim&&!dirty{ae}else{ar_ahead_if(input,&pos,&tags,&cur,p,lim,km,pre)};',
          '    r26_ar_hit(if p==e&&p<lim&&!dirty{12}else{13},1);r26_ar_hit(16,(p<lim&&!(p==e&&!dirty))as u64);\n    pre=if p==e&&p<lim&&!dirty{ae}else{ar_ahead_if(input,&pos,&tags,&cur,p,lim,km,pre)};')
    return (edit_fn(s,'ar_run1c<',main)+EXTRA).encode()

HARNESS=r'''
#![allow(dead_code)]
#[path=FROZEN]mod frozen;
#[path=OBSERVED]mod observed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn direct(s:&[u8],km:u32)->Vec<u32>{let mut a=vec![0;s.len()];let mut b=vec![0;s.len()];let na=frozen::ar_run1c::<32768>(s,&mut a,4,258,1000000,km,2,3);let nb=observed::ar_run1c::<32768>(s,&mut b,4,258,1000000,km,2,3);assert_eq!(na,nb);a.truncate(na);b.truncate(nb);assert_eq!(a,b);assert!(decode(s,&a));observed::r26_ar_take();a}
fn main(){let mut cases=0;for n in 0..65{let s:Vec<u8>=(0..n).map(|i|(i%7)as u8).collect();for km in [0xFFFF_FFFF,0xFFFF_FF00]{direct(&s,km);cases+=1;}}
for period in [1,2,7,17,251]{for n in [257,1024,32784]{let s:Vec<u8>=(0..n).map(|i|(i%period)as u8).collect();for km in [0xFFFF_FFFF,0xFFFF_FF00]{direct(&s,km);cases+=1;}}}
let mut x=7u32;let mut s=Vec::new();for _ in 0..66000{x=x.wrapping_mul(1664525).wrapping_add(1013904223);s.push((x>>24)as u8);}for i in 0..258{s[33040+i]=s[272+i];}for km in [0xFFFF_FFFF,0xFFFF_FF00]{direct(&s,km);cases+=1;}println!("R26_DIRECT {}",cases);
let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b,"{}",p.display());assert!(decode(&s,&b));let counts=observed::r26_ar_take();let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();print!("R26_REAL_ROW {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
'''

def build_harness(frozen,observed):
    s=HARNESS
    for key,path in [('FROZEN',frozen),('OBSERVED',observed)]:s=once(s,'#[path='+key+']','#[path='+json.dumps(str(path))+']')
    assert '#[path=FROZEN]'not in s and '#[path=OBSERVED]'not in s and s.count('#[path=')==2
    return s

def preflight(spec):
    assert spec['r26_mode']=='native'and spec['native_encoder']is True and spec['r26_a_row_counts']is True
    e=next(e for e in spec['entries']if e['name']==NAME);raw=(ROOT/e['path']/'parse.rs').read_bytes()
    assert sha(raw)==RUST==e['hashes']['parse.rs']and BUILD.source()==raw
    checked={'status':'VERIFIED_REAL_ROW_SOURCE_HARNESS_AND_MODELS_NOT_NATIVE','rust_sha256':RUST,'observer_sha256':sha(instrument(raw)),
             'harness_preflight_sha256':sha(build_harness(ROOT/e['path']/'parse.rs',Path('observed.rs')).encode()),'model':BUILD.model()}
    return checked

def run():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    from round4 import validate
    spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
    build=Path(os.environ['RUNNER_TEMP'])/'r26-a-real-row-build';build.mkdir();spool=build/'spool';spool.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-real-row';out.mkdir(parents=True)
    frozen=ROOT/'candidates'/NAME/'parse.rs';observer=build/'observed.rs';raw=instrument(frozen.read_bytes());observer.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
    harness=build_harness(frozen,observer);driver=build/'main.rs';driver.write_text(harness);(out/'harness.rs').write_text(harness)
    r={'status':'STARTED_REAL_ROW_TRAJECTORY_CHECKS','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
       'rust_sha256':RUST,'observer_sha256':sha(raw),'harness_sha256':sha(harness.encode()),
       'scope':'Real candidate trajectory; eachactualquery checks cachedaheadagainstfreshrow and victim-restored productionoffer againstpreinsertoracle. Instrumented output matches frozenproduction andoriginalencoder tokens. Untimed.'}
    report=out/'receipt.json';dump(report,r)
    try:
        binary=build/'check';UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
        corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';process=UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',240)
        native_path=out.parent/'r13-encoder/encoder.json';native=json.loads(native_path.read_bytes());expected={e['file']:e for e in native['rows']if e['candidate']==NAME};assert len(expected)==28
        rows=[];direct=None
        for line in process.stdout.splitlines():
            if line.startswith('R26_DIRECT '):direct=int(line.split()[1])
            if not line.startswith('R26_REAL_ROW '):continue
            _,file,n,nt,*vs=line.split();assert len(vs)==len(FIELDS);c=dict(zip(FIELDS,map(int,vs)))
            data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes();e=expected[file]
            assert len(data)==int(n)==e['raw_bytes']and len(ts)==4*int(nt)and int(nt)==e['tokens']
            assert sha(data)==e['input_sha256']and sha(ts)==e['tokens_sha256']
            q=c['normal_queries']+c['lazy_queries'];assert q==c['fresh_ahead_checks']==c['oracle_offer_checks']
            assert c['normal_validators']<=3*c['normal_queries']and c['lazy_validators']<=c['lazy_queries']
            assert c['record_calls']==c['end_cache_reused']+c['end_cache_fallback']
            assert c['end_cache_actual_reload']<=c['end_cache_fallback']
            rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'counts':c})
        assert len(rows)==28 and len({e['file']for e in rows})==28 and direct==162
        r.update(status='VERIFIED_REAL_ROW_IDENTITY_DECODE_FRESH_CACHE_PREINSERT_OFFERS_AND_COUNTS',direct_cases=direct,
          native_encoder_sha256=sha(native_path.read_bytes()),rows=rows,totals={f:sum(e['counts'][f]for e in rows)for f in FIELDS})
    except Exception as exc:
        r.update(status='FAILED_OR_INCOMPLETE_REAL_ROW_CHECKS',error_type=type(exc).__name__,error=str(exc));dump(report,r);raise
    dump(report,r);print(json.dumps({'status':r['status'],'totals':r['totals']},indent=2))

if __name__=='__main__':run()
