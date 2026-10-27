"""Freeze exact research component and its anticipated development interface."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import re
import json

base=Path(__file__).resolve().parent;root=base.parents[4]
path=base/'astra-word-add-raw-model1.lean';raw=path.read_bytes();source=raw.decode('utf-8')
assert not re.search(r'^\s*(?:import|axiom|constant|unsafe|partial|noncomputable|variable)\b',source,re.M)
assert not re.search(r'\b(?:sorry|admit|native_decide)\b',source)
deps=[]
for name in ['development-word-add-runtime3.lean','development-word-add-word-bridges-draft.lean',
             'astra-word-add-alignment2.lean','astra-word-add-bounds1.lean',
             'astra-word-add-model-bridge1.lean','development-word-add-foundation3.lean']:
    b=(base/name).read_bytes()
    deps.append(dict(path=name,bytes=len(b),sha256=sha256(b).hexdigest()))
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
    state='SOURCE_COMPLETE_DRAFT_NOT_COMPILED',
    request='20261025T004700000Z-r14-development-word-add-final-bridge-request.md',
    component=dict(path=path.relative_to(root).as_posix(),bytes=len(raw),sha256=sha256(raw).hexdigest()),
    theorem='Submission.R14WordAdd.raw_add_model',dependencies=deps,
    required_interface=dict(name='Submission.R14WordAdd.magnitudeNat',
        definition='R14WordAddAlignment.magnitude (wordSign(high u v)) (wordSign(low u v)) (mantissa(high u v)).toNat (mantissa(low u v)).toNat (gap u v).toNat',
        status='AGREED_INTERFACE_MUST_BE_DEFINED_BY_D_BEFORE_COMPONENT'),
    proof_path=['eligible_conditions normal input decodes',
                'sort-case sign/order conditions and exact gap',
                'exact_high_low or exact_low_high at decoded dyadic level',
                'N nonzero and log2>=24 from frozen magnitude/log2 bounds',
                'raw_normal_decode in original u/v order',
                'model_add_normal with caller-supplied complete exponent<=254'],
    exclusions='No raw Model.add commutativity, no input/domain expansion, no word runtime integration, no CI candidate or publication.',
    remaining='Actual Lean elaboration and D word-field/final add_spec assembly. A source-complete proof attempt is not an accepted theorem.')
(base/'astra-word-add-raw-model1.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
status_path=base/'astra-status.json';status=json.loads(status_path.read_text(encoding='utf-8'))
status['updated_at_utc']=record['timestamp_utc'];status['state']='R14_RAW_MODEL_ADD_BRIDGE_SOURCE_COMPLETE_NOT_COMPILED'
status['current_question']='Await D actual magnitudeNat/interface integration; independently check exact bridge composition and source APIs. Word fields/public entry remain D-owned.'
status['new_mathematical_task']['final_bridge']=record['component']
status['new_mathematical_task']['status']=record['state']
status['processed_shared_message_ids'].append(record['request'])
status['next_action']='Handoff exact raw_add_model component to D, then review integration/API feedback without new CI or publication.'
for p in [path,base/'astra-word-add-raw-model1.json',base/'astra-word-add-uint-bridges1.lean',base/'astra-d-support-integration-audit.json']:
    rel=p.relative_to(root).as_posix()
    if rel not in status['artifacts']:status['artifacts'].append(rel)
tmp=base/'astra-status.json.tmp';tmp.write_text(json.dumps(status,ensure_ascii=False,indent=2)+'\n',encoding='utf-8');tmp.replace(status_path)
print(json.dumps(record,ensure_ascii=False,indent=2))
