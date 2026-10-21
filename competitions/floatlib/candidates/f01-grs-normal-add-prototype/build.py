"""Unproved GRS algorithm screen. This file must never be treated as full gate accepted."""
from pathlib import Path
import json,hashlib
OWN=Path(__file__).resolve().parent;TRACK=OWN.parents[1]
base=(TRACK/'references/official-incumbent/Kernel.lean').read_text(encoding='utf-8')
example=(OWN.parent/'f01-mul-log2-proof3/next-research/textbook-adder-unproved.lean.txt').read_text(encoding='utf-8')
runtime=example[example.index('namespace Submission'):example.index('/-- The only lemma')].replace('namespace Submission','namespace GRSAdd',1)
needle='  if ea == 0 || ea == 0xff || eb == 0 || eb == 0xff then ExecFloat.add x y else\n'
assert needle in runtime
runtime=runtime.replace(needle,needle+'  if a >>> 31 != b >>> 31 then ExecFloat.add x y else\n')+'\nend GRSAdd\n'
source=base.replace('end TunedAdd\n','end TunedAdd\n'+runtime,1)
source=source.replace('def add (x y : Binary32) : Binary32 := TunedAdd.add x y','def add (x y : Binary32) : Binary32 := GRSAdd.add x y').replace(':= TunedAdd.add_spec\n',':= by sorry\n')
(OWN/'Kernel.lean').write_bytes(source.encode())
(OWN/'manifest.json').write_bytes((json.dumps({'candidate':OWN.name,'kernel_sha256':hashlib.sha256(source.encode()).hexdigest(),'kernel_bytes':len(source.encode()),'validation_mode':'benchmark-only','proof_status':'UNPROVED_PROTOTYPE_WITH_EXPLICIT_PLACEHOLDER','scope':'Algorithm screening only via official --bench. Full source policy and axiom gate intentionally reject this prototype. Never submit.','mechanism':'Guarded normal same-sign GRS right-alignment adder with sticky bits; actual algorithm alternative, all other inputs use certified fallback','attribution':'Runtime adapted from official textbook-unproved example; no championship/source identity claimed'},indent=2)+'\n').encode());print(OWN.name,hashlib.sha256(source.encode()).hexdigest())
