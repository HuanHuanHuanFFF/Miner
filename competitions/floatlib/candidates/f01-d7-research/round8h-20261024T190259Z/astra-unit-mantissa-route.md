# R14：归一化尾数与两次舍入的替代表示

这是相对R13整数尾数＋已有scaleTable路线的独立表示比较，仍是同一逐位乘法目标。原始来源为本轮固定FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c` 的Narrow roundProduct/Agreement及保留df5c；轻量反例筛查见 `astra-unit-mantissa-screen.json`，不作Lean或性能验收。

## 表示及正常结果域

原输入为normal，原指数字段分别是ex、ey，s=ex+ey，Mx=2^23+fraction(x)，My同理，P=MxMy，h=log2(P)∈{46,47}。精确乘积为 sign·P·2^(s−300)。

不把Mx/My转成Float32整数，可以构造两个无符号单位尾数：

`ux = Float32.ofBits(0x3f800000 | fraction(x))`，uy同理，值分别为Mx·2^−23、My·2^−23。

执行 `t=RN32(ux·uy)`，再乘实际位型 `sign | ((s−127)<<23)` 所表示的精确signed二次幂2^(s−254)。单位尾数首次乘法对应原roundProduct的scale252，整数尾数首次乘法对应scale298；两者在normal分支中使用完全相同的RNE(P/2^(h−23))，只有输出指数平移。

令R为这个RNE整数，c为R=2^24的进位，M为进位时2^23、否则R。t的Dyadic解码为 `(false,M,h+c−69)`；精确第二乘法后为 `(sign,M,h+c+s−323)`。这与原乘法raw指数 `h+c+s−173`、fraction `M−2^23` 相同。

先证明 **128≤s≤379、双方原E∈1..254**：缩放因子的rawE=s−127∈1..252，最终rawE∈1..254，均normal finite。最小最终值是2^−126，不会发生第二次精度舍入。380也应安全，但须补实际24×24乘积上界排除h47进位；不能仅从任意P<2^48推出。这个表示不受旧表index≥24造成的s≥174限制。

不能删normal-input条件；不能因选定特例成立而声明一般浮点结合律。s=127时把上述normal因子编码直接外推会编码为零；见实际原字反例 `0x1f800000 * 0x20000000`：原结果 `0x00400000`，错误路线为零。s=381同时存在finite和overflow结果，现有finite-target精确第二缩放桥不能无条件覆盖。

## 实现机会与未测成本

保留df5c的标量mul先按指数和<128走LowScale，其余nativeMul对两个normal输入分别做“UInt32尾数转Float32×scaleAt”，再做乘法和nonNaN结果判定。R13整数融合预期少一次浮点乘法、一次scaleTable读取，但原两次解码相互独立，因此乘法依赖深度未必减少。

单位尾数表示可以避免两次UInt32→Float32数值转换和scaleTable读取，换成三个同宽ofBits及两次浮点乘法。固定runtime的ofBits是实际边界，调用、跨调用保存、toBits和全调用守卫成本不能忽略；它可能比整数表示更慢。当前没有目标C/asm或计时，不宣称快。

若数学闭合，可比较整数融合/单位表示的完整调用成本，尤其实际bmm caller是否能复用某侧单位尾数。只改变标量mul并不自动改变矩阵内部已经展开的native点积；要分别核对作用范围。

## 同一指数分析导出的短路候选

normal输入s≤102严格小于半个最小subnormal，可直接返回signed zero；s≥382必为signed infinity。更便于复用现有有限mantissa界的**全raw保守版本**是 `ex+ey≤100`：该条件自动排除NaN/Inf，两个finiteScale之和≤100、实际P<2^48，而rounder需要右移至少49位，因此RNE为零。现有BMM UnderflowZero证明的是另一条件：两侧各自很小，使任意UInt64 product都可在shift≥65时归零。将该思想用于已计算指数和的标量入口是新作用范围，不能据BMM证书或旧零操作数快路的结果替代实际标量计时。

早期零结果只涉及乘法本身，必须保留XOR零符号；若用于dot还需恢复原+0加法。s≥382的捷径若要覆盖原E=255，必须先保留精确NaN选择；现阶段不提出未经证明的全输入Infinity返回。

## 验证状态与下一步

5504个原字模型样本（含2048随机、边界与全部符号组合）通过；原机实现/Lean/性能均NOT_RUN。原始oracle SHA与输入trace hash在筛查回执中，2秒/10000例硬上限，实际约0.046秒。两侧共用同一来源整数oracle，不是独立FP执行器。

下一必要义务是实际RNE输出M的24位界、mkBits字段decode，以及第一次native结果的canonical模型桥。本轮shape1/native-product1探针分别承担原roundProduct形状和真实native乘法/精确二次缩放。先收实际编译错误，再将这些引理组合；不为此替代表示提前安排多组完整性能确认。
