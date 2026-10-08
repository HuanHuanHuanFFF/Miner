"""CI-only cost-cache opportunity counts, with frozen-token/decode comparison.

No microfunction timer is used. Counter instrumentation is not benchmark code.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
import os

from round4 import ROOT, save, validate

_spec = importlib.util.spec_from_file_location("r9_log_helpers", ROOT / "scripts/research-round9-phases.py")
_helper = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_helper)
run_logged = _helper.run_logged
failure_receipt = _helper.failure_receipt

FIELDS = ["scheduled", "rebuild", "skipped", "halve"]
COUNTERS = r'''
use std::sync::atomic::{AtomicU64,Ordering};
static R10_COST_COUNTS:[AtomicU64;4]=[const{AtomicU64::new(0)};4];
pub fn r10_reset_counts(){for n in &R10_COST_COUNTS{n.store(0,Ordering::Relaxed)}}
pub fn r10_cost_counts()->[u64;4]{std::array::from_fn(|i|R10_COST_COUNTS[i].load(Ordering::Relaxed))}
'''

HARNESS = r'''
#![allow(dead_code,unused_variables)]
#[path="frozen.rs"]mod frozen;
#[path="instrumented.rs"]mod counted;
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for &t in ts{if t<256{out.push(t as u8)}else{if t<16777216{return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>32768||d>out.len()||l>258||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn main(){for(index,file)in std::env::args_os().skip(1).enumerate(){let s=std::fs::read(file).unwrap();let(mut a,mut b)=(vec![0u32;s.len()],vec![0u32;s.len()]);let an=frozen::parse(&s,&mut a);counted::r10_reset_counts();let bn=counted::parse(&s,&mut b);assert!(an<=s.len()&&bn<=s.len());assert_eq!(&a[..an],&b[..bn],"counter instrumentation changed tokens");assert!(decode(&s,&a[..an])&&decode(&s,&b[..bn]));let c=counted::r10_cost_counts();assert_eq!(c[0],c[1]+c[2]);assert!(c[3]<=c[1]);println!("R10_COSTCACHE {{\"file_index\":{},\"bytes\":{},\"tokens\":{},\"counts\":{:?},\"tokens_equal\":true,\"decode\":true}}",index,s.len(),an,c);}}
'''


def instrument(source):
    start = source.index("pub fn d_update_costs_cached(")
    end = source.index("pub fn d_parse(", start)
    old = source[start:end]
    opening = old.index("{") + 1
    new = old[:opening] + "\n    R10_COST_COUNTS[0].fetch_add(1, Ordering::Relaxed);" + old[opening:]
    assert new.count("    if tot > HALF_AT {") == 1
    new = new.replace("    if tot > HALF_AT {", "    if tot > HALF_AT {\n        R10_COST_COUNTS[3].fetch_add(1, Ordering::Relaxed);", 1)
    a = """    if refresh {
        make_costs(lf, df, lsym, litc, lc, dcc, huff);
    }"""
    b = """    if refresh {
        R10_COST_COUNTS[1].fetch_add(1, Ordering::Relaxed);
        make_costs(lf, df, lsym, litc, lc, dcc, huff);
    } else {
        R10_COST_COUNTS[2].fetch_add(1, Ordering::Relaxed);
    }"""
    assert new.count(a) == 1
    new = new.replace(a, b, 1)
    return source[:start] + new + source[end:] + COUNTERS


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    assert os.environ.get("GITHUB_REPOSITORY") == "HuanHuanHuanFFF/Miner"
    spec = validate(os.environ["ROUND4_SPEC"])
    if not spec.get("costcache_diagnostics"):
        print("ROUND10_COSTCACHE_NOT_REQUESTED")
        return
    entry = next(e for e in spec["entries"] if e["name"] == "r10-forward-costcache")
    raw = (ROOT / entry["path"] / "parse.rs").read_bytes()
    assert hashlib.sha256(raw).hexdigest() == entry["hashes"]["parse.rs"]
    files = sorted(p for p in (Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1").iterdir() if p.is_file())
    assert len(files) == 28 and sum(p.stat().st_size for p in files) == 15930000
    build = Path(os.environ["RUNNER_TEMP"]) / "round10-costcache-build"
    output = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/costcache-diagnostics"
    build.mkdir(exist_ok=True)
    output.mkdir(parents=True, exist_ok=True)
    (build / "frozen.rs").write_bytes(raw)
    (build / "instrumented.rs").write_text(instrument(raw.decode()))
    (build / "main.rs").write_text(HARNESS)
    report = {"status": "PENDING", "run_id": os.environ["GITHUB_RUN_ID"], "git_sha": os.environ["GITHUB_SHA"],
              "candidate": entry["name"], "source_sha256": entry["hashes"]["parse.rs"], "counter_order": FIELDS,
              "scope": "Actual scheduled/rebuilt/skipped/halved model counts. Frozen/instrumented tokens and decoding checked. No timers or competition-axis inference.",
              "corpus": [{"file": p.name, "bytes": p.stat().st_size, "sha256": hashlib.sha256(p.read_bytes()).hexdigest()} for p in files]}
    save(output / "costcache.json", report)
    with failure_receipt(report, output / "costcache.json"):
        binary = build / "costcache-count"
        proc = run_logged(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes", str(build / "main.rs"), "-o", str(binary)], output / "build.log", 180)
        report["compile_exit"] = proc.returncode
        if proc.returncode:
            raise RuntimeError("Costcache diagnostic Rust compilation failed; retained build.log")
        proc = run_logged([str(binary), *map(str, files)], output / "runtime.log", 180)
        report["runtime_exit"] = proc.returncode
        rows = [json.loads(line.removeprefix("R10_COSTCACHE ")) for line in proc.stdout.splitlines() if line.startswith("R10_COSTCACHE ")]
        assert proc.returncode == 0 and len(rows) == 28
        assert [r["file_index"] for r in rows] == list(range(28))
        assert all(r["tokens_equal"] and r["decode"] for r in rows)
        for row in rows:
            row["file"] = files[row["file_index"]].name
            row["named_counts"] = dict(zip(FIELDS, row["counts"]))
            assert row["counts"][0] == row["counts"][1] + row["counts"][2]
        totals = {key: sum(r["counts"][i] for r in rows) for i, key in enumerate(FIELDS)}
        report.update(status="VERIFIED_FINITE_COSTCACHE_COUNTS", records=rows, totals=totals,
                      instrumented_sha256=hashlib.sha256((build / "instrumented.rs").read_bytes()).hexdigest())
        save(output / "costcache.json", report)
        print("ROUND10_COSTCACHE", json.dumps({"status": report["status"], "files": 28, "totals": totals}))


if __name__ == "__main__":
    main()
