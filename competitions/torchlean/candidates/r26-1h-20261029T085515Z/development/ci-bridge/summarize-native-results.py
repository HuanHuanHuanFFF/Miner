"""Derive component scores from an audited full cohort; never alter raw receipts."""
from pathlib import Path
import copy, datetime, hashlib, importlib.util, json, sys

ROOT = next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
ROUND = Path(__file__).resolve().parents[2]
EVIDENCE = ROUND/'evidence/40852769757/download-988ea0459868494bb525e3d8f8795129'
AUDIT = ROUND/'verification/analysis-40852769757-final-root.json'
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
j = lambda p: json.loads(p.read_bytes())
spec = importlib.util.spec_from_file_location('r26_fixed_audit', ROUND/'verification/analyze-native-only.py')
audit_module = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = audit_module
spec.loader.exec_module(audit_module)
audit = j(AUDIT)
assert audit['status'] in {'COMPLETE_NATIVE_ONLY_DIAGNOSTIC','COMPLETE_NATIVE_ONLY_DIAGNOSTIC_POST_CUTOFF'}
comparison = audit['candidate_comparisons'][0]
assert comparison['total_pairs'] == comparison['total_checksum_pairs'] == 1800
assert comparison['total_ns_values'] == 3600
_, modules, pins = audit_module.r25_tools()
config, scoring = modules['config'], modules['scoring']
base = config.Config.load(EVIDENCE/'overall-config.toml').plan('overall')
pairs = [(j(EVIDENCE/f'fp-word-conv6-{seed}-request.json'),
          j(EVIDENCE/f'fp-word-conv6-{seed}-measurement.json')['result'])
         for seed in (26102901,26102903)]
base['strata'] = [{'environment':q['environment'],'identity':q['identity'],
                  'seed':q['seed'],'weight':0.5,'timing':q['timing']} for q,_ in pairs]
calibration_path = ROOT/'competitions/torchlean/champion-comparison.json'
calibration = j(calibration_path)
prior = {row['board']:row for row in calibration['rows']}
rows = []

def subset_score(cells):
    plan = copy.deepcopy(base)
    plan['cells'] = {c:base['cells'][c] for c in cells}
    subset = []
    for q,value in pairs:
        q, value = copy.deepcopy(q), copy.deepcopy(value)
        q['cells'] = [c for c in q['cells'] if c in cells]
        value['request_hash'] = config.measurement_hash(q)
        keep = {f"{w['id']}|{c}" for w in q['workloads'] for c in cells}
        value['repetitions'] = {k:v for k,v in value['repetitions'].items() if k in keep}
        for r in value['rounds']:
            r['cells'] = {k:v for k,v in r['cells'].items() if k in keep}
        subset.append((q,value))
    return scoring.assess(plan,subset)

for model in ['overall',*config.MODELS]:
    cells = list(base['cells']) if model == 'overall' else [c for c in base['cells'] if c.startswith(model+':')]
    score = subset_score(cells)
    if model == 'overall':
        assert score == comparison['score_vs_saved_reference']
    old = prior[model]
    estimate = old['estimated_our_time_vs_champion']
    rows.append({'board':model,'native_vs_retained':score['score'],
                 'speedup_vs_retained':1/score['score'],
                 'guard_passed_vs_retained':score['guard_passed'],
                 'gain_lower':score['gain_lower'],'outcome':score['outcome'],
                 'per_seed':[s['score'] for s in score['strata']],
                 'last_snapshot_champion':old['last_snapshot_champion'],
                 'retained_vs_champion_estimate':estimate,
                 'native_vs_champion_estimate':None if estimate is None else estimate*score['score'],
                 'native_vs_known_former2_estimate':old['our_time_vs_known_former2']*score['score']})

groups=[]
for model in config.MODELS:
    for batch in config.BATCHES[model]:
        cells=[c for c in base['cells'] if c.startswith(f'{model}:b{batch}:')]
        score=subset_score(cells)
        groups.append({'model':model,'batch':batch,'time_vs_retained':score['score'],
                       'guard_passed':score['guard_passed'],
                       'maximum_workload_cell_median':max(v for s in score['strata'] for v in s['guards'].values())})

result={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'run':40852769757,
        'source_commit':'12e6d73f5775a753d8a82d4c2f731900a74c0043',
        'candidate_sha256':comparison['candidate_source']['sha256'],
        'reference_sha256':comparison['reference']['sha256'],
        'scope':'NATIVE_ONLY_EXPLORATION_UNPROVED_GUARD_FAILED_NOT_PROMOTED',
        'audit':{'path':AUDIT.relative_to(ROOT).as_posix(),'sha256':sha(AUDIT)},
        'calibration':{'path':calibration_path.relative_to(ROOT).as_posix(),'sha256':sha(calibration_path),
                       'snapshot_utc':calibration['champion_snapshot_utc'],
                       'method':'Prior champion-time calibration multiplied by same-run native/retained score. INFERRED, not direct champion run.'},
        'component_method':'Unchanged pinned scorer over derived model/batch subsets of audited raw cohort. Workload weights, rounds, order and checksums retained; subset request hashes recomputed only in memory. Not separate official board jobs.',
        'pinned_scorer':pins,'paired_rows':1800,'checksums_matching':1800,'reported_ns_values':3600,
        'rows':rows,'batch_groups':groups,
        'adoption':{'promoted':False,'reason':'Original all-input correctness proof missing, and original 1.10 per-cell guard failed for small-batch MLP/normalized_mlp.'}}
out=ROUND/'native-summary.json'
out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'output':str(out),'rows':rows,'batches':groups},indent=2))
