"""R15 bounded native profiling; other native batches reuse the exact-encoder screen."""
from pathlib import Path
import hashlib,json,os,subprocess,sys,zlib
from round4 import ROOT,validate

HARNESS=r'''
#![allow(dead_code)]
#[path=SOURCE]mod frozen;
#[path=TOKEN]mod token;
#[path=CODEC]mod codec;
fn decode(s:&[u8],ts:&[u32])->bool{let mut v=Vec::new();for&t in ts{match token::decode(t){token::Token::Literal(x)=>v.push(x),token::Token::Match{dist,len}=>{if dist as usize>v.len()||v.len()+len as usize>s.len(){return false;}for _ in 0..len{let x=v[v.len()-dist as usize];v.push(x);}},_=>return false}}v==s}
fn main(){let args:Vec<_>=std::env::args().collect();let mut paths:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();paths.sort();for(i,p)in paths.iter().enumerate(){let s=std::fs::read(p).unwrap();let name=p.file_name().unwrap().to_str().unwrap();let mut expected=vec![0u32;s.len()];let nt=frozen::parse(&s,&mut expected);assert!(nt<=s.len());expected.truncate(nt);assert!(decode(&s,&expected));let enc=codec::encode(&expected,s.len()).unwrap();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.deflate",i)),&enc).unwrap();let mut tok=Vec::new();for&t in&expected{tok.extend(t.to_le_bytes());}std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",i)),tok).unwrap();for rep in 0..3{let mut out=vec![0u32;s.len()];let start=std::time::Instant::now();let base_nt=frozen::SFbase(&s,&mut out);let base_ns=start.elapsed().as_nanos();let start=std::time::Instant::now();let enabled=frozen::SFenabled(&s);let plan=if enabled{frozen::SFshape(&s,&out,base_nt)}else{Vec::new()};let shape_ns=start.elapsed().as_nanos();let start=std::time::Instant::now();let n=if enabled{frozen::Z167(&s,&plan,&mut out)}else{base_nt};let emit_ns=start.elapsed().as_nanos();assert!(n<=s.len());out.truncate(n);assert_eq!(out,expected,"phase decomposition {}",name);assert!(decode(&s,&out));println!("PHASE {} {} {} {} {} {} {} {} {} {}",i,name,s.len(),rep,enabled,base_ns,shape_ns,emit_ns,nt,enc.len());}}}
'''

def sha(b):return hashlib.sha256(b).hexdigest()
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC'])
    if not spec.get('r15_phase_profile'):
        subprocess.run([sys.executable,str(ROOT/'scripts/research-round13-native.py')],check=True);return
    entry=next(e for e in spec['entries']if e['name']=='public550');source=ROOT/entry['path']/'parse.rs';assert sha(source.read_bytes())==entry['hashes']['parse.rs']
    build=Path(os.environ['RUNNER_TEMP'])/'r15-phase-build';build.mkdir(exist_ok=True);spool=build/'spool';spool.mkdir(exist_ok=True)
    output=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r15-phases';output.mkdir(parents=True,exist_ok=True)
    upstream=Path(os.environ['DEFLATE_ROOT']);codec=upstream/'validator/measure/src/deflate.rs';token=codec.with_name('token.rs')
    text=HARNESS.replace('SOURCE',json.dumps(str(source))).replace('TOKEN',json.dumps(str(token))).replace('CODEC',json.dumps(str(codec)))
    driver=build/'phase.rs';driver.write_text(text);binary=build/'phase'
    record={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'STARTED_DIAGNOSTIC','source_hashes':entry['hashes'],'harness_sha256':sha(text.encode()),'codec_sha256':sha(codec.read_bytes()),'token_sha256':sha(token.read_bytes()),'scope':'Explicit calls to unchanged550 phase functions; equality to original full parse checked. Timings are diagnostic including observer/call-layout effects, not paired official time axis or proof.'}
    report=output/'phases.json';report.write_text(json.dumps(record,indent=2)+'\n')
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (output/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=upstream/'data/benchmark/corpus-stage1';r=subprocess.run([str(binary),str(corpus),str(spool)],capture_output=True,text=True,timeout=480)
    (output/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    rows=[]
    for line in r.stdout.splitlines():
        if not line.startswith('PHASE '):continue
        _,i,name,size,rep,enabled,base,shape,emit,nt,nb=line.split()
        raw=(corpus/name).read_bytes();enc=(spool/f'{i}.deflate').read_bytes();tok=(spool/f'{i}.tokens').read_bytes()
        assert len(raw)==int(size)and len(enc)==int(nb)and len(tok)==4*int(nt)and zlib.decompress(enc,-15)==raw
        rows.append({'file':name,'raw_bytes':int(size),'input_sha256':sha(raw),'repetition':int(rep),'phase':'warmup'if int(rep)==0 else'measured_diagnostic','shape_enabled':enabled=='true','base_ns':int(base),'shape_ns':int(shape),'emit_ns':int(emit),'tokens':int(nt),'token_sha256':sha(tok),'output_bytes':int(nb),'output_sha256':sha(enc)})
    assert len(rows)==84 and len({x['file']for x in rows})==28 and sum(x['raw_bytes']for x in rows if x['repetition']==0)==15930000
    record.update(status='VERIFIED_PHASE_COMPOSITION_TOKEN_EQUAL_AND_PUBLIC_DECODE',rows=rows,diagnostic_sum_ns={p:sum(r[p]for r in rows if r['repetition']>0)for p in('base_ns','shape_ns','emit_ns')})
    report.write_text(json.dumps(record,indent=2)+'\n');print(json.dumps({'status':record['status'],'diagnostic_sum_ns':record['diagnostic_sum_ns']}))
if __name__=='__main__':main()
