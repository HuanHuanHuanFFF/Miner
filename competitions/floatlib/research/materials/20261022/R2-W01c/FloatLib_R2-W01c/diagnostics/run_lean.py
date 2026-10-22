"""Use an already-installed pinned environment. Never installs or changes configuration."""
from pathlib import Path
import argparse
import json
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--official-lean", type=Path,
                        help="existing official lean directory containing the fixed lakefile")
    args = parser.parse_args()
    lean, lake = shutil.which("lean"), shutil.which("lake")
    result = {"lean_executable": lean, "lake_executable": lake, "status": "NOT_RUN",
              "installs_attempted": False, "configuration_modified": False,
              "compilation": "NOT_RUN", "axiom_audit": "NOT_RUN"}
    if lean is None or lake is None:
        result["reason"] = "lean or lake is absent from PATH"
    elif Path(lean).resolve().name == "elan" or Path(lake).resolve().name == "elan":
        result["reason"] = "refuses launcher shims; put the already installed toolchain binaries on PATH"
    elif args.official_lean is None:
        result["reason"] = "an existing pinned official environment was not supplied"
    else:
        version = subprocess.run([lean, "--version"], text=True, capture_output=True)
        result["version"] = version.stdout.strip()
        if version.returncode != 0 or "4.34.0" not in version.stdout:
            result["reason"] = "existing Lean version is not confirmed as 4.34.0"
        else:
            envdir = args.official_lean.resolve()
            if not (envdir / "lakefile.lean").is_file():
                raise SystemExit("expected existing official lakefile.lean")
            for name in ("lakefile.lean", "lean-toolchain"):
                if (envdir / name).read_bytes() != (ROOT / "public_sources/official/lean" / name).read_bytes():
                    raise SystemExit("existing official configuration does not match pinned source: " + name)
            outputs = []
            for name in ("ReusableModel.lean", "NormalEqAttempt.lean"):
                proc = subprocess.run([lake, "env", "lean", "-DautoImplicit=false",
                                       "-DrelaxedAutoImplicit=false", str(ROOT / "lean" / name)],
                                      cwd=envdir, text=True, capture_output=True)
                outputs.append({"file": name, "returncode": proc.returncode,
                                "stdout": proc.stdout, "stderr": proc.stderr})
                if proc.returncode:
                    break
            result["compilation"] = "PASS" if all(o["returncode"] == 0 for o in outputs) else "FAIL"
            result["status"] = result["compilation"]
            result["compiler_outputs"] = outputs
            if result["compilation"] == "PASS":
                with tempfile.TemporaryDirectory(prefix="r2w01c-audit-") as tmp:
                    audit = Path(tmp) / "AuditNormal.lean"
                    audit.write_bytes((ROOT / "lean/NormalEqAttempt.lean").read_bytes() + b"\n" +
                                      (ROOT / "diagnostics/AuditCommands.lean").read_bytes())
                    proc = subprocess.run([lake, "env", "lean", "-DautoImplicit=false",
                                           "-DrelaxedAutoImplicit=false", str(audit)], cwd=envdir,
                                          text=True, capture_output=True)
                    result["axiom_audit"] = "OUTPUT_REQUIRES_REVIEW" if proc.returncode == 0 else "FAIL"
                    result["axiom_output"] = {"returncode": proc.returncode,
                                              "stdout": proc.stdout, "stderr": proc.stderr}
    (ROOT / "results/lean_status.json").write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
