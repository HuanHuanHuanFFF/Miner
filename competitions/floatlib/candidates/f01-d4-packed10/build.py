"""One controlled tile-width experiment: less padding and fewer B objects for p=50."""
from pathlib import Path
import hashlib,json,re
ROOT=Path(__file__).resolve().parents[1];OUT=Path(__file__).resolve().parent
raw=(ROOT/'f01-d3-final-package/Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest()=='6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7'
s=raw.decode();a=s.index('namespace Packed8\n');b=s.index('end Submission',a)
t=s[a:b].replace('Packed8','Packed10').replace('F8','F10').replace('dot8','dot10').replace('zero8','zero10')
t=t.replace('(p + 7) / 8','(p + 9) / 8');t=re.sub(r'\b8\b','10',t)
t=t.replace('  s7 : Float32','  s7 : Float32\n  s8 : Float32\n  s9 : Float32')
t=t.replace('| _ => v.s7','| 7 => v.s7\n  | 8 => v.s8\n  | _ => v.s9')
t=t.replace('read (col + 7)\u27e9','read (col + 7), read (col + 8), read (col + 9)\u27e9')
t=t.replace('acc.s7 + a * v.s7\u27e9','acc.s7 + a * v.s7, acc.s8 + a * v.s8, acc.s9 + a * v.s9\u27e9')
t=t.replace('s0 s1 s2 s3 s4 s5 s6 s7','s0 s1 s2 s3 s4 s5 s6 s7 s8 s9')
t=t.replace('s0, s1, s2, s3, s4, s5, s6, s7','s0, s1, s2, s3, s4, s5, s6, s7, s8, s9')
t=t.replace('zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32','zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32')
t=t.replace('zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32','zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32')
t=t.replace('l = 6 \u2228 l = 7 :=','l = 6 \u2228 l = 7 \u2228 l = 8 \u2228 l = 9 :=')
t=t.replace('rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;>','rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;>')
for expr in ['(s7 + sharedA * v.s7)','(s7 + a * v.s7)']:
    t=t.replace(expr,expr+' '+expr.replace('s7','s8')+' '+expr.replace('s7','s9'))
lines=[]
for line in t.splitlines():
    lines.append(line)
    if line.strip().startswith('(s7 + (Araw.map'):
        lines.extend([line.replace('s7','s8'),line.replace('s7','s9')])
t='\n'.join(lines)+'\n'
# The explicit lane-update witness is a tuple of field expressions.
t=re.sub(r', (s7 \+ [^\n]*?\.s7)\u27e9',lambda m:', '+m[1]+', '+m[1].replace('s7','s8')+', '+m[1].replace('s7','s9')+'\u27e9',t)
t=t.replace('Four independent left folds','Ten independent left folds')
s=s[:a]+t+s[b:];data=s.encode();(OUT/'Kernel.lean').write_bytes(data)
m=dict(candidate=OUT.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parent='f01-d3-final-package',validation_mode='full-gate',proof_status='NOT_RUN',mechanism='Ten ordered output accumulators per row. For the official p=50 shape, no padded columns and five rather than seven B groups. Same all-shape proof pattern and fallback; register-pressure cost measured rather than assumed.')
(OUT/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m))
