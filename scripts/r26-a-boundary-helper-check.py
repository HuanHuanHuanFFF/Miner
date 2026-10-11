"""Direct Rust helper checks independent of public641's exact-length routing."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import random
import struct
import sys

ROOT=Path(__file__).resolve().parents[1]
MODEL=importlib.import_module('r26-a-build-boundary-log')
UTIL=importlib.import_module('research-round25-len3-price')
OUT=ROOT/'evidence/round26/route-a/boundary-helper'
NAME='r26-a-641-boundary-log'
RUST='8c7e791cc2d3acb483f2f7504538becb76dee5ab3f9fddba18a72fa50cb920d7'


def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())
def pack(ts):return b''.join(struct.pack('<I',t)for t in ts)


def prepare():
    OUT.mkdir(parents=True,exist_ok=True);cases=[]
    def add(label,ts):
        data=MODEL.decode(ts);expected,changed=MODEL.model(ts,data);raw=pack(ts)
        path=OUT/(label+'.tokens');path.write_bytes(raw)
        cases.append({'label':label,'path':path.relative_to(ROOT).as_posix(),'tokens':len(ts),'tokens_sha256':sha(raw),
                      'input_bytes':len(data),'input_sha256':sha(data),'expected_sha256':sha(pack(expected)),
                      'python_changed_pairs':changed})
    for count in [0,1,2,16383,16384,16385,32768]:
        ts=[65]*count
        if count>=8:ts[-2:]=[MODEL.token(19,1),MODEL.token(3,1)]
        add('count-'+str(count),ts)
    for seed in range(32):
        rng=random.Random(seed);ts=list(b'ABCDXYZABCDABCDXYZABCD');produced=len(ts)
        for _ in range(1024):
            if rng.randrange(4)==0:ts.append(rng.randrange(65,73));produced+=1
            else:
                l=rng.choice([3,4,5,6,7,8,9,10,11,12,13,18,19,22,34,35,66,67,130,131,194,195,226,227,257,258])
                d=rng.randrange(1,min(produced,32768)+1);ts.append(MODEL.token(l,d));produced+=l
        add('seed-'+str(seed),ts)
    add('maximum-distance',list(b'ABCD'*8192)+[MODEL.token(258,32768),MODEL.token(4,32768),MODEL.token(258,1)])
    for stem,before in [('inside-block',16382),('cross-block',16383)]:
        ts=[65]*8+[MODEL.token(5,1)]*100
        ts += [65]*(before-len(ts))
        ts += [MODEL.token(20,1),MODEL.token(4,1)]
        add(stem,ts)
    by={c['label']:c for c in cases}
    assert by['inside-block']['python_changed_pairs']==1 and by['cross-block']['python_changed_pairs']==0
    result={'status':'VERIFIED_FIXED_DIRECT_HELPER_FIXTURES_PYTHON_ONLY','candidate':NAME,'rust_sha256':RUST,
            'model_script_sha256':sha((ROOT/'scripts/r26-a-build-boundary-log.py').read_bytes()),'cases':cases,
            'coverage_note':'The regular444parser check has416synthetic lengths outsidepublic641PCroutes. These42directhelpercases bypass routing and check actualchangedtoken semantics,16384boundary and maximumdistance explicitly.'}
    dump(OUT/'fixture.json',result);print(json.dumps({'cases':len(cases),'changed_pairs':sum(c['python_changed_pairs']for c in cases),'inside_vs_cross':[by[x]['python_changed_pairs']for x in ['inside-block','cross-block']]},indent=2))


def preflight(spec=None):
    fixture=json.loads((OUT/'fixture.json').read_bytes());assert fixture['candidate']==NAME and fixture['rust_sha256']==RUST
    assert sha((ROOT/'candidates'/NAME/'parse.rs').read_bytes())==RUST
    assert sha((ROOT/'scripts/r26-a-build-boundary-log.py').read_bytes())==fixture['model_script_sha256']
    assert len(fixture['cases'])==42
    for case in fixture['cases']:
        raw=(ROOT/case['path']).read_bytes();assert sha(raw)==case['tokens_sha256'] and len(raw)==4*case['tokens']
        ts=[x[0]for x in struct.iter_unpack('<I',raw)];data=MODEL.decode(ts);changed,n=MODEL.model(ts,data)
        assert sha(data)==case['input_sha256'] and len(data)==case['input_bytes']
        assert sha(pack(changed))==case['expected_sha256'] and n==case['python_changed_pairs']
    if spec is not None:
        assert spec.get('r26_a_boundary_helper_check') is True
        entry=next(e for e in spec['entries']if e['name']==NAME)
        assert entry['hashes']['parse.rs']==RUST
    return fixture


HARNESS=r'''
#![allow(dead_code)]
#[path=SOURCE]mod candidate;
fn decode(ts:&[u32])->Vec<u8>{let mut data=Vec::new();for&t in ts{if t<256{data.push(t as u8);}else{assert!((16777216..25165824).contains(&t));let v=t-16777216;let l=(v%256+3)as usize;let d=(v/256+1)as usize;assert!(d<=data.len());for _ in 0..l{let x=data[data.len()-d];data.push(x);}}}data}
fn main(){let args:Vec<_>=std::env::args().collect();let root=std::path::Path::new(&args[1]);let spool=std::path::Path::new(&args[2]);let cases:&[(&str,&str)]=&[CASES];
for&(label,path)in cases{let raw=std::fs::read(root.join(path)).unwrap();let ts:Vec<_>=raw.chunks_exact(4).map(|v|u32::from_le_bytes(v.try_into().unwrap())).collect();assert_eq!(raw.len(),4*ts.len());let data=decode(&ts);let mut out=vec![0;data.len()];out[..ts.len()].copy_from_slice(&ts);let nt=candidate::r26_bl_finish(&data,&mut out,ts.len());assert_eq!(nt,ts.len());out.truncate(nt);assert_eq!(decode(&out),data);let mut changed=Vec::new();for&t in&out{changed.extend(t.to_le_bytes());}std::fs::write(spool.join(format!("{}.tokens",label)),changed).unwrap();println!("R26_HELPER {} {} {}",label,nt,data.len());}}
'''


def run():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    from round4 import validate
    spec=validate(os.environ['ROUND4_SPEC']);fixture=preflight(spec)
    build=Path(os.environ['RUNNER_TEMP'])/'r26-a-helper-build';build.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-boundary-helper';out.mkdir(parents=True)
    spool=build/'spool';spool.mkdir()
    cases=','.join('('+json.dumps(c['label'])+','+json.dumps(c['path'])+')'for c in fixture['cases'])
    harness=HARNESS.replace('SOURCE',json.dumps(str(ROOT/'candidates'/NAME/'parse.rs'))).replace('CASES',cases)
    driver=build/'main.rs';driver.write_text(harness);(out/'harness.rs').write_text(harness)
    result={'status':'STARTED_DIRECT_RUST_HELPER_CHECK','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],
            'batch':os.environ['ROUND4_SPEC'],'rust_sha256':RUST,'fixture_sha256':sha((OUT/'fixture.json').read_bytes()),'harness_sha256':sha(harness.encode()),
            'scope':'Directhelper checks bypass parser routing. ExactPythonmodel tokens and independent Rustdecode; not all-input proof or performance.'}
    report=out/'receipt.json';dump(report,result)
    try:
        binary=build/'check'
        UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
        process=UTIL.captured([str(binary),str(ROOT),str(spool)],out/'run.log',240)
        lines=[l for l in process.stdout.splitlines()if l.startswith('R26_HELPER ')];assert len(lines)==42
        checked=[]
        for case in fixture['cases']:
            raw=(spool/(case['label']+'.tokens')).read_bytes();ts=[x[0]for x in struct.iter_unpack('<I',raw)]
            assert sha(raw)==case['expected_sha256'] and len(ts)==case['tokens']
            assert sha(MODEL.decode(ts))==case['input_sha256']
            checked.append({**case,'actual_sha256':sha(raw),'matched_python_model':True,'decoded':True})
        result.update(status='VERIFIED_DIRECT_RUST_HELPER_42_EXACT_MODEL_AND_DECODE',cases=checked)
    except Exception as exc:
        result.update(status='FAILED_OR_INCOMPLETE_DIRECT_HELPER',error_type=type(exc).__name__,error=str(exc));dump(report,result);raise
    dump(report,result);print(json.dumps({'status':result['status'],'cases':len(checked)},indent=2))


if __name__=='__main__':
    if sys.argv[1:]==['--prepare']:prepare()
    elif sys.argv[1:]==['--self-check']:
        fixture=preflight();print(json.dumps({'status':'VERIFIED_DIRECT_HELPER_FIXTURE_PREFLIGHT','cases':len(fixture['cases'])}))
    else:run()
