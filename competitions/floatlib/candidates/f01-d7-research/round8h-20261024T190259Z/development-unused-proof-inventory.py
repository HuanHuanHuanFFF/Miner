"""Read-only conservative proof headroom inventory; never edits a Kernel."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter
import hashlib
import json
import re
import time

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
SOURCE = ROOT / 'competitions/floatlib/candidates/f01-r14-dev-combined-slim1/Kernel.lean'
raw = SOURCE.read_bytes()
assert hashlib.sha256(raw).hexdigest() == 'd94060b28aa4d374c16cdd0b8ee26ee7ba570155476bbf743877e4e3212ff277'
text = raw.decode()
started = time.perf_counter()
masked, docs = list(text), []
index, depth, in_string, doc_start = 0, 0, False, None
while index < len(text):
    if depth:
        if text.startswith('/-', index):
            depth += 1
            masked[index:index + 2] = '  '
            index += 2
        elif text.startswith('-/', index):
            depth -= 1
            masked[index:index + 2] = '  '
            index += 2
            if not depth and doc_start is not None:
                docs.append((doc_start, index))
                doc_start = None
        else:
            if text[index] != '\n':
                masked[index] = ' '
            index += 1
    elif in_string:
        if text[index] == '\\' and index + 1 < len(text):
            masked[index:index + 2] = '  '
            index += 2
        else:
            in_string = text[index] != '"'
            if text[index] != '\n':
                masked[index] = ' '
            index += 1
    elif text.startswith('--', index):
        end = text.find('\n', index)
        end = len(text) if end < 0 else end
        masked[index:end] = ' ' * (end - index)
        index = end
    elif text.startswith('/-', index):
        doc_start = index if text.startswith('/--', index) else None
        depth = 1
        masked[index:index + 2] = '  '
        index += 2
    elif text[index] == '"':
        in_string = True
        masked[index] = ' '
        index += 1
    else:
        index += 1
assert not depth and not in_string
clean = ''.join(masked)
counts = Counter(re.findall(r"[A-Za-z_][A-Za-z0-9_']*", clean))
lines = clean.splitlines(keepends=True)
starts, offset = [], 0
for line in lines:
    starts.append(offset)
    offset += len(line)
commands = [i for i, line in enumerate(lines) if re.match(r'^(?:@\[|(?:private\s+|protected\s+)?(?:theorem|lemma|def|abbrev|structure|inductive|instance|namespace|end|open|set_option|attribute|notation|noncomputable|variable|section|include|omit|import)\b)', line)]
rows = []
for line_number in commands:
    match = re.match(r'^(?:theorem|lemma) ([A-Za-z_][A-Za-z0-9_]*)\b', lines[line_number])
    if not match:
        continue
    name = match[1]
    if len(name) < 10 or counts[name] != 1:
        continue
    start = starts[line_number]
    if any(not clean[end:start].strip() for _, end in docs if end <= start):
        continue
    previous = next((lines[i].strip() for i in range(line_number - 1, -1, -1) if lines[i].strip()), '')
    if previous.endswith(']') or previous.startswith('set_option') or '@[' in previous:
        continue
    end_line = next((i for i in commands if i > line_number), len(lines))
    while end_line > line_number and not lines[end_line - 1].strip():
        end_line -= 1
    end = starts[end_line] if end_line < len(starts) else len(text)
    block = text[start:end].encode()
    rows.append(dict(name=name, start_line=line_number + 1, end_line_exclusive=end_line + 1,
                     character_start=start, character_end=end, bytes=len(block), sha256=hashlib.sha256(block).hexdigest(),
                     declaration_tokens_in_comment_free_source=1))
assert time.perf_counter() - started < 5
record = dict(at_utc=datetime.now(timezone.utc).isoformat(), state='PROPOSED_UNUSED_PROOF_INVENTORY_ONLY', source=SOURCE.relative_to(ROOT).as_posix(),
              source_sha256=hashlib.sha256(raw).hexdigest(), proposed_bytes=sum(row['bytes'] for row in rows), rows=rows,
              global_search_tactics_present=bool(re.search(r'\b(?:exact\?|apply\?|library_search|aesop|solve_by_elim)', clean)),
              scope='Conservative ASCII theorem-name occurrence inventory, excluding immediate attributes/docstrings/scoped options. No declarations removed, no Lean run, no claim that implicit elaboration dependencies have been checked. Full exact-source gate remains necessary.')
(OUT / 'development-unused-proof-inventory.json').write_bytes((json.dumps(record, indent=2) + '\n').encode())
print(json.dumps({key: value for key, value in record.items() if key != 'rows'}))
print(json.dumps(sorted(rows, key=lambda row: -row['bytes'])[:20]))
