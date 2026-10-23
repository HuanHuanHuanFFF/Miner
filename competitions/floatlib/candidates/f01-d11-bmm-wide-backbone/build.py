"""Isolated wide backbone: underflow+direct+fused, classifier, official fallback.

Only in-memory frozen constructors are called. No intermediate Kernel, Cross,
source overwrite, whitespace cleanup, Lean, Git or CI. Default dry run.
"""
from argparse import ArgumentParser
from collections import Counter
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import importlib.util
import json
import re
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
R11 = HERE.parent / 'f01-d7-research/round7h-20261023T193125Z'
COMPOSER = R11 / 'compose-structural.py'
COMPOSER_SHA = '299a5ce768230a2e658510f2669b1c949247b40d8ac59aa418eb96830f2eb6d5'
CLASSIFIER = HERE.parent / 'f01-d11-bmm-combined-classifier/build.py'
CLASSIFIER_SHA = 'a13842131e051be7e84796a2fafe8978acb6c38f5aff1b84cb2d677f6f9476de'
RECIPE_SHA = '2fd068b1893ac6d24feb766ec86673dc025a056650f0cdc5bdaf6b64073ef605'
F8DC = HERE.parent / 'f01-d11-bmm-combined-capacity/Kernel.lean'
F8DC_SHA = 'f8dca27517ed79927ab928af1b96ac25facffdff8b29efcbeccc48312fda9d03'


def sha(raw):
    return sha256(raw).hexdigest()


def load(path, expected, name):
    assert sha(path.read_bytes()) == expected
    sys.dont_write_bytecode = True
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def chunk(raw, inventory, name):
    lines = raw.decode().splitlines(keepends=True)
    at = inventory[name][0] - 1
    end = at + 1
    while end < len(lines) and not re.match(r'^(?:@\[[^]]+\]\s*)?(?:(?:private|protected|noncomputable)\s+)*(?:def|theorem|abbrev|namespace|end)\b', lines[end]):
        end += 1
    return ''.join(lines[at:end]).encode()


def construct():
    compose = load(COMPOSER, COMPOSER_SHA, 'frozen_structural_composer')
    donor = load(CLASSIFIER, CLASSIFIER_SHA, 'frozen_classifier_donor')
    sources, records = compose.snapshots()
    parts = ('underflow', 'direct')
    parent, composition, edits = compose.compose(sources, records, parts)
    assert sha(parent) == RECIPE_SHA and len(parent) == 239031
    assert composition['blank_line_only_trim']['saved_bytes'] == 0
    # This constructor validates/reproduces exact6457 and7317 donor sources;
    # its six before/after spans are then reused on the no-Cross recipe.
    _, donor_ops, _ = donor.construct('classifier+fallback')
    result, ledger = donor.apply(parent, donor_ops)
    assert len(ledger) == 6 and len(result) == 223584
    assert donor.inverse(result, ledger) == parent
    assert edits.inverse(donor.inverse(result, ledger)) == sources['base']
    inv, comments, policy = compose.helpers(sources)
    checks = compose.static_verify(result, parts, inv, policy)
    old_decl, new_decl = [inv['declarations'](raw.decode()) for raw in (parent, result)]
    removed = {k for k in old_decl if k.startswith('Submission.TunedAdd.')}
    assert set(old_decl) - set(new_decl) == removed and len(removed) == 40
    assert not (set(new_decl) - set(old_decl))
    assert not any('R11CrossRows' in name for name in new_decl)
    spec_checks = {}
    for name in ['Submission.add_spec', 'Submission.mul_spec', 'Submission.sum_spec', 'Submission.bmm_spec']:
        old, new = chunk(parent, old_decl, name), chunk(result, new_decl, name)
        assert old.split(b':=', 1)[0] == new.split(b':=', 1)[0]
        if name != 'Submission.add_spec':
            assert old == new
        spec_checks[name] = {'type_unchanged': True, 'full_chunk_unchanged': old == new,
                             'parent_sha256': sha(old), 'candidate_sha256': sha(new)}
    old_notices = Counter(comments['licence_hashes'](parent))
    new_notices = Counter(comments['licence_hashes'](result))
    assert not (old_notices - new_notices)
    # Removing the closed namespace makes the retained fastlog introduction
    # adjacent to the retained FastMul source paragraph. The pinned scanner now
    # additionally protects this unchanged introduction; no old notice is lost.
    additional_notices = dict(new_notices - old_notices)
    assert additional_notices == {'01045ce7808c049cda69516cd15451bc862f2e03e35095d3ecc5d302a57f9ae3': 1}
    outer = parent[parent.rindex(b'namespace Submission\n'):]
    previous = F8DC.read_bytes()
    assert sha(previous) == F8DC_SHA
    assert result.endswith(outer) and previous.endswith(outer)
    assert len(outer) == 1039 and sha(outer) == 'b135a8eef0606c7356dc12d5956115d3832aa5cddb5dc5e71e5030380c76062e'
    assert b'else bmmBeforeUnderflowZero batch m n p A B' in outer
    checks.update(donor_six_exact_edits='PASS', inverse_to_recipe_2fd='PASS', inverse_to_compact_f2fa='PASS',
        removed_only_forty_TunedAdd_declarations='PASS', Cross_declarations_absent='PASS',
        original_author_notice_hash_multiset_preserved='PASS',
        additional_notice_classification_from_retained_adjacent_comments=additional_notices,
        public_spec_checks=spec_checks,
        no_intermediate_Kernel_written=True, whitespace_changes='NONE')
    receipt = {'candidate': HERE.name, 'candidate_sha256': sha(result), 'candidate_bytes': len(result),
        'headroom_bytes': 256000-len(result), 'wrapper_sha256': sha(Path(__file__).read_bytes()),
        'frozen_composer_sha256': COMPOSER_SHA, 'frozen_donor_builder_sha256': CLASSIFIER_SHA,
        'recipe': 'underflow+direct then exact6457 and7317', 'recipe_source_sha256': RECIPE_SHA,
        'recipe_source_bytes': len(parent), 'parent': 'f01-d11-bmm-fused-output-compact',
        'parent_sha256': sha(sources['base']), 'state': 'READY_FOR_STATEMENT',
        'checks': checks, 'outer_underflow': {'bytes': len(outer), 'sha256': sha(outer),
            'text': outer.decode(), 'byte_identical_to_2fd_and_f8dc': True,
            'wide_must_only_replace_miss': 'Insert wide inside bmmBeforeUnderflowZero; preserve the outer guard and final public specification.'},
        'proof_status': 'NOT_RUN_NEW_COMBINATION', 'leanchecker': 'NOT_RUN', 'axiom_audit': 'NOT_RUN',
        'checksum': 'NOT_RUN', 'full_gate': 'NOT_RUN', 'generated_c_assembly': 'NOT_RUN',
        'performance': 'UNKNOWN_CAPACITY_AND_ISOLATION_ONLY', 'formal_submission': 'NOT_SUBMITTED'}
    return result, ledger, composition, receipt


def main():
    ap = ArgumentParser()
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument('--write', action='store_true')
    mode.add_argument('--verify', action='store_true')
    args = ap.parse_args()
    result, ledger, composition, receipt = construct()
    if args.verify:
        assert (HERE / 'Kernel.lean').read_bytes() == result
    elif args.write:
        names = ['Kernel.lean', 'manifest.json', 'exact-inverse.json', 'composition-evidence.json', 'static-checks.json']
        assert not any((HERE / n).exists() for n in names), 'Refuse overwrite'
        manifest = dict(receipt, candidate_file='Kernel.lean', created_at_utc=datetime.now(timezone.utc).isoformat(),
            mechanism='Independent no-Cross wide backbone retaining UnderflowZero outer guard, DirectContinuous short-n, fused RowStream,6457 endpoint classifiers and7317 official shared-add fallback. No wide loop added and no claim that removing Cross improves speed.',
            attribution='Frozen composer notices and exact donor licence/source paragraphs preserved; no whitespace or ordinary source cleanup.',
            validation_mode='New exact statement and original full gate required', ci_owner='root')
        (HERE / 'Kernel.lean').write_bytes(result)
        for name, payload in [('manifest.json', manifest), ('exact-inverse.json', ledger),
                              ('composition-evidence.json', composition), ('static-checks.json', receipt)]:
            (HERE / name).write_bytes((json.dumps(payload, ensure_ascii=False, indent=2)+'\n').encode())
    print(json.dumps({k:receipt[k] for k in ['candidate','candidate_sha256','candidate_bytes','headroom_bytes',
        'wrapper_sha256','frozen_composer_sha256','recipe_source_sha256','parent_sha256']},indent=2))
    print(json.dumps({'outer_underflow_sha256':receipt['outer_underflow']['sha256'],
        'outer_underflow_bytes':receipt['outer_underflow']['bytes'],'static_checks':'PASS',
        'Cross_declarations':0,'removed_TunedAdd_declarations':40,'new_Lean_fullgate':'NOT_RUN'},indent=2))


if __name__ == '__main__':
    main()
