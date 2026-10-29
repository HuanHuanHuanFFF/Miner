"""Build minimal Widen7 carriers; source checks only, never run Lean or CI."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / "AGENTS.md").is_file())
OLD = ROOT / "competitions/floatlib/candidates"
R24 = OLD / "f01-d7-research/round7h-20261028T203856Z"
BASE = OLD / "f01-r15-dev-packed-b2-1/Kernel.lean"
W7 = R24 / "research/representation/WidenNormal7.lean.inc"
INCUMBENT = R24 / "source-snapshot/torchlean/kernels/exact/incumbent/Kernel.lean"
CONTRACT = R24 / "source-snapshot/torchlean/lean/contract/ContractExact.lean"
sha = lambda b: hashlib.sha256(b).hexdigest()

base_bytes = BASE.read_bytes()
w7_bytes = W7.read_bytes()
assert sha(base_bytes) == "622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58"
assert sha(w7_bytes) == "336b8bbc19a206b2d485a8d047c88854be492493c1daf0d6a77f604884027cd7"
base = base_bytes.decode("utf-8").replace("\r\n", "\n")
w7 = w7_bytes.decode("utf-8").replace("\r\n", "\n")

def between(source, start, end):
    assert source.count(start) == 1, start
    return source[source.index(start):source.index(end, source.index(start))].rstrip() + "\n"

support = """/- Minimal dependency closure extracted from the retained B2 source.
   Only word decoding and model canonicality; no B2 runtime or public endpoints. -/
namespace R2W01c
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

"""
support += between(base[:base.index("end R2W01c")], "theorem modelCanonicalOfFinite", "theorem nativeModel_ofBits_of_decode") + "\n"
support += between(base, "theorem fields32_toDyadic", "theorem uint32_mantissa_model_eq_fields") + "\n"
support += between(base, "abbrev raw32 (u : UInt32)", "theorem mantissa_toNat") + "\n"
support += "end R2W01c\n"

original_exp_proof = """theorem expWord_toNat (u : UInt32) : (expWord u).toNat = wordExp u := by
  exact tableExp_nat u
"""
minimal_exp_proof = """theorem expWord_toNat (u : UInt32) : (expWord u).toNat = wordExp u := by
  rw [expWord, UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) &&& (2 ^ 8 - 1) = u.toNat / 8388608 % 2 ^ 8
  rw [Nat.and_two_pow_sub_one_eq_mod, Nat.shiftRight_eq_div_pow]
"""
assert w7.count(original_exp_proof) == 1
widen = w7.replace(original_exp_proof, minimal_exp_proof)
widen = widen.replace("/- R24 portable binary32-to-native-binary64 component. Normal values and\n   signed zeros only; nonzero subnormals and exponent-255 words are outside\n   Domain. Public B2 endpoints are unchanged. All new proofs are NOT_RUN. -/",
"/- R25 minimal Widen7 carrier. Runtime definitions are unchanged from R24 Widen7.\n   Domain contains binary32 normals and signed zeros only. Nonzero subnormals\n   and exponent-255 words are excluded. This source starts with status NOT_RUN. -/")
assert "tableExp_nat" not in widen
assert "open R2W01b" not in support

def runtime_declarations(source):
    return re.findall(r"(?ms)^@\[inline\] def .*?(?=\n\n)", source)

assert runtime_declarations(widen) == runtime_declarations(w7)
shift = between(widen, "theorem shift29_toReal", "theorem native_value")
shift_probe = "import ContractExact\n\nnamespace Submission.R25WidenShiftProbe\n\n" + shift + "\nend Submission.R25WidenShiftProbe\n"
carrier = "import ContractExact\n\n" + support + "\n" + widen
incumbent = INCUMBENT.read_bytes()
assert incumbent.startswith(b"import ContractExact")
kernel = incumbent + b"\n" + support.encode() + b"\n" + widen.encode()
assert kernel[:len(incumbent)] == incumbent
assert len(kernel) <= 256000

outputs = {
    "WidenSupport.lean.inc": support.encode(),
    "WidenNormal7.lean.inc": widen.encode(),
    "WidenShiftProbe.lean": shift_probe.encode(),
    "WidenCarrier.lean": carrier.encode(),
    "Kernel.lean": kernel,
}
for name, blob in outputs.items():
    if name.endswith(".lean"):
        assert re.findall(rb"(?m)^import .*", blob) == [b"import ContractExact\r" if b"\r\n" in blob[:30] else b"import ContractExact"]
    for token in (b"sorry", b"axiom ", b"unsafe ", b"implemented_by", b"@[extern", b"native_decide"):
        assert token not in blob, (name, token)
    (HERE / name).write_bytes(blob)

roots = ["Submission.R24RepresentationWiden." + name for name in (
    "normal_decode", "native_model", "native_finite", "actual_native_value", "signed_zero_bits", "shift29_toReal")]
support_names = re.findall(r"(?m)^(?:abbrev|def|theorem) ([A-Za-z0-9_]+)", support)
assert len(support_names) == 13, support_names
receipt = {
    "created_at_utc": datetime.now(timezone.utc).isoformat(),
    "first_tool_clock_utc": "2026-10-29T06:52:26Z",
    "deadline_utc": "2026-10-29T08:19:16Z",
    "proof_status": "NOT_RUN",
    "gate_status": "NOT_RUN",
    "performance_status": "NOT_RUN",
    "public_submission_status": "NOT_SUBMITTED",
    "official_repository": "conjectures-io/conjectures-optimisation-float-kernels",
    "official_commit": "accb82b6e2adeda1b41a57a260d68fb3879c427e",
    "FloatLib_commit": "0d91825727839f597fd06b22fdd038ea21480f0c",
    "Lean": "leanprover/lean4:v4.34.0",
    "only_import": "ContractExact",
    "support_namespace": "R2W01c",
    "support_declarations": support_names,
    "explicit_helper_roots": roots,
    "explicit_helper_root_count": len(roots),
    "official_obligation_root": "Submission.correct",
    "standalone_carrier_has_official_endpoints": False,
    "kernel_has_incumbent_prefix_and_official_endpoints": True,
    "runtime_declarations_unchanged_from_W7": True,
    "incumbent_prefix_unchanged": True,
    "incumbent_prefix_bytes": len(incumbent),
    "incumbent_prefix_sha256": sha(incumbent),
    "old_B2_whole_file_required": False,
    "proof_change_from_W7": "Only expWord_toNat inlined to eliminate tableExp_nat/tableIndex/R2W01b dependency; shift29 uses exact W7 hcNum repair.",
    "scope": "Normal binary32 words and signed zeros only; no total finite widening, no Tail/certificate producer/checker bridge, no new optimized kernel behavior.",
    "history": "R24 Math9 run 40810384656 FAIL; W6 errors are two Nat numeral casts in shift29_toReal. W7 was NOT_RUN; no previous acceptance inherited.",
    "inputs": [{"path": p.relative_to(ROOT).as_posix(), "sha256": sha(p.read_bytes()), "bytes": len(p.read_bytes())} for p in (BASE, W7, INCUMBENT, CONTRACT)],
    "outputs": [{"path": name, "sha256": sha(blob), "bytes": len(blob)} for name, blob in outputs.items()],
    "builder_sha256": sha(Path(__file__).read_bytes()),
    "static_checks": ["Exact old B2 and W7 source hashes", "13 support declarations only", "All inline runtime declarations unchanged", "Incumbent prefix byte equality", "256000-byte gate limit", "Only ContractExact import", "No added forbidden source constructs"],
    "resources": {"tokens": "UNKNOWN", "cached_input_tokens": "UNKNOWN", "reasoning_tokens": "UNKNOWN", "local_Lean": False, "local_native_builds": False, "CI_owner": "Droot", "CI_started_by_this_agent": []},
}
(HERE / "carrier-receipt.json").write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8")
ast.parse(Path(__file__).read_text(encoding="utf-8"))
print(json.dumps({"status": "STATIC_SOURCE_CHECKS_PASS_LEAN_NOT_RUN", "outputs": receipt["outputs"], "roots": roots}))
