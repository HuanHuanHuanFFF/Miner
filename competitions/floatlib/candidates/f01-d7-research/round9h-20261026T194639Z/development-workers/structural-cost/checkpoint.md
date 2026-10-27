# R19结构成本检查点

更新时间：2026-10-26 20:12 UTC。首份判别19:56落盘；接手19:51:54，阶段上限20:36:54 UTC。仅本目录写入，无Git/index/CI/本地Lean。使用huan-open-research；交接按prompt-entropy、交付轻量复核按verification-before-completion。tokens/cache UNKNOWN，CI占用0。

**决定：不重开A4B2或p≤8分派实验。推荐筛选双列原始A机器字索引＋output一次范围守卫，无A面板、无跨行tile缓存。** 精确B2为`622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58`。当前源5848行已包含p≤8连续输出；R16真正A4B2完整gate正确却BMM慢4.34%，不能再声称漏删转换或漏内联。

新判别由`audit_structural_cost.py`约0.1秒完成：重算精确B2、保留C/MainFull和三组已完成采用输入/数据哈希，并核对原artifact索引；`source-cost-audit.json`含12个选中C函数、调用边界、原行号与每shape事件。旧k体仍有两次Nat加法、Nat比较、A.getD大小/默认分支、原A转Float32、一次B2读取；只在终态分配F2。准备B一次；输出仍原finish/NaN early replay。静态C不是动态阶段计时；旧ASM仅诊断，不作MainFull成本。

| 622d已完成组 | BMM实测整包份额 | 整包降10%所需BMM降幅 | B2触及class整包上界 | 按该上界所需B2降幅 |
|---|---:|---:|---:|---:|
| D40168687803 |16.142%|61.950%|14.769%|67.712%|
| A40169957447 |20.023%|49.943%|17.149%|58.312%|
| B40171180249 |19.058%|52.472%|19.058%|52.472%|

所以**尚无支持整包10%的强预测**；把全部BMM加速2倍在D/B也只给8.07%/9.53%。B2上界是混合class上界，实际目标/循环耗时下界0。新方案的源级新增准备数据分配为0；编译器新增闭包/装箱UNKNOWN。旧计划每组条件平均n仅4.732/6.895/11.744，因此通用runDot每组4项guard有成本风险，推荐将两项guard升到output一次。

**产物可交D：** `Kernel-hoisted-b2.draft.lean`，SHA`9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1`，234277B；8条新增helper均有完整证明尝试，**NOT_COMPILED**。`implementation-design.md`给精确替换范围、证明链及MainFull C判别；`hoisted-draft-manifest.json`绑定构建器/片段。`validation.json`只验证静态delta和25018个有限地址步骤，不是Lean或浮点正确性。

**下一决定：** D若投入，先核精确原完整入口及选中C；热体仍有Nat/default分支或出现A准备/重复B准备就止步。C符合再按原完整发现门槛；不降低D+A+B。另一具体选择是DirectContinuous/旧B1 raw-A的同类全局守卫/USize读取，不改既有路由，覆盖数据在`route-coverage.json`。F10已有USize；旧Temporal四k布局、R9 NaN事件、R18数值负结果不重包装。本阶段已形成可实现交付，未占编译/计时名额；D继续本轮9h研究。
