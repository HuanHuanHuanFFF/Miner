# R25 收尾：下一轮机制与最低判别实验

本文件只提出两个未实现、未计时、未证明的新实验方向。现有证据支持继续研究 tinyPC 的匹配覆盖与原 encoder 符号集合成本之间的取舍，尚不支持可支付表现：主线程的最新独立确认中，已 gate 的 end4 与 tinyPC 各四个新主块均为零份额，NT2 也为零。主线程的同快照代数审计将 end4 归零定位为被 #626 支配，将 tinyPC 归零定位为被 #619、部分视图另被 #546 支配；这属于公共配对测量的官方公式投影，不是私有集、正式 admission 或收益保证。参见 [主线程代数回执](../score-algebra-29697.json)。

## 精确起点与证据边界

起点保持现有算法路由，不增加文件名、特定新长度或结果驱动的路由。

| 起点 | Rust SHA-256 | Lean SHA-256 | 当前状态 |
|---|---|---|---|
| combo：`r22-595-chain-halfhead` | `57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275` | `4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6` | 已有完整 gate |
| end4：`r25-astra-end4` | `03ec0aa4e617d622755e85324a9d4fbc77ef74e6572485b3170e2790681ed8e6` | 同 combo | 原版完整 gate 38125243582 通过 |
| tinyPC：`r25-astra-tiny-pc8-proof1` | `5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00` | `3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8` | 原版完整 gate 38130996700 通过 |

tinyPC 只改变现有 row12，采用 head-only PC、skip6、lazy16、4-byte probe、record8，正常匹配仍经过原验证。end4 改变现有 4-byte/dp1 PC 路径；O 中 400000 字节样本实际走 row1，12000 字节样本实际走 row12，196608 字节控制实际走 fallback。L 的 combo len3 PC 统计来自 row0 的 3-byte/dp2 路径，不能移作 tinyPC row12 的直接损益证据。

以下均为已执行诊断，算法因果解释另标为推断。

| 证据 | 已验证观察 | 不允许的外推 |
|---|---|---|
| K2 原 encoder 观察器 | tiny-config：combo 2487B、3094 token、89 match；tinyPC 2155B、2276 token、210 match。二者均为单个 dynamic block；literal 活码同为 78，length 活码 5→27，distance 活码 7→23。LL/D 符号向量 clone 3426→4328 / 265→923；长度与距离 lookup 比较 1891→7114。原配对计时的 tiny encoder 约 250–252µs→322–331µs。 | 计数不能线性换算可收回时间。CL clone 251→215，不能把所有树的工作都算作上升；更少 token 也不等于更少 match lookup。 |
| M 稀疏发射 | 固定五个 length 码的 native M 为 2441B，只保留 combo 之上 46B 改善，较 tinyPC 丢失 286B；另 27 输入 token/output 全同。原配对总时间仍比 combo 高约 0.72% / 0.47%。物理 token 改变后续 fold，M 并非同一强匹配轨迹的单纯重编码。 | 不能由 M 推出其他掩码一定可行，亦不能由符号减少宣称已加速。 |
| L 原 token 码价 | combo 的 PC len3：77589 个已知价，58 个缺价；76172 个 match 更便宜、456 个 literal 更便宜、961 个同价。已知局部 gain 626968 bit、loss 627 bit；每个 distance 码域都有获益反例，整域改 literal 均有已知净损失。 | 全引擎 2441 bit 局部 loss 不是 PC loss，更不是实际重编码收益；不能重开宽泛 len3 远距离阈值。 |
| O 固定合成域外诊断 | tinyPC 的 12 个 active row12 例全部更小，差值 [-1272,-828]B，中位数 -1015B；end4 的 12 个 active row1 例为 3 更小 / 4 同大小 / 5 更大，差值 [-25,+103]B，中位数 0。各组件的 12 个 inactive 主例及 3 个 fallback 控制均完整 token/output 相同。 | 模板、种子与长短前缀相关，非 12 个独立统计抽样；未测 time、官方或私有输入，不能给成功概率。 |

K 原始回执见 [K2 receipt](../38132193695/counts-k2-native/diagnostics/r25-tiny-encoder/receipt.json)，M 见 [native feedback](../astra/tiny-sparse-native-feedback.json) 与 [配对成本](../cost-m-screen-vs-combo.json)，L/O 的完整反例分别见 [L feedback](len3-price-feedback.json)、[O feedback](heldout-quality-feedback.json)。

主线程新增的 [冻结 token 活码覆盖诊断](../tiny-symbol-coverage.json) 验证 decode/input SHA 与 K 完整频率向量一致：tinyPC 的 210 个 match 中，169 个使用 combo 未活跃 length 码、覆盖 3027 原文 span 字节；96 个使用新 distance 码、覆盖 1132 span 字节；并集为 174 个 match / 3330 span 字节。原已活跃 length 码的 41 个 match 覆盖 6907 span 字节。这些是覆盖位置数量，不是边际节省字节；新增活码并非可以先验删除的少数无价值离群项。

## 方向一：保留强逻辑匹配，按覆盖选择小 length 符号集合

**假设（INFERRED）**：M 的固定集合最小可发长度为 11，浪费了真实短匹配覆盖；将强匹配规划与受限物理发射分开，并让固定小集合容纳短匹配，可能比 M 保留更多质量。这个方向不能承诺恢复 tinyPC 的 332B 收益，也不能承诺节省总时间。

依据是冻结 tinyPC 的 125 个长度小于 11 的 match 覆盖 678 原文 span 字节。已有固定五码离线 replay 的 literal tail 总计 838；同一强 token 流拆分后为 3010 token，而 native M 为 2954 token，SHA 不同，二者都 decode 正确。这直接暴露 fold 反馈差异；已有 replay 尚未取得原 encoder 的大小与计时结果，不能把“隔离反馈”写成改善。参见 [已有 replay](../sparse-offline-replay.json)。

最低判别动作是在任何输出实验前冻结**一个**规则：沿用 combo 的五个 length 活码规模，保留最短有效匹配的码域和 258 码域，其余三个按强逻辑 token 中的覆盖字节计数选择，固定同分顺序。这里只提出规则，不据已见输出选具体掩码，不扫码数或掩码。先以冻结 tinyPC token 为输入，用原 encoder 比较原 token、已有固定五码 replay 和这一个覆盖规则；全部保留 token/output/input SHA、decode、实际 block、LL/D/CL 活码及 clone、lookup、短匹配与尾部 literal 覆盖。也要记录拆分产生的额外 match 数；较短/较近的码在原 encoder 的反向 lookup 中可能需要更多比较。

若短覆盖仍大量变为 literal，或拆分与 lookup 成本抵消符号集合缩减，或实际大小接近 M 而明显丢失强父质量，则在观察阶段停止，不进入候选证明。只有原 encoder 的实际大小与未计时工作统计支持可检验的成本空间，才考虑一份 native 实现，再用固定 28 输入配对总时间判断。不得使用 O 的 27 例调规则；它们可作冻结后的反例集合。

**证明接口风险（UNKNOWN）**：逻辑 token 与物理 token 的 `nt`、`tokLen`、已解码前缀必须分别维护。合法 `MatchAt` 可为片段与 literal 提供安全依据，但不能直接复用一次发射的 `nt+1` 后置条件。需要新的拆分终止、长度上界、输出容量、scratch 初始化与前缀一致性义务；若原地扩张覆盖未读 token，还要额外证明读写不干扰。强父完整 gate 不能覆盖新增缓冲或发射函数。新增 token 遍历/存储本身有真实成本，不能省略后再声称预算不变。

## 方向二：只诊断 distance 码首次启用的覆盖门槛

**假设（INFERRED）**：对尚未启用的 distance 码增加一次覆盖要求，可能减少 K 中 D 活码与建树工作，同时保留已经启用码的短匹配。这来自现有 ET 的 `et_take` 思路，不是新机制类别；与 L 已否定的全域 len3/远距离剪裁不同，目标是当前 tinyPC 的 min4+ 路径和每个码的首次启用事件。

最低动作仍先用冻结强逻辑 token 做一个原价 replay，不加搜索、hash 或新文件路由。仅测试现有 ET 式规则：已启用 distance 码保留原 min4；未启用码要求覆盖至少 min4+8，否则该 span 发 literal，且不将该码标为已启用。所有 accepted match 仍保留父验证。阈值不是待扫参数；只用这一个已有规则作判别。

必须区分“最终未启用”“仅延迟启用”和“立即启用”，保留每次拒绝的覆盖与实际输出损失、最终 D 活码、LL/D/CL 工作和 lookup。若大多数拒绝只将启用推迟、最终码集合不变，即使局部判据漂亮也应停止：它支付质量损失，却未减少最终字母表。若少数码消失但带走大量真实覆盖，或原 encoder 实测损失大于可接受的已观察质量余量，也停止，不把局部 bit 差或 span/8 当作补偿。

**证明接口风险（UNKNOWN）**：新状态需证明 distance 码索引及 bit shift 有界；拒绝后 literal span 必须保留已解码前缀与终点。若进入 native，还要明确 `used` 是发射历史的保守集合还是当前 token 频率集合。后续 fold 可能删除早先启用该码的 token，单调 bitset 不代表最终频率；不能隐藏这层近似。隔离强逻辑轨迹有方向一的遍历/缓冲成本，内联处理则会影响后续 fold，必须另保留原轨迹反例。安全性可从父 `MatchAt` 延伸，质量最优性无需证明，但新状态与真实提取接口仍须完整 gate。

## 明确不重开的路线与实验顺序

R13 已覆盖 packed AoS 的直接先例，不能把半位互换或复制布局更名再跑；[packed 审计](packed-head-preaudit.md) 已保留最初只查 R2/R3 的遗漏与更正。L 不支持宽泛 len3 距离码域删除，R13 原价改写的负面结果也继续作为先验反例。O 的 end4 正负混合结果不支持“更多索引总会改善质量”。

同距相邻 token 合并仅有 10 组、5724 span 字节；125 个短 match 中只有一个长度 5 的 match 落在这些组里。因此它不能作为修复 678 字节短覆盖的主要机制，本轮不列为第三个实现建议。

下一轮先冻结上述一个规则和对照，再作原 token replay 的未计时质量/工作判别；有信号才投入一份 native 和配对总时间。只有冻结质量组件的跨 runner 总成本留下实际前沿余量，才安排新的真实提取与完整 gate。当前两方向均为未实现假设，不增加本轮候选、CI 或优化样本，也不改变两份已 gate 组件的冻结字节。
