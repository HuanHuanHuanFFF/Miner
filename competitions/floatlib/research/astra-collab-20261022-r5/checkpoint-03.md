# R5-03：延迟回退地址计算，独立的小改动候选

10:34:17Z冻结`f01-r5-lazy-finish/Kernel.lean`，136097 bytes，SHA `c127423da4562a2e34029c9c2e7df542db7a0664a9c6070b089527f05f28f136`。从ba93父本独立生成，与两个行输出稿分开。Lean/性能NOT_RUN。

真实起因：601同父本诊断C的Packed10.outputFromTiles___redArg先做坐标解码、4次回退地址Nat乘法及2次加法，然后选lane，最后调用finish检查finite。普通有限结果不读取这些地址，却已付计算和RC成本。还有1次m*p是坐标解码本身，不能算入本次削减。

本次变更：finishAt接收已解码的b/i/j/m/n/p，先检查result.isFinite。finite时直接旧ofFloat32；仅非finite分支内绑定一次baseA/baseB再执行原Fin.foldl。地址没有移进逐k回调，不增加回退路径每k重复乘法。布局、解码、tile结果、dot和标量三运算均原样，未增加行数组或其他存储。

finishAt_eq、output_eq、core_eq以及整入口相等均用定义相等rfl接旧完整规格，未引入新的浮点命题或前提。仍须实际statement/gate验证。D可将它作为两份行输出之外更小的对照；若输出稿copy成本抵消收益，这条能够单独判定“有限输出提前算回退地址”的成本。不要把多个变化的收益相加。只有实际C确认finite路径没有地址Nat mul/add，且完整调用测量有利，才可采纳。

网页第一路独立审查指出有限接纳分支会掩盖错误raw地址，这与父本finish定义一致。以下是补充解析见证（未冒充实际运行；NaN payload由固定软件参考确定）：

- 行基址：shape(1,2,1,1)，A=[+0,+Inf]，B=[1]；第二输出应+Inf，错误复用row0 raw地址得到+0。
- 列基址：shape(1,1,1,2)，A=[+Inf]，B=[+0,1]；正确为[NaN,+Inf]，第二列错误复用col0得到NaN。
- 批次基址：shape(2,1,1,1)，A=[1,+Inf]，B=[+0,1]；正确为[+0,+Inf]，第二批错误复用首批B得到NaN。

本地有限地址/顺序诊断另外通过3360形状、123480合法输出、370440有序地址对和226巨大Nat采样点；不替代Lean和float执行。见output-layout-check.json。所有原稿及原始CI保持不变。
