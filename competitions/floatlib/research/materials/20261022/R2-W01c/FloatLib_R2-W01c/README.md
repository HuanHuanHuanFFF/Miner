# R2-W01c 研究包

先读 `FloatLib_R2-W01c_report.md`。本包交付任意 normal word 的完整 Lean 证明尝试，**所有新 Lean 结果均为 NOT_RUN**：当前环境没有 Lean/lake。文本扫描、源码哈希和独立静态复核不等于 Lean 内核通过。

## 入口

- `lean/NormalEqAttempt.lean`：44,176 bytes；完整单文件，只导入 ContractTensor。
- `lean/ReusableModel.lean`：6,266 bytes；可先验证的整数 dyadic / Model 精确乘法核心。
- `lean/components/`：拼接来源。`*.fragment.lean` 不能单独作为 module 编译。
- `diagnostics/`：重建、静态检查和已有环境中的 Lean 诊断。审计命令独立于候选。
- `results/`：本轮实际静态检查与 NOT_RUN 记录。
- `public_sources/`：公开源码原件、许可和哈希清单。
- `appendices/`：各证明接口的来源审计、静态复核说明。
- `SHA256SUMS.txt`：除该文件自身外，包内所有文件的 SHA256。

## 关键名称

`R2W01c.normal_eq` 和 `R2W01c.normal_bits` 只接收输入 `u` 与正常域条件。
`R2W01c.convert_eq` 不带 `hNormal`；它在本轮尝试的 `normal_eq` 上组合旧零/回退证明。
旧 `R2W01b.convert_eq` 保留为内部使用的条件组合引理，不要与新命名空间混淆。

这些是转换层定理，包中没有新参赛 `SumObligation` 提交、没有 gate 成功声明，也没有新性能实验。

## 重跑静态检查

```sh
python3 diagnostics/rebuild.py
python3 diagnostics/verify_static.py
python3 diagnostics/run_lean.py
```

第三条在没有现成环境时只记录 NOT_RUN。已有固定工具链和官方目录时，参阅报告第10节；程序不包含安装步骤。不要升级依赖、提高编译选项或把条件结果当作已证明。

## 一项重要源码发现

固定 pin 已有完整 `roundDyadicWithRounding_toDyadic?`，位于 `Conversion/Text/Representation.lean`。对比版本只是把同一七定理证明块挪到 Exact；本轮没有引入这项新依赖。

原 W01b 包保留，未被本包替换。
