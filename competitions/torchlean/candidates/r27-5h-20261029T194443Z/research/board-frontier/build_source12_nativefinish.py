"""Owned native-finish variant of the exact source12 Winograd diagnostic.
No network, no new correct, and no source27 dependency. Previous sources stay
unchanged; exact input-output hashes distinguish this additional experiment.
"""
from __future__ import annotations
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
from pathlib import Path

HERE=Path(__file__).resolve().parent
BASE_VARIANT='c84cec61b61ef7d9d6e0744cba97c6a55837fa08ef019243a2e5915ca88082c7'

def transform(raw,submission,variant='winograd12-nativefinish'):
    assert submission==12 and variant=='winograd12-nativefinish'
    spec=importlib.util.spec_from_file_location('r27_source12_native',HERE/'build_source12_probes.py')
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    previous=m.transform(raw,12,'winograd12');assert hashlib.sha256(previous).hexdigest()==BASE_VARIANT
    source=previous.decode();marker='def linear (rows n outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :='
    assert source.count(marker)==1
    source=source.replace(marker,(HERE/'WinogradNativeFinish.lean.inc').read_text(encoding='utf-8')+'\n'+marker)
    old='act relu (R27PackedLinear.finish X W b row n col (a.low+w.low) (total a w n))'
    new='totalWords (fun hi lo => act relu (finishWords X W b row n col (a.low+w.low) hi lo)) a w n'
    assert source.count(old)==1;source=source.replace(old,new)
    result=source.encode();assert len(result)<=256000
    return result

def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    result=transform(a.source.read_bytes(),12)
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    dependencies=['build_source12_probes.py','build_packed_probe.py','PackedLinearRuntime.lean','WinogradRuntime.lean.inc','WinogradNativeFinish.lean.inc']
    r={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'UNCOMPILED_UNPROVED_NATIVE_ONLY_NO_CORRECT',
       'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),'parent_native_sha256':BASE_VARIANT,
       'builder_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
       'dependencies':{f:{'sha256':hashlib.sha256((HERE/f).read_bytes()).hexdigest(),'bytes':(HERE/f).stat().st_size}for f in dependencies},
       'change':'Keep signed128 body in native words; align into signed192 for exact bias plus YL/YD terminal; original Int finish for gaps beyond63/127; exact-zero replay retained',
       'proof_boundary':'Existing endpoint names do not prove new alignment/caller; no new correct theorem',
       'coverage':'Same normalized_mlp batch8 three-linears as winograd12; batch1/norm unchanged; no source27 fetch',
       'publication':'Owned sources and receipts only; reconstructed whole source private'}
    a.receipt.write_text(json.dumps(r,indent=2),encoding='utf-8');print(json.dumps({k:r[k]for k in['state','candidate_sha256','candidate_bytes','builder_sha256']}))

if __name__=='__main__':main()
