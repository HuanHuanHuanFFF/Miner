"""Cost-only comparison of block carry savings and original four-row reuse."""
from pathlib import Path
import hashlib,importlib.util
HERE=Path(__file__).resolve().parent
def transform(data,submission=23,variant='block16-allrows'):
    assert submission==23 and variant=='block16-allrows'
    p=HERE/'public23_block16_cost_v2.py'
    assert hashlib.sha256(p.read_bytes()).hexdigest()=='6526074aca3afa91f13720b4b1f1fa9b32b416f8dcb2ac1d19c6a48a304463dc'
    sp=importlib.util.spec_from_file_location('r27_frozen_block16_base',p)
    m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    raw=m.transform(data,23,'prepared-block16-unrolled-native-cost-v2')
    assert raw.count(b' if rows=1 then\n')==1
    result=raw.replace(b' if rows=1 then\n',b' if rows<65536 then\n',1)
    assert len(result)<=256000 and b'theorem correct:' not in result
    return result
