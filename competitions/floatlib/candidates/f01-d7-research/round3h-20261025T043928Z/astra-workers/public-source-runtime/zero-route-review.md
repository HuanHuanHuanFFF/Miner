# ±0 × finite：旧低路的反方成本核对

接受时间2026-10-25 05:13:12Z；范围仅精确df5c、`ex+ey<128`中的零乘积控制流。没有候选、Lean、编译、bench或CI。该报告回答源码成本问题，不给机器周期或whole收益。

**结论：前置raw-zero guard可以省掉当前生成C中可见的一段准备工作，并非完全重复当前同位置的判断；但现有roundLow和roundP都已经product==0早退，绝不能将fastLog2、RNE、Float32转换或外部调用计入此域的可省成本。最终Clang是否已合并/提前这些判断，仍UNKNOWN。**

## 两个rounder都先退，selector没有先退

精确DF源码：

- Kernel:2267–2279，`LowScale.roundLow`首先检查product==0，直接按sign返回0或0x80000000，然后才可能rseAny。
- Kernel:2308–2312，`roundSelect`先检查`product<2^48 && scale<=123`，之后分别进入roundLow或roundP。
- Kernel:1998起，`FastMul.roundP`也首先检查product==0，只有非零才fastLog2。
- Kernel:2330–2341，LowScale.core在调用roundSelect前完成sign、fraction、finiteMantissa、finiteScale、product与scale和。LowScale.mul还保留special检查。

[zero-route-c-audit.json](zero-route-c-audit.json)绑定原C SHA `31e1409237ccf2e66b3b107a1ff8b3a257c9faa4e2786749c624b6aac03ccbc2`和DF SHA `df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172`。23个关键位置已从此前核验的完整mul函数逐字匹配，并映射回原C行；[带原行号摘录](zero-route-numbered-excerpts.txt)可直接复核。

## 实际旧C的执行顺序

以下行号指原1430091B的Submission.c，非精简摘录。源码中的join point排版与控制流顺序不同，必须跟goto。

| 顺序 | 原C位置 | zero×finite低路可见工作 |
|---|---|---|
| 1 | 21954–21963 | 两次移位、两个exponent mask、ex+ey和及<128判断；ex/ey随后复用 |
| 2 | 21990–21998，23588 | 两个原字左移1及与0xff000000比较，计算FastMul.special；所讨论域两边皆非特殊，因此落入23588的普通分支 |
| 3 | 23594、23570、23543 | 两个sign mask/zero比较，Bool.xor被降为分支/joinpoint；不是调用浮点算术 |
| 4 | 23503–23506、23475 | 两个fraction mask、两侧exp==0；每侧取64位尾数，normal的一侧OR隐藏位，zero一侧尾数0 |
| 5 | 23448、23418 | 两侧exponent转UInt64及zero测试，normal scale=e−1，zero scale=0 |
| 6 | 23248–23251 | 一次UInt64尾数乘法、一次scale加法、product<2^48判断 |
| 7 | 23264 | scale<=123判断；再进入其中一个rounder |
| 8a | 23277，23401/23407 | roundLow检查product==0，按符号立即返回 |
| 8b | 23199，23235/23241 | roundP检查product==0，按符号立即返回；23204的fastLog2第一移位不执行 |

所有上述word函数在固定lean.h中是static inline：UInt32位运算约2098起，UInt32→UInt64为2120，UInt64算术为2130起、比较为2149起。此条C控制流未进入FloatLib后端、lean_apply、对象分配、table load、Float32 of_bits/to_bits、nonNaN结果守卫。那些站点存在于完整mul函数的其他分支，不能算到zero×finite低路。

“转UInt64”“mask”“branch”等是源级操作，不是保证存在的机器指令数。这个表不做静态站点→动态周期换算。

## 对cutoff84的精确增量域

已读scalar worker冻结方案：`ex+ey<=84`直接返回带符号零。若raw-zero判断放在该cutoff失败之后、仍在旧`ex+ey<128`分支内，则本次增量必为：

- 至少一侧原字magnitude为0；
- 另一侧是normal，原exponent为85–127；
- 两个零、zero×subnormal、zero×normal且exponent<=84均已被cutoff84覆盖，不计新增命中；
- exsum<128保证双方不可能exponent255，因为两个8位指数和最多510、不发生UInt32回卷；这个局部raw-zero守卫无须再验证另一侧finite。若移到全局mul入口，此结论失效，0×Inf/NaN必须保留原规格。

剩余域的旧rounder边界也很具体：

| 另一侧exponent | actual scale和 | 旧分支 | 已经避免 |
|---|---:|---|---|
| 85–124 | 84–123 | roundLow product==0早退 | RNE、全部Float32工作 |
| 125–127 | 124–126 | roundP product==0早退 | fastLog2、RNE、全部Float32工作 |

正负零与左右交换不改变这两种路径类别；返回符号仍须是输入sign XOR。

## 对新guard的支持与反方限制

若新guard紧接cutoff84之后并直接返回，它从当前生成C层面可绕开旧special检查、fraction/mantissa构造、scale构造、UInt64 product及scale和、roundSelect两个守卫和rounder迟到的productzero测试。仍需计算正确sign；原入口exsum与cutoff判断已经花费，不算节省。

这给出一个**有限但实际的源级机制差异**：把“构造product后发现0”移到“读取raw magnitude时发现0”。不能说旧zero路径还付出了高价位数搜索或舍入。

反方约束：

1. 新guard也让剩余的非零low输入支付magnitude检查/短路分支。只报zero命中频率不足以判断净收益。
2. C中已有ex/ey共享，没有重复提取指数可供额外计算收益；small-word转换不等于堆分配。
3. Clang O3可能把两支相同product==0早退合并、把scale计算后移、消除逻辑上冗余的product/特殊值守卫，甚至识别zero尾数路径。未取得此精确计时MainFull的对应机器码，不能保证表内工作都实际发生。
4. 前置raw-zero检测本身也可能与现有zero-mantissa分支CSE收敛；相反也可能改变分支预测或代码布局。当前没有证明哪种发生。
5. 即使最终确实少一次integer multiply及若干word分支，也没有whole提升幅度证据；不能继承cutoff84或矩阵候选的收益。

建议根把它保留为“证明成本低、增量域明确、潜在省掉有限prefix”的小候选，而非重型舍入优化。是否值得开发由额外域真实曝光、原始gate剩余时间与CI容量决定。首个有效证伪是精确新版本与DF在所选mul入口的最终代码差异：若原zero路径已等价早退或新增guard只留下非零成本，就不应指望此机制；若有明确差异，再以自己的完整D决定。这里不派发任何检查，也不推导收益。

