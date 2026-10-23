"""Resolve the Packed10 zero seed name locally; frozen initial source preserved."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
CS=HERE.parent
PARENT=CS/'f01-r11-wide4-actual/Kernel.lean'
EXPECTED='b554f9fe8e0c89ccb9caa0ddb7806fa11fefdabee6740df7a755b0b8b2e37f58'
sha=lambda b:hashlib.sha256(b).hexdigest()
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');a=ap.parse_args()
    original=PARENT.read_bytes();assert sha(original)==EXPECTED
    old=b'namespace Submission.R11WideRows4\nopen FloatLib.Floats Competition\n\n@[inline] def lane40'
    new=old.replace(b'open FloatLib.Floats Competition\n',b'open FloatLib.Floats Competition\nopen Packed10\n')
    assert original.count(old)==1
    data=original.replace(old,new)
    assert data.replace(new,old)==original and len(data)<=256000
    spec=importlib.util.spec_from_file_location('p',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p);p.static_check(data.decode())
    rec={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
         'parent':PARENT.parent.name,'parent_sha256':EXPECTED,'created_at_utc':datetime.now(timezone.utc).isoformat(),
         'repair':'Open Packed10 within the new run/within wrapper namespace, resolving all forty zero32 initial seeds. No change to loop/layout/guard/writer/old projection.',
         'trigger':'Local static namespace review found zero32 declared only inside Packed10; b554 not yet compiler-tested. Not an observed CI failure.',
         'exact_inverse_parent':True,'new_Lean':'NOT_RUN','proof_status':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN',
         'validation_mode':'full-gate','formal_submission':'NOT_SUBMITTED','static_policy':'PASS','size_margin':256000-len(data),
         'build_script_sha256':sha(Path(__file__).read_bytes())}
    if a.write:
        assert not (HERE/'Kernel.lean').exists()
        (HERE/'Kernel.lean').write_bytes(data)
        (HERE/'manifest.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    else:
        assert (HERE/'Kernel.lean').read_bytes()==data
        assert json.loads((HERE/'manifest.json').read_text(encoding='utf-8'))['candidate_sha256']==sha(data)
    print(json.dumps({k:rec[k] for k in ['candidate','candidate_sha256','candidate_bytes','static_policy','proof_status']}))
if __name__=='__main__':main()
