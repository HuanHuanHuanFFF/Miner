"""Pointwise128 v2: store bounded per-pixel scales as small Nat, avoiding UInt64 boxes.

This supersedes the unmeasured v1 pointwise prototype for selection; it is not an
extra requested timing variant and remains native-only without a correct root.
"""
from pathlib import Path
import hashlib,importlib.util,json,datetime,argparse
HERE=Path(__file__).resolve().parent
BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
PARENT=HERE/'build_pointwise128.py'
PARENT_SHA='f7fa680092dcea381efb8c78324880a38e21554238e51e37a5e37172707449f4'
def transform(raw,submission,variant):
    assert submission==53 and variant=='pointwise128-nat'
    assert hashlib.sha256(PARENT.read_bytes()).hexdigest()==PARENT_SHA
    spec=importlib.util.spec_from_file_location('r28pointnat',PARENT);p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
    s=p.HELPER
    edits=[
      ('ms:Array UInt64','ms:Array Nat',2),
      ('ms[p.toNat]!','(ms[p.toNat]!).toUInt64',1),
      ('let MS:=BX.map (fun v=>min (Yk (v>>>16)) cap)','let MS:=BX.map (fun v=>(min (Yk (v>>>16)) cap).toNat)',1),
      ('let width:Nat:=(mhi-mlo+1).toNat','let width:Nat:=mhi-mlo+1',1),
      ('let mm:=mlo+(z.val%width).toUInt64','let mm:=(mlo+z.val%width).toUInt64',1),
      ('let mm:=MS[p]!','let mm:=(MS[p]!).toUInt64',1),
      ('(mm-mlo).toNat','(MS[p]!-mlo)',2),
    ]
    for before,after,count in edits:
      assert s.count(before)==count,(before,s.count(before));s=s.replace(before,after)
    p.HELPER=s
    return p.transform(raw,53,'pointwise128')
def main():
    pa=argparse.ArgumentParser();pa.add_argument('--base',type=Path,default=BASE);a=pa.parse_args();data=transform(a.base.read_bytes(),53,'pointwise128-nat')
    out=HERE/'private/pointwise128-nat53.lean';out.write_bytes(data)
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'variant':'pointwise128-nat','candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'dependencies':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in [PARENT,HERE/'build_channel128.py',HERE.parent/'source-budget/compact53.py']},'base_sha256':hashlib.sha256(a.base.read_bytes()).hexdigest(),'proof_state':'UNPROVED_NATIVE_RESEARCH_ONLY; no new correct root','change_from_v1':'Only per-pixel MS payload and associated cache indices use Nat; existing scale values are bounded by510. No arithmetic domain or sparse/fallback change. All511 possible scale values roundtrip UInt64->Nat->UInt64 exactly in finite check.','runtime_claim':'Potential boxing reduction inferred from Lean value representation; generated C/native cost not observed.'}
    assert all((n&((1<<64)-1))==n for n in range(511))
    (HERE/'pointwise128-nat-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n');print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
