"""Inclusive native function-cost diagnostic on the declared original R18 source."""
from pathlib import Path
import hashlib,importlib.util,json,os,re,subprocess
from round4 import ROOT,validate
FUNCTIONS=['Z337','Z351','Z460','Z361','Z420','SFsmallmatches','SFsolve','SFtable','SFpositions','SFcost','SFprev']

def instrument(raw,functions=FUNCTIONS):
    text=raw.decode();wrappers=[]
    assert functions and len(functions)==len(set(functions))
    for index,name in enumerate(functions):
        needle='pub fn '+name+'(';assert text.count(needle)==1,name
        start=text.index(needle);brace=text.index('{',start);head=text[start:brace]
        args=re.findall(r'(?:\(|,)\s*(?:mut\s+)?([A-Za-z_][A-Za-z0-9_]*)\s*:',head)
        assert args and len(args)==head.count(':'),(name,args,head)
        text=text[:start]+text[start:].replace(needle,'pub fn r15_inner_'+name+'(',1)
        wrappers.append('#[inline(always)]\n'+head+'{let t=std::time::Instant::now();let result=r15_inner_'+name+'('+','.join(args)+');R15_COUNTS['+str(index*2)+'].fetch_add(1,std::sync::atomic::Ordering::Relaxed);R15_COUNTS['+str(index*2+1)+'].fetch_add(t.elapsed().as_nanos().min(u64::MAX as u128) as u64,std::sync::atomic::Ordering::Relaxed);result}\n')
    text+='\nuse std::sync::atomic::{AtomicU64,Ordering};\nstatic R15_COUNTS:[AtomicU64;'+str(len(functions)*2)+']=[const{AtomicU64::new(0)};'+str(len(functions)*2)+'];\npub fn r15_take()->[u64;'+str(len(functions)*2)+']{std::array::from_fn(|i|R15_COUNTS[i].swap(0,Ordering::Relaxed))}\n'+'\n'.join(wrappers)
    return text.encode()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);functions=spec.get('r15_profile_functions',FUNCTIONS);e=next(e for e in spec['entries']if e['name']==spec.get('r15_profile_entry','public550'));frozen=ROOT/e['path']/'parse.rs';raw=frozen.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    build=Path(os.environ['RUNNER_TEMP'])/'r18-functions-build';build.mkdir(exist_ok=True);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-functions';out.mkdir(parents=True,exist_ok=True)
    observed=build/'observed.rs';observed.write_bytes(instrument(raw,functions))
    loader=importlib.util.spec_from_file_location('r13_counts_harness',ROOT/'scripts/research-round13-counts.py');m=importlib.util.module_from_spec(loader);loader.loader.exec_module(m)
    text=m.HARNESS.replace('FROZEN',str(frozen)).replace('OBSERVED',str(observed)).replace('observed::r13_take()','observed::r15_take()').replace('R13_COUNT','R15_FUNCTION')
    source=build/'driver.rs';source.write_text(text);binary=build/'driver'
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'STARTED_FUNCTION_DIAGNOSTIC','candidate':e['name'],'functions':functions,'source_hashes':e['hashes'],'observer_sha256':hashlib.sha256(observed.read_bytes()).hexdigest(),'driver_sha256':hashlib.sha256(text.encode()).hexdigest(),'scope':'Inclusive instrumented function durations and counts, checked against frozen full-parse tokens and independent decode. Nested function times overlap and must not be summed as independent savings. Not official paired time, full proof or candidate promotion.'}
    report=out/'functions.json';report.write_text(json.dumps(result,indent=2)+'\n')
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=240);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=480);(out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    rows=[]
    for line in r.stdout.splitlines():
        if not line.startswith('R15_FUNCTION '):continue
        _,name,size,*values=line.split();assert len(values)==2*len(functions);v=list(map(int,values));data=(corpus/name).read_bytes();assert len(data)==int(size)
        rows.append({'file':name,'raw_bytes':len(data),'input_sha256':hashlib.sha256(data).hexdigest(),'functions':{n:{'calls':v[i*2],'inclusive_ns':v[i*2+1]}for i,n in enumerate(functions)}})
    assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
    result.update(status='VERIFIED_FUNCTION_OBSERVER_TOKEN_AND_DECODE_EQUAL',rows=rows,totals={n:{k:sum(r['functions'][n][k]for r in rows)for k in('calls','inclusive_ns')}for n in functions});report.write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({'status':result['status'],'totals':result['totals']}))
if __name__=='__main__':main()
