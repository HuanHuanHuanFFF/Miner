# R7检查点11：808实测、负结果及共同证明修复

2026-10-22 20:33 UTC。R见808已终态，独立通过GitHub连接器回收原始ZIP，GitHub digest `858306dae43e0005858ccad33a272f9a23d3c9e47713c301e924ca804a3c3a7d`完全一致，394057字节/63个原件，CRC通过；只落R目录并读取，不执行下载代码。入口`ci-recovery/808/receipt.json`与`nan-combination-808.json`。D仍为唯一CI协调者。

## 实际结果

CPU AMD EPYC9V45，seed808，原版current-public-v2、25轮及完整原spec/重放/三公理/fingerprint。

- **9a2a05cd NaN-fullpath FULL PASS**。新样本整包归一化0.87944122父本、BMM0.74967332。与806的0.80670725/0.65188410分别保留，不能挑旧CPU更好值冒充新确认。
- **7acff965 raw quiet guard FULL PASS，但未见收益**。整包0.89394852父本、BMM0.77107454，相对同批9a2反而更慢约1.65%整包、2.85%BMM；控制项本身也有约1%变化。本轮不采用该守卫替换，不再扩相近mask变体；其具体raw分类证明仍可复用。
- **b1696ff9组合statement FAIL，未进入性能阶段**。精确错误为NativeFinal.dot_eq第3262行` simp made no progress`。无运行反例，也不能把两个已有PASS组件的组合当PASS；整批failure并不抹掉前两份FULL PASS。

## 新命名proof1（优先替代旧待测稿）

从已通过9a2实际定理直接运输`replayEarly_eq`：将先`rw`再要求`simp`取得进展，改为完全限定的`simpa only [...] using (replayEarly_eq ...)`。原失败b169不改。`repair808-lineage.json`逐字节确认以下四对源码仅同一两行定理证明不同，全部运行定义未变；仍须真实Lean重验。

|新候选|精确SHA256|字节|用途|
|---|---|---:|---|
|f01-r7-nonfinite-combined-proof1|39a99b3213adf8ef40734c62b420f09a127b385d7129fb89b1467f0ad7c52e2b|173096|两个已验组件的组合修复，首先闭合|
|f01-r7-self-nonnan-guard-proof1|3baa785ee05745d2929af7208c6105d7e2f645a8c46b87e6e631e2165aaa9a6c|175060|四个原生终点的自比较守卫，相对39a|
|f01-r7-native-repair-proof1|0de8643c8992cdbff0242fe59bdbf97ba1dac10725351eb89c446aa463367a55|176344|矩阵native前缀＋精确事件修复，相对39a|
|f01-r7-sum-native-repair-proof1|cff840b1ace5c20cdc3b905c28aabeb716f8b9468d238e1b18f4ce8c58286a80|188325|求和native前缀＋raw后缀，相对39a|

**以上全部NOT_RUN。旧ee309626/627c31a8/6b00a89d没有跑过，它们继承已知失败的旧证明，因此停止排旧稿，改用各自proof1。** 原运行机制及最低证伪见检查点07/10，预算/权限不变。D可先statement快速定位证明，再按实际槽位进行完整候选配对；R没有派发/取消CI。

## 网页并行

W05继续完整canonical原生桥，主tab1，目标约20:40 UTC。20:25 UTC另开tab2，明确核实GPT-6选中与Pro5/5，W06仅研究公开Lean的守卫在终点返回/循环/数组映射上下文中的实际C/汇编，关注外部call和跨call浮点保存，目标约20:45。不传私有源码或计时，不由叶函数推断完整收益。下一检查点约20:50或更早实际CI反馈。
