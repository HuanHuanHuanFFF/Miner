# 唯一 short-shared A 变体：已冻结待验

已在5c5e通过912真实statement后生成Kernel、manifest和source-review，冻结待D安排新版本语句与完整gate。父本verdict SHA为3c85a3c7eaa396d57d5c21ebdd5539cf9b5e3b040184ac069893ed71b7400343；父本完整gate仍在914执行，新变体不继承该结果。D统一CI/Git。B scalar-call只保留在网页原包，不另生成变体。

确定性构建：输入为已冻结5c5e父本，以及E:/Download/R11-W03.zip中的A原件5645。全部908实报修复保留，尤其新dot8_lane fallback也使用显式zero8归一化。实际完整源254550B，SHA256 `7cad7df494da6004b9e4b202f4d09b838ef8d4b79ba6fe934eea7287784fea28`；余量1450B。verify.py只读核对当前Kernel、父本、构建器及原始静态策略；build.py默认只重建dry-run/planned.patch，不改Kernel，--write拒绝已有源。

变化仅为n1/n2且四个实际B起点相同时，先完成一至两轮全部输入解码，再展开八条原序mul/add链；保留每条链的初始+0。混合B起点和长n仍走原P12路径；不改变finish8、rawNaN replay、W8、尾部与最终输出。n2把12个输入标量放在部分和之前是源码形状，不能保证C/LLVM实际调度或寄存器常驻。

证明新增shortShared_lane，并把dot8_lane分为实际短分支/原循环分支。pack/wordLoop、lane_update、rowWord_eq和四spec均保留父本修复。build.py逆向还原完整5c5e，并运行同一原gate静态策略。仅静态PASS，Lean/C/asm/full-gate/性能均NOT_RUN或UNKNOWN。

第二个独立逆向检查移除恰好三处proof2修复后逐字节恢复网页A原件5645，绑定运行实现来源。声明顺序已核对：read32→shortShared→shortShared_lane→dot8→dot8_lane。helper自身在其他n上没有所需规格，但实际入口由n=1∨n=2守卫关闭；p在内部证明中仍通用，外层仅p2。n0/空维/小行数/超大机器长度走原fallback；混合B起点走原P12；尾部总定义getD、原raw NaN回放和输出筛选保留。

完整成本检查重点是旧n2,p2大batch机会，不是峰值microbenchmark：该旧852案例共有11029组，8823组四行B同址。所选分支可免17646个P12记录和8823个局部Array（源码对象计数），仍有F8/W8、全非NaN时每组16次源层终结原语调用、输出索引/构造与尾部，另外增加短n判断；跨batch短组可能重复B同址判断，实际C须核查。不能把14.81%旧BMM案例曝光或80%组数当收益预测。

代码生成须来自实际候选对象，核查P12/Array分配是否消失、转换是否穿过部分和、SLP、spill所保存的值及完整输出消费。若未来与单次序列化guard结合，当前朴素叠加会超源码上限，不能直接叠加。所有正式准入和冠军判断另行验收。
