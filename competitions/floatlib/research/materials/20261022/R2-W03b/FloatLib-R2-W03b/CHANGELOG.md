# R2-W03 → R2-W03b 变更说明

## 原件身份

上一轮 `FloatLib-R2-W03.zip` 未修改。

```text
8f95ae0e11a52e606bca05bf1cf005c238a73122a535fb2f39cff806dddfe1ea  FloatLib-R2-W03.zip
```

本轮单独交付 `FloatLib-R2-W03b.zip`，不覆盖旧报告、旧候选、旧 JSON 或旧 ZIP。

## 可执行定义

- 只保留 signedScaleTable 机制，移入 R2W03b namespace。
- zero32、exponent、mantissa、512 项 Array.ofFn、table.getD、raw +0 分支和 E=24..254 守卫保持原定义。
- 没有扩展低指数、subnormal、负零、Inf 或 NaN 的快路。
- 没有修改表类型、索引布局、sum 顺序或 bmm 输出布局。

## 新证明

- 原 `ConversionObligation` 只描述目标；本轮新增完整主定理正文及全称/函数相等形式。
- 增加 UInt32 字段到 Nat 的分解、24 位 M 精确转换、raw normal 解码、signed scale 解码。
- 将公开 roundWithAccuracy 桥的指数条件显式证明后传入，随后调用精确移位引理。
- 增加真实常量表的界内 lookup 证明，不再留下 table 内容待证项。
- 对 raw+0、guarded、fallback 分支完成全输入合成。

## 交付卫生与许可

- 候选与 #check / #print axioms 诊断彻底分离。
- 候选注释避开官方 raw-text 规则中的禁止形式；文本检查不冒充官方 gate。
- 两项 private helper 以 MIT 归属局部移植，单文件内保留完整许可。
- 使用全限定定义名称、显式常数位宽、simp 的依赖重写，并移除潜在多余 rfl。

## 验证与性能

- Lean 编译与诊断均 NOT_RUN；本地缺少 lake，未安装工具链。
- 运行的只有文件/文本诊断和打包完整性验证。
- 不重跑任何 C surrogate；不增加新的 C/Lean 耗时或速度比结论。
- 不声称已把候选并入真实 Kernel 或通过官方 gate。
