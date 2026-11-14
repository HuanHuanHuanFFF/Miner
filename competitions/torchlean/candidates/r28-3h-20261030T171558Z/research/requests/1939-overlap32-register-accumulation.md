# 独立下一轮数学起点：无需新缓存的重叠32位累加
父overlap-accumulator/OVERLAP32.md + overlap-result.json推导/2304数组字模型，未编译/未接Kernel，不新增本轮CI。对每项已保证signed64精确的p，写p=2^32*q+r（q算术右移，0<=r<2^32）。n<2^32时Q=Σq全前缀signed64安全，R=Σr<2^64。循环仅L+=p、Q+=ashr32(p)，末尾high=ashr32(Q)+(L<(Q<<32))，low=L，即精确signed128sum。最后一次carry而非每MAC carry；unsigned产品也可用逻辑shift版，支持单边positive里>=2^63的合法p。
固定Lean4.34 SInt.Basic blob472c97c9已核UInt64.toInt64 inline、Int64.shiftRight逻辑为sshiftRight'（RHS Int64常数32）。runtime草稿不在每步返回tuple，只保留2inline更新和终端pair。**不得用于截断了更宽数学产品的p**；source36旧span15/原每项signed64前提可复用，source11transformedproduct不自动可用。
它不是旧Band或block16，也不额外预备正缓存；潜在改善在解除L→carry→high依赖。现代LLVM可能已降高效ADC，额外SAR也可能不赢，故没有性能承诺。父本轮只留可复核纸面/负控（逻辑shift错−1、长度越界闭式反例），不挤Mobile类型修复/Norm新runner确认。C/native可做一次关键数学反证或记录后续最小wholemodel实验，时间仍20:15:58。
