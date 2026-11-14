# 非负输入的完整精度单边偏移：连接局部尺度与unsigned累加

这是父从B局部尺度和C正数缓存归约出的**条件精确表示**，不是已实现Kernel，不新增CI。它不使用近似量化、误差证书或改变ReLU位置，也不因目标conv的relu=false而失效：这里只对实际输入检查有限且非负，输出仍可为负并按原算子返回。

设某pixel已对齐的输入`a_i≥0`，`a_i<2^(24+sx)`；权重`|b_i|<2^(24+sw)`，原单乘guard为`sx+sw≤15`。取权重offset`Q=2^(24+sw)`，准备`v_i=b_i+Q`，输入直接存a_i。则

`Σ a_i b_i = Σ a_i v_i − Q Σ a_i`。

只有**一个**共享pixel行和及一个终端修正；不需要通用双边偏移中的weight行和、`nQxQw`或第二项修正。Q是幂，终端乘Q是两word移位+借位。偏置在修正后的同一完整dot内由原qCtx2加入并一次舍入，原零provenance fallback不变。

## 为什么不缩小B的span15域

`0<v_i<2^(25+sw)`，故正积`a_i v_i<2^(49+sx+sw)≤2^64`，UInt64低乘在整个原span15域精确。积可≥2^63，所以**必须使用C的unsigned128 carry-only更新**；B当前signed64 sign extension不能直接复用。B的原signed-product域是48+span≤63；通用双边偏移要额外两位、最多span14，而这个单边形式只多一位，仍允许span15。

每个像素的Σa_i可在B现有逐pixel准备中一次缓存，所有输出通道复用。若k<2^20且sx≤15，则Σa_i<2^59；实际Mobile小通道更小。权重sw≤6时`v_i<2^31`，可用原尺寸的Array UInt32存储；a_i<2^39是smallNat。不能沿用原固定weight偏置2^31：必须在每个输出channel的准备阶段改为真实Q，否则乘积范围可能更宽。

新loop每输出只做原非负input读、positiveweight读、1低乘、unsigned128加法。pair共享input及已缓存行和。相较B单乘loop，可把input减2^57、weight减2^31及每积sign extension移出热点；相较C通用centered，取消input侧offset及两项终端修正。收益未知：k短时末尾修正可能抵消，实际compiler可能已经合并部分原减法，所有prep/cache/drop仍须计时。

## 实际适用和回退

官方Mobile的pw1/pw2输入来自独立BN/ReLU，常见finite行非负；**内核仍必须实际检查**`sign=0 or mantissa=0`，而不是假设调用者总有BN。NaN/Inf或任意负非零输入走原完整源/已有signed路径，不修改全输入量词；允许-0但最终exactzero仍用原raw Ybz/zW。Sparse源的weight支撑接口另算，不能把两边收益相加或直接覆盖它。

全零weight行可选Q=1并使正积与修正精确相消，或回原路径；不能拿缺失的max/min当有效跨度。全零input行也不能用数值0替代raw零符号链。原narrow和bias-scale检查仍在。

`one_sided_model.py`有UInt64/128字级有限重放、signed-carry错误反例和span16拒绝例。它不覆盖实际producer/数组getters、通道尾部、偏置上下文或完整all12，未编译Lean/未测native。后续只在B/C现有成本信号有价值时考虑一个同族精炼，避免当前队列膨胀。
