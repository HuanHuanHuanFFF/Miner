# 读新机制后的父决策与重复投入约束
已读A PackedSupport/SpatialWinograd、B local-channel12853、C norm26及旧seen classifier覆盖。dc610a60冻结不动，D已确认收父一次关键审核，新增机制均独立目录/版本。

1. C classifier原先父列较前，但新模型13/18全span miss且准备70950项，已在父CI-REQUEST降优先；这不是测量负结果。新norm26-36 79615bd5父已逐字重建、审核D>0+ra/D<2^26数学与全源保留边界，按有机会同Mixer批次的小成本transfer保留，不能套R27NMLP负成绩或旧gate当当前验收。
2. B local-channel128是当前值得完整成本判别的新表示机制：实际通道/像素尺度变化支持singlemul，不同于旧Band/FP。关键数学：abs(a*b)<2^63来自24+24+combinedspan<=63（guard<=15）；取低64积再signextend加128，carry恒等式不依赖acc不回绕；仍要实际producer/偏置共同尺度与fallback证明。先交完整cost，别因为旧小根已接受就宣称all12。D独占调度。
3. A support63与父独立sparse-input/63bit模型是同一编码家族（factor56+index7、界<2^63），不能记成两条独立机制或增加信心。A实现3x3patch（复制overlap可能9倍）；父只分析pointwiseflat CSR（无patch9倍）。两者数学资料可复用，统计/成本只按实际版本。父不新增同类Kernel/CI，避免重复。
4. A空间Winograd是实质不同高上限路线。父1746文件给block8保守字长推导；请反证或写可核实接受。成本/接线前只做关键桥，勿先铺整套大证明；已有R27linearWinograd负结果不封死空间tile变换，但稀疏填密、padding、transform缓存/边界与signedzero都要计入。

本轮截止20:15:58不变，所有后续初始派发后files only；父复核只在新版本/风险变化时扩大。
