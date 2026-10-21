"""Audit real official full-gate receipts. Never writes into the input artifact.

Bootstrap replay follows validator/admission.py at official commit
978cc5b445edb9943fd9953b0a9037d97a9f33a8. Local run-gates uses evidence id 1.
"""

import argparse
import hashlib
import json
import math
import random
from datetime import datetime, timezone
from pathlib import Path
from statistics import median

OWN = Path(__file__).resolve().parent
ROOT = OWN.parents[3]
PIN = "978cc5b445edb9943fd9953b0a9037d97a9f33a8"
CLASSES = {
    "add:near-one", "add:wide-gap", "add:cancel",
    "mul:near-one", "mul:spread", "mul:tiny",
    "sum:dense", "sum:relu", "sum:wide",
    "bmm:dense", "bmm:relu", "bmm:wide",
}


def read(path):
    return json.loads(path.read_bytes())


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def gain_p05(rounds):
    policy = "paired-median-bootstrap-v1"
    blob = json.dumps([policy, "incumbent", 1, rounds], sort_keys=True, default=str).encode()
    rng = random.Random(int.from_bytes(hashlib.sha256(blob).digest()[:8], "big"))
    ratios = [sub / inc for inc, sub in rounds if inc > 0]
    gains = sorted(1 - median(rng.choice(ratios) for _ in ratios) for _ in range(2000))
    k = (len(gains) - 1) * .05
    lo = int(k)
    return gains[lo] + (gains[min(lo + 1, len(gains) - 1)] - gains[lo]) * (k - lo)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("artifact", type=Path)
    args = parser.parse_args()
    artifact = args.artifact.resolve()
    summary = read(artifact / "summary.json")
    assert summary["official_commit"] == PIN
    run = str(summary["run_id"])
    assert run.isdecimal()
    reference_sha = sha(ROOT / "competitions/floatlib/references/official-incumbent/Kernel.lean")
    output = {"run_id": run, "official_commit": PIN,
              "source_commit": summary["source_commit"],
              "artifact": str(artifact), "summary_sha256": sha(artifact / "summary.json"),
              "complete": summary["complete"], "audited_at_utc": datetime.now(timezone.utc).isoformat(),
              "results": [], "scope": "Public runner evidence against shipped reference; online result UNKNOWN"}
    for name in ("provenance.json", "environment.json"):
        if (artifact / name).exists():
            output[name + "_sha256"] = sha(artifact / name)
    for row in summary["results"]:
        name = row["candidate"]
        kernel = ROOT / "competitions/floatlib" / (
            "references/official-incumbent/Kernel.lean" if name == "baseline"
            else f"candidates/{name}/Kernel.lean")
        assert sha(kernel) == row["kernel_sha256"]
        assert row["reference_sha256"] == reference_sha
        result = {"candidate": name, "kernel_sha256": row["kernel_sha256"], "reference_sha256": reference_sha,
                  "full_gate": row["full_gate"], "exit_code": row["exit_code"], "seed": row["seed"]}
        verdict_path = artifact / row["verdict"]
        if verdict_path.exists():
            verdict = read(verdict_path)
            result.update(verdict_sha256=sha(verdict_path), stage=verdict.get("stage"),
                          reason=verdict.get("reason"))
        if row["full_gate"]:
            assert verdict_path.is_file(), "A full-gate claim requires the original verdict"
            assert row["exit_code"] == 0 and verdict["passed"]
            assert verdict["mode"] == "gate" and verdict["stage"] == "score"
            assert verdict["verifier_fingerprint"] == verdict["verifier_fingerprint_end"]
            classes, rounds = verdict["classes"], verdict["rounds"]
            assert set(classes) == CLASSES and len(rounds) == 25
            assert all(len(pair) == 2 and all(math.isfinite(x) and x > 0 for x in pair) for pair in rounds)
            ratio = sum(x["submission_ns"] for x in classes.values()) / sum(x["incumbent_ns"] for x in classes.values())
            assert abs(ratio - verdict["ratio"]) < 1e-10
            assert abs(ratio - row["ratio"]) < 1e-10
            paired = [sub / inc for inc, sub in rounds]
            gain = gain_p05(rounds)
            if row.get("paired_gain_p05") is not None:
                assert abs(gain - row["paired_gain_p05"]) < 1e-12
            kernels = {}
            for kind in ("add", "mul", "sum", "bmm"):
                subset = [value for key, value in classes.items() if key.startswith(kind + ":")]
                inc = sum(x["incumbent_ns"] for x in subset)
                sub = sum(x["submission_ns"] for x in subset)
                kernels[kind] = {"incumbent_ns": inc, "submission_ns": sub, "ratio": sub / inc}
            result.update(ratio=ratio, paired_ratio_median=median(paired),
                          paired_ratio_min=min(paired), paired_ratio_max=max(paired),
                          paired_gain_p05=gain, rounds=25, kernels=kernels,
                          public_statistical_check=("above-bar" if ratio > .97 else
                                                    "qualifies" if gain > 0 else "not-significant"))
        output["results"].append(result)
    target = OWN / "analyses"
    target.mkdir(exist_ok=True)
    (target / (run + ".json")).write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(output))


if __name__ == "__main__":
    main()
