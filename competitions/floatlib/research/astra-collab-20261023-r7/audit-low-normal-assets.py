from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent;W13=H/'web/R7-W13/original-extracted/R7-W13';W14=H/'web/R7-W14/original-extracted/R7-W14'
main=(W13/'R7W13.lean').read_bytes();inc=(W13/'R7W13Increment.lean').read_bytes();code=(W14/'source/R7W14.lean').read_bytes()
assert hashlib.sha256(main).hexdigest()=='a17d90417f1a8cd6a8cd396510501082355a00e513cf82af7875d5f8f443928d'
assert hashlib.sha256(inc).hexdigest()=='55ce42724776e218139bd702373829ca55910955c07f8f0821ba2feaf949b620'
compile=json.loads((W13/'logs/R7W13-attempt2.json').read_text());assert compile['returncode']==0 and compile['source_sha256']==hashlib.sha256(main).hexdigest()
audit=json.loads((W13/'logs/final-axiom-audit.json').read_text());assert audit['status']=='PASS' and audit['checked_declarations']==60 and not audit['unapproved']
def expr(s):
 a=s.index('def lowNormalDecode (u : UInt32) : Float32 :=')+len('def lowNormalDecode (u : UInt32) : Float32 :=')
 z=s.index('\n\n',a)
 return re.sub(r'\s+','',s[a:z])
assert expr(inc.decode())==expr(code.decode())
assert (W14/'logs/clang-probe.exitcode').read_text().strip()=='0'
obj=json.loads((W14/'evidence/elf/R7W14.json').read_text());assert obj['sha256']==obj['sha256_after_inspection']=='5c0b348378b900706b4fab63353836d7169c491fbc70455f56d07e7cf5cae8e0'
asm=(W14/'evidence/elf/raw/R7W14/objdump-disassembly.stdout').read_text();loop=asm.split('Disassembly of section .text.l_R7W14_researchLoop:')[1].split('Disassembly of section')[0]
assert re.search(r'^\s*7d:.*movss.*%xmm1,\(%rsp\)',loop,re.M)
assert re.search(r'^\s*f1:.*movss.*\(%rsp\),%xmm1',loop,re.M)
assert 'lean_float32_once_cold' in loop
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'mathematics_source_sha256':hashlib.sha256(main).hexdigest(),'mathematics_increment_sha256':hashlib.sha256(inc).hexdigest(),'codegen_source_sha256':hashlib.sha256(code).hexdigest(),'same_lowNormalDecode_expression_except_whitespace':'PASS','math_status':'ExactW13ordinaryLean finalsourcePASS/60declaration3axiomauditPASS forrealwordExp1..23, bothsigns/allfraction','codegen_object_sha256':obj['sha256'],'observed_loop_fp_stack_store_offset':'0x7d','observed_loop_fp_stack_reload_offset':'0xf1','once_cold_relocation_present':True,'scope':'W14historicMathNOT_PROVED report retained. LaterW13 verifies identicalhelperexpression onits conditionaldomain, notyetentirewrapper. Nativeobjectwasnotexecuted, nofullgate/performanceclaim. W14bconstant-source experiment andW13bfullguardproof pending.'}
(H/'low-normal-assets-audit.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
