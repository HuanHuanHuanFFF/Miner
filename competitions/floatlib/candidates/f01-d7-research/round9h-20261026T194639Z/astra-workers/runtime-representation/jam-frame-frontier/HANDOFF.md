# Jam frame frontier 当前决定

22:07 UTC：**值得一个冷fallback边界代码生成探针，不预测周期收益。** 真实b271 BENCH_PLAN lam3成功路径无call/栈读写；r14仅push/pop，16Bframe的六处栈访问全部在reject路径。r15/r12/rbp/rbx仍有成功路径用途，全部保存能否消失仅INFERRED。frame-evidence.json绑定C/ASM、寄存器live及无LTO独立MainFull编译命令。

这不同于旧W11：60f普通路自身有两ofBits调用与spill，停放noinline LowScale仍有效；现在拟隔离整个R19Base.mul冷fallback，让Jam成功臂有成为叶函数的具体机会。Lean noinline不保证C边界，必须看actual MainFull只声明/直接调用wrapper而不再内联旧body。

唯一完整源Kernel-jam-cold-fallback.lean：255173B，SHA256 1d15cbf9723de827597cf677b937151b10911e31b446e969ce05e01f5563c552；净+296B，42roots，逆patch恢复精确b271。只加普通noinline wrapper＋spec alias并更换guardedMul的fallback实参，arith/guards/fallback值/四spec保持。冻结b271原件hash已核未动；新Lean/C/replay/全gate/性能NOT_RUN，无bias/范围/多变体。

下一最小判别：真实MainFull成功臂仍无call/spill且完整frame/save缩减；miss须核直接wrapper调用/尾跳及额外ABI成本。旧diagnosticEntry未改，不能拿其frame代替public结论。若旧body仍内联或5save/16B未实质变化则停；机器码变小不等于收益。若进入成本比较，须有b271同算术control，B2仍保留基线。DECISION.md详边界，cold-wrapper.patch为替换补丁，HelperAudit-jam-cold.lean.inc保留原40＋新增2根。不自动排CI；b271首完整成本继续优先。小阶段cap22:14:24，主窗不延长。
