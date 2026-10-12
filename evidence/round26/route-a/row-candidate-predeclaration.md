# A12：单一 fixed4096×8 PC row 实际解析器

预声明记录时钟：2026-10-12 00:30:10 UTC；本地检查后交主线程调度，实际启动以原 CI 回执为准。一次原生批次，外层上限 20 分钟；不扫容量。研究截止 03:06 UTC，固定总截止 05:06:52 UTC。当前没有配对计时、正式提交或新证明。

## 为什么执行下一圈

A11 完整绑定原父 28 输入/token/decode，13 个实际 PC chain 输入全部有更多局部更长 offer，合计27045更长、7778更短；原 normal 赢家保留658389/666167。标签在780735/2792213实际预取为空（27.96%），lazy新表独有接受1801、原父独有551。这是比继续 lazy 深度/距离门槛更大的新消费变化，值得一次完整轨迹判别。

负证据不改写：7778旧赢家驱逐；原27868个len3中丢198；双方已有match时 normal gain_worse1573多于gain_better1224。row维护3923285次tag RMW、cursor RMW和位置写入，实际位置扫描含547888个过期来源。这些足以否决性能。原与影子helper计数的拒绝域和预取范围不同，不相减为时间。旧 R10 row-mask 回归仍是有效先例。

## 唯一生产变化

候选 `candidates/r26-a-641-row8` 基于原 public641，保留作者归属和原全部路由参数。13 个旧 chain 调用改用 `ar_run1c`；旧内核仍保留在源码，以免不相关证明/其他调用被修改。

主索引固定为32768个u32位置、4096个u64标签、4096个u8游标，共167936字节。原真实km与原乘数产出一次(row,tag)，normal最多2次（dp<2）或3次（dp≥2）窗口内字节验证，lazy最多1次；过期/空槽单独扫描但不消费字节验证预算。长度、距离、近距离拒绝、原gain、fold、record密度、writer、其他引擎都保持原定义。保留km3，不能按full4删去len3域。

读取顺序明确：ahead用行标签选择第一窗口内来源，预加载其word8，同时缓存row/tag、原cursor和剩余mask。当前位置插入返回被覆盖的位置；下一位置ahead后，当前位置offer消费缓存第一来源。其余槽按缓存的预插入顺序扫描；若读到刚覆盖的槽，则恢复victim。这样不复制整个row，也不把插入的新位置误当旧候选。所有来源都通过原窗口/字节验证。

match end 的ahead在原flush/fold/record之前准备。record对每个实际写入行累计dirty：只要写过被缓存的coarse row，就重新准备end的ahead；否则复用。此比较/OR进入生产成本；不新增版本数组，也不凭A11的454次变化省掉检查。原窗口外ahead保留fallback值，仅在真正将来查询时才重新读取，计数区分fallback分支与实际reload。

## 最小判别与冻结检查

先原28文件encoder，参照原641和514；原生decode按已有公共脚本运行。无有限token等价主张，因为这是新trajectory。原encoder bytes和逐文件token变动才决定真实质量，不使用A11局部offer相加。

同一原生作业随后运行未计时observer：每个实际normal/lazy消费之前，用新鲜row重算ahead并与缓存完全比较；用插入之前的row独立重算完整offer，与生产victim恢复后的offer比较。冻结candidate与observer的28输出token/decode和原encoder token SHA必须全部相同。另162个直接core调用覆盖长度0..64、不同重复周期、32768窗口构造与km3/full4，有限检查不代替全输入证明。

本地已检验12000个预插入victim顺序模型和12000个dirty模型，生成器 `--check` 与Python语法通过。候选Rust `9c42e665cfdb8831e2c7f4dbe0a2de6012e59bc8ae9bd6918d540ea71704e2ac`；Lean仍原父 `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e`，**未适配，不是新证明**。精确批次、生成器、observer、参照、快照等哈希在 `quality-a12-native-preflight.json`。

## 选择与证明成本

若实际质量明显变坏、helper oracle/cache/decode失败，保留负回执并先诊断，不自动上计时。若真实质量与成本形态仍有较大目标空间，才讨论两块原协议。小于目标空间的微小质量差不会单独支撑5/10声明，也不靠容量或近邻参数扫挽救。

接口成本详见 `row-shadow-proof-interface.md`。原probe和f_try可提供FoundAt/MatchAt，但新row数组/索引/移位/游标、预取tuple、victim参数、预算fuel及两层主循环都有新obligation。生产层不依赖tag/FIFO证明即可用字节验证确保合法，但ahead的cw=word8(source)必须证明；cached-first与rest-slot使用范围不同。父Lean487015B仅余37273B，是否容纳新循环证明UNKNOWN。当前只复制父文件作明确draft，性能信号前不投入完整Lean。

VERIFIED：本地生成、精确源身份、有限模型。INFERRED：A11的主读取/候选分布支持这一次真实native。UNKNOWN：Rust编译、实际token/字节、总压缩时间、新gate、正式或稳定5/10份额。
