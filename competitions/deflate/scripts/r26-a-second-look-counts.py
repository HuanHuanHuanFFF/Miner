"""Untimed actual A10 cached-second-position consumption counts."""
from pathlib import Path
import hashlib
import importlib
import json
import os

ROOT=Path(__file__).resolve().parents[1]
BUILD=importlib.import_module('r26-a-build-second-look')
UTIL=importlib.import_module('research-round25-len3-price')
NAME=BUILD.NAME
RUST='6ea536c7d7869f6fc7b6dbfb88e217c99530910f242f0a69ffd19200a7583cef'
FIELDS=['original_lazy_rejects','eligible_cached_second_probes','valid_second_offers','accepted_second_offers',
        'pending_literal_positions_before_fold','extra_head_prev_links','extra_ahead_calls','extra_actual_next_prefetches',
        'outer_matched_decisions','original_lazy_iterations']


def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(path,value):path.write_bytes((json.dumps(value,indent=2)+'\n').encode())
def once(text,old,new):
    assert text.count(old)==1,(old,text.count(old))
    return text.replace(old,new,1)


def instrument(raw):
    assert sha(raw)==RUST
    branch=BUILD.NEW
    changed=once(branch,'                    } else {','                    } else {\n                        r26_l2_hit(0,1);')
    changed=once(changed,'                        if q2 < lim && l <= input.len() - q2 {',
                 '                        if q2 < lim && l <= input.len() - q2 {\n                            assert_eq!(r26_l2_seen,0);r26_l2_seen=1;\n                            r26_l2_hit(1,1);')
    marker='                            let second = pc_probe_lazy(input, pre_c, pre_w, q2, l);'
    changed=once(changed,marker,marker+'\n                            r26_l2_hit(2,(second.0>=4)as u64);')
    marker='                            if second.0 >= 4 && pc_gain(second.0, second.1) > pc_gain(l, d) {'
    changed=once(changed,marker,marker+'\n                                r26_l2_hit(3,1);r26_l2_hit(4,2);')
    marker='                                pc_f_link::<H>(&mut head, &mut prev, pre_slot, q2);'
    changed=once(changed,marker,marker+'\n                                r26_l2_hit(5,1);')
    marker='                                let next = pc_ahead_if_m::<H>(input, &head, q2 + 1, lim, pre_slot, pre_c, pre_w, km);'
    changed=once(changed,marker,'                                r26_l2_hit(6,1);r26_l2_hit(7,(q2+1<lim)as u64);\n'+marker)
    text=once(raw.decode(),branch,changed)
    a=text.index('pub fn pc_run1c<const H: usize>');b=text.index('\n#[inline(always)] pub fn pc_put_match_checked',a)
    body=text[a:b]
    body=once(body,'                let mut go = 1u32;','                let mut go = 1u32;\n                let mut r26_l2_seen=0usize;\n                r26_l2_hit(8,1);')
    marker='                    let g = pc_probe_lazy(input, c2, w2, q, l);'
    body=once(body,marker,'                    r26_l2_hit(9,1);\n'+marker)
    text=text[:a]+body+text[b:]
    text+='''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_L2_COUNTS:[AtomicU64;10]=[const{AtomicU64::new(0)};10];
fn r26_l2_hit(i:usize,n:u64){R26_L2_COUNTS[i].fetch_add(n,Ordering::Relaxed);}
pub fn r26_l2_take()->[u64;10]{std::array::from_fn(|i|R26_L2_COUNTS[i].swap(0,Ordering::Relaxed))}
'''
    return text.encode()


HARNESS=r'''
#![allow(dead_code)]
#[path=FROZEN] mod frozen;
#[path=OBSERVED] mod observed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn main(){let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,frozen::parse);let b=tokens(&s,observed::parse);assert_eq!(a,b,"{}",p.display());assert!(decode(&s,&b));let counts=observed::r26_l2_take();let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();print!("R26_SECOND {} {} {}",name,s.len(),b.len());for x in counts{print!(" {}",x)}println!();}}
'''


def build_harness(frozen,observed):
    text=HARNESS
    for marker,path in [('FROZEN',frozen),('OBSERVED',observed)]:text=once(text,'#[path='+marker+']','#[path='+json.dumps(str(path))+']')
    assert '#[path=FROZEN]'not in text and '#[path=OBSERVED]'not in text and '#[path=OBSERVER]'not in text
    assert text.count('#[path=')==2
    return text


def preflight(spec):
    assert spec['r26_mode']=='native'and spec['native_encoder']is True
    entry=next(e for e in spec['entries']if e['name']==NAME);raw=(ROOT/entry['path']/'parse.rs').read_bytes()
    assert sha(raw)==RUST==entry['hashes']['parse.rs']and BUILD.generate()[0]==raw
    observed=instrument(raw);harness=build_harness(ROOT/entry['path']/'parse.rs',Path('observed.rs'))
    return {'status':'VERIFIED_ONE_CHANCE_BRANCH_TAIL_MODEL_AND_GENERATED_HARNESS_NOT_NATIVE','rust_sha256':RUST,
            'observer_sha256':sha(observed),'harness_preflight_sha256':sha(harness.encode()),'no_unexpanded_placeholders':True,'cost_model':BUILD.model()}


def run():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    from round4 import validate
    spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
    build=Path(os.environ['RUNNER_TEMP'])/'r26-a-second-look-build';build.mkdir();spool=build/'spool';spool.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-second-look';out.mkdir(parents=True)
    frozen=ROOT/'candidates'/NAME/'parse.rs';observer=build/'observed.rs';raw=instrument(frozen.read_bytes());observer.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
    harness=build_harness(frozen,observer);driver=build/'main.rs';driver.write_text(harness);(out/'harness.rs').write_text(harness)
    result={'status':'STARTED_UNTIMED_CACHED_SECOND_LOOK','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],
            'batch':os.environ['ROUND4_SPEC'],'rust_sha256':RUST,'observer_sha256':sha(raw),'harness_sha256':sha(harness.encode()),
            'scope':'Candidate trajectory only; pending two literal positions may later be absorbed by fold. Counters are logical work, not saved time.'}
    report=out/'receipt.json';dump(report,result)
    try:
        binary=build/'check'
        UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',180)
        corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
        process=UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',180)
        native_path=out.parent/'r13-encoder/encoder.json';native=json.loads(native_path.read_bytes());expected={r['file']:r for r in native['rows']if r['candidate']==NAME};assert len(expected)==28
        rows=[]
        for line in process.stdout.splitlines():
            if not line.startswith('R26_SECOND '):continue
            _,file,n,nt,*values=line.split();assert len(values)==len(FIELDS)
            counts=dict(zip(FIELDS,map(int,values)));data=(corpus/file).read_bytes();tokens=(spool/(file+'.tokens')).read_bytes();e=expected[file]
            assert len(data)==int(n)==e['raw_bytes']and len(tokens)==4*int(nt)and int(nt)==e['tokens']
            assert sha(data)==e['input_sha256']and sha(tokens)==e['tokens_sha256']
            assert counts['accepted_second_offers']<=counts['valid_second_offers']<=counts['eligible_cached_second_probes']<=counts['original_lazy_rejects']<=counts['outer_matched_decisions']
            assert counts['original_lazy_rejects']<=counts['original_lazy_iterations']
            assert counts['extra_head_prev_links']==counts['extra_ahead_calls']==counts['accepted_second_offers']
            assert counts['pending_literal_positions_before_fold']==2*counts['accepted_second_offers']
            assert counts['extra_actual_next_prefetches']<=counts['extra_ahead_calls']
            rows.append({'file':file,'raw_bytes':len(data),'input_sha256':sha(data),'tokens_sha256':sha(tokens),'counts':counts})
        assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
        result.update(status='VERIFIED_NATIVE_TOKEN_IDENTITY_DECODE_AND_ONE_SECOND_CHANCE_COUNTS',native_encoder_sha256=sha(native_path.read_bytes()),rows=rows,
                      totals={f:sum(r['counts'][f]for r in rows)for f in FIELDS})
    except Exception as exc:
        result.update(status='FAILED_OR_INCOMPLETE_SECOND_LOOK_COUNTS',error_type=type(exc).__name__,error=str(exc));dump(report,result);raise
    dump(report,result);print(json.dumps({'status':result['status'],'totals':result['totals']},indent=2))


if __name__=='__main__':run()
