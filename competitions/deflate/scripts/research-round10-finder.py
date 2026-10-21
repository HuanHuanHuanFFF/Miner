"""CI-only finite decoding and supplemental-finder provenance diagnostic.

No encoder/time-axis/admission claim. Observed copies must preserve each candidate's
tokens and the original candidate prefix at every visited search node.
"""
from __future__ import annotations

from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
NAMES = ("r10-finder-tag4", "r10-finder-hash5")
COUNTERS = (
    "cache_updates", "searched_positions", "eligible_cache_probes",
    "added_longer_records", "added_max_length_bytes", "original_records_retained",
    "full_candidate_slots", "baseline_supported_lengths", "new_supported_lengths",
)
ANCHOR = """            let r10_more = r10_supplement(input, r10_old, i, b8, cap, &mut cands, nc, best);
            nc = r10_more.0;
            best = r10_more.1;"""
OBSERVED = """            let r10_saved_cands = cands;
            let r10_saved_nc = nc;
            let r10_saved_best = best;
""" + ANCHOR + """
            crate::observe_query(input, i, r10_old, cap, &r10_saved_cands,
                r10_saved_nc, r10_saved_best, &cands, nc, best);"""

HARNESS = r'''
#![allow(dead_code)]
MODULES
use std::cell::RefCell;
thread_local! { static COUNTS: RefCell<([u64;9],[u64;8],[u64;8])> = const { RefCell::new(([0;9],[0;8],[0;8])) }; }
type Parser=fn(&[u8],&mut[u32])->usize;
fn bin(l:usize)->usize{if l<3{0}else if l<4{1}else if l<8{2}else if l<16{3}else if l<32{4}else if l<64{5}else if l<128{6}else{7}}
pub fn observe_store(){COUNTS.with(|s|s.borrow_mut().0[0]+=1);}
fn valid(s:&[u8],p:usize,l:usize,d:usize)->bool{
 d>=1&&d<=32768&&d<=p&&l>=3&&l<=258&&p+l<=s.len()&&(0..l).all(|j|s[p+j]==s[p-d+j])
}
pub fn observe_query(s:&[u8],p:usize,old:usize,cap:usize,before:&[u32;16],nc0:usize,best0:usize,
 after:&[u32;16],nc:usize,best:usize){
 assert!(nc0<=16&&nc<=16&&nc>=nc0&&nc<=nc0+1&&best>=best0&&best<=cap);
 assert_eq!(&before[..nc0],&after[..nc0],"supplement changed original candidate prefix");
 for &m in &after[..nc]{assert!(valid(s,p,(m&511)as usize,(m>>9)as usize),"invalid retained/supplemental match");}
 let eligible=old>0&&old<=p&&nc0<16&&best0<cap&&p-(old-1)<=32768;
 COUNTS.with(|c|{let mut c=c.borrow_mut();c.0[1]+=1;c.0[5]+=nc0 as u64;c.1[bin(best0)]+=1;
  if eligible{c.0[2]+=1;}if nc0==16{c.0[6]+=1;}c.0[7]+=best0.saturating_sub(2)as u64;
  if nc>nc0{assert!(eligible&&best>best0);let m=after[nc0];assert_eq!((m&511)as usize,best);
   c.0[3]+=1;c.0[4]+=(best-best0)as u64;c.0[8]+=(best-best0)as u64;c.2[bin(best0)]+=1;
  }else{assert_eq!(best,best0);}
 });
}
fn reset(){COUNTS.with(|s|*s.borrow_mut()=([0;9],[0;8],[0;8]));}
fn counters()->([u64;9],[u64;8],[u64;8]){COUNTS.with(|s|*s.borrow())}
fn tokens(s:&[u8],f:Parser)->Vec<u32>{let mut out=vec![0;s.len()];let n=f(s,&mut out);assert!(n<=s.len());out.truncate(n);out}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for &t in ts{
 if t<256{if out.len()>=s.len(){return false;}out.push(t as u8)}else{
  if t<16777216{return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;
  if d>32768||d>out.len()||l>258||out.len()+l>s.len(){return false}
  for _ in 0..l{let b=out[out.len()-d];out.push(b)}
 }}out==s}
fn sample(n:usize,mode:usize,mut z:u64)->Vec<u8>{
 let text=b"The quick brown fox, record 0123456789; fn result(value) { return value + 1; }\n";
 let prose=b"the quick brown fox walks through the garden and returns home ";
 let structured=b"2026-10-07,10002345,1234.55,region=002,code=200\n";
 let mut v=Vec::with_capacity(n);for i in 0..n{z^=z<<13;z^=z>>7;z^=z<<17;
  v.push(match mode{0=>(z>>24)as u8,1=>text[i%text.len()],2=>if z%79==0{(z%95+32)as u8}else{text[i%text.len()]},
  3=>if i%2==0{0xbf}else{z as u8},4=>if z%31==0{z as u8}else{0},5=>b"ACGT\n"[(z%5)as usize],
  6=>prose[i%prose.len()],_=>structured[i%structured.len()]})}
 if mode==0&&n>65536{for d in [16383,16384,16385,32767,32768,32769]{for j in 0..257{
  if 1024+d+j<n{v[1024+d+j]=v[1024+j]}}}}v
}
fn check(index:usize,kind:&str,s:&[u8],cases:&[(&str,Parser,Parser)]){
 let parent=tokens(s,parent::parse);assert!(decode(s,&parent));
 for (name,plain,observed) in cases{
  let a=tokens(s,*plain);let repeat=tokens(s,*plain);reset();let b=tokens(s,*observed);
  assert_eq!(a,repeat,"candidate nondeterminism");assert_eq!(a,b,"instrumentation changed candidate tokens");
  assert!(decode(s,&a),"candidate decode failed");let(c,h,w)=counters();
  let class=parent::route_class(s);let engine=parent::CLASS_TAB[class%16][0];
  println!("R10_FINDER {{\"index\":{},\"kind\":\"{}\",\"candidate\":\"{}\",\"input_bytes\":{},\"class\":{},\"engine\":{},\"tokens\":{},\"parent_tokens_equal\":{},\"repeat_tokens_equal\":true,\"observed_tokens_equal\":true,\"decode_ok\":true,\"counts\":{:?},\"before_length_hist\":{:?},\"winner_before_length_hist\":{:?}}}",index,kind,name,s.len(),class,engine,a.len(),a==parent,c,h,w);
 }
}
fn main(){let cases:&[(&str,Parser,Parser)]=&[CASES];let mut index=0;
 for path in std::env::args_os().skip(1){println!("R10_BEGIN {}",index);let s=std::fs::read(path).unwrap();check(index,"public",&s,cases);index+=1;}
 for n in [0,1,3,4,7,8,15,16,17,31,32,257,258,259,1023,16383,16384,16385,32767,32768,32769,65535,65536,65537,98305,131073]{
  for mode in 0..8{for seed in [1,987654321]{let s=sample(n,mode,seed);check(index,"synthetic",&s,cases);index+=1;}}
 }
 println!("R10_COMPLETE {}",index);
}
'''


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def instrument(source: str) -> str:
    if "crate::observe_" in source or source.count(ANCHOR) != 1:
        raise ValueError("Supplement observation anchor changed or already instrumented")
    changed = source.replace(ANCHOR, OBSERVED, 1)
    marker = "pub fn r10_cache_store("
    if changed.count(marker) != 1:
        raise ValueError("Expected exactly one supplemental store")
    position = changed.index("{", changed.index(marker)) + 1
    callback = "\n    crate::observe_store();"
    changed = changed[:position] + callback + changed[position:]
    if changed.replace(callback, "", 1).replace(OBSERVED, ANCHOR, 1) != source:
        raise ValueError("Observation source reverse audit failed")
    return changed


def save(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2, allow_nan=False) + "\n", encoding="utf-8")


def run_logged(command: list[str], path: Path, timeout: int) -> subprocess.CompletedProcess:
    try:
        result = subprocess.run(command, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired as error:
        def decode(value):
            return value.decode("utf-8", errors="replace") if isinstance(value, bytes) else value or ""
        path.write_text(decode(error.stdout) + decode(error.stderr), encoding="utf-8")
        raise
    path.write_text(result.stdout + result.stderr, encoding="utf-8")
    return result


def parse_rows(stdout: str, names: list[str]) -> list[dict]:
    rows = []
    seen = set()
    for line in stdout.splitlines():
        if not line.startswith("R10_FINDER "):
            continue
        row = json.loads(line.removeprefix("R10_FINDER "))
        key = row["index"], row["candidate"]
        if key in seen or row["candidate"] not in names:
            raise ValueError("Unexpected/duplicate diagnostic row")
        seen.add(key)
        counts = row.pop("counts")
        h = row["before_length_hist"]; w = row["winner_before_length_hist"]
        if len(counts) != len(COUNTERS) or len(h) != 8 or len(w) != 8:
            raise ValueError("Finder counter schema mismatch")
        if any(type(v) is not int or v < 0 for v in counts + h + w):
            raise ValueError("Invalid finder diagnostic counter")
        row.update(zip(COUNTERS, counts))
        if sum(h) != row["searched_positions"] or sum(w) != row["added_longer_records"]:
            raise ValueError("Finder histogram mismatch")
        if row["added_longer_records"] > row["eligible_cache_probes"] or row["new_supported_lengths"] != row["added_max_length_bytes"]:
            raise ValueError("Finder coverage mismatch")
        rows.append(row)
    expected = {(i, name) for i in range(444) for name in names}
    if seen != expected or not stdout.rstrip().endswith("R10_COMPLETE 444"):
        raise ValueError("Finite public+synthetic diagnostic incomplete")
    return rows


def main() -> None:
    from round4 import specification_path
    label = os.environ.get("ROUND4_SPEC")
    if not label:
        print("ROUND10_FINDER_DIAGNOSTIC_NOT_REQUESTED", flush=True); return
    spec = json.loads(specification_path(label).read_text(encoding="utf-8"))
    if spec.get("finder_diagnostics") is not True:
        print("ROUND10_FINDER_DIAGNOSTIC_NOT_REQUESTED", flush=True); return
    if not (sys.platform == "linux" and os.environ.get("GITHUB_ACTIONS") == "true"
            and os.environ.get("RUNNER_OS") == "Linux"
            and os.environ.get("GITHUB_REPOSITORY") == "HuanHuanHuanFFF/Miner"):
        raise SystemExit("Run only in this repository's Linux GitHub Actions runner")
    entries = [entry for entry in spec["entries"] if entry["name"] in NAMES]
    if not entries:
        raise ValueError("Finder diagnostic requested without a supported candidate")
    temp = Path(os.environ["RUNNER_TEMP"]).resolve(strict=True)
    build = temp / "round10-finder-build"
    output = temp / "round4-receipts/finder-diagnostics"
    for directory in (build, output):
        if not directory.resolve().is_relative_to(temp):
            raise ValueError("Temporary finder path escaped RUNNER_TEMP")
        directory.mkdir(parents=True, exist_ok=True)
    receipt = output / "finder-diagnostics.json"
    report = {
        "status": "NOT_RUN", "created_at": datetime.now(timezone.utc).isoformat(),
        "run_id": os.environ.get("GITHUB_RUN_ID"), "git_sha": os.environ.get("GITHUB_SHA"),
        "scope": "444 finite public/synthetic decode and repeat checks per candidate; each observed candidate must preserve all original records at visited search positions",
        "coverage_scope": "Supplement integrated into each candidate's evolving parse schedule; opportunities across different candidates are not comparisons at an identical fixed baseline schedule",
        "not_measured": "No encoder, official axes, whole-input optimality, private behavior, full Lean gate, admission or reward",
        "length_hist_bins": ["<3", "3", "4..7", "8..15", "16..31", "32..63", "64..127", "128..258"],
        "script_sha256": sha(Path(__file__).read_bytes()), "source_hashes": {}, "records": [],
    }
    save(receipt, report)
    try:
        modules = ['#[path="parent.rs"] mod parent;']; cases = []
        parent_raw = (ROOT / "candidates/r9-block-scalar/parse.rs").read_bytes()
        expected_parent = "faf1d7281678d12c3243002121feecdd0ea139633dea197dbc77d86fb6319257"
        if sha(parent_raw) != expected_parent:
            raise ValueError("Pinned scalar parent changed")
        (build / "parent.rs").write_bytes(parent_raw)
        report["source_hashes"]["parent"] = expected_parent
        for i, entry in enumerate(entries):
            path = (ROOT / entry["path"] / "parse.rs").resolve()
            if not path.is_relative_to(ROOT.resolve()):
                raise ValueError("Candidate source escaped repository")
            raw = path.read_bytes(); expected = entry["hashes"]["parse.rs"]
            if sha(raw) != expected:
                raise ValueError("Spec candidate source hash changed")
            source = raw.decode("utf-8").replace("\r\n", "\n")
            copied = instrument(source)
            (build / f"candidate{i}.rs").write_text(source, encoding="utf-8")
            (build / f"observed{i}.rs").write_text(copied, encoding="utf-8")
            modules.extend([f'#[path="candidate{i}.rs"] mod candidate{i};', f'#[path="observed{i}.rs"] mod observed{i};'])
            cases.append(f'({json.dumps(entry["name"])},candidate{i}::parse,observed{i}::parse)')
            report["source_hashes"][entry["name"]] = {"path": entry["path"], "sha256": expected,
                "observed_sha256": sha(copied.encode("utf-8"))}
        source = build / "finder.rs"
        source.write_text(HARNESS.replace("MODULES", "\n".join(modules)).replace("CASES", ",".join(cases)), encoding="utf-8")
        report["harness_sha256"] = sha(source.read_bytes())
        corpus = Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1"
        paths = sorted(path for path in corpus.iterdir() if path.is_file())
        if len(paths) != 28:
            raise ValueError("Expected 28 public corpus files")
        report["public_inputs"] = [{"file": path.name, "bytes": path.stat().st_size, "sha256": sha(path.read_bytes())} for path in paths]
        binary = build / "finder"
        command = ["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes", str(source), "-o", str(binary)]
        report.update(status="BUILD_PENDING", compile_command=command); save(receipt, report)
        compiled = run_logged(command, output / "build.log", 180)
        report["compile_exit"] = compiled.returncode
        if compiled.returncode:
            raise RuntimeError("Finder diagnostic build failed; inspect build.log")
        report["status"] = "RUNTIME_PENDING"; save(receipt, report)
        measured = run_logged([str(binary), *map(str, paths)], output / "runtime.log", 360)
        report["runtime_exit"] = measured.returncode
        if measured.returncode:
            raise RuntimeError("Finder diagnostic runtime failed; inspect retained runtime.log")
        names = [entry["name"] for entry in entries]
        report["records"] = parse_rows(measured.stdout, names)
        report["totals"] = {name: {kind: {key: sum(row[key] for row in report["records"]
            if row["candidate"] == name and row["kind"] == kind) for key in COUNTERS}
            for kind in ("public", "synthetic")} for name in names}
        report.update(status="VERIFIED_FINITE_DIAGNOSTIC_ONLY", completed_at=datetime.now(timezone.utc).isoformat())
        save(receipt, report)
        print("ROUND10_FINDER_DIAGNOSTIC", json.dumps({"status": report["status"], "cases_per_candidate": 444, "totals": report["totals"]}), flush=True)
    except Exception as error:
        report.update(status="DIAGNOSTIC_FAILED", error=f"{type(error).__name__}: {error}")
        save(receipt, report)
        raise


if __name__ == "__main__":
    main()
