from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('--parent',default='f01-r7-nonfinite-combined');ap.add_argument('--name',default='f01-r7-self-nonnan-guard');args=ap.parse_args()
assert args.parent.startswith('f01-r7-') and args.name.startswith('f01-r7-')
p=ROOT/'competitions/floatlib/candidates'/args.parent/'Kernel.lean';b=p.read_bytes();pm=json.loads(p.with_name('manifest.json').read_text());assert hashlib.sha256(b).hexdigest()==pm['candidate_sha256']
w=HERE/'web/R7-W04/original-extracted/R7-W04/R7W04.lean';wb=w.read_bytes();assert hashlib.sha256(wb).hexdigest()=='3668cbf3f7bab305ace60be4cdec39e5eb6d78c222d6c1630d699ba95d5fcaff'
proof=wb.decode().split('private theorem unpacked_self_le_eq_not_isNaN')[0]+'\nend R7W04\n';assert proof.startswith('import ContractTensor\n');proof=proof[len('import ContractTensor\n'):]
s=b.decode();s=s.replace('import ContractTensor\n','import ContractTensor\n'+proof+'\n',1)
old='if hf : result.isNaN = false then ExecFloat.Binary.ofFloat32 result';assert s.count(old)==4
s=s.replace(old,'if hf : R7W04.nonNaN result = true then ExecFloat.Binary.ofFloat32 result')
old='''  · rename_i hf
    have h := (dotLoop_eq n baseA baseB p A B 0 (Float32.ofBits 0) _ rfl hf).2'''
new='''  · rename_i hf
    have hnon := (R7W04.nonNaN_eq_true_iff _).mp hf
    have h := (dotLoop_eq n baseA baseB p A B 0 (Float32.ofBits 0) _ rfl hnon).2'''
assert s.count(old)==1;s=s.replace(old,new)
old='''  · rename_i hf
    have h := (NativeFinal.sumLoop_eq x 0 (Float32.ofBits 0) _ rfl hf).2'''
new='''  · rename_i hf
    have hnon := (R7W04.nonNaN_eq_true_iff _).mp hf
    have h := (NativeFinal.sumLoop_eq x 0 (Float32.ofBits 0) _ rfl hnon).2'''
assert s.count(old)==1;s=s.replace(old,new)
out=s.encode();d=ROOT/'competitions/floatlib/candidates'/args.name;d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(out)
m={'candidate':args.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':args.parent,'parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN_NEW_INTEGRATION','validation_mode':'full-gate','web_proof_original_sha256':hashlib.sha256(wb).hexdigest(),'proof_derivation':'Preserve exact W04 BEq proof prefix and true/false iff; omit unrelated optional <= proof. Each actual nonNaN guard proof converts its premise with concrete iff, all existing induction bridges unchanged.','mechanism':'Replace precisely four actual terminal native nonNaN classifiers with inline Float32 self-BEq in NativeFinal.dot/originalSum/Packed10.finish/finalsum. NaN payload repair, prefix iterations, scalar arithmetic, layout and input preparation unchanged.','expected_gain':'UNKNOWN; supplied GCC codegen confirms removal of externalisnan in tiny probes, not current officialclang full-candidate timing. Complete paired publicgate versus b169 required.','formal_submission':'NOT_SUBMITTED'}
m['expected_gain']=m['expected_gain'].replace('versus b169', 'versus '+args.parent)
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
