"""Independently authenticate selected B2 statement C; no local compiler."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
BASE = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168024176'
sha = lambda b: hashlib.sha256(b).hexdigest()
index = json.loads((BASE / 'original-artifact-hashes.json').read_bytes())
stage = BASE / index['directory']
for name, info in index['files'].items():
    raw = (stage / name).read_bytes()
    assert len(raw) == info['bytes'] and sha(raw) == info['sha256']
folder = stage / 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r15-dev-packed-b2-1'
source_index = json.loads((folder / 'candidate-c-index.json').read_bytes())
item = next(r for r in source_index if r['module'] == 'Submission')
raw = (folder / item['file']).read_bytes()
assert sha(raw) == item['sha256'] and item['kernel_sha256'] == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
text = raw.decode()
review_raw = (HERE / 'astra-b2-C-independent-review.json').read_bytes()
review = json.loads(review_raw)
lex = re.compile(r'"(?:\\.|[^"\\])*"|//[^\n]*|/\*[\s\S]*?\*/|[{}]')
rows = []
for name in ('lp_competition_Submission_R15PackedB2_packB___lam__0',
             'lp_competition_Submission_R15PackedB2_loop'):
    match = re.search(r'^LEAN_EXPORT [^\n]*\b' + re.escape(name) + r'\([^;\n]*\)\s*\{', text, re.M)
    assert match
    depth = 0
    for token in lex.finditer(text, match.end() - 1):
        if token[0] == '{': depth += 1
        elif token[0] == '}':
            depth -= 1
            if depth == 0:
                body = text[match.start():token.end()]
                break
    observed = next(r for r in review['function_bodies_checked'] if r['symbol'] == name)
    assert sha(body.encode()) == observed['body_sha256']
    counts = {n: len(re.findall(r'\b' + re.escape(n) + r'\s*\(', body)) for n in (
        'lean_alloc_ctor', 'lean_box_float32', 'lean_ctor_set_float32', 'lean_ctor_get_float32',
        'lean_float32_of_bits', 'lean_array_fget_borrowed', 'lean_nat_div', 'lean_nat_mod')}
    rows.append(dict(symbol=name, body_sha256=sha(body.encode()), static_sites=counts,
                     ctor_arguments=re.findall(r'lean_alloc_ctor\(([^)]*)\)', body)))
record = dict(at_utc=datetime.now(timezone.utc).isoformat(), run=40168024176,
    kernel_sha256=item['kernel_sha256'], original_files_verified=len(index['files']),
    source=(folder / item['file']).relative_to(ROOT).as_posix(), source_sha256=sha(raw),
    independent_research_review_sha256=sha(review_raw), observations=rows,
    scope='Exact diagnostic statement C; static implementation observations only, not actual timed-object assembly, dynamic counts, cycles or allocation totals. All original files remain unchanged.')
path = HERE / 'development-b2-generated-c-check.json'
assert not path.exists()
path.write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps(record))
