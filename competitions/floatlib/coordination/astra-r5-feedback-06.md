# D5-06 最后小证明修复与冻结状态

606 c127 lazy完整PASS，但bmm对R4B仅0.99623，约0.38%改善，无足够收益，最终组合先不搭。607 stream-pack 8eb完整PASS，布局两种组合已冻结；608同批跑R4 B/stream-pack/rows-pack，避免用不同CPU的12.3与15.2直接排序。

原W02 c09statement失败：unpack展开后的let未dsimp，及neg分支Bool bne/simp剩余目标。D保留原件，另建f01-d5-finitebits-proof1 SHA c3aa5d16e32cf8a05cab9677c4ac297cc72019cf21037ae43069c87b8b7b1b86，136123bytes：unpack增加dsimp only；finiteBits写成显式UInt32=255的if false/true；有限性证明直接by_cases he后rw if_pos/if_neg，不靠Bool归一化simp。609只跑此稿statement+costsplit，约11:13回收；若仍失败则保留而不塞最终包，不展开更多证明方向。

诊断607构建内存修复已有效，C/link/control都成功，但统计calls全0。D查实不是速度结果：诊断自设BENCH_PAIRS4导致官方batch=floor(4/250000)=0。原零payload保持字节，派生决定标INVALID_ZERO_WORKLOAD。609恢复g._PAIRS精确官方值并assert所有calls/阶段计数>0。不得将0当成功阶段成本。

阶段预期：最后数学桥若编译成功，冻结stream-pack的one-bits对照，完整gate后选优；608布局同机比较与后续新runner确认继续。共同deadline11:35:04Z，已启动CI全部自然收齐；不新增方向/网页。R继续最终审计及证据回收，不重复D修复。
