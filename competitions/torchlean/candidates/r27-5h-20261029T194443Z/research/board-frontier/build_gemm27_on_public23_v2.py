"""Coverage repair for the structural GEMM graft after replacing the unavailable small-k engine."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
BASE_RECIPE_SHA='a920b7ab2545ad4e7eb4f009b29c5a78da2ae0fa9f41415c9546e0f679049736'
BASE_OUTPUT_SHA='cdf2ca27692156246c66cd5b2217e407f8f22fe0ec404e4c60b96cfa0ce72434'
def transform(raw,submission=23,variant='gemm27-all-positive-k',donor_raw=None):
 assert submission==23 and variant=='gemm27-all-positive-k'
 path=HERE/'build_gemm27_on_public23.py';assert hashlib.sha256(path.read_bytes()).hexdigest()==BASE_RECIPE_SHA
 spec=importlib.util.spec_from_file_location('r27_gemm_base',path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
 old=m.transform(raw,23,'gemm27-public23',donor_raw);assert hashlib.sha256(old).hexdigest()==BASE_OUTPUT_SHA
 s=old.decode();assert s.count('if k<20||!(A.all finiteWord&&B.all finiteWord)')==1
 # Original threshold20 selected between twooptimizedruntimes. Thegraft lacksYa3.
 # ExistingGsn proof requiresonlypositivek, hence linearreusecanserveallk>=1.
 s=s.replace('if k<20||!(A.all finiteWord&&B.all finiteWord)','if k<1||!(A.all finiteWord&&B.all finiteWord)')
 return s.encode()
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--donor',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args();r=transform(a.source.read_bytes(),donor_raw=a.donor.read_bytes());a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(r)
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'FULL12_STRUCTURAL_GRAFT_COVERAGE_REPAIR_NOT_COMPILED','candidate_sha256':hashlib.sha256(r).hexdigest(),'candidate_bytes':len(r),'free_bytes':256000-len(r),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'base_recipe_sha256':BASE_RECIPE_SHA,'preserved_old_candidate':BASE_OUTPUT_SHA,'change':'Useexistinglinear-as-GEMM for allpositivek, keepingk0/nonfinitegemmWithYn fallback. ExistingGsn obligationonlyk>0; no newarithmeticproof.','reason':'PinnedtypicalT8..16 andboundaryT9..17 wouldall fallthrougholdthreshold20; donorYa3+proofmissingclosure7496B cannotfit3280Bfree. Thisrepairslostoptimizedfallbackcoverage, not a secondalgorithm or confirmationdata tuning.','correctness':'Completecorrectstillconnected; newexactsourceoriginalgatepending','comparison':'CurrentMixer36 only; wholeModel cost UNKNOWN'};a.receipt.write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps(out))
