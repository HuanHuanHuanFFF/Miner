"""Completed df5c samples only: scored cell costs and a NOT_PROVED route model."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import sys
import time
sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
ROOT = CS.parents[2]
RUNS = [(1224011,40074431355),(1224012,40076675251),(1224014,40078982864),
        (1224016,40080782614),(1224091,40083425886),(1224092,40083571000)]
CANDIDATE = 'f01-d12-scalar-combined'
EXPECTED = 'df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
sha = lambda data: hashlib.sha256(data).hexdigest()


def scan(c, role, length, width, limit, element, deadline):
    digest = hashlib.sha256()
    maximum = 0
    for i in range(length):
        if i % 8192 == 0:
            assert time.monotonic() < deadline
        word = element(c,i,role,width)
        digest.update(word.to_bytes(4,'little'))
        exponent = (word>>23)&255
        maximum = max(maximum,exponent)
        if exponent > limit:
            return {'passed':False,'max_raw_exp_in_scanned_prefix':maximum,'full_max_raw_exp':'UNKNOWN_UNREAD_SUFFIX',
                'words_read':i+1,'total_words':length,'first_reject_index':i,'first_reject_word':f'{word:08x}',
                'prefix_le_sha256':digest.hexdigest(),'limit':limit}
    return {'passed':True,'max_raw_exp_in_scanned_prefix':maximum,'full_max_raw_exp':maximum,
        'words_read':length,'total_words':length,'first_reject_index':None,'prefix_le_sha256':digest.hexdigest(),'limit':limit}


def main():
    start=time.monotonic();deadline=start+600
    parent=CS/CANDIDATE/'Kernel.lean';assert sha(parent.read_bytes())==EXPECTED
    previous=json.loads((HERE/'astra-column4-underflow-exposure.json').read_text(encoding='utf-8'))
    for source in previous['source_bindings']:
        p=ROOT/source['path'];assert sha(p.read_bytes())==source['sha256']
    ep=HERE.parent/'round7h-20261023T193125Z/review-output-underflow-exposure.py'
    sp=importlib.util.spec_from_file_location('lowexp_source_only',ep);ex=importlib.util.module_from_spec(sp);sp.loader.exec_module(ex)
    transcription=ex.RESEARCH/'public-nonfinite-opportunity.py'
    element=ex.load_generator(transcription)['element']
    planner=CS/'f01-d6-research/public-delta/benchmark_suite.py'
    make_plan=ex.load_plan_generator(planner)['make_plan']
    totals={k:0 for k in ['all_cases','all_MAC','all_outputs','maxsum_lt128_cases','maxsum_lt128_MAC',
        'already_underflow_cases','already_underflow_MAC','new_route_cases','new_route_MAC','new_route_outputs',
        'new_route_n_le4_cases','new_route_n_le4_MAC','new_route_n_gt4_cases','new_route_n_gt4_MAC',
        'hypothetical_certificate_words','failed_certificate_words']}
    result=[]
    for seed,run in RUNS:
        ci=CS/'f01-mul-log2-proof1/ci-runs'/str(run)
        index_path=ci/'original-artifact-hashes.json';index=json.loads(index_path.read_text())
        directory=ci/index['directory'];sub='diagnostics/f01-d7-public-suite/public-suite/'
        evidence={}
        objects={}
        for name in ['summary.json','public-drawn-plan.json','public-v2.json','public-cell-work.json',CANDIDATE+'-verdict.json']:
            data=(directory/(sub+name)).read_bytes();expected=index['files'][sub+name]
            assert len(data)==expected['bytes'] and sha(data)==expected['sha256']
            objects[name]=json.loads(data)
            evidence[name]={'canonical_path':str((directory/(sub+name)).relative_to(ROOT)).replace('\\','/'),'sha256':sha(data)}
        summary=objects['summary.json'];plan=objects['public-drawn-plan.json'];verdict=objects[CANDIDATE+'-verdict.json'];work=objects['public-cell-work.json']
        row=next(e for e in summary['results'] if e['candidate']==CANDIDATE)
        assert summary['complete'] and summary['seed']==verdict['seed']==seed
        assert summary['official_commit']==ex.OFFICIAL and summary['official_generator_sha256']==sha(planner.read_bytes())
        assert row['kernel_sha256']==EXPECTED and row['full_gate'] and verdict['passed'] and len(verdict['rounds'])==25
        assert make_plan(objects['public-v2.json'],seed,500000)==plan
        scored={cell:verdict['classes'][cell]['submission_ns']*n for cell,n in work.items()}
        total_cost=sum(scored.values());bmm_cost=sum(value for cell,value in scored.items() if cell.startswith('bmm:'))
        assert abs(total_cost-row['scored_submission_total_ns'])<0.01
        cell_costs={cell:{'recorded_scored_ns':value,'fraction_of_BMM_scored_cost':value/bmm_cost,
                         'fraction_of_whole_scored_cost':value/total_cost,'work':work[cell]}
                    for cell,value in scored.items() if cell.startswith('bmm:')}
        cases=[];local={k:0 for k in totals}
        for c in plan['cases']:
            if not(c['timed'] and c['kernel']=='bmm'):continue
            batch,m,n,p=[c[k] for k in ['batch','m','n','p']]
            assert c['work']==batch*m*n*p and c['work']>0
            A=scan(c,0,batch*m*n,n,127,element,deadline)
            B=scan(c,1,batch*n*p,p,127-A['full_max_raw_exp'],element,deadline) if A['passed'] else None
            hit=A['passed'] and B['passed']
            underflow=hit and A['full_max_raw_exp']<=43 and B['full_max_raw_exp']<=43
            new=hit and not underflow
            words=A['words_read']+(B['words_read'] if B else 0)
            local['all_cases']+=1;local['all_MAC']+=c['work'];local['all_outputs']+=batch*m*p
            local['hypothetical_certificate_words']+=words
            if not hit:local['failed_certificate_words']+=words
            for label,flag in [('maxsum_lt128',hit),('already_underflow',underflow),('new_route',new)]:
                if flag:local[label+'_cases']+=1;local[label+'_MAC']+=c['work']
            if new:
                local['new_route_outputs']+=batch*m*p
                label='new_route_n_le4' if n<=4 else 'new_route_n_gt4'
                local[label+'_cases']+=1;local[label+'_MAC']+=c['work']
            cases.append({'name':c['name'],'generator_case':c,'shape':[batch,m,n,p],'MAC':c['work'],
                'A_max_certificate_scan':A,'B_max_certificate_scan':B,'max_raw_exp_sum_lt128_reconstructed':hit,
                'already_UnderflowZero_reconstructed':underflow,'new_route_reconstructed':new,
                'new_route_case_time_ns':'UNKNOWN_NOT_RETAINED','actual_branch_events':'UNKNOWN_NOT_INSTRUMENTED'})
        touched={c['name'].rsplit(':',1)[0] for c in cases if c['new_route_reconstructed']}
        result.append({'seed':seed,'run':run,'evidence':evidence,'Root_index_sha256':sha(index_path.read_bytes()),
            'whole_recorded_scored_ns':total_cost,'BMM_recorded_scored_ns':bmm_cost,'BMM_whole_fraction':bmm_cost/total_cost,
            'BMM_cells':cell_costs,'counts':local,'cases':cases,
            'all_touched_cells_whole_time_loose_upper_bound':sum(scored[k] for k in touched)/total_cost,
            'upper_bound_warning':'Allcostinanytouchedcell, includingineligiblecases/prep/output/replay; notroutecost orrecoverablegain.'})
        for key in totals:totals[key]+=local[key]
    rec={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'NOT_PROVED_SOURCE_MODEL_NEXT_ROUND_MEMO_ONLY',
        'analysis_seconds':time.monotonic()-start,'script_sha256':sha(Path(__file__).read_bytes()),
        'candidate_sha256':EXPECTED,'source_bindings':previous['source_bindings'],
        'only_completed_df5c_full_runs':RUNS,'new_Kernel_or_CI_or_web':False,'totals':totals,
        'new_route_fraction_of_BMM_MAC':totals['new_route_MAC']/totals['all_MAC'],'runs':result,
        'timing_definition':'Actualofficialrecordedclasssubmission_ns×actualcell_work, agreeingwithscored_submission_total_ns. Thisisrecordedscoredcost, notbenchmarkwalltime orpercase/stage time.',
        'model_definition':'One hypotheticalcertificate:scanA formaxexp, rejectearlyonexp>=128; afterfullA scanB withlimit127-maxA. A/Bmaxsum<128 iffpasses. ExistingUnderflowZero hit iff bothmaxexp<=43; this impliesmaxsum<128, hencefailedmaxcertificatecannotbeanUnderflowhit. No runtimecertificateimplemented.',
        'scope':'INFERREDpinned-source wordreconstruction, notLean inputdump/compiledbranchevents/time. Thecelltimingdata areobservedbutcannotbeallocatedtothesubsetbyMAC/casefractions. Missscan costsandinputprep areunmeasured.'}
    (HERE/'astra-lowexp-integer-dot-memo.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'seconds':rec['analysis_seconds'],'totals':totals,'new_MAC_fraction':rec['new_route_fraction_of_BMM_MAC'],
        'per_run':[{'seed':r['seed'],'BMM_whole_fraction':r['BMM_whole_fraction'],'new_cases':r['counts']['new_route_cases'],
                    'new_MAC':r['counts']['new_route_MAC'],'new_names':[c['name'] for c in r['cases'] if c['new_route_reconstructed']]} for r in result]},indent=2))


if __name__=='__main__':main()
