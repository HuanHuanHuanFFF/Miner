"""Integrate the owned FP-only cost route on compact public23.

The frozen carrier adapter preserves the stronger public23 norm functions.
It has no correctness theorem for its actual new dense kernel.
"""
from pathlib import Path
import hashlib,importlib.util
HERE=Path(__file__).resolve().parent
PIN='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
COMPACT='4c3dd79284f6701d3b128687f9f973f47d9236f8d9db502d398e2eb4d131e129'
PATCH='d61bf830be1b197c451b50e555abb2af7b7cd001dc0c80cfb4ddacf6234dfc75'
HELPER='1762a473178d3a45b431c94b995a2616fd4b939dd5b98d65f40ada71dfc2c892'
def load(filename,pin):
    p=HERE/filename;assert hashlib.sha256(p.read_bytes()).hexdigest()==pin
    spec=importlib.util.spec_from_file_location('r27_frozen_'+p.stem,p)
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def transform(data,submission=23,variant='fp-only-public23'):
    assert submission==23 and variant=='fp-only-public23'
    assert hashlib.sha256(data).hexdigest()==PIN
    compact=load('frozen_compact_public23.py',COMPACT).transform(data,'proof')[0]
    assert hashlib.sha256(compact).hexdigest()=='fc7b1e9e1b258f5254c75e046972fdc3bdc630b5b20fb35c9821839883c62019'
    adapter=load('patch_fp_only.py',PATCH)
    helper=HERE/'LazyFPOnly.lean';assert hashlib.sha256(helper.read_bytes()).hexdigest()==HELPER
    adapter.BASE=hashlib.sha256(compact).hexdigest();adapter.HELPER=helper
    result=adapter.transform(compact,12,'fp-only-lazy')
    assert len(result)<=256000
    assert b'theorem correct:' not in result
    return result
