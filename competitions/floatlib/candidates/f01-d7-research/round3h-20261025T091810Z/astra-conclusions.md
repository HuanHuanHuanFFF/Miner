# R16 研究结论

状态：研究内容已冻结收尾。窗口为2026-10-25 09:18:10—12:18:10UTC。以下记录截至12:14前；最后数学探针的最新状态以[开发回执](development-ci-job-40192000569.json)为准。当前研究索引为[astra-status.json](astra-status.json)。

## 本轮策略与投入

根AGENTS已更新并由D提交推送a015ac77。使用writing-for-agents与prompt-entropy；研究沿用huan-open-research。策略优先有大幅整包收益依据的机制，60/20/15/5是初始研究token投入优先级，不是本轮已实测达到的比例。主控负责方向和关键检查，子agent限题推进，D独占Git、CI与采用决定。

先推进A4×B2矩阵复用和原生MUL重打包；接口与完整成本反馈后停止两者晋升，转向单次原生UInt32转换的高N ADD。必要的源码容量调查有界结束；未用无收益的组合或新种子恢复失败候选。当前三个性能负结果均保留原始慢样本。

## 已完成的真实参测结果

以下相对本轮保留版B2；小于1才更快。每项绑定精确源码和25轮原版完整gate。单次发现样本不是未来成功概率，也没有替代独立确认。

|机制|精确源SHA前缀|完整gate run|整包比|目标算子比|gain p05|决定|
|---|---|---:|---:|---:|---:|---|
|原生MUL字段重打包|c972fd72|40183711165|1.030550|MUL 1.081897|-0.089853|停止当前源晋升|
|四行A4×B2复用|2a937bb0|40183711165|1.007850|BMM 1.043437|-0.055889|停止当前源晋升|
|高N单次原生转换ADD|f7f4702f|40188276536|1.294551|ADD 1.873923|-0.290976|停止当前源晋升|

三者正确性通过而性能失败，不能称为性能突破。R独立核对原件哈希、完整gate状态、逐项权重和bootstrap算术：[第一组](astra-first-cost-check.json)、[ADD组](astra-cost-check-40188276536.json)。原发现门槛未降低；没有候选进入确认或采用。保留源码622d8394…与模型9222bdf6…；未正式参赛提交。

## 可复用资产与未解决问题

- 矩阵实际C实现了无Nat、转换、分配和RC的数值内循环；未发现输出重算/Float32装箱事故。额外panel、tiles和两个闭包存在，不能从源码运算减少推出收益。精确耗时归因仍未知：[成本复核](astra-workers/matrix-architecture/cost-review-401854.md)。
- 原生MUL实际选中C确为2cast/1MUL/0table/1toBits；调用后的活跃值及回退代码膨胀有证据，真实寄存器保存成本未知：[选中调用路径](astra-workers/scalar-representation/c972-probe-review.md)。
- 高N ADD完成了实际UInt32转换、字段重打包、精确对齐和原回退的全输入证明接线，但当前实现更慢。保留低N/零回退边界、溢出/消去反例和全部失败源：[交接](astra-workers/scalar-representation/next-add-u32/entry-stage-handoff.md)。
- 最终ADD选中C确为1cast/1toBits，无Nat、分配、闭包或幅度重复计算事故；八处指数排序比较、重复字段提取和调用后原输入活跃确实存在。四份回退是互斥拒绝路径，不能按全函数静态计数冒充单次工作。标量ASM缺失，周期归因未知：[最终C复核](astra-workers/scalar-representation/final-C-cost.md)。
- 后续数值往返接口确实可展开；高N UInt32→Float32→UInt32的RNE整数桥已有完整证明尝试及政策预检通过的依赖闭合探针。尚未形成新运行候选，编译/显式helper审计状态由后续回执决定：[数学桥](astra-workers/matrix-architecture/future-u32-roundtrip/math-bridge-handoff.md)、[探针清单](astra-workers/matrix-architecture/future-u32-roundtrip/packaged-probe-manifest.json)。
- 401871的B2 ADD慢对照不能由次正规缩放因子解释；表与该批dense输入边界已检查。计时回调/ELF和真实时钟缺失，原因未知。原异常保留；同输入新runner/反转顺序只做诊断，不是新独立成绩：[排除证据](astra-workers/scalar-representation/control-anomaly/conclusion.md)。
- 401897同源码、同1626007输入的复测恢复B2/41 ADD约0.90758、整包0.76873；旧ADD2.90662、整包1.41321仍保留。排除确定性的纯输入解释，不区分runner、顺序、代码生成或时钟原因：[诊断回执](development-final-diagnostic-feedback.md)。

## 执行经验与后续边界

纯文本intake/policy/options检查必须包含注释；本轮一次“not an axiom”说明文字被原policy拒绝，不能当数学失败。`Dyadic`必须绑定实际FloatLib类型。对已展开的目标反复`dsimp`造成了额外编译往返；修复保持运行逻辑不变，原失败回执未覆盖。

下一步先验证数值往返桥与实际重打包成本，再考虑完整新入口。不得把未编译草稿、有限模型、源码操作数量或当前三条负机制的组合写成收益。源码裁剪只解决容量；新调用证明可能引用旧叶定理，必须对新源重新检查。

网页Pro本轮现场核实为额度用尽、选项禁用；未新增网页请求、上传或下载，没有新增ZIP需要解包清理。用量只保存可取得的控制会话计数；子agent精确token为UNKNOWN，缓存输入和reasoning不重复累加：[计数](astra-usage-snapshot.json)。

最后数学探针先被换行字节一致性预检拦住。D保留原件并统一换行，参测源为4e97be71…/237959B；40192000569于12:10:59开始派发，晚于原12:04最晚开跑计划。记录时仍在途，不能宣称新helper编译、内核或公理检查通过。已启动作业由D收齐，不取消、不自动续试；研究截止不延长，若回执晚到须与窗口内研究分列。

本轮策略已实施，但没有获得可采用性能提升，也没有证明token配置最优。完整研究产物、有限模型、源码容量计划和所有负结果留在本分支，D作为唯一协调者负责最终提交/推送与开发看板。
