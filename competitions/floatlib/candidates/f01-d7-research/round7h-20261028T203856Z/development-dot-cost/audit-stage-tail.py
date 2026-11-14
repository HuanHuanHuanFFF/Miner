"""Runtime-only statement diagnostic; no new-math proof acceptance."""
from pathlib import Path
import hashlib, importlib.util, json, time
SOURCE='e50bf8769d0bef3cc7883d9c1285fd26439282d7c1fd8c141cb84073f90a7f78'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(p,d):p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
def stages(g,kernel,out,manifest):
    began=time.monotonic();here=Path(__file__).resolve().parent
    root=next(p for p in here.parents if (p/'AGENTS.md').is_file())
    assert sha(kernel)==manifest['candidate_sha256']==SOURCE
    assert manifest['validation_mode']=='statement-only' and manifest['diagnostic_timeout_seconds']==600
    assert manifest['runtime_cost']['absolute_stage_seconds']==580
    assert g._SANDBOX and g._BUILD_MEMORY_MB==4096
    assert [n for n,_ in g.STAGES]==['intake','policy','statement']
    assert not manifest.get('explicit_helper_audit')
    for item in manifest['components']:
        p=(root/item['path']).resolve()
        allowed=p.is_relative_to(here.parent) or (
            p.name=='bounded-capture-source.py' and sha(p)=='926e0e72695156c79c56612a20fe6ed015a2ea4a8373d8d9fc9ac5f37c12d90d')
        assert allowed and p.stat().st_size==item['bytes'] and sha(p)==item['sha256'],item['path']
    s=importlib.util.spec_from_file_location('r24_dot_driver',here/'driver.py')
    driver=importlib.util.module_from_spec(s);s.loader.exec_module(driver)
    target=Path(out)/'runtime-cost';target.mkdir(parents=True,exist_ok=True)
    state={'source_sha256':SOURCE,'diagnostic_only':True,'new_runtime_proof':'NOT_PROVED',
        'full_gate':False,'formal_adoption':False,'scope':'Own word64/128 versus certified-proposal research pilot; not a champion comparison',
        'status':'WAITING_ORIGINAL_STATEMENT'}
    save(target/'stage-receipt.json',state)
    def collect(src,verdict):
        prepared=None;owned=set(g.OWN_STEMS)
        try:
            assert sha(src)==sha(kernel)==sha(g.WORK)==SOURCE
            prepared=driver.prepare(g,kernel,target,manifest)
            state['status']='RUNNING';save(target/'stage-receipt.json',state)
            driver.build_and_measure(g,prepared,target,manifest,began+580)
            state['status']='DATA_COMPLETE_REVIEW_REQUIRED'
            return None
        except Exception as error:
            state.update(status='FAILED_PARTIAL_RETAINED',error_type=type(error).__name__,error=str(error))
            return 'dot cost diagnostic failed: '+str(error)
        finally:
            if prepared:
                try:driver.cleanup(prepared);state['owned_sources_cleanup']='EXACT_HASH_REMOVED'
                except Exception as error:state['owned_sources_cleanup']='PRESERVED_'+str(error)
            state['original_OWN_STEMS_unchanged']=owned==set(g.OWN_STEMS)
            state['seconds_from_stage_registration']=time.monotonic()-began
            save(target/'stage-receipt.json',state)
    return [('runtime-cost-diagnostic',collect)]
