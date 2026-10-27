# GRS变量jam数学子题：短草稿就绪，NOT_RUN

承接 exact 的暂停分解，新增 `JamVariable.lean`，**3477 B**，SHA **a78a153405a2b4a5fd29ac704d77114a8f650ac6120591700f4d2ad05afe5595**。无占位证明；先剥q块，28个v低态后只剩D/r线性比较，最后pow_add接任意d及k2/3/4。唯一omega在已固定C/v的`low_states`，不枚举d、不把原p/D*q塞给omega。更强中间结论允许任意D>0。

纸面关键：C/2为偶数，RTO不能把非中点送到中点；r=0时保留原q奇偶。28态系数检查通过，无d/p采样；不是Lean。已保存k1反例(p3,d1)与仅偶C反例(D2,C6,p17)。原FloatLib两个API文件按pinned commit重新核Git blob与本地字节；具体API和完整分解见`PROOF-NOTE.md`/`verified-api.json`。

**边界：Lean、公共ADD规格、C/性能全部NOT_RUN。** 尚需实际tactic编译，以及真实加/减T→jam、leading/k、小T、Model.add字段等桥。没有大Kernel、没有CI、未写exact目录。当前没有请求抢占DirectBias或Dual的槽；下一有条件动作仅是这份短数学源的真实类型检查。

本子题20分钟窗00:00:49—00:20:49 UTC；若c598真实目标到达立即回Dual。R总截止02:28:21 UTC不变。
