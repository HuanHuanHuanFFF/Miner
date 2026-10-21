"""Untimed frozen-token len3 prices; no token rewrite or candidate generation."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import subprocess
import zlib

ROOT = Path(__file__).resolve().parents[1]
CODEC_SHA = "172c240014f65d5e2762c1287e4982dd1cd426f2999f74e17011e05f2dc5fdec"
TOKEN_SHA = "8bf5d962324b3a0890f3c75f713198be086c4b0659797c24b8b976978cea4917"
EXPECTED_APPEND_SHA = "52789ab5a4533ecf3c412002e70e55b447f840e4c5be9a3f1ce78256ed6c5d82"
SOURCES = {
    "combo": {
        "path": "candidates/r22-595-chain-halfhead", "stem": "p125", "row_count": 17,
        "hashes": {"parse.rs": "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275",
                   "Parse.lean": "4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6"},
        "fixture": "evidence/round25/38130296690/quality-j-native/diagnostics/r13-encoder/encoder.json",
        "fixture_sha256": "01313010d9804647dae8ffb1a1e1e4f0275794ba3dd3f52e24d100df26209dba",
        "fixture_kind": "native",
    },
    "public578": {
        "path": "references/round25-public-578", "stem": "p125", "row_count": 20,
        "hashes": {"parse.rs": "e1f72d323e66a6787cb1310b2f07cb1d4045ceb247a78f2fb3547d2cd03d951e",
                   "Parse.lean": "4090a61ae9f3702cc36d57b36d6c103b05d0640a352a2cfedd0000340289b2c4"},
        "fixture": "evidence/round25/38126014186/screen-c/gate/round1-public578.jsonl",
        "fixture_sha256": "7a8adcab9f6e2495bc1a182214fd0c883abcb0517de29cb31ebde648c132d271",
        "fixture_kind": "benchmark",
    },
    "public584": {
        "path": "references/round18-public-584", "stem": "p135", "row_count": 20,
        "hashes": {"parse.rs": "82297feee16db3fe6af50fe07f034b81d73d7189a40a829b78b44db167410cf2",
                   "Parse.lean": "96239a6fcad5be34ad4ec3b8caaaa379592166ff99b9194803e432f6d0482f4d"},
        "fixture": "evidence/round18/37968740636/baselines-b-native/diagnostics/r13-encoder/encoder.json",
        "fixture_sha256": "f3047c4384ea5a63d2ba02c33b927dcfae6713a3d948515e816a00e0d274115f",
        "fixture_kind": "native",
    },
}
BASE_FIELDS = [
    "tokens", "literal_tokens", "match_tokens", "match_bytes", "len3_matches",
    "known_literal_prices", "missing_literal_prices", "match_cheaper", "literal_cheaper",
    "equal_price", "match_savings_bits", "match_loss_bits", "known_match_bits",
    "known_literal_bits", "stored_blocks", "fixed_blocks", "dynamic_blocks",
]
CODE_FIELDS = ["len3_matches", "known_literal_prices", "missing_literal_prices",
               "match_cheaper", "literal_cheaper", "equal_price", "match_savings_bits", "match_loss_bits"]
FIELDS = BASE_FIELDS + [f"distance_code_{i}_{f}" for i in range(30) for f in CODE_FIELDS]
WIDTH = len(FIELDS)
ROUTE_APPEND = r'''
// R25 untimed route observation only; no classifier re-run, parse decision or token change.
static R25_LP_ROWS: [std::sync::atomic::AtomicU64; 33] =
    [const { std::sync::atomic::AtomicU64::new(0) }; 33];
fn r25_lp_row(i: usize) {
    R25_LP_ROWS[i].fetch_add(1, std::sync::atomic::Ordering::Relaxed);
}
pub fn r25_lp_take() -> [u64; 33] {
    std::array::from_fn(|i| R25_LP_ROWS[i].swap(0, std::sync::atomic::Ordering::Relaxed))
}
'''

PRICE_BODY = r'''
pub fn r25_lp_prices(ts: &[u32], input: &[u8]) -> Vec<([u64; LP_WIDTH], usize, usize, usize, u64, u64, u64)> {
    let mut result = Vec::new();
    let mut pos = 0usize;
    for chunk in ts.chunks(BLOCK_TOKENS) {
        let mut b = Block::new();
        for &t in chunk {
            match token::decode(t) {
                token::Token::Literal(x) => b.push_literal(x),
                token::Token::Match { dist, len } => b.push_match(dist, len),
                _ => panic!("invalid frozen token"),
            }
        }
        let (ll, dl, kind, fix_bits, dyn_bits, stored_bits) = r25_lp_tables(&b);
        let from = pos;
        let mut counts = [0u64; LP_WIDTH];
        counts[LP_TOKENS] = chunk.len() as u64;
        counts[match kind { 0 => LP_STORED_BLOCKS, 1 => LP_FIXED_BLOCKS, 2 => LP_DYNAMIC_BLOCKS, _ => panic!("block type") }] = 1;
        for &t in chunk {
            match token::decode(t) {
                token::Token::Literal(_) => { counts[LP_LITERAL_TOKENS] += 1; pos += 1; },
                token::Token::Match { dist, len } => {
                    counts[LP_MATCH_TOKENS] += 1;
                    counts[LP_MATCH_BYTES] += len as u64;
                    assert!(dist >= 1 && dist as usize <= pos && pos + len as usize <= input.len());
                    if len == 3 {
                        assert_ne!(kind, 0, "a stored block cannot contain a match");
                        let (dc, extra, _) = dist_code(dist);
                        assert!(dc < 30 && ll[257] > 0 && dl[dc] > 0);
                        let cell = LP_CODE_BASE + dc * LP_CODE_WIDTH;
                        counts[LP_LEN3_MATCHES] += 1; counts[cell] += 1;
                        let known = input[pos..pos + 3].iter().all(|&x| ll[x as usize] > 0);
                        if known {
                            let mc = ll[257] as u64 + dl[dc] as u64 + extra as u64;
                            let lc = input[pos..pos + 3].iter().map(|&x| ll[x as usize] as u64).sum::<u64>();
                            counts[LP_KNOWN_LITERAL_PRICES] += 1; counts[cell + 1] += 1;
                            counts[LP_KNOWN_MATCH_BITS] += mc; counts[LP_KNOWN_LITERAL_BITS] += lc;
                            if mc < lc {
                                counts[LP_MATCH_CHEAPER] += 1; counts[cell + 3] += 1;
                                counts[LP_MATCH_SAVINGS_BITS] += lc - mc; counts[cell + 6] += lc - mc;
                            } else if mc > lc {
                                counts[LP_LITERAL_CHEAPER] += 1; counts[cell + 4] += 1;
                                counts[LP_MATCH_LOSS_BITS] += mc - lc; counts[cell + 7] += mc - lc;
                            } else { counts[LP_EQUAL_PRICE] += 1; counts[cell + 5] += 1; }
                        } else {
                            counts[LP_MISSING_LITERAL_PRICES] += 1; counts[cell + 2] += 1;
                        }
                    }
                    pos += len as usize;
                },
                _ => panic!("invalid frozen token"),
            }
        }
        assert_eq!(pos - from, b.raw_len);
        result.push((counts, from, pos, kind, fix_bits, dyn_bits, stored_bits));
    }
    assert_eq!(pos, input.len());
    result
}
'''

HARNESS = r'''
#![allow(dead_code)]
#[path=LP_TOKEN] mod token;
#[path=LP_TRUSTED] mod trusted;
#[path=LP_PRICES] mod prices;
LP_MODULES
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
            _ => panic!("invalid token"),
        }
    }
    assert_eq!(out, s);
}
fn main() {
    let args: Vec<_> = std::env::args().collect();
    let spool = std::path::Path::new(&args[2]);
    let cases: &[(&str, Parser, Parser, Routes)] = &[LP_CASES];
    let mut files: Vec<_> = std::fs::read_dir(&args[1]).unwrap().map(|x| x.unwrap().path()).filter(|p| p.is_file()).collect();
    files.sort();
    for (i, p) in files.iter().enumerate() {
        let s = std::fs::read(p).unwrap(); let name = p.file_name().unwrap().to_str().unwrap();
        for &(label, frozen, observed, routes) in cases {
            let a = parse(&s, frozen); let b = parse(&s, observed);
            assert_eq!(a, b, "observed parser differs: {} {}", label, name); decode(&s, &a);
            let hits = routes(); assert!(hits.iter().sum::<u64>() <= 1, "multiple top-level rows");
            let route = hits.iter().position(|&v| v > 0).unwrap_or(32);
            let enc = trusted::encode(&a, s.len()).unwrap();
            assert_eq!(enc, prices::encode(&a, s.len()).unwrap(), "instrumented encoder differs");
            let mut raw = Vec::new(); for &t in &a { raw.extend(t.to_le_bytes()); }
            std::fs::write(spool.join(format!("{}-{}.tokens", i, label)), raw).unwrap();
            std::fs::write(spool.join(format!("{}-{}.deflate", i, label)), &enc).unwrap();
            println!("R25_LP_FILE {} {} {} {} {} {}", label, i, name, enc.len(), a.len(), route);
            for (bi, (counts, from, to, kind, fix, dyn_, stored)) in prices::r25_lp_prices(&a, &s).iter().enumerate() {
                print!("R25_LP_BLOCK {} {} {} {} {} {} {} {} {} {}", label, i, name, bi, from, to, kind, fix, dyn_, stored);
                for v in counts { print!(" {}", v); } println!();
            }
        }
    }
}
'''


def sha(data):
    return hashlib.sha256(data).hexdigest()


def instrument(raw, source):
    """Insert only atomics into original top-level row entries; reversible bytes."""
    assert sha(raw) == source["hashes"]["parse.rs"]
    original = raw.decode()
    pattern = re.compile(r"pub fn (" + source["stem"] + r"_row(\d+))\([^\n]*?\)->usize\{")
    matches = list(pattern.finditer(original))
    assert sorted(int(m[2]) for m in matches) == list(range(source["row_count"]))
    row_bodies = {}
    for m in matches:
        depth = 1
        end = m.end()
        while depth:
            if original[end] == "{": depth += 1
            if original[end] == "}": depth -= 1
            end += 1
        row_bodies[m[1]] = original[m.end():end - 1]
    observed = original
    additions = []
    for m in reversed(matches):
        addition = f"r25_lp_row({m[2]});"
        additions.append(addition)
        observed = observed[:m.end()] + addition + observed[m.end():]
    observed += ROUTE_APPEND
    reversed_source = observed.removesuffix(ROUTE_APPEND)
    for addition in additions:
        assert reversed_source.count(addition) == 1
        reversed_source = reversed_source.replace(addition, "", 1)
    assert reversed_source.encode() == raw
    return observed.encode(), row_bodies


def price_append(codec_raw):
    """Copy the pinned write_block table preparation, including stored choice."""
    assert sha(codec_raw) == CODEC_SHA
    text = codec_raw.decode()
    header = "fn write_block(w: &mut BitWriter, b: &Block, last: bool) {\n"
    assert text.count(header) == 1
    start = text.index(header) + len(header)
    marker = "    if stored_bits < dyn_bits.min(fix_bits) && b.raw_len < 65536 {"
    stop = text.index(marker, start)
    prep = text[start:stop]
    assert "let stored_bits = 3 + 32 + 8 * b.raw_len as u64;" in prep
    assert "let fix_bits = b.fixed_cost();" in prep and "let dyn_bits = b.dynamic_cost" in prep
    constants = "\n".join(f"const LP_{f.upper()}: usize = {i};" for i, f in enumerate(BASE_FIELDS))
    constants += f"\nconst LP_WIDTH: usize = {WIDTH};\nconst LP_CODE_BASE: usize = {len(BASE_FIELDS)};\nconst LP_CODE_WIDTH: usize = {len(CODE_FIELDS)};\n"
    tables = "\nfn r25_lp_tables(b: &Block) -> (Vec<u8>, Vec<u8>, usize, u64, u64, u64) {\n" + prep
    tables += r'''
    let stored = stored_bits < dyn_bits.min(fix_bits) && b.raw_len < 65536 &&
        b.items.iter().all(|&(_, _, _, d, _, _)| d == u16::MAX);
    if stored { return (ll, dl, 0, fix_bits, dyn_bits, stored_bits); }
    if fix_bits <= dyn_bits {
        let (fll, fdl) = fixed_tables();
        (fll.to_vec(), fdl.to_vec(), 1, fix_bits, dyn_bits, stored_bits)
    } else { (ll, dl, 2, fix_bits, dyn_bits, stored_bits) }
}
'''
    return ("\n// R25 read-only block prices; original encode/write_block bytes above retained.\n" + constants + tables + PRICE_BODY).encode()


def expected_rows(name, source):
    raw = (ROOT / source["fixture"]).read_bytes()
    assert sha(raw) == source["fixture_sha256"]
    if source["fixture_kind"] == "native":
        d = json.loads(raw)
        assert d["source_hashes"][name] == source["hashes"]
        assert d["codec_sha256"] == CODEC_SHA and d["token_sha256"] == TOKEN_SHA
        rows = [r for r in d["rows"] if r["candidate"] == name]
    else:
        d = [json.loads(line) for line in raw.decode().splitlines()]
        assert d[0]["methods"][name]["source_sha256"] == source["hashes"]["parse.rs"]
        rows = [{"file": r["file"], "raw_bytes": r["raw_bytes"], "input_sha256": r["sha256"],
                 **{k: r["methods"][name][k] for k in ("tokens", "output_bytes", "tokens_sha256", "output_sha256")}}
                for r in d if r["kind"] == "file"]
    result = {r["file"]: r for r in rows}
    assert len(result) == len(rows) == 28 and sum(r["raw_bytes"] for r in rows) == 15930000
    return result


def check_counts(v):
    assert set(v) == set(FIELDS) and all(type(x) is int and x >= 0 for x in v.values())
    assert v["tokens"] == v["literal_tokens"] + v["match_tokens"]
    assert 3 * v["match_tokens"] <= v["match_bytes"] <= 258 * v["match_tokens"]
    assert v["len3_matches"] <= v["match_tokens"]
    assert v["len3_matches"] == v["known_literal_prices"] + v["missing_literal_prices"]
    assert v["known_literal_prices"] == v["match_cheaper"] + v["literal_cheaper"] + v["equal_price"]
    assert v["match_cheaper"] <= v["match_savings_bits"] <= 45 * v["match_cheaper"]
    assert v["literal_cheaper"] <= v["match_loss_bits"] <= 43 * v["literal_cheaper"]
    assert v["known_literal_bits"] - v["known_match_bits"] == v["match_savings_bits"] - v["match_loss_bits"]
    for f in CODE_FIELDS:
        assert sum(v[f"distance_code_{i}_{f}"] for i in range(30)) == v[f]
    for i in range(30):
        c = {f: v[f"distance_code_{i}_{f}"] for f in CODE_FIELDS}
        assert c["len3_matches"] == c["known_literal_prices"] + c["missing_literal_prices"]
        assert c["known_literal_prices"] == c["match_cheaper"] + c["literal_cheaper"] + c["equal_price"]
        assert c["match_cheaper"] <= c["match_savings_bits"] <= 45 * c["match_cheaper"]
        assert c["literal_cheaper"] <= c["match_loss_bits"] <= 43 * c["literal_cheaper"]


def preflight(spec=None, codec_raw=None):
    report = {"status": "VERIFIED_LOCAL_TEXT_HASH_AND_SCHEMA_ONLY", "script_sha256": sha(Path(__file__).read_bytes()), "rust_compile": "NOT_RUN",
              "runtime_token_output_decode": "NOT_RUN", "sources": {}, "fields": FIELDS,
              "route_limit": "Actual original top-level row entry; composite row11/13 sub-engine choice is not separately inferred."}
    identity = None
    for name, s in SOURCES.items():
        for f, h in s["hashes"].items(): assert sha((ROOT / s["path"] / f).read_bytes()) == h
        observed, bodies = instrument((ROOT / s["path"] / "parse.rs").read_bytes(), s)
        expected = expected_rows(name, s)
        current = {f: (r["raw_bytes"], r["input_sha256"]) for f, r in expected.items()}
        if identity is not None: assert current == identity
        identity = current
        report["sources"][name] = {**s, "observer_sha256": sha(observed), "observer_bytes": len(observed), "row_bodies": bodies}
    local = ROOT / "sources/conjectures-optimisation-deflate/validator/measure/src"
    if codec_raw is None and (local / "deflate.rs").is_file():
        codec_raw = (local / "deflate.rs").read_bytes().replace(b"\r\n", b"\n")
        token = (local / "token.rs").read_bytes().replace(b"\r\n", b"\n")
        assert sha(token) == TOKEN_SHA
        report["local_codec_normalization"] = "Read-only CRLF-to-LF normalization matches Linux pinned SHA; original local bytes unmodified."
    report.update(codec_sha256=CODEC_SHA, token_sha256=TOKEN_SHA, price_append_sha256=EXPECTED_APPEND_SHA,
                  price_append_binding="DECLARED_PINNED_SHA; runtime must check fetched codec and reconstruct exact original table preparation")
    if codec_raw is not None:
        appended = price_append(codec_raw); assert sha(appended) == EXPECTED_APPEND_SHA
        report.update(price_append_binding="VERIFIED_TEXT_HASH_ONLY; Rust compilation/runtime NOT_RUN", price_append_bytes=len(appended))
    zero = dict.fromkeys(FIELDS, 0); check_counts(zero)
    example = zero.copy()
    example.update(tokens=2, match_tokens=2, match_bytes=6, len3_matches=2, known_literal_prices=1,
                   missing_literal_prices=1, literal_cheaper=1, match_loss_bits=4,
                   known_match_bits=20, known_literal_bits=16, dynamic_blocks=1)
    for f in CODE_FIELDS: example[f"distance_code_29_{f}"] = example[f]
    check_counts(example)
    for k in ["known_literal_prices", "match_loss_bits", "distance_code_29_len3_matches"]:
        invalid = example.copy(); invalid[k] += 1
        try: check_counts(invalid)
        except AssertionError: pass
        else: raise AssertionError("invalid counts accepted: " + k)
    if spec is not None:
        assert spec.get("native_only") is True and spec.get("native_encoder") is False
        assert spec.get("r25_len3_price") is True and spec.get("gate_candidates", []) == [] and spec.get("extract_candidates", []) == []
        by = {e["name"]: e for e in spec["entries"]}
        for name, s in SOURCES.items():
            e = by[name]; assert e.get("control") and e["path"] == s["path"] and e["hashes"] == s["hashes"]
    return report


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


def aggregate(rows):
    result = {f: sum(r["counts"][f] for r in rows) for f in FIELDS}
    check_counts(result)
    return result


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    from round4 import validate
    spec = validate(os.environ["ROUND4_SPEC"])
    upstream = Path(os.environ["DEFLATE_ROOT"])
    trusted = upstream / "validator/measure/src/deflate.rs"; token = trusted.with_name("token.rs")
    codec_raw = trusted.read_bytes(); assert sha(codec_raw) == CODEC_SHA and sha(token.read_bytes()) == TOKEN_SHA
    checked = preflight(spec, codec_raw)
    appended = price_append(codec_raw); assert sha(appended) == checked["price_append_sha256"]
    build = Path(os.environ["RUNNER_TEMP"]) / "r25-len3-price-build"; build.mkdir()
    spool = build / "spool"; spool.mkdir()
    out = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/r25-len3-price"; out.mkdir(parents=True)
    prices = build / "prices.rs"; prices.write_bytes(codec_raw + appended)
    (out / "price-append.rs").write_bytes(appended)
    mods = []; cases = []; observers = {}
    for i, (name, s) in enumerate(SOURCES.items()):
        frozen = ROOT / s["path"] / "parse.rs"; raw = frozen.read_bytes()
        data, _ = instrument(raw, s); observed = build / f"observed{i}.rs"; observed.write_bytes(data)
        (out / f"{name}-route-observer.rs").write_bytes(data)
        observers[name] = {"sha256": sha(data), "frozen_sha256": sha(raw)}
        mods.extend([f"#[path={json.dumps(str(frozen))}] mod frozen{i};", f"#[path={json.dumps(str(observed))}] mod observed{i};"])
        cases.append(f"({json.dumps(name)}, frozen{i}::parse, observed{i}::parse, observed{i}::r25_lp_take)")
    harness = HARNESS.replace("LP_TOKEN", json.dumps(str(token))).replace("LP_TRUSTED", json.dumps(str(trusted)))
    harness = harness.replace("LP_PRICES", json.dumps(str(prices))).replace("LP_MODULES", "\n".join(mods)).replace("LP_CASES", ",\n".join(cases))
    driver = build / "main.rs"; driver.write_text(harness); (out / "harness.rs").write_text(harness)
    result = {"status": "STARTED_UNTIMED_LEN3_PRICE_OBSERVER", "script_sha256": sha(Path(__file__).read_bytes()), "run_id": os.environ["GITHUB_RUN_ID"],
              "git_sha": os.environ["GITHUB_SHA"], "batch": os.environ["ROUND4_SPEC"], "source_hashes": {n: s["hashes"] for n, s in SOURCES.items()},
              "codec_sha256": CODEC_SHA, "token_sha256": TOKEN_SHA, "price_append_sha256": sha(appended),
              "price_encoder_sha256": sha(codec_raw + appended), "harness_sha256": sha(harness.encode()), "route_observers": observers,
              "fields": FIELDS, "scope": "Three frozen complete original token streams; no rewrite, threshold, candidate, new filename/length route, performance score or proof claim.",
              "price_limits": "Original block tables and type; missing literal codes are UNKNOWN, never zero-priced. Local positive/negative bits exclude changed-table/header/block-split effects and are not final-byte gains. Original row entry labels composite rows without inventing sub-engine attribution."}
    report = out / "counts.json"; report.write_text(json.dumps(result, indent=2) + "\n")
    try:
        binary = build / "prices"
        captured(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes", str(driver), "-o", str(binary)], out / "compile.log", 300)
        result["binary_sha256"] = sha(binary.read_bytes())
        corpus = upstream / "data/benchmark/corpus-stage1"
        run = captured([str(binary), str(corpus), str(spool)], out / "run.log", 240)
        files = {}; blocks = {}
        for line in run.stdout.splitlines():
            if line.startswith("R25_LP_FILE "):
                _, name, index, filename, nb, nt, route = line.split()
                key = (name, filename); assert name in SOURCES and key not in files
                raw = (corpus / filename).read_bytes(); enc = (spool / f"{index}-{name}.deflate").read_bytes(); tok = (spool / f"{index}-{name}.tokens").read_bytes()
                assert len(enc) == int(nb) and len(tok) == int(nt) * 4 and zlib.decompress(enc, -15) == raw
                files[key] = {"candidate": name, "file": filename, "raw_bytes": len(raw), "input_sha256": sha(raw), "output_bytes": len(enc),
                              "tokens": int(nt), "tokens_sha256": sha(tok), "output_sha256": sha(enc), "row_index": int(route)}
            elif line.startswith("R25_LP_BLOCK "):
                _, name, index, filename, bi, start, end, kind, fix, dyn, stored, *values = line.split()
                assert len(values) == WIDTH
                counts = dict(zip(FIELDS, map(int, values))); check_counts(counts)
                assert sum(counts[f] for f in ["stored_blocks", "fixed_blocks", "dynamic_blocks"]) == 1
                assert counts[["stored_blocks", "fixed_blocks", "dynamic_blocks"][int(kind)]] == 1
                assert int(end) - int(start) == counts["literal_tokens"] + counts["match_bytes"]
                blocks.setdefault((name, filename), []).append({"block": int(bi), "from_byte": int(start), "to_byte": int(end),
                    "block_type": ["stored", "fixed", "dynamic"][int(kind)], "original_model_bits": {"fixed": int(fix), "dynamic": int(dyn), "stored_before_alignment": int(stored)}, "counts": counts})
        assert len(files) == len(blocks) == 84
        rows = []
        expected = {n: expected_rows(n, s) for n, s in SOURCES.items()}
        for key, row in files.items():
            name, filename = key; parent = expected[name][filename]
            for k in ["raw_bytes", "input_sha256", "output_bytes", "tokens", "tokens_sha256", "output_sha256"]: assert row[k] == parent[k], (name, filename, k)
            bs = blocks[key]; assert [b["block"] for b in bs] == list(range(len(bs)))
            assert bs[0]["from_byte"] == 0 and bs[-1]["to_byte"] == row["raw_bytes"]
            assert all(a["to_byte"] == b["from_byte"] for a, b in zip(bs, bs[1:]))
            totals = aggregate(bs); assert totals["tokens"] == row["tokens"]
            assert totals["literal_tokens"] + totals["match_bytes"] == row["raw_bytes"]
            route = row["row_index"]; assert route == 32 or 0 <= route < SOURCES[name]["row_count"]
            row.update(route_group=f"{name}:{SOURCES[name]['stem']}_row{route}" if route != 32 else f"{name}:fallback_without_top_row",
                       counts=totals, len3_known_loss_covered_bytes=3 * totals["literal_cheaper"], blocks=bs)
            rows.append(row)
        groups = []
        for name in SOURCES:
            subset = [r for r in rows if r["candidate"] == name]; assert len(subset) == 28 and sum(r["raw_bytes"] for r in subset) == 15930000
            for group in sorted({r["route_group"] for r in subset}):
                rr = [r for r in subset if r["route_group"] == group]; c = aggregate(rr)
                symbol = group.split(":", 1)[1]
                body = checked["sources"][name]["row_bodies"].get(symbol)
                groups.append({"candidate": name, "route_group": group, "original_row_body": body,
                               "original_row_body_sha256": sha(body.encode()) if body is not None else None,
                               "files": [r["file"] for r in rr], "raw_bytes": sum(r["raw_bytes"] for r in rr),
                               "counts": c, "len3_known_loss_covered_bytes": 3 * c["literal_cheaper"]})
        for name, s in SOURCES.items():
            for f, h in s["hashes"].items(): assert sha((ROOT / s["path"] / f).read_bytes()) == h
        assert trusted.read_bytes() == codec_raw and sha(token.read_bytes()) == TOKEN_SHA
        result.update(status="VERIFIED_UNTIMED_ORIGINAL_TOKEN_OUTPUT_ROUTE_AND_LEN3_PRICE_OBSERVER", phase="complete", rows=rows, route_groups=groups,
                      candidate_totals={n: aggregate([r for r in rows if r["candidate"] == n]) for n in SOURCES},
                      reference_receipts={n: {"path": s["fixture"], "sha256": s["fixture_sha256"]} for n, s in SOURCES.items()},
                      parity={"original_vs_route_observer_tokens": True, "original_vs_appended_encoder_outputs": True, "archived_input_token_output_84": True, "independent_zlib_decodes": 84})
    except Exception as exc:
        result.update(status="FAILED_OR_INCOMPLETE_LEN3_PRICE_OBSERVER", error_type=type(exc).__name__, error=str(exc))
        report.write_text(json.dumps(result, indent=2) + "\n"); raise
    report.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps({"status": result["status"], "totals": {n: {f: c[f] for f in BASE_FIELDS} for n, c in result["candidate_totals"].items()}}, indent=2))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(); parser.add_argument("--preflight", action="store_true"); args = parser.parse_args()
    if args.preflight:
        data = preflight(); path = ROOT / "evidence/round25/sol/len3-price-preflight.json"
        path.write_text(json.dumps(data, indent=2) + "\n")
        print(json.dumps({k: v for k, v in data.items() if k not in ["fields", "sources"]}, indent=2))
    else: main()
