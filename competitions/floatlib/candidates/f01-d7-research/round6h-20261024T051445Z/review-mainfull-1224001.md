# 1224001 MainFull 实际取证复核

**结论：原始 artifact 的 83 个索引成员全部通过字节数与 SHA-256 核验；run、plan、候选源与采集 metadata 相互吻合。** MainFull/Submission 的 C、trace 与对象 SHA 来自本次候选 upper；BenchSuite 来自标明的共享官方 build。静态输出明确是 `PARTIAL`，最终链接二进制身份仍为 `UNKNOWN`。计时受 observer 的影响也为 `UNKNOWN`，本报告不作性能或 codegain 结论。

## Run 与 full-gate 绑定

- run `40067286343`、job `120793083777` 已终态成功，HEAD `c2d92ffb0a92888a39388145a41d1f8def38071c`；run/artifact index 的 ID、HEAD 相同，下载 artifact listing 与 index 相符。SHA index 覆盖 83 个成员，83/83 字节数和 SHA 均吻合；artifact ID `12550231236`，归档 digest `d08d8e8a…7fc9d3c3`。
- provenance 绑定官方 commit `4b7e8384…`、public-v2 suite `a16494e9…`、generator `7198464d…`、seed `1224001`、25 轮、500000 pairs，以及 plan SHA `c01a8685…`。plan 的捕获目标 6c2d 是本批次最后候选；run 输入 Kernel 为 254654B、SHA `6c2d394d…fa4277d`。R8 对照 41 也在同一 run 完整通过。
- 两个候选 verdict 都是 `passed=true, mode=gate, slot=full, stage=score`，各有 25 轮；候选/对照 verifier fingerprint 均为 `dbfba2ce…d0479`，start/end 相同。候选 `Kernel.lean` 中 `add_spec`、`mul_spec`、`sum_spec`、`bmm_spec` 均存在；gate log 依序记录 statement、kernel、axioms、score 成功，axioms 仅为 `Classical.choice`、`Quot.sound`、`propext`。
- runner 证据为 GitHub-hosted `ubuntu-24.04`、Lean 4.34.0、Python 3.12.3、x86_64；`BENCH_CPU=0`。CI 未记录可核实的 CPU 型号或 runnerName，故硬件型号为 **UNKNOWN**，不沿用历史 runner 型号。

## MainFull / 对象来源

`capture-record.json` SHA `5c6844e7…5f26fcc` 与 summary 指向的 metadata SHA 一致。其 Kernel SHA 与 run 输入相同；`lean/work/Submission.lean` 捕获前后校验都匹配 6c2d。MainFull C、object 与 trace 均来自 `.sandbox/layer/upper`，路径和来源标记为 `original-candidate-layer`：

| 产物 | 来源 | 字节数 | SHA-256 |
|---|---|---:|---|
| MainFull C | `upper/ir/MainFull.c` | 82,483 | `9e8d7b11…6873621` |
| MainFull object | `upper/ir/MainFull.c.o.export`（私有副本已删除） | 12,792 | `e1685ee1…eddee41` |
| MainFull export trace | `upper/ir/MainFull.c.o.export.trace` | 1,295 | `5f0dda41…7571e855` |
| MainFull trace | `upper/lib/lean/MainFull.trace` | 3,894 | `e5b78f1c…5ccbbc03` |
| Submission object | `upper/ir/Submission.c.o.export`（私有副本已删除） | 603,112 | `5fa32bca…c5bac524` |
| BenchSuite object | `lean/.lake/build/ir/BenchSuite.c.o.export`（共享 build） | 287,352 | `5f9647fd…edbdb374` |

Submission 的 C/trace 也来自 candidate upper。BenchSuite 的 C、object、trace 明确标为 `unchanged-shared-benchmark-module`，没有冒充候选 upper。捕获的 `benchFull.trace`/`.hash` 绑定了实际链接输入路径：`MainFull.c.o.export`、`Submission.c.o.export`、`BenchSuite.c.o.export`。这能支持构建输入路径与捕获对象的静态关联；link trace 没有保留最终 `benchFull` 二进制，所以不能声称最终执行文件的字节身份已经证明。`private_objects_removed=true`、`private_directory_removed=true`。

## 静态分析缺项与时间界限

`disassembly.state=PARTIAL`：20 个 symbol 预算已用完，NM inventory 完整且三个 object 的 nm/relocation 命令均成功；MainFull 选中的 11/11 个函数已分析。剩余 15 项未分析：BenchSuite 9 个、Submission 6 个（`add`、`mul`、`nativeMul` 及 boxed 变体），均明确记为 `symbol_budget_or_deadline`。因此不能称为四函数或完整 benchmark 路径汇编审计通过。

wrapper 自己记录的 snapshot 时间是 UTC：`05:50:47.854316` 至 `05:50:47.866179`。原始 gate stage log 时间戳没有时区，metadata 中 `emitted_at_utc=null`、`capture_vs_axioms_emission=UNKNOWN`；`snapshot_finished_before_observed_score=true` 只比较 stdout reader 到达时间，不能用来断言原始 score 事件的 UTC 先后。原始进程 exit 0、未 timeout、stdout log 完整。捕获仍可能扰动 CPU/cache，observer overhead 保持 **UNKNOWN**；该批次只能作为诊断，不能叫 clean D 或独立确认。

报告核验了原始 SHA 与 full-gate receipts，没有重算或解释性能比值。文件哈希和更细的 run/capture 结构见同目录 `review-mainfull-1224001.json`。
