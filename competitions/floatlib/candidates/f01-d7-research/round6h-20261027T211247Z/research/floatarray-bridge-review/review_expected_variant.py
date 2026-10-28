from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json
here=Path(__file__).resolve().parent
r=here.parent
v=r/'streaming-public/floatarray-expected-variant'
old=r/'streaming-public/floatarray-storage'
runtime=(v/'Runtime.lean.inc').read_bytes()
kernel=(v/'Kernel-probe.lean').read_bytes()
assert sha256(kernel).hexdigest()=='f59d12dc43b6b16737c70a9cea864f61b2613904b709b305acc72a961092d980'
t=runtime.decode()
changes=[('Submission.R22FloatArrayB2Expected','Submission.R22FloatArrayB2'),
('    let raw0 := B.getD (base + k * p) posZero\n    let f0 := ExecFloat.Binary.toFloat32 raw0','    let f0 := ExecFloat.Binary.toFloat32 (B.getD (base + k * p) posZero)'),
('      let raw1 := B.getD (base + 1 + k * p) posZero\n      let f1 := ExecFloat.Binary.toFloat32 raw1','      let f1 := ExecFloat.Binary.toFloat32 (B.getD (base + 1 + k * p) posZero)'),
('R22ExpectedB2Check.check raw0 d0','R22FloatArrayBridgeReview.checkNative f0 d0'),
('R22ExpectedB2Check.check raw1 d1','R22FloatArrayBridgeReview.checkNative f1 d1')]
for i,(a,b) in enumerate(changes):
    assert t.count(a)==(2 if i==0 else 1)
    t=t.replace(a,b)
assert t.encode()==(old/'Runtime.lean.inc').read_bytes()
expected=(v/'ExpectedNativeWord-policy.lean.inc').read_bytes()
original=(r/'streaming-public/expected-native-word/ExpectedNativeWord.lean.inc').read_bytes()
assert expected.replace(b'expected native readback word',b'expected native import word')==original
check=(v/'ExpectedCheck.lean.inc').read_bytes()
prefix=kernel.removesuffix(runtime)
assert prefix.endswith(expected+b'\n'+check+b'\n')
inverse=prefix.removesuffix(expected+b'\n'+check+b'\n')+t.encode()
assert inverse==(old/'Kernel-probe.lean').read_bytes()
out={'first_tool_utc':'2026-10-28T02:21:26Z','checked_utc':datetime.now(timezone.utc).isoformat(),
 'source_sha256':sha256(kernel).hexdigest(),'bytes':len(kernel),'runtime_sha256':sha256(runtime).hexdigest(),
 'check_sha256':sha256(check).hexdigest(),'inverse_runtime_sha256':sha256(t.encode()).hexdigest(),
 'inverse_kernel_sha256':sha256(inverse).hexdigest(),'finding':'NO_DEFINITE_CHANGE_INTERFACE_ERROR_FOUND_STATIC_ONLY',
 'checked':['Both original B.getD addresses and order preserved, raw0/raw1 each feed one existing decode',
 'new check definition is the symmetric complete Bool equality from37cd for arbitrary stored',
 'Only namespace/raw binding/check expression changed; exact inverse preserves all layout/loop/guard/odd/fallback code',
 'ExpectedNativeWord policy projection changes only the one comment phrase; original37cd preserved'],
 'Lean':'NOT_RUN','CI':'NOT_RUN','public_BMM':'NOT_PROVED','performance':'UNKNOWN','source_mutation':'NONE'}
(here/'peer-expected-variant-review.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checked_utc':out['checked_utc'],'finding':out['finding'],'source_sha256':out['source_sha256']}))
