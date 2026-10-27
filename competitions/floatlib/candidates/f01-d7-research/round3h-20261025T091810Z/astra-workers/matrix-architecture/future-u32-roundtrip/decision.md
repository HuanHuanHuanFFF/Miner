# 接口可用，尚未证明新的整数往返／重打包替换

**第一判别为 AVAILABLE_UNFOLDABLE_MODEL，不能标成 opaque 阻塞。** 固定Lean4.34.0、commit293d5d0c…中，`Float32.toUInt32`确为带extern覆盖的 **def**，逻辑体是`a.toModel.toUInt32`；不是只有运行时函数。未获得现成的完整有界往返／重打包定理，本调查不编译、不写候选、不占CI。

**精确来源。** 重核固定tag记录指向293d5d0c0c3f3dded4688b3ccd6a33939ac5102b；原header快照136786B、SHA982c731a…66c13，来源和旧receipt相符。runtime Float32文件SHA2f4b7eb8…f7319、Model文件SHA90994c25…b98e1亦匹配固定commit原receipt。新取回的 [ToNat.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Unpacked/Operations/ToNat.lean) SHA **895edd1c3e2056afd9b64507b2d81d02097f2af078b0478bc3ee6d17b2dc7a3b**、Git blob0ceda6d0…42f5f和3832B均匹配GitHub目录响应；原文和完整7份来源哈希在本目录及receipt.json。未读取最新非固定工具链来替代它。

逻辑链可直接展开：

- `Float32.toUInt32`（runtime223–224）→ `Float32.Model.toUInt32`（Model270）→ `UnpackedFloat.toUInt32`（ToNat56–57）。
- 最底层是 `UInt32.ofNatClamp (f.toInt 0 (UInt32.size - 1)).toNat`；`toInt`对finite调用`roundToInt`，后者通过`decreaseExponent/shiftToExponent ... .exact 0`向零截断；NaN和零返回0，正负无穷取给定端点。
- `UInt32.toFloat32`（runtime303–304）→ `.ofModel (.ofUInt32 n)`；Model223–224将`UnpackedFloat.ofUInt32`打包，而OfNat.lean的定义到`normalize binary32 n.toNat 0 .positive`。Float32.Model公开导入Operations，Operations公开导入OfNat/ToNat，且这些文件为expose public section；ContractTensor→Contract→FloatLib环境已有该Float32模型链。实际新增定理编译可用性仍NOT_RUN。

**最小剩余义务，不是新增假设。** 令R为N经binary32 RN-even得到的数值整数。需证明该模型结果为有限非负整数R，且`0≤R<2^32`；于是向零截断保持R、Int.toNat不改变它、ofNatClamp不触发饱和。然后证明`repack(R)=N.toFloat32.toBits`，包括R=0、normal mantissa的移位整除性和进位后的leading-bit。不能把数值往返误写为N本身：不可表示的N先发生了RN-even。

**边界提醒：** `Nmax=2164260735=129*(2^24-1)`大于2^31。对齐差d≤7不意味着leading-bit≤30；相加进位后h可为31、舍入移位可为8。RN-even若建立误差≤128，则松界`R≤2164260863<4294967296`足以排除uint32上夹断；这只是需要证明的路线，有限整数算术核对没有替代浮点模型证明。`Model.NativeBinary32.toUInt32_ofFields`处理的是字段编码，不应误作这里的native数值cast桥。

**运行成本仍UNKNOWN。** 已读header确认UInt32→Float32是inline `(float)a`；Float32→UInt32是inline `0<=a ? (a<2^32 ? (uint32_t)a : UINT32_MAX) : 0`；toBits为external声明。替换会增加一个数值cast、可能保留的两次夹断比较和leading-bit/整数重打包逻辑，不能从inline推得更快。当前ADD修复及完整gate继续优先；本阶段仅交付接口可展开的证据，不启动宽泛证明或变体。
