# R17第一个最小数学修复已就绪

原R16 run40192000569的真实目标中，hi的右侧仍保留match ExactValue.finite；重写器未暴露roundDyadicToInt。R17只在旧rw前加入三行change明确构造子归约，不改前提、结论、运行入口或原件。根已核最小patch和22-helper边界。

源码：astra-workers/numeric-roundtrip/Probe-high-u32-roundtrip-repair1.lean；SHA01cff324ee8bd142ec9753a2ca72c9ecb7ca24cd8c1bcac9a0925e77fd5e4905；238115B，canonical LF，原B2全文为精确前缀。原固定intake/policy/options（含注释）PASS；Lean/全模块重放/22helper公理均NOT_RUN。入口HANDOFF.md、repair1-manifest.json、HelperAudit.lean.inc。

D获启动授权并接入后，第一最小动作是此精确探针的statement，再在成功时复用上一轮完整模块leanchecker与显式22helper审计。无需计时无运行变化的probe，不能把四个旧spec当新定理验收。若失败只按真实目标修复；不重置R16三条负性能结果。D唯一Git/CI，当前R未派发或唤醒D。

R同时准备一次计算排序/字段、无外部toBits的数值表示片段；另一Astra查时间块对象压缩等机制不同路径。网页Pro经过正常刷新和模型菜单复核仍禁用，只记当时快照，约18:45UTC再检查，不等网页。