"""Actual CI2 dependent-count goal. Local universal emit lemma, explicit fixed Fin fold equations."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,difflib,re
H=Path(__file__).resolve().parent;R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').exists());sha=lambda b:hashlib.sha256(b).hexdigest()
run=H.parents[1]/'ci-runs/40490738328';ixraw=(run/'original-artifact-hashes.json').read_bytes();ix=json.loads(ixraw);aroot=run/ix['directory'];c='f01-r21-dev-terminal-dc2';d=aroot/'diagnostics'/c
out=H/'count-two-repair';ev=out/'ci2';ev.mkdir(parents=True,exist_ok=True)
files=[aroot/'inputs'/c/'Kernel.lean',aroot/(c+'-verdict.json'),d/'full-build-output.txt',d/'replay.log',d/'index.json'];bind=[]
for p in files:
 b=p.read_bytes();v=ix['files'][p.relative_to(aroot).as_posix()];assert sha(b)==v['sha256'] and len(b)==v['bytes']
 name='input-0f389.lean' if p.name=='Kernel.lean' else p.name;(ev/name).write_bytes(b);bind.append({'original':str(p.resolve()),'sha256':sha(b),'bytes':len(b),'copy':name})
base=files[0].read_bytes();assert sha(base)=='0f389fa7f9237b446dbc7faad56040e884367fd5751af4345b648b7971bb4ba3'
assert base==(R/'competitions/floatlib/candidates/f01-r21-dev-terminal-dc2/Kernel.lean').read_bytes()
s=base.decode();a=s.index('theorem groupFrom_eq_original');z=s.index('@[inline] def group (',a);old=s[a:z]
assert '    simp only [hc]\n    rfl\n' in old
new=old.replace('    simp only [hc]\n    rfl\n','''    have emit_two (count : Nat) (hcount : count=2) (read : Fin count → Binary32) :
        RowStream.emit count read out =
          (out.push (read ⟨0,by omega⟩)).push (read ⟨1,by omega⟩) := by
      subst count
      unfold RowStream.emit
      rw [Fin.foldl_succ, Fin.foldl_succ, Fin.foldl_zero] <;> rfl
    exact (emit_two (min 2 (p - 2 * g.val)) hc
      (fun l => Packed10.finish n baseA ((baseB + 2 * g.val) + l.val) p A B
        (select (loop n baseA (baseB + 2 * g.val) p A B
          0 Packed10.zero32 Packed10.zero32) l.val))).symm
''',1)
fixed=(s[:a]+new+s[z:]).encode();assert len(fixed)<256000
assert old[:old.index(':= by')]==new[:new.index(':= by')]
assert fixed.startswith(s[:a].encode()) and fixed.endswith(s[z:].encode())
source=out/'Kernel-terminal-count2-repair.lean';source.write_bytes(fixed)
patch=''.join(difflib.unified_diff(s.splitlines(keepends=True),fixed.decode().splitlines(keepends=True),fromfile='CI2-dc2-0f389.lean',tofile='count2-local-bridge.lean'))
(out/'proof-only.patch').write_bytes(patch.encode())
assert fixed.decode().replace(new,old,1).encode()==base
(out/'replacement-proof.lean.inc').write_bytes(new.encode())
oldmf=json.loads((R/'competitions/floatlib/candidates/f01-r21-dev-terminal-dc2/manifest.json').read_bytes());roots=oldmf['explicit_helper_audit'];assert len(roots)==9
(out/'HelperAudit.lean.inc').write_text('\n'.join('#print axioms '+x for x in roots)+'\n')
m={'at_utc':datetime.now(timezone.utc).isoformat(),'failed_run':40490738328,'old_sha256':sha(base),'new_source':str(source.relative_to(H)),'new_sha256':sha(fixed),'new_bytes':len(fixed),'original_index_sha256':sha(ixraw),'original_bindings':bind,'changed_only':'groupFrom_eq_original proof body: replace unused count simp/rfl by local forall count=2 dependent-read bridge; subst independent count, explicit Fin.foldl_succ twice and zero','runtime_domain_all_other_bytes_identical':True,'old_statement_unchanged':True,'inverse_exact':True,'patch_sha256':sha(patch.encode()),'helper_roots':roots,'expected_count':9,'upstream_API':'Lean293d5d0 src/Init/Data/Fin/Fold.lean: foldl_succ254, foldl_zero251; Git blob f7039a47718cebc8c50a64f868667c69a0d5dcd8','formal':'NOT_RUN_NEW_PROOF_COPY','local_Lean':False,'CI_dispatch':False,'Git':False}
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps({k:m[k] for k in ('new_source','new_sha256','new_bytes','runtime_domain_all_other_bytes_identical','inverse_exact','expected_count','formal')}))
