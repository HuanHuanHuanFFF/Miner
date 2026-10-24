# 正常结果的专门整数乘法

目标域：两原字指数均为1..254，指数和s满足128..379。其他输入保留df5c路径。此域中结果正常且有限，因此可省去通用零、次正规、溢出和最高位搜索分支。

设24位尾数乘积P，h=P>>47（0或1），t=23+h，H=2^(t−1)，q=P>>t。最近偶数舍入可写成：

`R = (P + H - 1 + (q & 1)) >> t`

输出carry为R>>24，指数为s−127+h+carry，小数为R&0x7fffff，符号取原字异或的最高位。P<2^48，故加偏置过程远小于2^64；仍须在Lean中证明无回卷、偏置舍入、指数域和实际word packing/spec链。

[有限模型](development-word-normal-model.json)完成30800项，包括648个偶平局、432个奇平局和216个进位；只有源派生整数oracle核对，没有新Lean/硬件/性能结论。本机运行约0.15秒，设5秒上限。

旧9686只把log2换成46/47，仍保留通用rounder和额外乘积域检查，完整计时更慢；这次的机制差异是直接用已知正常输出域和偏置舍入。不会因有限模型通过就重复旧版或认为必然更快。

原始[SoftFloat f32_mul](https://github.com/ucb-bar/berkeley-softfloat-3/blob/497c81c1f5016dc6ef5b3219ece2f3c261d4d8f1/source/f32_mul.c)与[roundPack](https://github.com/ucb-bar/berkeley-softfloat-3/blob/497c81c1f5016dc6ef5b3219ece2f3c261d4d8f1/source/s_roundPackToF32.c)已实际读取，作者John R. Hauser，原件和完整许可证见[来源回执](development-softfloat-source-receipt.json)。其常规路径先归一化乘积，再加舍入偏置并修复平局；新Lean路线不是直接移植其全部异常、舍入模式或异常标志接口。

固定[Lean4.34头文件](https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h)中ofBits/toBits为导出声明，UInt32转Float32为内联。消除转换调用是否有收益仍需实际目标机器码和完整调用计时确认，头文件本身不是成本读数。

最小下一步：先完成偏置RNE与正常word输出证明；用小型独立编译探针检查，再集成精确单一候选。与研究侧native缩放合并路线分别验收，不将两者收益相加。
