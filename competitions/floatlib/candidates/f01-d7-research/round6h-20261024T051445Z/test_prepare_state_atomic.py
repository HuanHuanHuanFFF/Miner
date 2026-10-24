"""Actual coordinator function with file-open/replace failures in temporary files."""
from pathlib import Path
import ast
import json
import os
import tempfile
import unittest
from unittest.mock import patch
import uuid

HERE = Path(__file__).resolve().parent
tree = ast.parse((HERE/'prepare-plan.py').read_text())
function = next(n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name == 'save_state_atomic')
env = {'json':json,'os':os,'uuid':uuid}
exec(compile(ast.Module(body=[function],type_ignores=[]),'prepare-plan.py','exec'),env)
save = env['save_state_atomic']


class AtomicStateTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(prefix='.prepare-state-test-',dir=HERE)
        self.addCleanup(self.tmp.cleanup)
        self.path = Path(self.tmp.name)/'state.json'
        self.before = b'{"unchanged": true}\n'
        self.path.write_bytes(self.before)

    def test_direct_target_write_open_failure_is_avoided(self):
        original = Path.open
        def opened(path,mode='r',*args,**kwargs):
            if path == self.path and ('w' in mode or 'x' in mode):
                raise OSError(22,'injected target write-open failure')
            return original(path,mode,*args,**kwargs)
        with patch.object(Path,'open',opened):
            save(self.path,{'new':True},self.before)
        self.assertEqual(json.loads(self.path.read_bytes()),{'new':True})
        self.assertEqual(list(self.path.parent.glob('*.tmp')),[])

    def test_concurrent_change_is_preserved(self):
        self.path.write_bytes(b'external change')
        with self.assertRaisesRegex(ValueError,'Concurrent state change'):
            save(self.path,{'new':True},self.before)
        self.assertEqual(self.path.read_bytes(),b'external change')
        self.assertEqual(list(self.path.parent.glob('*.tmp')),[])

    def test_replace_failure_does_not_truncate_state(self):
        with patch.object(os,'replace',side_effect=OSError('injected replacement failure')):
            with self.assertRaises(OSError):
                save(self.path,{'new':True},self.before)
        self.assertEqual(self.path.read_bytes(),self.before)
        self.assertEqual(list(self.path.parent.glob('*.tmp')),[])


if __name__ == '__main__':
    unittest.main()
