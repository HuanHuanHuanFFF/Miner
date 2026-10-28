"""One literal annotation, preserving frozen originals and exact reverse patch."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,difflib
D=Path(__file__).resolve().parent
old=b'e + 0x00800000 +';new=b'e + (0x00800000 : UInt32) +'
rows=[]
for before,after,expected in [
 ('Runtime-same-exponent.lean.inc','Runtime-same-exponent-typefix.lean.inc',None),
 ('Kernel-same-exponent-probe.lean','Kernel-same-exponent-probe-typefix.lean','c37e74cafd26a4ee14ba9987e052b757a311d4507ab3f21d4f2ed9a9e1802c3b'),
 ('Kernel-same-exponent-full-v1.lean','Kernel-same-exponent-full-v2-typefix.lean','914a0acb3d3a9607380ebadb125fe825e4eabafa1edf88d842777be829ead4dc')]:
 b=(D/before).read_bytes();bh=hashlib.sha256(b).hexdigest();assert expected is None or bh==expected
 assert b.count(old)==1,(before,b.count(old));a=b.replace(old,new);assert a.replace(new,old)==b
 (D/after).write_bytes(a)
 patch=''.join(difflib.unified_diff(a.decode().splitlines(keepends=True),b.decode().splitlines(keepends=True),fromfile=after,tofile=before))
 patchfile=D/(after+'.inverse.patch');patchfile.write_text(patch,encoding='utf8',newline='\n')
 rows.append({'before':before,'after':after,'before_sha256':bh,'after_sha256':hashlib.sha256(a).hexdigest(),'bytes_before':len(b),'bytes_after':len(a),'occurrences':1,'inverse_verified_byte_exact':True,'inverse_patch':patchfile.name,'inverse_patch_sha256':hashlib.sha256(patchfile.read_bytes()).hexdigest()})
root=D.parents[1]
failure=root/'ci-runs/40588875685/download-7e10038626b14b4fa0b4efba2c7100c9/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-runtime-cost2/full-build-output.txt'
assert failure.exists(),failure
raw=failure.read_bytes();assert b'HAdd UInt32' in raw
out={'at_utc':datetime.now(timezone.utc).isoformat(),'source_error':{'run':40588875685,'path':str(failure),'sha256':hashlib.sha256(raw).hexdigest(),'line':7201,'actual_error':'HAdd UInt32 Nat','scope':'Verified original full-build output and D development-cost3-repair.json. No compiled prior runtime to compare.'},'edit':{'old':old.decode(),'new':new.decode(),'scope':'Only explicit type annotation; guard, intended formula, branches, fallback, public aliases and all proof text remain byte-identical otherwise.'},'outputs':rows,'full_v2_roots':'same-exponent-full-v1-manifest.json roots unchanged (47)','status':'TYPE_REPAIR_NOT_RUN; no performance or proof acceptance inferred'}
(D/'same-exponent-typefix-receipt.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({'outputs':[{k:r[k] for k in ['after','after_sha256','bytes_after']} for r in rows],'status':out['status']}))
