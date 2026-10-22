"""Compile this exact candidate in an already prepared, pinned official checkout.

No installation, dependency update, source replacement, gate dispatch, or submission.
Actual official full gate and paired timing remain a separate developer request.
"""
from pathlib import Path
import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parent.parent
OFFICIAL_COMMIT = "978cc5b445edb9943fd9953b0a9037d97a9f33a8"
FLOATLIB_COMMIT = "0d91825727839f597fd06b22fdd038ea21480f0c"
KERNEL_SHA = "98cef0f25c29fe22cf7fa32cc3fb0f2bc38bf1faf65f91aae4fd2d995fe13d84"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("official_root", type=Path)
    parser.add_argument("--output", required=True, type=Path,
                        help="new output directory outside the official checkout")
    args = parser.parse_args()
    official = args.official_root.resolve()
    output = args.output.resolve()
    if output.is_relative_to(official):
        raise SystemExit("Output must be outside the official checkout")
    output.mkdir(parents=True, exist_ok=False)
    kernel = ROOT / "Kernel.lean"
    if hashlib.sha256(kernel.read_bytes()).hexdigest() != KERNEL_SHA:
        raise SystemExit("Candidate SHA differs from the frozen deliverable")
    record = {"kernel_sha256": KERNEL_SHA, "status": "NOT_RUN", "steps": [],
              "installs": False, "official_submission": False}

    def run(label, command, cwd):
        item = {"label": label, "command": [str(x) for x in command], "cwd": str(cwd)}
        record["steps"].append(item)
        try:
            proc = subprocess.run(item["command"], cwd=cwd, capture_output=True, text=True)
        except FileNotFoundError as exc:
            item.update(status="NOT_RUN", reason=str(exc))
            raise RuntimeError(str(exc)) from exc
        (output / (label + ".log")).write_text(proc.stdout + proc.stderr)
        item.update(status="PASS" if proc.returncode == 0 else "FAIL", exit_code=proc.returncode)
        if proc.returncode:
            raise RuntimeError(label + " failed; see the corresponding log")
        return proc.stdout.strip()

    try:
        head = run("official-head", ["git", "rev-parse", "HEAD"], official)
        if head != OFFICIAL_COMMIT:
            raise RuntimeError("Official checkout commit differs from the required pin")
        lean_dir = official / "lean"
        pinned_files = {
            "gate.py": "2d2e97dcbe7e4a131a5655c915e63ffc05c3c34c3f6977534bf4bfd337434ff8",
            "lean/lean-toolchain": "8733782dc070a99b312039cda424f601b80f3be6f6f512627da5ba25adc27632",
            "lean/lakefile.lean": "d15b7364c34241d66e6abb8b3355db3e6eef3cf70d463fd4c9f54a4d3053d92f",
            "lean/lake-manifest.json": "2d2896739b47158bb8d28ffe3303860ee58109bbaad95c9748dc18ccdd1438ad",
        }
        for path, digest in pinned_files.items():
            if hashlib.sha256((official / path).read_bytes()).hexdigest() != digest:
                raise RuntimeError("Pinned file mismatch: " + path)
        manifest = json.loads((lean_dir / "lake-manifest.json").read_text())
        package = next(p for p in manifest["packages"] if p["name"] == "floatlib")
        if package["rev"] != FLOATLIB_COMMIT:
            raise RuntimeError("FloatLib manifest pin mismatch")
        dep_dir = lean_dir / ".lake/packages/floatlib"
        dep_head = run("floatlib-head", ["git", "rev-parse", "HEAD"], dep_dir)
        if dep_head != FLOATLIB_COMMIT:
            raise RuntimeError("Materialized FloatLib commit mismatch")
        lake = shutil.which("lake")
        if not lake:
            raise RuntimeError("lake is not installed/on PATH; no installation was attempted")
        version = run("lean-version", [lake, "env", "lean", "--version"], lean_dir)
        if "4.34.0" not in version:
            raise RuntimeError("Lean version differs from 4.34.0")
        command = [lake, "env", "lean", "--root=" + str(ROOT),
                   "-DautoImplicit=false", "-DrelaxedAutoImplicit=false",
                   "-o", str(output / "Kernel.olean"),
                   "-c", str(output / "Kernel.c"), str(kernel)]
        run("candidate-compile", command, lean_dir)
        record["status"] = "COMPILED_NOT_GATED"
        diagnostic = output / "DiagnosticKernel.lean"
        diagnostic.write_text(kernel.read_text() + "\n" + (ROOT / "diagnostics/Print.commands.txt").read_text())
        run("diagnostic-axioms", [lake, "env", "lean", "--root=" + str(output),
                                 "-DautoImplicit=false", "-DrelaxedAutoImplicit=false",
                                 str(diagnostic)], lean_dir)
        for path, digest in pinned_files.items():
            if hashlib.sha256((official / path).read_bytes()).hexdigest() != digest:
                raise RuntimeError("Pinned file changed while compiling: " + path)
        record["unchanged_pinned_files_after_compile"] = True
        record["note"] = "Inspect the diagnostic axiom report; official VerifyFull/leanchecker/full gate were not run by this script."
    except (OSError, RuntimeError, StopIteration, ValueError) as exc:
        record["reason"] = str(exc)
        if any(s.get("status") == "FAIL" for s in record["steps"]):
            record["status"] = "FAIL"
    finally:
        (output / "compile-record.json").write_text(json.dumps(record, indent=2) + "\n")
        print(json.dumps(record, indent=2))
    return 0 if record["status"] == "COMPILED_NOT_GATED" and "reason" not in record else 1


if __name__ == "__main__":
    sys.exit(main())
