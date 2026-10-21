"""Run actual full and bounded-tail A kernels through wrap-sensitive windows."""
from pathlib import Path
import hashlib,importlib,json,os,subprocess
from round4 import ROOT,validate
def harness():
    t=importlib.import_module('research-round18-a-ring').HARNESS
    t=t.replace('parent::a_slot_of','parent::Z158').replace('let mut newcost=vec![0u32;512]','let mut newcost=vec![0u32;n+1]')
    t=t.replace('*v=(next(&mut seed)&2047)as u32;','*v=if case%5==0{next(&mut seed)as u32}else{(next(&mut seed)&2047)as u32};')
    a=t.index(' parent::a_dp_pass(');b=t.index('\n}println!',a)
    t=t[:a]+''' for mode in 0..2 {oldcost.fill(0);newcost.fill(0);a.fill(0);b.fill(0);
 if mode==0 {parent::Z184(&input,&mp,&mb,p0,pe,&lit,&lc,&dc,&mut oldcost,&mut a);candidate::Z184(&input,&mp,&mb,p0,pe,&lit,&lc,&dc,&mut newcost,&mut b);}
 else {let tail=[0,1,3,8,258][case%5];parent::Z307(&input,&mp,&mb,p0,pe,&lit,&lc,&dc,&mut oldcost,&mut a,tail);candidate::Z307(&input,&mp,&mb,p0,pe,&lit,&lc,&dc,&mut newcost,&mut b,tail);}
 assert_eq!(a,b,"choices mode={} case={} n={} p0={} pe={}",mode,case,n,p0,pe);
 for i in 0..oldcost.len(){assert_eq!(oldcost[i]<<9,newcost[i],"packedcost mode={} case={} i={}",mode,case,i);}
 }
'''+t[b:]
    return t.replace('R18_A_RING_DIFFERENTIAL_OK 2400','R24_A_PACKED_DIFFERENTIAL_OK 4800')
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux';s=validate(os.environ['ROUND4_SPEC']);e=next(x for x in s['entries']if x['name']=='r24-609-a-packed');parent=next(x for x in s['entries']if x['name']=='once')
    build=Path(os.environ['RUNNER_TEMP'])/'r24-a-packed';build.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-a-packed';out.mkdir(parents=True);paths=[]
    for x in [e,parent]:
        p=ROOT/x['path']/'parse.rs';assert hashlib.sha256(p.read_bytes()).hexdigest()==x['hashes']['parse.rs'];paths.append(p)
    t=harness().replace('SOURCE',json.dumps(str(paths[0]))).replace('PARENT',json.dumps(str(paths[1])));driver=build/'main.rs';driver.write_text(t);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary)],capture_output=True,text=True,timeout=180);(out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0 and 'R24_A_PACKED_DIFFERENTIAL_OK 4800'in p.stdout
    d={'status':'VERIFIED_FINITE_REAL_A_KERNEL_PACKED_DIFFERENTIAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_files':e['hashes'],'parent_files':parent['hashes'],'harness_sha256':hashlib.sha256(t.encode()).hexdigest(),'cases':4800,'scope':'ActualZ184/Z307 choices and modulo23bit costs, finite windows/tails/U32wrap. Wholepublicparity is separate; no universal equivalence, speed or gate claim.'};(out/'receipt.json').write_bytes((json.dumps(d,indent=2)+'\n').encode());print(json.dumps(d))
if __name__=='__main__':main()
