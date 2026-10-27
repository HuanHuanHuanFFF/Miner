from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re
H=Path(__file__).resolve().parent;C=H.parents[3]/'competitions/floatlib/candidates'
p=C/'f01-r7-sum-singlepass-fused/Kernel.lean';b=p.read_bytes();assert hashlib.sha256(b).hexdigest()=='8ec342ec4bb9f7f72629ee219931fd0f8212c998de92876a2ab413a5466f5ef6'
old=(H/'singlepass-sum-block.lean').read_text();s=b.decode();assert s.count(old)==1
web=H/'web/R7-W12b/original-extracted/R7-W12b/R7W12bIncrement.lean';wb=web.read_bytes();assert hashlib.sha256(wb).hexdigest()=='415bc6b9c6af184f0746181ae577eae4f96611b07e12cb21818d37a9ea8eb0ca'
w=web.read_text();a=w.index('theorem low_false_lt_inf');z=w.index('/-- Exact Bool-branch',a);low=w[a:z].replace('low_false_lt_inf','low_reject_finite')
a=old.index('theorem low_reject_finite');z=old.index('theorem raw_nonNaN_of_le',a);new=old[:a]+low+old[z:]
new=new.replace('  exact decide_eq_true h\n','  unfold R7W12.rawNotNaN\n  rw [decide_eq_true_eq]\n  exact h\n')
new=new.replace('(le_of_lt hh)','(UInt32.le_of_lt hh)').replace('have hle := le_of_lt (low_reject_finite _ hl)','have hle := UInt32.le_of_lt (low_reject_finite _ hl)')
new=new.replace('(0x7f800000 : UInt32) := le_of_eq hinf','(0x7f800000 : UInt32) := by\n            rw [hinf]')
new=new.replace('  simpa only [R2W01b.convert, hg, Bool.true_eq, ite_true] using h','  simpa only [R2W01b.convert, if_pos hg] using h')
# Runtime declarations, including all three loops, are identical bytes.
def runtime(t):
 names=['natLoop','loop','run'];out={}
 for name in names:
  pat=('def '+name+' ')
  a=t.index(pat);z=t.index('\ntheorem ',a)
  out[name]=t[a:z]
 return out
assert runtime(new)==runtime(old)
(H/'singlepass-sum-block.draft8ec.lean').write_text(old,encoding='utf-8',newline='\n')
(H/'singlepass-sum-block.lean').write_text(new,encoding='utf-8',newline='\n')
out=s.replace(old,new).encode();d=C/'f01-r7-sum-singlepass-fused-proof1';d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(out)
m=json.loads(p.with_name('manifest.json').read_text());m.update(candidate=d.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=p.parent.name,parent_sha256=hashlib.sha256(b).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),proof_status='NOT_RUN_PROOF_REVIEWED_SINGLE_RUNTIME',repair='Adopt exactW12b low-guard wrap proof, use explicitUInt32 order lemmas, use actualconvert if_pos rewrite. Allruntime declaration bytes unchanged. Exactcandidate integration stillNOT_RUN; no claim originaldraftactuallyfailed.',ready_for_D=True)
m['proof_derivation']['W12b_increment_sha256']=hashlib.sha256(wb).hexdigest()
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
receipt={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'old_sha256':hashlib.sha256(b).hexdigest(),'new_sha256':hashlib.sha256(out).hexdigest(),'source_outside_new_sum_proofblock_byte_identical':s.replace(old,'<BLOCK>')==out.decode().replace(new,'<BLOCK>'),'runtime_declaration_text_identical':True,'runtime_declaration_sha256':{k:hashlib.sha256(v.encode()).hexdigest() for k,v in runtime(new).items()},'not_claimed':['Exactcandidate Lean acceptance','Generatedmachinecode identity','Performance gain']}
(H/'singlepass-proof1-lineage.json').write_text(json.dumps(receipt,indent=2)+'\n');print(json.dumps(m,indent=2))
