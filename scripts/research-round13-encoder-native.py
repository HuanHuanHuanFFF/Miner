"""Fast native candidate byte screening with the original pinned encoder."""
from pathlib import Path
import hashlib,json,os,statistics,subprocess,zlib
from round4 import ROOT,validate

HARNESS=r'''
#![allow(dead_code)]
#[path=TOKEN]mod token;
#[path=CODEC]mod codec;
MODULES
type Parser=fn(&[u8],&mut[u32])->usize;
fn parse(s:&[u8],f:Parser)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut v=Vec::new();for&t in ts{match token::decode(t){token::Token::Literal(x)=>v.push(x),token::Token::Match{dist,len}=>{if dist as usize>v.len()||v.len()+len as usize>s.len(){return false;}for _ in 0..len{let x=v[v.len()-dist as usize];v.push(x);}},_=>return false}}v==s}
fn main(){let args:Vec<_>=std::env::args().collect();let spool=std::path::Path::new(&args[2]);let cases:&[(&str,Parser)]=&[CASES];let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();for(i,p)in files.iter().enumerate(){let s=std::fs::read(p).unwrap();let name=p.file_name().unwrap().to_str().unwrap();for &(label,f)in cases{let ts=parse(&s,f);assert!(decode(&s,&ts),"decode {} {}",label,name);let enc=codec::encode(&ts,s.len()).unwrap();let mut raw=Vec::new();for&t in&ts{raw.extend(t.to_le_bytes());}std::fs::write(spool.join(format!("{}-{}.tokens",i,label)),raw).unwrap();std::fs::write(spool.join(format!("{}-{}.deflate",i,label)),&enc).unwrap();println!("ENCODER_NATIVE {} {} {} {} {}",i,name,label,enc.len(),ts.len());}}}
'''

def sha(b):return hashlib.sha256(b).hexdigest()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);assert spec['native_only']and spec['native_encoder']
    names=list(dict.fromkeys(['public514']+spec.get('native_encoder_references',[])+[e['name']for e in spec['entries']if not e['control']]))
    assert len(names)<=6;by={e['name']:e for e in spec['entries']};entries=[by[n]for n in names]
    build=Path(os.environ['RUNNER_TEMP'])/'r13-encoder-build';build.mkdir(exist_ok=True);spool=build/'spool';spool.mkdir(exist_ok=True);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-encoder';out.mkdir(parents=True,exist_ok=True)
    upstream=Path(os.environ['DEFLATE_ROOT']);codec=upstream/'validator/measure/src/deflate.rs';token=codec.with_name('token.rs')
    mods=[];cases=[]
    for i,e in enumerate(entries):
        p=ROOT/e['path']/'parse.rs';assert sha(p.read_bytes())==e['hashes']['parse.rs'];mods.append(f'#[path={json.dumps(str(p))}]mod source{i};');cases.append(f'({json.dumps(e["name"])},source{i}::parse)')
    text=HARNESS.replace('TOKEN',json.dumps(str(token))).replace('CODEC',json.dumps(str(codec))).replace('MODULES','\n'.join(mods)).replace('CASES',','.join(cases));source=build/'encoder.rs';source.write_text(text);binary=build/'encoder'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=upstream/'data/benchmark/corpus-stage1';r=subprocess.run([str(binary),str(corpus),str(spool)],capture_output=True,text=True,timeout=240);(out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    fixture=ROOT/'evidence/round13/37845275650/ef32-short-e/gate/round1-public514.jsonl';raw_fixture=[json.loads(v)for v in fixture.read_text().splitlines()];assert raw_fixture[0]['methods']['public514']['source_sha256']==by['public514']['hashes']['parse.rs'];expected={r['file']:r for r in raw_fixture if r['kind']=='file'}
    rows=[]
    for line in r.stdout.splitlines():
        if not line.startswith('ENCODER_NATIVE '):continue
        _,i,name,n,nb,nt=line.split();p=corpus/name;raw=p.read_bytes();enc_path=spool/f'{i}-{n}.deflate';tok_path=spool/f'{i}-{n}.tokens';enc=enc_path.read_bytes();tok=tok_path.read_bytes()
        assert len(enc)==int(nb)and len(tok)==4*int(nt)and zlib.decompress(enc,-15)==raw
        row={'candidate':n,'file':name,'raw_bytes':len(raw),'input_sha256':sha(raw),'output_bytes':int(nb),'tokens':int(nt),'tokens_sha256':sha(tok),'output_sha256':sha(enc)};assert row['input_sha256']==expected[name]['sha256']
        if n=='public514':
            for k in('output_bytes','tokens','tokens_sha256','output_sha256'):assert row[k]==expected[name]['methods']['public514'][k],(name,k)
        rows.append(row);enc_path.unlink();tok_path.unlink()
    assert len(rows)==28*len(names)
    summary=[];parent={r['file']:r for r in rows if r['candidate']=='public514'}
    for n in names:
        rr=[r for r in rows if r['candidate']==n];assert len(rr)==28 and sum(r['raw_bytes']for r in rr)==15930000
        summary.append({'candidate':n,'public_size_pct':statistics.mean(100*r['output_bytes']/r['raw_bytes']for r in rr),'changed_files':[{'file':r['file'],'extra_output_bytes':r['output_bytes']-parent[r['file']]['output_bytes'],'tokens_equal':r['tokens_sha256']==parent[r['file']]['tokens_sha256']}for r in rr if r['tokens_sha256']!=parent[r['file']]['tokens_sha256']or r['output_sha256']!=parent[r['file']]['output_sha256']]})
    record={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES','source_hashes':{e['name']:e['hashes']for e in entries},'codec_sha256':sha(codec.read_bytes()),'token_sha256':sha(token.read_bytes()),'harness_sha256':sha(source.read_bytes()),'rows':rows,'summary':summary,
        'scope':'Actual frozen parse programs, original pinned encoder unmodified;28 parent outputs/tokens exact versus prior official-harness receipts and all outputs independently zlib decoded. One untimed encoding per input. This is public byte screening, not paired time axis, extraction, full gate, private admission or reward.'}
    (out/'encoder.json').write_text(json.dumps(record,indent=2)+'\n');print(json.dumps({'status':record['status'],'summary':summary}))

if __name__=='__main__':main()
