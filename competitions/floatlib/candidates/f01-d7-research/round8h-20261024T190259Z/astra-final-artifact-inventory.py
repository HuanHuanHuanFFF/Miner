"""Research-owned pending paths for the sole Git coordinator; no staging/push."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json
import subprocess

base=Path(__file__).resolve().parent;root=base.parents[4]
prefix=base.relative_to(root).as_posix()+'/'
raw=subprocess.check_output(['git','status','--porcelain=v1','-z','--untracked-files=all','--',prefix],cwd=root,timeout=8)
rows=[]
for entry in raw.split(b'\0'):
    if not entry:continue
    status=entry[:2].decode();rel=entry[3:].decode('utf-8')
    if not rel.startswith(prefix+'astra-'):continue
    p=root/rel
    if p.is_file():
        b=p.read_bytes();rows.append(dict(path=rel,status=status,bytes=len(b),sha256=sha256(b).hexdigest()))
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),state='RESEARCH_HANDOFF_NO_GIT_MUTATION',
    pending_research_files=rows,count=len(rows),private_intakes='Keep exact .gitignore exclusions; do not blind-add private web chat intake/prompt/dispatch.',
    final_review='astra-rse-final-interface-review.md',
    current_index='astra-status.json',development_owner='D remains sole commit/push/CI coordinator',
    deadline_utc='2026-10-25T03:02:59Z',note='Snapshot excludes this self-referential inventory; include it explicitly if useful. No raw original file rewritten.')
(base/'astra-final-artifact-inventory.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(at_utc=record['timestamp_utc'],pending_research_files=len(rows)),ensure_ascii=False))
