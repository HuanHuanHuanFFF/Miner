"""Untimed exact-encoder EF32 price replay; no new parser or timing claim."""
from pathlib import Path
import hashlib,json,os,subprocess,zlib
from round4 import ROOT,validate

FIELDS=['length3_matches','known_literal_prices','match_cheaper','literal_cheaper','equal_price',
        'missing_literal_price','known_match_savings_bits','known_match_loss_bits']+[f'distance_code_{i}'for i in range(30)]+['dynamic_blocks','fixed_blocks']

APPEND=r'''
// R13 diagnostic appended to an isolated copy. The original encode path above
// remains byte-identical and is differentially checked against the pinned file.
fn r13_tables(b:&Block)->(Vec<u8>,Vec<u8>,bool){
    let mut lf=b.litlen_freq;lf[END_OF_BLOCK]+=1;
    let mut ll=package_merge(&lf,MAX_BITS_LITLEN);
    let mut dl=package_merge(&b.dist_freq,MAX_BITS_LITLEN);
    if dl.iter().all(|&x|x==0){dl[0]=1;}
    let mut hlit=NUM_LITLEN;while hlit>257&&ll[hlit-1]==0{hlit-=1;}
    let mut hdist=NUM_DIST;while hdist>1&&dl[hdist-1]==0{hdist-=1;}
    ll.truncate(hlit.max(257));ll.resize(NUM_LITLEN,0);
    let mut all=Vec::new();all.extend_from_slice(&ll[..hlit]);all.extend_from_slice(&dl[..hdist]);
    let rle=rle_lengths(&all);let mut clf=[0u32;NUM_CODELEN];
    for &(sym,_,_)in&rle{clf[sym as usize]+=1;}
    let cl=package_merge(&clf,MAX_BITS_CODELEN);
    if b.fixed_cost()<=b.dynamic_cost(&ll,&dl,&cl,&rle){let(a,d)=fixed_tables();(a.to_vec(),d.to_vec(),false)}else{(ll,dl,true)}
}
pub fn r13_rewrite(ts:&[u32],input:&[u8],policy:usize)->(Vec<u32>,[u64;40]){
    let mut out=Vec::new();let mut counts=[0u64;40];let mut pos=0usize;
    for chunk in ts.chunks(BLOCK_TOKENS){
        let mut b=Block::new();
        for&t in chunk{match token::decode(t){token::Token::Literal(x)=>b.push_literal(x),token::Token::Match{dist,len}=>b.push_match(dist,len),_=>panic!("invalid original token")}}
        let(ll,dl,dynamic)=r13_tables(&b);counts[if dynamic{38}else{39}]+=1;
        for&t in chunk{match token::decode(t){
            token::Token::Literal(_)=>{out.push(t);pos+=1;},
            token::Token::Match{dist,len}=>{
                let mut replace=false;
                if len==3{
                    counts[0]+=1;let(dc,extra,_)=dist_code(dist);counts[8+dc]+=1;
                    let known=input[pos..pos+3].iter().all(|&x|ll[x as usize]>0);
                    let mc=ll[257]as u32+dl[dc]as u32+extra;
                    let lc=input[pos..pos+3].iter().map(|&x|ll[x as usize]as u32).sum::<u32>();
                    if known{
                        counts[1]+=1;
                        if mc<lc{counts[2]+=1;counts[6]+=(lc-mc)as u64;}
                        else if mc>lc{counts[3]+=1;counts[7]+=(mc-lc)as u64;}else{counts[4]+=1;}
                    }else{counts[5]+=1;}
                    replace=match policy{
                        0=>known&&mc>lc,
                        1=>known&&mc>=lc+2,
                        2=>dist>32,3=>dist>128,4=>dist>512,5=>dist>2048,
                        _=>panic!("unknown diagnostic policy")
                    };
                }
                if replace{out.extend(input[pos..pos+3].iter().map(|&x|x as u32));}else{out.push(t);}
                pos+=len as usize;
            },_=>panic!("invalid original token")
        }}
    }
    assert_eq!(pos,input.len());(out,counts)
}
'''

HARNESS=r'''
#![allow(dead_code)]
#[path="PARSER"]mod frozen;
#[path="TOKEN"]mod token;
#[path="TRUSTED"]mod trusted;
#[path="OBSERVED"]mod observed;
fn parse(s:&[u8])->Vec<u32>{let mut v=vec![0;s.len()];let n=frozen::parse(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32]){let mut v=Vec::new();for&t in ts{match token::decode(t){token::Token::Literal(x)=>v.push(x),token::Token::Match{dist,len}=>{assert!(dist as usize<=v.len());for _ in 0..len{let x=v[v.len()-dist as usize];v.push(x);}},_=>panic!("bad token")}}assert_eq!(v,s);}
fn save(dir:&std::path::Path,i:usize,name:&str,label:&str,ts:&[u32],encoded:&[u8],counts:&[u64;40]){
    let prefix=format!("{}-{}",i,label);let mut raw=Vec::new();for&t in ts{raw.extend(t.to_le_bytes());}
    std::fs::write(dir.join(format!("{}.tokens",prefix)),raw).unwrap();
    std::fs::write(dir.join(format!("{}.deflate",prefix)),encoded).unwrap();
    print!("R13_PRICE {} {} {} {} {}",i,name,label,encoded.len(),ts.len());for x in counts{print!(" {}",x);}println!();
}
fn main(){
    let args:Vec<_>=std::env::args().collect();let dir=std::path::Path::new(&args[2]);
    let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
    for(i,p)in files.iter().enumerate(){let s=std::fs::read(p).unwrap();let name=p.file_name().unwrap().to_str().unwrap();let ts=parse(&s);decode(&s,&ts);
        let enc=trusted::encode(&ts,s.len()).unwrap();assert_eq!(enc,observed::encode(&ts,s.len()).unwrap());
        save(dir,i,name,"parent",&ts,&enc,&[0;40]);
        if name=="weights-f32.bin"{for(policy,label)in ["price0","price2","d32","d128","d512","d2048"].iter().enumerate(){
            let(alt,counts)=observed::r13_rewrite(&ts,&s,policy);decode(&s,&alt);let encoded=trusted::encode(&alt,s.len()).unwrap();
            save(dir,i,name,label,&alt,&encoded,&counts);
        }}
    }
}
'''

def sha(b):return hashlib.sha256(b).hexdigest()

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);assert spec['native_only']
    entry=next(e for e in spec['entries']if e['name']=='public514');frozen=ROOT/entry['path']/'parse.rs';assert sha(frozen.read_bytes())==entry['hashes']['parse.rs']
    upstream=Path(os.environ['DEFLATE_ROOT']);trusted=upstream/'validator/measure/src/deflate.rs';token=trusted.with_name('token.rs')
    build=Path(os.environ['RUNNER_TEMP'])/'r13-price-build';build.mkdir(exist_ok=True);spool=build/'spool';spool.mkdir(exist_ok=True)
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-price';out.mkdir(parents=True,exist_ok=True)
    observed=build/'observed.rs';observed.write_bytes(trusted.read_bytes()+APPEND.encode())
    source=build/'price.rs';text=HARNESS
    for old,new in [('PARSER',frozen),('TOKEN',token),('TRUSTED',trusted),('OBSERVED',observed)]:text=text.replace(old,str(new))
    source.write_text(text);binary=build/'price'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=180)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=upstream/'data/benchmark/corpus-stage1'
    r=subprocess.run([str(binary),str(corpus),str(spool)],capture_output=True,text=True,timeout=180);(out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    fixture=ROOT/'evidence/round13/37845275650/ef32-short-e/gate/round1-public514.jsonl'
    original=[json.loads(v)for v in fixture.read_text().splitlines()];assert original[0]['methods']['public514']['source_sha256']==entry['hashes']['parse.rs']
    expected={x['file']:x for x in original if x['kind']=='file'};rows=[]
    for line in r.stdout.splitlines():
        if not line.startswith('R13_PRICE '):continue
        _,index,name,label,n,nt,*values=line.split();assert len(values)==len(FIELDS)
        compressed=spool/f'{index}-{label}.deflate';tokens=spool/f'{index}-{label}.tokens';enc=compressed.read_bytes();tok=tokens.read_bytes();raw=(corpus/name).read_bytes()
        assert len(enc)==int(n)and len(tok)==int(nt)*4 and zlib.decompress(enc,-15)==raw
        row={'file':name,'policy':label,'raw_bytes':len(raw),'input_sha256':sha(raw),'output_bytes':int(n),'tokens':int(nt),'output_sha256':sha(enc),'tokens_sha256':sha(tok),'counts':dict(zip(FIELDS,map(int,values)))}
        assert row['input_sha256']==expected[name]['sha256']
        if label=='parent':
            for key in('output_bytes','tokens','output_sha256','tokens_sha256'):assert row[key]==expected[name]['methods']['public514'][key],(name,key)
        rows.append(row);compressed.unlink();tokens.unlink()
    assert len(rows)==34 and len([r for r in rows if r['policy']=='parent'])==28
    parent=next(r for r in rows if r['policy']=='parent'and r['file']=='weights-f32.bin')
    alternatives=[{**row,'extra_output_bytes_vs_parent':row['output_bytes']-parent['output_bytes']}for row in rows if row['policy']!='parent']
    result={'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
        'status':'VERIFIED_UNTIMED_PINNED_ENCODER_REPLAY','parent_source_sha256':entry['hashes']['parse.rs'],'codec_sha256':sha(trusted.read_bytes()),'token_sha256':sha(token.read_bytes()),'observer_sha256':sha(observed.read_bytes()),'harness_sha256':sha(source.read_bytes()),
        'scope':'Pinned original encoder unchanged. Parent outputs/tokens match28 formal-harness public receipts exactly; independent zlib roundtrip also checked. Alternatives edit captured EF32 tokens, not a new parse program. No timing, extraction, original obligation, formal admission or reward.',
        'price_limits':'Parent block tables guide price0/2; transformed token boundaries and tables are recomputed by exact encoder. Parent price improvement is not a monotonic final size guarantee or runtime-free policy.',
        'rows':rows,'alternatives':alternatives}
    (out/'price.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({'status':result['status'],'alternatives':[(r['policy'],r['extra_output_bytes_vs_parent'])for r in alternatives]}))

if __name__=='__main__':main()
