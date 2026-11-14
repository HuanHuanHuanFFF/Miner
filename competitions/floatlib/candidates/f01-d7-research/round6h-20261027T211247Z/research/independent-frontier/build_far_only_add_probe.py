from pathlib import Path
from datetime import datetime, timezone
import hashlib, json
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
base=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
b=base.read_bytes();assert len(b)==226829 and hashlib.sha256(b).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
frag=D/'Runtime-far-only-add.lean.inc';f=frag.read_bytes();assert len(f)<=1024
assert b'@[noinline] def coldAdd' in f and b'else coldAdd x y' in f
assert b'((26 : UInt32) <<< (23 : UInt32))' in f
assert not any(x in f for x in [b'sorry',b'unsafe ',b'@[extern',b'implemented_by'])
out=D/'Kernel-far-only-add-probe.lean';out.write_bytes(b+b'\n'+f)
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec',
       'Submission.R22FarOnlyAdd.coldAdd','Submission.R22FarOnlyAdd.diagnosticEntry']
(D/'HelperAudit-far-only-add.lean.inc').write_text('import Kernel\n'+''.join('#print axioms '+x+'\n' for x in roots))
def desc(p):
    data=p.read_bytes();return {'file':str(p.relative_to(R)),'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()}
oldsource=R/'competitions/floatlib/candidates/f01-r6-web-absorption26-proof2/Kernel.lean'
oldbase=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39796984460/download-24cbb8861ba947d0a6d0f4c441904229/diagnostics/f01-d6-public-suite/public-suite'
oldv=oldbase/'f01-r6-web-absorption26-proof2-verdict.json';oldp=oldbase/'f01-d5-stream-pack-verdict.json'
v=json.loads(oldv.read_bytes());p=json.loads(oldp.read_bytes())
assert v['passed'] and v['mode']=='gate' and v['stage']=='score'
assert 'def rightGuard' in oldsource.read_text() and 'expField a + 26' in oldsource.read_text()
manifest={'at_utc':datetime.now(timezone.utc).isoformat(),'requested_first_tool_utc':'2026-10-28T00:04:10Z',
          'delivery_target_utc':'2026-10-28T00:20:00Z','source':desc(out),'fragment':desc(frag),
          'base':desc(base),'exact_base_prefix':True,'roots':roots,'root_count':len(roots),
          'public_four':'B2_UNCHANGED','new_ADD_spec':'NOT_PROVED','Lean':'NOT_RUN','cost':'UNKNOWN',
          'entry':'Submission.R22FarOnlyAdd.diagnosticEntry',
          'caller_requirement':'Inline complete diagnosticEntry, with original noinline coldAdd fallback; selected caller/FFI/branch frame must be captured before interpretation.',
          'old_negative':{'source':desc(oldsource),'verdict':desc(oldv),'parent_verdict':desc(oldp),
                          'run':39796984460,'whole_ratio_to_old_parent':v['ratio']/p['ratio'],
                          'scope':'Full accepted normal-only two-direction expGuard; different old parent. No same raw-distance-three-select plus noinline-fallback negative found in bounded search.'},
          'proof_interfaces':['Existing Absorption26.spec_left/spec_right for two normals with exponent gap26',
                              'New UInt32 abs-sort/subtraction/guard=>fields bridge',
                              'Zero-low identity and subnormal-low extension, especially hi exponent26',
                              'Original fallback and Binary32 raw identity'],
          'boundary':'No local Lean/CI, no new extern/intrinsic/unsafe, no benchmark-input specialization; 26 cutoff fixed by request, not swept.'}
(D/'far-only-add-probe-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps({k:manifest[k] for k in ['source','fragment','root_count','old_negative']}))
