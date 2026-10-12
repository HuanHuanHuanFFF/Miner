# A15：上一已发射距离的查询预算交换观察

当前缺口：A14标签保原token但真实PC parser回退约25%，停止表示改造；A8额外lazy链虽少15119B，却慢约2.3–2.5%。当前641规划需要远大于此前局部质量收益。现在检验一个无需新增索引的历史来源是否能替换已有查询，而不是继续添一次查询后假定低成本。

本次变化：仅冻结641 observer。由当前已发射`out[nt-1]`的合法match token取得上一已发射距离；它不同于当前尚未发射的匹配距离。保持生产head、prev、token轨迹和所有原决策。原normal已经有首来源匹配时比较rep；在`dp>=2 && cl<c`域，固定保留head和第一旧来源，用rep替换第二旧来源（若rep与head/第一旧来源相同则保持原第三跳，不重复验证）。原lazy已经计算head offer后独立比较rep替换这个唯一head offer，分别与当前match决策比较，记录收益、同价和损失。

双方损失都保留。`normal_rep_gain_better`只表示额外rep线索；真正的normal预算交换看`exchange_gain_*`。lazy也分开“追加来源可胜出”与“替换现有head之后的净决策”，后者看`lazy_exchange_gain_*`。对每个合法rep匹配再按原input字节独立核对长度；源位置、旧/新distance都经过原窗口和near guard。无索引新增，无参数扫描，无生产candidate。

最小实验：28原始输入，observer与冻结641精确token/decode相同，并绑定A14原encoder中641的输入/token身份；逐文件统计normal/lazy机会、与原head/两级prev重叠、预算交换的正负覆盖和长度变化。这里的gain是既有启发式得分，不是压缩字节，也不是总时间。

分歧决定：若两类预算交换都以损失为主或只有稀薄改善，不做真实candidate/计时/证明；若有跨输入的明显独有改善，再固定一条具体交换规则做一次真实原encoder检查。保留全部失去原winner的反例；任何实际candidate仍要原协议总时间和完整gate。

更近先例见`last-distance-preaudit.md`：R11 continuation/gaprepeat、R13 rescue、R25 gap1均在原主hint失败时补查询，不等同于本次主hint成功的normal第三跳/lazy唯一来源交换；它们仍约束“免费rep”的假设。当前距离在此lazy域无法更优，已在该文给出推论，因此本次只使用上一已发射距离。

成本上限：原生编译和运行各240秒，建议15分钟外层cap；预期分钟级诊断，排队UNKNOWN。工作仅在临时Linux runner。本轮UTC09:18:52前冻结余量不变，最后90分钟保留验收/确认。证据位于`a15-native-proposed.json`及真实云端`r26-a-rep-shadow/receipt.json`。
