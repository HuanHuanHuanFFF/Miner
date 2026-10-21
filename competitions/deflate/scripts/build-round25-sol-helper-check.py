"""Extract a bounded native helper checker without compiling or dispatching it."""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = ROOT / "evidence/round25/sol"
EXPECTED = {
    "parent": "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275",
    "candidate": "043eed530748eafe81e0c2f8c8177c7b6caf03cb79f5aa065233c8689ce81dd8",
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def extract_function(source, name):
    start = source.index("pub fn " + name + "(")
    brace = source.index("{", start)
    depth = 1
    end = brace + 1
    while depth:
        depth += (source[end] == "{") - (source[end] == "}")
        end += 1
    return source[start:end]


HARNESS = r'''
fn valid(s: &[u8], p: usize, result: (usize, usize)) -> bool {
    let (length, distance) = result;
    length >= 3 && length <= 258 && distance > 0 && distance <= 32768
        && distance <= p && p + length <= s.len()
        && s[p - distance..p - distance + length] == s[p..p + length]
}

fn check(s: &[u8], c: usize, c2: usize, p: usize, l: usize, d: usize,
         minl: usize, ls: usize, counts: &mut [usize; 3]) {
    assert!(c <= p && valid(s, p, (l, d)), "generator violated original MatchAt");
    let old = original::pc_f_try(s, c, c2, p, l, d, minl);
    let new = changed::pc_f_try(s, c, c2, p, l, d, minl, ls);
    assert!(valid(s, p, old), "original helper selected invalid source");
    assert!(valid(s, p, new), "changed helper selected invalid source");
    counts[0] += 1;
    if old.0 > l {
        assert_eq!(new, old, "lost original strictly longer acceptance");
        counts[1] += 1;
    }
    if old != new {
        assert_eq!(old, (l, d), "change outside an original rejection");
        assert_eq!(new.0, l, "unexpected non-tie change");
        assert_eq!(new.1, p - c2);
        assert!(ls < p && l < 258 && c2 > 0 && d < p && l >= minl);
        assert_eq!(s[p - 1], s[c2 - 1], "new source cannot cover pending literal");
        assert_ne!(s[p - 1], s[p - 1 - d], "original source already covers it");
        counts[2] += 1;
    }
}

fn disjoint(counts: &mut [usize; 3]) {
    for l in 3..=258usize {
        for minl in [3usize, 4] {
            for prior in 0..4usize {
                for pending in [false, true] {
                    let (c2, c, p) = (16usize, 320usize, 640usize);
                    let mut s = vec![b'!'; 1100];
                    for start in [c2, c, p] {
                        for i in 0..l { s[start + i] = b'A' + (i % 23) as u8; }
                        s[start + l] = if start == p { b'R' } else { b'Q' };
                    }
                    s[p - 1] = b'z';
                    s[c2 - 1] = if prior & 1 == 0 { b'z' } else { b'x' };
                    s[c - 1] = if prior & 2 == 0 { b'y' } else { b'z' };
                    let ls = if pending { p - 1 } else { p };
                    check(&s, c, c2, p, l, p - c, minl, ls, counts);
                }
            }
            // Same source-prefix but a genuinely longer predecessor.
            let (c2, c, p) = (16usize, 320usize, 640usize);
            let mut s = vec![b'!'; 1100];
            for i in 0..258usize {
                s[c2 + i] = b'A' + (i % 23) as u8;
                s[p + i] = b'A' + (i % 23) as u8;
                if i < l { s[c + i] = b'A' + (i % 23) as u8; }
            }
            s[c + l] = b'Q';
            check(&s, c, c2, p, l, p - c, minl, p - 1, counts);
        }
    }
}

fn window_and_end(counts: &mut [usize; 3]) {
    for p in [32767usize, 32768, 32769, 32770, 33000] {
        for c2 in [0usize, 1, 2, p.saturating_sub(32767), p.saturating_sub(32768)] {
            let (c, l) = (p - 100, 4usize);
            let mut s = vec![b'!'; p + 16];
            for start in [c2, c, p] { s[start..start + l].copy_from_slice(b"abcd"); }
            if c2 > 0 { s[c2 - 1] = b'z'; }
            s[p - 1] = b'z'; s[c - 1] = b'y';
            s[c2 + l] = b'Q'; s[p + l] = b'R';
            check(&s, c, c2, p, l, 100, 4, p - 1, counts);
        }
    }
    for l in [3usize, 4, 16, 128, 257, 258] {
        let (c2, c, p) = (16usize, 320usize, 640usize);
        let mut s = vec![b'!'; p + l];
        for start in [c2, c, p] {
            for i in 0..l { s[start + i] = b'A' + (i % 23) as u8; }
        }
        s[p - 1] = b'z'; s[c2 - 1] = b'z'; s[c - 1] = b'y';
        check(&s, c, c2, p, l, p - c, 3, p - 1, counts);
        // Future/self head links must still reject without inspecting that source.
        check(&s, c, p, p, l, p - c, 3, p - 1, counts);
    }
}

fn periodic(counts: &mut [usize; 3]) {
    // Actual old MatchAt positions include overlapping sources and short periods.
    let mut state = 0x5a17_2026_1011u64;
    for case in 0..20000usize {
        state = state.wrapping_mul(6364136223846793005).wrapping_add(1);
        let period = 1 + (state as usize % 23);
        let mut s = vec![b'!'; 1200];
        for i in 0..s.len() { s[i] = b'A' + (i % period) as u8; }
        let p = 400 + case % 400;
        let d = period * (1 + case % 8);
        let c = p - d;
        let c2 = c.saturating_sub(period * (1 + (case / 8) % 8));
        let l = 3 + (case * 17) % 256;
        let ls = if case & 1 == 0 { p - 1 } else { p };
        check(&s, c, c2, p, l, d, if case & 2 == 0 { 3 } else { 4 }, ls, counts);
    }
}

fn main() {
    let mut counts = [0usize; 3];
    disjoint(&mut counts);
    window_and_end(&mut counts);
    periodic(&mut counts);
    assert!(counts[1] > 0 && counts[2] > 0, "both old and new branches must execute");
    println!("{{\"status\":\"PASS_ACTUAL_RUST_HELPER_BOUNDED\",\"cases\":{},\"strictly_longer_acceptances_preserved\":{},\"new_backward_ties\":{},\"scope\":\"Extracted exact helper only; not whole parse, Lean gate, corpus coverage or performance\"}}",
             counts[0], counts[1], counts[2]);
}
'''


def build():
    paths = {
        "parent": ROOT / "candidates/r22-595-chain-halfhead/parse.rs",
        "candidate": ROOT / "candidates/r25-sol-backtie/parse.rs",
    }
    raw = {name: path.read_bytes() for name, path in paths.items()}
    assert {name: sha(data) for name, data in raw.items()} == EXPECTED
    helpers = ("pc_be8", "pc_xor8", "pc_common_from", "pc_f_try")
    modules = []
    for name, module in (("parent", "original"), ("candidate", "changed")):
        functions = "\n\n".join(extract_function(raw[name].decode(), helper) for helper in helpers)
        modules.append("mod " + module + " {\n" + functions + "\n}\n")
    data = ("#![allow(dead_code)]\n" + "\n".join(modules) + HARNESS).encode()
    return data, paths


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data, paths = build()
    output = EVIDENCE / "native-helper-check.rs"
    if args.check:
        assert output.read_bytes() == data
    else:
        assert not output.exists(), output
        output.write_bytes(data)
        record = {
            "status": "PREPARED_NOT_COMPILED_NOT_RUN",
            "source_hashes": EXPECTED,
            "helper_source_sha256": sha(data),
            "extracted_functions": ["pc_be8", "pc_xor8", "pc_common_from", "pc_f_try"],
            "actual_rust_test_intent": "Preserve existing longer acceptance; every selected source byte-valid; any behavior delta is an equal forward match with an additional pending backward literal. Include disjoint support, minimum3/4, max258, empty/future links, exact window32768, end-of-input and periodic overlapping sources.",
            "cloud_commands": ["rustc -O evidence/round25/sol/native-helper-check.rs -o /tmp/r25-sol-helper-check", "/tmp/r25-sol-helper-check"],
            "scope": "Bounded real Rust helper discrimination only. Full parser decoder, fresh official extraction, original obligation/axioms, paired total timing and independent confirmation still required.",
        }
        (EVIDENCE / "native-helper-plan.json").write_bytes((json.dumps(record, indent=2) + "\n").encode())
    print(json.dumps({"file": str(output.relative_to(ROOT)).replace("\\", "/"), "sha256": sha(data), "check": args.check, "status": "PREPARED_NOT_RUN"}))


if __name__ == "__main__":
    main()
