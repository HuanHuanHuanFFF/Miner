"""Proof-pruning control for the R27 native-only experiment.
All runtime declaration bytes are verified unchanged against exact source27.
No complete correctness theorem remains; never label this a full-gate pass.
"""
from datetime import datetime,timezone
import argparse,hashlib,json
from pathlib import Path
from build_packed_probe import BASE_SHA256,prune,runtime_inventory

def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    raw=a.source.read_bytes();assert hashlib.sha256(raw).hexdigest()==BASE_SHA256
    old=raw.decode();new,removed=prune(old)
    assert runtime_inventory(old)==runtime_inventory(new)
    result=new.encode();assert len(result)<=256000
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    r={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'UNCOMPILED_NATIVE_ONLY_PRUNING_CONTROL_NO_CORRECT',
       'base_sha256':BASE_SHA256,'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
       'own_script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
       'pruning_script_sha256':hashlib.sha256(Path(__file__).with_name('build_packed_probe.py').read_bytes()).hexdigest(),
       'removed_proofs':len(removed),'runtime_definition_bytes_equal':True,
       'scope':'Control to test compiler/layout effect of removing erased proofs; source equality is not measured time equality'}
    a.receipt.write_text(json.dumps(r,indent=2),encoding='utf-8');print(json.dumps(r))

if __name__=='__main__':main()
