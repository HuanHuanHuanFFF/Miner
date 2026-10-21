"""Check every observed SF item price against its actual immutable table."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(x for x in spec['entries']if x['name']=='r24-609-item-price');source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs'];t=raw.decode()
    needle='let c=ct[Z353(SFdist(t)).wrapping_add(512)%1024]>>4;';assert t.count(needle)==1;t=t.replace(needle,needle+'assert!(t<33554432);let full=ct[Z353(SFdist(t)).wrapping_add(512)%1024];assert_eq!(full&15,0);assert!(full<=496);R24_ITEM[0].fetch_add(1,Ordering::Relaxed);')
    needle='let dcs=(SFitemprice(item) as u64)<<32;';assert t.count(needle)==3;t=t.replace(needle,needle+'assert_eq!(SFitemprice(item),ct[Z353(d).wrapping_add(512)%1024]);R24_ITEM[1].fetch_add(1,Ordering::Relaxed);')
    t+='''
use std::sync::atomic::{AtomicU64,Ordering};
static R24_ITEM:[AtomicU64;2]=[const{AtomicU64::new(0)};2];
pub fn r24_take()->[u64;2]{std::array::from_fn(|i|R24_ITEM[i].swap(0,Ordering::Relaxed))}
'''
    build=Path(os.environ['RUNNER_TEMP'])/'r24-item-price';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-item-price';out.mkdir(parents=True);obs=build/'observed.rs';obs.write_text(t)
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(obs)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_ITEM');driver=build/'main.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['retained_items_encoded','solver_item_uses_checked'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_ITEM '):
            _,name,size,*vals=line.split();assert len(vals)==2;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28;d={'status':'VERIFIED_FINITE_EVERY_ITEM_PRICE_EQUAL_AND_OBSERVER_TOKEN_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(t.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Actualobservedtable range, cachedpriceidentity andobserverparity; separate originalencoderreceipt comparescandidate toonce. No speed, universal equivalence orfullgate claim.'};(out/'receipt.json').write_bytes((json.dumps(d,indent=2)+'\n').encode());print(json.dumps(d['totals']))
if __name__=='__main__':main()
