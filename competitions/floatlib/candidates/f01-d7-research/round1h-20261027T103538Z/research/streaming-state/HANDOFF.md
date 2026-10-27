# R21 streaming-state — 真实证明错误已修v2，完整成本待验

实际10:39:21加入；共同截止11:35:38不延期，研究现已关闭。最后源/地址静态回执11:32:41，最后协调状态写入从11:35:36开始；此后仅按根要求收尾。v1保留，v2于11:11:39冻结后未改；D唯一Git/index/CI。最终状态收尾时间：2026-10-27 11:36:50 UTC。批6过期后到只收证据，不修新源。

- **当前冻结源** `v2/Kernel.lean`，237212B，SHA **4e36c931825b4c152933208987f066c95a5a0aada79cdea67202a045a7953ba4**，同19根，audit文本SHA **e23696a1d248072f60bfa737892ccc3035aaa27407771bab2408c46f66a2091a**。v1/5bbf在CI404929只有emit_size apply/Array类型统一错误；v2唯一+121B proof修订，149非证明声明全同，逆patch恢复v1。原文本检查PASS；**新Lean/重放/公理/C/性能NOT_RUN**，D待单槽承接。详v2/HANDOFF.md。
- **D入口映射已纠正**：v1研究manifest保留历史歧义；v2 manifest按D schema令helper_audit_source_sha256=Kernel4e36，auditfile另记e236，显式19根list和固定v8工具/hash。不要把audit文本hash当Kernel，不修改v1历史；D规范v1清单亦已核读。
- **完整调用而非MAC叶**：controlPair/streamedPair为两行×任意p，包含输出Array.mkEmpty、共享replicate初态、全部k、两遍原Packed10.finish/NaN replay、Vector输出及状态生命周期；p0直接空输出。外层专用loop，通用storageLoop只用于证明；public四入口仍B2，没有新fullbatch路由或#336结果继承。
- **唯一runtime选择**：安全Array.mapIdx整列consume，保留固定mapFinIdxM原边界；callback仅使用传入cell并捕获a0/a1、Braw、rowB，不读取/捕获旧state。原逐slotmodify未提交草稿保存在preliminary，不是第二候选。actualCtorReuse/closure0/COWfree尚无事实；第一k共享Cell、两slot替换/RC/COW、活跃标量/FPspill及最终F2析构全部计入。
- **等式链尝试**：State=Vector F2 p，advance_get→两lane hstep→loop_eq_storage→finish0/1→rows_eq→长度→pair_eq；使用A固定dd00510c通用接口。19根包括4旧public、2通用接口、13新定理。只有emit_size出现真实error，不由“其余未报错”升级整模块通过。A负责既有public源与batch/奇行证明，本方不改A文件。
- **成本范围**：未打包DC两行codec源级数4np→n(p+2)，逐输出k序和2np mul/2np add不变；不是速度/whole上界，不适用于B2/Packed10已缓存B。#336只绑定B2，1.6287×323，不用1.304校准。真实caller要求见C-ACCEPTANCE.md，first/shared/steady/finalize全计，不能拿leaf证明noalloc。
- **隔离后继**：first-sweep片段3283B/**ae1bdea0837ecc43b167d72479b802ad82148928f54b63a17ae8dd3efc0b94ba**（NOT_RUN），35组符号树含n0/p0一致，−0×1见证证明不可删初始+0；只提删zero填槽/首map准备，不提删p个Cell分配。MatrixDriver1694B/**ba2dfe460a76a24f607bc9f05001550267cc94639c49d85e27d41fe0bb7f3cb1**（NOT_RUN）按batch内m/2对＋原odd行，完整prefix/size公共桥归A；无Kernel/CI。两者均不改变冻结源，token/cacheUNKNOWN。
- **末段协调回执**：根转述D的不同运行体7de9完整D40493865047为whole0.99151657/BMM0.94317027/p05−0.024864，未达采用、不A/B或reseed，不能继承为本4e36的成本。D批6已启动本4e36/19根及两数学探针；尚无本源结果。本方不占单槽、不自行派发，过共同截止只收已启动证据，不再修源。
