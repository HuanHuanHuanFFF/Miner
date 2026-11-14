"""Isolate two unchanged actual-word certificates from pending native bridges."""
from pathlib import Path
import hashlib, json

ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file())
HERE=Path(__file__).resolve().parent
BASE=ROOT/'competitions/floatlib/candidates'
OUT=BASE/'f01-r24-dev-core-certificate1'
OUT.mkdir(exist_ok=True)
sha=lambda b:hashlib.sha256(b).hexdigest()
prefix_path=ROOT/'competitions/floatlib/references/official-incumbent/Kernel.lean'
prefix=prefix_path.read_bytes()
assert sha(prefix)=='5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
parts=[];components=[];names=[]
for parent in ['f01-r24-dev-broad-cell-primitive2','f01-r24-research-scalar-quotient2']:
    manifest=json.loads((BASE/parent/'manifest.json').read_bytes())
    assert sha((BASE/parent/'Kernel.lean').read_bytes())==manifest['candidate_sha256']
    item=manifest['fragment'];p=ROOT/item['path'];b=p.read_bytes()
    assert sha(b)==item['sha256'] and len(b)==item['bytes']
    parts.append(b);components.append({'path':p.relative_to(ROOT).as_posix(),'bytes':len(b),'sha256':sha(b)})
    names += [n for n in manifest['explicit_helper_audit'] if n not in names]
raw=prefix+b'\n\nset_option maxRecDepth 4096\nset_option maxHeartbeats 1000000\n\n'+b'\n\n'.join(parts)
assert len(names)==13
path=OUT/'Kernel.lean'
if path.exists():assert path.read_bytes()==raw
else:path.write_bytes(raw)
manifest={k:v for k,v in manifest.items() if k.startswith('helper_audit') or k in ['helper_audit_module','helper_audit_module_path']}
manifest.update(candidate=OUT.name,candidate_file='Kernel.lean',candidate_sha256=sha(raw),candidate_bytes=len(raw),
    validation_mode='statement-only',diagnostic_only=True,diagnostic_timeout_seconds=600,
    proof_status='NOT_RUN_SEPARATE_ACTUAL_WORD_CERTIFICATES',performance='NOT_A_PERFORMANCE_CANDIDATE',
    formal_submission='NOT_SUBMITTED',official_submission_inherited=False,explicit_helper_audit=names,
    helper_audit_required_endpoints=names,helper_audit_expected_count=len(names),helper_audit_source_sha256=sha(raw),
    diagnostic_evaluations=[],components=components,
    runtime_prefix={'path':prefix_path.relative_to(ROOT).as_posix(),'sha256':sha(prefix),'bytes':len(prefix),'byte_identical':True},
    scope='OriginalContractTensor shipped4publics unchanged; two independently useful actualRNE/UInt64 certificates. No native64 bridge, performance/newtarget or inheritedparent acceptance.')
p=OUT/'manifest.json'
if p.exists():assert json.loads(p.read_bytes())==manifest
else:p.write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':OUT.name,'sha256':sha(raw),'bytes':len(raw),'roots':len(names),'state':'PREPARED_NOT_COMPILED'}))
