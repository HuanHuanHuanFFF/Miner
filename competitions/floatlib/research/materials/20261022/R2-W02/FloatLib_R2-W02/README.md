# FloatLib R2-W02 — Packed4 窄候选

推荐只测一条机制：A 一次转换；B 直接转换并打包为四 Float32 字段对象，顺序 `[batch][columnBlock][k]`；四个独立递归累加器交错执行。每个输出仍从 +0 开始按 k 顺序乘后加，最终非有限时使用原始输入精确回退。

**交付状态：候选与结构证明均待 Lean 编译。没有完整 bmm_spec，没有性能结论，不是可直接被 gate 接受的提交。** 本轮未安装工具链。

## 先读

- `REPORT_zh.md`：中文研究报告，包含完整候选与结构证明附录。
- `RUN_REQUEST.md`：真实已准备环境中的 codegen、边界诊断、原 benchmark 完整调用对照与最终 gate 步骤。
- `diagnostics/status.json`：每个证据项的 RUN/NOT_RUN 状态。

## 文件

| 路径 | 用途 |
| --- | --- |
| `candidate/Kernel.lean` | 4,525 字节，唯一 import ContractTensor，暴露 Submission.bmm；没有 bmm_spec |
| `candidate/NativePacked4.lean` | 同一实现的带注释原稿 |
| `proof/ProofAppend.lean` | 投影、顺序 fold、map/default、finish 条件桥与 push 长度的证明源码；没有证明占位；未编译 |
| `codegen/Packed4CodegenProbe.lean` | 独立参数/结构状态/普通 Array 的小型 codegen 对照 |
| `codegen/run_codegen_probe.sh` | 要求真实已安装 4.34.0 bin，拒绝普通 elan shim，不安装依赖 |
| `diagnostics/NumericCheckAppend.lean` | 17 个原始字边界用例，尚未执行，只能用于外部诊断 |
| `diagnostics/compare_bench.py` | 直接比较两个原 benchBmm 二进制；25 轮，默认完整工作量；未执行真实计时 |
| `diagnostics/diagnose_layout.py` | 已执行的有限 RN32 与布局小诊断，结果和 stdout 同目录 |
| `diagnostics/check_kernel.py` | 只读固定文件 hash 和词法策略检查，不证明 Lean 正确性 |
| `diagnostics/cost_model.py` | 默认形状次数推导，不是计时 |
| `sources/` | 50 条固定源码 URL/hash，11 个 workspace 保护文件 hash |
| `licenses/` | FloatLib MIT 与 Lean Apache-2.0 许可文本 |
| `SHA256SUMS` | 包内文件完整性清单，排除清单自身 |

## 第一个实际入口

从本包目录运行；三个路径都应替换成真实路径：

```bash
bash codegen/run_codegen_probe.sh \
  /absolute/competition/lean /absolute/r2w02-codegen \
  /absolute/lean-4.34.0/bin
```

指定 workspace 必须已经固定为要求的公开版本，ContractTensor 与依赖已构建。脚本输出在外部目录，不改固定源码。实际生成 C 或证明 elaboration 的失败应原样保存。

**注意：固定版本的 gate --bench 仍构建 VerifyBmm；本候选当前不能用该模式计时。** 直接构建和比较原 benchBmm 的具体方法见 RUN_REQUEST；该诊断不会被报告为完整 gate 或晋升结论。

已执行的 Python 检查覆盖 720 个形状、4,860 个有限输出和 10,000 个任意精度索引等式，不模拟 FloatLib NaN payload 语义。NaN/native 编译/汇编/正式计时/完整证明均未运行。
