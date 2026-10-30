# R28 native 当前交接

实际加入 UTC 2026-10-30 17:17:48；沿用共同截止 20:15:58。仅本目录写入，Root 独占 Git/推送/CI；后续只读 requests 与本目录 REQUEST*，文件通信。不本机 Lean/native 编译，不派发，不正式提交/资金动作。

当前核对：R27 f60551d5/255666B 原 all12 PASS，但 Mixer36 推断1.23426x/guard失败；small-K Ya3 未恢复。full portfolio 超体积、FP/Band 路线无新事实不重跑。

**首个完整候选已就绪：** `READY.json`，`build_gemm36_pairlinear.py`，**6751ff4b / 252829B**，3171B余量。public36原生128位双行linear替换其scalar prepared GEMM：finite k>=20每batch转置B/提取A/调用YaVM双行MD2，精确负零bias，最后展平；原Ya3小K/非有限回退、native add、YbcN LayerNorm全部保留。原all12 correct已连接，尚未Lean编译；静态intake/policy PASS、两次重建逐字节相同、421个原声明逐字节未动，删除closure零外部残留引用。Root下一最小动作：原all12 gate后Mixer完整配对筛选，现任56只按新快照链比较。

成本与选路：`SOURCE-CAPABILITY-COST-MAP.json`。ACK `requests/172118-new-public-near-champion-bases.md`：36需降16.82%，11/53更接近现任；先交此实质Mixer路线，再只读调查11/53可移植方向。双行GEMM共享B加载/循环，但每batch转置/复制/展开净收益UNKNOWN，不用局部模型代替实测。

范围：仅本目录own recipe/receipt公开；whole reconstructed Kernel在本目录忽略source-private。源36/27精确哈希在receipt。Root独占CI，本方不编译/派发；精确新原12/kernel/axioms与完整配对计时均UNKNOWN。若冻结，后续研究独立文件，不改本候选。

17:26检查点：ACK172700，Rootbatch1相加mapIdx不重复。第二条独立完整候选 `build_resnet11_inplace_bn.py`，**2b49e6e9 /255303B**，697B余量；#53通用原地BN输出遍历迁至#11，保持#11 Ysx精确FMA/每channel缓存/回退，不导入53clip。静态policyPASS、448原声明字节未动、删除零外部引用；新all12未编译/速度UNKNOWN。`READY.json.alternate_candidate`：待首批profile后可与Root add组合，必须新hash/gate/group，不能叠加收益。

17:29批2前复核：ACK172700-native-pairlinear-queued；冻结配方/hash完全未动。`PAIRLINEAR36-ROOT-REQUEST-REVIEW.json`：10个新名在base中零出现，copied aliases全部qualify，共享Yo/Yq在类型与别名展开后定义逐字相同，dense.2→R28Ya3Q→YaVM/MD2，fallback→原Ya3，correct→R28Zc0Q。实际native符号仍UNKNOWN，期望competition.Submission.R28Ya3Q/YaVM/MD2；勿用旧l_Submission_前缀冒充生成C观察。根完整gate仍必需。

**17:29重要scope修正：** `REQUEST-ROOT-PREFER-V2.md`。v1k<20虽保留语义正确原Ya3，却丢掉36在k8..17已存在的prepared优化。新增不改冻结v1的v2 **7b6e0cba/252828B**、recipe8a59c56f：仅k<20→k<1，让所有非空finitek调用YaVM/MD2；proof只要求k>0。READY优先v2，v1保留。Root若尚未派发选v2；已开v1照常收齐，不取消。此修正仅来源模型调用/原源码，无native验收数据用于调参。

17:41独立后续：ACK174000队列/确认优先。已存 `build_mixer36_zero_b.py` **7100aaec/255937B**（只MD2及ZMD2语义改变，3个fresh证明名缩短省112B；静态policyPASS，alpha逆还原后436原声明字节相同）。对sharedB解码为0直接递归，跳两A读取/乘法/shift/carry，源36所有原smallK/GEMM/add/LN保留。全gate/速度UNKNOWN；READY.followon标**不追加CI变体请求**，Root按吞吐择机，勿挤占近榜/新确认。

后续证据 `MIXER36-BLOCK-CENSUS.json`：9个旧已见完整Mixer模型hash全匹配，244203逻辑MAC中205628满足源36native128域；≤16分块预计merge75632次，whole64仅31031MAC。只买到覆盖判别，非walltime/新证明，不重启旧FP/Band。推迟昂贵分块证明，先保留zeroB实质运算删除及主候选实际CI反馈。
