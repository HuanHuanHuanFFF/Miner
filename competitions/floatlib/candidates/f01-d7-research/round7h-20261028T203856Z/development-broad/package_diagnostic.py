"""Adapt the retained fixed audit, preserving its lifecycle/build checks."""
from pathlib import Path
import hashlib
import json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
OLD=ROOT/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z'
CAND=ROOT/'competitions/floatlib/candidates/f01-r24-dev-broad-nativepair-cost1'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    source=sha(CAND/'Kernel.lean')
    olddriver=OLD/'development-indexed8/driver.py'
    assert sha(olddriver)=='3ff2375738b651f40539d936e4367f59627307c14b98adbda9837743a7999ca8'
    driver=olddriver.read_text(encoding='utf-8')
    changes={
        '8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd':source,
        'R22Indexed8CostMain':'R24BroadCostMain','r22Indexed8Cost':'r24BroadCost',
        'R22MultiStaticCostLake':'R24BroadCostLake',
        '(2220001, 2220003)':'(2428001, 2428003)',
        "('raw8','indexed8')":"('nativearray','checkedflat')",
        "('runControl','runRaw8','runIndexed8')":"('runControl','runNativeArray','runCheckedFlat')",
        'Exact compiledR22Cost runtime required':'Exact compiled R24 broad runtime required',
        'Variants raw8/indexed8 changeBMM only, same8MAC/codec/pack/finish, newmachineword indices andfullNatfallback':'Variants nativearray/checkedflat change complete BMM only: prepare both native arrays once, paired output chains, single odd tail, original finish/NaN raw replay and complete failure fallback',
    }
    for old,new in changes.items():
        assert old in driver,old
        driver=driver.replace(old,new)
    (HERE/'driver.py').write_text(driver,encoding='utf-8',newline='\n')
    audit=(OLD/'development-indexed8-cost-audit.py').read_text(encoding='utf-8')
    audit=audit.replace('8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd',source)
    audit=audit.replace("here/'development-indexed8'","here")
    audit=audit.replace("here/'development-indexed8/driver.py'","here/'driver.py'")
    audit=audit.replace('ExactB2_622d_prefix; IndexedResident8 not proved','Exact B2/622d prefix; broad native pair BMM not proved')
    (HERE/'runtime_cost_audit.py').write_text(audit,encoding='utf-8',newline='\n')
    static=OLD/'development-indexed8/static_runner_audit.py'
    assert sha(static)=='1806bb3c9a6aa4285a22a7a811d070c3257537d92295b9c8b79be832ce1efe00'
    (HERE/'static_runner_audit.py').write_bytes(static.read_bytes())
    components=[]
    for name in ('driver.py','R24BroadCostMain.lean','static_runner_audit.py','BroadNativePair.lean.inc','build_candidate.py','package_diagnostic.py'):
        p=HERE/name;components.append({'path':p.relative_to(ROOT).as_posix(),'sha256':sha(p),'bytes':p.stat().st_size})
    manifest={
        'candidate':CAND.name,'candidate_file':'Kernel.lean','candidate_sha256':source,
        'candidate_bytes':(CAND/'Kernel.lean').stat().st_size,'parent_sha256':sha(ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'),
        'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':600,
        'proof_status':'NOT_RUN_PUBLIC_ENDPOINTS_B2_NEW_BMM_NOT_PROVED','performance':'NOT_RUN',
        'formal_submission':'NOT_SUBMITTED','official_submission_inherited':False,
        'helper_audit_module':'runtime_cost_audit.py',
        'helper_audit_module_path':(HERE/'runtime_cost_audit.py').relative_to(ROOT/'competitions/floatlib/candidates').as_posix(),
        'helper_audit_module_sha256':sha(HERE/'runtime_cost_audit.py'),'components':components,
        'runtime_cost':{'overall_budget_seconds_from_stage_registration':580,'build_cap_seconds':180,'measure_phase_cap_seconds':300,'seeds':[2428001,2428003],'order_per_seed':['control','nativearray','nativearray','control','control','checkedflat','checkedflat','control'],'processes':16,'pairs':500000,'inner':3,'observer':False},
        'scope':'One structural broad BMM diagnostic, no shape/guard sweep. Original B2 underflow shortcut, n<=1 full fallback; n>1 all shapes. Array native scalar caches versus checked contiguous F64 storage with F32 operations. Whole callback includes preparation/checking/failed prefix release/fallback, original raw NaN replay, odd single tail and output release. Numerical correctness UNKNOWN before complete endpoint proof.',
        'sources':{'base':'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean','base_prefix_exact':True,'new_fragment':(HERE/'BroadNativePair.lean.inc').relative_to(ROOT).as_posix()}
    }
    (CAND/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'candidate':CAND.name,'kernel_sha256':source,'manifest_sha256':sha(CAND/'manifest.json'),'helper_sha256':manifest['helper_audit_module_sha256'],'bytes':manifest['candidate_bytes']},indent=2))

if __name__=='__main__':main()
