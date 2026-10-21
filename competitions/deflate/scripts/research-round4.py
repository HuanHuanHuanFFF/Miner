"""Finite token equivalence, kept separate from official timing and proof gates."""
from pathlib import Path
import hashlib
import json
import os
import subprocess
import sys
from round4 import validate, save, ROOT

MAX_EQUIVALENCE_PAIRS = 8


def equivalence_pairs(spec):
    by_name = {entry['name']: entry for entry in spec['entries']}
    pairs = []
    for candidate in spec['entries']:
        reference_name = candidate.get('expected_equivalent_to')
        if not reference_name:
            continue
        if reference_name not in by_name:
            raise ValueError(
                f"{candidate['name']}: equivalence reference {reference_name!r} "
                "is missing from the validated spec entries"
            )
        reference = by_name[reference_name]
        if reference_name == candidate['name']:
            raise ValueError(f"{candidate['name']}: equivalence reference cannot be itself")
        candidate_path = (ROOT / candidate['path'] / 'parse.rs').resolve()
        reference_path = (ROOT / reference['path'] / 'parse.rs').resolve()
        if candidate_path == reference_path:
            raise ValueError(
                f"{candidate['name']}: equivalence reference {reference_name!r} "
                "resolves to the same parse.rs"
            )
        pairs.append((candidate, reference))
    if len(pairs) > MAX_EQUIVALENCE_PAIRS:
        raise ValueError(
            f"finite equivalence requested {len(pairs)} pairs; "
            f"limit is {MAX_EQUIVALENCE_PAIRS}"
        )
    return pairs


def build_harness(pairs):
    modules = []
    cases = []
    for i, (candidate, reference) in enumerate(pairs):
        candidate_path = ROOT / candidate['path'] / 'parse.rs'
        reference_path = ROOT / reference['path'] / 'parse.rs'
        modules.append(
            f'#[path={json.dumps(str(candidate_path))}] mod candidate{i};'
        )
        modules.append(
            f'#[path={json.dumps(str(reference_path))}] mod reference{i};'
        )
        cases.append(
            f'({json.dumps(candidate["name"])},{json.dumps(reference["name"])},'
            f'candidate{i}::parse,reference{i}::parse)'
        )

    harness = r'''
#![allow(dead_code)]
MODULES
type Parser = fn(&[u8], &mut [u32]) -> usize;
fn tokens(s:&[u8], f:Parser)->Vec<u32>{let mut out=vec![0;s.len()];let n=f(s,&mut out);assert!(n<=s.len());out.truncate(n);out}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for &t in ts{if t<256{out.push(t as u8)}else{if t<16777216{return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>32768||d>out.len()||l>258||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn prefix_len(a:&[u32],b:&[u32])->usize{a.iter().zip(b).take_while(|(x,y)|x==y).count()}
fn sample(n:usize,mode:usize,mut z:u64)->Vec<u8>{let text=b"The quick brown fox, record 0123456789; fn result(value) { return value + 1; }\n";let prose=b"the quick brown fox walks through the garden and returns home ";let structured=b"2026-10-07,10002345,1234.55,region=002,code=200\n";let mut v=Vec::with_capacity(n);for i in 0..n{z^=z<<13;z^=z>>7;z^=z<<17;v.push(match mode{0=>(z>>24)as u8,1=>text[i%text.len()],2=>if z%79==0{(z%95+32)as u8}else{text[i%text.len()]},3=>if i%2==0{0xbf}else{z as u8},4=>if z%31==0{z as u8}else{0},5=>b"ACGT\n"[(z%5)as usize],6=>prose[i%prose.len()],_=>structured[i%structured.len()]})}if mode==0&&n>65536{for d in [16383,16384,16385,32767,32768,32769]{for j in 0..257{if 1024+d+j<n{v[1024+d+j]=v[1024+j]}}}}v}
fn check(label:&str,s:&[u8],parsers:&[(&str,&str,Parser,Parser)],count:&mut[usize],bad:&mut[usize]){for(i,(candidate,reference,candidate_fn,reference_fn))in parsers.iter().enumerate(){count[i]+=1;let r=std::panic::catch_unwind(std::panic::AssertUnwindSafe(||tokens(s,*reference_fn)));let c=std::panic::catch_unwind(std::panic::AssertUnwindSafe(||tokens(s,*candidate_fn)));let mut r_decode=false;let mut c_decode=false;let mut common=0;let equal=match(&r,&c){(Ok(rt),Ok(ct))=>{r_decode=decode(s,rt);c_decode=decode(s,ct);common=prefix_len(rt,ct);r_decode&&c_decode&&rt==ct},_=>false};if !equal{bad[i]+=1;if bad[i]<=3{println!("EQUIVALENCE_DIFFERENT {} {} {} bytes={} reference_tokens={} candidate_tokens={} common_prefix={} reference_decode={} candidate_decode={} reference_panic={} candidate_panic={}",candidate,reference,label,s.len(),r.as_ref().map_or(0,|x|x.len()),c.as_ref().map_or(0,|x|x.len()),common,r_decode,c_decode,r.is_err(),c.is_err());}}}}
fn main(){let parsers:&[(&str,&str,Parser,Parser)]=&[CASES];let mut counts=vec![0;parsers.len()];let mut bad=vec![0;parsers.len()];let arg=std::env::args().nth(1).unwrap();let mut files:Vec<_>=std::fs::read_dir(arg).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();for p in files{let s=std::fs::read(&p).unwrap();check(p.file_name().unwrap().to_str().unwrap(),&s,parsers,&mut counts,&mut bad)}for n in [0,1,3,4,7,8,15,16,17,31,32,257,258,259,1023,16383,16384,16385,32767,32768,32769,65535,65536,65537,98305,131073]{for mode in 0..8{for seed in [1,987654321]{let s=sample(n,mode,seed);check(&format!("synthetic-{}-{}-{}",n,mode,seed),&s,parsers,&mut counts,&mut bad)}}}for(i,(candidate,reference,_,_))in parsers.iter().enumerate(){println!("EQUIVALENCE_RESULT {} {} {} {}",candidate,reference,counts[i],bad[i]);}}
'''
    return harness.replace('MODULES', '\n'.join(modules)).replace('CASES', ','.join(cases))


def main():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = validate(os.environ['ROUND4_SPEC'])
    pairs = equivalence_pairs(spec)
    output = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts'
    output.mkdir(exist_ok=True)
    if not pairs:
        save(output / 'equivalence-research.json', {'status': 'not requested'}); return
    build = Path(os.environ['RUNNER_TEMP']) / 'round4-research-build'
    build.mkdir(exist_ok=True)
    harness = build_harness(pairs)
    source = build / 'equivalence.rs'
    source.write_text(harness, encoding='utf-8')
    binary = build / 'equivalence'
    compiled = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(source), '-o', str(binary)], capture_output=True, text=True)
    (output / 'equivalence-build.log').write_text(compiled.stdout + compiled.stderr)
    if compiled.returncode:
        save(output / 'equivalence-research.json', {'status': 'diagnostic build failed', 'returncode': compiled.returncode})
        print(compiled.stderr[-3000:]); return
    run = subprocess.run([str(binary), str(Path(os.environ['DEFLATE_ROOT']) / 'data/benchmark/corpus-stage1')], capture_output=True, text=True, timeout=240)
    (output / 'equivalence-run.log').write_text(run.stdout + run.stderr)
    print(run.stdout, flush=True)
    result = {'scope': 'finite token/decode checks; not full proof or timing evidence', 'harness_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
              'returncode': run.returncode, 'cases': []}
    for line in run.stdout.splitlines():
        if line.startswith('EQUIVALENCE_RESULT '):
            _, candidate, reference, count, failed = line.split()
            result['cases'].append({'candidate': candidate, 'reference': reference,
                                    'cases': int(count), 'different_or_failed': int(failed)})
    save(output / 'equivalence-research.json', result)
    if run.returncode:
        raise SystemExit('Diagnostic harness or baseline failed; inspect logs')
    if len(result['cases']) != len(pairs) or any(row['different_or_failed'] for row in result['cases']):
        raise SystemExit('Requested finite token equality failed or result missing; receipt retained')


if __name__ == '__main__':
    main()
