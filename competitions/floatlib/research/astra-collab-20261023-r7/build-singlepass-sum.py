from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent;ROOT=H.parents[3];C=ROOT/'competitions/floatlib/candidates'
p=C/'f01-r7-nonfinite-combined-proof2/Kernel.lean';b=p.read_bytes();assert hashlib.sha256(b).hexdigest()=='0e8bc05ce954e3e8213fbef05ac6041f8f882673c88c1071a3c9d4254a3064cd'
s=b.decode()
w2=H/'web/R7-W02/original-extracted/R7-W02/R7W02Append.lean';wb=w2.read_bytes();assert hashlib.sha256(wb).hexdigest()=='7f2ebdf61b60cc51bbb0a9d27eff5447dedc304cc43c2fd4f64f8511aaa710f4'
raw=wb.decode().split('/- Append after the concretely proved Raw.lean and Step.lean.')[0]
raw=re.sub(r'\bimport\b','dependency',raw)
marker='end R7NaNProof';assert s.count(marker)==1;s=s.replace(marker,marker+'\n\nsection R7SumProof\n'+raw+'\nend R7SumProof\n')
w12=H/'web/R7-W12/original-extracted/R7-W12/R7W12Increment.lean';ib=w12.read_bytes();assert hashlib.sha256(ib).hexdigest()=='d907d96bd44159ba1b85569d7ff6d2d2b04fac0ef18a659665fc35dfd28aa26e'
inc=w12.read_text();closure=inc[:inc.index('end R7W12')+len('end R7W12')]
a=inc.index('def rawNotNaN');start=inc.rfind('namespace R7W12',0,a);end=inc.index('end R7W12',a)+len('end R7W12');guard=inc[start:end]
math=(H/'add-nonsignaling-block.lean').read_text()+'\n'+(H/'canonical-native-block.lean').read_text()+'\n'+closure+'\n'+guard
math=math.replace('R7W05Public.Submission.','Submission.').replace('R7W05Cached.R7W02.','R7W02.')
math=re.sub(r'\bimport\b','native constructor',math)
assert 'R7W05Cached.' not in math and 'R7W05Public.' not in math and '-1#8' not in math
suffix=(H/'sum-native-repair-block.lean').read_text().split('theorem nativeStep_eq')[0]+'\nend R7SumRepair\n'
assert s.count('end R7Native')==1;s=s.replace('end R7Native','end R7Native\n\n'+math+'\n'+suffix,1)
first=s.index('def sum {n : Nat}');last=s.index('end Submission',first)
old=s[first:last];assert old.count('theorem sum_spec')==1
old=old.replace('theorem sum_spec','theorem sumBeforeR7SinglePass_spec');old=re.sub(r'\bsum\b','sumBeforeR7SinglePass',old)
s=s[:first]+old+s[last:]
loop=(H/'singlepass-sum-block.lean').read_text()
s+='\n\nnamespace Submission\n\n'+loop+'\nopen FloatLib.Floats Competition\n\ndef sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R7SinglePassSum.run x\n\ntheorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := R7SinglePassSum.run_spec\n\nend Submission\n'
out=s.encode();assert len(out)<=256000
d=C/'f01-r7-sum-singlepass-fused';d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(out)
m={'candidate':d.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':p.parent.name,'parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN_LOCAL_DRAFT_AWAITING_REVIEW','validation_mode':'statement-only-first','mechanism':'Single native USize ordered prefix from +0; reuse original decoder low/high conditions; only high nonfinite cold branch tests Inf versus NaN. First original rawNaN executes one exact Submission.add and then W02 quiet-sum raw signaling suffix scan. Nativeacc may already be canonicalNaN; all-nonNaN raw input terminates by unconditional native import. Oversized logical vectors use Nat fallback. Other exported kernels unchanged from exact0e8.','proof_derivation':{'W02_append_sha256':hashlib.sha256(wb).hexdigest(),'W12_increment_sha256':hashlib.sha256(ib).hexdigest(),'W05_widths':'Exact format field expressions as actually compiled in W12; numeric8/23 mismatch avoided','new_proofs':'Decoder branch classification, actual native/raw mixed step, first rawNaN quietness, Nat fold equality and USize=Nat, full sumSpec. All exact candidate integration NOT_RUN.'},'finite_model':'singlepass-sum-oracle.json:9200traces/100020branchwords plus35publicsum output wordSHAs andactualchecksumanchors; notfullproof/hardware/performance.','expected_gain':'UNKNOWN. Ordinary input conditions intended reused; generatedC/branchcounts/allocation not yet verified. Source counts807:5035572nativeadds,320repairadds,10952rawsuffixwords,683additional coldInfvsNaN decisions. No speed claimed and no additive gain with earlier sum-prefix mechanism.','formal_submission':'NOT_SUBMITTED','ready_for_D':False}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
