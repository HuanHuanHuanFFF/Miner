"""Source-only R26 finite/prepare carriers; no Lean, native builds, or CI."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re
import types

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
R25 = ROOT / "competitions/torchlean/candidates/r25-90m-20261029T064916Z"
OLD = R25 / "research/widen"
sha = lambda b: hashlib.sha256(b).hexdigest()

def text(path):
    return path.read_bytes().decode("utf-8").replace("\r\n", "\n")

def write(path, value):
    path.parent.mkdir(exist_ok=True, parents=True)
    path.write_bytes(value.encode("utf-8"))

def policy(path):
    source = R25 / "verification/exact-policy-preflight.py"
    module = types.ModuleType("r25_pinned_policy")
    module.__file__ = str(source)
    exec(compile(source.read_bytes(), str(source), "exec"), module.__dict__)
    ns, sources = module.load_official_policy()
    wrapped = module.Utf8Path(path)
    a = ns["intake"](wrapped, None)
    b = ns["policy"](wrapped, None) if a is None else None
    return {"intake": a, "policy": b, "passed_intake_policy_only": a is None and b is None,
            "policy_source_sha256": sources}

runtime = text(OLD / "actual-bridge/ActualRuntime.lean.inc")
producer = text(OLD / "prepare-bridge/PrepareRuntime.lean.inc")
agreement = text(OLD / "prepare-bridge/PrepareAgreement.lean.inc")
expword = "namespace Submission.R24RepresentationWiden\n@[inline] def expWord (u : UInt32) : UInt32 := (u >>> 23) &&& 255\nend Submission.R24RepresentationWiden\n"
core_end = agreement.index("theorem step_values")
core = agreement[:core_end] + "\nend Submission.R25PrepareAgreement\n"
prefix = "import ContractExact\n\n" + runtime + "\n" + producer + "\n" + expword + "\n"
outputs = {
    "prepare-v1/PrepareCoreContractOnly.lean": prefix + core,
    "prepare-v1/PrepareAgreementContractOnly.lean": prefix + agreement,
}
R24 = ROOT / "competitions/floatlib/candidates/f01-d7-research/round7h-20261028T203856Z"
tail_runtime = text(R24 / "development-dot-cost/PortableF64Dot-tail-v2.lean.inc")
tail_runtime = tail_runtime[tail_runtime.index("def sumRemaining ("):tail_runtime.index("/-- Zero is a miss sentinel.")].rstrip()
sum_runtime = text(R24 / "research/representation/NativeSumEnclosure3.lean.inc")
sum_runtime = sum_runtime[sum_runtime.index("def loop :"):sum_runtime.index("theorem p2_pos")].rstrip()
tail_source = "import ContractExact\n\nnamespace Submission.R24PortableF64\n" + tail_runtime + "\nend Submission.R24PortableF64\n\n"
tail_source += "namespace Submission.R24RepresentationSum\n" + sum_runtime + "\nend Submission.R24RepresentationSum\n\n"
tail_source += text(HERE / "TailAgreement.lean.inc")
outputs["tail-v1/TailContractOnly.lean"] = tail_source
outputs["prepare-v1/PreparePeakContractOnly.lean"] = prefix + agreement + "\n" + text(HERE / "PreparePeak.lean.inc")
roots = {
    "prepare-v1/PrepareCoreContractOnly.lean": ["Submission.R25PrepareAgreement." + name for name in
        ("body_yields", "prepare_overflow", "prepare_valid_sizecap", "prepare_eq_forIn", "prepare_eq_fold")],
    "prepare-v1/PrepareAgreementContractOnly.lean": ["Submission.R25PrepareAgreement." + name for name in
        ("prepare_eq_forIn", "prepare_eq_fold", "prepare_raw", "prepare_values_data", "prepare_values_size",
         "prepare_valid_rawfinite", "prepare_get", "prepare_getter_interface")],
}
roots["tail-v1/TailContractOnly.lean"] = ["Submission.R26TailAgreement." + n for n in
    ("sumRemaining_eq_loop", "actualTerms_length", "sumRemaining_zero_eq_sum")]
roots["prepare-v1/PreparePeakContractOnly.lean"] = ["Submission.R26PreparePeak." + n for n in
    ("index_nat", "index_bound", "step_peak", "prepare_peak_bound", "prepare_index_bound", "prepare_full_interface")]
rows = []
for rel, source in outputs.items():
    path = HERE / rel
    write(path, source)
    blob = path.read_bytes()
    assert re.findall(rb"(?m)^import .*", blob) == [b"import ContractExact"]
    assert len(blob) < 256000
    rows.append({"path": path.relative_to(ROOT).as_posix(), "sha256": sha(blob), "bytes": len(blob),
                 "roots": roots[rel], **policy(path)})
receipt = {
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "status": "SOURCE_ONLY_LEAN_NOTRUN", "local_compile": False, "CI_owner": "D",
    "runtime_source": "R25 exact fragments from R24 PortableF64Dot-tail-v2; unchanged",
    "runtime_bytes_preserved_after_LF_normalization": True,
    "candidate_priority": "prepare-v1/PrepareCoreContractOnly.lean first, full agreement after actual forIn root passes",
    "outputs": rows,
    "limits": "No finite numeric widening is assumed by these structural producer roots; numerical value bridge and peak bounds remain separate.",
}
(HERE / "prepare-v1/receipt.json").write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8")
print(json.dumps(receipt, indent=2))
