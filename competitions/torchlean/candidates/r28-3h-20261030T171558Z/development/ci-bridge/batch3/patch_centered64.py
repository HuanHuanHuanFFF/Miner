"""Frozen adapter, same three sharp unsigned64 guards as producer centered64."""
from pathlib import Path
import importlib.util,hashlib
HERE=Path(__file__).resolve().parent
PINS={'build_centered36_cost.py': '6183a3634bb64082c65605d6ebbd01e32d429d603fe55e34861b4c6950105db7', 'build_gemm36_pairlinear.py': '80c7bbdd3a3042b4baed85a08ba46f55cb3e571251e4d1f037ba88a448347a96', 'build_gemm36_pairlinear_v2.py': '8a59c56f8c92d9f62d85375f3606224cd5bb9c756d4168519940fc4381391e08', 'build_norm26_36.py': 'fe05b956373f898af7e09ca43924583af81c56a357e98f0b4e674f3c9de84c48', 'CenteredDotRuntime.leanfrag': '9225913d650fcd8f7f3d981c686ec9e9cb4b899850359f495606c4e61cacd1d6'}
def transform(raw,submission,variant):
 assert submission==36 and variant=='centered64-cost'
 for name in ['build_centered36_cost.py','CenteredDotRuntime.leanfrag']:assert hashlib.sha256((HERE/name).read_bytes()).hexdigest()==PINS[name]
 path=HERE/'build_centered36_cost.py';sp=importlib.util.spec_from_file_location('r28_centered_base_frozen',path);m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
 prior,_=m.build(raw);assert hashlib.sha256(prior).hexdigest()=='51fd24bd4597980fe64ae9eb0b7cf13147cefc6deb1e16f5e67a9fcc2ef1fc48'
 s=prior.decode('utf-8')
 for old in ['cx1.2.2+cw.2.2<=61','cx2.2.2+cw.2.2<=61','ca.2.2+cb.2.2<=61']:
  assert s.count(old)==1;s=s.replace(old,old[:-2]+'62')
 out=s.encode('utf-8');assert hashlib.sha256(out).hexdigest()=='c5acf195e79d826a5ffac90bbb914ab842e0ddd14792ab88ede5de72aaf8f642';return out
