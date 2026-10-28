from pathlib import Path
from datetime import datetime, timezone
import hashlib,json
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
base=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean';b=base.read_bytes()
assert len(b)==226829 and hashlib.sha256(b).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
fragment=D/'Runtime-native-cold-add.lean.inc';f=fragment.read_bytes();assert len(f)<=1024
assert not any(x in f for x in [b'sorry',b'unsafe ',b'@[extern',b'implemented_by'])
assert b'R2W01b.fastOK x.raw.1 && R2W01b.fastOK y.raw.1' in f
assert b'@[noinline] def coldAdd' in f and b'else coldAdd x y' in f
kernel=D/'Kernel-native-cold-add-probe.lean';kernel.write_bytes(b+b'\n'+f)
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec',
       'Submission.R22NativeColdAdd.coldAdd','Submission.R22NativeColdAdd.diagnosticEntry']
helper=D/'HelperAudit-native-cold-add.lean.inc';helper.write_text('import Kernel\n'+''.join('#print axioms '+x+'\n' for x in roots))
def receipt(p):
    data=p.read_bytes();return {'file':str(p.relative_to(R)), 'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()}
historical=[]
for name in ['f01-r6-fused-add-proof1','f01-r6-normal-add-proof1','f01-d6-finite-decode-proof1','f01-d11-scalar-normal-band']:
    p=R/f'competitions/floatlib/candidates/{name}/Kernel.lean';historical.append(receipt(p))
bdbc=(R/'competitions/floatlib/candidates/f01-r6-fused-add-proof1/Kernel.lean').read_text()
assert '@[inline] def addR6Parent' in bdbc
assert 'if R2W01b.fastOK x.raw.1 && R2W01b.fastOK y.raw.1 then' in bdbc
assert 'else addR6Parent x y' in bdbc
out={'at_utc':datetime.now(timezone.utc).isoformat(),'first_tool_utc':'2026-10-28T00:31:35Z',
     'source':receipt(kernel),'fragment':receipt(fragment),'helper':receipt(helper),'base':receipt(base),
     'exact_B2_prefix':True,'root_count':len(roots),'roots':roots,'historical_sources':historical,
     'novelty_boundary':'The full fastOK domain and arithmetic are old R6 bdbc. Only the separate noinline exact B2 fallback boundary is the new cost hypothesis; current ADD frame/tail effect UNKNOWN.',
     'entry':'Submission.R22NativeColdAdd.diagnosticEntry','caller':'Inline complete entry in a static scalar callback; retain coldAdd noinline and original operand order',
     'guard':'Existing fastOK pair; each accepts +0/-0 or normal raw exponent24..254; no thresholds changed',
     'removed_source_work':'Inside accepted arm: both convert eligibility checks and output result self-BEq. Native output toBits and its own NaN normalization remain.',
     'public_four':'B2_UNCHANGED','new_ADD_spec':'NOT_PROVED','Lean':'NOT_RUN','cost':'UNKNOWN','new_numeric_model':'NONE; arithmetic and guard reuse existing B2 proven helpers',
     'stop_rule':'If actual selected callback retains comparable frame/guard/import work or loses complete cost, close; do not claim gain from noinline spelling or resweep guard.'}
(D/'native-cold-add-probe-manifest.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({k:out[k] for k in ['source','fragment','root_count','novelty_boundary']}))
