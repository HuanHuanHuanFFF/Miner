# 固定来源与许可

本包不复制完整父本，不改父本，也不包含新 2×4 热循环。

## 实际下载与读取

精确 URL、不可变 ref、字节数、SHA256 在 `source_manifest.json`。公开父本定位过程记录在 `parent_resolution.json`。

- [Miner 父本 Kernel.lean](https://github.com/HuanHuanHuanFFF/Miner/blob/1a2b072ef6efa83c7413624b83241e0f5fa87c00/competitions/floatlib/candidates/f01-d3-final-package/Kernel.lean)：125837 字节；SHA256 `6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7`。已实际阅读 Packed8.finish、Packed8Index 的循环/within/runDot 及其等价桥、tileResults、outputFromTiles 和 bmm 的相关定义。
- [Lean v4.34.0 Nat.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Basic.lean)：本次短证明所用的加法、乘法分配及乘法单调接口。
- [Lean v4.34.0 Nat.Lemmas](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Lemmas.lean)。
- [Lean v4.34.0 Array.Lemmas](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Lemmas.lean)：Array.size_map。
- [Lean v4.34.0 Vector.Basic](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Vector/Basic.lean)：Vector.size_toArray。
- [官方 ContractTensor.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean)。
- [官方 gate.py](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py)：只抽取词法 BANNED 表达式进行本地静态扫描，没有运行或修改官方 gate。

## 固定但本轮没有重新下载的依赖

- [FloatLib 固定 commit](https://github.com/lean-dojo/FloatLib/tree/0d91825727839f597fd06b22fdd038ea21480f0c)。没有把 FloatLib 数值桥重新声明成假设，也没有重做数值证明。父本 gate 历史来自用户反馈。

## 许可

父本文件头实际携带 Conjectures.io、FloatLib、TorchLean 的 MIT 许可及通知；这些头部通知逐字保存在 `PARENT_NOTICES.txt`。集成至原 Kernel 时保留原来的许可头。本包的 Nat 地址证明为本轮撰写，未复制第三方实现或数值内核；引用 Lean API 不复制其实现。

所核 Lean 源文件头标注 Apache 2.0。其固定许可链接为 [Lean v4.34.0 LICENSE](https://github.com/leanprover/lean4/blob/v4.34.0/LICENSE)。本包没有重分发 Lean 源码。

本轮新增的 RowPairBounds.lean、IntegrationExamples.inc.lean、报告与解析见证可按 MIT 许可使用，完整授权文本在 `LICENSE_NEW_MATERIAL.txt`。这不改变任何上游文件的许可。
