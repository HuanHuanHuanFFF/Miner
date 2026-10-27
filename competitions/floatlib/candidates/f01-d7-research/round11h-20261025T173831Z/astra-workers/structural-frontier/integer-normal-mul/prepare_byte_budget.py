"""Remove unused ordinary proof leaves only in a new preview, preserving all runtime definitions."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
src=H/'Public-math-layout-v1.lean.txt';data=src.read_bytes()
base=(R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert data.startswith(base)
needed=max(0,len(data)-255500)
boundaries=list(re.finditer(rb'(?m)^(?:theorem\b|def\b|abbrev\b|structure\b|class\b|instance\b|namespace\b|end\b|section\b|open\b|attribute\b|set_option\b|@\[|/-|--|#)',base))
leaves=[]
for m in re.finditer(rb'(?m)^theorem ([A-Za-z_][A-Za-z_0-9]*)\b',base):
 name=m.group(1)
 if name.endswith(b'_spec'):continue
 if len(re.findall(rb'(?<![A-Za-z_0-9])'+re.escape(name)+rb'(?![A-Za-z_0-9])',data))!=1:continue
 before=base[:m.start()].rstrip().splitlines()
 if before and before[-1].lstrip().startswith(b'@['):continue
 stop=next((x.start() for x in boundaries if x.start()>m.start()),len(base))
 raw=base[m.start():stop]
 if b'namespace ' in raw or re.search(rb'(?m)^(?:def|abbrev|instance|end|open|attribute)\b',raw):continue
 leaves.append(dict(name=name.decode(),start=m.start(),end=stop,bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest()))
selected=[];saved=0
for row in sorted(leaves,key=lambda x:-x['bytes']):
 if saved>=needed:break
 selected.append(row);saved+=row['bytes']
assert saved>=needed,(saved,needed)
cut=data
for row in sorted(selected,key=lambda x:-x['start']):cut=cut[:row['start']]+cut[row['end']:]
assert len(cut)<=256000 and b'\r' not in cut
# Reinsert exact original ranges to prove the preview has no other differences.
rebuilt=cut
offset=0
for row in sorted(selected,key=lambda x:x['start']):
 at=row['start'];rebuilt=rebuilt[:at]+data[row['start']:row['end']]+rebuilt[at:]
assert rebuilt==data
out=H/'Public-math-pruned-preview-v1.lean';out.write_bytes(cut)
j=dict(updated_utc=datetime.now(timezone.utc).isoformat(),state='UNUSED_ORDINARY_PROOF_LEAF_PREVIEW_NOT_FOR_CI',
 original_preview=dict(path=src.name,bytes=len(data),sha256=hashlib.sha256(data).hexdigest()),
 preview=dict(path=out.name,bytes=len(cut),sha256=hashlib.sha256(cut).hexdigest(),margin=256000-len(cut)),
 removed=selected,saved=saved,exact_inverse_rebuild=True,
 conditions=['Every removed untagged ordinary theorem name occurs exactly once in the entire assembled source',
 'No public *_spec, runtime definition, namespace boundary or attribute removed',
 'Only a new preview is changed; frozen B2/9f9/v3 original sources untouched'],
 limitations=['Lean elaboration and all new proof/helper audits NOT_RUN','Known UInt64 Int.toNat normalization repair remains prerequisite',
 'This is not the unchanged-prefix9f9 probe; it is a separate later public-math preview'],CI=False,Git=False,local_Lean=False)
(H/'byte-budget-preview.json').write_bytes((json.dumps(j,indent=2)+'\n').encode())
print(json.dumps({k:j[k] for k in ('state','preview','saved','removed')}))
