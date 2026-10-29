"""Frozen owned norm patch adapter; no complete upstream source embedded."""
from pathlib import Path
import importlib.util,hashlib
HERE=Path(__file__).resolve().parent
PIN="e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521"
def load(name):
 spec=importlib.util.spec_from_file_location("r27_norm_"+name,HERE/(name+".py"));m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def transform(data,submission,variant):
 assert submission==12 and hashlib.sha256(data).hexdigest()==PIN
 if variant=="guard26":return load("patch_norm_guard").transform(data.decode("utf-8")).encode("utf-8")
 if variant=="norm-prep":return load("patch_public").transform(data,12,"norm-prep")
 raise ValueError(variant)
