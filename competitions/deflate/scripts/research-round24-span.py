"""Record actual per-item excluded domains, preserving the candidate output."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux';spec=validate(os.environ['ROUND4_SPEC']);e=next(x for x in spec['entries']if x['name']=='r24-609-span-items');source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs'];t=raw.decode()
    needle='let low=Z457(3,(item>>23)as usize);let l=SFlen(t);';assert t.count(needle)==3;t=t.replace(needle,needle+'r24_span(l,low,&bend);')
    t+='''
use std::sync::atomic::{AtomicU64,Ordering};
static R24_SPAN:[AtomicU64;7]=[const{AtomicU64::new(0)};7];
fn r24_groups(bend:&[u32;512],mut x:usize,hi:usize)->u64{let mut count=0;while count<32&&x<=hi&&x<259{let e=Z248(Z457(bend[x%512]as usize,x),hi);x=e.wrapping_add(1);count+=1;}count}
fn r24_span(l:usize,lo:usize,bend:&[u32;512]){assert!(3<=lo&&lo<=l&&l<=258);let v=[1,(lo>3)as u64,(l-2)as u64,(l-lo+1)as u64,(Z248(l,10)-2)as u64,Z248(l,10).saturating_add(1).saturating_sub(lo)as u64,r24_groups(bend,11,l).saturating_sub(r24_groups(bend,Z457(11,lo),l))];for(i,n)in v.iter().enumerate(){R24_SPAN[i].fetch_add(*n,Ordering::Relaxed);}}
pub fn r24_take()->[u64;7]{std::array::from_fn(|i|R24_SPAN[i].swap(0,Ordering::Relaxed))}
'''
    build=Path(os.environ['RUNNER_TEMP'])/'r24-span';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-span';out.mkdir(parents=True);obs=build/'observed.rs';obs.write_text(t)
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(obs)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_SPAN');driver=build/'main.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['item_uses','pruned_item_uses','old_length_offers','new_length_offers','old_short_terms','new_short_terms','saved_long_groups'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_SPAN '):
            _,name,size,*vals=line.split();assert len(vals)==7;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28;d={'status':'VERIFIED_ACTUAL_SPAN_BOUNDS_COUNTS_OBSERVER_TOKEN_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(t.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Actualcandidateencodedbounds andquerydomain counts; olddomain counts oncandidateDPpath. Separate originalencoderreceipt mustestablish parentparity. No speed orall-inputproof.'};(out/'receipt.json').write_bytes((json.dumps(d,indent=2)+'\n').encode());print(json.dumps(d['totals']))
if __name__=='__main__':main()
