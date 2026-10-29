"""Exact repaired fetch/cache adapter, same native128 candidate bytes."""
from pathlib import Path
import hashlib,importlib.util,os
HERE=Path(__file__).resolve().parent
def module(path,name):
 spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def transform(data,submission,variant):
 assert submission==12
 if variant=="native-layer-stats-v1-hb":
  donor=Path(os.environ["TORCHLEAN_ROOT"])/"r27-source-private/official-27.lean"
  raw=donor.read_bytes();assert hashlib.sha256(raw).hexdigest()=="f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67"
  m=module(HERE/"graft_native_stats_v1.py","graft4");out,_=m.transform(data,raw,compact=True)
  assert hashlib.sha256(out).hexdigest()=="beca1b56d24ed64ed124fbeae50cb8be267fe3361336eab52b24f0c49720b0ed"
  return out.replace(b"import ContractExact\n",b"import ContractExact\nset_option maxHeartbeats 1000000\n",1)
 if variant=="norm-prep-proof3":return module(HERE/"repair_norm_prep_v3.py","prep4").transform(data,submission,variant)
 raise ValueError(variant)
