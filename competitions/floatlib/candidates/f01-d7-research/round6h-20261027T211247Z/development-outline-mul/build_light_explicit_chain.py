"""Exact three-stage chain: explicit nat_bias + conditional light normalized.
The complete outlet is derived only from the actual CI12 raw2177 source.
"""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD_NAT = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/exact-arithmetic/bias-frontier/shared-block-isolation/NatPostClosure.lean'
OLD_RUN = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40430974047'
OLD_RAW = OLD_RUN / 'download-08d56bf17d524b209ff9058819a9b0c8'
OUTLET = OLD_RAW / 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-math-outlet-isolation1/math-isolation/math-outlet/source.lean'
sha = lambda x: hashlib.sha256(x).hexdigest()


def main():
    nat = OLD_NAT.read_bytes()
    assert sha(nat) == 'cbdb2fb8e83908a6c6179c286b1648891c0186727db53b6d635a5af2689b8f31'
    raw = OUTLET.read_bytes()
    assert len(raw) == 32332 and sha(raw) == '2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266'
    old_index = json.loads((OLD_RUN / 'original-artifact-hashes.json').read_bytes())
    entry = old_index['files'][OUTLET.relative_to(OLD_RAW).as_posix()]
    assert entry['bytes'] == len(raw) and entry['sha256'] == sha(raw)
    begin, stop = nat.index(b'theorem nat_bias'), nat.index(b'theorem nat_grouped_bias')
    old_bias = nat[begin:stop].rstrip(b'\n') + b'\n'
    new_bias = (HERE / 'math-repair/NatBiasExplicit.lean.inc').read_bytes()
    light = (HERE / 'math-repair/LightNormalized.lean.inc').read_bytes()
    old_header = nat[nat.index(b'theorem normalized_quotient'):].split(b':= by', 1)[0]
    assert old_header == light[light.index(b'theorem normalized_quotient'):].split(b':= by', 1)[0]
    assert old_bias.split(b':= by', 1)[0] == new_bias.split(b':= by', 1)[0]

    def explicit(source):
        assert source.count(old_bias) == 1
        return source.replace(old_bias, new_bias)

    def normalized(source):
        marker = b'/-- The actual product cap prevents a second carry beyond bit47. -/'
        assert source.count(marker) == 1
        a = source.index(marker)
        b = source.index(b'\nend R19PostBias', a)
        header = source[source.index(b'theorem normalized_quotient', a):].split(b':= by', 1)[0]
        assert header == old_header
        return source[:a] + light.rstrip(b'\n') + source[b:]

    prefix = (HERE / 'math-repair/NatPostBeforeNormalized.lean').read_bytes()
    assert sha(prefix) == '401d368efb2ab40358f1fa6b2e23fad2b0577e52393c2558e478284fb294ed30'
    prefix_explicit = explicit(prefix)
    light_explicit = explicit((HERE / 'math-repair/NatPostLightNormalized.lean').read_bytes())
    nonblank = lambda s: [line for line in s.splitlines() if line.strip()]
    assert nonblank(normalized(explicit(nat))) == nonblank(light_explicit)
    outlet_light = normalized(explicit(raw))
    # Preserve the accepted NoWrap body and everything after its declaration start.
    nowrap_start = raw.index(b'theorem biased_sum_nat')
    assert outlet_light[outlet_light.index(b'theorem biased_sum_nat'):] == raw[nowrap_start:]
    out = HERE / 'math-repair'
    rows = []
    definitions = (
        ('NatPostBeforeNormalizedExplicit.lean', prefix_explicit, 4, 'Alwaysfirst; exact401dwithonlynat_biasreplacement.'),
        ('NatPostLightExplicit.lean', light_explicit, 5, 'Onlyifprevious4-rootprefixPASS; exact5blightwithonlynat_biasreplacement.'),
        ('MathOutletLightExplicit.lean', outlet_light, 48, 'OnlyifNatPostLightExplicitPASS; exactrawCI12-2177withtwoidentifiedproofregionschanged.'))
    for filename, source, roots, condition in definitions:
        (out / filename).write_bytes(source)
        rows.append({'file': filename, 'sha256': sha(source), 'bytes': len(source), 'new_named_roots': roots,
                     'execution_condition': condition, 'typecheck': 'NOT_RUN', 'axiom_replay': 'NOT_RUN'})
    manifest = {
        'state': 'THREE_STAGE_CONDITIONAL_DIAGNOSTIC_NOT_RUN', 'rows': rows,
        'source2177': {'path': str(OUTLET), 'bytes': len(raw), 'sha256': sha(raw), 'original_CI_inventory_match': True},
        'working_copy_fae383_32290_bytes': 'NOT_USED; no provenance/identity substitution',
        'nat_bias_replacement': {'source_helper_sha256': 'b9b7fbd16eb4cd5d69b2572d130d6f8418a8225169732fb5fc273c5c38747a7d',
                                 'result': 'Parent406192 typingPASS5.128s; sourceblockexactlyreused, stillnotfullpublicacceptance.'},
        'normalized_replacement': {'base_light_helper_sha256': '5b3e6b56cf66cfe0e124ac9424d9a8cebb83891718ca7073a39d0e722eeb26d1',
                                   'statement_byte_identical': True, 'new_proof_omega_count': 0,
                                   'condition': 'GateonfreshExplicit4-rootprefixPASS, notold401d(whichOOMedbeforeNatBiasfix).'},
        'NoWrap_and_after_byte_identical_to_raw2177': True,
        'light_helper_two_splice_recipe': 'Allnonblanklinesbyte-identical; helperpreserves5b extra blank namespace separator.',
        'unchanged': 'Allothermathdeclarations, raw2177 runtime/core/guards, originaldomains andprivatequotient remain byte-identical outside two exact proof-region replacements.',
        'caps': 'Originalg.own/read4096MiB, ordinarydiagnosticbudgetonly; nooriginalgate orresourcechanges.',
        'public_status': 'No newlargepublicKernelmaterialized; public88cdf remainsfailedpriorversion. No oldgate/scoretransfer.',
        'required_after_chain': 'Exactsourcehelperaxiom/replay thenfreshfullpublicassembly/originalgate/MainFull/performance; helperPASSdoesnotcompletewholecandidate.'
    }
    (out / 'light-explicit-chain-manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'raw2177_source_bound': True, 'rows': rows, 'NoWrap_unchanged': True}))


if __name__ == '__main__':
    main()
