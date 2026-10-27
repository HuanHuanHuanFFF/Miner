# R15：三组B2验收根独立复算全通过，交开发采用与收尾

时间：2026-10-25T07:29:50.431960+00:00。固定源622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58，cohort外部SHAe934782573a07d2cb8607a3325d18eca33ba3b15cbcc9ceacabe2d4989f78018未改。R自己的astra-independent-cohort-check.py从三组原始verdict、Kernel归档、work、summary/order/contracts和46个冻结文件重算；D/A/B全四算子原版gate与25轮都齐，源码/参照/指纹都匹配。

|组/run|whole/DF|根连续随机流p05|原门槛|
|---|---:|---:|---|
|D40168687803|0.9599930079|+0.0201530999|PASS|
|A40169957447|0.9376153311|+0.0342006923|PASS|
|B40171180249|0.9110868883|+0.0761701529|PASS|

原每run摘要A的p05=+0.0332948511与整cohort连续随机流的位置不同，均正；原始回执保持。所有阈值、原始慢样本、此前负D未变。首D不是三组最佳替代，三组全部达才交采用。根最终审核astra-cohort-independent-D-A-B.json，非新benchmark。

新鲜GitHub jobs原响应已保存astra-runner-observation-final.json：三个标准ubuntu24 jobs均success，runner ID分别1000001518/1519/1520；物理宿主UNKNOWN。旧回执当时缺runner字段仍保留，不回写历史。

B2 C/汇编分层核对已完，root实际重验4个Kernel/C绑定和12个函数体SHA，见astra-b2-C-independent-review.json；源码里8B双F32记录、一次准备、typed read、无热点Natstride乘法等得到诊断C佐证，SIMD/call/spill均仅statement对象，不冒充timed对象。ADD差距另root重验13函数与118185B前缀（11原字节一致，2仅SSA），参照漂移很小不足以解释7%差距，原因仍UNKNOWN，失败b116/f529不豁免。

数学/Lean/性能结论和未编译tight储备、旧负例、公开source调查与权限已集中astra-conclusions.md。R仅交研究/审计，不自行改retained、manifest、模型、Git/index或CI；请D按已授权原采用工具更新状态/新模型并核实其范围，正式在线准入/排名/奖励仍与本地确认分开，无正式提交或资金动作。

R继续到07:39:28研究窗口终点完成证据与交接，不新开运行机制。190旧研究公开HOLD；R15部分screen依赖本地旧HOLD helper仅为机会调查，别为公开复现而改名抄入190批次；正式Kernel与原版CI不依赖该私有研究helper。
