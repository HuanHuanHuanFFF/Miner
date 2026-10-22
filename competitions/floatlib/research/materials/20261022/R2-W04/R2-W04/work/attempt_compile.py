"""Record the actual local compiler launch, without installation or environment changes."""
from pathlib import Path
import json
import shutil
import subprocess

ROOT = Path(__file__).resolve().parent.parent
command = ["lake", "env", "lean", str(ROOT / "Kernel.lean")]
record = {"command": command, "cwd": str(ROOT),
          "executables": {x: shutil.which(x) for x in ["lean", "lake", "elan"]},
          "fixed_dependencies_available": False,
          "installs_performed": False,
          "official_submission_performed": False}
try:
    process = subprocess.run(command, cwd=ROOT, text=True, capture_output=True, timeout=60)
    record.update(status="RUN", exit_code=process.returncode,
                  stdout=process.stdout, stderr=process.stderr)
except FileNotFoundError as exc:
    record.update(status="NOT_RUN", stage="compiler_process_not_started",
                  reason=str(exc))
except subprocess.TimeoutExpired as exc:
    record.update(status="TIMEOUT", reason=str(exc))
(ROOT / "evidence/compile-attempt.json").write_text(json.dumps(record, indent=2) + "\n")
print(json.dumps(record, indent=2))
