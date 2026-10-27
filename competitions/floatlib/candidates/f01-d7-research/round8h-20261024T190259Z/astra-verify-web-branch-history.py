"""Read-only E/current-file/Git-blob equality for four downloaded artifacts."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
import json
import subprocess

base=Path(__file__).resolve().parent;root=base.parents[4]
start=monotonic();limit=3.0
head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=root,timeout=2).decode().strip()
index=json.loads((base/'development-web-materials-public/index.json').read_bytes())
rows=[]
for artifact in index['artifacts']:
    path=artifact['path'];work=(root/path).read_bytes()
    committed=subprocess.check_output(['git','cat-file','blob',f'HEAD:{path}'],cwd=root,timeout=2)
    assert work==committed and sha256(work).hexdigest()==artifact['sha256']
    row=dict(path=path,bytes=len(work),sha256=sha256(work).hexdigest(),git_blob_equal=True)
    if artifact['kind']=='original-mathematical-artifact':
        e=Path('E:/Download/FloatLib/20261025-R14')/Path(path).name
        assert e.read_bytes()==work
        row['e_copy_equal']=True
    else:
        assert b'chatgpt.com/c/' not in work
    rows.append(row)
    assert monotonic()-start<limit
private=[]
for path in ['astra-web-pro-materials/common-rounding/intake.json',
             'astra-web-pro-materials/integer-mul/intake.json']:
    rel=(base/path).relative_to(root).as_posix()
    tracked=subprocess.run(['git','cat-file','-e',f'HEAD:{rel}'],cwd=root,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL,timeout=2)
    ignored=subprocess.run(['git','check-ignore','--quiet',rel],cwd=root,timeout=2)
    assert tracked.returncode!=0 and ignored.returncode==0
    private.append(dict(path=rel,tracked_in_head=False,ignored=True))
record=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
    state='FOUR_ORIGINALS_E_WORKING_TREE_LOCAL_BRANCH_BLOBS_EQUAL',local_commit=head,
    elapsed_seconds=monotonic()-start,budget_seconds=limit,
    artifacts=rows,private_intakes=private,original_count=4,
    archives_received=0,archive_cleanup='NONE_REQUIRED_NO_ZIP_RECEIVED',
    remote_publication='Not asserted; current new public scope still held by D pending human reply.',
    scope='Exact data preservation and local branch history only; no compiler, performance or model-backend acceptance.')
Path(__file__).with_suffix('.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in record.items() if k not in ['artifacts','private_intakes']},ensure_ascii=False,indent=2))
