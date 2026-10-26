"""Check evidence parsing rejects missing, duplicated and nonstandard axioms."""
from pathlib import Path
import hashlib
import importlib.util
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
spec = importlib.util.spec_from_file_location('r16_audit_test', HERE/'development-helper-audit.py')
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)
names = ['Submission.testA', 'Submission.testB']
good = "'Submission.testA' depends on axioms: [propext,\n Classical.choice, Quot.sound]\n'Submission.testB' does not depend on any axioms\n"
allowed = {'propext', 'Classical.choice', 'Quot.sound'}
assert m.parse_reports(good, names, allowed)['Submission.testB'] == []
for output in (good.replace('testB', 'other'), good+good,
               good.replace('Quot.sound', 'False.elim_axiom'),
               good.replace('testA', 'testA_extra')):
    try:
        m.parse_reports(output, names, allowed)
    except ValueError:
        continue
    raise AssertionError('Invalid helper evidence accepted')
manifest = ROOT/'competitions/floatlib/candidates/f01-r17-dev-u32-roundtrip-repair1/manifest.json'
obj = json.loads(manifest.read_bytes())
assert obj['candidate_sha256'] == '01cff324ee8bd142ec9753a2ca72c9ecb7ca24cd8c1bcac9a0925e77fd5e4905'
obj['helper_audit_module_sha256'] = hashlib.sha256((HERE/'development-helper-audit.py').read_bytes()).hexdigest()
manifest.write_bytes((json.dumps(obj, ensure_ascii=False, indent=2)+'\n').encode())
print(json.dumps(dict(parser_checks=5, state='PASS', helper_module_sha256=obj['helper_audit_module_sha256'])))
