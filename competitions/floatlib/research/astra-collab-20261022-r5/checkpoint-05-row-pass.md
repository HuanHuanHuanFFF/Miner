# R5-05：首稿真实完整通过，逐输出生成代码变化已核实

R已独立读取604原始verdict/gate.log及实际C，不仅转述D反馈。精确97cbe074首稿首次完整gate通过：statement、Submission和VerifyFull重放、3允许公理、12类25轮、score通过。CPU AMD EPYC7763，seed604。证据及原始路径/哈希见row-output-first-result.json。

同批父本三类bmm最小耗时为0.994336/0.992252/0.992192 ns/MAC；首稿为0.873772/0.871546/0.866818。分别对固定随附参考归一化后，新/旧=0.8771623852，观察到约12.3%减少。候选三类spread约1.02—1.03；候选所配参考的spread达1.42—1.76，仍保留慢样本。其他未改标量运算也出现漂移，整包差异不能全部归因本变更。这是发现批次，不是冻结新runner确认，更不是对实际现任冠军的晋升证据。

同源码C SHA d31a083f78787c301301d00b585a08ebe291975bb580cdf502a1710af4f92775。逐输出row回调实际只有0次Nat mul、1add、1div、1mod、1次borrowed数组get；原outputFromTiles为5mul、2add、3div、3mod、3get。四次行基址mul和一个add移至每行row构造器；batch/row两层get各在相应外层。两层flatten在真实C中仍调用Array.append，额外搬运并未消失。观察到完整调用收益，因此暂保留首稿；不能将C静态调用点当作机器指令或独立耗时归因。

## 给D的组合审查

已读integrate-r5.py，不重复编写组合。它把RowOutput.row中的finish替成R5Finish.finishAt，纯lazy地址版本二者定义相等；原有限输出行基址已外提到每行，这个组合的额外收益可能小于lazy单独对父本的收益，不能相加。打包变化只要两条core都引用同一新的packB，结构桥仍保持。

若进一步采用checkpoint-04的W02 finiteBits数学桥，请注意可达调用：只改Packed10.finish不会改变R5Finish.finishAt的isFinite分支。需要同步把实际被row调用的finishAt改成同一个`let u := result.toBits` + `R5W02.finiteBits u` + `ofBits32 u`，raw基址仍只在else中绑定一次。这样finishAt对新的Packed10.finish仍定义相等；若一个用旧guard、另一个用新guard，则必须显式应用finish_expr_eq，不能继续靠旧rfl声称已接通。完整组合须独立gate和C确认。

W02全部原件已回收、固定模型定义也由R独立复读，完整c09候选保持WRITTEN_NOT_RUN，供D按当前队列选择；R不新增布局候选。全部12ZIP+12Markdown已重新校验，见download-index-final.json。605/606及后续完整组合由D自然收齐。
