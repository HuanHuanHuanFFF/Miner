"""CI3 actual goal: avoid the introduced finRange/list route; use original Fin.foldl equations."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,difflib
H=Path(__file__).resolve().parent;R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').exists());sha=lambda b:hashlib.sha256(b).hexdigest()
run=H.parents[1]/'ci-runs/40491855387';ixraw=(run/'original-artifact-hashes.json').read_bytes();ix=json.loads(ixraw);aroot=run/ix['directory'];c='f01-r21-dev-terminal-dc3';d=aroot/'diagnostics'/c
out=H/'fin-two-repair';ev=out/'ci3';ev.mkdir(parents=True,exist_ok=True)
files=[aroot/'inputs'/c/'Kernel.lean',aroot/(c+'-verdict.json'),d/'full-build-output.txt',d/'replay.log',d/'index.json'];bind=[]
for p in files:
 b=p.read_bytes();v=ix['files'][p.relative_to(aroot).as_posix()];assert sha(b)==v['sha256'] and len(b)==v['bytes'];name='input-2021ce.lean' if p.name=='Kernel.lean' else p.name;(ev/name).write_bytes(b);bind.append({'path':str(p.resolve()),'sha256':sha(b),'bytes':len(b),'copy':name})
base=files[0].read_bytes();assert sha(base)=='2021ce5f2e26711314f9a21c6503be40e89c2fb8c052d0f9f90230bd40abe394'
assert base==(R/'competitions/floatlib/candidates/f01-r21-dev-terminal-dc3/Kernel.lean').read_bytes()
before=b'    simp [emit2, RowStream.emit, Fin.foldl_eq_finRange_foldl, select]\n'
after=b'''    unfold emit2 RowStream.emit
    rw [Fin.foldl_succ, Fin.foldl_succ, Fin.foldl_zero] <;>
      simp only [select, Nat.add_zero, \xe2\x86\x93reduceIte]
'''
assert base.count(before)==1
fixed=base.replace(before,after,1);assert fixed.replace(after,before,1)==base and len(fixed)<256000
lo=base.index(b'theorem groupFrom_eq_original');hi=base.index(b'@[inline] def group (',lo);assert lo<base.index(before)<hi
source=out/'Kernel-terminal-fin2-repair.lean';source.write_bytes(fixed)
patch=''.join(difflib.unified_diff(base.decode().splitlines(keepends=True),fixed.decode().splitlines(keepends=True),fromfile='actual-CI3-dc3-2021ce.lean',tofile='original-fin2-equations.lean'));(out/'proof-only.patch').write_bytes(patch.encode())
roots=json.loads((R/'competitions/floatlib/candidates/f01-r21-dev-terminal-dc3/manifest.json').read_bytes())['explicit_helper_audit'];assert len(roots)==9
(out/'HelperAudit.lean.inc').write_text('\n'.join('#print axioms '+x for x in roots)+'\n')
m={'at_utc':datetime.now(timezone.utc).isoformat(),'failed_run':40491855387,'old_sha256':sha(base),'new_source':str(source.relative_to(H)),'new_sha256':sha(fixed),'new_bytes':len(fixed),'original_index_sha256':sha(ixraw),'original_bindings':bind,'only_change':'Replace the list-converting final simp in groupFrom_eq_original by unfold emit2/RowStream.emit and Fin.foldl_succ twice / Fin.foldl_zero, then scalar selector simplification','runtime_domain_statements_all_other_bytes_identical':True,'inverse_exact':True,'patch_sha256':sha(patch.encode()),'roots':roots,'expected_count':9,'formal':'NOT_RUN_NEW_PROOF_COPY','scope':'No guess about raw fold reducibility; fixed primary Fin APIs perform both iterations. No List/Array append bridge needed.','local_Lean':False,'Git':False,'CI_dispatch':False}
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps({k:m[k] for k in ('new_source','new_sha256','new_bytes','inverse_exact','expected_count','formal')}))
