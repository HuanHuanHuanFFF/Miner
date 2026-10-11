"""Count original probes beyond full-buffer code range, without changing old search."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(e for e in spec['entries']if e['name']=='once');source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    text=raw.decode();a=text.index('pub fn SFmorematches(');b=text.index('pub fn SFheavy(',a);part=text[a:b];needle='if j>=p||d>32768{break;}let cap=';assert part.count(needle)==1
    part=part.replace(needle,'if j>=p||d>32768{break;}r24_tick(count,&codes,d);let cap=');text=text[:a]+part+text[b:]
    text+=importlib.import_module('build-round24-capstop').HELPER+'''\nuse std::sync::atomic::{AtomicU64,Ordering};
static R24_CAP:[AtomicU64;3]=[const{AtomicU64::new(0)};3];
fn r24_tick(count:usize,codes:&[usize;4],d:usize){R24_CAP[0].fetch_add(1,Ordering::Relaxed);if count==4{R24_CAP[1].fetch_add(1,Ordering::Relaxed);if Z353(d)>SFmaxcode(codes){R24_CAP[2].fetch_add(1,Ordering::Relaxed);}}}
pub fn r24_take()->[u64;3]{std::array::from_fn(|i|R24_CAP[i].swap(0,Ordering::Relaxed))}
'''
    build=Path(os.environ['RUNNER_TEMP'])/'r24-cap';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-cap';out.mkdir(parents=True);obs=build/'observed.rs';obs.write_text(text)
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(obs)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_CAP');driver=build/'main.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['valid_chain_probes','full_buffer_probes','over_max_code_probes'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_CAP '):
            _,name,size,*vals=line.split();assert len(vals)==3;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28
    record={'status':'VERIFIED_UNTIMED_OLD_PATH_COUNTS_TOKEN_AND_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(text.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Counts are not speedup; old path remains unchanged in observer, new candidate measured separately.'}
    (out/'receipt.json').write_bytes((json.dumps(record,indent=2)+'\n').encode());print(json.dumps(record['totals']))
if __name__=='__main__':main()
