# R7检查点10：四个原生终点守卫的自比较稿

2026-10-22 20:17 UTC。新增受控候选`f01-r7-self-nonnan-guard/Kernel.lean`，SHA256 `6b00a89d1b1dd1fc3537d54871298583ff969169c22bd07b594eda5ab0a77e24`，175012字节，父本b1696ff9，状态 **NOT_RUN_NEW_INTEGRATION**。静态大小/哈希/导入/禁词检查PASS。

只把实际NativeFinal.dot、originalSum、Packed10.finish、最终sum这四个终点`result.isNaN = false`换成`R7W04.nonNaN result = true`，后者执行`result == result`。具体全输入iff把证明前提运输回已经通过的nonNaN归纳桥；不改迭代顺序、前缀、layout、标量、准备或NaN payload回退。Packed10.finish与dot的定义连接保持一致，最终sum仍通过原originalSum_spec。未将这个变化混入ee/627逐步prefix守卫，因此可独立比较。

真实固定Lean源显示isnan为外部runtime函数，BEq为header中的内联C比较。网页W04已独立证明真实Float32/Float32.Model所有构造下`(x==x)=!x.isNaN`，Inf也通过守卫；不能用命题等式`x=x`代替IEEE Bool BEq。完整75行源及38声明/32定理公理审计通过，供此候选只取BEq部分，省去未用的<=证明，原数学体不修改。

W04实际GCC13.3、x86_64、O2/O3、显式no-fast-math/no-finite-math-only下，自比较叶函数生成ucomiss/setnp，分类入口仍调用lean_float32_isnan。完整proof模块还生成额外私有match辅助函数；不能把叶函数三条指令当完整模块成本。该网页编译器不是官方gate的bundled clang；本候选实际完整gate/C生成/25轮收益仍须新验。

E盘原件：ZIP SHA `123e3beae3a72d0d9fa17bb40758d25b29427194db039c507fb88ca5a2abff88`（203332字节），报告SHA `27afa52d883986c0aef98e9c6dff27049bd8a5b6b244f4a2d1e6b78fd88b7eb7`。CRC与104条manifest一致，主源SHA `3668cbf3f7bab305ace60be4cdec39e5eb6d78c222d6c1630d699ba95d5fcaff`。完整入口[web-deliveries.json](web-deliveries.json)，当前5轮10个E盘文件。

若b169/7ac反馈已回收，D可在既有组合上优先测此低变更量的全输出守卫，再按槽位检查ee与627。所有优先级以D统一协调为准，R没有派发额外CI。

20:15 UTC左右启动W05：规范化Float32层的全输入add/mul同态、NaN分类双向等价及首次事件必quiet的具体桥。仅传固定公开库与已经GitHub公开的c760精确源URL，先用GitHub工具核实可读且Git blob63eb803c/本地SHA逐字节一致，记录public-nonnan-source-receipt.json；不传私人源、日志或性能数据。此任务可能消除当前事件修复后的冗余分类/冷分支，但先要求闭合真实数学桥，性能仍UNKNOWN。目标25分钟回收，R继续处理现有候选反馈。
