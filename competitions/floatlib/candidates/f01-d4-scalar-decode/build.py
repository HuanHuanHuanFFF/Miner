"""Use the all-input proven numeric decoder in native scalar add and mul."""
from pathlib import Path
import hashlib,json
ROOT=Path(__file__).resolve().parents[1];OUT=Path(__file__).resolve().parent
raw=(ROOT/'f01-d3-final-package/Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest()=='6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7'
s=raw.decode();a=s.index('namespace R2W01b\n');b=s.index('namespace Submission.NativeDecodeSum\n')
proof=s[a:b];s=s[:a]+s[b:]
pos=s.index('namespace Submission\n');s=s[:pos]+proof+'\n'+s[pos:]
for op in ['+','*']:
    old=f'ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x {op} ExecFloat.Binary.toFloat32 y)'
    new=f'ExecFloat.Binary.ofFloat32 (R2W01b.convert x.raw.1 {op} R2W01b.convert y.raw.1)'
    assert s.count(old)==1,(op,s.count(old));s=s.replace(old,new)
for lemma in ['ExecFloat.Binary.ofFloat32_add_of_isFinite','NativeBridge.ofFloat32Mul']:
    marker='    rw ['+lemma
    pos=s.index(marker)
    s=s[:pos]+'    rw [R2W01c.convert_eq, R2W01c.convert_eq]\n    change ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x '+('+' if 'add' in lemma else '*')+' ExecFloat.Binary.toFloat32 y) = _\n'+s[pos:]
data=s.encode();(OUT/'Kernel.lean').write_bytes(data)
m=dict(candidate=OUT.name,candidate_file='Kernel.lean',candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),parent='f01-d3-final-package',validation_mode='full-gate',proof_status='NOT_RUN',mechanism='Use the proven all-input inline numeric decoder for scalar native add/mul inputs; same guards, rounding and exact fallback. Unchanged final-package bmm and sum.')
(OUT/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m))
