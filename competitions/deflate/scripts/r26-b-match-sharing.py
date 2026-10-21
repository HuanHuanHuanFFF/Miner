"""Runner-only real base-record/SF-consumer coverage on exact public628."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import re
import subprocess

ROOT=Path(__file__).resolve().parents[1]
EXPECTED='784e02703c98a32f85753cae4f3b62aea3f505d91088869f327e0ad646629c14'
FIELDS=['input_bytes','base_generator_calls','eligible_full_base_generators','retained_cache_offsets',
        'retained_cache_items','cache_copy_logical_bytes','additional_base_generators',
        'sf_collector_calls','sf_position_visits','sf_base_record_visits','sf_items','sf_seed_covered_items',
        'sf_extra_items','sf_extra_exact_source_covered','sf_extra_same_code_covered',
        'sf_extra_uncached_items','sf_extra_shorter_cached_items','sf_max_interval_bytes',
        'observer_cache_copy_ns','observer_consumer_compare_ns']

STATE=r'''
struct R26BaseCache { offsets:Vec<u32>, items:Vec<u32>, format:usize, n:usize }
struct R26State { in_base:bool, enabled:bool, cache:Option<R26BaseCache>, counts:[u64;20] }
static R26_STATE:std::sync::Mutex<R26State>=std::sync::Mutex::new(R26State{in_base:false,enabled:false,cache:None,counts:[0;20]});
fn r26_reset(input:&[u8]) {
 let mut state=R26_STATE.lock().unwrap();
 state.in_base=false;state.enabled=SFenabled(input);state.cache=None;state.counts=[0;20];state.counts[0]=input.len()as u64;
}
fn r26_phase(base:bool) {R26_STATE.lock().unwrap().in_base=base;}
fn r26_capture(n:usize,offsets:&[u32],items:&[u32],format:usize) {
 let time=std::time::Instant::now();let mut state=R26_STATE.lock().unwrap();
 if !state.in_base{return;}state.counts[1]+=1;
 if !state.enabled||offsets.len()!=n+1{return;}
 assert!((offsets[n]as usize)<=items.len());
 state.counts[2]+=1;
 if state.cache.is_some(){state.counts[6]+=1;return;}
 let copy=R26BaseCache{offsets:offsets.to_vec(),items:items.to_vec(),format,n};
 state.counts[3]=offsets.len()as u64;state.counts[4]=items.len()as u64;state.counts[5]=4*(offsets.len()+items.len())as u64;
 state.cache=Some(copy);state.counts[18]+=time.elapsed().as_nanos()as u64;
}
fn r26_base_offer(x:u32,format:usize,remaining:usize)->(usize,usize) {
 let l=if format==0{3+((x>>15)&255)as usize}else{let v=(x>>20)as usize;if v>=512{v-512}else{v}};
 (l.min(258).min(remaining),((x&32767)+1)as usize)
}
fn r26_compare_sf(input:&[u8],orig:&[u32],a:usize,e:usize,items:&[u32],starts:&[u32]) {
 let time=std::time::Instant::now();let mut state=R26_STATE.lock().unwrap();
 let R26State{cache,counts,..}=&mut *state;
 counts[7]+=1;counts[17]=counts[17].max(e.saturating_sub(a)as u64);
 assert!(a<=e&&e<=input.len()&&starts.len()==e-a+1);
 for p in a..e {
  counts[8]+=1;let first=starts[p-a]as usize;let end=starts[p-a+1]as usize;
  assert!(first<=end&&end<=items.len());
  let base=cache.as_ref().filter(|v|v.n==input.len());
  let (lo,hi)=if let Some(v)=base{let lo=v.offsets[p]as usize;let hi=v.offsets[p+1]as usize;assert!(lo<=hi&&hi<=v.items.len());(lo,hi)}else{(0,0)};
  counts[9]+=(hi-lo)as u64;
  let original=Z168(orig,p-a);
  for t in &items[first..end] {
   counts[10]+=1;let l=SFlen(*t).min(e-p);let d=SFdist(*t);
   if original!=0&&SFdist(original)==d&&SFlen(original).min(e-p)>=l{counts[11]+=1;continue;}
   counts[12]+=1;
   if let Some(v)=base {
    let mut exact=false;let mut code=false;let mut shorter=false;
    for raw in &v.items[lo..hi] {
     let (bl,bd)=r26_base_offer(*raw,v.format,input.len()-p);
     if bd==d{if bl>=l{exact=true;}else{shorter=true;}}
     if Z353(bd)==Z353(d)&&bl>=l{code=true;}
    }
    if exact{counts[13]+=1;}if code{counts[14]+=1;}if shorter&&!exact{counts[16]+=1;}
   }else{counts[15]+=1;}
  }
 }
 counts[19]+=time.elapsed().as_nanos()as u64;
}
pub fn r26_take()->[u64;20]{R26_STATE.lock().unwrap().counts}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw)==EXPECTED
    text=raw.decode()
    fn=importlib.import_module('prepare-round24-extract-repro').fn
    wrappers=[]
    names=['parse','SFbase','Z145','Z186','Z368','SFsmallmatches','SFmorematches']
    for name in names:
        body=fn(text,name);head=body.split('{',1)[0]
        args=re.findall(r'(?:\(|,)\s*(?:mut\s+)?([A-Za-z_][A-Za-z0-9_]*)\s*:',head)
        assert args and len(args)==head.count(':'),(name,args,head)
        inner='r26_inner_'+name
        renamed=body.replace('pub fn '+name+'(','pub fn '+inner+'(',1)
        assert text.count(body)==1
        text=text.replace(body,renamed,1)
        call=inner+'('+','.join(args)+')'
        if name=='parse':
            wrapper=head+'{r26_reset(input);'+call+'}\n'
        elif name=='SFbase':
            wrapper=head+'{r26_phase(true);let result='+call+';r26_phase(false);result}\n'
        elif name in ('Z145','Z186'):
            wrapper=head+'{'+call+';r26_capture(s.len(),mp,mb,0);}\n'
        elif name=='Z368':
            wrapper=head+'{'+call+';r26_capture(input.len(),mstart,mc,1);}\n'
        else:
            wrapper=head+'{'+call+';r26_compare_sf(input,orig,a,e,items,starts);}\n'
        wrappers.append(wrapper)
    # Every existing parser function body is retained exactly after renaming.
    assert all(fn(text,'r26_inner_'+n).replace('pub fn r26_inner_'+n+'(','pub fn '+n+'(',1)==fn(raw.decode(),n) for n in names)
    return (text+'\n'+STATE+'\n'+'\n'.join(wrappers)).encode()


def preflight(spec):
    assert spec.get('r26_b_match_sharing') is True
    entry=next(e for e in spec['entries']if e['name']=='public628')
    assert entry['hashes']['parse.rs']==EXPECTED
    source=ROOT/entry['path']/'parse.rs';raw=source.read_bytes();observed=instrument(raw)
    return {'status':'VERIFIED_STRUCTURE_AND_FROZEN_SOURCE_ONLY','source_sha256':sha(raw),
            'observer_sha256':sha(observed),'field_count':len(FIELDS),
            'scope':'No localRust/Lean/native execution. Mutex/cache exists only in observation copy.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=importlib.import_module('round4').validate(os.environ['ROUND4_SPEC'])
    preflight(spec)
    entry=next(e for e in spec['entries']if e['name']=='public628')
    frozen=ROOT/entry['path']/'parse.rs';raw=frozen.read_bytes()
    build=Path(os.environ['RUNNER_TEMP'])/'r26-b-sharing';build.mkdir(exist_ok=False)
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-sharing';out.mkdir(parents=True,exist_ok=False)
    observed=build/'observed.rs';observed.write_bytes(instrument(raw))
    harness=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r26_take()').replace('R13_COUNT','R26_SHARE')
    driver=build/'driver.rs';driver.write_text(harness);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=480)
    (out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    rows=[]
    for line in r.stdout.splitlines():
        if not line.startswith('R26_SHARE '):continue
        _,name,n,*vals=line.split();assert len(vals)==len(FIELDS)
        data=(corpus/name).read_bytes();assert len(data)==int(n)
        rows.append({'file':name,'raw_bytes':len(data),'input_sha256':sha(data),
                     'counts':dict(zip(FIELDS,map(int,vals)))})
    assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
    result={'status':'VERIFIED_REAL_BASE_AND_SF_COVERAGE_OBSERVER_TOKEN_DECODE_EQUAL',
            'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
            'candidate':'public628','source_hashes':entry['hashes'],
            'observer_sha256':sha(observed.read_bytes()),'driver_sha256':sha(driver.read_bytes()),
            'fields':FIELDS,'rows':rows,'totals':{f:sum(r['counts'][f]for r in rows)for f in FIELDS},
            'scope':'Observation-only copies of first eligible full-position base generator records, compared to retained original SF offers after subtracting seed-covered offers. Real28 frozen/observed tokens and independentdecode agree. Cache copy and consumer comparisons include their logical data/observer costs; counts are not candidate speed or encoded gains. Multiple eligible generators are recorded, first-generator choice explicit. No global state is added to a submitted candidate.',
            'limitations':['Exact-source coverage means a cached verified prefix can supply the retained offer, not that every rawSF probe can be skipped.',
                           'Same-distance-code coverage supports a price-envelope hypothesis; different distances/ties can change tokens and encoder quality.',
                           'This diagnostic copies records for measurement. A production candidate must include real ownership transfer/storage and consumption cost and invalidate perparse/input, without mutable global state.',
                           'No new candidate, official timing, extraction, Lean gate, privateadmission or reward evidence.']}
    (out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'status':result['status'],'totals':result['totals']}))


if __name__=='__main__':main()
