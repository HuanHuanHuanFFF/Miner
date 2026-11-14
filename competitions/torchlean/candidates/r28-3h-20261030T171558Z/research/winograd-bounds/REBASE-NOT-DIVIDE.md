# 四倍body直接重标度，避免signed128除4

空间整数G'=2G令逆变换得到T=4S。原body所代表值是S*2^(B0−298)。若B0≥2，则令B0'=B0−2，直接使用T和新尺度：T*2^(B0'−298)=S*2^(B0−298)。无需机器整数除4或右移，核心桥改为精确dyadic重标度。原源码已引入finishWord_scale，实际字级调用仍需接线/编译。

**bias也必须同尺度重准备。** 原qCtx1的bias移位是idx(bias)+126−B0，m=mantissa(bias)<<23；改B0'后移位增加2，恰将bias的完整整数分子乘4。新finisher看到4(S+Bias)，在指数少2的尺度下量值相同，因此仍只舍入一次。不能沿用旧cb，不能先round body再加bias，不能逐product做截断除4。

机器边界：B0为UInt64，0/1必须原fallback；否则减2会下溢。原fast bias shift≤78，重标度后最多80，不能自动沿用旧fast字长证明；最小实现可要求旧shift≤76，其余原fallback，或正式绑定现有general YL的更宽路径。变换累加/逆变换128位安全、原guard真实性、输出布局仍各有证明。零结果保留原raw signed-zero replay，不从整数0推断+0。

这是纸面全量词量值恒等式及独立有限舍入核验，未实现Kernel、未编译Lean、未计时。它简化未来的桥接成本，不等于实现加速。除4路线仍有效，可按实际codegen/证明成本选用。
