"""Frozen next exact norm variants; full upstream source stays ephemeral."""
from pathlib import Path
import hashlib,importlib.util
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/"AGENTS.md").is_file())
ROUND=HERE.parents[2]
PIN="e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521"
def module(path,name):
 spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def transform(data,submission,variant):
 assert submission==12 and hashlib.sha256(data).hexdigest()==PIN
 if variant=="native-layer-stats-v1-hb":
  m=module(HERE/"graft_native_stats_v1.py","r27_graft3")
  result,receipt=m.transform(data,m.fetch(27),compact=True)
  assert hashlib.sha256(result).hexdigest()=="beca1b56d24ed64ed124fbeae50cb8be267fe3361336eab52b24f0c49720b0ed"
  marker=b"import ContractExact\n";assert result.count(marker)==1
  return result.replace(marker,marker+b"set_option maxHeartbeats 1000000\n",1)
 if variant=="guard26-v2":
  m=module(HERE/"patch_norm_guard_v2.py","r27_guard3");return m.transform(data.decode("utf-8")).encode("utf-8")
 if variant=="norm-prep-proof2":
  m=module(HERE/"repair_norm_prep_v2.py","r27_prep3");return m.transform(data,submission,variant)
 raise ValueError(variant)
