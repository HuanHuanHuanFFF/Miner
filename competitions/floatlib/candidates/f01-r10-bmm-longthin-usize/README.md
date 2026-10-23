# R10：long-thin DirectSmall USize循环

精确源SHA `f278796997dc8ca584ec661ea2f253e5174b95fedbd6268e11152040ce29d736`，243876B，余12124B。独立父本仍是41，不把n1的发现样本收益叠加。

只有n>4、p≤2且n/p/两数组长度均小于USize.size时选择新core。这六项检查放在矩阵入口一次执行；每个输出转换base/count/stride，MAC循环用USize加乘和带证明的Array.uget。浮点转换、乘法后加法顺序、+0种子、终点NaN判断与原字重放不改。短n、packed及巨大Nat均回到原41。

完整证明链包括：实际row-major q/k地址界、机器加乘不回绕、uget=getD、USize循环等于原NativeFinal.dotLoop、core等于原DirectSmall、四项原规格。代码中没有把抽象bounds作为外部假设；实际矩阵入口构造它。新Lean接受仍NOT_RUN。

原41除可逆bmm/spec标识符重命名外全部保留；旧NativeFinal.dotLoop及packed共享证明未动。build.py默认只读复现，--write只允许首次创建。increment.lean是构建输入，Kernel不导入它。

静态policy、作用域与身份核对通过。bounds-screen.json只是小整数域及32/64位边界的地址模型，**不是Lean、Float32运行或性能结果**。完整gate、实际C/asm和净收益均NOT_RUN，由D决定队列和三组对照。

[研究交接](../f01-d7-research/round2h-20261023T170031Z/astra-bmm.md) · [状态与精确映射](../f01-d7-research/round2h-20261023T170031Z/astra-bmm.json)
