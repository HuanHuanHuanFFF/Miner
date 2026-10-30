"""Reconstruct the owned native-only paired-product probe; no new correct.
Uses the same exact source27, lexical proof pruning and full terminal helper
as the packed probe. Whole reconstructed third-party source stays private.
"""
from datetime import datetime,timezone
import argparse,hashlib,json
from pathlib import Path
from build_packed_probe import transform,BASE_SHA256

TAIL='\nnamespace Submission\ndef kernels : ExactRuntime.Kernels := R27PackedExperiment.kernels\nend Submission\n'
BINDING='''
namespace R27WinogradExperiment
open ExactRuntime
def linear (rows k outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if 8 ≤ rows then R27Winograd.linear rows k outW relu X W b
  else Submission.retainedKernels.dense.linear rows k outW relu X W b
def kernels : Kernels :=
  { Submission.retainedKernels with dense := { Submission.retainedKernels.dense with linear := linear } }
end R27WinogradExperiment
namespace Submission
def kernels : ExactRuntime.Kernels := R27WinogradExperiment.kernels
end Submission
'''

def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    root=Path(__file__).resolve().parent
    packed,removed,inventory=transform(a.source.read_bytes(),root)
    text=packed.decode();assert text.endswith(TAIL)
    extra=(root/'WinogradRuntime.lean.inc').read_text(encoding='utf-8')
    result=(text[:-len(TAIL)]+'\n'+extra+'\n'+BINDING).encode()
    assert len(result)<=256000
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    r={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'UNCOMPILED_UNPROVED_NATIVE_ONLY_NO_SUBMISSION_CORRECT',
       'base_submission':27,'base_sha256':BASE_SHA256,'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
       'own_script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
       'dependencies':{name:{'sha256':hashlib.sha256((root/name).read_bytes()).hexdigest(),'bytes':(root/name).stat().st_size}
                       for name in['build_packed_probe.py','PackedLinearRuntime.lean','PackedBinding.lean.inc','WinogradRuntime.lean.inc']},
       'entry':'Submission.kernels; only rows>=8 dense.linear changed; original token GEMM/classifier retained',
       'runtime_boundary':'Metadata/factor caches/self products/cross products/128-bit corrections/strong per-output fallback/bias/terminal included',
       'limitations':['No new Submission.correct','Lexical dependency pruning still requires native compiler confirmation','Fallback loses four-row fusion; measure whole call','No current champion ratio'],
       'publication':'Owned sources/receipts only; reconstructed whole source private'}
    a.receipt.write_text(json.dumps(r,indent=2),encoding='utf-8');print(json.dumps({k:r[k]for k in['state','candidate_sha256','candidate_bytes','own_script_sha256']}))

if __name__=='__main__':main()
