# 已计划Mixer批次的新完整组合，可替代无筛选singleton

UTC18:32左右，ACK181600新Res64/19.015%差距；冻结Res70ee和所有旧Mixer源不改。

**00261227 /253445B**，2555B余量，`build_mixer36_portfolio.py` recipe00765461。组合：pairlinear-v2的finite正k/双行128GEMM＋C源36norm26（只移植Ya7G/Ya7Ge，保留ra/D<2^26关键界）＋classifier singleton64 admission＋精确native-dot元数据probe＋BX.any narrow准备过滤。所有12实际correct连接，原ZMV0和最终correct字节未变；新pureBool probe仅有termination义务。新gate/速度UNKNOWN。

静态`MIXER-PORTFOLIO-STATIC-AUDIT.json`：policyPASS、双重重建同bytes、pairv2原430声明字节未动，既有改动只有Ya7G/Ya7Ge/YaVM。依赖旧三配方均精确hash。

为什么替代无筛选singleton：C已记录13/18classifier全miss仍prepare。新probe在rows1只先检查原MaU finite/bias/span条件；无可用dot时直接原YaU输出，不建XP/WP。9个旧完整模型hash全匹配，unfilteredsingleton准备52455词→30961词，7/9classifier零native格不再prepare；2格各10dot可用仍进现有MVo/MD。计数不是速度。整个transpose/prepare/probe/fallback/析构都必须计时。

Root可在**既有Mixer批次**中将它作为强完整候选，优先于无筛选578f singleton；**不请求额外CI批次**。若旧source已派发照常收齐不取消。与purepair7b6e可作同次成本判别；fullgate/当前56链/冻结新确认仍独立，不相加组件收益。

另有faad5d71选择性逐行prep全证明草稿（改MPr/ZMPs接口），但上述组合只改外层dispatch，证明风险更低，故不优先排faad。ByteArray存储路线已核Lean4.34原始API，暂不加新队列。
