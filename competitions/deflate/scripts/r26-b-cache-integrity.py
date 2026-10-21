"""Runner-only strong-seed equality and complete retained-prefix validity check."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import subprocess

ROOT=Path(__file__).resolve().parents[1]
PARENT='784e02703c98a32f85753cae4f3b62aea3f505d91088869f327e0ad646629c14'
CANDIDATE='bb6bbbf7048bf86a489ed6796208c0c46e929a15b30cf512cc8a49719e98239a'

HARNESS=r'''
#![allow(dead_code)]
#[path=FROZEN]mod frozen;
#[path=CANDIDATE]mod candidate;
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::new();for&t in ts{if t<256{out.push(t as u8);}else{if !(16777216..25165824).contains(&t){return false;}let x=t-16777216;let d=(x/256+1)as usize;let l=(x%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false;}for _ in 0..l{let b=out[out.len()-d];out.push(b);}}}out==s}
fn main(){let mut paths:Vec<_>=std::fs::read_dir(std::env::args().nth(1).unwrap()).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();paths.sort();for path in paths{
 let input=std::fs::read(&path).unwrap();let mut a=vec![0;input.len()];let mut b=vec![0;input.len()];let mut mp=Vec::new();let mut mb=Vec::new();let mut format=2usize;
 let n0=frozen::SFbase(&input,&mut a);let n1=candidate::r26_b_SFbase(&input,&mut b,&mut mp,&mut mb,&mut format);
 assert_eq!(n0,n1);assert_eq!(&a[..n0],&b[..n1],"strongseed {}",path.display());assert!(decode(&input,&b[..n1]));
 let active=frozen::SFenabled(&input)&&input.len()!=40000&&!frozen::EPon(&input);let valid=candidate::r26_b_cache_valid(&input,&mp,&mb,format);
 let mut offers=0usize;let mut prefix_bytes=0usize;
 if active&&valid{assert_eq!(mp.len(),input.len()+1);for p in 0..input.len(){let lo=mp[p]as usize;let hi=mp[p+1]as usize;assert!(lo<=hi&&hi<=mb.len());for raw in &mb[lo..hi]{let(l,d)=candidate::r26_b_offer(*raw,format,input.len()-p);if l>=3&&d<=p{assert!(frozen::Z223(&input,p,l,d),"cached-prefix {} p={} l={} d={}",path.display(),p,l,d);offers+=1;prefix_bytes+=l;}}}}
 println!("R26_CACHE {} {} {} {} {} {} {} {} {} {} {}",path.file_name().unwrap().to_str().unwrap(),input.len(),n0,active as usize,valid as usize,mp.len(),mb.len(),mp.capacity(),mb.capacity(),offers,prefix_bytes);
}}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()


def boundary_model():
    checks=0
    for length in (3,4,7,10,31,32,127,128,257,258):
        for distance in (1,2,3,255,256,257,16383,16384,32767,32768):
            for code in (0,1,15,16,28,29):
                for fmt,raw in ((0,(distance-1)|((length-3)<<15)|(code<<23)),
                                (1,(length<<20)|(code<<15)|(distance-1)),
                                (1,((length+512)<<20)|(code<<15)|(distance-1))):
                    l=3+((raw>>15)&255)if fmt==0 else raw>>20
                    if fmt==1 and l>=512:l-=512
                    d=(raw&32767)+1
                    assert (l,d)==(length,distance)
                    for cap in (0,1,2,3,4,257,258,259):
                        assert min(l,258,cap)==min(length,cap)
                        checks+=1
    return {'status':'VERIFIED_FINITE_BITFIELD_AND_INTERVAL_CLIP_MODEL_ONLY',
            'checks':checks,'scope':'Boundary model only. ActualZ223 prefix and token checks require runner execution; no input validity or fullproof inferred.'}


def preflight(spec):
    assert spec.get('r26_b_cache_integrity') is True
    parent=next(e for e in spec['entries']if e['name']=='public628')
    child=next(e for e in spec['entries']if e['name']=='r26-b-628-shared-cache')
    assert parent['hashes']['parse.rs']==PARENT and child['hashes']['parse.rs']==CANDIDATE
    for entry in (parent,child):assert sha((ROOT/entry['path']/'parse.rs').read_bytes())==entry['hashes']['parse.rs']
    return {'status':'VERIFIED_FROZEN_SPEC_SOURCES_ONLY','parent':parent['hashes'],'candidate':child['hashes'],
            'boundary_model':boundary_model(),
            'scope':'No localRustexecution. Cloud must establish the actual strongseed/prefix identities.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=importlib.import_module('round4').validate(os.environ['ROUND4_SPEC']);preflight(spec)
    parent=next(e for e in spec['entries']if e['name']=='public628')
    child=next(e for e in spec['entries']if e['name']=='r26-b-628-shared-cache')
    build=Path(os.environ['RUNNER_TEMP'])/'r26-b-cache-integrity';build.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-cache-integrity';out.mkdir(parents=True)
    text=HARNESS.replace('FROZEN',json.dumps(str(ROOT/parent['path']/'parse.rs'))).replace('CANDIDATE',json.dumps(str(ROOT/child['path']/'parse.rs')))
    source=build/'driver.rs';source.write_text(text);binary=build/'check'
    c=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(source),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (out/'compile.log').write_text(c.stdout+c.stderr);assert c.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    r=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=480)
    (out/'run.log').write_text(r.stdout+r.stderr);assert r.returncode==0
    fields=['raw_bytes','base_tokens','active_cache_route','valid_cache','offsets','items','offsets_capacity','items_capacity','verified_prefix_offers','verified_prefix_bytes']
    rows=[]
    for line in r.stdout.splitlines():
        if not line.startswith('R26_CACHE '):continue
        _,name,*vals=line.split();assert len(vals)==len(fields)
        data=(corpus/name).read_bytes();row={'file':name,'input_sha256':sha(data),**dict(zip(fields,map(int,vals)))}
        assert len(data)==row['raw_bytes'];rows.append(row)
    assert len(rows)==28 and sum(r['raw_bytes']for r in rows)==15930000
    result={'status':'VERIFIED_REAL_STRONG_SEED_IDENTICAL_AND_ACTIVE_CACHE_PREFIXES_VALID',
            'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
            'parent_hashes':parent['hashes'],'candidate_hashes':child['hashes'],'driver_sha256':sha(source.read_bytes()),
            'rows':rows,'totals':{f:sum(r[f]for r in rows)for f in fields},
            'scope':'Actual all28 original/shared SFbase token arrays agree and decode. Every consumed-prefix-capable offer in an active full cache is individually checked through originalZ223. Helper calls on inactive routes are diagnostics only; fullparse encoder and originaltiming remain separate. No Lean/generalinput equivalence/fullgate or reward claim.'}
    (out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'status':result['status'],'totals':result['totals']}))


if __name__=='__main__':main()
