"""Integration tests against disposable local bare remotes, never the real origin."""
import json
import importlib.util
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SCRIPT = ROOT / "scripts/merge操作.py"


class MergeTests(unittest.TestCase):
    def setUp(self):
        scratch = ROOT / ".runtime"
        scratch.mkdir(exist_ok=True)
        self.temp = tempfile.TemporaryDirectory(prefix="merge-test-", dir=scratch)
        self.base = Path(self.temp.name).resolve()
        assert self.base.is_relative_to(scratch.resolve())
        self.remote = self.base / "remote.git"
        self.repo = self.base / "repo"
        self.repo.mkdir()
        self.git("init", "--bare", str(self.remote))
        self.git("init", "-b", "main")
        self.git("config", "user.name", "Merge Test")
        self.git("config", "user.email", "merge-test@example.invalid")
        (self.repo / "scripts").mkdir()
        (self.repo / "scripts/project.py").write_text("raise SystemExit(0)\n")
        (self.repo / "base.txt").write_text("base\n")
        (self.repo / ".gitignore").write_text("ignored.txt\n")
        self.git("add", ".")
        self.git("commit", "-m", "base")
        self.git("remote", "add", "origin", str(self.remote))
        self.git("push", "-u", "origin", "main")

    def tearDown(self):
        self.temp.cleanup()

    def git(self, *args, cwd=None):
        p = subprocess.run(["git", *args], cwd=cwd or self.repo, capture_output=True)
        if p.returncode:
            raise AssertionError(p.stderr.decode(errors="replace"))
        return p.stdout.decode().strip()

    def branch(self, name="codex/test", file="candidate.txt", content="candidate\n"):
        self.git("switch", "-c", name)
        (self.repo / file).write_text(content)
        self.git("add", file)
        self.git("commit", "-m", name)
        tip = self.git("rev-parse", "HEAD")
        self.git("push", "-u", "origin", name)
        self.git("switch", "main")
        return tip

    def run_merge(self, *args, expected=0):
        p = subprocess.run([sys.executable, str(SCRIPT), "--repo", str(self.repo), *args], capture_output=True)
        self.assertEqual(p.returncode, expected, p.stdout.decode(errors="replace") + p.stderr.decode(errors="replace"))
        return json.loads(p.stdout.decode())

    def test_preview_and_complete_merge_preserve_main_commit(self):
        tip = self.branch()
        (self.repo / "main-only.txt").write_text("unpublished main work\n")
        self.git("add", ".")
        self.git("commit", "-m", "main work")
        main_before = self.git("rev-parse", "HEAD")
        result = self.run_merge()
        self.assertEqual(result["status"], "PREVIEW_ONLY")
        self.assertEqual(self.git("rev-parse", "HEAD"), main_before)
        result = self.run_merge("--execute", "--push", "--cleanup")
        self.assertEqual(result["status"], "PUSHED_AND_CLEANED")
        self.git("merge-base", "--is-ancestor", tip, "main")
        self.git("merge-base", "--is-ancestor", main_before, "main")
        self.assertEqual(self.git("branch", "--format=%(refname)"), "refs/heads/main")
        self.assertNotIn("codex/test", self.git("ls-remote", "--heads", "origin"))
        self.assertEqual(self.git("rev-parse", "main"), self.git("rev-parse", "origin/main"))

    def test_dirty_worktree_stops_before_merge(self):
        self.branch()
        before = self.git("rev-parse", "main")
        (self.repo / "user.txt").write_text("keep me")
        result = self.run_merge("--execute", "--push", "--cleanup", expected=1)
        self.assertEqual(result["status"], "STOPPED")
        self.assertEqual(self.git("rev-parse", "main"), before)
        self.assertEqual((self.repo / "user.txt").read_text(), "keep me")

    def test_conflict_keeps_branches_and_remote(self):
        self.branch(file="base.txt", content="candidate change\n")
        (self.repo / "base.txt").write_text("main change\n")
        self.git("add", ".")
        self.git("commit", "-m", "conflicting main")
        remote_before = self.git("ls-remote", "--heads", "origin")
        result = self.run_merge("--execute", "--push", "--cleanup", expected=1)
        self.assertEqual(result["status"], "STOPPED")
        self.assertTrue((self.repo / ".git/MERGE_HEAD").exists())
        self.assertEqual(self.git("ls-remote", "--heads", "origin"), remote_before)
        self.assertIn("codex/test", self.git("branch", "--format=%(refname)"))

    def test_mismatched_local_remote_stops(self):
        self.branch()
        self.git("switch", "codex/test")
        (self.repo / "candidate.txt").write_text("not pushed\n")
        self.git("add", ".")
        self.git("commit", "-m", "unpublished change")
        self.git("switch", "main")
        result = self.run_merge("--execute", "--push", "--cleanup", expected=1)
        self.assertIn("不一致", result["error"])

    def test_validation_failure_prevents_push_and_delete(self):
        self.branch(file="scripts/project.py", content="raise SystemExit(1)\n")
        remote_before = self.git("ls-remote", "--heads", "origin")
        result = self.run_merge("--execute", "--push", "--cleanup", expected=1)
        self.assertIn("项目检查失败", result["error"])
        self.assertEqual(self.git("ls-remote", "--heads", "origin"), remote_before)
        self.assertIn("codex/test", self.git("branch", "--format=%(refname)"))

    def test_ignored_material_keeps_detached_worktree(self):
        self.branch()
        wt = self.repo / "extra-worktree"
        # Keep the nested worktree outside status reporting without changing committed files.
        with (self.repo / ".git/info/exclude").open("a") as f:
            f.write("extra-worktree/\n")
        self.git("worktree", "add", str(wt), "codex/test")
        (wt / "ignored.txt").write_text("private local material")
        result = self.run_merge("--execute", "--push", "--cleanup")
        self.assertEqual(len(result["retained_worktrees"]), 1)
        self.assertEqual((wt / "ignored.txt").read_text(), "private local material")
        self.assertIn("detached", self.git("worktree", "list", "--porcelain"))
        self.assertNotIn("codex/test", self.git("branch", "--format=%(refname)"))

    def test_clean_worktree_removed_and_other_branch_preserved(self):
        self.branch()
        self.git("branch", "user/keep")
        wt = self.repo / "extra-worktree"
        with (self.repo / ".git/info/exclude").open("a") as f:
            f.write("extra-worktree/\n")
        self.git("worktree", "add", str(wt), "codex/test")
        result = self.run_merge("--execute", "--push", "--cleanup")
        self.assertFalse(wt.exists())
        self.assertEqual(result["retained_worktrees"], [])
        self.assertIn("user/keep", result["plan"]["excluded_branches"])
        self.assertIn("user/keep", self.git("branch", "--format=%(refname)"))

    def test_remote_only_branch(self):
        tip = self.branch()
        self.git("branch", "-D", "codex/test")  # Disposable fixture, not cleanup under test.
        result = self.run_merge("--execute", "--push", "--cleanup")
        self.assertIsNone(result["plan"]["branches"][0]["local_sha"])
        self.git("merge-base", "--is-ancestor", tip, "main")
        self.assertNotIn("codex/test", self.git("ls-remote", "--heads", "origin"))

    def test_remote_race_blocks_deletion(self):
        self.branch()
        spec = importlib.util.spec_from_file_location("merge_operation", SCRIPT)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        original_git = mod.Merge.git
        fixture = self

        class ConcurrentMerge(mod.Merge):
            def git(self, *args, **kwargs):
                if args[:2] == ("push", "--atomic"):
                    # A collaborator adds a commit after main push, before cleanup.
                    fixture.git("commit", "--allow-empty", "-m", "concurrent branch work")
                    fixture.git("push", "origin", "HEAD:refs/heads/codex/test")
                return original_git(self, *args, **kwargs)

        operation = ConcurrentMerge(self.repo)
        with self.assertRaises(mod.Stop):
            operation.execute([], True, True)
        self.assertIn("codex/test", self.git("ls-remote", "--heads", "origin"))
        self.assertIn("codex/test", self.git("branch", "--format=%(refname)"))


if __name__ == "__main__":
    unittest.main()
