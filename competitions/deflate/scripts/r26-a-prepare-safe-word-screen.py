"""Freeze the exact A19 native-checked source and one original total-cost screen."""
from pathlib import Path
import hashlib
import importlib
import json

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/route-a'
NAME='r26-a-658-safe-word-offsets'
DIAG=importlib.import_module('r26-a-common-wrapping-lowering')

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def dump(p,obj):p.write_bytes((json.dumps(obj,indent=2)+'\n').encode())

def main():
 rp=ROOT/'evidence/round26/38223589692/observe-a19-native/diagnostics/r26-a-common-lowering/receipt.json';receipt=json.loads(rp.read_bytes())
 assert receipt['status']=='VERIFIED_OFFICIAL_FLAGS_SAFE_WORD_SUM_LOWERING_AND_FINITE_EQUALITY'and receipt['helper_cases']==1548 and len(receipt['rows'])==28
 raw=DIAG.variant(DIAG.BASE.read_bytes());digest=hashlib.sha256(raw).hexdigest();assert digest==receipt['preflight']['variant_sha256']=='10b2e02e230df8a2225e94db15a50eadf2d5d2abaabfa193936e885dd97a8e64'
 assert raw==(rp.parent/'safe_wrapping_words-parse.rs').read_bytes()
 parent=ROOT/'references/round26-public-658';lean=(parent/'Parse.lean').read_bytes();p=ROOT/'candidates'/NAME;assert not p.exists();p.mkdir();(p/'parse.rs').write_bytes(raw);(p/'Parse.lean').write_bytes(lean)
 hashes={'parse.rs':sha(p/'parse.rs'),'Parse.lean':sha(p/'Parse.lean')}
 dump(p/'manifest.json',{'candidate':NAME,'parent':'references/round26-public-658','hashes':hashes,'attribution':{'receipt':'references/round26-public-658/source-receipt.json','author_hotkey':'5G3YLL7PuDhRBoVoDBYKhAfTxFM4EouSDiYuFXeeWciNRzyK'},
  'mechanism':'Only a+k and b+k in u118_common wordloop changed to wrapping_add under existingcaller bounds. No be8, byte-tail, lastlink, windowfilter, searchbudget orrouting change.',
  'native_evidence':rp.relative_to(ROOT).as_posix(),'native_evidence_sha256':sha(rp),'helper_cases':1548,'public_exact_parent_tokens_decode':28,
  'lowering_evidence':'Officialflags/shim: row2asmunchangedexceptpaniclocationlabels. Row9mainwordloop unchanged28opcodes, bothalready64bitloads; row9lazywordloop removesonecomparison/branch, remainingbe8overflowcheckretained. Register/stackallocation changeselsewhere.',
  'proof_status':'ParentLean copied; fresh exactextract/fullgate NOT_RUN. Native equality notfullproof.','performance':'UNKNOWN_PENDING_ONE_ORIGINAL_PROTOCOL_SCREEN','formal_submission_sent':False})
 spec=json.loads((ROOT/'evidence/round26/screen-a14.json').read_bytes());spec['entries']=[e for e in spec['entries']if e['name']in ['probe3','r3-432-fast3','public432']]
 ref={'name':'public658','path':parent.relative_to(ROOT).as_posix(),'control':True,'anchor':'public658','formal_id':'658','hashes':{'parse.rs':sha(parent/'parse.rs'),'Parse.lean':sha(parent/'Parse.lean')}}
 shadow=json.loads(json.dumps(ref));shadow['name']='public658-shadow';shadow.pop('formal_id')
 entry={'name':NAME,'path':p.relative_to(ROOT).as_posix(),'control':False,'hashes':hashes,'anchor':'public658','comparison_baseline':'public658','native_decode_reference':'public658','expected_equivalent_to':'public658'}
 twin={'name':NAME+'-shadow','path':entry['path'],'control':True,'hashes':hashes,'anchor':'public658'}
 spec['entries'] += [ref,shadow,entry,twin];names=[e['name']for e in spec['entries']];spec['screen_orders']=[names,names[::-1]];spec['extract_candidates']=[NAME]
 spec['description']='A19 exactsafe wordoffsets only. Officialflag lowering removedone row9lazy compare/branch; row2and mainwordloop didnotimprove, bothalready64bitloads.28exactparenttokens+1548helperspassed. One2-blockoriginal11rep totalscreen with parent658/candidate duplicate controls, precedingexactRust extraction. Small signalnotgoalclosure; nofullgateunlessuseful realnetgain.'
 paths=[rp.relative_to(ROOT).as_posix(),(rp.parent/'safe_wrapping_words-parse.rs').relative_to(ROOT).as_posix(),'scripts/r26-a-prepare-safe-word-screen.py','scripts/r26-a-common-wrapping-lowering.py','scripts/r26-a-lastlink-lowering.py','scripts/r26-a-rep-shadow.py','scripts/round26-preflight.py','scripts/r26-standard-helper-checks.py','scripts/research-round5.py','evidence/round26/route-a/a19-screen-predeclaration.md',spec['snapshot_pages']]
 paths += [e['path']+'/'+f for e in spec['entries']for f in ['parse.rs','Parse.lean']]
 spec['r26_required_files']={f:sha(ROOT/f)for f in paths};dump(OUT/'a19-screen-proposed.json',spec);dump(OUT/'a19-candidate-build.json',{'status':'VERIFIED_EXACT_NATIVE_SCRATCH_TO_PRODUCTION_BYTES_NO_NEW_CHANGE','hashes':hashes,'raw_diagnostic_source_sha256':sha(rp.parent/'safe_wrapping_words-parse.rs'),'native_receipt_sha256':sha(rp),'full_gate':'NOT_RUN','paired_time':'NOT_RUN'});print(json.dumps({'candidate':NAME,'hashes':hashes},indent=2))

if __name__=='__main__':main()
