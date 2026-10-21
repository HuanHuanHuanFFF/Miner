"""Original-encoder probe: demote short DNA matches without changing search history."""
from pathlib import Path
import hashlib,json,os,subprocess,zlib
from round4 import ROOT,validate

HARNESS=r'''
#![allow(dead_code)]
#[path=TOKEN]mod token;
#[path=CODEC]mod codec;
#[path=ORIGINAL]mod original;
#[path=SPLIT]mod split;
type Parser=fn(&[u8],&mut[u32])->usize;
fn decode(s:&[u8],ts:&[u32])->bool{let mut v=Vec::new();for&t in ts{match token::decode(t){token::Token::Literal(x)=>v.push(x),token::Token::Match{dist,len}=>{if dist as usize>v.len()||v.len()+len as usize>s.len(){return false;}for _ in 0..len{let x=v[v.len()-dist as usize];v.push(x);}},_=>return false}}v==s}
fn main(){let args:Vec<_>=std::env::args().collect();let raw=std::fs::read(&args[1]).unwrap();let out=std::path::Path::new(&args[2]);let parsers:[(&str,Parser);2]=[("dna582",original::parse),("split4",split::parse)];
for(name,parse)in parsers{let mut ts=vec![0u32;raw.len()];let n=parse(&raw,&mut ts);ts.truncate(n);assert!(decode(&raw,&ts));let mut hist=[0u64;259];for&t in &ts{if let token::Token::Match{dist:_,len}=token::decode(t){hist[len as usize]+=1;}}
for l in 3..259{if hist[l]>0{println!("R18_DNA_LENGTH {} {} {}",name,l,hist[l]);}}
for cap in [0usize,6,8,10,12,16,258]{let mut changed=Vec::with_capacity(raw.len());let mut p=0usize;let mut demoted=0usize;
for&t in &ts{match token::decode(t){token::Token::Literal(_)=>{changed.push(t);p+=1;},token::Token::Match{dist:_,len}=>{let len=len as usize;if len<=cap {for &b in &raw[p..p+len]{changed.push(b as u32);}demoted+=1;}else{changed.push(t);}p+=len;},_=>panic!("invalid")}}
assert!(p==raw.len()&&changed.len()<=raw.len()&&decode(&raw,&changed));let enc=codec::encode(&changed,raw.len()).unwrap();let mut tokens=Vec::new();for&t in &changed{tokens.extend(t.to_le_bytes());}
std::fs::write(out.join(format!("{}-{}.deflate",name,cap)),&enc).unwrap();std::fs::write(out.join(format!("{}-{}.tokens",name,cap)),tokens).unwrap();println!("R18_DNA_DEMOTE {} {} {} {} {}",name,cap,enc.len(),changed.len(),demoted);}
}}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);assert spec['r18_dna_demotion_probe'];by={e['name']:e for e in spec['entries']};names=['dna582','r18-dna-split4'];paths=[]
    for name in names:
        e=by[name];p=ROOT/e['path']/'parse.rs';assert hashlib.sha256(p.read_bytes()).hexdigest()==e['hashes']['parse.rs'];paths.append(p)
    up=Path(os.environ['DEFLATE_ROOT']);codec=up/'validator/measure/src/deflate.rs';token=codec.with_name('token.rs');inp=up/'data/benchmark/corpus-stage1/genome.fasta';raw=inp.read_bytes()
    build=Path(os.environ['RUNNER_TEMP'])/'r18-demotion';build.mkdir();spool=build/'spool';spool.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r18-demotion';out.mkdir(parents=True)
    text=HARNESS.replace('TOKEN',json.dumps(str(token))).replace('CODEC',json.dumps(str(codec))).replace('ORIGINAL',json.dumps(str(paths[0]))).replace('SPLIT',json.dumps(str(paths[1])));driver=build/'driver.rs';driver.write_text(text);binary=build/'driver'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    rr=subprocess.run([str(binary),str(inp),str(spool)],capture_output=True,text=True,timeout=180);(out/'run.log').write_text(rr.stdout+rr.stderr);assert rr.returncode==0
    prior=json.loads((ROOT/'evidence/round18/37990998091/dna-al-native/diagnostics/r13-encoder/encoder.json').read_bytes());expected={r['candidate']:r for r in prior['rows']if r['file']=='genome.fasta'};hist={};rows=[]
    for line in rr.stdout.splitlines():
        if line.startswith('R18_DNA_LENGTH '):
            _,name,length,count=line.split();hist.setdefault(name,{})[length]=int(count)
        if line.startswith('R18_DNA_DEMOTE '):
            _,name,cap,nb,nt,demoted=line.split();cap=int(cap);enc=(spool/f'{name}-{cap}.deflate').read_bytes();tokens=(spool/f'{name}-{cap}.tokens').read_bytes();assert len(enc)==int(nb)and len(tokens)==4*int(nt)and zlib.decompress(enc,-15)==raw
            source='dna582'if name=='dna582'else'r18-dna-split4';baseline=expected[source];assert hashlib.sha256(raw).hexdigest()==baseline['input_sha256']
            if cap==0:assert hashlib.sha256(enc).hexdigest()==baseline['output_sha256']and hashlib.sha256(tokens).hexdigest()==baseline['tokens_sha256']
            rows.append({'source':source,'cutoff':cap,'output_bytes':len(enc),'tokens':int(nt),'demoted_matches':int(demoted),'bytes_change_vs_same_source':len(enc)-baseline['output_bytes'],'tokens_change_vs_same_source':int(nt)-baseline['tokens'],'output_sha256':hashlib.sha256(enc).hexdigest(),'tokens_sha256':hashlib.sha256(tokens).hexdigest()})
    assert len(rows)==14
    report={'status':'VERIFIED_FINITE_ORIGINAL_ENCODER_DEMOTED_TOKEN_STREAMS','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'source_hashes':{n:by[n]['hashes']for n in names},'input_sha256':hashlib.sha256(raw).hexdigest(),'raw_bytes':len(raw),'codec_sha256':hashlib.sha256(codec.read_bytes()).hexdigest(),'token_sha256':hashlib.sha256(token.read_bytes()).hexdigest(),'harness_sha256':hashlib.sha256(text.encode()).hexdigest(),'match_length_histograms':hist,'rows':rows,'scope':'Seven declared cutoffs bracket static DNA literal/match break-even and the all-literal endpoint. Original search/token positions remain fixed before transformation. One public genome input, original codec and zlib decode. These transformed streams are not runnable parser candidates, measured time, fullgate or payout evidence; chosen behavior must be implemented and rechecked over the full corpus.'};(out/'demotion.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps({'status':report['status'],'rows':rows}))

if __name__=='__main__':main()
