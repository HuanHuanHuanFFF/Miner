from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
base=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
raw=base.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
text=raw.decode()
pos=text.rindex('\ndef bmm (')
prefix=text[:pos]
tail=text[pos:].replace('def bmm (','def bmmBeforeTemporal (',1).replace('theorem bmm_spec','theorem bmmBeforeTemporal_spec',1).replace('(bmm batch','(bmmBeforeTemporal batch',1).replace('unfold bmm\n','unfold bmmBeforeTemporal\n',1)
out=(prefix+tail+'\n'+(H/'Temporal.lean.inc').read_text(encoding='utf-8')).encode()
assert len(out)<256000
assert not any(x in out for x in (b'sorry',b'admit',b'unsafe',b'implemented_by'))
(H/'Kernel-temporal-b2.lean').write_bytes(out)
meta={'at_utc':datetime.now(timezone.utc).isoformat(),'baseline_sha256':hashlib.sha256(raw).hexdigest(),'source_sha256':hashlib.sha256(out).hexdigest(),'source_bytes':len(out),'delta_bytes':len(out)-len(raw),'fragment_sha256':hashlib.sha256((H/'Temporal.lean.inc').read_bytes()).hexdigest(),'source':'Kernel-temporal-b2.lean','formal':'NOT_RUN','performance':'NOT_RUN','mechanism':'K4 temporal B2, original guard/order/raw replay/underflow retained','scope':'Complete candidate source draft; not only appended helpers'}
(H/'temporal-build.json').write_text(json.dumps(meta,indent=2)+'\n',encoding='utf-8')
print(json.dumps(meta))
