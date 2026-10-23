"""Expose concrete callbacks through the one actual wide runtime chain."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json
HERE=Path(__file__).resolve().parent
CS=HERE.parent
PARENT=CS/'f01-r11-wide4-actual-proof2/Kernel.lean'
EXPECTED='aa83734680e49eacdd7734089cb870fc531a57432f9e34121dcb8b823710c12e'
sha=lambda b:hashlib.sha256(b).hexdigest()
TARGETS={'Submission.R11WideLayout':['emitBlock','writeBatch','output'],
         'Submission.R11WideActual':['buildTiles','output']}
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');a=ap.parse_args()
    original=PARENT.read_bytes();assert sha(original)==EXPECTED
    text=original.decode();replacements=[]
    for ns,names in TARGETS.items():
        start=text.index('namespace '+ns+'\n');end=text.index('end '+ns,start)
        old=text[start:end];new=old
        for name in names:
            needle='\ndef '+name+' ('
            assert new.count(needle)==1
            new=new.replace(needle,'\n@[inline] def '+name+' (')
        text=text[:start]+new+text[end:];replacements.append((old,new))
    inverse=text
    for old,new in reversed(replacements):
        assert inverse.count(new)==1;inverse=inverse.replace(new,old)
    assert inverse.encode()==original
    data=text.encode();assert len(data)<=256000
    spec=importlib.util.spec_from_file_location('p',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p);p.static_check(text)
    rec={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
         'parent':PARENT.parent.name,'parent_sha256':EXPECTED,'created_at_utc':datetime.now(timezone.utc).isoformat(),
         'change':'Five permitted inline attributes expose concrete lane40/buildTiles callbacks through Layout emitBlock/writeBatch/output and Actual buildTiles/output. No runtime expressions, guards, loop order, cache scope or proofs changed.',
         'trigger':'Root authorized concrete high-order chain inline after source review; actual callback elimination UNKNOWN until same-object caller C/asm.',
         'inline_targets':TARGETS,'exact_inverse_parent':True,'proof_status':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN',
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
