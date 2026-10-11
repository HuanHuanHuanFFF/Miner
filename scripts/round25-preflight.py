"""Check R25 namespace, exact bytes, route and bounded experiment inputs."""
import os
from round4 import validate

def main():
    assert os.environ.get('ROUND4_SPEC_DIR') == 'evidence/round25'
    if os.environ['ROUND25_MODE']=='gate':
        import importlib
        spec=importlib.import_module('verify-round25-exact').validate(os.environ['ROUND4_SPEC'])
        print('R25_EXACT_PAIR_PREFLIGHT',spec['candidate'],spec['files']);return
    spec = validate(os.environ['ROUND4_SPEC'])
    if 'r25_expected_candidates' in spec:
        assert sum(not e.get('control', False) for e in spec['entries']) == spec['r25_expected_candidates'], 'Frozen candidate count must match actual entries'
    mode = os.environ['ROUND25_MODE']
    assert mode in ('native', 'standard', 'diagnostic', 'extract')
    if spec.get('r25_debug_extract_fixture'):
        assert mode=='extract', 'Debug extraction fixtures must never enter performance or full-gate routes'
    assert spec['r25_mode'] == mode
    assert bool(spec.get('native_only')) == (mode == 'native')
    if mode == 'extract':
        names=spec.get('extract_candidates',[])
        by={e['name']:e for e in spec['entries']}
        assert 1<=len(names)<=3 and len(names)==len(set(names))
        assert all(n in by and not by[n].get('control') for n in names)
        assert spec.get('gate_candidates')==[] and not spec.get('gate_limit')
    if mode == 'native' and spec.get('native_encoder'):
        names={'public514'} | set(spec.get('native_encoder_references',[])) | {e['name'] for e in spec['entries'] if not e.get('control')}
        assert len(names)<=6 and names <= {e['name'] for e in spec['entries']}
    if spec.get('r25_finite_equivalence'):
        assert mode=='native' and spec.get('native_encoder') is True
        import importlib
        m=importlib.import_module('research-round4')
        pairs=m.equivalence_pairs(spec)
        assert pairs and all(e.get('expected_equivalent_to') for e in spec['entries'] if not e.get('control'))
        m.build_harness(pairs)
    if mode == 'standard':
        from importlib import import_module
        pairs=[e for e in spec['entries'] if e.get('native_decode_reference')]
        if pairs:
            assert len(pairs)<=4
            import_module('research-round12-decode').harness(spec)
    if mode == 'diagnostic':
        if 'r25_order_timeout_seconds' in spec:
            seconds=spec['r25_order_timeout_seconds']
            assert type(seconds) is int and 300<=seconds<=900
            assert spec.get('r18_order_diagnostic') is True
        names = spec['diagnostic_methods']
        by = {e['name']:e for e in spec['entries']}
        assert len(names) == 4 and len(set(names)) == 4 and set(names) <= set(by)
        assert by[names[0]]['hashes'] == by[names[1]]['hashes']
        assert by[names[2]]['hashes'] == by[names[3]]['hashes']
        if spec.get('r25_affinity_diagnostic') or spec.get('r25_layout_diagnostic'):
            assert spec['isolated_blocks']==2 and spec['multimethod_blocks']==0
            assert not spec.get('r18_order_diagnostic') and not spec.get('r20_library_diagnostic')
        else:
            assert spec['isolated_blocks'] == 2 and spec['multimethod_blocks'] == 4
        if spec.get('r25_library_diagnostic'):
            from importlib import import_module
            import_module('research-round24-library').preflight()
            assert isinstance(spec.get('r25_library_blocks'),int) and 1<=spec['r25_library_blocks']<=2
        if spec.get('r18_order_diagnostic'):
            from importlib import import_module
            import_module('research-round18-order').preflight()
            assert isinstance(spec.get('r18_order_blocks',4),int) and 1<=spec.get('r18_order_blocks',4)<=4
            protocols=spec.get('r18_order_protocols',['original_fixed11','original_fixed20','balanced20'])
            assert protocols and len(protocols)==len(set(protocols)) and set(protocols)<={'original_fixed11','original_fixed20','balanced20'}
        if spec.get('r25_order_diagnostic'):
            from importlib import import_module
            import_module('research-round24-order').preflight()
            assert isinstance(spec.get('r25_order_blocks',4),int) and 1<=spec.get('r25_order_blocks',4)<=4
            protocols=spec.get('r25_order_protocols',['original_fixed11','original_fixed20','balanced20'])
            assert protocols and len(protocols)==len(set(protocols)) and set(protocols)<={'original_fixed11','original_fixed20','balanced20'}
    print('R25_PREFLIGHT', mode, len(spec['entries']), 'hash-bound pairs')

if __name__ == '__main__':
    main()
