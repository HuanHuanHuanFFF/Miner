"""Freeze an append-only statement probe. No Lean, CI, Git, or network execution."""
from pathlib import Path
from types import SimpleNamespace
import __future__
import argparse
import ast
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
CANDIDATES = HERE.parent
PARENT = CANDIDATES / 'f01-d7-direct-nonfinite/Kernel.lean'
BLOCK = HERE / 'seed-normalize-block.lean'
OUT = CANDIDATES / 'f01-d7-seed-normalize-probe'
R = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7'
GATE = R / 'upstream/gate-4b7e838.py'
CORE = R / 'web/R7-W10b/original-extracted/R7-W10b/Core.lean'
ORACLE = R / 'nonfinite-oracle.py'
EXPECTED_PARENT = '97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26'
EXPECTED_BLOCK = 'c44c4afbbe117e97b857ac3541638f3cbee370ba86f837fc76be16c41d08ed26'
EXPECTED_CORE = '270c698a2dd2b96d21766d35339e090ca1455f71404145b3323cd1862301b67f'
EXPECTED_GATE = '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
EXPECTED_ORACLE = '3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'


def require(ok, message):
    if not ok:
        raise RuntimeError(message)


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def label(path):
    return path.resolve().relative_to(ROOT).as_posix()


def runtime_definition(text):
    start = text.index('@[inline] def normalizeProductSeedRaw ')
    return text[start:text.index('\n\n', start)]


def current_policy(kernel, gate=GATE):
    """Execute unchanged policy/options AST; no other official stage is loaded."""
    raw = Path(gate).read_bytes()
    require(sha(raw) == EXPECTED_GATE, 'fixed upstream gate bytes differ')
    text = raw.decode('utf-8')
    tree = ast.parse(text)
    constants = {'OPTIONS', 'ATTRIBUTES', 'BANNED'}
    selected = []
    slots = None
    maximum = None
    for node in tree.body:
        if isinstance(node, ast.Assign):
            names = {t.id for t in node.targets if isinstance(t, ast.Name)}
            if names & constants:
                selected.append(node)
            if 'SLOTS' in names:
                slots = node.value
            if '_MAX_BYTES' in names:
                maximum = ast.literal_eval(node.value)
        elif isinstance(node, ast.FunctionDef) and node.name in ('policy', 'options'):
            selected.append(node)
    require(slots is not None and isinstance(slots, ast.Dict), 'fixed SLOTS shape differs')
    full = next(v for k, v in zip(slots.keys, slots.values) if ast.literal_eval(k) == 'full')
    contract = next(ast.literal_eval(k.value) for k in full.keywords if k.arg == 'contract')
    require(contract == 'ContractTensor' and maximum == 256000, 'fixed full contract/limit differs')
    require(len(selected) == 5, 'policy/options AST selection differs')
    env = {'re': re, 'Path': Path,
           'SLOTS': {'full': SimpleNamespace(contract=contract)}}
    code = compile(ast.Module(body=selected, type_ignores=[]), str(gate), 'exec',
                   flags=__future__.annotations.compiler_flag)
    exec(code, env)
    payload = kernel.read_bytes()
    payload.decode('utf-8')
    require(kernel.name == 'Kernel.lean' and len(payload) <= maximum, 'name/UTF8/byte intake check')
    reason = env['policy'](kernel, SimpleNamespace(slot='full'))
    return {'status': 'PASS_STATIC_ONLY' if reason is None else 'FAIL_STATIC_ONLY',
            'reason': reason, 'source': label(Path(gate)), 'gate_sha256': sha(raw),
            'official_commit': '4b7e83841cc0c32c6529f533923c73d33b5ecf97',
            'scope': 'Unmodified policy/options bodies; exact full-slot contract extracted from upstream AST. No build/kernel/axiom/score stage.',
            'function_source_sha256': {
                n.name: sha(ast.get_source_segment(text, n).encode())
                for n in selected if isinstance(n, ast.FunctionDef)}}


def finite_selftest():
    """Sixteen directed source-model cases only; no benchmark inputs or main."""
    raw = ORACLE.read_bytes()
    require(sha(raw) == EXPECTED_ORACLE, 'frozen integer oracle differs')
    wanted = {'exp', 'frac', 'nan', 'snan', 'inf', 'zero', 'choose',
              'unpack', 'rounded', 'add', 'mul'}
    nodes = [n for n in ast.parse(raw.decode()).body
             if isinstance(n, ast.FunctionDef) and n.name in wanted]
    require({n.name for n in nodes} == wanted, 'oracle definitions differ')
    env = {}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(ORACLE), 'exec'), env)
    normalize = lambda w: 0 if w == 0x80000000 else w
    products = [
        ('negative_zero', 0x80000000, 0x3f800000, 0x80000000, 0),
        ('positive_zero_negative_one', 0, 0xbf800000, 0x80000000, 0),
        ('negative_underflow', 0x80000001, 0x3f000000, 0x80000000, 0),
        ('positive_underflow', 1, 0x3f000000, 0, 0),
        ('minimum_subnormal', 1, 0x3f800000, 1, 1),
        ('zero_inf_invalid', 0, 0x7f800000, 0x7fc00000, 0x7fc00000),
        ('negative_zero_negative_inf', 0x80000000, 0xff800000, 0x7fc00000, 0x7fc00000),
        ('negative_infinity', 0xbf800000, 0x7f800000, 0xff800000, 0xff800000),
        ('negative_quiet_payload', 0xffc01234, 0x3f800000, 0xffc01234, 0xffc01234),
        ('quiet_then_signaling', 0x7fc00111, 0xff800022, 0xffc00022, 0xffc00022),
        ('both_signaling', 0x7f800011, 0xff800022, 0x7fc00011, 0x7fc00011),
        ('both_quiet', 0xffc00111, 0x7fc00222, 0xffc00111, 0xffc00111),
    ]
    rows = []
    for name, x, y, expected_product, expected_seed in products:
        product = env['mul'](x, y)
        result = env['add'](0, product)
        require(product == expected_product and result == normalize(product) == expected_seed,
                'directed product model differs: ' + name)
        require(not env['snan'](product), 'directed product remained signaling')
        rows.append({'kind': 'product', 'name': name, 'x': hex(x), 'y': hex(y),
                     'product': hex(product), 'seed_result': hex(result)})
    for q in (0x80000000, 0, 0xffc01234, 0xff800011):
        normal, added, signaling = normalize(q), env['add'](0, q), env['snan'](q)
        require((normal == added) == (not signaling), 'directed general premise boundary')
        rows.append({'kind': 'general_q', 'q': hex(q), 'normalized': hex(normal),
                     'actual_add_model': hex(added), 'is_snan': signaling,
                     'status': 'COUNTEREXAMPLE_WITHOUT_PREMISE' if signaling else 'MATCH_WITH_PREMISE'})
    require(sha(ORACLE.read_bytes()) == EXPECTED_ORACLE, 'oracle changed during selftest')
    return {'status': 'PASS_FINITE_INTEGER_MODEL_ONLY', 'case_count': len(rows),
            'oracle_path': label(ORACLE), 'oracle_sha256': EXPECTED_ORACLE,
            'oracle_unchanged': True, 'cases': rows, 'lean': 'NOT_RUN',
            'hardware': 'NOT_RUN', 'performance': 'UNKNOWN'}


def build(check_only=False, gate=GATE):
    parent = PARENT.read_bytes()
    block = BLOCK.read_bytes()
    core = CORE.read_bytes()
    require(sha(parent) == EXPECTED_PARENT, 'parent source hash differs')
    require(sha(block) == EXPECTED_BLOCK, 'new proof block differs from frozen builder')
    require(sha(core) == EXPECTED_CORE, 'W10b runtime original differs')
    text = block.decode('utf-8')
    require(runtime_definition(text) == runtime_definition(core.decode('utf-8')),
            'runtime differs from exact W10b Core definition')
    require(re.findall(r'^namespace\s+(\S+)', text, re.M) == ['D7SeedNormalize']
            and re.findall(r'^end\s+(\S+)', text, re.M) == ['D7SeedNormalize'],
            'new namespace structure differs')
    require(re.findall(r'^(?:@\[[^\]]*\]\s*)?def\s+(\w+)', text, re.M)
            == ['normalizeProductSeedRaw'], 'unexpected new runtime definition')
    require('@ite Float32' in text and '@ite Float.Model.UnpackedFloat' in text,
            'explicit proof decision boundary missing')
    require('R7W05' not in text and 'R7W10.' not in text,
            'large historical proof dependency leaked into block')
    payload = parent + b'\n\n' + block
    require(payload[:len(parent)] == parent and len(payload) <= 256000,
            'original source prefix changed or candidate too large')
    require(re.findall(rb'^import .*$', payload, re.M) == [b'import ContractTensor'],
            'extra source imports')
    kernel = OUT / 'Kernel.lean'
    if check_only:
        require(kernel.is_file() and kernel.read_bytes() == payload, 'existing probe bytes differ')
    else:
        OUT.mkdir(exist_ok=True)
        require(not kernel.exists() or kernel.read_bytes() == payload,
                'refusing to overwrite a different probe source')
        kernel.write_bytes(payload)
    policy = current_policy(kernel, gate)
    require(policy['reason'] is None, 'fixed official static policy: ' + str(policy['reason']))
    manifest = {
        'candidate': OUT.name, 'candidate_file': 'Kernel.lean',
        'candidate_sha256': sha(payload), 'candidate_bytes': len(payload),
        'parent': PARENT.parent.name, 'parent_sha256': EXPECTED_PARENT,
        'parent_bytes': len(parent), 'proof_block': label(BLOCK),
        'proof_block_sha256': EXPECTED_BLOCK, 'proof_block_bytes': len(block),
        'source_builder': label(Path(__file__)), 'builder_sha256': sha(Path(__file__).read_bytes()),
        'validation_mode': 'statement-only', 'proof_status': 'NOT_RUN_NEW_INTEGRATION',
        'compile_status': 'NOT_RUN', 'kernel_replay': 'NOT_RUN', 'axiom_audit': 'NOT_RUN',
        'full_gate': 'NOT_RUN', 'performance': 'NOT_RUN', 'gain': 'UNKNOWN',
        'formal_submission': 'NOT_SUBMITTED', 'probe_only': True,
        'original_source_prefix_byte_identical': True,
        'four_export_runtime_definitions_unchanged': True,
        'new_runtime_definition_count': 1, 'new_helper_used_by_exports': False,
        'mechanism': 'Append minimal actual +0-add/product proof and an unused raw-word normalizer. No exported add/mul/sum/bmm behavior is changed.',
        'normalizer_source': {'publication': 'LOCAL_ONLY', 'path': label(CORE),
                              'sha256': EXPECTED_CORE, 'runtime_definition_exact': True},
        'source_transformations': [
            'Copy only two W05 classifier lemmas; use explicit BitVec 8/23 types.',
            'Replace scoped Classical instance command with explicit proof-only ite decisions.',
            'Use retained NotNaNProbe.roundtrip and R7Native.ofFloat32Add; no complete W05.',
            'Use existing R7W01 quiet-NaN and all-product non-signaling proofs.',
            'Preserve exact W10b UInt32-select/ofRaw runtime definition.',
        ],
        'fixed_context': {'Lean': 'v4.34.0',
                          'FloatLib': '0d91825727839f597fd06b22fdd038ea21480f0c'},
        'static_policy': policy,
        'acceptance_boundary': 'Static source checks only. New type elaboration, proof replay, transitive axioms, checksums, code generation and current full gate remain NOT_RUN.',
    }
    if check_only:
        saved = json.loads((OUT / 'manifest.json').read_bytes())
        require(saved == manifest, 'saved manifest differs from deterministic builder')
    else:
        (OUT / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    require(sha(PARENT.read_bytes()) == EXPECTED_PARENT and sha(CORE.read_bytes()) == EXPECTED_CORE,
            'an original changed during build')
    return manifest


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true', help='Read-only verification of the frozen probe')
    parser.add_argument('--selftest', action='store_true', help='Sixteen local directed model cases; no source writes')
    parser.add_argument('--gate', type=Path, default=GATE)
    args = parser.parse_args()
    if args.selftest:
        print(json.dumps(finite_selftest(), indent=2))
    else:
        result = build(args.check, args.gate)
        print(json.dumps({k: result[k] for k in
                          ('candidate', 'candidate_sha256', 'candidate_bytes',
                           'validation_mode', 'proof_status', 'static_policy')}, indent=2))
