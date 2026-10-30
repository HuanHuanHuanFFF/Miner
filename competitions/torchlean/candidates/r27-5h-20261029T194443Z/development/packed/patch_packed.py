"""Whole-model packed-output discriminator over public13; no new Correct claim."""
from pathlib import Path
import hashlib

HERE=Path(__file__).resolve().parent
PIN='b31043213f07768a6a75449b5ab3de732560ac40de4e9a72c31f67239e8f1970'
RUNTIME_SHA='2a416a233a96566f344477d9aa8999c96d0593f4528036f5e62af909dd75ec5b'

def transform(data,submission,variant):
    assert submission==13 and hashlib.sha256(data).hexdigest()==PIN
    assert variant in {'packed8','packed32'}
    tile=8 if variant=='packed8' else 32
    source=data.decode('utf-8')
    for old,new in [
        ('def kernels:Kernels where','def retainedKernels:Kernels where'),
        ('theorem correct:Obligation kernels:=','theorem retainedCorrect:Obligation retainedKernels:='),
        ('simp only[Obligation,kernels,','simp only[Obligation,retainedKernels,'),
    ]:
        assert source.count(old)==1,(old,source.count(old))
        source=source.replace(old,new,1)
    runtime=(HERE/'PackedLinearRuntime.lean').read_bytes()
    assert hashlib.sha256(runtime).hexdigest()==RUNTIME_SHA
    runtime=runtime.decode('utf-8')
    assert runtime.startswith('import ContractExact')
    runtime=runtime[len('import ContractExact'):]
    old='linearSpec rows k outW relu X W b'
    assert runtime.count(old)==1
    runtime=runtime.replace(old,'Submission.retainedKernels.dense.linear rows k outW relu X W b',1)
    record=f'''
namespace Submission
open ExactRuntime
def kernels : Kernels where
  core := retainedKernels.core
  dense := ⟨R27PackedLinear.linear {tile}, retainedKernels.dense.gemm⟩
  conv := retainedKernels.conv
  elem := retainedKernels.elem
  norm := retainedKernels.norm
end Submission
'''
    result=(source+'\n'+runtime+'\n'+record).encode('utf-8')
    assert len(result)<=256000
    assert 'theorem correct:Obligation kernels:=' not in result.decode('utf-8')
    return result
