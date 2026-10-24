# R11 研究agent技术交接

本轮运行源码已按00:46:25 UTC目标冻结，窗口仍到02:31:25。以下只交接证据与下一轮证明/容量接口，不把新运行变体并入本轮，不改最终候选、cohort、helper或正式提交状态。

## 本轮保留结果与未胜边界

D已按预声明规则采用 **6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d**。固定首个干净D930及其后A/B两组新输入、新runner；相对原41的whole归一比为0.91622356 / 0.91672920 / 0.90641201，BMM为0.71805727 / 0.68973781 / 0.67609887，三组gain_p05均为正。这里是公共完整验证的归一成本，不是与当前私有冠军的直接计时或实际链上收益。

R的 **28b819 / 253315 B** 首次把40链、真实packB、原字NaN finish、尾行和输出前缀全部接通，完整929通过；实际C已消除逐输出lane40回调/浮点装箱，每块F40缓存一次，输出后释放，wordLoop与921的951 B机器码逐字一致。它仍有每g重复run边界检查与基址计算。

**e5b279 / 254988 B** 保留p=2 Cross与p>2 Wide，完整933通过。相对6c2d whole=1.00034702、BMM=1.00492783、gain_p05=-0.00918401，未满足预先公布的取代条件，未被采用。相对41的正向结果不能证明它优于6c2d；不能把没被采用解释为40链循环必然无效，也不能用重复抽样挑掉本次负结果。容量底座/备用路径及code layout不同，没有完整的Wide单组件因果控制。

原件和负面结果均保留：[验证索引](../../../coordination/development-status.json)、[真实929调用链](review-wide-actual-codegen-929.md)。

## 已验证的可复用基础

| 接口 | 精确证据 | 边界 |
| --- | --- | --- |
| R11WideRows4.wordLoop_row / within_row、实际within→输出桥 | 28b819，928 statement、929 full；e5b279完整933 | 原nativeA表示的真实完整算法；仍有run重复检查 |
| R11WideLayout.nativeA_span、Projects提升、emitBlock/输出前缀 | ea102356在925 statement；完整28b/e5内再次接受 | 完整四行块条件和真实packB仍需caller给出 |
| Panel4.packA_get、packA/block/wordLoop定义与终止 | 9a40118e，927/931原full；931真实机器码 | 9a的实际BMM仍是749b，Panel未接入口 |
| Panel4Bridge.packA_read、wordLoop_row、runDot_row、block_row、baseFor_rows | **0feec56a / 235258 B，937 statementPASS**，verdict a7a01fd7e8ac51513365bfd39a4f3384de7feed04435a46eecdcd1623113e632 | 用修正后93b1ac6f/6040 B资产；原cf1110草稿及ec112失败保留。没有新Panel完整算法验收 |
| Panel4Tail.prepare_read、dot10_shift、runDot_prepared、group/row/tail_prefix | **6e99f707 / 238501 B，935 statementPASS**，verdict90157372422f0be1876ec5f246cefb51dc38d312a36b26d9df5fea68acd836dc | 用ff487d27/9283 B资产；原f767/1afa失败未覆盖。尾函数未接真实Panel入口 |
| 因式分解tail：group_eq、row_eq、tail_eq及复用旧tail_prefix | **1b472298 / 251155 B，939 statementPASS**，verdictc7b6a78e12bbff00d8743a7f7f958fb74c4ef5ec2df02fc82b80cf7eda233432 | 新tail资产9d7bcb60/6165 B；必须同时保留旧R11WideLayout tail依赖，未接新入口 |
| R11WideGuardBridge.block_span / sized_block_span / sized_array_fits / direct_within_projects | **2dc2546f / 255400 B，938 statementPASS**，verdict0712256599ef118bae03a0955559ec66e0cf5bd6da839feef91b19079c05ffe4 | 新增四个定理，0新运行定义；原28b前缀不变，不代表检查已经移除 |

辅助statement没有替代新入口的kernel replay、axiom audit、checksum、完整gate和性能确认。未来必须绑定实际使用的修正资产，不能直接复用初版NOT_RUN文件的哈希宣称通过。

## 路线一：让已证明的边界进入实际接口

最小运行改变是让具体buildTiles直接调用已有within，取消每g run的三个重复检查。外层原guard已经给出n>0、n<USize.size及raw A大小界；b:Fin batch、h:Fin(m/4)给出完整四行块。已验nativeA_span/新block_span能证明最后一行跨度。

泛型builder只需新增一个**Prop参数** `nativeA.size = A.toArray.size`。output仍只准备一次真实A.map与packB，并把size_map证明传入；这些证明在运行时擦除，不需重新检查数组，也不需另造一份map。这样机器安全界只依赖尺寸；数值正确性则在真正的A.map/packB实例上由within_row和direct_within_projects闭合。

实际output/buildTiles/core与spec需要同步增加内部前提，由最外if命中分支给出；miss仍走原完整路径，官方bmm_spec的全Nat量词不能缩窄。把`base=(b*m+4*h)*n`与`packedB[b]`放在g闭包外另行核C，不假设inline会凭证明事实自动消除运行分支。

最小证伪顺序：先短statement验证改过的类型接口；随后实际C中确认producer不再调用run、不再每g比较三个界，并且没有重复map/新装箱；最后同场完整gate比较新稿、精确e5因果控制与已保留6c2d。重复检查是C事实，耗时占比和净收益仍UNKNOWN。

容量：e5仅余1012 B。把整个2085 B证明稿直接附加会到257073 B；即便在所有caller已替换后删除joinRows/run/run_row共1159 B，也只剩86 B给新接口。应复用现有nativeA_span，替换现有buildTiles_projects证明，不盲目保存重复见证定理。此方式的净接线体积尚UNKNOWN；不能删除同名Packed10Index.runDot/within，它们仍服务尾部和父本fallback。

## 路线二：Panel4局部准备接到真实输出

931实际wordLoop为825 B，F4一次向量读取替代四个A对象读取；十组SIMD、无热call/spill，但实际用了15个XMM名字。每k准备仍有四次ofBits和一次24 B F4请求；每块两个闭包的112 B请求也要计费。这些是请求/指令证据，不是物理RSS、分配器桶大小或性能倍率。

完整块可直接调用已验证的Panel4.block：在g循环外准备一次F4 panel，得到G个F40后按四行输出。新[block_projects草稿](astra-panel4-projects.lean)用具体原A、真实packB、已验block_row/baseFor_rows关闭Projects；目前该932 B连接定理尚NOT_RUN。可选短statement配方为exact0fee + 1238 B现有lane40接口 + 13639 B已验writer + 932 B该桥，共251067 B；只在内存核过policy，没有写新Kernel或派CI。

**真实输出必须改为只全局准备packedB。** 不能把Panel builder接到旧generic output后就认为旧A.map被消除：旧emitTail仍使用nativeA，会保留整份global map。应把完整块交给Panel4.block，把每batch剩余0..3行交给局部tail；尾部数值地址用rTail*n，raw finish/NaN回放用原 `(b*m+first+rTail)*n`。新输出还须把Panel块与局部尾前缀合并到原bmmSpec，保留巨大Nat/短n/形状miss回退。

最早的数值反例已保存：shape[2,5,5,11]中正确raw base45返回0xffc00022，错把local base0用于回放会返回0x7fc00011；native结果在两者判断前都是0x7fc00000。[有限字模型反例](astra-tail-raw-base-counterexample.json)不是Lean或独立oracle，但能直接抓住这一接线错误。

真实caller还须证明/检查：没有全局A.map重复准备；每块panel仅准备一次；F40不持有panel指针；最终Array.ofFn闭包销毁后不把panel带入下一块；尾数组只在该batch尾部准备一次。931未捕获外部Array.ofFn最终销毁，当前只有所有权推断，不能写成已测生命周期或RSS下降。

## 容量必须按依赖闭包算

[精确字节账本](astra-next-capacity.json)绑定e5。旧机器家族10105 B、nativeA_span570 B、旧tail2031 B、待替换flow3848 B、待替换producer1480 B，合18034 B。全部只是假设caller已改完后的条件替代量，不是删除授权。

现有完整Panel namespace、原5516 B投影草稿和9283 B尾稿合19474 B；即使先删上述旧段、还没放回新flow/producer，已达256428 B。采用已修正投影可省约22 B，仍不足。因此完整generalPanel尚不是可交付候选，需要证明因式分解或额外、独立闭合的无用依赖审计，不能删来源/运行义务或改256000 B上限。

**局部tail因式分解复用原emitTail_prefix，必须保留旧rowIndex/emitTail/emitTail_prefix共2031 B。** 939实际新尾稿为6165 B，较9283 B减少3118 B；不能同时把旧2031 B算成已删除。条件删除旧machine10105+native span570+flow3848+producer1480=16003 B，添加Panel namespace4675+已修正PanelBridge5494+factoredTail6165=16334 B，得到**255319 B**，此时尚未放回新flow/producer，只有681 B余量。短探针装得下不等于完整含Cross的下一稿装得下。namespace计数4675 B不含末尾换行，实际拼接另计。

更有希望的下一轮容量路线，是在共享RowStream层分离numericBase与rawFinishBase，用一个Prop类型的逐k read等式复用原group/row Prefix证明：普通行numericBase=rawRow*n，局部tail为rLocal*n，rawFinish始终指向global原字。数组仍作为直接运行参数，read等式仅在证明中出现；不要把每MAC读取改成返回Float32的高阶回调。这个共享接口会影响正常fallback，必须核旧调用的默认参数/特化开销、实际C借用/装箱及全gate，不能当成纯删除。新的完整体积仍UNKNOWN。

未来比较固定原Underflow最外1039 B、Cross路径和原NaN语义；不新增宽度/阈值网格，不用缺失同场控制的跨seed差值归因。先解决具体类型闭合和容量，再投入单一实际候选与全成本验证。


本公开技术摘录仅包含算法、证明、原CI和容量分析。当前唯一状态入口为 development-status.json；下一轮收益投入见 next-investment.md。
