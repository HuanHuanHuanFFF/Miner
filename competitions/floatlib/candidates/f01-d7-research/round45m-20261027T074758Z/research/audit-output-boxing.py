"""Check pinned ABI and one already-reviewed native output emitter, no compilation."""
from pathlib import Path
import datetime, hashlib, json, re
HERE=Path(__file__).resolve().parent
ROOT=Path(__file__).resolve().parents[6]
OLD=ROOT/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z'
HEADER=HERE/'source-intake/lean-runtime-293d5d0c/lean.h'
ASM=OLD/'development-workers/anchor-323/b16-ci21-codegen/actual-emit.asm.txt'
RECEIPT=ASM.parent/'receipt.json'
raw=HEADER.read_bytes(); header=raw.decode()
body=re.search(r'static inline lean_obj_res lean_box_uint32\(uint32_t v\) \{.*?\n\}',header,re.S).group()
assert 'if (sizeof(void*) == 4)' in body
assert 'lean_alloc_ctor' in body.split('} else {')[0]
assert 'return lean_box(v);' in body.split('} else {')[1]
asm=ASM.read_bytes(); asmtext=asm.decode()
entry=json.loads(RECEIPT.read_text(encoding='utf-8'))['files']['actual-emit.asm.txt']
assert len(asm)==entry['bytes'] and hashlib.sha256(asm).hexdigest()==entry['sha256']
assert '377: R_X86_64_PLT32\tlean_float32_to_bits-0x4' in asmtext
assert re.search(r'3ac:\s+lea\s+rsi,\[rax\*2\+0x1\]',asmtext)
assert '3b8: R_X86_64_PLT32\tlean_array_push-0x4' in asmtext
out={
  'verified_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
  'status':'VERIFIED_PINNED_64BIT_ABI_AND_ONE_NATIVE_EMITTER_NOT_TIMING',
  'header':{'path':str(HEADER),'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'fixed_commit':'293d5d0c0c3f3dded4688b3ccd6a33939ac5102b'},
  'emitter':{'path':str(ASM),'bytes':len(asm),'sha256':entry['sha256'],'receipt':str(RECEIPT),'source_scope':'R19 B16 CI21 actual emit, not a new B2 native measurement'},
  'facts':[
    'On 64-bit, lean_box_uint32 returns tagged immediate lean_box(v), no allocation in that primitive.',
    'On 32-bit the same primitive uses lean_alloc_ctor; that branch is not the x86_64 runner.',
    'Selected historical native emitter: to_bits relocation 0x377, tagged lea rsi,[rax*2+1] at 0x3ac, array_push relocation 0x3b8.',
    'Float32/F2/F4 boxes, Array allocation/copy/destruction, finish codecs and checksum costs are separate and not ruled out.'
  ],
  'decision':'Do not allocate research to eliminating one hypothetical heap object per Binary32 output. Terminal F2/F4 lifecycle fusion still has a distinct measured-source premise.',
  'new_lean_compilation':False,'new_timing':False,'whole_speedup':'UNKNOWN'
}
(HERE/'output-boxing-audit.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,ensure_ascii=False))
