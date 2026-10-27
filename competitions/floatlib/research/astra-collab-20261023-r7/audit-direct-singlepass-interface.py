from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent;C=H.parents[3]/'competitions/floatlib/candidates'
names={'base':'f01-r7-nonfinite-combined-proof2','sum':'f01-r7-sum-singlepass-fused-proof1','direct':'f01-d7-direct-nonfinite'}
blobs={k:(C/v/'Kernel.lean').read_bytes() for k,v in names.items()}
expected={'base':'0e8bc05ce954e3e8213fbef05ac6041f8f882673c88c1071a3c9d4254a3064cd','sum':'3d9b1ea94ec105073334b793adcb5a9fecc4eda37dd2a5809e715b5584a54576','direct':'97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26'}
for k,b in blobs.items():assert hashlib.sha256(b).hexdigest()==expected[k]
base=blobs['base'].decode();single=blobs['sum'].decode();direct=blobs['direct'].decode()
pos=base.rfind('namespace Submission\n');tail=base[pos:]
assert 'def bmm (' in tail and 'def sum ' not in tail
assert single.count(tail)==1 and direct.startswith(base[:pos])
newtail=direct[pos:];assert 'namespace Submission.DirectSmall' in newtail and not re.search(r'\bsum(?:_spec)?\b',newtail)
assert 'namespace Submission.DirectSmall' not in single
combined=single.replace(tail,newtail,1)
assert combined.replace(newtail,tail,1)==single
single_start=single.rfind('namespace R7SinglePassSum\n');assert single_start>=0
assert combined.endswith(single[single_start:])
assert len(re.findall(r'(?m)^def bmm \(',combined))==1
assert len(re.findall(r'(?m)^def sum \{n : Nat\}',combined))==1
assert 'def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R7SinglePassSum.run x' in combined
scope={'core_namespace':'Submission.DirectSmall','native_dot_interface':'Submission.NativeFinal.dot/dot_eq inheritedexactlyfrom0e8','scalar_interfaces':'Submission.add_eq/mul_eq retained','address_interface':'Submission.index_address retained','exported_sum':'R7SinglePassSum.run retained','new_suffix_opens':'Each newnamespace carries explicit open FloatLib.Floats Competition as97f','static_conflict':'NONE_IDENTIFIED_BY_SOURCE_INSPECTION_ONLY'}
actual=C/'f01-d7-direct-singlepass/Kernel.lean';act=None
if actual.exists():
 ab=actual.read_bytes();act={'bytes':len(ab),'sha256':hashlib.sha256(ab).hexdigest(),'matches_exact_in_place_BMM_tail_splice':ab==combined.encode()}
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'inputs':expected,'original_BMM_tail_in_3d9_exact_bytes':True,'DirectSmall_has_no_sum_dependency':True,'sum_full_appended_block_preserved':True,'in_memory_expected_bytes':len(combined.encode()),'in_memory_expected_sha256':hashlib.sha256(combined.encode()).hexdigest(),'undo_splice_recovers_exact3d9':True,'interfaces':scope,'D_file_readonly_observation':act,'scope':'Read-onlyinterfaceaudit; combinedbytescomputedinmemoryonly, nocandidatewritten/noDfilechanged. ExactnewLean/fullgate/C/performanceNOTRUN. This2-componentcombination isdifferentfrom353d olddecodehook caveat.'}
(H/'direct-singlepass-interface-audit.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
