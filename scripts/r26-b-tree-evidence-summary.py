"""Consolidate raw tree observer/native evidence; no timing or gate projection."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    paths = {
        'b19': ROOT/'evidence/round26/38215726866/tree-b19-native/diagnostics/r26-b-tree-edge/receipt.json',
        'b20': ROOT/'evidence/round26/38216239816/tree-b20-native/diagnostics/r26-b-tree-edge/receipt.json',
        'b21': ROOT/'evidence/round26/38216961738/quality-b21-native/diagnostics/r13-encoder/encoder.json',
        'profile_b21': ROOT/'evidence/round26/38216961738/quality-b21-native/diagnostics/r18-functions/functions.json'}
    data = {k: json.loads(p.read_bytes()) for k, p in paths.items()}
    name = 'r26-b-552-tree-prefix'
    parent = (ROOT/'references/round24-public-552/parse.rs').read_bytes()
    candidate = (ROOT/'candidates'/name/'parse.rs').read_bytes()
    proof = (ROOT/'candidates'/name/'Parse.lean').read_bytes()
    assert data['b19']['source_hashes']['parse.rs'] == data['b20']['source_hashes']['parse.rs'] == sha(parent)
    assert data['b21']['source_hashes'][name] == data['profile_b21']['source_hashes'] == {'parse.rs': sha(candidate), 'Parse.lean': sha(proof)}
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    helper = importlib.import_module('r26-b-build-tree-prefix').HELPERS
    original, changed = parent.decode(), candidate.decode()
    assert changed.endswith(helper)
    reverse = changed[:-len(helper)]
    for f in ('a_tree_insert', 'a_find_all'):
        reverse = reverse.replace(fn(reverse, f), fn(original, f), 1)
    assert reverse.encode() == parent
    rows = {r['file']: r for r in data['b21']['rows'] if r['candidate'] == 'public552'}
    candidate_rows = [r for r in data['b21']['rows'] if r['candidate'] == name]
    keys = ['input_sha256', 'tokens_sha256', 'output_sha256', 'output_bytes']
    assert len(rows) == len(candidate_rows) == 28
    assert all(all(r[k] == rows[r['file']][k] for k in keys) for r in candidate_rows)
    counts = data['b20']['totals']
    result = {'status': 'VERIFIED_B19_B20_ORIGINAL_TRAJECTORY_AND_B21_PRODUCTION_ENCODER_PARITY',
              'computed_utc': datetime.now(timezone.utc).isoformat(),
              'parent_hashes': {'parse.rs': sha(parent), 'Parse.lean': sha((ROOT/'references/round24-public-552/Parse.lean').read_bytes())},
              'candidate_hashes': {'parse.rs': sha(candidate), 'Parse.lean': sha(proof)},
              'source_audit': {'reversal_restores_original_bytes': True, 'only_original_functions_changed': ['a_tree_insert', 'a_find_all'],
                               'added_helpers': ['a_edge_join', 'a_edge_pair', 'a_edge_probe'], 'all_configuration_and_other_functions_preserved': True,
                               'proof_bytes_equal_parent': proof == (ROOT/'references/round24-public-552/Parse.lean').read_bytes(),
                               'original_author_hotkey': json.loads((ROOT/'references/round24-public-552/source-receipt.json').read_bytes())['author_hotkey']},
              'real_original_trajectory': {'b19_counts': data['b19']['totals'], 'b20_counts': counts,
                                           'combined_saved_word_pairs': counts['shortcut_word_pairs'] + counts['seed_saved_word_pairs'],
                                           'combined_saved_word_pairs_pct': 100*(counts['shortcut_word_pairs'] + counts['seed_saved_word_pairs'])/counts['probe_word_pairs'],
                                           'seed_cap258_unused_direction_difference': counts['seed_258_direction_difference']},
              'production_original_encoder': {'equal_files': 28, 'output_bytes': sum(r['output_bytes'] for r in candidate_rows),
                                              'parent_tokens_and_output_equal': True,
                                              'table_bytes': 131072, 'complete_metadata_reads_writes_initialization_retained': True},
              'pure_production_profile': {'totals': data['profile_b21']['totals'],
                                          'comparison_status': 'NO_SAME_RUN_PARENT_PROFILE; cannot subtract historical clocks or infer original protocol speed'},
              'next_action': 'B23 original11rep total paired cost with extraction/finite equivalence and same-source controls; B22 independent A DP width/lowering diagnosis.',
              'proof_status': 'DRAFT_PARENT_PROOF_UNCHANGED_FOR_CHANGED_RUST; no complete gate or frozen independent confirmation',
              'limits': ['18.9percent is observed word-pair coverage, not finder or total speed.',
                         'Native total bytes/tokens/decode are finite correctness; no formal admission/share/reward.',
                         'Pure candidate clocks include actual metadata work but have no same-run parent profiler and are not benchmark scores.',
                         'Packed high6bit/capped31 tree metadata remains an unimplemented re-visitation idea, no assumed saving.'],
              'input_hashes': {p.relative_to(ROOT).as_posix(): sha(p.read_bytes()) for p in paths.values()}}
    out = ROOT/'evidence/round26/route-b/b24-tree-native-summary.json'
    assert not out.exists()
    out.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({'status': result['status'], 'word_pair_coverage_pct': result['real_original_trajectory']['combined_saved_word_pairs_pct'], 'equal_files': 28, 'source_reversal': True}))


if __name__ == '__main__':
    main()
