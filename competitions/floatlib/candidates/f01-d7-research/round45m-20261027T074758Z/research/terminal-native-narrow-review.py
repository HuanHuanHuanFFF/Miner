"""Selected exact complete-pair native bodies: narrow work premise, not timing."""
from pathlib import Path
import datetime, hashlib, json, re
HERE=Path(__file__).resolve().parent
ROOT=HERE.parent/'ci-runs/40472418849'
idx=json.loads((ROOT/'original-artifact-hashes.json').read_bytes()); rawroot=ROOT/idx['directory']
prefix='diagnostics/f01-r20-dev-terminal-pair-probe1/'
parts={}
for tag,num,symbol in [('control',10,'control'),('emit',11,'loopEmit'),('pair',12,'loopPair'),('terminal',13,'terminal')]:
    rel=prefix+f'native-loop-{num}.asm.txt'; raw=(rawroot/rel).read_bytes(); meta=idx['files'][rel]
    assert len(raw)==meta['bytes'] and hashlib.sha256(raw).hexdigest()==meta['sha256']
    text=raw.decode(); anchor=f'0000000000000000 <lp_competition_Submission_R20TerminalPair_{symbol}>:'
    body=text[text.index(anchor):]
    parts[tag]={'path':str(rawroot/rel),'sha256':meta['sha256'],'body':body}
for tag,stack in [('emit','0x78'),('pair','0xa8')]:
    assert re.search(r'sub\s+rsp,'+stack+r'\b',parts[tag]['body'])
    assert len(re.findall(r'R_X86_64_\S+\s+lean_float32_of_bits',parts[tag]['body']))==3
assert 'mi_malloc_small' in parts['pair']['body'] and 'lean_inc_heartbeat' in parts['pair']['body']
assert 'mi_malloc_small' not in parts['emit']['body'] and 'lean_inc_heartbeat' not in parts['emit']['body']
assert len(re.findall(r'R_X86_64_\S+\s+lean_array_push',parts['emit']['body']))==2
assert 'mulss' in parts['emit']['body'] and 'addss' in parts['emit']['body']
assert 'mulps' in parts['pair']['body'] and 'addps' in parts['pair']['body']
out={'verified_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'run':40472418849,'source_sha256':'b6b77553d49e968db27639b84f104783a9cf474ed963ec9cff7753a7adb17962',
 'status':'SELECTED_TWO_PAIR_DIAGNOSTIC_BODIES_READ_NOT_TIME_MEASUREMENT',
 'bodies':{k:{f:v for f,v in m.items() if f!='body'} for k,m in parts.items()},
 'observations':[
  'Both loopPair and loopEmit retain three direct of_bits relocations; no codec-count gain versus paired control.',
  'Both prologues save six integer registers. loopPair reserves0xa8=168B; loopEmit0x78=120B. This is individual frame size, not combined peak.',
  'loopPair retains two-lane mulps/addps and16B vector stack accesses. loopEmit has two scalar mulss/addss chains and4B stack accesses.',
  'In ordinary repeated k path, loopPair explicit FP stack sites:0x116/0x1b3/0x279 stores and0x257/0x263/0x271 loads, six16B accesses=96 explicit bytes.',
  'loopEmit repeated k sites:0x115/0x1b7 decoded stores,0x299/0x2a3 accumulator stores,0x26f/0x275/0x27a/0x280 loads, eight4B accesses=32 explicit bytes. Entry stores0x7b/0x85 are not multiplied into steady iterations.',
  'loopPair terminal directly calls heartbeat/malloc forF2; loopEmit has neither direct relocation and performs two original array_push operations.'
 ],
 'decision':'The exact terminal rewrite changes the former rawpair negative cost premise: it removes F2 and narrows cross-codec spills, while also losing vector arithmetic. Preserve for one future full-call measurement after real public integration; do not infer speed from bytes/instructions.',
 'limits':'No timed invocation, new public BMMspec, or full-score. Array.push internal allocation, NaN replay, output checksum, and full dispatch cost remain. Ordinary steady-path explicit stack-byte counts are not latency or actual memory-bandwidth measurements; no speedup ratio derived.'}
(HERE/'terminal-native-narrow-review.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='bodies'},ensure_ascii=False))
