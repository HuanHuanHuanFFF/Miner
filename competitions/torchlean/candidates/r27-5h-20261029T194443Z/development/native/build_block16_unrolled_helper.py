"""Generate a fixed16 native sum with no per-MAC Nat fuel operation."""
from pathlib import Path
import hashlib,json
HERE=Path(__file__).resolve().parent
lines=['namespace R27Block16',
 '@[inline] def sum (n:ؾ) (f:(k:ؾ) -> k<n -> ػ) (k:ؾ):ػ:=']
for i in range(16):
 if i:lines.append(f' let k{i}:=k+{i}')
 key=f'k{i}' if i else 'k'
 lines.append(f' let a{i}:=if h:{key}<n then f {key} h else 0')
lines.extend([' '+'+'.join(f'a{i}' for i in range(16)),
 '@[specialize] def groups (n:ؾ) (f:(k:ؾ) -> k<n -> ػ) (B:ػ) (bw:ؼ) : Nat -> ؾ -> ػ -> ػ -> ػ',
 ' | 0,k,hi,lo=>QY6G n f B bw hi lo k',
 ' | fuel+1,k,hi,lo=>',
 '   let q:=sum n f k',
 '   groups n f B bw fuel (k+16) (QhiS hi lo q) (lo+q)',
 '@[inline] def run (n:ؾ) (f:(k:ؾ) -> k<n -> ػ) (B:ػ) (bw:ؼ)',
 ' (hi lo:ػ) (k:ؾ):ػ:=groups n f B bw (n.toNat/16) k hi lo',
 'end R27Block16'])
raw=('\n'.join(lines)+'\n').encode()
(HERE/'Block16PreparedUnrolled.lean.inc').write_bytes(raw)
print(json.dumps({'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest()}))
