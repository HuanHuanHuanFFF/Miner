from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,difflib
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').exists())
sha=lambda b:hashlib.sha256(b).hexdigest()
run=H.parents[1]/'ci-runs/40489842934';ixraw=(run/'original-artifact-hashes.json').read_bytes();ix=json.loads(ixraw);aroot=run/ix['directory']
c='f01-r20-dev-terminal-dc1';d=aroot/'diagnostics'/c
ps=[aroot/'inputs'/c/'Kernel.lean',aroot/(c+'-verdict.json'),d/'full-build-output.txt',d/'replay.log',d/'index.json']
out=H/'ci1-review';out.mkdir(exist_ok=True);bindings=[]
for p in ps:
 b=p.read_bytes();record=ix['files'][p.relative_to(aroot).as_posix()]
 assert sha(b)==record['sha256'] and len(b)==record['bytes']
 name='input-39626d.lean' if p.name=='Kernel.lean' else p.name
 (out/name).write_bytes(b);bindings.append({'path':str(p.resolve()),'sha256':sha(b),'bytes':len(b),'copy':name})
base=ps[0].read_bytes();assert sha(base)=='39626da401cbdcdf99c0efe089c0cc8ed230fba54b8412248d8c3675b6ca3f2b'
source=R/'competitions/floatlib/candidates/f01-r21-dev-terminal-dc2/Kernel.lean';fixed=source.read_bytes();mf=json.loads((source.parent/'manifest.json').read_bytes());assert mf['candidate_sha256']==sha(fixed)
before=b'simp only [groupFrom, groupFromOriginal, h, if_neg]';after=b'simp only [groupFrom, groupFromOriginal, h, ite_false]'
assert base.count(before)==1 and base.replace(before,after,1)==fixed
assert fixed.replace(after,before,1)==base
lo=base.index(b'theorem groupFrom_eq_original');hi=base.index(b'@[inline] def group (',lo);assert lo<base.index(before)<hi
build=ps[2].read_text();errors=re.findall(r'^error: work/Submission.lean:(\d+):(\d+): (.*)$',build,re.M)
assert errors==[('5966','4','Tactic `rfl` failed: The left-hand side')]
assert 'if False then' in build and 'This simp argument is unused:\n  if_neg' in build and 'This simp argument is unused:\n  hc' in build
v=json.loads(ps[1].read_bytes());assert v['stage']=='statement' and v['passed'] is False
patch=''.join(difflib.unified_diff(base.decode().splitlines(keepends=True),fixed.decode().splitlines(keepends=True),fromfile='CI1-39626d.lean',tofile='D-frozen-dc2.lean'))
(out/'dc1-to-dc2-proof.patch').write_bytes(patch.encode())
record={'at_utc':datetime.now(timezone.utc).isoformat(),'run':40489842934,'old_source_sha256':sha(base),'old_bytes':len(base),'original_index_sha256':sha(ixraw),'bindings':bindings,'D_source':str(source.resolve()),'D_source_sha256':sha(fixed),'D_source_bytes':len(fixed),'only_change':before.decode()+' -> '+after.decode(),'inside_proof':'Submission.R19DCRawPair.groupFrom_eq_original','runtime_all_other_bytes_identical':True,'inverse_replacement_exact':True,'patch_sha256':sha(patch.encode()),'diagnosis':'Residual if False prevents entry into the count=2 fold branch; original log does not establish a Fin.foldl/emit2 mismatch. ite_false directly matches the observed guard.','decision':'Support the already frozen D dc2 retry; do not duplicate or edit it','new_formal':'NOT_RUN_IN_THIS_REVIEW','new_runtime_version_created':False,'local_Lean':False,'Git':False,'CI_dispatch':False}
(H/'dc2-independent-review.json').write_text(json.dumps(record,indent=2)+'\n');print(json.dumps({k:record[k] for k in ('run','D_source_sha256','D_source_bytes','runtime_all_other_bytes_identical','only_change','decision','new_formal')}))
