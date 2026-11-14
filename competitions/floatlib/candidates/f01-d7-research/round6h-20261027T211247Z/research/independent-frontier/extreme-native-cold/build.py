from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
D=Path(__file__).resolve().parent;P=D.parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
base=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
native=R/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/development-nativecold/NativeCold.lean.inc'
old=P/'Runtime-extreme-cold-mul.lean.inc'
review=P.parent/'extreme-cold-mul-independent-review.json'
sha=lambda b:hashlib.sha256(b).hexdigest()
b=base.read_bytes();nb=native.read_bytes();ob=old.read_bytes();rb=review.read_bytes()
assert sha(b)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(nb)=='e3b93d3ab1383ce09da56dbf7b203760c037b8d779fc2aedae9e9b704fa1ce13' and len(nb)==784
assert sha(ob)=='ac7c9df8aee30277befe4b6aae2e7f43fbf81043d6e00ab35127126f0f3ebd59'
rv=json.loads(rb);assert rv['source_sha256']==sha(ob) and rv['cases']==98496 and rv['differences']==0
f=(D/'Runtime.lean.inc').read_bytes();text=f.decode();ns=nb.decode().replace('\r\n','\n');os=ob.decode().replace('\r\n','\n')
assert len(f)<=1200 and not any(x in f for x in [b'sorry',b'unsafe ',b'@[extern',b'implemented_by'])
assert 'def pairOK' not in text and 'def hotMul' not in text
old_body=os.split('@[noinline] def coldMul (x y : Binary32) : Binary32 :=\n',1)[1].split('\n\n@[inline]',1)[0]
new_body=text.split('@[noinline] def endpointMiss (x y : Binary32) : Binary32 :=\n',1)[1].split('\n\n@[inline]',1)[0]
assert new_body==old_body.replace('R22OutlineMul.retainedMul','R22NativeCold.retainedMul')
old_entry=ns.split('@[inline] def coldMul (x y : Binary32) : Binary32 :=\n',1)[1].split('\nend ',1)[0]
new_entry=text.split('@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=\n',1)[1].split('\n\nend ',1)[0]
expected=old_entry.replace('if pairOK','if R22NativeCold.pairOK').replace('then hotMul','then R22NativeCold.hotMul').replace('else retainedMul','else endpointMiss')
norm=lambda s:re.sub(r'\s+',' ',s).strip()
assert norm(new_entry)==norm(expected)
assert '@[noinline] def retainedMul (x y : Binary32) : Binary32 := Submission.mul x y' in ns
kernel=D/'Kernel-probe.lean';kernel.write_bytes(b+b'\n'+nb+b'\n'+f)
kb=kernel.read_bytes();assert kb[:len(b)]==b and kb[len(b)+1:len(b)+1+len(nb)]==nb
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec',
       'Submission.R22NativeCold.pairOK','Submission.R22NativeCold.hotMul',
       'Submission.R22ExtremeNativeCold.endpointMiss','Submission.R22ExtremeNativeCold.diagnosticEntry']
(D/'HelperAudit.lean.inc').write_text('import Kernel\n'+''.join('#print axioms '+x+'\n' for x in roots))
def receipt(p):
    data=p.read_bytes();return {'file':str(p.relative_to(R)),'bytes':len(data),'sha256':sha(data)}
declarations={}
for name in ['pairOK','hotMul','retainedMul']:
    match=re.search(rb'@\[(?:inline|noinline)\] def '+name.encode()+rb'\b.*?(?=\r?\n@\[|\r?\nend )',nb,re.S)
    assert match and match[0] in kb
    declarations[name]={'bytes':len(match[0]),'sha256':sha(match[0]),'exact_source_span_in_kernel':True}
out={'created_utc':datetime.now(timezone.utc).isoformat(),'first_tool_utc':'2026-10-28T02:02:56Z',
     'delivery_target_utc':'2026-10-28T02:12:56Z','common_deadline_utc':'2026-10-28T03:12:47Z',
     'state':'FROZEN_DIAGNOSTIC_ONLY_COST_BEFORE_PROOF','runtime':receipt(D/'Runtime.lean.inc'),
     'kernel':receipt(kernel),'B2':receipt(base),'native_parent':receipt(native),'original_endpoint':receipt(old),
     'unchanged_native_pairOK_hotMul_definitions':True,'exact_B2_native_prefix':True,
     'unchanged_native_declaration_spans':declarations,
     'entry_changed_only_miss_target_after_namespace_qualification':True,
     'endpoint_body_changed_only_original_B2_callee_namespace':True,
     'fixed_independent_endpoint_review':receipt(review),'fixed_reference_cases_reused':98496,
     'new_sampling_or_threshold_search':False,'entry':'Submission.R22ExtremeNativeCold.diagnosticEntry',
     'roots':roots,'root_count':len(roots),'public_four':'B2_UNCHANGED','new_mul_spec':'NOT_PROVED',
     'Lean':'NOT_RUN','actual_hot_ASM_equivalence':'UNKNOWN','complete_cost':'UNKNOWN','CI_dispatched':False,
     'scope':'Native e3b pairOK/hotMul source reused exactly. Only pairOK misses enter the unchanged ac7 endpoint formula. Native S382/E191 pairs still use original hotMul. No endpoint population or old performance transferred to this composition.',
     'freeze_isolation':'Uses frozen622d/e3b/ac7 and previously released98496 review only; no new confirmation input/result or metric used.'}
if (D/'HANDOFF.md').exists():out['handoff_sha256']=sha((D/'HANDOFF.md').read_bytes())
(D/'manifest.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({k:out[k] for k in ['runtime','kernel','root_count','unchanged_native_pairOK_hotMul_definitions','entry_changed_only_miss_target_after_namespace_qualification','Lean','complete_cost']}))
