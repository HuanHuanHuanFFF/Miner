"""Adapt the last audited local evidence tools; do not edit frozen old rounds."""
from pathlib import Path
import hashlib, json
OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
OLD=OUT.parent/'round3h-20261024T112622Z'
files=['prepare-plan.py','freeze-cohort.py','verify-three-groups.py','summarize-run.py','adopt-three-confirmed.py','refresh-retained-metadata.py','execution-binding.py','selection-policy.json']
record={}
new_ci=(OUT/'development-ci.py').relative_to(ROOT).as_posix()
for name in files:
    src=OLD/name; raw=src.read_bytes(); text=raw.decode().replace('R13-20261024T112622Z','R14-20261024T190259Z').replace('round3h-20261024T112622Z','round8h-20261024T190259Z').replace('R13','R14').replace('r13','r14')
    text=text.replace('competitions/floatlib/candidates/f01-mul-log2-proof1/ci.py',new_ci)
    dst=OUT/name
    assert not dst.exists(), dst
    dst.write_bytes(text.encode())
    if name.endswith('.py'): compile(text,str(dst),'exec')
    record[name]={'from':src.relative_to(ROOT).as_posix(),'source_sha256':hashlib.sha256(raw).hexdigest(),'adapted_sha256':hashlib.sha256(dst.read_bytes()).hexdigest()}
src=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci.py'
raw=src.read_bytes();text=raw.decode().replace("ROOT=Path(__file__).resolve().parents[4]", "ROOT=Path(__file__).resolve().parents[5]")
text=text.replace("evidence=Path(__file__).resolve().parent/'ci-runs'", "evidence=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'")
text=text.replace("ap.add_argument('--seed',default='42');args=ap.parse_args()", "ap.add_argument('--seed',default='42');ap.add_argument('--branch',default='huan/codex-gpt');args=ap.parse_args()")
text=text.replace("assert branch=='codex/multi-track-floatlib'", "assert branch==args.branch and branch.startswith(('codex/','huan/')),'Explicit experimental branch mismatch'")
dst=OUT/'development-ci.py';assert not dst.exists();dst.write_bytes(text.encode());compile(text,str(dst),'exec')
record[dst.name]={'from':src.relative_to(ROOT).as_posix(),'source_sha256':hashlib.sha256(raw).hexdigest(),'adapted_sha256':hashlib.sha256(dst.read_bytes()).hexdigest(),'changes':'New root depth, explicit branch, retain immutable common ci-runs evidence location for unchanged adoption guard.'}
plan_path=OUT/'round-plan.json';plan=json.loads(plan_path.read_bytes())
plan['id']=plan['round'];plan['frozen_current_model_sha256']='5d946420b8e1a7ecc68aacde44b0e2910a467ee3e3546724d502f252fe8a031f'
plan_path.write_bytes((json.dumps(plan,ensure_ascii=False,indent=2)+'\n').encode())
(OUT/'development-tool-provenance.json').write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps({'adapted_files':len(record),'old_round_modified':False}))
