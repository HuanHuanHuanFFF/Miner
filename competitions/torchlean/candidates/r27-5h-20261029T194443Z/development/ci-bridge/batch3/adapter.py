"""Frozen exact source12+27 composition, no whole upstream source embedded."""
from pathlib import Path
import hashlib,importlib.util
HERE=Path(__file__).resolve().parent
RECIPE=HERE/"graft_native_stats_v1.py"
RECIPE_SHA="1724c804a3c0fd7b2dda55122945ac2e4fac70cd32eeef7777b90c4c7592072d"
def transform(data,submission,variant):
 assert submission==12 and variant=="native-layer-stats-v1"
 assert hashlib.sha256(RECIPE.read_bytes()).hexdigest()==RECIPE_SHA
 spec=importlib.util.spec_from_file_location("r27_norm_graft_batch3",RECIPE);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
 donor=m.fetch(27)
 result,report=m.transform(data,donor,compact=True)
 assert hashlib.sha256(result).hexdigest()=="beca1b56d24ed64ed124fbeae50cb8be267fe3361336eab52b24f0c49720b0ed" and len(result)==255936
 return result
