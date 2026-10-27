"""Static exact-delta checks and bounded address traces. This never runs Lean."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re
import time

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
start = time.monotonic()
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
source = ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
base = source.read_text(encoding='utf-8')
assert sha(source) == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
begin = base.index('namespace Submission.R15PackedB2\n')
end = base.index('end Submission.R15PackedB2', begin)
old_namespace = base[begin:end]
decl = re.compile(r'(?m)^(?:@\[inline\] )?(?:def|theorem) ([A-Za-z0-9_]+)\b')
matches = list(decl.finditer(old_namespace))
old_blocks = {m.group(1): old_namespace[m.start():matches[i+1].start() if i+1<len(matches) else len(old_namespace)]
              for i,m in enumerate(matches)}
rows = []
for filename, manifest_name in (('Kernel-indexed-b2.draft.lean','draft-manifest.json'),
                                ('Kernel-hoisted-b2.draft.lean','hoisted-draft-manifest.json')):
    path = HERE / filename
    body = path.read_text(encoding='utf-8')
    manifest = json.loads((HERE/manifest_name).read_text(encoding='utf-8'))
    assert sha(path) == manifest['draft']['sha256']
    b = body.index('namespace Submission.R15PackedB2\n')
    e = body.index('end Submission.R15PackedB2', b)
    assert body[:b] == base[:begin] and body[e:] == base[end:]
    permitted = {'group','group_eq'} if 'hoisted' not in filename else {'output','output_eq'}
    unchanged = [name for name,block in old_blocks.items() if name not in permitted and block.rstrip() in body[b:e]]
    expected = set(old_blocks) - permitted
    assert set(unchanged) == expected, expected - set(unchanged)
    for token in ('sorry','axiom ','unsafe ','implemented_by ','extern '):
        assert body.count(token) == base.count(token)
    assert body.count('import ContractTensor') == 1
    assert len(path.read_bytes()) <= 256000
    rows.append(dict(path=filename,sha256=sha(path),bytes=path.stat().st_size,
                     old_declarations_preserved=unchanged, lean='NOT_RUN'))

guarded_shapes = old_fallback_shapes = trace_pairs = 0
edge_witnesses = []
# Small artificial word sizes make wraparound and zero-size edges reachable.
for word_size in (16, 256):
    for batch in range(4):
        for m in range(10):
            for n in range(10):
                a_size = batch*m*n
                fast = 0 < n and a_size < word_size
                if fast:
                    guarded_shapes += 1
                    for r in range(batch*m):
                        base_a = r*n
                        assert n < word_size and base_a < word_size
                        assert base_a + max(n-1,0) < a_size
                        for k in range(n):
                            old_address = base_a+k
                            word_address = (base_a+k) % word_size
                            assert old_address == word_address < a_size
                            assert (k+1) % word_size == k+1
                            trace_pairs += 1
                else:
                    old_fallback_shapes += 1
                if a_size == word_size or n == 0 or (batch*m == 0 and n > 0):
                    if len(edge_witnesses) < 20:
                        edge_witnesses.append(dict(word_size=word_size,batch=batch,m=m,n=n,A_size=a_size,fast=fast))
                assert time.monotonic()-start < 4.5
# General runDot guard: even arbitrary raw array bounds/defaults retain exact fallback.
general_steps = 0
for word_size in (16, 256):
    for n in range(12):
        for base_a in range(20):
            for a_size in range(24):
                guard = n < word_size and base_a < word_size and base_a+max(n-1,0)<a_size and a_size<word_size
                if guard:
                    for k in range(n):
                        assert (base_a+k)%word_size == base_a+k < a_size
                        assert (k+1)%word_size == k+1
                        general_steps += 1
                assert time.monotonic()-start < 4.5

record = dict(at_utc=datetime.now(timezone.utc).isoformat(),state='STATIC_DELTA_AND_FINITE_ADDRESS_MODELS_PASS',
              drafts=rows, row_guarded_shapes=guarded_shapes, fallback_shapes=old_fallback_shapes,
              row_trace_pairs=trace_pairs, general_guard_steps=general_steps,
              edge_witnesses=edge_witnesses, word_size_models=[16,256],
              limits=['No Lean parsing/typechecking/proof replay/axiom audit was performed',
                      'Finite address traces do not prove unbounded correctness or floating-point equality',
                      'No generated code, full gate, performance or MainFull stage cost was measured'],
              elapsed_seconds=time.monotonic()-start)
(HERE/'validation.json').write_text(json.dumps(record,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:record[k] for k in ('state','row_guarded_shapes','fallback_shapes','row_trace_pairs','general_guard_steps','elapsed_seconds')},indent=2))
