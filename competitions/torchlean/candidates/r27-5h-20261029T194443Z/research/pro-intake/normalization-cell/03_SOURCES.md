# 源身份、位置与证据台账

## 直接输入

本轮唯一任务附件为 `research-materials-r28.txt`，278,657 UTF-8字节。已按BEGIN/END区段提取并核对原字节哈希；这些提取文件仅供内部阅读，未放入交付zip。

| 区段 | 字节 | SHA256 |
|---|---:|---|
| RETIRED_PUBLIC23_KERNEL | 252639 | `1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe` |
| CONTRACT_EXACT_OLD_PIN_UNCHANGED_PROOF_ID | 16879 | `bddd6bd9caa19f9419e0e38cd553b109a7675fc710fdf82a6d6f7d0f2a4c8b1b` |
| OWN_FP_COST_HELPER_NOT_PROVED | 6739 | `1762a473178d3a45b431c94b995a2616fd4b939dd5b98d65f40ada71dfc2c892` |

输入说明声明Lean4.34.0、单文件只import ContractExact、256000B上限，且允许公理仅propext/Classical.choice/Quot.sound。本轮未独立解析FloatLib的完整固定commit，未安装/更换工具链。43源码不可见；`43/23=0.9072362322024092`来自输入说明，不能标作直接同机测量。

## 本报告的主要源码锚点

以下是原附件 `research-materials-r28.txt` 的函数起始行；提取出的Public23.lean行号比它小8。

| 事实/证明桥 | 起始行 |
|---|---:|
| Y2 / Y6 / Y7 | 1002 / 1005 / 1008 |
| YaD / YF / Y8 | 1021 / 1024 / 1029 |
| V1 / V0：denominator与mean语义 | 1099 / 1102 |
| U9 / U8：完整有理式 | 1126 / 1129 |
| Y2L | 1639 |
| m64 | 1650 |
| dv128 | 1662 |
| FY / FX / FW | 1691 / 1694 / 1699 |
| FTk / FNk / FF / FFr | 1702 / 1711 / 1719 / 1726 |
| rsV | 1732 |
| Y8f | 2337 |
| MYa7b / MYa7 | 2368 / 2382 |
| rqU / rrsG | 2407 / 2411 |
| Ya7G | 2628 |
| Ya7Ge | 2699 |
| MYbc | 2914 |
| YaEf / Ybb2 | 2943 / 2966 |
| 最终kernels / correct | 2972 / 2978 |
| Contract imports | 2985 |
| Contract稳定norm语义说明 | 3007 |
| layernormWith / layernormSpec | 3207 / 3216 |

上述函数起始行已用脚本扫描核对；MANIFEST还记录源附件整体SHA256。本文以实际函数体和显式证明桥为证据，不用函数名字猜成本。

## 附加材料与限制

本轮浏览尝试读取官方pinned StableNorm/SqrtProof页面，返回DisabledError。没有访问竞赛API。工作区已有的旧公开缓存用于理解定义，但没有在本轮独立复核其pin，因此不据此宣称完成传递依赖字节审计。

Lean官方文档用于核对原生proposal API：

- [Floating-Point Numbers](https://lean-lang.org/doc/reference/latest/Basic-Types/Floating-Point-Numbers/)
- [Init.Data.Float.Float](https://lean-lang.org/doc/api/Init/Data/Float/Float.html)

它们支持标准类型/转换API的描述，不构成Lean4.34固定环境已编译的证据。未引用第三方性能数字。

## 证据台账

| 项目 | 结论 |
|---|---|
| 附件区段bytes/SHA | 已核对 |
| 上游源码改动 | 无 |
| 原创native候选编译 | NOT_COMPILED |
| 原创Lean脚本编译 | NOT_COMPILED |
| Python有限模型及反例 | PASS，见两个JSON及对应脚本 |
| word soundness theorem | OPEN |
| 全输入Submission.correct | OPEN |
| native/整模/冠军计时 | NOT_RUN |
| 10%以上收益 | 未建立；只有明确条件和首个否证实验 |
| 最终256000B提交文件 | 未构建，不能声称达标 |

源码计数、有限验证、数学推导与实测已分别列示。zip中不含上游Kernel、Contract、旧helper、原附件或缓存依赖。
