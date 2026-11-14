"""Build a current proof-leaf index without changing any runtime or proof source."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
sha = lambda b: hashlib.sha256(b).hexdigest()
RUNTIME = '8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
ITEMS = [
    ('Nat8Projection-v1.lean.inc', '79574fb1b64febf7d3cd328fe41c2f11ac2172e81177fd2cb057aa74e574d6dd',
     'VERIFIED_CONDITIONAL_4_ROOTS_40619267183', [], 'nat8-projection-accepted-40619267183.json'),
    ('Indexed8LoopEq-v2.lean.inc', 'ccee65d418fbe9cce253dada4962b7574fb06ab0e5d3146fe7f39ef72884e81b',
     'VERIFIED_3_SELECTED_ROOTS_MODULE_REPLAY_40621932164', [], 'indexed8-loop-accepted-40621932164.json'),
    ('Nat8CacheSelected.lean.inc', 'a457ed45ade0ab620456da9f397c429517c4764ad19e10f793b60b21caadb5c1',
     'NOT_COMPILED_NOT_RUN', ['EXTERNAL:Pair8CacheProof2850a16c'], 'nat8-cache-selected-manifest.json'),
    ('Nat8ProjectionFacts.lean.inc', 'c63fdfebb9ee123e07e4e5998033a85ae55d71677b442e6b1f65de4d2df6fc3d',
     'NOT_COMPILED_NOT_RUN', ['Nat8Projection-v1.lean.inc'], 'nat8-projection-facts-manifest.json'),
    ('Nat8FinishLane.lean.inc', '1cde71346e7b2e0690253f893594963003fd2f3e1265e808c00014fea12a99cc',
     'NOT_COMPILED_NOT_RUN', ['Nat8Projection-v1.lean.inc', 'Nat8ProjectionFacts.lean.inc'], 'nat8-finish-lane-manifest.json'),
    ('Nat8CacheViewHRead.lean.inc', '41e6dbec2f3bc5094f76d4d22661058f3d762a64f15b31e43362e3718590ad5d',
     'NOT_COMPILED_NOT_RUN', ['Nat8Projection-v1.lean.inc', 'Nat8CacheSelected.lean.inc'], 'nat8-cache-hread-manifest.json'),
    ('Nat8WordProjection.lean.inc', '5277ada5d400f4e832ce6c3c7f708b04447e93034407232c067bff946e84d956',
     'NOT_COMPILED_NOT_RUN', ['Nat8Projection-v1.lean.inc'], 'nat8-word-projection-manifest.json'),
    ('Indexed8OutputEq.lean.inc', '3adbd31379c8946ebf0f01c3ae312888fef80cc2cb7743fcace971945bf52417',
     'NOT_COMPILED_NOT_RUN', ['Indexed8LoopEq-v2.lean.inc'], 'indexed8-output-eq-manifest.json'),
    ('Indexed8CoreEq.lean.inc', '9da6f3f9388056f52d80e4594e4502542ad53f3de497b1457f3a8e4b58612d7f',
     'NOT_COMPILED_NOT_RUN', ['Indexed8LoopEq-v2.lean.inc', 'Indexed8OutputEq.lean.inc'], 'indexed8-core-eq-manifest.json'),
    ('Nat8ReadProjection.lean.inc', 'a8cf1655d6e2418da1e474156bd982bee478e257639005c035c92eb46ca97549',
     'NOT_COMPILED_NOT_RUN', ['Nat8WordProjection.lean.inc'], 'nat8-read-projection-manifest.json'),
    ('Nat8PointwiseRead.lean.inc', '65101d8d067cf17ddb8740f295e131b744eb3efc62449be685a5a86ccbf7cc4e',
     'NOT_COMPILED_NOT_RUN', ['Nat8ReadProjection.lean.inc', 'Nat8FinishLane.lean.inc'], 'nat8-pointwise-read-manifest.json'),
    ('Nat8ActualRead.lean.inc', '378765ff0b7ff349051e8e7baff06f776a666b59e1b663c241f56e4adcc60580',
     'NOT_COMPILED_NOT_RUN', ['Nat8PointwiseRead.lean.inc', 'Nat8CacheViewHRead.lean.inc'], 'nat8-actual-read-manifest.json'),
]


def main():
    runtime = (HERE / 'KernelIndexed8Cost.lean').read_bytes()
    assert sha(runtime) == RUNTIME
    combined = (HERE / 'KernelIndexed8LoopProbe-v2.lean').read_bytes()
    assert sha(combined) == '7981b04cfe8fa1bf68eec31bd8c5d8abdd6a2e50c1a46bd5f7456a9a9d4d3ba8'
    assert combined.startswith(runtime)
    all_roots = set()
    selected_audited = set()
    typed_replayed = set()
    entries = []
    for filename, expected, state, deps, receipt in ITEMS:
        data = (HERE / filename).read_bytes()
        assert sha(data) == expected, filename
        text = data.decode()
        ns = re.search(r'^namespace (\S+)', text, re.M)[1]
        roots = [ns + '.' + s for s in re.findall(r'^theorem (\w+)', text, re.M)]
        assert not (set(roots) & all_roots), roots
        all_roots.update(roots)
        receipt_data = (HERE / receipt).read_bytes()
        json.loads(receipt_data)
        selected = []
        if filename == 'Nat8Projection-v1.lean.inc':
            selected = roots
            typed_replayed.update(roots)
        elif filename == 'Indexed8LoopEq-v2.lean.inc':
            selected = json.loads(receipt_data)['selected_roots']
            typed_replayed.update(roots)
        selected_audited.update(selected)
        entries.append(dict(path=filename, sha256=expected, bytes=len(data), roots=roots,
                            status=state, dependencies=deps,
                            explicitly_axiom_audited_roots=selected,
                            receipt=dict(path=receipt, sha256=sha(receipt_data))))
    result = dict(runtime=dict(path='KernelIndexed8Cost.lean', sha256=RUNTIME, bytes=len(runtime), frozen=True),
                  word_transport_probe=dict(path='KernelIndexed8LoopProbe-v2.lean',
                    sha256=sha(combined), bytes=len(combined), status='VERIFIED_3_SELECTED_ROOTS_MODULE_REPLAY_40621932164'),
                  leaves=entries,
                  counts=dict(unique_roots=len(all_roots), selected_axiom_audited_roots=len(selected_audited),
                    typed_replayed_not_selected_roots=len(typed_replayed-selected_audited),
                    uncompiled_roots=len(all_roots-typed_replayed)),
                  source_checks='Exact frozen hashes, root uniqueness, valid JSON receipts, unchanged runtime prefix.',
                  full_public_BMM_proof='UNKNOWN', full_gate='NOT_RUN',
                  note='Initial leaf comments/manifests retain their historical NOT_RUN state; accepted evidence is the separate receipt.')
    (HERE / 'proof-leaf-index.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(dict(runtime_sha256=RUNTIME, leaves=len(entries), unique_roots=len(all_roots),
                          selected_axiom_audited_roots=len(selected_audited),
                          typed_replayed_not_selected_roots=len(typed_replayed-selected_audited),
                          uncompiled_roots=len(all_roots-typed_replayed))))


if __name__ == '__main__':
    main()
