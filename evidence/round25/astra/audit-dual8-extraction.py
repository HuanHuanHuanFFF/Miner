"""Read exact extraction and byte receipts; no candidate/proof mutations."""
from pathlib import Path
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[3]
OUT = Path(__file__).resolve().parent
NEW = ROOT / "evidence/round25/38126033837/proof-c-extract/diagnostics/research5/r25-astra-dual8"
OLD = ROOT / "evidence/round23/38072972025/gate-combo/exact-gate/exact-gate/extracted"


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def definitions(path):
    text = path.read_text()
    text = re.sub(r"/\-.*?\-/", "", text, flags=re.S)
    text = re.sub(r"--[^\n]*", "", text)
    positions = list(re.finditer(r"(?m)^(?:@\[[^\]]*\]\s*)?def\s+([A-Za-z0-9_.]+)\b", text))
    result = {}
    for i, m in enumerate(positions):
        end = positions[i + 1].start() if i + 1 < len(positions) else len(text)
        result[m.group(1)] = re.sub(r"\s+", " ", text[m.start():end]).strip()
    return result


def main():
    old, new = definitions(OLD / "Funs.lean"), definitions(NEW / "Funs.lean")
    changed = sorted(k for k in old.keys() & new.keys() if old[k] != new[k])
    added = sorted(new.keys() - old.keys())
    removed = sorted(old.keys() - new.keys())
    feedback = json.loads((ROOT / "evidence/round25/feedback-c-native.json").read_bytes())
    dual = next(x for x in feedback["summary"] if x["candidate"] == "r25-astra-dual8")
    end4 = next(x for x in feedback["summary"] if x["candidate"] == "end4")
    rows = dual["changed_files"]
    losses = [x for x in rows if x["byte_delta"] > 0]
    wins = [x for x in rows if x["byte_delta"] < 0]
    gross_saved = -sum(x["byte_delta"] for x in wins)
    gross_lost = sum(x["byte_delta"] for x in losses)
    top4 = sorted(wins, key=lambda x: x["byte_delta"])[:4]
    comparison = {x["file"]: x["byte_delta"] for x in end4["changed_files"]}
    relative = [{"file": x["file"], "dual_minus_end4_bytes": x["byte_delta"] - comparison.get(x["file"], 0)}
                for x in rows]
    result = {
        "status": "VERIFIED_STATIC_ACTUAL_EXTRACTION_AND_NATIVE_BYTES_REVIEW_NOT_PROOF",
        "new_artifacts": {f: {"bytes": (NEW / f).stat().st_size, "sha256": sha(NEW / f)}
                          for f in ("Funs.lean", "Types.lean", "Constants.lean")},
        "parent_funs": {"path": (OLD / "Funs.lean").relative_to(ROOT).as_posix(), "sha256": sha(OLD / "Funs.lean")},
        "definition_comparison": {"normalization": "Remove generated comments and normalize whitespace; not a Lean semantic equivalence proof.",
                                  "parent_definitions": len(old), "new_definitions": len(new),
                                  "changed_shared": changed, "new": added, "removed": removed},
        "native": {"candidate": dual["candidate"], "source_sha256": feedback["candidate_hashes"][dual["candidate"]]["parse.rs"],
                   "raw_receipt": feedback["source_receipt"], "improved_files": len(wins), "worsened_files": len(losses),
                   "unchanged_files": 28 - len(rows), "gross_saved_bytes": gross_saved, "gross_lost_bytes": gross_lost,
                   "net_saved_bytes": gross_saved - gross_lost, "net_token_delta": sum(x["token_delta"] for x in rows),
                   "top4": top4, "top4_gross_saved_fraction": -sum(x["byte_delta"] for x in top4) / gross_saved,
                   "losses": losses, "active_file_dual_vs_end4": relative},
        "proof_limits": "Extraction used empty Parse.lean in research helper. It establishes Rust extraction only, not the inherited exact Rust/Lean pair. No candidate proof edited or compiled in this audit."
    }
    # Prevent a changed pre-existing shared function from being silently omitted in the review.
    assert changed == ["p125_row1", "p125_row6"], changed
    assert not removed, removed
    assert all(x.startswith("r25_d8_") for x in added), added
    candidate = ROOT / "candidates/r25-astra-dual8/parse.rs"
    assert sha(candidate) == result["native"]["source_sha256"]
    (OUT / "dual8-extraction-quality-audit.json").write_bytes((json.dumps(result, indent=2) + "\n").encode())
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
