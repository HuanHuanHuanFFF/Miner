"""Conditional proof replacement only; activated for localization only after401dPASS."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/exact-arithmetic/bias-frontier/shared-block-isolation/NatPostClosure.lean'
sha = lambda x: hashlib.sha256(x).hexdigest()


def main():
    old = OLD.read_bytes()
    assert sha(old) == 'cbdb2fb8e83908a6c6179c286b1648891c0186727db53b6d635a5af2689b8f31'
    marker = b'/-- The actual product cap prevents a second carry beyond bit47. -/'
    prefix = old[:old.index(marker)]
    fragment = (HERE / 'math-repair/LightNormalized.lean.inc').read_bytes()
    old_header = old[old.index(b'theorem normalized_quotient'):].split(b':= by', 1)[0]
    new_header = fragment[fragment.index(b'theorem normalized_quotient'):].split(b':= by', 1)[0]
    assert old_header == new_header
    assert b'omega' not in fragment
    assert b'namespace ' not in fragment and b'end R19PostBias' not in fragment
    source = prefix + fragment + b'\nend R19PostBias\n'
    target = HERE / 'math-repair/NatPostLightNormalized.lean'
    target.write_bytes(source)
    checks = 0
    A, D, M, U = 2**47, 2**23, 2**24, 281474951544833
    vals = {0, 1, 2**46, A - 2, A - 1, A, A + 1, A + D - 2, A + D - 1, A + D, U - 1, U}
    for b in sorted(vals):
        if b < A + D:
            q, h = b >> 23, b >> 47
            assert h == (1 if q == M else 0)
            assert b >> (23 + h) == (D if q == M else q)
            checks += 1
        if A <= b <= U:
            q, h = b >> 24, b >> 47
            assert h == 1 + (1 if q == M else 0)
            assert b >> (23 + h) == (D if q == M else q)
            checks += 1
    manifest = {'state': 'CONDITIONAL_NOT_RUN', 'file': target.name, 'sha256': sha(source), 'bytes': len(source),
                'activation': 'Only afterNatPostBeforeNormalized401d prefix PASS. If401dOOM continueearlierprefix; do notattributeOOM tolastdeclaration.',
                'base_sha256': sha(old), 'unchanged_prefix_bytes': len(prefix), 'unchanged_prefix_sha256': sha(prefix),
                'original_normalized_statement_byte_identical': True, 'original_shift_biased_definitions_unchanged': True,
                'new_body_omega_count': 0, 'new_private_lemmas': ['low_bias_upper', 'below_boundary', 'at_boundary', 'upper_half', 'normalized_low', 'normalized_high'],
                'explicit_new_roots': ['BranchlessRNESeed.nat_bias', 'BranchlessRNESeed.nat_grouped_bias',
                                       'R19PostBias.biased_quotient', 'R19PostBias.biased_bounds', 'R19PostBias.normalized_quotient'],
                'math_change': 'Same domainandconclusion. SealB-only range/division relations inprivateNatlemmas; mainproof hasnoOmega orlargecontext arithmeticsearch.',
                'API_primary_source': {'commit': '293d5d0c0c3f3dded4688b3ccd6a33939ac5102b',
                                       'path': 'src/Init/Data/Nat/Div/Basic.lean', 'git_blob': 'de984fa8bcba0e0324b6d236a54b1637f471705d',
                                       'div_eq_of_lt_le_argument_order': 'low k*n<=m, then high m<(k+1)*n; lines365-370',
                                       'div_lt_iff_lt_mul': 'line314: x/k<y iff x<y*k for0<k'},
                'boundary_integer_sanity_checks': checks, 'sanity_scope': 'Finitehostinteger checks, not Lean/formal/all-input proof.',
                'typecheck': 'NOT_RUN', 'axiom_replay': 'NOT_RUN', 'public_source': 'NOT_BUILT_NOT_VALIDATED',
                'runtime_and_caps': 'No runtime candidatechange. SameB2import/read4096MiB diagnostic only; noGit/CI/localLean.'}
    (HERE / 'math-repair/light-manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'file': str(target), 'sha256': sha(source), 'bytes': len(source), 'same_statement': True,
                      'unchanged_prefix': len(prefix), 'new_body_omega': 0, 'integer_boundary_checks': checks, 'status': 'CONDITIONAL_NOT_RUN'}))


if __name__ == '__main__':
    main()
