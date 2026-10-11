"""Adapt only tiny-PC cloned helpers after checking the real extracted interfaces."""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / "candidates/r22-595-chain-halfhead"
RUST_SOURCE = ROOT / "candidates/r25-root-tiny-pc8"
NAME = "r25-astra-tiny-pc8-proof1"
OUT = ROOT / "evidence/round25/astra"
RUST_HASH = "5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00"
LEAN_HASH = "4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6"
BASE_EXTRACT = ROOT / "evidence/round23/38072972025/gate-combo/exact-gate/exact-gate/extracted/Funs.lean"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def definitions(path):
    text = path.read_text()
    text = re.sub(r"/\-.*?\-/", "", text, flags=re.S)
    text = re.sub(r"--[^\n]*", "", text)
    text = re.sub(r"(?m)^end slot\s*$", "", text)
    marks = list(re.finditer(r"(?m)^(?:@\[[^\]]*\]\s*)?def\s+([A-Za-z0-9_.]+)\b", text))
    return {m.group(1): re.sub(r"\s+", " ", text[m.start():marks[i + 1].start() if i + 1 < len(marks) else len(text)]).strip()
            for i, m in enumerate(marks)}


def theorem(lean, name, following):
    a = lean.index("theorem " + name)
    b = lean.index(following, a)
    return lean[a:b].rstrip()


def proof_block(lean):
    # Only the three wrappers below need new bodies. The unchanged loops reuse actual parent proofs.
    record0 = theorem(lean, "record3_m_loop0_spec", "@[local step]")
    record0 = record0[:record0.index(" := C12590!")] + " := by\n" + """  simpa only [slot.r25_tiny_pc_record8_loop0, slot.r25_tiny_pc_record8_loop0.body,
    slot.pc_record3_m_loop0, slot.pc_record3_m_loop0.body] using
    (record3_m_loop0_spec s head km ins stop B hB hsB hs4 hH)"""
    record0 = record0.replace("theorem record3_m_loop0_spec", "theorem tiny_record8_loop0_spec", 1)
    # Change only the statement; the using-clause must still refer to the parent's theorem.
    pos = record0.index(" := by")
    record0 = record0[:pos].replace("slot.pc_record3_m", "slot.r25_tiny_pc_record8") + record0[pos:]
    record1 = theorem(lean, "record3_m_loop1_spec", "@[local step]")
    record1 = record1[:record1.index(" := C12591!")] + " := by\n" + """  simpa only [slot.r25_tiny_pc_record8_loop1, slot.r25_tiny_pc_record8_loop1.body,
    slot.pc_record3_m_loop1, slot.pc_record3_m_loop1.body] using
    (record3_m_loop1_spec s head «end» lim km ins B hB heB hl4 hH)"""
    record1 = record1.replace("theorem record3_m_loop1_spec", "theorem tiny_record8_loop1_spec", 1)
    pos = record1.index(" := by")
    record1 = record1[:pos].replace("slot.pc_record3_m", "slot.r25_tiny_pc_record8") + record1[pos:]
    record = theorem(lean, "record3_m_spec", "def LazyInv1")
    record = record.replace("theorem record3_m_spec", "theorem tiny_record8_spec", 1).replace("slot.pc_record3_m", "slot.r25_tiny_pc_record8")

    lazy = theorem(lean, "lazy1_loop_spec", "@[local step]")
    lazy = lazy[:lazy.index(" := C12598!")] + " := by\n" + """  simpa only [slot.r25_tiny_pc_run1_loop0_loop0, slot.r25_tiny_pc_run1_loop0_loop0.body,
    slot.pc_run1_loop0_loop0, slot.pc_run1_loop0_loop0.body] using
    (lazy1_loop_spec input lazy km p head lim pre_slot pre_c pre_w l d ins go
      hlim hH hm hB hplim hins hps hpc hpw)"""
    lazy = lazy.replace("theorem lazy1_loop_spec", "theorem tiny_lazy1_loop_spec", 1)
    pos = lazy.index(" := by")
    lazy = lazy[:pos].replace("slot.pc_run1", "slot.r25_tiny_pc_run1") + lazy[pos:]
    tails = []
    for number, following in ((1, "@[local step]"), (2, "def MainInv1")):
        name = f"tail1_loop{number}_spec"
        tail = theorem(lean, name, following)
        tail = tail[:tail.index(" := C12599!")] + " := by\n" + f"""  simpa only [slot.r25_tiny_pc_run1_loop{number}, slot.r25_tiny_pc_run1_loop{number}.body,
    slot.pc_run1_loop{number}, slot.pc_run1_loop{number}.body] using
    (tail1_loop{number}_spec input out n nt p hn hdec)"""
        tail = tail.replace("theorem " + name, "theorem tiny_" + name, 1)
        pos = tail.index(" := by")
        tails.append(tail[:pos].replace("slot.pc_run1", "slot.r25_tiny_pc_run1") + tail[pos:])
    main = theorem(lean, "main1_loop_spec ", "@[local step]")
    main = main.replace("theorem main1_loop_spec", "theorem tiny_main1_loop_spec", 1).replace("slot.pc_run1", "slot.r25_tiny_pc_run1")
    main_step = theorem(lean, "main1_loop_spec'", "theorem run1_spec")
    main_step = main_step.replace("main1_loop_spec", "tiny_main1_loop_spec").replace("slot.pc_run1", "slot.r25_tiny_pc_run1")
    run = theorem(lean, "run1_spec", "@[local step]")
    run = run.replace("theorem run1_spec", "theorem tiny_run1_spec", 1).replace("slot.pc_run1", "slot.r25_tiny_pc_run1")
    # This function is called on the isolated PC namespace, so duplicate theorem names in Q4 cannot match.
    parts = [record0, record1, record, lazy, *tails,
             "set_option maxHeartbeats 16000000 in\n" + main, main_step, run]
    return "\n-- R25_TINY_PC8_PROOF_BEGIN\n" + "\n\n".join("@[local step]\n" + p if i != 6 and i != 8 else p for i, p in enumerate(parts)) + "\n-- R25_TINY_PC8_PROOF_END\n"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--extracted-dir", required=True)
    args = parser.parse_args()
    extracted = Path(args.extracted_dir)
    if not extracted.is_absolute():
        extracted = ROOT / extracted
    funs = extracted / "Funs.lean"
    assert funs.is_file(), "Real extraction required before generating proof1"
    raw = (RUST_SOURCE / "parse.rs").read_bytes()
    original_lean = (PARENT / "Parse.lean").read_bytes()
    assert sha(raw) == RUST_HASH and sha(original_lean) == LEAN_HASH
    old, new = definitions(BASE_EXTRACT), definitions(funs)
    changed = sorted(k for k in old.keys() & new.keys() if old[k] != new[k])
    added = sorted(new.keys() - old.keys())
    removed = sorted(old.keys() - new.keys())
    assert changed == ["p125_row12"] and not removed, (changed, removed)
    assert len(added) == 14 and all(k.startswith("r25_tiny_pc_") for k in added), added
    mapping = {"r25_tiny_pc_record8": "pc_record3_m", "r25_tiny_pc_run1": "pc_run1"}
    cloned_equal = []
    for name in added:
        if name == "r25_tiny_pc_record8":
            continue  # The intended fixed 8 bound differs from pc_INS_MAX = 2.
        expected_name, body = name, new[name]
        for current, parent in mapping.items():
            expected_name = expected_name.replace(current, parent)
            body = body.replace(current, parent)
        assert body == old[expected_name], name
        cloned_equal.append(name)
    lean = original_lean.decode()
    pc_start = lean.index("namespace PC\n")
    pc_end = lean.index("\nend PC\n", pc_start)
    pc = lean[pc_start:pc_end]
    block = proof_block(pc)
    assert not re.search(r"\b(sorry|admit|axiom)\b", block)
    assert block.count("\ntheorem ") == 9
    lean = lean[:pc_end] + block + lean[pc_end:]
    a = lean.index("theorem p125_row12_spec")
    b = lean.index("@[local step]", a)
    row = lean[a:b]
    old_call = " exact ETINY.tiny_spec input out _ hlen"
    assert row.count(old_call) == 1
    row = row.replace(old_call, " exact PC.tiny_run1_spec _ input out _ _ _ _ hlen (by simp) (by simp)")
    lean = lean[:a] + row + lean[b:]
    assert lean[lean.index("theorem bulk_parse_spec"):] == original_lean.decode()[original_lean.decode().index("theorem bulk_parse_spec"):]
    path = ROOT / "candidates" / NAME
    assert not path.exists(), path
    path.mkdir()
    (path / "parse.rs").write_bytes(raw)
    (path / "Parse.lean").write_bytes(lean.encode())
    hashes = {f: sha((path / f).read_bytes()) for f in ("parse.rs", "Parse.lean")}
    assert hashes["parse.rs"] == RUST_HASH and len(lean.encode()) <= 524288
    manifest = json.loads((RUST_SOURCE / "manifest.json").read_bytes())
    manifest.update(candidate=NAME, parent=RUST_SOURCE.name, hashes=hashes,
                    proof_status="ACTUAL_EXTRACTION_ADAPTED_DRAFT_UNCOMPILED",
                    proof_change="Nine local PC correctness lemmas for cloned record/main helpers; row12 uses new run1_spec. Unchanged loop bodies reuse parent proofs by explicit definitional unfolding. Original final parse obligation and all existing proofs retained.",
                    proof_evidence="evidence/round25/astra/tiny-proof-build-audit.json")
    (path / "manifest.json").write_bytes((json.dumps(manifest, indent=2) + "\n").encode())
    audit = {"status": "VERIFIED_TEXT_INTERFACE_AND_HASH_AUDIT_NOT_LEAN_BUILD", "candidate": NAME,
             "hashes": hashes, "rust_byte_identical_to": RUST_SOURCE.relative_to(ROOT).as_posix(),
             "actual_extraction": extracted.relative_to(ROOT).as_posix(),
             "extraction_files": {f: {"bytes": (extracted / f).stat().st_size, "sha256": sha((extracted / f).read_bytes())}
                                  for f in ("Funs.lean", "Types.lean", "Constants.lean")},
             "changed_shared_definitions": changed, "new_definitions": added,
             "cloned_definitions_equal_after_name_mapping": cloned_equal,
             "new_lemmas": 9, "final_bulk_parse_and_parse_tail_unchanged": True,
             "lean_bytes": len(lean.encode()), "gate": "NOT_RUN", "local_lean": "NOT_RUN"}
    (OUT / "tiny-proof-build-audit.json").write_bytes((json.dumps(audit, indent=2) + "\n").encode())
    entry = {"name": NAME, "path": path.relative_to(ROOT).as_posix(), "control": False,
             "hashes": hashes, "anchor": "public595", "comparison_baseline": "combo",
             "native_decode_reference": "combo"}
    (OUT / "tiny-proof-entry.json").write_bytes((json.dumps(entry, indent=2) + "\n").encode())
    print(json.dumps(audit, indent=2))


if __name__ == "__main__":
    main()
