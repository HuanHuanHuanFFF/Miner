"""Runner-only finite token/decode checks and operation counts for the R11 fast probes.

Enable with spec.fast_diagnostics=true (or a list of candidate names). No timers:
the frozen candidates are measured separately by the official paired benchmark.
"""
from pathlib import Path
import argparse
import hashlib
import json
import os
import subprocess
import sys

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
from round4 import validate

FIELDS={
    'r11-fast-pendingfold':['calls','pending_nonempty','pending_consumed','budget_exhausted','length_cap','reach_old_tokens'],
    'r11-fast-continuation':['calls','full_boundary','old_invalid','repeat_key_checks','replaced'],
}


def sha(b):return hashlib.sha256(b).hexdigest()


def instrument(name,raw):
    text=raw.decode();start=text.index('pub fn r11_');end=text.index('\n#[inline(always)]\npub fn run1',start)
    helper=text[start:end]
    if name=='r11-fast-pendingfold':
        edits=[
            ('    if ls < p0 && p0 <= input.len() && l0 <= 258 {','    r11_fast_hit(0, 1);\n    if ls < p0 && p0 <= input.len() && l0 <= 258 {\n        r11_fast_hit(1, 1);'),
            ('                back += 1;','                back += 1;\n                r11_fast_hit(2, 1);'),
            ('        let nt = flush4(input, out, nt0, ls, p);','        r11_fast_hit(3, (back == BACKTOK) as u64);\n        r11_fast_hit(4, (l == 258) as u64);\n        let nt = flush4(input, out, nt0, ls, p);'),
            ('        if p == ls && back < BACKTOK {','        if p == ls && back < BACKTOK {\n            r11_fast_hit(5, 1);'),
        ]
    else:
        assert name=='r11-fast-continuation'
        edits=[
            ('    if span == 258 && p < lim && p <= s.len().saturating_sub(8) {','    r11_fast_hit(0, 1);\n    if span == 258 && p < lim && p <= s.len().saturating_sub(8) {\n        r11_fast_hit(1, 1);'),
            ('        if !(old_d.wrapping_sub(1) < 32768 && (((cw ^ pw) >> 32) & (km as u64)) == 0) {','        if !(old_d.wrapping_sub(1) < 32768 && (((cw ^ pw) >> 32) & (km as u64)) == 0) {\n            r11_fast_hit(2, 1);'),
            ('                let rc = p - d;','                r11_fast_hit(3, 1);\n                let rc = p - d;'),
            ('                    return (a, rc, rw);','                    r11_fast_hit(4, 1);\n                    return (a, rc, rw);'),
        ]
    for old,new in edits:
        assert helper.count(old)==1,(name,old)
        helper=helper.replace(old,new,1)
    added='''
use std::sync::atomic::{AtomicU64, Ordering};
static R11_FAST_COUNTERS: [AtomicU64; 6] = [const {AtomicU64::new(0)}; 6];
#[inline(always)] fn r11_fast_hit(i:usize,v:u64){R11_FAST_COUNTERS[i].fetch_add(v,Ordering::Relaxed);}
pub fn r11_fast_take()->[u64;6]{std::array::from_fn(|i|R11_FAST_COUNTERS[i].swap(0,Ordering::Relaxed))}
'''
    return (text[:start]+helper+text[end:]+added).encode()


HARNESS=r'''
#![allow(dead_code,unused_mut)]
MODULES
type Parser=fn(&[u8],&mut[u32])->usize;
type Counter=fn()->[u64;6];
fn tokens(s:&[u8],f:Parser)->Vec<u32>{let mut v=vec![0;s.len()+16];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],t:&[u32])->bool{let mut out=Vec::new();for &x in t{if x<256{out.push(x as u8)}else{if !(16777216..25165824).contains(&x){return false}let v=x-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||l>258||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn sample(n:usize,mode:usize,mut z:u64)->Vec<u8>{let text=b"The quick brown fox, record 0123456789; fn result(value) { return value + 1; }\n";let prose=b"the quick brown fox walks through the garden and returns home ";let structured=b"2026-10-07,10002345,1234.55,region=002,code=200\n";let mut v=Vec::with_capacity(n);for i in 0..n{z^=z<<13;z^=z>>7;z^=z<<17;v.push(match mode{0=>(z>>24)as u8,1=>text[i%text.len()],2=>if z%79==0{(z%95+32)as u8}else{text[i%text.len()]},3=>if i%2==0{0xbf}else{z as u8},4=>if z%31==0{z as u8}else{0},5=>b"ACGT\n"[(z%5)as usize],6=>prose[i%prose.len()],_=>structured[i%structured.len()]})}if mode==0&&n>65536{for d in [16383,16384,16385,32767,32768,32769]{for j in 0..257{if 1024+d+j<n{v[1024+d+j]=v[1024+j]}}}}v}
fn check(label:&str,s:&[u8],parsers:&[(&str,Parser,Parser,Counter)],bad:&mut usize){let rt=tokens(s,reference::parse);let rd=decode(s,&rt);assert!(rd);for &(name,f,inst,take) in parsers{take();let ft=tokens(s,f);let it=tokens(s,inst);let ct=take();let fe=ft==rt;let ie=ft==it;let dec=decode(s,&ft)&&decode(s,&it);println!("FAST_CASE {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}",name,label,s.len(),rt.len(),ft.len(),fe as u8,ie as u8,dec as u8,ct[0],ct[1],ct[2],ct[3],ct[4],ct[5],rd as u8);if !ie||!dec||(name=="r11-fast-pendingfold"&&!fe){*bad+=1;}}}
fn main(){let parsers:&[(&str,Parser,Parser,Counter)]=&[CASES];let arg=std::env::args().nth(1).unwrap();let mut paths:Vec<_>=std::fs::read_dir(arg).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();paths.sort();let mut bad=0;for(i,p)in paths.iter().enumerate(){let s=std::fs::read(p).unwrap();check(&format!("public-{}",i),&s,parsers,&mut bad)}for n in [0,1,3,4,7,8,15,16,17,31,32,257,258,259,1023,16383,16384,16385,32767,32768,32769,65535,65536,65537,98305,131073]{for mode in 0..8{for seed in [1,987654321]{let s=sample(n,mode,seed);check(&format!("synthetic-{}-{}-{}",n,mode,seed),&s,parsers,&mut bad)}}}assert_eq!(bad,0,"finite native comparison/decode failed");}
'''


def save(path,obj):path.write_text(json.dumps(obj,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--self-check',action='store_true');args=ap.parse_args()
    if args.self_check:
        for name in FIELDS:
            raw=(ROOT/'candidates'/name/'parse.rs').read_bytes();modified=instrument(name,raw)
            print(name,sha(raw),sha(modified),len(modified))
        assert HARNESS.count('MODULES')==1 and HARNESS.count('CASES')==1
        return
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);requested=spec.get('fast_diagnostics')
    if not requested:
        print('fast diagnostics not requested');return
    names=list(FIELDS) if requested is True else list(requested)
    entries={e['name']:e for e in spec['entries']};assert all(n in entries and n in FIELDS for n in names)
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/fast-diagnostics';out.mkdir(parents=True,exist_ok=True)
    build=Path(os.environ['RUNNER_TEMP'])/'round11-fast-build';build.mkdir(parents=True,exist_ok=True)
    base=ROOT/'candidates/r3-432-fast3/parse.rs'
    assert sha(base.read_bytes())=='bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef'
    modules=[f'#[path={json.dumps(str(base))}] mod reference;'];cases=[];sources={}
    for i,name in enumerate(names):
        path=ROOT/entries[name]['path']/'parse.rs';raw=path.read_bytes();assert sha(raw)==entries[name]['hashes']['parse.rs']
        altered=instrument(name,raw);ip=build/(name+'-instrumented.rs');ip.write_bytes(altered)
        modules.extend([f'#[path={json.dumps(str(path))}] mod frozen{i};',f'#[path={json.dumps(str(ip))}] mod instrumented{i};'])
        cases.append(f'({json.dumps(name)},frozen{i}::parse,instrumented{i}::parse,instrumented{i}::r11_fast_take)')
        sources[name]={'frozen_source_sha256':sha(raw),'instrumented_source_sha256':sha(altered),'counter_fields':FIELDS[name]}
    harness=HARNESS.replace('MODULES','\n'.join(modules)).replace('CASES',','.join(cases));hs=build/'fast.rs';hs.write_text(harness,encoding='utf-8');binary=build/'fast'
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';files=sorted(p for p in corpus.iterdir() if p.is_file())
    result={'status':'STARTED','run_id':os.environ.get('GITHUB_RUN_ID'),'git_sha':os.environ.get('GITHUB_SHA'),'batch':spec.get('batch',spec.get('name',os.environ.get('ROUND4_SPEC'))),'sources':sources,'harness_sha256':sha(harness.encode()),'corpus':[{'file':p.name,'bytes':p.stat().st_size,'sha256':sha(p.read_bytes())}for p in files],'scope':'Finite native full-parser token/decode checks; operation counters only, no timing claims. Frozen/instrumented equality is checked for each input.','files':[],'limits':{'compile_timeout_s':180,'run_timeout_s':240}}
    save(out/'fast.json',result)
    try:
        cp=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(hs),'-o',str(binary)],capture_output=True,text=True,timeout=180)
        (out/'compile.log').write_text(cp.stdout+cp.stderr,encoding='utf-8');result['compile_exit']=cp.returncode
        if cp.returncode:
            result['status']='COMPILE_FAILED';save(out/'fast.json',result);raise SystemExit('fast diagnostic compile failed')
        rp=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=240)
        (out/'run.log').write_text(rp.stdout+rp.stderr,encoding='utf-8');result['run_exit']=rp.returncode
        for line in rp.stdout.splitlines():
            if not line.startswith('FAST_CASE '):continue
            z=line.split();name,label=z[1:3];v=list(map(int,z[3:]));assert len(v)==13,(line,v)
            row={'candidate':name,'case':label,'bytes':v[0],'reference_tokens':v[1],'candidate_tokens':v[2],'equals_reference':bool(v[3]),'frozen_instrumented_equal':bool(v[4]),'decoded':bool(v[5]),'reference_decoded':bool(v[12]),'counts':dict(zip(FIELDS[name],v[6:12]))}
            if label.startswith('public-'):
                p=files[int(label.split('-')[1])];row.update(file=p.name,input_sha256=sha(p.read_bytes()))
            result['files'].append(row)
        result['summary']={};incomplete=[]
        for name in names:
            rows=[r for r in result['files'] if r['candidate']==name];pub=[r for r in rows if r['case'].startswith('public-')]
            result['summary'][name]={'cases':len(rows),'public_cases':len(pub),'token_changed_cases':sum(not r['equals_reference'] for r in rows),'public_token_changed_files':[r['file'] for r in pub if not r['equals_reference']],'all_frozen_instrumented_equal':all(r['frozen_instrumented_equal'] for r in rows),'all_decoded':all(r['decoded'] and r['reference_decoded'] for r in rows),'public_counts':{k:sum(r['counts'][k] for r in pub)for k in FIELDS[name]},'all_counts':{k:sum(r['counts'][k] for r in rows)for k in FIELDS[name]}}
            if len(rows)!=len(files)+416:
                incomplete.append({'candidate':name,'expected_cases':len(files)+416,'observed_cases':len(rows)})
        result['incomplete_cases']=incomplete
        result['status']='VERIFIED_FINITE_NATIVE_CHECKS' if rp.returncode==0 and not incomplete else 'NATIVE_CHECK_FAILED';save(out/'fast.json',result)
        if rp.returncode or incomplete:raise SystemExit('fast diagnostic native check failed or incomplete')
    except subprocess.TimeoutExpired as exc:
        result['status']='TIMEOUT';result['timeout_command']=list(map(str,exc.cmd));save(out/'fast.json',result)
        for label,data in [('stdout',exc.stdout),('stderr',exc.stderr)]:
            if data is not None:(out/('timeout-'+label+'.log')).write_bytes(data if isinstance(data,bytes) else data.encode())
        raise
    print(json.dumps({'status':result['status'],'summary':result.get('summary')},ensure_ascii=False),flush=True)


if __name__=='__main__':main()
