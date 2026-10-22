"""Repair only the Fin-zero coercion left by the exact failed singleton proof."""
from pathlib import Path
import ast
import copy
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / 'f01-d7-singleton/Kernel.lean'
EXPECTED_PARENT = '4ba2a23548e5df7f3c379b4734e6653c0546b8346d6d567eb397c1245f725d43'
OUT = ROOT / 'f01-d7-singleton-proof1'
FAILURE = ROOT / 'f01-mul-log2-proof1/ci-runs/39846309529/download-cc7339e93405469cb1426319df998e25/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-d7-singleton/full-build-output.txt'
POLICY = ROOT.parent / 'research/materials/20261022/R2-W01c/FloatLib_R2-W01c/public_sources/official/gate.py'
OLD = '  simp only [Fin.foldl_succ, Fin.foldl_zero]'
NEW = '  simp only [Fin.foldl_succ, Fin.foldl_zero, Fin.val_zero]'


def require(ok, message):
    if not ok:
        raise RuntimeError(message)


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    raw = PARENT.read_bytes()
    require(digest(raw) == EXPECTED_PARENT, 'failed parent source hash differs')
    failure = FAILURE.read_bytes()
    log = failure.decode('utf-8')
    require('error: work/Submission.lean:3386:68: unsolved goals' in log and '↑0' in log,
            'expected exact singleton coercion failure receipt')
    source = raw.decode('utf-8')
    start = source.index('theorem singletonCore_eq_reference ')
    end = source.index('\ndef bmm (', start)
    proof = source[start:end]
    require(proof.count(OLD) == 1 and source.count(OLD) == 1, 'singleton proof pattern differs')
    repaired = proof.replace(OLD, NEW, 1)
    payload = (source[:start] + repaired + source[end:]).encode('utf-8')
    require(payload.decode().replace(NEW, OLD, 1).encode() == raw, 'unexpected change outside the one proof line')
    require(source[:start].encode() == payload[:len(source[:start].encode())], 'prefix changed')
    require(payload.endswith(source[end:].encode()), 'suffix/runtime dispatcher changed')
    child = payload.decode('utf-8')
    tree = ast.parse(POLICY.read_text(encoding='utf-8'))
    banned_node = next(n for n in tree.body if isinstance(n, ast.Assign)
                       and any(isinstance(t, ast.Name) and t.id == 'BANNED' for t in n.targets))
    banned = re.compile(ast.literal_eval(banned_node.value.args[0]))
    require(banned.search(child) is None, 'saved official banned-token check failed')
    imports = [line for line in child.splitlines() if re.search(r'\bimport\b', line)]
    options = [line for line in child.splitlines() if re.search(r'\bset_option\b', line)]
    require(imports == ['import ContractTensor'] and options == [], 'unexpected imports/options')
    require(len(payload) <= 256000, 'candidate exceeds byte limit')
    manifest = copy.deepcopy(json.loads(PARENT.with_name('manifest.json').read_bytes()))
    manifest.update(candidate=OUT.name, candidate_sha256=digest(payload), candidate_bytes=len(payload),
                    parent='competitions/floatlib/candidates/f01-d7-singleton/Kernel.lean',
                    parent_sha256=EXPECTED_PARENT, parent_bytes=len(raw), validation_mode='full-gate',
                    proof_status='NOT_RUN', compile_status='NOT_RUN', full_gate_status='NOT_RUN',
                    performance_status='NOT_RUN', gain='UNKNOWN')
    manifest['proof_route'] = manifest['proof_route'].rstrip('.') + '; normalize the coerced zero Fin index with Fin.val_zero.'
    manifest['proof_fix'] = {
        'only_change': 'Add Fin.val_zero to the singletonCore_eq_reference simp-only list.',
        'runtime_and_other_proofs_unchanged': True,
        'exact_one_line_reverse_check': True,
        'failed_parent_status': 'FAILED_STATEMENT', 'failed_parent_run_id': '39846309529',
        'failure_log': FAILURE.relative_to(ROOT.parents[2]).as_posix(),
        'failure_log_sha256': digest(failure),
        'remaining_goal': 'Literal Nat zero versus the coerced (0 : Fin 1) in both reference k=0 addresses.',
        'lemma_source': 'https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Fin/Lemmas.lean#L231'
    }
    manifest['local_static_validation'] = {
        'status': 'PASS_STATIC_ONLY', 'imports': imports, 'set_options': options, 'banned_matches': [],
        'policy_source': POLICY.relative_to(ROOT.parents[2]).as_posix(), 'policy_sha256': digest(POLICY.read_bytes()),
        'parent_prefix_unchanged_bytes': len(source[:start].encode()),
        'parent_suffix_unchanged_bytes': len(source[end:].encode()),
        'runtime_and_other_proofs_unchanged': True, 'exact_one_line_reverse_check': True
    }
    OUT.mkdir(exist_ok=True)
    (OUT / 'Kernel.lean').write_bytes(payload)
    (OUT / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    require(digest(PARENT.read_bytes()) == EXPECTED_PARENT, 'original failed source was altered')
    print(json.dumps(manifest, indent=2))


if __name__ == '__main__':
    main()
