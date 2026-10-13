"""Validate original-protocol R27 source/proof bytes and routing."""
import os,importlib
from round4 import validate
def main():
    assert os.environ['ROUND4_SPEC_DIR']=='evidence/round27'
    mode=os.environ['ROUND27_MODE']
    assert mode in ('standard','gate','extract')
    if mode=='gate':
        s=importlib.import_module('verify-round27-exact').validate(os.environ['ROUND4_SPEC'])
    else:
        s=validate(os.environ['ROUND4_SPEC'])
        assert sum(not e.get('control') for e in s['entries'])==s['r27_expected_candidates']
        assert not s.get('native_only')
        by={e['name']:e for e in s['entries']}
        if mode=='standard':
            for e in s['entries']:
                assert e.get('anchor','public432') in by
                assert by[e.get('anchor','public432')].get('formal_id')
        if mode=='extract':
            assert 1<=len(s['extract_candidates'])<=3
    assert s['r27_mode']==mode
    print('R27_PREFLIGHT',mode,s.get('files',len(s.get('entries',[]))))
if __name__=='__main__':main()
