"""Extract original producer declarations and bind source-only proof fragments."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
R25 = HERE.parents[2]
R24 = ROOT / "competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z"
runtime_path = R24 / "development-dot-cost/PortableF64Dot-tail-v2.lean.inc"
raw = runtime_path.read_bytes()
runtime = raw.decode().replace("\r\n", "\n")
sha = lambda b: hashlib.sha256(b).hexdigest()

def between(source, start, end):
    assert source.count(start) == 1
    return source[source.index(start):source.index(end, source.index(start))].rstrip() + "\n"

prepared = between(runtime, "structure Prepared where", "@[inline] def index32")
index = between(runtime, "@[inline] def index32", "/-- Exact finite-word widening recipe")
prepare = between(runtime, "def prepare (", "@[inline] def ceilLog2")
prefix = "namespace Submission.R24PortableF64\n\n" + prepared + "\n" + index + "\n" + prepare + "\nend Submission.R24PortableF64\n"
(HERE / "PrepareRuntime.lean.inc").write_text(prefix, encoding="utf-8", newline="\n")
proof = (HERE / "PrepareAgreement.lean.inc").read_bytes()
for blob in (prefix.encode(), proof):
    for token in (b"sorry", b"axiom ", b"unsafe ", b"implemented_by", b"@[extern", b"native_decide", b"set_option"):
        assert token not in blob, token
evidence = R25 / "evidence/40834710293/download-ebdeaec1f0274f2783f55b29ff81c3ba"
summary = json.loads((evidence / "summary.json").read_text())
accepted = next(r for r in summary["results"] if r["name"] == "widen7")
assert accepted["sha256"] == sha((HERE.parent / "Kernel.lean").read_bytes())
assert accepted["proof_state"] == "FULL_ORIGINAL_PROOF_GATE_PASS"
assert accepted["helper_audit"]["pass"] is True
assert accepted["helper_audit"]["expected"] == accepted["helper_audit"]["printed"] == 6
helper = (evidence / "helper-widen7.log").read_text()
verdict = json.loads((evidence / "widen7-verdict.json").read_text())
proof_log = (evidence / "widen7-proof.log").read_text()
assert verdict["passed"] and verdict["stage"] == "axioms"
assert "Submission replays cleanly" in proof_log
assert "VerifyExact replays cleanly" in proof_log
printed = re.findall(r"^'([^']+)' depends on axioms: \[(.*)\]$", helper, re.M)
assert len(printed) == 6
for _, assumptions in printed:
    assert set(assumptions.split(", ")) <= {"propext", "Classical.choice", "Quot.sound"}
receipt = {
    "phase_first_tool_utc": "2026-10-29T07:41:15Z",
    "recorded_at_utc": datetime.now(timezone.utc).isoformat(),
    "phase_delivery_checkpoint_utc": "2026-10-29T07:58:00Z",
    "common_deadline_utc": "2026-10-29T08:19:16Z",
    "accepted_prior_carrier": {"sha256": accepted["sha256"], "full_original_gate": True, "six_helper_axioms": True, "seconds": accepted["verdict"]["seconds"], "run_id": "40834710293", "source_commit": summary["source_commit"]},
    "acceptance_evidence": [{"path": p.relative_to(ROOT).as_posix(), "sha256": sha(p.read_bytes()), "bytes": len(p.read_bytes())} for p in (evidence / "widen7-verdict.json", evidence / "widen7-proof.log", evidence / "helper-widen7.log")],
    "acceptance_not_inherited_by": ["actual-bridge", "finite-bridge", "prepare-bridge"],
    "new_Lean_status": "NOT_RUN",
    "new_CI_queued": False,
    "runtime_source": runtime_path.relative_to(ROOT).as_posix(),
    "runtime_source_sha256": sha(raw),
    "exact_producer_fragments_normalized_LF_only": True,
    "new_runtime_behavior": False,
    "files": [{"path": "PrepareRuntime.lean.inc", "bytes": len(prefix.encode()), "sha256": sha(prefix.encode())}, {"path": "PrepareAgreement.lean.inc", "bytes": len(proof), "sha256": sha(proof)}],
    "proposed_roots": ["Submission.R25PrepareAgreement." + n for n in ("prepare_overflow", "prepare_valid_sizecap", "prepare_eq_forIn", "prepare_eq_fold", "prepare_values_data", "prepare_valid_rawfinite", "prepare_get", "prepare_getter_interface")],
    "mandatory_actual_source_root": "Submission.R25PrepareAgreement.prepare_eq_forIn",
    "verification_order": ["prepare_overflow and prepare_valid_sizecap", "prepare_eq_forIn on exact original source", "body_yields and prepare_eq_fold", "step/fold values+valid", "prepare_getter_interface"],
    "limits": ["No compiled result for this fragment", "Peak/maxIndex invariant not included", "Native value needs still-unaccepted finite-bridge theorem", "Tail and actual radius not included", "No new large Kernel generated", "No local Lean, native build, Git, CI, or resource change"],
    "builder_sha256": sha(Path(__file__).read_bytes()),
    "tokens": "UNKNOWN", "cached_input": "UNKNOWN", "model_CPU": "UNKNOWN",
}
(HERE / "prepare-source-receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
ast.parse(Path(__file__).read_text())
print(json.dumps({"status": "STATIC_CHECKS_PASS_NEW_LEAN_NOT_RUN", "files": receipt["files"], "accepted_prior_sha256": accepted["sha256"]}))
