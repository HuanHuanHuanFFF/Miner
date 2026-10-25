"""A real B-reuse component on the exact published p2/n1 combination."""
from pathlib import Path
from datetime import datetime, timezone
import difflib
import hashlib
import json
import time

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
started = time.perf_counter()
original = (C / 'f01-d12-scalar-combined/Kernel.lean').read_bytes()
compact = (C / 'f01-r14-dev-compact-base/Kernel.lean').read_bytes()
published = (C / 'f01-r14-dev-p2-n1-cache/Kernel.lean').read_bytes()
assert hashlib.sha256(original).hexdigest() == 'df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
assert hashlib.sha256(compact).hexdigest() == '3c6af73f9d679e9831ac8c4abb9f0e6d41b61718301dd045bedd2402e980632a'
assert hashlib.sha256(published).hexdigest() == '83a981273988f07ce89d4a18c1dbef475adb6ed2fefce381138c5d165bf2a806'
old, small, new = [data.decode().splitlines(keepends=True) for data in (original, compact, published)]
assert len(old) == len(small) and len(old) < 8000 and len(new) < 8000
parts = []
changes = []
for op, a, b, c, d in difflib.SequenceMatcher(a=old, b=new, autojunk=False).get_opcodes():
    parts.extend(small[a:b] if op == 'equal' else new[c:d])
    if op != 'equal':
        changes.append(dict(kind=op, original_lines=[a + 1, b], published_lines=[c + 1, d]))
assert time.perf_counter() - started < 5, 'Local source-only construction exceeded5second cap'
base = ''.join(parts)
assert base.count('end Submission.R13N1Prepared') == 1
assert base.count('else R13N1Prepared.dispatch batch m n p A B') == 1
assert base.count('exact R13N1Prepared.dispatch_spec batch m n p A B') == 1
# Update the earlier caller before adding the new component, so its own
# fallback continues to call R13 and cannot become self-recursive.
base = base.replace('else R13N1Prepared.dispatch batch m n p A B', 'else R14ThinBCache.dispatch batch m n p A B')
base = base.replace('exact R13N1Prepared.dispatch_spec batch m n p A B', 'exact R14ThinBCache.dispatch_spec batch m n p A B')
fragment = OUT / 'development-thin-bcache.lean'
part = fragment.read_bytes()
anchor = 'end Submission.R13N1Prepared\n'
result = base.replace(anchor, anchor + '\n' + part.decode() + '\n', 1).encode()
assert len(result) <= 256000
assert result.count(b'else R13N1Prepared.dispatch batch m n p A B') == 1
assert result.count(b'else R14ThinBCache.dispatch batch m n p A B') == 1
folder = C / 'f01-r14-dev-thin-bcache1'
assert not folder.exists()
folder.mkdir()
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=hashlib.sha256(result).hexdigest(),
              candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(), validation_mode='full-gate',
              proof_status='COMPLETE_SOURCE_PROOF_ATTEMPT_NOT_COMPILED', performance='NOT_RUN',
              parent='f01-r14-dev-p2-n1-cache', parent_sha256=hashlib.sha256(published).hexdigest(),
              compact_parent_sha256=hashlib.sha256(compact).hexdigest(), base_line_edits=changes,
              fragment=fragment.relative_to(ROOT).as_posix(), fragment_sha256=hashlib.sha256(part).hexdigest(),
              mechanism='For m>=4,n>1,0<p<=2, map raw B to native Float32 once for reuse across rows, keep A raw and convert it in the original ordered dot, emit each output directly, retain raw A/B for exact NaN replay. n=1 keeps the already checked prepared-A route. No new dimension threshold grid.',
              history='M29 ce6832e6 cached both sides only for n=1,p>2,m>=4; its exposed853 draw did not reach the B cache. This route changes long-thin n>1 direct callers and keeps n1 unchanged; no historic speedup inherited. Published83a9 passed fixed978 full gate40136215532, but this changed candidate has no gate yet.',
              limits='B map/boxed storage/allocation, traversal, guards and output costs must all remain inside actual timed entry. Potential input MAC coverage is not time saved. Full source/spec and current public-v2 paired gates still required.')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
(OUT / 'development-thin-bcache-build.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({key: record[key] for key in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status', 'performance')}))
