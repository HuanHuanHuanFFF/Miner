"""Final static artifact audit. Does not run Lean, a benchmark, or CI."""
from pathlib import Path
from datetime import datetime, timezone
from fractions import Fraction
import hashlib
import json
import re
import types

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
R25 = ROOT / "competitions/torchlean/candidates/r25-90m-20261029T064916Z"
sha = lambda b: hashlib.sha256(b).hexdigest()
policy_path = R25 / "verification/exact-policy-preflight.py"
m = types.ModuleType("pinned_policy"); m.__file__ = str(policy_path)
exec(compile(policy_path.read_bytes(), str(policy_path), "exec"), m.__dict__)
ns, policy_sources = m.load_official_policy()
records = []
for rel in ("prepare-v1/receipt.json", "producer-draft/receipt.json", "producer-join-draft/receipt.json"):
    receipt = json.loads((HERE / rel).read_bytes())
    for e in receipt.get("outputs", [receipt]):
        path = ROOT / e["path"]
        raw = path.read_bytes()
        wrapped = m.Utf8Path(path)
        intake, policy = ns["intake"](wrapped, None), ns["policy"](wrapped, None)
        records.append({"path": e["path"], "sha256": sha(raw), "bytes": len(raw),
                        "receipt_identity": sha(raw) == e["sha256"] and len(raw) == e["bytes"],
                        "only_import_ContractExact": re.findall(rb"(?m)^import [^\r\n]*", raw) == [b"import ContractExact"],
                        "original_intake": intake, "original_policy": policy})
for e in records:
    assert e["receipt_identity"] and e["only_import_ContractExact"]
    assert e["original_intake"] is None and e["original_policy"] is None
counter_path = HERE / "endpoint-implication-counterexample.json"
c = json.loads(counter_path.read_bytes())
s, r, target, upper = map(Fraction, [c["s"]["rational"], c["radius"]["rational"], c["target_exact_rational"], c["native_upper"]["rational"]])
assert abs(s - target) == r and upper < target and c["not_a_runtime_counterexample"]
fields = (HERE / "sources/FloatLib-Fields-Proof.lean.raw").read_bytes()
blob_sha = hashlib.sha1(b"blob " + str(len(fields)).encode() + b"\0" + fields).hexdigest()
assert blob_sha == "d77233aaebfe75066394f8c61900adcd48169db9"
result = {"at_utc": datetime.now(timezone.utc).isoformat(), "source_count": len(records),
          "all_static_checks_pass": True, "sources": records, "policy_sources": policy_sources,
          "counterexample_receipt_sha256": sha(counter_path.read_bytes()),
          "counterexample_rational_implication_rechecked": True,
          "primary_fields_blob_matches": True,
          "Lean": "NOTRUN", "kernel_replay": "NOTRUN", "axiom_audit": "NOTRUN", "performance": "NOTRUN",
          "full_producer_proof": "NOT_ACCEPTED_KNOWN_FAILING_PREFIX_RETAINED",
          "diagnostic_blocker": "Both R26 jobs terminated before original finite diagnostic. No full goals received."}
(HERE / "final-audit.json").write_text(json.dumps(result, indent=2) + "\n")
print(json.dumps({k: result[k] for k in ("at_utc", "source_count", "all_static_checks_pass", "counterexample_rational_implication_rechecked", "Lean", "full_producer_proof")}))
