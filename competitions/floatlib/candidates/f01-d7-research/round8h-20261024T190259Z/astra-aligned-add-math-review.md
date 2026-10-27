# 研究侧对开发侧近指数整数加法的数学核对

时间：2026-10-24T21:34Z；R14数学支持，约10分钟纸面核对及固定源定位。开发侧已经在研究相近指数整数对齐；这里补必要条件和可复用接口，不另起实现、运行候选或CI。乘法原字指数平移仍是研究侧主线。

## 一次UInt32到Float32转换可以承担唯一一次舍入

两个正常输入的raw指数为ex、ey，尾数为Mx、My∈[2^23,2^24−1]。令a=min(ex,ey)，d=|ex−ey|。把两尾数在较小指数处精确对齐：L=Mx·2^(ex−a)，R=My·2^(ey−a)。

先按原符号做精确整数加减，得到符号s和非负幅度N。相同符号时N=L+R；不同符号时N=|L−R|，符号属于幅度较大的一项；N=0单独返回正零。正常非零输入只能以相反符号抵消，固定源也明确给出正零约定。

若d≤7，则

```text
0 ≤ N ≤ (2^24−1)(2^d+1)
      ≤ (2^24−1)·129
      = 2164260735 < 2^32.
```

因此对齐幅度、同号相加和异号绝对差都能在UInt32内精确计算，不要求Int或UInt64运行时计算。**这里不要求N<2^24**：`N.toFloat32`允许并负责完成RNE24舍入。固定retained源码的`R2W01c.uint32_model_eq_roundDyadic`对任意UInt32给出该转换的模型等式，可接`Model.NativeBinary32.ofUInt32_roundDyadic`。

原加法精确值为`(-1)^s N·2^(a−150)`。若最终结果normal finite，先把N正确舍入为Float32，再只平移其原字指数即可，fraction保持同一个RNE结果。运行原型的核心是：

```text
if N = 0: return +0
mid := N.toFloat32.toBits
mag := UInt32(mid + ((UInt32(a) - 150) << 23))
return mag | signBits(s)
```

该式不执行Float32加法，也不读取scaleTable。`UInt32(a)-150`的回卷必须按模2^32证明，不能假设它非负。

## 一个简单且保守的完整normal守卫

可先要求`24 ≤ a`、`max(ex,ey) ≤ 252`、`d ≤ 7`。这些条件已排除零、subnormal、Inf、NaN输入。N=0另处理。

N>0时令h=log2N∈[0,31]，舍入进位c∈{0,1}。由N<2^(25+d)得h≤24+d；从而最终raw指数为

```text
E = h+c+a−23,
1 ≤ a−23 ≤ E ≤ a+d+2 = max(ex,ey)+2 ≤ 254.
```

因此不会产生需要第二次subnormal舍入的结果，也不会把溢出Inf错误编码为非零fraction的NaN。这里252是为避免另证顶端不进位而采用的保守上界；253可能可扩展，但必须补更紧的进位界，不能从这个粗界直接推出。

必要边界：a=23、两相反符号尾数只差1时，精确结果为2^-127（subnormal），上面朴素平移却会变成零。d=8时，同号最大尾数的对齐和为(2^24−1)·257=4311744255，超过UInt32；若仍按32位加法执行会回卷。ex=ey=254、同号最大尾数时，原加法溢出Inf，朴素平移保留fraction会产生NaN。不能放宽这些条件后继续引用原证明。

## 固定源已有的原义务接口

精确源均为FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`，原作者FloatLib Team／MIT，原字节和Git blob SHA1已核对并记录在`astra-add-upstream-index.json`：

- `Model.Spec.add`：`toDyadic?`成功时恰为`roundDyadic fmt (addDyadic dx dy)`，不是先分别把输入转为近似值。
- `Model.addDyadicImpl_eq`：把原`addDyadic`接到独立符号／自然数幅度的精确实现，可直接处理对齐、比较与差。
- `Model.addDyadic_alignRightOffset`、`addDyadic_alignLeftOffset`：通用偏移对齐等式，可减少展开Int对齐计算的工作。
- `Model.addDyadic_sameSign_sameExponent`及三个`oppositeSign_sameExponent_*`引理覆盖同号、大小关系和精确抵消。其中`eq_zero`明确得到正零。
- `R2W01c.uint32_model_eq_roundDyadic`：已经在保留包内的UInt32原生转换模型桥；不同于只适用24位精确整数的`uint32_mantissa_model_decode`。

## 还没有关闭的关键义务和收益缺项

当前乘法草稿`native_round_normal`只处理h≥23；异号抵消会有h<23，**不能直接套用它**。需要在一次转换模型桥之后，同时覆盖roundDyadic的左移与右移两分支，再证明normal指数平移。可以先用同号路径避免小h以获得较小诊断，但这只是条件子域，不能冒充全路径结论。

同号／异号、大小关系、N=0、UInt32移位量和加减无回卷都须绑定真实运行体；Math/Real的相等不能替代raw-word结论。原型的额外守卫、符号分支、min/max及对齐成本可能抵消省掉的两个转换和浮点解码乘法，实际C/asm、完整配对计时和输入覆盖仍UNKNOWN。这里只给纸面归约与边界，未增加已验Lean定理或性能结论。

开发侧可在自然检查点取用；不要求改变已排队数学编译顺序，先把乘法整条链的真实编译结果收齐。
