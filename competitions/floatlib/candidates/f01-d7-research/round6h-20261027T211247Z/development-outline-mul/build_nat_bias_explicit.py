"""Modify only the two default simpa branches in nat_bias; no other proof change."""
from pathlib import Path
import difflib
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/exact-arithmetic/bias-frontier/shared-block-isolation/NatPostClosure.lean'
sha = lambda x: hashlib.sha256(x).hexdigest()


def main():
    raw = OLD.read_bytes()
    assert sha(raw) == 'cbdb2fb8e83908a6c6179c286b1648891c0186727db53b6d635a5af2689b8f31'
    begin, end = raw.index(b'theorem nat_bias'), raw.index(b'theorem nat_grouped_bias')
    old_block = raw[begin:end].rstrip(b'\n') + b'\n'
    new_block = (HERE / 'math-repair/NatBiasExplicit.lean.inc').read_bytes()
    assert old_block.split(b':= by', 1)[0] == new_block.split(b':= by', 1)[0]
    assert b'simpa [' not in new_block and new_block.count(b'simpa only [') == 2
    assert new_block.count(b'quotient_bias p ') == 2
    original_prefix = raw[:begin]
    source = original_prefix + new_block + b'\nend BranchlessRNESeed\n'
    target = HERE / 'math-repair/NatBiasExplicit.lean'
    target.write_bytes(source)
    patch = ''.join(difflib.unified_diff(old_block.decode().splitlines(keepends=True),
                    new_block.decode().splitlines(keepends=True),
                    fromfile='original-cbdb2/nat_bias', tofile='NatBiasExplicit/nat_bias', n=3))
    (HERE / 'math-repair/nat-bias-explicit.patch').write_text(patch, encoding='utf-8', newline='')
    checked = 0
    for t in (23, 24):
        d, h = 2**t, 2**(t - 1)
        values = {0, 1, h - 1, h, h + 1, d - 1, d, d + h - 1, d + h, d + h + 1,
                  2**46, 2**47 - 1, 2**47, (2**24 - 1)**2}
        for p in values:
            q, r = divmod(p, d)
            expected = q + (2 * r > d or (2 * r == d and q % 2 == 1))
            assert expected == (p + h - 1 + (p >> t) % 2) >> t
            checked += 1
    manifest = {
        'state': 'NAT_BIAS_EXPLICIT_REWRITE_NOT_RUN', 'file': target.name, 'bytes': len(source), 'sha256': sha(source),
        'base_source_sha256': sha(raw), 'base_nat_bias_block_sha256': sha(old_block),
        'new_nat_bias_block_sha256': sha(new_block), 'patch_sha256': sha(patch.encode()),
        'private_quotient_prefix_bytes_unchanged': len(original_prefix), 'private_prefix_sha256': sha(original_prefix),
        'statement_and_domain_byte_identical': True,
        'only_proof_change': 'Each of two defaultsimpa branches becomes explicitRNE rewrite, explicitfixedNat target, andone-way simpaonly shift/pow/sub/mul. Samequotient instantiation andhhalf proof.',
        'explicit_new_roots': ['BranchlessRNESeed.nat_bias'],
        'unchanged_outside_new_helper': ['originalcbdb2', 'privatequotient proof', 'NatGrouped', 'NoWrap8d49', 'normalized_quotient', 'public88cdf'],
        'not_in_helper': ['nat_grouped_bias', 'R19PostBias', 'NoWrap', 'publicendpoints'],
        'next_if_oom': 'Sameprivatequotient + only its two fixed numeric instantiations in aTrue helper; distinguishinstantiation fromrewrite. NoNatGrouped/NoWrap/normalized changes.',
        'runtime': 'No algorithm, guard, publiccandidate, orcap change. SameB2import/read4096MiB diagnostic only.',
        'typecheck': 'NOT_RUN', 'axiom_replay': 'NOT_RUN', 'public_validation': 'NOT_RUN',
        'finite_integer_boundary_checks': checked, 'finite_check_scope': 'Hostinteger sanity only, not Leanprooforall-input evidence.'
    }
    (HERE / 'math-repair/nat-bias-explicit-manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'file': str(target), 'sha256': sha(source), 'bytes': len(source),
                      'private_prefix_unchanged': len(original_prefix), 'statement_identical': True,
                      'boundary_checks': checked, 'Lean': 'NOT_RUN'}))


if __name__ == '__main__':
    main()
