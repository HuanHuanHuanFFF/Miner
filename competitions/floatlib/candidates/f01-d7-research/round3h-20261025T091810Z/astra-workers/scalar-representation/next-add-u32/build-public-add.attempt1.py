"""One source-closed public ADD draft on exact B2; no compilation or CI.
No old 36-item trim list is used. Only unused selected NEW support declarations
and non-license comments from inserted fragments are omitted.
"""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
PARENT=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
digest=lambda b:hashlib.sha256(b).hexdigest()
basebytes=PARENT.read_bytes();assert digest(basebytes)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
base=basebytes.decode()
support=(HERE/'Add-native-high-support.lean').read_text(encoding='utf-8')
# Retain only rounded_bounds in this already checked generic high-N module.
a=support.index('theorem shift_carry ');b=support.index('end Submission.R14WordAddRounding',a)
removed_rounding=support[a:b];support=support[:a]+support[b:]
assert 'R14WordAddRounding.shift_carry' not in support and 'R14WordAddRounding.masked_fraction' not in support
interface=(HERE/'UInt32NativeRound-interface.lean').read_text(encoding='utf-8')
a=interface.index('/-- Pure arithmetic check of the postguard argument.')
interface=interface[:a]+'end Submission.R16AddUInt32Interface\n'
entry=(HERE/'Add-native-high-entry.lean').read_text(encoding='utf-8')
insert='section R16NativeAddProof\nset_option maxRecDepth 8192\n'+support+'\n'+interface+'\n'+entry+'\nend R16NativeAddProof\n'
def strip_comment(m):
    return m.group(0) if re.search(r'copyright|license|authors:',m.group(0),re.I) else ''
insert=re.sub(r'/\-.*?\-/',strip_comment,insert,flags=re.S)
insert=re.sub(r'\n{3,}','\n\n',insert)
for name in ['shift_carry','masked_fraction','postguard_pre_normal','raw_round_positive_zero']:
    assert not re.search(r'\b'+name+r'\b',insert),name
assert not re.search(r'\b(sorry|admit|axiom|unsafe|native_decide)\b',insert)
start=base.index('@[inline] def add (x y : Binary32) : Binary32 :=\n  let result := R2W01b.convert')
end=base.index('@[inline] def nativeMul ',start)
fallback=base[start:end].replace('def add (','def addBeforeR16NativeCast (',1)
fallback=fallback.replace('theorem add_spec :','theorem addBeforeR16NativeCast_spec :',1)
fallback=fallback.replace(' add x y = ExecFloat.Spec.add',' addBeforeR16NativeCast x y = ExecFloat.Spec.add',1)
fallback=fallback.replace('  unfold add\n','  unfold addBeforeR16NativeCast\n',1)
public='''namespace Submission
open FloatLib.Floats Competition
@[inline] def add (x y : Binary32) : Binary32 :=
  R16AddWord.guardedAdd addBeforeR16NativeCast x y
theorem add_spec (x y : Binary32) : add x y = ExecFloat.Spec.add x y := by
  exact R16AddWord.guardedAdd_spec addBeforeR16NativeCast addBeforeR16NativeCast_spec x y

'''
candidate=base[:start]+fallback+'\nend Submission\n\n'+insert+'\n'+public+base[end:]
out=HERE/'Kernel-add-native-high-draft1.lean'
out.write_bytes(candidate.encode())
(HERE/'Add-native-high-complete-insertion.lean').write_bytes(insert.encode())
assert len(candidate.encode())<=256000,len(candidate.encode())
assert candidate.endswith(base[end:])
# Original B2 mul/nativeMul and the complete remainder are exact suffix bytes.
report={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'SOURCE_CLOSED_PUBLIC_ENTRY_DRAFT_NOT_COMPILED',
 'parent':{'path':str(PARENT.relative_to(ROOT)),'sha256':digest(basebytes),'bytes':len(basebytes)},
 'candidate':{'path':out.name,'sha256':digest(candidate.encode()),'bytes':len(candidate.encode())},
 'insertion':{'path':'Add-native-high-complete-insertion.lean','sha256':digest(insert.encode()),'bytes':len(insert.encode())},
 'old_R14_math_parent':'f01-r14-dev-word-add-entry2 /f958071e full-gate run40152158687',
 'new_support_scope':'Same-sign or opposite gap>=1 exact alignment; high N>=2^23 after unsigned no-wrap alignment; normal exponent guard; native UInt32 conversion and repack',
 'same_domain_note':'Opposite gap0 is rejected before subtraction because its exact absolute N<2^23; all low N and zeros fallback. This realizes the single high-N simplification, not a parameter grid.',
 'runtime_delta':{'ADD':'new native-cast arm plus exact B2 fallback','MUL':'original B2 source byte-identical; rejected c972 runtime absent','SUM_BMM':'original source suffix byte-identical, but raw/reference/replay calls resolving public ADD can execute new ADD; all four original gate obligations required'},
 'proof_status':'All referenced new local names have source bodies; no placeholder proof/axiom. Actual statement/helper audit/full gate/timing NOT_RUN; first UInt32 transport still awaits owner probe feedback.',
 'trimming':'No existing B2 declaration removed; two unused new R14 rounding helpers and two unused interface helpers omitted, inserted non-license comments removed; no inherited36-leaf deletion list applied.',
 'copied_R14_changes':'large_left/exact alignment/domain generalized from gap>=2 to>=1; magnitude lower bound changed to1; upper bound unchanged; new high-N guard supplies log>=23.',
 'removed_new_rounding_declarations_sha256':digest(removed_rounding.encode()),
 'components':[{'path':p.name,'sha256':digest(p.read_bytes()),'bytes':p.stat().st_size} for p in [HERE/'Add-native-high-support.lean',HERE/'UInt32NativeRound-interface.lean',HERE/'Add-native-high-entry.lean']],
 'tokens':'UNKNOWN','ci_occupancy_seconds':0}
(HERE/'public-add-draft1-manifest.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':report['candidate'],'insertion':report['insertion'],'state':report['state']},indent=2))
