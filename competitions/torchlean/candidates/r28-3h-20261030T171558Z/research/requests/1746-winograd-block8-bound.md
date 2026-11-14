# A空间Winograd：父给保守block8字长推导，请关键核验
已读A SpatialWinograd与28channel反例，父独立推导一个可修复范围，不改冻结c6a4da候选、不新增CI。
原source11 narrow combined sx+sw<=31、sw<=6。已对齐输入|X|<2^(24+sx)，权重|W|<2^(24+sw)。F(2x2,3x3)的B输入二维变换每项最多4原输入，所以|V|<2^(26+sx)；用G'=2G，两轴整数权重U'=G'WG'^T每项系数L1<=9，所以|U'|<2^(28+sw)，并因sw<=6有|U'|<2^34。
以2^25分割有V=lo+2^25*hi，0<=lo<2^25、|hi|<=2^(1+sx)（负数floor可等于边界，不写严格小于）。单乘|lo*U'|<2^59，|hi*U'|<2^(29+sx+sw)<=2^60。每组最多8输入通道则任意prefix低acc绝对值<2^62、高acc绝对值<2^63，保守signed64安全；组间按原模128carry累加。不能让全部28channel直接复用旧signed64界。
编码V以center2^58，g=(encoded>>>25)-2^33，lo=encoded&((1<<25)-1)；因sx<=31有|V|<2^57，encoded<2^59仍smallNat。变换权重可center2^35后ArrayNat（<2^36）存，取出减2^35；不要ArrayUInt64每项heap boxing。这个范围不是实际Lean proof，A请主动反证并记录接受/修正。
G'两轴让最终逆变换Yscaled=4*原body；先完整按块/逆变换收集128位有符号scaled body，证明四倍整除，arithmetic右移2恢复body，再复用原bias同一exactdotfinisher。不能先各product除4，也不能把bias放错尺度。保留原exactzero/-0 fallback，finite/narrow/shape guards之外原强路径。
稀疏weight变换会填密：原50%零MAC从36降18时，新16几乎无优势且prep更贵。可用真实非零weight guard保留原稀疏完整路径，不能按benchmark kind硬编码。正常dense两类可能有整包潜力，实际完整成本UNKNOWN；先判断最小可接runtime/源码预算是否本窗值得，别为未测大producer花满预算。
