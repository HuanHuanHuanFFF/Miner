# FloatLib R4-W01

本包仅提供 2 行 × 4 列组织的反方审查与地址辅助证明。不是完整新候选，没有实现热循环，也没有修改公开父本。

先阅读 `FloatLib_R4-W01_Report_zh.md`。

- `RowPairBounds.lean`：唯一 `import ContractTensor`，20 个 Nat 地址定理，带完整证明体。
- `IntegrationExamples.inc.lean`：追加到上述文件后的两个数组长度接线示例；不是独立模块。
- `diagnostics/AddressChecks.inc.lean`：只用于临时诊断文件，不能复制进候选。
- `diagnostics/witnesses.json`：17 个解析完整调用输入；NaN payload 的精确预期必须由原始软件参考生成。
- `diagnostics/counts_result.json`：已执行的整数计数结果，不是机器指令或性能结果。
- `diagnostics/environment.json`、`static_preflight.json`：实际环境与词法扫描记录。
- `review/`：独立数学、反方和计数审查原件。
- `sources/`：固定源 SHA、许可和公开父本定位。
- `SHA256SUMS`：除自身外的包内文件 SHA256。

Lean elaboration、内核/公理检查、新候选执行和计时均为 **NOT_RUN**。当前环境没有 lean/lake/elan，未安装工具链。辅助证明没有占位体，但静态阅读不能冒充编译通过。

在已有固定官方环境中：

```bash
lake env lean /absolute/path/FloatLib_R4-W01/RowPairBounds.lean
cat /absolute/path/FloatLib_R4-W01/RowPairBounds.lean /absolute/path/FloatLib_R4-W01/IntegrationExamples.inc.lean > /tmp/R4W01AddressExamples.lean
lake env lean /tmp/R4W01AddressExamples.lean
cat /absolute/path/FloatLib_R4-W01/RowPairBounds.lean /absolute/path/FloatLib_R4-W01/diagnostics/AddressChecks.inc.lean > /tmp/R4W01AddressAxioms.lean
lake env lean /tmp/R4W01AddressAxioms.lean
```

集成时把 namespace 内容加入原单文件 Kernel；保留唯一原 import 与原许可头。不要引入辅助文件 import，不改工具链或官方 gate。新 Kernel 的总字节上限和三允许公理仍须由原官方流程检查。本轮没有正式提交。
