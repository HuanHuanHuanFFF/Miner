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
    assert spec['r26_mode'] == mode
    assert bool(spec.get('native_only')) == (mode == 'native')
    assert sum(not e.get('control', False) for e in spec['entries']) == spec['r26_expected_candidates']
    by = {e['name']: e for e in spec['entries']}
    if spec.get('r26_a_boundary_helper_check'):
        assert mode == 'standard'
        importlib.import_module('r26-a-boundary-helper-check').preflight(spec)
    if mode == 'standard':
        for e in spec['entries']:
            anchor = e.get('anchor', 'public432')
            assert anchor in by, f"Missing summary anchor {anchor} for {e['name']}"
            assert by[anchor].get('formal_id'), f"Summary anchor {anchor} needs a formal reference ID"
    assert sum(bool(spec.get(k)) for k in ('r26_a_replay', 'r26_a_boundary', 'r26_a_boundary641', 'r26_b_match_sharing', 'r26_b_cache_integrity', 'r26_b_cache_phases', 'r18_function_profile')) <= 1
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
        raise AssertionError('A diagnostic protocol must be explicitly preflighted before enabling it')
    print('R26_PREFLIGHT', mode, len(spec['entries']), 'hash-bound pairs')

if __name__ == '__main__':
    main()
