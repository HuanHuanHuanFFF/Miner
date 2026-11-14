"""Verify fixed source evidence and source behavior anchors; no compiler execution."""
from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
idx=json.loads((D/'codec-source-index.json').read_bytes());rows=[]
for r in idx['files']:
 p=D/r['name'];b=p.read_bytes();assert hashlib.sha256(b).hexdigest()==r['sha256'];assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()==r['git_blob_sha'];rows.append({'path':str(p.relative_to(R)),'sha256':r['sha256'],'bytes':len(b)})
api=(D/'codec-Float32.lean').read_text();test=(D/'codec-float_compiler.lean').read_text();ir=(D/'codec-LCNF-Irrelevant.lean').read_text();emit=(D/'codec-LCNF-EmitC.lean').read_text();util=(D/'codec-LCNF-Util.lean').read_text()
assert 'attribute [extern "lean_float32_of_bits"] Float32.ofModel' in api
assert '@[extern "lean_float32_of_bits"] def Float32.ofBits' in api
assert 'let _x.2 := Float32.ofModel x.1;' in test and 'def g : Float32.Model → Float32\n  | a => ⟨a⟩' in test
assert 'if isRuntimeBuiltinType declName then return none' in ir and '``Float, ``Float32' in util
assert '| some (.standard _ fn) =>' in emit and 'emit fn; emit "("' in emit
legacy=R/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/runtime-representation/static-dispatch-frontier/primary'
li=json.loads((legacy/'source-index.json').read_bytes())
for name in ['ToDecl.lean','ToLCNF.lean']:
 item=next(x for x in li if x['file']==name);p=legacy/name;b=p.read_bytes();assert hashlib.sha256(b).hexdigest()==item['sha256'];rows.append({'path':str(p.relative_to(R)),'sha256':item['sha256'],'bytes':len(b),'legacy_fixed_source':True})
decl=(legacy/'ToDecl.lean').read_text();assert 'if let some externAttrData := getExternAttrData? env declName then' in decl and 'value := .extern externAttrData' in decl
for name,rel,expected in [('header','competitions/floatlib/candidates/f01-d7-research/round45m-20261027T074758Z/research/source-intake/lean-runtime-293d5d0c/lean.h','982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'),('object','competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/public-source-runtime/sources/lean-object.txt','b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a')]:
 p=R/rel;b=p.read_bytes();assert hashlib.sha256(b).hexdigest()==expected;rows.append({'path':rel,'sha256':expected,'bytes':len(b),'legacy_fixed_source':True})
out={'verified_at_utc':datetime.now(timezone.utc).isoformat(),'first_tool_utc':'2026-10-27T22:50:24Z','deadline_utc':'2026-10-27T23:10:24Z','status':'CLOSED_SUPPORTED_PUBLIC_CONSTRUCTOR_RETAINS_SAME_EXTERN','source_count':len(rows),'files':rows,'new_primary_count':7,'new_primary_bytes':sum(r['bytes'] for r in idx['files']),'behavior_evidence':'Pinned compiler #guard_msgs source asserts constructor call survives. Standard extern lowering source emits named call. The test was not executed here.','allocation_boundary':'Model has UInt32+Prop; do not assert required model allocation. Float32 runtime builtin prevents outer trivial wrapper erasure.','semantics_boundary':'Arbitrary raw NaN payload is not a valid direct Float32.Model field; canonicalization required, raw Binary32 fallback kept.','no_probe_or_local_compiler_or_CI':True}
(D/'codec-source-verification.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps({k:out[k] for k in ['status','source_count','new_primary_count','new_primary_bytes','no_probe_or_local_compiler_or_CI']}))
