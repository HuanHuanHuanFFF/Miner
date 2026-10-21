"""Move #361's existing DP insertion pipeline into D, preserving record parent.

One fixed structural candidate, without linkearly or any key/depth/table change.
Run the finite old-head/table/schedule model before producing the package.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r10-record-nonempty"
NAME = "r10-finder-pipeline"
PINNED = {"parse.rs": "7f1c661fd1ce29d12c69671f034ff5a713e284ed1fcba66ba404ff25479b55b7",
          "Parse.lean": "86cfc36adb009970bccbb5a9c543c5f559148d729e8c0f041934aab44e95592d"}


def sha(raw: bytes) -> str:
    return hashlib.sha256(raw).hexdigest()


def once(s: str, before: str, after: str) -> str:
    if s.count(before) != 1:
        raise ValueError(f"Expected one exact D anchor: {before[:100]!r}")
    return s.replace(before, after, 1)


def model_check() -> dict:
    """Finite cache/table oracle, with independent fixed legal iteration schedules.

    The baseline reads fresh heads then inserts. The pipeline stores cached heads,
    pre-reads i+1, and must refresh after a range-inserting jump. This checks only
    the scheduler/cache mechanism, not native parser/record/encoder performance.
    """
    def word(data: bytes, q: int) -> int:
        return int.from_bytes(data[q:q+8], "big") if q + 8 <= len(data) else 0
    def hashes(b8: int) -> tuple[int, int, int]:
        x4 = b8 >> 32
        return (((x4 >> 8) * 2654435761 & 0xFFFFFFFF) >> 18,
            ((x4 * 2654435761 & 0xFFFFFFFF) >> 16),
            (((b8 >> 8) * 0x9E3779B97F4A7C15 & ((1 << 64) - 1)) >> 48))
    def fresh(heads: list[list[int]], hh: tuple[int, int, int]) -> tuple[int, int, int]:
        return tuple(heads[j][hh[j]] for j in range(3))
    def store(heads, prev, q, hh, old):
        for j in range(3): heads[j][hh[j]] = q
        prev[0][q % 32768] = old[1]; prev[1][q % 32768] = old[2]
    total_visits = 0; inserted = 0; jumps = 0; crossed_windows = 0; stale_differences = 0
    checks = []
    for size in (16,17,32,258,259,260,4097,32767,32768,32769,65536,65537):
        for mode in range(4):
            rng = random.Random(3613300 + size * 11 + mode)
            pattern = b"abcabcabc common repeated prefix; value=0123456789\n"
            data = bytes(rng.randrange(256) for _ in range(size)) if mode == 0 else (
                bytes([97])*size if mode == 1 else (pattern*(size//len(pattern)+1))[:size])
            old_heads = [[0]*16384,[0]*65536,[0]*65536]
            new_heads = [[0]*16384,[0]*65536,[0]*65536]
            old_prev = [[0]*32768,[0]*32768]; new_prev = [[0]*32768,[0]*32768]
            lim = size - 8; i = 0; b8 = word(data,0); hh = hashes(b8); pre = fresh(new_heads,hh)
            visited = 0; local_inserted = 0; local_jumps = 0
            while i < lim:
                original_b8 = word(data,i); original_hh = hashes(original_b8); original_hc = fresh(old_heads,original_hh)
                assert (b8,hh,pre) == (original_b8,original_hh,original_hc)
                store(old_heads,old_prev,i,original_hh,original_hc)
                store(new_heads,new_prev,i,hh,pre)
                assert old_prev[0][i%32768] == new_prev[0][i%32768]
                assert old_prev[1][i%32768] == new_prev[1][i%32768]
                b8n = word(data,i+1); hn = hashes(b8n); pn1 = fresh(new_heads,hn)
                # Fixed schedules include only-literal, alternating continuation,
                # frequent long matches, and mixed small/long jumps up to258.
                if mode == 0 or (mode == 2 and visited % 3 != 0): length = 1
                elif mode == 1: length = min(258,size-i)
                else: length = min(rng.choice((1,1,3,9,16,33,257,258)),size-i)
                local_inserted += 1
                if length > 1:
                    end = min(i+length,lim)
                    for q in range(i+1,end):
                        ob = word(data,q); oh = hashes(ob); oc = fresh(old_heads,oh); store(old_heads,old_prev,q,oh,oc)
                        nb = word(data,q); nh = hashes(nb); nc = fresh(new_heads,nh); store(new_heads,new_prev,q,nh,nc)
                        assert (ob,oh,oc) == (nb,nh,nc)
                        local_inserted += 1
                    next_i = i + length
                    if i//32768 != next_i//32768: crossed_windows += 1
                    i = next_i
                    b8 = word(data,i); hh = hashes(b8); pre = fresh(new_heads,hh)
                    if i < lim and pre != pn1: stale_differences += 1
                    local_jumps += 1
                else:
                    i += 1; b8,hh,pre = b8n,hn,pn1
                visited += 1
            assert old_heads == new_heads and old_prev == new_prev
            total_visits += visited; inserted += local_inserted; jumps += local_jumps
            checks.append({"size":size,"mode":mode,"main_visits":visited,"inserted_positions":local_inserted,"long_jumps":local_jumps})
    return {"status":"VERIFIED_FINITE_PYTHON_INSERT_PIPELINE_MODEL_ONLY", "cases":len(checks),
        "main_visits":total_visits,"inserted_positions":inserted,"long_jumps":jumps,
        "window_crossing_jumps":crossed_windows,"fresh_jump_heads_differing_from_unused_pn1":stale_differences,
        "scope":"Exact bytes/hash/old heads at every visited main and range position, exact predecessor writes and final arrays against fresh synchronous insertion under fixed legal schedules",
        "not_verified":"Native Rust444 token/record/decode equality, actual extraction/proof, encoder bytes or paired time",
        "generator_sha256":sha(Path(__file__).read_bytes()),"checks":checks}


def generate() -> dict[str,bytes]:
    raw = {file:(BASE/file).read_bytes() for file in PINNED}
    if {file:sha(value) for file,value in raw.items()} != PINNED:
        raise ValueError("Frozen record parent changed")
    source = raw["parse.rs"].decode("utf-8")
    start = source.index("/// `dp_parse` with node recording (see the section comment);")
    end = source.index("/// Engine D with knobs k",start)
    original = source[start:end]; region = original; edits = []
    before = "    let mut alen = 0usize;\n    while i < lim {"
    after = """    let mut alen = 0usize;
    // Existing #361 DP insertion pipeline: current bytes/hash/old heads.
    let mut b8 = be8(input, 0);
    let mut hh = hashes(b8, sh7);
    let mut pre = dp_heads(&head3, &head4, &head7, hh.0, hh.1, hh.2);
    while i < lim {"""
    edits.append((before,after)); region = once(region,before,after)
    before = """        let b8 = be8(input, i);
        let hc = insert_pos(&mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i, b8, sh7);"""
    after = """        let hc = pre;
        dp_store(&mut head3, &mut head4, &mut prev4, &mut head7, &mut prev7, i, hh.0, hh.1, hh.2, hc.1, hc.2);
        // Read i+1 only after i's stores; same-hash next positions see i.
        let b8n = be8(input, i.wrapping_add(1));
        let hn = hashes(b8n, sh7);
        let pn1 = dp_heads(&head3, &head4, &head7, hn.0, hn.1, hn.2);"""
    edits.append((before,after)); region = once(region,before,after)
    before = "        let dnode = if lazy_here { d7l } else if cl >= 1 { d7e } else { d7 };"
    after = before + "\n        let mut jumped = false;"
    edits.append((before,after)); region = once(region,before,after)
    before = "                open_chunk(&mut pa, s);\n            } else {"
    after = "                open_chunk(&mut pa, s);\n                jumped = true;\n            } else {"
    edits.append((before,after)); region = once(region,before,after)
    before = "        if i - s >= CHUNK {"
    after = """        // Range insertion invalidates the speculative next heads after a jump.
        if jumped {
            b8 = be8(input, i);
            hh = hashes(b8, sh7);
            pre = dp_heads(&head3, &head4, &head7, hh.0, hh.1, hh.2);
        } else {
            b8 = b8n;
            hh = hn;
            pre = pn1;
        }
""" + before
    edits.append((before,after)); region = once(region,before,after)
    restored = region
    for before,after in reversed(edits): restored = once(restored,after,before)
    if restored != original: raise ValueError("Exact D pipeline reversal failed")
    rust = (source[:start]+region+source[end:]).encode("utf-8")
    files = {"parse.rs":rust,"Parse.lean":raw["Parse.lean"]}
    parent = json.loads((BASE/"manifest.json").read_text(encoding="utf-8"))
    manifest = {
        "candidate":NAME,"parent":"candidates/r10-record-nonempty","base_submission_id":"361",
        "parent_hashes":PINNED,"hashes":{file:sha(value) for file,value in files.items()},
        "bytes":{file:len(value) for file,value in files.items()},"attribution":parent["attribution"],
        "mechanism":"Port #361 dp_parse's existing software-pipelined insertion to D: carry current b8/hash/pre-heads, store i using cached heads, immediately read i+1, refresh after taken-match range insertion",
        "mechanism_source":"record parent's dp_parse lines1495..1509 and1600..1609; existing hashes/dp_heads/dp_store and their contracts reused unchanged",
        "old_trial_review":"No D insertion-pipeline candidate in narrow R7/R9 script/manifest/design searches; original DP already used it, so mechanism is attributed reuse rather than invention",
        "expected_equivalent_to":"r10-record-nonempty",
        "equivalence_status":"INFERRED: speculative next heads are read after current stores, ordinary/continuation branches do not mutate heads, longjump range insertion forces fresh new-i heads. Finite cache model passed, native444 and public rs/tokens/bytes checks pending",
        "source_audit":"Reverse five exact D-region substitutions restores verified record Rust; existing shared helpers, D matching/record/relax/backward/emit functions and all routes/knobs retain exact parent bytes. Does not combine linkearly.",
        "proof_status":"UNADAPTED_PARENT_DRAFT / NOT_RUN: D loop carries extra pipeline values and branch jump flag; port actual extracted interfaces using existing DP store/heads contracts. Original obligation/allowed axioms/public round trip still required",
        "proof_cost":"Three conceptual states b8/hh/pre; existing DP extraction flattens hh into x3/x4/x7, so anticipate five extra function-state components. Add cached-head<=i bounds; no cached-word truth needed for planner totality, but equality needed for same-output claim.",
        "cost_scope":"Mostly same insertion/hash/head-read work redistributed across iterations; speculative i+1 is unused on long jumps and final exit, adding bounded prepare work. Cache/value live ranges can add spills. No assumed speedup.",
        "performance_status":"UNKNOWN paired total compression/current codegen; original DP use does not prove useful scheduling in D's larger loop",
        "stop":"Reject unexplained cache/record/token/output mismatch; stop if speculative work/register pressure loses time or actual release code has no useful head-load overlap. One fixed transfer, no new pipeline parameter sweep."}
    if not all(0<len(value)<=524288 for value in files.values()): raise ValueError("Per-file size boundary exceeded")
    files["manifest.json"]=(json.dumps(manifest,indent=2,ensure_ascii=False)+"\n").encode("utf-8")
    audit={"status":"VERIFIED_LOCAL_REVERSIBLE_D_SOURCE_PORT_ONLY","parent_hashes":PINNED,"candidate_hashes":manifest["hashes"],
        "old_D_region_sha256":sha(original.encode()),"new_D_region_sha256":sha(region.encode()),
        "exact_reversed_substitutions":len(edits),"outside_D_source_identical":True,"parent_Lean_bytes_identical":True,
        "new_helpers":[],"shared_reused_helpers":["hashes","dp_store","dp_heads"],"native_or_full_gate": "NOT_RUN"}
    files["source-audit.json"]=(json.dumps(audit,indent=2)+"\n").encode("utf-8")
    return files


def main() -> None:
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument("--check",action="store_true");parser.add_argument("--model-only",action="store_true");args=parser.parse_args()
    target=ROOT/"candidates"/NAME;target.mkdir(exist_ok=True)
    if args.model_only:
        receipt=model_check();(target/"pipeline-model-check.json").write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
        print(json.dumps({k:v for k,v in receipt.items() if k!="checks"}));return
    files=generate()
    if args.check:
        if not all((target/file).read_bytes()==value for file,value in files.items()): raise ValueError("Pipeline candidate reconstruction differs")
    else:
        model=json.loads((target/"pipeline-model-check.json").read_text(encoding="utf-8"))
        if model["status"]!="VERIFIED_FINITE_PYTHON_INSERT_PIPELINE_MODEL_ONLY" or model["generator_sha256"]!=sha(Path(__file__).read_bytes()): raise ValueError("Run exact generator's model first")
        for file,value in files.items():
            path=target/file
            if path.exists() and path.read_bytes()!=value: raise ValueError(f"Preserve differing pipeline candidate {path}")
            path.write_bytes(value)
    print(json.dumps({"candidate":NAME,"hashes":json.loads(files["manifest.json"])["hashes"],"proof_status":"UNADAPTED_PARENT_DRAFT"}))


if __name__=="__main__":main()
