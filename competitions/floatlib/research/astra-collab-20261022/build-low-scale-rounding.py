from pathlib import Path
import hashlib,json,datetime

here=Path(__file__).resolve().parent
root=here.parents[3]
base=root/'competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean'
assert hashlib.sha256(base.read_bytes()).hexdigest()=='86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217'
fragment=(here/'low-scale-rounding-draft.lean').read_text(encoding='utf8').removeprefix('import ContractTensor\n\n')
out=root/'competitions/floatlib/candidates/f01-r2-low-scale-rounding-proof';assert not out.exists();out.mkdir()
(out/'Kernel.lean').write_text(base.read_text(encoding='utf8')+'\n'+fragment,encoding='utf8',newline='\n');data=(out/'Kernel.lean').read_bytes()
manifest={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),'parent':base.parent.name,'parent_sha256':hashlib.sha256(base.read_bytes()).hexdigest(),'validation_mode':'statement-only','proof_status':'NOT_RUN: bounded roundLow equality and total guarded-selector equality','runtime_change_to_entry':'NONE: all four exported entry functions unchanged; helper feasibility only','mechanism':'When product<2^48 and scale<=123, leading<=47 and position<=170<172. Skip log2/normalization classification; keep existing subnormal rounding and packing. No duplicate hardware/software hybrid dispatcher.','next_integration':'D may consume roundLow/roundSelect in its existing proved low-exponent software branch only after this helper compiles; actual integrated source requires own full gate/timing.','created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8');print(json.dumps(manifest,indent=2))
