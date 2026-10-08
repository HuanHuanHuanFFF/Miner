"""Untimed wider-key opportunity replay along unchanged public514 EF32 positions."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess
from round4 import ROOT,validate

FIELDS=['searches','parent_window_candidates','parent_matches','parent_match_bytes',
        'wide15_longer_matches','wide15_added_match_bytes','wide16_longer_matches','wide16_added_match_bytes']

def instrument(raw):
    original=raw.decode();a=original.index('pub fn ef32_run(');b=original.index('// ─────────────── ETINY:',a);body=original[a:b]
    x='        let mut head = [0u32; 16384];'
    y=x+'\n        let mut r13_wide15 = [0u32;32768];\n        let mut r13_wide16 = [0u32;65536];'
    assert body.count(x)==1;body=body.replace(x,y,1)
    x='            let l = ef32_probe(input, c, p);'
    y=x+'''
            let key=(input[p] as u32)|((input[p+1]as u32)<<8)|((input[p+2]as u32)<<16);
            let mixed=key.wrapping_mul(0x9E37_79B1);
            let h15=(mixed>>17)as usize;let h16=(mixed>>16)as usize;
            let c15=r13_wide15[h15]as usize;let c16=r13_wide16[h16]as usize;
            r13_wide15[h15]=p as u32;r13_wide16[h16]=p as u32;
            let l15=ef32_probe(input,c15,p);let l16=ef32_probe(input,c16,p);
            r13_ef_hit(0,1);r13_ef_hit(1,(c<p&&p-c<=32768)as u64);
            r13_ef_hit(2,(l>=3)as u64);r13_ef_hit(3,if l>=3{l as u64}else{0});
            r13_ef_hit(4,(l15>l&&l15>=3)as u64);
            r13_ef_hit(5,if l15>l&&l15>=3{(l15-if l>=3{l}else{0})as u64}else{0});
            r13_ef_hit(6,(l16>l&&l16>=3)as u64);
            r13_ef_hit(7,if l16>l&&l16>=3{(l16-if l>=3{l}else{0})as u64}else{0});
'''
    assert body.count(x)==1;body=body.replace(x,y,1)
    changed=original[:a]+body+original[b:]
    counters='''
use std::sync::atomic::{AtomicU64,Ordering};
static R13_EF_COUNTS:[AtomicU64;8]=[const{AtomicU64::new(0)};8];
fn r13_ef_hit(i:usize,x:u64){R13_EF_COUNTS[i].fetch_add(x,Ordering::Relaxed);}
pub fn r13_take()->[u64;8]{std::array::from_fn(|i|R13_EF_COUNTS[i].swap(0,Ordering::Relaxed))}
'''
    assert changed.replace(y,x,1).replace('        let mut r13_wide15 = [0u32;32768];\n        let mut r13_wide16 = [0u32;65536];\n','',1)==original
    return (changed+counters).encode()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);entry=next(e for e in spec['entries']if e['name']=='public514')
    frozen=ROOT/entry['path']/'parse.rs';raw=frozen.read_bytes();assert hashlib.sha256(raw).hexdigest()==entry['hashes']['parse.rs']
    loader=importlib.util.spec_from_file_location('r13_shared_count_harness',ROOT/'scripts/research-round13-counts.py');m=importlib.util.module_from_spec(loader);loader.loader.exec_module(m)
    build=Path(os.environ['RUNNER_TEMP'])/'r13-ef-counts-build';build.mkdir(exist_ok=True)
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-ef-counts';out.mkdir(parents=True,exist_ok=True)
    observed=build/'observed.rs';observed.write_bytes(instrument(raw))
    source=build/'counts.rs';source.write_text(m.HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)))
    binary=build/'counts';c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=120);(out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    files=[]
    for line in r.stdout.splitlines():
        if line.startswith('R13_COUNT '):
            _,name,n,*values=line.split();assert len(values)==len(FIELDS)
            p=corpus/name;assert p.stat().st_size==int(n)
            files.append({'file':name,'bytes':int(n),'input_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'counts':dict(zip(FIELDS,map(int,values)))})
    assert len(files)==28 and sum(f['bytes']for f in files)==15930000
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
        'status':'VERIFIED_FINITE_FROZEN_OBSERVED_TOKEN_AND_DECODE_EQUAL','source_sha256':hashlib.sha256(raw).hexdigest(),
        'observer_sha256':hashlib.sha256(observed.read_bytes()).hexdigest(),'harness_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
        'scope':'Wider keys replayed along original positions without choosing their matches. Extra bytes are opportunities, not saved compressed bytes, timing gains or private guarantees.',
        'files':files,'totals':{f:sum(x['counts'][f]for x in files)for f in FIELDS}}
    (out/'counts.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({'totals':result['totals'],'scope':result['scope']}))

if __name__=='__main__':main()
