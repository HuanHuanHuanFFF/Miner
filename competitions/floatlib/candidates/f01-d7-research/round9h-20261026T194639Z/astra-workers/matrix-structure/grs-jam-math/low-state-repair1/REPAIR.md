# low_states资源修复：中点分解，原条件不变

真实失败来自peer run40429425157/38df646a：原完整探针 **5d0f2e8b1cef4927b0145e3579903d0795679ae722cb1b1ac645c29f6d3ca5bc** /230284 B。原日志在low_states声明6618:0报告whnf心跳200000耗尽，下游6629:8缺low_states常量是后果。没有数学反例，也没有18/9根通过的结论。原件是direct statement布局，直接位于artifact根；本脚本未套旧public-suite路径。六份自有原件已按peer原索引核字节/SHA并复制到ci-40429425157/。

新完整探针 **Probe-jam-variable-repair1.lean** /233592 B，SHA **b3724bc5cb19a85fdae25187d8700bb43233ab4098a9c0a92b97a36d0eaac496**；新独立片段 **JamVariable-repair1.lean** /6785 B，SHA **0704e9d7a79879a6576226a4237941b55a1a47ba2fcbff62d0671056dd1f874e**。旧a78/5d0f/c9均保留。原B2前226829 B精确622d不动，所有已有运行定义与公开算法不改。

修复只改low_states证明组织并新增6个小helper。lowJam_ge与lowJam_lt_even单独证明奇jam不越过偶数边界；decision_below/above/tie各自关闭一种判断；decision_midpoint按v<H、v=H、H<v三支，正中点再分r=0/非0。变量D*v只参与乘法单调性、加法界及ac_rfl，不进入omega；唯一奇偶omega仅处理v/H的模2与加1。最后low_states只用H=2/4/8三次实例化，并独立证明j<C。

原low_states的D/C/q/v/r、D>0、r<D、v<C、C4/8/16及结论均逐字保留；后续三个主桥及rne_jam亦逐字未改。未改maxHeartbeats、其他选项、主定理假设或舍入定义。不再有interval_cases或嵌套split_ifs的28态大合取证明。新资源是否足够仍须实际Lean；没有把组织更小当作已通过。

15根完整列表与HelperAudit.lean.inc在本目录：原4公开根、原5数学根、新6小helper。repair_low_states.py核原件、新旧接口、B2前缀、冻结依赖、固定文本intake/policy/options及256000 B上限；独立逆proof-resource-only.patch精确恢复原5d0f。**新源Lean / replay / 公理审计仍NOT_RUN**，该探针公开运算仍B2，无GRS速度结论。JamTranslate不包含在这次探针，仍冻结NOT_RUN；Dual b92不变。
