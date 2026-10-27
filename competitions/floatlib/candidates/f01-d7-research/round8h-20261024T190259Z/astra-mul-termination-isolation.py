"""Prepare proof-only minimal reproducer metadata; never create/dispatch a candidate."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json

base=Path(__file__).resolve().parent;root=base.parents[4]
old=(base/'astra-biased-rne3.lean').read_bytes()
nat=old[:old.index(b'@[inline] def biased ')]+b'end Submission.R14BiasRNE\n'
path=base/'astra-biased-rne3-nat-only.lean'
if path.exists():assert path.read_bytes()==nat
else:path.write_bytes(nat)
parent=(root/'competitions/floatlib/candidates/f01-r14-dev-compact-base/Kernel.lean').read_bytes()
assert sha256(parent).hexdigest()=='3c6af73f9d679e9831ac8c4abb9f0e6d41b61718301dd045bedd2402e980632a'
probes=[]
for label,fragment in [('nat_only',nat),('complete_bias3',old)]:
    source=parent+b'\n'+fragment
    probes.append(dict(kind=label,bytes=len(source),sha256=sha256(source).hexdigest(),
                       created_as_candidate=False,public_runtime='unchanged compact DF'))
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
    state='MINIMAL_PROOF_TRIGGER_METADATA_ONLY_NOT_RUN',
    fragment=path.name,bytes=len(nat),sha256=sha256(nat).hexdigest(),probes=probes,
    recommended_order=['D exactM4 same-source new-runner reproduction first',
       'If reproduced, parent+Nat-only isolates large-modulus omega proof from Word lift and new integer runtime/code generation',
       'Parent+completeBias3 adds back only word lift/runtime helper; parent four exports remain unchanged',
       'Only after a causal clue compare quotient-proof option with same public statement/runtime suffix'],
    passive_evidence=['Capture failed-layer .trace/.c/.olean existence and hashes before cleanup, not only after successful statement',
       'Read runner resource/cgroup/journal events or sample task process RSS with timestamps; no gate/cap changes',
       'Use exact source fingerprints and preserve -15/empty output, separate from Lean theorem diagnostics'],
    authority='R creates no full candidate, queue, CI or public push; D chooses minimal diagnosis within remaining window.',
    limits='No cause has been established. These are proof/compiler diagnostics, not new runtime representations or benchmark retries.')
(base/'astra-mul-termination-isolation.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,ensure_ascii=False,indent=2))
