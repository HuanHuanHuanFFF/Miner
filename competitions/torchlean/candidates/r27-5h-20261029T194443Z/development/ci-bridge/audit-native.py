"""Audit fetched-source native exploration using unchanged pinned pure scorer."""
from pathlib import Path
import argparse, hashlib, importlib.util, json, math, re, shlex, sys

sys.dont_write_bytecode = True
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
ROUND=Path(__file__).resolve().parents[2]
BASE=ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/verification/analyze-native-only.py'
spec=importlib.util.spec_from_file_location('r26_verified_primitives',BASE)
base=importlib.util.module_from_spec(spec);sys.modules[spec.name]=base;spec.loader.exec_module(base)
j=lambda p:json.loads(p.read_bytes())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()

def flags(folder):
    out={}
    def norm(xs):
        return [re.sub(r'(?<=/)(?:MainExact|R27NativeMain)(?=\.)','<MAIN>',
                re.sub(r'(?<=/)(?:benchExact|r27Native)(?=\.|$)','<BIN>',x)) for x in xs]
    for kind in ('compile','link','response'):
        a,b=folder/f'original-{kind}.raw',folder/f'owned-{kind}.raw'
        av=shlex.split(a.read_text()) if kind=='response' else base.trace_args(a)
        bv=shlex.split(b.read_text()) if kind=='response' else base.trace_args(b)
        saved=j(folder/'flags.json')[kind]
        assert norm(av)==norm(bv) and saved['original_args']==av and saved['owned_args']==bv and saved['equal_only_root_mapping']
        out[kind]='PASS_ONLY_EXPECTED_TARGET_NAMES_NORMALIZED'
    return out

def analyze(run):
    run_dir=ROUND/'evidence'/str(run);ci=j(run_dir/'ci-run.json')
    assert ci['status']=='completed'
    manifest=j(run_dir/'original-artifact-hashes.json');folder=run_dir/manifest['directory']
    outer=base.audit_tree(folder,manifest['files']);assert outer['status']=='PASS'
    inside=base.audit_tree(folder,j(folder/'file-hashes.json'),excluded=('file-hashes.json',));assert inside['status']=='PASS'
    summary=j(folder/'summary.json');plan=j(folder/'plan.json')
    dispatch_path,dispatch=base.find_dispatch(ROUND/'evidence',run)
    assert summary['source_commit']==ci['headSha']==dispatch['source_commit']
    assert summary['official_commit']==plan['official_commit']=='accb82b6e2adeda1b41a57a260d68fb3879c427e'
    plan_path=ROUND.relative_to(ROOT).as_posix()+'/ci-plan.json'
    assert dispatch['frozen_files'][plan_path]==sha(folder/'plan.json')
    assert summary['originals_unchanged'] and summary['protected_before']==summary['protected_after']
    for command in summary['commands']:
        assert command['exit_code']==0 and sha(folder/(command['label']+'.log'))==command['log_sha256']
    _,modules,pins=base.r25_tools()
    cfg=modules['config'].Config.load(folder/'overall-config.toml');board=cfg.plan(plan['board'])
    expected=6 if plan['board']!='overall' else 30
    assert len(board['cells'])==expected
    rows=[];results={x['name']:x for x in summary['results']}
    ref=results['calibration'];assert ref['source_sha256']==plan['reference']['sha256']
    reference_flags=flags(folder/'calibration')
    for entry in plan['candidates']:
        if entry['name'] not in results:
            rows.append({'candidate':entry['name'],'status':'BUILD_FAILED_OR_NOT_RUN','score':'UNKNOWN'})
            continue
        current=results[entry['name']];assert current['source_sha256']==entry['sha256']
        assert current['measurement_state']=='COMPLETE_NATIVE_ONLY_EXPLORATION'
        checked_flags=flags(folder/entry['name']);pairs=[];cpus=[];counts=[]
        for seed in plan['seeds']:
            request=j(folder/f"{entry['name']}-{seed}-request.json")
            result=j(folder/f"{entry['name']}-{seed}-measurement.json")['result']
            assert request['candidate_hash']==entry['sha256'] and request['reference_hash']==plan['reference']['sha256']
            assert request['seed']==seed and request['cells']==list(board['cells'])
            assert request['workloads']==modules['multiseed'].workloads(seed)
            assert request['benchmark_identity']==board['benchmark_identity']
            assert request['identity']==cfg.environments['local']['identity']
            modules['scoring'].validate_result(request,result,board['cells'])
            base.raw_rounds(folder,entry['name'],seed,request,result)
            assert len(result['rounds'])==request['timing']['rounds']
            count=sum(len(x['cells']) for x in result['rounds'])
            assert count==expected*6*request['timing']['rounds']
            provenance=result['provenance']
            assert provenance['candidate_binary']==current['binary_sha256'] and provenance['reference_binary']==ref['binary_sha256']
            cpus.append({k:provenance[k] for k in ('identity','machine','architecture','cpu_affinity')})
            counts.append({'seed':seed,'paired_rows':count,'ns_values':2*count,'checksum_pairs':count})
            pairs.append((request,result))
        assert len(pairs)==len(plan['seeds']) and all(cpus[0]==x for x in cpus)
        scoring_plan=dict(board);scoring_plan['strata']=[{'environment':q['environment'],'identity':q['identity'],'seed':q['seed'],'weight':1/len(pairs),'timing':q['timing']} for q,_ in pairs]
        scored=modules['scoring'].assess(scoring_plan,pairs)
        champion=plan['champion'];factor=champion['current_champion_over_calibration']
        rows.append({'candidate':entry['name'],'candidate_sha256':entry['sha256'],'board':plan['board'],
                     'current_champion_submission':champion['submission'],'native_flags':checked_flags,
                     'counts':counts,'cpu':cpus,'score_vs_calibration_internal':scored,
                     'candidate_time_over_current_champion_estimate':scored['score']/factor,
                     'champion_comparison':'INFERRED_SCREEN_CROSS_ENV_AND_SEEDS; direct current-source measurement unavailable',
                     'candidate_proof':current['proof_state'],'eligibility':'NOT_ESTABLISHED_NO_ORIGINAL_FULL_GATE_REPLAY',
                     'status':'NATIVE_ONLY_EXPLORATION_AUDITED'})
    return {'run':run,'source_commit':ci['headSha'],'ci_conclusion':ci['conclusion'],
            'status':'AUDITED_NATIVE_ONLY_EXPLORATION','board':plan['board'],'outer_hashes':outer,'inner_hashes':inside,
            'reference_flags':reference_flags,'source_preservation':'PASS','MainExact_sha256':summary['owned_main_equals_original_sha256'],
            'pinned_scorer':pins,'dispatch':dispatch_path.relative_to(ROOT).as_posix(),'helpers':summary.get('helper_diagnostics',[]),
            'results':rows,'scope':'Pure original quick scorer and finite checksums; no full proof/official ranking/adoption claim. Full unknown-license source/C not redistributed.'}

if __name__=='__main__':
    ap=argparse.ArgumentParser();ap.add_argument('--run',type=int,required=True);ap.add_argument('--output',type=Path,required=True);args=ap.parse_args()
    assert not args.output.exists(),'Do not overwrite original audit receipts'
    result=analyze(args.run)
    args.output.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'run':args.run,'status':result['status'],'results':[{k:x[k] for k in ('candidate','candidate_time_over_current_champion_estimate','status') if k in x} for x in result['results']]}))
