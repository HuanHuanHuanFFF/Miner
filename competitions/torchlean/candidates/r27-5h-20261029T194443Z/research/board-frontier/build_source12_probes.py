"""Legal source12-only native alternatives; no fetch or source27 dependency.

Shared pruning code is owned; it reads the exact source supplied by D. This
does not retry a denied source endpoint. All prototypes lack a new correct.
"""
from __future__ import annotations
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
from pathlib import Path

HERE=Path(__file__).resolve().parent
PIN="e2c1f1f1ba52e32563fb193ceea7e2a271b989fd3ba2eb16cff747987879b521"


def helper():
    spec=importlib.util.spec_from_file_location('r27_c_owned_pruning',HERE/'build_packed_probe.py')
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m


def build(raw,variant):
    assert hashlib.sha256(raw).hexdigest()==PIN
    assert variant in ['packed12','winograd12','control12']
    m=helper();old=raw.decode();source,removed=m.prune(old)
    inventory=m.runtime_inventory(old)
    assert inventory==m.runtime_inventory(source)
    if variant!='control12':
        assert source.count('def kernels:Kernels where')==1
        source=source.replace('def kernels:Kernels where','def retainedKernels:Kernels where')
        runtime=(HERE/'PackedLinearRuntime.lean').read_text(encoding='utf-8')
        assert runtime.startswith('import ContractExact\n')
        source+='\n'+runtime.removeprefix('import ContractExact\n')
        implementation='R27PackedLinear.linear 16'
        if variant=='winograd12':
            source+='\n'+(HERE/'WinogradRuntime.lean.inc').read_text(encoding='utf-8')
            implementation='R27Winograd.linear'
        source+='''
namespace R27Source12Experiment
open ExactRuntime
def linear (rows k outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if 8 ≤ rows then '''+implementation+''' rows k outW relu X W b
  else Submission.retainedKernels.dense.linear rows k outW relu X W b
def kernels : Kernels :=
  { Submission.retainedKernels with dense := { Submission.retainedKernels.dense with linear := linear } }
end R27Source12Experiment
namespace Submission
def kernels : ExactRuntime.Kernels := R27Source12Experiment.kernels
end Submission
'''
    result=source.encode()
    assert len(result)<=256000
    assert [l for l in source.splitlines()if l.startswith('import ')]==['import ContractExact']
    return result,removed,inventory


def transform(raw,submission,variant):
    assert submission==12
    return build(raw,variant)[0]


def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);p.add_argument('--variant',choices=['packed12','winograd12','control12'],required=True);a=p.parse_args()
    result,removed,inventory=build(a.source.read_bytes(),a.variant)
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    r={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'UNCOMPILED_UNPROVED_NATIVE_ONLY_NO_CORRECT',
       'variant':a.variant,'base_submission':12,'base_sha256':PIN,'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
       'builder_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
       'dependencies':{name:{'sha256':hashlib.sha256((HERE/name).read_bytes()).hexdigest(),'bytes':(HERE/name).stat().st_size}
            for name in['build_packed_probe.py','PackedLinearRuntime.lean','WinogradRuntime.lean.inc']},
       'removed_proofs':len(removed),'runtime_definition_inventory':inventory,
       'coverage':'normalized_mlp: all3 dense.linear calls at batch8; batch1 unchanged; RMS/layernorm unchanged',
       'comparison':'Source12 strong predecessor internal cost only; current23 ratio UNKNOWN pending policy/config reconciliation',
       'network':'No network code in this builder; caller supplies exact source12, never source27',
       'publication':'Owned builder/runtime/metadata only; whole reconstructed source private'}
    a.receipt.write_text(json.dumps(r,indent=2),encoding='utf-8');print(json.dumps({k:r[k]for k in['state','variant','candidate_sha256','candidate_bytes','builder_sha256']}))


if __name__=='__main__':main()
