"""Whole Kernel.lean artifact boundary: layout, licence bytes and preservation."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

SCRIPT=Path(__file__).with_name('source-budget.py')
TEMP_ROOT=SCRIPT.resolve().parents[4]/'.local-maintenance/r7-20261023/source-budget-tests'

class SourceBudgetArtifactTests(unittest.TestCase):
    def invoke(self,source):
        TEMP_ROOT.mkdir(parents=True,exist_ok=True)
        with tempfile.TemporaryDirectory(prefix='case-',dir=TEMP_ROOT) as temp:
            d=Path(temp);src=d/'Kernel.lean';dst=d/'Prepared.lean';report=d/'report.json'
            self.assertTrue(d.resolve().is_relative_to(TEMP_ROOT.resolve()))
            src.write_bytes(source)
            process=subprocess.run([sys.executable,str(SCRIPT),'--input',str(src),
                '--prepared-output',str(dst),'--report',str(report)],capture_output=True)
            self.assertEqual(src.read_bytes(),source,'input Kernel bytes changed')
            return process, dst.read_bytes() if dst.exists() else None, json.loads(report.read_bytes()) if report.exists() else None

    def test_standalone_note_is_removed_without_changing_indented_code(self):
        source=b'import ContractTensor\n-- explanatory note\nnamespace Submission\n  def x := 1 -- inline note\nend Submission\n'
        expected=b'import ContractTensor\n\nnamespace Submission\n  def x := 1 -- inline note\nend Submission\n'
        process,prepared,report=self.invoke(source)
        self.assertEqual(process.returncode,0,process.stderr)
        self.assertEqual(prepared,expected)
        self.assertEqual(report['prepared_sha256'],hashlib.sha256(expected).hexdigest())

    def test_nested_notes_preserve_licence_crlf_unicode_and_multiline_inline_columns(self):
        licence=b'/- MIT License\r\nCopyright Example\r\nPermission notice retained.\r\n-/\r\n'
        code='theorem α : True := by /- inline\r\n     /- nested inline -/\r\n     -/ exact True.intro\r\n'.encode()
        source=b'import ContractTensor\r\n'+licence+b'/- remove\r\n  /- nested -/\r\n-/\r\n'+code
        expected=b'import ContractTensor\r\n'+licence+b'\r\n'+code
        process,prepared,report=self.invoke(source)
        self.assertEqual(process.returncode,0,process.stderr)
        self.assertEqual(prepared,expected)

    def test_unsupported_lexical_forms_fail_before_writing_any_prepared_file(self):
        examples=[b'import ContractTensor\ndef text := "keep -- text"\n',
                  'import ContractTensor\ndef «a--b» := 1\n'.encode(),
                  b'import ContractTensor\n#check `foo\n',
                  b'import ContractTensor\n/- never closed\n',
                  b'import ContractTensor\n-- invalid UTF8 \xff\n']
        for source in examples:
            with self.subTest(source=source):
                process,prepared,report=self.invoke(source)
                self.assertNotEqual(process.returncode,0)
                self.assertIsNone(prepared)
                self.assertIsNone(report)

    def test_input_and_existing_artifacts_are_never_overwritten(self):
        for mode in ['output-is-input','report-is-input','output-exists','report-exists','shared-output-report']:
            with self.subTest(mode=mode):
                TEMP_ROOT.mkdir(parents=True,exist_ok=True)
                with tempfile.TemporaryDirectory(prefix='preserve-',dir=TEMP_ROOT) as temp:
                    d=Path(temp);self.assertTrue(d.resolve().is_relative_to(TEMP_ROOT.resolve()))
                    src=d/'Kernel.lean';dst=d/'Prepared.lean';report=d/'report.json'
                    src.write_bytes(b'import ContractTensor\n-- note\n');before={src:src.read_bytes()}
                    if mode=='output-is-input':dst=src
                    if mode=='report-is-input':report=src
                    if mode=='output-exists':dst.write_bytes(b'unrelated output');before[dst]=dst.read_bytes()
                    if mode=='report-exists':report.write_bytes(b'unrelated report');before[report]=report.read_bytes()
                    if mode=='shared-output-report':report=dst
                    process=subprocess.run([sys.executable,str(SCRIPT),'--input',str(src),
                        '--prepared-output',str(dst),'--report',str(report)],capture_output=True)
                    self.assertNotEqual(process.returncode,0)
                    for path,raw in before.items():self.assertEqual(path.read_bytes(),raw)
                    for path in {dst,report}-set(before):self.assertFalse(path.exists())

    def test_report_binds_complete_input_licence_layout_and_new_unverified_bytes(self):
        licence=b'/- MIT License\nCopyright Example\n-/\n'
        source=b'import ContractTensor\n'+licence+b'-- note\n  def x := 1\n'
        expected=b'import ContractTensor\n'+licence+b'\n  def x := 1\n'
        code=b'import ContractTensor\n  def x := 1\n'
        process,prepared,report=self.invoke(source)
        self.assertEqual(process.returncode,0,process.stderr)
        self.assertEqual(prepared,expected)
        self.assertEqual(report['input_bytes'],len(source))
        self.assertEqual(report['saved_bytes'],len(source)-len(expected))
        self.assertEqual(report['code_lines_sha256'],hashlib.sha256(code).hexdigest())
        self.assertTrue(report['code_lines_byte_equal'])
        self.assertEqual(report['licence_comment_hashes'],[hashlib.sha256(licence[:-1]).hexdigest()])
        self.assertEqual(report['new_Lean_fullgate'],'NOT_RUN')

if __name__=='__main__':unittest.main()
