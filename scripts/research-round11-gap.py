"""CI-only, output-preserving counts for the frozen pipeline d_gap.

The instrumented copy executes the original scalar decisions. Opportunity
counts are source-operation counts, never timers, official axes or proof gates.
"""
from __future__ import annotations

import hashlib
import importlib.util
import json
import os
from pathlib import Path

from round4 import ROOT, save, validate
from round3_synthetic import inputs as synthetic_inputs

_spec = importlib.util.spec_from_file_location("r11_log_helpers", ROOT / "scripts/research-round9-phases.py")
_helper = importlib.util.module_from_spec(_spec)
assert _spec.loader is not None
_spec.loader.exec_module(_helper)
run_logged, failure_receipt = _helper.run_logged, _helper.failure_receipt

BASE_SHA = "b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf"
LEAN_SHA = "e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db"
FIELDS = (
    "gap_calls", "phase0_bytes", "phase1_bytes", "third_bytes", "third_nonempty_calls",
    "third_strict_cont", "third_literal", "third_full_cell_equal", "high_cost_tie",
    "high_cost_tie_cont_choice_lower", "high_cost_tie_literal_choice_lower",
    "dlit_zero_calls", "dlit_D_LIT_calls", "dlit_other_calls", "dlit_high_calls",
    "zero_literal_bytes", "zero_literal_strict_cont", "zero_literal_not_strict_cont",
    "literal_cost32_wrap", "continuation_cost32_trunc", "kc_cost32_high",
    "kc_add64_wrap", "continuation_add64_wrap", "choice_add64_wrap", "choice_high32",
    "choice_ge_D_LIT", "rem_lt3", "rem_gt258", "rem_mod512_boundary",
    "third_not_below_lo", "lc_platform_changes", "lc_platforms",
    "strict_seeds_oracle", "strict_seeds_guard", "oracle_safe_bytes_after_seed",
    "guard_safe_bytes_after_seed", "oracle_seed_only", "guard_seed_only",
    "oracle_segments", "guard_segments", "oracle_physical_segments", "guard_physical_segments",
    "oracle_stopped_platform", "guard_stopped_platform", "oracle_stopped_condition",
    "guard_stopped_condition", "oracle_stopped_call", "guard_stopped_call",
    "ring_wrap_boundaries", "guard_rejected_price_max", "guard_rejected_zero_choice",
    "guard_rejected_generic", "oracle_rejected_price_wrap", "oracle_rejected_zero_choice",
    "oracle_rejected_generic", "third_array_guard_stop", "third_end_guard_stop",
    "gap_call_boundary", "third_stop_boundary", "table_loads", "metadata_literal_reads",
    "metadata_length_reads", "metadata_price_comparisons", "zero_price_table_epochs",
)
HISTOGRAMS = ("lc_platform", "strict_cont_run", "oracle_after_seed", "guard_after_seed",
              "oracle_physical", "guard_physical")
BUCKETS = ("1", "2", "3", "4..7", "8..15", "16..31", "32..63", "64..127", "128..255", ">=256")

SUPPORT = r'''
use std::sync::Mutex;
struct R11All {
    c: [u64; R11_N], h: [[u64; 10]; 6], epoch: u64, tb: usize,
    minlit: u32, maxlit: u32, owner: usize, block: usize,
    tables: Vec<[u64; 6]>, samples: Vec<String>, margin: u64,
}
static R11_ALL: Mutex<R11All> = Mutex::new(R11All {
    c: [0; R11_N], h: [[0; 10]; 6], epoch: 0, tb: 0,
    minlit: 0, maxlit: 0, owner: 0, block: 0,
    tables: Vec::new(), samples: Vec::new(), margin: u64::MAX,
});
pub fn r11_reset() {
    let mut a = R11_ALL.lock().unwrap();
    a.c = [0; R11_N]; a.h = [[0; 10]; 6]; a.epoch = 0;
    a.tables.clear(); a.samples.clear(); a.margin = u64::MAX;
}
pub fn r11_json() -> String {
    let a = R11_ALL.lock().unwrap();
    format!("{{\"counts\":{:?},\"histograms\":{:?},\"table_epochs\":{:?},\"samples\":{:?},\"min_literal_margin\":{}}}",
            a.c, a.h, a.tables, a.samples, a.margin)
}
fn r11_load(tb: usize, litc: &[u32; 256], lc: &[u32; 512]) {
    let mut min = u32::MAX; let mut max = 0; let mut zeros = 0;
    for &x in litc { min = min.min(x); max = max.max(x); zeros += (x == 0) as usize; }
    let mut platforms = 0; let mut previous = None;
    for &x in lc { platforms += (previous != Some(x)) as usize; previous = Some(x); }
    let mut a = R11_ALL.lock().unwrap(); a.epoch += 1; a.tb = tb; a.minlit = min; a.maxlit = max;
    a.c[TABLE_LOADS] += 1; a.c[METADATA_LITERAL_READS] += 256;
    a.c[METADATA_LENGTH_READS] += 512; a.c[METADATA_PRICE_COMPARISONS] += 3 * 256 + 512;
    a.c[ZERO_PRICE_TABLE_EPOCHS] += (zeros != 0) as u64;
    let epoch = a.epoch;
    a.tables.push([epoch, tb as u64, min as u64, max as u64, zeros as u64, platforms as u64]);
}
fn r11_owner(owner: usize, block: usize) {
    let mut a = R11_ALL.lock().unwrap(); a.owner = owner; a.block = block;
}
fn r11_bin(n: usize) -> usize {
    match n { 0 | 1 => 0, 2 => 1, 3 => 2, 4..=7 => 3, 8..=15 => 4,
        16..=31 => 5, 32..=63 => 6, 64..=127 => 7, 128..=255 => 8, _ => 9 }
}
struct R11Gap {
    c: [u64; R11_N], h: [[u64; 10]; 6], minlit: u32, maxlit: u32,
    epoch: u64, owner: usize, block: usize, hi: usize, stop: usize, end: usize,
    lo: usize, chd: u64, dlit: u64, kcd: u64,
    previous_l: Option<u32>, platform: usize, strict: usize,
    active: [bool; 2], span: [usize; 2], physical: [usize; 2],
    margin: u64, samples: Vec<String>, entry_q: usize, entry_nxt: u64,
}
impl R11Gap {
    fn new(hi: usize, stop: usize, end: usize, lo: usize, chd: u64, dlit: u64, kcd: u64) -> Self {
        let a = R11_ALL.lock().unwrap();
        let mut z = Self { c: [0; R11_N], h: [[0; 10]; 6], minlit: a.minlit, maxlit: a.maxlit,
            epoch: a.epoch, owner: a.owner, block: a.block, hi, stop, end, lo, chd, dlit, kcd,
            previous_l: None, platform: 0, strict: 0, active: [false; 2], span: [0; 2],
            physical: [0; 2], margin: u64::MAX, samples: Vec::new(), entry_q: 0, entry_nxt: 0 };
        z.c[GAP_CALLS] = 1; z.c[GAP_CALL_BOUNDARY] = 1;
        z.c[if dlit == 0 { DLIT_ZERO_CALLS } else if dlit == D_LIT { DLIT_D_LIT_CALLS } else { DLIT_OTHER_CALLS }] += 1;
        z.c[DLIT_HIGH_CALLS] += (dlit >> 32 != 0) as u64; z
    }
    fn finish_span(&mut self, i: usize, why: usize) {
        if !self.active[i] { return; }
        self.c[why] += 1;
        if self.span[i] == 0 { self.c[if i == 0 { ORACLE_SEED_ONLY } else { GUARD_SEED_ONLY }] += 1; }
        else { self.h[2+i][r11_bin(self.span[i])] += 1;
            self.c[if i == 0 { ORACLE_SEGMENTS } else { GUARD_SEGMENTS }] += 1; }
        self.finish_physical(i); self.active[i] = false; self.span[i] = 0;
    }
    fn finish_physical(&mut self, i: usize) {
        if self.physical[i] != 0 {
            self.h[4+i][r11_bin(self.physical[i])] += 1;
            self.c[if i == 0 { ORACLE_PHYSICAL_SEGMENTS } else { GUARD_PHYSICAL_SEGMENTS }] += 1;
            self.physical[i] = 0;
        }
    }
    fn step(&mut self, q: usize, rem: usize, nxt: u64, kc: u64, l: u32, price: u32, vc: u64, vl: u64, v: u64) {
        const M: u64 = 1u64 << 32;
        let first = self.c[THIRD_BYTES] == 0;
        if first { self.entry_q = q + 1; self.entry_nxt = nxt; self.c[THIRD_NONEMPTY_CALLS] += 1; }
        self.c[THIRD_BYTES] += 1;
        let won = vc < vl;
        self.c[if won { THIRD_STRICT_CONT } else if vc == vl { THIRD_FULL_CELL_EQUAL } else { THIRD_LITERAL }] += 1;
        if vc >> 32 == vl >> 32 {
            self.c[HIGH_COST_TIE] += 1;
            self.c[HIGH_COST_TIE_CONT_CHOICE_LOWER] += ((vc as u32) < (vl as u32)) as u64;
            self.c[HIGH_COST_TIE_LITERAL_CHOICE_LOWER] += ((vl as u32) < (vc as u32)) as u64;
        }
        if price == 0 { self.c[ZERO_LITERAL_BYTES] += 1;
            self.c[if won { ZERO_LITERAL_STRICT_CONT } else { ZERO_LITERAL_NOT_STRICT_CONT }] += 1; }
        self.c[LITERAL_COST32_WRAP] += ((nxt >> 32) + price as u64 >= M) as u64;
        self.c[CONTINUATION_COST32_TRUNC] += (kc as u128 + l as u128 >= M as u128) as u64;
        self.c[KC_COST32_HIGH] += (kc >= M) as u64;
        self.c[CONTINUATION_ADD64_WRAP] += (kc.checked_add(l as u64).is_none()) as u64;
        self.c[CHOICE_ADD64_WRAP] += (self.chd.checked_add(rem as u64).is_none()) as u64;
        let choice128 = self.chd as u128 + rem as u128;
        self.c[CHOICE_HIGH32] += (choice128 >= M as u128) as u64;
        self.c[CHOICE_GE_D_LIT] += (choice128 >= D_LIT as u128) as u64;
        self.c[REM_LT3] += (rem < 3) as u64; self.c[REM_GT258] += (rem > 258) as u64;
        self.c[REM_MOD512_BOUNDARY] += (rem % 512 == 0) as u64;
        self.c[THIRD_NOT_BELOW_LO] += (q >= self.lo) as u64;
        assert!(q < self.lo, "third segment reached pending-push position q={} lo={}", q, self.lo);
        let same = self.previous_l == Some(l);
        if !same {
            if self.platform != 0 { self.h[0][r11_bin(self.platform)] += 1; self.c[LC_PLATFORM_CHANGES] += 1; }
            self.platform = 0; self.c[LC_PLATFORMS] += 1;
            self.finish_span(0, ORACLE_STOPPED_PLATFORM); self.finish_span(1, GUARD_STOPPED_PLATFORM);
        }
        self.platform += 1; self.previous_l = Some(l);
        if won { self.strict += 1; } else if self.strict != 0 { self.h[1][r11_bin(self.strict)] += 1; self.strict = 0; }
        let cost = kc.wrapping_add(l as u64) as u32 as u64;
        self.margin = self.margin.min(M - 1 - cost);
        let generic = choice128 < M as u128 && self.dlit < M && rem >= 3 && rem <= 258
            && (self.dlit == 0 || self.dlit == D_LIT);
        let no_wrap = cost + (price as u64) < M;
        let zero_ok = price > 0 || choice128 <= self.dlit as u128;
        let max_ok = cost + (self.maxlit as u64) < M;
        let min_ok = self.minlit > 0 || choice128 <= self.dlit as u128;
        let cond = [generic && no_wrap && zero_ok, generic && max_ok && min_ok];
        self.c[ORACLE_REJECTED_GENERIC] += (!generic) as u64;
        self.c[GUARD_REJECTED_GENERIC] += (!generic) as u64;
        self.c[ORACLE_REJECTED_PRICE_WRAP] += (!no_wrap) as u64;
        self.c[ORACLE_REJECTED_ZERO_CHOICE] += (!zero_ok) as u64;
        self.c[GUARD_REJECTED_PRICE_MAX] += (!max_ok) as u64;
        self.c[GUARD_REJECTED_ZERO_CHOICE] += (!min_ok) as u64;
        if !first && q % D_RING == D_RING - 1 {
            self.c[RING_WRAP_BOUNDARIES] += 1;
            self.finish_physical(0); self.finish_physical(1);
        }
        for i in 0..2 {
            if self.active[i] && same && cond[i] && nxt >> 32 == cost {
                assert_eq!(v, vc, "safe predicate failed owner={} epoch={} q={} rem={} kc={} l={} price={} chd={} dlit={} nxt={} vc={} vl={}",
                    self.owner, self.epoch, q, rem, kc, l, price, self.chd, self.dlit, nxt, vc, vl);
                self.span[i] += 1; self.physical[i] += 1;
                self.c[if i == 0 { ORACLE_SAFE_BYTES_AFTER_SEED } else { GUARD_SAFE_BYTES_AFTER_SEED }] += 1;
            } else {
                self.finish_span(i, if i == 0 { ORACLE_STOPPED_CONDITION } else { GUARD_STOPPED_CONDITION });
                if won && generic {
                    self.active[i] = true;
                    self.c[if i == 0 { STRICT_SEEDS_ORACLE } else { STRICT_SEEDS_GUARD }] += 1;
                }
            }
        }
    }
    fn finish(mut self, q: usize, nxt: u64, kc: u64, s_len: usize, out_len: usize) {
        if self.platform != 0 { self.h[0][r11_bin(self.platform)] += 1; }
        if self.strict != 0 { self.h[1][r11_bin(self.strict)] += 1; }
        self.finish_span(0, ORACLE_STOPPED_CALL); self.finish_span(1, GUARD_STOPPED_CALL);
        self.c[THIRD_ARRAY_GUARD_STOP] += (q > s_len || q > out_len) as u64;
        self.c[THIRD_END_GUARD_STOP] += (self.end < q) as u64;
        self.c[THIRD_STOP_BOUNDARY] += (q == self.stop) as u64;
        if self.c[THIRD_BYTES] >= 32 {
            self.samples.push(format!("owner={} block={} epoch={} hi={} stop={} end={} lo={} kcd={} chd={} dlit={} kc={} third_entry_q={} third_entry_nxt={} exit_q={} exit_nxt={} third_bytes={} guard_after_seed={}",
                self.owner, self.block, self.epoch, self.hi, self.stop, self.end, self.lo, self.kcd,
                self.chd, self.dlit, kc, self.entry_q, self.entry_nxt, q, nxt, self.c[THIRD_BYTES], self.c[GUARD_SAFE_BYTES_AFTER_SEED]));
        }
        let mut a = R11_ALL.lock().unwrap();
        for j in 0..R11_N { a.c[j] += self.c[j]; }
        for j in 0..6 { for k in 0..10 { a.h[j][k] += self.h[j][k]; } }
        a.margin = a.margin.min(self.margin);
        for sample in self.samples { if a.samples.len() < 16 { a.samples.push(sample); } }
    }
}
'''

HARNESS = r'''
#![allow(dead_code, unused_variables)]
#[path="frozen.rs"] mod frozen;
#[path="instrumented.rs"] mod observed;
fn quote(s: &str) -> String { format!("\"{}\"", s.replace('\\', "\\\\").replace('"', "\\\"")) }
fn decode(src: &[u8], tokens: &[u32]) -> bool {
    let mut out = Vec::with_capacity(src.len());
    for &t in tokens {
        if t < 256 { out.push(t as u8); } else {
            if t < 16777216 { return false; }
            let v = t - 16777216; let d = (v / 256 + 1) as usize; let n = (v % 256 + 3) as usize;
            if d > 32768 || d > out.len() || n > 258 || out.len().saturating_add(n) > src.len() { return false; }
            for _ in 0..n { let b = out[out.len()-d]; out.push(b); }
        }
    }
    out == src
}
fn main() {
    for (index, file) in std::env::args_os().skip(1).enumerate() {
        let name = file.to_string_lossy(); let input = std::fs::read(&file).unwrap();
        let mut a = vec![0; input.len()]; let mut b = vec![0; input.len()];
        let an = frozen::parse(&input, &mut a); observed::r11_reset();
        let bn = observed::parse(&input, &mut b);
        assert!(an <= input.len() && bn <= input.len());
        assert_eq!(a[..an], b[..bn], "observer changed tokens {}", name);
        assert!(decode(&input, &a[..an]) && decode(&input, &b[..bn]), "decode failed {}", name);
        println!("R11_GAP {{\"file_index\":{},\"file\":{},\"bytes\":{},\"tokens\":{},\"tokens_equal\":true,\"decode\":true,\"diagnostics\":{}}}",
            index, quote(&name), input.len(), an, observed::r11_json());
    }
}
'''


def replace_once(source: str, old: str, new: str, label: str) -> str:
    assert source.count(old) == 1, (label, source.count(old))
    return source.replace(old, new, 1)


def instrument(source: str) -> str:
    assert "R11Gap" not in source
    frozen_source = source
    # Limit loop anchors to d_gap; original comparisons, stores and returns stay intact.
    start, end = source.index("pub fn d_gap("), source.index("\npub fn ", source.index("pub fn d_gap(") + 1)
    original = source[start:end]
    body = replace_once(original, "    let mut q = hi;", "    let mut r11 = R11Gap::new(hi, stop, end, lo, chd, dlit, kcd);\n    let mut q = hi;", "gap observer")
    body = replace_once(body, "while q > mid && q <= s.len() && q <= out.len() {", "while q > mid && q <= s.len() && q <= out.len() {\n        r11.c[PHASE0_BYTES] += 1;", "literal phase")
    body = replace_once(body, "while q > s1 && q <= s.len() && q <= out.len() && end >= q {", "while q > s1 && q <= s.len() && q <= out.len() && end >= q {\n        r11.c[PHASE1_BYTES] += 1;", "pending phase")
    body = replace_once(body, "let kc = (d_cell(ring, end) >> 32).wrapping_add(kcd);", "let r11_kc_base = d_cell(ring, end) >> 32;\n    r11.c[KC_ADD64_WRAP] += r11_kc_base.checked_add(kcd).is_none() as u64;\n    let kc = (d_cell(ring, end) >> 32).wrapping_add(kcd);", "kc wrap observation")
    body = replace_once(body, "        let v = if vc < vl { vc } else { vl };", "        let v = if vc < vl { vc } else { vl };\n        r11.step(q, rem, nxt, kc, lc[rem % 512], litc[s[q] as usize], vc, vl, v);", "third step")
    body = replace_once(body, "    nxt\n}", "    r11.finish(q, nxt, kc, s.len(), out.len());\n    nxt\n}", "gap observer finish")
    source = source[:start] + body + source[end:]
    start, end = source.index("pub fn d_load("), source.index("\n}", source.index("pub fn d_load("))
    source = source[:end] + "\n    r11_load(tb, litc, lc);" + source[end:]
    source = replace_once(source, "                nxt = d_gap(s, &litc, &lc,", "                r11_owner(p, bs[0]);\n                nxt = d_gap(s, &litc, &lc,", "owner context")
    # Removing all injected observations recovers every original source byte.
    reversed_source = replace_once(source, "\n    r11_load(tb, litc, lc);", "", "reverse load")
    reversed_source = replace_once(reversed_source, "                r11_owner(p, bs[0]);\n", "", "reverse owner")
    reversed_source = replace_once(reversed_source, body, original, "reverse gap body")
    assert reversed_source == frozen_source
    constants = "\nconst R11_N: usize = " + str(len(FIELDS)) + ";\n" + "\n".join(f"const {name.upper()}: usize = {i};" for i, name in enumerate(FIELDS))
    return source + constants + SUPPORT


def run_candidate_checks(spec):
    """Finite loaded-table/rs checks, separate from the observer and full gate."""
    groups = bool(spec.get("gap_groups_checks"))
    name = "r11-gap-groups" if groups else "r11-gap-meta"
    rust_pin = "6ef07be874052d23fbe3cdca8de7e311e82a306338a93f70389fe35006e99992" if groups else "25bd4ee52560288f36c73f813a769345044cab2c4924705e6c4c92a64c017de6"
    harness_pin = "fc7c3e0faaaf88e0cd4345eb7e47a87127e1186db854d44494e2118827f5d880" if groups else "24b6fb47cb660bcb3c57554c01f9a16178d054a472b2efa5baab4928f200aeca"
    corrected = groups and spec.get("gap_groups_check_v2", False)
    if corrected:
        harness_pin = "5e791ea2a9176cfcfd951ccf9bb5a15857276292bd72de2abc37b347579a9959"
    marker = "R11_GAP_GROUPS_BOUNDARY " if groups else "R11_GAP_BOUNDARY "
    prefix = "groups-checks" if groups else "candidate-checks"
    base = next(e for e in spec["entries"] if e["name"] == "r10-finder-pipeline-proof")
    entry = next(e for e in spec["entries"] if e["name"] == name)
    frozen = (ROOT / base["path"] / "parse.rs").read_bytes()
    candidate = (ROOT / entry["path"] / "parse.rs").read_bytes()
    harness = (ROOT / entry["path"] / ("native-helper-check-v2.rs" if corrected else "native-helper-check.rs")).read_bytes()
    assert hashlib.sha256(frozen).hexdigest() == base["hashes"]["parse.rs"] == BASE_SHA
    assert hashlib.sha256(candidate).hexdigest() == entry["hashes"]["parse.rs"] == rust_pin
    assert hashlib.sha256(harness).hexdigest() == harness_pin
    build = Path(os.environ["RUNNER_TEMP"]) / "round11-gap-checks"
    output = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/gap-diagnostics"
    build.mkdir(parents=True, exist_ok=True); output.mkdir(parents=True, exist_ok=True)
    (build / "frozen.rs").write_bytes(frozen); (build / "candidate.rs").write_bytes(candidate)
    (build / "main.rs").write_bytes(harness)
    report = {"status": "PENDING", "run_id": os.environ["GITHUB_RUN_ID"], "git_sha": os.environ["GITHUB_SHA"],
              "candidate": entry["name"], "frozen_source_sha256": BASE_SHA,
              "candidate_source_sha256": hashlib.sha256(candidate).hexdigest(),
              "harness_sha256": hashlib.sha256(harness).hexdigest(),
              "diagnostic_script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              "scope": "Finite generic-rs d_dp output equality, loaded-table metadata, reachable slot510, honest cost-wrap fallback; expected false-metadata counterexample. Not universal helper equivalence or a proof gate."}
    receipt = output / ("gap-groups-checks.json" if groups else "gap-candidate-checks.json"); save(receipt, report)
    with failure_receipt(report, receipt):
        binary = build / "gap-helper-checks"
        proc = run_logged(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes",
                           str(build / "main.rs"), "-o", str(binary)], output / (prefix + "-build.log"), 180)
        report["compile_exit"] = proc.returncode
        if proc.returncode: raise RuntimeError("Gap candidate helper compilation failed; retained log")
        proc = run_logged([str(binary)], output / (prefix + "-runtime.log"), 120)
        report["runtime_exit"] = proc.returncode
        if proc.returncode: raise RuntimeError("Gap candidate helper check failed; retained log")
        if corrected:
            extra = (ROOT / entry["path"] / "native-cross-ring-check.rs").read_bytes()
            assert hashlib.sha256(extra).hexdigest() == "5e4bf1f8dda7e27bd439787360c106b6a3fe6a7e227bbb2168b5e57dfab21aa0"
            extra_path = build / "cross.rs"; extra_path.write_bytes(extra)
            extra_binary = build / "gap-cross-checks"
            cp = run_logged(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes",
                             str(extra_path), "-o", str(extra_binary)], output / "cross-build.log", 180)
            assert cp.returncode == 0
            cp = run_logged([str(extra_binary)], output / "cross-runtime.log", 120)
            assert cp.returncode == 0
            report["additional_cross_ring_checks"] = {"harness_sha256": hashlib.sha256(extra).hexdigest(),
                                                      "compile_exit": 0, "runtime_exit": 0,
                                                      "stdout": cp.stdout}
        rows = [json.loads(s.removeprefix(marker)) for s in proc.stdout.splitlines() if s.startswith(marker)]
        assert len(rows) == 1 and rows[0]["loader_cases"] == (14 if groups else 10) and rows[0]["dp_cases"] == (2156 if groups else 1540)
        assert all(rows[0][key] for key in ("slot510_witness", "honest_wrap_fallback", "false_metadata_counterexample_expected"))
        report.update(status="VERIFIED_FINITE_GAP_HELPER_CHECKS", checks=rows[0],
                      limits=["False metadata intentionally fails semantic equivalence; only actual d_load_meta-origin metadata is trusted.",
                              "These finite malformed-rs checks do not prove all-input parse equivalence or replace444/public/full gate.",
                              "No benchmark or elapsed-time conclusion is drawn from this harness."])
        save(receipt, report); print("ROUND11_GAP_CHECKS", json.dumps(report))


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    assert os.environ.get("GITHUB_REPOSITORY") == "HuanHuanHuanFFF/Miner"
    spec = validate(os.environ["ROUND4_SPEC"])
    if spec.get("gap_candidate_checks") or spec.get("gap_groups_checks"):
        run_candidate_checks(spec)
    if not spec.get("gap_diagnostics"):
        print("ROUND11_GAP_NOT_REQUESTED")
        return
    entry = next(e for e in spec["entries"] if e["name"] == "r10-finder-pipeline-proof")
    raw = (ROOT / entry["path"] / "parse.rs").read_bytes()
    assert hashlib.sha256(raw).hexdigest() == entry["hashes"]["parse.rs"] == BASE_SHA
    assert entry["hashes"]["Parse.lean"] == LEAN_SHA
    source = raw.decode("utf-8")
    observed = instrument(source)
    assert source.encode("utf-8") == raw
    build = Path(os.environ["RUNNER_TEMP"]) / "round11-gap-build"
    output = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/gap-diagnostics"
    build.mkdir(parents=True, exist_ok=True); output.mkdir(parents=True, exist_ok=True)
    public = sorted(p for p in (Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1").iterdir() if p.is_file())
    assert len(public) == 28 and sum(p.stat().st_size for p in public) == 15_930_000
    generated = build / "synthetic"; generated.mkdir(exist_ok=True)
    extra = []
    for name, data in synthetic_inputs().items():
        path = generated / name; path.write_bytes(data); extra.append(path)
    files = public + extra
    assert len(files) == 36
    (build / "frozen.rs").write_bytes(raw)
    (build / "instrumented.rs").write_text(observed, encoding="utf-8")
    (build / "main.rs").write_text(HARNESS, encoding="utf-8")
    report = {"status": "PENDING", "run_id": os.environ["GITHUB_RUN_ID"], "git_sha": os.environ["GITHUB_SHA"],
              "candidate": entry["name"], "frozen_source_sha256": BASE_SHA, "lean_sha256": LEAN_SHA,
              "instrumented_source_sha256": hashlib.sha256((build / "instrumented.rs").read_bytes()).hexdigest(),
              "harness_sha256": hashlib.sha256((build / "main.rs").read_bytes()).hexdigest(),
              "diagnostic_script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              "synthetic_generator_sha256": hashlib.sha256((ROOT / "scripts/round3_synthetic.py").read_bytes()).hexdigest(),
              "counter_fields": list(FIELDS), "histogram_fields": list(HISTOGRAMS), "histogram_buckets": list(BUCKETS),
              "table_epoch_fields": ["load_epoch", "table_offset", "minlit", "maxlit", "zero_literal_entries", "actual_lc_platforms"],
              "scope": "Scalar d_gap operation counts and seed-excluding opportunities; no bulk replacement, timers or official score.",
              "corpus": [{"file": p.name, "kind": "public" if i < 28 else "fixed-generated", "bytes": p.stat().st_size,
                          "sha256": hashlib.sha256(p.read_bytes()).hexdigest()} for i, p in enumerate(files)]}
    receipt = output / "gap-diagnostics.json"; save(receipt, report)
    with failure_receipt(report, receipt):
        binary = build / "gap-counts"
        proc = run_logged(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes",
                           str(build / "main.rs"), "-o", str(binary)], output / "build.log", 180)
        report["compile_exit"] = proc.returncode
        if proc.returncode: raise RuntimeError("Gap observer compile failed; retained build.log")
        runtime = run_logged([str(binary), *map(str, files)], output / "runtime.log", 300)
        report["runtime_exit"] = runtime.returncode
        if runtime.returncode: raise RuntimeError("Gap observer token/decode/predicate check failed; retained runtime.log")
        rows = [json.loads(s.removeprefix("R11_GAP ")) for s in runtime.stdout.splitlines() if s.startswith("R11_GAP ")]
        assert len(rows) == 36 and [r["file_index"] for r in rows] == list(range(36))
        for row in rows:
            index = row["file_index"]; row.update(report["corpus"][index])
            d = row["diagnostics"]
            assert row["tokens_equal"] and row["decode"] and len(d["counts"]) == len(FIELDS)
            d["named_counts"] = dict(zip(FIELDS, d.pop("counts")))
            d["named_histograms"] = dict(zip(HISTOGRAMS, d.pop("histograms")))
            assert d["named_counts"]["third_not_below_lo"] == 0
            assert d["named_counts"]["guard_safe_bytes_after_seed"] <= d["named_counts"]["oracle_safe_bytes_after_seed"] <= d["named_counts"]["third_bytes"]
        totals = {kind: {key: sum(r["diagnostics"]["named_counts"][key] for r in rows if r["kind"] == kind) for key in FIELDS}
                  for kind in ("public", "fixed-generated")}
        hist_totals = {kind: {key: [sum(r["diagnostics"]["named_histograms"][key][j] for r in rows if r["kind"] == kind)
                                  for j in range(len(BUCKETS))] for key in HISTOGRAMS}
                       for kind in ("public", "fixed-generated")}
        report.update(status="VERIFIED_FINITE_GAP_OPERATION_COUNTS", files=rows, totals=totals, histogram_totals=hist_totals,
                      tokens_equal_all_files=True, all_decoded=True,
                      limits=["Observer perturbs execution. Counts are not machine loads, elapsed time or time fractions.",
                              "All opportunities exclude their scalar seed; physical ring splits do not automatically require new seeds.",
                              "Min/max/platform metadata are diagnostic scans once per actual d_load epoch; their production cost is unmeasured.",
                              "Conservative opportunity guard additionally restricts rem to 3..258 and dlit to 0/D_LIT; generic fallback stays necessary.",
                              "Finite 28 public plus 8 fixed generated token/decode checks do not prove universal equivalence or replace gate.",
                              "Safe opportunity cells are checked against the already-computed scalar v, without writing different cells."])
        save(receipt, report)
        print("ROUND11_GAP", json.dumps({"status": report["status"], "files": 36, "totals": totals}))


if __name__ == "__main__":
    main()
