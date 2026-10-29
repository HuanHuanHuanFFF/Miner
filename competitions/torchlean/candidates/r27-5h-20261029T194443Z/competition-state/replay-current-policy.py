"""Reconcile current board fingerprints without modifying historical evidence."""
from pathlib import Path
import copy, datetime, importlib.util, json, sys
sys.dont_write_bytecode=True
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
HERE=Path(__file__).resolve().parent
sp=importlib.util.spec_from_file_location('r27_frozen_policy',ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py')
m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
_,modules,pins=m.r25_tools();cfg=modules['config']
history=json.loads((HERE/'exact-report-policy-replay.json').read_bytes())
live={x['id']:x for x in json.loads((HERE/'boards-2150.raw').read_bytes())['boards']}
benchmark='6df065ba88f41fef36907eae008f839e5ffd7c0bb408a242daebafcaf3faa5cd'
rows=[]
for old in history['rows']:
    board=old['board'];plan=copy.deepcopy(old['report_plan'])
    plan['benchmark_identity']=benchmark
    digest=cfg.digest(plan)
    assert digest==live[board]['config_hash'],(board,digest,live[board]['config_hash'])
    negative=copy.deepcopy(plan);negative['benchmark_identity']=old['report_plan']['benchmark_identity']
    assert cfg.digest(negative)!=digest
    rows.append({'board':board,'current_config_hash':digest,'matches_live':True,
                 'only_changed_field':'benchmark_identity','historical_hash':cfg.digest(negative),
                 'negative_control_old_benchmark':'REJECTED','plan':plan})
report=json.loads((HERE/'submission43-report.raw').read_bytes())
norm=next(x for x in report['evaluations'] if x['board']=='normalized_mlp' and x['state']=='completed')
assert norm['config_hash']==next(x['current_config_hash'] for x in rows if x['board']=='normalized_mlp')
result={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'ALL_SIX_LIVE_BOARD_HASHES_AND_NEW43_REPORT_REPRODUCED',
        'official_commit':'27fb1d19c712ead50ad34b4ad0d4ba597161e616','rows':rows,
        'finding':'Deadline attribution fix changes benchmark fingerprint only; proof identity/contracts and all other plan fields unchanged.',
        'boundary':'Policy reconstruction closes configuration mismatch only. Current-source runtime and production ranking remain unmeasured.'}
(HERE/'current-policy-replay.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'status':result['status'],'matched':len(rows),'new43_report_matched':True}))
