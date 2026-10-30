"""Fresh source/receipt/point-score verification for exact D-owned batch3.
Does not rerun Lean locally or replace Dverify's pinned-scorer/CI audit.
"""
from __future__ import annotations
from datetime import datetime,timezone
import hashlib,json,math,statistics,tomllib
from pathlib import Path

HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
RAW=ROUND/'evidence/40952423982/download-c05e7f6758db41928bb591db9b6e5e90'
PIN='dced7848655a50a136750c1837b46f084a25ec26d13df72fe907d4a162bf1cb9'

def read(path):return json.loads(path.read_text(encoding='utf-8-sig'))
def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    source=HERE/'private/norm-guard26-v2/Kernel.lean';assert digest(source)==PIN
    summary=read(RAW/'summary.json');assert summary['run_id']=='40952423982'
    assert summary['source_commit']=='c6999b16ac9e24ddf64abc48ec040edcd3152b86'
    gate=next(g for g in summary['full_gates']if g['name']=='public12-guard26-v2')
    verdict=read(RAW/'public12-guard26-v2/full-gate-verdict.json')
    assert gate['source_sha256']==PIN and gate['exit_code']==0 and gate['verdict']==verdict
    assert verdict['stage']=='axioms' and verdict['passed'] and not verdict['exhausted']
    assert verdict['verifier_fingerprint']==verdict['verifier_fingerprint_end']
    log=(RAW/'public12-guard26-v2-full-gate.log').read_text()
    assert 'Submission replays cleanly' in log and 'VerifyExact replays cleanly' in log
    assert "['Classical.choice', 'Quot.sound', 'propext']" in log
    candidate=next(x for x in summary['results']if x['name']=='public12-guard26-v2')
    ref=next(x for x in summary['results']if x['name']=='calibration')
    assert candidate['source_sha256']==PIN and candidate['flags_pass']
    assert candidate['proof_state']=='FULL_ORIGINAL_GATE_REPLAYED'
    config=tomllib.loads((RAW/'overall-config.toml').read_text())
    assert config['timing']=={'rounds':5,'inner':3,'cell_ms':2,'run_seconds':300}
    assert config['boards']['normalized_mlp']['models']=={'normalized_mlp':1.0}
    assert config['boards']['normalized_mlp']['reference']['sha256']==ref['source_sha256']
    per_seed=[];total_rows=0;guard_max=0;files=[]
    for seed in[27102921,27102923]:
        p=RAW/f'public12-guard26-v2-{seed}-measurement.json';j=read(p)['result'];files.append({'path':str(p.relative_to(ROUND)),'sha256':digest(p)})
        assert len(j['rounds'])==5 and len(j['workloads'])==6
        assert j['provenance']['candidate_binary']==candidate['binary_sha256']
        assert j['provenance']['reference_binary']==ref['binary_sha256']
        cell_ratios={};weighted=0
        for r in j['rounds']:
            assert len(r['cells'])==36
            for name,c in r['cells'].items():
                assert c['candidate_ns']>0 and c['reference_ns']>0
                assert c['candidate_checksum']==c['reference_checksum']
                cell_ratios.setdefault(name,[]).append(c['candidate_ns']/c['reference_ns'])
                total_rows+=1
        for w in j['workloads']:
            # Original reducer order: geometric mean across a workload's cells
            # in each round, median across rounds, then workload-weighted GM.
            round_logs=[]
            for r in j['rounds']:
                vals=[c['candidate_ns']/c['reference_ns']for name,c in r['cells'].items()if name.startswith(w['id']+'|')]
                assert len(vals)==6
                round_logs.append(sum(map(math.log,vals))/len(vals))
            weighted+=w['weight']*statistics.median(round_logs)
        score=math.exp(weighted);per_seed.append(score)
        guard_max=max(guard_max,max(map(statistics.median,cell_ratios.values())))
    combined=math.exp(sum(map(math.log,per_seed))/len(per_seed))
    audit_path=ROUND/'verification/audit-native-40952423982.json';audit=read(audit_path)
    fixed=next(x for x in audit['results']if x['candidate']=='public12-guard26-v2')
    assert abs(combined-fixed['score_vs_calibration_internal']['score'])<1e-14
    assert guard_max<=config['admission']['guard']
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'FRESH_RECEIPT_AUDIT_PASS',
      'run':40952423982,'source_commit':summary['source_commit'],'candidate_sha256':PIN,'candidate_bytes':source.stat().st_size,
      'actual_original_all12_gate':'PASS_FROM_EXACT_CI_LOG_VERDICT_AND_SOURCE_BINDING','verifier_fingerprint':verdict['verifier_fingerprint'],
      'full_gate_seconds':verdict['seconds'],'gate_log_sha256':digest(RAW/'public12-guard26-v2-full-gate.log'),
      'verdict_sha256':digest(RAW/'public12-guard26-v2/full-gate-verdict.json'),
      'timing_scope':'EXPLORATORY_QUICK5_INNER3_CELL2MS_SINGLE_X86_RUNNER_NOT_FRESH_CONFIRMATION',
      'paired_rows':total_rows,'ns_values':2*total_rows,'matching_checksum_pairs':total_rows,
      'point_ratio_vs_exact_predecessor12_internal':combined,'per_seed':per_seed,'maximum_cell_median_ratio':guard_max,
      'current_champion_ratio':'UNKNOWN_CONFIG_POLICY_RECONCILIATION_PENDING','official_qualification':'NOT_ESTABLISHED',
      'point_reducer_note':'Median of workload-round geomeans, not geomean of per-cell medians; the latter would give0.9879804905151399.',
      'independent_fixed_audit':{'path':str(audit_path.relative_to(ROUND)),'sha256':digest(audit_path)},'measurement_files':files,
      'metadata_correction':'Fixed audit eligibility text says NO_ORIGINAL_FULL_GATE_REPLAY despite its candidate_proof/full_gate entries passing. Actual12 gate passed; formal eligibility is unestablished for other reasons.',
      'limits':['No local Lean/native rerun; D owns original CI','No formal submission/ranking','No new proof for packed/Winograd carriers','Do not convert cross-config chain into verified current ratio']}
    (HERE/'guard26-v2-verified-result.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
    print(json.dumps(result))

if __name__=='__main__':main()
