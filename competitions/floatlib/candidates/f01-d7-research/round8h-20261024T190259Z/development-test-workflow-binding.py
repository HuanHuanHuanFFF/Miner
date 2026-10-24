"""Replay real archived acceptance and reject failed/foreign job metadata in memory."""
from pathlib import Path
from copy import deepcopy
import importlib.util,json
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4];D7=OUT.parent
def module(name,p):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
old=module('r14_old_guard',D7/'adoption-guard.py');new=module('r14_named_job_guard',OUT/'adoption-guard.py')
args=(ROOT,D7,'f01-d12-scalar-combined',40074431355,40083425886,'f01-d11-bmm-combined-classifier')
before,packets=old.verify_adoption(*args);after,_=new.verify_adoption(*args)
b={k:v for k,v in before.items() if k!='helper_sha256'};a={k:v for k,v in after.items() if k!='helper_sha256'};assert a==b and before['accepted']
original=new.load_run
def replay(change):
    def mock(root,own,rid,names):
        p=deepcopy(next(p for p in packets if p['run_id']==rid));p.update(change);return p
    new.load_run=mock
    try:return new.verify_adoption(*args)[0]
    finally:new.load_run=original
assert replay({'job_name':'verify'})['accepted']
negatives=[]
for change in [{'job_name':'foreign'},{'job_conclusion':'failure'},{'run_conclusion':'cancelled'}]:
    try:replay(change)
    except ValueError:negatives.append(change)
    else:raise AssertionError(change)
result={'status':'PASS','real_archived_pair':[40074431355,40083425886],'old_new_all_numeric_and_evidence_values_identical':True,'dedicated_job_metadata_allowed':True,'rejected_in_memory_negative_cases':negatives,'raw_receipts_modified':False,'local_lean_or_ci':False}
(OUT/'development-workflow-binding-test.json').write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps(result))
