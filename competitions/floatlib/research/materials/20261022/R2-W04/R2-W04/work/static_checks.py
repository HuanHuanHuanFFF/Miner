"""Reproduce bounded static checks; this does not typecheck Lean."""
from pathlib import Path
from types import SimpleNamespace
import ast
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parent.parent
gate = ROOT / "upstream/official/gate.py"
gate_bytes = gate.read_bytes()
assert hashlib.sha256(gate_bytes).hexdigest() == "2d2e97dcbe7e4a131a5655c915e63ffc05c3c34c3f6977534bf4bfd337434ff8"
tree = ast.parse(gate_bytes.decode())
names = {"_MAX_BYTES", "AXIOMS", "OPTIONS", "ATTRIBUTES", "BANNED"}
functions = {"intake", "policy", "options"}
selected = []
for node in tree.body:
    if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id in names for t in node.targets):
        selected.append(node)
    elif isinstance(node, ast.FunctionDef) and node.name in functions:
        selected.append(node)
env = {"re": re, "Path": Path, "Verdict": object,
       "SLOTS": {"full": SimpleNamespace(contract="ContractTensor")}}
# Only the named literal policy constants and pure scanner functions are evaluated.
# No gate initialization, dependency download, subprocess, or telemetry runs here.
exec(compile(ast.Module(body=selected, type_ignores=[]), str(gate), "exec"), env)
verdict = SimpleNamespace(slot="full")
rows = []
for relative in ["upstream/Kernel.parent.lean", "Kernel.lean"]:
    path = ROOT / relative
    source = path.read_text()
    intake = env["intake"](path, verdict)
    policy = env["policy"](path, verdict)
    rows.append({"file": relative, "bytes": path.stat().st_size,
                 "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
                 "official_intake_function": "PASS" if intake is None else intake,
                 "official_policy_function": "PASS" if policy is None else policy})
    assert intake is None and policy is None, (relative, intake, policy)

candidate = (ROOT / "Kernel.lean").read_text()
start = candidate.index("namespace CheckedFloatArray\n")
prep_start = candidate.index("def prepareLoop ", start)
prep_end = candidate.index("theorem prepareLoop_sound", prep_start)
runtime_prep = candidate[prep_start:prep_end]
assert runtime_prep.count("let d := encode x") == 1
assert "checkOne x d = true" in runtime_prep
assert "out.push d" in runtime_prep
assert "FloatArray.emptyWithCapacity xs.size" in runtime_prep
for absent in [".data", ".map", ".all", "FloatArray.mk"]:
    assert absent not in runtime_prep
assert runtime_prep.count("else none") == 1
assert runtime_prep.count("else some out") == 1
runtime_wrapper = candidate[candidate.index("def bmm ", start):candidate.index("theorem bmm_spec", start)]
assert runtime_wrapper.count("originalBmm batch m n p A B") == 2
assert runtime_wrapper.index("prepare A.toArray") < runtime_wrapper.index("| none =>") < runtime_wrapper.index("prepare B.toArray")
assert re.findall(r"^import\s+(\S+)", candidate, re.M) == ["ContractTensor"]
for spec in ["add_spec", "mul_spec", "sum_spec", "bmm_spec"]:
    assert re.search(r"^theorem\s+" + spec + r"\b", candidate, re.M)
result = {
    "status": "PASS",
    "scope": "exact official intake/policy function replay plus bounded source checks; not Lean elaboration or full gate",
    "official_gate_sha256": hashlib.sha256(gate_bytes).hexdigest(),
    "sources": rows,
    "single_source_encode_binding": True,
    "same_d_checked_and_pushed": True,
    "option_constructor_sites_only_failure_and_endpoint": True,
    "no_runtime_data_map_all_or_FloatArray_mk_in_preparation": True,
    "nested_A_then_B_and_two_original_input_fallbacks": True,
    "single_ContractTensor_import": True,
    "four_specification_declarations_present": True,
    "elaboration_and_axiom_audit": "NOT_RUN",
}
(ROOT / "evidence/static-checks.json").write_text(json.dumps(result, indent=2) + "\n")
print(json.dumps(result, indent=2))
