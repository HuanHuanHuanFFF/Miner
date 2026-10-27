# CI10第一已见计划：原whole-pass ns，输出引用释放在C计时边界内

UTC 2026-10-27 00:42:11接手，15分钟上限00:57:11；只写本目录，无Git/CI/Lean/新agent。不改structural child包/新v2，也不继续runtime harness。

**边界结论：** 实际`BenchSuite_C.c:8698—8708`的runBmm pass是`lean_apply_6(kernel)`→输出checksum遍历→`lean_dec_ref(output)`→return。`measure`的timed helper在`8003`取起点，`8010`调用pass，`8016`拆解/释放IO结果wrapper后，`8017`取终点。原ns因此不是纯乘加：包括该次完整kernel的guard/准备/输出构造、输出checksum、输出本地引用drop及调用/部分IO包装开销。

输入A/B的Array.ofFn及pass closure构造在measure之前；checksum warmup先运行且不计时，inner=3次完整pass取min，打印在计时之外。最终保留的pass/input closure引用释放位于计时循环退出，不能把所有输入生命周期也算进每个ns。

**只确认C/source层的引用生命周期。** `lean_dec_ref`会drop引用；是否是最后引用、是否物理free所有子对象、LLVM具体内联/消除/调度及cycle成本，不能由这一语句确定。原BenchSuite对象和binary只有metadata SHA，未留raw对象、LLVM IR或BenchSuite ASM，故本次不能独立反汇编证明native cleanup。也没有证据把cleanup假定成计时之外。摘要不是phase分解或纯算术成本。

## 第一计划raw ns独立重算

只读取已见seed1927003：两份原log各156例/152 timed，checksum全一致；35个BMM label中34 timed。独立parser逐行重算，和保存结果完全相等，四运算→whole、所有route→BMM、均值三层均守恒。均值口径为**先每case两次ns取均值，再相加求份额**，不是平均百分比，不按MAC或work重加权。

| route | mean ns | BMM份额 | whole份额 |
|---|---:|---:|---:|
| DirectContinuous（12例） | 18,445,923.5 | 44.3371% | 7.1908% |
| B2（10例） | 14,491,968.5 | 34.8333% | 5.6494% |
| Packed10（6例） | 5,336,268.0 | 12.8264% | 2.0802% |
| B1（3例） | 3,121,241.5 | 7.5023% | 1.2168% |
| UnderflowZero（3例） | 208,426.0 | 0.5010% | 0.0813% |

mean whole=256,521,113 ns；mean BMM=41,603,827.5 ns，占whole **16.2185%**。process0 whole180,101,077/BMM31,097,423 ns；process1 whole332,941,149/BMM52,110,232 ns。整体漂移**1.848635×**，BMM1.675709×，Packed10反而0.899648×，不能用统一比例归一化或删慢样本；原因UNKNOWN。第二已见seed1927005 metadata exit124，整批collection失败不抹掉第一计划完整结果，但不能写跨seed稳定或score。

## 下一大路线的预算边界

[全部DC case排序和shape](DC-cases.md)保留两次原ns。前列为`bmm:ml:1`（5882×2×3×5，输出58820）、`bmm:subnormal:3`（2714×1×13×5）、`bmm:dense:5`（204×1×432×2）。12例涵盖m1..3、n3..432、p1..8，**本计划无n=1 DC**；不能把它概括成同一种inner-loop形状。

预算推论（INFERRED）：在其他case不变的这个成本分解里，即使DC全部pass成本归零，归属whole成本也只有7.19%；且其中包含不可任意删除的benchmark工作，不是可实现收益。整包10%若全靠BMM，需要降低本计划全部BMM成本约61.66%。因此优先调查可影响多route的输出/容器生命周期、批次/行准备成本，并保留短n大量输出与长n少量输出两端反证；没有新增阈值网格或声称分配/释放已被单独测量。第二计划完整结果未取得前，只作投入依据，不作总体上界。

绑定：run40425497337、源B2/622d；当前原件索引138项，本复核对21份相关原件重新验SHA/大小。C文件匹配before build身份；binary/objects后续不变仅由原driver成功路径的断言作证，不能冒充本次读取了raw对象。MainFull实际传给BenchSuite的bmm closure仍为原Submission.bmm。metadata在独立进程，原timer日志没有ROUTE19。

详见[review.json](review.json)、[原C定位摘录](boundary-C-excerpts.txt)。复验：`python -B competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-workers/anchor-323/route-boundary-review/review-route.py`。未读任何未见holdout；没有新测试、性能或采用结论。
