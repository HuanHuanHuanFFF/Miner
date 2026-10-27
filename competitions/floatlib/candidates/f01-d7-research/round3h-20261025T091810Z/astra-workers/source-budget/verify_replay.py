"""Independent byte-slice replay of budget.json, without constructing a Kernel file."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
import json, re

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[6]
def h(b): return sha256(b).hexdigest()

start=monotonic()
record=json.loads((HERE/'budget.json').read_bytes())
plan=record['common_plan']; assert plan['recovery']==11990
receipts={}
for key, meta in record['sources'].items():
    path=ROOT/meta['path']; original=path.read_bytes()
    assert h(original)==meta['sha256'] and len(original)==meta['bytes']
    current=original; names=[]; recovered=0; count=0
    for stage in plan['rounds']:
        item=stage['sources'][key]
        assert h(current)==item['parent_sha256']
        text=current.decode('utf-8'); keep=[]; last=0; wave_bytes=0
        for row in item['rows']:
            lo,hi=row['start'],row['end']; piece=text[lo:hi].encode('utf-8')
            assert lo>=last and len(piece)==row['bytes'] and h(piece)==row['sha256']
            assert re.match(rb'(?:private |protected )?(?:theorem|lemma) ',piece)
            assert row['name'].split('.')[-1] not in meta['protected_public_names']
            assert not re.search(rb'(?im)^\s*(?:attribute|instance|def|abbrev|structure|inductive|notation|syntax|macro|export|namespace|section|end|set_option)\b',piece)
            assert b'/-' not in piece and b'--' not in piece, 'Selected slices should contain no comments'
            keep.append(text[last:lo]); last=hi
            names.append(row['name'].split('.')[-1]); wave_bytes+=len(piece); count+=1
        keep.append(text[last:]); current=''.join(keep).encode('utf-8')
        assert h(current)==item['result_sha256']
        assert wave_bytes==stage['recovery']; recovered+=wave_bytes
    assert len(original)-len(current)==recovered==11990
    final=current.decode('utf-8')
    missing=[n for n in names if re.search(r"(?<![\w'])"+re.escape(n)+r"(?![\w'])",final)]
    assert not missing, missing
    # Preserve originals and avoid claiming elaborator or gate validation.
    assert path.read_bytes()==original
    receipts[key]=dict(original_sha256=h(original),all_source_slices_verified=True,
                       all_selected_slices_plain_theorems_without_comments=True,
                       all_protected_public_names_preserved=True,
                       no_removed_leaf_or_generated_child_prefix_text_reference=True,
                       removed_declarations=count,recovered_bytes=recovered,
                       replay_bytes=len(current),replay_sha256=h(current),
                       original_still_unchanged=True)
assert monotonic()-start<4.5
result=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),state='BYTE_SLICE_REPLAY_VERIFIED_NOT_LEAN_VALIDATED',
            budget_sha256=h((HERE/'budget.json').read_bytes()),
            audit_script_sha256=h((HERE/'audit_budget.py').read_bytes()),
            verifier_script_sha256=h(Path(__file__).read_bytes()),sources=receipts,
            elapsed_seconds=monotonic()-start,Lean='NOT_RUN',CI='NOT_RUN',tokens='UNKNOWN')
(HERE/'replay-verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(result,ensure_ascii=False,indent=2))
