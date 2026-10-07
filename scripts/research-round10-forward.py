"""CI-only finite rs/seed checks and sampled inclusive forward cost attribution.

These timings are diagnostics, never official competition axes. Helper samples
overlap (d_walk includes probe, d_record includes d_backext); do not sum them.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
import os
import statistics

from round4 import ROOT, save, validate

_spec = importlib.util.spec_from_file_location("r9_phases", ROOT / "scripts/research-round9-phases.py")
_helper = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_helper)
run_logged = _helper.run_logged
failure_receipt = _helper.failure_receipt

PHASES = ["insert_pos", "probe", "d_walk", "d_record", "d_backext", "d_relax", "backtrack", "update_costs", "d_parse"]

INSTRUMENT = r'''
use std::cell::Cell;
thread_local! {
    static R10_CALLS: Cell<[u64;9]> = const { Cell::new([0;9]) };
    static R10_NS: Cell<[u64;9]> = const { Cell::new([0;9]) };
    static R10_SAMPLES: Cell<[u64;9]> = const { Cell::new([0;9]) };
    static R10_MASK: Cell<u64> = const { Cell::new(1023) };
}
struct R10Timer(usize, Option<std::time::Instant>);
impl R10Timer {
    #[inline(always)]
    fn new(i:usize)->Self {
        let count=R10_CALLS.with(|c|{let mut a=c.get();let n=a[i];a[i]+=1;c.set(a);n});
        let sampled=i==8 || R10_MASK.with(|m|count&m.get()==0);
        Self(i,if sampled{Some(std::time::Instant::now())}else{None})
    }
}
impl Drop for R10Timer {
    #[inline(always)]
    fn drop(&mut self){if let Some(t)=self.1{let ns=t.elapsed().as_nanos() as u64;
        R10_NS.with(|c|{let mut a=c.get();a[self.0]+=ns;c.set(a)});
        R10_SAMPLES.with(|c|{let mut a=c.get();a[self.0]+=1;c.set(a)});
    }}
}
pub fn r10_reset(mask:u64){R10_CALLS.with(|c|c.set([0;9]));R10_NS.with(|c|c.set([0;9]));R10_SAMPLES.with(|c|c.set([0;9]));R10_MASK.with(|c|c.set(mask));}
pub fn r10_times()->([u64;9],[u64;9],[u64;9]){(R10_CALLS.with(|c|c.get()),R10_NS.with(|c|c.get()),R10_SAMPLES.with(|c|c.get()))}
'''

HARNESS = r'''
#![allow(dead_code,unused_variables)]
#[path="reference.rs"] mod reference;
#[path="instrumented.rs"] mod profiled;
#[path="candidate.rs"] mod candidate;
use std::time::Instant;
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for &t in ts{if t<256{out.push(t as u8)}else{if t<16777216{return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>32768||d>out.len()||l>258||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn seed_check(s:&[u8],case:usize,forced:bool){
    if s.len()<16{return}
    let cls=reference::route_class(s)%16;
    if !forced && reference::CLASS_TAB[cls][0]!=2{return}
    let row=if forced{case%11}else{reference::CLASS_TAB[cls][1]%16};
    let k=reference::D_KNOBS[row];
    let(mut old_plan,mut old_rs,mut new_plan,mut new_rs)=(Vec::new(),Vec::new(),Vec::new(),Vec::new());
    let t=Instant::now();reference::d_parse(s,&mut old_plan,&mut old_rs,k[0],k[1],k[2],k[3],k[4],k[5],k[8],k[9],k[10],k[11],k[12],k[13],k[14],k[15]);let old_ns=t.elapsed().as_nanos();
    let t=Instant::now();candidate::d_collect(s,&mut new_plan,&mut new_rs,k[0],k[1],k[2],k[3],k[4],k[5],k[8],k[9],k[10],k[11],k[12],k[13],k[14],k[15]);let collect_ns=t.elapsed().as_nanos();
    assert_eq!(old_rs,new_rs,"D candidate stream changed");assert!(new_plan.is_empty());
    let mut out=vec![0u32;s.len()];let t=Instant::now();candidate::d_seed(s,&new_rs,&mut out,&mut new_plan);let seed_ns=t.elapsed().as_nanos();
    let mut p=0;for &v in &new_plan{let l=(v%512)as usize;let d=(v>>9)as usize;if l>=3{assert!(reference::check(s,p,l,d),"invalid seed match");p+=l}else{p+=1}}
    assert_eq!(p,s.len(),"seed plan coverage");
    let mut tok=vec![0;s.len()];let nt=candidate::parse(s,&mut tok);assert!(nt<=s.len());assert!(decode(s,&tok[..nt]));
    println!("R10_SEED {{\"case\":{},\"synthetic\":{},\"bytes\":{},\"row\":{},\"rs_words\":{},\"rs_equal\":true,\"seed_valid\":true,\"decode\":true,\"forward_ns\":{},\"collect_ns\":{},\"seed_ns\":{}}}",case,forced,s.len(),row,old_rs.len(),old_ns,collect_ns,seed_ns);
}
fn sample(n:usize,mode:usize)->Vec<u8>{let text=b"The quick brown fox, record 0123456789; fn result(value) { return value + 1; }\n";let mut z=987654321u64;let mut v=Vec::with_capacity(n);for i in 0..n{z^=z<<13;z^=z>>7;z^=z<<17;v.push(match mode%6{0=>(z>>24)as u8,1=>text[i%text.len()],2=>if z%79==0{(z%95+32)as u8}else{text[i%text.len()]},3=>if i%2==0{0xbf}else{z as u8},4=>if z%31==0{z as u8}else{0},_=>b"ACGT\n"[(z%5)as usize]})}v}
fn main(){
    for (index,file) in std::env::args_os().skip(1).enumerate(){
        let s=std::fs::read(file).unwrap();seed_check(&s,index,false);
        for rep in 0..3 {
            let mask=if rep==2{63}else{1023};profiled::r10_reset(mask);
            let(mut a,mut b)=(vec![0u32;s.len()],vec![0u32;s.len()]);
            let(mut an,mut bn,mut at,mut bt)=(0,0,0u128,0u128);
            for order in 0..2{if (order+rep)%2==0{let t=Instant::now();an=reference::parse(&s,&mut a);at=t.elapsed().as_nanos()}else{let t=Instant::now();bn=profiled::parse(&s,&mut b);bt=t.elapsed().as_nanos()}}
            assert_eq!(&a[..an],&b[..bn],"profile changed tokens");
            let(calls,ns,samples)=profiled::r10_times();
            println!("R10_FORWARD {{\"file_index\":{},\"rep\":{},\"mask\":{},\"reference_ns\":{},\"instrumented_ns\":{},\"calls\":{:?},\"sample_ns\":{:?},\"samples\":{:?},\"tokens_equal\":true}}",index,rep,mask,at,bt,calls,ns,samples);
        }
    }
    let mut case=0;for n in [16,17,31,257,258,259,1023,16385,32769,65537,98305]{for mode in 0..6{let s=sample(n,mode);seed_check(&s,case,true);case+=1}}
}
'''


def instrument(source):
    assert "R10Timer" not in source
    for index, name in enumerate(PHASES):
        marker = "pub fn " + name + "("
        assert source.count(marker) == 1
        point = source.index("{", source.index(marker)) + 1
        source = source[:point] + f"\n    let _r10_timer = R10Timer::new({index});" + source[point:]
    return source + INSTRUMENT


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    assert os.environ.get("GITHUB_REPOSITORY") == "HuanHuanHuanFFF/Miner"
    spec = validate(os.environ["ROUND4_SPEC"])
    if not spec.get("forward_diagnostics"):
        print("ROUND10_FORWARD_NOT_REQUESTED")
        return
    reference = next(e for e in spec["entries"] if e["name"] == "r9-block-scalar")
    candidate = next(e for e in spec["entries"] if e["name"] == "r10-forward-seed")
    sources = {}
    for label, entry in (("reference", reference), ("candidate", candidate)):
        raw = (ROOT / entry["path"] / "parse.rs").read_bytes()
        assert hashlib.sha256(raw).hexdigest() == entry["hashes"]["parse.rs"]
        sources[label] = raw
    files = sorted(p for p in (Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1").iterdir() if p.is_file())
    assert len(files) == 28 and sum(p.stat().st_size for p in files) == 15930000
    build = Path(os.environ["RUNNER_TEMP"]) / "round10-forward-build"
    output = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/forward-diagnostics"
    build.mkdir(exist_ok=True)
    output.mkdir(parents=True, exist_ok=True)
    for name, raw in sources.items():
        (build / f"{name}.rs").write_bytes(raw)
    (build / "instrumented.rs").write_text(instrument(sources["reference"].decode()))
    (build / "main.rs").write_text(HARNESS)
    report = {"status": "PENDING", "run_id": os.environ["GITHUB_RUN_ID"], "git_sha": os.environ["GITHUB_SHA"],
              "reference_sha256": reference["hashes"]["parse.rs"], "candidate_sha256": candidate["hashes"]["parse.rs"],
              "scope": "Finite rs-stream equality, seed validity and decode. Sampled helper costs are inclusive/overlapping and instrumented; parser-only, no official axes.",
              "phases": PHASES, "corpus": [{"file": f.name, "bytes": f.stat().st_size, "sha256": hashlib.sha256(f.read_bytes()).hexdigest()} for f in files]}
    save(output / "forward.json", report)
    with failure_receipt(report, output / "forward.json"):
        binary = build / "forward-profile"
        proc = run_logged(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes", str(build / "main.rs"), "-o", str(binary)], output / "build.log", 180)
        report["compile_exit"] = proc.returncode
        if proc.returncode:
            raise RuntimeError("Forward diagnostic Rust build failed; retained build.log")
        cpu = str(min(os.sched_getaffinity(0)))
        proc = run_logged(["taskset", "-c", cpu, str(binary), *map(str, files)], output / "runtime.log", 420)
        report["runtime_exit"] = proc.returncode
        phases = [json.loads(line.removeprefix("R10_FORWARD ")) for line in proc.stdout.splitlines() if line.startswith("R10_FORWARD ")]
        seeds = [json.loads(line.removeprefix("R10_SEED ")) for line in proc.stdout.splitlines() if line.startswith("R10_SEED ")]
        assert proc.returncode == 0 and len(phases) == 84 and all(r["tokens_equal"] for r in phases)
        assert len([r for r in seeds if r["synthetic"]]) == 66
        assert all(r["rs_equal"] and r["seed_valid"] and r["decode"] for r in seeds)
        report.update(status="VERIFIED_FINITE_FORWARD_DIAGNOSTIC", records=phases, seed_records=seeds, cpu_affinity=cpu,
                      instrumented_sha256=hashlib.sha256((build / "instrumented.rs").read_bytes()).hexdigest())
        save(output / "forward.json", report)
        print("ROUND10_FORWARD", json.dumps({"status": report["status"], "profile_comparisons": len(phases), "seed_checks": len(seeds)}))


if __name__ == "__main__":
    main()
