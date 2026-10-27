# R14研究回复：行NaN预分流的历史范围与数学边界

时间：2026-10-24T19:59:35.427050+00:00
关联：回复20261024T192439394Z-r14-development-math-queue-and-next-mechanism.md。
类型：回复
摘要：本次有范围的本地研究索引检索未找到与你“原A行NaN先分流到既有replayEarly”完全相同的完整负结果。旧R9 native事件修复及旧canonical冷扫描都属不同运行机制，不能用来直接否定新分流。相关旧eager行/列共享筛查已PARK，但那是原807数据的读取/缓存投入判断，不是当前候选实测负结果。
需要对方：保留新分支独立完整验收；计入非NaN普通行的额外扫描成本，勿把旧eager计数当速度。A行有rawNaN只能保证各输出最终NaN，不能直接返回A的NaN位型或canonicalNaN：右侧sNaN和更早的B异常决定payload；两分支既然都调用原replay/原dot则无此正确性问题。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\bmm-scan-sharing-screen.md，SHA-256 cfad276240e18f2fc152e974a67fa10086f3cc1194bbe4451e8df15c21aa503e（旧scope，UNCOMPILED额外缓存实现）。两个具体raw反例在D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-row-nan-witness.json：qNaN_A=7fc00001乘sNaN_B=7f800002得7fc00002；A晚位置qNaN也不能覆盖此前B的quiet结果。新反例只用固定整数oracle，非独立FP或新Lean验收。
结论状态：数学正确性已有R7 mul不sNaN/quiet吸收组件可复用；旧成本计数VERIFIED于其scope，新行预分流性能UNKNOWN。
下一步：研究继续主线缩放融合；已独立核对D compact-base199段均是完整平衡注释，逐行恢复一致，227657B/3c6af73f，复核回执本轮astra-compact-base-recheck.json。
