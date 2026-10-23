"""Exercise the actual embedded statement: optional tools cannot block its adapter."""
import ast
import hashlib
import json
from pathlib import Path
import subprocess
import tempfile
import types
import unittest

HERE = Path(__file__).resolve().parent
SOURCE = HERE.parent.parent / 'f01-word-tensors/ci-diagnostics.py'
SYMBOL = 'lp_competition_Submission_Packed10Index_loop___redArg'


def statement_ast(source=SOURCE):
    outer = ast.parse(source.read_text(encoding='utf-8'))
    embedded = next(n.value.value for n in ast.walk(outer)
                    if isinstance(n, ast.Assign) and isinstance(n.value, ast.Constant)
                    and any(isinstance(t, ast.Name) and t.id == 'code' for t in n.targets))
    tree = ast.parse(embedded)
    fn = next(n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name == 'statement')
    return ast.Module(body=[fn], type_ignores=[])


class AdapterFailure(RuntimeError):
    pass


class OriginalFailure(RuntimeError):
    pass


class OuterDiagnosticCaptureTests(unittest.TestCase):
    def harness(self, nm='ok', objdump='ok', reason=None, adapter_error=None, original_error=None):
        temp = tempfile.TemporaryDirectory(prefix='.outer-diagnostic-test-', dir=HERE)
        self.addCleanup(temp.cleanup)
        base = Path(temp.name).resolve()
        self.assertTrue(base.is_relative_to(HERE) and base.name.startswith('.outer-diagnostic-test-'))
        upper = base / 'layer/upper/ir'
        upper.mkdir(parents=True)
        (upper / 'Submission.c').write_bytes(b'/* fake successful original statement C */\n')
        (upper / 'Submission.c.o.export').write_bytes(b'\x7fELFfake-object')
        out = base / 'reports'
        out.mkdir()
        kernel = base / 'candidates/f01-d7-public-suite/Kernel.lean'
        kernel.parent.mkdir(parents=True)
        kernel.write_bytes(b'import ContractTensor\n')
        (kernel.parent / 'suite-plan.json').write_bytes(b'{}')
        profiler = base / 'candidates/f01-d5-costsplit/profile-native.py'
        g = types.SimpleNamespace(LAYER=base / 'layer')
        verdict = object()
        calls = {'original': [], 'adapter': [], 'tools': [], 'imports': []}

        def original_statement(src, received):
            calls['original'].append((src, received))
            if original_error is not None:
                raise original_error
            return reason

        def run_adapter(*args):
            calls['adapter'].append(args)
            if adapter_error is not None:
                raise adapter_error

        def spec_from_file_location(name, path):
            calls['imports'].append((name, path))
            self.assertEqual(name, 'current_public_suite')
            self.assertEqual(path, base / 'candidates/f01-d7-research/public-suite.py')
            return types.SimpleNamespace(loader=types.SimpleNamespace(
                exec_module=lambda module: setattr(module, 'run', run_adapter)))

        def tool(argv, **kwargs):
            calls['tools'].append(argv)
            self.assertEqual(kwargs['timeout'], 15)
            self.assertTrue(kwargs['capture_output'])
            mode = nm if argv[0] == 'nm' else objdump
            self.assertIn(argv[0], ('nm', 'objdump'))
            if mode == 'timeout':
                raise subprocess.TimeoutExpired(argv, 15)
            if mode == 'oserror':
                raise OSError('tool unavailable sentinel')
            code = 17 if mode == 'nonzero' else 0
            if argv[0] == 'nm':
                self.assertEqual(argv[:2], ['nm', '--defined-only'])
                self.assertTrue(kwargs['text'])
                return types.SimpleNamespace(returncode=code, stdout='00000000 T ' + SYMBOL + '\n',
                                             stderr='nm stderr sentinel')
            self.assertEqual(argv[:4], ['objdump', '-d', '--no-show-raw-insn', '-Mintel'])
            return types.SimpleNamespace(returncode=code, stdout=b'fake asm\n', stderr=b'objdump stderr sentinel')

        ns = {'original_statement': original_statement, 'g': g, 'kernel': kernel,
              'out': out, 'profiler': profiler, 'json': json, 'hashlib': hashlib,
              'subprocess': types.SimpleNamespace(run=tool, TimeoutExpired=subprocess.TimeoutExpired),
              'importlib': types.SimpleNamespace(util=types.SimpleNamespace(
                  spec_from_file_location=spec_from_file_location,
                  module_from_spec=lambda spec: types.SimpleNamespace()))}
        exec(compile(statement_ast(), str(SOURCE) + ':embedded-statement', 'exec'), ns)
        return ns['statement'], g, kernel, out, verdict, calls

    def assert_optional_failure_continues(self, tool, mode):
        fn, g, kernel, out, verdict, calls = self.harness(**{tool: mode})
        self.assertIsNone(fn(kernel, verdict))
        self.assertEqual(calls['original'], [(kernel, verdict)])
        self.assertEqual(calls['adapter'], [(g, kernel, out)])
        rows = json.loads((out / 'native-assembly-index.json').read_text())
        unknown = [r for r in rows if r.get('state') == 'UNKNOWN' and r.get('tool') == tool]
        self.assertEqual(len(unknown), 1, rows)
        if mode == 'nonzero':
            self.assertEqual(unknown[0]['exit_code'], 17)
        else:
            self.assertEqual(unknown[0]['error_type'], 'TimeoutExpired' if mode == 'timeout' else 'OSError')
        if tool == 'nm':
            self.assertEqual([x[0] for x in calls['tools']], ['nm'])
        self.assertFalse(list(out.glob('native-loop-*')))

    def test_nm_timeout_is_unknown_and_adapter_runs(self):
        self.assert_optional_failure_continues('nm', 'timeout')

    def test_nm_oserror_is_unknown_and_adapter_runs(self):
        self.assert_optional_failure_continues('nm', 'oserror')

    def test_nm_nonzero_is_unknown_and_partial_symbols_are_not_used(self):
        self.assert_optional_failure_continues('nm', 'nonzero')

    def test_objdump_timeout_is_unknown_and_adapter_runs(self):
        self.assert_optional_failure_continues('objdump', 'timeout')

    def test_objdump_oserror_is_unknown_and_adapter_runs(self):
        self.assert_optional_failure_continues('objdump', 'oserror')

    def test_objdump_nonzero_is_unknown_and_adapter_runs(self):
        self.assert_optional_failure_continues('objdump', 'nonzero')

    def test_original_failure_reason_is_unchanged_and_adapter_is_not_called(self):
        reason = 'original statement rejected sentinel'
        fn, g, kernel, out, verdict, calls = self.harness(reason=reason)
        self.assertIs(fn(kernel, verdict), reason)
        self.assertEqual(calls['adapter'], [])
        self.assertEqual(calls['tools'], [])
        self.assertFalse((out / 'native-assembly-index.json').exists())

    def test_original_statement_exception_propagates(self):
        error = OriginalFailure('original crash sentinel')
        fn, g, kernel, out, verdict, calls = self.harness(original_error=error)
        with self.assertRaises(OriginalFailure) as caught:
            fn(kernel, verdict)
        self.assertIs(caught.exception, error)
        self.assertEqual(calls['adapter'], [])
        self.assertEqual(calls['tools'], [])

    def test_adapter_exception_propagates_with_and_without_capture_failure(self):
        for mode in ('ok', 'timeout'):
            with self.subTest(nm=mode):
                error = AdapterFailure('adapter validation failed sentinel')
                fn, g, kernel, out, verdict, calls = self.harness(nm=mode, adapter_error=error)
                with self.assertRaises(AdapterFailure) as caught:
                    fn(kernel, verdict)
                self.assertIs(caught.exception, error)
                self.assertEqual(calls['adapter'], [(g, kernel, out)])

    def test_success_keeps_capture_and_calls_adapter_once(self):
        fn, g, kernel, out, verdict, calls = self.harness()
        self.assertIsNone(fn(kernel, verdict))
        self.assertEqual(calls['adapter'], [(g, kernel, out)])
        rows = json.loads((out / 'native-assembly-index.json').read_text())
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]['kind'], 'actual-built-object-disassembly')
        self.assertEqual(rows[0]['exit_code'], 0)
        self.assertEqual(rows[0]['symbol'], SYMBOL)
        self.assertEqual(len(list(out.glob('native-loop-*'))), 1)


if __name__ == '__main__':
    unittest.main()
