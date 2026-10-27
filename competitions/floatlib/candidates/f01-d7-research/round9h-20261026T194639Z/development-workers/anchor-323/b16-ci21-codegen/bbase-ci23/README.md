# CI23：GO，仅跑预定义f494完整D

**缓存真的省掉了普通输出的重复B-base工作，未发现新增闭包/动态call/核心spill将其替代。** 精确源f49458b9…/255745B、声明/两模块/20根回执及92原件hash已绑定；不重做数学或CI21全raw复核。原whole≤.97＋正p05、完整gate/controls不变，不预告收益或采用。

| 实际机器边界 | CI21旧体 | CI23实际体 |
|---|---|---|
| emit的乘法 | 入口r*n、bi*n已CSE；lane循环仍有×p@0x182 | 只剩入口r*n@0x4c；从lane循环0xa0起没有乘法 |
| 列组基址 | finite/NaN test前每lane加4g@0x1c6 | group中一次+4g@0x301；emit只做baseB+j@0x102 |
| group→loop | 原调用 | call0x1f4/rel1f5，同一四lane核心；返回后才在0x232/0x27f算bi*n、×p |
| group→真实emit | 固定专化函数 | call0x609/0x718，rel60a/719直接传cache，不是helper替身 |
| 栈框架 | group104B、emit136B | group104B、emit88B，均6push |
| 核心 | 实际redArg | 整段native body含relocation文本与CI21逐字相同 |

实际C也确认：group在runDot之后构造baseB，一次调用emit后释放；emit参数11→10，group/emit都无新heap closure、apply、Float32 box或ctor，native没有间接call。baseB为普通小Nat时tagged immediate；BigNat构造/RC与存活到emit结束的成本仍保留。F4和A4/B16准备、finish、输出/checksum及析构未移到计时之外。

同前次边界：bi=0原本跳过残留×p，不能将所有有限值输出都算作省一次乘；该域主要减少重复+4g/control。bi>0普通小Nat路径的×p由每lane变每group一次。有限值to_bits和NaN replay仍按原分支，不将cold replay提前。准备、fallback和四lane核心未借新let改变工作范围。

GO是对真实代码减少的判断，不把乘法数、栈字节或帧大小换算延迟。cache可能产生的冷Nat/布局效应及完整生命周期净收益，仍由这一次完整D回答；不另开路线。statement对象不是未来timed ELF。未读取D22/D24/确认输入或结果，未Git/CI/Lean或改任何源。

产物：`review.json`、`native-evidence.json`、`all-originals.json`、old/new C和group/emit ASM摘录及`receipt.json`。
