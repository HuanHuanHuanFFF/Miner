"""Prepare a local sparse-emitter proof draft against the real M extraction."""
from pathlib import Path
import hashlib
import importlib.util
import json
import re

ROOT = Path(__file__).resolve().parents[1]
RUST_PARENT = ROOT / "candidates/r25-astra-tiny-pc-sparse"
LEAN_PARENT = ROOT / "candidates/r25-astra-tiny-pc8-proof1"
NAME = "r25-astra-tiny-pc-sparse-proof1"
RUST_SHA = "84ccbcbe88c56d8459c6df0d8bad5391b0ce95209d4e2f5fb4148369c9c294e5"
LEAN_SHA = "3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8"
OLD = ROOT / "evidence/round25/38130286911/proof-i-extract/diagnostics/research5/r25-root-tiny-pc8"
NEW = ROOT / "evidence/round25/38132862529/proof-m-extract/diagnostics/research5/r25-astra-tiny-pc-sparse"
EVIDENCE = ROOT / "evidence/round25/astra"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def once(text, old, new):
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new)


BRIDGE = """
-- R25_SPARSE_EMITTER_BRIDGE_BEGIN
@[local step]
theorem tiny_sparse_pieces_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (nt p l d : Std.Usize) (lens : Array Std.U16 260#usize)
    (hl : Q4.LensBound lens) (hdec : Dec input out nt.val p.val)
    (hm : MatchAt input p.val l.val d.val) :
    slot.q4_e_pieces input out nt p l d lens ⦃ fun r =>
      r.1.2.val = p.val + l.val ∧ r.2.length = out.length ∧
      Dec input r.2 r.1.1.val r.1.2.val ⦄ := by
  rcases hm with ⟨hl3, hl258, hpl, hd1, hd32, hdp, hmatch⟩
  have hdecq : Q4.Dec input out nt.val p.val := by
    simpa only [Dec, Q4.Dec] using hdec
  apply Std.WP.spec_mono
    (Q4.e_pieces_spec input out nt p l d lens hl hdecq hpl hd1 hd32 hdp hmatch)
  rintro ⟨⟨nt', e'⟩, out'⟩ ⟨hdec', he, hout⟩
  refine ⟨he, hout, ?_⟩
  simpa only [Dec, Q4.Dec] using hdec'
-- R25_SPARSE_EMITTER_BRIDGE_END

"""


def adapted_lean(raw):
    text = raw.decode()
    start = text.index("set_option maxHeartbeats 16000000 in\ntheorem tiny_main1_loop_spec")
    end = text.index("-- R25_TINY_PC8_PROOF_END", start)
    old_block = text[start:end]
    block = old_block
    # Real M extraction puts the immutable lens immediately after km; tuple state is unchanged.
    a = block.index("theorem tiny_run1_spec")
    main, run = block[:a], block[a:]
    for old in (
        "(skip lazy skcap : Std.Usize) (km : Std.U32) (nt ls p : Std.Usize)",
    ):
        assert main.count(old) == 2
        main = main.replace(old, "(skip lazy skcap : Std.Usize) (km : Std.U32)\n    (lens : Array Std.U16 260#usize) (nt ls p : Std.Usize)")
    hyp = "(hlim : lim.val + 8 = input.length) (hskip : skip.val < 32) (hH : 0 < H.val)"
    assert main.count(hyp) == 2
    main = main.replace(hyp, hyp + "\n    (hl : Q4.LensBound lens)")
    assert main.count("input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w") == 3
    main = main.replace("input out skip lazy skcap km nt ls p head lim miss fuel pre_slot pre_c pre_w",
                        "input out skip lazy skcap km lens nt ls p head lim miss fuel pre_slot pre_c pre_w")
    main = once(main, "out.length hlim hskip hH ⟨hdec, rfl, hlsp, hB, hmiss, hps, hpc, hpw⟩",
                      "out.length hlim hskip hH hl ⟨hdec, rfl, hlsp, hB, hmiss, hps, hpc, hpw⟩")
    run = once(run, " := C125102! slot.r25_tiny_pc_run1", """ := by
  rw [slot.r25_tiny_pc_run1]
  have hmax : input.length ≤ Std.Usize.max := Std.Slice.length_ineq input
  have hB0 : HeadBound (Std.Array.repeat H 0#u32) 0 := HeadBound.init H
  have hL0 : Q4.LensBound (Std.Array.repeat 260#usize 0#u16) := Q4.LensBound.init
  have hdec0 : Dec input out (0#usize).val (0#usize).val := Dec.init input out hlen
  step*""")
    block = BRIDGE + main + "attribute [local step] Q4.e_lens_spec\n\n" + run
    assert not re.search(r"\b(sorry|admit|axiom)\b", block)
    changed = text[:start] + block + text[end:]
    assert changed[:start] == text[:start] and changed.endswith(text[end:])
    assert changed[changed.index("theorem bulk_parse_spec"):] == text[text.index("theorem bulk_parse_spec"):]
    assert re.findall(r"set_option [^\n]+", changed) == re.findall(r"set_option [^\n]+", text)
    return changed.encode(), {"changed_existing_lemmas": ["PC.tiny_main1_loop_spec", "PC.tiny_main1_loop_spec'", "PC.tiny_run1_spec"],
                             "new_lemmas": ["PC.tiny_sparse_pieces_spec"],
                             "loop_constant_parameter_order": "input out skip lazy skcap km lens nt ls p head lim miss fuel pre_slot pre_c pre_w",
                             "main_loop_state_unchanged": True, "main_invariant_and_fuel_measure_unchanged": True,
                             "final_bulk_parse_and_parse_tail_unchanged": True, "all_set_option_directives_unchanged": True,
                             "no_nt_plus_one_postcondition_assumed_for_sparse_emitter": True}


def main():
    utility = ROOT / "scripts/build-round25-astra-tiny-proof.py"
    spec = importlib.util.spec_from_file_location("r25_tiny_proof_audit", utility)
    helper = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(helper)
    old, new = helper.definitions(OLD / "Funs.lean"), helper.definitions(NEW / "Funs.lean")
    assert set(old) == set(new)
    changed_defs = sorted(k for k in old if old[k] != new[k])
    assert changed_defs == ["r25_tiny_pc_run1", "r25_tiny_pc_run1_loop0", "r25_tiny_pc_run1_loop0.body"], changed_defs
    assert "(km : Std.U32) (lens : Array Std.U16 260#usize) (nt : Std.Usize)" in new["r25_tiny_pc_run1_loop0"]
    assert "(km : Std.U32) (lens : Array Std.U16 260#usize) (lim : Std.Usize)" in new["r25_tiny_pc_run1_loop0.body"]
    assert "q4_e_pieces input out1 i1 i2 i3 d1 lens" in new["r25_tiny_pc_run1_loop0.body"]
    assert "q4_e_lens lens 302256384#u32" in new["r25_tiny_pc_run1"]
    assert old["r25_tiny_pc_run1_loop0_loop0"] == new["r25_tiny_pc_run1_loop0_loop0"]
    rust, parent_lean = (RUST_PARENT / "parse.rs").read_bytes(), (LEAN_PARENT / "Parse.lean").read_bytes()
    assert sha(rust) == RUST_SHA and sha(parent_lean) == LEAN_SHA
    lean, proof_changes = adapted_lean(parent_lean)
    assert len(rust) <= 524288 and len(lean) <= 524288
    path = ROOT / "candidates" / NAME
    assert not path.exists(), "Do not overwrite a frozen draft"
    path.mkdir()
    (path / "parse.rs").write_bytes(rust)
    (path / "Parse.lean").write_bytes(lean)
    hashes = {"parse.rs": sha(rust), "Parse.lean": sha(lean)}
    manifest = json.loads((RUST_PARENT / "manifest.json").read_bytes())
    manifest.update(candidate=NAME, parent=RUST_PARENT.name, hashes=hashes,
        proof_status="ACTUAL_M_EXTRACTION_ADAPTED_DRAFT_UNCOMPILED",
        proof_change="Add PC-local full-end/Dec wrapper around the already proved Q4 sparse emitter; main loop carries immutable bounded lens after km; run initializes LensBound. All old record/lazy/tail definitions and proofs remain unchanged. Original options and final obligation tail retained.",
        proof_evidence="evidence/round25/astra/tiny-sparse-proof-build-audit.json",
        proof_parent=LEAN_PARENT.name, proof_parent_gate="38130996700",
        native_encoder_status="SAME_RUST_VERIFIED_RUN_38132623194", performance_status="PENDING_ROOT_SCREEN_M")
    (path / "manifest.json").write_bytes((json.dumps(manifest, indent=2) + "\n").encode())
    entry = {"name": NAME, "path": path.relative_to(ROOT).as_posix(), "control": False, "hashes": hashes,
             "anchor": "public595", "comparison_baseline": "combo", "native_decode_reference": "combo"}
    (EVIDENCE / "tiny-sparse-proof-entry.json").write_bytes((json.dumps(entry, indent=2) + "\n").encode())
    audit = {"status": "VERIFIED_ACTUAL_INTERFACES_AND_TEXT_SCOPE_NOT_LEAN_BUILD", "candidate": NAME,
             "hashes": hashes, "bytes": {"parse.rs": len(rust), "Parse.lean": len(lean)},
             "rust_byte_identical_to": RUST_PARENT.relative_to(ROOT).as_posix(),
             "parent_lean_sha256": LEAN_SHA, "definitions_old": len(old), "definitions_new": len(new),
             "changed_definitions": changed_defs, "added_or_removed_definitions": [], "proof_changes": proof_changes,
             "real_extraction": NEW.relative_to(ROOT).as_posix(),
             "real_extraction_hashes": {f: sha((NEW / f).read_bytes()) for f in ["Funs.lean", "Types.lean", "Constants.lean"]},
             "unchanged_real_definitions_count": len(old) - len(changed_defs), "lean_compile": "NOT_RUN",
             "axiom_scan": "PENDING_ORIGINAL_GATE", "full_gate": "NOT_RUN"}
    (EVIDENCE / "tiny-sparse-proof-build-audit.json").write_bytes((json.dumps(audit, indent=2) + "\n").encode())
    print(json.dumps(audit, indent=2))


if __name__ == "__main__":
    main()
