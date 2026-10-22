# R2-W03b 交付入口

本包包含 signedScaleTable / fromBitsTable 全输入等式的完整 Lean 证明草稿。

**所有 Lean 证明均为 `WRITTEN_NOT_RUN`。** 没有 Lean 编译或官方 gate 通过证据；本地没有安装工具链。完整说明见 `R2-W03b-report.md`。

## 文件

| 文件 | 用途 |
|---|---|
| `ConversionCandidate.lean` | 单文件转换定义、34 项定理及完整许可头；只 import ContractTensor |
| `R2-W03b-report.md` | 中文完整推导、边界、反例、状态和开发建议 |
| `diagnostics/Diagnostics.lean` | 仅用于追加到临时诊断文件的 #check / #print axioms 命令 |
| `tools/run_fixed_diagnostics.py` | 使用已有固定环境检查候选与独立诊断；不安装工具 |
| `tools/check_candidate_text.py` | 有限文本检查，不能替代官方 policy |
| `verification/compile-status.json` | 本轮实际 NOT_RUN 原因 |
| `verification/definition-comparison.json` | 六个可执行定义与原版的文本一致性及旧 ZIP 身份 |
| `text-check.json` | 最终候选的文本检查、字节数、SHA256 |
| `StaticReview.md` | 独立源码/证明静态审查记录 |
| `sources/ProofDependencies.md` | 证明分层、公开 API 与移植归属 |
| `sources/declarations.json` | 34 项本地声明及候选内位置 |
| `sources/source_manifest.json` | 所核对的公开固定来源、字节数与 SHA256 |
| `LICENSES/FloatLib-LICENSE` | 两项局部移植辅助证明的 MIT 许可 |
| `LICENSES/Lean4-LICENSE` | 所引用 Lean 固定源码的许可文本 |
| `CHANGELOG.md` | 与 R2-W03 原版的具体区别 |
| `SHA256SUMS.txt` | 包内文件校验值；不包含该清单自身 |

## 在现有固定环境检查

先确认已有工程为指定三项 pin，并已具备构建好的依赖。本包不执行依赖下载或 Lake build。

```bash
python3 tools/run_fixed_diagnostics.py /absolute/path/to/pinned-project/lean --output /absolute/path/to/new/w03b-logs
```

工具将分别检查候选和候选加诊断的临时文件；原文件保持分离。查看诊断日志中的最终定理类型和公理集合，允许集合仅为 `propext`、`Classical.choice`、`Quot.sound`。之后将候选 namespace 内的定义/证明合入实际 Kernel，保留一个 `import ContractTensor`，按主定理替换旧转换，再运行原有官方 gate。

本文件不是完整 sum/bmm 提交，没有声明 Competition.SumObligation 或 BmmObligation。已有有序计算的接入证明可以使用点态 `R2W03b.fromBitsTable_eq_ofBits`，或者函数等式 `R2W03b.fromBitsTable_eq`。合并后总文件的大小和官方策略仍须检查。

诊断文件包含官方 policy 不接受的命令；不要把它粘进候选。内部文本检查的 PASS 只代表该脚本的检查成功。
