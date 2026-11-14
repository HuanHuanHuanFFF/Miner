# R27 FP proof 当前交接

21:28 UTC；实际开始19:47:45，共同截止00:44:43不延；ACTIVE。严格文件，仅本目录写，无本机Lean/native、Git、CI或nested agent。

- **P0 成本源绑定核查**：父7cc98e2b helper有2处log2word调用但自身/精确12/13与已存contract未见定义；已备自有显式绑定补丁，`NATIVE-COST-STATIC-BLOCKER.json`给新helper/完整carrier哈希。未改父目录、未Lean验证；请成本源freeze前核对/采用后更新整套pins。

- **接受链**：key-core4e1ed0b4四根＋RealStrict e004d3d7五根＋PrepareCore b8251fbb四根，三个公共run对应文件均exit0/AX仅允许三项；精确回执 `batch1/2/3-proof-receipt.json`。不是原all12 gate/replay。
- **下一proof**：`CI-REQUEST.json`现FP-004。实际guarded checker36599B/dfa924ad；真实prepare4459B/b8251fbb已过，下一getter/peak不得把core当fullproducer；getter/peak、finite widening分块待跑。禁止重跑已验单独Real。`BATCH3-HELPER-BUNDLE.json`供D选择7个13–38KB独立诊断块，不拼105KB未验闭包。
- **接口减负**：checker有限性guard可推出实际±的RNE等式；最终只留下radius finite＋forward error。13.4KB独立EndpointCore可隔离验证，36.6KB完整helper再导出exact total非零；均NOT_RUN。`CELL-AUDIT.md`保留signed-zero/minnormal/maxfinite边界。
- **新增成本证据**：`census/SUMMARY.json`旧R26两root共108个b1 MLP/NMLP/Mixer完整样本，全部输出FNV匹配旧native；69600 dots中69445接受/155拒绝，全部exact结果normal非零，proposal全对，拒绝仅保守界。eager word准备5009400词，逐miss不缓存懒准备158320词（3.1605%）；这是词数，不是时间比。整数RNE回放6.44M MAC共12.42s，未读确认数据。
- **最小native判别已具体化**：`LAZY-PREPARE-DISCRIMINATOR.json`＋`census/patch_lazy_prepare.py`仅改旧R26两块，60544B/b6a8680b；可选相对标量等价证明源61843B/a67b4dcd。原AST intake/policy PASS，Lean/native仍NOT_RUN，旧FP/fallback/all12仍UNPROVED。建议D选择完整调用成本再决定昂贵完整producer投入；没有自行派发。
- 退任12/27无native64/roundAt桥，未知许可整源未复制。新旧config不同，当前冠军倍数UNKNOWN。实际cached tensor构造、bias、fallback范围见`INTEGRATION-BOUNDARY.md`；不把热MAC装箱当已知瓶颈。

已处理父19:51/20:05/20:14/20:25/20:30/20:40。下一步按精确goal修复并收齐候选证据；D冻结后只用冻结前材料转独立follow-on。token/cache/连续模型CPU UNKNOWN。历史详情见`HANDOFF-20261029T2047-history.md`。

**任意分榜新取舍**：`MLP-DENSE-ONLY-ROUTE.md`指出可用specKernels保全12接口，仅实现dense.linear冲MLP（快照冠军33），无须把FP证明追加到218KB前任整包。建议ThinFP成本判别顺带MLP；如果有信号，再测ExactRuntime.dotOf懒fallback以去掉Word证明闭包。source约220KB只是组成估算，实际全源/证明/速度仍UNKNOWN，未派CI。

21:14已补旧batch8两root：72个完整MLP/NMLP样本全输出FNV匹配；共180个旧完整cell。`census/BATCH-COMPARISON.json`按分榜/batch拆统计，避免把Mixer点数占优的99.78%混用到MLP/NMLP；b8权重复用使懒准备词数比例明显高于b1。仍不报告速度比。

后续方向已隔离：四路Float累加18KB纸面/Lean草稿复用SUM3，L>=3可保持原半径；108旧cell整数RNE模型无半径反例、accept/miss不变。最新`follow-on/four-chain-v2-receipt.json`，未排CI、未声称native收益；不替代当前checker/prepare验收。

21:50新比较核查：父已核6个saved report-plan SHA，报告政策身份不再UNKNOWN；live API表示未重放，跨环境quick仍INFERRED。`MLP-REPORT-CHAIN.json`核33→13→12链，规划乘积0.60748，说明MLP只减证明体积而非更易赢。优先父强12 Thin成本；四输出保持scalarEq优先于本侧每dot四链重排，见`follow-on/FOUR-OUTPUT-REVIEW.md`。

**22:xx证明成本备选实测覆盖**：父narrow guard在108旧完整b1cell/69600dots上新增拒绝0，20358准备向量全normal/±0，proposal全E2..253且frac!=0。`NARROW-DOMAIN-CENSUS-AND-FIXED-SCALE.json`附原数据。新自写小root直接利用官方dot固定2^-298，推num.log2=E+171与roundShiftRightEven(num,E+148)，有望去掉泛Dyadic/Rat45KB链；源仅5KB级NOT_RUN，无新大闭包/未排CI，仍须真实guard与producer连接。
