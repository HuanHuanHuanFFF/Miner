"""Read-only independent acceptance audit after D declared standard9 complete."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,math,statistics
HERE=Path(__file__).resolve().parent;ROUND=HERE.parent.parent
RAW=ROUND/'evidence/40972962791/download-a0c91db6885947d89d15a80b7020aaf2'
SHA='6fe5feb6cf0b919a9700f5f05264b1e98e24d7ee74b9d2853c1e55be866d4ada';REF='f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67';FP='3a69968c7210ab18b325047e518ddfa942e642e21268a241e8693b075377bee6'
def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
 source=HERE/'private/gemm27-public23-all-positive/Kernel.lean';assert digest(source)==SHA and source.stat().st_size==252719
 summary=json.loads((RAW/'summary.json').read_bytes());assert summary['complete']and summary['originals_unchanged'];assert summary['run_id']=='40972962791'
 verdict_path=RAW/'public23-gemm27-all-positive-k/full-gate-verdict.json';v=json.loads(verdict_path.read_bytes());assert v['passed']and v['stage']=='axioms'and v['verifier_fingerprint']==v['verifier_fingerprint_end']==FP
 log=RAW/'public23-gemm27-all-positive-k-full-gate.log';text=log.read_text();assert 'Submission replays cleanly'in text and'VerifyExact replays cleanly'in text and"['Classical.choice', 'Quot.sound', 'propext']"in text
 rows=[];scores=[];counts={'pairs':0,'ns_values':0,'checksum_pairs':0};binaries=set()
 for m in sorted(RAW.glob('*measurement.json')):
  d=json.loads(m.read_bytes())['result'];req=json.loads(m.with_name(m.name.replace('-measurement.json','-request.json')).read_bytes());assert req['candidate_hash']==SHA and req['reference_hash']==REF;assert req['timing']['rounds']==11 and req['timing']['inner']==3 and req['timing']['cell_ms']==50
  assert len(d['rounds'])==11 and len(d['workloads'])==6
  bywork={w['id']:[]for w in d['workloads']}
  for rr in d['rounds']:
   assert len(rr['cells'])==36
   for name,c in rr['cells'].items():
    assert c['reference_ns']>0 and c['candidate_ns']>0 and c['reference_checksum']==c['candidate_checksum'];counts['pairs']+=1;counts['ns_values']+=2;counts['checksum_pairs']+=1
   for w in bywork:
    vals=[math.log(c['candidate_ns']/c['reference_ns'])for k,c in rr['cells'].items()if k.startswith(w+'|')];assert len(vals)==6;bywork[w].append(math.exp(sum(vals)/len(vals)))
  score=math.exp(sum(w['weight']*math.log(statistics.median(bywork[w['id']]))for w in d['workloads']));scores.append(score);binaries.add((d['provenance']['candidate_binary'],d['provenance']['reference_binary']))
  rows.append({'measurement_sha256':digest(m),'request_sha256':digest(m.with_name(m.name.replace('-measurement.json','-request.json'))),'pairs':396,'score_internal':score})
 assert len(rows)==2 and len(binaries)==1 and counts=={'pairs':792,'ns_values':1584,'checksum_pairs':792}
 score=math.exp(sum(map(math.log,scores))/2);D=json.loads((ROUND/'CI-RESULTS-BATCH9.json').read_bytes());reported=D['results'][0]['score_vs_calibration_internal']['score'];assert abs(score-reported)<1e-12,(score,reported)
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'ACTUAL_ALL12_PASS_STANDARD_PERFORMANCE_REJECTED','run':40972962791,'source_commit':summary['source_commit'],'candidate_sha256':SHA,'candidate_bytes':252719,'proof_fingerprint':FP,'gate_seconds':v['seconds'],'gate_log_sha256':digest(log),'gate_verdict_sha256':digest(verdict_path),'original_source_protection':True,'original_gate_checked':['statement','Submissionleanchecker','VerifyExactleanchecker','allowedaxioms'],'sample_counts':counts,'standard_timing':{'rounds':11,'inner':3,'cell_ms':50},'measurement_receipts':rows,'independent_point_score_over_retired27':score,'current36_report_chain_estimate':D['results'][0]['candidate_time_over_current_champion_estimate'],'current36_measurement':'INFERRED_CROSS_ENV_REPORT_CHAIN; direct sourcewithheld','D_standard_admission_outcome':D['results'][0]['score_vs_calibration_internal']['outcome'],'D_standard_guard':D['results'][0]['score_vs_calibration_internal']['guard_passed'],'current_champion_achieved':False,'proof_only_compactor':'Partofthisactualgateaccepted source; no standalonefc7gateclaim','barrier':'Read onlyafterDdeclaredstandard9complete. Roots/cohort nowSEEN; nofuturecandidateuseasfreshconfirmation. No changes to frozen9.','limits':['One x86runner; no ARM confirmation','No officialpromotion/formalsubmission','No percellselection ordiscard; rawslowcasesretained']};(HERE/'gemm9-verified-result.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps(out))
if __name__=='__main__':main()
