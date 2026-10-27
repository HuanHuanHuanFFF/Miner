# R14 ADD 字段与最终入口静态复核

时间：2026-10-25T00:50Z。只读 development-word-add-fields1.lean / spec1.lean；全部NOT_COMPILED。

字段数学链未找到新的数值反例：小gap左移与加法完整UInt32界、异号减法先证大小、base<=30使base+1<32、one-bit log2、t1..8、64位RNE、carry<=1窄化、完整未掩码E无回卷、fraction低23位，以及mkW_ofNat字段构造互相衔接。exponentWord实际先给宽松<=263足以避免32位回卷，最终e-1<=253提供E<=254；不需要额外把打包字段别名问题带入当前入口。

一处可简化的表示桥建议，**不是已确认编译失败**：spec1的core_spec末行目前为

```lean
simpa only [R2W01c.rawModel_eq_ofUInt32] using core_model x.raw.1 y.raw.1 hd he
```

目标经fromRaw_toModel/exec_toModel_eq_rawModel后直接使用 **Model.NativeBinary32.ofUInt32**；同一父源已有精确 `R2W01c.rawModel_eq_native32`，可在新版本改成

```lean
simpa only [R2W01c.rawModel_eq_native32] using core_model x.raw.1 y.raw.1 hd he
```

固定FloatLib Carrier/Native Base源码显示，generic Model.ofUInt32通过ofNatBits/ofWordNat重包Nat，而NativeBinary32.ofUInt32直接ofBits UInt32.toBitVec；父源的rawModel_eq_ofUInt32也以BitVec.ofNat_toNat化简建立二者关系。推荐后者是为了直接匹配当前目标表示，避免依赖simp把另一个表示同步规范化；尚未用真实Lean确认原写法会失败，不能把它记成编译错误。

公开API已核对：R7Native.toModelExecAdd把ExecFloat.add映射到Model.Spec.add；Model.Proof.add_eq_spec提供Model.add/Spec.add桥；R7W02.fromRaw_toModel和exec_toModel_eq_rawModel均输出NativeBinary32.ofUInt32。guardedAdd_spec的所有非快域分支保留原始x/y有序fallback。没有建议扩大输入域、改运行体或加入额外编译案例。

固定依据：FloatLib 0d918257，Model/Carrier.lean Git blob8849d6b29facd7ccff8d1f32e2b15626d0771023；Word/Narrow/Base/Runtime.lean 已在astra-upstream原件中。新raw_add_model/d507组件已按请求交付。后续必须以精确完整源实际编译及gate确认。
