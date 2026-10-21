"""Fresh synthetic content at activation sizes; encoder bytes, not a private score."""
from pathlib import Path
import hashlib, json, os, random, subprocess, sys, zlib
from round4 import ROOT, validate

SEED = 'r15-frozen-base-active-transfer-20261009-v1'
CASES = [('source-like.txt',1300000),('records.json.txt',1100000),('markup.xml.txt',1400000),('multilingual.txt',250000),('structured.bin',500000),('wide.csv.txt',1000000)]

def sha(raw): return hashlib.sha256(raw).hexdigest()

def make_input(name, cap):
    rng = random.Random(int.from_bytes(hashlib.sha256((SEED+':'+name).encode()).digest(), 'big'))
    out = bytearray(); i = 0
    words = ['amber','river','index','cache','green','window','sample','branch','signal','forest','silver','target']
    while len(out) < cap:
        a,b,c = (rng.randrange(1024) for _ in range(3)); word = words[rng.randrange(len(words))]
        if name == 'source-like.txt':
            row = f'/* block {i%71}: {word} */\nint routine_{a%97}(int x) {{ int v = (x + {b}) ^ {c}; if (v > {a}) return v + {b%31}; return x - {c%17}; }}\n'
        elif name == 'records.json.txt':
            row = json.dumps({'id':i,'group':a%83,'status':word,'values':[a,b,c],'message':f'{word} record group {b%29} value {a%127}'}, separators=(',',':'))+'\n'
        elif name == 'markup.xml.txt':
            row = f'<item id="{i}" type="{word}" group="{a%83}"><name>{word}-{b%67}</name><value>{c}</value><note>entry {b%17} carries {word} sequence {a%31}</note></item>\n'
        elif name == 'multilingual.txt':
            row = f'记录{i}：山川与河流，窗口{a%71}，数据{b}。 日本語の文章と観測番号{c}。 Русский текст {word} и пример {a}.\n'
        elif name == 'wide.csv.txt':
            row = ','.join(f'{words[(j+a)%len(words)]}:{rng.randrange(100000)}' for j in range(120))+'\n'
        else:
            row = b'R15\x00'+i.to_bytes(4,'little')+a.to_bytes(2,'little')+b.to_bytes(2,'little')+c.to_bytes(2,'little')+(word.encode()+b'\x00')*4+bytes(rng.randrange(256) for _ in range(7))
        out.extend(row.encode() if isinstance(row,str) else row); i += 1
    return bytes(out[:cap])

HARNESS = r'''
#![allow(dead_code)]
#[path=PARENT]mod parent;
#[path=CANDIDATE]mod candidate;
#[path=TOKEN]mod token;
#[path=CODEC]mod codec;
fn decode(s:&[u8],ts:&[u32])->bool{let mut v=Vec::new();for&t in ts{match token::decode(t){token::Token::Literal(x)=>v.push(x),token::Token::Match{dist,len}=>{if dist as usize>v.len()||v.len()+len as usize>s.len(){return false;}for _ in 0..len{let x=v[v.len()-dist as usize];v.push(x);}},_=>return false}}v==s}
fn main(){let args:Vec<_>=std::env::args().collect();let root=std::path::Path::new(&args[1]);let spool=std::path::Path::new(&args[2]);let parsers:[(&str,fn(&[u8],&mut[u32])->usize);2]=[("public550",parent::parse),("r15-550-base-only",candidate::parse)];let mut paths:Vec<_>=std::fs::read_dir(root).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();paths.sort();for(i,p)in paths.iter().enumerate(){let s=std::fs::read(p).unwrap();let name=p.file_name().unwrap().to_str().unwrap();let enabled=parent::SFenabled(&s);for &(label,f)in &parsers{let mut ts=vec![0;s.len()];let nt=f(&s,&mut ts);assert!(nt<=s.len());ts.truncate(nt);assert!(decode(&s,&ts));let enc=codec::encode(&ts,s.len()).unwrap();let mut tok=Vec::new();for&t in &ts{tok.extend(t.to_le_bytes());}std::fs::write(spool.join(format!("{}-{}.tokens",i,label)),&tok).unwrap();std::fs::write(spool.join(format!("{}-{}.deflate",i,label)),&enc).unwrap();println!("TRANSFER {} {} {} {} {} {} {}",i,name,label,s.len(),enabled,nt,enc.len());}}}
'''

def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = validate(os.environ['ROUND4_SPEC']); entries = {e['name']:e for e in spec['entries']}
    names = ['public550','r15-550-base-only']
    build = Path(os.environ['RUNNER_TEMP'])/'r15-transfer-build'; data = build/'inputs'; spool = build/'spool'
    out = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r15-transfer'
    for p in (data,spool,out): p.mkdir(parents=True,exist_ok=True)
    inputs = {}
    for name,cap in CASES:
        raw = make_input(name,cap); assert len(raw) == cap
        (data/name).write_bytes(raw); inputs[name] = {'bytes':len(raw),'sha256':sha(raw)}
    paths = {n:ROOT/entries[n]['path']/'parse.rs' for n in names}
    assert all(sha(paths[n].read_bytes()) == entries[n]['hashes']['parse.rs'] for n in names)
    codec = Path(os.environ['DEFLATE_ROOT'])/'validator/measure/src/deflate.rs'; token = codec.with_name('token.rs')
    text = HARNESS
    for k,v in {'PARENT':paths[names[0]],'CANDIDATE':paths[names[1]],'TOKEN':token,'CODEC':codec}.items(): text = text.replace(k,json.dumps(str(v)))
    source = build/'transfer.rs'; source.write_text(text); binary = build/'transfer'
    c = subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (out/'compile.log').write_text(c.stdout+c.stderr); assert c.returncode == 0
    r = subprocess.run([str(binary),str(data),str(spool)],capture_output=True,text=True,timeout=360)
    (out/'run.log').write_text(r.stdout+r.stderr); assert r.returncode == 0
    rows = []
    for line in r.stdout.splitlines():
        if not line.startswith('TRANSFER '): continue
        _,i,name,label,size,enabled,nt,nb = line.split(); enc=(spool/f'{i}-{label}.deflate').read_bytes(); tok=(spool/f'{i}-{label}.tokens').read_bytes()
        assert len(enc)==int(nb) and len(tok)==4*int(nt) and zlib.decompress(enc,-15)==(data/name).read_bytes()
        rows.append({'file':name,'candidate':label,'raw_bytes':int(size),'shape_enabled':enabled=='true','output_bytes':int(nb),'tokens':int(nt),'output_sha256':sha(enc),'tokens_sha256':sha(tok)})
    assert len(rows)==2*len(CASES)
    by={(r['file'],r['candidate']):r for r in rows}; differences=[]
    for name,_ in CASES:
        p=by[name,names[0]];c=by[name,names[1]]
        differences.append({'file':name,'shape_enabled':p['shape_enabled'],'extra_bytes':c['output_bytes']-p['output_bytes'],'size_change_pp':100*(c['output_bytes']-p['output_bytes'])/p['raw_bytes']})
    assert sum(r['shape_enabled'] for r in differences)>=3
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'status':'VERIFIED_FRESH_SYNTHETIC_ACTIVE_PATH_ENCODER_AND_DECODE','source_hashes':{n:entries[n]['hashes'] for n in names},'seed':SEED,'python_version':sys.version,'generator_sha256':sha(Path(__file__).read_bytes()),'harness_sha256':sha(text.encode()),'codec_sha256':sha(codec.read_bytes()),'token_sha256':sha(token.read_bytes()),'inputs':inputs,'rows':rows,'differences':differences,'scope':'Six new synthetic contents generated after candidate freezing, using known activation sizes. All encodings independently decoded. No timings, private-stage2 bytes, seeds or score calibration. This does not certify private transfer or replace the full gate.'}
    (out/'transfer.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'status':result['status'],'differences':differences}))

if __name__=='__main__':main()
