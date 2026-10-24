"""Real pure updates/transaction writes in disposable fixtures; original gate I/O mocked."""
from copy import deepcopy
import importlib.util
import json
from pathlib import Path
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location("adopt3",HERE/"adopt-three-confirmed.py")
ad=importlib.util.module_from_spec(spec);spec.loader.exec_module(ad)
BASE_NAME="f01-d12-scalar-combined"
BASE_BYTES=(ad.ROOT/"competitions/floatlib/candidates"/BASE_NAME/"Kernel.lean").read_bytes()
CONTROL_NAME="f01-r8-combined-result-guard"
CONTROL_SHA="41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7"
CONTROL_BYTES=(ad.ROOT/"competitions/floatlib/candidates"/CONTROL_NAME/"Kernel.lean").read_bytes()


class Fixture:
    def __init__(self, root):
        self.root=Path(root);self.here=self.root/ad.REL
        self.own=self.here.parent;self.scripts=self.root/"competitions/floatlib/scripts"
        self.state_path=self.root/"competitions/floatlib/coordination/development-status.json"
        self.view_path=self.own/"multiplier-comparison.json"
        self.model_path=self.own/"champion-time-estimate.json"
        self.dashboard=self.root/"dashboard.md"
        for d in (self.here,self.scripts,self.state_path.parent):d.mkdir(parents=True,exist_ok=True)
        self.hash=ad.sha(b"new-synthetic-source")
        self.source=self.root/"competitions/floatlib/candidates/new-synthetic/Kernel.lean"
        self.source.parent.mkdir();self.source.write_bytes(b"new-synthetic-source")
        baseline=self.root/"competitions/floatlib/candidates"/BASE_NAME/"Kernel.lean"
        baseline.parent.mkdir();baseline.write_bytes(BASE_BYTES)
        control=self.root/"competitions/floatlib/candidates"/CONTROL_NAME/"Kernel.lean"
        control.parent.mkdir();control.write_bytes(CONTROL_BYTES)
        self.policy={"baseline":"current_champion","layout":"custom-current-layout","updated_at_utc":"preserve-exactly","custom":True}
        self.view={"candidate":BASE_NAME,"kernel_sha256":ad.BASELINE,"full_gate_runs":[1],"public_results":(self.own/"public-suite-results.json").relative_to(self.root).as_posix(),
            "champion":{"submission":285,"digest":"champion","official_normalized_self_time":1.0,"custom_champion":"preserve"},"dashboard_policy":self.policy,"formal_submission":"NOT_SUBMITTED"}
        self.state={"candidate":baseline.parent.relative_to(self.root).as_posix(),"kernel":baseline.relative_to(self.root).as_posix(),"kernel_sha256":ad.BASELINE,
            "current_multiplier_view":{"dashboard_policy":deepcopy(self.policy)},"current_champion_comparison":{"submission":285},
            "research_round":{"start_utc":"start","deadline_utc":"deadline","active_ci":[999]},"active_jobs":[999],
            "research_resources":"authorized current resources","resources":{"owner":"root","allow_private":False},"collaboration":{"old_history":"keep"},"remaining":["current obligations"]}
        self.old_numeric_freeze={"path":"prior/retained-estimate-freeze.json","candidate":BASE_NAME,
            "source_sha256":ad.BASELINE,"champion_digest":"champion","model_sha256":"old-model"}
        self.view["retained_numeric_model_freeze"]=deepcopy(self.old_numeric_freeze)
        self.state["current_multiplier_view"]["retained_numeric_model_freeze"]=deepcopy(self.old_numeric_freeze)
        self.save(self.view_path,self.view);self.save(self.state_path,self.state);self.save(self.model_path,{"old_model":True});self.dashboard.write_bytes(b"old dashboard")
        self.anchor=self.here/"freeze-anchor.json";self.save(self.anchor,{"anchor":"synthetic-original-IO"})
        self.save(self.own/"current-official-snapshot.json",{"champion":285})
        self.rows=[]
        self.baseline_rows=[]
        self.control_rows=[]
        self.checked_record_sources=[]
        self.score_baseline_pairs=[]
        for run in (11,12,13,14):
            ratio=.8 if run!=14 else 1.3
            common={"run":run,"seed":100+run,"full_gate":True,"suite_sha256":"suite",
                "runner_execution":f"runner-execution-{run}",
                "official_commit":"official","drawn_plan_sha256":f"drawn-{run}",
                "provenance_sha256":f"provenance-{run}","incumbent_sha256":"incumbent",
                "reference_champion_sha256":"champion","verifier_fingerprint":"fingerprint",
                "cell_work":{op+':dense':1 for op in ad.OPS}}
            self.rows.append({**common,"candidate":"new-synthetic","kernel_sha256":self.hash,
                "operation_total_ns":{op:100*ratio for op in ad.OPS},"operation_reference_total_ns":{op:100 for op in ad.OPS},
                "time_share_percent":{op:25 for op in ad.OPS},"ratio":ratio,"verdict":f"artifacts/run-{run}/candidate.json","verdict_sha256":f"hash-{run}"})
            self.rows[-1].update(classes={op+':dense':{'submission_ns':100*ratio,'incumbent_ns':100} for op in ad.OPS})
            self.baseline_rows.append({**common,"candidate":BASE_NAME,"kernel_sha256":ad.BASELINE,
                "operation_total_ns":{op:100 for op in ad.OPS},"operation_reference_total_ns":{op:100 for op in ad.OPS},
                "time_share_percent":{op:25 for op in ad.OPS},"ratio":1.0,"verdict":f"artifacts/run-{run}/retainedDF.json","verdict_sha256":f"baseline-hash-{run}",
                "classes":{op+':dense':{'submission_ns':100,'incumbent_ns':100} for op in ad.OPS}})
            # Deliberately distinguish the estimator's retained 41 anchor from the score baseline 6c2d.
            self.control_rows.append({**common,"candidate":CONTROL_NAME,"kernel_sha256":CONTROL_SHA,
                "operation_total_ns":{op:125 for op in ad.OPS},"operation_reference_total_ns":{op:100 for op in ad.OPS},
                "time_share_percent":{op:25 for op in ad.OPS},"ratio":1.25,"verdict":f"artifacts/run-{run}/estimator41.json","verdict_sha256":f"control41-hash-{run}",
                "classes":{op+':dense':{'submission_ns':125,'incumbent_ns':100} for op in ad.OPS}})
        self.index=self.own/"public-suite-results.json";self.save(self.index,{"records":self.rows+self.baseline_rows+self.control_rows})
        self.runs={"D":11,"A":12,"B":13}
        self.freeze={"candidate":{"name":"new-synthetic","sha256":self.hash},"baseline":{"name":BASE_NAME,"sha256":ad.BASELINE},
            "estimator_control":{"name":CONTROL_NAME,"sha256":CONTROL_SHA},
            "groups":{r:{"seed":100+n,"run":n} for r,n in self.runs.items()},"suite_sha256":"suite",
            "selection_policy":{"headline_normalized_ratio_max":.97,"gain_p05_min_exclusive":0.0},"files":{}}
        for p in (self.here/"adopt-three-confirmed.py",self.scripts/"estimate_champion_time.py",self.scripts/"render_dashboard.py",self.anchor):
            if not p.exists():p.write_bytes(b"synthetic-frozen-helper")
            self.freeze["files"][p.relative_to(self.root).as_posix()]={"sha256":ad.sha(p.read_bytes())}
        self.freeze_path=self.here/"cohort-freeze.json";self.save(self.freeze_path,self.freeze)
        self.freeze_sha=ad.sha(self.freeze_path.read_bytes())
        self.selection={"accepted":True,"group_count":3,"failures":[],"groups":{r:{"run":n,"job":n+1000,"seed":n+100,"relative_normalized_ratio":.8,"gain_p05":.2} for r,n in self.runs.items()}}
        self.fresh_calls=0;self.freeze_calls=0;self.fail_estimate=False;self.fail_after_model=False;self.external_state=False;self.fail_render=False;self.mutate_source=False;self.mutate_index=False
        self.estimator_control_pairs=[];self.score_baseline_pairs=[];self.checked_record_sources=[]
        self.verifier=SimpleNamespace(import_guard=lambda:None,verify_freeze=self.verify_freeze,verify_three_groups=self.verify_groups)
        self.est=SimpleNamespace(DEFAULT_ANCHOR=self.anchor,main=self.estimate_main,select_pairs=self.select_pairs,checked_record=self.checked_record,estimate_from_anchor=self.predict,save=self.save)
        self.renderer=SimpleNamespace(main=self.render)

    def save(self,path,value):Path(path).write_bytes(ad.encoded(value))
    def verify_freeze(self,freeze,expected,path,guard,root):
        self.freeze_calls+=1
        ad.require(ad.sha(Path(path).read_bytes())==expected,"freeze changed")
        ad.require(ad.sha(self.source.read_bytes())==freeze["candidate"]["sha256"],"source changed")
        ad.require(freeze.get("estimator_control")=={"name":CONTROL_NAME,"sha256":CONTROL_SHA},"estimator control identity changed")
        control=root/"competitions/floatlib/candidates"/CONTROL_NAME/"Kernel.lean"
        ad.require(ad.sha(control.read_bytes())==freeze["estimator_control"]["sha256"],"estimator control source changed")
    def verify_groups(self,*args,**kwargs):
        self.fresh_calls+=1
        if self.mutate_source:self.source.write_bytes(b"external source change")
        return deepcopy(self.selection)
    def select_pairs(self,records,runs,source,anchor,root):
        if self.fail_estimate:raise ValueError("estimate refused")
        self.estimator_control_pairs=[]
        pairs=[]
        for run in runs:
            candidate=[r for r in records if r["run"]==run and r["kernel_sha256"]==source and r.get("full_gate") is True]
            control=[r for r in records if r["run"]==run and r["kernel_sha256"]==CONTROL_SHA and r.get("full_gate") is True]
            ad.require(len(candidate)==1 and len(control)==1,"missing/duplicate same-runner 41 estimator control")
            c,b=self.checked_record(candidate[0],root),self.checked_record(control[0],root)
            ad.require(b.get("candidate")==CONTROL_NAME and b.get("kernel_sha256")==CONTROL_SHA,"wrong 41 estimator control source")
            ad.require((c["seed"],c["suite_sha256"],c["runner_execution"]) ==
                       (b["seed"],b["suite_sha256"],b["runner_execution"]),"41 control is not a matched same-runner pair")
            self.estimator_control_pairs.append({"run":run,"kernel_sha256":b["kernel_sha256"],"runner_execution":b["runner_execution"]})
            pairs.append((c,b))
        return pairs
    def checked_record(self,row,root):
        # Raw gate I/O is mocked; production uses the frozen estimator's full authenticator.
        ad.require(row.get("full_gate") is True,"Incomplete score baseline")
        ad.require(row.get("kernel_sha256") in {ad.BASELINE,CONTROL_SHA,self.hash},"Wrong authenticated pair source")
        self.checked_record_sources.append(row["kernel_sha256"])
        if row.get("kernel_sha256")==ad.BASELINE:
            self.score_baseline_pairs.append({"run":row["run"],"kernel_sha256":row["kernel_sha256"],
                                              "runner_execution":row.get("runner_execution")})
        return deepcopy(row)
    def predict(self,*args):
        if self.mutate_index:self.save(self.index,{"records":self.rows,"external_change":True})
        pairs=args[-1]
        ad.require(pairs and all(b["kernel_sha256"]==CONTROL_SHA and
                  (a["run"],a["seed"],a["suite_sha256"],a["runner_execution"]) ==
                  (b["run"],b["seed"],b["suite_sha256"],b["runner_execution"]) for a,b in pairs),
                  "estimate must use matched 41 control pairs")
        return {"operations":{op:{"ratio_median":.8} for op in ad.OPS},"whole":{"ratio_median":.8},"kernel_sha256":self.hash}
    def estimate_main(self,args):
        if "--dry-run" in args:return {"champion_digest":"champion","champion_submission":285,"champion_suite":{"sha256":"private"}}
        if self.external_state:
            self.state_path.write_bytes(b"external concurrent state")
            raise RuntimeError("external writer interrupted refresh")
        self.est.save(self.model_path,{"new_model":True})
        if self.fail_after_model:raise RuntimeError("estimator failed after model save")
        v,s=ad.read(self.view_path),ad.read(self.state_path)
        v["dashboard_policy"]["updated_at_utc"]="estimator timestamp"
        s["current_multiplier_view"]["dashboard_policy"]["updated_at_utc"]="estimator timestamp"
        self.est.save(self.view_path,v);self.est.save(self.state_path,s)
    def render(self):
        self.dashboard.write_text("new diagnostic-free dashboard",encoding="utf-8")
        if self.fail_render:raise RuntimeError("renderer failed after its write")
    def target_bytes(self):return {p:p.read_bytes() for p in (self.view_path,self.state_path,self.model_path,self.dashboard)}
    def all_records(self):return self.rows+self.baseline_rows+self.control_rows
    def estimator_pairs(self):
        return self.select_pairs(self.all_records(),[r["run"] for r in self.rows],self.hash,self.anchor,self.root)
    def scoring_pairs(self):
        return ad.scoring_pairs(self.all_records(),self.estimator_pairs(),self.est,self.root)
    def run(self):return ad.adopt(self.freeze_path,self.freeze_sha,self.runs,self.root,self.verifier,self.est,self.renderer)


class AdoptionTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory(prefix=".adoption-test-",dir=HERE)
        self.assertEqual(Path(self.temp.name).resolve().parent,HERE.resolve())
        self.addCleanup(self.temp.cleanup)
        self.f=Fixture(self.temp.name)
    def zero_write_failure(self):
        before=self.f.target_bytes();result,path=self.f.run()
        self.assertFalse(result["accepted"],result)
        self.assertEqual(before,self.f.target_bytes())
        self.assertTrue(path.exists())
        return result
    def test_success_preserves_policy_resources_and_serializes_all_three_plus_slow_extra(self):
        result,path=self.f.run();self.assertTrue(result["accepted"],result)
        v,s=ad.read(self.f.view_path),ad.read(self.f.state_path)
        self.assertEqual(self.f.fresh_calls,1);self.assertGreaterEqual(self.f.freeze_calls,4)
        self.assertEqual({p["kernel_sha256"] for p in self.f.estimator_control_pairs},{CONTROL_SHA})
        self.assertEqual({p["run"] for p in self.f.estimator_control_pairs},{11,12,13,14})
        self.assertEqual({p["kernel_sha256"] for p in self.f.score_baseline_pairs},{ad.BASELINE})
        self.assertEqual({p["run"] for p in self.f.score_baseline_pairs},{11,12,13,14})
        self.assertEqual({p["runner_execution"] for p in self.f.estimator_control_pairs},
                         {p["runner_execution"] for p in self.f.score_baseline_pairs})
        self.assertEqual(v["full_gate_runs"],[11,12,13,14]);self.assertEqual(s["performance"]["full_gate_runs"],[11,12,13,14])
        self.assertEqual(v["independent_adoption_runs"],[11,12,13]);self.assertEqual(len(s["performance"]["independent_samples"]),3)
        self.assertEqual(s["performance"]["all_source_samples"][-1]["ratio"],1.3)
        self.assertEqual(v["dashboard_policy"],self.f.policy);self.assertEqual(s["current_multiplier_view"]["dashboard_policy"],self.f.policy)
        self.assertNotIn("retained_numeric_model_freeze",v)
        self.assertNotIn("retained_numeric_model_freeze",s["current_multiplier_view"])
        for key in ("resources","research_resources","research_round","active_jobs","collaboration","remaining"):
            self.assertEqual(s[key],self.f.state[key])
        self.assertEqual(v["champion"]["submission"],285);self.assertEqual(v["champion"]["custom_champion"],"preserve")
    def test_missing_third_is_rejected_without_writes(self):
        del self.f.selection["groups"]["B"]
        self.zero_write_failure()
    def test_new_retained_source_clears_old_overlay_and_numeric_model_freeze(self):
        self.f.view['dashboard_research_candidate']={'candidate':'older-research'}
        self.f.state['current_multiplier_view']['displayed_research_candidate']={'candidate':'older-research'}
        self.f.view['retained_numeric_model_freeze']=deepcopy(self.f.old_numeric_freeze)
        self.f.state['current_multiplier_view']['retained_numeric_model_freeze']=deepcopy(self.f.old_numeric_freeze)
        self.f.save(self.f.view_path,self.f.view);self.f.save(self.f.state_path,self.f.state)
        result,path=self.f.run();self.assertTrue(result['accepted'],result)
        self.assertNotIn('dashboard_research_candidate',ad.read(self.f.view_path))
        view,state=ad.read(self.f.view_path),ad.read(self.f.state_path)
        self.assertNotIn('displayed_research_candidate',state['current_multiplier_view'])
        self.assertNotIn('retained_numeric_model_freeze',view)
        self.assertNotIn('retained_numeric_model_freeze',state['current_multiplier_view'])
    def test_missing_renderer_freeze_is_rejected_before_target_writes(self):
        del self.f.freeze['files']['competitions/floatlib/scripts/render_dashboard.py']
        self.f.save(self.f.freeze_path,self.f.freeze)
        self.f.freeze_sha=ad.sha(self.f.freeze_path.read_bytes())
        result=self.zero_write_failure()
        self.assertTrue(any('freeze' in x['reason'] for x in result['failures']))
    def test_missing_estimator_control_freeze_is_rejected_before_target_writes(self):
        del self.f.freeze["estimator_control"]
        self.f.save(self.f.freeze_path,self.f.freeze)
        self.f.freeze_sha=ad.sha(self.f.freeze_path.read_bytes())
        self.zero_write_failure()
    def test_wrong_estimator_control_freeze_sha_is_rejected_before_target_writes(self):
        self.f.freeze["estimator_control"]["sha256"]="d"*64
        self.f.save(self.f.freeze_path,self.f.freeze)
        self.f.freeze_sha=ad.sha(self.f.freeze_path.read_bytes())
        self.zero_write_failure()
    def test_scoring_pairs_use_6c_while_estimator_pairs_use_41(self):
        estimator_pairs=self.f.estimator_pairs()
        score_pairs=ad.scoring_pairs(self.f.all_records(),estimator_pairs,self.f.est,self.f.root)
        self.assertEqual({b["kernel_sha256"] for _,b in score_pairs},{ad.BASELINE})
        self.assertEqual({b["kernel_sha256"] for _,b in estimator_pairs},{CONTROL_SHA})
        self.assertEqual({c["run"] for c,_ in score_pairs},{11,12,13,14})
        self.assertEqual({c["run"] for c,_ in estimator_pairs},{11,12,13,14})
        self.assertAlmostEqual(score_pairs[0][0]["ratio"]/score_pairs[0][1]["ratio"],.8)
        self.assertAlmostEqual(estimator_pairs[0][0]["ratio"]/estimator_pairs[0][1]["ratio"],.8/1.25)
    def test_missing_same_run_6c_score_baseline_is_rejected(self):
        self.f.baseline_rows=[r for r in self.f.baseline_rows if r["run"]!=12]
        with self.assertRaisesRegex(ValueError,"No unique same-runner retainedDF score baseline"):
            self.f.scoring_pairs()
    def test_wrong_sha_6c_score_baseline_is_rejected(self):
        self.f.baseline_rows[1]["kernel_sha256"]="d"*64
        with self.assertRaisesRegex(ValueError,"No unique same-runner retainedDF score baseline"):
            self.f.scoring_pairs()
    def test_incomplete_6c_score_baseline_is_rejected(self):
        self.f.baseline_rows[1]["full_gate"]=False
        with self.assertRaisesRegex(ValueError,"No unique same-runner retainedDF score baseline"):
            self.f.scoring_pairs()
    def test_same_run_6c_baseline_from_different_artifact_is_rejected(self):
        self.f.baseline_rows[1]["verdict"]="other-artifact/retainedDF.json"
        with self.assertRaisesRegex(ValueError,"No unique same-runner retainedDF score baseline"):
            self.f.scoring_pairs()
    def test_same_run_6c_baseline_from_different_runner_is_rejected(self):
        self.f.baseline_rows[1]["runner_execution"]="another-runner-execution"
        with self.assertRaisesRegex(ValueError,"RetainedDF score baseline execution differs from candidate"):
            self.f.scoring_pairs()
    def test_score_and_estimator_pairs_use_distinct_6c_and_41_sources(self):
        estimator_pairs=self.f.estimator_pairs()
        score_pairs=ad.scoring_pairs(self.f.all_records(),estimator_pairs,self.f.est,self.f.root)
        self.assertEqual({b["kernel_sha256"] for _,b in score_pairs},{ad.BASELINE})
        self.assertEqual({b["kernel_sha256"] for _,b in estimator_pairs},{CONTROL_SHA})
        self.assertEqual({c["run"] for c,_ in score_pairs},{11,12,13,14})
        self.assertEqual({c["run"] for c,_ in estimator_pairs},{11,12,13,14})
        self.assertAlmostEqual(score_pairs[0][0]["ratio"]/score_pairs[0][1]["ratio"],.8)
        self.assertAlmostEqual(estimator_pairs[0][0]["ratio"]/estimator_pairs[0][1]["ratio"],.8/1.25)
    def test_missing_same_run_6c_score_baseline_is_rejected(self):
        self.f.baseline_rows=[r for r in self.f.baseline_rows if r["run"]!=12]
        with self.assertRaisesRegex(ValueError,"No unique same-runner retainedDF score baseline"):
            self.f.scoring_pairs()
    def test_wrong_sha_6c_score_baseline_is_rejected(self):
        self.f.baseline_rows[1]["kernel_sha256"]="d"*64
        with self.assertRaisesRegex(ValueError,"No unique same-runner retainedDF score baseline"):
            self.f.scoring_pairs()
    def test_incomplete_6c_score_baseline_is_rejected(self):
        self.f.baseline_rows[1]["full_gate"]=False
        with self.assertRaisesRegex(ValueError,"No unique same-runner retainedDF score baseline"):
            self.f.scoring_pairs()
    def test_same_run_6c_baseline_from_different_artifact_is_rejected(self):
        self.f.baseline_rows[1]["verdict"]="other-artifact/retainedDF.json"
        with self.assertRaisesRegex(ValueError,"No unique same-runner retainedDF score baseline"):
            self.f.scoring_pairs()
    def test_same_run_6c_baseline_from_different_runner_is_rejected(self):
        self.f.baseline_rows[1]["runner_execution"]="another-runner-execution"
        with self.assertRaisesRegex(ValueError,"RetainedDF score baseline execution differs from candidate"):
            self.f.scoring_pairs()
    def test_slow_third_is_rejected_without_writes(self):
        self.f.selection["groups"]["B"]["relative_normalized_ratio"]=1.04
        self.zero_write_failure()
    def test_unaccepted_fresh_guard_cannot_use_prior_pass(self):
        self.f.selection.update(accepted=False,failures=[{"reason":"third failed"}])
        self.zero_write_failure();self.assertEqual(self.f.fresh_calls,1)
    def test_state_change_before_start_rejected(self):
        state=ad.read(self.f.state_path);state["kernel_sha256"]="other";self.f.save(self.f.state_path,state)
        self.zero_write_failure()
    def test_source_change_during_guard_rejected_before_target_writes(self):
        self.f.mutate_source=True;self.zero_write_failure()
    def test_estimate_rejection_has_zero_target_writes(self):
        self.f.fail_estimate=True;self.zero_write_failure()
    def test_index_change_during_estimate_preflight_rejected_before_writes(self):
        self.f.mutate_index=True;self.zero_write_failure()
    def test_missing_same_run_41_estimator_control_is_rejected_before_writes(self):
        self.f.control_rows.pop(1)
        self.f.save(self.f.index,{"records":self.f.all_records()})
        self.zero_write_failure()
    def test_wrong_sha_41_estimator_control_is_rejected_before_writes(self):
        self.f.control_rows[1]["kernel_sha256"]="d"*64
        self.f.save(self.f.index,{"records":self.f.all_records()})
        self.zero_write_failure()
    def test_failed_41_estimator_control_is_rejected_before_writes(self):
        self.f.control_rows[1]["full_gate"]=False
        self.f.save(self.f.index,{"records":self.f.all_records()})
        self.zero_write_failure()
    def test_diagnostic_row_cannot_be_adopted(self):
        self.f.rows[-1]["diagnostic_only"]=True;self.f.save(self.f.index,{"records":self.f.all_records()})
        self.zero_write_failure()
    def test_tampered_aggregate_cannot_replace_authenticated_raw_cells(self):
        self.f.rows[-1]['operation_total_ns']['bmm']=1;self.f.save(self.f.index,{"records":self.f.all_records()})
        self.zero_write_failure()
    def test_estimator_failure_after_write_rolls_back_only_own_files(self):
        self.f.fail_after_model=True;result=self.zero_write_failure()
        self.assertTrue(result["rollback"]);self.assertTrue(all(x["status"]=="RESTORED" for x in result["rollback"]))
    def test_renderer_failure_rolls_back_dashboard_and_model(self):
        self.f.fail_render=True;self.zero_write_failure()
    def test_external_state_change_is_preserved_during_rollback(self):
        self.f.external_state=True;before=self.f.target_bytes();result,path=self.f.run()
        self.assertFalse(result["accepted"])
        self.assertEqual(self.f.state_path.read_bytes(),b"external concurrent state")
        self.assertEqual(self.f.view_path.read_bytes(),before[self.f.view_path])
        self.assertTrue(any(x["status"]=="EXTERNAL_CHANGE_PRESERVED" for x in result["rollback"]))
    def test_duplicate_groups_rejected_before_guard_or_writes(self):
        self.f.runs['B']=self.f.runs['A'];self.zero_write_failure()
        self.assertEqual(self.f.fresh_calls,0)
    def test_missing_independent_full_index_row_rejected(self):
        self.f.save(self.f.index,{"records":[r for r in self.f.all_records()
                                                if not (r["kernel_sha256"]==self.f.hash and r['run']==13)]})
        self.zero_write_failure()
    def test_transaction_refuses_to_overwrite_a_foreign_change(self):
        path=self.f.dashboard;tx=ad.Transaction([path]);tx.write(path,b'owned')
        path.write_bytes(b'foreign')
        with self.assertRaises(ValueError):tx.write(path,b'next')
        self.assertEqual(tx.rollback()[0]['status'],'EXTERNAL_CHANGE_PRESERVED')
        self.assertEqual(path.read_bytes(),b'foreign')
    def test_failed_audit_receipt_rolls_back_and_preserves_alternative_failure_receipt(self):
        before=self.f.target_bytes();original=Path.open
        def opened(path,*args,**kwargs):
            if path.name=='receipt.json' and args and args[0]=='xb':raise OSError('injected audit failure')
            return original(path,*args,**kwargs)
        with patch.object(Path,'open',opened):result,path=self.f.run()
        self.assertFalse(result['accepted']);self.assertEqual(before,self.f.target_bytes())
        self.assertEqual(path.name,'receipt-audit-failure.json');self.assertTrue(path.exists())


if __name__=="__main__":unittest.main(verbosity=2)
