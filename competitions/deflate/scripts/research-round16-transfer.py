"""Fresh synthetic weak-pattern inputs; original encoder bytes and decode, never a private score."""
from pathlib import Path
import hashlib,json,os,random,subprocess,sys,zlib
from round4 import ROOT,validate

SEED='r16-weak-pattern-transfer-20261009-v1'
KINDS=('source','logs','multilingual','short-fragments','noisy-periods','binary-records')

def sha(b):return hashlib.sha256(b).hexdigest()

def make_input(kind,seed):
    rng=random.Random(int.from_bytes(hashlib.sha256(f'{SEED}:{kind}:{seed}'.encode()).digest(),'big'))
    n=500000 if kind=='binary-records' else 800000
    words=['cedar','stone','field','table','event','cache','value','river','index','delta']
    fragments=[bytes(rng.randrange(32,127)for _ in range(rng.randrange(4,13)))for _ in range(384)]
    out=bytearray();i=0
    while len(out)<n:
        a,b,c=(rng.randrange(10000)for _ in range(3));w=words[a%len(words)]
        if kind=='source':row=f'int fn_{a%127}(int x) {{ /* {w} */ return (x + {b%71}) ^ {c}; }}\n'.encode()
        elif kind=='logs':row=f'2026-10-09T{i%24:02}:{a%60:02}:{b%60:02} host={a%23} event={w} id={i} values={a},{b},{c}\n'.encode()
        elif kind=='multilingual':row=f'记录{i} 山川河流 {w} 数据{a}。日本語と番号{b}。 Русский текст {c}。\n'.encode()
        elif kind=='short-fragments':row=fragments[a%len(fragments)]+fragments[b%len(fragments)]+str(c).encode()+b'\n'
        elif kind=='noisy-periods':
            row=bytearray((f'{w}:{b%19}:sample={a%31}:'.encode())*4)
            row[rng.randrange(len(row))]=rng.randrange(32,127);row=bytes(row)+str(c).encode()+b'\n'
        else:row=b'R16\x00'+i.to_bytes(4,'little')+a.to_bytes(2,'little')+b.to_bytes(2,'little')+c.to_bytes(2,'little')+fragments[a%384]*3+b'\x00'
        out.extend(row);i+=1
    return bytes(out[:n])

HARNESS=r'''
#![allow(dead_code)]
#[path=TOKEN]mod token;
#[path=CODEC]mod codec;
MODULES
type Parser=fn(&[u8],&mut[u32])->usize;
fn decode(s:&[u8],ts:&[u32])->bool{let mut v=Vec::new();for&t in ts{match token::decode(t){token::Token::Literal(x)=>v.push(x),token::Token::Match{dist,len}=>{if dist as usize>v.len()||v.len()+len as usize>s.len(){return false;}for _ in 0..len{let x=v[v.len()-dist as usize];v.push(x);}},_=>return false}}v==s}
fn main(){let args:Vec<_>=std::env::args().collect();let spool=std::path::Path::new(&args[2]);let cases:&[(&str,Parser)]=&[CASES];let mut paths:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();paths.sort();for(i,p)in paths.iter().enumerate(){let s=std::fs::read(p).unwrap();let name=p.file_name().unwrap().to_str().unwrap();let route=source0::route(&s);for &(label,f)in cases{let mut ts=vec![0;s.len()];let n=f(&s,&mut ts);assert!(n<=s.len());ts.truncate(n);assert!(decode(&s,&ts));let enc=codec::encode(&ts,s.len()).unwrap();let mut tok=Vec::new();for&t in&ts{tok.extend(t.to_le_bytes());}std::fs::write(spool.join(format!("{}-{}.tokens",i,label)),tok).unwrap();std::fs::write(spool.join(format!("{}-{}.deflate",i,label)),&enc).unwrap();println!("TRANSFER {} {} {} {} {} {} {}",i,name,label,s.len(),route,n,enc.len());}}}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);names=['r13-514-abs15']+spec['r16_transfer_candidates']
    assert 1<=len(spec['r16_transfer_candidates'])<=2 and len(set(names))==len(names)
    entries={e['name']:e for e in spec['entries']};build=Path(os.environ['RUNNER_TEMP'])/'r16-transfer-build';inputs=build/'inputs';spool=build/'spool';out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r16-transfer'
    for p in(inputs,spool,out):p.mkdir(parents=True,exist_ok=True)
    identities={}
    for kind in KINDS:
        for seed in(0,1):
            name=f'{kind}-{seed}.bin';raw=make_input(kind,seed);(inputs/name).write_bytes(raw);identities[name]={'bytes':len(raw),'sha256':sha(raw)}
    mods=[];cases=[]
    for i,n in enumerate(names):
        p=ROOT/entries[n]['path']/'parse.rs';assert sha(p.read_bytes())==entries[n]['hashes']['parse.rs'];mods.append(f'#[path={json.dumps(str(p))}]mod source{i};');cases.append(f'({json.dumps(n)},source{i}::parse)')
    codec=Path(os.environ['DEFLATE_ROOT'])/'validator/measure/src/deflate.rs';token=codec.with_name('token.rs')
    text=HARNESS.replace('TOKEN',json.dumps(str(token))).replace('CODEC',json.dumps(str(codec))).replace('MODULES','\n'.join(mods)).replace('CASES',','.join(cases))
    source=build/'transfer.rs';source.write_text(text);binary=build/'transfer'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180);(out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    run=subprocess.run([str(binary),str(inputs),str(spool)],capture_output=True,text=True,timeout=360);(out/'run.log').write_text(run.stdout+run.stderr);assert run.returncode==0
    rows=[]
    for line in run.stdout.splitlines():
        if not line.startswith('TRANSFER '):continue
        _,i,file,n,size,route,nt,nb=line.split();enc=(spool/f'{i}-{n}.deflate').read_bytes();tok=(spool/f'{i}-{n}.tokens').read_bytes()
        assert len(enc)==int(nb) and len(tok)==int(nt)*4 and zlib.decompress(enc,-15)==(inputs/file).read_bytes()
        rows.append({'file':file,'candidate':n,'raw_bytes':int(size),'route':int(route),'tokens':int(nt),'output_bytes':int(nb),'output_sha256':sha(enc),'tokens_sha256':sha(tok)})
    assert len(rows)==12*len(names)
    by={(x['file'],x['candidate']):x for x in rows};differences=[]
    for file in identities:
        for n in names[1:]:
            a=by[file,names[0]];b=by[file,n];differences.append({'candidate':n,'file':file,'route':a['route'],'extra_bytes':b['output_bytes']-a['output_bytes'],'size_change_pp':100*(b['output_bytes']-a['output_bytes'])/a['raw_bytes']})
    result={'status':'VERIFIED_SYNTHETIC_ENCODER_AND_DECODE','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'seed':SEED,'python_version':sys.version,'generator_sha256':sha(Path(__file__).read_bytes()),'source_hashes':{n:entries[n]['hashes']for n in names},'harness_sha256':sha(text.encode()),'codec_sha256':sha(codec.read_bytes()),'inputs':identities,'rows':rows,'differences':differences,'scope':'Twelve synthetic contents, frozen generator before paired feedback. Known original activation lengths used without candidate route changes. Byte and decode diagnostic only; no official total timing, held-out data, admission or score guarantee.'}
    (out/'transfer.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'status':result['status'],'differences':differences}))

if __name__=='__main__':main()
