"""Real A-DP full-cost-vector differential for the block-extrema hybrid."""
from pathlib import Path
import hashlib,importlib.util,json,os,subprocess
from round4 import ROOT,validate

def harness():
    sp=importlib.util.spec_from_file_location('aring_harness',ROOT/'scripts/research-round18-a-ring.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);text=m.HARNESS
    assert text.count('let mut newcost=vec![0u32;512]')==1;text=text.replace('let mut newcost=vec![0u32;512]','let mut newcost=vec![0u32;n+1]')
    old='for i in p0..pe.min(p0+258){assert_eq!(oldcost[i],newcost[i&511],"cost case={} at={}",case,i);}';assert text.count(old)==1;text=text.replace(old,'assert!(oldcost==newcost,"fullcost case={}",case);')
    needle=' let pe=if case%2==0';assert text.count(needle)==1
    text=text.replace(needle,''' let group=match case%4{0=>512,1=>8,2=>32,_=>1};let mut price=0u32;
 for i in 0..512{if i%group==0{price=if case%5==0{next(&mut seed)as u32}else{(next(&mut seed)&2047)as u32};}lc[i]=price;}
'''+needle)
    return text.replace('R18_A_RING_DIFFERENTIAL_OK','R18_A_BLOCK_DIFFERENTIAL_OK')

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux';s=validate(os.environ['ROUND4_SPEC']);e=next(x for x in s['entries']if x['name']==s['r18_a_block_check']);parent=next(x for x in s['entries']if x['name']==e['expected_equivalent_to'])
    build=Path(os.environ['RUNNER_TEMP'])/'r18-a-block-check';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-a-block-check';out.mkdir(parents=True);paths=[]
    for entry in(e,parent):
        p=ROOT/entry['path']/'parse.rs';assert hashlib.sha256(p.read_bytes()).hexdigest()==entry['hashes']['parse.rs'];paths.append(p)
    text=harness().replace('SOURCE',json.dumps(str(paths[0]))).replace('PARENT',json.dumps(str(paths[1])));driver=build/'driver.rs';driver.write_text(text);binary=build/'driver'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    rr=subprocess.run([str(binary)],capture_output=True,text=True,timeout=120);(out/'run.log').write_text(rr.stdout+rr.stderr);assert rr.returncode==0 and 'R18_A_BLOCK_DIFFERENTIAL_OK 2400'in rr.stdout
    enc=json.loads((Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-encoder/encoder.json').read_bytes());rows={(r['candidate'],r['file']):r for r in enc['rows']};actual=[r for r in enc['rows']if r['candidate']==e['name']];assert len(actual)==28
    for r in actual:assert all(r[k]==rows[parent['name'],r['file']][k]for k in('output_bytes','tokens_sha256','output_sha256'))
    result={'status':'VERIFIED_FINITE_A_BLOCK_DIFFERENTIAL_AND_PUBLIC_TOKEN_BYTES_EQUAL','cases':2400,'public_files':28,'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_hashes':e['hashes'],'parent_hashes':parent['hashes'],'harness_sha256':hashlib.sha256(text.encode()).hexdigest(),'scope':'Actual A-DP helper choices and fullcostvectors compared on finite windows, candidate layouts andflat/grouped/randomprices includingU32wrap. Fullpublic28file tokens/bytes equal. This is not universal equivalence, performance or fullgate.'};(out/'differential.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))

if __name__=='__main__':main()
