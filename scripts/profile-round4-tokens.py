"""Untimed token/block diagnostics for fast3 plus at most two round-4 candidates.

Run only on the prepared temporary Linux CI runner. A diagnostic failure is
saved and reported but returns zero; this never certifies a candidate or changes
official measurements. Set profile_names in the spec to choose two candidates.
"""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]
BASELINE = "r3-432-fast3"
PREFIX = "TOKEN_PROFILE "


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def save(path, value):
    path.write_text(json.dumps(value, indent=2, ensure_ascii=False, allow_nan=False) + "\n", encoding="utf-8")


def table(source, name, size):
    match = re.search(rf"const {name}:\s*\[\(u32, u32\); [^\]]+\]\s*=\s*\[(.*?)\];", source, re.S)
    if not match:
        raise ValueError(f"Cannot read official {name}")
    pairs = [(int(a), int(b)) for a, b in re.findall(r"\((\d+),\s*(\d+)\)", match[1])]
    if len(pairs) != size or any(a < 0 for a, _ in pairs) or any(pairs[i][1] >= pairs[i + 1][1] for i in range(size - 1)):
        raise ValueError(f"Unexpected official {name} table")
    return pairs


def select(spec):
    entries = spec["entries"]
    names = [e["name"] for e in entries]
    if len(names) != len(set(names)) or BASELINE not in names:
        raise ValueError("Spec needs unique names and r3-432-fast3")
    eligible = [e["name"] for e in entries if not e.get("control", False) and e["name"] != BASELINE]
    requested = spec.get("profile_names", eligible[:2])
    if not isinstance(requested, list) or len(requested) > 2 or len(requested) != len(set(requested)):
        raise ValueError("profile_names must list at most two distinct non-control candidates")
    if not all(n in eligible for n in requested):
        raise ValueError("profile_names contains an absent/control candidate")
    chosen = [BASELINE] + requested
    return [next(e for e in entries if e["name"] == n) for n in chosen]


def check_rust_formats(source):
    """Check brace escaping in this harness's ordinary Rust format literals."""
    count = 0
    for match in re.finditer(r'(?:println|format)!\(\s*("(?:\\.|[^"\\])*")', source):
        value = json.loads(match[1])
        count += 1
        i = 0
        while i < len(value):
            c = value[i]
            if c in "{}" and i + 1 < len(value) and value[i + 1] == c:
                i += 2
                continue
            if c == "{":
                end = value.find("}", i + 1)
                if end < 0 or "{" in value[i + 1:end]:
                    raise ValueError("Invalid generated Rust format opening brace")
                i = end + 1
                continue
            if c == "}":
                raise ValueError("Invalid generated Rust format closing brace")
            i += 1
    if count < 4:
        raise ValueError("Missing generated Rust profile format strings")
    return count


HARNESS = r'''
#[path = __PARSER_PATH__] mod parser;
#[path = __TOKEN_PATH__] mod official_token;
use std::io::Write;
use std::path::Path;
use std::process::{Command, Stdio};

const BLOCK_TOKENS: usize = __BLOCK_TOKENS__;
const LEN_TABLE: [(u32,u32); 29] = __LEN_TABLE__;
const DIST_TABLE: [(u32,u32); 30] = __DIST_TABLE__;

fn quoted(s: &str) -> String {
    let mut out = String::from("\"");
    for c in s.chars() {
        match c {
            '"' => out.push_str("\\\""), '\\' => out.push_str("\\\\"),
            '\n' => out.push_str("\\n"), '\r' => out.push_str("\\r"), '\t' => out.push_str("\\t"),
            x if x < ' ' => out.push_str(&format!("\\u{:04x}", x as u32)),
            x => out.push(x),
        }
    }
    out.push('"'); out
}

// Coreutils hashes the in-memory bytes over stdin; no token-array file is made.
fn digest(bytes: &[u8]) -> String {
    let mut child = Command::new("sha256sum").stdin(Stdio::piped()).stdout(Stdio::piped()).spawn().expect("sha256sum unavailable");
    child.stdin.take().unwrap().write_all(bytes).expect("sha256sum stdin");
    let output = child.wait_with_output().expect("sha256sum wait");
    assert!(output.status.success(), "sha256sum failed");
    let text = String::from_utf8(output.stdout).unwrap();
    let hash = text.split_whitespace().next().unwrap();
    assert!(hash.len() == 64 && hash.chars().all(|c| c.is_ascii_hexdigit()));
    hash.to_owned()
}

fn code(value: u32, table: &[(u32,u32)]) -> (usize,u32) {
    let mut i = table.len() - 1;
    while table[i].1 > value { i -= 1; }
    (i, table[i].0)
}

fn validate(data: &[u8], tokens: &[u32]) {
    let mut pos = 0usize;
    for (i, &t) in tokens.iter().enumerate() {
        match official_token::decode(t) {
            official_token::Token::Literal(b) => {
                assert!(pos < data.len() && data[pos] == b, "literal mismatch token={i} pos={pos}");
                pos += 1;
            },
            official_token::Token::Match { dist, len } => {
                let d = dist as usize; let l = len as usize;
                assert!(d >= 1 && d <= 32768 && d <= pos && l >= 3 && l <= 258 && l <= data.len() - pos,
                    "match bounds token={i} pos={pos} dist={d} len={l}");
                for j in 0..l {
                    assert!(data[pos+j] == data[pos+j-d], "match mismatch token={i} byte={j}");
                }
                pos += l;
            },
            official_token::Token::Invalid => panic!("invalid token index={i} value={t}"),
        }
    }
    assert_eq!(pos, data.len(), "token stream length mismatch");
}

fn block(label: &str, bi: usize, start: usize, ts: &[u32], raw_start: usize) -> usize {
    let mut ll = [0u32; 288]; let mut ds = [0u32; 30];
    let mut literals = 0usize; let mut matches = 0usize; let mut matched_bytes = 0usize;
    let mut length_extra_bits = 0u64; let mut distance_extra_bits = 0u64;
    for &t in ts {
        match official_token::decode(t) {
            official_token::Token::Literal(b) => { ll[b as usize] += 1; literals += 1; },
            official_token::Token::Match { dist, len } => {
                let (lc, le) = code(len, &LEN_TABLE); let (dc, de) = code(dist, &DIST_TABLE);
                ll[257+lc] += 1; ds[dc] += 1; matches += 1; matched_bytes += len as usize;
                length_extra_bits += le as u64; distance_extra_bits += de as u64;
            },
            official_token::Token::Invalid => unreachable!(),
        }
    }
    // The encoder adds one EOB frequency to each token block before package merge.
    ll[256] = 1;
    let raw_end = raw_start + literals + matched_bytes;
    let la = ll[..256].iter().filter(|&&v| v > 0).count();
    let ma = ll[257..286].iter().filter(|&&v| v > 0).count();
    let da = ds.iter().filter(|&&v| v > 0).count();
    println!("TOKEN_PROFILE {{\"kind\":\"block\",\"file\":{},\"block_index\":{},\"token_start\":{},\"token_end\":{},\"token_count\":{},\"raw_start\":{},\"raw_end\":{},\"literal_bytes\":{},\"match_bytes\":{},\"match_tokens\":{},\"literal_active_symbols\":{},\"length_active_symbols\":{},\"distance_active_symbols\":{},\"litlen_active_with_eob\":{},\"end_of_block_frequency\":1,\"distance_dummy_code_needed\":{},\"length_extra_bits\":{},\"distance_extra_bits\":{},\"total_extra_bits\":{},\"litlen_frequencies\":{:?},\"distance_frequencies\":{:?}}}",
        quoted(label),bi,start,start+ts.len(),ts.len(),raw_start,raw_end,literals,matched_bytes,matches,
        la,ma,da,la+ma+1,da==0,length_extra_bits,distance_extra_bits,length_extra_bits+distance_extra_bits,ll,ds);
    raw_end
}

fn profile(path: &Path) {
    let label = path.file_name().unwrap().to_str().unwrap();
    let data = std::fs::read(path).expect("read input");
    let mut tokens = vec![0u32; data.len()];
    let nt = parser::parse(&data, &mut tokens);
    assert!(nt <= tokens.len(), "parser returned too many tokens");
    tokens.truncate(nt); validate(&data, &tokens);
    let input_sha256 = digest(&data);
    let mut token_bytes = Vec::with_capacity(4*tokens.len());
    for &t in &tokens { token_bytes.extend_from_slice(&t.to_le_bytes()); }
    let tokens_sha256 = digest(&token_bytes);
    let mut raw_end = 0usize; let mut block_count = 0usize;
    if tokens.is_empty() {
        raw_end = block(label,0,0,&[],0); block_count = 1;
    } else {
        for (bi, ts) in tokens.chunks(BLOCK_TOKENS).enumerate() {
            raw_end = block(label,bi,bi*BLOCK_TOKENS,ts,raw_end); block_count += 1;
        }
    }
    assert_eq!(raw_end,data.len());
    println!("TOKEN_PROFILE {{\"kind\":\"file\",\"file\":{},\"raw_bytes\":{},\"total_token_count\":{},\"block_count\":{},\"input_sha256\":{},\"tokens_sha256\":{},\"token_hash_encoding\":\"counted u32 prefix, little endian\",\"decode_checked\":true}}",
        quoted(label),data.len(),nt,block_count,quoted(&input_sha256),quoted(&tokens_sha256));
}

fn main() {
    let folder = std::env::args().nth(1).expect("corpus path");
    let mut files: Vec<_> = std::fs::read_dir(folder).unwrap().map(|e| e.unwrap().path()).filter(|p| p.is_file()).collect();
    files.sort();
    for path in files {
        let result = std::panic::catch_unwind(|| profile(&path));
        if let Err(error) = result {
            let message = if let Some(s) = error.downcast_ref::<String>() { s.as_str() }
                else if let Some(s) = error.downcast_ref::<&str>() { *s } else { "unknown panic" };
            println!("TOKEN_PROFILE {{\"kind\":\"error\",\"file\":{},\"error\":{}}}",
                quoted(path.file_name().unwrap().to_str().unwrap()),quoted(message));
        }
    }
}
'''


def run_profile(output, working, report):
    if os.environ.get("GITHUB_ACTIONS") != "true" or sys.platform != "linux":
        raise RuntimeError("Token profiling is restricted to the prepared temporary Linux CI runner")
    if os.environ.get("GITHUB_REPOSITORY") != "HuanHuanHuanFFF/Miner":
        raise RuntimeError("Unexpected repository")
    label = os.environ["ROUND4_SPEC"]
    if not re.fullmatch(r"[a-z0-9-]{1,48}", label):
        raise ValueError("Invalid ROUND4_SPEC")
    spec_path = ROOT / "evidence/round4" / f"{label}.json"
    spec_bytes = spec_path.read_bytes()
    spec = json.loads(spec_bytes)
    selected = select(spec)
    upstream = Path(os.environ["DEFLATE_ROOT"]).resolve()
    encoder_path = upstream / "validator/measure/src/deflate.rs"
    token_path = upstream / "validator/measure/src/token.rs"
    record_path = upstream / "validator/measure/src/record.rs"
    encoder_bytes = encoder_path.read_bytes()
    token_bytes = token_path.read_bytes()
    encoder = encoder_bytes.decode("utf-8")
    lengths, distances = table(encoder, "LEN_TABLE", 29), table(encoder, "DIST_TABLE", 30)
    bm = re.search(r"pub const BLOCK_TOKENS:\s*usize\s*=\s*(\d+);", encoder)
    if not bm or int(bm[1]) != 16384:
        raise ValueError("Official BLOCK_TOKENS differs from the required 16384")
    toolchain_path = upstream / "validator/rust-toolchain.toml"
    toolchain_bytes = toolchain_path.read_bytes()
    channel = tomllib.loads(toolchain_bytes.decode())["toolchain"]["channel"]
    registry_path = upstream / "validator/corpora.toml"
    registry = tomllib.loads(registry_path.read_text())
    public = next(e for e in registry["corpus"] if e["name"] == "corpus-stage1")
    if public.get("public", True) is not True:
        raise ValueError("Refusing non-public corpus")
    corpus = (upstream / public["path"]).resolve()
    inputs = {p.name: {"bytes": p.stat().st_size, "sha256": sha256(p.read_bytes())}
              for p in sorted(corpus.iterdir()) if p.is_file()}
    if not inputs:
        raise ValueError("No public corpus files")
    report.update({
        "spec": label, "spec_sha256": sha256(spec_bytes), "profile_names": [e["name"] for e in selected],
        "selection": "baseline plus explicit profile_names, or first two non-control spec entries",
        "official_source": {
            "deflate.rs": {"path": str(encoder_path), "sha256": sha256(encoder_bytes)},
            "token.rs": {"path": str(token_path), "sha256": sha256(token_bytes)},
            "record.rs": {"path": str(record_path), "sha256": sha256(record_path.read_bytes()), "role": "official SHA256 token encoding is counted u32 prefix in little endian"},
            "rust-toolchain.toml": {"path": str(toolchain_path), "sha256": sha256(toolchain_bytes)},
            "corpora.toml": {"sha256": sha256(registry_path.read_bytes())},
        },
        "block_tokens": 16384, "length_table_extra_base": lengths, "distance_table_extra_base": distances,
        "frequency_indices": "litlen[0:256] literals, [256] EOB=1 per block, [257:286] length codes, [286:288] reserved; distance[0:30] actual match codes, dummy code not added to frequency",
        "inputs": inputs, "corpus": "corpus-stage1", "toolchain": channel,
        "candidate_sources": {}, "files": [], "failures": [],
    })
    diagnostics = output / "token-profile-diagnostics"
    diagnostics.mkdir(exist_ok=True)
    rows_path = output / "token-profile.jsonl"
    compile_flags = ["--edition=2021", "-Awarnings", "-O", "-C", "overflow-checks=yes", "-C", "panic=unwind", "-C", "lto=fat", "-C", "codegen-units=1"]
    report["compile_flags"] = compile_flags
    report["rustc_version"] = subprocess.run(["rustc", "+" + channel, "--version"], capture_output=True, text=True, timeout=30).stdout.strip()
    revision = subprocess.run(["git", "rev-parse", "HEAD"], cwd=upstream, capture_output=True, text=True, timeout=30)
    report["official_revision"] = revision.stdout.strip() if revision.returncode == 0 else "UNKNOWN"
    hash_version = subprocess.run(["sha256sum", "--version"], capture_output=True, text=True, timeout=30)
    report["token_hash_implementation"] = hash_version.stdout.splitlines()[0] if hash_version.returncode == 0 and hash_version.stdout else "UNKNOWN"
    with rows_path.open("w", encoding="utf-8") as sink:
        sink.write(json.dumps({"kind": "provenance", **{k: report[k] for k in ("spec", "spec_sha256", "official_revision", "official_source", "block_tokens", "frequency_indices", "length_table_extra_base", "distance_table_extra_base", "inputs", "compile_flags", "rustc_version", "token_hash_implementation")}}, ensure_ascii=False) + "\n")
        for entry in selected:
            name = entry["name"]
            if not re.fullmatch(r"[A-Za-z0-9_-]+", name):
                raise ValueError("Invalid candidate name")
            candidate = (ROOT / entry["path"]).resolve()
            if not candidate.is_relative_to((ROOT / "candidates").resolve()):
                raise ValueError("Candidate outside candidates root")
            source = candidate / "parse.rs"
            hashes = {n: sha256((candidate / n).read_bytes()) for n in ("parse.rs", "Parse.lean")}
            if hashes != entry["hashes"]:
                raise ValueError(f"Spec hash mismatch: {name}")
            report["candidate_sources"][name] = {"path": entry["path"], "hashes": hashes}
            harness = HARNESS
            for key, value in {
                "__PARSER_PATH__": json.dumps(str(source), ensure_ascii=False),
                "__TOKEN_PATH__": json.dumps(str(token_path), ensure_ascii=False),
                "__BLOCK_TOKENS__": "16384",
                "__LEN_TABLE__": "[" + ",".join(f"({a},{b})" for a,b in lengths) + "]",
                "__DIST_TABLE__": "[" + ",".join(f"({a},{b})" for a,b in distances) + "]",
            }.items():
                harness = harness.replace(key, value)
            check_rust_formats(harness)
            work = working / name
            work.mkdir(exist_ok=True)
            rust_path, binary = work / "token_profile.rs", work / "token_profile"
            rust_path.write_text(harness, encoding="utf-8")
            report["candidate_sources"][name]["harness_sha256"] = sha256(harness.encode())
            try:
                compiled = subprocess.run(["rustc", "+" + channel, *compile_flags, str(rust_path), "-o", str(binary)],
                                          cwd=work, capture_output=True, text=True, timeout=240)
                (diagnostics / f"{name}-compile.txt").write_text((compiled.stdout + compiled.stderr)[-65536:], encoding="utf-8")
                if compiled.returncode:
                    report["failures"].append({"candidate": name, "stage": "compile", "returncode": compiled.returncode})
                    print(PREFIX + json.dumps(report["failures"][-1]), flush=True)
                    continue
                executed = subprocess.run([str(binary), str(corpus)], cwd=work, capture_output=True, text=True, timeout=180)
                if any(sha256((candidate / f).read_bytes()) != h for f, h in hashes.items()):
                    raise ValueError(f"Candidate source/proof changed during profiling: {name}")
                if encoder_path.read_bytes() != encoder_bytes or token_path.read_bytes() != token_bytes:
                    raise ValueError("Official token/encoder source changed during profiling")
                (diagnostics / f"{name}-runtime.txt").write_text(executed.stderr[-65536:], encoding="utf-8")
                blocks, files, errors = [], [], []
                for line in executed.stdout.splitlines():
                    if not line.startswith(PREFIX):
                        continue
                    row = json.loads(line[len(PREFIX):])
                    row.update({"candidate": name, "source_sha256": hashes["parse.rs"], "proof_sha256": hashes["Parse.lean"]})
                    if row["kind"] == "file":
                        expected = inputs[row["file"]]
                        if row["raw_bytes"] != expected["bytes"] or row["input_sha256"] != expected["sha256"]:
                            raise ValueError(f"Input changed while profiling: {name}/{row['file']}")
                        files.append(row)
                    elif row["kind"] == "block":
                        blocks.append(row)
                    elif row["kind"] == "error":
                        errors.append(row)
                successful = {f["file"]: f for f in files}
                for f in files:
                    bs = [b for b in blocks if b["file"] == f["file"]]
                    if len(bs) != f["block_count"] or sum(b["token_count"] for b in bs) != f["total_token_count"]:
                        raise ValueError(f"Incomplete block records: {name}/{f['file']}")
                    if sum(b["literal_bytes"] + b["match_bytes"] for b in bs) != f["raw_bytes"]:
                        raise ValueError(f"Block byte accounting mismatch: {name}/{f['file']}")
                    for b in bs:
                        if len(b["litlen_frequencies"]) != 288 or len(b["distance_frequencies"]) != 30:
                            raise ValueError("Frequency array dimensions differ from official alphabets")
                        if sum(b["litlen_frequencies"]) != b["token_count"] + 1 or sum(b["distance_frequencies"]) != b["match_tokens"]:
                            raise ValueError("Frequency/token accounting mismatch")
                    for field in ("literal_bytes", "match_bytes", "match_tokens", "length_extra_bits", "distance_extra_bits", "total_extra_bits"):
                        f[field] = sum(b[field] for b in bs)
                # Keep only blocks with a completed, validated file record.
                for row in [*files, *(b for b in blocks if b["file"] in successful), *errors]:
                    sink.write(json.dumps(row, ensure_ascii=False, allow_nan=False) + "\n")
                sink.flush()
                report["files"].extend(files)
                report["failures"].extend(errors)
                if executed.returncode or len(files) + len(errors) != len(inputs):
                    report["failures"].append({"candidate": name, "stage": "runtime", "returncode": executed.returncode,
                                               "complete_files": len(files), "expected_files": len(inputs)})
                print(PREFIX + json.dumps({"candidate": name, "profiled_files": len(files), "blocks": sum(f["block_count"] for f in files), "errors": len(errors)}), flush=True)
            except (subprocess.TimeoutExpired, OSError, ValueError) as exc:
                report["failures"].append({"candidate": name, "stage": "diagnostic", "error": str(exc)})
                print(PREFIX + json.dumps(report["failures"][-1]), flush=True)
    report["records_sha256"] = sha256(rows_path.read_bytes())
    report["status"] = "DIAGNOSTIC_PARTIAL" if report["failures"] else "DIAGNOSTIC_OK"


def main():
    report = {"scope": "untimed public token/block statistics and independent byte validation; not official encoder execution, Lean acceptance, gate, performance, stage2, admission or reward evidence",
              "script_sha256": sha256(Path(__file__).read_bytes()), "status": "DIAGNOSTIC_FAILED"}
    # These directories exist only in RUNNER_TEMP; compiled sources/binaries are
    # deliberately outside the receipt directory uploaded by the parent workflow.
    output = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts"
    output.mkdir(exist_ok=True)
    working = Path(os.environ["RUNNER_TEMP"]) / "round4-token-profile-working"
    working.mkdir(exist_ok=True)
    try:
        run_profile(output, working, report)
    except Exception as exc:
        report["failure"] = {"type": type(exc).__name__, "error": str(exc)}
        print(PREFIX + json.dumps({"status": report["status"], "failure": report["failure"]}), flush=True)
    save(output / "token-profile.json", report)
    print(PREFIX + json.dumps({"status": report["status"], "receipt": "round4-receipts/token-profile.json", "file_records": len(report.get("files", []))}), flush=True)


if __name__ == "__main__":
    main()
