"""Independent current-source and exact four-slice replay; no candidate file."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json,re,time

base=Path(__file__).resolve().parent; root=base.parents[7]
def h(b):return sha256(b).hexdigest()
start=time.monotonic(); plan_bytes=(base/'budget.json').read_bytes(); p=json.loads(plan_bytes)
source=root/p['source']; raw=source.read_bytes()
assert h(raw)==p['source_sha256']=='2f998811caa348ad7c0e66026b0d049c6ce0720549dd12622345777d24a1e13e','STOP_SOURCE_HASH_CHANGED'
text=raw.decode('utf-8'); parts=[]; last=0; n=0
for row in p['selected']:
    lo,hi=row['start'],row['end']; piece=text[lo:hi].encode('utf-8')
    assert lo>=last and len(piece)==row['bytes'] and h(piece)==row['sha256']
    assert re.match(rb'theorem ',piece)
    assert not re.search(rb'(?im)^\s*(?:@\[|def\b|abbrev\b|instance\b|attribute\b|namespace\b|section\b|end\b|notation\b|set_option\b)',piece)
    assert b'/-' not in piece and b'--' not in piece
    assert row['name'].split('.')[-1] not in p['protected_names']
    parts.append(text[last:lo]);last=hi;n+=len(piece)
parts.append(text[last:]); result=''.join(parts).encode('utf-8')
assert n==2142==p['recovered_bytes'] and len(raw)-len(result)==n
assert h(result)==p['resulting_sha256'] and len(result)==253771
for row in p['selected']:
    leaf=row['name'].split('.')[-1]
    assert not re.search(r"(?<![\w'])"+re.escape(leaf)+r"(?![\w'])",result.decode('utf-8'))
assert source.read_bytes()==raw,'STOP_SOURCE_HASH_CHANGED_DURING_REPLAY'
receipt=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),state='FOUR_SLICE_REPLAY_VERIFIED_NOT_LEAN_VALIDATED',
             plan_sha256=h(plan_bytes),source_sha256=h(raw),source_bytes=len(raw),
             recovered_bytes=n,resulting_bytes=len(result),resulting_sha256=h(result),
             remaining_capacity_bytes=256000-len(result),all_slices_sha_match=True,
             no_attribute_comment_or_runtime_declaration_in_selected_slices=True,
             no_removed_leaf_or_child_prefix_text_references=True,source_still_unchanged=True,
             candidate_emitted=False,Lean='NOT_RUN',full_gate='NOT_RUN',tokens='UNKNOWN',
             elapsed_seconds=time.monotonic()-start)
assert receipt['elapsed_seconds']<4.5
(base/'verification.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,ensure_ascii=False,indent=2))
