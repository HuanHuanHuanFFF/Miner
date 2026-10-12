"""Frozen combo token boundary diagnostic; no candidate or timing claim."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import statistics
import sys
import zlib

ROOT = Path(__file__).resolve().parents[1]
HELP = importlib.import_module('research-round25-len3-price')
SRC = HELP.SOURCES['combo']
PC_ROWS = [0,1,3,5,6,7,8,9]
FIELDS = ['adjacent_pairs','same_block_pairs','legal_cap_pairs','byte_comparisons','movable_pairs','legal_shift_options','known_price_options','unknown_price_options','chosen_pairs','shifted_bytes','frozen_price_saved_bits','largest_shift','unknown_pair_prices']

APPEND = r'''
pub fn r26_length_prices(ts:&[u32])->Vec<Vec<u32>> {
 let mut result=Vec::new();
 for chunk in ts.chunks(BLOCK_TOKENS) {
  let mut b=Block::new();
  for &t in chunk {match token::decode(t){token::Token::Literal(x)=>b.push_literal(x),token::Token::Match{dist,len}=>b.push_match(dist,len),_=>panic!("bad token")}}
  let (ll,_,kind,_,_,_)=r25_lp_tables(&b);
  let mut prices=vec![u32::MAX;259];
  if kind!=0 {for length in 3..=258 {let (lc,extra,_)=len_code(length as u32);if lc<ll.len()&&ll[lc]>0 {prices[length]=ll[lc] as u32+extra as u32;}}}
  result.push(prices);
 }
 result
}
'''

HARNESS = r'''
#![allow(dead_code)]
#[path=TOKEN_PATH]mod token;
#[path=CODEC_PATH]mod codec;
#[path=PRICES_PATH]mod prices;
#[path=PARSER_PATH]mod parser;
#[path=OBSERVER_PATH]mod observer;
fn parse(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut o=vec![0;s.len()];let n=f(s,&mut o);assert!(n<=s.len());o.truncate(n);o}
fn decode(s:&[u8],ts:&[u32]){let mut o=Vec::new();for &t in ts{match token::decode(t){token::Token::Literal(x)=>o.push(x),token::Token::Match{dist,len}=>{assert!(dist>0&&dist as usize<=o.len()&&o.len()+len as usize<=s.len());for _ in 0..len{let x=o[o.len()-dist as usize];o.push(x);}},_=>panic!("bad token")}}assert_eq!(o,s);}
fn ml(t:u32)->Option<(usize,usize)>{match token::decode(t){token::Token::Match{dist,len}=>Some((len as usize,dist as usize)),_=>None}}
fn tk(l:usize,d:usize)->u32{assert!((3..=258).contains(&l)&&(1..=32768).contains(&d));16777216+(d as u32-1)*256+l as u32-3}
fn rewrite(s:&[u8],ts:&[u32],pr:&[Vec<u32>])->(Vec<u32>,[u64;13]){
 let mut out=ts.to_vec();let mut stat=[0u64;13];let mut p=0usize;
 for i in 0..ts.len(){
  let current=ml(ts[i]);
  if i>0 {if let (Some((l,d)),Some((w,old_d)))=(current,ml(out[i-1])) {
   stat[0]+=1;
   if i/16384==(i-1)/16384 {
    stat[1]+=1;
    let cap=(w-3).min(258-l).min(p.saturating_sub(d));
    if cap>0 {
     stat[2]+=1;let mut reach=0usize;
     while reach<cap {stat[3]+=1;if s[p-reach-1]!=s[p-reach-1-d]{break;}reach+=1;}
     if reach>0 {stat[4]+=1;}
     let price=&pr[i/16384];
     if price[w]==u32::MAX||price[l]==u32::MAX {stat[12]+=1;} else {
      let old_cost=price[w]+price[l];let mut best=old_cost;let mut shift=0usize;
      for k in 1..=reach {
       stat[5]+=1;
       if price[w-k]==u32::MAX||price[l+k]==u32::MAX {stat[7]+=1;continue;}
       stat[6]+=1;let cost=price[w-k]+price[l+k];
       if cost<best {best=cost;shift=k;}
      }
      if shift>0 {
       out[i-1]=tk(w-shift,old_d);out[i]=tk(l+shift,d);
       stat[8]+=1;stat[9]+=shift as u64;stat[10]+=(old_cost-best)as u64;stat[11]=stat[11].max(shift as u64);
      }
     }
    }
   }
  }}
  p+=current.map(|x|x.0).unwrap_or(1);
 }
 assert_eq!(p,s.len());(out,stat)
}
fn main(){
 let args:Vec<_>=std::env::args().collect();let spool=std::path::Path::new(&args[2]);
 let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for (index,path) in files.iter().enumerate(){
  let data=std::fs::read(path).unwrap();let name=path.file_name().unwrap().to_str().unwrap();
  let original=parse(&data,parser::parse);let observed=parse(&data,observer::parse);assert_eq!(original,observed);decode(&data,&original);
  let hits=observer::r25_lp_take();assert!(hits.iter().sum::<u64>()<=1);let row=hits.iter().position(|&v|v>0).unwrap_or(32);
  let original_encoded=codec::encode(&original,data.len()).unwrap();assert_eq!(original_encoded,prices::encode(&original,data.len()).unwrap());
  let active=[0usize,1,3,5,6,7,8,9].contains(&row);
  let (changed,stat)=if active{rewrite(&data,&original,&prices::r26_length_prices(&original))}else{(original.clone(),[0;13])};
  assert_eq!(original.len(),changed.len());decode(&data,&changed);
  let encoded=codec::encode(&changed,data.len()).unwrap();
  for (label,ts,bytes) in [("original",&original,&original_encoded),("boundary",&changed,&encoded)] {
   let mut raw=Vec::new();for&t in ts {raw.extend(t.to_le_bytes());}
   std::fs::write(spool.join(format!("{}-{}.tokens",index,label)),raw).unwrap();std::fs::write(spool.join(format!("{}-{}.deflate",index,label)),bytes).unwrap();
   println!("R26_BOUNDARY_ROW {} {} {} {} {} {}",index,name,label,ts.len(),bytes.len(),row);
  }
  print!("R26_BOUNDARY_COUNT {} {}",index,name);for v in stat {print!(" {}",v);}println!();
 }
}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())


def preflight(spec=None):
    raw=(ROOT/SRC['path']/'parse.rs').read_bytes()
    assert sha(raw)==SRC['hashes']['parse.rs']
    observed,bodies=HELP.instrument(raw,SRC)
    for row in PC_ROWS:
        assert bodies['p125_row'+str(row)].startswith('pc_run1')
    expected=HELP.expected_rows('combo',SRC)
    if spec is not None:
        assert spec.get('r26_a_boundary') and not spec.get('native_encoder')
        assert not spec.get('gate_candidates') and not spec.get('extract_candidates')
    # Meaningful lightweight counterexample: different match distances allow a
    # legal suffix transfer; the entire previous match need not match at new d.
    def decoded(ts):
        out=bytearray()
        for length,distance in ts:
            if distance==0:out.append(length)
            else:
                for _ in range(length):out.append(out[-distance])
        return bytes(out)
    seed=[(x,0)for x in b'ABCDXYZABCDABCDXYZABCD']
    valid=invalid=0
    for w in range(3,13):
        for l in range(3,13):
            for d1 in range(1,9):
                for d2 in range(1,9):
                    tokens=seed+[(w,d1),(l,d2)];data=decoded(tokens);p=len(seed)+w
                    for k in range(1,min(w-3,258-l,p-d2)+1):
                        guard=all(data[p-j-1]==data[p-j-1-d2]for j in range(k))
                        altered=decoded(seed+[(w-k,d1),(l+k,d2)])
                        assert (altered==data)==guard
                        valid+=guard;invalid+=not guard
    assert valid>0 and invalid>0
    # Original dynamic LL vectors can be truncated below length258. Absent
    # entries and explicit zero lengths must both stay unknown, never indexed.
    for size in [257,258,266,286]:
        table=[0]*size
        table[256]=1
        for lc in range(257,286):
            value=table[lc] if lc<len(table) else 0
            assert value==0
    return {'status':'VERIFIED_SOURCE_ROUTE_AND_LIGHTWEIGHT_SUFFIX_INVARIANT_PREFLIGHT_NOT_NATIVE',
            'source':SRC,'active_pc_rows':PC_ROWS,'observer_sha256':sha(observed),'expected_files':len(expected),
            'script_sha256':sha(Path(__file__).read_bytes()),'finite_shift_model':{'accepted':valid,'rejected':invalid},
            'missing_price_handling':'Truncated or zero-code LL prices stay MAX; unknown pair counts and skips; unknown proposed shifts count and skip.',
            'native':'NOT_RUN','time':'NOT_RUN','proof':'NOT_RUN'}


def run():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    from round4 import validate
    spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec)
    upstream=Path(os.environ['DEFLATE_ROOT']);codec=upstream/'validator/measure/src/deflate.rs';token=codec.with_name('token.rs')
    codec_raw=codec.read_bytes();assert sha(codec_raw)==HELP.CODEC_SHA and sha(token.read_bytes())==HELP.TOKEN_SHA
    build=Path(os.environ['RUNNER_TEMP'])/'r26-a-boundary-build';build.mkdir();spool=build/'spool';spool.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-boundary';out.mkdir(parents=True)
    prices=build/'prices.rs';appended=HELP.price_append(codec_raw)+APPEND.encode();prices.write_bytes(codec_raw+appended)
    (out/'price-append.rs').write_bytes(appended)
    original=ROOT/SRC['path']/'parse.rs';observer=build/'observer.rs';observer_raw,_=HELP.instrument(original.read_bytes(),SRC);observer.write_bytes(observer_raw)
    (out/'parser-observer.rs').write_bytes(observer_raw)
    replacements={'TOKEN_PATH':token,'CODEC_PATH':codec,'PRICES_PATH':prices,'PARSER_PATH':original,'OBSERVER_PATH':observer}
    harness=HARNESS
    for marker,path in replacements.items():harness=harness.replace(marker,json.dumps(str(path)))
    driver=build/'main.rs';driver.write_text(harness);(out/'harness.rs').write_text(harness)
    result={'status':'STARTED_UNTIMED_BOUNDARY_REPLAY','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],
            'batch':os.environ['ROUND4_SPEC'],'source':SRC,'codec_sha256':HELP.CODEC_SHA,'token_sha256':HELP.TOKEN_SHA,
            'observer_sha256':sha(observer_raw),'harness_sha256':sha(harness.encode()),'append_sha256':sha(appended),
            'scope':'Frozen exact combo tokens and original encoder; no candidate, native timing, future fold equality or original full gate claim.'}
    report=out/'receipt.json';dump(report,result)
    try:
        binary=build/'check'
        HELP.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
        corpus=upstream/'data/benchmark/corpus-stage1'
        run=HELP.captured([str(binary),str(corpus),str(spool)],out/'run.log',240)
        expected=HELP.expected_rows('combo',SRC);rows=[];counts={}
        for line in run.stdout.splitlines():
            if line.startswith('R26_BOUNDARY_ROW '):
                _,index,file,label,nt,nb,route=line.split();data=(corpus/file).read_bytes();encoded=(spool/(index+'-'+label+'.deflate')).read_bytes();tokens=(spool/(index+'-'+label+'.tokens')).read_bytes()
                assert len(encoded)==int(nb) and len(tokens)==4*int(nt) and zlib.decompress(encoded,-15)==data
                row={'file':file,'label':label,'raw_bytes':len(data),'input_sha256':sha(data),'tokens':int(nt),'output_bytes':int(nb),
                     'tokens_sha256':sha(tokens),'output_sha256':sha(encoded),'route_row':int(route),'active_pc':int(route)in PC_ROWS}
                assert row['input_sha256']==expected[file]['input_sha256']
                if label=='original':
                    for k in ['raw_bytes','input_sha256','tokens','output_bytes','tokens_sha256','output_sha256']:assert row[k]==expected[file][k],(file,k)
                rows.append(row)
            elif line.startswith('R26_BOUNDARY_COUNT '):
                _,index,file,*vals=line.split();assert len(vals)==len(FIELDS);counts[file]=dict(zip(FIELDS,map(int,vals)))
        assert len(rows)==56 and len(counts)==28
        pairs=[]
        for file in expected:
            a=next(r for r in rows if r['file']==file and r['label']=='original');b=next(r for r in rows if r['file']==file and r['label']=='boundary')
            assert a['tokens']==b['tokens']
            if not a['active_pc']:assert a['tokens_sha256']==b['tokens_sha256'] and a['output_sha256']==b['output_sha256']
            pairs.append({'file':file,'route_row':a['route_row'],'active_pc':a['active_pc'],'extra_output_bytes':b['output_bytes']-a['output_bytes'],
                          'quality_delta_pp':100*(b['output_bytes']-a['output_bytes'])/a['raw_bytes'],'counts':counts[file]})
        assert codec.read_bytes()==codec_raw
        result.update(status='VERIFIED_UNTIMED_BOUNDARY_REPLAY_ORIGINAL_IDENTITIES_AND_DUAL_DECODE',rows=rows,pairs=pairs,
                      total_extra_output_bytes=sum(r['extra_output_bytes']for r in pairs),quality_delta_pp=statistics.mean(r['quality_delta_pp']for r in pairs),
                      totals={f:(max(r['counts'][f]for r in pairs)if f=='largest_shift' else sum(r['counts'][f]for r in pairs))for f in FIELDS})
    except Exception as exc:
        result.update(status='FAILED_OR_INCOMPLETE_BOUNDARY_REPLAY',error_type=type(exc).__name__,error=str(exc));dump(report,result);raise
    dump(report,result)
    print(json.dumps({k:result[k]for k in ['status','total_extra_output_bytes','quality_delta_pp','totals']},indent=2))


if __name__=='__main__':
    if sys.argv[1:]==['--self-check']:
        result=preflight();dest=ROOT/'evidence/round26/route-a/boundary-preflight.json';dump(dest,result);print(json.dumps(result,indent=2))
    else:run()
