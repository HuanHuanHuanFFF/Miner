"""Original O_A discovery work removed by C3; no timing instrumentation."""
from pathlib import Path
import hashlib, importlib, json, os
ROOT=Path(__file__).resolve().parents[1]
BUILD=importlib.import_module('r26-c-build-deferred-extension')
HELP=importlib.import_module('r26-a-rep-shadow')
UTIL=importlib.import_module('research-round25-len3-price')
BASE=BUILD.BASE/'parse.rs'
FIELDS=['base_fast_calls','base_full_word_pairs','base_capped_word_pairs','removed_word_pairs','long64_calls','long64_original_span','long64_removed_suffix_bytes','changed_shadow_lengths']
EXTRA=r'''
use std::sync::atomic::{AtomicU64,Ordering};
static C3_COUNTS:[AtomicU64;8]=[const{AtomicU64::new(0)};8];
pub fn c3_take()->[u64;8]{std::array::from_fn(|i|C3_COUNTS[i].swap(0,Ordering::Relaxed))}
fn c3_count_fast(s:&[u8],a:usize,b:usize,cap:usize)->(usize,u64){
 let mut l=8usize;let mut go=1usize;let mut it=0usize;let mut pairs=0u64;
 while go==1&&it<40{if l<cap{pairs+=1;let x=o_a_ld8(s,a.wrapping_add(l))^o_a_ld8(s,b.wrapping_add(l));let k=if x==0{8}else{o_a_first_diff(x)};l=l.wrapping_add(k);go=if x==0{1}else{0};}else{go=0;}it+=1;}
 (if l>cap{cap}else{l},pairs)
}
fn c3_observe_fast(s:&[u8],a:usize,b:usize,cap:usize)->usize{
 let original=o_a_fast_len(s,a,b,cap);let(full,oldpairs)=c3_count_fast(s,a,b,cap);
 let(short,newpairs)=c3_count_fast(s,a,b,cap.min(64));assert_eq!(original,full);assert_eq!(short,full.min(64));assert!(newpairs<=oldpairs);
 let c=[1,oldpairs,newpairs,oldpairs-newpairs,(full>=64)as u64,if full>=64{full as u64}else{0},full.saturating_sub(64)as u64,(short!=full)as u64];
 for i in 0..8{C3_COUNTS[i].fetch_add(c[i],Ordering::Relaxed);}original
}
'''
def sha(b):return hashlib.sha256(b).hexdigest()
def dump(p,x):p.write_bytes((json.dumps(x,indent=2)+'\n').encode())
def instrument(raw):
    assert sha(raw)==BUILD.RUST
    text=HELP.edit_fn(raw.decode(),'o_a_eval(',lambda s:HELP.once(s,'o_a_fast_len(input, c.wrapping_sub(1), p, cap)','c3_observe_fast(input, c.wrapping_sub(1), p, cap)'))
    return(text+EXTRA).encode()
def harness(observed):
    text=HELP.HARNESS.replace('A15_CORPUS','C3_CORPUS').replace('observed::a15_take','observed::c3_take')
    for key,path in [('FROZEN',BASE),('OBSERVED',observed)]:text=HELP.once(text,'#[path='+key+']','#[path='+json.dumps(str(path))+']')
    return text
def preflight(spec):
    assert spec['r26_mode']=='native' and spec['native_encoder'] is True and spec['r26_c_deferred_counts'] is True
    assert spec['r26_native_decode'] is True and not spec['r26_finite_equivalence']
    by={e['name']:e for e in spec['entries']};e=by[BUILD.NAME]
    assert by['public658']['hashes']['parse.rs']==BUILD.RUST==sha(BASE.read_bytes())
    assert e['hashes']['parse.rs']==sha(BUILD.source())==sha((ROOT/e['path']/'parse.rs').read_bytes())
    return{'status':'VERIFIED_C3_SOURCE_OBSERVER_BINDING_NOT_COMPILED','candidate_hashes':e['hashes'],'observer_sha256':sha(instrument(BASE.read_bytes())),'harness_template_sha256':sha(harness(Path('observed.rs')).encode())}
def run():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    from round4 import validate
    spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
    build=Path(os.environ['RUNNER_TEMP'])/'r26-c-deferred-build';build.mkdir();spool=build/'spool';spool.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-c-deferred';out.mkdir(parents=True)
    observed=build/'observed.rs';raw=instrument(BASE.read_bytes());observed.write_bytes(raw);(out/'observer.rs').write_bytes(raw)
    h=harness(observed);driver=build/'main.rs';driver.write_bytes(h.encode());(out/'harness.rs').write_bytes(h.encode())
    r={'status':'STARTED_C3_ORIGINAL_DISCOVERY_ORACLE','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'preflight':checked,'observer_sha256':sha(raw),'harness_sha256':sha(h.encode()),'scope':'Untimed original658 O_A base discovery, not cycles or new timing. Source-level exact original-vs-capped read counts. Candidate bytes separately from originalencoder.'}
    dest=out/'receipt.json';dump(dest,r)
    try:
        binary=build/'check';UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
        corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';result=UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',240)
        np=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-encoder/encoder.json';j=json.loads(np.read_bytes());assert j['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
        expected={e['file']:e for e in j['rows']if e['candidate']=='public658'};cand={e['file']:e for e in j['rows']if e['candidate']==BUILD.NAME};assert len(expected)==len(cand)==28;rows=[]
        for line in result.stdout.splitlines():
            if not line.startswith('C3_CORPUS '):continue
            _,file,n,nt,*vs=line.split();assert len(vs)==len(FIELDS);c=dict(zip(FIELDS,map(int,vs)));e=expected[file];v=cand[file]
            data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes()
            assert sha(data)==e['input_sha256'] and sha(ts)==e['tokens_sha256'] and len(ts)==4*int(nt) and len(data)==int(n)
            assert c['base_full_word_pairs']-c['base_capped_word_pairs']==c['removed_word_pairs']
            rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'counts':c,'candidate_same_tokens':v['tokens_sha256']==e['tokens_sha256'],'candidate_same_output':v['output_sha256']==e['output_sha256'],'candidate_byte_delta':v['output_bytes']-e['output_bytes']})
        assert len(rows)==28
        r.update(status='VERIFIED_C3_ORIGINAL_TRAJECTORY_AND_NATIVE_OUTPUTS',encoder_receipt_sha256=sha(np.read_bytes()),rows=rows,totals={f:sum(e['counts'][f]for e in rows)for f in FIELDS},performance='NOT_MEASURED',full_gate='NOT_RUN')
    except Exception as exc:r.update(status='FAILED_OR_INCOMPLETE_C3_ORACLE',error_type=type(exc).__name__,error=str(exc));dump(dest,r);raise
    dump(dest,r);print(json.dumps({'status':r['status'],'totals':r['totals']},indent=2))
if __name__=='__main__':run()
