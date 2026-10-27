# 共用整数舍入器：边界与集成审阅

R14研究侧，2026-10-24T22:24Z。针对开发侧913d公开乘法接入、0382转换桥与signed64加法纸面路线。这里只记录静态／数学核对；没有新增CI或第三种乘法运行候选。

## 913d的实际接入

独立重新核对913d715b…的当前字节与本地7f312bfe Git blob：250296B。四份冻结数学片段各恰好出现一次、顺序与哈希完全一致；新入口之前的compact父本前缀不变，`add_eq`开始直到文件末尾的原父本尾部逐字不变。

原mul改名范围仅定义名、规格名、规格左侧与unfold目标；原函数体和分支证明保持原字节。新公开`mul/spec`在原`mul_eq`及`referenceBmm`之前，调用guardedMul与无环mulBeforeExponent。闭合／重开Submission恢复原本顶层open，原先其他open都在已闭合的子namespace内，没有丢失顶层local变量或section。完整回执`astra-development-integration-review-913d.json`。**该检查不等于Lean编译或运行验收。**

## 0382的一处静态编译风险

0382a6d9…与compact父本＋一个LF＋当前development-int64-rounding-bridge.lean（99c2e2f6…）精确一致。`low_int64_model_eq_roundDyadic`在`rw [int64_model_eq_roundDyadic, uint64_toInt64_toInt n hn]`后继续have/simp；重写后ofScaledInt的自然数系数可能已与目标定义相同，rw可能自动rfl关闭目标，留下“No goals to be solved”。这是静态风险，未取得编译报错，不能当作实测失败。

可用不依赖rw是否自动结束的末尾simpa写法：

```lean
  have hm := int64_model_eq_roundDyadic n.toInt64
  have hc := uint64_toInt64_toInt n hn
  have hnonnegative : ¬ (n.toNat : Int) < 0 := by omega
  simpa [hc, FloatLib.Numerics.Dyadic.ofScaledInt, hnonnegative] using hm
```

固定Lean293d5d0c的SInt/Lemmas提供`UInt64.toInt64_ofNat'`、`Int64.toInt_ofNat_of_lt`、`UInt64.ofNat_toNat`另一条短证明路径。原源259689B、Git blob与Apache2许可证已核验，入口`astra-int64-source-index.json`。开发现有BitVec证明也有合理的精确范围前提，不要求替换成这个备用证明。

## signed64原字平移应保留已经存在的符号位

正幅度版本先平移正mid，再OR输入XOR符号；signed64加法转换所得mid本身已有符号。应证的源式是

```text
mkBits(sign, em, f) + ((s-k) << 23)
    = mkBits(sign, em+s-k, f).
```

`astra-raw-exponent-shift-general.lean`已写通用k及上述保留存储符号的代数版本草稿，假设s<512、k≤512、em<256、fraction<2^23且目标E∈1..254。它只依赖原mkBits_nat，没有Float32重结合；NOT_RUN。模运算必须在UInt32中完整保留，负数回卷通过模2^32消去，不是把delta截到8位后推理。

## postguard怎样推出原roundDyadic确实走normal分支

令非零精确整数幅度为N，h=log2N，c是把N舍入为24位尾数时的进位。第一转换的指数em=h+c+127。加法原指数为a−150，a=min(ex,ey)≥1。postguard要求E=em+a−150=h+c+a−23在1..254。

这里应显式使用：**整数转换在h≤23时完全精确，不能进位；c=1必有h≥24。**

- 若c=0，E≥1直接给h+a≥24。
- 若c=1，h≥24且a≥1，仍给h+a≥25。

所以原精确加法的未舍入总指数`h+a−150≥−126`，确实走原roundDyadic的normal分支；上界E≤254也给包含carry的总指数≤127。**正常输入加法不必为此额外排除E=1**，但证明中不能漏掉“低位整数不进位”这条连接。

对任意负缩放指数单独抽象时，postguard本身不蕴含未舍入normal。例如N=2^25−1、缩放−151，第一次转换进位，最后E=1，但未舍入指数为−127。这个例子反驳的是少条件的分支推理，并不反驳舍入结果相等；它不满足加法a≥1的尺度条件。乘法当前S≥128也已直接保证h+S−300≥−126，无需放宽守卫。

当前乘法Nat-normal草稿只写h≥23。要为signed64加法复用，应把首轮尾数定义统一为：h≥23时RSE(N,h−23)，h<23时N<<(23−h)，再证明低h无carry、一般归一化尾数界和正常舍入形状。现有`Submission.FastMul.log2_shift`以及公开RSE上下界可避免枚举整个整数域。研究侧继续这个共享引理草稿；不另造运行候选、不扩张当前四项编译计划。

## 表示比较的边界

研究侧`astra-int64-native-product-substitution-draft.lean`写了整数积转换与原两次精确UInt32转换＋一次Float32乘法相等的证明草稿。它的前两个转换引理与开发现有桥重叠，保留为比较推导，不请求重复编译；不创建signed64乘法运行版本。当前实际乘法机制仍只比较原生乘法平移与开发侧偏置RNE整数打包。操作数减少和源码较短都不能代替真实成本计时。
