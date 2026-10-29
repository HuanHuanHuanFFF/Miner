# 下一轮投入决定（R26证据，不改项目规则）

本轮没有购买到算法判别证据：首次native目标09:20未达，09:26:56才派发；原setup完成后driver缺loguru，修环境后的09:37:13派发于09:39:19进入，已超过自身09:38 startguard。两次均无编译/measurement/fullgoal。它们解释本轮为何没有性能结论，不证明任何算法无效。

下一窗口先解决一个可观测里程碑：原精确源完整Lean stdout与实际native整包成本。优先修D拥有的自有bridge环境载入；区分“停止新派发”与“已接受运行按截止预算完成”的语义，不能以排队后的同一dispatch cutoff直接空跑。保留实际原始失败，不追改历史回执；新运行另保存plan/source/cutoff。官方工具和正确性义务不变。

数学优先队列：keyCore7648B→real16117B→checker24252B；prepareCore4432B／Tail1618B。首次失败必须保存完整上下文再改。105/140KB组合均已有失败prefix，继续拼更大闭包不能缩短首次类型判别。RNE endpoint接口反例已明确；复用原fixedpoint/monotonic pullback与SUM3 round_grid，不重做gamma分析。

成本优先队列：先实际fp-word-conv6/ad9bde3e与原retained同generator/MainExact/编译选项、完整边界、逐项checksum、保存原ns。尚无成本读数时不把FP、word128或block16称为大收益。若取得失败率／fallback占比或native profile，用它决定下一批，不从旧单点推断整包硬上界。

保留两条实质不同的高上限机制：FP64 exact-product加误差认证以消除多数整数MAC；预对齐UInt32因子与block16→128减少宽回退工作。第二条需先接真实scale/bias/zero outerguard和缓存metadata，成本探针each128控制并非D当前nativeLoop，对照必须新增实际基线。原小缓存收益只是保留版本，不作为主攻。

资源判断：本轮3Astra+开发预留2已达项目上限；未开Pro。token/cache/CPU无读数，不能声称达到60/20/15/5真实配额，也不能把文档字节数当有效成果。下一轮在有授权时间窗内优先让CI吞吐与研究小源成熟度匹配，先获得一条可证伪输出再扩展。
