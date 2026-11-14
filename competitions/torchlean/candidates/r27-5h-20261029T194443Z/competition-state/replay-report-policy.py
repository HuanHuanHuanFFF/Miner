"""Reconstruct production report plan hashes from pinned code and public fields."""
from pathlib import Path
import copy, datetime, hashlib, importlib.util, json, sys

sys.dont_write_bytecode=True
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
ROUND=Path(__file__).resolve().parents[1]
load=ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py'
sp=importlib.util.spec_from_file_location('r27_policy_pins',load)
module=importlib.util.module_from_spec(sp);sp.loader.exec_module(module)
_,modules,pins=module.r25_tools();config=modules['config']
local=ROUND/'evidence/40945451009/download-b99ae08657c2480f99ece8b5894ffd2f/overall-config.toml'
template=config.Config.load(local).plan('mixer')
boards=json.loads((ROUND/'competition-state/boards.raw').read_bytes())['boards']
targets={'mlp':33,'mixer':36,'resnet':11,'overall':8,'mobilenet':7,'normalized_mlp':23}
initial='9b2d940338dfcc42a38443324d63041a27cc9b5df1b18675103c7d67934d1df8'
rows=[]
for board in boards:
    name=board['id'];submission=targets[name]
    report=json.loads((ROUND/f'competition-state/submission{submission}-report.raw').read_bytes())
    evaluation=next(x for x in report['evaluations'] if x['board']==name and x['state']=='completed')
    plan=copy.deepcopy(template);plan.update(board=name,initial_reference=initial,seed_mode='fresh')
    plan['cells']={f'{model}:b{batch}:{kind}':weight/6 for model,weight in board['models'].items() for batch in config.BATCHES[model] for kind in config.KINDS}
    plan['timing']=config.DEFAULT_TIMING|{'benchmark_seconds':360 if len(board['models'])==1 else 1200}
    plan['strata']=[]
    for env in board['environments']:
        st={'environment':env['id'],'identity':env['identity'],'seed':0,'weight':env['weight']}
        architecture='amd64' if env['id']=='prod-amd64' else 'arm64'
        resolved=plan['timing']|config.build_defaults(architecture)
        if resolved!=plan['timing']:st['timing']=resolved
        plan['strata'].append(st)
    assert plan['cells']==evaluation['cells'] and plan['timing']==evaluation['timing']
    assert plan['admission']==evaluation['admission_policy']
    digest=config.digest(plan);assert digest==evaluation['config_hash'],(name,digest,evaluation['config_hash'])
    negative=copy.deepcopy(plan);negative['strata'][0]['timing']['build_seconds']+=1
    assert config.digest(negative)!=evaluation['config_hash']
    rows.append({'board':name,'current_submission':submission,'reconstructed_report_config_hash':digest,
                 'expected_report_config_hash':evaluation['config_hash'],'matches':True,
                 'negative_control_one_build_limit_change':'REJECTED',
                 'live_board_config_hash':board['config_hash'],'live_hash_reproduced':digest==board['config_hash'],
                 'report_plan':plan,'actual_evaluation_reference_hash':evaluation['reference_hash']})
result={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'ALL_SIX_EXACT_REPORT_POLICY_HASHES_RECONSTRUCTED',
        'method':'Pinned Config.plan schema/default timings/fingerprints, public board cells+environment identities/weights, fresh placeholder seed0. Initial reference remains fixed independently of the changing evaluation reference.',
        'pinned_config':pins['config.py'],'initial_reference_role':'Configuration identity only; no new shipped performance measurement.',
        'finding':'AMD64 default build300/cached120 differs from global ARM64 build960/cached180; this resolved per-environment timing is part of the original plan digest.',
        'limits':'Live boards API hash uses an unreproduced representation. This does not turn a local quick screen into a direct current-source comparison, production result, or official promotion.',
        'rows':rows}
out=ROUND/'competition-state/exact-report-policy-replay.json'
out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'status':result['status'],'matched':len(rows),'live_hashes_matched':sum(x['live_hash_reproduced'] for x in rows)}))
