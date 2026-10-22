# 来源与许可说明

本轮辅助矩阵证明与包装为新写片段，不包含完整公开父本，也不包含用户另一路的机器字循环实现。

父本固定地址：
https://github.com/HuanHuanHuanFFF/Miner/blob/9fa0c60d8d5589d58b3152202adac2df444ec5e2/competitions/floatlib/candidates/f01-d2-web-packed4-proof1/Kernel.lean

本轮实际核对其 72,452 字节与 SHA256 bb1f783fd3103fba89e1e072459d7fdcff9ffdb5edc3e2983b39f1eafced2f18。实际 Kernel 应继续保留父本自带 Conjectures / FloatLib / TorchLean 等来源与许可 notice。

Lean v4.34.0 标准库用于核对 API；其 Apache-2.0 许可见：
https://github.com/leanprover/lean4/blob/v4.34.0/LICENSE

FloatLib 固定版本按任务保持 0d91825727839f597fd06b22fdd038ea21480f0c；本轮没有改动或复制其数值运算实现。其许可见：
https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/LICENSE

source_manifest.json 只列本轮实际下载并散列的 10 个公开文件。依赖的真实 within / within_eq 由用户本轮给出接口，源文件不在本包中；不得将该依赖状态记为本轮已核实现或已编译。
