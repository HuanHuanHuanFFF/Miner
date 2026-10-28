"""Exact declaration-boundary cut of cbdb2; no proof edit and no Lean invocation."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/exact-arithmetic/bias-frontier/shared-block-isolation/NatPostClosure.lean'
sha = lambda x: hashlib.sha256(x).hexdigest()


def main():
    original = OLD.read_bytes()
    assert sha(original) == 'cbdb2fb8e83908a6c6179c286b1648891c0186727db53b6d635a5af2689b8f31'
    marker = b'/-- The actual product cap prevents a second carry beyond bit47. -/'
    assert original.count(marker) == 1
    stop = original.index(marker)
    prefix = original[:stop]
    source = prefix + b'end R19PostBias\n'
    assert source.count(b'theorem ') == 5  # One private quotient plus four public roots.
    assert b'normalized_quotient' not in source
    out = HERE / 'math-repair'
    out.mkdir(exist_ok=True)
    target = out / 'NatPostBeforeNormalized.lean'
    target.write_bytes(source)
    manifest = {
        'state': 'EXACT_DECLARATION_PREFIX_NOT_RUN', 'file': target.name, 'bytes': len(source), 'sha256': sha(source),
        'base': {'path': str(OLD), 'bytes': len(original), 'sha256': sha(original)},
        'source_fidelity': {'unchanged_prefix_bytes': stop, 'unchanged_prefix_sha256': sha(prefix),
                            'only_new_bytes': 'end R19PostBias newline; closes the still-open namespace after originalbiased_bounds.'},
        'explicit_new_roots': ['BranchlessRNESeed.nat_bias', 'BranchlessRNESeed.nat_grouped_bias',
                               'R19PostBias.biased_quotient', 'R19PostBias.biased_bounds'],
        'context': 'Import exact compiledB2 Submission, same original g.own/read 4096MiB; no newresource/cap/gate setting.',
        'decision': {'prefix_pass': 'The final normalized_quotient declaration or its extra live context remains the new discriminating segment; do not rewriteNoWrap.',
                     'prefix_oom': 'Failure is before normalized_quotient; next exact declaration prefix is Nat seed alone, then nat_bias versusnat_grouped_bias. Do not call finalclosure the cause.',
                     'typed_error': 'Read exact goal; keeporiginalcbdb2 and failedprefix bytes. Do not classifytyped error asOOM.'},
        'runtime': 'Only original shift/biased mathematicaldefinitions; no publiccandidate/runtime/MUL change.',
        'proof_edits': False, 'typecheck': 'NOT_RUN', 'axiom_replay': 'NOT_RUN', 'score': 'NOT_RUN',
        'not_transferable': 'Helper success does not complete originalcbdb2,2177,fa652 or88cdf full source.'
    }
    (out / 'prefix-manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'path': str(target), 'sha256': sha(source), 'bytes': len(source), 'new_roots': 4,
                      'unchanged_prefix_bytes': stop, 'status': 'NOT_RUN'}))


if __name__ == '__main__':
    main()
