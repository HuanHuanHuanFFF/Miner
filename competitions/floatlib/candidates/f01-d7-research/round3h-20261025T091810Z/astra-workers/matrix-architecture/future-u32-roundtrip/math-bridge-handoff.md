# 高N数值桥：依赖已对上，完整小草稿待编译

目标仅为 `2^23≤n.toNat≤2164260735` 下的native数值往返，没有创建ADD变体。`HighRoundtrip-bridge.lean`给出完整证明尝试；最后两个定理只带该原范围，不把浮点形状、cast行为或结果范围留作假设。**NOT_COMPILED，尚未宣称Lean闭合或标准公理审计通过。** 本阶段数学路线未遇到新的opaque接口，未占当前f7f的CI。

令 `h=N.log2`、`q=roundShiftRightEven N (h−23)`、`c=[q=2^24]`、`m=if c=1 then 2^23 else q`，定义 `R=m*2^(h+c−23)`。草稿的最终结论是：

```lean
theorem high_roundtrip_RNE (n : UInt32)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat ≤ 2164260735) :
    n.toFloat32.toUInt32.toNat =
      R14NatNormal.rounded n.toNat * 2^(n.toNat.log2-23)
```

桥的每段都有实际来源和已写出的承接：

1. 复用 `R14NatNormal.model_round_normal`、`R14WordAddRounding.rounded_bounds` 与原B2内的 `R2W01c.uint32_model_eq_roundDyadic/fields32_toDyadic`，推出native转换结果精确解码为 `⟨false,m,h+c−23⟩`。
2. 新的有界整数引理证明23≤h≤31，并在h=31时用 `N/256≤8454143`、RSE上界q≤8454144排除carry。故23≤h+c≤31，0≤e=h+c−23≤8；m<2^24给出R<2^32。没有借用错误的全UInt32无饱和断言。
3. 固定FloatLib `Model.toInt_toModel_eq` 结合 `Model.toModel_ofFloat32Model`、`exactValue_eq_finite_of_toDyadic?_eq_some`，把native `toUInt32`接到已解码dyadic的`roundDyadicToInt .towardZero`。非负整数指数使其定义直接得到m·2^e，没有截断损失；`UInt32.toNat_ofNatClamp_of_lt`消除夹断。
4. c=0/1两支用pow_succ证明归一化的m·2^e等于q·2^(h−23)，明确返回的是RNE整数R，而非未舍入N。全部条件由前述引理在最终目标中消去。

新取回的四份固定0d918源码、原293d ToNat定义、当前R14 support及B2源码均在 `bridge-check.json` 绑定路径/hash/来源；原文保留作者和许可。`fixed-Native-ToInt.lean`中真正使用的是无符号cast可复用的通用 `toInt_toModel_eq`，没有误用signed Int32的范围或把位编码toUInt32当数值转换。

轻量反证检查覆盖17426个构造N边界点；整数RSE模型、归一化R、host binary32后转整数相等，均无clamp，最大观察R为2164260608。另用每边38个mantissa边界值、d0..7及高N筛选检查21171组，未否定所提h阈值式：同号h=23+d+[R≥2^(24+d)]；异号d≥1时h=22+d+[R≥2^(23+d)]。d0同号h24，d7同号可h31/shift8；异号d0没有高N点。**这些是有限模型检查，不是阈值公式的Lean证明或完整输入穷举；未将阈值式接入任何运行代码。** 脚本实际约0.05秒，外层强制5秒超时。

当前缺项是固定环境对该小片段的实际elaboration、内核和axiom回执；不是已知的数学反例。整数重打包等式、完整ADD接线及成本另属后续任务，本阶段到此结束，不自动续做，也不改变f7f修复／完整gate优先级。token计数UNKNOWN；无本机Lean、Git、CI或未来确认输入访问。
