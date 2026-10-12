"""Original OA base-extension and whole-lazy work, alongside real C4 native output."""
from pathlib import Path
import hashlib, importlib, json, os
ROOT=Path(__file__).resolve().parents[1]
BUILD=importlib.import_module('r26-c-build-greedy-once')
C3=importlib.import_module('r26-c-deferred-counts')
HELP=importlib.import_module('r26-a-rep-shadow')
UTIL=importlib.import_module('research-round25-len3-price')
BASE=BUILD.BASE/'parse.rs'
FIELDS=['base_fast_calls','base_fast_word_pairs','eval2_calls','eval3_calls','lazy_more_calls','lazy_fast2_calls','lazy_fast2_word_pairs','lazy_fast3_calls','lazy_fast3_word_pairs']
EXTRA=r'''
use std::sync::atomic::{AtomicU64,Ordering};
static C4_COUNTS:[AtomicU64;9]=[const{AtomicU64::new(0)};9];
fn c4_hit(i:usize,n:u64){C4_COUNTS[i].fetch_add(n,Ordering::Relaxed);}
pub fn c4_take()->[u64;9]{std::array::from_fn(|i|C4_COUNTS[i].swap(0,Ordering::Relaxed))}
fn c4_count_fast(s:&[u8],a:usize,b:usize,cap:usize)->(usize,u64){
 let mut l=8usize;let mut go=1usize;let mut it=0usize;let mut pairs=0u64;
 while go==1&&it<40{if l<cap{pairs+=1;let x=o_a_ld8(s,a.wrapping_add(l))^o_a_ld8(s,b.wrapping_add(l));let k=if x==0{8}else{o_a_first_diff(x)};l=l.wrapping_add(k);go=if x==0{1}else{0};}else{go=0;}it+=1;}
 (if l>cap{cap}else{l},pairs)
}
fn c4_observe_fast(s:&[u8],a:usize,b:usize,cap:usize,site:usize)->usize{
 let original=if site==0{o_a_fast_len(s,a,b,cap)}else if site==1{o_a_fast_len2(s,a,b,cap)}else{o_a_fast_len3(s,a,b,cap)};
 let(full,pairs)=c4_count_fast(s,a,b,cap);assert_eq!(original,full);
 let i=if site==0{0}else if site==1{5}else{7};c4_hit(i,1);c4_hit(i+1,pairs);original
}
'''
def sha(b):return hashlib.sha256(b).hexdigest()
def dump(p,x):p.write_bytes((json.dumps(x,indent=2)+'\n').encode())
def instrument(raw):
    assert sha(raw)==BUILD.RUST;text=raw.decode()
    text=HELP.edit_fn(text,'o_a_eval(',lambda s:HELP.once(s,'o_a_fast_len(input, c.wrapping_sub(1), p, cap)','c4_observe_fast(input, c.wrapping_sub(1), p, cap,0)'))
    for name,index,old,site in [('o_a_eval2(',2,'o_a_fast_len2',1),('o_a_eval3(',3,'o_a_fast_len3',2)]:
        def edit(s,index=index,old=old,site=site):
            s=HELP.once(s,'    let n = input.len();',f'    c4_hit({index},1);\n    let n = input.len();')
            return HELP.once(s,old+'(input, c.wrapping_sub(1), p, cap)',f'c4_observe_fast(input, c.wrapping_sub(1), p, cap,{site})')
        text=HELP.edit_fn(text,name,edit)
    text=HELP.edit_fn(text,'o_a_lazy_more<',lambda s:HELP.once(s,'    let mut m = m0;','    c4_hit(4,1);\n    let mut m = m0;'))
    return(text+EXTRA).encode()
def harness(observed):
    text=HELP.HARNESS.replace('A15_CORPUS','C4_CORPUS').replace('observed::a15_take','observed::c4_take')
    for key,path in [('FROZEN',BASE),('OBSERVED',observed)]:text=HELP.once(text,'#[path='+key+']','#[path='+json.dumps(str(path))+']')
    return text
def preflight(spec):
    assert spec['r26_mode']=='native'and spec['native_encoder']is True and spec['r26_c_greedy_counts']is True
    assert spec['r26_native_decode']is True and not spec['r26_finite_equivalence']
    by={e['name']:e for e in spec['entries']};e=by[BUILD.NAME]
    assert by['public658']['hashes']['parse.rs']==BUILD.RUST==sha(BASE.read_bytes())
    assert e['hashes']['parse.rs']==sha(BUILD.source())==sha((ROOT/e['path']/'parse.rs').read_bytes())
    return{'status':'VERIFIED_C4_SOURCE_OBSERVER_BINDING_NOT_COMPILED','candidate_hashes':e['hashes'],'observer_sha256':sha(instrument(BASE.read_bytes())),'harness_template_sha256':sha(harness(Path('observed.rs')).encode())}
def run():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    from round4 import validate
    spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
    build=Path(os.environ['RUNNER_TEMP'])/'r26-c-greedy-build';build.mkdir();spool=build/'spool';spool.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-c-greedy';out.mkdir(parents=True)
    observed=build/'observed.rs';raw=instrument(BASE.read_bytes());observed.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
    h=harness(observed);driver=build/'main.rs';driver.write_bytes(h.encode());(out/'harness.rs').write_bytes(h.encode())
    r={'status':'STARTED_C4_ORIGINAL_STAGE_ORACLE','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'preflight':checked,'observer_sha256':sha(raw),'harness_sha256':sha(h.encode()),'scope':'Original658 untimedwork only;countsarenotnewcandidatecycles. RealC4quality separatelymeasuredwithoriginalencoder, shiftsinitsfuturetrajectory included.'};dest=out/'receipt.json';dump(dest,r)
    try:
        binary=build/'check';UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
        corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';result=UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',240)
        np=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-encoder/encoder.json';j=json.loads(np.read_bytes());assert j['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
        expected={e['file']:e for e in j['rows']if e['candidate']=='public658'};cand={e['file']:e for e in j['rows']if e['candidate']==BUILD.NAME};assert len(expected)==len(cand)==28;rows=[]
        for line in result.stdout.splitlines():
            if not line.startswith('C4_CORPUS '):continue
            _,file,n,nt,*vs=line.split();assert len(vs)==len(FIELDS);c=dict(zip(FIELDS,map(int,vs)));e=expected[file];v=cand[file]
            data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes();assert sha(data)==e['input_sha256']and sha(ts)==e['tokens_sha256']and len(ts)==4*int(nt)and len(data)==int(n)
            rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'counts':c,'candidate_same_tokens':v['tokens_sha256']==e['tokens_sha256'],'candidate_same_output':v['output_sha256']==e['output_sha256'],'candidate_byte_delta':v['output_bytes']-e['output_bytes']})
        assert len(rows)==28;r.update(status='VERIFIED_C4_ORIGINAL_STAGE_COUNTS_AND_NATIVE_OUTPUTS',encoder_receipt_sha256=sha(np.read_bytes()),rows=rows,totals={f:sum(e['counts'][f]for e in rows)for f in FIELDS},performance='NOT_MEASURED',full_gate='NOT_RUN')
    except Exception as exc:r.update(status='FAILED_OR_INCOMPLETE_C4_ORACLE',error_type=type(exc).__name__,error=str(exc));dump(dest,r);raise
    dump(dest,r);print(json.dumps({'status':r['status'],'totals':r['totals']},indent=2))
if __name__=='__main__':run()
