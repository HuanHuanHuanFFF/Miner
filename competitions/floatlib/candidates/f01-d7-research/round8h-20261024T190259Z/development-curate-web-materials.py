"""Keep exact mathematical artifacts, separate private research-link receipts."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
SOURCE = OUT / 'astra-web-pro-materials'
DEST = OUT / 'development-web-materials-public'
PRIVATE = re.compile(r'https?://(?:chatgpt\.com|chat\.openai\.com)(?:/|\b)')
DEST.mkdir(exist_ok=False)
records, changed = [], []


def sanitize(value, path=''):
    if isinstance(value, dict):
        return {key: sanitize(item, path + '/' + key) for key, item in value.items()}
    if isinstance(value, list):
        return [sanitize(item, path + '/' + str(i)) for i, item in enumerate(value)]
    if isinstance(value, str) and PRIVATE.search(value):
        changed.append(path)
        return 'PRIVATE_RESEARCH_REFERENCE_RETAINED_LOCALLY'
    return value


for topic in ('common-rounding', 'integer-mul'):
    source = SOURCE / topic / 'intake.json'
    original = source.read_bytes()
    private_before = len(changed)
    result = dict(state='PUBLIC_DERIVATIVE_OF_LOCAL_INTAKE', original_receipt_sha256=hashlib.sha256(original).hexdigest(),
                  original_receipt_bytes=len(original), original_kept_local_unchanged=True,
                  intake=sanitize(json.loads(original)), scope='Private research URL values omitted; mathematical original artifact bytes are unchanged. This is not the original intake JSON.')
    result['private_reference_fields_omitted'] = changed[private_before:]
    target = DEST / (topic + '-intake.public.json')
    data = (json.dumps(result, ensure_ascii=False, indent=2) + '\n').encode()
    assert not PRIVATE.search(data.decode()) and source.read_bytes() == original
    target.write_bytes(data)
    records.append(dict(path=target.relative_to(ROOT).as_posix(), sha256=hashlib.sha256(data).hexdigest(), bytes=len(data), kind='public-intake-derivative'))
    for artifact in sorted((SOURCE / topic / 'originals').iterdir()):
        if not artifact.is_file():
            continue
        data = artifact.read_bytes()
        assert not PRIVATE.search(data.decode('utf-8'))
        records.append(dict(path=artifact.relative_to(ROOT).as_posix(), sha256=hashlib.sha256(data).hexdigest(), bytes=len(data), kind='original-mathematical-artifact'))
index = dict(at_utc=datetime.now(timezone.utc).isoformat(), state='EXACT_ARTIFACTS_AND_PUBLIC_RECEIPTS_NOT_COMPILED',
             artifacts=records, original_artifact_count=sum(row['kind'] == 'original-mathematical-artifact' for row in records),
             actual_web_response_backend='UNKNOWN', private_intake_originals_in_git=False,
             scope='Standalone mathematical reports/fragments only, not private conversation transcripts, prompts or URLs. Imported claims remain NOT_RUN until exact pinned validation. Confirmed mkW_ofNat correction was checked against local source independently.')
(DEST / 'index.json').write_bytes((json.dumps(index, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({'original_artifacts':index['original_artifact_count'], 'public_intakes':2, 'private_fields_omitted':len(changed), 'originals_modified':False}))
