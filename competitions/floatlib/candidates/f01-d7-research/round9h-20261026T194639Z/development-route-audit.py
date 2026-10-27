"""Explicit statement-only route collection hook. Never a proof or score stage."""
from pathlib import Path
import hashlib,importlib.util,json,os,time,traceback

SOURCE='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
def _sha(path):return hashlib.sha256(Path(path).read_bytes()).hexdigest()

def _process_age_seconds():
    # Inner ci-diagnostics replay has a120s process timeout; retain8s for receipts.
    fields=Path('/proc/self/stat').read_text().rsplit(')',1)[1].split()
    started=int(fields[19])/os.sysconf('SC_CLK_TCK')
    return max(0.0,float(Path('/proc/uptime').read_text().split()[0])-started)

def stages(g,kernel,out,manifest):
    kernel,out=Path(kernel),Path(out)
    folder=Path(__file__).resolve().parent/'development-route-profile'
    assert manifest['validation_mode']=='statement-only' and manifest['diagnostic_only']is True
    assert _sha(kernel)==manifest['candidate_sha256']==manifest['helper_audit_source_sha256']==SOURCE
    assert _sha(__file__)==manifest['helper_audit_module_sha256']
    assert manifest['helper_audit_module']=='development-route-audit.py'
    root=next(p for p in folder.parents if(p/'competitions/floatlib/pins.json').is_file())
    components={}
    for item in manifest['components']:
        path=(root/item['path']).resolve()
        assert path.is_relative_to(folder.resolve()) and path.is_file()
        assert path.stat().st_size==item['bytes'] and _sha(path)==item['sha256']
        assert path.name not in components
        components[path.name]=item
    required={'driver.py','RouteLabels.lean','legacy-whole-parser.py','parser-provenance.json',
              'seen-1927003-plan.json','seen-1927005-plan.json','request.json','request-original-240.json'}
    assert set(components)==required
    request_path=folder/'request.json';request=json.loads(request_path.read_text())
    assert _sha(request_path)==manifest['route_profile_request_sha256']
    assert request['maximum_module_seconds']==manifest['route_profile_maximum_seconds']==60
    assert request['original_maximum_module_seconds']==240
    assert _sha(folder/'request-original-240.json')==request['original_request_sha256']
    assert json.loads((folder/'request-original-240.json').read_text())['maximum_module_seconds']==240
    assert request['parser']['sha256']==components['legacy-whole-parser.py']['sha256']
    assert request['parser']['git_blob']=='abc3d912dac66d1b2970ba1a7e5288a3d51446a4'
    parser_provenance=json.loads((folder/'parser-provenance.json').read_text())
    assert parser_provenance['git_blob']==request['parser']['git_blob']
    assert parser_provenance['sha256']==request['parser']['sha256'] and parser_provenance['worktree_equals_git_blob']is True
    assert [p['seed']for p in request['plans']]==[1927003,1927005]
    for p in request['plans']:assert _sha(folder/p['path'])==p['sha256']==components[p['path']]['sha256']
    first_plan=json.loads((folder/request['plans'][0]['path']).read_text())
    spec=importlib.util.spec_from_file_location('r19_bound_route_driver',folder/'driver.py')
    driver=importlib.util.module_from_spec(spec);spec.loader.exec_module(driver)

    def collect(src,verdict):
        callback_started=time.monotonic()
        record=dict(diagnostic_only=True,full_gate=False,new_kernel_replay=False,new_axiom_audit=False,
                    kernel_sha256=SOURCE,request_sha256=_sha(request_path),collection_complete=False,
                    requested_cap_seconds=60,original_design_cap_seconds=240,
                    inner_process_timeout_seconds=120,nested_statement_timeout_seconds=180,
                    destruction_boundary='PENDING_ACTUAL_BENCHSUITE_C_REVIEW')
        target=out/'route-audit.json'
        def save():target.write_text(json.dumps(record,indent=2)+'\n')
        save()
        try:
            assert _sha(g.WORK)==_sha(kernel)==SOURCE
            assert not any(name in ('score','kernel','axioms','helper-kernel','helper-axioms')for name,_ in g.STAGES)
            age=_process_age_seconds();cap=min(60.0,120.0-age-8.0)
            absolute_deadline=min(callback_started+60,time.monotonic()+max(0.0,cap))
            record.update(inner_process_age_seconds=age,effective_cap_seconds=max(0.0,cap));save()
            if cap<1.0:raise RuntimeError('Insufficient inner120s budget after original statement/capture; collection not started')
            result=driver.run(g,kernel,out/'route-profile',first_plan,1927003,
                              absolute_deadline=absolute_deadline)
            record['collection_complete']=result.get('complete')is True
            record['result_sha256']=_sha(out/'route-profile/route-results.json')
            save()
            return None if record['collection_complete']else 'Route collection incomplete'
        except Exception as error:
            record.update(error_type=type(error).__name__,error=str(error),traceback=traceback.format_exc());save()
            return 'Independent route diagnostic failed: '+str(error)
    return [('route-collection',collect)]
