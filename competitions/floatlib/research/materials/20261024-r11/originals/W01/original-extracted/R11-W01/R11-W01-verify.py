#!/usr/bin/env python3
"""Exact R11-W01 static audit. This does NOT invoke Lean or establish acceptance."""
from pathlib import Path
import argparse, difflib, hashlib, json, re

BASE = "4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0"
PATCHED = "96f8b69364e93a145853f5d98b23222b82b20d55a0c359507dbaa25cf389f40c"
INSERTION = b"decreasing_by omega\n"
ANCHOR = ("  · rename_i hk\n    rw [NativeFinal.dotLoop, dif_neg hk]\n"
          "termination_by n-k\n\ndef wordLoop").encode()
PATCHED_ANCHOR = ANCHOR.replace(b"termination_by n-k\n",
                               b"termination_by n-k\n" + INSERTION)
sha = lambda b: hashlib.sha256(b).hexdigest()

def strip_comments_and_strings(text):
    # A bounded Lean lexer sufficient for this exact source's token scan.
    result, i, depth, quoted = [], 0, 0, False
    while i < len(text):
        if depth:
            if text.startswith("/-", i):
                depth += 1; i += 2
            elif text.startswith("-/", i):
                depth -= 1; i += 2
            else:
                result.append("\n" if text[i] == "\n" else " "); i += 1
        elif quoted:
            if text[i] == "\\":
                i += 2
            elif text[i] == '"':
                quoted = False; result.append(" "); i += 1
            else:
                result.append("\n" if text[i] == "\n" else " "); i += 1
        elif text.startswith("/-", i):
            depth = 1; result.append(" "); i += 2
        elif text.startswith("--", i):
            end = text.find("\n", i)
            if end < 0: break
            result.append("\n"); i = end + 1
        elif text[i] == '"':
            quoted = True; result.append(" "); i += 1
        else:
            result.append(text[i]); i += 1
    assert depth == 0 and not quoted
    return "".join(result)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--directory", type=Path, default=Path(__file__).resolve().parent)
    args = ap.parse_args()
    d = args.directory.resolve()
    b = (d/"Kernel.original.lean").read_bytes()
    c = (d/"Kernel.conditional.lean").read_bytes()
    assert sha(b) == BASE and len(b) == 252609
    assert sha(c) == PATCHED and len(c) == 252629
    assert b.count(ANCHOR) == 1
    anchor_pos = b.index(ANCHOR)
    theorem_pos = b.rfind(b"\ntheorem ", 0, anchor_pos)
    assert b[theorem_pos:].startswith(b"\ntheorem natLoop_lane ")
    assert b.rfind(b"\ndef ", 0, anchor_pos) < theorem_pos
    generated = b.replace(ANCHOR, PATCHED_ANCHOR)
    assert generated == c
    assert c.replace(PATCHED_ANCHOR, ANCHOR) == b
    assert len(c) <= 256000
    diff = "".join(difflib.unified_diff(
        b.decode().splitlines(True), c.decode().splitlines(True),
        fromfile="a/Kernel.lean", tofile="b/Kernel.lean"))
    assert diff == (d/"R11-W01-conditional.patch").read_text()
    clean = strip_comments_and_strings(c.decode())
    forbidden = re.findall(r"\b(?:sorry|admit|unsafe|extern|implemented_by|axiom|native_decide)\b", clean)
    imports = re.findall(r"(?m)^import\s+([^\n]+)", clean)
    options = re.findall(r"\bset_option\s+([^\n]+)", clean)
    assert imports == ["ContractTensor"]
    assert not forbidden and not options
    result = {
        "static_status": "PASS",
        "lean": "NOT_RUN",
        "official_gate": "NOT_RUN",
        "transitive_axiom_audit": "NOT_RUN",
        "performance": "UNKNOWN",
        "base": {"sha256": sha(b), "bytes": len(b), "margin": 256000-len(b)},
        "conditional": {"sha256": sha(c), "bytes": len(c), "margin": 256000-len(c)},
        "patch": {"added_bytes": len(c)-len(b), "applies_to_exact_base": True,
                  "reverse_reconstructs_exact_base": True,
                  "only_insertion": INSERTION.decode().rstrip(),
                  "insertion_scope": "theorem Submission.R11CrossRows.natLoop_lane",
                  "all_other_source_bytes_identical": True,
                  "runtime_definition_bytes_changed": False},
        "imports": imports, "source_set_options": options,
        "forbidden_token_scan": forbidden,
        "warning": "Source-byte/token checks do not establish elaboration, trusted axioms, runtime correctness, or benchmark acceptance."
    }
    print(json.dumps(result, ensure_ascii=False, indent=2))

if __name__ == "__main__":
    main()
