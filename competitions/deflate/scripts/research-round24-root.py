"""Record the old finder's eligible condition without mutating search behavior."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(x for x in spec['entries']if x['name']=='once');source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs'];text=raw.decode()
    for name in ['Z145','Z186']:
        a=text.index('pub fn '+name+'(');b=text.index('{',a)+1;text=text[:b]+'r24_record(s.len(),skip);'+text[b:]
    text+='''\nuse std::sync::atomic::{AtomicU64,Ordering};
static R24_ROOT:[AtomicU64;4]=[const{AtomicU64::new(0)};4];
fn r24_record(n:usize,skip:usize){R24_ROOT[0].fetch_add(1,Ordering::Relaxed);R24_ROOT[1].fetch_add(n as u64,Ordering::Relaxed);if skip>=258{R24_ROOT[2].fetch_add(1,Ordering::Relaxed);R24_ROOT[3].fetch_add(n as u64,Ordering::Relaxed);}}
pub fn r24_take()->[u64;4]{std::array::from_fn(|i|R24_ROOT[i].swap(0,Ordering::Relaxed))}
'''
    build=Path(os.environ['RUNNER_TEMP'])/'r24-root';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-root';out.mkdir(parents=True);obs=build/'observed.rs';obs.write_text(text)
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(obs)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_ROOT');driver=build/'main.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['finder_calls','finder_input_bytes','eligible_calls','eligible_input_bytes'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_ROOT '):
            _,name,size,*vals=line.split();assert len(vals)==4;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28;result={'status':'VERIFIED_UNTIMED_COVERAGE_OLD_TOKEN_AND_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(text.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Invocation/bytes coverage only; not uniqueinput counts, speed bound, complete proof or candidate promotion.'};(out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result['totals']))
    env=subprocess.run(['lscpu','--caches','--json'],capture_output=True,text=True,timeout=15);(out/'cache-topology.log').write_text(env.stdout+env.stderr)
if __name__=='__main__':main()
