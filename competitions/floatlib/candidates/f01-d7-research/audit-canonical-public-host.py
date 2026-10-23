"""Independently bind saved W12c public-host sources, assertions and raw logs.

Read-only evidence audit: never invokes Lean or inherits new runtime acceptance.
"""
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
import re
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent
R = ROOT / "competitions/floatlib/research/astra-collab-20261023-r7"
W = R / "web/R7-W12c/original-extracted/R7-W12c"
FILES = {}


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def read(path):
    raw = path.read_bytes()
    rel = path.relative_to(ROOT).as_posix()
    FILES[rel] = {"path": rel, "bytes": len(raw), "sha256": sha(raw), "availability": "LOCAL_ONLY"}
    return raw


def obj(path):
    return json.loads(read(path))


def proof_text_without_comments_or_space(raw):
    text = raw.decode()
    out = []
    depth = 0
    i = 0
    while i < len(text):
        if text.startswith("/-", i):
            depth += 1
            i += 2
        elif depth and text.startswith("-/", i):
            depth -= 1
            i += 2
        elif depth:
            i += 1
        elif text.startswith("--", i):
            end = text.find("\n", i)
            i = len(text) if end == -1 else end
        else:
            # These proof blocks contain no string literals. Refuse to apply
            # comment normalization if a future source introduces any.
            assert text[i] != '"'
            if not text[i].isspace():
                out.append(text[i])
            i += 1
    assert depth == 0
    return "".join(out)


def raw_axioms(log):
    reports = {}
    for match in re.finditer(r"'([^']+)' depends on axioms:\s*\[([^]]*)\]", log, re.S):
        name = match.group(1)
        assert name not in reports
        reports[name] = set(re.findall(r"[A-Za-z_][A-Za-z0-9_.]*", match.group(2)))
    for match in re.finditer(r"'([^']+)' does not depend on any axioms", log):
        name = match.group(1)
        assert name not in reports
        reports[name] = set()
    return reports


def main():
    original = read(W / "original/Kernel.lean")
    merged = read(W / "Kernel.lean")
    increment = read(W / "R7W12cIncrement.lean")
    assert sha(original) == "60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15"
    assert sha(merged) == "173a091ecfa2d6ae7c3c048459e570cbffed4098d2a5ce70af3d2da6afa5c911"
    assert sha(increment) == "e2e2ce789b087824239d2b6ae52ac6f8e4620c7d36bb1ea1fc00c0c09b40f218"
    insertion = obj(W / "evidence/insertion-preservation.json")
    position = insertion["insertion_original_offset"]
    assert merged == original[:position] + b"\n" + increment + b"\n" + original[position:]
    local = read(R / "canonical-image-minimal-block.lean")
    assert sha(local) == "61d49494b764bc433312202f3928a3dc6986eb91f4f64d2fb309ccf7370e0aed"
    assert proof_text_without_comments_or_space(local) == proof_text_without_comments_or_space(increment)
    static_spec = importlib.util.spec_from_file_location("exact_policy_preflight", HERE / "precheck-plan.py")
    static_module = importlib.util.module_from_spec(static_spec)
    static_spec.loader.exec_module(static_module)
    gate = HERE / "official-policy/gate-4b7e838.raw"
    gate_bytes = read(gate)
    assert sha(gate_bytes) == "1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194"
    policy = static_module.extract_policy(gate_bytes, sha(gate_bytes))
    slot = SimpleNamespace(slot="full")
    assert policy["intake"](W / "Kernel.lean", slot) is None
    assert policy["policy"](W / "Kernel.lean", slot) is None
    attempts = []
    for name in ("Kernel-attempt1", "ScratchMerged-attempt1", "OriginalDiagnostics-attempt1", "Kernel-attempt2", "KernelDiagnostics-attempt1"):
        record = obj(W / f"logs/{name}.json")
        snapshot = read(W / f"logs/{name}.lean")
        log = read(W / record["log"])
        assert record["returncode"] == 0
        assert sha(snapshot) == record["source_sha256"]
        assert not re.search(rb":\d+:\d+: error(?:\b|\()", log)
        attempts.append({"name": name, "source_sha256": sha(snapshot), "explicit_exit": record["returncode"], "seconds": record["elapsed_seconds"]})
    assert read(W / "logs/Kernel-attempt1.lean") == original
    assert read(W / "logs/Kernel-attempt2.lean") == merged
    original_diag = read(W / "logs/OriginalDiagnostics-attempt1.lean")
    merged_diag = read(W / "logs/KernelDiagnostics-attempt1.lean")
    assert original_diag.startswith(original) and merged_diag.startswith(merged)
    specs = read(W / "evidence/SpecAssertions.lean.txt")
    closures = read(W / "evidence/ClosureAssertions.lean.txt")
    assert specs in original_diag and specs in merged_diag and closures in merged_diag
    allowed = {"propext", "Classical.choice", "Quot.sound"}
    audits = {}
    for prefix, name, count in (("original", "OriginalDiagnostics", 8), ("final", "KernelDiagnostics", 41)):
        log = read(W / f"logs/{name}-attempt1.log").decode()
        actual = raw_axioms(log)
        summary = obj(W / f"logs/{prefix}-axiom-audit.json")
        required = obj(W / ("evidence/original-required-axiom-declarations.json" if prefix == "original" else "evidence/required-axiom-declarations.json"))
        assert len(actual) == count and set(actual) == set(required)
        assert actual == {k: set(v) for k, v in summary["axioms"].items()}
        assert all(s <= allowed for s in actual.values())
        audits[prefix] = actual
    for name in ("add", "mul", "sum", "bmm"):
        assert audits["original"][f"Submission.{name}_spec"] == audits["final"][f"Submission.{name}_spec"]
    for rel, info in FILES.items():
        assert sha((ROOT / rel).read_bytes()) == info["sha256"], rel
    report = {
        "checked_at_utc": datetime.now(timezone.utc).isoformat(),
        "status": "PASS_SAVED_SOURCE_LOG_BINDING_AND_ASSERTIONS",
        "public_original_sha256": sha(original), "public_merged_sha256": sha(merged),
        "compiled_increment_sha256": sha(increment), "minimal61d_proof_text_equivalence": True,
        "exact_original_single_insertion": True, "attempts": attempts,
        "current_original_intake_options_policy": "PASS_STATIC_ONLY",
        "raw_axiom_counts": {k: len(v) for k, v in audits.items()},
        "original_four_spec_assertions_identical": True, "four_unconditional_closure_assertions_present": True,
        "files": FILES,
        "boundary": "Independently read retained compiler source snapshots, explicit exits and raw axiom logs. No compiler or leanchecker rerun. W12c source is public60f plus unused proof declarations only; current4792 BMM and3d9 sum actual-loop integration, original fullgate and performance remain NOT_RUN.",
    }
    (HERE / "canonical-public-host-review.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"status": report["status"], "files": len(FILES), "attempts": len(attempts), "raw_axioms": report["raw_axiom_counts"]}))


if __name__ == "__main__":
    main()
