# 29d09f的实际caller证伪表

只约束将来的实际C/ASM/成本解释；当前新源仍NOT_RUN，不以语义界推出编译器删检查。

| 对照 | 真正可能删除 | 新增或仍在 |
|---|---|---|
| R18 UInt64→F32→UInt64 | unsigned64反向的2^63补偿、双cvtt/subss等 | UInt64前向仍在；新增F32×2^-23和常量访问；U32的0/2^32/NaN相关选择须实看 |
| R19 Jam17 b271（已完整D负） | jam fixedshift/lowmask/sticky flag/OR，以及高位提取尺度差异 | 新FPmul依赖链，更宽前向转换；同类U32 reverse上界夹断仍可能保留。不能把Jam17遗忘后只挑旧U64逆转换作对照 |
| R19 DirectBias7489（诊断无稳定强收益） | 不存在简单指令包含关系；其整数偏置/变移位换成FP舍入链 | 7489已无FP/call而未见强收益，因此“更少cast”本身不足以继续扩大证明投入 |

核对完整guardedMul成功路径及原B2 fallback，不仅导出normalCore。powNeg23必须区分module初始化/once冷路/once热读；若scale来自不透明的cached Float32，编译器可能不知道其正/有限，reverse的下界/NaN分支不能靠数学界宣称消失。实际是否重新出现需回执，不预判。

须保存真实P乘法次数、UInt64前向conversion、FPscale multiply、U32 reverse、每个clamp、call/relocation、frame/save/spill、常量首次初始化与热访问。原B2前缀和官方4入口仍原字节，当前probe即使全通过也不提供新publicMULspec或性能。正式#336只绑定原B2，不能继承给新源。

Math桥5568B中scaled_decode确实走已有Model.mul exact-value及native_mul_eq接口，没有Float64跨宽假设；UInt32cast证明体逐字复用。但其Lean/allowedaxioms/kernelreplay尚未运行，P→decode、字段/guard→mul_spec也没有组合。成本不足即停放该精确runtime，不因证明草稿完整追seed。
