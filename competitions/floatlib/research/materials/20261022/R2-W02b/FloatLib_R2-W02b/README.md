# FloatLib R2-W02b

**完整四函数 Kernel 与无条件 bmm_spec 的编译候选；Lean 状态为 NOT_RUN。**

推荐先读 `REPORT_zh.md` 和 `COMPILE_REQUEST.md`。真正送入固定环境的是根目录 `Kernel.lean`，不要把诊断文件或源码片段分别当作提交。

## 关键事实

- 父本：公开 Miner commit `46a9f085db7634a22324d25623f715829f7074f9` 的 `f01-d2-final-finite/Kernel.lean`；58,079 字节，SHA256 与用户给定值一致。
- 父本前 56,956 字节逐字节保留，覆盖 add/mul/sum、相关证明及所有现有数值桥。
- 完整新 Kernel：72,509 字节，唯一 import ContractTensor；固定词法禁止项扫描包括注释，零命中。
- B 使用 batch × groups × n 的分层 Vector F4；块结果使用 batch × m × groups 的分层 Vector F4，每块只计算一次，输出 Vector.ofFn 选 lane。
- `bmm_spec` 没有外部 sound 假设；四函数证明源码齐全、没有证明占位。尚未经过 Lean elaboration 或 kernel check。
- 没有新 C timing、benchmark 脚本、工具链安装或正式提交。

## 文件

| 文件/目录 | 内容 |
| --- | --- |
| `Kernel.lean` | 完整单文件候选，包含父本原样数值桥和新 bmm 证明 |
| `parent/Kernel.lean` | 本轮从精确公开 URL 下载并核验的父本 |
| `src/` | 新增 Layout、Dot、Decode、Main 四段，用于阅读和精确重组；不是独立模块 |
| `parent-to-packed4.diff` | 相对父本的完整文本差异 |
| `REPORT_zh.md` | 中文报告和完整 Kernel 附录 |
| `COMPILE_REQUEST.md` | 固定既有环境的四函数编译、内核重放、公理检查 |
| `PROOF_DEPENDENCIES.md` | 数值桥与布局/输出证明的依赖、精确剩余验收目标 |
| `diagnostics/ProofTargets.lean` | 分离的四 obligation 与中间定理检查 |
| `diagnostics/verify_source.py` | 只读 byte/hash/词法检查，可选核对固定官方 checkout |
| `diagnostics/check_layout_trace.py` | 新布局的纯符号操作顺序诊断，不是 Float32 执行 |
| `diagnostics/*result*` / `*preflight*` | 本轮实际执行结果和原始输出 |
| `sources/` | 父本保留范围、固定公开源 URL/hash、词法规则快照 |
| `licenses/` | 父本内嵌 notice、FloatLib MIT、Lean Apache-2.0 |
| `status.json` | 源码完整性、实际诊断与各项 NOT_RUN 的机器可读状态 |
| `SHA256SUMS` | 包内完整性清单，排除清单自身 |

Kernel SHA256：

```text
be7f94691e8a93eeb6f6f704869a280714f01d9f0efca21989d3a7b6eb7136a0
```

本包独立命名为 R2-W02b；未读取或改写旧交付包。父本 gate 39656662501 通过只作为用户给定反馈保存，未访问 CI 或账户。
