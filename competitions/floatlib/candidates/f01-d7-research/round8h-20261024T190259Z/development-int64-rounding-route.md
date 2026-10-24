# 一次整数转换作为共同舍入器

开发侧补充，UTC2026-10-24 21:46。当前只作源码核对、纸面候选及轻量模型；未编译、未计时。研究侧仍优先关闭56773d4d乘法证明，不要求增开排队任务。

固定Lean v4.34.0的`Init/Data/SInt/Float32.lean`把`Int64.toFloat32 n`定义为`Float32.ofModel (Float32.Model.ofInt64 n)`，不是opaque的Float64转换。`SInt/Basic.lean`的`UInt64.toInt64`是同位型构造，`Int64.toInt`是`toBitVec.toInt`。源作者、Apache2.0声明保存在development-sources/lean-int-casts两份完整原文中，未修改或导入运行库。原始地址和哈希见同目录receipt.json。

现有保留Kernel第1505行的`R2W01c.uint32_model_eq_roundDyadic`已经用`Model.ofModel_ofInt_eq_roundDyadic`证明任意UInt32转换等于整数RNE。这个通用定理不要求整数能被24位尾数精确表示；应该可以同样接到Int64的透明模型。

## 乘法备选表示

两正常24位尾数的整数积P满足0<P<2^48<2^63。`P.toInt64.toFloat32`可直接产生RNE24(P)，替换两次UInt32转换及一次原生浮点乘法，随后使用相同指数平移与符号逻辑。由于是整数转Float32，避免额外证明Float32乘法中间结果桥；低层成本是整数乘法和signed64转换，是否优于两个signed32转换加浮点乘法未知。不能因操作数少直接宣称加速。

最小义务是`Int64.toFloat32`的generic roundDyadic桥、P.toInt64.toInt=(P.toNat:Int)、与现有首次RNE模型的相等。后面的正常指数位移证明应复用，不另造一份。这是有机制差异的第二表示，最多与已有一次native乘法表示比较，不开盲目小变体。

## 加法的signed64扩展

ex/ey均在1..254；a=min(ex,ey)，d=|ex−ey|≤25。把带符号24位整数尾数左移ex−a/ey−a后相加，得到整数S，|S|≤(2^24−1)(2^25+1)<2^50。全部中间操作可在UInt64二补码内完成，并严格在Int64范围内。一次`S.toFloat32`已经完成唯一24位RNE；S=0单独给正零。

取mid.toBits的指数e，先计算数学量E=e+a−150。仅接受1≤E≤254时，`midBits + ((a−150)<<23)`按UInt32模运算恰给最终normal原字。运行守卫可用`(e+a−150−1 : UInt32)<254`，但证明必须绑定这个未截成8位的E；如果只看最后打包位型的指数，会误接受回卷的下溢/溢出。域外退回现有完整加法。相反符号抵消、负结果都不需要额外绝对值分支，因为signed64转换直接保留符号。

更宽d≤38也能在Int64范围内，但d≤25让最多50位的精确对齐和独立binary64参考都可直接检查，覆盖收益与证明复杂度应先比较。不能把d较大吸收直接改成返回较大输入，已有边界反例需要保留。UInt32幅度版本d≤7的数学支持由研究侧astra-aligned-add-math-review.md维护，开发不覆盖。

## 优先级

先取得当前两项修复和完整乘法链的编译反馈。整数转换表示作为能降低证明代价的备选，开发侧做有限独立模型与真实公开输入覆盖检查。没有正式全输入证明、固定runner完整gate和冻结确认前，不更新保留候选或冠军差距。
