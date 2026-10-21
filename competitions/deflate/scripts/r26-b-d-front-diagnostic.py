"""Real public552 D-forward sampled-write/domain opportunity; original trajectory only."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import re
import subprocess

ROOT=Path(__file__).resolve().parents[1]
EXPECTED='5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
FIELDS=['relax_calls','nonempty_calls','actual_sampled_writes','actual_improving_writes',
        'same_cost_choice_improving_writes','offered_length_span','omitted_length_positions',
        'long_sampled_writes','long_omitted_positions','full_long_code_intervals',
        'partial_long_code_intervals','full_long_dense_intervals','constant_long_code_parts',
        'nonconstant_long_code_parts','full_long_code_sampled_writes','partial_long_code_sampled_writes',
        'constant_long_dense_event_groups','dense_event_floor_covered_lengths',
        'main_loop_arrival_queries','backward_arrival_reads','chunk_resets',
        'price_rebuilds','actual_non_long_writes','empty_calls']

COUNTER=r'''
use std::sync::atomic::{AtomicU64,AtomicBool,Ordering};
static R26_D_ACTIVE:AtomicBool=AtomicBool::new(false);
static R26_D_COUNTERS:[AtomicU64;24]=[const{AtomicU64::new(0)};24];
fn r26_d_hit(i:usize,n:u64){if R26_D_ACTIVE.load(Ordering::Relaxed){R26_D_COUNTERS[i].fetch_add(n,Ordering::Relaxed);}}
pub fn r26_take()->[u64;24]{std::array::from_fn(|i|R26_D_COUNTERS[i].swap(0,Ordering::Relaxed))}
fn r26_d_domain_counts(pa:&[u64;RING],lc:&[u32;512],nextl:&[u16;512],i:usize,lo:usize,hi:usize,base:u32,dpack:u32) {
 if !R26_D_ACTIVE.load(Ordering::Relaxed){return;}
 let mut local=[0u64;24];local[0]=1;
 if lo>hi{local[23]=1;}else{
  assert!(lo>=3&&hi<=258&&dpack&511==0);local[1]=1;local[5]=(hi-lo+1)as u64;
  let mut actual=[false;259];let mut l=lo;
  while l<hi {
   assert!(l<=258);actual[l]=true;
   let next=nextl[l%512]as usize;assert!(next>l);l=next;
  }actual[hi]=true;
  for length in lo..=hi {
   if actual[length]{
    local[2]+=1;if length>=67{local[7]+=1;}else{local[22]+=1;}
    let v=((base.wrapping_add(lc[length%512])as u64)<<32)|(dpack|length as u32)as u64;
    let old=pa[(i+length)%RING];if v<old{local[3]+=1;if v>>32==old>>32{local[4]+=1;}}
   }else{local[6]+=1;if length>=67{local[8]+=1;}}
  }
  let mut at=lo;
  while at<=hi {
   let mut code=0usize;while code<28&&at as u32>=LBASE[code+1]{code+=1;}
   let begin=LBASE[code]as usize;
   let end=if code<28{LBASE[code+1]as usize-1}else{258};
   let stop=end.min(hi);let span=stop-at+1;
   if end-begin+1>=16 {
    let full=at==begin&&stop==end;let mut count=0usize;let mut constant=true;
    for pos in at..=stop{if actual[pos]{count+=1;}if lc[pos%512]!=lc[at%512]{constant=false;}}
    if full{local[9]+=1;local[14]+=count as u64;if count==span{local[11]+=1;}}
    else{local[10]+=1;local[15]+=count as u64;}
    if constant{local[12]+=1;if span>=16&&count==span{local[16]+=1;local[17]+=span as u64;}}
    else{local[13]+=1;}
   }
   at=stop+1;
  }
 }
 for field in 0..24{R26_D_COUNTERS[field].fetch_add(local[field],Ordering::Relaxed);}
}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw)==EXPECTED
    text=raw.decode();fn=importlib.import_module('prepare-round24-extract-repro').fn
    wrappers=[]
    for name in ('d_parse','relax_run','open_chunk','make_costs'):
        original=fn(text,name);body=original;head=body.split('{',1)[0]
        args=re.findall(r'(?:\(|,)\s*(?:mut\s+)?([A-Za-z_][A-Za-z0-9_]*)\s*:',head)
        assert len(args)==head.count(':')and args
        inner='r26_d_inner_'+name
        body=body.replace('pub fn '+name+'(','pub fn '+inner+'(',1)
        if name=='d_parse':
            old='    while i < lim {';assert body.count(old)==1
            body=body.replace(old,old+'\n        r26_d_hit(18,1);',1)
            wrapper=head+'{R26_D_ACTIVE.store(true,Ordering::Relaxed);'+inner+'('+','.join(args)+');R26_D_ACTIVE.store(false,Ordering::Relaxed);}\n'
        elif name=='relax_run':
            wrapper=head+'{r26_d_domain_counts(pa,lc,nextl,i,lo,hi,base,dpack);'+inner+'('+','.join(args)+');}\n'
        else:
            field=20 if name=='open_chunk' else 21
            wrapper=head+'{r26_d_hit('+str(field)+',1);'+inner+'('+','.join(args)+')}\n'
        text=text.replace(original,body,1);wrappers.append(wrapper)
    for name in ('back_best','d_back_best'):
        original=fn(text,name);needle='let v = ((pa[(i - t) % RING] >> 32) as u32)'
        assert original.count(needle)==1
        changed=original.replace(needle,'r26_d_hit(19,1);\n        '+needle,1)
        text=text.replace(original,changed,1)
    return (text+'\n'+COUNTER+'\n'+'\n'.join(wrappers)).encode()


def preflight(spec):
    assert spec.get('r26_b_d_front_counts')is True and spec.get('native_encoder')is False
    entry=next(e for e in spec['entries']if e['name']=='public552')
    assert entry['hashes']['parse.rs']==EXPECTED
    observed=instrument((ROOT/entry['path']/'parse.rs').read_bytes())
    assert len(FIELDS)==24
    coarse=importlib.import_module('research-round18-functions')
    coarse.instrument((ROOT/entry['path']/'parse.rs').read_bytes(),spec['r15_profile_functions'])
    return {'status':'VERIFIED_SOURCE_AND_COUNTER_COARSE_PROFILE_STRUCTURE_ONLY','source_sha256':EXPECTED,
            'observer_sha256':sha(observed),'fields':FIELDS,
            'scope':'No localRustexecution. Counterfollows actualnextl points plus hi, doesnotpretend skippedlengths arewrites.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=importlib.import_module('round4').validate(os.environ['ROUND4_SPEC']);preflight(spec)
    entry=next(e for e in spec['entries']if e['name']=='public552');frozen=ROOT/entry['path']/'parse.rs'
    build=Path(os.environ['RUNNER_TEMP'])/'r26-b-d-front';build.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-d-front';out.mkdir(parents=True)
    observed=build/'observed.rs';observed.write_bytes(instrument(frozen.read_bytes()))
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r26_take()').replace('R13_COUNT','R26_D_FRONT')
    driver=build/'driver.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=480)
    (out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    rows=[]
    for line in r.stdout.splitlines():
        if not line.startswith('R26_D_FRONT '):continue
        _,name,n,*vals=line.split();assert len(vals)==len(FIELDS)
        data=(corpus/name).read_bytes();assert len(data)==int(n)
        rows.append({'file':name,'raw_bytes':len(data),'input_sha256':sha(data),'counts':dict(zip(FIELDS,map(int,vals)))})
    assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
    result={'status':'VERIFIED_ACTUAL_SAMPLED_WRITE_DOMAINS_OBSERVER_TOKEN_DECODE_EQUAL',
            'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
            'source_hashes':entry['hashes'],'observer_sha256':sha(observed.read_bytes()),'driver_sha256':sha(driver.read_bytes()),
            'rows':rows,'totals':{f:sum(r['counts'][f]for r in rows)for f in FIELDS},
            'scope':'Real28 frozen/originalD parse token/decode identity. Actualnextl writes, successful/fullU64choice ties and omittedlengths separately counted, plus longfull/partial/constant/dense domains and main/backward read/chunk/price rebuild burden. Counts do notinclude a productionqueue and are nottime/quality gains.',
            'limits':['Denseevent substitution onlycovers domains whose actualnextl wroteeverylength; omittedpositions cannotbecome legaloffers without intentionally changingthealgorithm.',
                      'Fullinterval but sparsesampled domain isnot savedwidth writes. Mostrows useflen8/16, so expectedopportunitymay be zero.',
                      'Eventvalues must freeze generationtime prices, preservefull(cost,choice)tie comparison, backreadstates andCHUNK/skipepoch invalidation; queue implementation notcreated.',
                      'Coarsefunction profile is separately compiled from exactoriginalsource, without heavycounter instrumentation; timesremain inclusive/instrumented, notoriginalpaired totaltime.']}
    (out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'status':result['status'],'totals':result['totals']}))
    importlib.import_module('research-round18-functions').main()


if __name__=='__main__':main()
