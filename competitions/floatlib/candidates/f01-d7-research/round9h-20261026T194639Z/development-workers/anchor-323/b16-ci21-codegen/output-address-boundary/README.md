# 输出地址因果判别：仅B基址缓存为局部GO

**不是三次乘法都逐lane重复，也不全在NaN冷臂。** 对通常小Nat、地址乘积不溢出的路径：

| 计算 | 实际emit native位置 | 判别 |
|---|---|---|
| `r*n` | prologue `mul 0x28`，缓存`[rsp+0x68]@0xad` | 已每次emit一次；针对重复乘法重写是NO-GO。 |
| `bi*n` | prologue `mul 0x47`，缓存`[rsp+0x60]@0xd0` | 同样已提到lane循环外。 |
| `(bi*n)*p` | lane循环内`mul 0x182` | `bi*n≠0`时，每lane真执行；`0x17d→0x1b0`会跳过零乘积，所以不能说所有普通输出都执行它。 |
| 加`4g`、再加`j` | `0x1c6`、`0x1f4` | 在lane选择/NaN检查之前执行；前者可复用，后者随j变化。 |

实际group在relocation `0x400/0x5a8`调用已采emit/spec0。C中emit第49063行先计算三个Nat地址站点，再传Packed10.finish（第38100行）；finish只在NaN分支使用地址。**原生finish已内联到emit**：四lane在`0x36d/0x47d/0x230/0x4fd`作self-ucomiss，非NaN汇入`0x376`，relocation`0x377`直接调to_bits，之后push并在`0x3d8→0xf0`继续下一lane；NaN才在`0x486`之后走replayLoop，call`0x4bb`、relocation`0x4bc`。因此剩余B基址工作是严格求值造成的普通输出热工作，不是仅raw replay的冷工作。

**最小后续改法（未写源）：** 在group的`let v := runDot ...`之后、RowStream.emit之前，绑定一次`baseB := bi.val*n*p+4*g.val`；callback将`baseB+j.val`传给**原样**Packed10.finish。只改这一共享点，保留lane结果选择、NaN判断和原字回放顺序，不加新hot helper/noinline或懒求值closure。r*n让现有native CSE处理即可。合法selected Fin group至少一个输出；当前这些B地址计算已在有限值路径执行，缓存一次不会把原本仅NaN触发的工作提前。

新增/改变成本须保留：baseB Nat值存活到最多4次emit结束；小Nat是tagged immediate，大Nat的构造/引用/释放周期仍要计。捕获参数由bi/4g等转成baseB，编译器可能继续专化为普通参数，也可能保留新closure或增加寄存器/栈压力，不能预先写零。raw A/B、F4、finish、输出/校验/析构生命周期不变。大Nat/overflow臂仍有逐lane helper，以上普通CSE结论不涵盖它们。

GO仅表示一个明确的后续实现机会，不是完整D/速度/收益建议，也不保证batch1（bi=0）收益。无Nat乘法计数→耗时换算。D22源、输入和结果完全未触碰；无源码生成、Git/CI/Lean或新运行。精确C/ASM引用、逐边指令/relocation及哈希在review.json、native-evidence.json和receipt.json；本次未重复数学或全130原件复核。
