"""E1 proof2: normalize actual Aeneas fallback clones to original loop specs.

The Rust and proof1 are preserved. Textual clone checks are a preflight only;
all equalities and the original obligation must be checked by the remote gate.
"""
from pathlib import Path
import datetime
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
OLD = ROOT / "candidates/r26-e-658-short-same-proof1"
NEW = ROOT / "candidates/r26-e-658-short-same-proof2"
OUT = ROOT / "evidence/round26/extension90m/route-e"
FUNS = ROOT / "evidence/round26/38268487485/screen90-e1/gate/research5/r26-e-658-short-same/Funs.lean"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def dump(path, obj):
    path.write_bytes((json.dumps(obj, indent=2, ensure_ascii=False)+"\n").encode())


def definition(text, number, body=False):
    suffix = ".body" if body else ""
    name = f"u118_same_loop{number}{suffix}"
    pattern = rf"(?m)^def {re.escape(name)}\n.*?(?=\n/--|\Z)"
    match = re.search(pattern, text, re.S)
    assert match, name
    return match.group(0).strip()


def main():
    assert not NEW.exists(), NEW
    rust = (OLD / "parse.rs").read_bytes()
    lean1 = (OLD / "Parse.lean").read_bytes()
    assert sha(rust) == "bc1b3fec788a0d58d220efb84505e26f83a7045129c724f43095704c6097adc0"
    assert sha(lean1) == "f89c185a339c499c4b07deb7e25eb94a66c7b3bd6f28e51a6e36e64f997cee12"
    funs_raw = FUNS.read_bytes()
    funs = funs_raw.decode().replace("\r\n", "\n")
    aliases = []
    checked = []
    for number in range(3, 15):
        base = number % 3
        for body in [True, False]:
            current = definition(funs, number, body)
            normalized = current.replace(f"u118_same_loop{number}", f"u118_same_loop{base}")
            original = definition(funs, base, body)
            assert normalized == original, (number, base, body)
            checked.append({"clone": f"u118_same_loop{number}" + (".body" if body else ""),
                "reference": f"u118_same_loop{base}" + (".body" if body else ""),
                "equal_after_exact_name_normalization": True,
                "clone_text_sha256": sha(current.encode()), "reference_text_sha256": sha(original.encode())})
        aliases.append(f'''theorem e1_same_loop{number}_eq (s : Slice Std.U8)
    (a b len k ok1 : Std.Usize) :
    slot.u118_same_loop{number} s a b len k ok1 =
      slot.u118_same_loop{base} s a b len k ok1 := by rfl
''')
    aliases_text = ("/- E1 UNCOMPILED: real extraction duplicates fallback loops. Each alias\n"
                    "   below is a kernel equality of the unchanged cloned program. -/\n" + "\n".join(aliases) + "\n")
    text = lean1.decode()
    start = text.index("@[local step]\ntheorem same_spec", text.index("namespace U118_MAIN"))
    text = text[:start] + aliases_text + text[start:]
    same_start = text.index("theorem same_spec", text.index("namespace U118_MAIN"))
    rw_start = text.index("  rw [slot.u118_same]\n", same_start)
    names = ", ".join(f"e1_same_loop{n}_eq" for n in range(3, 15))
    text = (text[:rw_start] + text[rw_start:].replace("  rw [slot.u118_same]\n",
            f"  rw [slot.u118_same]\n  simp only [{names}]\n", 1))
    lean2 = text.encode()
    assert len(lean2) <= 524288
    assert not re.search(rb"(?m)^\s*(axiom\s|.*\b(sorry|admit)\b)", lean2)
    NEW.mkdir()
    (NEW / "parse.rs").write_bytes(rust)
    (NEW / "Parse.lean").write_bytes(lean2)
    metadata = json.loads((OLD / "manifest.json").read_bytes())
    metadata.update({"candidate": NEW.name,
        "hashes": {"parse.rs": sha(rust), "Parse.lean": sha(lean2)},
        "proof_status": "UNCOMPILED_ORIGINAL_GATE_NOT_RUN",
        "proof_origin": {"path": OLD.relative_to(ROOT).as_posix()+"/Parse.lean", "sha256": sha(lean1)},
        "proof_adaptation": "Add12 rfl equalities for actual Aeneas fallback clones3..14 and normalize them to original loop0/1/2 before step*. Original loop invariants and complete same_spec obligations remain unchanged. Actual kernel checking and fast-prefix branch matching remain untested.",
        "extraction_reference": FUNS.relative_to(ROOT).as_posix(),
        "extraction_reference_sha256": sha(funs_raw),
        "proof_freeze_time_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "confirmation_status": "No post-freeze measurement or full gate for this exact proof2 pair. Prior Rust-identical measurements are discovery only.",
        "formal_submission_sent": False})
    dump(NEW / "manifest.json", metadata)
    entry = {"name": NEW.name, "path": NEW.relative_to(ROOT).as_posix(),
        "hashes": metadata["hashes"], "status": metadata["proof_status"],
        "rust_bytes": len(rust), "lean_bytes": len(lean2), "lean_spare_bytes": 524288-len(lean2),
        "control": False, "anchor": "public658", "comparison_baseline": "public658"}
    dump(OUT / "e1-proof2-entry.json", entry)
    dump(OUT / "e1-real-clone-preflight.json", {"status": "TEXTUAL_CLONE_PREFLIGHT_ONLY_NOT_LEAN",
        "extracted_funs_sha256": sha(funs_raw), "clone_definitions_checked": checked,
        "loop_clone_aliases": len(aliases), "hashes": metadata["hashes"]})
    (OUT / "E1-clone-aliases-UNCOMPILED.lean").write_bytes(aliases_text.encode())
    print(json.dumps(entry, indent=2))


if __name__ == "__main__":
    main()
