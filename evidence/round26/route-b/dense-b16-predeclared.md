# B16 D complete forward lengths, intentional graph/quality exchange

缺口与不同大阶段：B15新增9.31M有效记录仅减21B，停止价格域重选。本次改 D 首遍提供的长度图，而非新候选发现/稀薄价差。原B8观察12.82M实际ring写、19.45M提供长度域，其中6.62M长度未写；Dforward原阶段时间轴占比历史代理约22.6%，不是可省时间上界。本次可能更慢，不能因父版更快而自动判否，须实际质量后二轴复算。

实质变化：唯一 `d_fill_nextl` helper置每项为l+1，因此已提供lo..hi候选长度完整枚举，不扫描flen阈值/价格/passes。不扩最大match、距离、搜索位置/深度或record格式，不加事件队列，不改环/reset、价格规则、backward reconstruction、encoder。直接skip的长匹配和未搜索continuation单端点路径保持原样，因此“完整”只指调用relax_run的既有候选长度域，不假称所有parser位置都成完整匹配图。

边合法性：原relax候选来自probe/d_walk/有效continuation，lo从3起且只提供至该匹配hi≤258。fback≥100路径还将原逐字节核验的back_best回扩匹配从j=i-t提供区间[t+3,t+len-1]；该截短区间的relax_run也恢复完整枚举，末端relax_one本身不改。back_best保证len+t≤258、j≥chunk开始、距离不变，新增长度均是该已核验扩展匹配前缀。新nextl对l<512是l+1，严格前进且不跳出hi；relax_run只有l<hi循环和最后hi一次写，lo>hi仍为空。lc索引%512、pa目标%RING8192保持；原live window258、CHUNK4096及open_chunk失效规则全部保留。恢复会改变价格/计划，但未引入延迟事件或旧epoch报价。原matcher实现和参数不变，最终路径及统计可以改变；不声明旧plan等价。

历史排重：R10routecfg明确仅恢复key/update/half，仍flen16、直接插入/不同walk，不是当前完整Dforward版本。R7block1/seed1在旧361匹配/路由上显示前后向规划质量／时间交换，seed1相对block1质量损失约.00465pp；它不是当前552收益保证。R7当年所有17候选及root29803重放零保留。此前稀疏长域事件NO_GO仍有效：此次主动改变枚举集合，以质量换工作，不宣称同字节大节省。

最小有效操作与成本：一份 `r26-b-552-dense-forward`，native20mincap、原28encoder与parent552比较，独立decode；低频parse/d_plan_k/d_parse/d_tally/d_dp/d_extract及backtrack/update包含成本，不计hotrelax每pair时钟。源码反撤销、brace/span、全lo/hi/flen有限枚举／环边界验证、完整round4.validate/round26-preflight先做。绑定B8raw与历史来源，真实新增工作以本次profile解释；6.62M不能当实测新边/速度/输出预测。

改变选择：实际质量改善若足够明显，即使更慢也按root最新同快照重放二维机会，再定原协议paired；质量无改善或代价远超交换空间则停止此版，不跟随更多flen阈值扫描。精确Rust/Lean保留，Lean只DRAFT；原DpNextl规范需新extraction适配/fullgate，正式准入/奖励UNKNOWN。目标仍两个不同且稳定5/10%，最后确认余量不动。
