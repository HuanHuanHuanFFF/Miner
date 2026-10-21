"""Check exact R26 inputs before original native, measurement, extraction or gate routes."""
import importlib
import os
from round4 import validate

def main():
    assert os.environ.get('ROUND4_SPEC_DIR') == 'evidence/round26'
    mode = os.environ['ROUND26_MODE']
    assert mode in ('native', 'standard', 'extract', 'gate', 'diagnostic')
    if mode == 'gate':
        spec = importlib.import_module('verify-round26-exact').validate(os.environ['ROUND4_SPEC'])
        print('R26_EXACT_PAIR_PREFLIGHT', spec['candidate'], spec['files'])
        return
    spec = validate(os.environ['ROUND4_SPEC'])
    assert sum(bool(spec.get(k)) for k in ('r26_b_tag_graph_integrity', 'r26_b_tree_packed_counts', 'r26_b_a_flatten_counts')) <= 1
    assert sum(bool(spec.get(k)) for k in ('r26_a_lazy_chain_counts', 'r26_a_distance12_counts', 'r26_a_second_look_counts', 'r26_a_row_counts', 'r26_a_tagged_counts', 'r26_a_lastlink_lowering', 'r26_a_window_counts')) <= 1
    assert spec['r26_mode'] == mode
    assert bool(spec.get('native_only')) == (mode == 'native')
    assert sum(not e.get('control', False) for e in spec['entries']) == spec['r26_expected_candidates']
    by = {e['name']: e for e in spec['entries']}
    if spec.get('r26_a_boundary_helper_check'):
        assert mode == 'standard'
        importlib.import_module('r26-a-boundary-helper-check').preflight(spec)
    if spec.get('r26_a_pc_budget_counts'):
        assert mode == 'standard' and not spec.get('r26_a_boundary_helper_check')
        importlib.import_module('r26-a-pc-budget-counts').preflight(spec)
    if mode == 'standard':
        for e in spec['entries']:
            anchor = e.get('anchor', 'public432')
            assert anchor in by, f"Missing summary anchor {anchor} for {e['name']}"
            assert by[anchor].get('formal_id'), f"Summary anchor {anchor} needs a formal reference ID"
    assert sum(bool(spec.get(k)) for k in ('r26_a_replay', 'r26_a_boundary', 'r26_a_boundary641', 'r26_a_distance12_observer_only', 'r26_a_row_shadow', 'r26_a_link_replay', 'r26_a_rep_shadow', 'r26_a_near_counts', 'r26_a_common_lowering', 'r26_b_match_sharing', 'r26_b_cache_integrity', 'r26_b_cache_phases', 'r26_b_d_front_counts', 'r26_b_a_repeat_counts', 'r26_b_a_overlap_counts', 'r26_b_a_discarded_counts', 'r26_b_tree_edge_counts', 'r26_b_a_compiler_counts', 'r26_b_a_price_group_counts', 'r18_function_profile')) <= 1
    if spec.get('r26_a_replay'):
        assert mode == 'native' and spec.get('native_encoder') is False
        assert all(e.get('control') for e in spec['entries'])
        assert spec.get('gate_candidates') == [] and spec.get('extract_candidates') == []
        importlib.import_module('r26-a-replay').preflight(spec)
    if spec.get('r26_a_boundary'):
        assert mode == 'native' and spec.get('native_encoder') is False
        assert all(e.get('control') for e in spec['entries'])
        assert spec.get('gate_candidates') == [] and spec.get('extract_candidates') == []
        importlib.import_module('r26-a-boundary').preflight()
    if spec.get('r26_a_boundary641'):
        assert mode == 'native' and spec.get('native_encoder') is False
        assert all(e.get('control') for e in spec['entries'])
        assert spec.get('gate_candidates') == [] and spec.get('extract_candidates') == []
        importlib.import_module('r26-a-boundary641').preflight(spec)
    if spec.get('r26_b_match_sharing'):
        assert mode == 'native' and spec.get('native_encoder') is False
        assert all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-b-match-sharing').preflight(spec)
    if spec.get('r26_b_cache_integrity'):
        assert mode == 'native' and spec.get('native_encoder') is False
        assert spec['r26_b_cache_integrity_module'] == 'r26-b-cache-integrity-fix1'
        importlib.import_module(spec['r26_b_cache_integrity_module']).preflight(spec)
    if spec.get('r26_b_cache_phases'):
        assert mode == 'native' and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-b-cache-phases').preflight(spec)
    if spec.get('r26_b_d_front_counts'):
        assert mode == 'native' and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-b-d-front-diagnostic').preflight(spec)
    if spec.get('r26_b_a_repeat_counts'):
        assert mode == 'native' and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-b-a-repeat-diagnostic').preflight(spec)
    if spec.get('r26_b_a_overlap_counts'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-b-a-overlap-diagnostic').preflight(spec)
    if spec.get('r26_b_a_discarded_counts'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-b-a-discarded-diagnostic').preflight(spec)
    if spec.get('r26_b_tree_edge_counts'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        module=spec.get('r26_b_tree_edge_module', 'r26-b-tree-edge-diagnostic')
        assert module in ('r26-b-tree-edge-diagnostic', 'r26-b-tree-seed-diagnostic')
        importlib.import_module(module).preflight(spec)
    if spec.get('r26_b_a_compiler_counts'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        module=spec.get('r26_b_a_compiler_module', 'r26-b-a-compiler-diagnostic')
        assert module in ('r26-b-a-compiler-diagnostic', 'r26-b-a-checked-lowering')
        importlib.import_module(module).preflight(spec)
    if spec.get('r26_b_a_price_group_counts'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-b-a-price-group-counts').preflight(spec)
    if spec.get('r26_a_lazy_chain_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True and not spec.get('r18_function_profile')
        importlib.import_module('r26-a-lazy-chain-counts').preflight(spec)
    if spec.get('r26_a_distance12_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True and not spec.get('r18_function_profile')
        assert not spec.get('r26_a_lazy_chain_counts')
        importlib.import_module('r26-a-distance12-counts').preflight(spec)
    if spec.get('r26_a_distance12_observer_only'):
        assert mode == 'native' and spec.get('native_encoder') is False
        assert not spec.get('r26_a_distance12_counts') and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-a-distance12-counts').preflight(spec)
    if spec.get('r26_a_row_shadow'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-a-row-shadow').preflight(spec)
    if spec.get('r26_a_link_replay'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-a-link-replay').preflight(spec)
    if spec.get('r26_a_rep_shadow'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-a-rep-shadow').preflight(spec)
    if spec.get('r26_a_near_counts'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-a-near-counts').preflight(spec)
    if spec.get('r26_a_common_lowering'):
        assert mode == 'native' and spec.get('native_encoder') is False and all(e.get('control') for e in spec['entries'])
        importlib.import_module('r26-a-common-wrapping-lowering').preflight(spec)
    if spec.get('r26_a_second_look_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True and not spec.get('r18_function_profile')
        importlib.import_module('r26-a-second-look-counts').preflight(spec)
    if spec.get('r26_a_row_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True and not spec.get('r18_function_profile')
        importlib.import_module('r26-a-row-counts').preflight(spec)
    if spec.get('r26_a_tagged_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True and not spec.get('r18_function_profile')
        importlib.import_module('r26-a-tagged-counts').preflight(spec)
    if spec.get('r26_a_lastlink_lowering'):
        assert mode == 'native' and spec.get('native_encoder') is True and not spec.get('r18_function_profile')
        importlib.import_module('r26-a-lastlink-lowering').preflight(spec)
    if spec.get('r26_c_greedy_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True
        importlib.import_module('r26-c-greedy-counts').preflight(spec)
    if spec.get('r26_c_deferred_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True
        importlib.import_module('r26-c-deferred-counts').preflight(spec)
    if spec.get('r26_c_fold_tail_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True
        importlib.import_module('r26-c-fold-tail-counts').preflight(spec)
    if spec.get('r26_a_window_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True and not spec.get('r18_function_profile')
        importlib.import_module('r26-a-window-counts').preflight(spec)
    if spec.get('r26_b_tag_graph_integrity'):
        assert mode == 'native' and spec.get('native_encoder') is True and spec.get('r18_function_profile') is True
        importlib.import_module('r26-b-tag-graph-integrity').preflight(spec)
    if spec.get('r26_b_tree_packed_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True and spec.get('r18_function_profile') is True
        importlib.import_module('r26-b-tree-packed-counts').preflight(spec)
    if spec.get('r26_b_a_flatten_counts'):
        assert mode == 'native' and spec.get('native_encoder') is True and spec.get('r18_function_profile') is True
        module=spec.get('r26_b_a_flatten_module', 'r26-b-a-flatten-counts')
        assert module in ('r26-b-a-flatten-counts', 'r26-b-a-no-owner-counts')
        importlib.import_module(module).preflight(spec)
    if spec.get('r18_function_profile'):
        assert mode == 'native' and spec.get('native_encoder') is True
        from round4 import ROOT
        e = by[spec['r15_profile_entry']]
        importlib.import_module('research-round18-functions').instrument((ROOT/e['path']/'parse.rs').read_bytes(), spec['r15_profile_functions'])
    if mode == 'extract':
        names = spec.get('extract_candidates', [])
        assert 1 <= len(names) <= 3 and len(names) == len(set(names))
        assert all(n in by and not by[n].get('control') for n in names)
        assert spec.get('gate_candidates') == [] and not spec.get('gate_limit')
    if mode == 'native' and spec.get('native_encoder'):
        names = {'public514'} | set(spec.get('native_encoder_references', [])) | {e['name'] for e in spec['entries'] if not e.get('control')}
        assert len(names) <= 6 and names <= set(by)
    if spec.get('r26_finite_equivalence'):
        assert mode == 'native' and spec.get('native_encoder') is True
        module = importlib.import_module('research-round4')
        pairs = module.equivalence_pairs(spec)
        assert pairs and all(e.get('expected_equivalent_to') for e in spec['entries'] if not e.get('control'))
        module.build_harness(pairs)
    if spec.get('r26_native_decode'):
        assert mode == 'native' and not spec.get('r26_finite_equivalence')
        importlib.import_module('research-round12-decode').harness(spec)
    if mode == 'standard' and any(e.get('native_decode_reference') for e in spec['entries']):
        importlib.import_module('research-round12-decode').harness(spec)
    if mode == 'diagnostic':
        assert sum(bool(spec.get(k)) for k in ('r26_a_engine_placement', 'r26_v_call_cpu')) == 1
        assert spec.get('r18_mode') == 'diagnostic'
        assert all(e.get('control') for e in spec['entries']) and not spec.get('native_encoder')
        module = 'r26-v-call-cpu' if spec.get('r26_v_call_cpu') else 'r26-a-engine-placement'
        importlib.import_module(module).preflight(spec)
    print('R26_PREFLIGHT', mode, len(spec['entries']), 'hash-bound pairs')

if __name__ == '__main__':
    main()
