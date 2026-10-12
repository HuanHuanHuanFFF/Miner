"""One fixed emitter isolation: frozen tiny-PC matcher with inherited ETINY lengths."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / "candidates/r25-root-tiny-pc8"
PROOF_PARENT = ROOT / "candidates/r25-astra-tiny-pc8-proof1"
NAME = "r25-astra-tiny-pc-sparse"
RUST_SHA = "5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00"
LEAN_SHA = "3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8"
MASK = 302256384
EVIDENCE = ROOT / "evidence/round25/astra"
K_RECEIPT = ROOT / "evidence/round25/38132193695/counts-k2-native/diagnostics/r25-tiny-encoder/receipt.json"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def function_span(text, name):
    start = text.index("pub fn " + name + "<")
    opening = text.index("{", start)
    end, depth = opening + 1, 1
    while depth:
        depth += (text[end] == "{") - (text[end] == "}")
        end += 1
    return start, end


def build_bytes():
    raw = (PARENT / "parse.rs").read_bytes()
    lean = (PROOF_PARENT / "Parse.lean").read_bytes()
    assert sha(raw) == RUST_SHA and sha(lean) == LEAN_SHA
    verified = json.loads((PROOF_PARENT / "VERIFICATION.json").read_bytes())
    assert verified["status"] == "VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED"
    assert verified["files"] == {"parse.rs": RUST_SHA, "Parse.lean": LEAN_SHA}
    text = raw.decode()
    a, b = function_span(text, "r25_tiny_pc_run1")
    original = text[a:b]
    init = "    let n = input.len();"
    sparse_init = init + "\n    let mut lens = [0u16; 260];\n    q4_e_lens(&mut lens, 302256384);"
    emit = "                let r = pc_put_match(input, out, b.0, b.1, d, b.2);"
    sparse_emit = "                let r = q4_e_pieces(input, out, b.0, b.1, b.2, d, &lens);"
    assert original.count(init) == original.count(emit) == 1
    changed = original.replace(init, sparse_init).replace(emit, sparse_emit)
    assert changed.replace(sparse_init, init).replace(sparse_emit, emit) == original
    result = (text[:a] + changed + text[b:]).encode()
    assert len(result) <= 524288 and len(lean) <= 524288
    assert result != raw and result[:a] == raw[:a]
    assert text[:a] + changed.replace(sparse_init, init).replace(sparse_emit, emit) + text[b:] == text
    return result, lean, {"changed_function": "r25_tiny_pc_run1", "initialized_lens_entries": 260,
                          "fixed_mask": MASK, "code_indices": [i for i in range(29) if MASK & (1 << i)],
                          "reversible_exact_parent_patch": True, "outside_function_byte_identical": True,
                          "new_functions": 0, "new_branches_in_main_loop": 0,
                          "proof_parent_gate_run": verified["run_id"]}


def main():
    rust, lean, change = build_bytes()
    k = json.loads(K_RECEIPT.read_bytes())
    assert k["status"] == "VERIFIED_UNTIMED_ORIGINAL_OBSERVER_BYTES_DECODE_AND_PRIOR_IDENTITY"
    hashes = {"parse.rs": sha(rust), "Parse.lean": sha(lean)}
    path = ROOT / "candidates" / NAME
    assert not path.exists(), "Do not overwrite a frozen candidate"
    path.mkdir()
    (path / "parse.rs").write_bytes(rust)
    (path / "Parse.lean").write_bytes(lean)
    manifest = json.loads((PARENT / "manifest.json").read_bytes())
    manifest.update(candidate=NAME, parent=PARENT.name, hashes=hashes,
        mechanism="Keep the exact tiny-PC matcher, lazy search, fold, record8, route, H and skip. Only initialize the inherited ETINY mask302256384 lens table and replace the local match emission with inherited q4_e_pieces, which emits allowed lengths plus literal remainder and consumes the complete valid match span.",
        difference_from_old_work="A single fixed emission isolation after native K2 identified broader length/distance symbols and greater package-merge and lookup work. No mask search, insertion/search/H tuning, new distance admission, encoder modification or combination.",
        reference_differences="Starts from exact I Rust5c20b99c, with no matcher source replacement. Sparse emitter and mask are already present in the inherited public595/combo source.",
        proof_status="DRAFT_COPIED_GATE_PASSED_PROOF1_NOT_ADAPTED_TO_SPARSE_EMITTER",
        proof_parent=PROOF_PARENT.name, proof_parent_gate="38130996700",
        performance_status="NOT_RUN", native_encoder_status="NOT_RUN",
        causal_cost_claim="UNKNOWN: K2 logical work counts are not elapsed-time attribution; new original-encoder bytes and separate original-protocol timings are required.",
        risks=["Short matches below the minimum allowed length become literals.",
               "Greedy allowed pieces can increase tokens and literal remainder.",
               "Existing fold reads a changed historical token stream, though its full-span end invariant is retained.",
               "Distance symbols are not directly restricted; reducing the LL alphabet may not recover the full encoder cost."],
        experiment_predeclaration="evidence/round25/astra/tiny-sparse-design.md",
        diagnostic_evidence=K_RECEIPT.relative_to(ROOT).as_posix(), formal_submission_sent=False)
    (path / "manifest.json").write_bytes((json.dumps(manifest, indent=2) + "\n").encode())
    entry = {"name": NAME, "path": path.relative_to(ROOT).as_posix(), "control": False,
             "hashes": hashes, "anchor": "public595", "comparison_baseline": "combo",
             "native_decode_reference": "combo"}
    (EVIDENCE / "tiny-sparse-entry.json").write_bytes((json.dumps(entry, indent=2) + "\n").encode())
    audit = {"status": "VERIFIED_FROZEN_SOURCE_AND_REVERSIBLE_PATCH_NOT_NATIVE",
             "candidate": NAME, "parent_rust_sha256": RUST_SHA, "hashes": hashes,
             "bytes": {"parse.rs": len(rust), "Parse.lean": len(lean)}, "change": change,
             "k2_receipt_sha256": sha(K_RECEIPT.read_bytes()),
             "lean_byte_identical_to_gate_passed_proof1": True,
             "rust_compile": "NOT_RUN", "native_encoder": "NOT_RUN", "fresh_extraction": "NOT_RUN", "gate": "NOT_RUN"}
    (EVIDENCE / "tiny-sparse-preflight.json").write_bytes((json.dumps(audit, indent=2) + "\n").encode())
    print(json.dumps(audit, indent=2))


if __name__ == "__main__":
    main()
