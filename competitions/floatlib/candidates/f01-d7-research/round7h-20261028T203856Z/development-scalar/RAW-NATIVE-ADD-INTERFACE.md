# Raw UInt32/native ADD：精确命题、既有覆盖和停止决定

UTC2026-10-28T21:18Z；固定FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`、Lean4.34；仅旧研究scope。无ContractExact kernel、remote编译或新CI。

记`R(w) = Model.ofUInt32 w : Model binary32`，`W(z) = UInt32.ofNat z.toNatBits`，`N(u,v) = (Float32.ofBits u + Float32.ofBits v).toBits`。

1. **输入解释（全raw）**：`(Float32.ofBits w).toModel.unpack = Model.toModel (R w)`。这是unpack身份，不声称所有raw原字往返不变；native packed model会canonicalize NaN。
2. **输出解释（全native）**：`W (Model.ofFloat32Model f.toModel) = f.toBits`，无需有限性假设，因为native packed model本就canonical。
3. **有限ADD**：若`(Model.toModel(R u)).isFinite = true`且v同样有限，则`N(u,v) = W(Model.add(R u)(R v))`。包含±0、正规、次正规、抵消为零和有限输入溢出到Inf；不要求结果有限。
4. **更宽notNaN域**：旧B2/F7的`Submission.R7Native.modelAdd/ofFloat32Add`已经包含输入Inf及Inf+(−Inf)的canonical invalid NaN；可以运输到同一raw命题，但这是旧结果的API运输。仅pinned库的`Native/AddSub.lean`有限定理不能不加证明直接升级到Inf。
5. **NaN域**：任一输入是NaN时调用精确fallback `F(u,v)`，要求`∀u v, F(u,v)=W(Model.add(R u)(R v))`。这样payload、signaling优先次序和原符号由原规格保留；不以native canonical NaN替代。
6. **fromRaw前提**：旧`R7W02.fromRaw_raw w`对任意UInt32均有`(fromRaw w).raw.1=w`，没有notNaN前提。相反，`(Float32.ofBits w).toBits=w`需raw word为canonical；notNaN是足够条件，任意NaN raw不满足。`fromRaw`的raw身份不能替代native ofBits的canonicalization论证。

`NativeWordAddBridge.lean.inc`现有6根草稿对应1/2/3及raw bits，**NOT_COMPILED**；没有为4/5另堆wrapper lemma。可复用根：`raw_bits`、`model_from_bits`、`unpack_from_bits`、`native_word`、`native_add_model`、`native_add_word`。既有同宽有限ADD定理为`Model.add_eq_ofModel_add_of_isFinite`、`ExecFloat.Binary.toModel_ofFloat32_add_of_isFinite`。旧F7另有`fastOK_notNaN`、`native_add_spec_of_fastOK`、`diagnosticEntry_spec`；其public endpoint与新raw API不同，核心算术并未新增。

**关键核实后的停止决定**：`native-add-adapter-audit.json`已对精确F7/f7ba的原gate statement侧C重新核C/trace/源码hash。`Submission_add`导出体本来就是`uint32_t (uint32_t,uint32_t)`，最后一个native ADD后直接`lean_float32_to_bits`返回；不存在Model/word/carrier adapter调用。public boxed wrapper另有2 unbox、2 dec、1 box，但新raw theorem不自动改变Suite的boxed callback ABI。

因此**不以“删除F7 adapter”为理由构造新helper候选或请求CI**。当前6根只保留为可复用API草稿。若后续目标的实际caller从`Model.add`开始，先核那个caller并量完整成本，再决定是否值得单数学helper验证；不能从F7接口文字推断其机器成本。新目标尚未授权实装。

证据边界：所读F7 C是原gate statement-side capture，不是本agent新跑的timed MainFull对象。该run外层`native-assembly-index.json`绑定另一个8eb63源，**不是F7**，故未用其ASM作F7结论。
