#!/usr/bin/env python3
"""Check the draft in an already provisioned pinned project. Never installs tools.

Run with the directory containing the pinned project's lakefile.  The combined
diagnostic source is written to a temporary directory, outside the project.
No benchmark, dependency, project source, or compiler-option file is edited.
"""

import argparse
import json
import re
import shutil
import subprocess
import tempfile
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("project", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    status = {
        "candidate_compile": "NOT_RUN",
        "diagnostics": "NOT_RUN",
        "official_policy": "NOT_RUN",
        "official_gate": "NOT_RUN",
        "required_lean": "4.34.0",
        "required_floatlib": "0d91825727839f597fd06b22fdd038ea21480f0c",
        "required_official": "978cc5b445edb9943fd9953b0a9037d97a9f33a8",
        "reason": "",
    }

    def finish(code):
        (output / "compile-status.json").write_text(
            json.dumps(status, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
        )
        print(json.dumps(status, ensure_ascii=False, indent=2))
        return code

    lake = shutil.which("lake")
    if lake is None:
        status["reason"] = "lake is not on PATH; no tool installation was attempted"
        return finish(2)
    project = args.project.resolve()
    if not (project / "lakefile.lean").is_file():
        status["reason"] = "project must be the already provisioned pinned lean/ directory"
        return finish(2)
    toolchain_file = project / "lean-toolchain"
    if not toolchain_file.is_file() or toolchain_file.read_text().strip() != "leanprover/lean4:v4.34.0":
        status["reason"] = "existing lean-toolchain does not name leanprover/lean4:v4.34.0"
        return finish(2)
    elan = shutil.which("elan")
    if elan is not None:
        installed = subprocess.run(
            [elan, "toolchain", "list"], text=True, capture_output=True, check=False
        )
        (output / "installed-toolchains.txt").write_text(
            installed.stdout + installed.stderr, encoding="utf-8"
        )
        if installed.returncode != 0 or not any(
            line.split() and line.split()[0] == "leanprover/lean4:v4.34.0"
            for line in installed.stdout.splitlines()
        ):
            status["reason"] = "required toolchain is not already installed; stopped before invoking lake"
            return finish(2)
    version = subprocess.run(
        [lake, "env", "lean", "--version"], cwd=project,
        text=True, capture_output=True, check=False,
    )
    (output / "lean-version.txt").write_text(version.stdout + version.stderr, encoding="utf-8")
    if version.returncode != 0 or not re.search(r"version 4\.34\.0(?:\s|,|$)", version.stdout):
        status["reason"] = "existing project did not report Lean version 4.34.0"
        return finish(2)
    status["reported_version"] = version.stdout.strip()
    status["dependency_pin_verification"] = "operator must confirm the existing pinned checkout"
    candidate = (root / "ConversionCandidate.lean").read_text(encoding="utf-8")
    commands = (root / "diagnostics" / "Diagnostics.lean").read_text(encoding="utf-8")
    with tempfile.TemporaryDirectory(prefix="r2-w03b-") as directory:
        temporary = Path(directory)
        for key, name, source in [
            ("candidate_compile", "ConversionCandidate.lean", candidate),
            ("diagnostics", "ConversionDiagnostics.lean", candidate + "\n" + commands),
        ]:
            path = temporary / name
            path.write_text(source, encoding="utf-8")
            result = subprocess.run(
                [lake, "env", "lean", str(path)], cwd=project,
                text=True, capture_output=True, check=False,
            )
            (output / (key + ".log")).write_text(
                result.stdout + result.stderr, encoding="utf-8"
            )
            status[key] = "PASS" if result.returncode == 0 else "FAIL"
            if result.returncode != 0:
                status["reason"] = "see the first failing Lean log; no retry with different options"
                return finish(1)
    status["reason"] = "Lean commands completed; inspect printed dependencies and run the official gate after integration"
    return finish(0)


if __name__ == "__main__":
    raise SystemExit(main())
