"""Read-only, independent comparison of the actual old/new complete Kernel files."""
from pathlib import Path
import difflib
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
OLD = HERE / "patch-norm-cache-policy1/Kernel.lean"
NEW = HERE / "patch-norm-cache-guarded/Kernel.lean"
NAMES = {"linearCached": ("linearPreGuard", "rows * outW"),
         "gemmCached": ("gemmPreGuard", "batch * (m * n)"),
         "conv2dCached": ("conv2dPreGuard", "s.cout * (s.ho * s.wo)"),
         "depthwiseCached": ("depthwisePreGuard", "s.cin * (s.ho * s.wo)"),
         "rmsnormCached": ("rmsnormPreGuard", "rows * n"),
         "layernormCached": ("layernormPreGuard", "rows * n")}


def block(source: str, name: str) -> str:
    found = re.search(r"^def " + name + r"\b.*?(?=^theorem " + name + r"_eq\b)", source, re.M | re.S)
    assert found is not None, name
    return found.group()


def main() -> None:
    old_raw, new_raw = OLD.read_bytes(), NEW.read_bytes()
    old, new = OLD.read_text(encoding="utf-8"), NEW.read_text(encoding="utf-8")
    assert hashlib.sha256(old_raw).hexdigest() == "bddffa3746a6d36045538d4ec5a57928d81a3d9b23bc52e9bd782c8e932153cf"
    records = []
    for name, (renamed, size) in NAMES.items():
        before, after = block(old, name), block(new, renamed)
        assert before.replace(name, renamed) == after, name
        wrapper = block(new, name)
        expected = f"if {size} = 0 then #[] else {renamed}"
        assert expected in wrapper and "let " not in wrapper, name
        records.append({"kernel": name, "prior_body_identical_after_name_change": True,
                        "guard_is_first_runtime_expression": True, "output_size": size,
                        "old_definition_sha256": hashlib.sha256(before.encode()).hexdigest(),
                        "new_prior_definition_sha256": hashlib.sha256(after.encode()).hexdigest()})
    diff = "".join(difflib.unified_diff(old.splitlines(keepends=True), new.splitlines(keepends=True),
                                        fromfile=OLD.relative_to(HERE).as_posix(), tofile=NEW.relative_to(HERE).as_posix()))
    (HERE / "guard-only.diff").write_text(diff, encoding="utf-8")
    result = {"old_sha256": hashlib.sha256(old_raw).hexdigest(), "new_sha256": hashlib.sha256(new_raw).hexdigest(),
              "old_bytes": len(old_raw), "new_bytes": len(new_raw), "records": records,
              "unified_diff_sha256": hashlib.sha256(diff.encode()).hexdigest(),
              "changes": "Six original cached implementations retained under renamed definitions; only output-empty wrappers and proofs added",
              "original_gate_policy": "PASS_SEPARATE_POLICY_CHECK", "lean": "NOT_RUN", "native_empty_case": "NOT_RUN"}
    (HERE / "guard-change-review.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
