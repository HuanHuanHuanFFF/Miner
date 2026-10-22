# R6 九十分钟冲冠

窗口：2026-10-22 13:17:45—14:47:45 UTC。目标为取代评测时现任冠军；尚未达成。用户收益准则：耗时份额×可实现降耗，再考虑完整开发、证明与验证成本。

本轮发现官方刚加入私有套件评分与新的公开练习套件，见[适用范围](../../docs/suite-transition-20261022.md)。旧十二类实验继续收齐，下一采用决定需看新版公开suite；旧冠军推算不跨套件继承。

- 当前唯一状态：[development-status.json](../../coordination/development-status.json)。
- 精确窗口、运行与路线：[window.json](window.json)、[原始回执核验与逐项结果](summary.json)。
- [Astra交接](../../coordination/astra-handoff-r6.md)及[研究入口](../../research/astra-collab-20261022-r6/checkpoint-05-suite-and-proof-repair.md)。
- 新公开套件：[原版gate独立验证计划](../f01-d6-public-suite/suite-plan.json)。其nested suite回执单独验收，外层statement通过不代表它已通过。

| 本轮机制 | 实际结果 | 决定 |
|---|---|---|
| binary32单次位转换 | 705完整通过；同机矩阵约慢0.6% | 保留证明，运行版本停放 |
| 单区间加法守卫 | 706旧版与719新公开suite均完整通过；新suite整包归一化改善约0.3% | 无明显冲冠收益，暂不替换当前完整包 |
| 低指数乘法删重复守卫 | 706完整通过；旧整包无稳定优势 | 停放微调 |
| 整数普通乘法／46-47最高位 | 707完整通过，旧整包约慢14% | 停放该实现 |
| 偏置舍入／其加乘组合 | 707、719精确源码statement失败 | 保留未闭合目标，不采用 |
| non-NaN往返和输入反推 | 706四个实质引理及helper编译通过 | 尚缺实际Inf运算桥与finish集成 |
| 远距26-bit吸收 | 707仅两处规格接口错误；两行接口修复65cd1338在720新suite完整PASS；该样本整包约慢0.4% | 保留gap26全输入证明，停放此实现 |

新版public-v2的当前8eb包已实际通过152个计分case、26cell、25配对轮。seed719当前包耗时占比为add18.3%、mul21.5%、sum10.8%、bmm49.4%；bmm:specials单组约占整包17.1%。这些是当前包完整调用的工作量加权结果，见[精确结果](public-suite-results.json)。旧十二类占比不再用于新套件的投入选择。

下一轮优先用小而有效的完整调用诊断比较矩阵特殊值回退、多shape下padding/布局，以及sum的Inf桥接。可实现降耗仍须实测；W03的抽象后缀吸收仍有具体NaN输出分类前提，不当作已验实现。

原有409份本地草稿和R6四个ZIP/四份报告均已独立校验，见[preservation-check](preservation-check.json)。GitHub本窗发生[Actions Results延迟](https://stspg.io/44w94j036yc8)，已完成job与顶层元数据分列，全部已启动CI自然结束后收齐；不取消、不重复派发。最终活动作业与窗口消耗见开发状态。

研究窗口已按14:47:45截止停止新增，11轮CI全部终态、原件已回收。最终720成功；8eb当前包已在新public-v2的719/720两个新seed、新runner完整通过；未采用微小/退化改动，冲冠目标仍未达成。
