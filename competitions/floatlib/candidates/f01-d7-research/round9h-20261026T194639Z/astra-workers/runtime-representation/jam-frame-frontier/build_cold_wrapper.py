"""One proof-preserving cold boundary on exact frozen b271; never edit that source."""
from pathlib import Path
import hashlib,json,datetime,difflib
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=HERE.parents[2]
base=ROUND/'astra-workers/exact-arithmetic/repair1/Kernel-jam17-public-repair1-parser.lean'
sha=lambda b:hashlib.sha256(b).hexdigest()
raw=base.read_bytes();assert sha(raw)=='b2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff'
s=raw.decode()
old='''@[inline] def mul (x y : Binary32) : Binary32 := R19Base.R19Jam17.guardedMul R19Base.mul x y
theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  R19Base.R19Jam17.guardedMul_spec R19Base.mul R19Base.mul_spec x y'''
new='''/- R19: isolate the exact old fallback; Jam arithmetic and guards are unchanged. -/
@[noinline] def jamColdFallback (x y : Binary32) : Binary32 := R19Base.mul x y
theorem jamColdFallback_spec (x y : Binary32) :
    jamColdFallback x y = ExecFloat.Spec.mul x y := R19Base.mul_spec x y
@[inline] def mul (x y : Binary32) : Binary32 := R19Base.R19Jam17.guardedMul jamColdFallback x y
theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  R19Base.R19Jam17.guardedMul_spec jamColdFallback jamColdFallback_spec x y'''
assert s.count(old)==1
t=s.replace(old,new);b=t.encode();assert len(b)<=256000
assert t.replace(new,old).encode()==raw
p=HERE/'Kernel-jam-cold-fallback.lean';p.write_bytes(b)
(HERE/'cold-wrapper.patch').write_text(''.join(difflib.unified_diff(s.splitlines(True),t.splitlines(True),fromfile='frozen-b271/Kernel.lean',tofile='jam-cold-fallback/Kernel.lean')),encoding='utf-8')
(HERE/'Cold-wrapper.lean.inc').write_text(new+'\n',encoding='utf-8')
diag=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40404258098/download-a36f332343924d11998e1f7ce5ebce36/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-jam17-public1'
roots=[l.removeprefix('#print axioms ').strip() for l in (diag/'helper-audit-source.lean').read_text().splitlines() if l.startswith('#print axioms ')]
assert len(roots)==40
roots+=['Submission.jamColdFallback','Submission.jamColdFallback_spec']
(HERE/'HelperAudit-jam-cold.lean.inc').write_text('\n'.join('#print axioms '+x for x in roots)+'\n',encoding='utf-8')
r={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'SINGLE_COMPLETE_SOURCE_PROOF_PRESERVING_ATTEMPT_NOT_RUN',
 'candidate':{'path':str(p),'bytes':len(b),'sha256':sha(b)},'base':{'path':str(base),'bytes':len(raw),'sha256':sha(raw)},
 'inverse_splice_recovers_exact_b271':True,'original_source_untouched':sha(base.read_bytes())==sha(raw),
 'runtime_change':'One ordinary noinline two-Binary32 wrapper around R19Base.mul. Existing guardedMul receives that definition instead; same guards, Jam arithmetic and all fallback values by definitional equality.',
 'changes_excluded':['bias','range mask','new guard','new arithmetic','compiler options','gate edits','other public entry behavior'],
 'explicit_helper_roots':roots,'expected_helper_count':42,
 'verification':{'lean':'NOT_RUN','codegen':'NOT_RUN','kernel_replay':'NOT_RUN','helper_audit':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN'},
 'scope':'b271 first complete cost run keeps priority and its exact source unchanged; this artifact is optional next codegen discrimination only, no automatic CI.',
 'failure_conditions':['Lean noinline still expands cold body into actual selected MainFull','Guard-success gains a call/closure/Nat/heap/spill','Same shared five-save16B-frame remains without a new measurable difference','Miss ABI loses direct tail transfer and its added cost overwhelms any hit saving'],
 'resources':{'local_compiles':0,'CI_runs':0,'tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN'}}
(HERE/'candidate-manifest.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate_bytes':len(b),'candidate_sha256':sha(b),'extra_bytes':len(b)-len(raw),'roots':len(roots),'base_unchanged':r['original_source_untouched']}))
