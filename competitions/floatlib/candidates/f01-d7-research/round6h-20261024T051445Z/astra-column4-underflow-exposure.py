"""Only seven explicitly completed plans; source-model routing, never timing."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import re
import sys
import time
sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
ROOT = CS.parents[2]
R11 = HERE.parent/'round7h-20261023T193125Z'
RUNS = [(1224001,40067286343),(1224003,40068680108),(1224005,40071334389),
        (1224007,40072436647),(1224009,40073100983),(1224010,40073679847),(1224016,40080782614)]
sha = lambda raw: hashlib.sha256(raw).hexdigest()


def main():
    start = time.monotonic()
    deadline = start+600
    exp_path = R11/'review-output-underflow-exposure.py'
    previous = json.loads((R11/'review-output-underflow-exposure.json').read_text(encoding='utf-8'))
    assert previous['analysis_source_sha256'] == sha(exp_path.read_bytes())
    sp = importlib.util.spec_from_file_location('prior_underflow_readonly', exp_path)
    exp = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(exp)
    receipt_path = R11/'review-output-underflow-source-receipt.json'
    receipt = json.loads(receipt_path.read_text(encoding='utf-8'))
    assert receipt['official_commit'] == exp.OFFICIAL and not receipt['truncated']
    entries = {e['path']: e for e in receipt['entries']}
    lean = exp.RESEARCH/'upstream/BenchSuite.lean'
    planner = CS/'f01-d6-research/public-delta/benchmark_suite.py'
    transcription = exp.RESEARCH/'public-nonfinite-opportunity.py'
    for official, local in [('lean/bench/BenchSuite.lean', lean), ('benchmark_suite.py', planner)]:
        raw = local.read_bytes()
        assert len(raw) == entries[official]['size'] and exp.blob_id(raw) == entries[official]['sha']
    old_transcription = next(e for e in previous['sources'] if e['path'].endswith('public-nonfinite-opportunity.py'))
    assert sha(transcription.read_bytes()) == old_transcription['sha256']
    element = exp.load_generator(transcription)['element']
    make_plan = exp.load_plan_generator(planner)['make_plan']
    parent = CS/'f01-d12-scalar-combined/Kernel.lean'
    raw_parent = parent.read_bytes()
    assert sha(raw_parent) == 'df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
    assert b'R2W01b.magnitude x.raw.1 < (0x16000000 : UInt32)' in raw_parent
    assert b'A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small' in raw_parent
    totals = {k:0 for k in ['all_timed_BMM_cases','all_timed_BMM_MAC','potential_cases','potential_MAC',
        'potential_outputs','underflow_bypassed_cases','underflow_bypassed_MAC','underflow_bypassed_outputs',
        'surviving_cases','surviving_MAC','surviving_outputs','model_guard_words','potential_padding10',
        'potential_padding4','surviving_padding10','surviving_padding4']}
    results = []
    for seed, run in RUNS:
        ci = CS/'f01-mul-log2-proof1/ci-runs'/str(run)
        index_path = ci/'original-artifact-hashes.json'
        index = json.loads(index_path.read_text(encoding='utf-8'))
        base = (ci/index['directory']).resolve()
        assert base.is_relative_to(ci.resolve())
        sub = 'diagnostics/f01-d7-public-suite/public-suite/'
        evidence = {}
        for name in ['summary.json','provenance.json','public-drawn-plan.json','public-v2.json',
                     'public-cell-work.json','f01-d11-bmm-combined-classifier-verdict.json']:
            rel = sub+name
            data = (base/rel).read_bytes()
            entry = index['files'][rel]
            assert len(data) == entry['bytes'] and sha(data) == entry['sha256']
            evidence[name] = {'path': str((base/rel).relative_to(ROOT)).replace('\\','/'), 'sha256': sha(data)}
        suite = base/sub
        summary = json.loads((suite/'summary.json').read_text())
        prov = json.loads((suite/'provenance.json').read_text())
        plan = json.loads((suite/'public-drawn-plan.json').read_text())
        config = json.loads((suite/'public-v2.json').read_text())
        verdict = json.loads((suite/'f01-d11-bmm-combined-classifier-verdict.json').read_text())
        assert summary['complete'] and summary['seed'] == prov['seed'] == verdict['seed'] == seed
        assert verdict['passed'] and verdict['stage']=='score' and len(verdict['rounds'])==25
        assert prov['official_commit'] == exp.OFFICIAL
        assert prov['official_generator_sha256'] == sha(planner.read_bytes())
        assert make_plan(config, seed, 500000) == plan
        cases = [c for c in plan['cases'] if c['timed'] and c['kernel']=='bmm']
        all_mac = sum(c['work'] for c in cases)
        work = json.loads((suite/'public-cell-work.json').read_text())
        assert all_mac == sum(v for k,v in work.items() if k.startswith('bmm:'))
        rows = []
        for c in cases:
            if c['p'] not in (3,4) or c['n']<=4:
                continue
            batch,m,n,p = [c[k] for k in ['batch','m','n','p']]
            assert c['work'] == batch*m*n*p and c['work']>0
            A = exp.scan(c,0,batch*m*n,n,element,deadline)
            B = exp.scan(c,1,batch*n*p,p,element,deadline) if A['all_small'] else None
            hit = A['all_small'] and B['all_small']
            row = {'name':c['name'],'input_seed':c['seed'],'generator_case':c,
                'shape':[batch,m,n,p],'MAC':c['work'],'outputs':batch*m*p,
                'A_scan_model':A,'B_scan_model':B,'B_not_read_after_A_rejection':B is None,
                'underflow_bypass_reconstructed':hit,
                'guard_words_reconstructed':A['words_read_including_failure']+(B['words_read_including_failure'] if B else 0),
                'padding10_lane_MAC':batch*m*n*(10-p),'padding4_lane_MAC':batch*m*n*(4-p)}
            rows.append(row)
        local = {k:0 for k in totals}
        local.update(all_timed_BMM_cases=len(cases),all_timed_BMM_MAC=all_mac,potential_cases=len(rows))
        for row in rows:
            local['potential_MAC']+=row['MAC'];local['potential_outputs']+=row['outputs']
            local['model_guard_words']+=row['guard_words_reconstructed']
            local['potential_padding10']+=row['padding10_lane_MAC'];local['potential_padding4']+=row['padding4_lane_MAC']
            prefix='underflow_bypassed' if row['underflow_bypass_reconstructed'] else 'surviving'
            local[prefix+'_cases']+=1;local[prefix+'_MAC']+=row['MAC'];local[prefix+'_outputs']+=row['outputs']
            if prefix=='surviving':
                local['surviving_padding10']+=row['padding10_lane_MAC'];local['surviving_padding4']+=row['padding4_lane_MAC']
        for key in totals:totals[key]+=local[key]
        results.append({'seed':seed,'run':run,'evidence':evidence,'counts':local,'cases':rows,
            'Root_index_sha256':sha(index_path.read_bytes()),'input_plan_regenerated_exactly':True})
    rec = {'at_utc':datetime.now(timezone.utc).isoformat(),'state':'COMPLETED_SEVEN_PLAN_SOURCE_MODEL_ONLY',
        'analysis_seconds':time.monotonic()-start,'script_sha256':sha(Path(__file__).read_bytes()),
        'only_allowed_completed_runs':RUNS,'future_confirmation_inputs_read':False,
        'source_bindings':[{'path':str(p.relative_to(ROOT)).replace('\\','/'),'sha256':sha(p.read_bytes())}
            for p in [receipt_path,lean,planner,transcription,exp_path,parent]],
        'source_predicate':'magnitude(rawWord)<0x16000000 onallA thenallB, withshortcircuit; magnitude masks sign bit',
        'totals':totals,'fractions':{'bypassed_fraction_of_shape_potential_MAC':totals['underflow_bypassed_MAC']/totals['potential_MAC'],
            'shape_potential_fraction_all_BMM_MAC':totals['potential_MAC']/totals['all_timed_BMM_MAC'],
            'surviving_fraction_all_BMM_MAC':totals['surviving_MAC']/totals['all_timed_BMM_MAC']},
        'runs':results,'scope':'INFERRED deterministic reconstruction frompinnedofficial source andexactregenerated completedplans. NotLean arraydump, realbranch-eventcount, hardwaretiming, ns, allocatortrace orperformanceprediction. Negativecases stopatfirstbadword; nofull-arrayhashclaimedforunreadsuffix. B isnot reconstructedwhenA alreadyrejects.',
        'next_measurement_gap':'Beforefurtherkernelresearch, measureactualtakenbranchandper-stagewhole-calltime ondiscovery-onlyinputs withsame-sourcecontrols. Currentofficialverdictcelltotals cannotgivepercase/guard/slice ns.'}
    (HERE/'astra-column4-underflow-exposure.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'seconds':rec['analysis_seconds'],'totals':totals,'fractions':rec['fractions']},indent=2))


if __name__=='__main__':
    main()
