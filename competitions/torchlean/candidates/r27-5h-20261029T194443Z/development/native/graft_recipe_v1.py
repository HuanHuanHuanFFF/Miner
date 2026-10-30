"""Hash-bound adapter for the shared runner materialize transform interface."""
from pathlib import Path
import hashlib
import importlib.util
import sys

sys.dont_write_bytecode=True
ROOT=next(p for p in Path(__file__).resolve().parents if (p/"AGENTS.md").is_file())
RECIPE=ROOT/"competitions/torchlean/candidates/r27-5h-20261029T194443Z/development/native/graft_native_stats_v1.py"
RECIPE_SHA256="1724c804a3c0fd7b2dda55122945ac2e4fac70cd32eeef7777b90c4c7592072d"
EXPECTED="beca1b56d24ed64ed124fbeae50cb8be267fe3361336eab52b24f0c49720b0ed"

def transform(data,submission,variant):
    assert submission==12 and variant=="native-layer-stats-v1"
    assert hashlib.sha256(RECIPE.read_bytes()).hexdigest()==RECIPE_SHA256
    spec=importlib.util.spec_from_file_location("r27_native_graft_frozen_v1",RECIPE)
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    donor=mod.fetch(27)
    result,receipt=mod.transform(data,donor,compact=True)
    assert hashlib.sha256(result).hexdigest()==EXPECTED and len(result)==255936
    return result
