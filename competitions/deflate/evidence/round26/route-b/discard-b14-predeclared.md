# B14 fixed sparse discarded A-probe consumer observation

缺口与新来源：B13 完整原 encoder 只多 9 B，本轮普通继承重选停止。原 A 树已经计算 `length<=best` 的 LCP，却未写入缓存；本次观察这些真实已探测来源是否提供原缓存任何同code最长前缀不能复现的新长度。R8D已有记录重选、B12继承和R24 SF四／八槽负例保留，不把旧完整前缀的未提供短边计新信息。

固定样本：沿用事前 `u32 avalanche hash(position)>>27==0`，不按反馈换seed/密度；约1/32物理位置，原 finder 和 full/sample DP完整运行。只对选中树搜索位置收集已探测的discarded候选，每distance code最多保留最长一个。原缓存同code最长前缀可复现的discarded记录扣除；消费域还从 `max(original_samecode_maxlen+1, original_record_lo)` 开始，并扣除原 byte-eligible inherited 同code前缀，避免把已有同code可覆盖长度或B12来源重新算新机会。此更强来源排重有意排除了能由旧记录全前缀重选实现的边。

字节／供需：新增保留前缀用原 `check` 完整核验。稀疏8B(position+packedrecord)按物理位置递增存储，每个原DP invocation用binary lower_bound定位，然后随反向位置游标消费，不建dense offset表、不存n×30矩阵。物理生产数量、sampled search位置、同code排重、byte-valid/invalid、logical/capacity bytes、真实DP消费记录／域／query项、原packedbest价格改善与同价tie分开记录。全28原token及独立decode保持相同。样本覆盖不外推全输入质量、bit节省或速度。

实际操作及成本上限：一份原552观察副本，public native20mincap；云端编译240s、运行720s，绑定run/git/Rust/Lean/observer/input原哈希。新增维护／查询都计数，无hotpair时钟，不启动生产候选/paired/proof。已有样本计划在7A文件上最多46,938物理位置，所有30codes的稀疏逻辑上限11.27MB/文件；capacity/原状态另计，不假称实际RSS。第一次有效结果依赖完整原轨迹、消费者原价格和成本数组，不以producer计数替代。

事前有限检查：10,000递增长度frontier／同code完整前缀排重／严格低价域案例，逐项核对1,533,580个新长度项；10,000稀疏重复位置／随机p0..pe游标案例核对消费者边界。它们不是Rust原轨迹或完整证明。

选择判别：若有byte-invalid先诊断；若来源扣除后大部分为空或主要买tie，直接停止。若集中真实价差覆盖且维护/消费数量有可承担路径，再考虑一份低成本保原边的实际encoder实现。无条件bit差求和推字节；不因为“不同于R8”继续多轮。当前正式份额、私有质量、gate均UNKNOWN。
