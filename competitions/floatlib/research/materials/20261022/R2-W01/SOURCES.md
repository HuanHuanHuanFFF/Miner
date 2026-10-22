# 一手来源清单

本研究的源文件均在给定固定版本读取；完整文件级 SHA256 与 Git blob 核对结果见 sources_manifest.json。该清单记录阅读过的公共源码，不把整个依赖库放进交付包。

## 固定比赛仓库

- [ContractTensor.lean：sum/bmm 定义与全域 obligation](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean)
- [Contract.lean：Binary32 与公开 imports](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/Contract.lean)
- [BenchTensor.lean：三个 sum 生成器、ReLU odd fraction、n=1000](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean)
- [BenchBmm.lean：n=100，ReLU A / dense B](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchBmm.lean)
- [lakefile.lean：固定 FloatLib revision](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/lakefile.lean)
- [lean-toolchain：Lean v4.34.0](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/lean-toolchain)

## 固定 FloatLib revision

- [ExecFloat/Proof/Arithmetic.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Proof/Arithmetic.lean)
- [Arithmetic/Semantics.lean：finite add / roundAt 桥](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean)
- [Rounding/Proof.lean：dyadic、nearestEven、roundAt](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean)
- [ModelRounding/Proof.lean：normal/subnormal target exponent](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean)
- [Conversion/Text/Representation.lean：有限非零实值等式恢复全位相等](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean)
- [Configured/Instances.lean：toModel_inj](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Instances.lean)

## 固定 Lean tag

- [Float32 包装、ofBits/toBits/isFinite](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean)
- [Float32.Model 与 NaN 规范化](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean)
- [UnpackedFloat.isFinite](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Operations/Status.lean)

## 背景一手文献

- [George–Adkisson–Anandkumar, FloatLib: Verified Floating-Point Arithmetic in Lean](https://arxiv.org/html/2609.19352v1)：解释 encoded equality 与 real rounding 的区别。具体 API 以固定源码为准。
- [Ogita–Rump–Oishi, Accurate Sum and Dot Product](https://www.tuhh.de/ti3/paper/rump/OgRuOi05.pdf)：EFT/高精度求和背景；不把其目标等同 ordered RN。
- [Lean v4.34.0 官方 release notes](https://lean-lang.org/doc/reference/latest/releases/v4.34.0/)：版本背景，未据此改动工具链。

所有反例、转移摘要、odd 证书、固定锚点构造和本地统计为本轮自造推导/实验。没有以公开材料中的性能数据代替本任务计时。
