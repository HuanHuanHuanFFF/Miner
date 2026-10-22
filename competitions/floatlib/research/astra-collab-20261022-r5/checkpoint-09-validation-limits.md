# R5-09：数学桥修复仍失败；阶段探针混入未计分raw

609/run39768383550原始回执已回收并由R读取。c3aa5d16修复稿statement仍FAIL，未产生可审计候选C，也无完整kernel/公理/计时通过。按D5-06约定停放，不再新增修复实验，不将它塞进最终包。

## 最小剩余证明障碍

full-build-output显示同一个指数同时出现`= -1#spec.exponentBits`与`≠ (-1 : BitVec spec.exponentBits)`的分支；这两种常量没有被统一为定义相等，rfl不消解上下文矛盾，具体binary32下if_pos/if_neg也找不到预期模式。这个问题被之前let规约失败遮住，首修只消除了第一层遮挡。

已独立读取固定Lean BitVec.Basic：allOnes由ofNatLT(2^n-1)构造，Neg则经ofNat模2^n；不能未经规范化把两个源码表示当成rfl。下次最小动作是统一泛型unpack引理的全一常量到固定源使用的表示，先编译这一小引理，再接原已无报错的exponent_toNat/allOnes_iff。这里是精确未闭合的Lean脚本目标，不宣称第二修复已经写成或验证。原c09、c3与各自失败日志保持原样。

## 13次调用的计数有效，但不代表正式计时阶段占比

609的profile-result.json现为checksum_matches_control=true，3次独立进程每次calls=13。nativeA累计约0.95—1.00ms、packB约1.06ms、tiles约1.58—1.66ms、output约1007—1016ms。它确有运行负载，不能再标成零工作量；但也不能据此称“正式bmm耗时99%来自output”。

R新读固定官方BenchBmm.lean，SHA646c471678d9d4e1c99e8fe5735920b5f21371e642e0a4e6af0dac5f9d4deb9e，原件在upstream/official-BenchBmm.lean。runBmm对dense/relu/wide每类先执行1次checksum pass，再执行默认3次计时pass；raw只执行1次不计时checksum pass。因此恰为3*(1+3)+1=13次。探针在kernel core累计所有调用，没有区分类，raw可能大量触发昂贵的精确软件回退。

profile-control.log中三类正常bmm各约0.50ms，raw标记false且正式时间字段为0；计数器的约1秒输出累计不能由正式三类计时直接解释。需未来把每次调用或每类阶段数据分开，才能求计分域的成本占比。当前正确状态是“有效混合工作量计数，正式计时阶段归因UNKNOWN”；不能把raw的0时间字段当作实际无成本，也不能从总累计反推出raw精确耗时。

这是对已有609数据与固定官方执行顺序的审计，没有修改bench/gate，也没有新增作业。D继续608布局同机比较和最终独立确认。
