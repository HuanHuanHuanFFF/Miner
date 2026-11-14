"""Freeze an original-ContractTensor runtime pilot, never an admission candidate."""
from pathlib import Path
import hashlib, json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
R24=HERE.parent
NAME='f01-r24-dev-dot-cost1'
OUT=ROOT/'competitions/floatlib/candidates'/NAME
OUT.mkdir(exist_ok=True)
sha=lambda b:hashlib.sha256(b).hexdigest()
prefix_path=ROOT/'competitions/floatlib/references/official-incumbent/Kernel.lean'
prefix=prefix_path.read_bytes()
assert sha(prefix)=='5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
inputs=[
    ('development-broad/ExactDotCost.lean.inc','cb0eaf4cf11181c2ee006b906f3008ec4d92ddcc5a317c1ceb47b23f70e7bd53'),
    ('development-broad/ExactDotTiered.lean.inc','daf2f330ce681b7a1db46e56e8fd6a5bdda8d16db2ad20d288e8330530dbf7d5'),
    ('development-scalar/PortableF64Dot.lean.inc','dd775683cade6e575dc6f0684f9216742e1c772c3cf7460b0c53c54e4e3eff04'),
    ('development-dot-cost/Adapters.lean.inc','4ac3cf62b0a66bcc82acec505e2ee9dc54eb1d507dfd424cb33777cf83e337cf')]
parts=[]
for relative,want in inputs:
    b=(R24/relative).read_bytes();assert sha(b)==want,(relative,sha(b));parts.append(b)
raw=prefix+b'\n\n'+b'\n\n'.join(parts)
assert len(raw)<=256000
p=OUT/'Kernel.lean'
if p.exists():assert p.read_bytes()==raw,'Frozen source requires a new version'
else:p.write_bytes(raw)
audit='''"""Runtime-only statement diagnostic; no new-math proof acceptance."""
from pathlib import Path
import hashlib, importlib.util, json, time
SOURCE=__SOURCE__
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(p,d):p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\\n',encoding='utf-8')
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
'''.replace('__SOURCE__',repr(sha(raw)))
p=HERE/'audit-stage.py'
if p.exists():assert p.read_text(encoding='utf-8')==audit
else:p.write_text(audit,encoding='utf-8',newline='\n')
paths=[R24/x for x,_ in inputs]
paths += [HERE/n for n in ['driver.py','parse-results.py','audit-callers.py','audit-stage.py','R24DotCostMain.lean','R24DotBarrier.lean','fixtures.json']]
paths += [R24/'development-scalar/f64-cost/driver.py',ROOT/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-runtime-cost/bounded-capture-source.py']
components=[{'path':p.relative_to(ROOT).as_posix(),'bytes':p.stat().st_size,'sha256':sha(p.read_bytes())} for p in paths]
manifest={'candidate':NAME,'candidate_file':'Kernel.lean','candidate_sha256':sha(raw),'candidate_bytes':len(raw),
    'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':600,
    'helper_audit_module':'audit-stage.py','helper_audit_module_path':(HERE/'audit-stage.py').relative_to(ROOT/'competitions/floatlib/candidates').as_posix(),
    'helper_audit_module_sha256':sha((HERE/'audit-stage.py').read_bytes()),'components':components,
    'proof_status':'OLD_SHIPPED4_RETAINED_NEW_RUNTIME_UNPROVED','performance':'NOT_RUN','formal_submission':'NOT_SUBMITTED',
    'official_submission_inherited':False,'runtime_cost':{'absolute_stage_seconds':580,'build_cap':180,'measure_phase_cap':300,
        'seeds':[24282403,24282405],'variants':['exact','eager','lazy'],'boundaries':['full','prepared'],
        'order':['exact','eager','eager','exact','exact','lazy','lazy','exact'],'processes':32,'mac_target_per_case':131072,'raw_samples':3,
        'sample_role':'EXPLORATION_ONLY','all_148_numeric_dots':True,'all_1049_word_round_cases':True},
    'runtime_prefix':{'path':prefix_path.relative_to(ROOT).as_posix(),'bytes':len(prefix),'sha256':sha(prefix),'byte_identical':True},
    'scope':'OriginalContractTensor generic dot primitive only, four shipped public callbacks unchanged. Own word64/128/reference control, not actual former2/current champion. Full prep/drop and prepared reuse reported separately; all misses/rejections retained.',
    'trust_gaps':['All new word64/128, FP subnormal decode, fold/error/checker/fallback composition remain unproved','Finite native oracle and cost do not establish all-input correctness or admission','Packed integer prep is not the best possible metadata-only cold reference','No new target kernels, current-champion score, ARM or private input measurement']}
(OUT/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':NAME,'source_sha256':sha(raw),'bytes':len(raw),'components':len(components),'state':'PREPARED_NOT_COMPILED'}))
