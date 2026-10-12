"""Untimed pinned-encoder work counts for two frozen parsers and two tiny inputs."""
from pathlib import Path
import ast
import hashlib
import importlib
import json
import os
import re
import struct
import sys
import zlib

ROOT = Path(__file__).resolve().parents[1]
CODEC_SHA = "172c240014f65d5e2762c1287e4982dd1cd426f2999f74e17011e05f2dc5fdec"
TOKEN_SHA = "8bf5d962324b3a0890f3c75f713198be086c4b0659797c24b8b976978cea4917"
PARSERS = {
    "combo": "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275",
    "tiny_pc8": "5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00",
}
FILES = ["tiny-config.json.txt", "tiny-app.log"]
TREE_FIELDS = ["live_symbols", "rounds", "packages_built", "merge_leaf_clones", "merge_package_clones",
               "syms_clone_elements", "syms_extend_elements", "selected_packages", "selected_symbol_visits",
               "logical_syms_vec_clone_calls"]
FIXTURE = ROOT / "evidence/round25/38129545231/quality-i-native/diagnostics/r13-encoder/encoder.json"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def once(text, old, new):
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new)


def instrument(raw):
    assert sha(raw) == CODEC_SHA
    text = raw.decode()
    a = text.index("fn package_merge(")
    b = text.index("/// Canonical codes", a)
    body = text[a:b]
    live = "    let live: Vec<usize> = (0..n).filter(|&i| freqs[i] > 0).collect();"
    body = once(body, live, live + "\n    let mut trace = [0u64; 10];\n    trace[0] = live.len() as u64;")
    body = once(body, "        0 => return lengths,", "        0 => { r25_tree(freqs, max_bits, &lengths, &trace); return lengths; },")
    body = once(body, "            return lengths;", "            r25_tree(freqs, max_bits, &lengths, &trace);\n            return lengths;")
    body = once(body, "    let mut current = leaves.clone();", "    let mut current = leaves.clone();\n    trace[5] += live.len() as u64;\n    trace[9] += live.len() as u64;")
    body = once(body, "    for _ in 1..max_bits {", "    for _ in 1..max_bits {\n        trace[1] += 1;")
    body = once(body, "            let mut syms = current[i].syms.clone();",
                "            trace[2] += 1;\n            trace[5] += current[i].syms.len() as u64;\n            trace[6] += current[i + 1].syms.len() as u64;\n            trace[9] += 1;\n            let mut syms = current[i].syms.clone();")
    body = once(body, "                merged.push(leaves[a].clone());",
                "                trace[3] += 1;\n                trace[5] += leaves[a].syms.len() as u64;\n                trace[9] += 1;\n                merged.push(leaves[a].clone());")
    body = once(body, "                merged.push(packaged[b].clone());",
                "                trace[4] += 1;\n                trace[5] += packaged[b].syms.len() as u64;\n                trace[9] += 1;\n                merged.push(packaged[b].clone());")
    body = once(body, "    for pkg in current.iter().take(take) {", "    for pkg in current.iter().take(take) {\n        trace[7] += 1;")
    body = once(body, "        for &s in &pkg.syms {", "        for &s in &pkg.syms {\n            trace[8] += 1;")
    body = once(body, "    lengths\n}", "    r25_tree(freqs, max_bits, &lengths, &trace);\n    lengths\n}")
    text = text[:a] + body + text[b:]
    bits = "    let stored_bits = 3 + 32 + 8 * b.raw_len as u64;"
    text = once(text, bits, bits + "\n    println!(\"R25_BLOCK {} {} {} {} {} {} {} {}\", b.items.len(), b.raw_len, hlit, hdist, hclen(&cl), dyn_bits, fix_bits, stored_bits);")
    guard = "        if b.items.iter().all(|&(_, _, _, d, _, _)| d == u16::MAX) {"
    text = once(text, guard, guard + "\n            println!(\"R25_CHOICE stored\");")
    text = once(text, "    if fix_bits <= dyn_bits {", "    if fix_bits <= dyn_bits {\n        println!(\"R25_CHOICE fixed\");")
    text = once(text, "    let llc = canonical(&ll, MAX_BITS_LITLEN);", "    println!(\"R25_CHOICE dynamic\");\n    let llc = canonical(&ll, MAX_BITS_LITLEN);")
    text += """
fn r25_tree(freqs: &[u32], max_bits: u32, lengths: &[u8], trace: &[u64; 10]) {
    println!("R25_TREE {} {} {:?} {:?} {:?}", freqs.len(), max_bits, freqs, lengths, trace);
}
"""
    return text.encode()


HARNESS = r'''
#![allow(dead_code)]
#[path=TOKEN] mod token;
#[path=CODEC] mod codec;
#[path=OBSERVED] mod observed;
MODULES
type Parser=fn(&[u8],&mut[u32])->usize;
fn tokens(s:&[u8],f:Parser)->Vec<u32>{let mut out=vec![0;s.len()];let n=f(s,&mut out);assert!(n<=s.len());out.truncate(n);out}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::new();for&t in ts{match token::decode(t){token::Token::Literal(x)=>out.push(x),token::Token::Match{dist,len}=>{if dist as usize>out.len()||out.len()+len as usize>s.len(){return false;}for _ in 0..len{let x=out[out.len()-dist as usize];out.push(x);}},_=>return false}}out==s}
fn main(){let args:Vec<_>=std::env::args().collect();let corpus=std::path::Path::new(&args[1]);let spool=std::path::Path::new(&args[2]);let cases:&[(&str,Parser)]=&[CASES];
for name in ["tiny-config.json.txt","tiny-app.log"]{let s=std::fs::read(corpus.join(name)).unwrap();for&(label,f)in cases{
let ts=tokens(&s,f);assert!(decode(&s,&ts));println!("R25_CONTEXT {} {}",label,name);
let original=codec::encode(&ts,s.len()).unwrap();let measured=observed::encode(&ts,s.len()).unwrap();assert_eq!(original,measured,"encoder identity {} {}",label,name);
let mut raw=Vec::new();for&t in&ts{raw.extend(t.to_le_bytes());}let stem=format!("{}-{}",label,name);
std::fs::write(spool.join(format!("{}.tokens",stem)),raw).unwrap();std::fs::write(spool.join(format!("{}.deflate",stem)),&original).unwrap();std::fs::write(spool.join(format!("{}.observed.deflate",stem)),&measured).unwrap();
println!("R25_RESULT {} {} {} {}",label,name,ts.len(),original.len());}}}
'''


def tables(text):
    def get(name):
        part = text.split("const " + name + ":", 1)[1].split("= [", 1)[1].split("];", 1)[0]
        return [(int(a), int(b)) for a, b in re.findall(r"\((\d+),\s*(\d+)\)", part)]
    length, distance = get("LEN_TABLE"), get("DIST_TABLE")
    assert len(length) == 29 and len(distance) == 30
    return length, distance


def token_summary(raw, codec):
    lt, dt = tables(codec)
    assert len(raw) % 4 == 0
    ts = [x[0] for x in struct.iter_unpack("<I", raw)]
    ll, dd = [0] * 288, [0] * 30
    literals = matches = length_steps = distance_steps = produced = 0
    for token in ts:
        if token < 256:
            ll[token] += 1
            literals += 1
            produced += 1
        else:
            assert 16777216 <= token < 25165824
            value = token - 16777216
            distance, length = value // 256 + 1, value % 256 + 3
            assert distance <= produced
            li, di = len(lt) - 1, len(dt) - 1
            while lt[li][1] > length:
                li -= 1
                length_steps += 1
            while dt[di][1] > distance:
                di -= 1
                distance_steps += 1
            ll[257 + li] += 1
            dd[di] += 1
            produced += length
            matches += 1
    # Both selected inputs are known to fit one encoder block; do not merge histograms across blocks.
    assert len(ts) < 16384
    ll[256] += 1
    return {"tokens": len(ts), "literal_tokens": literals, "match_tokens": matches, "produced_bytes": produced,
            "litlen_frequency_including_eob": ll, "distance_frequency": dd,
            "live_literal_symbols": sum(x > 0 for x in ll[:256]),
            "live_length_symbols": sum(x > 0 for x in ll[257:]), "live_distance_symbols": sum(x > 0 for x in dd),
            "len_code_while_iterations": length_steps, "dist_code_while_iterations": distance_steps,
            "lookup_comparisons_including_exit": length_steps + distance_steps + 2 * matches}


def read_arrays(text):
    decoder, result = json.JSONDecoder(), []
    while text.strip():
        value, end = decoder.raw_decode(text.lstrip())
        result.append(value)
        text = text.lstrip()[end:]
    return result


def self_check():
    codec = ROOT / "sources/conjectures-optimisation-deflate/validator/measure/src/deflate.rs"
    original = codec.read_bytes()
    # Read-only local checkout can carry CRLF; the pinned Linux file is the exact LF byte stream.
    raw = original.replace(b"\r\n", b"\n")
    observer = instrument(raw)
    assert codec.read_bytes() == original
    assert observer.count(b"R25_CHOICE ") == 3 and observer.count(b"R25_BLOCK ") == 1
    assert read_arrays("[1, 2] [3] [4, 5]") == [[1, 2], [3], [4, 5]]
    sample = struct.pack("<2I", 65, 16777216 + 8)  # one literal + length11/distance1
    summary = token_summary(sample, raw.decode())
    assert summary["produced_bytes"] == 12 and summary["live_length_symbols"] == 1
    report = {"status": "VERIFIED_GENERATOR_TABLE_AND_PARSE_PREFLIGHT_NOT_NATIVE", "codec_sha256": sha(raw),
              "local_checkout_sha256": sha(original), "local_line_endings_normalized_in_memory_only": original != raw,
              "observer_sha256": sha(observer), "observer_bytes": len(observer), "tree_fields": TREE_FIELDS,
              "compile": "NOT_RUN", "native": "NOT_RUN", "official_codec_unchanged": True}
    target = ROOT / "evidence/round25/astra/tiny-encoder-selfcheck.json"
    target.write_bytes((json.dumps(report, indent=2) + "\n").encode())
    print(json.dumps(report, indent=2))


def preflight(spec):
    """Pure local/spec preflight used by the root's dispatcher; no build or artifact writes."""
    assert spec.get("r25_tiny_encoder_counts") is True and spec.get("native_encoder") is False
    assert not spec.get("extract_candidates") and not spec.get("gate_candidates")
    by_name = {e["name"]: e for e in spec["entries"]}
    for name, expected in (("combo", PARSERS["combo"]), ("r25-root-tiny-pc8", PARSERS["tiny_pc8"])):
        entry = by_name[name]
        assert entry["control"] is True and entry["hashes"]["parse.rs"] == expected
        assert sha((ROOT / entry["path"] / "parse.rs").read_bytes()) == expected
    assert FIXTURE.is_file(), "Frozen I native fixture must be committed before dispatch"
    fixture = json.loads(FIXTURE.read_bytes())
    assert fixture["status"] == "VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES"
    assert fixture["codec_sha256"] == CODEC_SHA and fixture["token_sha256"] == TOKEN_SHA
    required = {(name, file) for name in ("combo", "r25-root-tiny-pc8") for file in FILES}
    assert required <= {(r["candidate"], r["file"]) for r in fixture["rows"]}
    for name, expected in (("combo", PARSERS["combo"]), ("r25-root-tiny-pc8", PARSERS["tiny_pc8"])):
        assert fixture["source_hashes"][name]["parse.rs"] == expected
    codec = ROOT / "sources/conjectures-optimisation-deflate/validator/measure/src/deflate.rs"
    result = {"status": "VERIFIED_FROZEN_SPEC_SOURCE_AND_FIXTURE_ONLY",
              "parsers": ["combo", "r25-root-tiny-pc8"], "files": FILES, "native": "NOT_RUN",
              "fixture_sha256": sha(FIXTURE.read_bytes()), "runtime_codec_sha256_required": CODEC_SHA,
              "runtime_token_sha256_required": TOKEN_SHA}
    if codec.is_file():
        original = codec.read_bytes()
        observed = instrument(original.replace(b"\r\n", b"\n"))
        assert codec.read_bytes() == original
        result.update(observer_generation="VERIFIED_OPTIONAL_LOCAL_READING_COPY", observer_sha256=sha(observed))
    else:
        result.update(observer_generation="PENDING_RUNTIME_AFTER_CI_PREPARE", observer_sha256=None,
                      local_reader="Absent; not required before ci-prepare. Runtime DEFLATE_ROOT bytes remain mandatory.")
    return result


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    from round4 import validate
    spec = validate(os.environ["ROUND4_SPEC"])
    assert spec.get("r25_tiny_encoder_counts") and not spec.get("native_encoder")
    preflight(spec)
    captured = importlib.import_module("research-round25-dual8-counts").captured
    upstream = Path(os.environ["DEFLATE_ROOT"])
    codec = upstream / "validator/measure/src/deflate.rs"
    token = codec.with_name("token.rs")
    codec_raw, token_raw = codec.read_bytes(), token.read_bytes()
    assert sha(codec_raw) == CODEC_SHA and sha(token_raw) == TOKEN_SHA
    build = Path(os.environ["RUNNER_TEMP"]) / "r25-tiny-encoder-build"
    build.mkdir()
    out = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/r25-tiny-encoder"
    out.mkdir(parents=True)
    spool = out / "tokens-and-output"
    spool.mkdir()
    obs = build / "deflate-observed.rs"
    observed = instrument(codec_raw)
    obs.write_bytes(observed)
    modules, cases, sources = [], [], {}
    for i, (label, expected) in enumerate(PARSERS.items()):
        entry = next(e for e in spec["entries"] if e["hashes"]["parse.rs"] == expected)
        source = ROOT / entry["path"] / "parse.rs"
        assert sha(source.read_bytes()) == expected
        modules.append(f"#[path={json.dumps(str(source))}] mod parser{i};")
        cases.append(f"({json.dumps(label)},parser{i}::parse)")
        sources[label] = {"entry": entry["name"], "path": entry["path"], "hashes": entry["hashes"]}
    harness = HARNESS.replace("TOKEN", json.dumps(str(token))).replace("CODEC", json.dumps(str(codec)))
    harness = harness.replace("OBSERVED", json.dumps(str(obs))).replace("MODULES", "\n".join(modules)).replace("CASES", ",".join(cases))
    driver = build / "main.rs"
    driver.write_text(harness)
    (out / "deflate-observed.rs").write_bytes(observed)
    (out / "harness.rs").write_text(harness)
    result = {"status": "STARTED_UNTIMED_PINNED_ENCODER_DIAGNOSTIC", "run_id": os.environ["GITHUB_RUN_ID"],
              "git_sha": os.environ["GITHUB_SHA"], "batch": os.environ["ROUND4_SPEC"], "sources": sources,
              "codec_sha256": CODEC_SHA, "token_sha256": TOKEN_SHA, "observer_sha256": sha(observed),
              "harness_sha256": sha(harness.encode()), "scope": "Untimed logical algorithm work, not performance. Original/observer encoders must return identical bytes for exactly the same frozen tokens, plus independent zlib decode and priorI token/output identity. No official codec or candidate changed."}
    report = out / "receipt.json"
    report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
    try:
        result["phase"] = "compile"
        binary = build / "check"
        captured(["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes", str(driver), "-o", str(binary)], out / "compile.log", 180)
        result["phase"] = "run"
        corpus = upstream / "data/benchmark/corpus-stage1"
        run = captured([str(binary), str(corpus), str(spool)], out / "run.log", 180)
        traces, current = {}, None
        for line in run.stdout.splitlines():
            if line.startswith("R25_CONTEXT "):
                _, label, file = line.split()
                current = (label, file)
                assert current not in traces
                traces[current] = {"trees": [], "blocks": [], "choices": []}
            elif line.startswith("R25_TREE "):
                _, n, bits, arrays = line.split(" ", 3)
                freq, lengths, work = read_arrays(arrays)
                assert len(freq) == len(lengths) == int(n) and len(work) == len(TREE_FIELDS)
                assert work[0] == sum(x > 0 for x in freq)
                if work[0] >= 2:
                    assert work[1] == int(bits) - 1
                    assert work[9] == work[0] + work[2] + work[3] + work[4]
                traces[current]["trees"].append({"alphabet_size": int(n), "max_bits": int(bits), "frequency": freq,
                                                  "code_lengths": lengths, "work": dict(zip(TREE_FIELDS, work))})
            elif line.startswith("R25_BLOCK "):
                values = list(map(int, line.split()[1:]))
                assert len(values) == 8
                traces[current]["blocks"].append(dict(zip(["items", "raw_bytes", "hlit", "hdist", "hclen", "dynamic_bits", "fixed_bits", "stored_bits"], values)))
            elif line.startswith("R25_CHOICE "):
                traces[current]["choices"].append(line.split()[1])
        fixture = json.loads(FIXTURE.read_bytes())
        prior = {(r["candidate"], r["file"]): r for r in fixture["rows"]}
        rows = []
        for (label, file), trace in traces.items():
            assert label in PARSERS and file in FILES
            raw_input = (corpus / file).read_bytes()
            stem = label + "-" + file
            ts = (spool / (stem + ".tokens")).read_bytes()
            enc = (spool / (stem + ".deflate")).read_bytes()
            obs_enc = (spool / (stem + ".observed.deflate")).read_bytes()
            assert enc == obs_enc and zlib.decompress(enc, -15) == raw_input
            expected = prior[("combo" if label == "combo" else "r25-root-tiny-pc8", file)]
            assert (sha(raw_input), sha(ts), sha(enc)) == (expected["input_sha256"], expected["tokens_sha256"], expected["output_sha256"])
            summary = token_summary(ts, codec_raw.decode())
            assert summary["produced_bytes"] == len(raw_input)
            assert len(trace["trees"]) == 3 and len(trace["blocks"]) == len(trace["choices"]) == 1
            assert [t["alphabet_size"] for t in trace["trees"]] == [288, 30, 19]
            assert trace["trees"][0]["frequency"] == summary["litlen_frequency_including_eob"]
            assert trace["trees"][1]["frequency"] == summary["distance_frequency"]
            assert trace["blocks"][0]["items"] == summary["tokens"]
            assert ((enc[0] >> 1) & 3) == {"stored": 0, "fixed": 1, "dynamic": 2}[trace["choices"][0]]
            rows.append({"candidate": label, "file": file, "input_sha256": sha(raw_input), "tokens_sha256": sha(ts),
                         "output_sha256": sha(enc), "output_bytes": len(enc), "token_summary": summary, **trace})
        assert len(rows) == 4
        # Unchanged tiny-app is an independent instrumentation/control identity check.
        control = [r for r in rows if r["file"] == "tiny-app.log"]
        assert len(control) == 2
        for key in ("tokens_sha256", "output_sha256", "token_summary", "trees", "blocks", "choices"):
            assert control[0][key] == control[1][key]
        assert codec.read_bytes() == codec_raw and token.read_bytes() == token_raw
        result.update(status="VERIFIED_UNTIMED_ORIGINAL_OBSERVER_BYTES_DECODE_AND_PRIOR_IDENTITY", phase="complete", rows=rows)
    except Exception as exc:
        result.update(status="FAILED_OR_INCOMPLETE_TINY_ENCODER_DIAGNOSTIC", error_type=type(exc).__name__, error=str(exc))
        report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
        raise
    report.write_bytes((json.dumps(result, indent=2) + "\n").encode())
    print(json.dumps({"status": result["status"], "rows": [{"candidate": r["candidate"], "file": r["file"],
                      "live_symbols": [t["work"]["live_symbols"] for t in r["trees"]], "choices": r["choices"]} for r in rows]}, indent=2))


if __name__ == "__main__":
    if sys.argv[1:] == ["--self-check"]:
        self_check()
    else:
        main()
