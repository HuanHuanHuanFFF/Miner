from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
here=Path(__file__).resolve().parent
root=next(p for p in here.parents if (p/'competitions/floatlib/pins.json').is_file())
base=root/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
data=base.read_bytes();assert hashlib.sha256(data).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
fragment=(here/'A4B2-core.lean').read_bytes()
out=data+b'\n'+fragment
assert len(out)<=256000
(here/'Kernel-core-probe.lean').write_bytes(out)
manifest=dict(at_utc=datetime.now(timezone.utc).isoformat(),status='COMPLETE_LOCAL_PROJECTION_ATTEMPT_NOT_COMPILED',parent_sha256=hashlib.sha256(data).hexdigest(),
 kernel_sha256=hashlib.sha256(out).hexdigest(),kernel_bytes=len(out),fragment_sha256=hashlib.sha256(fragment).hexdigest(),
 active_entry='Unchanged B2; this is a core compile/codegen probe, not performance candidate',
 exact_probe=['R16A4B2.packA','R16A4B2.wordLoop','R16A4B2.runDot','R16A4B2.buildTiles'],
 proof=['packA_read','wordLoop_row','runDot_row','buildTiles_row'],lean='NOT_RUN',full_gate='NOT_RUN',performance='NOT_RUN')
(here/'core-probe-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps(manifest))
