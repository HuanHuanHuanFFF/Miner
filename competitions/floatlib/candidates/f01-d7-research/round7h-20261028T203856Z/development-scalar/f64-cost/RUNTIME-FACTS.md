# 固定runtime核实：FloatArray getter与boxing

UTC2026-10-28T21:55:11Z。在线读取Lean4.34官方`src/include/lean/lean.h`，Git blob `910ecae72a7d1c149d4ccc8111ee438c8b4551dd`；与仓库已有`round1h-20261023T110107Z/runtime-boundary/lean.h.raw`逐字相同。现已重新算原文件136786B、SHA256`982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13`，没有重复下载/修改旧文件。

- **FloatArray.get!不是必然的外部函数call**：header1251的`lean_float_array_get`为static inline，先查index标记和array size再读double。1243/1247的uget/fget同为static inline，前者直接连续double load，后者先unbox Nat索引。生成C出现prototype不能据此宣称真实FFI call。实际内联/分支是否消失仍看新C/ASM。
- **Array Float与FloatArray布局确有差异**：header2997的`lean_box_float`分配一个含double的对象；generic Array存其指针，取值再`lean_unbox_float`。FloatArray的data为连续double，避免这层value对象读取。header3007的`lean_box_float32`同样分配含float的对象；不能把Float32值boxing误当UInt32 immediate。两表的初始化/分配本包都在进程墙钟范围，但共享binary的control也会初始化它们，不能据此估计最终独立包的启动收益。
- **UInt32 scalar callback boxing在64位不分配**：2955/2967在64位分支只是lean_box/lean_unbox immediate，32位才分配/读constructor。故F7/F90 actual public boxed wrapper中出现box_uint32/dec，不能直接推断每调用heap allocation或大RC成本。其真实CPU份额仍UNKNOWN。

原型08a使用get!，仍有合法边界检查；它先测试真实全路径成本，不偷偷更改已冻结源码。若实际getter检查成为可区分瓶颈，可用global512长度证明＋既有R2 index<512引理改fget；这种新源需另测，不能把header可能省下的分支直接当收益。

一手：[Lean4.34 lean.h](https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h)、[FloatArray公共API](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/FloatArray/Basic.lean)。本文件是固定源码事实，不是新candidate的代码生成或性能验收。
