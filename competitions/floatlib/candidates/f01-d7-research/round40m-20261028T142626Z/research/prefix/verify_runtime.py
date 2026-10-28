"""Independent nonempty-line declaration-slice comparison; not a Lean check."""
from pathlib import Path
from collections import Counter
from datetime import datetime, timezone
import re
import json
import hashlib

root = next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').exists())
source = root/'competitions/floatlib/candidates/f01-r22-dev-indexed8-cost1/Kernel.lean'
target = root/'competitions/floatlib/candidates/f01-r23-research-unconditional-reader/Kernel.lean'
start = re.compile(r'(?m)^(?:@\[[^\n]*\]\s*)*(?:(?:private|protected|noncomputable|unsafe)\s+)*(?:def|abbrev|structure|inductive|instance)\s+([^\s(:{]+)')
boundary = re.compile(r'(?m)^(?:/[-*]|--|@\[|(?:(?:noncomputable|private|protected) )?(?:def|abbrev|theorem|lemma|structure|inductive|instance|example)\b|namespace |section\b|end\b|open |set_option |attribute |#)')

def slices(s):
    result = []
    for m in start.finditer(s):
        nxt = boundary.search(s, m.end())
        body = s[m.start():nxt.start() if nxt else len(s)]
        normalized = '\n'.join(line for line in body.splitlines() if line.strip())
        result.append((m.group(1), normalized))
    return result

sbytes, tbytes = source.read_bytes(), target.read_bytes()
sraw, traw = sbytes.decode('utf-8'), tbytes.decode('utf-8')
ss, ts = slices(sraw), slices(traw)
missing = list((Counter(ss)-Counter(ts)).elements())
needed = ['packB_get', 'packB_read', 'cacheView_read', 'zero_lane', 'loop_lane',
          'nat_loop_lane', 'nat_finish_lane', 'wordAt', 'ofBits_raw', 'tile_word',
          'DotReads', 'packed_getTile_word', 'packed_dot_reads',
          'finish_eq_dot', 'convert_eq', 'vector_get_ofFn', 'loop_s0', 'loop_s1']
missing_declarations = [name for name in needed if not re.search(r'\b(?:def|theorem|abbrev)\s+'+re.escape(name)+r'\b', traw)]
receipt = dict(
    checked_at_utc=datetime.now(timezone.utc).isoformat(),
    source=str(source.relative_to(root)), source_sha256=hashlib.sha256(sbytes).hexdigest(),
    target=str(target.relative_to(root)), target_sha256=hashlib.sha256(tbytes).hexdigest(), target_bytes=len(tbytes),
    source_runtime_declarations=len(ss), target_runtime_declarations=len(ts),
    missing_or_changed_runtime_slices=[dict(name=name,sha256=hashlib.sha256(body.encode()).hexdigest()) for name,body in missing],
    required_lexical_declarations=needed, missing_required_lexical_declarations=missing_declarations,
    result='PASS_STATIC_RUNTIME_SLICES_AND_REQUIRED_NAMES' if not missing and not missing_declarations else 'FAIL_STATIC_SCREEN',
    limitation='Standalone regex slice comparison and required-name existence only; namespace binding, implicit elaboration dependencies and proof correctness require pinned CI.',
    lean_status='NOT_RUN',
)
out=Path(__file__).resolve().parent/'unconditional-runtime-review.json'
out.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,indent=2))
