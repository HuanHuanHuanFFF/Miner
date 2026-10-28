# R22 A：native product / combined scale 两条小桥

**已PARK**：40607316341精确nativeprod四组MUL1.034864/1.041024/1.099496/1.043395，停止新public证明；本页两桥保持NOT_RUN储备。当前A唯一索引转[../wordcarry-review/HANDOFF.md](../wordcarry-review/HANDOFF.md)。

阶段 **23:52:12—00:07:12 UTC**，共同截止 **03:12:47 UTC** 不变。B持有e51a/92ff，D唯一Git/CI；本方不改运行体、不造public候选。

- [NativeScaleBridges.lean.inc](NativeScaleBridges.lean.inc)：**5f5b1e0a / 5165 B / 2根 / NOT_RUN**。第一根对实际`((s−150)<<23)|signBit`证明NormalBand/wordExp/wordSign，再复用scale_native_decode；第二根把已首次RNE的`m*2^e`（e23或24）与该scale的native乘法接到正常目标mkBits，E47..254，无新精度舍入。
- [精确接口图](INTERFACE-MAP.md)：6589真实product decode直接复用；原输入E1..23用R17 `R18.R14NatNormal.raw_normal_decode`，不能用R2 E≥24域；R17 model_mul_normal_fields和sign_word_eq连接同一目标。旧source manifest时点不改。
- [manifest](manifest.json)：e51a/92ff/6589验收/00ab/B2字节绑定，414个synthetic sign/S整数字段检查通过；未重跑root19872模型，也不把字段检查当Float32/Lean或速度。

仍缺真实typing/replay、公理、actual product/sign/Model.mul/carrier与公开guard/fallback接线；B另管GuardFields。成本先决定完整工程，S174..380不扩。Broad-word三根仅留NOT_RUN储备，已停止大证明。
