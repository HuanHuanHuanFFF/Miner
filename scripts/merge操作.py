"""Inspect or execute a guarded merge into main; see --help and docs/merge-operation.md."""
import argparse
import datetime as dt
import json
from pathlib import Path
import subprocess
import sys


class Stop(RuntimeError):
    pass


class Merge:
    def __init__(self, root):
        self.root = root.resolve()
        self.receipt = {"started_at": dt.datetime.now(dt.timezone(dt.timedelta(hours=8))).isoformat(),
                        "steps": [], "retained_worktrees": []}

    def git(self, *args, cwd=None, check=True):
        p = subprocess.run(["git", *args], cwd=cwd or self.root,
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if check and p.returncode:
            # Git errors may contain remote credentials; keep raw errors off receipts/logs.
            raise Stop("Git操作失败：" + args[0] + "；请在本地检查状态，未继续后续步骤。")
        return p.stdout.decode("utf-8", errors="replace").strip(), p.returncode

    def sha(self, ref):
        return self.git("rev-parse", "--verify", ref)[0]

    def ancestor(self, a, b):
        return self.git("merge-base", "--is-ancestor", a, b, check=False)[1] == 0

    def clean(self, path):
        if self.git("status", "--porcelain=v1", "--untracked-files=all", cwd=path)[0]:
            raise Stop("工作区有未提交或未跟踪文件：" + str(path))
        for marker in ("MERGE_HEAD", "CHERRY_PICK_HEAD", "REVERT_HEAD", "rebase-merge", "rebase-apply"):
            value = self.git("rev-parse", "--git-path", marker, cwd=path)[0]
            if (path / value).exists():
                raise Stop("工作区有未结束的Git操作：" + str(path))

    def worktrees(self):
        raw = self.git("worktree", "list", "--porcelain", "-z")[0]
        rows, row = [], {}
        for field in raw.split("\0"):
            if not field:
                if row:
                    rows.append(row)
                    row = {}
                continue
            k, _, v = field.partition(" ")
            row[k] = v
        if row:
            rows.append(row)
        return rows

    def refs(self, prefix):
        raw = self.git("for-each-ref", "--format=%(refname) %(objectname)", prefix)[0]
        return dict(line.split(" ", 1) for line in raw.splitlines())

    def plan(self, requested):
        local = self.refs("refs/heads/")
        remote = self.refs("refs/remotes/origin/")
        main_wt = [r for r in self.worktrees() if r.get("branch") == "refs/heads/main"]
        if len(main_wt) != 1:
            raise Stop("需要一个已登记且检出main的工作区。")
        target = Path(main_wt[0]["worktree"]).resolve()
        self.clean(target)
        names = set(k.removeprefix("refs/heads/") for k in local)
        names |= set(k.removeprefix("refs/remotes/origin/") for k in remote)
        selected = sorted(set(requested) if requested else {n for n in names if n.startswith("codex/")})
        records = []
        for name in selected:
            if not name.startswith("codex/") or name not in names:
                raise Stop("只接受存在的codex/实验分支：" + name)
            lsha, rsha = local.get("refs/heads/" + name), remote.get("refs/remotes/origin/" + name)
            if lsha and rsha and lsha != rsha:
                raise Stop("本地和远端分支不一致，先核对归属与提交：" + name)
            for row in self.worktrees():
                if row.get("branch") == "refs/heads/" + name:
                    if "locked" in row or "prunable" in row:
                        raise Stop("实验worktree被锁定或失效：" + name)
                    self.clean(Path(row["worktree"]).resolve())
            records.append({"branch": name, "local_sha": lsha, "remote_sha": rsha,
                            "tip": lsha or rsha})
        upstream = remote.get("refs/remotes/origin/main")
        main = local["refs/heads/main"]
        if upstream and not (self.ancestor(upstream, main) or self.ancestor(main, upstream)):
            raise Stop("main与origin/main分叉，先人工核对；脚本不会重置或改写历史。")
        result = {"main_worktree": str(target), "main_sha": main, "origin_main_sha": upstream,
                  "branches": records,
                  "excluded_branches": sorted(n for n in names if n not in selected and n not in ("main", "HEAD")),
                  "remote_state": "本地tracking记录；执行模式会先fetch重新核对"}
        self.receipt["plan"] = result
        return result

    def validate(self, target):
        checker = target / "scripts/project.py"
        if not checker.is_file():
            raise Stop("缺少项目检查入口scripts/project.py。")
        p = subprocess.run([sys.executable, str(checker), "check"], cwd=target,
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        self.receipt["steps"].append({"step": "project_check", "exit_code": p.returncode})
        if p.returncode:
            raise Stop("项目检查失败；已停止推送和删除，请单独运行project.py check查看问题。")

    def execute(self, requested, push, cleanup):
        self.git("fetch", "origin", "--prune")
        plan = self.plan(requested)
        target = Path(plan["main_worktree"])
        self.validate(target)
        if not plan["branches"]:
            self.receipt["status"] = "NO_BRANCHES"
            return
        if plan["origin_main_sha"] and self.ancestor(plan["main_sha"], plan["origin_main_sha"]):
            self.git("merge", "--ff-only", plan["origin_main_sha"], cwd=target)
        for row in plan["branches"]:
            if not self.ancestor(row["tip"], "main"):
                self.clean(target)
                self.git("merge", "--no-ff", row["tip"], "-m",
                         "chore: 合并实验分支 " + row["branch"] + " [skip ci]", cwd=target)
            if not self.ancestor(row["tip"], "main"):
                raise Stop("合并祖先核对失败：" + row["branch"])
            self.receipt["steps"].append({"step": "merged", **row})
        self.validate(target)
        self.clean(target)
        merged = self.sha("main")
        self.receipt["merged_main_sha"] = merged
        if not push:
            self.receipt["status"] = "MERGED_LOCAL"
            return
        self.git("push", "origin", "main:refs/heads/main")
        live = self.git("ls-remote", "--heads", "origin", "refs/heads/main")[0]
        if not live or live.split()[0] != merged:
            raise Stop("远端main未与本地一致，停止删除。")
        self.receipt["steps"].append({"step": "push_verified", "main_sha": merged})
        if cleanup:
            # Delete remote branches in one transaction guarded by exact fetched tips.
            remotes = [r for r in plan["branches"] if r["remote_sha"]]
            if remotes:
                leases = ["--force-with-lease=refs/heads/" + r["branch"] + ":" + r["remote_sha"] for r in remotes]
                deletes = [":refs/heads/" + r["branch"] for r in remotes]
                self.git("push", "--atomic", "origin", *leases, *deletes)
            for row in plan["branches"]:
                if not row["local_sha"]:
                    continue
                if self.sha("refs/heads/" + row["branch"]) != row["local_sha"]:
                    raise Stop("本地分支在执行期间变化，停止删除：" + row["branch"])
                for wt in self.worktrees():
                    if wt.get("branch") != "refs/heads/" + row["branch"]:
                        continue
                    raw_path = Path(wt["worktree"])
                    path = raw_path.resolve()
                    self.clean(path)
                    if "locked" in wt or path == target:
                        raise Stop("工作区不可清理：" + str(path))
                    self.git("switch", "--detach", row["local_sha"], cwd=path)
                    ignored = self.git("ls-files", "--others", "--ignored", "--exclude-standard", cwd=path)[0]
                    safe_path = path.is_relative_to(self.root) and not raw_path.is_symlink() and not raw_path.is_junction()
                    if safe_path:
                        safe_path = all(not parent.is_symlink() and not parent.is_junction()
                                        for parent in raw_path.parents if parent != self.root and parent.is_relative_to(self.root))
                    if ignored or not safe_path:
                        self.receipt["retained_worktrees"].append({"path": str(path), "reason": "保留忽略资料或仓库外工作区；已detach"})
                    else:
                        self.git("worktree", "remove", "--", str(path))
                # Explicit ancestry check plus -d; never force deletion.
                if not self.ancestor(row["local_sha"], "main"):
                    raise Stop("分支未合并，停止删除。")
                self.git("branch", "-d", row["branch"], cwd=target)
            remaining = self.git("ls-remote", "--heads", "origin")[0]
            for row in plan["branches"]:
                if any(line.endswith("\trefs/heads/" + row["branch"]) for line in remaining.splitlines()):
                    raise Stop("远端分支仍存在，检查是否有并发更新。")
            self.receipt["steps"].append({"step": "cleanup_verified", "branches": [r["branch"] for r in plan["branches"]]})
        self.clean(target)
        self.receipt["status"] = "PUSHED_AND_CLEANED" if cleanup else "PUSHED"


def main():
    p = argparse.ArgumentParser(description="merge操作：默认只预检；执行按需合并、检查、推送、清理。")
    p.add_argument("branches", nargs="*", help="指定codex/分支；省略时选取全部本地及tracking实验分支")
    p.add_argument("--repo", type=Path, default=Path(__file__).resolve().parents[1])
    p.add_argument("--execute", action="store_true", help="实际执行，先fetch origin；冲突或检查失败立即停止")
    p.add_argument("--push", action="store_true", help="合并检查后推送main并核对远端")
    p.add_argument("--cleanup", action="store_true", help="推送成功后安全删除所选已合并分支；需要--push")
    args = p.parse_args()
    if (args.push or args.cleanup) and not args.execute:
        p.error("--push/--cleanup需要--execute")
    if args.cleanup and not args.push:
        p.error("--cleanup需要--push")
    op = Merge(args.repo)
    code = 0
    receipt_path = None
    try:
        if args.execute:
            # Local ignored receipt: no automatic staging, credentials, or raw Git stderr.
            common = Path(op.git("rev-parse", "--git-common-dir")[0])
            if not common.is_absolute():
                common = op.root / common
            receipt_dir = common.resolve() / "merge-receipts"
            receipt_dir.mkdir(exist_ok=True)
            stamp = dt.datetime.now(dt.timezone.utc).strftime("%Y%m%dT%H%M%S%fZ")
            receipt_path = receipt_dir / (stamp + ".json")
            op.execute(args.branches, args.push, args.cleanup)
        else:
            op.plan(args.branches)
            op.receipt["status"] = "PREVIEW_ONLY"
    except (Stop, OSError) as exc:
        op.receipt["status"] = "STOPPED"
        op.receipt["error"] = str(exc) if isinstance(exc, Stop) else "本地文件或进程操作失败，请检查环境。"
        code = 1
    finally:
        if receipt_path:
            receipt_path.write_text(json.dumps(op.receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(json.dumps({**op.receipt, "receipt": str(receipt_path) if receipt_path else None}, ensure_ascii=False, indent=2))
    return code


if __name__ == "__main__":
    raise SystemExit(main())
