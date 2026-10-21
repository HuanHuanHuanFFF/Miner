# 环境配置验收：2026-10-21

**VERIFIED：FloatLib 官方环境和完整基线 gate 已通过。** 用户要求环境配置后停下，本会话不再修复候选或启动新运行。开发会话在自然检查点读取本报告和 [环境状态](../coordination/environment-status.json)，按自身授权接管后续工作。

## 实际执行

- [GitHub CI 39554146703](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/39554146703)：北京时间 14:13:55—14:51:12，精确源码提交 `cd2229f47e57f2ccadbbfb94c67fc8f05b2d25c1`。
- 官方提交 `978cc5b445edb9943fd9953b0a9037d97a9f33a8`；原版 setup、gate、contract、bench 未修改。
- `ubuntu-24.04`，Lean 4.34.0，Python 3.12.3，bubblewrap 0.11.2；systemd 内存限制启用，官方源码 diff 为 CLEAN。
- runner 报告 AMD EPYC 9V74，4 个逻辑 CPU，计时固定 CPU 0。这只描述本次公开 runner，正式评测 CPU 仍为 UNKNOWN。
- 冷安装和自检耗时 31 分 44 秒；依赖缓存保存成功，用于后续同版本运行。后续热缓存耗时尚未实测。
- 完整基线 gate 约 231.551 秒，通过 intake、policy、原始 statement、Lean kernel 重放、公理、round trip 及 score；12 类、25 轮配对结果齐全，开始和结束 verifier fingerprint 一致。

| 输入 | 完整 gate | 本次耗时 | 相对官方附带参考的总时间比 | 性能／线上状态 |
|---|---|---:|---:|---|
| 原版 baseline（与参考同字节） | PASS | 231.551 秒 | 1.0009522413 | 公开同源码对照；线上结果 UNKNOWN |
| 原始 f01-mul-log2 | FAIL，statement | 11.751 秒 | UNKNOWN | 性能 NOT_RUN；未正式上传 |

基线的约 0.095% 差异是本次同源码对照观测，不是优化收益。整个 CI 的 conclusion 为 `failure`，原因是原始候选被拒绝；不能把 CI 标成全绿，也不能将候选错误归为环境故障。

## 给开发会话的实际反馈

执行过的候选 SHA-256：`ac4f32a610e1e4b66141d8cb8d099411cda476ffe6c5cd821df0ede41c8158d7`。原始 verifier 在 `work/Submission.lean:645:4` 和 `:657:6` 报 `Type mismatch: After simplification, term`，终止于 statement。该输入是完整复制的原始 `Kernel.lean`，上述行号可对照 [原始候选](../candidates/f01-mul-log2/Kernel.lean)。

实际错误是类型不匹配；此前关于 `rw` 可能产生 “no goals to be solved” 的判断未被这次日志证实。官方回执只保留了压缩后的错误摘要，不能据此声称已经定位全部证明原因。

开发会话准备的 `f01-mul-log2-proof1` 未进入本次 CI；本会话没有修改或提交其未完成文件，也不声明该版本已修好。第二候选同样没有运行正式 gate。是否修复、选择哪个版本、何时重新运行，由开发会话根据自身用户授权继续。

## 回执与配置入口

- [运行元数据](../evidence/39554146703/ci-run.json)、[完整 CI 日志](../evidence/39554146703/ci.log)、[artifact 字节与 SHA-256 索引](../evidence/39554146703/original-artifact-hashes.json)。
- [环境自检](../evidence/39554146703/download-6d09073267f64a12be780cf296192bb8/environment.json)、[完整结果汇总](../evidence/39554146703/download-6d09073267f64a12be780cf296192bb8/summary.json)。
- [基线原始 verdict](../evidence/39554146703/download-6d09073267f64a12be780cf296192bb8/baseline-verdict.json)、[候选原始 verdict](../evidence/39554146703/download-6d09073267f64a12be780cf296192bb8/f01-mul-log2-verdict.json)。
- [环境使用说明](environment.md)：当前通过原有 `deflate-baseline.yml` 的 `competition=floatlib` 手动入口运行，独立 workflow 尚未在 main 登记；没有合并 main。

原始 artifact 文件保持字节不变。目录迁移的原始回执字节核对、历史路径查询和本地项目检查已通过；合并入口的 9 个隔离测试通过。本轮不涉及正式参赛提交、钱包或资金操作。
