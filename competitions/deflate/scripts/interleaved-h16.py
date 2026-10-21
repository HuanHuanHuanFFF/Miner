"""H16-specific wrapper of the existing optional multi-method diagnostic.

Official engine, sandbox, ordering and repetition counts are unchanged. Relative
fields explicitly name the configured H16 baseline, not the old fast3 baseline.
"""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path

HERE = Path(__file__).resolve()
spec = importlib.util.spec_from_file_location("h16_interleaved_common", HERE.with_name("interleaved-round4.py"))
common = importlib.util.module_from_spec(spec)
spec.loader.exec_module(common)
common.BASELINE = "h16-base"
original_summary = common.summarize
original_run = common.run


def rename_relative_fields(value):
    if isinstance(value, dict):
        return {key.replace("fast3", "baseline"): rename_relative_fields(item) for key, item in value.items()}
    if isinstance(value, list):
        return [rename_relative_fields(item) for item in value]
    return value


def summarize(files, order, incumbent):
    return rename_relative_fields(original_summary(files, order, incumbent))


def run(config_request, output, report):
    report.update({"relative_baseline": common.BASELINE,
                   "wrapper_sha256": hashlib.sha256(HERE.read_bytes()).hexdigest(),
                   "relative_field_schema": "*_baseline refers to h16-base; no fast3-relative fields"})
    return original_run(config_request, output, report)


common.summarize = summarize
common.run = run

if __name__ == "__main__":
    common.main()
