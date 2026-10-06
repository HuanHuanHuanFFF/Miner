"""Two finite experiments using the unchanged official measurement pipeline.

Full per-process records go to the CI log, without caches or uploaded artifacts.
No submission client, database publication, wallet, or chain worker is invoked.
"""

from __future__ import annotations

import dataclasses
import hashlib
import json
import os
import statistics
from pathlib import Path

from bench import corpora
from bench.driver import Config, Keep, run
from bench.results import INCUMBENT


def main() -> None:
    assert os.environ.get("GITHUB_ACTIONS") == "true"
    assert os.environ.get("RUNNER_OS") == "Linux"
    assert os.environ.get("GITHUB_REPOSITORY") == "HuanHuanHuanFFF/Miner"
    upstream = Path(os.environ["DEFLATE_ROOT"])
    workspace = Path(os.environ["GITHUB_WORKSPACE"])
    reports = Path(os.environ["RUNNER_TEMP"]) / "deflate-reports"
    corpus = corpora.load(upstream / "validator").by_name("corpus-stage1")
    assert corpus.public
    # One available CPU throughout this job reduces migration noise. The paired
    # incumbent always uses the same CPU, encoder, repetitions and toolchain.
    cpu = str(min(os.sched_getaffinity(0)))
    config = dataclasses.replace(
        Config.from_env(upstream / "validator"),
        reps=11, warmup=1, cpus=cpu, keep=Keep.NEVER, bars=False,
    )
    sources = {
        "template": upstream / "miner/template/parse.rs",
        "submission-261": workspace / "references/submission-261/parse.rs",
        "hash-wide": workspace / "candidates/hash-wide/parse.rs",
        "probe2": workspace / "candidates/probe2/parse.rs",
    }
    results: list[dict] = []
    evidence = {}
    orders = [list(sources), list(reversed(sources))]
    for round_index, order in enumerate(orders, 1):
        for name in order:
            print(f"MEASURE_BEGIN round={round_index} candidate={name}", flush=True)
            measured = run(config, {name: sources[name]}, corpus).only()
            errors = measured.failures(name) + measured.failures(INCUMBENT)
            if errors:
                raise RuntimeError(errors)
            files = [file for file in measured.files if file.raw_bytes > 0]
            ratios = [
                file.methods[name].total_s / file.methods[INCUMBENT].total_s
                for file in files
            ]
            size = statistics.mean(
                100 * file.methods[name].output_bytes / file.raw_bytes for file in files
            )
            result = {
                "round": round_index,
                "candidate": name,
                "balanced_time_ratio_public": statistics.mean(ratios),
                "mean_file_compression_pct_public": size,
                "raw_bytes": measured.totals(name).raw_bytes,
                "output_bytes": measured.totals(name).output_bytes,
                "parse_s": measured.totals(name).parse_s,
                "total_s": measured.totals(name).total_s,
                "incumbent_total_s": measured.totals(INCUMBENT).total_s,
                "worst_spread": measured.worst_spread(),
                "files": len(files),
                "source_sha256": hashlib.sha256(sources[name].read_bytes()).hexdigest(),
            }
            results.append(result)
            evidence[round_index, name] = measured
            print("MEASUREMENT " + json.dumps(result, allow_nan=False), flush=True)
            for record in measured.raw_records:
                print(f"RAW_EVIDENCE {round_index} {name} " + json.dumps(record, allow_nan=False))
            print(f"MEASURE_END round={round_index} candidate={name}", flush=True)

    # Repeated compressed bytes and tokens must agree, including the incumbent.
    for name in sources:
        first = evidence[1, name]
        second = evidence[2, name]
        assert [f.sha256 for f in first.files] == [f.sha256 for f in second.files]
        for a, b in zip(first.files, second.files, strict=True):
            for method in (name, INCUMBENT):
                assert a.methods[method].output_sha256 == b.methods[method].output_sha256
                assert a.methods[method].tokens_sha256 == b.methods[method].tokens_sha256

    output = {
        "status": "measured; proof gate is a separate step",
        "scope": "CI host; public corpus-stage1 only; no ranking or reward prediction",
        "cpu_affinity": cpu,
        "warmup_rounds": 1,
        "measured_rounds": 11,
        "experiment_rounds": 2,
        "orders": orders,
        "metrics": "mean per-file ratios of median parser+encoder times; mean per-file size percentages",
        "results": results,
    }
    (reports / "comparison.json").write_text(json.dumps(output, indent=2, allow_nan=False) + "\n")
    print("COMPARISON " + json.dumps(output, allow_nan=False), flush=True)


if __name__ == "__main__":
    main()
