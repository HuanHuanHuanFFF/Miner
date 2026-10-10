"""Check R21 namespace, exact bytes, route and bounded experiment inputs."""
import os
from round4 import validate

def main():
    assert os.environ.get('ROUND4_SPEC_DIR') == 'evidence/round21'
    if os.environ['ROUND21_MODE']=='gate':
        import importlib
        spec=importlib.import_module('verify-round21-exact').validate(os.environ['ROUND4_SPEC'])
        print('R21_EXACT_PAIR_PREFLIGHT',spec['candidate'],spec['files']);return
    spec = validate(os.environ['ROUND4_SPEC'])
    mode = os.environ['ROUND21_MODE']
    assert mode in ('native', 'standard', 'diagnostic')
    assert spec['r21_mode'] == mode
    assert bool(spec.get('native_only')) == (mode == 'native')
    if mode == 'diagnostic':
        names = spec['diagnostic_methods']
        by = {e['name']:e for e in spec['entries']}
        assert len(names) == 4 and len(set(names)) == 4 and set(names) <= set(by)
        assert by[names[0]]['hashes'] == by[names[1]]['hashes']
        assert by[names[2]]['hashes'] == by[names[3]]['hashes']
        assert spec['isolated_blocks'] == 2 and spec['multimethod_blocks'] == 4
        if spec.get('r21_library_diagnostic'):
            from importlib import import_module
            import_module('research-round21-library').preflight()
            assert isinstance(spec.get('r21_library_blocks'),int) and 1<=spec['r21_library_blocks']<=2
        if spec.get('r18_order_diagnostic'):
            from importlib import import_module
            import_module('research-round18-order').preflight()
            assert isinstance(spec.get('r18_order_blocks',4),int) and 1<=spec.get('r18_order_blocks',4)<=4
            protocols=spec.get('r18_order_protocols',['original_fixed11','original_fixed20','balanced20'])
            assert protocols and len(protocols)==len(set(protocols)) and set(protocols)<={'original_fixed11','original_fixed20','balanced20'}
        if spec.get('r21_order_diagnostic'):
            from importlib import import_module
            import_module('research-round21-order').preflight()
            assert isinstance(spec.get('r21_order_blocks',4),int) and 1<=spec.get('r21_order_blocks',4)<=4
            protocols=spec.get('r21_order_protocols',['original_fixed11','original_fixed20','balanced20'])
            assert protocols and len(protocols)==len(set(protocols)) and set(protocols)<={'original_fixed11','original_fixed20','balanced20'}
    print('R21_PREFLIGHT', mode, len(spec['entries']), 'hash-bound pairs')

if __name__ == '__main__':
    main()
