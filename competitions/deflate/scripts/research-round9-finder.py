"""CI-only q9 discovery diagnostic at unchanged #361 search positions."""
from __future__ import annotations

from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import random
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
SOURCES = {
    "baseline": ("references/round7-public-361/parse.rs", "f426f7cec777ef2ca74616eb62205d54ae0bf6938799835a1fe6024ed59b5c45"),
    "q9": ("references/round8-public-454/parse.rs", "382176623abda73f77a9a5323e8cb14c5cdd6c8221b018cbc8c51cf959448639"),
}
ANCHOR = """            let pcd = if cl >= 3 { cd } else { 0 };
            alen = next_anchor(alen, best, cl, best);
            anchor = next_anchor(anchor, i, cl, best);"""
CALLBACK = "            crate::compare_at_search(input, i, &cands, nc, &dtab, &dcc);\n"
COUNTERS = [
    "searched_positions", "baseline_records", "q9_records_at_search",
    "q9_longer_positions", "baseline_longer_positions", "extra_max_length_bytes", "lost_max_length_bytes",
    "baseline_supported_lengths", "q9_supported_lengths", "new_supported_lengths", "lost_supported_lengths",
    "common_supported_lengths", "q9_cheaper_common_lengths", "q9_costlier_common_lengths",
    "sum_common_edge_saving_units16", "sum_common_edge_cost_increase_units16",
    "q9_new_distance_records", "baseline_uncovered_distance_records", "q9_over16_search_positions",
    "baseline_checked_match_bytes", "q9_all_records", "q9_all_checked_match_bytes",
]

HARNESS = r'''
#![allow(dead_code)]
#[path="baseline.rs"] mod baseline;
#[path="baseline-observed.rs"] mod observed;
#[path="q9.rs"] mod q9;
use std::cell::RefCell;
use std::time::Instant;

#[derive(PartialEq, Eq)]
struct Cache { ep: Vec<u32>, ms: Vec<u32>, mc: Vec<u32> }
struct State { cache: Cache, cursor: usize, last: usize, counts: [u64;22], nc_hist: [u64;17] }
thread_local! { static STATE: RefCell<Option<State>> = const { RefCell::new(None) }; }

fn valid_match(input:&[u8], p:usize, len:usize, distance:usize)->bool {
    distance>=1 && distance<=32768 && distance<=p && len>=3 && len<=258
        && p+len<=input.len() && (0..len).all(|j|input[p+j]==input[p-distance+j])
}
fn unpack_q9(m:u32)->(usize,usize) { (((m>>20)&511)as usize, ((m&32767)+1)as usize) }

pub fn compare_at_search(input:&[u8], p:usize, cands:&[u32;16], nc:usize,
                         dtab:&[u8;512], dcc:&[u32;32]) {
    STATE.with(|cell| {
        let mut guard=cell.borrow_mut();
        let state=guard.as_mut().expect("finder diagnostic state");
        assert!(nc<=16 && p>=state.last); state.last=p;
        let State{cache,cursor,counts,nc_hist,..}=state;
        while *cursor<cache.ep.len() && (cache.ep[*cursor] as usize)<p { *cursor+=1; }
        let (a,b)=if *cursor<cache.ep.len() && cache.ep[*cursor] as usize==p {
            (cache.ms[*cursor] as usize,cache.ms[*cursor+1] as usize)
        } else {(0,0)};
        let matches=&cache.mc[a..b];
        counts[0]+=1; counts[1]+=nc as u64; counts[2]+=matches.len() as u64; nc_hist[nc]+=1;
        if matches.len()>16 {counts[18]+=1;}
        let mut bp=[u32::MAX;259]; let mut qp=[u32::MAX;259];
        let mut bl=2usize; let mut ql=2usize;
        for &c in &cands[..nc] {
            let len=(c&511)as usize; let distance=(c>>9)as usize;
            assert!(valid_match(input,p,len,distance),"invalid #361 candidate");
            counts[19]+=len as u64; bl=bl.max(len);
            let price=dcc[baseline::dsym(dtab,distance)%32];
            for l in 3..=len {bp[l]=bp[l].min(price);}
            if !matches.iter().any(|&m|{let(l,d)=unpack_q9(m);d==distance&&l>=len}) {counts[17]+=1;}
        }
        for &m in matches {
            let(len,distance)=unpack_q9(m); ql=ql.max(len);
            let price=dcc[baseline::dsym(dtab,distance)%32];
            for l in 3..=len {qp[l]=qp[l].min(price);}
            if !cands[..nc].iter().any(|&c|(c>>9)as usize==distance&&(c&511)as usize>=len) {counts[16]+=1;}
        }
        if ql>bl {counts[3]+=1;counts[5]+=(ql-bl)as u64;}
        if bl>ql {counts[4]+=1;counts[6]+=(bl-ql)as u64;}
        for l in 3..=bl.max(ql) {
            let has_b=bp[l]!=u32::MAX; let has_q=qp[l]!=u32::MAX;
            if has_b {counts[7]+=1;} if has_q {counts[8]+=1;}
            if has_q&&!has_b {counts[9]+=1;}
            else if has_b&&!has_q {counts[10]+=1;}
            else if has_b&&has_q {
                counts[11]+=1;
                if qp[l]<bp[l] {counts[12]+=1;counts[14]+=(bp[l]-qp[l])as u64;}
                if bp[l]<qp[l] {counts[13]+=1;counts[15]+=(qp[l]-bp[l])as u64;}
            }
        }
    });
}

fn build_cache(input:&[u8])->(Cache,u128) {
    let start=Instant::now();
    let mut cache=Cache{ep:Vec::with_capacity(input.len()/6+1),
        ms:Vec::with_capacity(input.len()/6+1),mc:Vec::with_capacity(input.len()/3+1)};
    q9::q9_hfind(input,&mut cache.ep,&mut cache.ms,&mut cache.mc,32);
    let elapsed=start.elapsed().as_nanos(); (cache,elapsed)
}
fn check_cache(input:&[u8],cache:&Cache)->[u64;22] {
    assert_eq!(cache.ms.len(),cache.ep.len()+1);
    assert_eq!(cache.ms.last().copied().unwrap() as usize,cache.mc.len());
    let mut counts=[0u64;22]; let mut last=0usize;
    for (index,&pos) in cache.ep.iter().enumerate() {
        let p=pos as usize; assert!(p<input.len() && (index==0||p>last));last=p;
        let a=cache.ms[index] as usize;let b=cache.ms[index+1] as usize;
        assert!(a<b&&b<=cache.mc.len());
        let mut length=2;
        for &m in &cache.mc[a..b] {
            let(l,d)=unpack_q9(m);
            assert!(l>length&&valid_match(input,p,l,d),"invalid q9 cache match");length=l;
            counts[20]+=1;counts[21]+=l as u64;
        }
    }
    counts
}
fn parse_plain(input:&[u8])->(Vec<u32>,u128) {
    let mut out=vec![0u32;input.len()];let start=Instant::now();
    let n=baseline::parse(input,&mut out);let elapsed=start.elapsed().as_nanos();
    assert!(n<=out.len());out.truncate(n);(out,elapsed)
}
fn decode(input:&[u8],tokens:&[u32])->bool {
    let mut out=Vec::with_capacity(input.len());
    for &t in tokens {
        if t<256 {if out.len()>=input.len(){return false;}out.push(t as u8);}
        else {
            if t<16777216{return false;}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;
            if d>32768||d>out.len()||l>258||out.len()+l>input.len(){return false;}
            for _ in 0..l {let b=out[out.len()-d];out.push(b);}
        }
    } out==input
}
fn main() {
    for (index,path) in std::env::args_os().skip(1).enumerate() {
        println!("R9_BEGIN {}",index);
        let input=std::fs::read(path).unwrap();
        let class=baseline::route_class(&input);let engine=baseline::CLASS_TAB[class%16][0];
        // Two opposite orders, with diagnostics outside both finder timers.
        let(cache,tq1)=build_cache(&input);let(reference,tb1)=parse_plain(&input);
        let(repeat,tb2)=parse_plain(&input);let(cache2,tq2)=build_cache(&input);
        assert!(reference==repeat,"baseline nondeterminism");
        assert!(cache==cache2,"q9 cache nondeterminism");drop(cache2);
        let checked=check_cache(&input,&cache);
        let cache_records=cache.mc.len();let cache_positions=cache.ep.len();
        let cache_capacity_bytes=4*(cache.ep.capacity()+cache.ms.capacity()+cache.mc.capacity());
        STATE.with(|cell|*cell.borrow_mut()=Some(State{cache,cursor:0,last:0,counts:checked,nc_hist:[0;17]}));
        let mut out=vec![0u32;input.len()];let n=observed::parse(&input,&mut out);
        assert!(n<=out.len());out.truncate(n);
        let equivalent=out==reference;let decoded=decode(&input,&out);
        let state=STATE.with(|cell|cell.borrow_mut().take().unwrap());
        println!("R9_RESULT {{\"index\":{},\"input_bytes\":{},\"class\":{},\"engine\":{},\"tokens\":{},\"token_equivalent\":{},\"decode_ok\":{},\"q9_finder_ns\":[{},{}],\"baseline_parse_ns\":[{},{}],\"cache_positions\":{},\"cache_records\":{},\"cache_capacity_bytes\":{},\"counts\":{:?},\"nc_hist\":{:?}}}",
            index,input.len(),class,engine,n,equivalent,decoded,tq1,tq2,tb1,tb2,cache_positions,cache_records,cache_capacity_bytes,state.counts,state.nc_hist);
        assert!(equivalent&&decoded,"observation changed baseline output or decode failed");
    }
}
'''


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def instrument(source: str) -> str:
    start_marker = "pub fn dp_parse("
    end_marker = "\npub const D_TS: usize = 560;"
    if source.count(start_marker) != 1 or source.count(end_marker) != 1 or "crate::compare_at_search" in source:
        raise ValueError("#361 exact observation anchor changed or was already instrumented")
    start = source.index(start_marker)
    end = source.index(end_marker, start)
    region = source[start:end]
    if region.count(ANCHOR) != 1:
        raise ValueError("Expected one exact observation anchor inside dp_parse only")
    return source[:start] + region.replace(ANCHOR, CALLBACK + ANCHOR, 1) + source[end:]


def synthetic_inputs() -> list[tuple[str, bytes]]:
    result = []
    patterns = [
        b"fn transform_record(value: usize) -> usize { let common_prefix = value + 1729; return common_prefix; }\n",
        b"the reader follows the garden path and finds the same quiet house beyond the old trees \n",
        b'<record><name>common prefix and repeated field</name><value>constant value</value></record>\n',
    ]
    for mode, pattern in enumerate(patterns):
        for size in (65537, 131073):
            data = bytearray((pattern * (size // len(pattern) + 1))[:size])
            rng = random.Random(361454 + mode * 100 + size)
            for offset in range(257, size, 257):
                data[offset] = 97 + rng.randrange(26)
            result.append((f"synthetic-prefix-{mode}-{size}.bin", bytes(data)))
    return result


def parse_results(stdout: str, inputs: list[dict]) -> list[dict]:
    rows = []
    for line in stdout.splitlines():
        if not line.startswith("R9_RESULT "):
            continue
        raw = json.loads(line[len("R9_RESULT "):])
        index = raw.pop("index")
        if index != len(rows) or index >= len(inputs):
            raise ValueError("Unexpected result index")
        counts, hist = raw.pop("counts"), raw.pop("nc_hist")
        if len(counts) != len(COUNTERS) or len(hist) != 17:
            raise ValueError("Counter schema mismatch")
        if any(type(x) is not int or x < 0 for x in counts + hist):
            raise ValueError("Invalid diagnostic counter")
        row = {**inputs[index], **raw, **dict(zip(COUNTERS, counts))}
        if row["input_bytes"] != inputs[index]["input_bytes"]:
            raise ValueError("Input manifest mismatch")
        if sum(hist) != row["searched_positions"] or sum(i*n for i,n in enumerate(hist)) != row["baseline_records"]:
            raise ValueError("Search histogram mismatch")
        if row["baseline_supported_lengths"] != row["common_supported_lengths"] + row["lost_supported_lengths"]:
            raise ValueError("Baseline length coverage mismatch")
        if row["q9_supported_lengths"] != row["common_supported_lengths"] + row["new_supported_lengths"]:
            raise ValueError("q9 length coverage mismatch")
        if row["q9_all_records"] != row["cache_records"]:
            raise ValueError("Cache validation coverage mismatch")
        row["baseline_candidate_histogram"] = {str(i): n for i,n in enumerate(hist)}
        row["q9_finder_over_baseline_parse"] = [q/b if b else None for q,b in zip(row["q9_finder_ns"],row["baseline_parse_ns"])]
        rows.append(row)
    return rows


def save(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2, allow_nan=False) + "\n", encoding="utf-8")


def run_logged(command: list[str], path: Path, timeout: int) -> subprocess.CompletedProcess:
    try:
        result = subprocess.run(command, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired as error:
        def as_text(value):
            return value.decode("utf-8",errors="replace") if isinstance(value,bytes) else (value or "")
        path.write_text(as_text(error.stdout)+as_text(error.stderr),encoding="utf-8")
        raise
    path.write_text(result.stdout+result.stderr,encoding="utf-8")
    return result


def main() -> None:
    if not (sys.platform == "linux" and os.environ.get("GITHUB_ACTIONS") == "true"
            and os.environ.get("RUNNER_OS") == "Linux"
            and os.environ.get("GITHUB_REPOSITORY") == "HuanHuanHuanFFF/Miner"):
        raise SystemExit("Run only in this repository's Linux GitHub Actions runner")
    label = os.environ.get("ROUND4_SPEC")
    if not label:
        print("ROUND9_FINDER_DIAGNOSTIC_NOT_REQUESTED", flush=True)
        return
    from round4 import specification_path
    specification = json.loads(specification_path(label).read_text(encoding="utf-8"))
    if specification.get("finder_diagnostics") is not True:
        print("ROUND9_FINDER_DIAGNOSTIC_NOT_REQUESTED", flush=True)
        return
    temp = Path(os.environ["RUNNER_TEMP"]).resolve(strict=True)
    build = temp / "round9-finder-build"
    output = temp / "round4-receipts/finder-diagnostics"
    for folder in (build, output):
        if not folder.resolve().is_relative_to(temp):
            raise ValueError("Temporary path escaped RUNNER_TEMP")
        folder.mkdir(parents=True, exist_ok=True)
    receipt = output / "finder-diagnostics.json"
    report = {
        "status": "NOT_RUN", "created_at": datetime.now(timezone.utc).isoformat(),
        "run_id": os.environ.get("GITHUB_RUN_ID"), "git_sha": os.environ.get("GITHUB_SHA"),
        "scope": "q9 discovery at unchanged #361 searched positions; diagnostic timings exclude encoder and are not official scores",
        "timing_scope": "two opposite-order observations, no warmups; finder includes cache allocation/build but excludes validation; baseline timer excludes output allocation; not a statistically established speedup",
        "coverage_scope": "all retained q9 candidates compared without 16-slot truncation; lengths and alternative-edge cost differences are not chosen-path/encoded savings",
        "counter_limits": "records and validated match bytes are counted; internal tree node visits and comparison bytes are not instrumented",
        "script_sha256": sha256(Path(__file__).read_bytes()), "source_hashes": {},
        "compile_exit": None, "runtime_exit": None, "files": [],
    }
    save(receipt, report)
    try:
        for name,(relative,expected) in SOURCES.items():
            data=(ROOT/relative).read_bytes()
            if sha256(data)!=expected: raise ValueError(f"Pinned {name} source hash changed")
            report["source_hashes"][name]={"path":relative,"sha256":expected}
            normalized=data.decode("utf-8").replace("\r\n","\n")
            (build/f"{name}.rs").write_text(normalized,encoding="utf-8")
            if name=="baseline":
                copied=instrument(normalized)
                (build/"baseline-observed.rs").write_text(copied,encoding="utf-8")
                report["observed_baseline_sha256"]=sha256(copied.encode())
        source=build/"finder.rs";source.write_text(HARNESS,encoding="utf-8")
        report["harness_sha256"]=sha256(source.read_bytes())
        corpus=Path(os.environ["DEFLATE_ROOT"])/"data/benchmark/corpus-stage1"
        paths=sorted(path for path in corpus.iterdir() if path.is_file())
        if len(paths)!=28: raise ValueError("Expected 28 public corpus files")
        inputs=[{"file":path.name,"kind":"public","input_bytes":path.stat().st_size,
                 "input_sha256":sha256(path.read_bytes())} for path in paths]
        for name,data in synthetic_inputs():
            path=build/name;path.write_bytes(data);paths.append(path)
            inputs.append({"file":name,"kind":"synthetic","input_bytes":len(data),"input_sha256":sha256(data)})
        report["input_manifest"]=inputs
        binary=build/"finder"
        command=["rustc","+nightly-2026-08-18","--edition=2021","-O","-C","overflow-checks=yes",str(source),"-o",str(binary)]
        report["compile_command"]=command;report["status"]="BUILD_PENDING";save(receipt,report)
        compiled=run_logged(command,output/"build.log",180);report["compile_exit"]=compiled.returncode
        if compiled.returncode: raise RuntimeError("Rust diagnostic build failed; inspect build.log")
        report["status"]="RUNTIME_PENDING";save(receipt,report)
        measured=run_logged([str(binary),*map(str,paths)],output/"runtime.log",360)
        report["runtime_exit"]=measured.returncode
        report["files"]=parse_results(measured.stdout,inputs)
        if measured.returncode or len(report["files"])!=len(inputs): raise RuntimeError("Finder diagnostic incomplete")
        if not all(row["decode_ok"] is True and row["token_equivalent"] is True for row in report["files"]):
            raise RuntimeError("Baseline observation equivalence/decode failure")
        for name,(relative,expected) in SOURCES.items():
            if sha256((ROOT/relative).read_bytes())!=expected: raise RuntimeError(f"Original {name} source changed")
        report["totals_by_kind"]={kind:{key:sum(row[key] for row in report["files"] if row["kind"]==kind) for key in COUNTERS}
                                  for kind in ("public","synthetic")}
        report["status"]="VERIFIED_DIAGNOSTIC_ONLY";report["completed_at"]=datetime.now(timezone.utc).isoformat()
        save(receipt,report)
        print("ROUND9_FINDER_DIAGNOSTIC",json.dumps({"status":report["status"],"files":len(report["files"]),"totals_by_kind":report["totals_by_kind"]}),flush=True)
    except Exception as error:
        report["status"]="DIAGNOSTIC_FAILED";report["error"]=f"{type(error).__name__}: {error}";save(receipt,report)
        raise


if __name__=="__main__":
    main()
