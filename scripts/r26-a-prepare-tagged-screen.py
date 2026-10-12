"""Prepare one original-protocol A14 paired screen only after exact native evidence is collected."""
from pathlib import Path
import argparse
import copy
import hashlib
import json

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/route-a'
NAME='r26-a-641-tagged-head'
RUST='f5350f86643ca65b955b4739165c6f04b27ef673a6e986c1614257687618e04c'

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def dump(path,obj):path.write_bytes((json.dumps(obj,indent=2)+'\n').encode())

def main():
 ap=argparse.ArgumentParser();ap.add_argument('native_receipt');ap.add_argument('--snapshot',default='evidence/round26/extension4h/official-start/pareto-pages.json');args=ap.parse_args()
 path=(ROOT/args.native_receipt).resolve();assert path.is_relative_to(ROOT);native=json.loads(path.read_bytes())
 assert native['status']=='VERIFIED_NATIVE_TAGGED_PARENT_IDENTITY_DECODE_ORACLES_AND_BOUNDARIES'
 assert native['rust_sha256']==RUST and len(native['direct'])==169 and len(native['rows'])==28 and native['helpers']
 total=native['totals'];assert total['tag_miss_skips']>0 and total['ahead_calls']>0
 entry=json.loads((OUT/'a14-tagged-entry.json').read_bytes());assert entry['hashes']['parse.rs']==RUST
 spec=json.loads((ROOT/'evidence/round26/screen-a12.json').read_bytes())
 controls=[e for e in spec['entries'] if e['name'] in ['probe3','r3-432-fast3','public432','public641','public641-shadow']]
 shadow=copy.deepcopy(entry);shadow.update(name=NAME+'-shadow',control=True)
 for key in ['native_decode_reference','expected_equivalent_to','comparison_baseline']:shadow.pop(key,None)
 spec['entries']=controls+[entry,shadow];names=[e['name']for e in spec['entries']]
 spec['screen_orders']=[names,list(reversed(names))];spec['extract_candidates']=[NAME]
 spec['snapshot_pages']=args.snapshot
 spec['description']='A14 tag8/pos24 preserved original641 parent tokens/output in28 originalencoder files,444 finite checks and169 direct cases incl2^24 fallback. Two original11rep reverseblocks with exactsame-source641/candidate controls; exactRust extraction for interface risk only. Counts not speed; no fullLean or stable5/10 claim. 35minoutercap.'
 spec['r26_required_files']={}
 declaration={'purpose':'Measure whether original-word-load rejection pays for tag/mask/branch maintenance in complete original two-axis timings.',
  'old_result':'A12 row slower about9%; A14 keeps original head/prev sequence and has exact native identity.',
  'change':'One frozen A14 representation, no additional tuning.',
  'native_receipt':path.relative_to(ROOT).as_posix(),'native_receipt_sha256':sha(path),
  'candidate_hashes':entry['hashes'],'actual_ahead_miss_fraction':total['tag_miss_skips']/total['ahead_calls'],
  'minimal_action':'Two original public28 blocks of1 warmup+11rep, reverse process order, 641 and A14 exactsource controls, one exactextraction before measurements.',
  'decision':'If total regression follows candidate and sourcecontrols, stop this exact representation. If usable total gain with no output difference, independently confirm frozen candidate and budget fullproof. If control disagreement changes target classification, retain every block and diagnose before promotion.',
  'cost_cap_minutes':35,'time_reserve':'No new direction afterUTC09:10; fullgate/independentconfirmation reserve remains. QueueUNKNOWN.',
  'limits':['Counts do not predict speed.','Two blocks in one runner are discovery, not independent confirmation.','Extraction is not fullgate.','Public projections are not formaladmission/rewards.']}
 decl=OUT/'a14-screen-predeclaration.json';assert not decl.exists();dump(decl,declaration)
 paths=[path.relative_to(ROOT).as_posix(),decl.relative_to(ROOT).as_posix(),args.snapshot,'scripts/round26-preflight.py','scripts/r26-standard-helper-checks.py','scripts/research-round5.py','scripts/r26-a-prepare-tagged-screen.py','evidence/round26/route-a/a14-predeclaration.md']
 paths += [e['path']+'/'+f for e in spec['entries']for f in ['parse.rs','Parse.lean']]
 spec['r26_required_files']={p:sha(ROOT/p)for p in paths}
 dest=OUT/'a14-screen-proposed.json';assert not dest.exists();dump(dest,spec)
 print(json.dumps({'prepared':str(dest),'hashes':entry['hashes'],'native_counts':total,'declaration':str(decl)},indent=2))

if __name__=='__main__':main()
