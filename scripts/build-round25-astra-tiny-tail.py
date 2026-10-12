"""Generate one tiny-span remainder repair; no CI or official-tree changes."""
from pathlib import Path
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "evidence/round25/astra"
PARENT = ROOT / "candidates/r22-595-chain-halfhead"
NAME = "r25-astra-tiny-tail"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def replace_once(text, old, new):
    assert text.count(old) == 1, (old[:100], text.count(old))
    return text.replace(old, new)


def model(source):
    table = source.split("pub const q4_TF_LSYM: [u8; 512] = [", 1)[1].split("];", 1)[0]
    symbols = [int(v) for v in re.findall(r"\d+", table)]
    assert len(symbols) == 512
    mask = 302256384
    lens = [0] * 260
    current = 0
    for i in range(3, 259):
        if (mask >> symbols[i]) & 1:
            current = i
        lens[i] = current
    minl = min(i for i in range(3, 259) if lens[i] == i)

    def piece(rem):
        x = lens[min(rem, 258)]
        return x if 3 <= x <= rem else 0

    def gain(l, d):
        c = 168
        if 10 < l < 258:
            c += 16 * ((l - 3).bit_length() - 3)
        if d > 4:
            c += 16 * ((d - 1).bit_length() - 2)
        return l * 80 - c

    def repaired(rem, d):
        x = piece(rem)
        if x >= 3 and minl >= 3 and rem > x and rem - x < minl and minl <= rem:
            a = piece(rem - minl)
            b = piece(rem - a)
            if a >= 3 and b >= 3 and a + b > x and gain(a, d) + gain(b, d) > gain(x, d):
                return a
        return x

    def split(rem, d, repair):
        output = []
        while True:
            x = repaired(rem, d) if repair else piece(rem)
            if x < 3:
                break
            assert x <= rem and x <= 258 and lens[x] == x
            output.append(x)
            rem -= x
        return output, rem

    distances = [1, 2, 4, 5, 8, 16, 32, 128, 512, 2048, 8192, 32768]
    checks = changes = 0
    examples = []
    for d in distances:
        for span in range(0, 2049):
            old, old_rest = split(span, d, False)
            new, rest = split(span, d, True)
            assert rest <= old_rest, (span, d, old, new)
            assert sum(new) + rest == span
            if new != old:
                changes += 1
                if span <= 258 and len(examples) < 24:
                    examples.append({"span": span, "distance": d, "old_pieces": old, "old_literals": old_rest,
                                     "new_pieces": new, "new_literals": rest})
            # et_cover returns covered bytes; et_pieces receives exactly that amount.
            emitted, leftover = split(sum(new), d, True)
            assert leftover == 0 and sum(emitted) == sum(new), (span, d, new, emitted, leftover)
            checks += 1
    assert split(65, 1, True) == ([54, 11], 0)
    assert split(23, 1, True) == ([22], 1)
    return {"status": "VERIFIED_FINITE_SPLIT_MODEL_ONLY", "span_range_inclusive": [0, 2048],
            "distances": distances, "cases": checks, "changed_cases": changes, "min_length": minl,
            "allowed_lengths": [i for i in range(3, 259) if lens[i] == i], "examples": examples,
            "scope": "No new length symbols; finite model pieces valid and covered length is emit-stable. Actual Rust/native encoder/Lean proof remain unverified."}


def main():
    parent = (PARENT / "parse.rs").read_bytes()
    assert sha(parent) == "57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275"
    source = parent.decode()
    check = model(source)
    helper = """/// R25: repair a greedy short literal tail using two already-allowed lengths.
/// The price estimate only screens the split; original encoding measures actual cost.
#[inline(always)]
pub fn et_piece_tail(lens: &[u16; 260], rem: usize, minl: usize, d: usize) -> usize {
    let x = q4_e_piece(lens, rem);
    if x >= 3 && minl >= 3 && rem > x && rem - x < minl && minl <= rem {
        let a = q4_e_piece(lens, rem - minl);
        let b = q4_e_piece(lens, rem - a);
        if a >= 3 && b >= 3 && a + b > x && pc_gain(a, d) + pc_gain(b, d) > pc_gain(x, d) {
            a
        } else { x }
    } else { x }
}

"""
    source = replace_once(source, "/// Bytes covered by the greedy pieces of allowed lengths of a match of length `l`.",
                          helper + "/// Bytes covered by allowed pieces, including a profitable two-piece tail repair.")
    source = replace_once(source,
        "pub fn et_cover(lens: &[u16; 260], l: usize) -> usize {",
        "pub fn et_cover(lens: &[u16; 260], l: usize, minl: usize, d: usize) -> usize {")
    start = source.index("pub fn et_cover(")
    end = source.index("/// Record the positions", start)
    body = replace_once(source[start:end], "let x = q4_e_piece(lens, r);", "let x = et_piece_tail(lens, r, minl, d);")
    source = source[:start] + body + source[end:]
    source = replace_once(source, "et_cover(lens, bk + f)", "et_cover(lens, bk + f, minl, d)")
    source = replace_once(source,
        "pub fn et_pieces(s: &[u8], out: &mut [u32], nt0: usize, x0: usize, end: usize, d: usize, lens: &[u16; 260]) -> (usize, usize) {",
        "pub fn et_pieces(s: &[u8], out: &mut [u32], nt0: usize, x0: usize, end: usize, d: usize, lens: &[u16; 260], minl: usize) -> (usize, usize) {")
    source = replace_once(source, "let pc = q4_e_piece(lens, end - x);", "let pc = et_piece_tail(lens, end - x, minl, d);")
    source = replace_once(source,
        "pub fn et_emit(s: &[u8], out: &mut [u32], nt0: usize, ls: usize, bs0: usize, bd: usize, bcov: usize, bend: usize, lens: &[u16; 260]) -> (usize, usize) {",
        "pub fn et_emit(s: &[u8], out: &mut [u32], nt0: usize, ls: usize, bs0: usize, bd: usize, bcov: usize, bend: usize, lens: &[u16; 260], minl: usize) -> (usize, usize) {")
    source = replace_once(source, "et_cover(lens, bend - st)", "et_cover(lens, bend - st, minl, bd)")
    source = replace_once(source, "et_pieces(s, out, r.0, bs, end, bd, lens)", "et_pieces(s, out, r.0, bs, end, bd, lens, minl)")
    source = replace_once(source, "et_emit(s, out, nt, ls, c.0, c.1, c.2, c.3, &lens)",
                          "et_emit(s, out, nt, ls, c.0, c.1, c.2, c.3, &lens, minl)")
    path = ROOT / "candidates" / NAME
    assert not path.exists(), path
    path.mkdir()
    files = {"parse.rs": source.encode(), "Parse.lean": (PARENT / "Parse.lean").read_bytes()}
    for filename, data in files.items():
        assert len(data) <= 524288
        (path / filename).write_bytes(data)
    hashes = {f: sha(data) for f, data in files.items()}
    manifest = {"candidate": NAME, "parent": PARENT.name, "hashes": hashes,
        "mechanism": "Repair a final shorter-than-minimum literal tail by reducing the previous greedy piece and adding a second existing allowed length at the same validated distance. Original pc_gain screens the added token cost; actual original encoder bytes decide quality. et_cover and et_pieces use the same selector.",
        "difference_from_old_work": "No matchfinder, search-depth, mask or distance-admission threshold change. Existing q4_e_piece greedily takes the largest allowed length, whereas older TF planners had a more expensive two-piece search. This is a bounded constant-work transfer of remainder repair into current et_tiny, not R24 DNA cost40 or generic gap rescue.",
        "attribution": {"source": "references/round21-public-595/source-receipt.json",
                        "inherited_helper": "Original q4_e_piece, pc_gain and all byte-validation/emission machinery retained.",
                        "prior_mechanism": "candidates/probe3/parse.rs tf_piece0 had general two-kept-length search; current helper uses at most two extra table reads and three gain calls only at a stranded tail."},
        "proof_status": "DRAFT_UNCOMPILED_FOR_NEW_EXACT_PAIR",
        "proof_migration": "New et_piece_tail range/decrease lemma. et_cover/et_pieces/et_emit and extracted loop captures gain minl/d parameters. Preserve original Matches/Dec and trusted emit; finite split model is not the full obligation.",
        "performance_status": "UNKNOWN", "formal_submission_sent": False}
    (path / "manifest.json").write_bytes((json.dumps(manifest, indent=2) + "\n").encode())
    entry = {"name": NAME, "path": path.relative_to(ROOT).as_posix(), "control": False,
             "hashes": hashes, "anchor": "public595", "comparison_baseline": "combo",
             "native_decode_reference": "combo"}
    for name, value in [("tiny-tail-entry.json", entry), ("tiny-tail-model.json", check),
                        ("tiny-tail-preflight.json", {
                            "status": "PREDECLARED_NATIVE_QUALITY_SCREEN",
                            "known_gap": "Same-input tiny-config bytes: combo2487, public5842155, public6092077. This is only an opportunity bound from different parsers, not achievable savings for tail repair.",
                            "minimum": "Run actual Rust through original28-file encoder with exact combo/public595 references and independent decode. Save all per-file token/output hashes and bytes.",
                            "cost_cap_runner_minutes": 12,
                            "decision": "If output is identical, count real et_piece_tail stranded-tail calls before any more variants. If smaller, inspect extra tokens and original paired total time before gate. If larger, stop this concrete split-cost policy; do not sweep literal prices or length masks.",
                            "proof": "New exact Rust/Lean remains DRAFT; actual extraction and original full gate required."
                        })]:
        target = OUT / name
        assert not target.exists(), target
        target.write_bytes((json.dumps(value, indent=2) + "\n").encode())
    print(json.dumps({"entry": entry, "finite_cases": check["cases"], "changed_cases": check["changed_cases"]}, indent=2))


if __name__ == "__main__":
    main()
