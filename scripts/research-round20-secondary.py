"""Untimed secondary-match opportunity by primary length, exact-output checked."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess
from round4 import ROOT,validate

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(e for e in spec['entries']if e['name']=='csv18');src=ROOT/e['path']/'parse.rs';raw=src.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    text=raw.decode();a=text.index('pub fn pc_f_try(');b=text.index('#[inline(always)]',a);part=text[a:b]
    before='    let n = s.len();';assert part.count(before)==1
    part=part.replace(before,'    let group=if l<=4{0}else if l<=8{1}else if l<=16{2}else if l<=32{3}else if l<=64{4}else if l<=128{5}else{6};\n    r20_hit(group*4,1);\n'+before)
    before='        let mut cap = n - p;';assert part.count(before)==1;part=part.replace(before,'        r20_hit(group*4+1,1);\n'+before)
    before='            (m, d2)';assert part.count(before)==1;part=part.replace(before,'            r20_hit(group*4+2,1);\n            r20_hit(group*4+3,m-l);\n'+before)
    text=text[:a]+part+text[b:]+'''\nuse std::sync::atomic::{AtomicU64,Ordering};
static R20_COUNTS:[AtomicU64;28]=[const{AtomicU64::new(0)};28];
fn r20_hit(i:usize,x:usize){R20_COUNTS[i].fetch_add(x as u64,Ordering::Relaxed);}
pub fn r13_take()->[u64;28]{std::array::from_fn(|i|R20_COUNTS[i].swap(0,Ordering::Relaxed))}
'''
    build=Path(os.environ['RUNNER_TEMP'])/'r20-secondary-build';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r20-secondary';out.mkdir(parents=True)
    observed=build/'observed.rs';observed.write_text(text)
    sp=importlib.util.spec_from_file_location('h',ROOT/'scripts/research-round13-counts.py');h=importlib.util.module_from_spec(sp);sp.loader.exec_module(h)
    driver=build/'driver.rs';driver.write_text(h.HARNESS.replace('FROZEN',str(src)).replace('OBSERVED',str(observed)))
    binary=build/'driver';c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    run=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(run.stdout+run.stderr);assert run.returncode==0
    rows=[]
    for line in run.stdout.splitlines():
        if line.startswith('R13_COUNT '):
            _,name,size,*vs=line.split();assert len(vs)==28;values=list(map(int,vs));rows.append({'file':name,'raw_bytes':int(size),'groups':[dict(zip(['requests','endpoint_pass','selected_longer','extra_match_bytes'],values[4*i:4*i+4]))for i in range(7)]})
    assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'VERIFIED_UNTIMED_OBSERVER_EXACT_TOKENS_AND_DECODE','source_hashes':e['hashes'],'observer_sha256':hashlib.sha256(observed.read_bytes()).hexdigest(),'primary_length_bins':['3-4','5-8','9-16','17-32','33-64','65-128','129-258'],'rows':rows,'totals':[{k:sum(r['groups'][i][k]for r in rows)for k in rows[0]['groups'][i]}for i in range(7)],'scope':'Counts of original choices, not final encoded benefit or measured speed. All28 observed tokens equal exact frozenCSV18 and decode. Any pruning requires actual new bytes/time/fullgate.'}
    (out/'counts.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result['totals']))
if __name__=='__main__':main()
