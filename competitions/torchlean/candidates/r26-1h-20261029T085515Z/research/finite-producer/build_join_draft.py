"""Bind the real producer and A's real checker; source-only, no queue request."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import types

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
R25 = ROOT / "competitions/torchlean/candidates/r25-90m-20261029T064916Z"
R24 = ROOT / "competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z"
sha = lambda b: hashlib.sha256(b).hexdigest()
records = []

def read(path):
    raw = path.read_bytes()
    records.append({"path": path.relative_to(ROOT).as_posix(), "sha256": sha(raw), "bytes": len(raw)})
    return raw.decode().replace("\r\n", "\n")

source = read(HERE / "producer-draft/ProducerContractOnly.lean")
checker = read(HERE.parent / "key/follow-on/RuntimeIdentityContractOnly.lean")
assert checker.startswith("import ContractExact\n")
source += "\n\n" + checker[len("import ContractExact\n"):]
source += "\n\n" + read(R24 / "research/controller/StrictEnclosure-v2.lean.inc")
runtime = read(R24 / "development-dot-cost/PortableF64Dot-tail-v2.lean.inc")
i = runtime.index("def attemptPrepared (")
attempt = runtime[i:runtime.index("/-- Preparation and dropping", i)].rstrip() + "\n"
source += "\nnamespace Submission.R24PortableF64\n" + attempt + "\nend Submission.R24PortableF64\n"
source += "\n" + read(HERE / "AttemptGuards.lean.inc")
source += "\n" + read(HERE / "ProducerCheckerJoin.lean.inc")
out = HERE / "producer-join-draft/ProducerCheckerContractOnly.lean"
out.parent.mkdir(exist_ok=True)
out.write_bytes(source.encode())
policy_path = R25 / "verification/exact-policy-preflight.py"
m = types.ModuleType("pinned_policy"); m.__file__ = str(policy_path)
exec(compile(policy_path.read_bytes(), str(policy_path), "exec"), m.__dict__)
ns, sources = m.load_official_policy()
wrapped = m.Utf8Path(out)
intake = ns["intake"](wrapped, None)
policy = ns["policy"](wrapped, None) if intake is None else None
result = {"at_utc": datetime.now(timezone.utc).isoformat(),
          "path": out.relative_to(ROOT).as_posix(), "sha256": sha(out.read_bytes()), "bytes": out.stat().st_size,
          "intake": intake, "policy": policy, "inputs": records,
          "status": "INSPECTION_ONLY_KNOWN_FAILING_PREFIX_NOTRUN_NO_NEW_CI_REQUEST",
          "root": "Submission.R26ProducerCheckerJoin.attemptPrepared_contains_rawSum",
          "root_premise": "Actual attemptPrepared on actual prepares returns a nonzero UInt32. No B/enclosure/finite/shape premises remain at this root.",
          "conclusion": "Exact raw real dot lies strictly between the actual returned word midpoint values; official integer-total/finishWord equality and signed-zero fallback still separate."}
(out.parent / "receipt.json").write_text(json.dumps(result, indent=2) + "\n")
print(json.dumps({k: result[k] for k in ("status", "sha256", "bytes", "intake", "policy", "root")}))
