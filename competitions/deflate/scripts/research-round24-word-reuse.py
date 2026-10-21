"""Count the actual firstword reuse seam, preserving the uninstrumented candidate."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);e=next(x for x in spec['entries']if x['name']=='r24-609-word-reuse');source=ROOT/e['path']/'parse.rs';raw=source.read_bytes();assert hashlib.sha256(raw).hexdigest()==e['hashes']['parse.rs']
    text=raw.decode();a=text.index('pub fn Afirstword(');b=text.index('pub fn Z162(',a);part=text[a:b]
    part=part.replace(' if k==0 {',' R24_WR[0].fetch_add(1,Ordering::Relaxed);if k==0 {R24_WR[1].fetch_add(1,Ordering::Relaxed);')
    part=part.replace('if other!=word {return','if other!=word {R24_WR[2].fetch_add(1,Ordering::Relaxed);return')
    text=text[:a]+part+text[b:]+'''\nuse std::sync::atomic::{AtomicU64,Ordering};
static R24_WR:[AtomicU64;3]=[const{AtomicU64::new(0)};3];
pub fn r24_take()->[u64;3]{std::array::from_fn(|i|R24_WR[i].swap(0,Ordering::Relaxed))}
'''
    build=Path(os.environ['RUNNER_TEMP'])/'r24-word-reuse';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-word-reuse';out.mkdir(parents=True);obs=build/'observed.rs';obs.write_text(text)
    h=importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN',str(source)).replace('OBSERVED',str(obs)).replace('observed::r13_take()','observed::r24_take()').replace('R13_COUNT','R24_WR');driver=build/'main.rs';driver.write_text(h);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    fields=['calls','zero_prefix_calls','firstword_mismatch'];rows=[]
    for line in p.stdout.splitlines():
        if line.startswith('R24_WR '):
            _,name,size,*vals=line.split();assert len(vals)==3;rows.append({'file':name,'raw_bytes':int(size),**dict(zip(fields,map(int,vals)))})
    assert len(rows)==28
    result={'status':'VERIFIED_UNTIMED_WORD_COUNTS_OBSERVER_TOKEN_AND_DECODE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'observer_sha256':hashlib.sha256(text.encode()).hexdigest(),'harness_sha256':hashlib.sha256(h.encode()).hexdigest(),'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},'scope':'Observed candidate with counts has equal tokens/decode; separate native receipt compares to once. Not timing/proof/private evidence.'}
    (out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result['totals']))
if __name__=='__main__':main()
