"""Hash existing fixed sources and the in-memory diagnostic append plan; no Kernel emitted."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'AGENTS.md').exists())
F=H.parent/'structural-frontier/inline-u64-mul'
sha=lambda b:hashlib.sha256(b).hexdigest()
def ident(p):
 b=p.read_bytes();return {'path':str(p.relative_to(R)),'bytes':len(b),'sha256':sha(b)}
items=[
 (F/'Runtime-u64-mul-integer-v3-lf.lean.inc','cd301ba43a18ba2b9db2a8b2f1109406d00242acdd543b26364d9925ffde6c67'),
 (F/'Bridge-u64-integer-v3-lf.lean.inc','2261f1e317310bfb6505eb3ee333ad8b6b31f9ad13307f728719ecd3920fb906'),
 (F.parent/'upstream/Float32.lean','2f4b7eb845c03bd5581d70921f891798cc193f5c8c1372302a3e6064a34f7319'),
 (R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/lean-lean.h','982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'),
 (R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/lean-object.cpp','b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a'),
 (R/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/development-sources/lean-int-casts/SInt-Float32.lean.raw','f4f7be22aa75c1ebdbe513efbbc8c889fee07d723ae26b1a83fd59d339a37dfc'),
 (R/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/development-sources/lean-int-casts/SInt-Basic.lean.raw','4868b10bbef3740a4ddcaa5c8b7ccf18fd099bef301ddbc5ac8b1b8ce4e7b225')]
records=[]
for p,expected in items:
 i=ident(p);assert i['sha256']==expected,(p,i['sha256']);records.append(i)
header=items[3][0].read_text();obj=items[4][0].read_text()
primitive=[]
for name in ['lean_uint32_to_uint64','lean_uint64_mul','lean_uint64_to_float32','lean_float32_to_uint64','lean_int64_to_float32','lean_float32_to_int64','lean_box_uint64']:
 m=re.search(r'(?m)^static inline[^\n]*\b'+name+r'\([^\n]*?\)\s*\{',header);assert m
 o=header.index('{',m.start());e=o+1;dep=1
 while dep:dep+=(header[e]=='{')-(header[e]=='}');e+=1
 text=header[m.start():e]
 primitive.append({'name':name,'line':header.count('\n',0,m.start())+1,'body':text,'body_sha256':sha(text.encode())})
assert 'lean_float32_isnan' not in next(p['body'] for p in primitive if p['name']=='lean_float32_to_uint64')
assert 'lean_float32_isnan' in next(p['body'] for p in primitive if p['name']=='lean_float32_to_int64')
isnan_decl=re.search(r'(?m)^LEAN_EXPORT uint8_t lean_float32_isnan\(float a\);',header);assert isnan_decl
isnan_impl=re.search(r'(?m)^extern "C" LEAN_EXPORT uint8_t lean_float32_isnan[^\n]+',obj);assert isnan_impl
parent=F/'probe-b2-v1/Probe-b2-u64-roundtrip-v1.lean';base=parent.read_bytes()
assert sha(base)=='9f9a297e90f236c349283248cca9aa8f94c35ff24ebe9e26873e2c63d708a933'
runtime=items[0][0].read_bytes();diag=(H/'Diagnostic-entry-b2.lean.inc').read_bytes()
legacy=(F/'Diagnostic-entry-v2.lean.inc').read_bytes()
assert diag.decode()==legacy.decode().replace('\r\n','\n').replace('Submission.mulBeforeR16NativeRepack','Submission.mul')
assert b'Submission.mulBeforeR16NativeRepack' not in base
combined=base+b'\n'+runtime+b'\n'+diag
assert len(combined)<=256000
plan={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'APPEND_PLAN_ONLY_NO_KERNEL_EMITTED_NO_CI',
 'parent':ident(parent),'runtime':ident(items[0][0]),'diagnostic':ident(H/'Diagnostic-entry-b2.lean.inc'),
 'legacy_diagnostic':ident(F/'Diagnostic-entry-v2.lean.inc'),
 'legacy_CRLF_count':legacy.count(b'\r\n'),'new_CRLF_count':diag.count(b'\r\n'),
 'concatenation':'parent bytes + oneLF + runtime bytes + oneLF + diagnostic bytes',
 'combined_bytes':len(combined),'combined_sha256':sha(combined),'remaining_capacity_bytes':256000-len(combined),
 'public_entry_changes':'NONE; appended plain diagnosticEntry calls new guardedMul with original B2 Submission.mul as fallback',
 'original_math_probe':'No new runtime until the two appendices are actually assembled by D',
 'cost_scope':'diagnostic unboxed caller/object only; original MainFull MUL still B2; no timing conclusion'}
with (H/'diagnostic-plan.json').open('x',encoding='utf-8') as f:json.dump(plan,f,indent=2);f.write('\n')
review={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'FIXED_SOURCE_COST_REVIEW_CODEGEN_PENDING',
 'lean_commit':'293d5d0c0c3f3dded4688b3ccd6a33939ac5102b','floatlib_commit':'0d91825727839f597fd06b22fdd038ea21480f0c',
 'source_records':records,'primitive_bodies':primitive,
 'signed_reverse_external_call':{'declaration_line':header.count('\n',0,isnan_decl.start())+1,
   'implementation_line':obj.count('\n',0,isnan_impl.start())+1,'implementation':isnan_impl.group()},
 'visible_B_expression_bounds':{'mantissas':[2**23,2**24-1],'exact_product':[2**46,(2**24-1)**2],'RNE24_product':[2**46,2**48-2**25],
   'optimizer_eliminated_clamps':'UNKNOWN','scope':'Mathematical source semantics, not compiler metadata or a new Lean proof'},
 'old_C_control_report':ident(H/'audit-old-c972-v1/audit.json'),
 'extractor':ident(H/'audit_u64_roundtrip_c.py'),'review':ident(H/'review.md'),'usage':ident(H/'README.md'),
 'diagnostic_plan':ident(H/'diagnostic-plan.json'),'historical_A':ident(F/'Runtime-u64-mul-v1.lean.inc'),
 'tokens':'UNKNOWN','cached_input':'UNKNOWN','CI_occupancy_seconds':0,'new_C_ASM':'NOT_RUN'}
with (H/'source-review.json').open('x',encoding='utf-8') as f:json.dump(review,f,indent=2);f.write('\n')
print(json.dumps({'combined_bytes':len(combined),'combined_sha256':sha(combined),'diagnostic_bytes':len(diag),
 'legacy_CRLF':legacy.count(b'\r\n'),'source_records':len(records),'isnan_line':review['signed_reverse_external_call']},indent=2))
