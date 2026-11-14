"""Bounded old-source/verdict/codepath check; no Git, CI, compilation or new timing."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,subprocess

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
C=ROOT/'competitions/floatlib/candidates'
OLD=C/'f01-d7-research/round9h-20261026T194639Z'
STRUCT=OLD/'development-workers/structural-cost'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
names={
 'f01-r15-dev-shortn-inline-decode1':'f65e4aa5baf0b38a808f1e57e0ded26d71870d8b61b993a80ab92aeef77e8d8c',
 'f01-d9-bmm-direct-decode-proof2':'d5e3512f95dc938db6d41f63745d8bf777cb1f6865c7b4b83a8b9055db2b5b09',
 'f01-r19-dev-b2-index-inline1':'f84ea2dbffbf0406f453bbc20b4335288ba5d77bb787ae33db203665016ac384',
 'f01-r15-dev-packed-b2-1':'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58',
}
for name,expected in names.items():assert sha(C/name/'Kernel.lean')==expected
result_path=OLD/'result-1927005-f01-r19-dev-b2-index-inline1-vs-f01-r15-dev-packed-b2-1.json'
result=json.loads(result_path.read_text())
bound=[]
for run,name in [(40407333869,'f01-r19-dev-b2-index-inline1'),(40407333869,'f01-r15-dev-packed-b2-1'),(39961709177,'f01-d9-bmm-direct-decode-proof2')]:
    runpath=C/f'f01-mul-log2-proof1/ci-runs/{run}'
    verdict_paths=list(runpath.rglob(name+'-verdict.json'))
    assert len(verdict_paths)==1,(run,name,verdict_paths)
    vp=verdict_paths[0];v=json.loads(vp.read_text())
    kernels=[p for p in runpath.rglob('Kernel.lean') if p.parent.name==name and 'inputs' in p.parts]
    assert len(kernels)==1 and sha(kernels[0])==names[name]
    assert v['passed'] and v['stage']=='score' and len(v['rounds'])==25
    if run==40407333869:assert sha(vp)==result['evidence']['verdict_sha256'][name]
    bound.append({'run':run,'name':name,'verdict':str(vp.relative_to(ROOT)).replace('\\','/'),
                  'verdict_sha256':sha(vp),'kernel_sha256':sha(kernels[0]),'full_gate':True,'rounds':25,'ratio':v['ratio']})
assert abs(bound[0]['ratio']/bound[1]['ratio']-result['relative_normalized_ratio'])<1e-14
cg_path=STRUCT/'codegen-40404258098.json';cg=json.loads(cg_path.read_text())
runpath=C/'f01-mul-log2-proof1/ci-runs/40404258098'
indexes=[p for p in runpath.rglob('native-assembly-index.json') if p.parent.name=='f01-r19-dev-b2-index-inline1']
assert len(indexes)==1
ap=indexes[0].parent/cg['selected_ASM']['index_entry']['file']
restoration=None
if ap.exists():asmbytes=ap.read_bytes()
else:
    recovery_path=ROOT/'competitions/floatlib/evidence/maintenance-20261027/recoverable-evidence.json'
    recovery=json.loads(recovery_path.read_text())
    logical=str(ap.relative_to(ROOT)).replace('\\','/')
    entry=recovery['entries'][logical]
    asmbytes=subprocess.check_output(['git','cat-file','blob',entry['git_blob']],cwd=ROOT)
    assert len(asmbytes)==entry['bytes'] and hashlib.sha256(asmbytes).hexdigest()==entry['sha256']
    restoration={'index_sha256':sha(recovery_path),'logical_path':logical,'git_blob':entry['git_blob'],'source_commit':entry['source_commit'],'scope':'Read original bytes in memory only; no original-path or Git mutation.'}
asmsha=hashlib.sha256(asmbytes).hexdigest()
assert asmsha==cg['selected_ASM']['index_entry']['sha256']
text=asmbytes.decode();symbol=cg['selected_ASM']['index_entry']['symbol']
match=re.search(r'(?m)^0+ <'+re.escape(symbol)+r'>:\s*$',text);assert match
body_start=text.index('\n',match.start())+1
end=re.search(r'(?m)^(?:Disassembly of section|0[0-9a-f]+ <)',text[body_start:])
body=text[body_start:body_start+end.start()] if end else text[body_start:]
instructions=[]
for line in body.splitlines():
    m=re.match(r'\s*([0-9a-f]+):\s+([a-z][a-z0-9]*)\s*(.*)',line)
    if m:instructions.append({'offset':int(m[1],16),'mnemonic':m[2],'operands':m[3]})
warm=[r for r in instructions if 0x40<=r['offset']<0xb4]
assert len(warm)==30 and not any(r['mnemonic']=='call' or 'rsp' in r['operands'] for r in warm)
history=json.loads((STRUCT/'inline-convert-history.json').read_text())
assert history['standalone']['frozen_decision']=='COMPONENT_PROTOTYPE_NOT_SELECTED_STANDALONE'
header=C/'f01-d7-research/round3h-20261025T043928Z/astra-workers/public-source-runtime/sources/lean-header.txt'
ht=header.read_text();assert 'LEAN_EXPORT float lean_float32_of_bits(uint32_t u);' in ht
assert 'static inline float lean_uint32_to_float32(uint32_t a) { return (float) a; }' in ht
out={
 'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'F84_LATER_FULL_A_ONLY_TEST_FOUND_AND_BOUND',
 'sources':{name:{'sha256':sha(C/name/'Kernel.lean'),'bytes':(C/name/'Kernel.lean').stat().st_size} for name in names},
 'full_gate_bindings':bound,
 'f65_standalone':history['standalone'],
 'f65_combination_scope':history['combined_test'],
 'f84_discovery':{'run':40407333869,'seed':1927005,'whole':result['relative_normalized_ratio'],'bmm':result['per_operation_normalized']['bmm'],'p05':result['gain_p05'],'adopted':False,'result_sha256':sha(result_path)},
 'f84_actual_statement_warm_loop':{'asm_path':str(ap.relative_to(ROOT)).replace('\\','/'),'asm_sha256':asmsha,'symbol':symbol,'warm_instructions':30,'warm_calls':0,'warm_rsp_references':0,'scope':'Selected statement diagnostic object, not a newF8 or finaltimedELF guarantee.','durable_recovery':restoration},
 'header_sha256':sha(header),
 'new_F8_condition':'FourrawA decodes feed8ordered accumulationlanes and oneF2 Bpacket withoutA panel; actualregister/call/spill structure differs from oldtwo-laneF84. No gain inferred.',
 'new_candidate':False,'local_Lean':False,'CI':False,
}
(HERE/'history-binding.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k not in ('sources','f65_combination_scope','full_gate_bindings')},indent=2))
