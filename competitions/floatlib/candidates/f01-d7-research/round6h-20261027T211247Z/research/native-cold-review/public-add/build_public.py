from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from types import SimpleNamespace
import ast
import json
import re

here = Path(__file__).resolve().parent
repo = next(p for p in here.parents if (p / 'AGENTS.md').is_file())
round_dir = here.parents[2]
base_path = repo / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
runtime_path = round_dir / 'development-nativecold/NativeColdAdd.lean.inc'
helper_path = here.parent / 'FastOKNativeBridges.lean.inc'
base = base_path.read_bytes()
runtime = runtime_path.read_bytes()
helpers = helper_path.read_bytes()
assert sha256(base).hexdigest() == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha256(runtime).hexdigest() == '21cd91284ee5bc31fed0e7aaa3b1cf35e6a705cbe2e680d8095baf2388551f50'
assert sha256(helpers).hexdigest() == '5607ee4abd4c0610fe5448797968a9c11bb0b5d89726b7ac9155438babfdecc4'
first, sep, body = base.partition(b'\n')
assert first.strip() == b'import ContractTensor' and sep
assert not re.search(rb'(?m)^import\s', body)
assert b'_root_' not in body and b'namespace FloatLib' not in body
entry = (here / 'EntryProof.lean.inc').read_bytes()
aliases = (here / 'PublicAliases.lean.inc').read_bytes()
# Whole original body is preserved verbatim under one outer namespace.
# The original runtime21cd and helper5607 bytes are likewise not rewritten.
kernel = first + sep + b'\nnamespace R22NativeAddBase\n' + body + b'\n' + runtime + b'\n' + helpers + b'\n' + entry + b'\nend R22NativeAddBase\n\n' + aliases
assert len(kernel) <= 256000
assert kernel.count(body) == 1 and kernel.count(runtime) == 1 and kernel.count(helpers) == 1
assert first + sep + body == base
(here / 'Kernel.lean').write_bytes(kernel)

prefix = 'R22NativeAddBase.Submission.'
roots = ['Submission.add_spec', 'Submission.mul_spec', 'Submission.sum_spec', 'Submission.bmm_spec']
roots += [prefix + 'R22NativeColdReview.' + x for x in
          ['fastOK_notNaN', 'native_add_spec_of_fastOK', 'native_mul_spec_of_fastOK']]
roots += [prefix + 'R22NativeColdAdd.' + x for x in
          ['coldAdd', 'diagnosticEntry', 'diagnosticEntry_spec', 'diagnosticEntry_eq_B2_add']]
(here / 'HelperAudit.lean.inc').write_text('\n'.join('#print axioms '+r for r in roots)+'\n', encoding='utf-8')

# Read-only use of the exact pinned intake/policy functions, not the gate/build.
gate_path = repo / 'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw'
gate = gate_path.read_bytes()
assert sha256(gate).hexdigest() == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree = ast.parse(gate)
selected = [n for n in tree.body if (isinstance(n, ast.FunctionDef) and n.name in ('intake','options','policy'))
            or (isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in ('OPTIONS','ATTRIBUTES','BANNED') for t in n.targets))]
env = {'Path':Path, 're':re, '_MAX_BYTES':256000, 'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
program = ast.Module(body=[ast.ImportFrom(module='__future__',names=[ast.alias(name='annotations')],level=0),*selected],type_ignores=[])
exec(compile(ast.fix_missing_locations(program),str(gate_path)+':read-only-extract','exec'),env)
policy = {name:env[name](here/'Kernel.lean',SimpleNamespace(slot='full')) for name in ('intake','policy')}
assert all(value is None for value in policy.values()), policy

def file_record(p):
    b = p.read_bytes()
    return {'path':p.relative_to(repo).as_posix(), 'sha256':sha256(b).hexdigest(), 'bytes':len(b)}

out = {
    'candidate':'r22-research-native-cold-public-add1',
    'created_utc':datetime.now(timezone.utc).isoformat(),
    'first_tool_utc':'2026-10-28T01:11:53Z', 'bound_utc':'2026-10-28T01:31:53Z',
    'common_deadline_utc':'2026-10-28T03:12:47Z',
    'candidate_file':'Kernel.lean', 'candidate_sha256':sha256(kernel).hexdigest(),
    'candidate_bytes':len(kernel), 'headroom_bytes':256000-len(kernel),
    'base':file_record(base_path), 'runtime':file_record(runtime_path), 'helpers':file_record(helper_path),
    'carrier':'Original import at file head; entire unchanged B2 body, exact21cd runtime and exact5607 helpers inside R22NativeAddBase; public four aliases outside.',
    'original_base_body_byte_identical':True, 'runtime_component_byte_identical':True,
    'public_add':'R22NativeAddBase.Submission.R22NativeColdAdd.diagnosticEntry',
    'other_public_operations':'MUL/SUM/BMM alias original retained B2 bodies under carrier; their internal references do not route through new public ADD',
    'explicit_helper_audit':roots, 'root_count':len(roots),
    'files':{name:file_record(here/name) for name in ['Kernel.lean','EntryProof.lean.inc','PublicAliases.lean.inc','HelperAudit.lean.inc']},
    'policy_preflight':{'gate_sha256':sha256(gate).hexdigest(),'results':policy,'scope':'Exact saved function AST only; not Lean/gate/replay'},
    'proof_status':'NOT_RUN_COMPLETE_PROOF_ATTEMPT', 'CI':'NOT_RUN',
    'performance':'NOT_RUN_FOR_THIS_PUBLIC_SOURCE', 'formal_submission':'NOT_SUBMITTED',
    'new_axioms':'NONE_INTENDED; actual helper audit/replay NOT_RUN',
    'next':'D original four obligations, explicit helper replay/allowed axioms, actual originalMainFull caller and complete cost. No diagnostic speed inheritance.'
}
(here / 'manifest.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:out[k] for k in ['candidate_sha256','candidate_bytes','headroom_bytes','root_count','proof_status','policy_preflight']},ensure_ascii=False))
