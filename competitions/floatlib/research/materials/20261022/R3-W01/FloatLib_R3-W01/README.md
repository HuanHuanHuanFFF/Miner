# FloatLib R3-W01：整次 bmm 的机器字准入

本包只补外围矩阵地址界和一次准入包装。**Lean elaboration、内核检查、公理输出、实际 word loop 执行与计时均为 NOT_RUN。** 没有安装工具链，没有正式提交，没有实现或改写 within。

## 文件

| 文件 | 用途 |
| --- | --- |
| `src/MatrixBounds.lean` | 90 行纯地址证明；唯一 import ContractTensor，可在已有合同环境单独检查 |
| `src/WholeCall.inc.lean` | 完整 tile/core 包装与 bmmOnce 规格连接；依赖用户现有 within / within_eq |
| `Packed4WholeCallFragment.inc.lean` | 上两份拼接、删除重复 import 的直接插入版；9,758 字节 |
| `REPORT_zh.md` | 中文数学、边界与证据说明，并包含完整插入片段 |
| `INTEGRATION.md` | 精确接口、命名空间、最小编译与实际入口集成边界 |
| `diagnostics/` | 独立 Lean 检查命令片段、整数诊断、实际结果和审阅记录 |
| `sources/` | 固定公开父本和标准库 URL/hash、来源说明 |
| `SHA256SUMS` | 包内完整性清单，不含自身 |

## 重要依赖边界

公开父本 SHA256：

```text
bb1f783fd3103fba89e1e072459d7fdcff9ffdb5edc3e2983b39f1eafced2f18
```

本轮读到的父本为 72,452 字节，未复制进 ZIP。该父本没有用户另一路正在验收的 within / within_eq。插入片段引用实际声明 `Submission.Packed4.within` 与 `Submission.Packed4.within_eq`；若开发侧名称不同，只对齐这两处全名。没有附加替身实现、数学公理或 sound 参数。

`bmmOnce` 是并列诊断入口，便于直接检查新路径的无条件规格。仅追加本片段不会改变已有 `Submission.bmm`；不能将仍检查旧入口的 VerifyFull 结果当成新入口通过。生产集成说明见 INTEGRATION.md。

组合插入片段 SHA256：

```text
a84ced5d975f7caed47d3b9126f284b726815f81cccd268ef065b51de0dd981f
```
