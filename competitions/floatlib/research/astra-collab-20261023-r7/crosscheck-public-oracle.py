from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[3]
ap=argparse.ArgumentParser();ap.add_argument('--analysis',required=True);ap.add_argument('--diagnostic',required=True);ap.add_argument('--output',required=True);args=ap.parse_args()
p=HERE/args.analysis;apath=ROOT/args.diagnostic
s=json.loads(p.read_text());a=json.loads(apath.read_text());bad=[];checks=0
for r in s['cases']:
    for proc in a['measurements']:
        actual=proc['benchmark_rows'][r['name']]['checksum'];checks+=1
        if actual!=r['checksum32']:bad.append({'case':r['name'],'process':proc['process'],'derived':r['checksum32'],'actual':actual})
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'status':'PASS_ACTUAL_DIAGNOSTIC_CHECKSUM_CROSSCHECK' if not bad else 'FAIL_TRANSCRIPTION_OR_MODEL','checks':checks,'cases':len(s['cases']),'mismatches':bad,'analysis_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'diagnostic_sha256':hashlib.sha256(apath.read_bytes()).hexdigest(),'control_agreement_reported':a['checksum_matches_control'],'source_plan_sha256':s['plan_sha256'],'scope':'Derived source-generator/integer oracle output words compared to actual pinned-Lean full-vector rolling checksums from D diagnostic; finite collision-prone checksum agreement, not a proof or timing claim. No official gate modified.'}
target=HERE/args.output;assert target.resolve().is_relative_to(HERE.resolve());target.write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
