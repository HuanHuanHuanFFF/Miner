"""Archive an observed Pro Markdown download from E, preserving its original bytes."""
from pathlib import Path
import argparse,datetime,hashlib,json
HERE=Path(__file__).resolve().parent
ap=argparse.ArgumentParser();ap.add_argument('source');ap.add_argument('--topic',required=True);ap.add_argument('--chat-url',required=True);args=ap.parse_args()
src=Path(args.source).resolve();assert src.is_relative_to(Path('E:/Download').resolve()) and src.is_file()
assert src.suffix.lower()=='.md','Only the observed Markdown artifact; no executables or archives'
raw=src.read_bytes();assert len(raw)<=2*1024*1024
stamp=datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
dest=HERE/'pro-results'/stamp;dest.mkdir(parents=True,exist_ok=False)
copy=dest/src.name;copy.write_bytes(raw);assert copy.read_bytes()==raw
record=dict(intake_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),source_path=str(src),copy_path=str(copy),bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest(),topic=args.topic,chat_url=args.chat_url,
 model='UI-selected GPT-6 with Pro fifth effort position; backend version UNKNOWN',
 status='UNVERIFIED_EXTERNAL_MATHEMATICAL_REVIEW',scope='Read-only proposed algorithms and paper proofs; not implemented/Lean-checked/timed/adopted',
 source_policy='Only independently described mathematics/public URLs sent; no complete license-unknown third-party source uploaded',
 first_download_destination='E:/Download as observed from browser download event',archives='NONE')
(dest/'receipt.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,ensure_ascii=False))
