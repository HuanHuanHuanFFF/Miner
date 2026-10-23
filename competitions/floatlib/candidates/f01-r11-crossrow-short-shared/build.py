"""Prepare only: rebase web short-n A on exact proof2. No dispatch authority."""
from pathlib import Path
import argparse,difflib,hashlib,importlib.util,json,zipfile
from datetime import datetime,timezone
HERE=Path(__file__).resolve().parent
CS=HERE.parent
PARENT=CS/'f01-r11-crossrow-p2-pack12-proof2/Kernel.lean'
EXPECTED='5c5e7071927400ecd75d02d69b0ce62236a50a615912d99e7f8470a9ccf19c6b'
ARCHIVE=Path('E:/Download/R11-W03.zip')
def sha(b):return hashlib.sha256(b).hexdigest()
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');args=ap.parse_args()
    raw=PARENT.read_bytes();assert sha(raw)==EXPECTED
    assert sha(ARCHIVE.read_bytes())=='58cb49f49c6325a795348f7fd0736de3d6974cb69c6e6d1a3f34f8d8082b7da9'
    with zipfile.ZipFile(ARCHIVE) as z:
        donor=z.read('R11-W03/agent-candidates/Kernel.short-shared.lean')
        assert sha(donor)=='5645b861ce6eeaa00cbb80a791dcb225dca75463f1816ca051d52fe6b62ba910'
    text=raw.decode();ds=donor.decode();ns=text.index('namespace Submission.R11CrossRows')
    a=text.index('def dot8 (',ns);e=text.index('\ndef laneIndex',a)
    da=ds.index('@[inline] def read32',ds.index('namespace Submission.R11CrossRows'))
    de=ds.index('\ndef laneIndex',da);insert=ds[da:de]
    old='    simpa only [lane_zero] using\n      natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B 0 zero8 l'
    fixed='    have h := natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B 0 zero8 l\n    rw [lane_zero] at h\n    simpa only [zero8] using h'
    assert insert.count(old)==1;insert=insert.replace(old,fixed)
    new=text[:a]+insert+text[e:];data=new.encode()
    assert len(data)<=256000
    inverse=new[:a]+text[a:e]+new[a+len(insert):];assert inverse.encode()==raw
    # A second independent inverse removes exactly the three real proof2 repairs
    # from the rebased child and recovers the exact web A source, runtime included.
    repairs=json.loads((CS/'f01-r11-crossrow-p2-pack12-proof2/proof-repair-review.json').read_text())['replacements']
    donor_inverse=new
    for r in repairs:
        if r['theorem']!='dot8_lane':
            assert donor_inverse.count(r['new'])==1
            donor_inverse=donor_inverse.replace(r['new'],r['old'])
    assert donor_inverse.count(fixed)==1
    donor_inverse=donor_inverse.replace(fixed,old)
    assert donor_inverse.encode()==donor
    sp=importlib.util.spec_from_file_location('r11_proof2_checks',CS/'f01-r11-crossrow-p2-pack12-proof2/build.py')
    checks=importlib.util.module_from_spec(sp);sp.loader.exec_module(checks);checks.static_check(new)
    verdict=CS/'f01-mul-log2-proof1/ci-runs/40029166371/download-89f249ddf5f34d25ba61e872ff5eaba4/diagnostics/f01-d7-public-suite/public-suite/f01-r11-crossrow-p2-pack12-proof2-verdict.json'
    assert sha(verdict.read_bytes())=='3c85a3c7eaa396d57d5c21ebdd5539cf9b5e3b040184ac069893ed71b7400343'
    accepted=json.loads(verdict.read_text());assert accepted['passed'] and accepted['stage']=='statement'
    manifest={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),
              'parent_sha256':EXPECTED,'web_donor_sha256':sha(donor),'archive_sha256':sha(ARCHIVE.read_bytes()),
              'created_at_utc':datetime.now(timezone.utc).isoformat(),'mechanism':'n1/n2 with allfourBbases equal: decode wholeone/twoslices thenunroll8orderedchains; noVectorP12 on selectedgroup. Mixedbases/othern retainparent.',
              'proof_rebase':'Allthree observed908repairs retained, including explicitzero8normalization inside newdot8_lane fallback.',
              'validation_mode':'full-gate','proof_status':'NOT_RUN','full_gate':'NOT_RUN','codegen':'NOT_RUN','performance':'UNKNOWN',
              'formal_submission':'NOT_SUBMITTED','readiness':'FROZEN_READY_FOR_D_STATEMENT' if args.write else 'DRY_RUN_ONLY',
              'parent_statement_pass':{'run':40029166371,'seed':912,'verdict_sha256':sha(verdict.read_bytes()),'scope':'Parentstatementonly; no newcandidateacceptance inherited'},
              'build_script_sha256':sha(Path(__file__).read_bytes()),'attribution':'Web6Pro R11-W03; originalsource notices preserved. A/B are alternative lowerings, onlyA prepared.'}
    report={'manifest':manifest,'inverse_parent_sha256':sha(inverse.encode()),'inverse_web_A_sha256':sha(donor_inverse.encode()),'changed_original_region':{'start':a,'end':e},
            'original_region':text[a:e],'new_region':insert,'static':'PASS','source_margin':256000-len(data)}
    if args.write:
        assert not (HERE/'Kernel.lean').exists() and not (HERE/'manifest.json').exists()
        (HERE/'Kernel.lean').write_bytes(data)
        for n,obj in [('manifest.json',manifest),('source-review.json',report)]:
            (HERE/n).write_text(json.dumps(obj,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    else:
        (HERE/'dry-run.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        patch=''.join(difflib.unified_diff(text.splitlines(keepends=True),new.splitlines(keepends=True),
                    fromfile='a/Kernel.lean',tofile='b/Kernel.lean'))
        (HERE/'planned.patch').write_bytes(patch.encode())
    print(json.dumps({'sha256':sha(data),'bytes':len(data),'static':'PASS','inverse_parent':True,'Kernel_written':args.write,'readiness':manifest['readiness']}))
if __name__=='__main__':main()
