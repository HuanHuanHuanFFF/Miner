# 一个硬界pre-guard：在codec前结束fallback可能性

2026-10-27 01:45Z。根在本成本阶段追加12min纸面/有限模型判别。**未发现反例，且相对7737有具体可删除工作，故只保存一个独立成本候选。** 原7737、原数学资产均未改，不排CI、不开始publicADD证明。新候选仍只有B2公开四入口，单独diagnosticEntry试验此运行路径。

令正常输入排序后`X=mx·8`、`Y=shiftRightJam(my·8,d)`，`2^23≤mx,my≤2^24−1`；同号T=X+Y，异号T=X−Y。

- 同号最小T大于4；因`0<Y≤my·8`，最大T为`2·(2^24−1)·8=2^28−16`，d0、两个最大尾数达到上界。
- 异号d0已按magnitude排序，T为非负8倍数，所以非零至少8。
- 异号d1右移精确，`X≥2^26`、`Y≤4·(2^24−1)=2^26−4`，故T至少4，确实可达。d2/3仍精确且Y更小；d≥4有`Y≤ceil((2^27−8)/16)≤2^23`，T更大。d≥32的Y=1也在此界内。
- 异号T≤X−1<2^27，故统一得到：**T=0，或4≤T≤2^28−16**。上端本身是小于2^28的最大binary32整数可表点，整数RNE不会跨到2^28；数值转换后的biased exponent `Ehat∈129..154`。

因此固定数学域 **25≤eBig≤253** 充分保证`Ehat+eBig−153∈1..254`。T0分支仍先返回+0，包括域外eBig。区间不是样本调参：eBig24,d1的最小T4给postE0；eBig254,d0最大T给postE255，说明仅凭统一T界不能直接放宽任一端。

在非零准入域令UInt32

`delta=((eBig−153)<<23)+(hi & 0x80000000)`，输出`mid+delta`。

mid为正数位串`Ehat·2^23+frac`；UInt32运算是模2^32，故其和模等于`(Ehat+eBig−153)·2^23+frac+sign·2^31`。最终指数1..254及frac<2^23让各字段无重叠，恰等于原OR打包。`eBig−153`在word中回卷是此模恒等式的组成，不应误改为Nat截断减法。原GRS→ADD的RTO/低指数桥仍须独立证明；这里没有用实数等价跳过IEEE舍入，也没有新增native假设。

**成本因果点：** 在codec之前判断`eBig−25≤228`，然后准备delta；通过后没有任何fallback分支，codec返回只做一个word加法。源级未来使用只剩delta，7737为postE失败保留的raw-u/raw-v/abs值不再需要跨call。普通编译器仍可能选择共同callee-save frame或在前门spill，故不承诺一寄存器/无栈；必须核真正diagnosticEntry C/ASM。目标是移除已见两热栈写和postcall E/pack，并非靠函数长度或阈值网格推速度。

**历史差异范围：** 精确f7f的guardedAdd仍在toBits后检查E并回退；R17 sorted runtime仍有结果边界及fallback；R6/R7/R11 native input guard是已有机制，不能称为新发现。R14还试过whole-word rebias，相关桥失败/UNKNOWN保留。本次有区别的是GRS的统一4..2^28−16硬界，加pre-call正常域，再用mid+delta让原输入跨codec死掉；在上述已读历史中未找到同一完整机制的已测负样本。不是全库“首次发现”声称。

有限检查复用已有三组256点/case，不扩样本，另加21个端点/符号/zero见证。每个准入结果与原typed7737模型及整数normal ADD oracle一致，T界未失效；**不是Lean证明或性能**。Python生成器仍未独立Lean对齐。收窄有成本：

| 已见旧组 | 新pre-guard命中 / 原7737命中 | 新eligible整包等成本代理 | 零额外miss成本下10%whole所需降耗 |
|---|---:|---:|---:|
| 40168687803 | 9436 / 9754 | 31.304% | 31.944% |
| 40169957447 | 8815 / 9389 | 29.385% | 34.031% |
| 40171180249 | 9534 / 10258 | 31.740% | 31.506% |

它牺牲低/最高输入指数的一些旧命中，不能只计ABI收益不计域损失；实际eligible/miss成本仍UNKNOWN。模型不构成严格收益上界。

唯一产物：`Runtime-grs32-pre-guard.lean.inc` **1857B/75e3740aecfd3aee0f5209b00325495b4fcea64f487fae272be3e18817e68eb1**；完整原B2追加`Kernel-grs32-pre-guard.lean` **228686B/d3c550da05a3e91b5b037bed77623545dbe72af385d826ebc73236d2ed7ec2b5**。沿用同7根，inverse.patch恢复7737片段；namespace不变，按精确hash区分。manifest SHA **fd7667908f8de07b695f9f6cf68a160c91f66fa33f6ab774be3d1ff5fee11201**。全部Lean/codegen/publicADD/fullgate/计时NOT_RUN。

下一最低验收只有完整入口的实际代码判别：若仍需old inputs跨codec或保留相应两热spill，停止该假设；若达到只保留delta且postcall一个add，再评估是否值得原全路径配对成本与公共证明。DirectBias及已有验证优先；本方无CI、Git、本机编译，不再造边界变体。
