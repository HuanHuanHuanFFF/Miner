"""Read-only original artifact audit; derived evidence is written beside this script."""
from pathlib import Path
from types import SimpleNamespace
import ast
import hashlib
import json
import re
import zipfile
from datetime import datetime, timezone

ROOT = Path(__file__).resolve().parent
sha = lambda b: hashlib.sha256(b).hexdigest()
now = datetime.now(timezone.utc).isoformat()
rows = []
for ident in ['R2-W01c', 'R2-W04']:
    receipt = json.loads((ROOT / 'web' / ident / 'download-receipt.json').read_text())
    archive = Path(receipt['original_download'])
    assert sha(archive.read_bytes()) == receipt['original_sha256']
    root = Path(receipt['extracted_root'])
    with zipfile.ZipFile(archive) as z:
        assert z.testzip() is None
        report = z.read(receipt['report_in_zip'])
        assert sha(report) == receipt['report_sha256']
        disk_report = Path(receipt['original_report'] or 'E:/Download/R2-W04.md')
        assert disk_report.read_bytes() == report
        prefix = receipt['report_in_zip'].rsplit('/', 1)[0] + '/'
        files = [i for i in z.infolist() if not i.is_dir()]
        for member in files:
            assert member.filename.startswith(prefix)
            rel = member.filename[len(prefix):]
            assert '..' not in Path(rel).parts
            assert (root / rel).read_bytes() == z.read(member)
    rows.append({'id': ident, 'zip': str(archive), 'zip_sha256': sha(archive.read_bytes()),
                 'crc': 'PASS', 'all_extracted_files_byte_equal': len(files),
                 'report': str(disk_report), 'report_sha256': sha(report)})

w4 = ROOT / 'web/R2-W04/original-extracted/R2-W04'
gate = w4 / 'upstream/official/gate.py'
gate_bytes = gate.read_bytes()
assert sha(gate_bytes) == '2d2e97dcbe7e4a131a5655c915e63ffc05c3c34c3f6977534bf4bfd337434ff8'
# These exact official pure functions and constant expressions were read before use.
tree = ast.parse(gate_bytes.decode())
constants = {'_MAX_BYTES', 'AXIOMS', 'OPTIONS', 'ATTRIBUTES', 'BANNED'}
functions = {'intake', 'policy', 'options'}
selected = [n for n in tree.body if
    (isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in constants for t in n.targets))
    or (isinstance(n, ast.FunctionDef) and n.name in functions)]
env = {'re': re, 'Path': Path, 'Verdict': object,
       'SLOTS': {'full': SimpleNamespace(contract='ContractTensor')}}
exec(compile(ast.Module(body=selected, type_ignores=[]), str(gate), 'exec'), env)
scans = []
for p in [w4/'Kernel.lean', ROOT/'web/R2-W01c/original-extracted/FloatLib_R2-W01c/lean/NormalEqAttempt.lean',
          ROOT/'web/R2-W01c/original-extracted/FloatLib_R2-W01c/lean/ReusableModel.lean']:
    v = SimpleNamespace(slot='full')
    scans.append({'file': str(p.relative_to(ROOT)), 'sha256': sha(p.read_bytes()),
                  'bytes': p.stat().st_size, 'intake': env['intake'](p,v) or 'PASS',
                  'policy': env['policy'](p,v) or 'PASS', 'lean_compilation': 'NOT_RUN'})

parent = (w4/'upstream/Kernel.parent.lean').read_bytes()
candidate = (w4/'Kernel.lean').read_bytes()
assert sha(parent) == '5be0735a90d58d9efb8ee2c6d666c11029bca66665dca03b6b5eff5baf6cbfc4'
assert sha(candidate) == '98cef0f25c29fe22cf7fa32cc3fb0f2bc38bf1faf65f91aae4fd2d995fe13d84'
prefix = b'namespace CheckedFloatArray\n'
assert parent.split(prefix)[0] == candidate.split(prefix)[0]
def dot_block(b):
    start = b.index(b'def dotLoop ', b.index(prefix))
    end = b.index(b'end CheckedFloatArray', start)
    return b[start:end]
assert dot_block(parent) == dot_block(candidate)
w1 = ROOT / 'web/R2-W01c/original-extracted/FloatLib_R2-W01c/public_sources'
fixed = w1 / 'floatlib_fixed/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean'
newer = w1 / 'floatlib_comparison/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Exact.lean'
marker = "/-- A nonzero decoded dyadic already uses the format's canonical exponent. -/"
def representation_block(path):
    text = path.read_text(encoding='utf-8')
    start = text.index(marker)
    return text[start:text.index('\nend ', start)].rstrip().encode('utf-8')
fixed_block, newer_block = representation_block(fixed), representation_block(newer)
assert fixed_block == newer_block
assert sha(fixed_block) == 'a1534622adfdb290ef9af0a3985dbf98a4279444f626aa40d703c73cd2780dac'
result = {'checked_at_utc': now, 'artifacts': rows, 'official_pure_policy_scans': scans,
          'w04_protected_prefix_bytes': len(parent.split(prefix)[0]),
          'w04_checked_dot_unchanged': True, 'downloaded_scripts_executed': False,
          'w01c_pinned_representation_block': {'bytes': len(fixed_block), 'sha256': sha(fixed_block),
              'byte_equal_to_later_moved_block': True, 'pin_update_required_for_these_seven_theorems': False},
          'scope': 'Artifact byte integrity, policy and static scope review only; no Lean, C generation, benchmark or new experiment.'}
(ROOT/'closeout-recovery-audit.json').write_text(json.dumps(result, indent=2, ensure_ascii=False)+'\n', encoding='utf-8')
print(json.dumps(result, indent=2, ensure_ascii=False))
