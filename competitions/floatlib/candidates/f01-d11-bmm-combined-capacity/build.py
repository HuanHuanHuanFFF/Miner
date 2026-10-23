"""Root-authorized capacity base from frozen combined-classifier constructor.

Default dry run; --write creates only this new directory's source/receipts once.
No changes to the donor builder, old sources, Git, CI, options or whitespace.
"""
from argparse import ArgumentParser
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import importlib.util
import json
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
FROZEN_BUILDER = HERE.parent / 'f01-d11-bmm-combined-classifier/build.py'
BUILDER_SHA = 'a13842131e051be7e84796a2fafe8978acb6c38f5aff1b84cb2d677f6f9476de'
PARENT = HERE.parent / 'f01-d11-bmm-combined-classifier/Kernel.lean'
PARENT_SHA = '6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d'
ORIGIN = HERE.parent / 'f01-d11-bmm-combined-direct/Kernel.lean'
ORIGIN_SHA = '0655b26612f7359c100b2c7e091e3d2f4c53fcde5e8286d25f3c41cbdc75f06e'
EXPECTED_SHA = 'f8dca27517ed79927ab928af1b96ac25facffdff8b29efcbeccc48312fda9d03'


def sha(raw):
    return sha256(raw).hexdigest()


def construct():
    assert sha(FROZEN_BUILDER.read_bytes()) == BUILDER_SHA
    # Import definitions without running main and without writing cache files
    # into a frozen candidate. All source operations remain in memory.
    sys.dont_write_bytecode = True
    spec = importlib.util.spec_from_file_location('frozen_6c2d_constructor', FROZEN_BUILDER)
    donor = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(donor)
    source, full_ledger, receipt = donor.construct('classifier+fallback')
    classifier, _, _ = donor.construct('classifier')
    parent, origin = PARENT.read_bytes(), ORIGIN.read_bytes()
    assert sha(parent) == PARENT_SHA and classifier == parent
    assert sha(origin) == ORIGIN_SHA
    assert sha(source) == EXPECTED_SHA and len(source) == 239141
    assert len(full_ledger) == 6
    fallback_ledger = full_ledger[3:]
    assert donor.inverse(source, full_ledger) == origin
    assert donor.inverse(source, fallback_ledger) == parent
    # Preserve the entire final namespace: outer zero guard, its miss alias and
    # final specification proof. Wide must later modify only that miss path.
    outer_at = parent.rindex(b'namespace Submission\n')
    outer = parent[outer_at:]
    assert source.endswith(outer) and origin.endswith(outer)
    assert b'if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then\n' in outer
    assert b'  else bmmBeforeUnderflowZero batch m n p A B\n' in outer
    outer_receipt = {'sha256': sha(outer), 'bytes': len(outer),
        'offset_in_6c2d': outer_at, 'offset_in_new_source': len(source) - len(outer),
        'exact_bytes_unchanged': True, 'text': outer.decode(),
        'required_wide_integration': 'Keep this outer guard first; install wide only inside bmmBeforeUnderflowZero / equivalent underflow miss path.'}
    receipt.update(candidate=HERE.name, candidate_file='Kernel.lean', parent='f01-d11-bmm-combined-classifier',
        parent_sha256=PARENT_SHA, origin_sha256=ORIGIN_SHA, candidate_sha256=EXPECTED_SHA,
        candidate_bytes=239141, delta_from_parent_bytes=-15513, headroom_bytes=16859,
        state='READY_FOR_STATEMENT', proof_status='NOT_RUN_NEW_COMBINATION',
        wrapper_sha256=sha(Path(__file__).read_bytes()), frozen_constructor_sha256=BUILDER_SHA,
        whitespace_changes='NONE', outer_underflow=outer_receipt)
    receipt['checks']['inverse_to_6c2d'] = 'PASS'
    receipt['checks']['inverse_to_0655'] = 'PASS'
    receipt['checks']['outer_underflow_guard_and_final_spec_exact_bytes'] = 'PASS'
    return source, fallback_ledger, full_ledger, receipt


def main():
    ap = ArgumentParser()
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument('--write', action='store_true')
    mode.add_argument('--verify', action='store_true')
    args = ap.parse_args()
    source, fallback_ledger, full_ledger, receipt = construct()
    if args.verify:
        assert (HERE / 'Kernel.lean').read_bytes() == source
    elif args.write:
        outputs = ['Kernel.lean', 'manifest.json', 'exact-inverse.json', 'origin-inverse.json', 'static-checks.json']
        assert not any((HERE / n).exists() for n in outputs), 'Refuse overwrite'
        manifest = dict(receipt, created_at_utc=datetime.now(timezone.utc).isoformat(),
            mechanism='Exact frozen construct(classifier+fallback): retain0655 Cross/Underflow/DirectContinuous/fused, add6457 classifiers, replace shared add NaN-result fallback with original ExecFloat.add and remove unused TunedAdd. No wide4 loop or new width.',
            component_fallback_evidence='Root reports isolated exact7317 fullPASS in919; whole1.003288,BMM1.006013,add0.996474,sum1.038845 vs a066, with unchanged-path variability. This is a capacity option, not a speed claim or validation of this new combination.',
            validation_mode='New exact statement and original full gate required',
            performance='UNKNOWN_NEW_COMBINATION_NOT_ADDITIVE', formal_submission='NOT_SUBMITTED', ci_owner='root',
            attribution='All donor notices preserved by frozen constructor; no ordinary blank lines removed.')
        (HERE / 'Kernel.lean').write_bytes(source)
        for name, payload in [('manifest.json', manifest), ('exact-inverse.json', fallback_ledger),
                              ('origin-inverse.json', full_ledger), ('static-checks.json', receipt)]:
            (HERE / name).write_bytes((json.dumps(payload, ensure_ascii=False, indent=2) + '\n').encode())
    print(json.dumps({k: receipt[k] for k in ['candidate', 'candidate_sha256', 'candidate_bytes',
        'parent_sha256', 'origin_sha256', 'headroom_bytes', 'wrapper_sha256', 'frozen_constructor_sha256']}, indent=2))
    print(json.dumps({'outer_underflow_sha256': receipt['outer_underflow']['sha256'],
                     'outer_underflow_bytes': receipt['outer_underflow']['bytes'],
                     'outer_underflow_exact_bytes_unchanged': True,
                     'checks': 'PASS', 'new_Lean_fullgate': 'NOT_RUN'}, indent=2))


if __name__ == '__main__':
    main()
