from pathlib import Path
import hashlib,json,datetime

here=Path(__file__).resolve().parent
root=here.parents[3]
base=root/'competitions/floatlib/candidates/f01-r2-web-packed4/Kernel.lean'
assert hashlib.sha256(base.read_bytes()).hexdigest()=='be7f94691e8a93eeb6f6f704869a280714f01d9f0efca21989d3a7b6eb7136a0'
s=base.read_text(encoding='utf8')
old='''  by_cases hi : i < Araw.size
  · simp only [Array.getD, Array.size_map, dif_pos hi, Array.getElem_map]
  · simp only [Array.getD, Array.size_map, dif_neg hi] <;> rfl'''
new='''  by_cases hi : i < Araw.size
  · simp [zero32, Array.getD, hi]
  · simp [zero32, Array.getD, hi] <;> rfl'''
assert s.count(old)==1;s=s.replace(old,new)
old2='''    simp only [dif_pos hk, if_pos hk]
    dsimp only
    have ih := dot4_lane'''
new2='''    simp only [dif_pos hk, if_pos hk]
    have ih := dot4_lane'''
assert s.count(old2)==1;s=s.replace(old2,new2)
out=root/'competitions/floatlib/candidates/f01-r2-web-packed4-proof1';assert not out.exists();out.mkdir()
(out/'Kernel.lean').write_text(s,encoding='utf8',newline='\n');data=(out/'Kernel.lean').read_bytes()
assert data[:56956]==base.read_bytes()[:56956]
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'parent':base.parent.name,'parent_sha256':hashlib.sha256(base.read_bytes()).hexdigest(),'runtime_change':'NONE: only nativeA_getD proof and redundant dsimp in dot4_lane changed','proof_status':'NOT_RUN: repair actual compiler errors1397/1425 from39670733380','actual_failure_log':'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39670733380/download-a04b3a9bd49c431bbb12b0c42ce227cb/diagnostics/f01-d2-web-packed4/replay.log','repair':'Use full simp for Array.getInternal/map transport, as already full-gated preconverted proof did; remove dsimp that made no progress so recursive proof can elaborate','protected_parent_prefix_bytes':56956,'validation_mode':'statement-only','created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf8');print(json.dumps(m,indent=2))
