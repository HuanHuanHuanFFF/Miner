"""Count actual A reduction ranges and constant-price aligned-block opportunities."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess
from round4 import ROOT,validate

EXTRA=r'''
use std::sync::atomic::{AtomicU64,Ordering};
static R18_A:[AtomicU64;16]=[const{AtomicU64::new(0)};16];
fn r18_a_hit(i:usize,v:u64){R18_A[i].fetch_add(v,Ordering::Relaxed);}
fn r18_a_range(p:usize,start:usize,end:usize,lc:&[u32;512]){
 if start>end{return;}let terms=end-start+1;r18_a_hit(1,1);r18_a_hit(2,terms as u64);
 let bin=if terms<4{3}else if terms<8{4}else if terms<16{5}else if terms<32{6}else if terms<64{7}else if terms<128{8}else{9};r18_a_hit(bin,1);
 let mut a=start;while a<=end{let price=lc[(a-p)&511];let mut b=a;
 while b<end&&lc[(b+1-p)&511]==price{b+=1;}
 r18_a_hit(10,1);let lo=(a+15)/16*16;let hi=(b+1)/16*16;let blocks=if hi>lo{(hi-lo)/16}else{0};
 r18_a_hit(11,blocks as u64);r18_a_hit(12,(b-a+1-blocks*16)as u64);a=b+1;}
}
pub fn r18_take()->[u64;16]{std::array::from_fn(|i|R18_A[i].swap(0,Ordering::Relaxed))}
'''

def instrument(text):
    a=text.index('pub fn a_dp_pass(');b=text.index('/// Follows the planned path',a);part=text[a:b]
    needle='    let cl = cost.len();';assert part.count(needle)==1;part=part.replace(needle,'    r18_a_hit(14,1);\n'+needle)
    needle='            let nxt = cost[i + 1];';assert part.count(needle)==1;part=part.replace(needle,'            r18_a_hit(0,1);\n'+needle)
    needle='let mut at = prev + 1;';assert part.count(needle)==2;part=part.replace(needle,'r18_a_range(i,prev+1,stop,lc);\n                    '+needle)
    needle='                    let l = stop.wrapping_sub(i) as u32;';assert part.count(needle)==1;part=part.replace(needle,'                    r18_a_hit(13,1);\n'+needle)
    return text[:a]+part+text[b:]+EXTRA

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);entry=next(e for e in spec['entries']if e['name']==spec['r18_a_range_counts']);source=ROOT/entry['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==entry['hashes']['parse.rs']
    observed_text=instrument(raw.decode())
    build=Path(os.environ['RUNNER_TEMP'])/'r18-a-ranges';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-a-ranges';out.mkdir(parents=True);observed=build/'observed.rs';observed.write_text(observed_text)
    sp=importlib.util.spec_from_file_location('harness',ROOT/'scripts/research-round13-counts.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    harness=m.HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r18_take()').replace('R13_COUNT','R18_A_RANGE');driver=build/'driver.rs';driver.write_text(harness);binary=build/'driver'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    rr=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=480);(out/'run.log').write_text(rr.stdout+rr.stderr);assert rr.returncode==0
    labels=['positions','variable_queries','variable_terms','width1_3','width4_7','width8_15','width16_31','width32_63','width64_127','width128_plus','price_segments','aligned16_blocks','partial_terms','fixed_single_terms','dp_calls','unused'];rows=[]
    for line in rr.stdout.splitlines():
        if line.startswith('R18_A_RANGE '):
            _,name,size,*vals=line.split();v=list(map(int,vals));assert len(v)==16;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(labels,v))})
    assert len(rows)==28;tot={k:sum(r[k]for r in rows)for k in labels};assert tot['variable_terms']==16*tot['aligned16_blocks']+tot['partial_terms']
    report={'status':'VERIFIED_ACTUAL_A_RANGE_COUNTS_TOKEN_AND_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_hashes':entry['hashes'],'observer_sha256':hashlib.sha256(observed_text.encode()).hexdigest(),'harness_sha256':hashlib.sha256(harness.encode()).hexdigest(),'rows':rows,'totals':tot,'scope':'Actual A reductions, not the earlier573family range diagnostic. Constant-price segments and aligned16blocks are counted from real per-pass prices. A block-min planner would add cache-build, wrap/tie and query costs; counts are not speed, equivalence, proof or promotion.'};(out/'ranges.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps({'status':report['status'],'totals':tot}))

if __name__=='__main__':main()
