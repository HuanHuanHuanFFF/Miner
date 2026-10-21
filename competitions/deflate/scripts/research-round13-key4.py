"""Untimed additional fourth-byte-key candidates at original EF32 positions."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess
from round4 import ROOT,validate

FIELDS=['parent_probes','parent_matches','key4_window_candidates','key4_longer_matches','key4_added_match_bytes','key4_length_ge7','key4_length_ge11']

def instrument(raw):
    original=raw.decode();a=original.index('pub fn ef32_run(');b=original.index('// ─────────────── ETINY:',a);body=original[a:b]
    x='        let mut head = [0u32; 16384];';extra='\n        let mut r13_key4_head = [0u32;32768];'
    assert body.count(x)==1;body=body.replace(x,x+extra,1)
    x='            let l = ef32_probe(input, c, p);'
    addition='''
            let k4=(input[p]as u32)|((input[p+1]as u32)<<8)|((input[p+2]as u32)<<16)|((input[p+3]as u32)<<24);
            let h4=(k4.wrapping_mul(0x9E37_79B1)>>17)as usize;
            let c4=r13_key4_head[h4]as usize;r13_key4_head[h4]=p as u32;
            let l4=ef32_probe(input,c4,p);
            r13_k4_hit(0,1);r13_k4_hit(1,(l>=3)as u64);r13_k4_hit(2,(c4<p&&p-c4<=32768)as u64);
            r13_k4_hit(3,(l4>l&&l4>=4)as u64);
            r13_k4_hit(4,if l4>l&&l4>=4{(l4-if l>=3{l}else{0})as u64}else{0});
            r13_k4_hit(5,(l4>l&&l4>=7)as u64);r13_k4_hit(6,(l4>l&&l4>=11)as u64);
'''
    assert body.count(x)==1;body=body.replace(x,x+addition,1)
    changed=original[:a]+body+original[b:];assert changed.replace(extra,'',1).replace(addition,'',1)==original
    counters='''
use std::sync::atomic::{AtomicU64,Ordering};
static R13_KEY4_COUNTS:[AtomicU64;7]=[const{AtomicU64::new(0)};7];
fn r13_k4_hit(i:usize,x:u64){R13_KEY4_COUNTS[i].fetch_add(x,Ordering::Relaxed);}
pub fn r13_take()->[u64;7]{std::array::from_fn(|i|R13_KEY4_COUNTS[i].swap(0,Ordering::Relaxed))}
'''
    return(changed+counters).encode()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(e for e in spec['entries']if e['name']=='public514');frozen=ROOT/e['path']/'parse.rs';raw=frozen.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    l=importlib.util.spec_from_file_location('r13_key4_harness',ROOT/'scripts/research-round13-counts.py');m=importlib.util.module_from_spec(l);l.loader.exec_module(m)
    build=Path(os.environ['RUNNER_TEMP'])/'r13-key4-build';build.mkdir(exist_ok=True)
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-key4';out.mkdir(parents=True,exist_ok=True)
    observed=build/'observed.rs';observed.write_bytes(instrument(raw));source=build/'counts.rs';source.write_text(m.HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)));binary=build/'counts'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=120);(out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    rows=[]
    for line in r.stdout.splitlines():
        if line.startswith('R13_COUNT '):
            _,name,n,*vs=line.split();assert len(vs)==len(FIELDS)
            p=corpus/name;assert p.stat().st_size==int(n);rows.append({'file':name,'raw_bytes':int(n),'input_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'counts':dict(zip(FIELDS,map(int,vs)))})
    assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
        'status':'VERIFIED_FINITE_FROZEN_OBSERVED_TOKEN_AND_DECODE_EQUAL','source_sha256':hashlib.sha256(raw).hexdigest(),'observer_sha256':hashlib.sha256(observed.read_bytes()).hexdigest(),'harness_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
        'scope':'Auxiliary fourth-byte key observed at original probe positions. Original outputs preserved; extra covered bytes are opportunities, not compressed-byte savings or independent performance confirmation.',
        'files':rows,'totals':{f:sum(x['counts'][f]for x in rows)for f in FIELDS}}
    (out/'counts.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result['totals']))

if __name__=='__main__':main()
