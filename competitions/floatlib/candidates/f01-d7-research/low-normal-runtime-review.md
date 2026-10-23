# 353d 低 normal 求和解码候选独立源审查

2026-10-23 00:41:31 UTC开始，最多35分钟。只读R检查点22、builder/lineage、精确候选/父本和已回收公开原件；只写本报告及同名JSON。未执行builder、Lean、CI、上传、目标对象或微基准。原窗口04:22:17、源码冻结02:45不变。

**未发现确定静态错误。实际两类求和循环都接到新decoder，原NaN结果回放完整保留；独立逆变换逐字节恢复c760父本。精确新候选的Lean/公理/完整gate/C和性能仍NOT_RUN，gain UNKNOWN。**

## 身份与独立逆变换

- [候选Kernel](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r7-low-normal-sum-decode/Kernel.lean)：174914字节，`353d9816425d92fbc6d0cc14c9d30e17fb64d6d4fb7ebdf594700ef02c417c2a`。
- [父本Kernel](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r7-nonnan-runtime/Kernel.lean)：153390字节，`c76056882d69a1122da44b4bc0bb3ab5274251826f0677af2aec5771926d7435`。

未运行R的builder。本审查独立对两源做逐行对齐，只有三条非相同区间：

| 差异 | 父本行 | 新候选行 | 内容 |
|---|---:|---:|---|
| 插入 | 3345后 | 3346–3855 | 510行、21504字节新声明，块SHA `b842d6c21b621f91b4525d7ce4ad7b7f1d7c92469a73ba5fadbf3508469c4fea` |
| 替换 | 3350 | 3860 | `decode` 从 `R2W01b.convert` 改为 `R7LowTableDecode.convert` |
| 替换 | 3354 | 3864 | `decode_eq`重写引理从 `R2W01c.convert_eq` 改为 `R7LowTableDecode.convert_eq` |

反向应用这三个区间得到父本完整字节及c760哈希。另独立切片核对：`NativeDecodeSumWord`模块1689字节、最终`Submission.sum/sum_spec`块527字节、随后全部RowOutput/RowStream/BMM源5821字节均与父本相同。原前缀中的add/mul及已有reference/native算法也逐字保留。这里的“相同”指源字节，不能推广为生成C/对象布局、初始化成本或机器码相同。

## 实际调用与边界

实际调用链为 `Submission.sum`（3937）→ `NativeDecodeSumWord.run`（3919）→ USize `loop`（3890）或大维度Nat后备 → `NativeDecodeSum.decode`（3860）→ `R7LowTableDecode.convert`（3838）。Nat `NativeDecodeSum.loop`第3869行同样调用该decoder，未遗漏后备路线。

USize循环仍取 `x.toArray.uget k`，`count.toNat=n`、读数组界、`Packed10Index.next_decreases/stepNat`以及`n<USize.size`入口判断均为原字节。`k<count`时下一步不跨USize上界；`n≥USize.size`仍走原Nat循环。n=0直接返回原+0 seed，没有新维度/工作量/seed派发。左到右单acc加法顺序、循环终点与读取次数没有源级改变。

`convert_eq`第3851行是 **任意UInt32** 的 `convert u = Float32.ofBits u`，最终`decode_eq`第3862行是 **任意Binary32** 的 native decode等式。没有把finite、非NaN或E1..23作为求和调用方的新前提。最后的`rfl`目标与父本在旧convert重写后的目标相同；这是静态推断，尚非353d的Lean接受结果。

实际wrapper第3840–3846行保持旧外层两个条件，只在旧低条件假且`magnitude≥0x00800000`时进入新helper。W13b候选内第3695行的证明用wrapped减法的严格正值/上界及minNormal下界导出E1..23，不是仅凭小于Inf。

| 输入域 | 实际路线 | 约束 |
|---|---|---|
| ±0 | 原wrapped低条件为真，原tableProduct | 符号零路线未改 |
| 非零次正规E0 | 原低条件假、minNormal条件假，原ofBits | 不误入未覆盖的E0公式 |
| normal E1..23 | 原低条件假、minNormal真，新两乘法helper | 全sign/fraction，由W13条件定理支撑 |
| normal E24..254 | 原高端tableProduct | 读表算术源保持 |
| Inf/NaN | 原高端ofBits | 不用新helper处理非有限值 |

新helper将编码指数加32至33..55，W13证明sign/fraction不变且不发生UInt32回绕；再按真实model/codec/rounder精确乘2^-32返回原normal值。常量来自既有表项118，UInt32自减恒等式对全u成立。

## raw NaN、特殊值和最终规格

第3938–3940行完全保留：先算native结果；仅`result.isNaN=false`时`ofFloat32`返回，否则`referenceSum x`。后者第2297行为原始Binary32向量从posZero经`Submission.add`左折；没有把解码后/canonicalized的输入传给回放。

因此NaN sign/payload、signaling优先级及Inf相消invalid等精确语义仍由原raw回放承担。现有`NativeFinal.sumLoop_eq`第2664行以最终结果非NaN为条件，用原`NotNaNProbe.add_inputs`倒推中间acc/input非NaN；最终`originalSum_spec`第2762行处理成功native与reference两分支。新decoder的全输入Float32值等式正好接在原接口上，没有另造native NaN闭包假设。

`wrapper.toBits = oldConvert.toBits`不等于任意raw payload原样恢复。此前原成功见证的`0xffc12345/0x7f800001 → 0x7fc00000`边界仍适用；353d未利用这个假raw roundtrip替换fallback。±0、次正规、Inf/overflow与invalid路径的算法源都保留原判断，未新增标量低指数分支或更改标量add/mul。

## 命名空间、资源选项与来源组合

插入点前第3344行已经`end Submission`。新块只打开/关闭`R7W13`、`R7W13b`与`R7LowTableDecode`，命名配对平衡，父本没有这些namespace。块中已有`open FloatLib.Floats`及原证明所需作用域，未发现前向名字/同名export覆盖。候选仍只有原`import ContractTensor`与一份四entry及四spec。

唯一set_option在第3802行：`maxRecDepth 8192`。原10000及见证驱动32768未搬入。该顶层选项作用于后续声明，属于编译资源改变，不是运行数据派发；精确组合仍须真实编译。现行固定4b7原policy/options对**实际Kernel路径**重新执行返回PASS_STATIC_ONLY；174914字节低于256000限制。

独立从候选插入字节中找到以下完整原件各恰一次：W13 Increment14224字节、W13b Increment5624字节，以及W14c编译常量块删除import/资源行后仅将namespace改为`R7LowTableDecode`的版本。tail与`low-normal-runtime-tail.lean`逐字相同。W13的49186字节前置证明与c760/公开60f前缀也相同。实际组合与R builder按其声明构造一致，逆变换不依赖该builder的自断言。

新增三桥的具体未编译目标是：

- 第3834行 `lowNormalDecode_eq_proved`：新表常量helper等于原W13 helper；只展开定义并重写全u常量等式。
- 第3848行 `convert_eq_wrapper`：新wrapper等于原已证明W13b wrapper；相同分支上重写helper等式。
- 第3851行 `convert_eq`：通过前一等式与W13b全u定理传递。

随后第3862行新`decode_eq`与完整宿主其余证明一起仍未编译。未发现这些目标需要遗漏的数学前提或新库接口，但不能据短证明形状宣布接受。

## 公共成功证据没有覆盖的部分

上一份[W14b/W14c审查](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/low-normal-constant-source-review.md)已绑定原件、实际exit、公理与C/asm；本轮只复核相关源身份，不重做相同codegen报告。

- W13/W13b成功编译证明了原公共组合中的低normal数学及全UInt32 wrapper；353d插入的是相同增量，但整份新宿主尚无Lean回执。
- W14c的8192完整公开Host只附加常量块，namespace仍`R7W14b`，四entry保持旧公开60f。它关闭资源上限问题，未编译上述三条新桥及实际USize接线。
- 检查点22所述W13c意图只在公开60f后组合数学helper、不改四entry。00:43本地尚未回收；这不是失败。即使该公共组合后来成功，也不能替代353d的声明编译/完整gate。
- W14b是独立Nat/Array探针；353d live入口是Vector Binary32/USize。新增源码还带数学reference helper，可能生成旧once符号/初始化；不能外推整个候选无once、无额外初始化或热路径机器码相同。

未发现应阻止一次**精确353d statement检查**的静态缺口。下一个判别应直接编译该SHA的四spec及公理；通过后核实际live求和代码，再由D按授权安排完整配对计时。性能、确认与采用均不能从公共片段或295268低normal词曝光中推出。
