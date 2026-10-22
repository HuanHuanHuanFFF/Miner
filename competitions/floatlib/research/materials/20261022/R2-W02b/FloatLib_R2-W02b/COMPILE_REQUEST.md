# R2-W02b 最小编译与正确性验收请求

本轮只解决完整正确性。已有环境中执行下面的步骤；不安装工具链、不更新依赖、不修改编译选项，不运行计时。

## 前提

- 官方仓库固定为 `978cc5b445edb9943fd9953b0a9037d97a9f33a8`。
- FloatLib 固定为 `0d91825727839f597fd06b22fdd038ea21480f0c`。
- 已有真实 Lean 4.34.0 工具链、依赖和 ContractTensor 构建结果。
- 使用明确的隔离开发 checkout。下面只替换该隔离目录中的候选 `lean/work/Submission.lean`；原 gate、verifier、bench、lakefile、toolchain 和依赖保持原样。
- `/absolute/lean-4.34.0/bin` 指真实安装目录，不能用普通 elan shim 目录代替；若缺少工具，记为 NOT_RUN，不安装。

## 1. 只读预检

在本包目录运行：

```bash
python3 diagnostics/verify_source.py /absolute/official-isolated
/absolute/lean-4.34.0/bin/lean --version
```

预检验证父本 SHA、56,956 字节保护前缀、完整候选 SHA、源码片段重组、包括注释在内的固定词法规则，以及固定 workspace 文件 hash。它不是 Lean 接受证明。

## 2. 正常 Lake 构建四函数 verifier

```bash
cp /absolute/FloatLib_R2-W02b/Kernel.lean \
  /absolute/official-isolated/lean/work/Submission.lean
cd /absolute/official-isolated/lean
/absolute/lean-4.34.0/bin/lake build VerifyFull
```

使用原 `VerifyFull.lean`，它同时要求 `Submission.add_spec`、`mul_spec`、`sum_spec`、`bmm_spec` 满足固定的四个 obligation。保存完整 stdout/stderr、退出码和本次 Kernel SHA。

不添加编译参数，不通过更换 verifier、添加证明占位或扩大合同来消除报错。本轮候选没有新增 set_option；如 elaboration 资源耗尽，保留原错误作为反馈。

## 3. 内核重放与单独诊断

在同一已准备环境，使用其已有 leanchecker：

```bash
/absolute/lean-4.34.0/bin/lake env leanchecker Submission
/absolute/lean-4.34.0/bin/lake env leanchecker VerifyFull
/absolute/lean-4.34.0/bin/lake env /absolute/lean-4.34.0/bin/lean \
  /absolute/FloatLib_R2-W02b/diagnostics/ProofTargets.lean
```

若现有环境没有 leanchecker，记录缺失；不要安装或替换工具链。独立 `ProofTargets.lean` 检查四函数 obligation 和关键中间定理，并打印最终定理公理；它含诊断命令，不能并入候选 Kernel。

打印结果的公理集合必须是 `{propext, Classical.choice, Quot.sound}` 的子集。普通构建成功和词法检查都不能替代这项验收。

## 4. 接收标准与回收件

需要回收：固定源 hash、候选 hash、真实 Lean 版本、正常 Lake 构建日志、leanchecker 结果、最终公理列表。成功状态分别记录，不合并成一句“通过”。本轮交付没有原生编译、完整 gate 或时间数据。

若编译失败，首个错误连同完整未解 Lean 目标是下一轮修复依据。优先按以下依赖顺序定位：

1. `vector_get_ofFn` / `nativeA_getD`：标准库接口或默认值归约。
2. `packB_lane` / `dot4_lane`：布局读取或递归投影。
3. `tile_finish` / `outputFromTiles_eq`：B 地址和列分解。
4. `core_eq_reference` / `bmm_spec`：输出外延和父本 obligation 连接。

源码没有待用户补入的数学 sound 前提；未执行 Lean 意味着这些完整证明体仍需编译器验收。没有计划修改现有 benchmark 请求或启动正式参赛提交。
