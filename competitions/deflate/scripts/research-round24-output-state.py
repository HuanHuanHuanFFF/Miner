"""Runner-only finite output-buffer independence check, outside official timings."""
from pathlib import Path
import hashlib, json, os, subprocess
from round4 import ROOT, validate

HARNESS = r'''
#![allow(dead_code)]
#[path=FROZEN] mod frozen;
fn tokens(s:&[u8], fill:u32)->Vec<u32>{let mut out=vec![fill;s.len()];let n=frozen::parse(s,&mut out);assert!(n<=s.len());out.truncate(n);out}
fn main(){let mut ps:Vec<_>=std::fs::read_dir(std::env::args().nth(1).unwrap()).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();ps.sort();for p in ps{let s=std::fs::read(&p).unwrap();let zero=tokens(&s,0);for fill in [u32::MAX,0xA5A5A5A5,0x1000000]{assert_eq!(zero,tokens(&s,fill),"{} fill={}",p.display(),fill);}println!("OUTPUT_STATE_EQUAL {} {} 4",p.file_name().unwrap().to_str().unwrap(),s.len());}}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);name=spec['r24_output_state_entry'];e=next(e for e in spec['entries'] if e['name']==name)
    source=ROOT/e['path']/'parse.rs';assert hashlib.sha256(source.read_bytes()).hexdigest()==e['hashes']['parse.rs']
    build=Path(os.environ['RUNNER_TEMP'])/'r24-output-state';build.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-output-state';out.mkdir(parents=True)
    text=HARNESS.replace('FROZEN',json.dumps(str(source)));driver=build/'main.rs';driver.write_text(text);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    p=subprocess.run([str(binary),str(Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1')],capture_output=True,text=True,timeout=240)
    (out/'run.log').write_text(p.stdout+p.stderr);assert p.returncode==0
    rows=[line.split()[1:] for line in p.stdout.splitlines() if line.startswith('OUTPUT_STATE_EQUAL ')]
    assert len(rows)==28 and sum(int(r[1]) for r in rows)==15930000
    receipt={'status':'VERIFIED_FINITE_OUTPUT_STATE_EQUAL','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'candidate':name,'files':e['hashes'],'harness_sha256':hashlib.sha256(text.encode()).hexdigest(),'rows':rows,'fills':[0,4294967295,2779096485,16777216],'scope':'Four initial output-buffer values on the fixed28 public files. Finite independence evidence, not universal equivalence, proof, official timing or payability.'}
    (out/'receipt.json').write_bytes((json.dumps(receipt,indent=2)+'\n').encode());print(receipt['status'])
if __name__=='__main__':main()
