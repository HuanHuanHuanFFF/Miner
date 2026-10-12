"""Share one local eight-byte word between end4 and its end1 tail key."""
from pathlib import Path
import argparse
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r25-astra-end4"
NAME = "r25-sol-end4-wordtail"
EVIDENCE = ROOT / "evidence/round25/sol"
EXPECTED = {
    "parse.rs": "03ec0aa4e617d622755e85324a9d4fbc77ef74e6572485b3170e2790681ed8e6",
    "Parse.lean": "4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6",
}
HELPER = """/// Hash an already loaded four-byte big-endian key; same formula as pc_slot_of_m.
#[inline(always)]
pub fn r25_pc_slot_word<const H: usize>(word: u32, km: u32) -> usize {
    let k = (word & km) as u64;
    (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - pc_HB)) as usize % H
}

"""
OLD_EXTRA = """    // One complete four-byte key at the matched suffix, before the crossing end-1 key.
    // Preserve the original head inserts and monotone position order; never duplicate them.
    if end >= 4 && ins <= end - 4 && end - 4 < lim {
        let j = end - 4;
        let a = pc_slot_of_m::<H>(s, j, km);
        pc_f_link::<H>(head, prev, a, j);
    }
"""
NEW_EXTRA = """    // One complete four-byte key at the matched suffix, before the crossing end-1 key.
    // The two keys are three bytes apart; keep their link order and share this local word.
    let mut tail_a = H;
    if end >= 4 && ins <= end - 4 && end - 4 < lim {
        let j = end - 4;
        let word = pc_be8(s, j);
        let a = r25_pc_slot_word::<H>((word >> 32) as u32, km);
        pc_f_link::<H>(head, prev, a, j);
        // ins <= end-4 implies that the original TAIL=1 branch takes end-1.
        // An absent tail leaves the impossible-slot sentinel and performs no second hash.
        if end - 1 < lim {
            tail_a = r25_pc_slot_word::<H>((word >> 8) as u32, km);
        }
    }
"""


def sha(data):
    return hashlib.sha256(data).hexdigest()


def generate():
    raw = {name: (BASE / name).read_bytes() for name in EXPECTED}
    assert {name: sha(data) for name, data in raw.items()} == EXPECTED
    source = raw["parse.rs"].decode()
    start = source.index("pub fn pc_f_record3<const H: usize>")
    end = source.index("/// `pc_run1` with chain links", start)
    before = source[start:end]
    assert before.count(OLD_EXTRA) == 1
    after = before.replace(OLD_EXTRA, NEW_EXTRA, 1)
    tail_start = after.index("    if pc_TAIL == 1 {")
    tail_end = after.index("    } else {", tail_start)
    old_tail = after[tail_start:tail_end]
    needle = "            let a = pc_slot_of_m::<H>(s, ins, km);"
    assert old_tail.count(needle) == 1
    new_tail = old_tail.replace(needle,
        "            let a = if tail_a < H { tail_a } else { pc_slot_of_m::<H>(s, ins, km) };", 1)
    after = after[:tail_start] + new_tail + after[tail_end:]
    attr = source.rfind("#[inline(always)]", 0, start)
    source = source[:attr] + HELPER + source[attr:start] + after + source[end:]
    assert source.replace(HELPER, "", 1).replace(after, before, 1).encode() == raw["parse.rs"]
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    assert all(0 < len(value) <= 524288 for value in files.values())
    hashes = {name: sha(data) for name, data in files.items()}
    manifest = {
        "candidate": NAME, "parent": BASE.name, "parent_hashes": EXPECTED,
        "hashes": hashes,
        "mechanism": "On the existing eligible end4 insertion, read one local big-endian8 word. Derive end4 key with >>32 and end1 key with >>8, using the identical masked multiply/shift/mod hash. Preserve both original link operations in end4-before-end1 order and every existing insertion guard. Reuse a bounded cached tail slot only in TAIL=1; all other paths retain the original slot load.",
        "difference_from_old_work": "The end4 parent introduces a new adjacent pair of4-byte insertion keys at offset3. This shares their one local overlapping byte load, without persistent main-loop word state, changed search, removed updates, compact tables or match-prefix cache maintenance. R12 wordhead carried a word across hash/probe iterations and regressed; R13 matched-ahead skipped a different load and regressed; R24 prefix/range caches added different maintenance work. Those negative results remain retained.",
        "attribution": {"parent": "candidates/r25-astra-end4/manifest.json",
            "original_source": "references/round21-public-595/source-receipt.json",
            "ownership": "Public595 matcher and original headers retained; end4 mechanism inherited from Astra's R25 candidate. This Sol derivative changes local input-word reuse only."},
        "semantic_status": "INFERRED token/byte equality with exact end4. Native28-file token/original-encoder/decode parity is required; finite key/index models are not a Rust equivalence certificate.",
        "proof_status": "DRAFT_PARENT_LEAN_COPIED_UNADAPTED_FOR_WORD_HASH_HELPER",
        "proof_migration": "New r25_pc_slot_word needs only0<H and returns slot<H. Actual pc_f_record3 extraction must check the local tail_a cached slot/sentinel branch. No main-loop state, source obligation, table type or recording loop changes intended; original fresh gate required.",
        "performance_status": "UNKNOWN; fewer source loads do not establish CPU or total-time improvement",
        "comparison_baseline": "end4", "native_decode_reference": "end4",
        "expected_equivalent_to": "end4", "formal_submission_sent": False,
        "source_reversal": "Remove one word-hash helper and reverse the isolated record3 body replacement to recover exact end4 Rust bytes. Lean is an exact parent copy.",
        "stop_condition": "Any actual token/encoder/decode mismatch stops or diagnoses this exact implementation. Only preserved end4 quality and useful original paired total time can justify new proof migration or confirmation. Leaf code size, counters and instruction count never substitute for total-time evidence.",
    }
    files["manifest.json"] = (json.dumps(manifest, indent=2, ensure_ascii=False) + "\n").encode()
    return files, manifest


def models():
    rng = random.Random(251011)
    salt = 0x9E3779B97F4A7C15
    words = [value << (8 * byte) for byte in range(8) for value in range(256)]
    words += [rng.getrandbits(64) for _ in range(10000)]
    cases = 0
    for word in words:
        data = word.to_bytes(8, "big")
        for km in (0xFFFFFF00, 0xFFFFFFFF):
            for size in (1, 8192, 32768, 65536):
                def slot(key):
                    return (((key & km) * salt & ((1 << 64) - 1)) >> 49) % size
                assert slot(word >> 32) == slot(int.from_bytes(data[:4], "big"))
                assert slot((word >> 8) & 0xFFFFFFFF) == slot(int.from_bytes(data[3:7], "big"))
                cases += 1
    indices = 0
    cache_hits = 0
    for p in range(8):
        for length in range(3, 259):
            for ahead in (1, 2):
                for remaining in (0, 1, 4, 8, 16):
                    end = p + length
                    n = end + remaining
                    if n <= 16 or p >= n - 8:
                        continue
                    lim = n - 8
                    ins0 = p + ahead
                    stop = min(end, ins0 + 2, lim)
                    ins = max(ins0, stop)
                    extra = end >= 4 and ins <= end - 4 and end - 4 < lim
                    tail = end - 1 if ins + 1 < end else ins
                    old = ([end - 4] if extra else []) + ([tail] if tail < end and tail < lim else [])
                    cached_tail = extra and end - 1 < lim
                    if extra:
                        assert end - 4 + 8 < n
                        assert ins + 1 < end
                    if cached_tail:
                        assert tail == end - 1 and tail == end - 4 + 3
                        cache_hits += 1
                    new = ([end - 4] if extra else []) + ([end - 1 if cached_tail else tail] if tail < end and tail < lim else [])
                    assert new == old
                    indices += 1
    return {"status": "VERIFIED_FINITE_PYTHON_KEY_AND_INDEX_MODELS_ONLY",
        "key_cases": cases, "word_cases": len(words), "index_cases": indices,
        "index_cases_with_cached_tail": cache_hits,
        "scope": "Integer key extraction/hash and small insertion/boundary trace model only. No Rust execution, actual corpus insertion frequency, universal parse equivalence, Lean gate or performance claim."}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    files, manifest = generate()
    destination = ROOT / "candidates" / NAME
    if args.check:
        assert all((destination / name).read_bytes() == files[name] for name in ("parse.rs", "Parse.lean"))
        assert json.loads((destination / "manifest.json").read_bytes())["hashes"] == manifest["hashes"]
    else:
        assert not destination.exists(), destination
        destination.mkdir()
        for name, data in files.items():
            (destination / name).write_bytes(data)
        plan = {"candidate": NAME, "parent_hashes": EXPECTED, "hashes": manifest["hashes"],
            "source_reversal_exact": True, "lean_is_exact_parent_copy": True,
            "minimum_action": "Actual28-file full token/original-encoder/decode equality with frozen end4. If identical, original paired total time versus end4 and combo; no leaf-only timing promotion.",
            "cost_cap_runner_minutes_for_native": 12, "models": models(),
            "proof_status": manifest["proof_status"], "native_rust": "NOT_RUN", "total_time": "NOT_RUN"}
        entries = [{"name": NAME, "path": destination.relative_to(ROOT).as_posix(), "control": False,
            "hashes": manifest["hashes"], "anchor": "public595", "comparison_baseline": "end4",
            "native_decode_reference": "end4", "expected_equivalent_to": "end4"}]
        for name, data in (("wordtail-preflight.json", plan), ("wordtail-entries.json", entries)):
            path = EVIDENCE / name
            assert not path.exists(), path
            path.write_bytes((json.dumps(data, indent=2, ensure_ascii=False) + "\n").encode())
    print(json.dumps({"candidate": NAME, "hashes": manifest["hashes"], "status": manifest["proof_status"], "check": args.check}))


if __name__ == "__main__":
    main()
