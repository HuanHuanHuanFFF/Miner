from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re
H=Path(__file__).resolve().parent;R=H.parents[3];C=R/'competitions/floatlib/candidates'
p=C/'f01-r7-nonnan-runtime/Kernel.lean';b=p.read_bytes();assert hashlib.sha256(b).hexdigest()=='c76056882d69a1122da44b4bc0bb3ab5274251826f0677af2aec5771926d7435'
def exact(rel,sha):
 p=H/rel;b=p.read_bytes();assert hashlib.sha256(b).hexdigest()==sha;return b.decode()
math=exact('web/R7-W13/original-extracted/R7-W13/R7W13Increment.lean','55ce42724776e218139bd702373829ca55910955c07f8f0821ba2feaf949b620')
guard=exact('web/R7-W13b/original-extracted/R7-W13b/R7W13bIncrement.lean','f7d2cd47627ba56aa1f4d1b41800fdc289355587ed6b466dae8659d557db0e91')
constant=(H/'web/R7-W14b/original-extracted/R7-W14b/source/ConstantSource.lean').read_text()
constant=constant[constant.index('namespace R7W14b'):].replace('R7W14b','R7LowTableDecode')
# The whole exact candidate still requires Lean; 8192 is the official allowed maximum.
block='\n'+math+'\n'+guard+'\nset_option maxRecDepth 8192\n\n'+constant+'\n'+(H/'low-normal-runtime-tail.lean').read_text()+'\n'
assert not re.search(r'\bimport\b',block) and 'maxRecDepth 10000' not in block
s=b.decode();marker='namespace Submission.NativeDecodeSum\n';assert s.count(marker)==1;s=s.replace(marker,block+marker,1)
old='@[inline] def decode (x : Binary32) : Float32 := R2W01b.convert x.raw.1\n\ntheorem decode_eq (x : Binary32) : decode x = ExecFloat.Binary.toFloat32 x := by\n  unfold decode\n  rw [R2W01c.convert_eq]\n  rfl'
new=old.replace('R2W01b.convert x.raw.1','R7LowTableDecode.convert x.raw.1').replace('rw [R2W01c.convert_eq]','rw [R7LowTableDecode.convert_eq]')
assert s.count(old)==1;s=s.replace(old,new,1);out=s.encode()
assert s.replace(block,'',1).replace(new,old,1).encode()==b
assert len(out)<=256000
d=C/'f01-r7-low-normal-sum-decode';d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(out)
m={'candidate':d.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':p.parent.name,'parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN_EXACT_KERNEL_NAMESPACE_AND_OPTION_INTEGRATION','validation_mode':'statement-only','mechanism':'Only NativeDecodeSum.decode replaced. Original low/high decoderconditions retained; original lowfailure normal e1..23 uses proved exponent+32 tableproduct then2^-32 via existingtable118. Zero/subnormal/nonfinite/allotherwords exactlysameFloat32result. Existing USize/Nat sumloops andexactNaNrawfallback unchanged; scalaradd/mul/BMMdefinitions unchanged. One decoder-only controlled mechanism, notcombinedwith3d9 singlepasssum.','proof_sources':{'W13':'55ce42724776e218139bd702373829ca55910955c07f8f0821ba2feaf949b620','W13b':'f7d2cd47627ba56aa1f4d1b41800fdc289355587ed6b466dae8659d557db0e91','W14b_constant_source_sha256':hashlib.sha256((H/'web/R7-W14b/original-extracted/R7-W14b/source/ConstantSource.lean').read_bytes()).hexdigest(),'mapping':'Only newconstantnamespaceR7LowTableDecode; maxRecDepth8192 replaces prototype10000; two newactualvalueequivalence bridges; exacttypeddecodepointwire. No source ofprivatecandidate senttoweb.'},'runtime_evidence':'W14b standaloneactualLean/clangO3 low-normal Natloop removesinputofBits/once-state/hotFPspill; this exactUSizecandidateC/benchmarkNOTRUN. Unusedmathematicalreferencehelpers remainin source; no claim wholemodulehasnoonce orcodebytesunchanged.','performance':'UNKNOWN. 807countedlow-normalprefix295268/5035892words isnotatimefraction; extraarithmetic/tableloads/ordinarybranchlayout requirefullpairedcost.','source_identity':'Removingnewblock andundoingonlydecodebody/proofrewire exactlyrecoversc760 originalbytes.','formal_submission':'NOT_SUBMITTED','ready_for_D':False}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
(H/'low-normal-candidate-lineage.json').write_text(json.dumps({'created_at_utc':m['created_at_utc'],'candidate_sha256':m['candidate_sha256'],'parent_sha256':m['parent_sha256'],'inverse_transform_byte_identity':'PASS','parent_runtime_change':'Only NativeDecodeSum.decode call target; add/mul/BMM andsumloop/fallback bodybytes retained','not_claimed':['Exactcandidate compile','Machinecodeidentity','Speedup']},indent=2)+'\n')
print(json.dumps(m,indent=2))
