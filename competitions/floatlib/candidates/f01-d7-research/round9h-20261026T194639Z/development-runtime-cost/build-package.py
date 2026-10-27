"""Local packaging only. Copies historical bytes; no Lean/Git/CI/network."""
from pathlib import Path
import hashlib
import json
from datetime import datetime, timezone

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
R19=HERE.parent
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(p,v):p.write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
def main():
    source=ROOT/'competitions/floatlib/candidates/f01-r19-dev-direct-bias-runtime1/Kernel.lean'
    candidate=ROOT/'competitions/floatlib/candidates/f01-r19-dev-runtime-cost1'
    assert sha(source)=='74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc'
    assert source.read_bytes()==(candidate/'Kernel.lean').read_bytes()
    old=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40420540388/download-dc507616807e4785a2f3fef3abb4fb38/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-direct-bias-runtime1'
    history=HERE/'historical40420540388';history.mkdir(exist_ok=True)
    copied=[]
    paths=[old/n for n in ('helper-audit.json','helper-axioms.raw','helper-audit-source.lean','diagnostic-only-verdict.json','index.json','replay.log')]
    paths+=[R19/'development-proof-f01-r19-dev-direct-bias-runtime1-40420540388.json']
    paths+=[ROOT/'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw']
    for path in paths:
        target=history/path.name;raw=path.read_bytes()
        if target.exists():assert target.read_bytes()==raw
        else:target.write_bytes(raw)
        copied.append({'original_path':path.relative_to(ROOT).as_posix(),'copy_path':target.relative_to(ROOT).as_posix(),'sha256':sha(path),'bytes':len(raw)})
    report=json.loads((history/'helper-audit.json').read_bytes())
    assert report['accepted'] is True and report['kernel_replay'] is True and len(report['names'])==7
    save(HERE/'historical-bindings.json',{'run':40420540388,'source_sha256':sha(source),'scope':'Historical original statement/Submission+VerifyFull replay/7explicit roots only; no theorem for replacing public MUL','copies':copied})
    files=[HERE/n for n in ('R19RuntimeCostMain.lean','driver.py','plan-1927003.json','plan-1927005.json','exposed-plans.json','legacy-whole-parser.py','bounded-capture-source.py','historical-bindings.json')]+sorted(history.iterdir())
    components=[{'path':p.relative_to(ROOT).as_posix(),'sha256':sha(p),'bytes':p.stat().st_size} for p in files]
    manifest={'candidate':candidate.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(source),'candidate_bytes':source.stat().st_size,
        'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':'f01-r19-dev-direct-bias-runtime1','parent_sha256':sha(source),
        'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':600,
        'proof_status':'HISTORICAL748999_STATEMENT_REPLAY_7ROOTS_BOUND_PUBLIC_MUL_REMAINS_B2_NEW_GUARDED_EQUIVALENCE_UNKNOWN',
        'performance':'NOT_RUN','formal_submission':'NOT_SUBMITTED','mechanism':'Exact748999 carrier; post-original-statement owned Lake target; same binary inline guardedMul(B2fallback) versus B2, all four Bench.Suite callbacks',
        'components':components,'helper_audit_module':'development-runtime-cost-audit.py','helper_audit_module_sha256':sha(R19/'development-runtime-cost-audit.py'),
        'historical_statement_evidence':{'run':40420540388,'binding_path':(HERE/'historical-bindings.json').relative_to(ROOT).as_posix(),'binding_sha256':sha(HERE/'historical-bindings.json'),'not_rerun':True},
        'runtime_cost':{'overall_budget_seconds_from_stage_registration':580,'build_cap_seconds':180,'measure_phase_cap_seconds':300,'post_tools_phase_cap_seconds':32,'receipt_reserve_seconds':20,
            'reuse_historical_replay_only':True,'seeds':[1927003,1927005],'already_exposed_only':True,'order_per_seed':['control','guarded','guarded','control'],
            'processes':8,'rows_per_process':156,'timed_rows_per_process':152,'pairs':500000,'inner':3,'observer':False,
            'resource_caps':'Original g.own bwrap/systemd scope,build4096MiB and original benchmark memory/CPU; no flag or limit mutation',
            'new_target_is_original_gate_admissible':False,'requires_parent_hook_and_600s_outer_allowance':True},
        'scope':'NOT_RUN independent diagnostic composition only; no original25-round score/gate/adoption or proof of new public MUL. Future caller/transitive shape may differ.'}
    save(candidate/'manifest.json',manifest)
    save(HERE/'package-receipt.json',{'status':'PACKAGED_REMOTE_NOT_RUN','source_sha256':sha(source),'audit_sha256':manifest['helper_audit_module_sha256'],'driver_sha256':sha(HERE/'driver.py'),'caller_sha256':sha(HERE/'R19RuntimeCostMain.lean'),'manifest_sha256':sha(candidate/'manifest.json'),'component_count':len(components)})
if __name__=='__main__':main()
