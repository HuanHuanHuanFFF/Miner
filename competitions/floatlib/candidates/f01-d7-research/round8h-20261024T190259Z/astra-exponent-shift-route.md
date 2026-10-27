# R14优先新路线：一次原生舍入乘法后平移指数位

## 相对已有路线的变化

保留df5c的normal标量路径包含两次“整数尾数转换×scaleTable”解码、一次原生乘法、nonNaN结果判定及toBits。R13整数融合及本轮已写草稿把它变为两次原生乘法＋一次表读。

现在可以进一步省掉第二次乘法和全部scaleTable访问：两尾数UInt32→Float32精确转换后，只做一次原生乘法，再读取其toBits并调整指数字段。第一次乘积已经完成与目标相同的RNE24舍入；在最终结果normal finite的域内，之后缩放只改变指数，根本不必再执行浮点乘法。

这是对先前两乘表示的机制变化，不是给相同代码换seed。本地已检查现有候选manifest、RESULTS及数学储备索引，未找到相同“native整数尾数乘积＋raw指数平移”的完整结果；R6 normal-mul是整数48位乘积＋软件round/log2，不同。此检索范围不构成全局新颖性证明。

## 精确公式与边界

原输入raw指数ex,ey∈1..254，S=ex+ey∈128..380。Mx=2^23+fraction(x)，My同理，P=MxMy。令h=log2P∈{46,47}，R=RNE(P/2^(h−23))，c为R=2^24的进位，M为归一化尾数。

`t = Float32(Mx) * Float32(My)` 的实际舍入结果是 `M*2^(h+c−23)`，正号原字为 `Emid*2^23 + (M−2^23)`，其中Emid=h+c+127。实际24×24乘积上界排除h47进位，故Emid∈173..174。

原乘法结果normal时的指数是 `Etarget=Emid+S−300`，原字仅需：

```text
delta := (UInt32(S) - 300) << 23
magnitude := UInt32(t.toBits + delta)
result := magnitude | ((rawX xor rawY) & 0x80000000)
```

所有加减均在UInt32模2^32语义下执行，不能用无界整数赋值草率替代。S<300时delta回卷；最终Etarget∈1..254，正确消掉回卷且不会污染结果符号位。第一次舍入的进位已经包含在t的指数内，无须运行时另算h或carry。fraction保持原RNE结果。

最小端S128、最小尾数时，t是2^46，指数173平移−172成为rawE1，正确产生最小normal。S380最大尾数时，t的指数174、fraction0x7ffffe，平移80得到0x7f7ffffe。h46进位的样本同样通过。

两个真实域外反例必须保留：

- S127：`0x1f800000 * 0x20000000` 原结果0x00400000，盲目指数平移却为零（应走subnormal舍入）。
- S381：`0x5f7fffff * 0x5fffffff` 原结果正Inf，盲目指数平移却产生0x7ffffffe（NaN而非Inf）。溢出不能只改指数而留住fraction。

两输入normal守卫及S范围之外全部保留原mul。负结果只用原XOR符号置位；本域没有零、subnormal、NaN或Inf输出。

## 已有证明接口与下一关键义务

固定FloatLib的RNE上下界、原roundDyadic正常式和UInt32 mantissa native解码足以连接第一次真实原生乘法与mid原字。本轮shape1/native-product1/rounded-bounds1已经交给D统一编译，Nat正常式与全输入模型草稿均已写出但NOT_RUN。

本路线不再需要通用Real二次缩放或第二原生乘法桥；保留它们为备选资产。新增主要义务转为一个有边界的UInt32模加减/移位恒等式，以及sign/fraction字段绑定。中间位型来自实际Float32.toBits，不能假设P被Float32精确存储。公共完整mul_spec及全输入fallback仍须绑定真正运行体。

## 证据与性能缺项

`astra-exponent-shift-screen.json`记录7340个边界/符号/随机样本，2秒/10000例上限，实际约0.046秒，SHA与trace、反例均保留。两侧共用固定整数oracle，非独立硬件执行、非Lean证明、非完整枚举。

静态上删除两个浮点乘法与两次表访问，并把乘法依赖深度从两层降为一层；完整成本仍包括UInt32守卫、两次UInt32→Float32转换、toBits边界、符号打包和回退。本路线只重构公开标量mul，不自动降低已经预转换的BMM每MAC成本。实际生成C/asm及25轮完整调用计时仍UNKNOWN，先收编译与原义务，再判断采用。

## 编译通过后的集成位置与义务（2026-10-24T21:26Z）

冻结proof1（56773d4d，249900B）仍保留原公开`Submission.mul`。它若通过statement，只证明新增辅助声明能够编译；原gate只审计四个公开规格时，也不能据此声称新guardedMul已进入证明依赖锥或运行体。

开发侧集成时建议在compact-base原公开`mul`定义之前插入四份新namespace片段；该位置已经有全部R2W01b/c、R7W01/02依赖，也已经有原`nativeMul_spec`。原位置处于`namespace Submission`内，插入绝对`namespace Submission.R14…`前必须先`end Submission`，之后重新`namespace Submission`并恢复`open FloatLib.Floats Competition`。可用单独section包住四片段及`maxRecDepth8192`，避免该设置流入后续旧证明。

把原公开mul及其规格仅在该定义块内改名为`mulBeforeR14ExponentShift`和`mulBeforeR14ExponentShift_spec`，原函数体与原两分支证明逐字保留。紧接着定义新的公开入口：

```lean
@[inline] def mul (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul mulBeforeR14ExponentShift x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  R14ExponentShift.guardedMul_spec mulBeforeR14ExponentShift
    mulBeforeR14ExponentShift_spec x y
```

这样后续原`mul_eq`、`referenceBmm`及其证明仍能在原声明顺序解析公开mul；fallback不引用新入口，不形成递归。不要只把新定义放在文件末尾同时删除旧mul，因为中途的`mul_eq`和`referenceBmm`会先失去名字绑定。也不要保留两个同名公开mul。

后续`referenceBmm`使用公开mul，因此部分参考/回退路径可能跟着变化；已经预转换的矩阵native MAC并不自动变成这条路线。实际影响必须从最终公开caller的C/asm与完整逐项计时核对，不能笼统宣称BMM完全不变。

该段仅为已读源码后的集成说明，没有创建新的运行候选、修改开发侧文件或派发CI。冻结proof1及其片段哈希保持原样；先收真实编译反馈，再由开发侧形成精确新运行版本。
