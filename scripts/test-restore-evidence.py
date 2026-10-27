"""Fault checks for exact-byte recovery; no contest toolchain required."""
import hashlib
import importlib.util
from pathlib import Path
import subprocess
import tempfile
import unittest

spec = importlib.util.spec_from_file_location('recovery', Path(__file__).with_name('restore-evidence.py'))
recovery = importlib.util.module_from_spec(spec)
spec.loader.exec_module(recovery)


class RecoveryTests(unittest.TestCase):
    def setUp(self):
        scratch = recovery.ROOT / '.local-maintenance' / 'recovery-tests'
        scratch.mkdir(parents=True, exist_ok=True)
        self.directory = tempfile.TemporaryDirectory(prefix='recovery-', dir=scratch)
        assert Path(self.directory.name).resolve().is_relative_to(scratch.resolve())
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        subprocess.run(['git', 'init', '-q', str(self.root)], check=True)
        self.raw = b'original\r\nbytes\x00\xff\n'
        oid = subprocess.check_output(['git', 'hash-object', '-w', '--stdin'], input=self.raw,
                                      cwd=self.root).decode().strip()
        self.entry = {'bytes': len(self.raw), 'sha256': hashlib.sha256(self.raw).hexdigest(), 'git_blob': oid}

    def test_exact_restore_and_idempotence(self):
        with recovery.GitBlobs(self.root) as blobs:
            self.assertEqual(recovery.restore(self.root, 'evidence/raw.bin', self.entry, blobs), 'restored')
            self.assertEqual(recovery.restore(self.root, 'evidence/raw.bin', self.entry, blobs), 'already_present')
        self.assertEqual((self.root / 'evidence/raw.bin').read_bytes(), self.raw)

    def test_changed_existing_file_is_preserved(self):
        target = self.root / 'changed.bin'
        target.write_bytes(b'user work')
        with recovery.GitBlobs(self.root) as blobs, self.assertRaisesRegex(ValueError, 'overwrite'):
            recovery.restore(self.root, 'changed.bin', self.entry, blobs)
        self.assertEqual(target.read_bytes(), b'user work')

    def test_bad_digest_leaves_no_output(self):
        entry = dict(self.entry, sha256='0' * 64)
        with recovery.GitBlobs(self.root) as blobs, self.assertRaisesRegex(ValueError, 'digest mismatch'):
            recovery.restore(self.root, 'bad.bin', entry, blobs)
        self.assertFalse((self.root / 'bad.bin').exists())
        self.assertFalse(list(self.root.glob('.evidence-*')))

    def test_unsafe_paths_are_rejected(self):
        for name in ('../escape', '/absolute', 'C:/absolute', 'a\\b', 'a/../b', 'a//b', '.'):
            with self.subTest(name=name), self.assertRaises(ValueError):
                recovery.destination(self.root, name)


if __name__ == '__main__':
    unittest.main()
