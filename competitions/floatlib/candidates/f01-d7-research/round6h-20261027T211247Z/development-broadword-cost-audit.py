"""Statement-only runtime cost stage; no replay/axiom stage and no command on import."""
from pathlib import Path
import hashlib
import importlib.util
import json
import sys
import time

sys.dont_write_bytecode = True
SOURCE = '0274763264d760775e6a447848e873db418adc2e6fb651d117c5fc04b4b5d4a5'
GATE = '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
sha = lambda p: hashlib.sha256(Path(p).read_bytes()).hexdigest()


def save(path, value):
    Path(path).write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())


def stages(g, kernel, out, manifest):
    started = time.monotonic()  # Includes later original intake/policy/statement work.
    here = Path(__file__).resolve().parent
    root = next(p for p in here.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
    assert sha(kernel) == manifest['candidate_sha256'] == SOURCE
    assert manifest['diagnostic_timeout_seconds'] == 600
    assert manifest['runtime_cost']['overall_budget_seconds_from_stage_registration'] == 580
    assert manifest['validation_mode'] == 'statement-only' and manifest['diagnostic_only'] is True
    assert [n for n,_ in g.STAGES] == ['intake','policy','statement'], 'Only original statement prefix allowed'
    assert sha(g.HERE/'gate.py') == GATE and g._SANDBOX
    assert g._BUILD_MEMORY_MB == 4096, 'Original4GiB build scope required'
    assert not manifest.get('explicit_helper_audit'), 'Do not rerun historical7root/replay'
    for item in manifest['components']:
        path = (root/item['path']).resolve()
        assert path.is_relative_to(here/'development-broadword'), 'Only this diagnostic package components'
        assert path.stat().st_size == item['bytes'] and sha(path) == item['sha256'], item['path']
    driver = here/'development-broadword/driver.py'
    spec=importlib.util.spec_from_file_location('r19_runtime_cost_driver',driver)
    module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    target=Path(out)/'runtime-cost';target.mkdir(parents=True,exist_ok=True)
    state={'diagnostic_only':True,'status':'WAITING_ORIGINAL_STATEMENT','source_sha256':SOURCE,
           'prior_components':'ExactB2_622d_prefix; BroadwordADD not proved',
           'full_gate':False,'new_public_ADD_correctness':'UNKNOWN','original25_round_score':'NOT_RUN',
           'outer_timeout_seconds':600,'inner_absolute_seconds_from_registration':580,
           'original_OWN_STEMS_unchanged':True,'original_foreign_would_reject_new_target':True}
    save(target/'stage-receipt.json',state)
    deadline=started+580
    def collect(src, verdict):
        prepared=None;before=set(g.OWN_STEMS)
        try:
            assert sha(src)==sha(kernel)==sha(g.WORK)==SOURCE
            assert time.monotonic()<deadline-52,'Insufficient remaining budget after original statement'
            state['status']='RUNNING';save(target/'stage-receipt.json',state)
            prepared=module.prepare(g,kernel,target)
            module.build_and_measure(g,prepared,target,deadline)
            assert before==set(g.OWN_STEMS),'Original artifact ownership rules changed'
            state['status']='DIAGNOSTIC_DATA_COMPLETE_REVIEW_PENDING'
            return None
        except Exception as error:
            state.update(status='FAILED_PARTIAL_RETAINED',error_type=type(error).__name__,error=str(error))
            return 'runtime-cost diagnostic failed: '+str(error)
        finally:
            if prepared:
                try: module.cleanup_owned(prepared);state['owned_work_sources_cleanup']='EXACT_HASH_REMOVED'
                except Exception as error: state['owned_work_sources_cleanup']='PRESERVED_'+str(error)
            state['original_OWN_STEMS_unchanged']=before==set(g.OWN_STEMS)
            state['elapsed_seconds_from_registration']=time.monotonic()-started
            state['remaining_seconds']=deadline-time.monotonic()
            save(target/'stage-receipt.json',state)
    return [('runtime-cost-diagnostic',collect)]
