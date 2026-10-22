# 2026-10-22：完整包套件评分

本轮13:40 UTC核验官方公开源码，HEAD为 `a0e80de64aa5394a42b1c9a237c15047ec766f73`。新 [MANUAL](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/a0e80de64aa5394a42b1c9a237c15047ec766f73/MANUAL.md) 和 [BENCHMARKING](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/a0e80de64aa5394a42b1c9a237c15047ec766f73/docs/BENCHMARKING.md) 明确付费榜采用私有套件；公开练习套件为 `suites/public-v2.json`。服务实际部署配置未另行认证；源码规则和部署事实分列。

| 项目 | 旧固定环境 | 新套件环境 |
|---|---|---|
| 官方源 | pins.json的978cc5b4 | a0e80de6，独立临时checkout |
| 输入 | 十二计分类、固定长度/矩阵shape | dense/ml/sparse/specials/subnormal/paired/extremes，多种长度和shape |
| 准备与回退 | 原合同与原调用边界 | 原合同未变，计分包含特殊值、低指数及非finite回退 |
| 汇总 | 各类跨轮最小耗时之和 | 各case跨轮最小耗时之和；verdict按运算/组汇总 |
| 默认轮次 | 25配对轮 | 25配对轮，suite hash进入fingerprint |

只有相同suite/源码/工具链与精确候选的回执才能支持相应比较。旧份额、旧冠军逐类比值链保留为历史，不用于新套件排序。按新套件实测份额及命中/回退成本重新采用用户的收益准则。

新版verdict的cell耗时是每单位工作量耗时。复算headline、运算份额与组别成本时先乘该seed公开计划的cell工作量，再求和；直接把26个cell的ns相加会改变原评分口径。[真实回执红绿重放](../candidates/f01-d6-research/suite-parser-replay.json)已验证此差异。

原 pins、官方副本和历史回执保持原版。本轮新环境入口在 [suite-plan.json](../candidates/f01-d6-public-suite/suite-plan.json) 与 [public-suite.py](../candidates/f01-d6-research/public-suite.py)。它通过既有手动CI进入独立原版新gate，外层statement-only结果仅表示旧包编译；必须核对artifact内 `diagnostics/f01-d6-public-suite/public-suite/summary.json`、精确原始verdict、25轮、suite hash、前后fingerprint和官方源码clean结果，才可报告新版公开套件完整通过。

新环境沿用固定Lean4.34/FloatLib依赖并逐字节核对合同与manifest。公开套件使用官方建议的gate时间上限900秒；已启动运行自然完成回收。无需获取私有套件，也不作正式上传或资金操作。

原始官方响应、时间、SHA和差异在 [public-delta](../candidates/f01-d6-research/public-delta/official-compare-receipt.json)。当前运行与决定统一从 [开发状态](../coordination/development-status.json) 和 [R6](../candidates/f01-d6-research/README.md) 进入。
