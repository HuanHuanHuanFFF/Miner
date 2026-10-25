"""Read exact statement-layer C; do not call it the subsequent timed object."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import re
import subprocess
import argparse

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
BASE = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40166091242'
sha = lambda b: hashlib.sha256(b).hexdigest()
index = json.loads((BASE / 'original-artifact-hashes.json').read_bytes())
ci = json.loads((BASE / 'ci-run.json').read_bytes())
STAGE = BASE / index['directory']
for relative, record in index['files'].items():
    raw = (STAGE / relative).read_bytes()
    assert len(raw) == record['bytes'] and sha(raw) == record['sha256']
parser = argparse.ArgumentParser()
parser.add_argument('--revision', type=int, choices=[1, 2], default=2)
audit_args = parser.parse_args()
suffix = '' if audit_args.revision == 1 else '-v2'
OUT = HERE / ('development-codegen-40166091242' + suffix)
assert not OUT.exists()
OUT.mkdir()
function = re.compile(r'^(?:LEAN_EXPORT )?(?:lean_object\*|uint32_t|uint64_t|float|double)\s+([A-Za-z_][A-Za-z0-9_]*)\(([^;\n]*)\)\s*\{', re.M)
tokens = re.compile(r'"(?:\\.|[^"\\])*"|\x27(?:\\.|[^\x27\\])*\x27|//[^\n]*|/\*[\s\S]*?\*/|[{}]')
records = []
for candidate in ['f01-r15-dev-column-pairs2', 'f01-r15-dev-mul-branchless1']:
    prefix = 'diagnostics/f01-d7-public-suite/public-suite/'
    kp = STAGE / prefix / 'inputs' / candidate / 'Kernel.lean'
    kernel = kp.read_bytes()
    original = subprocess.check_output(['git', 'show', ci['headSha'] + ':competitions/floatlib/candidates/' + candidate + '/Kernel.lean'], cwd=ROOT)
    assert kernel == original
    folder = STAGE / prefix / 'diagnostics' / candidate
    cindex = json.loads((folder / 'candidate-c-index.json').read_bytes())
    for source in cindex:
        raw = (folder / source['file']).read_bytes()
        assert sha(raw) == source['sha256'] and source['kernel_sha256'] == sha(kernel)
        text = raw.decode()
        for m in function.finditer(text):
            name, args = m[1], m[2]
            scalar_main = source['module'] == 'MainFull' and 'main___lam__' in name and len(re.findall(r'uint32_t\s+[A-Za-z_][A-Za-z0-9_]*', args)) == 2
            chosen = scalar_main or (
                source['module'] == 'Submission' and any(n in name for n in (
                    'R15BranchlessNormal_round', 'R15BranchlessNormal_core',
                    'R14DIntegerNormal_core', 'FastMul_rse', 'R15ThinPairs_loop'))
                and not name.endswith('___boxed'))
            if not chosen:
                continue
            start = m.end() - 1
            depth = 0
            end = None
            for token in tokens.finditer(text, start):
                if token[0] == '{': depth += 1
                elif token[0] == '}':
                    depth -= 1
                    if depth == 0:
                        end = token.end()
                        break
            assert end is not None
            body = text[m.start():end].encode()
            label = candidate.removeprefix('f01-r15-dev-') + '-' + source['module'] + '-' + str(len(records)) + '.c'
            target = OUT / label
            target.write_bytes(body)
            counts = {needle: len(re.findall(r'\b' + re.escape(needle) + r'\s*\(', body.decode())) for needle in (
                'lean_apply_1', 'lean_apply_2', 'lean_alloc_ctor', 'lean_box_float32',
                'lean_box_uint64', 'lean_float32_of_bits', 'lean_float32_to_bits',
                'lean_float32_add', 'lean_float32_mul', 'lean_uint64_land',
                'lean_uint64_lor', 'lean_uint64_shift_right')}
            records.append(dict(candidate=candidate, kernel_sha256=sha(kernel), module=source['module'],
                source_file=(folder / source['file']).relative_to(ROOT).as_posix(), source_sha256=sha(raw),
                symbol=name, signature=m[0].split('{')[0].strip(),
                original_c_line=text.count('\n', 0, m.start()) + 1,
                extracted_path=target.relative_to(ROOT).as_posix(), bytes=len(body), sha256=sha(body), static_sites=counts))
report = dict(at_utc=datetime.now(timezone.utc).isoformat(), run=40166091242, source_commit=ci['headSha'], audit_revision=audit_args.revision,
              original_artifact_files_verified=len(index['files']), functions=records,
              scope='Exact statement-layer Submission/MainFull C captured in40166091242. Static sites only, not dynamic counts, branch prediction, cycles, or the subsequently timed40166656717 object. Native assembly captured by the generic hook selects old Packed10Index loops, not the new scalar MUL.',
              extracted_bytes_preserved=True)
path = HERE / ('development-codegen-audit-40166091242' + suffix + '.json')
assert not path.exists()
path.write_bytes((json.dumps(report, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps(dict(report=path.relative_to(ROOT).as_posix(), functions=len(records),
    selected=[dict(candidate=r['candidate'], module=r['module'], symbol=r['symbol'], bytes=r['bytes']) for r in records])))
