"""Untimed shallow-chain recovery on primary failures; original output preserved."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess
from round4 import ROOT,validate

FIELDS=['primary_misses','live_head_misses','older_live_candidates','one_step_recovered','one_step_bytes','existing_depth_recovered','existing_depth_bytes','recovered_ge7','recovered_ge16']

def instrument(raw):
    original=raw.decode();a=original.index('pub fn pc_run1c<const H: usize>');b=original.index('/// Structured binaries (class 3)',a);body=original[a:b]
    before='            let f = pc_probe_m(input, c, cw, p, km);';addition='''
            if f.0<3 {
                r13_res_hit(0,1);
                if c<p && p-c<=32768 {
                    r13_res_hit(1,1);let cl=prev[c%32768]as usize;
                    r13_res_hit(2,(cl<c&&p-cl<=32768)as u64);
                    let one=pc_f_try(input,c,cl,p,0,0,minl);
                    let deep=pc_f_deepen(input,&prev,c,cl,p,0,0,dp,minl);
                    r13_res_hit(3,(one.0>=minl&&one.0>=3)as u64);r13_res_hit(4,one.0 as u64);
                    r13_res_hit(5,(deep.0>=minl&&deep.0>=3)as u64);r13_res_hit(6,deep.0 as u64);
                    r13_res_hit(7,(deep.0>=7)as u64);r13_res_hit(8,(deep.0>=16)as u64);
                }
            }
'''
    assert body.count(before)==1;body=body.replace(before,before+addition,1);changed=original[:a]+body+original[b:];assert changed.replace(addition,'',1)==original
    counters='''
use std::sync::atomic::{AtomicU64,Ordering};
static R13_RESCUE:[AtomicU64;9]=[const{AtomicU64::new(0)};9];
fn r13_res_hit(i:usize,x:u64){R13_RESCUE[i].fetch_add(x,Ordering::Relaxed);}
pub fn r13_take()->[u64;9]{std::array::from_fn(|i|R13_RESCUE[i].swap(0,Ordering::Relaxed))}
''';return(changed+counters).encode()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(e for e in spec['entries']if e['name']=='public514');frozen=ROOT/e['path']/'parse.rs';raw=frozen.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    l=importlib.util.spec_from_file_location('r13_res_harness',ROOT/'scripts/research-round13-counts.py');m=importlib.util.module_from_spec(l);l.loader.exec_module(m)
    build=Path(os.environ['RUNNER_TEMP'])/'r13-rescue-build';build.mkdir(exist_ok=True);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-rescue';out.mkdir(parents=True,exist_ok=True)
    observed=build/'observed.rs';observed.write_bytes(instrument(raw));source=build/'counts.rs';source.write_text(m.HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)));binary=build/'counts'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=120);(out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    rows=[]
    for line in r.stdout.splitlines():
        if line.startswith('R13_COUNT '):
            _,name,n,*vs=line.split();assert len(vs)==len(FIELDS);p=corpus/name;assert p.stat().st_size==int(n);rows.append({'file':name,'raw_bytes':int(n),'input_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'counts':dict(zip(FIELDS,map(int,vs)))})
    assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'VERIFIED_FINITE_FROZEN_OBSERVED_TOKEN_AND_DECODE_EQUAL','source_sha256':hashlib.sha256(raw).hexdigest(),'observer_sha256':hashlib.sha256(observed.read_bytes()).hexdigest(),'harness_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'files':rows,'totals':{f:sum(x['counts'][f]for x in rows)for f in FIELDS},'scope':'Recovery candidates validated by original byte/window probes along original primary-miss positions. Original outputs unchanged. Covered bytes are opportunities, not final encoded savings or time gains.'}
    (out/'counts.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result['totals']))

if __name__=='__main__':main()
