"""Widen the compiled two-row bridge uniformly; never overwrite either candidate."""
from pathlib import Path
import hashlib
import json
import re
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
sha = lambda b: hashlib.sha256(b).hexdigest()
old_candidate = ROOT/'competitions/floatlib/candidates/f01-r4-tile2x4/Kernel.lean'
assert sha(old_candidate.read_bytes()) == '7de60fa52c445fa31aad8a0b9e4143933e0c0b26cdebf07d12805c3fa72a5476'
s = (HERE/'tile2x4-block.lean').read_text(encoding='utf-8')
assert old_candidate.read_text(encoding='utf-8').endswith(s)
header = 'abbrev F4 := Packed4.F4\nabbrev F8 := Packed8.F8'
assert s.count(header) == 1
s = s.replace(header, '__RESULT_DECLARATION__')
s = re.sub(r'\bF8\b', 'F16', s)
s = re.sub(r'\bF4\b', 'Packed8.F8', s)
s = s.replace('Packed4.', 'Packed8.').replace('.dot4', '.dot8')
s = s.replace('Tile2x4', 'Tile2x8').replace('Fin 4', 'Fin 8')
s = s.replace('4 * g.val', '8 * g.val').replace('/ 4', '/ 8').replace('% 4', '% 8')

states = lambda lo, hi: ' '.join(f's{i}' for i in range(lo, hi))
record = lambda lo, hi: '⟨'+', '.join(f's{i}' for i in range(lo, hi))+'⟩'
s = s.replace(states(0,8), states(0,16))
s = s.replace(record(0,8), record(0,16))
# Half projections grow only after whole-state occurrences have been widened.
s = s.replace(record(0,4), record(0,8)).replace(record(4,8), record(8,16))
for base, lo, hi, nlo, nhi in [('base0',0,4,0,8),('base1',4,8,8,16)]:
    s = s.replace(f'Packed8.dot8 n {base} A B k {states(lo,hi)}',
                  f'Packed8.dot8 n {base} A B k {states(nlo,nhi)}')
    s = s.replace(f'Packed8.dot8_lane n {base} baseB p Araw Braw B l hb k {states(lo,hi)}',
                  f'Packed8.dot8_lane n {base} baseB p Araw Braw B l hb k {states(nlo,nhi)}')

def updates(width):
    lines = [f'(s{i} + a{i//width} * b{i%width})' for i in range(2*width)]
    return '\n'.join('      '+' '.join(lines[i:i+2]) for i in range(0,2*width,2))
assert s.count(updates(4)) == 2
s = s.replace(updates(4), updates(8))

def field_bindings(width):
    return '\n'.join(f'    let b{i} := v.s{i}' for i in range(width))
assert s.count(field_bindings(4)) == 2
s = s.replace(field_bindings(4), field_bindings(8))

def expanded_updates(width):
    return '\n'.join(f'      (s{i} + A.getD (base{i//width} + k) zero32 * '
                     f'(B.get ⟨k, hk⟩).s{i%width})' for i in range(2*width))
assert s.count(expanded_updates(4)) == 2
s = s.replace(expanded_updates(4), expanded_updates(8))
s = re.sub(r'\bzero32(?:\s+zero32){7}\b', ' '.join(['zero32']*16), s)
s = s.replace('⟨'+', '.join(['zero32']*8)+'⟩', '⟨'+', '.join(['zero32']*16)+'⟩')
s = s.replace('Packed8.zero8', 'zero16')
s = s.replace('l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3', ' ∨ '.join(f'l = {i}' for i in range(8)))
s = s.replace('rcases hll with rfl | rfl | rfl | rfl', 'rcases hll with '+' | '.join(['rfl']*8))
s = re.sub(r'(?m)^@\[inline\] def low .*$',
           '@[inline] def low (v : F16) : Packed8.F8 := ⟨'+', '.join(f'v.s{i}' for i in range(8))+'⟩',s)
s = re.sub(r'(?m)^@\[inline\] def high .*$',
           '@[inline] def high (v : F16) : Packed8.F8 := ⟨'+', '.join(f'v.s{i}' for i in range(8,16))+'⟩',s)
a=s.index('@[inline] def rowLane')
b=s.index('theorem rowLane_zero',a)
lane=['@[inline] def rowLane (v : F16) (r : Fin 2) (l : Fin 8) : Float32 :=',
      '  if r.val = 0 then','    match l.val with']
lane += [f'    | {i} => v.s{i}' for i in range(7)]+['    | _ => v.s7','  else','    match l.val with']
lane += [f'    | {i} => v.s{i+8}' for i in range(7)]+['    | _ => v.s15','','']
s=s[:a]+'\n'.join(lane)+s[b:]
s=s.replace('__RESULT_DECLARATION__', 'structure F16 where\n'+'\n'.join(f'  s{i} : Float32' for i in range(16)))
marker='abbrev zero32 : Float32 := Packed8.zero32'
s=s.replace(marker,marker+'\n\n@[inline] def zero16 : F16 := ⟨'+', '.join(['zero32']*16)+'⟩')
s=s.replace('sharing the four right-hand values', 'sharing the eight right-hand values')
assert 'Packed4' not in s and 'Fin 4' not in s
assert s.count('(s15 + a1 * b7)') == 2
assert f'Packed8.dot8 n base0 A B k {states(0,8)}' in s
assert f'Packed8.dot8 n base1 A B k {states(8,16)}' in s
runtime=s[s.index('def wordLoop '):s.index('theorem wordLoop_eq')]
assert len(re.findall(r'\(s\d+ \+ a[01] \* b\d+\)',runtime)) == 16
(HERE/'tile2x8-block.lean').write_text(s,encoding='utf-8')

parent=ROOT/'competitions/floatlib/candidates/f01-d3-final-package/Kernel.lean'
pb=parent.read_bytes()
assert sha(pb)=='6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7'
prefix=pb.decode();a=prefix.index('\ndef bmm (batch m n p');b=prefix.index('\nend Submission',a)
tail=re.sub(r'\bbmm_spec\b','bmmBase_spec',prefix[a:b]);tail=re.sub(r'\bbmm\b','bmmBase',tail)
prefix=prefix[:a]+tail+prefix[b:]
data=(prefix+'\n'+s).encode()
out=ROOT/'competitions/floatlib/candidates/f01-r4-tile2x8'
out.mkdir(exist_ok=False)
(out/'Kernel.lean').write_bytes(data)
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),
   'candidate_bytes':len(data),'parent':str(parent.relative_to(ROOT)),'parent_sha256':sha(pb),
   'proof_template':'Compiled2x4 source7de60fa5; uniformly widened projections/arguments/constructors',
   'mechanism':'2rows x8columns,16scalar accumulators; reuse parentF8 Bpacking anddot8 bridge; two A reads andone Bpacket per k',
   'preserved':'Parentadd/mul/decoded sum unchanged; originalbmm renamed. Old2x4 untouched.',
   'validation_mode':'diagnostic-statement-only','proof_status':'NOT_RUN','performance':'NOT_RUN',
   'formal_submission':'NOT_PERFORMED','created_at_utc':datetime.now(timezone.utc).isoformat()}
(out/'manifest.json').write_text(json.dumps(m,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
print(json.dumps(m,indent=2,ensure_ascii=False))
