from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent;W=H/'web/R7-W11/original-extracted/R7-W11';dest=H/'web/R7-W11/reviewed-evidence';dest.mkdir(exist_ok=True)
manifest=json.loads((W/'manifest.json').read_text());assert len(manifest['files'])==590
for x in manifest['files']:
 p=(W/x['path']).resolve();assert p.is_relative_to(W.resolve());b=p.read_bytes();assert len(b)==x['bytes'] and hashlib.sha256(b).hexdigest()==x['sha256']
assert (W/'R7-W11-report.md').read_bytes()==Path('E:/Download/R7-W11-report.md').read_bytes()
paths=['NOTICE.md','README.md','R7-W11-report.md','SHA256SUMS','manifest.json','generated/MainFull.c','evidence/final-status.json','evidence/kernel-final-identity.json','evidence/target-clang-commands.json','evidence/toolchain-files.json','evidence/toolchain-source-files.json','evidence/dependency-revisions.json','evidence/harness-c-path.json','evidence/harness-c-excerpts.txt','evidence/elf/MainFull.json','evidence/elf/index.json','evidence/elf/raw/MainFull/nm-size-sort.stdout','evidence/elf/raw/MainFull/readelf-relocations.stdout','evidence/elf/raw/MainFull/objdump-disassembly.stdout','source/toolchain/include/lean/lean.h']
copies=[]
for rel in paths:
 b=(W/rel).read_bytes();q=dest/rel;q.parent.mkdir(parents=True,exist_ok=True)
 if q.exists():assert q.read_bytes()==b
 else:q.write_bytes(b)
 copies.append({'path':rel,'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()})
nm=(W/'evidence/elf/raw/MainFull/nm-size-sort.stdout').read_text();symbols={}
for line in nm.splitlines():
 p=line.split()
 if len(p)==4:symbols[p[3]]=int(p[1],16)
expected={'lp_competition_main___lam__0':238,'lp_competition_main___lam__1':884,'lp_competition_main___lam__3':884,'lp_competition_main___lam__0___boxed':116,'lp_competition_main___lam__1___boxed':116,'lp_competition_main___lam__3___boxed':116}
for k,v in expected.items():assert symbols[k]==v
obj=json.loads((W/'evidence/elf/MainFull.json').read_text());assert obj['sha256']==obj['sha256_after_inspection']=='f87b30d3644aa60f2b604a19f88525f3ea5c6cdd73b4abaea1ec981fc160783f';assert obj['elf_header']['Class']=='ELF64'
c=(W/'generated/MainFull.c').read_text();assert '.m_fun = (void*)lp_competition_main___lam__0___boxed' in c and '.m_fun = (void*)lp_competition_main___lam__3___boxed' in c
asm=(W/'evidence/elf/raw/MainFull/objdump-disassembly.stdout').read_text();wrapper=asm.split('Disassembly of section .text.lp_competition_main___lam__0___boxed:')[1].split('Disassembly of section')[0]
assert 'lean_alloc' not in wrapper and 'malloc' not in wrapper
assert 'lea    0x1(,%rax,2),%rax' in wrapper and 'shr    $1,%rsi' in wrapper
header=(W/'source/toolchain/include/lean/lean.h').read_text();boxing=header[header.index('static inline lean_obj_res lean_box_uint32'):header.index('static inline lean_obj_res lean_box_uint64')];assert 'sizeof(void*) == 4' in boxing and 'return lean_box(v)' in boxing
suite=(W/'generated/BenchSuite.c').read_text();assert 'lean_apply_2(v_kernel_2335_, v_fst_2345_, v_snd_2346_)' in suite
receipt={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'zip_sha256':'18cec34b9ac33146e9144fb7dd7e31d49891b5355a0c7bc7501204464eb7b7f7','payload_manifest_entries_verified':590,'standalone_report_byte_identity':'PASS','copied_light_evidence':copies,'copied_bytes':sum(x['bytes'] for x in copies),'actual_object_sha256':obj['sha256'],'scalar_symbol_sizes_from_original_nm':expected,'confirmed':'MainFull closures targetlocalboxed scalar wrappers; suite traversal stilllean_apply_2. On thisELF64 actualwrapper return UInt32 boxing istag-shift/lea, noheapallocation call. Genericreference-count coldbranches remainbut validrawUInt32 parametersareimmediates. Do notmistakeboxedABI forperresultheapallocation.','bounds':'Actualofflinefixedpublic60f C/objectmetadata, notCI timedobject identity. No execution orspeed claim; benchFull linking timedout. Sourcecondition/compilerlayout performance remainsUNKNOWN.'}
(H/'w11-codegen-audit.json').write_text(json.dumps(receipt,indent=2)+'\n')
print(json.dumps({k:v for k,v in receipt.items() if k!='copied_light_evidence'},indent=2))
