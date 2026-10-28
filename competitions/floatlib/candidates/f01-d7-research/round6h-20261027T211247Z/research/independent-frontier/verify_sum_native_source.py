from pathlib import Path
from datetime import datetime,timezone
import re,json,hashlib
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
B=R/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/ci-runs/40602369221'
idx=json.loads((B/'original-artifact-hashes.json').read_bytes());A=B/idx['directory'];rows=[]
prefix='diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-broadword-cost1/runtime-cost/'
def read(key):
    p=A/key;b=p.read_bytes();sha=hashlib.sha256(b).hexdigest();assert sha==idx['files'][key]['sha256']
    rows.append({'path':str(p.relative_to(R)),'sha256':sha,'bytes':len(b)});return b
C=read(prefix+'original-statement-Submission.c').decode()
main=read(prefix+'build-product-0-R22BroadWordCostMain.c').decode()
kernel=read('diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r22-dev-broadword-cost1/Kernel.lean')
base=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean';bb=base.read_bytes()
assert hashlib.sha256(bb).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert kernel.startswith(bb)
sym='lp_competition_Submission_R7SinglePassSum_loop___redArg'
m=re.search(r'LEAN_EXPORT uint32_t '+sym+r'\([^\n]*\)\{',C);assert m
level=1;j=m.end()
while level:
    if C[j]=='{':level+=1
    elif C[j]=='}':level-=1
    j+=1
body=C[m.start():j]
assert 'float v_acc_13019_' in body
assert body.count('lean_float32_to_bits(v_acc_13019_)')==2
assert len(re.findall(r'v_acc_13019_ = v___x_\d+_;',body))==3
assert body.count('goto _start;')==3
assert '.m_fun = (void*)lp_competition_Submission_sum___boxed' in main
assert 'def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R7SinglePassSum.run x' in bb.decode()
assert 'loop x (USize.ofNat n) (USize.toNat_ofNat_of_lt\' hn) 0 (Float32.ofBits 0)' in bb.decode()
(D/'sum-current-native-loop-selected.c').write_text(body+'\n')
out={'verified_utc':datetime.now(timezone.utc).isoformat(),'state':'CLOSED_ALREADY_NATIVE_ACCUMULATOR',
     'source_sha256':hashlib.sha256(bb).hexdigest(),'actual_module_source':'0274 exact B2 prefix/publicsum unchanged',
     'files':rows,'loop_symbol':sym,'accumulator_type':'float','native_backedges':3,
     'accumulator_toBits_sites':{'terminal':1,'first_raw_nan_repair':1,'ordinary_loop_backedges':0},
     'new_runtime':'NONE','new_Lean':'NOT_RUN','new_CI':False,
     'scope':'Current selected SUM callback chain and generated C, not new timing or optimized-cycle attribution.'}
(D/'sum-native-source-binding.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({k:out[k] for k in ['state','loop_symbol','native_backedges','accumulator_toBits_sites']}))
