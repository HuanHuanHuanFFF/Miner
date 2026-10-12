"""Frozen synthetic quality/decode diagnostic; no timing, tuning or candidate."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
import zlib

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = ROOT / "evidence/round25/sol"
DECLARATION = EVIDENCE / "heldout-quality-predeclared.json"
FROZEN_INPUTS = EVIDENCE / "heldout-quality-inputs.json"
CODEC_SHA = "172c240014f65d5e2762c1287e4982dd1cd426f2999f74e17011e05f2dc5fdec"
TOKEN_SHA = "8bf5d962324b3a0890f3c75f713198be086c4b0659797c24b8b976978cea4917"
SOURCES = {
    "combo": {"path": "candidates/r22-595-chain-halfhead", "hashes": {
        "parse.rs": "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275",
        "Parse.lean": "4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6"}},
    "end4": {"path": "candidates/r25-astra-end4", "hashes": {
        "parse.rs": "03ec0aa4e617d622755e85324a9d4fbc77ef74e6572485b3170e2790681ed8e6",
        "Parse.lean": "4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6"}},
    "tiny-pc8": {"path": "candidates/r25-astra-tiny-pc8-proof1", "hashes": {
        "parse.rs": "5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00",
        "Parse.lean": "3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8"}},
}

# BEGIN FROZEN_SYNTHETIC_GENERATOR
FAMILIES = ("json-config", "markdown-log", "c-source")
PRIMARY_LENGTHS = (12000, 400000)
PRIMARY_SEEDS = (0, 1, 2, 3)
CONTROL_LENGTHS = (196608,)
CONTROL_SEEDS = (0,)
SALTS = {"json-config": 0x6A09E667F3BCC909, "markdown-log": 0xBB67AE8584CAA73B,
         "c-source": 0x3C6EF372FE94F82B}
MAX_UNITS = 20000


class SplitMix64:
    def __init__(self, value):
        self.state = value & ((1 << 64) - 1)

    def next(self):
        mask = (1 << 64) - 1
        self.state = (self.state + 0x9E3779B97F4A7C15) & mask
        x = self.state
        x = ((x ^ (x >> 30)) * 0xBF58476D1CE4E5B9) & mask
        x = ((x ^ (x >> 27)) * 0x94D049BB133111EB) & mask
        return x ^ (x >> 31)

    def choose(self, choices):
        return choices[self.next() % len(choices)]


def content_unit(family, rng, index):
    """Own-authored structured templates; bounded vocabulary and variable fields."""
    service = rng.choose(("gateway", "worker", "catalog", "cache", "scheduler", "metrics"))
    mode = rng.choose(("ready", "waiting", "retry", "complete", "warm"))
    slot = rng.next() % 64
    count = rng.next() % 100000
    region = rng.choose(("north", "east", "west", "local"))
    if family == "json-config":
        obj = {
            "service": f"{service}-{slot}", "revision": index % 23,
            "enabled": bool(rng.next() & 1), "region": region,
            "limits": {"workers": 1 + rng.next() % 16, "timeout_ms": 50 + rng.next() % 950, "retry_count": rng.next() % 5},
            "routes": [{"path": f"/v1/items/{slot}", "method": "GET", "cache": mode},
                       {"path": "/v1/health", "method": "GET", "cache": "none"}],
            "labels": ["配置", "queue", "stable", service], "counter": count,
            "message": rng.choose(("keep the queue bounded", "retry after the next cycle", "use the local worker")),
        }
        return json.dumps(obj, sort_keys=True, ensure_ascii=False, separators=(",", ":")) + "\n"
    if family == "markdown-log":
        sentence = rng.choose((
            "The worker reads a batch, checks its status and records the completed items.",
            "A retry keeps the original request identifier and returns to the same queue.",
            "The cache stores recent entries while the scheduler waits for a free worker.",
            "The summary lists the pending jobs and the reason each job remains queued.",
        ))
        return (f"## Section {index % 31}: {service} / {region}\n\n"
                f"{sentence} 状态记录保持一致。\n\n"
                f"- batch: {slot}\n- state: {mode}\n- count: {count}\n"
                f"2026-01-01T{index % 24:02d}:{slot % 60:02d}:00Z INFO service={service} region={region} state={mode} count={count}\n"
                f"```text\nqueue/{service}/{slot} -> {mode}\n```\n\n")
    if family == "c-source":
        limit = 1 + rng.next() % 257
        return (f"/* module {service}, region {region}: 合成状态检查 */\n"
                f"static unsigned {service}_step_{slot}(unsigned value, unsigned flags) {{\n"
                f"    const unsigned limit = {limit}u;\n"
                f"    unsigned result = value ^ {count}u;\n"
                f"    for (unsigned i = 0; i < limit; ++i) {{\n"
                f"        result = (result + i + {index % 17}u) ^ (flags & 31u);\n"
                f"        if ((result & 7u) == 0u) {{ result += {slot}u; }}\n"
                f"    }}\n"
                f"    return result; /* {mode} */\n"
                f"}}\n\n")
    raise ValueError("unknown fixed family")


def generate_input(family, length, seed):
    assert family in FAMILIES and length in PRIMARY_LENGTHS + CONTROL_LENGTHS
    assert seed in PRIMARY_SEEDS
    rng = SplitMix64(SALTS[family] ^ seed)
    chunks = []
    total = 0
    units = 0
    while total < length:
        assert units < MAX_UNITS
        b = content_unit(family, rng, units).encode("utf-8")
        b.decode("utf-8", errors="strict")
        assert b and len(b) < 4096
        chunks.append(b); total += len(b); units += 1
    raw = b"".join(chunks)[:length]
    complete = raw.decode("utf-8", errors="ignore").encode("utf-8")
    padding = length - len(complete)
    assert 0 <= padding <= 3
    data = complete + b" " * padding
    assert len(data) == length
    data.decode("utf-8", errors="strict")
    return data, {"units": units, "padding_bytes": padding}


def fixed_matrix():
    cases = []
    for family in FAMILIES:
        for length in PRIMARY_LENGTHS:
            for seed in PRIMARY_SEEDS:
                cases.append(("primary", family, length, seed))
    for family in FAMILIES:
        for length in CONTROL_LENGTHS:
            for seed in CONTROL_SEEDS:
                cases.append(("inactive-control", family, length, seed))
    return cases
# END FROZEN_SYNTHETIC_GENERATOR


ROUTE_APPEND = r'''
// Untimed observation of actual original row/fallback entry; no classifier rerun.
static R25_HQ_HITS: [std::sync::atomic::AtomicU64; 33] =
    [const { std::sync::atomic::AtomicU64::new(0) }; 33];
fn r25_hq_hit(i: usize) { R25_HQ_HITS[i].fetch_add(1, std::sync::atomic::Ordering::Relaxed); }
pub fn r25_hq_take() -> [u64; 33] {
    std::array::from_fn(|i| R25_HQ_HITS[i].swap(0, std::sync::atomic::Ordering::Relaxed))
}
'''

HARNESS = r'''
#![allow(dead_code)]
#[path=HQ_TOKEN] mod token;
#[path=HQ_CODEC] mod codec;
HQ_MODULES
type Parser = fn(&[u8], &mut [u32]) -> usize;
type Routes = fn() -> [u64; 33];
fn parse(s: &[u8], f: Parser) -> Vec<u32> {
    let mut out = vec![0u32; s.len()]; let n = f(s, &mut out);
    assert!(n <= s.len()); out.truncate(n); out
}
fn decode(s: &[u8], ts: &[u32]) {
    let mut out = Vec::new();
    for &t in ts {
        match token::decode(t) {
            token::Token::Literal(x) => out.push(x),
            token::Token::Match { dist, len } => {
                assert!(dist >= 1 && dist as usize <= out.len() && out.len() + len as usize <= s.len());
                for _ in 0..len { let x = out[out.len() - dist as usize]; out.push(x); }
            },
            _ => panic!("invalid original token"),
        }
    }
    assert_eq!(out, s);
}
fn main() {
    let args: Vec<_> = std::env::args().collect(); let spool = std::path::Path::new(&args[2]);
    let cases: &[(&str, Parser, Parser, Routes)] = &[HQ_CASES];
    let mut files: Vec<_> = std::fs::read_dir(&args[1]).unwrap().map(|x| x.unwrap().path()).filter(|p| p.is_file()).collect();
    files.sort(); assert_eq!(files.len(), 27);
    for (i, p) in files.iter().enumerate() {
        let s = std::fs::read(p).unwrap(); assert!(std::str::from_utf8(&s).is_ok());
        let name = p.file_name().unwrap().to_str().unwrap();
        for &(label, frozen, observed, routes) in cases {
            let a = parse(&s, frozen); let b = parse(&s, observed);
            assert_eq!(a, b, "route observer token mismatch {} {}", label, name); decode(&s, &a);
            let hits = routes(); assert_eq!(hits.iter().sum::<u64>(), 1, "top-level route count");
            let route = hits.iter().position(|&v| v == 1).unwrap();
            let enc = codec::encode(&a, s.len()).unwrap(); let mut raw = Vec::new();
            for &t in &a { raw.extend(t.to_le_bytes()); }
            std::fs::write(spool.join(format!("{}-{}.tokens", i, label)), raw).unwrap();
            std::fs::write(spool.join(format!("{}-{}.deflate", i, label)), &enc).unwrap();
            println!("R25_HQ {} {} {} {} {} {}", label, i, name, enc.len(), a.len(), route);
        }
    }
}
'''


def sha(data):
    return hashlib.sha256(data).hexdigest()


def generator_sha():
    text = Path(__file__).read_bytes().replace(b"\r\n", b"\n")
    start = text.index(b"# BEGIN FROZEN_SYNTHETIC_GENERATOR\n")
    end = text.index(b"# END FROZEN_SYNTHETIC_GENERATOR\n", start)
    return sha(text[start:end])


def generated_cases():
    cases = []
    for cohort, family, length, seed in fixed_matrix():
        data, extra = generate_input(family, length, seed)
        case_id = f"{cohort}-{family}-n{length:06d}-s{seed}"
        cases.append({"case_id": case_id, "filename": case_id + ".utf8", "cohort": cohort, "family": family,
                      "raw_bytes": length, "seed": seed, "input_sha256": sha(data), "utf8": True, **extra})
    assert len(cases) == len({r["case_id"] for r in cases}) == len({r["input_sha256"] for r in cases}) == 27
    assert sum(r["raw_bytes"] for r in cases) == 5533824
    return cases


def input_manifest():
    return {"status": "FROZEN_SYNTHETIC_INPUT_HASHES_BEFORE_NATIVE_OUTPUTS", "generator_sha256": generator_sha(),
            "declaration_sha256": sha(DECLARATION.read_bytes()), "cases": generated_cases(),
            "counts": {"primary": 24, "inactive-control": 3}, "total_raw_bytes": 5533824,
            "scope": "Own-authored deterministic synthetic inputs, not private or official stage2; no result-dependent selection."}


def instrument(raw, source):
    assert sha(raw) == source["hashes"]["parse.rs"]
    original = raw.decode()
    pattern = re.compile(r"pub fn (p125_row(\d+))\([^\n]*?\)->usize\{")
    matches = list(pattern.finditer(original))
    assert sorted(int(m[2]) for m in matches) == list(range(17))
    insertions = [(m.end(), f"r25_hq_hit({m[2]});") for m in matches]
    fallback = re.search(r"pub fn fallback\([^\n]*?\)->usize\{", original)
    assert fallback is not None
    insertions.append((fallback.end(), "r25_hq_hit(32);"))
    bodies = {}
    for m in matches:
        end = m.end(); depth = 1
        while depth:
            if original[end] == "{": depth += 1
            if original[end] == "}": depth -= 1
            end += 1
        bodies[m[1]] = original[m.end():end - 1]
    observed = original
    for index, addition in sorted(insertions, reverse=True):
        observed = observed[:index] + addition + observed[index:]
    observed += ROUTE_APPEND
    reversed_source = observed.removesuffix(ROUTE_APPEND)
    for _, addition in insertions:
        assert reversed_source.count(addition) == 1
        reversed_source = reversed_source.replace(addition, "", 1)
    assert reversed_source.encode() == raw
    return observed.encode(), bodies


def preflight(spec=None, require_frozen=True):
    plan = json.loads(DECLARATION.read_bytes())
    assert plan["status"] == "PREDECLARED_BEFORE_INPUT_GENERATION_OR_ANY_ENCODER_OUTPUT"
    matrix = plan["matrix"]
    assert matrix["families"] == list(FAMILIES) and matrix["primary_lengths"] == list(PRIMARY_LENGTHS)
    assert matrix["primary_seeds"] == list(PRIMARY_SEEDS) and matrix["inactive_control_lengths"] == list(CONTROL_LENGTHS)
    assert matrix["inactive_control_seeds"] == list(CONTROL_SEEDS) and matrix["total_cases"] == 27
    assert matrix["total_raw_bytes"] == 5533824
    assert plan["generator"]["family_salts_hex"] == {f: f"{v:016x}" for f, v in SALTS.items()}
    observed = {}
    for name, s in SOURCES.items():
        assert plan["sources"][name] == {"path": s["path"], **s["hashes"]}
        for f, h in s["hashes"].items(): assert sha((ROOT / s["path"] / f).read_bytes()) == h
        raw, bodies = instrument((ROOT / s["path"] / "parse.rs").read_bytes(), s)
        observed[name] = {"source_hashes": s["hashes"], "observer_sha256": sha(raw), "row_bodies": bodies}
    inputs = input_manifest()
    if require_frozen: assert json.loads(FROZEN_INPUTS.read_bytes()) == inputs
    if spec is not None:
        assert spec.get("native_only") is True and spec.get("native_encoder") is False and spec.get("r25_heldout_quality") is True
        assert spec.get("gate_candidates", []) == [] and spec.get("extract_candidates", []) == []
        by = {e["name"]: e for e in spec["entries"]}
        for name, s in SOURCES.items():
            e = by[name]; assert e.get("control") and e["path"] == s["path"] and e["hashes"] == s["hashes"]
    return {"status": "VERIFIED_LOCAL_GENERATION_TEXT_HASH_AND_INPUT_SCHEMA_ONLY", "script_sha256": sha(Path(__file__).read_bytes()),
            "generator_sha256": inputs["generator_sha256"], "declaration_sha256": inputs["declaration_sha256"], "inputs": inputs,
            "sources": observed, "early_preflight_requires_local_sources": False,
            "runtime_rust_encoder_decode": "NOT_RUN", "timing": "NOT_MEASURED"}


def generate_main(directory):
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    manifest = input_manifest(); assert manifest == json.loads(FROZEN_INPUTS.read_bytes())
    directory.mkdir()
    for row in manifest["cases"]:
        data, extra = generate_input(row["family"], row["raw_bytes"], row["seed"])
        assert sha(data) == row["input_sha256"] and extra == {k: row[k] for k in ["units", "padding_bytes"]}
        (directory / row["filename"]).write_bytes(data)
    (directory.parent / "input-manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps({"status": "GENERATED_FROZEN_27_INPUTS", "generator_sha256": manifest["generator_sha256"], "raw_bytes": 5533824}))


def captured(command, logfile, timeout):
    try:
        p = subprocess.run(command, capture_output=True, text=True, timeout=timeout)
        logfile.write_text(p.stdout + p.stderr)
    except subprocess.TimeoutExpired as exc:
        decode = lambda v: v.decode(errors="replace") if isinstance(v, bytes) else (v or "")
        logfile.write_text(decode(exc.stdout) + decode(exc.stderr) + f"\nTIMEOUT after {timeout}s\n")
        raise
    if p.returncode: raise RuntimeError(f"exit={p.returncode}; see {logfile.name}")
    return p


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    from round4 import validate
    spec = validate(os.environ["ROUND4_SPEC"]); checked = preflight(spec)
    upstream = Path(os.environ["DEFLATE_ROOT"])
    codec = upstream / "validator/measure/src/deflate.rs"; token = codec.with_name("token.rs")
    codec_raw = codec.read_bytes(); token_raw = token.read_bytes()
    assert sha(codec_raw) == CODEC_SHA and sha(token_raw) == TOKEN_SHA
    build = Path(os.environ["RUNNER_TEMP"]) / "r25-heldout-quality-build"; build.mkdir()
    spool = build / "spool"; spool.mkdir()
    out = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/r25-heldout-quality"; out.mkdir(parents=True)
    result = {"status": "STARTED_SYNTHETIC_QUALITY_DIAGNOSTIC", "run_id": os.environ["GITHUB_RUN_ID"], "git_sha": os.environ["GITHUB_SHA"],
              "batch": os.environ["ROUND4_SPEC"], "script_sha256": checked["script_sha256"], "generator_sha256": checked["generator_sha256"],
              "declaration_sha256": checked["declaration_sha256"], "source_hashes": {n: s["hashes"] for n, s in SOURCES.items()},
              "codec_sha256": CODEC_SHA, "token_sha256": TOKEN_SHA,
              "scope": "24 fixed primary syntheticcases plus3 inactive controls, not official/private heldout, stage2, ranking or a success probability. No timing or tuning."}
    report = out / "quality.json"; report.write_text(json.dumps(result, indent=2) + "\n")
    try:
        inputs_dir = out / "inputs"
        captured([sys.executable, str(Path(__file__)), "--generate", str(inputs_dir)], out / "generate.log", 60)
        manifest = json.loads((out / "input-manifest.json").read_bytes())
        assert manifest == checked["inputs"]
        expected = {r["filename"]: r for r in manifest["cases"]}
        mods = []; cases = []; observers = {}
        for i, (name, s) in enumerate(SOURCES.items()):
            frozen = ROOT / s["path"] / "parse.rs"; data, _ = instrument(frozen.read_bytes(), s)
            observer = build / f"observed{i}.rs"; observer.write_bytes(data); (out / f"{name}-route-observer.rs").write_bytes(data)
            observers[name] = sha(data)
            mods.extend([f"#[path={json.dumps(str(frozen))}] mod frozen{i};", f"#[path={json.dumps(str(observer))}] mod observed{i};"])
            cases.append(f"({json.dumps(name)}, frozen{i}::parse, observed{i}::parse, observed{i}::r25_hq_take)")
        harness = HARNESS.replace("HQ_TOKEN", json.dumps(str(token))).replace("HQ_CODEC", json.dumps(str(codec)))
        harness = harness.replace("HQ_MODULES", "\n".join(mods)).replace("HQ_CASES", ",\n".join(cases))
        driver = build / "main.rs"; driver.write_text(harness); (out / "harness.rs").write_text(harness)
        binary = build / "quality"
        result.update(harness_sha256=sha(harness.encode()), route_observer_sha256=observers)
        captured(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes", str(driver), "-o", str(binary)], out / "compile.log", 300)
        result["binary_sha256"] = sha(binary.read_bytes())
        run = captured([str(binary), str(inputs_dir), str(spool)], out / "run.log", 240)
        rows = []
        for line in run.stdout.splitlines():
            if not line.startswith("R25_HQ "): continue
            _, name, index, filename, nb, nt, route = line.split()
            assert name in SOURCES and filename in expected
            case = expected[filename]; raw = (inputs_dir / filename).read_bytes()
            enc = (spool / f"{index}-{name}.deflate").read_bytes(); tok = (spool / f"{index}-{name}.tokens").read_bytes()
            assert sha(raw) == case["input_sha256"] and len(raw) == case["raw_bytes"]
            raw.decode("utf-8", errors="strict")
            assert len(enc) == int(nb) and len(tok) == int(nt) * 4 and zlib.decompress(enc, -15) == raw
            route = int(route); wanted = {12000: 12, 400000: 1, 196608: 32}[len(raw)]
            assert route == wanted, (name, filename, route, wanted)
            symbol = f"p125_row{route}" if route != 32 else "fallback"
            rows.append({**case, "candidate": name, "output_bytes": len(enc), "tokens": int(nt), "tokens_sha256": sha(tok), "output_sha256": sha(enc),
                         "actual_route": symbol, "actual_row_body": checked["sources"][name]["row_bodies"].get(symbol),
                         "component_active": name != "combo" and ((name == "end4" and route == 1) or (name == "tiny-pc8" and route == 12)),
                         "diagnostic_compression_pct": 100 * len(enc) / len(raw)})
        assert len(rows) == len({(r["candidate"], r["case_id"]) for r in rows}) == 81
        by = {(r["candidate"], r["case_id"]): r for r in rows}; changes = []
        for name in ["end4", "tiny-pc8"]:
            for case in manifest["cases"]:
                a = by[("combo", case["case_id"])]; b = by[(name, case["case_id"])]
                changes.append({"candidate": name, "case_id": case["case_id"], "cohort": case["cohort"], "family": case["family"], "raw_bytes": case["raw_bytes"],
                    "seed": case["seed"], "bytes_delta_vs_combo": b["output_bytes"] - a["output_bytes"], "tokens_delta_vs_combo": b["tokens"] - a["tokens"],
                    "component_active": b["component_active"],
                    "tokens_equal": b["tokens_sha256"] == a["tokens_sha256"], "output_equal": b["output_sha256"] == a["output_sha256"]})
                if case["cohort"] == "inactive-control":
                    assert b["tokens_sha256"] == a["tokens_sha256"] and b["output_sha256"] == a["output_sha256"]
        summaries = []
        for cohort in ["primary", "inactive-control"]:
            for name in ["end4", "tiny-pc8"]:
                rr = [r for r in changes if r["cohort"] == cohort and r["candidate"] == name]
                assert len(rr) == (24 if cohort == "primary" else 3)
                summaries.append({"cohort": cohort, "candidate": name, "cases": len(rr), "bytes_delta_sum_vs_combo": sum(r["bytes_delta_vs_combo"] for r in rr),
                    "component_active_cases": sum(r["component_active"] for r in rr),
                    "active_case_bytes_delta_sum_vs_combo": sum(r["bytes_delta_vs_combo"] for r in rr if r["component_active"]),
                    "tokens_delta_sum_vs_combo": sum(r["tokens_delta_vs_combo"] for r in rr), "smaller_cases": sum(r["bytes_delta_vs_combo"] < 0 for r in rr),
                    "equal_cases": sum(r["bytes_delta_vs_combo"] == 0 for r in rr), "larger_cases": sum(r["bytes_delta_vs_combo"] > 0 for r in rr),
                    "regressions": [r for r in rr if r["bytes_delta_vs_combo"] > 0]})
        for name, s in SOURCES.items():
            for f, h in s["hashes"].items(): assert sha((ROOT / s["path"] / f).read_bytes()) == h
        assert codec.read_bytes() == codec_raw and token.read_bytes() == token_raw
        assert input_manifest() == manifest
        result.update(status="VERIFIED_UNTIMED_27_SYNTHETIC_CASES_ORIGINAL_ENCODER_DECODE_AND_ROUTE_PARITY", phase="complete", input_manifest=manifest,
                      rows=rows, changes_vs_combo=changes, summaries=summaries,
                      parity={"full_frozen_observed_tokens": True, "native_rust_decodes": 81, "independent_zlib_decodes": 81,
                              "runtime_regenerated_frozen_input_hashes": True, "actual_routes_match_predeclared_static_coverage": True, "inactive_control_token_output_equal": True},
                      interpretation="All cases and counterexamples retained. Improvements are these exact self-built inputs, not unseen/private distribution guarantees, official scores, rewards, or success probabilities. No timing.")
    except Exception as exc:
        result.update(status="FAILED_OR_INCOMPLETE_SYNTHETIC_QUALITY_DIAGNOSTIC", error_type=type(exc).__name__, error=str(exc))
        report.write_text(json.dumps(result, indent=2) + "\n"); raise
    report.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({"status": result["status"], "summaries": summaries}, indent=2))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(); parser.add_argument("--preflight", action="store_true"); parser.add_argument("--generate", type=Path); args = parser.parse_args()
    if args.preflight:
        data = preflight(require_frozen=False)
        if FROZEN_INPUTS.exists(): assert json.loads(FROZEN_INPUTS.read_bytes()) == data["inputs"]
        else: FROZEN_INPUTS.write_text(json.dumps(data["inputs"], indent=2) + "\n")
        preflight()
        (EVIDENCE / "heldout-quality-preflight.json").write_text(json.dumps(data, indent=2) + "\n")
        print(json.dumps({k: v for k, v in data.items() if k not in ["inputs", "sources"]}, indent=2))
    elif args.generate is not None: generate_main(args.generate)
    else: main()
