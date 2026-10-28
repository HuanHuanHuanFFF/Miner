from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json
import re

here = Path(__file__).resolve().parent
repo = next(p for p in here.parents if (p / 'AGENTS.md').is_file())
round_dir = here.parents[1]
source = round_dir / 'development-outline-mul/public/Kernel.lean'
old = repo / 'competitions/floatlib/candidates/f01-r19-dev-direct-bias-public1/Kernel.lean'
base = repo / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
raw = source.read_bytes()
text = raw.decode()
assert sha256(raw).hexdigest() == '88cdf318d952d74df95ecabed5e2bbadeab76d4827af1c4e5fd88e43d9d8f054'
assert sha256(old.read_bytes()).hexdigest() == 'fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5'
assert sha256(base.read_bytes()).hexdigest() == '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
old_text = old.read_bytes().decode()
marker = '\nnamespace Submission\nopen FloatLib.Floats Competition\n@[inline] def add := R19BiasBase.add'
cold = ('\nnamespace R19BiasBase.R19DirectBias\nopen Competition\n'
        '@[noinline] def retainedMul (x y : Binary32) : Binary32 :=\n'
        '  R19BiasBase.mul x y\nend R19BiasBase.R19DirectBias\n')
expected = old_text.replace(marker, cold + marker)
expected = expected.replace('R19BiasBase.R19DirectBias.guardedMul R19BiasBase.mul x y',
    'R19BiasBase.R19DirectBias.guardedMul R19BiasBase.R19DirectBias.retainedMul x y')
expected = expected.replace('R19BiasBase.R19DirectBias.guardedMul_spec R19BiasBase.mul R19BiasBase.mul_spec x y',
    'R19BiasBase.R19DirectBias.guardedMul_spec R19BiasBase.R19DirectBias.retainedMul R19BiasBase.mul_spec x y')
assert expected == text
start = text.index('namespace BranchlessRNESeed')
public = text.index('\nnamespace Submission\n', start)
suffix = text[start:public]
# Every boundary is a complete existing namespace block. No Lean file is emitted.
blocks = []
cursor = start
for label, name in [
    ('seed', 'BranchlessRNESeed'), ('nat_bias', 'R19PostBias'),
    ('word_bias', 'R19BiasBase.R19DirectBiasWord'),
    ('roundP_shape', 'R19BiasBase.R19BiasShape'),
    ('runtime', 'R19BiasBase.R19DirectBias'),
    ('output_shape', 'R19BiasBase.R19BiasShape'),
    ('original_mul_transport', 'R19BiasBase.R19DirectBias'),
    ('cold_wrapper', 'R19BiasBase.R19DirectBias')]:
    a = text.index('namespace ' + name + '\n', cursor)
    z = text.index('end ' + name + '\n', a) + len('end ' + name + '\n')
    fragment = text[a:z]
    blocks.append({'label': label, 'namespace': name, 'start_line': text[:a].count('\n')+1,
                   'end_line': text[:z].count('\n'), 'start_offset': len(text[:a].encode()),
                   'end_offset': len(text[:z].encode()), 'bytes': len(fragment.encode()),
                   'sha256': sha256(fragment.encode()).hexdigest()})
    cursor = z

decls = list(re.finditer(r'(?m)^(?:@\[[^\n]*\]\s*)?(?:private )?(?:theorem|def|abbrev) ([A-Za-z0-9_]+)', suffix))
inventory = []
for i, hit in enumerate(decls):
    end = decls[i+1].start() if i+1 < len(decls) else len(suffix)
    piece = suffix[hit.start():end]
    inventory.append({'name': hit.group(1), 'line': text[:start+hit.start()].count('\n')+1,
                      'bytes_to_next_declaration': len(piece.encode()),
                      'omega_calls': len(re.findall(r'\bomega\b', piece)),
                      'decide_calls': len(re.findall(r'\bdecide\b', piece)),
                      'norm_num_calls': len(re.findall(r'\bnorm_num\b', piece)),
                      'unfold_or_dsimp': len(re.findall(r'\b(?:unfold|dsimp)\b', piece)),
                      'scope': 'Static textual inventory, not elaboration cost or blame'})

prefixes = [{'id':'P0', 'through':'exact unchanged B2', 'bytes':len(base.read_bytes()),
             'sha256':sha256(base.read_bytes()).hexdigest(), 'fits_256000':True}]
for i, block in enumerate(blocks, 1):
    end = block['end_offset']
    # Only the new suffix namespace prefix is rebased; B2 stays byte-identical.
    added = raw[len(text[:start].encode()):end].decode().replace('R19BiasBase.', 'Submission.')
    probe = base.read_bytes() + b'\n' + added.encode()
    prefixes.append({'id':f'P{i}', 'through':block['label'], 'source_end_line':block['end_line'],
                     'bytes':len(probe), 'sha256':sha256(probe).hexdigest(),
                     'fits_256000':len(probe)<=256000,
                     'public_endpoints':'unchanged B2; diagnostics only',
                     'new_roots_namespace':'R19BiasBase prefix mapped to Submission only in appended suffix'})

fine = []
for name, cut, close in [
    ('Q0_quotient_bias', 'theorem nat_bias', 'BranchlessRNESeed'),
    ('Q1_biased_bounds', '/-- The actual product cap prevents a second carry beyond bit47. -/', 'R19PostBias'),
    ('Q2_biased_sum_nat', 'def biasedWord', 'R19BiasBase.R19DirectBiasWord'),
    ('Q3_mantissa_bounds', 'theorem literal_shift_eq', 'R19BiasBase.R19BiasShape'),
    ('Q4_pre_roundP_normal', 'theorem roundP_normal', 'R19BiasBase.R19BiasShape'),
    ('Q5_pre_mantissaWord_eq_old', 'theorem mantissaWord_eq_old', 'R19BiasBase.R19BiasShape'),
    ('Q6_normalCore_eq_roundP', 'theorem finiteMantissa_eq', 'R19BiasBase.R19DirectBias'),
    ('Q7_finiteScale_sum', 'theorem signBit_eq_bit', 'R19BiasBase.R19DirectBias'),
    ('Q8_sign_word_eq', 'theorem normalCore_eq_core', 'R19BiasBase.R19DirectBias')]:
    stop = text.index(cut, start)
    added = (text[start:stop] + '\nend ' + close + '\n').replace('R19BiasBase.', 'Submission.')
    probe = base.read_bytes() + b'\n' + added.encode()
    fine.append({'id':name,'first_omitted_line':text[:stop].count('\n')+1,
                 'close_namespace':close.replace('R19BiasBase.','Submission.'),
                 'bytes':len(probe),'sha256':sha256(probe).hexdigest(),'fits_256000':len(probe)<=256000})

out = {'checked_utc':datetime.now(timezone.utc).isoformat(),
       'first_tool_utc':'2026-10-28T00:53:29Z', 'bound_utc':'2026-10-28T01:08:29Z',
       'state':'STATIC_PREFIX_PLAN_NO_COMPILE_NO_CANDIDATE_EMITTED',
       'source':{'path':source.relative_to(repo).as_posix(),'sha256':sha256(raw).hexdigest(),'bytes':len(raw)},
       'old_parent_sha256':sha256(old.read_bytes()).hexdigest(),
       'base_sha256':sha256(base.read_bytes()).hexdigest(),
       'blocks':blocks, 'prefix_plan':prefixes, 'finer_boundaries':fine, 'declarations':inventory,
       'no_new_quotient_or_math_in_88cdf_delta':True,
       'new_delta':'one noinline retainedMul definition plus two final wrapper references; fa652 already contained every arithmetic proof',
       'warning':'These are planned diagnostic prefixes, not typed or replayed sources and not public MUL proofs; original unmodified reproducer still required.'}
(here/'prefix-plan.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'prefix_sizes':[(x['id'],x['bytes'],x['fits_256000']) for x in prefixes],
                  'finer_boundaries':fine,'exact_209_byte_delta_reproduced':expected==text},ensure_ascii=False,indent=2))
