"""Exact28b819 prefix plus the existing2085B proof-only namespace; no active entry change."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent
PARENT=CS/'f01-r11-wide4-inline-proof3/Kernel.lean'
ASSET=CS/'f01-d7-research/round7h-20261023T193125Z/astra-wide-guard-proof.lean'
PARENT_SHA='28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b'
ASSET_SHA='f40c26861a780997a42c6142c15da19da53a7e749454bcb5b2971e21dae69677'
sha=lambda b:hashlib.sha256(b).hexdigest()
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');a=ap.parse_args()
    raw=PARENT.read_bytes();proof=ASSET.read_bytes()
    assert len(raw)==253315 and sha(raw)==PARENT_SHA
    assert len(proof)==2085 and sha(proof)==ASSET_SHA
    assert raw.endswith(b'\n') and proof.endswith(b'\n')
    data=raw+proof
    assert len(data)==255400 and len(data)<=256000
    assert data[:len(raw)]==raw and data[len(raw):]==proof
    assert proof.count(b'namespace Submission.R11WideGuardBridge')==1
    assert b'\ndef ' not in proof and proof.count(b'\ntheorem ')==4
    spec=importlib.util.spec_from_file_location('policy',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p);p.static_check(data.decode())
    rec={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
         'created_at_utc':datetime.now(timezone.utc).isoformat(),'parent':PARENT.parent.name,'parent_sha256':PARENT_SHA,
         'parent_bytes':len(raw),'proof_asset':str(ASSET),'proof_asset_sha256':ASSET_SHA,'proof_asset_bytes':len(proof),
         'exact_parent_prefix':True,'active_four_entries_and_specs':'BYTE_IDENTICAL_PREFIX',
         'new_runtime_definitions':0,'new_theorems':['Submission.R11WideGuardBridge.'+n for n in ['block_span','sized_block_span','sized_array_fits','direct_within_projects']],
         'validation_mode':'statement-only','proof_status':'NOT_RUN','kernel_replay':'NOT_RUN','axiom_audit':'NOT_RUN',
         'full_gate':'NOT_RUN','performance':'NOT_APPLICABLE_UNUSED_THEOREMS','matrix_algorithm_acceptance':'NOT_APPLICABLE_NO_NEW_ENTRY',
         'formal_submission':'NOT_SUBMITTED','source_headroom':256000-len(data),'static_policy':'PASS',
         'scope':'Future typed guard-erasure interface only; currentrun/checks/dispatcher unchanged. Root owns short statement, no R Git/CI/reset.',
         'build_script_sha256':sha(Path(__file__).read_bytes())}
    if a.write:
        assert not (HERE/'Kernel.lean').exists()
        (HERE/'Kernel.lean').write_bytes(data)
        (HERE/'proof-asset.lean').write_bytes(proof)
        (HERE/'manifest.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        (HERE/'exact-inverse.json').write_text(json.dumps({'remove_suffix_bytes':len(proof),'suffix_sha256':ASSET_SHA,
            'result_parent_bytes':len(raw),'result_parent_sha256':PARENT_SHA,'active_prefix_byte_identical':True,
            'source_notices_unchanged':True,'resource_options_unchanged':True,'no_active_runtime_delta':True},indent=2)+'\n',encoding='utf-8')
    else:
        assert (HERE/'Kernel.lean').read_bytes()==data
        assert json.loads((HERE/'manifest.json').read_text(encoding='utf-8'))['candidate_sha256']==sha(data)
    print(json.dumps({k:rec[k] for k in ['candidate','candidate_sha256','candidate_bytes','source_headroom','proof_status','static_policy','new_runtime_definitions']}))
if __name__=='__main__':main()
